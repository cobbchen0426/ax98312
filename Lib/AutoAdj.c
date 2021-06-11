/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************
#include "Include.h"

//******************************************************************************
// M A C R O   D E F I N I T I O N S
//******************************************************************************
#define LOOP_COUNTER        10 /*!< Count of iteration of ADC gain/offset calibration. */
#define ADC_GAIN_TOLERANCE   3 /*!< The tolerance of ADC gain calibration. */
#define ADC_OFFSET_TOLERANCE 3 /*!< The tolerance of ADC offset calibration. */
#define GetInputHActWid() (ReadShortScaler(&SC_GI_POS_HWID_LO) & 0x0FFF) /*!< Horizontal active pixel count from scaler. */
#define GetInputVActLen() (ReadShortScaler(&SC_GI_POS_VLEN_LO) & 0x07FF) /*!< Vertical active line count from scaler. */
#define GetInputHActBeg() (ReadShortScaler(&SC_GI_POS_HBEG_LO) & 0x0FFF) /*!< Horizontal start position count from scaler. */
#define GetInputVActBeg() (ReadShortScaler(&SC_GI_POS_VBEGO_LO) & 0x07FF) /*!< Vertical start position count from scaler. */

//******************************************************************************
// G L O B A L   V A R I A B L E S
//******************************************************************************

//******************************************************************************
// S T A T I C   V A R I A B L E S
//******************************************************************************
static BOOL bAbortAutoTune; /*!< Flag of status of auto-tune. */
static BOOL bIsNonFullScreen; /*!< Flag of status of full-screen. */
static xdata UCHAR ucPhaseRange; /*!< The range of phase calibration. The value would be 16 or 32. */
static xdata UCHAR ucPhaseIndexLo; /*!< Variable for auto-tune functions. */
static xdata UCHAR ucPhaseIndexHi; /*!< Variable for auto-tune functions. */
static xdata UCHAR ucAutoPct; /*!< Percentage of progress of auto-tune. */

//******************************************************************************
// E X T E R N A L   V A R I A B L E   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// S T A T I C   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
static void AutoTuneComplete(void);
static ULONG CheckPhaseData(void);
static BOOL AutoGainCoarse(void);
static BOOL MeasureImageSize(void);
static BOOL AutoClockByPhase(void);
static void CheckImageOutOfScreen(void);

//******************************************************************************
// E X T E R N A L   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// F U N C T I O N   B O D Y S
//******************************************************************************

/**************************************************************************//**
 * Check we can perform auto-tune on the the current input interface or not.
 * @return TRUE if interface is valid else FALSE.
 ******************************************************************************/
BOOL IsAutoTuneValid(void)
{
    UCHAR interface = GetCurrInputInterface();

    if ((interface == DIGITAL_INPUT0) || (interface == DIGITAL_INPUT1) || (interface == DISPLAY_PORT_INPUT)) {
        return FALSE;
    }
    return TRUE;
}

/**************************************************************************//**
 * Automatically find H/V start position, input clock and ADC phase
 * @return TRUE if auto-tune is succeeded else FALSE.
 ******************************************************************************/
BOOL AutoTune(void)
{
    UCHAR reg_bak1, reg_bak2;

#if AutoTune_Debug == ENABLE
printf("01_AutoTune\n");	//150526 george
#endif

//ResetWDTimer();				//150526 george
    if (!IsAutoTuneValid()) {
        return FALSE;
    }																											

    ucAutoPct = 4;

    reg_bak1 = SC_JITTER_CTRL;
    reg_bak2 = SC_VI_AUTO_CTRL;

    SC_JITTER_CTRL = 0x00;
    if ((SC_ADC_MID_CH_SEL & 0x07) == YPBPR_CLAMP) {
        SC_VI_AUTO_CTRL |= BIT7;
    }
    else {
        SC_VI_AUTO_CTRL &= ~BIT7;
    }

    bIsNonFullScreen = FALSE;
    bAbortAutoTune = FALSE;
    if (AutoPosition() == FALSE) {
        SC_JITTER_CTRL = reg_bak1;
        SC_VI_AUTO_CTRL = reg_bak2;
        AutoTuneComplete();
        return FALSE;
    }
    if ((bAbortAutoTune == FALSE) && (bIsNonFullScreen == FALSE)) {
        if (AutoClock() == FALSE) {
            SC_JITTER_CTRL = reg_bak1;
            SC_VI_AUTO_CTRL = reg_bak2;
            AutoTuneComplete();
            return FALSE;
        }
    }

    if (ucAutoPct < 100) {   
        OSDUpdateAutoTune(ucAutoPct++);
    }

    if (AutoClockByPhase() == FALSE) {
        SC_JITTER_CTRL = reg_bak1;
        SC_VI_AUTO_CTRL = reg_bak2;
        AutoTuneComplete();
        return FALSE;
    }

    if (AutoPhaseFineTune(ucPhaseRange) == FALSE) {
        SC_JITTER_CTRL = reg_bak1;
        SC_VI_AUTO_CTRL = reg_bak2;
        AutoTuneComplete();
        return FALSE;
    }

    if (AutoPosition() == FALSE) {
        SC_JITTER_CTRL = reg_bak1;
        SC_VI_AUTO_CTRL = reg_bak2;
        AutoTuneComplete();
        return FALSE;
    }
//ResetWDTimer();				//150526 george
    AutoTuneComplete();

    SC_JITTER_CTRL = reg_bak1;
    SC_VI_AUTO_CTRL = reg_bak2;

    return TRUE;
}

/**************************************************************************//**
 * Complete the remainder percentage of auto-tune.
 ******************************************************************************/
static void AutoTuneComplete(void)
{ 

#if AutoTune_Debug == ENABLE
printf("02_AutoTuneComplete\n");	//150526 george
#endif

    while (ucAutoPct < 100) {
        OSDUpdateAutoTune(ucAutoPct++);
        Sleep(20);
        if (CheckModeChangeFlag() == TRUE) {
            bAbortAutoTune = TRUE;
            return ;
        }
    }
    OSDUpdateAutoTune(100);

}

/**************************************************************************//**
 * Automatically find image H/V start position.
 * If system detect mode changed or non-full-screen content, system will stop AutoPosition.
 * @return TRUE if system succeed in finding H/V position else FALSE.
 ******************************************************************************/
