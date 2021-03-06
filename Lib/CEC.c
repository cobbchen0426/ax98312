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

#if ENABLE_HW_CEC == ON

//******************************************************************************
// M A C R O   D E F I N I T I O N S
//******************************************************************************
#define CEC_TX_OK    0 /*!< Scaler CEC status. */
#define CEC_RX_OK    1 /*!< Scaler CEC status. */
#define CEC_TX_BUSY  2 /*!< Scaler CEC status. */
#define CEC_TX_FAIL  3 /*!< Scaler CEC status. */
#define CEC_RX_FAIL  4 /*!< Scaler CEC status. */
#define CEC_BUS_FAIL 5 /*!< Scaler CEC status. */
#define CEC_IDLE     6 /*!< Scaler CEC status. */

#define CEC_ACTIVE_SOURCE               0x82 /*!< CEC command ID. Please refer to the HDMI spec. */
#define CEC_IMAGE_VIEW_ON               0x04 /*!< CEC command ID. Please refer to the HDMI spec. */
#define CEC_TEXT_VIEW_ON                0x0d /*!< CEC command ID. Please refer to the HDMI spec. */
#define CEC_REQUEST_ACTIVE_SOURCE       0x85 /*!< CEC command ID. Please refer to the HDMI spec. */
#define CEC_STANDBY                     0x36 /*!< CEC command ID. Please refer to the HDMI spec. */
#define CEC_GIVE_PHYSICAL_ADDRESS       0x83 /*!< CEC command ID. Please refer to the HDMI spec. */
#define CEC_GET_MENU_LANGUAGE           0x91 /*!< CEC command ID. Please refer to the HDMI spec. */
#define CEC_REPORT_PHYSICAL_ADDRESS     0x84 /*!< CEC command ID. Please refer to the HDMI spec. */
#define CEC_SET_MENU_LANGUAGE           0x32 /*!< CEC command ID. Please refer to the HDMI spec. */
#define CEC_DEVICE_VENDOR_ID            0x87 /*!< CEC command ID. Please refer to the HDMI spec. */
#define CEC_GIVE_DEVICE_VENDOR_ID       0x8c /*!< CEC command ID. Please refer to the HDMI spec. */
#define CEC_VENDOR_COMMAND              0x89 /*!< CEC command ID. Please refer to the HDMI spec. */
#define CEC_VENDOR_RC_BUTTON_DOWN       0x8a /*!< CEC command ID. Please refer to the HDMI spec. */
#define CEC_VENDOR_RC_BUTTON_UP         0x8b /*!< CEC command ID. Please refer to the HDMI spec. */
#define CEC_SET_OSD_STRING              0x64 /*!< CEC command ID. Please refer to the HDMI spec. */
#define CEC_GIVE_OSD_NAME               0x46 /*!< CEC command ID. Please refer to the HDMI spec. */
#define CEC_SET_OSD_NAME                0x47 /*!< CEC command ID. Please refer to the HDMI spec. */
#define CEC_MENU_REQUEST                0x8d /*!< CEC command ID. Please refer to the HDMI spec. */
#define CEC_MENU_STATUS                 0x8e /*!< CEC command ID. Please refer to the HDMI spec. */
#define CEC_USER_CONTROL_PRESSED        0x44 /*!< CEC command ID. Please refer to the HDMI spec. */
#define CEC_USER_CONTROL_RELEASED       0x45 /*!< CEC command ID. Please refer to the HDMI spec. */
#define CEC_GIVE_DEVICE_POWER_STATUS    0x8f /*!< CEC command ID. Please refer to the HDMI spec. */
#define CEC_REPORT_POWER_STATUS         0x90 /*!< CEC command ID. Please refer to the HDMI spec. */
#define CEC_FEATURE_ABORT               0x00 /*!< CEC command ID. Please refer to the HDMI spec. */
#define CEC_RECORD_OFF                  0x0b /*!< CEC command ID. Please refer to the HDMI spec. */
#define CEC_RECORD_ON                   0x09 /*!< CEC command ID. Please refer to the HDMI spec. */
#define CEC_RECORD_STATUS               0x0a /*!< CEC command ID. Please refer to the HDMI spec. */
#define CEC_RECORD_TV_SCREEN            0x0f /*!< CEC command ID. Please refer to the HDMI spec. */
#define CEC_SELECT_DIGITAL_SOURCE       0x93 /*!< CEC command ID. Please refer to the HDMI spec. */
#define CEC_INACTIVE_SOURCE             0x9D /*!< CEC command ID. Please refer to the HDMI spec. */
#define CEC_ABORT_TEST                  0xff /*!< CEC command ID. Please refer to the HDMI spec. */

