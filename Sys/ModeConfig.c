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

//******************************************************************************
// G L O B A L   V A R I A B L E S
//******************************************************************************

//******************************************************************************
// S T A T I C   V A R I A B L E S
//******************************************************************************

//******************************************************************************
// E X T E R N A L   V A R I A B L E   P R O T O T Y P E S
//******************************************************************************
//============== CHIU	(from \App\OSD\FOSDView.c  ->  STATIC   VARIABLES) =======
//static code UCHAR ucVersionText[]={16,'V',VERSION+'0','.',(REVERSION>>4)+'0',(REVERSION&0x0F)+'0',' ',DATE};	
//static code UCHAR ucScalerText[]={7,SCALER_TEXT};

#ifdef USE_X18_BOARD
	code UCHAR ucModelText[]={4,"X18 "};
#else
	code UCHAR ucModelText[]={4,"X15N"};	//"X215"};	//"X215"};	//"X15N"};	//"X07W"};	//"X29W"};	//"XXW"};		//"X10N"};	// (at \App\OSD\FOSDView.c -> OSDShowFactory() )
#endif

	code UCHAR ucDateText[]={sizeof(__DATE__)-1 ,__DATE__};		 	// (at \App\OSD\FOSDView.c -> OSDShowFactory() ),  another (at \Sys\Nvram.c -> GetFirmwareVer() )
	code UCHAR ucPanelText[]={sizeof(PANEL_NAME)-1,PANEL_NAME};		// (at \App\OSD\FOSDView.c -> OSDShowFactory() )


#if OSD_SHOW_VERSION == ENABLE	 // show at osd-user-mode
//	static code UCHAR ucVersionText[]={16,'V',VERSION+'0','.',(REVERSION>>4)+'0',(REVERSION&0x0F)+'0',' ',DATE};	
//cobb m	code UCHAR ucVersionText[]={20,"F/W Ver: P6121-V1.00"};	//V2.00  "};				// (at \App\OSD\OSDView.c) -> OSDShowMainMenu() -> 	OSDAPI_ShowIndentString(...)

	code UCHAR ucVersionText[]={23,"F/W Ver: P6151-SB-V1.02"};	//V2.00  "};				// (at \App\OSD\OSDView.c) -> OSDShowMainMenu() -> 	OSDAPI_ShowIndentString(...)
#endif
		
//============== CHIU
//******************************************************************************
// S T A T I C   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
static void CheckInvalidParameter(void);

//******************************************************************************
// E X T E R N A L   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// F U N C T I O N   B O D Y S
//******************************************************************************

/**************************************************************************//**
 * Setup capture window and post display.
 * @return TRUE if system can show image normally. FASLE if OOR happens.
 ******************************************************************************/
BOOL ModeConfig(void)
{
    BOOL result;

    if (GetInputSyncMode() == DIG_SYNC) { //Digital input
        PowerDownAnalogInput();
        SetDVIPLL();
    #if (DVI_MODE==DVI_HV_MODE) || (DVI_MODE==DVI_HVDE_MODE)
        DVIAutoPosition();
    #endif
    #if (INPUT_INTERFACE&INPUT_DP)
        // power off DP or Digital sync?
    // Sequence : Run DPConfigFIFO() after DVIAutoPosition() 
        if (GetCurrInputInterface() == DISPLAY_PORT_INPUT) {
            PowerDownDigitalInput();
            DP_AudioMNCheckerInit();
        }
        //DPConfigFIFO();
        DPConfigCRC(); // CTS for Cut2/3 Use Only
    #endif
    #if ENABLE_HDMI == ON
        ClearHDMIStatus();
    #endif
#if ENABLE_NR_BYTIMING == ON    
        SetNRByDigitalTiming();
#endif
    }
    else { //Analog Input
        PowerDownDigitalInput();
        CheckInvalidParameter();
        SetADCPLL(InputTiming.usHTotal);
        SetADCPhase(InputTiming.ucPhase);
        SetNRByAnalogTiming();
        SetMinMax();
        SetHP(InputTiming.usHStart);
        SetVP(InputTiming.usVStart);
    }

#if ENABLE_OVERSCAN == ON
    CheckOverScan();
#else
    SetCaptureSize(InputTiming.usCapHActive, InputTiming.usCapVActive);
#endif
    SetHmask();

#if 0//ENABLE_SR == ON
    UserSetSR();
#endif

#if !IS_NT68770_SERIES && !IS_NT68850_SERIES && !IS_NT68655_SERIES && !IS_NT68790_SERIES
    SetColorSpace();
#endif

    result = SetupDisplayTiming(InputTiming.usHTotal50);

#if ENABLE_SR == ON
    UserSetSR();
#endif

#if ENABLE_SCALER_3D == ON
    SC3DAPI_Setup3DMode();
#endif
#if (INPUT_INTERFACE&INPUT_DP)
    // 0x1046 = 0x17, DPConfigFIFO() after SetupDisplayTiming()???
    if (GetCurrInputInterface() == DISPLAY_PORT_INPUT) {
        DPConfigFIFO();
    }
#endif

    return result;
}