BOOL AutoPosition(void)
{
#define MAX_THR_LEVEL 0xA0
#define MIN_THR_LEVEL 0x30
    USHRT temph, tempv, h_active, v_active;
    USHRT cap_vlen, cap_hwid;
    UCHAR thr_level, k;
    BOOL pass_fail;

#if AutoTune_Debug == ENABLE
printf("03_AutoPosition\n");	//150526 george
#endif

    cap_vlen = ReadShortScaler(&SC_GI_CAP_VLEN_LO) & 0x07FF;
    cap_hwid = ReadShortScaler(&SC_GI_CAP_HWID_LO) & 0x0FFF;
    SetHmask();
    SC_GI_AUTO_TUNE_CTRL = 0x00;

    for (thr_level=MIN_THR_LEVEL; thr_level<MAX_THR_LEVEL; thr_level+=0x10) {
        SC_GI_POS_THR = thr_level; //Red Noise Margin
        
        for (k=0; k<5; k++) {
            if (MeasureImageSize() == TRUE) {
                tempv = GetInputVActLen();
                temph = GetInputHActWid();
                if ((tempv > 0x100) && (temph > 0x100)) {
                    pass_fail = TRUE;//pass
                }
                else {
                    pass_fail = FALSE;//fail
                }
            }
            else {
                return FALSE;
            }
            if (pass_fail == FALSE) {
                break;
            }
        }
        if (k == 5) {
            break;
        }
    }

    if (thr_level > MAX_THR_LEVEL) {
        return FALSE;
    }

    //SC_GI_POS_THR = 0x40; //Red Noise Margin
    if (MeasureImageSize() == TRUE) {
        v_active = GetInputVActLen();
        h_active = GetInputHActWid();
        if ((abs(h_active-temph) > 5) || (abs(v_active-tempv) > 5)) {
            bIsNonFullScreen = TRUE;
            CheckImageOutOfScreen();
            return FALSE;
        }
    }
    else {
        return FALSE;
    }

    temph = GetInputHActBeg();
    tempv = GetInputVActBeg();
    if (IsHNonFullScreen(temph,h_active)) {
        bIsNonFullScreen = TRUE;
        CheckImageOutOfScreen();
        return FALSE;
    }
    SetHP(temph);

    if (!IsVNonFullScreen(tempv,v_active)){
    SetVP(tempv);
    }

    return TRUE;
}

/**************************************************************************//**
 * Check current input content is full-screen or not.
 * @return TRUE if content is full-screen else FALSE.
 ******************************************************************************/
void CheckImageOutOfScreen(void)
{
    USHRT h_start, v_start, h_active, v_active;
    USHRT cap_vlen, cap_hwid, cap_vstart, cap_hstart, ref;

#if OTHER_Degub == ENABLE
	printf("04_CheckImageOutOfScreen\n");	//150526 george
#endif

    cap_vlen = ReadShortScaler(&SC_GI_CAP_VLEN_LO) & 0x07FF;
    cap_hwid = ReadShortScaler(&SC_GI_CAP_HWID_LO) & 0x0FFF;
    cap_vstart = ReadShortScaler(&SC_GI_CAP_VBEGO_LO) & 0x07FF;
    cap_hstart = ReadShortScaler(&SC_GI_CAP_HBEG_LO) & 0x0FFF;
    v_active = GetInputVActLen();
    h_active = GetInputHActWid();
    v_start = GetInputVActBeg();
    h_start = GetInputHActBeg();

    if ((v_active < cap_vlen) && (v_start < GetInputVTotal())) {//vertical small then screen
        if (v_start > cap_vstart) {//down
            ref = v_active + v_start - cap_vstart;
            if (ref > cap_vlen) {
                cap_vstart = ref - cap_vlen + cap_vstart;
            }
        }
        else {//up
            cap_vstart = v_start;
        }
    }
    if ((h_active < cap_hwid) && (h_start < GetAngInputHTotal())) {//horizontal small then screen
        if (h_start > cap_hstart) {//right
            ref = h_active + h_start - cap_hstart;
            if (ref > cap_hwid) {
                cap_hstart = ref - cap_hwid + cap_hstart;
            }
        }
        else {//left
            cap_hstart = h_start;
        }
    }

    // Avoid InputTiming.usHStart < Min, make Hstart related operation abnormal, ex: OSD SliderBar overflow
    if (cap_hstart < InputTiming.usHStartMin) 
        cap_hstart = InputTiming.usHStartMin;
    else if (cap_hstart > InputTiming.usHStartMax)
        cap_hstart = InputTiming.usHStartMax;

    SetHP(cap_hstart);
    SetVP(cap_vstart);

    InputTiming.usHStart = GetInputHStart();
    InputTiming.usVStart = GetInputVStart();
//    InputTiming.usHStart50 = InputTiming.usHStart;
//    InputTiming.usVStart50 = InputTiming.usVStart;

}

/**************************************************************************//**
 * Waiting for scaler to complete the image size detection .
 * The detection includes H/V start position, width and height.
 * The maximum waiting time is 100ms.
 * If the time is over 100ms, the function will return FASLE.
 * @return TRUE if the detection is completed else FALSE.
 ******************************************************************************/
static BOOL MeasureImageSize(void)
{
    BOOL i;
    USHRT local_timer;

#if AutoTune_Debug == ENABLE
printf("05_MeasureImageSize\n");	//150526 george
#endif

    i = FALSE;
    SC_GI_AUTO_TUNE_CTRL = 0x41;

    local_timer = GetTimerTick();
    do {
        ResetWDTimer();
        if (CheckModeChangeFlag() == TRUE) {
            break;
        }
        if ((SC_GI_AUTO_TUNE_CTRL & BIT0) == 0) {
            i = TRUE;
            break;
        }
    } while ((GetTimerTick()-local_timer) < 100);

    if (i == FALSE) {
        bAbortAutoTune = TRUE;
    }
    return i;
}

/**************************************************************************//**
 * Automatically find the best htotal (HPLL divider)  to the present analog timing.
 * If content is not full-screen, the function will return FALSE.
 * @return TRUE if the function is completed else FALSE.
 ******************************************************************************/