#define CEC_REQ_SYS_POWERUP             0x01 /*!< Mask for CEC request. */
#define CEC_REQ_SYS_POWERDOWN           0x02 /*!< Mask for CEC request. */
#define CEC_REQ_ACTIVATE_INPUT          0x04 /*!< Mask for CEC request. */
#define CEC_REQ_INACTIVATE_INPUT        0x08 /*!< Mask for CEC request. */
#define CEC_REQ_DEVICE_CTRL             0x10 /*!< Mask for CEC request. */

#define IsCECPwrUp() ((ucCECReqFlag&CEC_REQ_SYS_POWERUP) != 0)                /*!< Check CEC request status. */
#define IsCECPwrDn() ((ucCECReqFlag&CEC_REQ_SYS_POWERDOWN) != 0)              /*!< Check CEC request status. */
#define IsCECAvtInput() ((ucCECReqFlag&CEC_REQ_ACTIVATE_INPUT) != 0)          /*!< Check CEC request status. */
#define IsCECInavtInput() ((ucCECReqFlag&CEC_REQ_INACTIVATE_INPUT) != 0)      /*!< Check CEC request status. */
#define IsCECDevCtrl() ((ucCECReqFlag&CEC_REQ_DEVICE_CTRL) != 0)              /*!< Check CEC request status. */
#define SetCECPwrUpFlag() {ucCECReqFlag |= CEC_REQ_SYS_POWERUP;}              /*!< Set CEC request status. */
#define SetCECPwrDnFlag() {ucCECReqFlag |= CEC_REQ_SYS_POWERDOWN;}            /*!< Set CEC request status. */
#define SetCECAvtInputFlag() {ucCECReqFlag |= CEC_REQ_ACTIVATE_INPUT;}        /*!< Set CEC request status. */
#define SetCECInavtInputFlag() {ucCECReqFlag |= CEC_REQ_INACTIVATE_INPUT;}    /*!< Set CEC request status. */
#define SetCECDevCtrlFlag() {ucCECReqFlag |= CEC_REQ_DEVICE_CTRL;}            /*!< Set CEC request status. */
#define ClearCECPwrUpFlag() {ucCECReqFlag &= ~CEC_REQ_SYS_POWERUP;}           /*!< Clear CEC request status. */
#define ClearCECPwrDnFlag() {ucCECReqFlag &= ~CEC_REQ_SYS_POWERDOWN;}         /*!< Clear CEC request status. */
#define ClearCECAvtInputFlag() {ucCECReqFlag &= ~CEC_REQ_ACTIVATE_INPUT;}     /*!< Clear CEC request status. */
#define ClearCECInavtInputFlag() {ucCECReqFlag &= ~CEC_REQ_INACTIVATE_INPUT;} /*!< Clear CEC request status. */
#define ClearCECDevCtrlFlag() {ucCECReqFlag &= ~CEC_REQ_DEVICE_CTRL;}         /*!< Clear CEC request status. */
#define ClearCECAllFlag() {ucCECReqFlag = 0x00;}                              /*!< Clear all CEC request status. */

//******************************************************************************
// G L O B A L   V A R I A B L E S
//******************************************************************************

