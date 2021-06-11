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
#include "ScalerProfile.h"

//******************************************************************************
// M A C R O   D E F I N I T I O N S
//******************************************************************************

//******************************************************************************
// G L O B A L   V A R I A B L E S
//******************************************************************************

//******************************************************************************
// S T A T I C   V A R I A B L E S
//******************************************************************************

//******************************************************************************
// E X T E R N A L   V A R I A B L E   P R O T O T Y P E S
//******************************************************************************
extern xdata ULONG ulHFreqCounter;

//******************************************************************************
// S T A T I C   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// E X T E R N A L   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// F U N C T I O N   B O D Y S
//******************************************************************************

/**************************************************************************//**
 * Initialize TMDS-related registers.
 ******************************************************************************/
void TMDSInit(void)
{
    SC_DVI_CTRL_303 |= BIT0;
    SC_DVI_CTRL_301 |= BIT0;
    SC_DVI_CTRL_303 |= BIT7;
    //SC_DVI_RB_SWAP = 0x00;
    SC_DVI_CTRL_32C = 0x04;
    SC_DVI_CTRL_330 = DEFAULT_CLKIMP1;
    SC_DVI_CTRL_339 = DEFAULT_DATAIMP1;
    SC_DVI_CTRL_332 = DEFAULT_EQBIAS1;
    SC_DVI_CTRL_331 = SCREG_331;
    SC_DVI_CTRL_334 = SCREG_334_PU;
    SC_DVI_CTRL_337 = DEFAULT_EQRF1;
    SC_DVI_CTRL_338 = 0xFC;
    SC_DVI_CTRL_33E = DEFAULT_EQBIAS1;
    SC_DVI_CTRL_33F = DEFAULT_EQRF1;

    DVI_PowerOn();
    SC_HDCP_CTRL = SCREG_643;
    SC_DVI_PLL_M = 0x20;
}

/**************************************************************************//**
 * Detect current input signal quality and set proper impedance.
 ******************************************************************************/
