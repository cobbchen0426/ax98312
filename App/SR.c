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

#if ENABLE_SR == ON

//******************************************************************************
// M A C R O   D E F I N I T I O N S
//******************************************************************************

//******************************************************************************
// G L O B A L   V A R I A B L E S
//******************************************************************************

//******************************************************************************
// S T A T I C   V A R I A B L E S
//******************************************************************************
static code MDNBlock MDNModes[NUM_MDN_MODE] = {
    //MDN_FILTER_CUTOFF_TH, SLOP
    //VAR_TH,LOW_VAR_Gain,HIGH_VAR_Gain
    SR_MDN_1
};

static code USMRegionBlock USMRegionModes[NUM_USMRGN_MODE] = {
    //HIGH_PASS_FILTER_CUTOFF_TH
    //VAR_TH,LOW_VAR_Gain,HIGH_VAR_Gain
    SR_USMRegion_1,
    SR_USMRegion_2,
    SR_USMRegion_3,
    SR_USMRegion_4
};

static code USMGainBlock USMGainModes[NUM_USMGAIN_MODE] = {
    //Gain
    //VAR_TH,LOW_VAR_Gain,HIGH_VAR_Gain
    SR_USMGain_1,
    SR_USMGain_2,
    SR_USMGain_3,
    SR_USMGain_4
};

static code SRBlock SRModes[NUM_SR_MODE]= {
    {//OFF
        &MDNModes[MDN_MODE_1],
        &USMRegionModes[USM_REGION_MODE_1],
        &USMGainModes[USM_GAIN_MODE_1],
        0x0000,  // 128 gray - low gray will be smooth = =
        USM_DARK_LIMIT_OFF,
    },
    {//Weak
        &MDNModes[MDN_MODE_1],
        &USMRegionModes[USM_REGION_MODE_1],
        &USMGainModes[USM_GAIN_MODE_1],
        0x0000,
        USM_DARK_LIMIT_OFF,
    },
    {//Median
        &MDNModes[MDN_MODE_1],
        &USMRegionModes[USM_REGION_MODE_2],
        &USMGainModes[USM_GAIN_MODE_2],
        0x0000,/*0x0025*/
        USM_DARK_LIMIT_OFF,
    },
    {//Strong
        &MDNModes[MDN_MODE_1],
        &USMRegionModes[USM_REGION_MODE_3],
        &USMGainModes[USM_GAIN_MODE_3],
        0x0000,/*0x0030*/
        USM_DARK_LIMIT_OFF,
    },
    {//Strongest
        &MDNModes[MDN_MODE_1],
        &USMRegionModes[USM_REGION_MODE_4],
        &USMGainModes[USM_GAIN_MODE_4],
        0x0000,/*0xC00*/
        USM_DARK_LIMIT_OFF,
    }
};

//******************************************************************************
// E X T E R N A L   V A R I A B L E   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// S T A T I C   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// E X T E R N A L   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************

/**************************************************************************//**
 * Configure the SR of Scaler
 ******************************************************************************/
void InitSR(void)
{
    SRAPI_InitSR();
    SRAPI_SetDemoRegion(OFF, SR_DEMO_LEFT, 0x0500);
}

/**************************************************************************//**
 * Set SR Mode.
 * @param SR mode.
 ******************************************************************************/
void SetSRMode(SRMode mode)
{
#if IS_NT68770_SERIES || IS_NT68850_SERIES || IS_NT68655_SERIES || IS_NT68790_SERIES
    if (mode == SR_MODE_OFF) {
        SRAPI_TurnOnOff(OFF);
   }
    else {
        SRAPI_SetMDNFilter(SRModes[mode].pMDNLPF);
        SRAPI_SetUSMFilter(SRModes[mode].pSRHPRegion, SRModes[mode].pSRHPGain);
        SRAPI_SetUSMLPThreshold(SRModes[mode].usLPFGain);
        SRAPI_SetUSMDarkLimit(SRModes[mode].bDarkLimit);
#if 0 //CSCEnhance
        SC_SR_CONTROL = 0x00;
#endif
        SRAPI_TurnOnOff(ON);

    }
    //WaitDisVSync();
        
    SetColorSpace();
#if 0 //CSCEnhance
        SC_SR_CONTROL = 0x30;
#endif
#else
    if (mode == SR_MODE_OFF) {
        SRAPI_TurnOnOff(OFF);
    }
    else {
        SRAPI_TurnOnOff(ON);
        SRAPI_SetMDNFilter(SRModes[mode].pMDNLPF);
        SRAPI_SetUSMFilter(SRModes[mode].pSRHPRegion, SRModes[mode].pSRHPGain);
        SRAPI_SetUSMLPThreshold(SRModes[mode].usLPFGain);
    }        
#endif    
}

