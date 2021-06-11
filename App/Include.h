/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/
#ifndef __INCLUDE_H__
#define __INCLUDE_H__

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************
#include <intrins.h>
#include <math.h>
#include <stdio.h>
#include "ChiuDef.h"					// \APP
#include "3D.h"							// \APP
#include "APPCtrl.h"					// \APP
#include "AutoAdj.h"					// \Lib
#include "AutoAdjConfig.h"				// \Sys
#include "Board.h"						// \Phy\SI\NVT\Board
#include "CEC.h"						// \Lib
#include "ColorConfig.h"				// \App
#include "ColorEngine.h"				// \Lib,  \Lib\ColorEngine\INC, \Lib\ColorEngine\Release
#include "Component.h"					// 
#include "Ddcci.h"
#include "DdcciCtrl.h"
#include "Event.h"
#include "EventHandle.h"
#include "FOSDView.h"
#include "DemoOSDView.h"
#include "InputTiming.h"
#include "Int.h"
#include "KeyCtrl.h"
#include "KeyPad.h"
#include "Logo.h"
#include "Mcu.h"
#include "McuAPI.h"
#include "McuReg.h"
#include "Misc.h"
#include "ModeConfig.h"
#include "ModeHandler.h"	//
#include "ModeSearch.h"
#include "ModeTable.h"
#include "ModelCfg.h"
#include "NR.h"
#include "Nvram.h"
#include "NvramIIC.h"		//
#include "OSDAPI.h"
#include "OSDAPI_Common.h"
#include "OSDAPI_Indent.h"
#include "OSDCtrl.h"
#include "OSDFont.h"
#include "OSDFunc.h"
#include "OSDIndex.h"
#include "OSDType.h"
#include "OSDView.h"

#include "Panel.h"

#include "Ram.h"			//
#include "Scaler.h"
#include "ScalerAccess.h"
#include "ScalerReg.h"
#include "SyncHandler.h"
#include "SysAPI.h"
#include "Typedef.h"
#include "UserDefault.h"
#include "UserSetting.h"
#include "Utilities.h"
//Optional Header Files
#if ENABLE_DBC == ON
#include "DBCAPI.h"
#include "DBC.h"
#endif
#if ENABLE_EMBEDDED_CHECKSUM == ON
#include "EmbedCheckSum.h"
#endif
#if ENABLE_FE2P == ON
#include "FE2P_API.h"
#endif
#if ENABLE_GAMMA == ON
#include "GammaAPI.h"
#include "Gamma.h"
#endif
#if ENABLE_HDCP == ON
#include "HDCPAPI.h"
#include "HDCP.h"
#endif
#if ENABLE_LD == ON
#include "LDAPI.h"
#include "LD.h"
#endif
#if ENABLE_OD == ON
#include "ODAPI.h"
#include "OD.h"
#endif
#if ENABLE_SR == ON
#include "SRAPI.h"
#include "SR.h"
#endif
#if ENABLE_OD_TRANSFORM == ON
#include "ODTransform.h"
#endif

#if (INPUT_INTERFACE&INPUT_MHL0) || (INPUT_INTERFACE&INPUT_MHL1)
#include "MHL.h"
#endif

#if (INPUT_INTERFACE&INPUT_DP)
#include "Scaler_DP_Common.h"
#include "Scaler_DP.h"
#endif


#if (XRS232 == ADS_RS232)			//150723  George 
	#include "XRS232_APP.h"
#elif (XRS232 == LWO_RS232)
	#include "XRS232_LWO_APP.h"
#endif


#if ALS_EnDis == ALSMODE		//150723  George 
	#include "CM3218_ALSMode.h"
#elif ALS_EnDis == ALSOffSET	
	#include "CM3218_ALSOffset.h"
#elif ALS_EnDis == ALSRange
	#include "LS3101_ADS.h"
#endif	//#if ALS_EnDis == ENABLE


#if IR_REMOT_CTL == ENABLE				//150511  George 
#include "IR.h"
#endif


//******************************************************************************
// G L O B A L   D E F I N I T I O N S
//******************************************************************************

//******************************************************************************
// G L O B A L   V A R I A B L E S
//******************************************************************************

//******************************************************************************
// S T A T I C   V A R I A B L E S
//******************************************************************************
static USHRT second = 0;     //FEFANJACKY FOR TIMERCOUNTER
static USHRT minute = 0;
static USHRT hour = 0;
//******************************************************************************
// E X T E R N A L   V A R I A B L E   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// S T A T I C   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// E X T E R N A L   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************

#endif //__INCLUDE_H__