/**************************************************************************//**
 * Determine current input timing is video timing or not.
 * @return TRUE if input timing is video timing else FALSE.
 ******************************************************************************/
BOOL IsVideoTiming(void)
{

#if (INPUT_INTERFACE&INPUT_MHL0) || (INPUT_INTERFACE&INPUT_MHL1)
     if ( (GetInputSyncMode() == DIG_SYNC) && MHL_IsMHLInput() ) {
           return TRUE;
    }
#endif   
   
    if ((InputTiming.usModeIndex == _720x480I_60HZ)   ||
        (InputTiming.usModeIndex == _1440x480I_60HZ)  ||
        (InputTiming.usModeIndex == _2880x480I_60HZ)  ||
        (InputTiming.usModeIndex == _720x480P_60HZ)   ||
        (InputTiming.usModeIndex == _720x576I_50HZ)   ||
        (InputTiming.usModeIndex == _1440x576I_50HZ)  ||
        (InputTiming.usModeIndex == _2880x576I_50HZ)  ||
        (InputTiming.usModeIndex == _720x576P_50HZ)   ||
        (InputTiming.usModeIndex == _1280x720P_50HZ)  ||
        (InputTiming.usModeIndex == _1280x720_60HZ)   ||
        (InputTiming.usModeIndex == _1920x1080P_60HZ) ||
        (InputTiming.usModeIndex == _1920x1080P_50HZ) ||
        (InputTiming.usModeIndex == _1920x1080I_50HZ) ||
        (InputTiming.usModeIndex == _1920x1080I_50HZ_RB)) {
        return TRUE;
    }

    return FALSE;
}

/**************************************************************************//**
 * Determine current input timing is "Out Of Range" or not.
 * @return TRUE if input timing is OOR else FALSE.
 ******************************************************************************/
BOOL IsOutOfRange(void)
{

#if ENABLE_SCALER_3D == ON
    if (SC3DAPI_IsHDMI3DMode()) {
        return FALSE;
    }
#endif
#if ENABLE_DVI_DUAL_LINK == ON
    if (TMDS_IsDualLink()) {
        return FALSE;
    }
#endif

    if (IsVideoTiming()) {
        return FALSE;
    }

    //Check HSync Frequency
    if (InputTiming.usHSyncFreq < MIN_H_FREQ) {
        return TRUE;
    }
    if (InputTiming.usHSyncFreq > MAX_H_FREQ) {
        return TRUE;
    }
    //Check VSync Frequency
    if (InputTiming.usVSyncFreq < MIN_V_FREQ) {
        return TRUE;
    }
    if (InputTiming.usVSyncFreq > MAX_V_FREQ) {
        return TRUE;
    }
    //Check ADC clock frequency
    if (GetInputSyncMode() != DIG_SYNC) {
        if (CheckADCPLLOutOfRange(InputTiming.usHTotal) == TRUE) {
            return TRUE;
        }
    }

	return FALSE;
}

/**************************************************************************//**
 * Define the minimum and maximum value of HTotal, HStart and VStart
 ******************************************************************************/
void SetMinMax(void)
{
    USHRT temp;

    temp = InputTiming.usHTotal50 > 50 ? 50 : InputTiming.usHTotal50;
    InputTiming.usHTotalMin = InputTiming.usHTotal50 - temp;
    InputTiming.usHTotalMax = InputTiming.usHTotal50 + temp;

    temp = InputTiming.usHStart50 > 50 ? 50 : InputTiming.usHStart50;
    InputTiming.usHStartMin = InputTiming.usHStart50 - temp;
    InputTiming.usHStartMax = InputTiming.usHStart50 + temp;

    temp = InputTiming.usVStart50 > 20 ? 20 : InputTiming.usVStart50-1;
    InputTiming.usVStartMin = InputTiming.usVStart50 - temp;
    InputTiming.usVStartMax = InputTiming.usVStart50 + temp;
}

/**************************************************************************//**
 * Verify the present HTotal, HStart and VStart.
 * The criteria is
 *   If HTotal > 2*HActive, HTotal is invalid and HTotal = HActive * 3 / 2.
 *   If HStart > 0.5*HTotal, HStart is invalid and HStart = (HTotal - HActive) / 2.
 *   If VStart > 0.5*VTotal, VStart is invalid and VStart = (VTotal - VActive) / 2.
 ******************************************************************************/
