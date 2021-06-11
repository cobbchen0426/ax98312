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

#if (INPUT_INTERFACE&INPUT_MHL0) || (INPUT_INTERFACE&INPUT_MHL1)

//******************************************************************************
// G L O B A L   D E F I N I T I O N S
//******************************************************************************

// Write Burst State
enum {
 WB_NONE,
 WB_WAIT2GO,
 WB_REQ,
 WB_GRT,
 WB_WRITING,
 WB_DEVCHG,
};

//******************************************************************************
// G L O B A L   V A R I A B L E S
//******************************************************************************
idata UCHAR ucMHLConnState = MHL_NONE;
idata UCHAR ucCBusState = CBUS_UNACTIVE;
idata UCHAR ucCmdIndex;
idata UCHAR ucCBUSErrorCode;
idata UCHAR ucDataLen;
idata USHRT usCBUSTimeoutIdle;
idata USHRT usCBUSTimeoutACK;
idata USHRT usCBUSTimeoutAbort;
idata USHRT usCBUSTimeoutDAT;
idata USHRT usTimerCDSense2VBus;
idata UCHAR ucCBUSDDCStatus;
xdata UCHAR ucCbusBuffer[CBUS_BUF_LEN];
xdata UCHAR ucEDIDIndex = 0;
xdata UCHAR ucHdcpIndex = 0;
xdata UCHAR ucIsMHLSrcConnected[MHL_CBUS_NUM];
xdata UCHAR ucWrBurstState;
xdata UCHAR ucWrBurstCount;
static BOOL bStartOfFrame = 0;
static BOOL bHdcpFlag = FALSE;
static BOOL bDDCWriteFlag = FALSE;	// TRUE: Received "Write" command
static BOOL bReadDevCapFlag = FALSE;	// David.
static BOOL bPackPixelModeIntFlag = FALSE;
static BOOL bClearHPD = 0;
static BOOL bCheckDDCTimeout = 0;
static BOOL bEnEOF = 0;
static BOOL bTranslationReady = 0;
BOOL bCheckTimeout;
BOOL bCBUSAbort;
BOOL bTranCMD;
BOOL bSetVBus;
BOOL bWaitACK;
idata UCHAR ucCBUSCMDTxBuffer = 0;
#if 1//def E_DEBUG
BOOL bCBusArbFailFlag = 0;
#endif
extern idata USHRT usTimerTickMHL;

//UCHAR volatile xdata EDID_SRAM_BUFF3[256] _at_ 0xFB00;
#if MHL_DDC_CHANNEL == 0x00
//    xdata UCHAR volatile EDID_SRAM_MHL[256] _at_ 0xF800;
    #define EDID_SRAM_MHL EDID_SRAM_BUFF0
#elif MHL_DDC_CHANNEL == 0x01
//    xdata UCHAR volatile EDID_SRAM_MHL[256] _at_ 0xF900;
    #define EDID_SRAM_MHL EDID_SRAM_BUFF1
#elif MHL_DDC_CHANNEL == 0x02
//    xdata UCHAR volatile EDID_SRAM_MHL[256] _at_ 0xFA00;
    #define EDID_SRAM_MHL EDID_SRAM_BUFF2
#elif MHL_DDC_CHANNEL == 0x03
//    xdata UCHAR volatile EDID_SRAM_MHL[256] _at_ 0xFB00;
    #define EDID_SRAM_MHL EDID_SRAM_BUFF3
#endif
UCHAR volatile xdata *pMHLDDCPtr;
    
#if defined(MHL_CTS_DEBUG_TEST1)
BOOL bCbusLowFlag = FALSE;
idata USHRT usTimerCheckCBUSLow = 0;
#endif

//******************************************************************************
// S T A T I C   V A R I A B L E S
//******************************************************************************
#if ENABLE_DEMO_MHL_EDID == ON
static code UCHAR MHL_EDID_Tbl[]={
	//0    1    2    3    4    5    6    7    8    9    a    b    c    d    e    f
0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x4D, 0x29, 0x87, 0x96, 0x01, 0x00, 0x00, 0x00,
0x20, 0x15, 0x01, 0x03, 0x80, 0x52, 0x2E, 0x78, 0x0A, 0x0D, 0xC9, 0xA0, 0x57, 0x47, 0x98, 0x27,
0x12, 0x48, 0x4C, 0x21, 0x09, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
0x01,0x01,0x01,0x01,0x01,0x01,0x02,0x3A,0x80,0x18,0x71,0x38,0x2D,0x40,0x58,0x2C,
0x45, 0x00, 0xC4, 0x8E, 0x21, 0x00, 0x00, 0x1E, 0x01, 0x1D, 0x00, 0x72, 0x51, 0xD0, 0x1E, 0x20,
0x6E, 0x28, 0x55, 0x00, 0xC4, 0x8E, 0x21, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0xFC, 0x00, 0x43,
0x50, 0x39, 0x36, 0x38, 0x37, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0xFD,
0x00, 0x17, 0x78, 0x0F, 0x85, 0x1E, 0x00, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x01, 0x15,
0x02, 0x03, 0x34, 0x72, 0x55, 0x90, 0x84, 0x03, 0x02, 0x0E, 0x0F, 0x07, 0x23, 0x24, 0x05, 0x94,
0x13, 0x12, 0x11, 0x1D, 0x1E, 0x20, 0x21, 0x22, 0x01, 0x1F, 0x26, 0x09, 0x7F, 0x07, 0x15, 0x07,
0x50, 0x83, 0x01, 0x00, 0x00, 0x6E, 0x03, 0x0C, 0x00, 0x40, 0x00, 0xF8, 0x3C, 0x21, 0x84, 0x80,
0x01, 0x02, 0x03, 0x04, 0x8C, 0x0A, 0xD0, 0x90, 0x20, 0x40, 0x31, 0x20, 0x0C, 0x40, 0x55, 0x00,
0xC4, 0x8E, 0x21, 0x00, 0x00, 0x18, 0x01, 0x1D, 0x80, 0x18, 0x71, 0x1C, 0x16, 0x20, 0x58, 0x2C,
0x25, 0x00, 0xC4, 0x8E, 0x21, 0x00, 0x00, 0x9E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24,
};
#endif

//******************************************************************************
// E X T E R N A L   V A R I A B L E   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// S T A T I C   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
static BOOL WriteBurst3DInfo(void);

//******************************************************************************
// E X T E R N A L   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************


