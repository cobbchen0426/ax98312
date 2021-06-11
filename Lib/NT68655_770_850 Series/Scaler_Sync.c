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
#define HSYNC_LOWER_BOUND   12   /*!< The lower bound of valid HSync frequency. The unit is KHz. */
#define HSYNC_UPPER_BOUND   200  /*!< The upper bound of valid HSync frequency. The unit is KHz. */
#define VSYNC_LOWER_BOUND   20   /*!< The lower bound of valid VSync frequency. The unit is Hz. */
#define VSYNC_UPPER_BOUND   200  /*!< The upper bound of valid VSync frequency. The unit is Hz. */
#define H_CNT_LOW_THLD      (8UL*REF_CLK/1000/HSYNC_UPPER_BOUND) /*!< The low threshold of valid HSync counter. */
#define H_CNT_HIGH_THLD     (8UL*REF_CLK/1000/HSYNC_LOWER_BOUND) /*!< The high threshold of valid HSync counter. */
#define V_CNT_LOW_THLD      (1UL*REF_CLK/256/VSYNC_UPPER_BOUND)  /*!< The low threshold of valid VSync counter. */
#define V_CNT_HIGH_THLD     (1UL*REF_CLK/256/VSYNC_LOWER_BOUND)  /*!< The high threshold of valid VSync counter. */
#define DIG_VALID_PIXEL_RATE 22

//******************************************************************************
// G L O B A L   V A R I A B L E S
//******************************************************************************
xdata USHRT usHSyncFreq; /*!< HSync frequency. The unit is 0.1KHz. */
xdata USHRT usVSyncFreq; /*!< VSync frequency. The unit is 0.1Hz. */
xdata UCHAR ucZpInterface; /*!< Interface ID in the zero power mode. */

//******************************************************************************
// S T A T I C   V A R I A B L E S
//******************************************************************************

//******************************************************************************
// E X T E R N A L   V A R I A B L E   P R O T O T Y P E S
//******************************************************************************
#if ENABLE_LOW_PWR_MODE == ON
extern idata USHRT usMCUCLKDIVIDERLoop;
#endif

//******************************************************************************
// S T A T I C   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
static BOOL CheckSOG(void);
static BOOL ZpSyncDetect(void);
#if ((INPUT_INTERFACE&INPUT_DIG0) || (INPUT_INTERFACE&INPUT_DIG1))
static BOOL ZpHVpresentDetect(void);
#endif

//******************************************************************************
// E X T E R N A L   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// F U N C T I O N   B O D Y S
//******************************************************************************

/**************************************************************************//**
 * Initialize Sync-related registers.
 ******************************************************************************/
void SyncInit(void)
{
    SC_GI_SYNC_CTRL = 0x24;
    SC_GI_SYNC_CTRL2 = 0xC0;
    SC_GI_SYNC_CTRL3 = 0x42;
    SC_HPRE_THR_LO = 0x00;
    SC_HPRE_THR_HI = 0x1F;
    SC_VPRE_THR_LO = 0x13;
    SC_VPRE_THR_HI = 0x42;
    SC_HCNT_THR = 0x04;
    SC_V_CHANG_CTRL = 0x24;
    SC_SYNC_INT_EN1 = 0x3C;
    SC_SYNC_INT_EN2 = 0x07;

    SC_SYNC_INT_FLAG1 = 0x3F;
    SC_SYNC_INT_FLAG2 = 0x1F;
    SC_GI_FIELD_WIN = 0xC5;
    SC_NEW_HSYNC_CTRL1 |= (BIT0 | BIT2);
    SC_FAST_MUTE_CTRL = 0x4A;
    SC_FIELD_POLARITY_CTRL = 0x02;
    SC_VCR_CTRL = 0x10;

    EnableSyncProcFreeRun(FALSE);
}

/**************************************************************************//**
 * Get current input HSync frequency.
 * The unit is 0.1KHz.
 * @return Input HSync frequency.
 ******************************************************************************/
USHRT GetInputHFreq(void)
{
    USHRT cnt;

    cnt = ReadShortScaler(&SC_GI_HCNT_LO) & 0x1FFF;

    // Valid HSync range : 12KHz < HS < 200KHz
    if ((cnt > H_CNT_HIGH_THLD) || (cnt < H_CNT_LOW_THLD)) {
        usHSyncFreq = 0xFFFF;
    }
    else {
        usHSyncFreq = (USHRT) ((8UL * REF_CLK / cnt + 50) / 100);
    }

    return usHSyncFreq;
}

/**************************************************************************//**
 * Get current input VSync frequency.
 * The unit is 0.1Hz.
 * @return Input VSync frequency.
 ******************************************************************************/
USHRT GetInputVFreq(void)
{
    USHRT cnt;

    cnt = ReadShortScaler(&SC_GI_VCNT_LO) & 0x1FFF;

    // Valid VSync range : 20Hz < VS < 200Hz
    if ((cnt > V_CNT_HIGH_THLD) || (cnt < V_CNT_LOW_THLD)) {
        usVSyncFreq = 0xFFFF;
    }
    else {
        usVSyncFreq = (USHRT) ((10UL * REF_CLK / cnt + 128) / 256);
    }

    return usVSyncFreq;
}

/**************************************************************************//**
 * Get current input HSync/VSync polarity.
 * The unit is 0.1Hz.
 * @return Input HSync/VSync polarity.
 ******************************************************************************/
UCHAR GetInputHVPolarity(void)
{
    UCHAR polarity;

    switch (SC_GI_SYNC_STATUS & 0x03) {
        case 0x00:
            polarity = HNVN;
            break;

        case 0x01:
            polarity = HPVN;
            break;

        case 0x02:
            polarity = HNVP;
            break;

        case 0x03:
            polarity = HPVP;
            break;
    
        default:
            polarity = HPVP;
            break;
    }

    return polarity;
}

/**************************************************************************//**
 * Get current input HSync width.
 * The value is number of 12MHz.
 * @return Input HSync width.
 ******************************************************************************/
UCHAR GetInputHSyncWidth(void)
{
    return SC_GI_HS_WID;
}

/**************************************************************************//**
 * Get current input VSync width.
 * The value is number of lines.
 * @return Input VSync width.
 ******************************************************************************/
UCHAR GetInputVSyncWidth(void)
{
    return SC_GI_VS_WID;
}