void TMDSImpedanceDetection(void)
{
//cobb m#define GOOD_EYE_THRESHOLD 1 // 2 //every channel needs number of  '0x00' good eye.
#define GOOD_EYE_THRESHOLD 0 // 2 //every channel needs number of  '0x00' good eye.	, cobb change value from 1 to 0

#define BREAK_LOOP 0xEE

    code UCHAR ucClkIMPTable[] = {
        //0x330
        DEFAULT_CLKIMP1,
        DEFAULT_CLKIMP2,
        DEFAULT_CLKIMP3
    };
    code UCHAR ucDataIMPTable[][2] = {
        //0x339            0x33A
        {DEFAULT_DATAIMP1, 0xA0},
        {DEFAULT_DATAIMP1, 0x60},
        {DEFAULT_DATAIMP2, 0x60},
        {DEFAULT_DATAIMP3, 0x60}
    };
    code UCHAR ucEQBiasTable[][2] = {
        //0x332           0x337
        {DEFAULT_EQBIAS1, DEFAULT_EQRF1},
        {DEFAULT_EQBIAS2, DEFAULT_EQRF2},
        {DEFAULT_EQBIAS3, DEFAULT_EQRF3},
        {DEFAULT_EQBIAS4, DEFAULT_EQRF4},
        {DEFAULT_EQBIAS5, DEFAULT_EQRF5}
    };

    UCHAR i, j, k, l, ch, Reg0x306, Reg0x310, Reg0x311, Reg0x336;
    UCHAR *ptr;
    USHRT localtimer;
    EyeData tmp_eye;
    EyeData eye = {
        DEFAULT_CLKIMP1,
        DEFAULT_DATAIMP1,
        0xA0,
        DEFAULT_EQBIAS1,
        DEFAULT_EQRF1,
        0,
        0xffff,
        {0, 0, 0}
    };
    
    McuScalerIntDisable();//make sure sync processor interrupt disable.
    Reg0x306 = SC_DVI_CTRL_306;
    Reg0x310 = SC_DVI_CTRL_310;
    Reg0x311 = SC_DVI_CTRL_311;
    Reg0x336 = SC_DVI_CTRL_336;
    SC_DVI_CTRL_336 &= ~BIT5; //disable CKDT to control channels impedance power down

#if (INPUT_INTERFACE&INPUT_MHL0) || (INPUT_INTERFACE&INPUT_MHL1)  
    if ( MHL_IsMHLInput() ) {
        Sleep(1);
        SC_DVI_CTRL_339 = 0x16;//DEFAULT_DATAIMP1;
        if (((SC_DVI_STATUS & BIT0) != 0)) {
            SC_DVI_CTRL_33A = 0xA0;//0x20; why 0x20??
    }
    else {
            SC_DVI_CTRL_33A = 0x60;//0x20; why 0x20??
    }
        SC_DVI_CTRL_33E = ucEQBiasTable[0][0];//EQ bias for MHL
        SC_DVI_CTRL_33F = ucEQBiasTable[0][1];//EQ resistor for MHL
        Sleep(1);
#if 0 // MHL PP Mode Compability, Reseverd
        SC_DVI_CTRL_306 = 0x00;
        SC_DVI_CTRL_309 |= BIT0;//clear error
        SC_DVI_CTRL_311 = 0x22;//eye detection with Vs
        Sleep(20);
        for ( i=0,j=0,k=0; i<7; i++ ) {
            if ((SC_DVI_CTRL_308 & 0x01) == 0x00) {
                j++;
            }
            else {
                j = 0;
                k++;
            }
            if ( j==3 ) {
                break;
            }
            SC_DVI_CTRL_306 = 0x00;
            SC_DVI_CTRL_309 |= BIT0;//clear error
            SC_DVI_CTRL_311 = 0x22;//eye detection with Vs
            Sleep(20);
        }
        SC_DVI_CTRL_331 = 5+k;
#endif
        SC_DVI_CTRL_306 = Reg0x306;
        SC_DVI_CTRL_310 = Reg0x310;
        SC_DVI_CTRL_311 = Reg0x311;
        SC_DVI_CTRL_336 = Reg0x336; 
        return;
    }
    else
#endif        
    {
        SC_DVI_CTRL_330 = DEFAULT_CLKIMP3; //for SCDT first
        SC_DVI_CTRL_339 = DEFAULT_DATAIMP3;
        SC_DVI_CTRL_33A = 0x60;
    }    
    
    Sleep(1);
    if (((SC_DVI_STATUS & BIT0) != 0) && ((SC_GI_SYNC_STATUS & 0xF8) == 0x18)) {
        SC_DVI_CTRL_311 = 0x22;//eye detection with Vs
        SC_DVI_CTRL_310 = 0x13;//detection start
        for (i = 0; i < sizeof(ucClkIMPTable); i++) {
            tmp_eye.ClkIMP = ucClkIMPTable[i];
            SC_DVI_CTRL_330 = tmp_eye.ClkIMP;//clock impedance       
            for (j = 0; j < sizeof(ucDataIMPTable) / 2; j++) {
                tmp_eye.DataIMP = ucDataIMPTable[j][0];
                tmp_eye.IMPMode = ucDataIMPTable[j][1];
                SC_DVI_CTRL_339 = tmp_eye.DataIMP;//data impedance
                SC_DVI_CTRL_33A = tmp_eye.IMPMode;
                for (k = 0; k < sizeof(ucEQBiasTable) / 2; k++) {
                    tmp_eye.EQBias = ucEQBiasTable[k][0];
                    tmp_eye.EQRF = ucEQBiasTable[k][1];
                    SC_DVI_CTRL_33E = tmp_eye.EQBias;//EQ bias   //data ch0
                    SC_DVI_CTRL_33F = tmp_eye.EQRF;//EQ resistor //data ch0   
                    SC_DVI_CTRL_332 = tmp_eye.EQBias;//EQ bias   //data ch1,ch2
                    SC_DVI_CTRL_337 = tmp_eye.EQRF;//EQ resistor //data ch1,ch2
                    tmp_eye.MaxGoodEye = 0;
                    tmp_eye.SumOfEye = 0xffff;
                    for (ch = 0; ch < 3; ch++) {
                        tmp_eye.RGBGoodEye[ch] = 0;
                        SC_DVI_CTRL_306 = ch;
                        SC_DVI_CTRL_309 |= BIT0;//clear error
                        SC_DVI_CTRL_310 = 0x13;//detection start
                        localtimer = GetTimerTick();
                        do {
                            Sleep(1);//detection period for 0x308 data error statistics 
                        } while (((SC_DVI_CTRL_310 & BIT3) != BIT3) && ((GetTimerTick() - localtimer) < 30));
                        if ((SC_DVI_STATUS & BIT0) == 0) {
                            //force change to next clock impedance
                            tmp_eye.SumOfEye = 0xffff;
                            tmp_eye.RGBGoodEye[ch] = 0;
                            tmp_eye.MaxGoodEye = 0;
                            j = k = ch = BREAK_LOOP;
                        }
                        else if ((SC_DVI_CTRL_308 & 0x07) == 0x00) {
                            ptr = &SC_DVI_CTRL_317;
                            for (l = 0; l < 5; l++) { //search 0x317~0x31B equals to 0x00
                                tmp_eye.SumOfEye += *ptr;
                                if (*ptr++ == 0x00) {
                                    tmp_eye.RGBGoodEye[ch]++;
                                    tmp_eye.MaxGoodEye++;
                                }
                            }
                        }
                        else {
                            //data error force break
                            tmp_eye.SumOfEye = 0xffff;
                            tmp_eye.RGBGoodEye[ch] = 0;
                            tmp_eye.MaxGoodEye = 0;
                            ch = BREAK_LOOP;
                        }
                    }
                    if (((tmp_eye.MaxGoodEye > eye.MaxGoodEye)
                            && (tmp_eye.RGBGoodEye[0] > 0
                                    && tmp_eye.RGBGoodEye[1] > 0
                                    && tmp_eye.RGBGoodEye[2] > 0))
                            || ((tmp_eye.SumOfEye < eye.SumOfEye)
                                    && (eye.RGBGoodEye[0] == 0
                                            || eye.RGBGoodEye[1] == 0
                                            || eye.RGBGoodEye[2] == 0))) {
                        //Maximum good-eye is prior to minimum sum of eye
                        eye = tmp_eye;

                    }
                    if ((tmp_eye.RGBGoodEye[0] >= GOOD_EYE_THRESHOLD)
                            && (tmp_eye.RGBGoodEye[1] >= GOOD_EYE_THRESHOLD)
                            && (tmp_eye.RGBGoodEye[2] >= GOOD_EYE_THRESHOLD)) {
                        eye = tmp_eye;
                        i = j = k = BREAK_LOOP;//for force to break
                    }
                }
            }
        }
    }

    SC_DVI_CTRL_339 = eye.DataIMP;
    SC_DVI_CTRL_33A = eye.IMPMode;
    SC_DVI_CTRL_330 = eye.ClkIMP;
    SC_DVI_CTRL_33E = eye.EQBias;//data ch0
    SC_DVI_CTRL_33F = eye.EQRF;  //data ch0     
    SC_DVI_CTRL_332 = eye.EQBias;//data ch1,ch2
    SC_DVI_CTRL_337 = eye.EQRF;  //data ch1,ch2
    Sleep(1);
    SC_DVI_CTRL_306 = Reg0x306;
    SC_DVI_CTRL_310 = Reg0x310;
    SC_DVI_CTRL_311 = Reg0x311;
    SC_DVI_CTRL_336 = Reg0x336;

#undef GOOD_EYE_THRESHOLD
#undef BREAK_LOOP
}

