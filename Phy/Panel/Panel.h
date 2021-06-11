/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/
#ifndef __PANEL_H__
#define __PANEL_H__

//******************************************************************************
// G L O B A L   D E F I N I T I O N S
//******************************************************************************
// Panel vendor list
#define AUO 0x10
#define CMO 0x20
#define CPT 0x30
#define DataImage 0x31			//150109 mike 
#define INL 0x40
#define IVO 0x50
#define LPL 0x60
#define SEC 0x70
#define TPV 0x80
#define BOE 0x90
#define PET 0xA0  									//150105 mike 
#define SRP 0xB0				//150907 george Sharp
#define NVT 0xF0


// Pane resolution list
#define RES_1024X768  0x01
#define RES_1280X1024 0x02
#define RES_1366X768  0x03
#define RES_1400X1050 0x04
#define RES_1440X900  0x05
#define RES_1600X900  0x06
#define RES_1680X1050 0x07
#define RES_1920X1080 0x08
#define RES_1920X1200 0x09
#define RES_2560X1440 0x0A
#define RES_640X480   0x0B		//george
#define RES_1280X800  0x0C		//george
#define RES_1280X768  0x0D		//george

#define PANEL_VENDOR  (PANEL_TYPE&0xF0)
#define IS_AUO_PANEL  ((PANEL_TYPE&0xF0) == AUO)
#define IS_CMO_PANEL  ((PANEL_TYPE&0xF0) == CMO)
#define IS_CPT_PANEL  ((PANEL_TYPE&0xF0) == CPT)
#define IS_INL_PANEL  ((PANEL_TYPE&0xF0) == INL)
#define IS_IVO_PANEL  ((PANEL_TYPE&0xF0) == IVO)
#define IS_LPL_PANEL  ((PANEL_TYPE&0xF0) == LPL)
#define IS_SEC_PANEL  ((PANEL_TYPE&0xF0) == SEC)
#define IS_TPV_PANEL  ((PANEL_TYPE&0xF0) == TPV)
#define IS_BOE_PANEL  ((PANEL_TYPE&0xF0) == BOE)
#define IS_NVT_PANEL  ((PANEL_TYPE&0xF0) == NVT)
#define IS_PET_PANEL  ((PANEL_TYPE&0xF0) == PET)					//150105 mike
#define IS_SRP_PANEL  ((PANEL_TYPE&0xF0) == SRP)					//150907 george
#define IS_DataImage_PANEL  ((PANEL_TYPE&0xF0) == DataImage)		//150108 mike

#define PANEL_RESOLUTION   (PANEL_TYPE&0x0F)
#define IS_1024X768_PANEL  ((PANEL_TYPE&0x0F) == RES_1024X768 )
#define IS_1280X1024_PANEL ((PANEL_TYPE&0x0F) == RES_1280X1024)
#define IS_1366X768_PANEL  ((PANEL_TYPE&0x0F) == RES_1366X768 )
#define IS_1400X1050_PANEL ((PANEL_TYPE&0x0F) == RES_1400X1050)
#define IS_1440X900_PANEL  ((PANEL_TYPE&0x0F) == RES_1440X900 )
#define IS_1600X900_PANEL  ((PANEL_TYPE&0x0F) == RES_1600X900 )
#define IS_1680X1050_PANEL ((PANEL_TYPE&0x0F) == RES_1680X1050)
#define IS_1920X1080_PANEL ((PANEL_TYPE&0x0F) == RES_1920X1080)
#define IS_1920X1200_PANEL ((PANEL_TYPE&0x0F) == RES_1920X1200)
#define IS_2560X1440_PANEL ((PANEL_TYPE&0x0F) == RES_2560X1440)
#define IS_640X480_PANEL ((PANEL_TYPE&0x0F) == RES_640X480)
#define IS_1280X800_PANEL ((PANEL_TYPE&0x0F) == RES_1280X800)
#define IS_1280X768_PANEL ((PANEL_TYPE&0x0F) == RES_1280X768)

#define PANEL_INSERT_BLACK          0x01
#define PANEL_INSERT_WHITE          0x02
#define PANEL_POWER_LVDS_SWAP       0x04
#define PANEL_PWR_SEQ_DEFAULT       0xFF


//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************


//CHIU DEFINE ALL INCALUDE DATA
 //-----------------------------------------	06N		//150907 george
#if defined(SRP_LQ064V3DG01)				
	#include "SRP_LQ064V3DG01\Panel.h" 

//-----------------------------------------	07W		//150108 mike
#elif defined(D_FG0700A2DSSWBG02)				
	#include "D_FG0700A2DSSWBG02\Panel.h" 
#elif defined(AUO_G070VW01_V0)
	#include "AUO_G070VW01_V0\Panel.h"		
#elif defined(SGD_GVTW70SNAD1E0)
	#include "SGD_GVTW70SNAD1E0\Panel.h"			//160106 george
//------------------------------------	10"
#elif defined(CMO_G104X1_L04)				
	#include "CMO_G104X1_L04\Panel.h"	   			//150813 george

#elif defined(IVO_M101NWWB_R3)				
	#include "IVO_M101NWWB_R3\Panel.h"	   			//160309 george
//------------------------------------		15"
#elif defined(AUO_G151EVN01_720)				
	#include "AUO_G151EVN01_720\Panel.h"
