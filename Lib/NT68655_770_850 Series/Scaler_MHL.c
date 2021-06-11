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
#include "include.h"

#if (INPUT_INTERFACE&INPUT_MHL0) || (INPUT_INTERFACE&INPUT_MHL1)

//******************************************************************************
// M A C R O   D E F I N I T I O N S
//******************************************************************************

//******************************************************************************
// G L O B A L   V A R I A B L E S
//******************************************************************************

//******************************************************************************
// S T A T I C   V A R I A B L E S
//******************************************************************************
#if IS_NT68850_SERIES
static BOOL bVirtualCBus1 = 0; //Only for NT68850
#endif
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
void MHLCDSense1On(void)
{
#if IS_NT68770_SERIES && (INPUT_INTERFACE&INPUT_MHL0)
    UCHAR tmp_reg;

    tmp_reg = SC_MCU_IO_CTRL1 & ~(BIT7|BIT6);
    SC_MCU_IO_CTRL1 = tmp_reg | BIT6;

#if defined(MHL_CTS_DEBUG_TEST1)
    RDPA_REG |= BIT4;
#endif
#endif
}

void MHLCDSense2On(void)
{
#if IS_NT68770_SERIES && (INPUT_INTERFACE&INPUT_MHL1)
    UCHAR tmp_reg;

    tmp_reg = SC_MCU_IO_CTRL1 & ~(BIT5|BIT4);
    SC_MCU_IO_CTRL1 = tmp_reg | BIT4;

#if defined(MHL_CTS_DEBUG_TEST1)
    RDPA_REG |= BIT5;
#endif
#endif
}

#if IS_NT68770_SERIES
BOOL MHL_Is_CDSense1_IO_HIGH()
{
/*
#if ENABLE_VBUS_IO_CONTROL == ON || (IS_NT68770_SERIES && (INPUT_INTERFACE&INPUT_MHL0))
#if IS_NT68770_SERIES && (INPUT_INTERFACE&INPUT_MHL0)
    if ( ( PortA & BIT0 ) != 0 ) {
        return TRUE;
    }
    else {
        return FALSE;
    }
#else
    return FALSE;
#endif
#else
    return FALSE;
#endif
*/
}


BOOL MHL_Is_CDSense2_IO_HIGH()
{
/*
#if ENABLE_VBUS_IO_CONTROL == ON || (IS_NT68770_SERIES && (INPUT_INTERFACE&INPUT_MHL1))
#if IS_NT68770_SERIES && (INPUT_INTERFACE&INPUT_MHL1)
    if ( ( PortA & BIT1 ) != 0 ) {
        return TRUE;
    }
    else {
        return FALSE;
    }
#else
    return FALSE;
#endif
#else
    return FALSE;
#endif
*/
}
#endif

void MHLCBus1On(void)
{
#if IS_NT68770_SERIES && (INPUT_INTERFACE&INPUT_MHL0)
    UCHAR tmp_reg;

    tmp_reg = SC_MCU_IO_CTRL2 & ~(BIT7|BIT6);
    SC_MCU_IO_CTRL2 = tmp_reg | BIT6;
#elif IS_NT68850_SERIES && (INPUT_INTERFACE&INPUT_MHL0)
    bVirtualCBus1 = ON;
#endif
}

void MHLCBus1Off(void)
{
#if IS_NT68770_SERIES
    SC_MCU_IO_CTRL2 &= ~(BIT7|BIT6);
#elif IS_NT68850_SERIES
    bVirtualCBus1 = OFF;
#endif
    ucIsMHLSrcConnected[0] = 0;
}

void MHLCBus2On(void)
{
#if IS_NT68770_SERIES && (INPUT_INTERFACE&INPUT_MHL1)
    UCHAR tmp_reg;

    tmp_reg = SC_MCU_IO_CTRL2 & ~(BIT5|BIT4);
    SC_MCU_IO_CTRL2 = tmp_reg | BIT4;
#endif
}

