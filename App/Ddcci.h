/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/
#ifndef __DDCCI_H__
#define __DDCCI_H__

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************
#include "Typedef.h"

//******************************************************************************
// G L O B A L   D E F I N I T I O N S
//******************************************************************************
#define ACCESSBUS_ADDR          0x6E

#define CMDOP_GET_VCP           0x01
#define CMDOP_VCP_RPL           0x02
#define CMDOP_SET_VCP           0x03
#define CMDOP_GET_TIMING        0x07
#define CMDOP_SAVE              0x0c
#define CMDOP_SET_CAP           0xf3

#define VCPOP_NEW_CTRL          0x02
#define VCPOP_RECALL            0x04
#define VCPOP_RECALL_BC         0x05
#define VCPOP_RECALL_HV_POS     0x06
#define VCPOP_RECALL_COLOR      0x08
#define VCPOP_COLOR_INC         0x0B
#define VCPOP_COLOR_REQ         0x0C
#define VCPOP_CLOCK             0x0E
#define VCPOP_BRIGHT            0x10
#define VCPOP_CONTRAST          0x12
#define VCPOP_SEL_COLOR         0x14
#define VCPOP_RGAIN             0x16
#define VCPOP_GGAIN             0x18
#define VCPOP_BGAIN             0x1A
#define VCPOP_AUTO_SET          0x1E
#define VCPOP_AUTO_COLOR        0x1F
#define VCPOP_H_POS             0x20
#define VCPOP_V_POS             0x30
#define VCPOP_H_PHASE           0x3E
#define VCPOP_ACTIVE_CTRL       0x52
#define VCPOP_INPUT             0x60
#define VCPOP_AUDIO             0x62
#define VCPOP_DDC_DATA          0x63
#define VCPOP_ROFFSET           0x6C
#define VCPOP_GOFFSET           0x6E
#define VCPOP_BOFFSET           0x70
#define VCPOP_MUTE              0x8D
#define VCPOP_H_FREQ            0xAC
#define VCPOP_V_FREQ            0xAE
#define VCPOP_PANEL_PIXEL       0xB2
#define VCPOP_DISP_TYPE         0xB6
#define VCPOP_USE_TIME          0xC0
#define VCPOP_APP_KEY           0xC6
#define VCPOP_CTRL_TYPE         0xC8
#define VCPOP_FW_LEVEL          0xC9
#define VCPOP_OSD_LOCK          0xCA
#define VCPOP_LANGUAGE          0xCC
#define VCPOP_POWER_MODE        0xD6
#define VCPOP_SMARTIMAGE        0xDC
#define VCPOP_MCC20             0xDF
#define VCPOP_END               0xFF

#define VCPOP_NVT_HDCP_START    0xED
#define VCPOP_NVT_HDCP_WRITE    0xEE
#define VCPOP_NVT_HDCP_CHKSUM   0xEF

//******************************************************************************
// E X T E R N A L   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
extern BOOL DDCCIUserUpdate(void);
extern BOOL DDCCITmgUpdate(void);
extern BOOL DDCCISysUpdate(void);
extern BOOL DDCCICalUpdate(void);
extern BOOL DDCCIPwrOn(void);
extern BOOL DDCCIPwrOff(void);
extern BOOL DDCCIPwrSaving(void);
extern void DDCCiUpdateNotice(void);
extern void CheckDDC2Bi(void);

#endif //__DDCCI_H__