#if IS_NT68661_SERIES || IS_NT68770_SERIES || IS_NT68850_SERIES || IS_NT68655_SERIES || IS_NT68790_SERIES
/**************************************************************************//**
 * Set Htotal (HPLL divider) pixel of SR.
 * Before SR block bypass disable, htotal must be setting ready.
 * If input timing Htotal be changed, It must be update at the same time.
 * @param htotal Horizontal pixel count of input timing.
 ******************************************************************************/
void SetSRHtotal(USHRT htotal)
{
    SRAPI_SetHtotal(htotal);
}

/**************************************************************************//**
 * Set input timing Htotal,H width,V height of SR.
 * Before SR block bypass disable, input timing parameter must be setting ready.
 ******************************************************************************/
void SetSRInputTimingParameter(void)
{
    xdata USHRT htotal_temp;
    UCHAR ch;
    ch = 0;
    if (GetInputSyncMode() == DIG_SYNC) {
    #if (INPUT_INTERFACE&INPUT_DP)  
        if (GetCurrInputInterface() == DISPLAY_PORT_INPUT) {
            htotal_temp = (ULONG)DP_GetClock()*10000/GetInputHFreq();
        }
        else
    #endif
        {
 #if ENABLE_HDMI == ON
	        htotal_temp = (ULONG)TMDSDeepColorDetection()*10000/GetInputHFreq();
	        if ((SC_HDMI_DET & BIT1) != 0) {
	            //Set repeat for Manual CSC mode
	            ch = SC_HDMI_AVI[4] & 0x0F;
	            if (ch == 0x01) {//pixel sent 2 times
	                htotal_temp >>= 1; 
	            }
	            else if (ch == 0x03) {//pixel sent 4 times
	                htotal_temp >>= 2;
	            }
	        }
#else
	       htotal_temp = (ULONG)TMDS_GetClock()*10000/GetInputHFreq();
#endif
        }
		
        SRAPI_SetHtotal(htotal_temp);
        if (IsInterlaced()) {
            SRAPI_SetCaptureSize(ReadShortScaler(&SC_GI_CAP_HWID_LO), ReadShortScaler(&SC_GI_CAP_VLEN_LO) >> 1);
        }
        else{
            SRAPI_SetCaptureSize(ReadShortScaler(&SC_GI_CAP_HWID_LO), ReadShortScaler(&SC_GI_CAP_VLEN_LO));
        }
    }
    else {
        SRAPI_SetHtotal(GetAngInputHTotal());
        if (IsInterlaced()) {
           SRAPI_SetCaptureSize(InputTiming.usCapHActive, InputTiming.usCapVActive >> 1);
        }
        else{
           SRAPI_SetCaptureSize(InputTiming.usCapHActive, InputTiming.usCapVActive);            
        }
    }
}

/**************************************************************************//**
 * Set SR block bypass.
 * @param on if on is TRUE(bypass),on is FALSE(not bypass)
 ******************************************************************************/
void SetSRBlockOnOff(UCHAR on)
{
    if (on) {
        SRAPI_SRBlockEnable();
    }
    else {
        SRAPI_SRBlockDisable();
    }
}
#endif
#else
void ForSRCompilerCodePass(void)
{
  code UCHAR temp[]={0x00};
  UCHAR i;
  i = temp[0];
}
#endif //ENABLE_SR == ON