void MHLCBus2Off(void)
{
#if IS_NT68770_SERIES
    SC_MCU_IO_CTRL2 &= ~(BIT5|BIT4);
#endif
    ucIsMHLSrcConnected[1] = 0;
}

BOOL MHLIsCBus1On(void)
{
#if IS_NT68770_SERIES
    return ((SC_MCU_IO_CTRL2 & (BIT7|BIT6))==BIT6);
#elif IS_NT68850_SERIES
    return bVirtualCBus1;
#else
    return FALSE;
#endif
}

BOOL MHLIsCBus2On(void)
{
#if IS_NT68770_SERIES
    return ((SC_MCU_IO_CTRL2 & (BIT5|BIT4))==BIT4);
#elif IS_NT68850_SERIES
    return FALSE;
#else
    return FALSE;
#endif
}

#if ENABLE_VBUS_IO_CONTROL == OFF
void MHL_EnableVBus1(void)
{
/*
#if IS_NT68770_SERIES && (INPUT_INTERFACE&INPUT_MHL0)
UCHAR tmp_reg;
    tmp_reg = SC_MCU_IO_CTRL4 & ~(BIT5|BIT4);
	    SC_MCU_IO_CTRL4 = tmp_reg | BIT4;
#elif IS_NT68850_SERIES && (INPUT_INTERFACE&INPUT_MHL0)
//UCHAR tmp_reg;  //FEFANJACKY REMOVE FOR PC5 DP_CABLE_DET
//    tmp_reg = SC_MCU_IO_CTRL5 & ~(BIT5|BIT4);  //FEFANJACKY REMOVE
//    SC_MCU_IO_CTRL5 = tmp_reg | BIT5;//FEFANJACKY REMOVE
#endif
*/
}
#endif

#if 0
void MHL_DisableVBus1(void)
{
/*
#if IS_NT68770_SERIES && (INPUT_INTERFACE&INPUT_MHL0)
    SC_MCU_IO_CTRL4 &= ~(BIT5|BIT4);
#elif IS_NT68850_SERIES && (INPUT_INTERFACE&INPUT_MHL0)
//    SC_MCU_IO_CTRL5 &= ~(BIT5|BIT4);             //FEFANJACKY REMOVE
#endif
*/
}
#endif

#if ENABLE_VBUS_IO_CONTROL == ON
void MHL_Set_VBus1_IO_On(void)
{
/*
#if IS_NT68770_SERIES && (INPUT_INTERFACE&INPUT_MHL0)
    #if SET_IO_VBUS_ACTIVE==HIGH
        PortC |= BIT2;
    #else
        PortC &= ~BIT2;
    #endif
#elif IS_NT68850_SERIES && (INPUT_INTERFACE&INPUT_MHL0)
    #if SET_IO_VBUS_ACTIVE==HIGH
        PortC |= BIT5;
    #else
        PortC &= ~BIT5;
    #endif
#endif
*/
}
void MHL_Set_VBus1_IO_Off(void)
{
/*
#if IS_NT68770_SERIES && (INPUT_INTERFACE&INPUT_MHL0)
    #if SET_IO_VBUS_ACTIVE==HIGH
        PortC &= ~BIT2;
    #else
        PortC |= BIT2;
    #endif
#elif IS_NT68850_SERIES && (INPUT_INTERFACE&INPUT_MHL0)
    #if SET_IO_VBUS_ACTIVE==HIGH
        PortC &= ~BIT5;
    #else
        PortC |= BIT5;
    #endif
#endif
*/
}
#endif

#if ENABLE_VBUS_IO_CONTROL == OFF
void MHL_EnableVBus2(void)
{
/*
#if IS_NT68770_SERIES && (INPUT_INTERFACE&INPUT_MHL1)
UCHAR tmp_reg;
    tmp_reg = SC_MCU_IO_CTRL4 & ~(BIT3|BIT2);
    SC_MCU_IO_CTRL4 = tmp_reg | BIT2;
#endif
*/
}
#endif