/**************************************************************************//**
 * Detect the TMDS clock is stable or not.
 * @return TRUE if clock is stable else FALSE.
 ******************************************************************************/
BOOL TMDSClockStable(void)
{
    USHRT pre_clock, stable_timer, unstable_timer;

    pre_clock = TMDS_GetClock();
    stable_timer = GetTimerTick();
    unstable_timer = stable_timer;

    //Wait the TMDS clock to be stable for 150 ms or unstable for 300 ms
    while ((GetTimerTick()-unstable_timer) < 300) {
        if (abs(pre_clock - TMDS_GetClock()) > 2) {
            pre_clock = TMDS_GetClock();
            stable_timer = GetTimerTick();
        }
        if ((GetTimerTick() - stable_timer) > 150) {
            return TRUE;
        }
        ResetWDTimer();
    }

    return FALSE;
}

/**************************************************************************//**
 * According to the TMDS clock, we set some specific registers to get more signal qualities.
 * We reset TMDS phase detection only when clock is stable.
 * @param reset TRUE to reset TMDS phase detection else FALSE.
 ******************************************************************************/
void TMDSBandwidthDetection(UCHAR reset)
{
#if (INPUT_INTERFACE&INPUT_MHL0) || (INPUT_INTERFACE&INPUT_MHL1)
    if ( !MHL_IsMHLInput() ) { // not mhl
        if (TMDS_GetClock() < (TMDS_BANDWIDTH_SEGMENT - 1)) {
            SC_DVI_CTRL_334 = SCREG_334_LF;
            SET_SCREG_335_LF;
            SC_DVI_CTRL_303 = SCREG_303_LF;
        }
        else if (TMDS_GetClock() > (TMDS_BANDWIDTH_SEGMENT + 1)) {
            SC_DVI_CTRL_334 = SCREG_334_HF;
            SET_SCREG_335_HF;
            SC_DVI_CTRL_303 = SCREG_303_HF;
        }

        if (reset) {
            //Toogle 0x303 for digital input
            SC_DVI_CTRL_303 &= ~BIT0;
            SC_DVI_CTRL_303 |= BIT0;
        }
    }
    else { //mhl
        if ( (SC_HDMI_MHL_MODE_DETECT&BIT6) == 0 ) {
            SC_DVI_CTRL_303 = SCREG_303_LF;
        }
        else {
            SC_DVI_CTRL_303 = SCREG_303_HF; //pp mode
        }
        SC_DVI_CTRL_334 = 0xF1;
        SC_DVI_CTRL_335 = 0x00;
    }
#else    
    if (TMDS_GetClock() < (TMDS_BANDWIDTH_SEGMENT - 1)) {
        SC_DVI_CTRL_334 = SCREG_334_LF;
        SET_SCREG_335_LF;
        SC_DVI_CTRL_303 = SCREG_303_LF;
    }
    else if (TMDS_GetClock() > (TMDS_BANDWIDTH_SEGMENT + 1)) {
        SC_DVI_CTRL_334 = SCREG_334_HF;
        SET_SCREG_335_HF;
        SC_DVI_CTRL_303 = SCREG_303_HF;
    }

    if (reset) {
        //Toogle 0x303 for digital input
        SC_DVI_CTRL_303 &= ~BIT0;
        SC_DVI_CTRL_303 |= BIT0;
    }
#endif
}