#elif defined(AUO_G151EVN01_1024)	
       #include "AUO_G151EVN01_1024\Panel.h"	
#elif defined(AUO_G150XTN05_V0)
	#include "AUO_G150XTN05_V0\Panel.h"   			//15" 140515 mike 		   
//------------------------------------		17"
#elif defined (AUO_G170ETN01_V0)
	#include "AUO_G170ETN01_V0\Panel.h"					//140303  mike

#elif defined (TRULY_TFT1280120)
	#include "TRULY_TFT1280120\Panel.h"				//george

//------------------------------------		17.3"
#elif defined (PET_OT173ZFDDLN_00)
	#include "PET_OT173ZFDDLN_00\Panel.h"				//150202 mike 1920x1080

//------------------------------------		19W"
#elif defined (LWO_EWK_1902C)
	#include "LWO_EWK-1902C\Panel.h"					//160223 george 1920x360
//------------------------------------          215"
#elif defined(LG_LM215WF3_SLK1)				
	#include "LG_LM215WF3-SLK1\Panel.h"
#elif defined(LG_LM215WF3_SLC1)				
	#include "LG_LM215WF3-SLC1\Panel.h"
#elif defined(PET_OT215ZFWDLV_02)				
	#include "PET_OT215ZFWDLV_02\Panel.h"				//150105 mike 
//------------------------------------		22"ÿ
#elif defined (CMO_M220ZGE_L20)
#include "CMO_M220ZGE_L20\Panel.h"
//------------------------------------		23"
#elif defined(LG_LM230WF3_SLD1)				
	#include "LG_LM230WF3_SLD1\Panel.h"
//------------------------------------		27"
#elif defined(AUO_P270HVN010)					
	#include "AUO_P270HVN010\Panel.h"	
#elif defined(LG_LM270WF5_SLM1)					
	#include "LG_LM270WF5_SLM1\Panel.h"	
//------------------------------------   	29"		//151117 george
#elif defined(INL_S290AJ1_LE1)	
	#include "INL_S290AJ1-LE1\Panel.h"
//------------------------------------		32"		
#elif defined(LC320WXN_SCA4)				
	#include "LC320WXN_SCA4\Panel.h"	
#elif defined(LC320EUN_SEM2)				
	#include "LC320EUN_SEM2\Panel.h"
#elif defined(LD320EUN_SEM1)				
	#include "LD320EUN_SEM1\Panel.h"	
//------------------------------------	        38"
#elif defined(TX38D09VM0CAA)				
	#include "TX38D09VM0CAA\Panel.h"	
//------------------------------------	        42"
#elif defined(LC420EUN_SFM1)				
	#include "LC420EUN_SFM1\Panel.h"	
//----------------------------------------- 	  46"
#elif defined(AUO_P460HVN03_V0)
       #include "AUO_P460HVN03_V0\Panel.h"				 //141211 mike		
//------------------------------------	        55"
#elif defined(LC550EUN_SFM2)				
	#include "LC550EUN_SFM2\Panel.h"

#endif


#ifndef PANEL_TYPE
#error "Please choose one panel at least!"
#endif
#if (PANEL_MIN_VTOTAL <= (PANEL_HEIGHT + PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACKPORCH))
#error "Wrong PanelVTotal setting! Please review it!"
#endif

#ifndef PANEL_FOUR_PORT_LVDS
#define PANEL_FOUR_PORT_LVDS 0
#endif
#ifndef PANEL_LVDS_OFFSET
#define PANEL_LVDS_OFFSET 0
#endif
#ifndef PANEL_TEN_BIT_SHIFT
#define PANEL_TEN_BIT_SHIFT 0
#endif
#ifndef PANEL_FOUR_PORT_SWAP
#define PANEL_FOUR_PORT_SWAP 0
#endif
#ifndef PANEL_PWR_OFF_SEQUENCE_MODE
#define PANEL_PWR_OFF_SEQUENCE_MODE   PANEL_INSERT_WHITE
#endif

typedef struct {
    UCHAR ucLVDS_Swing : 5;
    UCHAR bDualPortLVDS : 1;
    UCHAR bEnableSSC : 1;
    UCHAR bDEMode : 1;
    UCHAR bPortSwap : 1;
    UCHAR bBitShift : 1;
    UCHAR ucColorDepth;
    USHRT usWidth;
    USHRT usHeight;
    ULONG ulMinPClk;
    ULONG ulMaxPClk;
    USHRT usMinHTotal;
    USHRT usTypHTotal;
    USHRT usMaxHTotal;
    USHRT usMinHSyncWidth;
    USHRT usMinHSyncBackPorch;
    USHRT usMinVTotal;
    USHRT usTypVTotal;
    USHRT usMaxVTotal;
    USHRT usMinVSyncWidth;
    USHRT usMinVSyncBackPorch;
    ULONG ulFreeRunH_Freq;
    USHRT usPowerUpPanelTime;
    USHRT usPowerUpInvTime;
    USHRT usPowerDownPanelTime;
    USHRT usPowerDownInvTime;
    USHRT usPowerOffOnPanelTime;
    UCHAR ucSpreadSpectrumCtrl;
} PanelData;

//******************************************************************************
// G L O B A L   V A R I A B L E S
//******************************************************************************
extern code PanelData PanelDataDefault;

#endif //__PANEL_H__