//******************************************************************************
// Prototype: 
//  void MHLInit()
// Parameters:
//
// Return:
//  None
// Purpose:
//
// Notes:
//  None
//******************************************************************************
void MHLInit(void)
{
    USHRT i;
#if ENABLE_DEMO_MHL_EDID == ON	   //150425 George (use #if for compiler code no-warning. )
    bit diff;
#endif
    SC_MHL_CDSENSE_CTRL |= BIT1; //turn off CDSense

    // Init EDID data
#if ENABLE_DEMO_MHL_EDID == ON
    diff = FALSE;
    for (i=0; i<256; i++) {
        if ((EDID_SRAM_MHL[i] != MHL_EDID_Tbl[i]) && (i < 8)) {//check head
            diff = TRUE;
        EDID_SRAM_MHL[i] = MHL_EDID_Tbl[i];
    }
        else if ((i > 7) && (diff == TRUE)) {//copy
            EDID_SRAM_MHL[i] = MHL_EDID_Tbl[i];
        }
    }
#endif

    for(i=0; i<40; i++) {
        ucCbusBuffer[i]=0x00;
    }

    ucMHLConnState = MHL_NONE;
    ucCBusState = CBUS_UNACTIVE;
    ucCBUSErrorCode = CBUS_NORMAL;
    ucIsMHLSrcConnected[MHL_CBUS_CH1] = ucIsMHLSrcConnected[MHL_CBUS_CH2] = FALSE;
    IntMHLStatus();
    RCP_TEST = 0xFF;

    SC_18V_LDO_CONTROL = 0x41;
//    SC_CBUS_DEBUG_CTRL = 0x01;    // Set MHL_LANE_ON to manual mode.
#if 1//def E_DEBUG
	// for cut 4 ECO version (David, @ 2012/08/28)
    SC_CBUS_DEBUG_CTRL = BIT4|BIT5|BIT6;
#endif
    SC_SINK_WAKE = 0x0F;    // Fix HTC EVO discovery fail bug. (change 0x0C to 0x0F)
    MHL_SetCBus1DrvCurrent();
    MHL_SetCBus2DrvCurrent();
    SC_CBUS_RESISTOR_CTRL = 0x33;
    SC_ACK_BIT_INIT_FALLING_EDGE = 0x00; // 4.3.10.1
    SC_ARBIT_WAIT_TIME1 = 0xC2; // 4.3.11.1
    SC_RXSENSE_EN_TIME = 0x01; //follow LG
    SC_LINK_CONTROL = 0x00;
    SC_CBUS_DISCOVERY_TIME = 0x01;//for 4.3.23.2 & 4.3.6.2
    SC_CBUS_DRV = 0x44;
    MHL_EnhanceCompatibility();
    MHL_SetCBus1K();
    #if SET_IO_VBUS_ACTIVE == HIGH
    SC_VBUS_ENABLE_TIME &= ~BIT7;
    #else
    SC_VBUS_ENABLE_TIME |= BIT7;
    #endif

    SC_CBUS_DIS_INT_MASK = ~(BIT1|BIT5);//Enable CD_sense change, connected INT, Stuck low
#if 1//def E_DEBUG
	SC_CBUS_INT_EN = 0xF0|BIT0;						// Enable DIS, TRANS, LINK
	SC_CBUS_LINK_INT_MASK = ~CBUS_ARB_FAIL;//~(INVALID_BIT_TIME|CBUS_ARB_FAIL);
#else
    SC_CBUS_INT_EN = 0xF0|CBUS_INT_MASK;
#endif	

    INTSC_EN |= BIT6;	// enable MHL interrupt group
    SC_MHL_CDSENSE_CTRL &= ~BIT1; //turn on CDSense

    MHLCDSense1On();
    MHLCDSense2On();
    bSetVBus = 0;
    usTimerCDSense2VBus = GetTimerTick();

    SetCbusChannel();
#if (INPUT_INTERFACE&INPUT_MHL0)
    if (MHL_GetCbusCH() == MHL_CBUS_CH1 ) {
        Digi0HPDOn();
    }
#endif
#if (INPUT_INTERFACE&INPUT_MHL1)
    if (MHL_GetCbusCH() == MHL_CBUS_CH2 ) {
        Digi1HPDOn();
    }
#endif

//initial device capability
    SC_CBUS_DEV_STATE = 0x00;
    SC_CBUS_MHL_VER = CDF_MHL_VER;
    SC_CBUS_DEV_CAT = CDF_DEV_CAT;
    SC_CBUS_ADOPTER_ID_H = CDF_ADOPTER_ID_H;
    SC_CBUS_ADOPTER_ID_L = CDF_ADOPTER_ID_L;
    SC_CBUS_VID_LINK_MODE = CDF_VID_LINK_MODE;
    SC_CBUS_AUD_LINK_MODE = CDF_AUD_LINK_MODE;
    SC_CBUS_VIDEO_TYPE = CDF_VIDEO_TYPE;
    SC_CBUS_LOG_DEV_MAP = CDF_LOG_DEV_MAP;
    SC_CBUS_BANDWIDTH = CDF_BANDWIDTH;
    SC_CBUS_FEATURE_FLAG = CDF_FEATURE_FLAG;
    SC_CBUS_DEVICE_ID_H = CDF_DEVICE_ID_H;
    SC_CBUS_DEVICE_ID_L = CDF_DEVICE_ID_L;
    SC_CBUS_SCRATCHPAD_SIZE = CDF_SCRATCHPAD_SIZE;
    SC_CBUS_INT_STAT_SIZE = CDF_INT_STAT_SIZE;
}

//******************************************************************************
// Prototype: 
//  void SetCbusChannel(void)
// Parameters:
//
// Return:
//  None
// Purpose:
//
// Notes:
//  None
//******************************************************************************
void SetCbusChannel(void)
{
    if( MHL_IsCDSenseFlagOn()) {
        if ( (SC_DVI_CTRL_333&(BIT0|BIT1|BIT2)) != (BIT0|BIT1|BIT2) ) {
        DVI_PowerOn();
        }
        if (MHL_GetCbusCH() == MHL_CBUS_CH1) {
            MHLCBus1On();
        }
        else {
            MHLCBus2On();
        }
    }
    else {
        // If can't detected CD sense in present C bus,then change to another C bus channel.
        if (MHL_GetCbusCH() == MHL_CBUS_CH1) {
            MHLCBus1Off();
#if (INPUT_INTERFACE&INPUT_MHL1)           
            MHL_SetCbusCH(MHL_CBUS_CH2);
#endif
        }
        else {
            MHLCBus2Off();
#if (INPUT_INTERFACE&INPUT_MHL0)
            MHL_SetCbusCH(MHL_CBUS_CH1);
#endif
        }
        SetCbusConnectStatus(MHL_NONE);
    }

#if ENABLE_VBUS_IO_CONTROL==OFF
    if ( !bSetVBus ) {
        if ( (GetTimerTick()-usTimerCDSense2VBus) > 100 ) {
            // From sink VBUS output (set by 0x2A1)
            // For avoid temporary pulse, so postpone to turn on VBus control
            // remember to set PC2,PC3 to correct initial state
            MHL_EnableVBus1();
            MHL_EnableVBus2();
            bSetVBus = 1;
        }
    }
#endif
}

//******************************************************************************
// Prototype: 
//  void CbusDiscoveryHandler()
// Parameters:
//
// Return:
//  None
// Purpose:
//
// Notes:
//  None
//******************************************************************************
void CbusDiscoveryHandler(void)
{
    if( MHL_IsDiscoveryFlagOn() ) {
    #if ENABLE_INT_DISCOVERY == ON
        SC_CBUS_INT_EN |= DIS_INT_CLR;
    #endif
        if (ucMHLConnState == MHL_NONE) {
            //IP = 0x01;
     #if ENABLE_INT_DISCOVERY == ON
        usTimerTickMHL = GetTimerTickInt();
     #else
        usTimerTickMHL = GetTimerTick();
     #endif
        ucMHLConnState = MHL_DISCOVERY_RDY;
        ucCBusState = CBUS_DISCOVERY_DONE;
        ucIsMHLSrcConnected[MHL_GetCbusCH()] = TRUE;
            IntMHLStatus();
        }
    }
    else if (MHL_IsDisconnFlagOn()) {
    #if ENABLE_INT_DISCOVERY == ON
        SC_CBUS_INT_EN |= DIS_INT_CLR;
    #endif
        SC_CBUS_RESISTOR_CTRL = 0x38;//Toggle RxSense
        SC_CBUS_RESISTOR_CTRL = 0x33;
        ucMHLConnState = MHL_NONE;
        ucCBusState = CBUS_UNACTIVE;
        ucIsMHLSrcConnected[MHL_GetCbusCH()] = FALSE;
        //IP = 0x00;
        IntMHLStatus();
    }
}

void IntMHLStatus(void)
{
    ucCmdIndex = 0;
    bEnEOF = 0;
    bCheckTimeout = 0;
    bCBUSAbort = 0;
    ucDataLen = 0;
    bTranCMD = 1;
    bStartOfFrame = 0;
    bDDCWriteFlag = FALSE;
    ucCBUSDDCStatus = CBUS_DDC_EOF;
    ucCBUSErrorCode = CBUS_NORMAL;
    bClearHPD = 0;
    bWaitACK = 0;
    ucWrBurstState = 0;
    ucWrBurstCount = 0;
    MHL_Set24bitMode();
}

//******************************************************************************
// Prototype: 
//  void CbusHandler()
// Parameters:
//
// Return:
//  None
// Purpose:
//
// Notes:
//  None
//******************************************************************************
void CbusHandler(void)
{
    if ( !IsZpMode() ) {
        SetCbusChannel();
    }

#if ENABLE_INT_DISCOVERY == OFF
    CbusDiscoveryHandler();
    SC_CBUS_INT_EN |= DIS_INT_CLR;
#endif

#if ENABLE_VBUS_IO_CONTROL == ON
    if ( MHL_Is_CDSense1_IO_HIGH() ) {
        MHL_Set_VBus1_IO_On();
    }
    else {
        MHL_Set_VBus1_IO_Off();
    }
    if ( MHL_Is_CDSense2_IO_HIGH() ) {
        MHL_Set_VBus2_IO_On();
    }
    else {
        MHL_Set_VBus2_IO_Off();
    }
#endif
}

