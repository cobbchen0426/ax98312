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

#if ENABLE_HDMI == ON

//******************************************************************************
// M A C R O   D E F I N I T I O N S
//******************************************************************************
#if AUDIO_OUT == IIS_OUT
    #define AUDIO_PINOUT_SEL       0x04
    #define AUDIO_OUT_CTRL         0x00
    #define AUDIO_OUT_IIS_CTRL1    0x40
    #define AUDIO_OUT_IIS_CTRL2    0xF8
    #define AUDIO_OUT_IIS_CTRL3    0x05
    #define AUDIO_EXT_CAP          0x00
#else
    #define AUDIO_PINOUT_SEL       0x00
    #define AUDIO_OUT_CTRL         0x01
    #define AUDIO_EXT_CAP          0x00
    #define AUDIO_OUT_IIS_CTRL3    0x60
#endif

//******************************************************************************
// G L O B A L   V A R I A B L E S
//******************************************************************************
#if ENABLE_HDMI_AUDIO_CK_RCVY == ON 
/*!
 * Data type for HDMI audio clock recovery (ARC).
 */
typedef struct _ACRITM_ {
    ULONG ulNSVAL;
    ULONG ulCTSSVAL;
} ACRItm;

/*!
 * Data type for HDMI audio clock recovery (ARC).
 */
typedef enum _HDMICLKTYPE_ {
    HDMI_25MHz,
    HDMI_25MHz_101,
    HDMI_27MHz,
    HDMI_27MHz_101,
    HDMI_54MHz,
    HDMI_54MHz_101,
    HDMI_74MHz,
    HDMI_74MHz_101,
    HDMI_148MHz,
    HDMI_148MHz_101,
    HDMI_297MHz,
    HDMI_297MHz_101,
    NUM_HDMICLKTYPE
} HDMICLKTYPE;

/*!
 * Data type for HDMI audio clock recovery (ARC).
 */
typedef enum _AUDIOFSTYPE_ {
    AUDIOFS_44KHz,
    AUDIOFS_NOTINDICATED,
    AUDIOFS_48KHz,
    NUM_AUDIOFSTYPE
} AUDIOFSTYPE;
#endif

//******************************************************************************
// S T A T I C   V A R I A B L E S
//******************************************************************************
static BOOL bHDMIMute = FALSE; /*!< Status of HDMI mute. */
#if ENABLE_INTERNAL_AUDIO_BUZZER == ON
static UCHAR ucReg0x8605; /*!< Temperal storage for scaler register. */
static UCHAR ucReg0x8700; /*!< Temperal storage for scaler register. */
static UCHAR ucReg0x871A; /*!< Temperal storage for scaler register. */
static UCHAR ucReg0x871D; /*!< Temperal storage for scaler register. */
#endif

//******************************************************************************
// E X T E R N A L   V A R I A B L E   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// S T A T I C   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
static void ConfigHDMIAnalogAudioGain(UCHAR value);
static void ConfigHDMIDigitalAudioGain(USHRT value);
static void AudioOffset(void);
#if ENABLE_HDMI_AUDIO_CK_RCVY == ON 
static void HDMIAudioACRCorrection(void);
#endif

//******************************************************************************
// E X T E R N A L   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// F U N C T I O N   B O D Y S
//******************************************************************************

/**************************************************************************//**
 * Get deep color mode by HDMI deep color PLL divider M select
 ******************************************************************************/
/*
UCHAR GetSCDeepColor(void)
{
 UCHAR ret=DEEP_COLOR_24BIT;
    switch (SC_DVI_PLL_M) {
        default:
        case 0x10:
        case 0x20:   
            ret = DEEP_COLOR_24BIT;
            break;
        case 0x28:
            ret = DEEP_COLOR_30BIT;
            break;
        case 0x30:
            ret = DEEP_COLOR_36BIT;
            break;
        case 0x40:
            ret = DEEP_COLOR_48BIT;
            break;
    }

    return ret;
}
*/

/**************************************************************************//**
 * CSC Dithering Manual Mode Enable
 * For The MNT screen have garbage/mute issue when AVI InfoFrame change.
 ******************************************************************************/
