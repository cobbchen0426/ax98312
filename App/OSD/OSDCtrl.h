/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/
#ifndef __OSD_CTRL_H__
#define __OSD_CTRL_H__

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************
#include "Typedef.h"

//******************************************************************************
// G L O B A L   D E F I N I T I O N S
//******************************************************************************
enum _OSDAPPCEVENT_ {
    OSD_NO_SYNC_EVENT,
    OSD_NO_CABLE_EVENT,
    OSD_NML_EVENT,
    OSD_OOL_EVENT,
    OSD_OOR_EVENT,
    OSD_OFF_EVENT,
    OSD_NOP_EVENT,
    NUM_OSD_APP_EVENTS
} ;

enum _OSDKEYEVENT_ {
    OSD_MENUKEY_EVENT,
    OSD_AUTOKEY_EVENT,
    OSD_UPKEY_EVENT,
    OSD_DOWNKEY_EVENT,
	OSD_INPUT_EVENT,	//george
    OSD_NONKEY_EVENT,
    NUM_OSD_KEY_EVENTS
} ;

typedef enum _OSDSTATE_ {
    OSD_OFF_STATE,								// 0
    OSD_MAIN_BEG,								// 1
    OSD_MAIN_1_STATE = OSD_MAIN_BEG,			// 1
    OSD_MAIN_2_STATE,	// 2
    OSD_MAIN_3_STATE,	// 3						
    OSD_MAIN_4_STATE,	// 4				
    OSD_MAIN_5_STATE,    // 5
    OSD_MAIN_6_STATE,    // 6
    OSD_MAIN_7_STATE,    // 7
    OSD_MAIN_END,            // 8
    OSD_MAIN_1_1_STATE = OSD_MAIN_END, //8			       	
    OSD_MAIN_1_2_STATE,	//9					//140314 mike   
 	OSD_MAIN_1_3_STATE,		//150616 george: ALS_1   Ambient-Light-Sensor  	//  OSD_MAIN_1_3_STATE,							//140314 mike 

#if ALS_EnDis == ALSMODE
    OSD_MAIN_1_4_STATE,	//george: F_ALSOnOff_04B					//140314 mike 
#elif ALS_EnDis == ALSOffSET	
    OSD_MAIN_1_4_STATE,	//george: F_ALSOnOff_04B					//140314 mike 
#elif ALS_EnDis == ALSRange
	OSD_MAIN_1_4_STATE,	
#else	//Normal

#endif	//#if ALS_EnDis == ENABLE

//    OSD_MAIN_1_5_STATE, //george: F_ALSBV_04B     //a					//140314 mike 
//gg_old	OSD_MAIN_1_6_STATE,	//george: F_Touch_04B
///	OSD_MAIN_1_7_STATE,  // george_Item17
    OSD_MAIN_1_END,			//b					//140314 mike 
    OSD_MAIN_2_1_STATE = OSD_MAIN_1_END,          //b		
    OSD_MAIN_2_2_STATE,      // c
    OSD_MAIN_2_3_STATE,      // d
    OSD_MAIN_2_4_STATE,      // e
    OSD_MAIN_2_END,              // f 
    OSD_MAIN_3_1_STATE = OSD_MAIN_2_END,		//140314 mike 
    OSD_MAIN_3_2_STATE,      // 10
    OSD_MAIN_3_3_STATE,      // 11
    OSD_MAIN_3_4_STATE,      // 12
    OSD_MAIN_3_END,              // 13
    OSD_MAIN_4_1_STATE = OSD_MAIN_3_END,       		//140314 mike 
    OSD_MAIN_4_2_STATE,	// 14					
    OSD_MAIN_4_3_STATE,	// 15					
    OSD_MAIN_4_4_STATE,	// 16 					
//    OSD_MAIN_4_5_STATE,							
    OSD_MAIN_4_END,              // 17 
    //-------------------------------------
    OSD_MAIN_5_1_STATE = OSD_MAIN_4_END,			 

#if AUDIO_EnDis == ENABLE
	OSD_MAIN_5_2_STATE,	// 18 					
	OSD_MAIN_5_3_STATE,	// 19											
#else	//audio_osd-item_disable
#endif	//#if AUDIO_EnDis == ENABLE

    OSD_MAIN_5_4_STATE,	// 1a					
 //OSD_MAIN_5_5_STATE,
 //OSD_MAIN_5_6_STATE,
    OSD_MAIN_5_7_STATE,	// 1b					

#if TOUCH_EnDis == ENABLE
	OSD_MAIN_5_8_STATE, //gg_new
#endif //#if TOUCH_EnDis == ENABLE

#if ENABLE_ASPECT_RATIO == ON		//george 20160217
	OSD_MAIN_5_9_STATE,  			// (at OSDView.h) #define OSDFocusItm59 OSDFocusTouch
#endif

    OSD_MAIN_5_END,	              // 1c
    //--------------------------------------
    /*
    OSD_MAIN_5_1_STATE = OSD_MAIN_4_END,
    OSD_MAIN_5_2_STATE,							//140317 mike for mute
    OSD_MAIN_5_3_STATE,
 //OSD_MAIN_5_4_STATE,
 //OSD_MAIN_5_5_STATE,
 //OSD_MAIN_5_6_STATE,
    OSD_MAIN_5_7_STATE,
    OSD_MAIN_5_END,
    */
    //---------------------------------------
    OSD_ITEM_1_1_STATE = OSD_MAIN_5_END,	//george:0x1C
    OSD_ITEM_1_2_STATE,		// 1d
    OSD_ITEM_1_3_STATE,		// 1e

#if ALS_EnDis == ALSMODE
	OSD_ITEM_1_4_STATE,		//george: F_ALSOnOff_04A
#elif ALS_EnDis == ALSOffSET	
	OSD_ITEM_1_4_STATE,		//george: F_ALSOnOff_04A
#elif ALS_EnDis == ALSRange
	OSD_ITEM_1_4_STATE,		
#else	//Normal

#endif	//#if ALS_EnDis == ENABLE

//    OSD_ITEM_1_5_STATE,     //george: F_ALSBV_04A
//gg_old    OSD_ITEM_1_6_STATE,     //george: F_Touch_04A
///    OSD_ITEM_1_7_STATE,       // george_Item17

    OSD_ITEM_2_1_STATE,       // 21
    OSD_ITEM_2_2_STATE,       // 22
    OSD_ITEM_2_3_STATE,       // 23
    OSD_ITEM_2_4_STATE,       // 24
    OSD_ITEM_3_1_STATE,       // 25
    OSD_ITEM_3_2_STATE,       // 26
    OSD_ITEM_3_3_STATE,       // 27
    OSD_ITEM_3_4_STATE,       // 28
    OSD_ITEM_4_1_STATE,       // 29
    OSD_ITEM_4_2_STATE,       // 2a
    OSD_ITEM_4_3_STATE,       // 2b
    OSD_ITEM_4_4_STATE,       // 2c
//    OSD_ITEM_4_5_STATE,       // 2d		// non-used (at OSDView.h) #define OSDFocusItm45 OSDFocusOSDRotation
    OSD_ITEM_5_1_STATE,       // 2e 	// OSDEnterItm51() -> language

#if AUDIO_EnDis == ENABLE
	OSD_ITEM_5_2_STATE,       // 2f		// OSDEnterItm52() -> volume
	OSD_ITEM_5_3_STATE,       // 30		// OSDEnterItm53() -> mute
#else	//audio_osd-item_disable
#endif	//#if AUDIO_EnDis == ENABLE	

    OSD_ITEM_5_4_STATE,       // 31		// OSDEnterItm54() -> input
//    OSD_ITEM_5_5_STATE,       // 32		// non-used (at OSDView.h) #define OSDFocusItm55 OSDFocusOverscan ;  (SCALERCFG.H) #if ENABLE_OVERSCAN == ON
//    OSD_ITEM_5_6_STATE,       // 33		// non-used (at OSDView.h) #define OSDFocusItm56 OSDFocusOD
    OSD_ITEM_5_7_STATE,       // 34		// (at OSDView.h) #define OSDFocusItm57 OSDFocusReset

#if TOUCH_EnDis == ENABLE
	OSD_ITEM_5_8_STATE,	//gg_new  		// (at OSDView.h) #define OSDFocusItm58 OSDFocusTouch	//gg_new
#endif //#if TOUCH_EnDis == ENABLE

#if ENABLE_ASPECT_RATIO == ON		//george 20160217
	OSD_ITEM_5_9_STATE,	//gg_new  		// (at OSDView.h) #define OSDFocusItm58 OSDFocusTouch	//gg_new
#endif



#if ENABLE_FUNC_OSD == ON		// george: not complier here
    OSD_FUNC_BEG,
    OSD_FUNC_1_STATE = OSD_FUNC_BEG,
    OSD_FUNC_2_STATE,
    OSD_FUNC_3_STATE,
    OSD_FUNC_4_STATE,
    OSD_FUNC_5_STATE,
    OSD_FUNC_6_STATE,
    OSD_FUNC_END,
    OSD_FNITM_1_STATE = OSD_FUNC_END,
    OSD_FNITM_2_STATE,
    OSD_FNITM_3_STATE,
    OSD_FNITM_4_STATE,
    OSD_FNITM_5_STATE,
    OSD_FNITM_6_STATE,
#endif
    OSD_DIRECT_1_STATE,			// george: OSDEnterDir1()
    OSD_DIRECT_2_STATE,			// george: OSDEnterDir2()
    OSD_DIRECT_3_STATE,			// george: OSDEnterDir3()
    OSD_AUTOTUNE_STATE,			// george: 0x38, OSDEnterAuto()
    OSD_INFO_OUTOFLIMIT_STATE,	// george:       OSDEnterOOL(), OSDConfigKeyBehavior(), OSDTimerRoutine()
    OSD_INFO_OUTOFRANCE_STATE,	// george: 0x3a, OSDEnterOOR(), OSDConfigKeyBehavior(), OSDTimerRoutine()
    OSD_INFO_NOSYNC_STATE,		// george:    OSDEnterNoSync(), OSDConfigKeyBehavior(), OSDTimerRoutine()
    OSD_INFO_NOCABLE_STATE,		// george:   OSDEnterNoCable(), OSDConfigKeyBehavior(), OSDTimerRoutine()
    OSD_INFO_NOTICE_STATE,		// george:    OSDEnterNormal(), OSDConfigKeyBehavior(), OSDTimerRoutine()
    OSD_INFO_SOURCE_STATE,		// george:						OSDConfigKeyBehavior()
    OSD_OPT1_STATE,				// george: 0x3f, OSDEnterOpt1(), OSDTimerRoutine()	{osd-show: "Bright Frame", "LTMItemStrTab: '76\% NTSC', '80\% NTSC', 'NovaColor 1', 'NovaColor 2', 'Standard'  "}
    OSD_OPT2_STATE,				// george: 0x40, OSDEnterOpt2(), OSDTimerRoutine()  {osd-show: "input";  *SourceStrTab[]:"VGA,DVI,HDMI,YPbPr,DP"}
    OSD_FACT_STATE,				// george: OSDEnterFactory(), OSDUpFactory(), OSDDnFactory(), 
    OSD_FITM_STATE,				// george: FactoryItm, OSDEnterFItm(), OSDUpFItm(), OSDDnFItm(), OSDExitFItm(), 
    OSD_DEMO_STATE,				// george: OSDEnterDemo(), OSDUpDemo(), OSDDnDemo(), 
    OSD_DITM_STATE,				// george: OSDEnterDItm(), OSDUpDItm((), OSDDnDItm(),  OSDExitDItm()
    OSD_NON_STATE,
    NUM_OSD_STATUS				//george: 0x46
} OSDState;