//******************************************************************************
// Prototype: 
//  void CbusMSCCmdHandler(void)
// Parameters:
//
// Return:
//  None
// Purpose:
//
// Notes:
//  None
//******************************************************************************
void CbusMSCCmdHandler(void) using 1
{
    idata UCHAR tmp;
    idata UCHAR i;

    do {
        usTimerTickMHL = GetTimerTickInt();//reset MHL timer
        if (ucMHLConnState == MHL_NONE) {
            ucMHLConnState = MHL_DISCOVERY_RDY;
            ucCBusState = CBUS_DISCOVERY_DONE;
            ucIsMHLSrcConnected[MHL_GetCbusCH()] = TRUE;
        }
        //if ((bCBUSAbort == 1) && ((GetTimerTickInt() - usCBUSTimeoutAbort) < CBUS_AA_TIMEOUT)) {
            //break;
        //}
        tmp = SC_CBUS_TRANS_FLAG0 & (MSC_CMD_READ_VALID|MSC_DATA_READ_VALID);
        switch ( tmp )   {
        case MSC_CMD_READ_VALID:
            cMSCCmd = SC_CBUS_RX_DATA;
            //if ((bWaitACK == 1) && ((cMSCCmd != CBUS_ACK) && (cMSCCmd != CBUS_GET_STATE) && (cMSCCmd != CBUS_ABORT))) {
//            if ((bWaitACK == 1) && ((cMSCCmd != CBUS_ACK) && (cMSCCmd != CBUS_GET_STATE))) {
                //break;
            //}

            switch ( cMSCCmd ) {
            case CBUS_ACK:
                bWaitACK = 0;
                bTranslationReady = 1;

                if (bTranCMD == 1) {
        //TEST CASE : 6.3.11.4 CBM: DUT Receives (0x33) ACK Packet While No Command Outstanding
                    MHLCbusTx(TX_MSC_CMD,CBUS_ABORT);
                    ucCBUSErrorCode = ERROR_INVALID_OP_CODE;
                }
                bTranCMD = 1;
                
#if ENABLE_INT_TRANSLATION == ON
                if ( bReadDevCapFlag == FALSE ) {
                    bTranslationReady = 0;
                    MSCCmdTranslation();
                }
#endif                
                ucCmdIndex = 0;//index to cMSCCmd
                break;
            case CBUS_ABORT:
                //TEST CASE : 6.3.11.7 CBM: DUT Receives (0x35) ABORT While No Command Outstanding
                ucCBUSErrorCode = ERROR_INVALID_OP_CODE;
                ucCmdIndex = 0;//index to cMSCCmd
                break;
            case CBUS_NACK:
                //TEST CASE : 6.3.11.5 CBM: DUT Receives (0x34) a NACK Packet While No Command Outstanding
                MHLCbusTx(TX_MSC_CMD, CBUS_ABORT);
                ucCBUSErrorCode = ERROR_INVALID_OP_CODE;
                ucCmdIndex = 0;//index to cMSCCmd
                break;
            case CBUS_WRITE_STAT:
                usCBUSTimeoutDAT = GetTimerTickInt();
                bCheckTimeout = 1;
                ucDataLen = 2;//offset + value1
                ucCmdIndex = 1;//index to cMSCOffset
                break;
            case CBUS_READ_DEVCAP:
                usCBUSTimeoutDAT = GetTimerTickInt();
                bCheckTimeout = 1;
                ucCmdIndex = 1;//index to cMSCOffset
                break;
            case CBUS_MSC_MSG:
                usCBUSTimeoutDAT = GetTimerTickInt();
                bCheckTimeout = 1;
                ucDataLen = 2;//value1 + value2
                ucCmdIndex = 1;//index to cMSCOffset
                break;
            case CBUS_WRITE_BURST:
                usCBUSTimeoutDAT = GetTimerTickInt();
                bCheckTimeout = 1;
                bEnEOF = 1;
                ucDataLen = 16;//ID_H + ID_L + data#n
                ucCmdIndex = 1;//index to cMSCOffset
                break;
            case CBUS_SET_HPD://0x64
            case CBUS_CLR_HPD://0x65
                //TEST CASE : 6.3.16.1 CBM-Sink: Sink DUT Receives (0x64) SET_HPD Command
                //TEST CASE : 6.3.16.2 CBM-Sink: Sink DUT Receives (0x65) CLR_HPD Command
                MHLCbusTx(TX_MSC_CMD, CBUS_ABORT);
                ucCBUSErrorCode = ERROR_INVALID_OP_CODE;
                ucCmdIndex = 0;//index to cMSCCmd
                break;
            case CBUS_EOF:
                if (ucDataLen != 0) {//data over ?
                //TEST CASE : 6.3.11.19 CBM: DUT Receives (0x6C) WRITE_BURST - Too Much Data 
                //TEST CASE : 6.3.11.20 CBM: DUT Receives (0x6C) WRITE_BURST - Offset Wrap ABORT 
                    if (ucCmdIndex == 2) {
                    //TEST CASE : 6.3.11.16 CBM: DUT Receives (0x6C) WRITE_BURST - Data 0 EOF
                        ucCBUSErrorCode = ERROR_CBUS_POTOCOL;
                    }
                    else {
                        ucCBUSErrorCode = ERROR_BAD_OFFSET;
                    }
                    MHLCbusTx(TX_MSC_CMD, CBUS_ABORT);
                }
                else if ((bEnEOF == 0) || (ucCBUSErrorCode != CBUS_NORMAL)) {
                //TEST CASE : 6.3.11.6 CBM: DUT Receives (0x32) EOF While No Command Outstanding
//                    MHLCbusTx(TX_MSC_CMD, CBUS_ABORT);//??
                    if (bEnEOF == 0) {
                        MHLCbusTx(TX_MSC_CMD, CBUS_ABORT);//??
                        ucCBUSErrorCode = ERROR_INVALID_OP_CODE;
                    }
                    else {
                        MHLCbusTx(TX_MSC_CMD, CBUS_ACK);//??
                    }
                }
                else if ((bEnEOF == 1) && (ucCBUSErrorCode == CBUS_NORMAL)) {
                MHLCbusTx(TX_MSC_CMD, CBUS_ACK);
                }
                bEnEOF = 0;
                ucCmdIndex = 0;//index to cMSCCmd
                break;
            case CBUS_GET_STATE:
                if ((ucCmdIndex != 0) || (ucCBUSErrorCode != CBUS_NORMAL)) {
                //TEST CASE : 6.3.11.8 CBM: DUT Receives (0x61) READ_DEVCAP - Offset Control
                //TEST CASE : 6.3.11.10 CBM: DUT Receives (0x60) SET_INT - Offset Control
                //TEST CASE : 6.3.11.11 CBM: DUT Receives (0x60) SET_INT - Data Control
                //TEST CASE : 6.3.11.12 CBM: DUT Receives (0x60) WRITE_STAT - Data Control
                //TEST CASE : 6.3.11.14 CBM: DUT Receives (0x6C) WRITE_BURST - Offset Control
                //TEST CASE : 6.3.11.15 CBM: DUT Receives (0x6C) WRITE_BURST - Control Instead of First Data
                //TEST CASE : 6.3.11.17 CBM: DUT Receives (0x6C) WRITE_BURST - Data 1 Control
                //TEST CASE : 6.3.11.22 CBM: DUT Receives (0x68) MSC_MSG - Data 0 Control 
                //TEST CASE : 6.3.11.24 CBM: DUT Receives (0x68) MSC_MSG - Data 1 Control 
                    MHLCbusTx(TX_MSC_CMD,CBUS_ABORT);
                    if (ucCBUSErrorCode == CBUS_NORMAL) {
                        ucCBUSErrorCode = ERROR_CBUS_POTOCOL;
                    }
                }
                else {
                    ucCBUSErrorCode = CBUS_NORMAL;
                    MHLCbusTx(TX_MSC_DATA, CBUS_NORMAL);//no error
                }
                ucCmdIndex = 0;//index to cMSCCmd
                break;
            case CBUS_GET_VENDOR_ID:
                MHLCbusTx(TX_MSC_DATA, 0x01);
                ucCmdIndex = 0;//index to cMSCCmd
                break;
            case CBUS_GET_SC1_ERRORCODE:
            case CBUS_GET_SC3_ERRORCODE:
            case CBUS_GET_DDC_ERRORCODE:
                MHLCbusTx(TX_MSC_DATA, 0x01);
                ucCmdIndex = 0;//index to cMSCCmd
                break;
            case CBUS_GET_MSC_ERRORCODE:
                //TEST CASE : 6.3.10.5 CBM: DUT Receives (0x6B) GET_MSC_ERRCODE Command (When Err)
                MHLCbusTx(TX_MSC_DATA, ucCBUSErrorCode);
                ucCmdIndex = 0;//index to cMSCCmd                
                break;
            default://potocol is error
            //TEST CASE : 6.3.11.2 CBM: DUT Receives Illegal Commands 
                MHLCbusTx(TX_MSC_CMD,CBUS_ABORT);
                ucCBUSErrorCode = ERROR_INVALID_OP_CODE;
                ucCmdIndex = 0;//index to cMSCCmd
                break;
            }
            if (cMSCCmd == CBUS_ABORT) {
                bCBUSAbort = 1;
                usCBUSTimeoutAbort = GetTimerTickInt();
            }
            else {
                bCBUSAbort = 0;
            }
            usCBUSTimeoutIdle = GetTimerTickInt();
            break;
        case MSC_DATA_READ_VALID:
            bWaitACK = 0;
            ucCbusBuffer[ucCmdIndex] = SC_CBUS_RX_DATA;
            usCBUSTimeoutDAT = GetTimerTickInt();
            bCheckTimeout = 1;
            if ((ucCmdIndex == 0) || ((GetTimerTickInt() - usCBUSTimeoutIdle) > CBUS_IDLE_TIMEOUT)) {
            //TEST CASE : 6.3.6.2 CBM: DUT Receives Bad Reply; Data instead of Control
            //TEST CASE : 6.3.11.3 CBM: DUT Receives Data While No Command Outstanding 
//                if (ucCBUSErrorCode != ERROR_INVALID_OP_CODE) {
                if (ucCBUSCMDTxBuffer != CBUS_ABORT) {
                MHLCbusTx(TX_MSC_CMD,CBUS_ABORT);
                ucCBUSErrorCode = ERROR_INVALID_OP_CODE;
            }
                bWaitACK = 0;
            }
            else {
            if(bReadDevCapFlag == TRUE)	{
                bReadDevCapFlag = FALSE;
            }
            else {
                if ( ++ucCmdIndex >= CBUS_BUF_LEN ) {
                    ucCmdIndex = CBUS_BUF_LEN-1;
                    // Do something if any error occurred?
                }
                    if(cMSCCmd == CBUS_READ_DEVCAP)    {
                        if (cMSCOffset > 0x0F) {
                        //TEST CASE : 6.3.10.5 CBM: DUT Receives (0x6B) GET_MSC_ERRCODE Command (When Err)
                            MHLCbusTx(TX_MSC_CMD, CBUS_ABORT);
                            ucCBUSErrorCode = ERROR_BAD_OFFSET;
                        }
                        else {
                    MHLCbusTx(TX_MSC_CMD, CBUS_ACK);
                    switch (cMSCOffset) {
                            case DEVCAP_DEVSTATE:
                                MHLCbusTx(TX_MSC_DATA, SC_CBUS_DEV_STATE);//TEST CASE : 6.3.10.3 CBM: DUT receives (0x61) READ_DEVCAP Command
                                break;
                            case DEVCAP_MHLVERSION:
                                MHLCbusTx(TX_MSC_DATA, SC_CBUS_MHL_VER);//Version 1.2
                                break;
                    case DEVCAP_DEVCAT:
                                MHLCbusTx(TX_MSC_DATA, SC_CBUS_DEV_CAT);		// Sink, power = 1
                        break;
                    case DEVCAP_ADOPTERIDH:
                                MHLCbusTx(TX_MSC_DATA, SC_CBUS_ADOPTER_ID_H); //540 in Spec 2.0 for Novatek
                        break;
                    case DEVCAP_ADOPTERIDL:
                                MHLCbusTx(TX_MSC_DATA, SC_CBUS_ADOPTER_ID_L); //540 in Spec 2.0 for Novatek
                        break;
                    case DEVCAP_VIDLINKMODE:
                                MHLCbusTx(TX_MSC_DATA, SC_CBUS_VID_LINK_MODE);
                        break;
                    case DEVCAP_AUDLINKMODE:
                                MHLCbusTx(TX_MSC_DATA, SC_CBUS_AUD_LINK_MODE); 
                        break;
                    case DEVCAP_VIDEOTYPE:
                                MHLCbusTx(TX_MSC_DATA, SC_CBUS_VIDEO_TYPE); 
                        break;
                    case DEVCAP_LOGDEVMAP:
                                MHLCbusTx(TX_MSC_DATA, SC_CBUS_LOG_DEV_MAP); 
                        break;
                    case DEVCAP_BANDWIDTH:
                                MHLCbusTx(TX_MSC_DATA, SC_CBUS_BANDWIDTH);  //75Mhz/5
                        break;
                    case DEVCAP_FEATUREFLAG:
                                MHLCbusTx(TX_MSC_DATA, SC_CBUS_FEATURE_FLAG); // FEATURE_FLAG = 0x07 
                        break;
                    case DEVCAP_DEVICEIDH:
                                MHLCbusTx(TX_MSC_DATA, SC_CBUS_DEVICE_ID_H); 
                        break;
                    case DEVCAP_DEVICEIDL:
                                MHLCbusTx(TX_MSC_DATA, SC_CBUS_DEVICE_ID_L); 
                        break;
                    case DEVCAP_SCRATCHPADSIZE:
                                MHLCbusTx(TX_MSC_DATA, SC_CBUS_SCRATCHPAD_SIZE); 
                        break;
                    case DEVCAP_INSTATSIZE:
                                MHLCbusTx(TX_MSC_DATA, SC_CBUS_INT_STAT_SIZE); 
                        break;
                    default:
                                MHLCbusTx(TX_MSC_DATA, 0x00);//Reserved
                        break;
                    }
                }
                    }
                    else if(cMSCCmd == CBUS_WRITE_BURST) {//0x6C
                        if (ucCmdIndex == 2) {//offset
                            if ((cMSCOffset < 0x40) || (cMSCOffset > 0x7F)){//error
                                ucCBUSErrorCode = ERROR_BAD_OFFSET;
                            }
                            i = (CDF_SCRATCHPAD_SIZE + 0x40) - cMSCOffset;
                            if (i > 16) {
                                ucDataLen = 16;
                            }
                        }
                        else {//CDF_ADOPTER_ID_H, CDF_ADOPTER_ID_L, value
                            ucDataLen--;
                            if (ucDataLen > 16) {//error: too much data
                                ucCBUSErrorCode = ERROR_BAD_OFFSET;
                        }
                        else {
                            //    ucWriteBurstBuffer[ucCmdIndex + cMSCOffset - 0x44] = ucCbusBuffer[ucCmdIndex];
                            }
                            break;
                        }
                    }
                    else if(cMSCCmd == CBUS_MSC_MSG) {//0x68
                        ucDataLen--;
                        if(ucCmdIndex == 3) {//end (ucDataLen == 0)
                            MHLCbusTx(TX_MSC_CMD, CBUS_ACK);
                            if (cMSCOffset == MHL_MSC_MSG_RCP || cMSCOffset == MHL_MSC_MSG_UCP ) { //send RCPK
                            MHLCbusTx(TX_MSC_CMD, CBUS_MSC_MSG);
                                MHLCbusTx(TX_MSC_DATA, cMSCOffset+1);  //MHL_MSC_MSG_RCPK or MHL_MSC_MSG_UCPK
                                MHLCbusTx(TX_MSC_DATA, cMSCValue);
//                                        ucCBusState= CBUS_MSG_RCPK; 
                    	     }
                            if (cMSCOffset == MHL_MSC_MSG_RAP) { //send RAPK
                                MHLCbusTx(TX_MSC_CMD, CBUS_MSC_MSG);
                                MHLCbusTx(TX_MSC_DATA, MHL_MSC_MSG_RAPK);
                                MHLCbusTx(TX_MSC_DATA, 0x00);//no error
                                if (cMSCValue == 0x10) {//ON
                                    if (SC_DISPLAY_MUTE_CTRL == 0x00) {
                                        SC_DITHER_TOGGLE_CTRL &= ~BIT7;
                                    }
                                }
                                else if (cMSCValue == 0x11) {//OFF
                                    if (SC_DISPLAY_MUTE_CTRL == 0x00) {
                                        SC_DITHER_TOGGLE_CTRL |= BIT7;
                                    }
                                }
                            }
                        }
                    }
                    else if(cMSCCmd == CBUS_SET_INT) {//CBUS_WRITE_STAT 0x60
                        ucDataLen--;
                        if(ucCmdIndex == 3) {//end (ucDataLen == 0)
                        MHLCbusTx(TX_MSC_CMD, CBUS_ACK);
//                            if (cMSCOffset == 0x30)	{// CONNECTED_RDY
                            if ((cMSCOffset == 0x20)){// || (cMSCOffset == 0x30))	{// RCHANGE_INT
                            if(cMSCValue == 0x01) {
                                MHLCbusTx(TX_MSC_CMD, CBUS_SET_HPD);
                                ucCBusState = CBUS_SETHPD;
                                ucMHLConnState = MHL_SET_HPD;
                                    //usTimerTickMHL = usTimerTick_1ms;
                            }
                                else if ((cMSCValue & 0x10) != 0 ) {
                                    ucWrBurstState = WB_WAIT2GO;
                                    ucWrBurstCount = 0;
                                }
                                else if ((cMSCValue & 0x08) != 0) {
                                    ucWrBurstState = WB_GRT;
                                }
                        }
                            else if (cMSCOffset == 0x31) {
                            if ( (cMSCValue&0x07)==0x02 ) {
                                bPackPixelModeIntFlag = TRUE;
                            }
                            else {
                                bPackPixelModeIntFlag = FALSE;
                                }
                            }
                        }
                    }
                }
            }
            break;	
        }
    }while(tmp !=0);
}