/**************************************************************************//**
 * Get digital input HDE pixel count.
 * Before system invoke this function, the input VSync frequency must be determined.
 * This value is determined by the capture block not TMDS block.
 * @return Digital input HDE.
 ******************************************************************************/
USHRT GetDigInputHActive(void)
{
#if 0
    return ReadShortScaler(&SC_DVI_CAP_HWID_LO);
#else
    UCHAR i;
    USHRT hactive, htemp;

    htemp = 0;
    for (i=0; i<5; i++) { //Reg0x03C/Reg0x03D can not be read immediately after 0x6B5[2] was changed
        hactive = ReadShortScaler(&SC_DVI_CAP_HWID_LO);
        if (htemp != hactive) {
            htemp = hactive;
            DelayVTime(1);
        }
        else {
            break;
        }
    }

    return hactive;
#endif
}

/**************************************************************************//**
 * Get digital input VDE line count.
 * Before system invoke this function, the input VSync frequency must be determined.
 * This value is determined by the capture block not TMDS block.
 * @return Digital input VDE.
 ******************************************************************************/
USHRT GetDigInputVActive(void)
{
#if 0
    if (IsInterlaced()) {
        return ReadShortScaler(&SC_DVI_CAP_VLEN_LO) * 2;
    }
    else {
        return ReadShortScaler(&SC_DVI_CAP_VLEN_LO);
    }
#else
    UCHAR i;
    USHRT vactive, vtemp;

    vtemp = 0;
    for (i=0; i<5; i++) {
        vactive = ReadShortScaler(&SC_DVI_CAP_VLEN_LO);
        if (vtemp != vactive) {
            vtemp = vactive;
            DelayVTime(4);
        }
        else {
            break;
        }
    }

        return vactive;
#endif
}