typedef enum _OSDACTION_ {
    OSDATN_ENT_MAIN,
    OSDATN_EXT_MAIN,
    OSDATN_UP_MAIN,
    OSDATN_DN_MAIN,
    OSDATN_ENT_SUB1,
    OSDATN_EXT_SUB1,
    OSDATN_UP_SUB1,
    OSDATN_DN_SUB1,
    OSDATN_ENT_SUB2,
    OSDATN_EXT_SUB2,
    OSDATN_UP_SUB2,
    OSDATN_DN_SUB2,
    OSDATN_ENT_SUB3,
    OSDATN_EXT_SUB3,
    OSDATN_UP_SUB3,
    OSDATN_DN_SUB3,
    OSDATN_ENT_SUB4,
    OSDATN_EXT_SUB4,
    OSDATN_UP_SUB4,
    OSDATN_DN_SUB4,
    OSDATN_ENT_SUB5,
    OSDATN_EXT_SUB5,
    OSDATN_UP_SUB5,
    OSDATN_DN_SUB5,
    OSDATN_ENT_ITM11,
    OSDATN_EXT_ITM11,
    OSDATN_ENT_ITM12,
    OSDATN_EXT_ITM12,
    OSDATN_ENT_ITM13,
    OSDATN_EXT_ITM13,
    OSDATN_ENT_ITM14,
    OSDATN_EXT_ITM14,
    OSDATN_ENT_ITM21,
    OSDATN_EXT_ITM21,
    OSDATN_ENT_ITM22,
    OSDATN_EXT_ITM22,
    OSDATN_ENT_ITM23,
    OSDATN_EXT_ITM23,
    OSDATN_ENT_ITM24,
    OSDATN_EXT_ITM24,
    OSDATN_ENT_ITM31,
    OSDATN_EXT_ITM31,
    OSDATN_ENT_ITM32,
    OSDATN_EXT_ITM32,
    OSDATN_ENT_ITM33,
    OSDATN_EXT_ITM33,
    OSDATN_ENT_ITM34,
    OSDATN_EXT_ITM34,
    OSDATN_ENT_ITM41,
    OSDATN_EXT_ITM41,
    OSDATN_ENT_ITM42,
    OSDATN_EXT_ITM42,
    OSDATN_ENT_ITM43,
    OSDATN_EXT_ITM43,
    OSDATN_ENT_ITM44,
    OSDATN_EXT_ITM44,
    OSDATN_ENT_ITM51,
    OSDATN_EXT_ITM51,
    OSDATN_ENT_ITM52,
    OSDATN_EXT_ITM52,
    OSDATN_ENT_ITM53,
    OSDATN_EXT_ITM53,
    OSDATN_ENT_ITM54,
    OSDATN_EXT_ITM54,
    OSDATN_ENT_ITM55,
    OSDATN_EXT_ITM55,
    OSDATN_ENT_ITM56,
    OSDATN_EXT_ITM56,
    OSDATN_ENT_ITM57,
    OSDATN_EXT_ITM57,
    OSDATN_UP_ITM11,
    OSDATN_DN_ITM11,
    OSDATN_UP_ITM12,
    OSDATN_DN_ITM12,
    OSDATN_UP_ITM13,
    OSDATN_DN_ITM13,
    OSDATN_UP_ITM14,
    OSDATN_DN_ITM14,
    OSDATN_UP_ITM21,
    OSDATN_DN_ITM21,
    OSDATN_UP_ITM22,
    OSDATN_DN_ITM22,
    OSDATN_UP_ITM23,
    OSDATN_DN_ITM23,
    OSDATN_UP_ITM24,
    OSDATN_DN_ITM24,
    OSDATN_UP_ITM31,
    OSDATN_DN_ITM31,
    OSDATN_UP_ITM32,
    OSDATN_DN_ITM32,
    OSDATN_UP_ITM33,
    OSDATN_DN_ITM33,
    OSDATN_UP_ITM34,
    OSDATN_DN_ITM34,
    OSDATN_UP_ITM41,
    OSDATN_DN_ITM41,
    OSDATN_UP_ITM42,
    OSDATN_DN_ITM42,
    OSDATN_UP_ITM43,
    OSDATN_DN_ITM43,
    OSDATN_UP_ITM44,
    OSDATN_DN_ITM44,
    OSDATN_UP_ITM51,
    OSDATN_DN_ITM51,
    OSDATN_UP_ITM52,
    OSDATN_DN_ITM52,
    OSDATN_UP_ITM53,
    OSDATN_DN_ITM53,
    OSDATN_UP_ITM54,
    OSDATN_DN_ITM54,
    OSDATN_UP_ITM55,
    OSDATN_DN_ITM55,
    OSDATN_UP_ITM56,
    OSDATN_DN_ITM56,
    OSDATN_UP_ITM57,
    OSDATN_DN_ITM57,
    OSDATN_ENT_AUTO,
    OSDATN_ENT_DIR1,
    OSDATN_EXT_DIR1,
    OSDATN_UP_DIR1,
    OSDATN_DN_DIR1,
    OSDATN_ENT_DIR2,
    OSDATN_EXT_DIR2,
    OSDATN_UP_DIR2,
    OSDATN_DN_DIR2,
    OSDATN_ENT_DIR3,
    OSDATN_EXT_DIR3,
    OSDATN_UP_DIR3,
    OSDATN_DN_DIR3,
    OSDATN_ENT_OPT1,
    OSDATN_EXT_OPT1,
    OSDATN_UP_OPT1,
    OSDATN_DN_OPT1,
    OSDATN_ENT_OPT2,
    OSDATN_EXT_OPT2,
    OSDATN_UP_OPT2,
    OSDATN_DN_OPT2,

    OSDATN_ENT_NOSYNC,
    OSDATN_ENT_NOCBL,
    OSDATN_ENT_NML,
    OSDATN_ENT_OOR,
    OSDATN_NO_OSD,

    OSDATN_ENT_FACT,
    OSDATN_EXT_FACT,
    OSDATN_UP_FACT,
    OSDATN_DN_FACT,
    OSDATN_ENT_FITM,
    OSDATN_EXT_FITM,
    OSDATN_UP_FITM,
    OSDATN_DN_FITM,

    OSD_NON_ACTION,
    NUM_OSD_ACTIONS
} OSDAction;