/*
void CSCDitherManualModeEn(void)
{
 if((SC_CSC_CTRL2 & BIT0) == 0x01){
    SC_HDMI_RESET_CTRL &= ~BIT3;  
 	if((GetSCDeepColor() >= DEEP_COLOR_30BIT)||((SC_HDMI_AVI[0] & 0x60) == BIT5)){// 10/12/16 bit deep color or YCbCr 422
		SC_CSC_CTRL2 |= BIT4;
	}
	else{
		SC_CSC_CTRL2 &= ~BIT4;
	}
 }
}
*/

/**************************************************************************//**
 * Initialize HDMI-related registers.
 ******************************************************************************/
void HDMIInit(void)
{
    SC_HDMI_SOFTWARE_RESET = 0xFF;
    SC_HDMI_SOFTWARE_RESET = 0x10;

    SC_TMDS_LINK_CLK_SEL |= BIT0;
    SC_AUDIO_SMOOTH = 0xFF;
    SC_AUDIO_VOLUME_R = 0xC6;				 
    SC_AUDIO_VOLUME_L = 0xC6;
    ScalerAudioPowerOn();
    SC_AUDIO_EXT_CAP_CTRL = AUDIO_EXT_CAP;
#if AUDIO_OUT == IIS_OUT
    SC_AUDIO_OUT_IIS_CTRL1 = AUDIO_OUT_IIS_CTRL1;
    SC_AUDIO_OUT_IIS_CTRL2 = AUDIO_OUT_IIS_CTRL2;
#endif
    SC_AUDIO_OUT_IIS_CTRL3 = AUDIO_OUT_IIS_CTRL3;

    // Enable external cap for improving audio performance
    SC_AUDIO_DAC_DRIV_CTRL = 0xcc; //test by Rex 0x00
    SC_AUDIO_TEST1 = 0x06;//test by Rex 0x07;
    SC_AUDIO_ANALOG_OUT_CTRL = 0x70;

#if ENABLE_HDMI_AUDIO_AUTO_MUTE == ON
    SC_AUDIO_AUTO_CTRL1 = 0x00;
    if(GetSCID() == SCID_770_E){
        SC_AUDIO_AUTO_CTRL2 = 0x02;
    }
    else{
        SC_AUDIO_AUTO_CTRL2 = 0x20;
    }
    SC_AUDIO_AUTO_CTRL3 = 0x32;
    SC_AUDIO_AUTO_CTRL4 = 0xC6;
#endif

    SC_HDMI_CLK_INT |= BIT0; // Normal HDMI interrupt
    SC_CP_PACKET_TYPE = 0x02;
    SC_HDMI_PREAMBLE_CYCLE = 0x06;
}

/**************************************************************************//**
 * System perform this function periodically to handle the HDMI events.
 * For example, Color space changed, AV mute etc...
 ******************************************************************************/