/**************************************************************************//**
 * Get digital input HDE without any delay.
 * This value is determined by the capture block not TMDS block.
 * @return Digital input HDE.
 ******************************************************************************/
USHRT GetDigInputHActiveImmediate(void)
{
#if ENABLE_HDMI == ON
// Because of inconsistent update issue of high/low bytes, we should read hde/vde with filter.
    return ReadShortScalerHighLowFilter(&SC_VIDEO_DE_WIDTH_LO);
#else
    return ReadShortScalerHighLowFilter(&SC_DVI_CAP_HWID_LO);
#endif
}

/**************************************************************************//**
 * Get digital input VDE without any delay.
 * This value is determined by the capture block not TMDS block.
 * @return Digital input VDE.
 ******************************************************************************/
USHRT GetDigInputVActiveImmediate(void)
{
#if ENABLE_HDMI == ON
    // Because of inconsistent update issue of high/low bytes, we should read hde/vde with filter.
    return ReadShortScalerHighLowFilter(&SC_VIDEO_DE_LINE_LO);
#else
    return ReadShortScalerHighLowFilter(&SC_DVI_CAP_VLEN_LO);
#endif
}

#if ENABLE_HDMI == ON
/**************************************************************************//**
 * Get digital input HTotal without any delay.
 * This value is determined by the TMDS block not capture block.
 * @return Digital input HTotal.
 ******************************************************************************/
USHRT GetDigInputHTotalImmediate(void)
{
    // Because of inconsistent update issue of high/low bytes, we should read h/vtotal with filter.
#if (INPUT_INTERFACE&INPUT_DP)  
    if (GetCurrInputInterface() == DISPLAY_PORT_INPUT) {
        return ReadShortScalerHighLowFilter(&SC_DP_HTOTAL_LO);
    }
#endif
    return ReadShortScalerHighLowFilter(&SC_VIDEO_HTOTAL_LO);
}

/**************************************************************************//**
 * Get digital input VTotal without any delay.
 * This value is determined by the TMDS block not capture block.
 * @return Digital input VTotal.
 ******************************************************************************/
USHRT GetDigInputVTotalImmediate(void)
{
    // Because of inconsistent update issue of high/low bytes, we should read h/vtotal with filter.
#if (INPUT_INTERFACE&INPUT_DP)  
    if (GetCurrInputInterface() == DISPLAY_PORT_INPUT) {
        return ReadShortScalerHighLowFilter(&SC_DP_VTOTAL_LO);
    }
#endif
    return ReadShortScalerHighLowFilter(&SC_VIDEO_VTOTAL_LO);
}
#endif

/**************************************************************************//**
 * Get the count of HSync frequency (from sync processor) of digital timing.
 ******************************************************************************/
