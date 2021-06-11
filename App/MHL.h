/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/
#ifndef __MHL_H__
#define __MHL_H__

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************
#include "Typedef.h"

//******************************************************************************
// M A C R O   D E F I N I T I O N S
//******************************************************************************
#define HDCP_PAGE_ADDR		0x8600
#define SET_HPD_TIMER          300
#define HPD_CLR_SET_TIMER  100
#define CBUS_BUF_LEN            40
#define CBUS_IDLE_TIMEOUT   9000//10000
#define CBUS_TPKT_TIMEOUT   100
#define CBUS_AA_TIMEOUT     1950//CTS 2.0 ACK & ABORT timeout
// --------------------------------------------------------------------------------
//  DEBUG_STAGE:  these definitions can be remove in release version
// --------------------------------------------------------------------------------
#define ENABLE_VBUS_IO_CONTROL (IS_NT68770_SERIES)
#define ENABLE_MHL_CTS_TEST 0
//#define MHL_CTS_DEBUG_TEST1 //reset MHL if CBUS_LOW for 500ms
//#define MHL_CTS_DEBUG_TEST2 // CTS 4.3.18.1: sol: when get 0x2B0.0, add 0x2c1, 0x2c2 by one
#if defined(MHL_CTS_DEBUG_TEST2)
#define CBUS_INT_MASK (0x00|DISC_INT_MASK) //enable link layer
#else
#define CBUS_INT_MASK (0x02|DISC_INT_MASK) //disable link layer
#endif

#define ENABLE_INT_TRANSLATION  ON
#define ENABLE_INT_DISCOVERY    OFF
#if ENABLE_INT_DISCOVERY == ON
    #define DISC_INT_MASK 0x02
#else
    #define DISC_INT_MASK 0x03
#endif

#define DEF_BIT_TIME_THD_LO 0x09
#define DEF_BIT_TIME_THD_HI 0x0F


//******************************************************************************
// G L O B A L   D E F I N I T I O N S
//******************************************************************************
typedef enum _MHL_CBUS_CH_ {
    MHL_CBUS_CH1,
    MHL_CBUS_CH2,
    MHL_CBUS_NUM
}MHLCBUSCH;

/*!< MHL Connection Status  */
typedef enum _MHL_STATUS_ {
    MHL_NONE,
    MHL_DISCOVERY_RDY,
    MHL_CONNECT_RDY,
    MHL_SET_HPD,
    MHL_PATH_EN,
    MHL_DATA_RDY,
    MHL_CLR_HPD
}MHLSTATUS;

/*!< CBUS Connection Status  */
typedef enum _CBUS_STATUS_ {
    CBUS_UNKNOWN = 0xFF,
    CBUS_UNACTIVE = 0x00,
    CBUS_DISCOVERY_DONE = 0x01,
    CBUS_SETHPD = 0x02,
    CBUS_MSG_RCPK = 0x06,
    CBUS_CLRHPD = 0x0E,
    CBUS_ACTIVE = 0x0F,
    CONNECTED_RDY = 0x30,
    LINK_MODE = 0x31,
    RCHANGE_INT = 0x20,
    RDEV_VER = 0x10,
    RDEV_CAT = 0x11,
    RDEV_LOG = 0x12,
    RDEV_VID_LINK = 0x13,
    RDEV_VIDEO_TYPE = 0x14,
    RDEV_BANDWIDTH = 0x15,
    RDEV_AUDIO = 0x16,
}CBUSSTATUS;