#define NUM_MAIN_ITEMS  (OSD_MAIN_END-OSD_MAIN_BEG)
#define NUM_SUB1_ITEMS  (OSD_MAIN_1_END-OSD_MAIN_END)
#define NUM_SUB2_ITEMS  (OSD_MAIN_2_END-OSD_MAIN_1_END)
#define NUM_SUB3_ITEMS  (OSD_MAIN_3_END-OSD_MAIN_2_END)
#define NUM_SUB4_ITEMS  (OSD_MAIN_4_END-OSD_MAIN_3_END)
#define NUM_SUB5_ITEMS  (OSD_MAIN_5_END-OSD_MAIN_4_END)

//******************************************************************************
// E X T E R N A L   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
void OSDActionDispatcher(UCHAR event);
UCHAR OSDActionDemander(void);
void OSDConfigTimeout(USHRT timer);
void OSDCloseAll(void);
void OSDUpdateAutoTune(UCHAR pnt);


//******************************************************************************
// S T A T I C   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
void OSDTimerRoutine(void);
void OSDEnterMainMenu(void);
void OSDExitMainMenu(void);
void OSDMainMenuUp(void);
void OSDMainMenuDown(void);
void OSDEnterSubMenu1(void);
void OSDExitSubMenu1(void);
void OSDSubMenuUp1(void);
void OSDSubMenuDown1(void);
void OSDEnterSubMenu2(void);
void OSDExitSubMenu2(void);
void OSDSubMenuUp2(void);
void OSDSubMenuDown2(void);
void OSDEnterSubMenu3(void);
void OSDExitSubMenu3(void);
void OSDSubMenuUp3(void);
void OSDSubMenuDown3(void);
void OSDEnterSubMenu4(void);
void OSDExitSubMenu4(void);
void OSDSubMenuUp4(void);
void OSDSubMenuDown4(void);
void OSDEnterSubMenu5(void);
void OSDExitSubMenu5(void);
void OSDSubMenuUp5(void);
void OSDSubMenuDown5(void);
void OSDEnterItm11(void);
void OSDExitItm11(void);
void OSDEnterItm12(void);
void OSDExitItm12(void);
void OSDEnterItm13(void);
void OSDExitItm13(void);