void CheckInvalidParameter(void)
{
    USHRT temp;
    temp = InputTiming.usCapHActive << 1;
    if (InputTiming.usHTotal > temp) {
        temp = InputTiming.usCapHActive >> 1;
        InputTiming.usHTotal = InputTiming.usCapHActive + temp;
    }
    temp = InputTiming.usHTotal >> 1;
    if (InputTiming.usHStart > temp) {
        InputTiming.usHStart = (InputTiming.usHTotal - InputTiming.usCapHActive) / 2;
    }
    temp = InputTiming.usVTotal >> 1;
    if (InputTiming.usVStart > temp) {
        InputTiming.usVStart = (InputTiming.usVTotal - InputTiming.usCapVActive) / 2;
    }
}

#if ENABLE_OVERSCAN == ON
/**************************************************************************//**
 * Perform over-scan with some conditions.
 ******************************************************************************/
void CheckOverScan(void)
{
#if ((ENABLE_HDMI == ON) && !(INPUT_INTERFACE&INPUT_DP))
    if ((GetInputSyncMode() == DIG_SYNC) && IsHDMIVideo() && IsOverScan())
#else
    if ((GetInputSyncMode() == DIG_SYNC) && IsOverScan())
#endif
    {
        SetOverScanRatio(OVER_SCAN_RATIO);
    }
    else{
        SetOverScanRatio(0);
    }
}

/**************************************************************************//**
 * Update capture-related parameters.
 ******************************************************************************/
static void UpdateCaptureInfo(void)
{
    USHRT vactive = GetDigInputVActive();
    if (IsInterlaced()) {
        vactive = vactive * 2;
    }

    InputTiming.usModeHActive = GetDigInputHActive();
    InputTiming.usModeVActive = vactive;
    InputTiming.usCapHActive = InputTiming.usModeHActive;
    InputTiming.usCapVActive = InputTiming.usModeVActive;
    InputTiming.usHStart = GetInputHStart();
    InputTiming.usVStart = GetInputVStart();
    InputTiming.usHStart50 = InputTiming.usHStart;
    InputTiming.usVStart50 = InputTiming.usVStart;
}

/**************************************************************************//**
 * Perform over-scan.
 * Over-scan procedures must follow the following steps.
 *   1. Disable over-scan.
 *   2. Set capture window.
 *   3. Wait for a VSync duty (20ms).
 *   4. Enable over-scan.
 * @param ratio Over-scan ratio.
 ******************************************************************************/
void SetOverScanRatio(UCHAR ratio)
{
    USHRT hstart, vstart;

    if (ratio != 0) { //On
        DisableOverSample();
        DVIAutoPosition();
        UpdateCaptureInfo();
        hstart = InputTiming.usCapHActive * ratio / 100 / 2;
        vstart = InputTiming.usCapVActive * ratio / 100 / 2;
        InputTiming.usHStart = hstart;
        InputTiming.usVStart = GetInputVStart();
        InputTiming.usVStart += vstart;
        InputTiming.usCapHActive = InputTiming.usCapHActive - hstart * 2;
        InputTiming.usCapHActive &= 0xFFFE;
        if (IsInterlaced() == TRUE) {
            InputTiming.usCapVActive = InputTiming.usCapVActive - vstart * 4;
        }
        else {
            InputTiming.usCapVActive = InputTiming.usCapVActive - vstart * 2;
        }
        SetHP(InputTiming.usHStart);
        SetVP(InputTiming.usVStart);
        SetCaptureSize(InputTiming.usCapHActive, InputTiming.usCapVActive);
        DelayVTime(2);
        EnableOverSample();
    }
    else { //Off
        if (IsOverSample() == TRUE) {
            DisableOverSample();
            DVIAutoPosition();
            UpdateCaptureInfo();
        }
        SetCaptureSize(InputTiming.usCapHActive, InputTiming.usCapVActive);
    }
}
#endif
//******************************************************************************
// Prototype:
//  BOOL CheckVSyncWidthChange(void)
// Parameters:
//  None
// Return:
//  TRUE/FALSE
// Purpose:
//  Check Vsync width change
// Notes:
//  v31_1106221_2200_SYS#2
//******************************************************************************
/*
BOOL CheckVSyncWidthChange(void)
{
#define VS_WID_DIFF_CNT 4

    UCHAR uctemp_Vs_wid;
    if (GetModeHandleState() == WAIT_MODE_CHANGE) {
        if (((InputTiming.usModeHActive == 1360) ||(InputTiming.usModeHActive == 1366)) && (InputTiming.usModeVActive == 768)) { //v31_110627_2225_SYS#7
            uctemp_Vs_wid = GetInputVSyncWidth();
            if (uctemp_Vs_wid != Custom_System.ucVs_wid) {
                Custom_System.ucVs_wid_diff_cnt ++;
            }
            else {
                Custom_System.ucVs_wid_diff_cnt = 0;
            }
            if ( Custom_System.ucVs_wid_diff_cnt > VS_WID_DIFF_CNT) {
                return TRUE;
            }
        }
    }
    return FALSE;
}
*/