void HdmiHandler(void)
{
    UCHAR ch;

    ch = GetCurrInputInterface();
    if ((ch != DIGITAL_INPUT0) && (ch != DIGITAL_INPUT1)) {
        return;
    }

    bHDMIMute = FALSE;

    ch = SC_HDMI_INT_STATE1[2];
    if (ch != 0) {
        //printf("SC_HDMI_INT_STATE1[2] = %02BX\r\n", ch);
        if ((ch & BIT7) != 0) {
            //printf("HDMI/DVI change\r\n");
            bHDMIMute = TRUE;
        }
        //if ((ch & BIT4) != 0) {
        //    printf("Clock detect change detected\r\n");
        //}
        //if ((ch & BIT3) != 0) {
        //    printf("Sync detect change detected\r\n");
        //}
        //if ((ch & BIT0) != 0) {
        //    printf("Video clock frequency changed\r\n");
        //}
#if ENABLE_SCALER_3D == ON
        // Because this bit is used for AMD 3D detection now.
        // We can not clear the bit here
        // Jude 2011/08/25
        ch &= ~BIT6;
#endif
        SC_HDMI_INT_STATE1[2] = ch;
    }
    ch = SC_HDMI_INT_STATE1[3];
    if (ch != 0) {
        //printf("SC_HDMI_INT_STATE1[3] = %02BX\r\n", ch);
        //if ((ch & BIT7) != 0) {
        //    printf("New General Control Packet detected\r\n");
        //}
        if ((ch & BIT6) != 0) {
            bHDMIMute = TRUE;
            //printf("General Control Packet set to mute\r\n");
        }
        if ((ch & BIT4) != 0) {
            //printf("New/changed unrecognized packet detected\r\n");
        }
        if ((ch & BIT3) != 0) {
            //printf("New/changed MPEG InfoFrame detected\r\n");
        }
        if ((ch & BIT2) != 0) {
            //printf("New/changed audio InfoFrame detected\r\n");
        }
        if ((ch & BIT1) != 0) {
            //printf("New/changed SPD InfoFrame detected\r\n");
        }
        if ((ch & BIT0) != 0) {
            //printf("New/changed AVI InfoFrame detected\r\n");
            if (GetModeHandleState() == WAIT_MODE_CHANGE){
                if ((SC_HDMI_AVI[0] & 0x60) != GetScalerColorSpace()){
                    SetModeChangeFlag();
                }
            }
            else{
                SetColorSpace();
            }
        }
        SC_HDMI_INT_STATE1[3] = ch;
    }
    ch = SC_HDMI_INT_STATE1[4];
    if (ch != 0) {
        //printf("SC_HDMI_INT_STATE1[4] = %02BX\r\n", ch);
        if ((ch & BIT4) != 0) {
            //printf("No AVI\r\n");
        }
        if ((SC_CTRL_PACKET[0] != 0) && (SC_CTRL_PACKET[1] != 0)) {
#if ENABLE_HDMI_AUDIO_CK_RCVY == ON 
            HDMIAudioACRCorrection(); // 20100727 Leon for unknown media player
#endif
#if ENABLE_HDMI_FS_MUTE == ON 
            HDMIAPI_MuteUnmatchedFs();
#endif
            if ((ch & BIT0) != 0) {
                //printf("FIFO under run\r\n");
                SC_HDMI_SOFTWARE_RESET |= BIT1;
                SC_HDMI_SOFTWARE_RESET &= ~BIT1;
                Sleep(5);
            }
            if ((ch & BIT1) != 0) {
                //printf("FIFO over run\r\n");
                SC_HDMI_SOFTWARE_RESET |= BIT1;
                SC_HDMI_SOFTWARE_RESET &= ~BIT1;
                Sleep(5);
            }
        }
        SC_HDMI_INT_STATE1[4] = ch;
    }
    
#if ENABLE_SCALER_3D == ON
    ch = SC_HDMI_INT_STATE2[1];
    if (ch != 0) {
        if ((ch & BIT7) != 0) {
            // On some devices, the VSP is sent after timing stable and our f/w may not catch the
            // correct the information during mode change. It causes the display to be 2D while input
            // is 3D.To avoid this kind of issue, we check the VSP periodically to make display
            // being right.
            if (IsHDMI() && SC3DAPI_CheckVSI3DStatus() && !SC3DAPI_IsHDMI3D()) {
                SetModeChangeFlag();
            }
            if (IsHDMI() && !SC3DAPI_CheckVSI3DStatus() && SC3DAPI_IsHDMI3D() && !SC3DAPI_IsManualHDMI3D()) {
                SetModeChangeFlag();
            }
            if (IsHDMI() && SC3DAPI_CheckVSI3DStatus() && SC3DAPI_IsHDMI3DFmtChanged()) {
                SetModeChangeFlag();
            }
        }
        SC_HDMI_INT_STATE2[1] = ch;
    }
#endif
}

/**************************************************************************//**
 * Check HDMI audio/video are muted or not.
 * @return TRUE if HDMI audio/video are muted else FALSE.
 ******************************************************************************/
BOOL IsHDMIDataMute(void)
{
    return bHDMIMute;
}

/**************************************************************************//**
 * Clear HDMI-related interrupt status.
 * E.x. AV mute.
 ******************************************************************************/
void ClearHDMIStatus(void)
{
    SC_HDMI_INT_STATE1[2] = (BIT7 | BIT4 | BIT3);
    SC_HDMI_INT_STATE1[3] = BIT6;
}

#if 0
/**************************************************************************//**
 * Enable AVMute interrupt.
 * @param enable TRUE to enable HDMI AVMute interrupt.
 ******************************************************************************/