//******************************************************************************
// S T A T I C   V A R I A B L E S
//******************************************************************************
static UCHAR ucDestinationLA;     /*!< CEC initiator. */
static UCHAR ucActiveSource;      /*!< CEC active source. */
static UCHAR ucDeviceCtlCode;     /*!< CEC device control code. */
static UCHAR ucCECReqFlag = 0x00; /*!< CEC request status. */

//******************************************************************************
// E X T E R N A L   V A R I A B L E   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// S T A T I C   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
static UCHAR CEC_Tx(UCHAR Dist,UCHAR Length);
static UCHAR CEC_Rx(void);

//******************************************************************************
// E X T E R N A L   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// F U N C T I O N   B O D Y S
//******************************************************************************

/**************************************************************************//**
 * Transmit CEC data to the specific CEC destination.
 * There is no need to pass the data to scaler through this function.
 * The data are already assigned in the scaler CEC TX buffer.
 * @param des CEC destination.
 * @param length Data length.
 * @return CEC_TX_OK if transmission is succeeded else CEC_TX_FAIL.
 ******************************************************************************/
UCHAR CEC_Tx(UCHAR des,UCHAR length)
{
    UCHAR temp;
    SC_CEC_INT_FLAG = 0x2e; // Clear all status except Rx
    SC_CEC_TX_HEAD = des; // Set destination LA, (initiator LA= 0)
    SC_CEC_TX_LENGTH = length;    //Send CEC data
    while((SC_CEC_INT_FLAG & 0x2e) == 0x00) {    //wait for Tx ready or bus Fail
        ResetWDTimer();
    }
    temp = SC_CEC_INT_FLAG;
    SC_CEC_INT_FLAG = 0x2e;
    if (temp & 0x2c)
        return CEC_TX_FAIL;
    if (temp & 0x02)
        return CEC_TX_OK;
}

/**************************************************************************//**
 * Get the CEC command and send CEC data.
 * @return CEC_RX_OK if CEC bus is not idle or unexpected error.
 ******************************************************************************/