BOOL AutoClock(void)
{
    UCHAR h_difference, i, compare;
    USHRT h_ref, h_max, h_total, h_active, h_total_bak;

#if AutoTune_Debug == ENABLE
 printf("06_AutoClock\n");	//150526 george
#endif

    h_ref = ReadShortScaler(&SC_GI_CAP_HWID_LO);
    h_max = h_ref<< 1 ;
    //Set H active reference
    WriteShortScaler(&SC_GI_CLK_REF_LO, h_ref);
    //Read pll divider
    h_total = ReadShortScaler(&SC_HSDDS_DIVIDER_LO);
    h_total_bak = h_total;

    if (h_total <= h_ref) {
        h_total = h_ref + 16;
        SetADCPLL2(h_total);
    }

    for (i=0; i<0x20; i++) {  
        SetHmask();
        if (MeasureImageSize() == TRUE) {
            h_active = GetInputHActWid();
            h_difference = SC_GI_CLK_RESULT;
            compare = (h_difference & 0xC0) >> 6;
            h_difference = h_difference & 0x3F;
            if (compare == 0x00) { //h_ref is equal to h_active
                break;
            }
            if (compare == 0x01) { //less than
                h_total = h_total + h_difference;
                if (h_total > h_max) {
                    i = 0xFF;
                    break;
                }
            }
            if (compare > 0x01) { //greater than
                h_total = h_total - h_difference;
                if (h_total < h_ref) {
                    i = 0xFF;
                    break;
                }
            }
            if (CheckADCPLLOutOfRange(h_total) == TRUE) {
                i = 0xFF;
                break;
            }
            SetADCPLL2(h_total);
        }
        else {
            SetADCPLL2(h_total_bak);
            return FALSE;
        }
    }

    if (i == 0xFF) {
        SetADCPLL2(h_total_bak);
        bIsNonFullScreen = TRUE;
        return FALSE;
    }
    else {
        return TRUE;
    }

}

/**************************************************************************//**
 * Automatically find tune the HPLL phase setting.
 * If system detect mode changed, the function will return FALSE.
 * @return TRUE if the function is completed else FALSE.
 ******************************************************************************/
BOOL AutoPhaseFineTune(UCHAR len)
{
    UCHAR qq, yy, uu, i, k;
    ULONG phase_0, phase_1, phase_2, phase_pre3, phase_now3, phase_delta;
    USHRT local_timer;

#if AutoTune_Debug == ENABLE
 printf("07_AutoPhaseFineTune\n");	//150526 george
#endif

    phase_1 = 0x00000000; //(i-1)
    phase_2 = 0x00000000; //(i-2)
    phase_pre3 = 0x00000000; //(pre sum)->(delta)->(now sum)
    phase_delta = 0xFFFFFFFF; //(min delta)
    qq = SC_HPLL_PHASE_CTRL1 & 0x3F;
    SC_GI_AUTO_TUNE_CTRL = 0x42;

    for (yy=1; yy<len; yy++) {
        if (ucAutoPct < 100) {
            OSDUpdateAutoTune(ucAutoPct++);
        }

        k = 0;
        local_timer = GetTimerTick();
        do {
            ResetWDTimer();
            if (CheckModeChangeFlag() == TRUE) {
                bAbortAutoTune = TRUE;
                return FALSE;
            }
            if ((SC_GI_AUTO_TUNE_CTRL & BIT1) == 0) {
                k = 1;
                break;
            }
        } while ((GetTimerTick()-local_timer) < 100);

        if (k == 0) {
            bAbortAutoTune = TRUE;
            return FALSE;
        }
        k = (qq + yy) & 0x3F;
        SetADCPhase(k);

        SC_GI_AUTO_TUNE_CTRL = 0x42;

        phase_now3 = ReadShortScaler(&SC_GI_PHS_SDIFF_HI0);
        phase_now3 <<= 16;
        phase_now3 += ReadShortScaler(&SC_GI_PHS_SDIFF_LO0);
        i = (k - 1) & 0x3F;

        phase_2 = phase_1; //Shift    
        phase_1 = phase_0;
        phase_0 = phase_now3;
        phase_now3 = (phase_0>>2) + (phase_1>>1) + (phase_2>>2);
        if (yy < 4) {
            phase_pre3 = phase_now3; //phase_pre3 = phase_now3
        }
        else {
            if (phase_now3 > phase_pre3) {
                phase_pre3 = phase_now3 - phase_pre3;
            }
            else {
                phase_pre3 = phase_pre3 - phase_now3; //phase_pre3 = delta
            }
            if (phase_pre3 < phase_delta) {
                uu = i;           
                phase_delta = phase_pre3;
            }
            phase_pre3 = phase_now3; //phase_pre3 = phase_now3
        }     
    }
    k = (uu - 1) & 0x3F;
    SetADCPhase(k);

    return TRUE;
}

/**************************************************************************//**
 * Calibrate the ADC offset of R/G/B channels.
 * This function will perform simple auto-gain function first then h/w auto-offset.
 * @return TRUE if the calibration is succeeded else FALSE.
 ******************************************************************************/
BOOL AutoOffset(void)
{
#if AutoTune_Debug == ENABLE
printf("08_AutoOffset\n");	//150526 george
#endif

    if (AutoGainCoarse() == TRUE) {
        return HwAutoOffset();
    }
    else {
        return FALSE;
    }
}

/**************************************************************************//**
 * Calibrate the ADC offset of R/G/B channels by scaler.
 * @return TRUE if the calibration is succeeded else FALSE.
 ******************************************************************************/