void HDMIEnableAVMuteInt(UCHAR enable)
{
    if (enable) {
        SC_HDMI_INT_UNMASK1[2] |= BIT6;
        McuScalerHDMIIntEnable();
    }
    else {
        SC_HDMI_INT_UNMASK1[2] &= ~BIT6;
        McuScalerHDMIIntDisable();
    }
}
#endif

/**************************************************************************//**
 * Detect the status of deep color from info-frame and set proper divider.
 ******************************************************************************/
USHRT TMDSDeepColorDetection(void)
{
    USHRT clock;

    clock = TMDS_GetClock();
    switch (SC_HDCP_PACKING & 0x07) {
        case 4:
            SC_DVI_PLL_M = 0x20;
            break;
        case 5:
            SC_DVI_PLL_M = 0x28;
            clock = (clock * 8 + 5) / 10;
            break;
        case 6:
            SC_DVI_PLL_M = 0x30;
            clock = (clock * 8 + 6) / 12;
            break;
        case 7:
            SC_DVI_PLL_M = 0x40;
            clock = (clock * 8 + 8) / 16;
            break;
    }
    return clock;
}

/**************************************************************************//**
 * Function to enable/disable detecting HDMI preamble.
 * @param enable TRUE/FALSE to enable/disable preamble detection.
 ******************************************************************************/
void HDMIEnablePreambleDetection(UCHAR enable)
{
    if (enable) {
        SC_HDMI_PREAMBLE_CYCLE = 0x06;
    }
    else {
        SC_HDMI_PREAMBLE_CYCLE = 0x09;
    }
}

/**************************************************************************//**
 * Function to enable/disable auto HDMI video configuration by scaler.
 * @param enable TRUE/FALSE to enable/disable AVC.
 ******************************************************************************/
void HDMIEnableAVC(UCHAR enable)
{
    if (enable) {
        SC_HDMI_AUTO_CTRL |= BIT2;
    }
    else {
        SC_HDMI_AUTO_CTRL &= ~BIT2;
    }
}

/**************************************************************************//**
 * Soft reset HDMI-related circuits.
 ******************************************************************************/
void HDMISoftReset(void)
{
    // After this soft reset, please make sure there is delay timing befure turn on system interrupt
    SC_HDMI_SOFTWARE_RESET |= BIT0;
    SC_HDMI_SOFTWARE_RESET &= ~BIT0;
}

/**************************************************************************//**
 * Set HDMI analog audio gain.
 * @param value The range is from 0x00 to 0xC6.
 ******************************************************************************/
static void ConfigHDMIAnalogAudioGain(UCHAR value)
{
    SC_AUDIO_VOLUME_R = value;
    SC_AUDIO_VOLUME_L = value;
}

/**************************************************************************//**
 * Set HDMI digital audio gain
 * @param value The range is from 0x0000 to 0xFFFF.
 ******************************************************************************/
static void ConfigHDMIDigitalAudioGain(USHRT value)
{
    WriteShortScaler(&SC_DIG_AUDIO_GAIN_L_LO, value);        
    WriteShortScaler(&SC_DIG_AUDIO_GAIN_R_LO, value);       
}

/**************************************************************************//**
 * Control the volume of scaler audio output.
 * @param value The range is from 0 to HDMI_AUDIO_VOL_INF_RANGE.
 ******************************************************************************/