/**************************************************************************//**
 * Get current input VTotal
 * The value is number of 12MHz.
 * @return Input VTotal.
 ******************************************************************************/
USHRT GetInputVTotal(void)
{
    // Sometimes, we may get wrong vtotal during mode search because scaler does not update the vtotal yet.
    // To solve this issue, we always get vtotal from H/V sync calculation.
    // Jude 2011/10/18
#if 1
    USHRT hcnt, vcnt;

    hcnt = ReadShortScaler(&SC_GI_HCNT_LO) & 0x1FFF;
    if ((hcnt > H_CNT_HIGH_THLD) || (hcnt < H_CNT_LOW_THLD)) {
        return 0;
    }

    vcnt = ReadShortScaler(&SC_GI_VCNT_LO) & 0x1FFF;
    if ((vcnt > V_CNT_HIGH_THLD) || (vcnt < V_CNT_LOW_THLD)) {
        return 0;
    }

    return (USHRT)((float)2048 * vcnt / hcnt + 0.5);
#else
    USHRT hcnt, vcnt;
    UCHAR interface = GetCurrInputInterface();

    hcnt = ReadShortScaler(&SC_GI_HCNT_LO) & 0x1FFF;
    if ((hcnt > H_CNT_HIGH_THLD) || (hcnt < H_CNT_LOW_THLD)) {
        return 0;
    }

    vcnt = ReadShortScaler(&SC_GI_VCNT_LO) & 0x1FFF;
    if ((vcnt > V_CNT_HIGH_THLD) || (vcnt < V_CNT_LOW_THLD)) {
        return 0;
    }

    // We can not get correct vtotal under DVI if signal is pure DE
    // or if sync-processor is in DE mode. To solve this issue, we
    // return vtotal by Hsync/Vsync when input is digital signal.
    if ((interface == DIGITAL_INPUT0) || (interface == DIGITAL_INPUT1)) {
        return (USHRT)((float)2048 * vcnt / hcnt + 0.5);
    }

    return ReadShortScaler(&SC_GRAPHIC_VTOTAL_COUNTER_LO) + 1;
#endif
}

/**************************************************************************//**
 * Setup Hync overflow mask to reduce mode change time.
 * @param on TRUE to setup overflow mask by HSync. FALSE to setup default overflow mask.
 ******************************************************************************/
void SetupHSyncOverflowMask(UCHAR on)
{
#define HSYNC_BAND_LOW  ((float)REF_CLK/12000000*244)
#define HSYNC_BAND_MID  ((float)REF_CLK/12000000*478)
#define HSYNC_BAND_MAX  ((float)REF_CLK/12000000*947)

    SC_INPUT_SELECT &= 0x0F;
if (GetCurrInputInterface() != DISPLAY_PORT_INPUT) { // Fix DP DE original mode bug
    SC_INPUT_SELECT |= 0x80; // Default overflow point 11.72KHz

    if (on) {
        if (usHSyncFreq > HSYNC_BAND_MAX) {
            SC_INPUT_SELECT |= 0xF0; // overflow point 93.75KHz
        }
        else if (usHSyncFreq > HSYNC_BAND_MID) {
            SC_INPUT_SELECT |= 0xE0; // overflow point 46.8KHz
        }
        else if (usHSyncFreq > HSYNC_BAND_LOW) {
            SC_INPUT_SELECT |= 0xC0; // overflow point 23.4KHz
        }
    }
}
#undef HSYNC_BAND_LOW
#undef HSYNC_BAND_MID
#undef HSYNC_BAND_MAX
}

/**************************************************************************//**
 * Check current input sync status.
 * @return The value would be one of NO_SYNC/SEP_SYNC/COM_SYNC/SOG_SYNC/DIG_SYNC.
 ******************************************************************************/