//******************************************************************************
// Prototype: 
//  void CbusDDCCmdHandler(void)
// Parameters:
//
// Return:
//  None
// Purpose:
//
// Notes:
//  None
//******************************************************************************
void CbusDDCCmdHandler(void) using 1
{
    UCHAR tmp;
    do {
        tmp = SC_CBUS_TRANS_FLAG0 & (DDC_CMD_READ_VALID|DDC_DATA_READ_VALID);
        switch ( tmp )   {
        case DDC_DATA_READ_VALID:
            //MHLCbusTx(TX_DDC_CMD, CBUS_ACK);
            DDCTranslation(SC_CBUS_RX_DATA);
            break;        
        case DDC_CMD_READ_VALID:
            tmp = SC_CBUS_RX_DATA;
            switch ( tmp ) {
            case CBUS_CONT:
                if (bStartOfFrame == 0) {//after get offset
                    //TEST CASE : 6.3.22.1 CBM-Sink: DUT Receives SOF, CONT 
                    //TEST CASE : 6.3.22.2 CBM-Sink: DUT Receives DDC Write; Various Errs 
                MHL_HDCP_SendData();
                    ucCBUSDDCStatus = CBUS_DDC_Data;
                    usCBUSTimeoutDAT = GetTimerTickInt();
                    bCheckDDCTimeout = 1;
                }
                else {
                    MHLCbusTx(TX_DDC_CMD, CBUS_ABORT);
                }
                break;
            case CBUS_SOF:
                ucCmdIndex = 0;		// Start to push DDC command to cCBusBuffer
                bStartOfFrame = 1;
                ucCBUSDDCStatus = CBUS_DDC_SOF;
                bCheckDDCTimeout = 0;
                break;
            case CBUS_EOF:
                if (ucCBUSDDCStatus != CBUS_DDC_Stop){
                        //TEST CASE : 6.3.22.2 CBM-Sink: DUT Receives DDC Write; Various Errs 
                    MHLCbusTx(TX_DDC_CMD, CBUS_ABORT);
                }
                bCheckDDCTimeout = 0;
                ucCBUSDDCStatus = CBUS_DDC_EOF;//IDLE status
                bStartOfFrame = 0;		// Reset _SOF command count
                bDDCWriteFlag = FALSE;	// Reset Write command ready flag.
                break;
            case CBUS_STOP:
                if (ucCBUSDDCStatus != CBUS_DDC_Data){
                    MHLCbusTx(TX_DDC_CMD, CBUS_ABORT);
                    ucCBUSDDCStatus = CBUS_DDC_EOF;//IDLE status
                    bCheckDDCTimeout = 0;
                }
                else {
                    usCBUSTimeoutDAT = GetTimerTickInt();
                    bCheckDDCTimeout = 1;
                    ucCBUSDDCStatus = CBUS_DDC_Stop;//STOP status
                }
                bStartOfFrame = 0;		// Reset _SOF command count
                bDDCWriteFlag = FALSE;	// Reset Write command ready flag.
                break;
            case CBUS_ABORT:
                ucCBUSDDCStatus = CBUS_DDC_EOF;
                bStartOfFrame = 0;		// Reset _SOF command count
                bDDCWriteFlag = FALSE;	// Reset Write command ready flag.
                break;
            }
            break;
        }
    }while(tmp !=0);
}