void ConfigScalerAudio(USHRT value)
{
#ifndef HDMI_AUDIO_VOLUME_RANGE
#define HDMI_AUDIO_VOLUME_RANGE    1023
#endif

#define VOL_STEP 8

    if (value > HDMI_AUDIO_VOLUME_RANGE) 
	{
        	ConfigHDMIAnalogAudioGain(DEF_HDMI_ANA_VOL);
        	ConfigHDMIDigitalAudioGain(DEF_HDMI_DIG_VOL);
        	return;
    	}

    if ((SC_AUDIO_SELECT & 0x20) != 0)	 //PCM
	{ 
        USHRT startvol, endvol, vol;
        startvol = ReadShortScaler(&SC_DIG_AUDIO_GAIN_L_LO);
        endvol = (ULONG)value * 0xFFFE / HDMI_AUDIO_VOLUME_RANGE + 1;
        ConfigHDMIAnalogAudioGain(DEF_HDMI_ANA_VOL);
        if (endvol > 0x6000) 
		{
            		SC_AUDIO_DELTA_SIGMA_CTRL &= ~BIT4;
        	}
        else 
		{
            		SC_AUDIO_DELTA_SIGMA_CTRL |= BIT4;
        	}
        if (startvol > endvol) 
	     {
             	for (vol=startvol; vol>endvol; vol-=VOL_STEP) 
			{
                		ResetWDTimer();
                		ConfigHDMIDigitalAudioGain(vol);
               	 if ((vol - endvol) < VOL_STEP) 
				{
                    			break;
                		}
            		}
          	 }
        else 
		{
            	for (vol=startvol; vol<endvol; vol+=VOL_STEP) 
		 	{
                  		ResetWDTimer();
                 		 ConfigHDMIDigitalAudioGain(vol);
                	   if ((endvol - vol) < VOL_STEP)
				{
                      		break;
                     	}
               	}
              }
        	ConfigHDMIDigitalAudioGain(endvol);
    }
    else 
	{
        	value = HDMI_AUDIO_VOLUME_RANGE - value;
        	value = (ULONG)value * 0xC6 / HDMI_AUDIO_VOLUME_RANGE;
       	 ConfigHDMIAnalogAudioGain(value);
   	 }

#undef VOL_STEP
}

/**************************************************************************//**
 * Turn off scaler analog audio power.
 ******************************************************************************/
void ScalerAudioPowerOff(void)
{
    SC_AUDIO_OUT_CTRL &= ~BIT0;
}

/**************************************************************************//**
 * Turn on scaler analog audio power.
 ******************************************************************************/
void ScalerAudioPowerOn(void)
{
    SC_AUDIO_OUT_CTRL = AUDIO_OUT_CTRL;
}

/**************************************************************************//**
 * Select audio in/output channel.
 * @param ch Input/output audio channel.
 ******************************************************************************/
void ScalerAudioSelect(AudioInOutChannel ch)
{
    // Select audio input channel
    switch(ch & AUDIO_IN_CH_MASK) {
        case AUDIO_IN_LINE1:
        #if ENABLE_HDMI_AUDIO_AUTO_MUTE == ON
            SC_AUDIO_AUTO_CTRL1 = 0x00;
        #endif
            SC_AUDIO_SELECT = (SC_AUDIO_SELECT & 0xCF);
            break;
        case AUDIO_IN_LINE2:
        #if ENABLE_HDMI_AUDIO_AUTO_MUTE == ON
            SC_AUDIO_AUTO_CTRL1 = 0x00;
        #endif
            SC_AUDIO_SELECT = (SC_AUDIO_SELECT & 0xCF) | BIT4;
            break;
        case AUDIO_IN_DSD:
        #if ENABLE_HDMI_AUDIO_AUTO_MUTE == ON
            SC_AUDIO_AUTO_CTRL1 = 0x03;
        #endif
            SC_AUDIO_SELECT = (SC_AUDIO_SELECT & 0xCF) | BIT5 | BIT4;
            break;
        default : // AUDIO_IN_HDMI
        #if ENABLE_HDMI_AUDIO_AUTO_MUTE == ON
            SC_AUDIO_AUTO_CTRL1 = 0x03;
        #endif
            SC_AUDIO_SELECT = (SC_AUDIO_SELECT & 0xCF) | BIT5;
            break;
    }

    // Select audio output channel
    switch(ch & AUDIO_OUT_CH_MASK) {
        case AUDIO_OUT_DISABLE:
            SC_AUDIO_SELECT = SC_AUDIO_SELECT | BIT3 | BIT2;
            break;
        case AUDIO_OUT_IIS:
            SC_AUDIO_SELECT = (SC_AUDIO_SELECT & 0xF3) | BIT2;
            break;
        case AUDIO_OUT_DSD:
            SC_AUDIO_SELECT = (SC_AUDIO_SELECT & 0xF3) | BIT3;
            break;
        default : // AUDIO_OUT_LINEOUT
            SC_AUDIO_SELECT = (SC_AUDIO_SELECT & 0xF3);
            break;
    }
}

/**************************************************************************//**
 * Turn on internal audio pattern with specific frequency.
 * @param freq Audio frequency.
 ******************************************************************************/
