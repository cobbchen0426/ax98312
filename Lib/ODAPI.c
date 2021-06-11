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

#if ENABLE_OD == ON

//******************************************************************************
// M A C R O   D E F I N I T I O N S
//******************************************************************************
#define MOTION_THRESHOLD_OD_OFF 0x40L
#define MOTION_THRESHOLD_OD_ON  0x1FFFFF

//******************************************************************************
// G L O B A L   V A R I A B L E S
//******************************************************************************

//******************************************************************************
// S T A T I C   V A R I A B L E S
//******************************************************************************

//******************************************************************************
// E X T E R N A L   V A R I A B L E   P R O T O T Y P E S
//******************************************************************************

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
 * Turn off OD function.
 ******************************************************************************/
void ODAPI_DisableOD(void)
{
    SC_OD_DDC_CONFIGURATION = 0x00;
#if !IS_NT68360_SERIES
    // We always keept 0x580[0] as on on NT68360 because some garbage on screen when on/off this bit. 
    // Jude 2011/08/29
    SC_OD_CONFIGURATION &= ~BIT0;
#endif
}

/**************************************************************************//**
 * Turn on OD function.
 ******************************************************************************/
void ODAPI_EnableOD(void)
{
    SC_OD_CONFIGURATION |= BIT0;
    Sleep(50);
    SC_OD_DDC_CONFIGURATION = 0x01;
}

/**************************************************************************//**
 * Initialize OD-related registers and load OD table.
 * @param ptr Pointer to OD table.
 ******************************************************************************/
void ODAPI_LoadOD(UCHAR *ptr)
{
    ResetWDTimer();
    SC_BYPASS_CTRL &= ~BIT1;    // Turn on OD power

    ODAPI_DisableOD();
    Sleep(50); // 24Hz is around 41ms
    SC_OD_DDC_CONFIGURATION = 0x04;
    //Sleep(100); // Remove the redundant delay.
#if ENABLE_OD_TRANSFORM == ON
    WriteODTransformData(OD_TBL|BIT2, ptr, FALSE);
#else
    WriteScalerIndexPort(OD_TBL|BIT2, 0, 1024, ptr);
#endif
#if ENABLE_OD_3D_MODE == ON
    SC_OD_DDC_CONFIGURATION |= BIT1;
#if ENABLE_OD_TRANSFORM == ON
    WriteODTransformData(OD_TBL|BIT2, ptr+272, TRUE);//272 = 16x17
#else
    WriteScalerIndexPort2(OD_TBL|BIT2, 0, 1024, ptr+1024);
#endif
    SC_OD_DDC_CONFIGURATION &= ~BIT1;
    WriteShortScaler(&SC_OD_MULTI_ZONE_LOW_BOUNDARY_LO, UserPanelData.usHeight / 4);
    WriteShortScaler(&SC_OD_MULTI_ZONE_HIGH_BOUNDARY_LO, UserPanelData.usHeight * 3 / 4);
    SC_OD_BTC_CONFIGURATION2 |= BIT3;
#endif
    SC_OD_BTC_CONFIGURATION = 0x70;
#if ENABLE_OD_MOTION_CHK == ON
    SC_OD_MOTION_CHECK_BOUNCE_MONITOR = 0x0E;
    SC_OD_MOTION_CHECK_THRESHOLD = 0x01;
    SC_OD_MOTION_CHECK_DEBOUNCE = 0x01;
#endif
    SC_OD_STILL_CONFIGURATION = 0x03;
    SC_OD_STILL_THRESHOLD = 0x0B; // Threshold of gray2gray
 #if ENABLE_OD_MOTION_CHK == ON   
    ODAPI_SetMCOnOff(ON);
 #else
    ODAPI_SetMCOnOff(OFF);
 #endif
    ODAPI_SetMCThreshold(MOTION_THRESHOLD_OD_OFF, MOTION_THRESHOLD_OD_ON);

    // We use the following two registers to indicate the OD has been reset or not.
    // 0xFF means the OD has been initialized.
    // Others mean the OD is reset.
    SC_OD_TEST_TP_H_MT_STEP |= 0x0F;
    SC_OD_TEST_TP_V_MT_STEP |= 0x0F;

    ResetWDTimer();
}

/**************************************************************************//**
 * Check OD is reset or not.
 * @return TRUE if OD is reset else FALSE.
 ******************************************************************************/
BOOL ODAPI_IsODReset(void)
{
    if (((SC_OD_TEST_TP_H_MT_STEP & 0x0F) == 0x0F) &&
        ((SC_OD_TEST_TP_V_MT_STEP & 0x0F) == 0x0F)) {
        return FALSE;
    }
    return TRUE;
}

/**************************************************************************//**
 * Turn on/off motion check of OD function.
 * @param on_off ON to turn on motion check, otherwise OFF.
 ******************************************************************************/
void ODAPI_SetMCOnOff(UCHAR on_off)
{
    if (on_off == ON) {
    #if IS_NT68750_SERIES || IS_NT68360_SERIES
        SC_OD_MOTION_CHECK_CFGCONFIGURATION = 0x12;
    #else
        SC_OD_MOTION_CHECK_CFGCONFIGURATION = 0x10;
    #endif
    }
    else {
        SC_OD_MOTION_CHECK_CFGCONFIGURATION = 0x00;
    }
}

/**************************************************************************//**
 * Set threshold of motion detection.
 * @param low Low threshold for motion detection.
 * @param high High threshold for motion detection.
 ******************************************************************************/
void ODAPI_SetMCThreshold(ULONG low, ULONG high)
{
    SC_OD_MOTION_LOW_THRESHOLD_LO = low;
    SC_OD_MOTION_LOW_THRESHOLD_MI = low >> 8;
    SC_OD_MOTION_LOW_THRESHOLD_HI = low >> 16;
    SC_OD_MOTION_HIGH_THRESHOLD_LO = high;
    SC_OD_MOTION_HIGH_THRESHOLD_MI = high >> 8;
    SC_OD_MOTION_HIGH_THRESHOLD_HI = high >> 16;
}

/**************************************************************************//**
 * Dynamically turn on/off motion detection.
 * Main flow will call this function periodically.
 ******************************************************************************/
#if ENABLE_OD_MOTION_CHK == ON
void ODAPI_MotionCheck(void)
{
    static UCHAR ucODVcnt = 0;

    // Confirm the scaler has display VSync out or not!
    if ((SC_OD_CONFIGURATION & BIT0) == 0) {
        return;
    }
    if ((SC_POWER_CTRL1 & BIT0) != 0) {
        return;
    }
    if ((SC_DPLL_CTRL1 & BIT0) == 0) {
        return;
    }
    if ((SC_DISPLAY_CTRL & BIT0) == 0) 		//150112 mike 
	{
        	return;                                              
        }

    if (++ucODVcnt > 50) {//4.6ms per loop
        ucODVcnt = 0;
        if (SC_OD_MOTION_CHECK_STATUS != 0) {
            SC_OD_MOTION_LOW_THRESHOLD_LO = MOTION_THRESHOLD_OD_OFF;
        }
        else {
            SC_OD_MOTION_LOW_THRESHOLD_LO = 0x00;
        }
    }
}

#endif
#endif