//******************************************************************************
// Prototype: 
//  void MHLHandler()
// Parameters:
//
// Return:
//  None
// Purpose:
//
// Notes:
//  None
//******************************************************************************
void MHLHandler(void)
{
    UCHAR curr_interface = GetCurrInputInterface();

    if (IsMHL0CableConnect() || IsMHL1CableConnect()) 
      {
        if (IP != 0x01)
            IP = 0x01;
        }
    else 
	{
        if (IP != 0x00)
            IP = 0x00;    
       }

    CbusHandler();

    if ( GetCbusConnectStatus() == MHL_DATA_RDY ) { 
        if (!((curr_interface==DIGITAL_INPUT0 &&  MHLIsCBus1On() ) ||
                    (curr_interface==DIGITAL_INPUT1 &&  MHLIsCBus2On() ))) { //not current MHL port
            if ( !MHLIsClearHPD() ) {
                MHLClearHPD();
             }
            }
        }

    if ( bPackPixelModeIntFlag ) {
        bPackPixelModeIntFlag = 0;
        MHLPackedPixelMode(TRUE);
    }

#if ENABLE_HDMI_PRETEST == ON
//RCP/UCP test//////////////////////////////////////
    if ((ucMHLConnState == MHL_PATH_EN) || (ucMHLConnState == MHL_DATA_RDY)) 
	{
        if (RCP_TEST != 0xFF) {		// debug ID code.
            switch( SC_SRGB_DITH_CTRL ) {
            case 0x00:
            if (CBUSTxData(TX_MSC_CMD, CBUS_MSC_MSG)) {
                if (CBUSTxData(TX_MSC_DATA, MHL_MSC_MSG_RCP)) {
                    CBUSTxData(TX_MSC_DATA, RCP_TEST);
                }
            }	
            RCP_TEST = 0xFF;
                break;
             case 0x01:
                if (CBUSTxData(TX_MSC_CMD, CBUS_MSC_MSG)) {
                    if (CBUSTxData(TX_MSC_DATA, MHL_MSC_MSG_UCP)) {
                        CBUSTxData(TX_MSC_DATA, RCP_TEST);
                    }
                }	
                RCP_TEST = 0xFF;
                break;
             case 0x02:
                if (CBUSTxData(TX_MSC_CMD, CBUS_MSC_MSG)) {
                    if (CBUSTxData(TX_MSC_DATA, MHL_MSC_MSG_RAP)) {
                        CBUSTxData(TX_MSC_DATA, RCP_TEST);
                    }
                }	
                RCP_TEST = 0xFF;
                break;
             default:
                break;
            }
        }
    }
#endif

///////////////////////////////////////////////
//TEST CASE : 6.3.12.1 CBM: DUT Receives (0x61) READ_DEVCAP - Offset Timeout 
//TEST CASE : 6.3.12.2 CBM: DUT Receives (0x60) SET_INT / WRITE_STAT - Offset Timeout 
//TEST CASE : 6.3.12.3 CBM: DUT Receives (0x60) SET_INT - Data Timeout 
//TEST CASE : 6.3.12.5 CBM: DUT Receives (0x6C) WRITE_BURST - Offset Timeout 
//TEST CASE : 6.3.12.6 CBM: DUT Receives (0x6C) WRITE_BURST - Data 0 Timeout 
//TEST CASE : 6.3.12.7 CBM: DUT Receives (0x6C) WRITE_BURST - EOF Timeout 
//TEST CASE : 6.3.12.8 CBM: DUT Receives (0x68) MSC_MSG - Data 0 Timeout 
//TEST CASE : 6.3.12.9 CBM: DUT Receives (0x68) MSC_MSG - Data 1 Timeout 
    if (bCheckTimeout == TRUE) {
        if ((GetTimerTick() - usCBUSTimeoutDAT) > CBUS_TPKT_TIMEOUT) {
            ucCBUSErrorCode = ERROR_CBUS_TIMEOUT;
            bWaitACK = 0;
        }
    }
    if (bCheckDDCTimeout == TRUE) {
    //TEST CASE : 6.3.22.1 CBM-Sink: DUT Receives SOF, CONT 
    //TEST CASE : 6.3.22.2 CBM-Sink: DUT Receives DDC Write; Various Errs 
        if ((GetTimerTick() - usCBUSTimeoutDAT) > CBUS_TPKT_TIMEOUT) {
            CBUSTxData(TX_DDC_CMD, CBUS_ABORT);
            bCheckDDCTimeout = 0;
            bWaitACK = 0;
        }
    }
    if ((bWaitACK == 1) && ((GetTimerTick() - usCBUSTimeoutACK) > CBUS_AA_TIMEOUT)) {
        bWaitACK = 0;
    }

#if ENABLE_INT_TRANSLATION == OFF    
    if (bTranslationReady == 1) {
        if (bReadDevCapFlag == FALSE) {
            bTranslationReady = 0;
            MSCCmdTranslation();
        }
    }
#endif    

    if (ucWrBurstState != WB_NONE) {
        switch (ucWrBurstState) {
        case WB_WAIT2GO: // send 60 20 04
            if (CBUSTxData(TX_MSC_CMD, CBUS_SET_INT)) {
                if (CBUSTxData(TX_MSC_DATA, 0x20)) {
                    if (CBUSTxData(TX_MSC_DATA, 0x04)) {
                        ucWrBurstState = WB_REQ;
                    }
                }
            }
            break;
        case WB_GRT: //REQ:60 20 04; GRT:60 20 08; WriteBurst
            WriteBurst3DInfo();
            ucWrBurstState = WB_WRITING;
            ucWrBurstCount++;
            break;
        case WB_WRITING: //REQ:60 20 04; GRT:60 20 08; WriteBurst
            if (CBUSTxData(TX_MSC_CMD, CBUS_SET_INT)) {
                if (CBUSTxData(TX_MSC_DATA, 0x20)) {
                    if (CBUSTxData(TX_MSC_DATA, 0x02)) {
                        if (ucWrBurstCount <2 ) {
                            ucWrBurstState = WB_WAIT2GO;
                        }
                        else {
                            ucWrBurstState = WB_NONE;
                        }
                    }
                }
            }
            break;
        default:
            break;
        }
    }
}