#if ENABLE_INTERNAL_AUDIO_BUZZER == ON
void EnableVCSAudioBuzzer(USHRT freq)
{
    ULONG ratio;
    ULONG cts_value, n_value;

    if ((SC_AUDIO_DELTA_SIGMA_CTRL & BIT0) != 0) {
        // Internal audio pattern has been turned on.
        return;
    }

    if (((GetCurrInputInterface() == DIGITAL_INPUT0)
            || (GetCurrInputInterface() == DIGITAL_INPUT1)) && IsHDMI()) {
        n_value = (float) freq * 4096 / 1000;
        Write3ByteScaler(&SC_ACR_N_VALUE_LO, n_value); //Write 0x703~0x705
        cts_value = ReadShortScaler(&SC_VIDEO_HTOTAL_LO) & 0x1FFF;
        cts_value = cts_value * usHSyncFreq / 10; // cts_value = Input clock /1000
        Write3ByteScaler(&SC_ACR_CTS_VALUE_LO, cts_value); //Write 0x709~0x70B
        ucReg0x8700 = SC_ACR_CTRL;
        SC_ACR_CTRL = 0x18; // User software N, CTS value
    }
    else {
        ratio = (float) freq * 16384 * 131072 / REF_CLK;
        Write3ByteScaler(&SC_VCLK_RATIO_LO, ratio);
        SC_HPLL_FREQ_CTRL &= ~BIT4;
    }
    ucReg0x8605 = SC_HDMI_SOFTWARE_RESET;
    ucReg0x871A = SC_AUDIO_SELECT;
    ucReg0x871D = SC_AUDIO_DELTA_SIGMA_CTRL;
    SC_HDMI_SOFTWARE_RESET = 0x00;
    SC_AUDIO_SELECT = 0x20;
    SC_AUDIO_DELTA_SIGMA_CTRL = 0x15;
}

/**************************************************************************//**
 * Turn off internal audio pattern.
 ******************************************************************************/
void DisableVCSAudioBuzzer(void)
{
    if (((GetCurrInputInterface() == DIGITAL_INPUT0)
            || (GetCurrInputInterface() == DIGITAL_INPUT1)) && IsHDMI()) {
        SC_ACR_CTRL = ucReg0x8700; // Recover to hardware N, CTS value
    }
    else {
        SC_HPLL_FREQ_CTRL |= BIT4;
    }
    SC_HDMI_SOFTWARE_RESET = ucReg0x8605;
    SC_AUDIO_SELECT = ucReg0x871A;
    SC_AUDIO_DELTA_SIGMA_CTRL = ucReg0x871D;
}
#endif

/**************************************************************************//**
 * Check the current input is HDMI or not.
 * @return TRUE if input is HDMI else FALSE.
 ******************************************************************************/
BOOL IsHDMI(void)
{
    if ((SC_HDMI_DET & BIT1) != 0) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}

/**************************************************************************//**
 * Check the current input is HDMI video timing or not.
 * @return TRUE if input is HDMI video timing else FALSE.
 ******************************************************************************/
BOOL IsHDMIVideo(void)
{
    if (((SC_HDMI_DET & BIT1) != 0) && (SC_HDMI_AVI_TYPE == 0x82) && ((SC_HDMI_AVI[0] & 0x60) != 0)) {//HDMI & YUV color
        return TRUE;
    }
    else {
        return FALSE;
    }
}

#if ENABLE_HDMI_AUDIO_CK_RCVY == ON 
/**************************************************************************//**
 * Function of recovering HDMI audio clock.
 ******************************************************************************/