//CDF define
#define CDF_MHL_VER             0x20    //define by CDF: MHL_VER_MAJOR=1, MHL_VER_MINOR=2
#define CDF_DEV_CAT             0x31    //define by CDF: DEV_TYPE[0..3]=1, POW = 900mA
#define CDF_ADOPTER_ID_H        0x02    //define by CDF
#define CDF_ADOPTER_ID_L        0x1C    //define by CDF
#define CDF_VID_LINK_MODE       0x3F    //define by CDF: SUPP_RGB444, SUPP_YCBCR444, SUPP_ YCBCR422, SUPP_PPIXEL, SUPP_ISLANDS, SUPP_VGA
#define CDF_AUD_LINK_MODE       0x03    //define by CDF: AUD_2CH, AUD_8CH
#define CDF_VIDEO_TYPE          0x8F    //define by CDF: VT_GRAPHICS, VT_PHOTO, VT_CINEMA, VT_GAME, SUPP_VT
#define CDF_LOG_DEV_MAP         0x80    //define by CDF: LD_DISPLAY, LD_VIDEO, LD_AUDIO, LD_MEDIA, LD_TUNER, LD_RECORD, LD_SPEAKER, LD_GUI
#define CDF_BANDWIDTH           15      //define by CDF: 15x5 =75MHz
#define CDF_FEATURE_FLAG        0x1F       //define by CDF: UCP_RECV_SUPPORT, UCP_SEND_SUPPORT, RCP_SUPPORT, RAP_SUPPORT, SP_SUPPORT
#define CDF_DEVICE_ID_H         0xFF    //define by CDF
#define CDF_DEVICE_ID_L         0xFF    //define by CDF
#define CDF_SCRATCHPAD_SIZE     16//64      //define by CDF (change to 16 for 6.3.11.19 CBM: DUT Receives (0x6C) WRITE_BURST - Too Much Data.)
#define CDF_INT_STAT_SIZE       0xFF    //define by CDF

typedef enum _CBUS_DDC_STATUS_ {
    CBUS_DDC_EOF = 0,
    CBUS_DDC_SOF,//1
    CBUS_DDC_DevAddr,//2
    CBUS_DDC_Offset,//3
    CBUS_DDC_Data,//4 CONT or Data
    CBUS_DDC_Stop,//5
}CBUSDDCSTATUS;

typedef enum _DEVICE_CAP {
    DEVCAP_DEVSTATE = 0x00,
    DEVCAP_MHLVERSION,
    DEVCAP_DEVCAT,
    DEVCAP_ADOPTERIDH,
    DEVCAP_ADOPTERIDL,
    DEVCAP_VIDLINKMODE,
    DEVCAP_AUDLINKMODE,
    DEVCAP_VIDEOTYPE,
    DEVCAP_LOGDEVMAP,
    DEVCAP_BANDWIDTH,
    DEVCAP_FEATUREFLAG,
    DEVCAP_DEVICEIDH,
    DEVCAP_DEVICEIDL,
    DEVCAP_SCRATCHPADSIZE,
    DEVCAP_INSTATSIZE
}DEVICECAP;

typedef enum {
    MHL_MSC_MSG_MSGE            = 0x02,     // MSC_MSG Error sub-command
    MHL_MSC_MSG_RCP             = 0x10,     // RCP sub-command
    MHL_MSC_MSG_RCPK            = 0x11,     // RCP Acknowledge sub-command
    MHL_MSC_MSG_RCPE            = 0x12,     // RCP Error sub-command
    MHL_MSC_MSG_RAP             = 0x20,     // RAP sub-command
    MHL_MSC_MSG_RAPK            = 0x21,     // RAP Acknowledge sub-command
    MHL_MSC_MSG_UCP             = 0x30,     // UTF-8 character protocol sub-command
    MHL_MSC_MSG_UCPK            = 0x31,     // UCP Acknowledge sub-command
    MHL_MSC_MSG_UCPE            = 0x32,     // UCP Error sub-command
};

#define    TX_MSC_CMD		0x10
#define	 TX_MSC_DATA		0x11
#define    TX_DDC_CMD		0x20
#define    TX_DDC_DATA		0x21