#if 0
void MHL_DisableVBus2(void)
{
/*
#if IS_NT68770_SERIES && (INPUT_INTERFACE&INPUT_MHL1)
    SC_MCU_IO_CTRL4 &= ~(BIT3|BIT2);
#endif
*/
}
#endif

#if ENABLE_VBUS_IO_CONTROL == ON
void MHL_Set_VBus2_IO_On(void)
{
/*
#if IS_NT68770_SERIES && (INPUT_INTERFACE&INPUT_MHL1)
    #if SET_IO_VBUS_ACTIVE==HIGH
        PortC |= BIT3;
    #else
        PortC &= ~BIT3;
    #endif
#endif
*/
}
void MHL_Set_VBus2_IO_Off(void)
{
/*
#if IS_NT68770_SERIES && (INPUT_INTERFACE&INPUT_MHL1)
    #if SET_IO_VBUS_ACTIVE==HIGH
        PortC &= ~BIT3;
    #else
        PortC |= BIT3;
    #endif
#endif
*/
}
#endif

BOOL MHLSetInterface(UCHAR interface)
{
    if ( (interface==DIGITAL_INPUT0 && IsMHL0CableConnect()) ||
        (interface==DIGITAL_INPUT1 && IsMHL1CableConnect()) ) {
        SC_MHL_CTRL_2E0 |= BIT7|BIT0;
        PowerDownAnalogInput();
        if ( MHL_IsPackedPixelMode() ) {
            SC_DISPLAY_CHANNEL &= ~BIT6; //get correct PHY clock 0x016 after set 0x159.6=0
        }
        return TRUE;
    }
    else {
        SC_MHL_CTRL_2E0 = 0x00;
        return FALSE;
    }
}

void MHLPackedPixelMode(BOOL On)
{
    if ( On ) {
        MHL_SetPackedPixelMode();
    }
    else {
        MHL_Set24bitMode();
    }
}

UCHAR MHLCbusTx(UCHAR type, UCHAR d) using 1
{
    MHL_WaitCBusReady();
    
    bTranCMD = 0;

#if ENABLE_INT_TRANSLATION == ON && ENABLE_HDMI_PRETEST == ON
{
    UCHAR countlag;
    for (countlag = 0;countlag<10;countlag++); //CTS 6.3.6.5, need delay to let 0x280 response abort command send by source, the count value should be larger than 3, its around 60 micro sec.
    
    if ((MHL_GetMSCCmd() || MHL_GetDDCCmd()) && (type == TX_MSC_CMD || type == TX_MSC_DATA)) {//130415_2230_SYS#2
        return FALSE;
    }
}
#endif    

    switch(type) {
    case TX_MSC_CMD:
        SC_CBUS_MSC_CMD = d;
        ucCmdIndex = 0;//index to cMSCCmd
        bCheckTimeout = 0;
        ucCBUSCMDTxBuffer = d;
        break;
    case TX_MSC_DATA:
        SC_CBUS_MSC_DATA = d;
        ucCBUSCMDTxBuffer = 0;
        break;
    case TX_DDC_CMD:
        SC_CBUS_DDC_CMD = d;
        ucCBUSCMDTxBuffer = d;
        break;
    case TX_DDC_DATA:
        SC_CBUS_DDC_DATA = d;
        ucCBUSCMDTxBuffer = 0;
        break;
    }

    return TRUE;
}