BOOL HwAutoOffset(void)
{
    USHRT local_timer, totalRGB[3];
    UCHAR rgb[3], rgbbk[3], k, value;

#if PWRSeq_Deug == ENABLE
printf("09_HwAutoOffset\n");	//150526 george
#endif

#if IS_NT68150_SERIES
    SC_CAP_SWAP |= BIT5;
#endif

    rgbbk[0] = GetADCROffset();
    rgbbk[1] = GetADCGOffset();
    rgbbk[2] = GetADCBOffset();

    rgb[0] = 0;
    rgb[1] = 0;
    rgb[2] = 0;
    SetADCROffset(0);
    SetADCGOffset(0);
    SetADCBOffset(0);

#if IS_NT68750_SERIES// || IS_NT68770_SERIES || IS_NT68850_SERIES || IS_NT68655_SERIES
    SC_VI_AUTO_CTRL |= BIT5;

    SC_AUTO_OFFSET_TARGET_RED = 0x00;
    SC_AUTO_OFFSET_TARGET_GREEN = 0x00;
    SC_AUTO_OFFSET_TARGET_BLUE = 0x00;
#else
    SC_AUTO_OFFSET_TARGET_GREEN = 0x00;
    if ((SC_ADC_MID_CH_SEL & 0x07) == YPBPR_CLAMP) {
        SC_AUTO_OFFSET_TARGET_RED = 0x80;
        SC_AUTO_OFFSET_TARGET_BLUE = 0x80;
    }
    else {
        SC_AUTO_OFFSET_TARGET_RED = 0x00;
        SC_AUTO_OFFSET_TARGET_BLUE = 0x00;
    }
#endif

    SC_AUTO_OFFSET_CTRL2 = 0x80;
    SC_AUTO_OFFSET_CTRL3 = 0x03;
    
    k = LOOP_COUNTER;
    totalRGB[0] = 0;
    totalRGB[1] = 0;
    totalRGB[2] = 0;

    local_timer = GetTimerTick();
    do {
        ResetWDTimer();
        Sleep(2);
        if (CheckModeChangeFlag() == TRUE) {
            k = LOOP_COUNTER;
            break;
        }
        else {
            value = GetADCROffset();
            if (abs(rgb[0] - value) > ADC_OFFSET_TOLERANCE) {
                k = LOOP_COUNTER;
            }
            rgb[0] = value;
            value = GetADCGOffset();
            if (abs(rgb[1] - value) > ADC_OFFSET_TOLERANCE) {
                k = LOOP_COUNTER;
            }
            rgb[1] = value;
            value = GetADCBOffset();
            if (abs(rgb[2] - value) > ADC_OFFSET_TOLERANCE) {
                k = LOOP_COUNTER;
            }
            rgb[2] = value;
            if (k == LOOP_COUNTER) {//reset totalRGB[]
                totalRGB[0] = rgb[0];
                totalRGB[1] = rgb[1];
                totalRGB[2] = rgb[2];
            }
            else {//accumulate
                totalRGB[0] += rgb[0];
                totalRGB[1] += rgb[1];
                totalRGB[2] += rgb[2];
            }
            if (--k == 0) {
                rgb[0] = totalRGB[0] / LOOP_COUNTER;
                rgb[1] = totalRGB[1] / LOOP_COUNTER;
                rgb[2] = totalRGB[2] / LOOP_COUNTER;
            }
        }
    } while ((k != 0) && ((GetTimerTick() - local_timer) < 300));

    SC_AUTO_OFFSET_CTRL2 = 0x00;
    SC_AUTO_OFFSET_CTRL3 = 0x00;

#if IS_NT68150_SERIES
    SC_CAP_SWAP &= ~BIT5;
#endif
    if (k != 0) {
        SetADCROffset(rgbbk[0]);
        SetADCGOffset(rgbbk[1]);
        SetADCBOffset(rgbbk[2]);
        return FALSE;
    }

    if ((SC_ADC_MID_CH_SEL & 0x07) == YPBPR_CLAMP) {
        SetADCROffset(rgb[0]);
        SetADCGOffset(rgb[1] + ADC_OFFSET_ADJ);
        SetADCBOffset(rgb[2]);
    }
    else {
        SetADCROffset(rgb[0] + ADC_OFFSET_ADJ);
        SetADCGOffset(rgb[1] + ADC_OFFSET_ADJ);
        SetADCBOffset(rgb[2] + ADC_OFFSET_ADJ);
    }

    return TRUE;
}

/**************************************************************************//**
 * Calibrate the ADC gain of R/G/B channels.
 * If we enable ENABLE_HW_AUTOCOLOR, this function will call h/w ADC gain calibration.
 * Otherwise, f/w based calibration will be performed.
 * @return TRUE if the calibration is succeeded else FALSE.
 ******************************************************************************/
BOOL AutoGain(void)
{
#if ENABLE_HW_AUTOCOLOR == ON
    return HWAutoGain();
#else
    UCHAR i, j, k, m, n, value, *p, offset, bak[3];
    USHRT local_timer;
    ULONG phase_result, temp, basic_level;
    BOOL time;

#if AutoTune_Debug == ENABLE
printf("10_AutoGain\n");	//150526 george
#endif

    bak[0] = GetADCRGain();
    bak[1] = GetADCGGain();
    bak[2] = GetADCBGain();
    SC_GAUGE_OFFSET = 0xF8;
    basic_level = ReadShortScaler(&SC_GI_CAP_VLEN_LO);
    for (m=0; m<3; m++) {
        i = 0x001 + m * 3; //1,4,7
        p = &SC_ADC_CTRL;
        p += i;
        offset = *p;
        for (k=offset; k>7; k=k-8) {
            SC_GAUGE_CTRL2 = 0x00;
            i = 0x001 + m * 3; //1,4,7
            p = &SC_ADC_CTRL;
            p += i;
            *p = k;
            i = 0x80 + (2-m)*0x08;
            SC_GAUGE_CTRL2 = i;
            time = 0;
            local_timer = GetTimerTick();
            do {
                ResetWDTimer();
                if (CheckModeChangeFlag() == TRUE) {
                    bAbortAutoTune = TRUE;
                    break;
                }
                if ((SC_GAUGE_CTRL2 & BIT7) == 0) {
                    time = 1;
                    break;
                }
            } while((GetTimerTick() - local_timer) < 100);
    
            if (time == 0) {
                bAbortAutoTune = TRUE;
            }
            if (bAbortAutoTune == TRUE) {
                SetADCRGain(bak[0]);
                SetADCGGain(bak[1]);
                SetADCBGain(bak[2]);
                return FALSE;
            }

            j = 0;
            temp = 0;
            for (i=0; i<8; i++) {
                SC_GAUGE_AREA_SEL = i;
                phase_result = ReadShortScaler(&SC_GAUGE_RESULT_MI);
                phase_result <<= 8;
                value = SC_GAUGE_RESULT_LO;
                phase_result += value;
                //printf("phase_result %x = %x %ld\r\n",(USHRT)m,(USHRT)k,(phase_result));
                if (phase_result > (basic_level*3)) {
                    j = 0xFF;
                    break;
                }
            }
            if (j != 0) {
                break;
            }
        }
        if (k == 0) {
            bAbortAutoTune = TRUE;
            SetADCRGain(bak[0]);
            SetADCGGain(bak[1]);
            SetADCBGain(bak[2]);
            return FALSE;
        }
        for (n=0; n<16; n++) {
            SC_GAUGE_CTRL2 = 0x00;
            i = 0x001 + m * 3; //1,4,7
            p = &SC_ADC_CTRL;
            p += i;
            *p = k-n;
            i = 0x80 + (2-m)*0x08;
            SC_GAUGE_CTRL2 = i;
            time = 0;
            local_timer = GetTimerTick();
            do {
                ResetWDTimer();
                if (CheckModeChangeFlag() == TRUE) {
                    bAbortAutoTune = TRUE;
                    break;
                }
                if ((SC_GAUGE_CTRL2 & BIT7) == 0) {
                    time = 1;
                    break;
                }
            } while ((GetTimerTick() - local_timer) < 100);
    
            if (time == 0) {
                bAbortAutoTune = TRUE;
            }
            if (bAbortAutoTune == TRUE) {
                SetADCRGain(bak[0]);
                SetADCGGain(bak[1]);
                SetADCBGain(bak[2]);
                return FALSE;
            }
            j = 0;
            temp = 0;
            SC_GAUGE_AREA_SEL = 7;
            phase_result = ReadShortScaler(&SC_GAUGE_RESULT_MI);
            phase_result <<= 8;
            value = SC_GAUGE_RESULT_LO;
            phase_result += value;
            //printf("phase_result %x = %x %ld\r\n",(USHRT)m,(USHRT)n,phase_result);
            if (phase_result > (basic_level * 10)) {//80
                break;
            }
        }       
        i = 0x001 + m * 3;  //1,4,7
        j = k-n;
        p = &SC_ADC_CTRL;
        p += i;
        *p = j;
        //printf("Gain %x = %x %x\r\n",(USHRT)m,(USHRT)k,(USHRT)j);
    }

    return TRUE;
#endif
}