//******************************************************************************
// Prototype: 
//  void SetCbusConnectStatus(UCHAR status)
// Parameters:
//
// Return:
//  None
// Purpose:
//
// Notes:
//  None
//******************************************************************************
void SetCbusConnectStatus(UCHAR status)
{
    ucMHLConnState = status;
    
    switch (status) {
        case MHL_NONE:
            ucCBusState = CBUS_UNACTIVE;
        bClearHPD = 0;
            break;
        case MHL_DISCOVERY_RDY:
            ucCBusState = CBUS_DISCOVERY_DONE;
            ucIsMHLSrcConnected[MHL_GetCbusCH()] = TRUE;
            break;
        case MHL_CONNECT_RDY:
            ucCBusState = CONNECTED_RDY;
            break;
        case MHL_SET_HPD:
            ucCBusState = CBUS_SETHPD;
            break;
        case MHL_PATH_EN:
            ucCBusState = LINK_MODE;
            break;
        case MHL_DATA_RDY:
            ucCBusState = CBUS_ACTIVE;
            break;
        case MHL_CLR_HPD:
            ucCBusState = CBUS_CLRHPD;
        break;
        default:
            ucCBusState = CBUS_UNKNOWN;
            break;
    }
}

//******************************************************************************
// Prototype: 
//  UCHAR GetCbusConnectStatus(void)
// Parameters:
//
// Return:
//  None
// Purpose:
//
// Notes:
//  None
//******************************************************************************
UCHAR GetCbusConnectStatus(void)
{
    return ucMHLConnState;
}

//******************************************************************************
// Prototype: 
//  void MSCCmdTranslation(void)
// Parameters:
//
// Return:
//  None
// Purpose:
//
// Notes:
//  None
//******************************************************************************
void MSCCmdTranslation(void)
{
#if ENABLE_INT_TRANSLATION == ON
	switch(ucCBusState) {
        case CBUS_SETHPD:
            if ( MHLCbusTx(TX_MSC_CMD, CBUS_WRITE_STAT) ) {
                if (MHLCbusTx(TX_MSC_DATA,0x30)) {		// Connected Device Ready status
                    if (MHLCbusTx(TX_MSC_DATA,0x01)) {		// DCAP_RDY
                        ucCBusState = CONNECTED_RDY;
                        ucMHLConnState = MHL_CONNECT_RDY;
                        bWaitACK = 1;
                        usCBUSTimeoutACK = GetTimerTickInt();
                    }
    }
            }
            break;
		case CONNECTED_RDY:
            if ( MHLCbusTx(TX_MSC_CMD, CBUS_WRITE_STAT) ) {
                if (MHLCbusTx(TX_MSC_DATA, 0x31)) {		// Link Mode
                    if (MHLCbusTx(TX_MSC_DATA, 0x08)) {		// PATH_EN
                        ucCBusState = LINK_MODE;
                        ucMHLConnState = MHL_PATH_EN;
                        bWaitACK = 1;
                        usCBUSTimeoutACK = GetTimerTickInt();
                    }
                }
            }
            break;
        case CBUS_ACTIVE:
		case LINK_MODE:
#if 0//ENABLE_HDMI_PRETEST == ON
            Sleep(100);//2.	4.3.17.2 CBT-Sink: Sink Loses Arbitration Collision Correctly.
#endif
            if ( MHLCbusTx(TX_MSC_CMD, CBUS_SET_INT) ) {
                if ( MHLCbusTx(TX_MSC_DATA, 0x20) ) {		// Rchange_int
                    if ( MHLCbusTx(TX_MSC_DATA, 0x01) ) {		// DCAP_CHG
                        ucCBusState = RCHANGE_INT;
                        bWaitACK = 1;
                        usCBUSTimeoutACK = GetTimerTickInt();
                    }
                }
            }
            break;
        case RCHANGE_INT:
            break;
        default:
            ucCBusState = CBUS_UNKNOWN;
        break;
    }
#else

    //if (ucCmdIndex != 0) {
        //return;
    //}
#if 0//ENABLE_INT_TRANSLATION == OFF    
    if (bCBUSAbort == 1) {
        if ((GetTimerTickInt() - usCBUSTimeoutIdle) < CBUS_AA_TIMEOUT) {
            return;
        }
    }
#endif
	switch(ucCBusState) {
		case CBUS_SETHPD:
            if (CBUSTxData(TX_MSC_CMD, CBUS_WRITE_STAT)) {
                if (CBUSTxData(TX_MSC_DATA,0x30)) {		// Connected Device Ready status
                    if (CBUSTxData(TX_MSC_DATA,0x01)) {		// DCAP_RDY
                        ucCBusState = CONNECTED_RDY;
                        ucMHLConnState = MHL_CONNECT_RDY;
                        bWaitACK = 1;
                        usCBUSTimeoutACK = GetTimerTickInt();
                    }
                }
            }
			break;
		case CONNECTED_RDY:
            if (CBUSTxData(TX_MSC_CMD, CBUS_WRITE_STAT)) {
                if (CBUSTxData(TX_MSC_DATA, 0x31)) {		// Link Mode
                    if (CBUSTxData(TX_MSC_DATA, 0x08)) {		// PATH_EN
                        ucCBusState = LINK_MODE;
                        ucMHLConnState = MHL_PATH_EN;
                        bWaitACK = 1;
                        usCBUSTimeoutACK = GetTimerTickInt();
                    }
                }
            }
			break;
            case CBUS_ACTIVE:
		case LINK_MODE:
#if 1//ENABLE_HDMI_PRETEST == ON
            Sleep(100);//2.	4.3.17.2 CBT-Sink: Sink Loses Arbitration Collision Correctly.
#endif
            if (CBUSTxData(TX_MSC_CMD, CBUS_SET_INT)) {
                if (CBUSTxData(TX_MSC_DATA, 0x20)) {		// Rchange_int
                    if (CBUSTxData(TX_MSC_DATA, 0x01)) {		// DCAP_CHG
                        ucCBusState = RCHANGE_INT;
                        bWaitACK = 1;
                        usCBUSTimeoutACK = GetTimerTickInt();
                    }
                }
            }
            break;
        case RCHANGE_INT:
			break;
#if 0
		case CBUS_MSG_RCPK:
			CBUSTxData(TX_MSC_CMD, CBUS_READ_DEVCAP);
			MHLCbusTx(TX_MSC_DATA, 0x01);
			ucCBusState = RDEV_VER;
			bReadDevCapFlag = TRUE;
			break;
		case RDEV_VER:
			MHLCbusTx(TX_MSC_CMD, CBUS_READ_DEVCAP);
			MHLCbusTx(TX_MSC_DATA, 0x02);
			ucCBusState = RDEV_CAT;
			bReadDevCapFlag = TRUE;
			break;
		case RDEV_CAT:
			MHLCbusTx(TX_MSC_CMD, CBUS_READ_DEVCAP);
			MHLCbusTx(TX_MSC_DATA, 0x08);
			ucCBusState = RDEV_LOG;
			bReadDevCapFlag = TRUE;			
			break;
		case RDEV_LOG:
			MHLCbusTx(TX_MSC_CMD, CBUS_READ_DEVCAP);
			MHLCbusTx(TX_MSC_DATA, 0x05);
			ucCBusState = RDEV_VID_LINK;
			bReadDevCapFlag = TRUE;
			break;
		case RDEV_VID_LINK:
			MHLCbusTx(TX_MSC_CMD, CBUS_READ_DEVCAP);
			MHLCbusTx(TX_MSC_DATA, 0x06);
			ucCBusState = RDEV_AUDIO;	
			bReadDevCapFlag = TRUE;
			break;
		case RDEV_AUDIO:
			MHLCbusTx(TX_MSC_CMD, CBUS_READ_DEVCAP);
			MHLCbusTx(TX_MSC_DATA, 0x07);
			ucCBusState = RDEV_VIDEO_TYPE;
			bReadDevCapFlag = TRUE;
			break;
		case RDEV_VIDEO_TYPE:
			MHLCbusTx(TX_MSC_CMD, CBUS_READ_DEVCAP);
			MHLCbusTx(TX_MSC_DATA, 0x09);
			bReadDevCapFlag = TRUE;
			ucCBusState = RDEV_BANDWIDTH;      
			break;
#endif
		default:
			ucCBusState = CBUS_UNKNOWN;
                    break;
	}
#endif    
}