UCHAR CEC_Rx(void)
{
    //UCHAR i,length;
    if (SC_CEC_INT_FLAG & 0x38) {
        SC_CEC_INT_FLAG = 0x38;
        return CEC_BUS_FAIL;
    }
    if (SC_CEC_INT_FLAG & 0x01) {
        if (SC_CEC_RX_LENGTH == 0) {
            SC_CEC_INT_FLAG = 0x01;
            return CEC_IDLE;
        }

        ucDestinationLA = (SC_CEC_RX_HEAD&0xf0)>>4;
        if ((SC_CEC_RX_HEAD & 0x0f) == 0x0f) {    //broadcasting
            switch(SC_CEC_RX_DATA[0]) {
                case CEC_STANDBY:
                    SetCECPwrDnFlag();
                    break;
                case CEC_ACTIVE_SOURCE:    
                    ucActiveSource = ucDestinationLA;
                    if(SC_CEC_RX_DATA[1] != 0)
                        SetCECAvtInputFlag();
                    break;
            };
        }
        else {
            switch(SC_CEC_RX_DATA[0]) {
                case CEC_IMAGE_VIEW_ON:    
                case CEC_TEXT_VIEW_ON:
                    //dont need change source
                    //SetCECAvtInputFlag();
                    break;
                /*
                case CEC_SET_OSD_STRING:
                case CEC_GIVE_DEVICE_VENDOR_ID:
                case CEC_FEATURE_ABORT:
                case CEC_REPORT_PHYSICAL_ADDRESS:
                    break;
                */
                case CEC_INACTIVE_SOURCE:
                    SetCECInavtInputFlag();
                    break;
                case CEC_GIVE_PHYSICAL_ADDRESS:
                    SC_CEC_TX_DATA[0] = CEC_REPORT_PHYSICAL_ADDRESS;
                    SC_CEC_TX_DATA[1] = 0x00;    
                    SC_CEC_TX_DATA[2] = 0x00;    
                    SC_CEC_TX_DATA[3] = 0x00; // TV
                    CEC_Tx(0x0f,4);    //broadcast
                    break;
                case CEC_STANDBY:
                    SetCECPwrDnFlag();
                    break;
                case CEC_GET_MENU_LANGUAGE:
                    SC_CEC_TX_DATA[0] = CEC_SET_MENU_LANGUAGE;
                    SC_CEC_TX_DATA[1] = 'e';
                    SC_CEC_TX_DATA[2] = 'n';
                    SC_CEC_TX_DATA[3] = 'g';
                    CEC_Tx(ucDestinationLA,4);
                    break;
                case CEC_GIVE_DEVICE_POWER_STATUS:
                    SC_CEC_TX_DATA[0] = CEC_REPORT_POWER_STATUS;
                    //Check system power status by ADC power
                    if (IsZpMode() == FALSE){
                        SC_CEC_TX_DATA[1] = 0x00;   //ON
                    }
                    else {
                        SC_CEC_TX_DATA[1] = 0x01;   //Standby
                    }
                    CEC_Tx(ucDestinationLA,2);
                    break;
                case CEC_RECORD_TV_SCREEN:
                    SC_CEC_TX_DATA[0] = CEC_FEATURE_ABORT;
                    SC_CEC_TX_DATA[1] = 0x02;    //Feature abort, can't soupport
                    CEC_Tx(ucDestinationLA,2);
                    break;
                case CEC_ABORT_TEST:
                case CEC_SELECT_DIGITAL_SOURCE:
                    SC_CEC_TX_DATA[0] = CEC_FEATURE_ABORT;
                    SC_CEC_TX_DATA[1] = 0x00;    //Feature abort, unrecognized
                    SC_CEC_TX_DATA[2] = 0x00;    //Feature abort, unrecognized
                    CEC_Tx(ucDestinationLA,3);
                    break;
                case CEC_USER_CONTROL_PRESSED:
                    ucDeviceCtlCode = SC_CEC_RX_DATA[1];
                    SetCECDevCtrlFlag();
                    break;
                default:    
                    break;
            };
        }
        SC_CEC_INT_FLAG = 0x01;
        return CEC_RX_OK;
    }
    return CEC_IDLE;
}

/**************************************************************************//**
 * Initialize CEC-related registers and assign CEC output port.
 * @param port CEC input/output port. 0 or 1, it depends on hardware.
 ******************************************************************************/
void InitialCEC(UCHAR port)
{
    SC_CEC_RXD_RANGE = 40;

#if !(IS_NT68674_SERIES || IS_NT68770_SERIES || IS_NT68850_SERIES || IS_NT68790_SERIES)
    SC_CEC_CTRL = 0x01;
    
	#if IS_NT68360_SERIES
    	SC_MCU_IO_CTRL2 = (SC_MCU_IO_CTRL2 & 0x3C) | ((port==1) ? 0x01 : 0x40);
    #elif IS_NT68750_SERIES
	    switch (port) {
	        case 0:
	            SC_MCU_IO_CTRL3 = (SC_MCU_IO_CTRL3 & 0xFC) | 0x02;
	            break;
	        case 1:
	            SC_MCU_IO_CTRL4 = (SC_MCU_IO_CTRL4 & 0x3F) | 0x40;
	            break;
	    }
    #else
    	SC_CEC_OUTPUT_SELECT = (0x01<<port)&0x0F;
    #endif

#elif IS_NT68770_SERIES
    SC_CEC_CTRL = 0x01;
    SC_MCU_IO_CTRL3 = (SC_MCU_IO_CTRL3&0xFC)|0x01; 
	port = port;
#elif IS_NT68850_SERIES || IS_NT68790_SERIES
    SC_CEC_CTRL = 0x01;
    SC_MCU_IO_CTRL4 = (SC_MCU_IO_CTRL4&0xFC)|0x01; 
	port = port;
#else
    if (port == 0) {
        SC_CEC_CTRL = 0x07;
    }
    else {
        SC_CEC_CTRL = 0x0b;
    }
#endif
    SC_CEC_INT_FLAG = 0xff;
    
    ucDestinationLA = 0x0f;
    ucActiveSource = 0x0f;
    ucDeviceCtlCode = 0xff;
    CECUpdateRefClock();
}