/**************************************************************************//**
 * Calibrate the ADC gain of R/G/B channels by scaler.
 * @return TRUE if the calibration is succeeded else FALSE.
 ******************************************************************************/
#if ENABLE_SELF_AUTOCOLOR == ON
BOOL HWAutoGain(void)
{
    USHRT local_timer, totalRGB[3];
    UCHAR rgb[3], rgbbk[3], k, value;


#if OTHER_Degub == ENABLE
	printf("11_HWAutoGain\n");	//150526 george
#endif

#if IS_NT68150_SERIES
    SC_CAP_SWAP |= BIT5;
#endif

    rgbbk[0] = GetADCRGain();
    rgbbk[1] = GetADCGGain();
    rgbbk[2] = GetADCBGain();

    SetADCInput(ADC_INPUT_INT_WHITE);
    SC_ADC_TRIM_CTRL |= BIT7;

    SC_AUTO_GAIN_CTRL2 = 0x71;
    SC_AUTO_GAIN_CTRL3 = 0xFF;
    SC_AUTO_GAIN_CTRL4 = 0x00;

    rgb[0] = 0;
    rgb[1] = 0;
    rgb[2] = 0;
    SetADCRGain(0xFF);
    SetADCGGain(0xFF);
    SetADCBGain(0xFF);

#if 1
    SC_AUTO_OFFSET_TARGET_RED = 0xF4;
    SC_AUTO_OFFSET_TARGET_GREEN = 0xF1;
    SC_AUTO_OFFSET_TARGET_BLUE = 0xEC;
#else
    SC_AUTO_OFFSET_TARGET_RED = 0xF5;
    SC_AUTO_OFFSET_TARGET_GREEN = 0xF4;
    SC_AUTO_OFFSET_TARGET_BLUE = 0xF0;
#endif

    SC_AUTO_OFFSET_CTRL2 = 0x80;
    SC_AUTO_OFFSET_CTRL3 = 0x03;
    
    k = LOOP_COUNTER;
    totalRGB[0] = 0;
    totalRGB[1] = 0;
    totalRGB[2] = 0;

    local_timer = GetTimerTick();
    do {
        ResetWDTimer();
        Sleep(2);
        if (CheckModeChangeFlag() == TRUE) {
            k = LOOP_COUNTER;
            break;
        }
        else {
            value = GetADCRGain();
            if (abs(rgb[0] - value) > ADC_GAIN_TOLERANCE) {
                k = LOOP_COUNTER;
            }
            rgb[0] = value;
            value = GetADCGGain();
            if (abs(rgb[1] - value) > ADC_GAIN_TOLERANCE) {
                k = LOOP_COUNTER;
            }
            rgb[1] = value;
            value = GetADCBGain();
            if (abs(rgb[2] - value) > ADC_GAIN_TOLERANCE) {
                k = LOOP_COUNTER;
            }
            rgb[2] = value;
            if (k == LOOP_COUNTER) {//reset totalRGB[]
                totalRGB[0] = rgb[0];
                totalRGB[1] = rgb[1];
                totalRGB[2] = rgb[2];
            }
            else {//accumulate
                totalRGB[0] += rgb[0];
                totalRGB[1] += rgb[1];
                totalRGB[2] += rgb[2];
            }
            if (--k == 0) {
                rgb[0] = totalRGB[0] / LOOP_COUNTER;
                rgb[1] = totalRGB[1] / LOOP_COUNTER;
                rgb[2] = totalRGB[2] / LOOP_COUNTER;
            }
        }
    } while ((k != 0) && ((GetTimerTick() - local_timer) < 300));

    SC_AUTO_OFFSET_CTRL2 = 0x00;
    SC_AUTO_OFFSET_CTRL3 = 0x00;

    SC_ADC_TRIM_CTRL &= ~BIT7;
    SC_AUTO_GAIN_CTRL2 = 0x00;
    SetADCInput(ADC_INPUT_EXT_RGB);
#if IS_NT68150_SERIES
    SC_CAP_SWAP &= ~BIT5;
#endif

    if (k != 0) {
        SetADCRGain(rgbbk[0]);
        SetADCGGain(rgbbk[1]);
        SetADCBGain(rgbbk[2]);
        return FALSE;
    }

    SetADCRGain(rgb[0] + ADC_GAIN_ADJ);
    SetADCGGain(rgb[1] + ADC_GAIN_ADJ);
    SetADCBGain(rgb[2] + ADC_GAIN_ADJ);
    return TRUE;
}
#endif

/**************************************************************************//**
 * Check we can perform auto-color on the the current input interface or not.
 * @return TRUE if the interface is valid else FALSE.
 ******************************************************************************/
BOOL IsAutoColorValid(void)
{
    UCHAR interface = GetCurrInputInterface();

#if OTHER_Degub == ENABLE
	printf("12_IsAutoColorValid\n");	//150526 george
#endif

    if ((interface == DIGITAL_INPUT0) ||(interface == DIGITAL_INPUT1) ||(interface == DISPLAY_PORT_INPUT)) 
	{
       	 return FALSE;
    	}

   		 return TRUE;
}

/**************************************************************************//**
 * Perform auto-color function with external signal.
 * @return TRUE if auto-color is succeeded else FALSE.
 ******************************************************************************/
