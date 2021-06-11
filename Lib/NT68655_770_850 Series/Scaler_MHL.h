/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/

#ifndef __MHL_API_H__
#define __MHL_API_H__

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************
 
//******************************************************************************
// M A C R O   D E F I N I T I O N S
//******************************************************************************
// intergated these definitions into falcon
#define MHL_GetCbusCH()  (SC_CBUS_CHANNEL_SEL & BIT0)  /*!< CBUS Channel=0 or 1. */
#define MHL_SetCbusCH(x) {SC_CBUS_CHANNEL_SEL = (SC_CBUS_CHANNEL_SEL & 0xfe) | x; \
                                                   SC_CBUS_INT_EN = 0xF0 | CBUS_INT_MASK; }  /*!< Set CBUS Channel=0 or 1, it cause interrupt occurred */
#define MHL_IsCDSenseFlagOn() ((SC_CBUS_DIS_INT_MASK & CDSENSE_INT_FLG) !=0 )
#define MHL_IsDiscoveryFlagOn() ((SC_CBUS_DIS_INT_MASK & (CDSENSE_INT_FLG | CBUS_CONN_INT_FLG))== \
                                (CDSENSE_INT_FLG | CBUS_CONN_INT_FLG))
#define MHL_IsDisconnFlagOn() ((SC_CBUS_DIS_INT_MASK & STUCKLOW_INT_FLG) !=0 )
#define MHL_IsMHLPathEnable()  ((SC_MHL_CTRL_2E0 & BIT7)!=0)
#define MHL_IsMHLInput()             ((SC_HDMI_MHL_MODE_DETECT & BIT7) != 0)
//#define MHL_WaitCBusReady()   {while((SC_CBUS_TRANS_FLAG1 & 0x40) == 0);}
#define MHL_GetMSCCmd() (SC_CBUS_TRANS_FLAG0 & (MSC_CMD_READ_VALID | MSC_DATA_READ_VALID))
#define MHL_GetDDCCmd() (SC_CBUS_TRANS_FLAG0 & (DDC_CMD_READ_VALID | DDC_DATA_READ_VALID))

#define MHL_SetPackedPixelMode() { SC_MHL_CTRL_2E0 |= BIT6; }
#define MHL_Set24bitMode() { SC_MHL_CTRL_2E0 &= ~BIT6; }
#define MHL_IsPackedPixelMode() ( (SC_MHL_CTRL_2E0&BIT6)!=0 )

//******************************************************************************
// D A T A   T Y P E   D E F I N E S
//******************************************************************************

//******************************************************************************
// V A R I A B L E S   P R O T O T Y P E
//******************************************************************************

//******************************************************************************
// F U N C T I O N   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// E X T E R N A L   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
extern void MHLCDSense1On(void);
extern void MHLCDSense2On(void);
#if IS_NT68770_SERIES
extern BOOL MHL_Is_CDSense1_IO_HIGH();
extern BOOL MHL_Is_CDSense2_IO_HIGH();
#endif
extern void MHLCBus1On(void);
extern void MHLCBus1Off(void);
extern void MHLCBus2On(void);
extern void MHLCBus2Off(void);
extern BOOL MHLIsCBus1On(void);
extern BOOL MHLIsCBus2On(void);
extern void MHL_EnableVBus1(void);
extern void MHL_DisableVBus1(void);
extern void MHL_Set_VBus1_IO_On(void);
extern void MHL_Set_VBus1_IO_Off(void);
extern void MHL_EnableVBus2(void);
extern void MHL_DisableVBus2(void);
extern void MHL_Set_VBus2_IO_On(void);
extern void MHL_Set_VBus2_IO_Off(void);
extern BOOL MHLSetInterface(UCHAR interface);
extern void MHLPackedPixelMode(BOOL On);
extern UCHAR MHLCbusTx(UCHAR type, UCHAR d);
extern BOOL CBUSTxData(UCHAR type, UCHAR d);
extern void MHL_SetCBus1DrvCurrent(void);
extern void MHL_SetCBus2DrvCurrent(void);
extern void MHL_SetCBus1K(void);
extern void MHL_EnhanceCompatibility(void);
extern void MHL_WaitCBusReady(void);

#endif //__MHL_API_H__