/**************************************************************************//**
 * CEC Handler.
 * @return CEC requests.
 ******************************************************************************/
CECRequest CECHandler(void)
{
    CECRequest request = CECATN_NONE;
    if (CEC_Rx() == CEC_RX_OK) {
        if (IsCECPwrUp()) {
            request = CECREQ_POWERUP;
        } 
        else if (IsCECPwrDn()) { 
            request = CECREQ_POWERDOWN;
        }
        else if (IsCECAvtInput()) {
            request = CECREQ_ACTIVATE_SC;
        } 
        else if (IsCECInavtInput()) {
            request = CECREQ_INACTIVATE_SC;
        } 
        else if (IsCECDevCtrl()) {
            request = CECREQ_DEVCTRL;
        }
        ClearCECAllFlag();
    }
    return request;
}

/**************************************************************************//**
 * Set number of reference clock (12MHz or 14.318MHz) counts of CEC clock unit (10us).
 ******************************************************************************/
void CECUpdateRefClock(void)
{
    UCHAR divider = 0;
    
    divider = (SC_MCU_CLK_DIVIDER&0x03);
    
    if (divider == 0) {
        // Get basic counter without applying clock divider.
        SC_CEC_CLK_BASE = (REF_CLK/100000);
    }
    else {
        SC_CEC_CLK_BASE = (REF_CLK/100000) >> divider;
    }
}

/**************************************************************************//**
 * Get active source of CEC command.
 * @return Active source.
 ******************************************************************************/
/*
UCHAR CECGetActiveSC(void)
{
    return ucActiveSource;
}
*/

/**************************************************************************//**
 * Get CEC device control code.
 * @return CEC device control code.
 ******************************************************************************/
UCHAR CECGetDeviceCtlCode(void)
{
    return ucDeviceCtlCode;
}

/**************************************************************************//**
 * Broadcast CEC standby command to other CEC compliance devices.
 ******************************************************************************/
void CECSetStandby(void)
{
    SC_CEC_TX_DATA[0] = CEC_STANDBY;
    CEC_Tx(0x0f,1); // Broadcast command.
}

/**************************************************************************//**
 * Broadcast CEC "set language" command to other CEC compliance devices.
 * @param lang System language ID.
 ******************************************************************************/
void CECSetOSDLanguage(CECLanguage lang)
{
    code UCHAR ucCECLanguageCode[NUM_CEC_LANGUAGE][3] = {
        "eng",//CECLANG_ENGLISH,
        "spa",//CECLANG_SPANISH,
        "fra",//CECLANG_FRENCH,
        "ger",//CECLANG_GERMAN,
        "ita",//CECLANG_ITALIAN,
        "por",//CECLANG_PORTUGUESE,
        "rus",//CECLANG_RUSSIAN,
        "zho",//CECLANG_SCHINESE,
        "swe",//CECLANG_SWEDISH,
        "pol",//CECLANG_POLISH,
        "cze",//CECLANG_CZECH,
        "kor",//CECLANG_KOREAN,
        "zho",//CECLANG_TCHINESE,
        "jpn",//CECLANG_JAPANESE,
        "dut",//CECLANG_DUTCH,
        "fin",//CECLANG_FINNISH,
    };

    SC_CEC_TX_DATA[0] = CEC_SET_MENU_LANGUAGE;
    SC_CEC_TX_DATA[1] = ucCECLanguageCode[lang][0];
    SC_CEC_TX_DATA[2] = ucCECLanguageCode[lang][1];
    SC_CEC_TX_DATA[3] = ucCECLanguageCode[lang][2];
    CEC_Tx(0x0f,4);    //broadcast
}
#endif //ENABLE_HW_CEC == ON