BOOL AutoColor(void)
{
    UCHAR reg_bak1, reg_bak2, rgb[6];

#if OTHER_Degub == ENABLE
	printf("13_AutoColor\n");	//150526 george
#endif

    if (!IsAutoColorValid()) 
	{
       	 return FALSE;
    	}

    reg_bak1 = SC_JITTER_CTRL;
    reg_bak2 = SC_VI_AUTO_CTRL;
     
    SC_JITTER_CTRL = 0x00;
    SC_VI_AUTO_CTRL &= ~BIT5;
    
    bAbortAutoTune = FALSE;

    //offset
    rgb[0] = GetADCROffset();
    rgb[1] = GetADCGOffset();
    rgb[2] = GetADCBOffset();
    //gain
    rgb[3] = GetADCRGain();
    rgb[4] = GetADCGGain();
    rgb[5] = GetADCBGain();

    if (AutoOffset() == TRUE) 
	{
       	 if (AutoGain() == FALSE) 
		 {
           		 bAbortAutoTune = TRUE;
        	}
    	}
    else {
        bAbortAutoTune = TRUE;
    }

    if (bAbortAutoTune == TRUE) {
        //offset
        SetADCROffset(rgb[0]);
        SetADCGOffset(rgb[1]);
        SetADCBOffset(rgb[2]);
        //gain
        SetADCRGain(rgb[3]);
        SetADCGGain(rgb[4]);
        SetADCBGain(rgb[5]);

        // We do not have to invoke offset again.
        //HwAutoOffset();
        //bAbortAutoTune = TRUE;
    }
#if 0//(ModelName == AOC_e2252Vw && defined(AUO_M215HW01_VB)) || (ModelName == AOC_e2351Fh&&defined(LPL_BM230WF5_TJC1)) || (ModelName==AOC_i2353Ph&&defined(LPL_BM230WF3_SJC1))||(ModelName==Envision_G2465Wgl && defined(CMI_M236H3_LA3))////v31_110803_1530_SYS#4
    else {
        SetADCRGain(GetADCRGain() - 5);
        SetADCGGain(GetADCGGain() - 5);
        SetADCBGain(GetADCBGain() - 5);
    }
#endif

    SC_JITTER_CTRL = reg_bak1;
    SC_VI_AUTO_CTRL = reg_bak2;
    return !bAbortAutoTune;
}

/**************************************************************************//**
 * Perform auto-color function with internal white level.
 * @return TRUE if auto-color is succeeded else FALSE.
 ******************************************************************************/
#if ENABLE_SELF_AUTOCOLOR == ON
BOOL InternalAutoColor(void)
{
    UCHAR reg_bak1, reg_bak2, result;

#if OTHER_Degub == ENABLE
	printf("14_InternalAutoColor\n");	//150526 george
#endif

    result = FALSE;
    reg_bak1 = SC_JITTER_CTRL;
    reg_bak2 = SC_VI_AUTO_CTRL;

    SC_JITTER_CTRL = 0x00;
    SC_VI_AUTO_CTRL &= ~BIT5;

    EnableSyncProcFreeRun(TRUE);
    SetADCInput(ADC_INPUT_INT_GND);
    if (HwAutoOffset()) {
        SetADCInput(ADC_INPUT_INT_WHITE);
        if (HWAutoGain()) {
            result = TRUE;
        }
    }

    SetADCInput(ADC_INPUT_EXT_RGB);
    EnableSyncProcFreeRun(FALSE);

    SC_JITTER_CTRL = reg_bak1;
    SC_VI_AUTO_CTRL = reg_bak2;

    return result;
}
#endif

/**************************************************************************//**
 * Automatically fine tune htotal with best ADC phase.
 * @return TRUE if the function is succeeded else FALSE.
 ******************************************************************************/
static BOOL AutoClockByPhase(void)
{
    #define CLOCKFINETUNESTEP 2

    UCHAR k,templ,temph;
    USHRT good_dot_clock, poor_dot_clock, htotal;
    ULONG maximum_delta, value, minimum_delta;

#if AutoTune_Debug == ENABLE
printf("15_AutoClockByPhase\n");	//150526 george    
#endif

	htotal = ReadShortScaler(&SC_HSDDS_DIVIDER_LO);
    good_dot_clock = htotal;
    poor_dot_clock = htotal;
    maximum_delta = 0;
    minimum_delta = 0xFFFFFFFF;
    htotal -= CLOCKFINETUNESTEP; //2005-05-25 mingyu: reduce fine tune time change to 2 times from 5 times
    for (k=0; k<(CLOCKFINETUNESTEP+2); k++) {
        SetADCPLL2(htotal);
        //WaitSetup(40);
        value = CheckPhaseData();
        if (bAbortAutoTune == TRUE)
            return FALSE;
        if (maximum_delta < value) {
            good_dot_clock = htotal;
            maximum_delta = value;
            templ = ucPhaseIndexLo;
            temph = ucPhaseIndexHi;
        }
        if (minimum_delta > value) {
            minimum_delta = value;
            poor_dot_clock = htotal;
        }
        htotal ++;
    }

    htotal = good_dot_clock;

    if (abs(good_dot_clock - poor_dot_clock) != 1) {
        htotal &= 0xfffe;
    }

    SetADCPLL2(htotal);
    if (good_dot_clock != htotal) {
        value = CheckPhaseData();
        maximum_delta = value;
        templ = ucPhaseIndexLo;
        temph = ucPhaseIndexHi;
    }

    good_dot_clock = ReadShortScaler(&SC_GI_CAP_HWID_LO);
    poor_dot_clock = ReadShortScaler(&SC_GI_CAP_VLEN_LO);
    value = (ULONG)good_dot_clock * poor_dot_clock *64; //V028, FIND BEST IN PAT-1
    //printf("Value=%ld\r\n", Value);
    //printf("maximum_delta=%ld\r\n", maximum_delta);
    if (maximum_delta < value) {
        k = (templ + 24) & 0x3F;
        ucPhaseRange = 32;
        //printf("REVERSE 180\r\n");
    }
    else {
        k = (temph - 8) & 0x3F;
        ucPhaseRange = 16;
        //printf("FIND BEST PHASE\r\n");
    }
    SetADCPhase(k);

    return TRUE;
}

/**************************************************************************//**
 * Get the difference of maximum SOD and minimum SOD.
 * @return The difference of maximum SOD and minimum SOD.
 ******************************************************************************/