//******************************************************************************
// Prototype: 
//  UCHAR HDCPAddrRemaping(UCHAR offset)
// Parameters:
//
// Return:
//  None
// Purpose:
//
// Notes:
//  None
//******************************************************************************
UCHAR HDCPAddrRemaping(UCHAR offset) using 1
{
    								// 0    1    2    3    4    5    6    7    8    9    a
    code UCHAR hdcp_index1[]={0x1a,0x1b,0x1c,0x1d,0x1e,0xff,0xff,0xff,0x1f,0x20,0x0a};
    								// 10   11   12   13   14   15   16   17   18   19   1a   1b   1c   1d   1e   1f
    code UCHAR hdcp_index2[]={0x21,0x22,0x23,0x24,0x25,0xff,0xff,0xff,0x26,0x27,0x28,0x29,0x2a,0x2b,0x2c,0x2d};
    								// 40   41   42
    code UCHAR hdcp_index3[]={0x2e,0xff,0x30};
    								// F8,  F9   FA
    code UCHAR hdcp_index4[]={0xf3,0xf4,0xf5};	

    if(offset <= 0x0a)
        return hdcp_index1[offset];
    else if((offset >= 0x10) && (offset <= 0x1F))
        return hdcp_index2[offset-0x10];
    else if((offset >= 0x40) && (offset <= 0x42))
        return hdcp_index3[offset-0x40];
    else if((offset >=0xF8) && (offset <= 0xFA))
        return hdcp_index4[offset-0xF8];
    else 
        return 0xFF;
}

//******************************************************************************
// Prototype: 
//  void MHL_HDCP_SendData(void)
// Parameters:
//
// Return:
//  None
// Purpose:
//
// Notes:
//  None
//******************************************************************************
void MHL_HDCP_SendData(void) using 1
{
    if (pMHLDDCPtr == (HDCP_PAGE_ADDR + 0xFF)) {
        MHLCbusTx(TX_DDC_DATA, 0x00);
    }
    else {
    MHLCbusTx(TX_DDC_DATA, *pMHLDDCPtr);
    }
    
    if(bHdcpFlag==TRUE)  {
        ucHdcpIndex++;
        if ( ucHdcpIndex == 0x09 ) { // for speedup Ri
            pMHLDDCPtr = HDCP_PAGE_ADDR+0x20;
            ucMHLConnState = MHL_DATA_RDY;
            ResetWDTimer(); //jtest: need confirm
        }
        else {
            pMHLDDCPtr = HDCP_PAGE_ADDR + HDCPAddrRemaping(ucHdcpIndex);
        }
    }
    else {     
        pMHLDDCPtr++;
    ucEDIDIndex++;
    if(ucEDIDIndex>=0x100) {
        ucEDIDIndex = 0x100;
    }
}
}