UCHAR CheckInputSync(void)
{
    UCHAR curr_interface;
    UCHAR sync = NO_SYNC;
    if (IsZpMode() == TRUE) 
	{
        if (ZpSyncDetect() == TRUE) 
		{
    		#if (INPUT_INTERFACE&INPUT_DP)
            		if (GetCurrInputInterface()==DISPLAY_PORT_INPUT && (DP_CTRL&BIT4) == 0) 
				{
                			return NO_SYNC;
            			}
    		#endif
            			return UNKNOWN_SYNC;
        	}
        else 
		{
            		return NO_SYNC;
        	}
    }
    //=================================
    curr_interface = GetCurrInputInterface();
    switch (curr_interface) 
		{
        	case ANALOG_SEP_INPUT0: //Composite signal's priority is higher than separate signal
            							//H/V present, Composite non-present, H/V non-overflow
            		if ((SC_GI_SYNC_STATUS & 0xF8) == 0x18) 
				{
               			 McuScalerIntEnable(); //MCU will response to scaler interrupt
                			sync = SEP_SYNC;
            			} //H/V/Com present, H/V non-overflow
            		else if ((SC_GI_SYNC_STATUS & 0xF8) == 0x38) 
				{
                			McuScalerIntEnable(); //MCU will response to scaler interrupt
               		 	SetInputInterface(ANALOG_COM_INPUT0);
                			sync = COM_SYNC;
            			}
            				break;

        case ANALOG_SEP_INPUT1: ////Composite signal's priority is higher than seperate signal
            							//H/V present, Composite non-present, H/V non-overflow
            if ((SC_GI_SYNC_STATUS & 0xF8) == 0x18) 
			{
                		McuScalerIntEnable(); //MCU will response to scaler interrupt
                		sync = SEP_SYNC;
            		} //H/V/Com present, H/V non-overflow
            else if ((SC_GI_SYNC_STATUS & 0xF8) == 0x38) 
			{
                		McuScalerIntEnable(); //MCU will response to scaler interrupt
                		SetInputInterface(ANALOG_COM_INPUT1);
                		sync = COM_SYNC;
            		}
            break;

        case ANALOG_COM_INPUT0:
        case ANALOG_COM_INPUT1:
            //Composite present, H/V non-overflow
            if ((SC_GI_SYNC_STATUS & 0xE8) == 0x28) 
		{
              	  	McuScalerIntEnable(); //MCU will response to scaler interrupt
                		sync = COM_SYNC;
            	}
            break;

        case ANALOG_SOG_INPUT0:
        case ANALOG_SOG_INPUT1:
        case ANALOG_YPBPR_INPUT0:
        case ANALOG_YPBPR_INPUT1:
            //Composite present, H/V non-overflow
            if ((SC_GI_SYNC_STATUS & 0xE0) == 0x20) 
			{
                							// Check vtotal to avoid the bug of new h-polarity detection.
                if (CheckSOG() == TRUE) 
				{
                    			McuScalerIntEnable(); //MCU will response to scaler interrupt
                    			sync = SOG_SYNC;
                		}
                else 
				{
                    			sync = NO_SYNC;
                		}
            		}
            break;
#if (INPUT_INTERFACE&INPUT_DP)
        case DISPLAY_PORT_INPUT:
            if (IsDPTrainingDone() == TRUE) {
                if ((SC_DP_10F2 & BIT6) != 0) {
                    if ((DP_GetClock() > 12)) {
    //                #if DVI_MODE == DVI_DE_MODE
                        if ((SC_GI_SYNC_STATUS & 0xC0) == 0x00) {
    //                #else
    //                    if ((SC_GI_SYNC_STATUS & 0xF8) == 0x18) {
    //                #endif
                            McuScalerIntEnable(); //MCU will response to scaler interrupt
                            sync = DIG_SYNC;
                        }
                    }
                }
            }
            break;
#endif
        case DIGITAL_INPUT0:
        case DIGITAL_INPUT1:
#if (INPUT_INTERFACE&INPUT_MHL0) || (INPUT_INTERFACE&INPUT_MHL1)
            MHLSetInterface(curr_interface);
#endif
            //Check SCDT
            TMDSImpedanceDetection();
            if ((SC_DVI_STATUS & BIT0) != 0) {
                TMDSBandwidthDetection(FALSE);
            #if ENABLE_HDMI == ON
                // Always enable preamble detection during sync detection
                HDMIEnablePreambleDetection(TRUE);
                HDMIEnableAVC(TRUE);
            #endif
                if (TMDSClockStable() == TRUE ) {
                    TMDSBandwidthDetection(TRUE);
                #if ENABLE_HDMI == ON
                    TMDSDeepColorDetection();
                #endif
                #if ENABLE_SCALER_3D == ON
                    SC3DAPI_SetupHDMI3DMode(); //Setup 3D mode registers before reading 0x03C/0x03D
                #endif                
                    // Double check H/V present to avoid abnormal display
                    // under pure DE digital signal. TMDSBandwidthDetection
                    // must be prior to H/V present checking
                #if DVI_MODE == DVI_DE_MODE
                    if ((SC_GI_SYNC_STATUS & 0xC0) == 0x00) {
                #else
                    if ((SC_GI_SYNC_STATUS & 0xF8) == 0x18) {
                #endif
                        McuScalerIntEnable(); //MCU will response to scaler interrupt
						sync = DIG_SYNC;
                    }
                }
            }
            break;

        default:
            sync = NO_SYNC;
            break;
    }

    if ((GetInputHFreq() == 0xFFFF) || (GetInputVFreq() == 0xFFFF)) {
        sync = NO_SYNC;
    }

    // Remove the condition to solve the issue of no image display when switching timing from 56KHz to 47KHz.
    // Jude 2011/09/28
    //if (sync == NO_SYNC) {
        // Recover the HSync overflow mask setting to default.
        SetupHSyncOverflowMask(FALSE);
    //}

    return sync;
}

/**************************************************************************//**
 * Check the input sync is SOG or not.
 * @return TRUE if input is SOG else FALSE.
 ******************************************************************************/
static BOOL CheckSOG(void)
{
#define LIMIT_SOG_HS ((8UL * REF_CLK) /150000)    //640 H sync can't bigger than 150KHz
#define LIMIT_SOG_VS ((ULONG)REF_CLK*10/256/915)    //512  V sync can't bigger than 91.5Hz
#define LIMIT_SOG_HSWID_1 ((((ULONG)REF_CLK*4.98)/1000000)+0.5)    //60
#define LIMIT_SOG_HSWID_2 ((((ULONG)REF_CLK*4.15)/1000000)+0.5)    //50
#define LIMIT_SOG_HSWID_3 ((((ULONG)REF_CLK*2.49)/1000000)+0.5)    //30

    USHRT temp1, temp2;

    //VSync width
    temp1 = SC_GI_VS_WID;
    if ((temp1 > 0x0F) || (temp1==0x00)) {
        return FALSE;
    }
    //HSync width
    temp1 = SC_GI_HS_WID;
    temp2 = ReadShortScaler(&SC_GI_HCNT_LO);
    if (temp1 > ((temp2 / 8) / 6)) { //HSync width is over 1/6 of HTotal
        return FALSE;
    }
    //HSync frequency
    temp1 = ReadShortScaler(&SC_GI_HCNT_LO);
    if ((temp1 < LIMIT_SOG_HS) || (temp1 == 0x1FFF)) {
        return FALSE;
    }
    //VSync frequency
    temp1 = ReadShortScaler(&SC_GI_VCNT_LO);
    if ((temp1 < LIMIT_SOG_VS) || (temp1 == 0x1FFF)) {
        return FALSE;
    }
    //VTotal
    temp1 = SC_GI_HS_WID;
    temp2 = ReadShortScaler(&SC_GRAPHIC_VTOTAL_COUNTER_LO)+1;
    if (temp2 < 200) {
        return FALSE;
    }
    if (temp2 < 380) { //576I SOG
        if (temp1 > LIMIT_SOG_HSWID_1) {
            return FALSE;
        }
    }
    else if (temp2 < 730) {
        if (temp1 > LIMIT_SOG_HSWID_2) {
            return FALSE;
        }
    }
    else {
        if (temp1 > LIMIT_SOG_HSWID_3) {
            return FALSE;
        }
    }
    
    return TRUE;
    
#undef LIMIT_SOG_HS
#undef LIMIT_SOG_VS
#undef LIMIT_SOG_HSWID_1
#undef LIMIT_SOG_HSWID_2
#undef LIMIT_SOG_HSWID_3
}

/**************************************************************************//**
 * Setup interlace settings.
 * Set interlace input enable (Reg0x020[2]) by SyncProcessor flag.
 ******************************************************************************/
void SetupInterlace(void)
{
    SC_GI_SYNC_CTRL3 &= ~BIT0;

    //Set 0x020[2] and 0x020[6]
     if (IsInterlaceSyncPreset()) { //If input is interlaced
        SC_GPORT_CTRL |= BIT2;
    }
    else {
        SC_GPORT_CTRL &= ~BIT2;
    }
}

/**************************************************************************//**
 * Check Interlace Sync Preset
 * @return TRUE if input is interlaced sync else FALSE.
 ******************************************************************************/
BOOL IsInterlaceSyncPreset(void)
{
            if ((SC_GI_SYNC_STATUS & BIT2) != 0) { //If input is interlaced
                return TRUE;
            }
            else {
                return FALSE;
            }
        }

/**************************************************************************//**
 * Check the current timing is interlace or not.
 * @return TRUE if input is interlaced else FALSE.
 ******************************************************************************/
BOOL IsInterlaced(void)
{
    if ((SC_GPORT_CTRL & BIT2) != 0) { //If input is interlaced
        return TRUE;
    }
    else {
        return FALSE;
    }
}

/**************************************************************************//**
 * Enable/disable sync processor free run mode
 * @param enable TRUE to enable sync processor free run mode else FALSE.
 ******************************************************************************/
void EnableSyncProcFreeRun(UCHAR enable)
{
#define SYNC_PROC_H_FREERUN 67500
#define SYNC_PROC_V_FREERUN 60

    if (enable) {
        McuScalerIntDisable();
        ClearModeChangeFlag();
        WriteShortScaler(&SC_HREE_DIV_LO, REF_CLK / SYNC_PROC_H_FREERUN - 1);
        WriteShortScaler(&SC_VREE_DIV_LO, SYNC_PROC_H_FREERUN / SYNC_PROC_V_FREERUN - 1);
        WriteShortScaler(&SC_HSDDS_DIVIDER_LO, UserPanelData.usTypHTotal);
        SC_GI_SYNC_CTRL2 = 0xB2;
        SC_GI_SYNC_CTRL = 0x01;
        SC_PREPATTERN_CTRL1 |= BIT5;
    }
    else {
        SC_GI_SYNC_CTRL2 = 0xC0;
        switch(GetCurrInputInterface()) {
            case ANALOG_SEP_INPUT0:
            case ANALOG_SEP_INPUT1:
                SC_GI_SYNC_CTRL = 0x20;
                break;
            case ANALOG_COM_INPUT0:
            case ANALOG_SOG_INPUT0:
            case ANALOG_YPBPR_INPUT0:
            case ANALOG_COM_INPUT1:
            case ANALOG_SOG_INPUT1:
            case ANALOG_YPBPR_INPUT1:
                SC_GI_SYNC_CTRL = 0x21;
                break;
            case DIGITAL_INPUT0:
            case DIGITAL_INPUT1:
            #if DVI_MODE == DVI_DE_MODE
                SC_GI_SYNC_CTRL = 0x20;
            #else
                SC_GI_SYNC_CTRL = 0x90;
            #endif
                break;
#if (INPUT_INTERFACE&INPUT_DP)
            case DISPLAY_PORT_INPUT:
//            #if DVI_MODE == DVI_DE_MODE
                SC_GI_SYNC_CTRL = 0x20;
//            #else
//                SC_GI_SYNC_CTRL = 0x90;
//            #endif
                break;
#endif
        }
        
        SC_PREPATTERN_CTRL1 &= ~BIT5;
        SetModeChangeFlag();
    }
}

#if (INPUT_INTERFACE&INPUT_VGA0) || (INPUT_INTERFACE&INPUT_YPbPr0)
/**************************************************************************//**
 * Check the sync state of analog channel 0 under zero power mode.
 * @return TRUE if input signal is present else FALSE.
 ******************************************************************************/
BOOL ZpVGA0SyncDetect(void)
{
    SC_ADC_ZERO_POWER_CTRL = 0x89 | BIT1;    //enable CR R/W, SOG power
    SC_INPUT_SELECT = 0x80;
    //SC_ADC_ZERO_POWER_CTRL = 0x89;    //enable CR R/W, SOG power
    SC_SOG_SLICER_CTRL = SCREG_012_LP;    //SOG slicer en
    SC_ADC_REG_1D |= BIT6;
    SC_SOG_SLICER_EN = 0x08;

    CNT_CTRL = 0x7f;     //rst counter
    CNT_CTRL = 0x0f;    //start counter
    Sleep(20);
    CNT_CTRL = 0x00;    //stop counter

    SC_ADC_REG_1D &= ~BIT6;
    SC_SOG_SLICER_EN = 0x01;
    SC_SOG_SLICER_CTRL = SCREG_012_PD;    //SOG slicer dis
    SC_ADC_ZERO_POWER_CTRL = 0x83;    //disable CR R/W, SOG power

    if (((ucZpInterface==ANALOG_SEP_INPUT0) || (ucZpInterface==ANALOG_COM_INPUT0)) && ((HS_CNT_LB>10) || (HS_CNT_HB>0))) {
        CNT_CTRL = 0x8f;    //start counter
        Sleep(20);
        if ((ucZpInterface==ANALOG_SEP_INPUT0) && ((VS_CNT>0) && (VS_CNT<10))) { //Vsync detected
            ScalerPowerUp();
            SetInputInterface(ANALOG_SEP_INPUT0);
            return TRUE;
        }
        else if (ucZpInterface == ANALOG_COM_INPUT0) {//If we can not detect seperate sync
            //Composite sync detection
            SC_ADC_ZERO_POWER_CTRL = 0x89|BIT1; //Enable sync processor
            SchmittTriggerPowerOn();
            SC_ADC_CTRL = 0x10; //Select HSYNCI
            SC_GI_SYNC_CTRL = 0x61; //Composite Sync
            Sleep(50); //Waiting for sync processor flags
            if ((SC_GI_SYNC_STATUS & 0xE8) == 0x28) { //Composite present, H/V non-overflow
                // Check vtotal to avoid the bug of new h-polarity detection.
                if (GetInputVTotal() > 100) {
                    ScalerPowerUp();
                    SetInputInterface(ANALOG_COM_INPUT0);
                    return TRUE;
                }
            }
            SchmittTriggerPowerOff();
            SC_ADC_ZERO_POWER_CTRL = 0x83;    //disable CR R/W, SOG power
        }
    }

    if (((ucZpInterface == ANALOG_SOG_INPUT0) || (ucZpInterface == ANALOG_YPBPR_INPUT0)) && 
        ((SOG_CNT_LB>10) || (SOG_CNT_HB>0))) {
        SC_ADC_ZERO_POWER_CTRL = 0x89|BIT1; //Enable sync processor
        SC_SOG_SLICER_CTRL = SCREG_012_LP;
        SC_SOG_SLICER_EN |= BIT3;
        SC_ADC_CTRL = 0x18; //Select SOGI
        SC_GI_SYNC_CTRL = 0x61; //Composite Sync
        Sleep(50); //Waiting for sync processor flags
        if ((SC_GI_SYNC_STATUS & 0xE0) == 0x20) { //Composite present, H/V non-overflow
            // Check vtotal to avoid the bug of new h-polarity detection.
            if (CheckSOG() && (GetInputVTotal() > 100)) {
                // ScalerPowerUp must be put in the following condition.
                // Can not be moved prior to the condition.
                // Because of after ScalerPowerUp, the ucZpinterface will be changed to the original user setting value.
                // And it may make the system fail to wakeup from power saving mode.
                // P.S. This issue will happen when ENABLE_CUT_POWER_ARCH is used.
                if (ucZpInterface == ANALOG_YPBPR_INPUT0) {
                    ScalerPowerUp();
                    SetInputInterface(ANALOG_YPBPR_INPUT0);
                }
                else {
                    ScalerPowerUp();
                    SetInputInterface(ANALOG_SOG_INPUT0);
                }
                return TRUE;
            }
        }
        SC_SOG_SLICER_CTRL = SCREG_012_PD;
        SC_SOG_SLICER_EN &= ~BIT3;
        SC_ADC_ZERO_POWER_CTRL = 0x83;    //disable CR R/W, SOG power
    }

    return FALSE;
}
#endif

#if (INPUT_INTERFACE&INPUT_VGA1) || (INPUT_INTERFACE&INPUT_YPbPr1)
/**************************************************************************//**
 * Check the sync state of analog channel 1 under zero power mode.
 * @return TRUE if input signal is present else FALSE.
 ******************************************************************************/
BOOL ZpVGA1SyncDetect(void)
{
    SC_ADC_ZERO_POWER_CTRL = 0x89 | BIT1;    //enable CR R/W, SOG power
    SC_INPUT_SELECT = 0x81;
    //SC_ADC_ZERO_POWER_CTRL = 0x89;    //enable CR R/W, SOG power
    SC_SOG_SLICER_CTRL = SCREG_012_LP;    //SOG slicer en
    SC_ADC_REG_1D |= BIT6;
    SC_SOG_SLICER_EN = 0x08;

    CNT_CTRL = 0xff;     //rst counter
    CNT_CTRL = 0x8f;    //start counter
    Sleep(20);
    CNT_CTRL = 0x80;    //stop counter

    SC_ADC_REG_1D &= ~BIT6;
    SC_SOG_SLICER_EN = 0x01;
    SC_SOG_SLICER_CTRL = SCREG_012_PD;    //SOG slicer dis
    SC_ADC_ZERO_POWER_CTRL = 0x83;    //disable CR R/W, SOG power
    if (((ucZpInterface==ANALOG_SEP_INPUT1) || (ucZpInterface==ANALOG_COM_INPUT1)) && ((HS_CNT_LB>10) || (HS_CNT_HB>0))) {
        CNT_CTRL = 0x8f;    //start counter
        Sleep(20);
        if ((ucZpInterface==ANALOG_SEP_INPUT1) && ((VS_CNT>0) && (VS_CNT<10))) { //Vsync detected
            ScalerPowerUp();
            SetInputInterface(ANALOG_SEP_INPUT1);
            return TRUE;
        }
        else if (ucZpInterface == ANALOG_COM_INPUT1) {//If we can not detect seperate sync
            //Composite sync detection
            SC_ADC_ZERO_POWER_CTRL = 0x89|BIT1; //Enable sync processor
            SchmittTriggerPowerOn();
            SC_ADC_CTRL = 0x10; //Select HSYNCI
            SC_GI_SYNC_CTRL = 0x61; //Composite Sync
            Sleep(50); //Waiting for sync processor flags
            if ((SC_GI_SYNC_STATUS & 0xE8) == 0x28) { //Composite present, H/V non-overflow
                // Check vtotal to avoid the bug of new h-polarity detection.
                if (GetInputVTotal() > 100) {
                    ScalerPowerUp();
                    SetInputInterface(ANALOG_COM_INPUT1);
                    return TRUE;
                }
            }
            SchmittTriggerPowerOff();
            SC_ADC_ZERO_POWER_CTRL = 0x83;    //disable CR R/W, SOG power
        }
    }
    if (((ucZpInterface == ANALOG_SOG_INPUT1) || (ucZpInterface == ANALOG_YPBPR_INPUT1)) && 
        ((SOG_CNT_LB>10) || (SOG_CNT_HB>0))) {
        SC_ADC_ZERO_POWER_CTRL = 0x89|BIT1; //Enable sync processor
        SC_SOG_SLICER_CTRL = SCREG_012_LP;
        SC_SOG_SLICER_EN |= BIT3;
        SC_ADC_CTRL = 0x18; //Select SOGI
        SC_GI_SYNC_CTRL = 0x61; //Composite Sync
        Sleep(50); //Waiting for sync processor flags
        if ((SC_GI_SYNC_STATUS & 0xE0) == 0x20) { //Composite present, H/V non-overflow
            // Check vtotal to avoid the bug of new h-polarity detection.
            if (CheckSOG() && (GetInputVTotal() > 100)) {
                // ScalerPowerUp must be put in the following condition.
                // Can not be moved prior to the condition.
                // Because of after ScalerPowerUp, the ucZpinterface will be changed to the original user setting value.
                // And it may make the system fail to wakeup from power saving mode.
                // P.S. This issue will happen when ENABLE_CUT_POWER_ARCH is used.
                if (ucZpInterface == ANALOG_YPBPR_INPUT1) {
                    ScalerPowerUp();
                    SetInputInterface(ANALOG_YPBPR_INPUT1);
                }
                else {
                    ScalerPowerUp();
                    SetInputInterface(ANALOG_SOG_INPUT1);
                }
                return TRUE;
            }
        }
        SC_SOG_SLICER_CTRL = SCREG_012_PD;
        SC_SOG_SLICER_EN &= ~BIT3;
        SC_ADC_ZERO_POWER_CTRL = 0x83;    //disable CR R/W, SOG power
    }
    return FALSE;
}
#endif

#if (INPUT_INTERFACE&INPUT_DIG0)
/**************************************************************************//**
 * Check the sync state of digital channel 0 under zero power mode.
 * @return TRUE if input signal is present else FALSE.
 ******************************************************************************/
BOOL ZpDVI0SyncDetect(void)
{
    // For improving the issue of unabling to wake up from DPSM mode over some specific TMDS source
    // Jude 2011/11/07
#if 1
    SC_ADC_ZERO_POWER_CTRL = 0x83;
    SC_INPUT_SELECT = 0x82;
    HDCP_MUX = DIGITAL_INPUT0_HDCP_MUX;
    //SC_ADC_ZERO_POWER_CTRL = 0x81;
    SC_DVI_CTRL_333 = SCREG_333_LP0;
    SC_DVI_CTRL_334 = SCREG_334_PU;
    SC_DVI_CTRL_336 = SCREG_336_LP0;
    SC_DVI_CTRL_330 = DEFAULT_CLKIMP3;
    Sleep(2);
#if (INPUT_INTERFACE&INPUT_MHL0)
    if ( !MHL_IsCDSenseFlagOn() ) {
        MHL_SetCbusCH(MHL_CBUS_CH1);
    #if IS_NT68770_SERIES
        MHLCBus2Off();
        MHLCBus1On();
    #endif
    }
    else if ( MHL_IsCDSenseFlagOn() && MHL_GetCbusCH() == MHL_CBUS_CH1 ) {
        //#if IS_NT68850_SERIES
        //SC_CBUS_RESISTOR_CTRL = 0x33; // due to nt68850: MHL Cdsense effect HDMI Impedance, remove after cut2
        //#endif
        MHLCBus2Off();
        MHLCBus1On();
        if ( MHL_IsDiscoveryFlagOn() ) {
            SC_CBUS_INT_EN |= DIS_INT_CLR;
            MHLCBus1Off();
            SetInputInterface(DIGITAL_INPUT0);
            return TRUE;
        }
        else if (MHL_IsDisconnFlagOn() ) {
            SetCbusConnectStatus(MHL_NONE);
            ucIsMHLSrcConnected[0] = 0;
            SC_CBUS_INT_EN |= DIS_INT_CLR;
        }
    }
    //#if IS_NT68850_SERIES
    //SC_CBUS_RESISTOR_CTRL = 0x38; // due to nt68850: MHL Cdsense effect HDMI Impedance, remove after cut2
    //Sleep(2);
    //#endif
#endif

    if ((SC_DVI_STATUS & BIT0) != 0) {
        if (TMDS_GetClock() > DIG_VALID_PIXEL_RATE) {
           if (ZpHVpresentDetect() == TRUE){
                ScalerPowerUp();
                SetInputInterface(DIGITAL_INPUT0);
                return TRUE;
            }
        }
    }
    SC_ADC_ZERO_POWER_CTRL = 0x83;
#else
    UCHAR result;
    static UCHAR ucDVIZpCnt = 0;

    SC_ADC_ZERO_POWER_CTRL = 0x83;
    SC_INPUT_SELECT = 0x82;
    HDCP_MUX = DIGITAL_INPUT0_HDCP_MUX;
    SC_ADC_ZERO_POWER_CTRL = 0x01;
    result=0;
    SC_DVI_ZERO_POWER_CTRL = 0x12;    //detect current mode
    Sleep(2);
    if ((SC_DVI_ZERO_POWER_DETECT & 0x02) != 0) {
        SC_ADC_ZERO_POWER_CTRL = 0x81;       //Power up 
        SC_DVI_ZERO_POWER_CTRL = 0x32;
        Sleep(2);
        if ((SC_DVI_ZERO_POWER_DETECT & 0x08) != 0) {
            result=1;
        }
        SC_ADC_ZERO_POWER_CTRL = 0x01;
    }
/*  Disable voltage mode to solve some DVD issue. e.x. Pioneer DVD DV-610AV
    SC_DVI_ZERO_POWER_CTRL = 0x10;    //detect voltage mode
    Sleep(2);
    if ((SC_DVI_ZERO_POWER_DETECT & 0x01) != 0) {
        result=1;
    }
*/
    SC_DVI_ZERO_POWER_CTRL = 0x12; //detect current mode

    // Force  SCDT detection  every 15'th  loop to  sove the  issue of unable to
    // wakeup  from power  saving state  with some  specific graph  card and dvd
    // player.
    ucDVIZpCnt++;
    if (result || (ucDVIZpCnt>=15)) {
        ucDVIZpCnt = 0;
        SC_ADC_ZERO_POWER_CTRL = 0x81;       //Power up 
        SC_DVI_CTRL_333 = SCREG_333_LP0;
        SC_DVI_CTRL_334 = SCREG_334_PU;
        SC_DVI_CTRL_336 = SCREG_336_LP0;
        SC_DVI_ZERO_POWER_CTRL = 0x00;
        SC_DVI_CTRL_330 = DEFAULT_CLKIMP3;
        Sleep(2);
        if ((SC_DVI_STATUS & BIT0) != 0) {
            if (TMDS_GetClock() > DIG_VALID_PIXEL_RATE) {
                ScalerPowerUp();
                SetInputInterface(DIGITAL_INPUT0);
                return TRUE;
            }
        }
        SC_DVI_ZERO_POWER_CTRL = 0x12; //detect current mode
    }

    DVI_PowerOff();
    TurnOffScalerMainPower();
    SC_ADC_ZERO_POWER_CTRL = 0x01;
#endif
    return FALSE;
}
#endif

#if (INPUT_INTERFACE&INPUT_DIG1)
/**************************************************************************//**
 * Check the sync state of digital channel 1 under zero power mode.
 * @return TRUE if input signal is present else FALSE.
 ******************************************************************************/
BOOL ZpDVI1SyncDetect(void)
{
    // For improving the issue of unabling to wake up from DPSM mode over some specific TMDS source
    // Jude 2011/11/07
#if 1
    SC_ADC_ZERO_POWER_CTRL = 0x83;
    SC_INPUT_SELECT = 0x86;
    HDCP_MUX = DIGITAL_INPUT1_HDCP_MUX;
    //SC_ADC_ZERO_POWER_CTRL = 0x81;
    SC_DVI_CTRL_333 = SCREG_333_LP1;
    SC_DVI_CTRL_334 = SCREG_334_PU;
    SC_DVI_CTRL_336 = SCREG_336_LP1;
    SC_DVI_CTRL_330 = DEFAULT_CLKIMP3;
    Sleep(2);
#if (INPUT_INTERFACE&INPUT_MHL1)
    if ( !MHL_IsCDSenseFlagOn() ) {
        MHL_SetCbusCH(MHL_CBUS_CH2);
        MHLCBus1Off();
        MHLCBus2On();
    }
    else if ( MHL_IsCDSenseFlagOn() && MHL_GetCbusCH() == MHL_CBUS_CH2 ) {
        MHLCBus1Off();
        MHLCBus2On();
        if (MHL_IsDiscoveryFlagOn() ) {
            SC_CBUS_INT_EN |= DIS_INT_CLR;
            MHLCBus2Off();            
            SetInputInterface(DIGITAL_INPUT1);
            return TRUE;
        }
        else if (MHL_IsDisconnFlagOn() ) {
            SetCbusConnectStatus(MHL_NONE);
            ucIsMHLSrcConnected[1] = 0;
            SC_CBUS_INT_EN |= DIS_INT_CLR;
        }
    }
#endif

    if ((SC_DVI_STATUS & BIT0) != 0) {
        if (TMDS_GetClock() > DIG_VALID_PIXEL_RATE) {
           if (ZpHVpresentDetect() == TRUE){
                ScalerPowerUp();
                SetInputInterface(DIGITAL_INPUT1);
                return TRUE;
           }
        }
    }
    SC_ADC_ZERO_POWER_CTRL = 0x83;
#else
    UCHAR result;
    static UCHAR ucDVI1ZpCnt = 0;

    SC_ADC_ZERO_POWER_CTRL = 0x83;
    SC_INPUT_SELECT = 0x87;
    HDCP_MUX = DIGITAL_INPUT1_HDCP_MUX;
    SC_ADC_ZERO_POWER_CTRL = 0x01;
    result = 0;
    SC_DVI1_ZERO_POWER_CTRL = 0x12;    //detect current mode
    Sleep(2);
    if ((SC_DVI1_ZERO_POWER_DETECT & 0x02) != 0) {
        SC_ADC_ZERO_POWER_CTRL = 0x81;       //Power up 
        SC_DVI1_ZERO_POWER_CTRL = 0x32;
        Sleep(2);
        if ((SC_DVI1_ZERO_POWER_DETECT & 0x08) != 0) {
            result = 1;
        }
        SC_ADC_ZERO_POWER_CTRL = 0x01;
    }
/*  Disable voltage mode to solve some DVD issue. e.x. Pioneer DVD DV-610AV
    SC_DVI1_ZERO_POWER_CTRL = 0x10;    //detect voltage mode
    Sleep(2);
    if ((SC_DVI1_ZERO_POWER_DETECT & 0x01) != 0) {
        result = 1;            
    }
*/
    SC_DVI1_ZERO_POWER_CTRL = 0x12; //detect current mode

    // Force  SCDT detection  every 15'th  loop to  sove the  issue of unable to
    // wakeup  from power  saving state  with some  specific graph  card and dvd
    // player.
    ucDVI1ZpCnt++;
    if (result || (ucDVI1ZpCnt >= 15)) {
        ucDVI1ZpCnt = 0;
        SC_ADC_ZERO_POWER_CTRL = 0x81;       //Power up 
        SC_DVI_CTRL_333 = SCREG_333_LP1;
        SC_DVI_CTRL_334 = SCREG_334_PU;
        SC_DVI_CTRL_336 = SCREG_336_LP1;
        SC_DVI1_ZERO_POWER_CTRL = 0x00;
        SC_DVI_CTRL_330 = DEFAULT_CLKIMP3;
        Sleep(2);
        if ((SC_DVI_STATUS & BIT0) != 0) {
            if (TMDS_GetClock() > DIG_VALID_PIXEL_RATE) {
                ScalerPowerUp();
                SetInputInterface(DIGITAL_INPUT1);
                return TRUE;
            }
        }    
        SC_DVI1_ZERO_POWER_CTRL = 0x12; //detect current mode
    }

    DVI_PowerOff();
    TurnOffScalerMainPower();
    SC_ADC_ZERO_POWER_CTRL = 0x01;
#endif
    return FALSE;
}
#endif

#if (INPUT_INTERFACE&INPUT_DP)
/**************************************************************************//**
 * Check the sync state of display port under zero power mode.
 * @return TRUE if input signal is present else FALSE.
 ******************************************************************************/
BOOL ZpDPSyncDetect(void)
{
    SC_ADC_ZERO_POWER_CTRL = 0x83;
    if (IsDPAUXDetect() || GetDPLink() == TRUE) {
        ClrDPLink();
        ClearDPAUXDetect();
        ScalerPowerUp();
        SetInputInterface(DISPLAY_PORT_INPUT);
        return TRUE;
    }

    return FALSE;
}
#endif    
/**************************************************************************//**
 * Check the sync state under zero power mode.
 * @return TRUE if input signal is present else FALSE.
 ******************************************************************************/
static BOOL ZpSyncDetect(void)
{
    BOOL result=FALSE;

    switch (ucZpInterface&PORT_MASK) {
      #if (INPUT_INTERFACE&INPUT_VGA0) || (INPUT_INTERFACE&INPUT_YPbPr0)
        case ANALOG_SEP_INPUT0&PORT_MASK:
        case ANALOG_YPBPR_INPUT0&PORT_MASK:
            result = ZpVGA0SyncDetect();
            break;
      #endif

      #if (INPUT_INTERFACE&INPUT_VGA1) || (INPUT_INTERFACE&INPUT_YPbPr1)
        case ANALOG_SEP_INPUT1&PORT_MASK:
        case ANALOG_YPBPR_INPUT1&PORT_MASK:
            result = ZpVGA1SyncDetect();
            break;
      #endif

      #if (INPUT_INTERFACE&INPUT_DIG0)
        case DIGITAL_INPUT0&PORT_MASK:
            result = ZpDVI0SyncDetect();
            break;
      #endif

      #if (INPUT_INTERFACE&INPUT_DIG1)
        case DIGITAL_INPUT1&PORT_MASK:
            result = ZpDVI1SyncDetect();
            break;
      #endif

      #if (INPUT_INTERFACE&INPUT_DP)
        case DISPLAY_PORT_INPUT&PORT_MASK:
            result = ZpDPSyncDetect();
            break;
      #endif
    }

    return result;
}

/**************************************************************************//**
 * Delay time of 'n' frames.
 * @param n Number of frames. The max n is 10.
 ******************************************************************************/
void DelayVTime(UCHAR n) small
{
    USHRT temp, delay;

    // We limit n as smaller than 10.
    if (n > 10) {
        n = 10;
    }

    // If the input vsync freq is abnormal, we force the delay time as 20ms
    if ((usVSyncFreq < ((USHRT) VSYNC_LOWER_BOUND * 10)) ||
        (usVSyncFreq > ((USHRT) VSYNC_UPPER_BOUND * 10))) {
        delay = 20 * n;
    }
    else {
        delay = (ULONG) 10000 * n / usVSyncFreq + 1;
    }

    temp = GetTimerTick();
    while ((GetTimerTick() - temp) < delay) {
        ResetWDTimer();
    }
}

#if ((INPUT_INTERFACE&INPUT_DIG0) || (INPUT_INTERFACE&INPUT_DIG1))
/**************************************************************************//**
 * Check the H/V sync state under zero power mode.
 * @return TRUE if HV sync is present else FALSE.
 ******************************************************************************/
static BOOL ZpHVpresentDetect(void)
{    
    BOOL result=FALSE;
    UCHAR Reg0xB46 ,Reg0xB57, Reg0x102, Reg0x101, Reg0x333, Reg0x335, Reg0x336;
    UCHAR Reg0x302;
    
#if DVI_MODE == DVI_DE_MODE
    return TRUE;
#endif
    
#if ENABLE_CUT_POWER_ARCH == ON
    if ((SC_POWER_CTRL1&0x0F) != 0x0D) {
      SC_POWER_CTRL1 |= BIT7;
      SC_CUT_POWER_CTRL |= BIT2;
      SC_CUT_POWER_CTRL |= BIT0;
      SC_ISOLATION_CONTROL = SCREB_B61_PU;
      SC_CUT_POWER_CTRL &= 0x07;
      SC_CUT_POWER_CTRL &= ~BIT1;
      SC_POWER_CTRL1 &= ~BIT7;
    }
#endif
    //For nomal case
    Reg0xB57 = SC_ADC_ZERO_POWER_CTRL;
    Reg0xB46 = SC_MPLL_X2;
    Reg0x333 = SC_DVI_CTRL_333;
    Reg0x335 = SC_DVI_CTRL_335;            
    Reg0x336 = SC_DVI_CTRL_336; 
    Reg0x101 = SC_POWER_CTRL1;
    Reg0x102 = SC_POWER_CTRL2;    
    Reg0x302 = SC_DVI_RB_SWAP;
    SC_ADC_ZERO_POWER_CTRL = 0xE3; //Enable sync processor
    SC_DVI_CTRL_333 = SCREG_333_PU;
    SC_DVI_CTRL_336 = SCREG_336_PU;
    SET_SCREG_335_HF;
    SC_POWER_CTRL1 &= ~(BIT3|BIT5);
    SC_POWER_CTRL2 |= (BIT1|BIT5);
    
    //For HDCP+deep color
    SC_HDCP_INPUT_CTRL = 0x00;//Hdmi Input Clock Select (Select TMDS clock)
    SC_MPLL_X2 &= ~(BIT4|BIT3);
    LDO_ADJ |= BIT7;
        
    //For R/B swap
#if (INPUT_INTERFACE&INPUT_DIG0)
     if (ucZpInterface == DIGITAL_INPUT0) {
         SC_DVI_RB_SWAP = DIGITAL0_CHANNEL_SWAP << 1;
     }
#endif
#if (INPUT_INTERFACE&INPUT_DIG1)
     if (ucZpInterface == DIGITAL_INPUT1) {
         SC_DVI_RB_SWAP = DIGITAL1_CHANNEL_SWAP << 1;
     }
#endif
    
        
     Sleep(50); //Waiting for sync processor flags//120131_1010_SYS#1
    
     if ((SC_GI_SYNC_STATUS & 0xF8) == 0x18) {   //HV Preset
        result = TRUE;
     }
     else {        
        result = FALSE;
     }
    
     SC_DVI_CTRL_333 = Reg0x333;
     SC_DVI_CTRL_335 = Reg0x335;                
     SC_DVI_CTRL_336 = Reg0x336;
     SC_POWER_CTRL2 = Reg0x102;
     SC_POWER_CTRL1 = Reg0x101;
     SC_DVI_RB_SWAP = Reg0x302;
     if ((SC_POWER_CTRL1&0x0F) != 0x0D) { 
       LDO_ADJ &= ~BIT7;
     }
     SC_MPLL_X2 = Reg0xB46;
     SC_ADC_ZERO_POWER_CTRL = Reg0xB57;
    
#if ENABLE_CUT_POWER_ARCH == ON
#if IS_NT68850_SERIES || IS_NT68790_SERIES
    #if (INPUT_INTERFACE&INPUT_DP)
    DPConfigHWHPD(FALSE);
    #endif
    if ((SC_POWER_CTRL1&0x0F) != 0x0D) {
      SC_ISOLATION_CONTROL = SCREB_B61_PD|BIT4;
    }
#else
     SC_ISOLATION_CONTROL = SCREB_B61_PD;
#endif
     if ((SC_POWER_CTRL1&0x0F) != 0x0D) {
      SC_CUT_POWER_CTRL |= (SCREB_B62_PD & ~BIT1);//0xF8
      SC_CUT_POWER_CTRL |= BIT1;
      SC_CUT_POWER_CTRL &= ~BIT2;
      SC_CUT_POWER_CTRL &= ~BIT0;
     }
#endif
        return result;
}

#endif