static void HDMIAudioACRCorrection(void)
{   
    static code ACRItm ulNCTSSVALTable[NUM_AUDIOFSTYPE][NUM_HDMICLKTYPE] = 
    {
	    {// Audio FS = 44.1KHz
            {6272,        28000}, // HDMI_25MHz
            {7007,        31250}, // HDMI_25MHz_101
            {6272,        30030}, // HDMI_27MHz
            {6272,        30000}, // HDMI_27MHz_101
            {6272,        60060}, // HDMI_54MHz
            {6272,        60000}, // HDMI_54MHz_101
            {0x001880, 0x014244}, // HDMI_74MHz
            {0x0045AC, 0x039387}, // HDMI_74MHz_101
            {6272,       165000}, // HDMI_148MHz
            {8918,       234375}, // HDMI_148MHz_101
            {4704,       247500}, // HDMI_297MHz
            {4459,       234375}, // HDMI_297MHz_101
        },
        {// Audio FS = Not indicated
            {6272,        28000}, // HDMI_25MHz
            {7007,        31250}, // HDMI_25MHz_101
            {6272,        30030}, // HDMI_27MHz
            {6272,        30000}, // HDMI_27MHz_101
            {6272,        60060}, // HDMI_54MHz
            {6272,        60000}, // HDMI_54MHz_101
            {0x001880, 0x014244}, // HDMI_74MHz
            {0x0045AC, 0x039387}, // HDMI_74MHz_101
            {6272,       165000}, // HDMI_148MHz
            {8918,       234375}, // HDMI_148MHz_101
            {4704,       247500}, // HDMI_297MHz
            {4459,       234375}, // HDMI_297MHz_101
        },
        {// Audio FS = 48KHz
            {6144,        25200}, // HDMI_25MHz
            {6864,        28125}, // HDMI_25MHz_101
            {6144,        27027}, // HDMI_27MHz
            {6144,        27000}, // HDMI_27MHz_101
            {6144,        54054}, // HDMI_54MHz
            {6144,        54000}, // HDMI_54MHz_101
            {6144,        74250}, // HDMI_74MHz
            {11648,      140625}, // HDMI_74MHz_101
            {6144,       148500}, // HDMI_148MHz
            {5824,       140625}, // HDMI_148MHz_101
            {5120,       247500}, // HDMI_297MHz
            {5824,       281250}, // HDMI_297MHz_101
        },
    };
    UCHAR fs, ch, type = 0xFF;
    USHRT pixelclock;
    ULONG n_hval, cts_hval;

    SC_VPLL_CTRL |= BIT2; // Audio FIFO Auto Balance
    
    ch = SC_HDMI_INT_STATE1[4];
    fs = SC_AUDIO_IN_SPDIF_STATE4 & 0x0F;
    pixelclock = TMDS_GetClock();//DVI pixel clock
    n_hval = Read3ByteScaler(&SC_ACR_N_HVAL[0]) & 0x0FFFFF;
    cts_hval = Read3ByteScaler(&SC_ACR_CTS_HVAL[0]) & 0x0FFFFF;
    if (pixelclock <= 0x0019) {//25MHz
        type = 0;
    }
    else if (pixelclock < 0x0028) {//40MHz
        type = 1;
    }
    else if (pixelclock < 0x0040) {//64MHz
        type = 2;
    }
    else if (pixelclock < 0x006F) {//111MHz
        type = 3;
    }
    else if (pixelclock < 0x00DE) {//222MHz
        type = 4;
    }
    else if (pixelclock < 0x0130) {//304MHz
        type = 5;
    }
//pixelclock > 304MHz, audio != 44k, 48k. software reset and return
    if ((type == 0xFF) || (fs >= NUM_AUDIOFSTYPE) || (fs == AUDIOFS_NOTINDICATED)) {
        if (SC_ACR_CTRL != 0x00) {
            SC_ACR_CTRL = 0x00;
            Sleep(60);
            SC_HDMI_SOFTWARE_RESET |= BIT1;
            SC_HDMI_SOFTWARE_RESET &= ~BIT1;
            Sleep(5);
            SC_HDMI_INT_STATE1[4] = ch;
        }
        return;
    }
//pixelclock < 304MHz, audio == 44k, 48k
    type *= 2;
    if (((labs(n_hval - ulNCTSSVALTable[fs][type].ulNSVAL) > 100) && (labs(n_hval - ulNCTSSVALTable[fs][type+1].ulNSVAL) > 100)) 
    || ((labs(cts_hval - ulNCTSSVALTable[fs][type].ulCTSSVAL) > 1000) && (labs(cts_hval - ulNCTSSVALTable[fs][type+1].ulCTSSVAL) > 1000))) {
        if ((SC_ACR_CTRL & 0x18) == 0x00) { //hardware-determined: auto
            // N-CTS Value Type 1
            Write3ByteScaler(&SC_ACR_N_VALUE_LO, ulNCTSSVALTable[fs][type].ulNSVAL);
            Write3ByteScaler(&SC_ACR_CTS_VALUE_LO, ulNCTSSVALTable[fs][type].ulCTSSVAL);
            SC_ACR_CTRL = 0x19; //software-determined: manual
            Sleep(60);
            SC_HDMI_SOFTWARE_RESET |= BIT1;
            SC_HDMI_SOFTWARE_RESET &= ~BIT1;
            Sleep(5);

            SC_HDMI_INT_STATE1[4] = ch;
            
            ch = SC_HDMI_INT_STATE1[4];
            if ((ch & BIT1) != 0) { // N-CTS Format Type 2. FIFO over run
                Write3ByteScaler(&SC_ACR_N_VALUE_LO, ulNCTSSVALTable[fs][type+1].ulNSVAL);
                Write3ByteScaler(&SC_ACR_CTS_VALUE_LO, ulNCTSSVALTable[fs][type+1].ulCTSSVAL);
                SC_ACR_CTRL = 0x19; //software-determined: manual
                Sleep(60);
                SC_HDMI_SOFTWARE_RESET |= BIT1;
                SC_HDMI_SOFTWARE_RESET &= ~BIT1;
                Sleep(5);

                SC_HDMI_INT_STATE1[4] = ch;
            }
        }
    }
    else {
        if (SC_ACR_CTRL != 0x00) { //no error change to hardware-determined
            SC_ACR_CTRL = 0x00;
            Sleep(60);
            SC_HDMI_SOFTWARE_RESET |= BIT1;
            SC_HDMI_SOFTWARE_RESET &= ~BIT1;
            Sleep(5);

            SC_HDMI_INT_STATE1[4] = ch;
        }
    }
}
#endif