//******************************************************************************
// Prototype: 
//  void DDCTranslation(UCHAR rxdata)
// Parameters:
//
// Return:
//  None
// Purpose:
//
// Notes:
//  None
//******************************************************************************
void DDCTranslation(UCHAR rxdata) using 1
{
    UCHAR offset;
////////////////////////////////////////////////////////////////////
//TEST CASE : 6.3.21.1 CBM-Sink: DUT Receives DDC Write
//TEST CASE : 6.3.21.2 CBM-Sink: DUT Receives DDC Current Read
//TEST CASE : 6.3.21.3 CBM-Sink: DUT Receives regular DDC Read 
//TEST CASE : 6.3.21.5 CBM-Sink: DUT NACKs DDC Segment Read; Segment Register Not Implemented
    ucCbusBuffer[ucCmdIndex] = rxdata;
    if (ucCmdIndex == 0) {//check DevAddr
        offset = ucCbusBuffer[ucCmdIndex] & 0xFE;
        if ((offset != CBUS_EDID_WRITE) && (offset != CBUS_HDCP_WRITE)) {//not EDID or HDCP and no segment function (0x60)
            MHLCbusTx(TX_DDC_CMD, CBUS_NACK);
        }
        else {//EDID or HDCP
            MHLCbusTx(TX_DDC_CMD, CBUS_ACK);
        }
    }
    else {//data
        MHLCbusTx(TX_DDC_CMD, CBUS_ACK);
    }

    if(bStartOfFrame) {
        if(ucCmdIndex == 0) {
            // First DDC command
            ucCBUSDDCStatus = CBUS_DDC_DevAddr;
            if((ucCbusBuffer[0] & 0x01)==0) {
                // Write command
                bDDCWriteFlag = TRUE;
                usCBUSTimeoutDAT = GetTimerTickInt();
                bCheckDDCTimeout = 1;
            }
            else {
                // Read command.
                if(bDDCWriteFlag == FALSE) {
                    // Short Read & Current Read command.
                    if(ucCbusBuffer[0] == CBUS_HDCP_READ) {
                        if (bHdcpFlag == FALSE) {//DevAddr not match
                           // TxData(TX_DDC_CMD, CBUS_ABORT);
                        }
                        else {//DevAddr match
                        pMHLDDCPtr = HDCP_PAGE_ADDR + 0x1F;
                        ucHdcpIndex = 0x08;
                    }
                    }
//                    else if(ucCbusBuffer[0] == CBUS_EDID_READ) {
//                        if (bHdcpFlag == TRUE) {//DevAddr not match
                         //   TxData(TX_DDC_CMD, CBUS_ABORT);
//                        }
//                    }
                    else {//error DevAddr
                    }
                }
                bStartOfFrame = FALSE;
                bDDCWriteFlag = FALSE;
            }
        }
        else {
            ucCBUSDDCStatus = CBUS_DDC_Offset;
            if((ucCbusBuffer[0]&0xFE) == CBUS_EDID_WRITE) {
                pMHLDDCPtr =  &EDID_SRAM_MHL + ucCbusBuffer[1];		// Pointer = EDID_SRAM + Offset
                bHdcpFlag = FALSE;
            }
            else if((ucCbusBuffer[0]) == CBUS_HDCP_WRITE) {
                ucHdcpIndex = ucCbusBuffer[1];
                offset = HDCPAddrRemaping(ucHdcpIndex);
                pMHLDDCPtr  = HDCP_PAGE_ADDR + offset;				// Pointer = HDCP_SRAM + Offset
                bHdcpFlag = TRUE;
            }
            bStartOfFrame = FALSE;
        }		

        if ( ++ucCmdIndex >= CBUS_BUF_LEN ) {
            ucCmdIndex = CBUS_BUF_LEN-1;
            // Do something if any error occurred?
        }
    }		
    else if(ucCbusBuffer[0] == CBUS_HDCP_WRITE || ucCbusBuffer[0] == CBUS_EDID_WRITE) {        // Write data.
        if ((ucCBUSDDCStatus != CBUS_DDC_Offset) && (ucCBUSDDCStatus != CBUS_DDC_Data)) {//offset or data
        //TEST CASE : 6.3.22.2 CBM-Sink: DUT Receives DDC Write; Various Errs
        //TEST CASE : 6.3.22.3 CBM-Sink: DUT Receives DDC Short Read and Current Read; Various Errs 
            MHLCbusTx(TX_DDC_CMD, CBUS_ABORT);
        }
        else {
            if(pMHLDDCPtr != (HDCP_PAGE_ADDR + 0xFF)) {
            *pMHLDDCPtr++ = rxdata;
    }
            ucCBUSDDCStatus = CBUS_DDC_Data;
            usCBUSTimeoutDAT = GetTimerTickInt();
            bCheckDDCTimeout = 1;
        }
    }
}

//******************************************************************************
// Prototype: 
//  BOOL IsMHL0CableConnect(void)
// Parameters:
//
// Return:
//  None
// Purpose:
//
// Notes:
//  None
//******************************************************************************
BOOL IsMHL0CableConnect(void)
{
    UCHAR ret = 0;
#if IS_NT68850_SERIES
    UCHAR Reg0xB57 =0;
    UCHAR ZpState=0;
#endif

#if IS_NT68770_SERIES
    if ( MHL_Is_CDSense1_IO_HIGH() ) {
        ret = TRUE;
    }
#elif IS_NT68850_SERIES
    if ( IsZpMode() ) {
        Reg0xB57 = SC_ADC_ZERO_POWER_CTRL;
        SC_ADC_ZERO_POWER_CTRL |= BIT7;
        ZpState = 1;
    }
    
    if ( MHL_IsCDSenseFlagOn() ) {
        ret = TRUE;
    }
    
    if(ZpState == 1){
        SC_ADC_ZERO_POWER_CTRL = Reg0xB57;
    }
#endif

    return ret;
}

//******************************************************************************
// Prototype: 
//  BOOL IsMHL1CableConnect(void)
// Parameters:
//
// Return:
//  None
// Purpose:
//
// Notes:
//  None
//******************************************************************************
BOOL IsMHL1CableConnect(void)
{
    UCHAR ret = 0;
#if IS_NT68770_SERIES
    if ( MHL_Is_CDSense2_IO_HIGH() ) {
        ret = TRUE;
    }
#endif

    return ret;
}

//******************************************************************************
// Prototype: 
//  BOOL IsMHL0Connect(void)
// Parameters:
//
// Return:
//  None
// Purpose:
//
// Notes:
//  None
//******************************************************************************
BOOL IsMHL0Connect(void)
{
    return ucIsMHLSrcConnected[MHL_CBUS_CH1];
}

//******************************************************************************
// Prototype: 
//  BOOL IsMHL1Connect(void)
// Parameters:
//
// Return:
//  None
// Purpose:
//
// Notes:
//  None
//******************************************************************************
BOOL IsMHL1Connect(void)
{
    return ucIsMHLSrcConnected[MHL_CBUS_CH2];
}

//******************************************************************************
// Prototype: 
//  void MHLClearHPD(void)
// Parameters:
//
// Return:
//  None
// Purpose:
//
// Notes:
//  None
//******************************************************************************
void MHLClearHPD(void)
{
    MHL_WaitCBusReady();
    if ( ucMHLConnState == MHL_DATA_RDY && ucCBUSDDCStatus == CBUS_DDC_EOF) {
        SC_CBUS_MSC_CMD = CBUS_CLR_HPD;
        bClearHPD = 1;
    }
}

//******************************************************************************
// Prototype: 
//  void MHLResetHPD(void)
// Parameters:
//
// Return:
//  None
// Purpose:
//
// Notes:
//  None
//******************************************************************************
void MHLResetHPD(void)
{
    MHL_WaitCBusReady();
    if ( ucCBUSDDCStatus == CBUS_DDC_EOF ) {
        SC_CBUS_MSC_CMD = CBUS_SET_HPD;
    SetCbusConnectStatus(MHL_SET_HPD);
    bClearHPD = 0;
    }
}


//******************************************************************************
// Prototype: 
//  void MHLIsClearHPD(void)
// Parameters:
//
// Return:
//  None
// Purpose:
//
// Notes:
//  None
//******************************************************************************

BOOL MHLIsClearHPD(void)
{
    return bClearHPD;
}

#if ((INPUT_INTERFACE&INPUT_MHL0) || (INPUT_INTERFACE&INPUT_MHL1))// && ENABLE_HDMI_PRETEST == ON
//TEST CASE : 6.3.1.1 CBM: Capability Regs
// Error : DUT does not response all 16 DEV_CAP registers.
//TEST CASE : 4.2.x.x: wait discovery....
void ToggleRxSense(void)
{
    SC_CBUS_RESISTOR_CTRL = 0x38;
    Sleep(5);
    SC_CBUS_RESISTOR_CTRL = 0x33;
}
#endif

#if defined(MHL_CTS_DEBUG_TEST1)
BOOL MHLIsCBus1Active(void)
{
     if (McuGetIOBit(DIG0_HPD_PORT, DIG0_HPD_BIT) != DIG0_HPD_ACTIVE) {
        return FALSE;
    }
    return TRUE;
}

BOOL MHLIsCBus2Active(void)
{
     if (McuGetIOBit(DIG1_HPD_PORT, DIG1_HPD_BIT) != DIG1_HPD_ACTIVE) {
        return FALSE;
    }
    return TRUE;
}
#endif

static BOOL WriteBurst3DInfo(void)
{
    UCHAR i;
    if ( !CBUSTxData(TX_MSC_CMD, CBUS_WRITE_BURST) ) { //WriteBurst
        return 0;
    }
    if ( !CBUSTxData(TX_MSC_DATA, 0x40) ) { //Scrapthpad
        return 0;
    }
    if ( !CBUSTxData(TX_MSC_DATA, 0x00) ) { // 3D_VIC(2) or 3D_DTD(2)
        return 0;
    }
    if ( !CBUSTxData(TX_MSC_DATA, 0x10+ucWrBurstCount) ) { // 3D_VIC(2) or 3D_DTD(2)
        return 0;
    }
    if ( !CBUSTxData(TX_MSC_DATA, 0xFF-0x10-ucWrBurstCount+1) ) { // Checksum
        return 0;
    }
    for (i=0; i<13; i++ ) {
        if (!CBUSTxData(TX_MSC_DATA, 0x00)) {
            return 0;
        }
    }
    if (!CBUSTxData(TX_MSC_CMD, CBUS_EOF)) {
        return 0;
    }

    return 1;
}

#endif