BOOL CBUSTxData(UCHAR type, UCHAR d)
{
    UCHAR i = 10;
    do {
    #if ENABLE_INT_TRANSLATION == 0
        Sleep(10);
    #endif
        MHL_WaitCBusReady();
        bTranCMD = 0;
    if (MHL_GetMSCCmd() || MHL_GetDDCCmd()) {
        return 0;
    }
        if (bCBUSAbort == 0) {//normal
            switch(type) {
            case TX_MSC_CMD:
                SC_CBUS_MSC_CMD = d;
                ucCmdIndex = 0;//index to cMSCCmd
                bCheckTimeout = 0;
            break;
            case TX_MSC_DATA:
                SC_CBUS_MSC_DATA = d;
                break;
            case TX_DDC_CMD:
                SC_CBUS_DDC_CMD = d;
                break;
            case TX_DDC_DATA:
                SC_CBUS_DDC_DATA = d;
                break;
            }
        }
    #if 1//def E_DEBUG
        Sleep(1);
        if (bCBusArbFailFlag == TRUE) {
            bCBusArbFailFlag = FALSE;
            i--;
        }
        else
    #endif
        {
            i = 0;
        }
    } while (i != 0);
    return !bCBUSAbort;
}

void MHL_SetCBus1DrvCurrent(void)
{
#if IS_NT68770_SERIES && (INPUT_INTERFACE&INPUT_MHL0)
    PA47_CURR |= 0x03;
#elif IS_NT68850_SERIES && (INPUT_INTERFACE&INPUT_MHL0) 
    PD46_CURR |= 0x0C;
#endif
}

void MHL_SetCBus2DrvCurrent(void)
{
#if IS_NT68770_SERIES && (INPUT_INTERFACE&INPUT_MHL1)
    PA47_CURR |= 0x0C;
#endif
}

void MHL_SetCBus1K(void)
{
 UCHAR ucSCID = GetSCID();
#if IS_NT68770_SERIES
    UCHAR i;
    if (ucSCID >= SCID_770_G && ucSCID <= SCID_770_FINAL) {
        i = SC_CBUS_CONTROL & 0x0F;
        SC_CBUS_CONTROL = i | 0x50;
    }
#elif IS_NT68850_SERIES
    UCHAR i;
    if (ucSCID >= SCID_850_C && ucSCID <= SCID_850_FINAL) {
        i = SC_CBUS_CONTROL & 0x0F;
        SC_CBUS_CONTROL = i | 0x50;
    }
#endif
}

void MHL_EnhanceCompatibility(void)
{
    UCHAR ucSCID = GetSCID();
#if IS_NT68770_SERIES
    // Ignore wake_up criteria
    if (ucSCID >= SCID_770_H && ucSCID <= SCID_770_FINAL) {
        SC_CBUS_DISCOVERY_TIME |= BIT7;
        SC_DISCOVERY2CONN |= BIT7;
    }
#elif IS_NT68850_SERIES
// Ignore wake_up criteria
    if (ucSCID >= SCID_850_C && ucSCID <= SCID_850_FINAL) {
        SC_SINK_WAKE &= ~(BIT5|BIT6);
        SC_SINK_WAKE |= BIT5;
        SC_REJECT_CBUS_DISCOVERY_PULSE_MIN = 0x2A;
        SC_REJECT_CBUS_DISCOVERY_PULSE_MAX = 0x70;
        SC_SINK_WAKE &= ~(BIT5|BIT6);
        SC_SINK_WAKE |= BIT6;
        SC_REJECT_CBUS_DISCOVERY_PULSE_MIN = 0x78;
        SC_REJECT_CBUS_DISCOVERY_PULSE_MAX = 0xFF;
        SC_SINK_WAKE &= ~(BIT5|BIT6);
        SC_WAKE_MODE = 0xd5;    
    }
#endif
}

void MHL_WaitCBusReady(void)
{
    USHRT uscount = 0;

    while ((SC_CBUS_TRANS_FLAG1 & 0x40) == 0) {//130319_1732_SYS#1
        ResetWDTimer();
        uscount ++;

        if (uscount == 0x8000) {//allion cts 4.3.20.1 CBT-sink Response to Ack with different timings (ucount = min 256 can pass,ucount = 255 fail)
            SC_CBUS_CONTROL |= BIT3;
            SC_CBUS_CONTROL &= ~BIT3;
            SetCbusConnectStatus(MHL_NONE);   
            break;
        }
    }

}

#endif //ENABLE_DBC == ON