void OSDEnterDirInput(void);	//gg1

#if ALS_EnDis == ALSMODE
	void OSDEnterItm14(void);		//george: F_ALSOnOff_04A
	void OSDExitItm14(void);		//george: F_ALSOnOff_04B
#elif ALS_EnDis == ALSOffSET	
	void OSDEnterItm14(void);		//george: F_ALSOnOff_04A
	void OSDExitItm14(void);		//george: F_ALSOnOff_04B
#elif ALS_EnDis == ALSRange
	void OSDEnterItm14(void);		
	void OSDExitItm14(void);		
#else	//Normal

#endif	//#if ALS_EnDis == ENABLE

//void OSDEnterItm15(void);		//george: F_ALSBV_04A
//void OSDExitItm15(void);		//george: F_ALSBV_04B

//gg_old void OSDEnterItm16(void);		//george: F_Touch_04A
//gg_old void OSDExitItm16(void);		//george: F_Touch_04B

/// void OSDEnterItm17(void);	//george_Item17
/// void OSDExitItm17(void);


void OSDEnterItm21(void);
void OSDExitItm21(void);
void OSDEnterItm22(void);
void OSDExitItm22(void);
void OSDEnterItm23(void);
void OSDExitItm23(void);
void OSDEnterItm24(void);
void OSDExitItm24(void);
void OSDEnterItm31(void);
void OSDExitItm31(void);
//------------------------OSDEnterItm331  //140430 mike 
void OSDEnterItm331(void);
void OSDEnterItm332(void);
void OSDEnterItm333(void);
void OSDEnterItm334(void);
//------------------------
void OSDEnterItm32(void);
void OSDExitItm32(void);
void OSDEnterItm33(void);
void OSDExitItm33(void);
void OSDEnterItm34(void);
void OSDExitItm34(void);
void OSDEnterItm41(void);
void OSDExitItm41(void);
void OSDEnterItm42(void);
void OSDExitItm42(void);
void OSDEnterItm43(void);
void OSDExitItm43(void);
void OSDEnterItm44(void);
void OSDExitItm44(void);
void OSDEnterItm45(void);
void OSDExitItm45(void);
void OSDEnterItm51(void);
void OSDExitItm51(void);