/**************************************************************************//**
 * Function to validate the audio clock.
 * If the CTS/N of current HDMI input does not match with audio sampling rate in
 * the info-frame, the system audio will be muted.
 ******************************************************************************/
#if ENABLE_HDMI_FS_MUTE == ON 
void HDMIAPI_MuteUnmatchedFs(void)
{
    code USHRT FsTable[][2] = {
        {0x0000,   441},
        {0x0008,   882},
        {0x000C,  1764},
        {0x0002,   480},
        {0x000A,   960},
        {0x000E,  1920},
        {0x0003,   320}
    };

    UCHAR i;
    ULONG tmp_cts, tmp_n;
    USHRT clk, fs;

    for (i = 0; i < sizeof(FsTable)/sizeof(USHRT)/2 ; i++) {
        if (FsTable[i][0] == (SC_AUDIO_HW_EXT_FS & 0x0F)) {
            break;
        }
    }

    if (i >= sizeof(FsTable)/sizeof(USHRT)/2) {
        return;
    }

    tmp_n = Read3ByteScaler(&SC_ACR_N_HVAL[0]) & 0x0FFFFF;
    tmp_cts = Read3ByteScaler(&SC_ACR_CTS_HVAL[0]) & 0x0FFFFF;
    if ((tmp_n == 0) || (tmp_cts == 0)) {
        return;
    }
    clk = TMDS_GetClock();
    fs = (USHRT)((float)clk * 10000 * tmp_n / tmp_cts / 128);

    // We define the tolerance of fs and CTS/N less then 10KHz
    // If the tolerance is larger than 10K, we mute the audio.
    // Jude 2011/08/27
    if (abs(fs - FsTable[i][1]) > 100) {
    #if ENABLE_INTERNAL_AUDIO_BUZZER == ON
        SC_AUDIO_SELECT |= 0x0C;
    #else
        SC_AUDIO_DELTA_SIGMA_CTRL = 0x01;
    #endif
        SetGlobalTimer(GLOBAL_TMR_HDMI_FS_MUTE, 500);
    }
    else if (GetGlobalTimer(GLOBAL_TMR_HDMI_FS_MUTE) == 0) {
    #if ENABLE_INTERNAL_AUDIO_BUZZER == ON
        SC_AUDIO_SELECT = (SC_AUDIO_SELECT & 0xF3) | AUDIO_PINOUT_SEL;;
    #else
        SC_AUDIO_DELTA_SIGMA_CTRL = 0x00;
    #endif
    }
}
#endif

#endif //ENABLE_HDMI == ON