// DDC and MSC Commands
#define    CBUS_SOF					0x30	// Start of Frame
#define	 CBUS_EOF					0x32	// End of Frame														(7.4.3.10)
#define	 CBUS_ACK					0x33	// Command/Data byte acknowledged						 		(7.3.1.1)
#define	 CBUS_NACK					0x34	// Command/Data byte not acknowledged 							(7.3.1.2)
#define	 CBUS_ABORT				0x35	// Transaction abort													(7.3.1.3)
#define	 CBUS_CONT					0x50	// The transfer keeps going.
#define 	 CBUS_STOP					0x51	// The transfer approaches to end.
#define	 CBUS_WRITE_STAT			0x60	// Write one byte to responder's status bytes 				(7.4.3.8)
#define	 CBUS_SET_INT				0x60	// Write one or more interrupt bits in a byte 				(7.4.3.9)
#define	 CBUS_READ_DEVCAP			0x61	// Read one byte from responder's registers.					(7.4.3.7)
#define	 CBUS_GET_STATE			0x62	// Read state from responder.										(7.4.3.1)
#define	 CBUS_GET_VENDOR_ID		0x63	// Read vendor ID value from responder.						(7.4.3.2)
#define	 CBUS_SET_HPD				0x64	// Set Hot Plug Detect in responder.							(7.4.3.3)
#define	 CBUS_CLR_HPD				0x65	// Clear Hot Plug Detect in responder.							(7.4.3.4)
#define	 CBUS_MSC_MSG				0x68	// Send RCP or RAP code.											(7.4.3.11)
#define	 CBUS_GET_SC1_ERRORCODE	0x69	// Get channel 1 command error code.			
#define	 CBUS_GET_DDC_ERRORCODE	0x6A	// Get DDC channel command error code.							(7.4.3.5)
#define	 CBUS_GET_MSC_ERRORCODE	0x6B	// Get MSC command error code.									(7.4.3.6)
#define	 CBUS_WRITE_BURST			0x6C	// Write 1-16 bytes to responder's Scratchpad Registers.	(7.4.3.10)
#define	 CBUS_GET_SC3_ERRORCODE	0x6D	// Get channel 3 command error code.

#define	 CBUS_EDID_WRITE			0xA0
#define	 CBUS_EDID_READ			0xA1
#define	 CBUS_HDCP_WRITE			0x74
#define	 CBUS_HDCP_READ			0x75
#define	 CBUS_SEG_WRITE			0x60		// Segment Read

//7.4.1 error
#define	CBUS_NORMAL                 0x00
#define	ERROR_CBUS_CAN_RETRY        0x01
#define	ERROR_CBUS_POTOCOL          0x02
#define	ERROR_CBUS_TIMEOUT          0x04
#define	ERROR_INVALID_OP_CODE       0x08
#define	ERROR_BAD_OFFSET            0x10
#define	ERROR_PEER_IS_BUSY          0x20

#define    cMSCCmd			ucCbusBuffer[0]
#define	 cMSCOffset		       ucCbusBuffer[1]
#define    cMSCValue		       ucCbusBuffer[2]

//******************************************************************************
// G L O B A L   V A R I A B L E S
//******************************************************************************
extern idata UCHAR ucCmdIndex;
extern UCHAR ucIsMHLSrcConnected[];
extern BOOL bCheckTimeout;
extern BOOL bCBUSAbort;
extern BOOL bTranCMD;
extern idata UCHAR ucCBUSCMDTxBuffer;
#if 1//def E_DEBUG
extern BOOL bCBusArbFailFlag;
#endif

//******************************************************************************
// E X T E R N A L   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
extern void MHLInit(void);
extern void SetCbusChannel(void);
extern void CbusDiscoveryHandler(void);
extern void IntMHLStatus(void);
extern void CbusHandler(void);
extern void CbusMSCCmdHandler(void);
extern void CbusDDCCmdHandler(void);
extern void MHLHandler();
extern void SetCbusConnectStatus(UCHAR status);
extern UCHAR GetCbusConnectStatus(void);
extern void MSCCmdTranslation(void);
extern UCHAR HDCPAddrRemaping(UCHAR offset);
extern void MHL_HDCP_SendData();
extern void DDCTranslation(UCHAR RxData);
extern BOOL IsMHL0Connect(void);
extern BOOL IsMHL1Connect(void);
extern void MHLClearHPD(void);
extern void MHLResetHPD(void);
extern BOOL MHLIsClearHPD(void);
extern void ToggleRxSense(void);
extern BOOL MHLIsCBus1Active(void);
extern BOOL MHLIsCBus2Active(void);
extern BOOL IsMHL0CableConnect(void);
extern BOOL IsMHL1CableConnect(void);
#endif 