#if AUDIO_EnDis == ENABLE
	void OSDEnterItm52(void);
	void OSDExitItm52(void);
	void OSDEnterItm53(void);									//140318 mike 
	void OSDExitItm53(void);
#else	//audio_osd-item_disable
#endif	//#if AUDIO_EnDis == ENABLE


void OSDEnterItm54(void);
void OSDExitItm54(void);	

void OSDEnterItm55(void);
void OSDExitItm55(void);
void OSDEnterItm56(void);
void OSDExitItm56(void);
void OSDEnterItm57(void);
void OSDExeItm57(void);		//george
void OSDExitItm57(void);

#if TOUCH_EnDis == ENABLE
	void OSDEnterItm58(void);	//gg_new
	void OSDExitItm58(void);	//gg_new
#endif //#if TOUCH_EnDis == ENABLE

#if ENABLE_ASPECT_RATIO == ON		//george 20160217
	void OSDEnterItm59(void);
	void OSDExitItm59(void);
#endif


void OSDEnterFuncMenu(void);
void OSDExitFuncMenu(void);
void OSDFuncMenuUp(void);
void OSDFuncMenuDown(void);
void OSDEnterFunc1(void);
void OSDExitFunc1(void);
void OSDEnterFunc2(void);
void OSDExitFunc2(void);
void OSDEnterFunc3(void);
void OSDExitFunc3(void);
void OSDEnterFunc4(void);
void OSDExitFunc4(void);
void OSDEnterFunc5(void);
void OSDExitFunc5(void);
void OSDEnterFunc6(void);
void OSDExitFunc6(void);
void OSDEnterAuto(void);
void OSDEnterDir1(void);
void OSDEnterDir2(void);
void OSDEnterDir3(void);
void OSDExitDir(void);
void OSDEnterOpt1(void);
void OSDExitOpt1(void);
void OSDEnterOpt2(void);
void OSDExitOpt2(void);
void OSDEnterNormal(void);
void OSDEnterNoSync(void);
void OSDEnterNoCable(void);
void OSDEnterOOL(void);
void OSDEnterOOR(void);
void OSDEnterFactory(void);
void OSDUpFactory(void);
void OSDDnFactory(void);
void OSDEnterFItm(void);
void OSDExitFItm(void);
void OSDUpFItm(void);
void OSDDnFItm(void);
void OSDEnterDemo(void);
void OSDUpDemo(void);
void OSDDnDemo(void);
void OSDEnterDItm(void);
void OSDExitDItm(void);
void OSDUpDItm(void);
void OSDDnDItm(void);
void OSDDummyFunction(void);

extern void OSDColorUserRGBUp(void);				//140509 mike
extern void OSDColorUserRGBDown(void);				//140509 mike

#endif //__OSD_CTRL_H__