void SetDVIPLL(void)
{
    USHRT pixel_rate;

    SC_HPLL_FREQ_CTRL &= ~BIT6;

#if ENABLE_HDMI == ON
    TMDSDeepColorDetection();
#endif

    SC_HPLL_LINE_CNT = 0x0B;//0x0C; //4096 line

    pixel_rate = ReadShortScaler(&SC_GI_HCNT_LO) & 0x1FFF;
    if ((pixel_rate==0x1FFF) || (pixel_rate==0)) {
        ulHFreqCounter = 0xFFFFFFFF;
    }
    else {
        ulHFreqCounter = (ULONG)pixel_rate * 8192;
    }
}

/**************************************************************************//**
 * Turn off TMDS power.
 ******************************************************************************/
void DVI_PowerOff(void)
{
#if (INPUT_INTERFACE&INPUT_MHL0) || (INPUT_INTERFACE&INPUT_MHL1)
    if ( IsMHL0Connect() ||IsMHL1Connect() ) {
        return;
    }
#endif
    SC_DVI_CTRL_333 = SCREG_333_PD;
    SC_DVI_CTRL_334 = SCREG_334_PD;
    SC_DVI_CTRL_335 = SCREG_335_PD;
    SC_DVI_CTRL_336 = SCREG_336_PD;
    SC_POWER_CTRL2 &= ~BIT1;
}

/**************************************************************************//**
 * Turn on TMDS power.
 ******************************************************************************/
void DVI_PowerOn(void)
{
    SC_POWER_CTRL2 |= (BIT5 | BIT1);
    SC_DVI_CTRL_333 = SCREG_333_PU;
    SC_DVI_CTRL_334 = SCREG_334_PU;
    SET_SCREG_335_HF;
    SC_DVI_CTRL_336 = SCREG_336_PU;
}

/**************************************************************************//**
 * Turn on the termination power of TMDS clock pair for TMDS clock detection.
 ******************************************************************************/
void TMDS_EnableSCDT(void)
{
    SC_DVI_CTRL_336 = SCREG_336_PU;
}

/**************************************************************************//**
 * Get current TMDS clock.
 * @return TMDS clock frequency.
 ******************************************************************************/
USHRT TMDS_GetClock(void)
{
USHRT clk_tmp;
#if REF_CLK==12000000
    if ((SC_DVI_STATUS & BIT0) != 0) {
    #if (INPUT_INTERFACE&INPUT_MHL0) || (INPUT_INTERFACE&INPUT_MHL1)
        if ( MHL_IsPackedPixelMode() ) { //get correct PHY clock 0x016 after set 0x159.6=0
            return SC_TMDS_CLOCK_DET;
        }
    #endif
#if IS_NT68770_SERIES
        SC_DVI_CTRL_32C |= BIT7;
#endif
        clk_tmp = ReadShortScaler(&SC_DVI_PIXELCLK_LO) & 0x0FFF;
#if IS_NT68770_SERIES
        SC_DVI_CTRL_32C &= ~BIT7;
#endif
        return clk_tmp;
    }
#else
#define OSC_FREQ_RATIO ((float)REF_CLK/12000000)
    if ((SC_DVI_STATUS & BIT0) != 0) {
    #if (INPUT_INTERFACE&INPUT_MHL0) || (INPUT_INTERFACE&INPUT_MHL1)
        if ( MHL_IsPackedPixelMode() ) { //get correct PHY clock 0x016 after set 0x159.6=0
            clk_tmp = (USHRT)SC_TMDS_CLOCK_DET * OSC_FREQ_RATIO;
            return clk_tmp;
        }
    #endif
#if IS_NT68770_SERIES
        SC_DVI_CTRL_32C |= BIT7;
#endif
        clk_tmp = (USHRT)((ReadShortScaler(&SC_DVI_PIXELCLK_LO) & 0x0FFF) * OSC_FREQ_RATIO);
#if IS_NT68770_SERIES
        SC_DVI_CTRL_32C &= ~BIT7;
#endif
        return clk_tmp;
    }
#undef OSC_FREQ_RATIO
#endif
    return 0;
}