static ULONG CheckPhaseData(void)
{
    ULONG value, minimum_value, maximum_value;
    USHRT local_timer;
    UCHAR phase;
    BOOL k;

#if AutoTune_Debug == ENABLE
printf("16_CheckPhaseData\n");	//150526 george    
#endif

    maximum_value = 0;
    minimum_value = 0xFFFFFFFF;
    phase = 0;
    SetADCPhase(phase);

    SC_GI_AUTO_TUNE_CTRL = 0x42;
    for (phase=4; phase<0x42; phase=phase+4) {
        if (ucAutoPct < 100) {
            OSDUpdateAutoTune(ucAutoPct++);
        }
        k = 0;
        local_timer = GetTimerTick();
        do {
            ResetWDTimer();
            if (CheckModeChangeFlag() == TRUE) {
                bAbortAutoTune = TRUE;
                return FALSE;
            }
            if ((SC_GI_AUTO_TUNE_CTRL & BIT1) == 0) {
                k = 1;
                break;
            }
        } while ((GetTimerTick()-local_timer) < 100);
        if (k == 0) {
            bAbortAutoTune = TRUE;
            return FALSE;
        }
        SetADCPhase(phase);
        SC_GI_AUTO_TUNE_CTRL = 0x42;
        value = ReadShortScaler(&SC_GI_PHS_SDIFF_HI0);
        value <<= 16;
        value += ReadShortScaler(&SC_GI_PHS_SDIFF_LO0);
        //printf("Phase %d = %ld\r\n", (USHRT)(phase), value);
        //printf("Phase %d = %ld\r\n", (USHRT)(phase-4), value);
        if (value < minimum_value) {
            minimum_value = value;
            ucPhaseIndexLo = (phase - 4) & 0x3F;
        }
        if (value > maximum_value) {
            maximum_value = value;
            ucPhaseIndexHi = (phase - 4) & 0x3F;
        }
    }

    value = maximum_value - minimum_value;

    //printf("usHTotal = %d\r\n",usHTotal);
    //printf("MaxMin = %ld\r\n",Value);

    return value;
}

/**************************************************************************//**
 * Automatically calibrate the ADC gain by Max/Min function in scaler.
 * @return TRUE if the calibration is succeeded else FALSE..
 ******************************************************************************/
static BOOL AutoGainCoarse(void)
{
#define MAX_WHITE_GAIN  0xF8
#define MIN_WHITE_GAIN  0xF0
#define ADC_MIN_GAIN    0x08
#define ADC_MAX_GAIN    0xF8

#if ENABLE_HW_AUTOCOLOR == ON
    return TRUE;
#else
    UCHAR i,k,value,rgb[3],bak[3];
    USHRT local_timer, temp;

#if OTHER_Degub == ENABLE
	printf("17_AutoGainCoarse\n");	//150526 george
#endif

    bak[0] = GetADCRGain();
    bak[1] = GetADCGGain();
    bak[2] = GetADCBGain();
    rgb[0] = GetADCRGain();
    rgb[1] = GetADCGGain();
    rgb[2] = GetADCBGain();

    for (k=0; k<128; k++) {
        i = 0;
        local_timer = GetTimerTick();
        SC_GI_AUTO_TUNE_CTRL = 0x6e;
        do {
            ResetWDTimer();
            if (CheckModeChangeFlag() == TRUE) {
                bAbortAutoTune = TRUE;
                break;
            }
            if ((SC_GI_AUTO_TUNE_CTRL & BIT1) == 0) {
                i = 1;
                break;
            }
        } while ((GetTimerTick() - local_timer) < 100);

        if (i == 0) { //timeout
            bAbortAutoTune = TRUE;
        }

        if (bAbortAutoTune == TRUE) { //timeout or mode change
            SetADCRGain(bak[0]);
            SetADCGGain(bak[1]);
            SetADCBGain(bak[2]);
            return FALSE;
        }

        //printf("\r\n");
        //printf("r = %d\r\n", (USHRT)rgb[0]);
        //printf("g = %d\r\n", (USHRT)rgb[1]);
        //printf("b = %d\r\n", (USHRT)rgb[2]);
        i = 0;
        value = SC_GI_PHS_SDIFF_LO0;

        // Basic concept of the following formula is
        //   ADC code is 0x60 when input is 0.5V and gain setting is 0xFF
        //   ADC code is 0xF0 when input is 0.5V and gain setting is 0x00
        //   (Those assumptions are always true!)
        // If the ADC code of 0.5V with specific gain setting is larger than
        // real input data, it means the input data is too small to meet our
        // Scaler spec. (0.5V ~ 0.9V white video level)
        temp = (USHRT)(0xFF-rgb[0]) * (0xF0-0x60) / 0xFF + 0x60;
//        printf("R = %d %d\r\n", (USHRT)value, temp);
        if (value < temp) {
            break;
        }

        if ((value<MIN_WHITE_GAIN) && (rgb[0]>ADC_MIN_GAIN)) {
            rgb[0] -= (MIN_WHITE_GAIN-value);
            i = 0xFF;
        }
        if ((value>MAX_WHITE_GAIN) && (rgb[0]<ADC_MAX_GAIN)) {
            rgb[0] += (value-MAX_WHITE_GAIN);
            i = 0xFF;
        }
        value = SC_GI_PHS_SDIFF_LO1;

        temp = (USHRT)(0xFF-rgb[1]) * (0xF0-0x60) / 0xFF + 0x60;
//        printf("G = %d %d\r\n", (USHRT)value, temp);
        if (value < temp) {
            break;
        }

        if ((value<MIN_WHITE_GAIN) && (rgb[1]>ADC_MIN_GAIN)) {
            rgb[1] -= (MIN_WHITE_GAIN-value);
            i = 0xFF;
        }
        if ((value>MAX_WHITE_GAIN) && (rgb[1]<ADC_MAX_GAIN)) {
            rgb[1] += (value-MAX_WHITE_GAIN);
            i = 0xFF;
        }
        value = SC_GI_PHS_SDIFF_HI0;

        temp = (USHRT)(0xFF-rgb[2]) * (0xF0-0x60) / 0xFF + 0x60;
//        printf("B = %d %d\r\n", (USHRT)value, temp);
        if (value < temp) {
            break;
        }

        if ((value<MIN_WHITE_GAIN) && (rgb[2]>ADC_MIN_GAIN)) {
            rgb[2] -= (MIN_WHITE_GAIN-value);
            i = 0xFF;
        }
        if ((value>MAX_WHITE_GAIN) && (rgb[2]<ADC_MAX_GAIN)) {
            rgb[2] += (value-MAX_WHITE_GAIN);
            i = 0xFF;
        }
        if (i == 0) {
            if ((rgb[0] < ADC_MIN_GAIN) || (rgb[0] > ADC_MAX_GAIN)) {
                break;
            }
            if ((rgb[1] < ADC_MIN_GAIN) || (rgb[1] > ADC_MAX_GAIN)) {
                break;
            }
            if ((rgb[2] < ADC_MIN_GAIN) || (rgb[2] > ADC_MAX_GAIN)) {
                break;
            }
            return TRUE;
        }
        else {
            SetADCRGain(rgb[0]);
            SetADCGGain(rgb[1]);
            SetADCBGain(rgb[2]);
            //Sleep(10);
        }
    }
    SetADCRGain(bak[0]);
    SetADCGGain(bak[1]);
    SetADCBGain(bak[2]);
    bAbortAutoTune = TRUE;

    return FALSE;
#endif
}

/**************************************************************************//**
 * Set horizontal mask to mask the coupling noise from HSync.
 ******************************************************************************/
void SetHmask(void)
{
#define ADC_PIPE_DELAY    0x08
#define HSYNC_LOCK_DELAY  0x18

    UCHAR sw;
    USHRT input_active_width, htotal, hposition, hw, mask;
    float temp;

#if PWRSeq_Deug == ENABLE
 printf("18_SetHmask\n");	//150526 george
#endif

    sw = SC_INPUT_SELECT & 0x03;
    if (sw > 0x01) {//DVI
        SC_GI_HMASK_BEG = 1;  // AutoPosition Pixel mask -> H
        SC_GI_HMASK_END = 0;  // AutoPosition Pixel mask -> H
        SC_GI_VMASK_BEG = 0;
        SC_GI_VMASK_END = 0;
    }
    else {
        /*
        SC_GI_HMASK_BEG = 0x10;  // AutoPosition Pixel mask -> H
        SC_GI_HMASK_END = 0x10;  // AutoPosition Pixel mask -> H
        SC_GI_VMASK_BEG = 3;
        SC_GI_VMASK_END = 3;
        */
        input_active_width = ReadShortScaler(&SC_GI_CAP_HWID_LO);
        htotal = ReadShortScaler(&SC_HSDDS_DIVIDER_LO);
        hposition = ReadShortScaler(&SC_GI_CAP_HBEG_LO);
        sw = SC_GI_HS_WID + 1;   // Always + 1 to avoid HMask taking no effect to coupling noise.
        hw = ReadShortScaler(&SC_GI_HCNT_LO) & 0x1FFF;
        temp = (float)htotal * sw * 8 / hw;
        mask = (USHRT)temp + (HSYNC_LOCK_DELAY - ADC_PIPE_DELAY);
        if (mask > 0xFF) {
            mask = 0xFF;
        }
        hw = htotal - input_active_width - hposition;
        if (mask > hw) {
            mask = hw;
        }
        SC_GI_HMASK_BEG = 0;
        SC_GI_HMASK_END = mask;
        SC_GI_VMASK_BEG = 0;
        SC_GI_VMASK_END = 0;
    }
}

#if (DVI_MODE==DVI_HV_MODE) || (DVI_MODE==DVI_HVDE_MODE)
/**************************************************************************//**
 * Automatically find the H/V start position of content when input is digital timing.
 * @return TRUE if the function is succeeded else FALSE.
 ******************************************************************************/
BOOL DVIAutoPosition(void)
{
    BOOL i;
    USHRT local_timer;

#if PWRSeq_Deug == ENABLE
 printf("19_DVIAutoPosition\n");	//150526 george
#endif

    if ((SC_GI_SYNC_CTRL & BIT7) == 0x00) {
        // DVIAutoPosition is only available under H+V.
        return FALSE;
    }

    bAbortAutoTune = 0;
    SetHmask();
    SC_GI_POS_THR = 0x40;  // Red Noise Margin
    SC_GI_AUTO_TUNE_CTRL = 0x00;
 
    SC_GI_AUTO_TUNE_CTRL = 0x11;
    Sleep(20);
    i = 0;
    local_timer = GetTimerTick();
    do {
        ResetWDTimer();
        if (CheckModeChangeFlag() == TRUE) {
            bAbortAutoTune = TRUE;
            break;
        }
        if ((SC_GI_AUTO_TUNE_CTRL & BIT0) == 0) {
            i = 1;
            break;
        }
    } while ((GetTimerTick() - local_timer) < 100);

    if (i == 0) {//timeout
        bAbortAutoTune = TRUE;
    }
    if (bAbortAutoTune == TRUE) {
        return FALSE;
    }
    else {
        WriteShortScaler(&SC_GI_CAP_VBEGE_LO, ReadShortScaler(&SC_GI_POS_VBEGE_LO));
        WriteShortScaler(&SC_GI_CAP_VBEGO_LO, ReadShortScaler(&SC_GI_POS_VBEGO_LO));
        WriteShortScaler(&SC_GI_CAP_HBEG_LO, GetInputHActBeg());
        return TRUE;
    }
}
#endif

/**************************************************************************//**
 * Set htotal (HPLL divider) step by step.
 * @param htotal Horizontal pixel count of input timing.
 ******************************************************************************/
void SetADCPLL2(USHRT htotal)
{
    USHRT htotal_end, htotal_begin;

#if AutoTune_Debug == ENABLE
printf("20_SetADCPLL2\n");	//150526 george
#endif

    SC_HPLL_PHASE_CTRL &= ~BIT2;
    htotal_begin = ReadShortScaler(&SC_HSDDS_DIVIDER_LO);
    htotal_end = htotal;
    htotal = htotal_begin;
    do {
        if (htotal_end != htotal_begin) {
            if (htotal_end > htotal_begin) {
                htotal += 4;
                if (htotal > htotal_end)
                    htotal = htotal_end;
            }
            else {
                htotal -= 4;
                if (htotal < htotal_end)
                    htotal = htotal_end;
            }
            WaitDisVSync();
            WriteShortScaler(&SC_HSDDS_DIVIDER_LO, htotal);
#if IS_NT68661_SERIES || IS_NT68770_SERIES || IS_NT68850_SERIES || IS_NT68655_SERIES || IS_NT68790_SERIES
#if ENABLE_SR == ON
            SetSRHtotal(htotal);
#endif
#endif
        }
    } while (htotal != htotal_end);
}

/**************************************************************************//**
 * Check the pixel clock is out of scaler spec or not.
 * @return TRUE if pixel clock is out of scaler spec else FALSE.
 ******************************************************************************/
BOOL CheckADCPLLOutOfRange(USHRT htotal)
{
#if PWRSeq_Deug == ENABLE
printf("21_CheckADCPLLOutOfRange\n");	//150526 george
#endif

    if (((ULONG)MAX_ANALONG_PIXEL_CLOCK * 10000) < ((ULONG)GetInputHFreq() * htotal)) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}
