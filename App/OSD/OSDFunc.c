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

//******************************************************************************
// G L O B A L   D E F I N I T I O N S
//******************************************************************************

//******************************************************************************
// G L O B A L   V A R I A B L E S
//******************************************************************************

//******************************************************************************
// S T A T I C   V A R I A B L E S
//******************************************************************************

//******************************************************************************
// S T A T I C   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
code void (*OSDKeyRoutine[OSD_NON_STATE][OSD_NONKEY_EVENT])(void) = {
    //MENU_EVENT        AUTO_EVENT          UP_EVENT            DOWN_EVENT		KEYEVT_INPUT(for IR-Remote)
#if ENABLE_FUNC_OSD == ON
    {OSDEnterMainMenu,  OSDEnterAuto,       OSDEnterFuncMenu,   OSDEnterOpt1,	NULL},     
#else
	//150526 george (Compiler use this)
    {OSDEnterMainMenu,  OSDEnterAuto,       OSDEnterDir1,       OSDEnterDir2,	OSDEnterDirInput },		//george: F_ALSBV_04F     //[0][x]     //140317 mike for valume 	
#endif
    //140421 mike 
    {OSDEnterSubMenu1,  OSDExitMainMenu,    OSDMainMenuDown,    OSDMainMenuUp,	OSDEnterDirInput },         
    {OSDEnterSubMenu2,  OSDExitMainMenu,    OSDMainMenuDown,    OSDMainMenuUp,	OSDEnterDirInput },          
    {OSDEnterSubMenu3,  OSDExitMainMenu,    OSDMainMenuDown,    OSDMainMenuUp,	OSDEnterDirInput },         
    {OSDEnterSubMenu4,  OSDExitMainMenu,    OSDMainMenuDown,    OSDMainMenuUp,	OSDEnterDirInput },     
    {OSDEnterSubMenu5,  OSDExitMainMenu,    OSDMainMenuDown,    OSDMainMenuUp,	OSDEnterDirInput },     
//------------------------------------------------------------------------------
    {OSDEnterFactory,   OSDExitMainMenu,    OSDMainMenuUp,    OSDMainMenuDown,	NULL },      
    {OSDEnterDemo,      OSDExitMainMenu,    OSDMainMenuUp,    OSDMainMenuDown,	NULL },     
//-----------------------------------------------------------------------------
    {OSDEnterItm11,     OSDExitSubMenu1,    OSDSubMenuDown1,    OSDSubMenuUp1,	OSDEnterDirInput },     //usOSDState= 8
    {OSDEnterItm12,     OSDExitSubMenu1,    OSDSubMenuDown1,    OSDSubMenuUp1,	OSDEnterDirInput },     
    {OSDEnterItm13,     OSDExitSubMenu1,    OSDSubMenuDown1,    OSDSubMenuUp1,	OSDEnterDirInput },     // Sharpness	 150616 george	: ALS_2	  Ambient-Light-Sensor


#if ALS_EnDis == ALSMODE
	{OSDEnterItm14,     OSDExitSubMenu1,    OSDSubMenuDown1,    OSDSubMenuUp1,	OSDEnterDirInput },     //george: F_ALSOnOff_04A
#elif ALS_EnDis == ALSOffSET	
    {OSDEnterItm14,     OSDExitSubMenu1,    OSDSubMenuDown1,    OSDSubMenuUp1,	NULL },     //george: F_ALSOnOff_04A
#elif ALS_EnDis == ALSRange
    {OSDEnterItm14,     OSDExitSubMenu1,    OSDSubMenuDown1,    OSDSubMenuUp1,	NULL },     
#else	//Normal

#endif	//#if ALS_EnDis == ENABLE


//    {OSDEnterItm15,     OSDExitSubMenu1,    OSDSubMenuDown1,    OSDSubMenuUp1},     //george: F_ALSBV_04A	, [0x0A= 10][x]
//    {OSDEnterItm16,     OSDExitSubMenu1,    OSDSubMenuDown1,    OSDSubMenuUp1},     //george: F_Touch_04A
///     {OSDEnterItm17,     OSDExitSubMenu1,    OSDSubMenuDown1,    OSDSubMenuUp1},     // george: F_ALS_13
//-----------------------------------------------------------------------------
    {OSDEnterItm21,     OSDExitSubMenu2,    OSDSubMenuDown2,    OSDSubMenuUp2,	OSDEnterDirInput },     
    {OSDEnterItm22,     OSDExitSubMenu2,    OSDSubMenuDown2,    OSDSubMenuUp2,	OSDEnterDirInput },     
    {OSDEnterItm23,     OSDExitSubMenu2,    OSDSubMenuDown2,    OSDSubMenuUp2,	OSDEnterDirInput },    
    {OSDEnterItm24,     OSDExitSubMenu2,    OSDSubMenuDown2,    OSDSubMenuUp2,	OSDEnterDirInput },     
    {OSDEnterItm31,     OSDExitSubMenu3,    OSDSubMenuDown3,    OSDSubMenuUp3,	OSDEnterDirInput },    
    {OSDEnterItm32,     OSDExitSubMenu3,    OSDSubMenuDown3,    OSDSubMenuUp3,	OSDEnterDirInput },     
    {OSDEnterItm33,     OSDExitSubMenu3,    OSDSubMenuDown3,    OSDSubMenuUp3,	OSDEnterDirInput },     
    {OSDEnterItm34,     OSDExitSubMenu3,    OSDSubMenuDown3,    OSDSubMenuUp3,	OSDEnterDirInput },     
//--------------------------------------------------------------------------
    {OSDEnterItm41,     OSDExitSubMenu4,    OSDSubMenuDown4,    OSDSubMenuUp4,	OSDEnterDirInput },     
    {OSDEnterItm42,     OSDExitSubMenu4,    OSDSubMenuDown4,    OSDSubMenuUp4,	OSDEnterDirInput },     //150526 george [0x14= 20][x]
    {OSDEnterItm43,     OSDExitSubMenu4,    OSDSubMenuDown4,    OSDSubMenuUp4,	OSDEnterDirInput },     
    {OSDEnterItm44,     OSDExitSubMenu4,    OSDSubMenuDown4,    OSDSubMenuUp4,	OSDEnterDirInput },     
//--------------------------------------------------------------------------
    {OSDEnterItm51,     OSDExitSubMenu5,    OSDSubMenuDown5,    OSDSubMenuUp5,	OSDEnterDirInput },     
//--------------------------------------------------------------------------
#if AUDIO_EnDis == ENABLE
	{OSDEnterItm52,     OSDExitSubMenu5,    OSDSubMenuDown5,    OSDSubMenuUp5,	OSDEnterDirInput },     
	{OSDEnterItm53,     OSDExitSubMenu5,    OSDSubMenuDown5,    OSDSubMenuUp5,	OSDEnterDirInput },    
#else	//audio_osd-item_disable
#endif	//#if AUDIO_EnDis == ENABLE	

    {OSDEnterItm54,     OSDExitSubMenu5,    OSDSubMenuDown5,    OSDSubMenuUp5,	OSDEnterDirInput },    
    {OSDEnterItm57,     OSDExitSubMenu5,    OSDSubMenuDown5,    OSDSubMenuUp5,	OSDEnterDirInput }, 
#if TOUCH_EnDis == ENABLE
    {OSDEnterItm58,     OSDExitSubMenu5,    OSDSubMenuDown5,    OSDSubMenuUp5,	OSDEnterDirInput },     //gg_new
#endif //#if TOUCH_EnDis == ENABLE

#if ENABLE_ASPECT_RATIO == ON		//george 20160217
    {OSDEnterItm59,     OSDExitSubMenu5,    OSDSubMenuDown5,    OSDSubMenuUp5,	OSDEnterDirInput },     //gg_new
#endif //#if TOUCH_EnDis == ENABLE

//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
    {OSDExitItm11,      OSDExitItm11,       OSDUpItm11,         OSDDnItm11,		OSDEnterDirInput },       
    {OSDExitItm12,      OSDExitItm12,       OSDUpItm12,         OSDDnItm12,		OSDEnterDirInput },        
    {OSDExitItm13,      OSDExitItm13,       OSDUpItm13,         OSDDnItm13,		OSDEnterDirInput },        	//30

#if ALS_EnDis == ALSMODE
	{OSDExitItm14,      OSDExitItm14,       OSDUpItm14,         OSDDnItm14,		OSDEnterDirInput },       	//george: F_ALSOnOff_04B, F_ALSOnOff_04C, F_ALSOnOff_04D
#elif ALS_EnDis == ALSOffSET	
    {OSDExitItm14,      OSDExitItm14,       OSDUpItm14,         OSDDnItm14,		NULL },       	//george: F_ALSOnOff_04B, F_ALSOnOff_04C, F_ALSOnOff_04D
#elif ALS_EnDis == ALSRange
    {OSDExitItm14,      OSDExitItm14,       OSDUpItm14,         OSDDnItm14,		NULL },       	
#else	//Normal

#endif	//#if ALS_EnDis == ENABLE

//    {OSDExitItm15,      OSDExitItm15,       OSDUpItm15,         OSDDnItm15},       	//george: F_ALSBV_04B, F_ALSBV_04C, F_ALSBV_04D 
//gg_old    {OSDExitItm16,      OSDExitItm16,       OSDUpItm16,         OSDDnItm16},       	//george: F_Touch_04B, F_Touch_04C, F_Touch_04D		//george_Item16
///     {OSDExitItm17,      OSDExitItm17,       OSDDnItm17,         OSDUpItm17},       // george_Item17

    {OSDExitItm21,      OSDExitItm21,       OSDUpItm21,         OSDDnItm21,		OSDEnterDirInput },        
    {OSDExitItm22,      OSDExitItm22,       OSDUpItm22,         OSDDnItm22,		OSDEnterDirInput },       
    {OSDExitItm23,      OSDExitItm23,       OSDUpItm23,         OSDDnItm23,		OSDEnterDirInput },        
    {OSDExitItm24,      OSDExitItm24,       OSDUpItm24,         OSDDnItm24,		OSDEnterDirInput },        
    //-----------------------------------------------------------------
   
    {OSDEnterItm331,      OSDExitItm31,       OSDDnItm31,         OSDUpItm31,	OSDEnterDirInput },            
    {OSDEnterItm332,      OSDExitItm32,       OSDUpItm32,         OSDDnItm32,	OSDEnterDirInput },         
    {OSDEnterItm333,      OSDExitItm33,       OSDUpItm33,         OSDDnItm33,	OSDEnterDirInput },          
    {OSDEnterItm334,      OSDExitItm34,       OSDUpItm34,         OSDDnItm34,	OSDEnterDirInput },        //,	//40

    //=================================================
    //-----------------------------------------------------------------
    {OSDExitItm41,      OSDExitItm41,       OSDUpItm41,         OSDDnItm41,		OSDEnterDirInput },        //,
    {OSDExitItm42,      OSDExitItm42,       OSDUpItm42,         OSDDnItm42,		OSDEnterDirInput },        //,
    {OSDExitItm43,      OSDExitItm43,       OSDUpItm43,         OSDDnItm43,		OSDEnterDirInput },        //,
    {OSDExitItm44,      OSDExitItm44,       OSDUpItm44,         OSDDnItm44,		OSDEnterDirInput },        //,
//    {OSDExitItm45,      OSDExitItm45,       OSDUpItm45,         OSDDnItm45},        //,					// non-used (at OSDView.h) #define OSDFocusItm45 OSDFocusOSDRotation
    {OSDExitItm51,      OSDExitItm51,       OSDDnItm51,         OSDUpItm51,		OSDEnterDirInput },        //,   //    

#if AUDIO_EnDis == ENABLE
	{OSDExitItm52,      OSDExitItm52,       OSDUpItm52,         OSDDnItm52,		OSDEnterDirInput },        //,
	{OSDExitItm53,      OSDExitItm53,       OSDUpItm53,         OSDDnItm53,		OSDEnterDirInput },        //,
#else	//audio_osd-item_disable
#endif	//#if AUDIO_EnDis == ENABLE

    {OSDConfirmItm54,	OSDExitItm54,       OSDDnItm54,         OSDUpItm54,		OSDUpItm54 },        
//    {OSDExitItm55,      OSDExitItm55,       OSDUpItm55,         OSDDnItm55},        //,    //50		// non-used (at OSDView.h) #define OSDFocusItm55 OSDFocusOverscan
//    {OSDExitItm56,      OSDExitItm56,       OSDUpItm56,         OSDDnItm56},        //,				// non-used (at OSDView.h) #define OSDFocusItm56 OSDFocusOD
    {OSDExeItm57,       OSDExitItm57,       OSDUpItm57,         OSDDnItm57,		OSDEnterDirInput },        //,  

#if TOUCH_EnDis == ENABLE
	{OSDExitItm58,      OSDExitItm58,       OSDUpItm58,         OSDDnItm58,		OSDEnterDirInput },        //,  //gg_new
#endif //#if TOUCH_EnDis == ENABLE

#if ENABLE_ASPECT_RATIO == ON		//george 20160217
	{OSDExitItm59,      OSDExitItm59,       OSDUpItm59,         OSDDnItm59,		OSDEnterDirInput },        //,  //gg_new
#endif


#if ENABLE_FUNC_OSD == ON
    {OSDEnterFunc1,     OSDExitFuncMenu,    OSDFuncMenuDown,    OSDFuncMenuUp,	NULL },     //,		//Compiler no used
    {OSDEnterFunc2,     OSDExitFuncMenu,    OSDFuncMenuDown,    OSDFuncMenuUp,	NULL },     //,
    {OSDEnterFunc3,     OSDExitFuncMenu,    OSDFuncMenuDown,    OSDFuncMenuUp,	NULL },     //,
    {OSDEnterFunc4,     OSDExitFuncMenu,    OSDFuncMenuDown,    OSDFuncMenuUp,	NULL },     //,
    {OSDEnterFunc5,     OSDExitFuncMenu,    OSDFuncMenuDown,    OSDFuncMenuUp,	NULL },     //,
    {OSDEnterFunc6,     OSDExitFuncMenu,    OSDFuncMenuDown,    OSDFuncMenuUp,	NULL },     //,
    {OSDExitFunc1,      OSDExitFunc1,       OSDFuncDown1,       OSDFuncUp1,		NULL },        //,
    {OSDExitFunc2,      OSDExitFunc2,       OSDFuncDown2,       OSDFuncUp2,		NULL },        //,
    {OSDExitFunc3,      OSDExitFunc3,       OSDFuncUp3,         OSDFuncDown3,	NULL },      //,
    {OSDExitFunc4,      OSDExitFunc4,       OSDFuncUp4,         OSDFuncDown4,	NULL },      //,
    {OSDExitFunc5,      OSDExitFunc5,       OSDFuncDown5,       OSDFuncUp5,		NULL },        //,
    {OSDExitFunc6,      OSDExitFunc6,       OSDFuncDown6,       OSDFuncUp6,		NULL },        //,
#endif
    {OSDExitDir,        OSDExitDir,         OSDUpDir1,          OSDDnDir1,		NULL },         //,		//Compiler used here
    {OSDExitDir,        OSDExitDir,         OSDUpDir2,          OSDDnDir2,		NULL },         //,
    {OSDExitDir,        OSDExitDir,         OSDUpDir3,          OSDDnDir3,		NULL },         //,
    {NULL,              NULL,               NULL,               NULL},              //,
#if ENABLE_FUNC_OSD == ON
    {OSDEnterMainMenu,  OSDEnterAuto,       OSDEnterFuncMenu,   OSDEnterOpt1,	NULL },      //,		//Compiler no used
#else
    {OSDEnterMainMenu,  OSDEnterAuto,       OSDEnterDir2,       OSDEnterOpt1,	NULL },      //,		//Compiler used here
#endif
  //-------------------------------------------------------------------------
    {NULL,              NULL,               NULL,               NULL,			NULL },      //, ->  
    {NULL,              NULL,               NULL,               NULL,			NULL },      //,     ->  
    {NULL,              NULL,               NULL,               NULL,			NULL },      //,				//60
 //---------------------------------------------------------------------------------------------------------
#if ENABLE_FUNC_OSD == ON
    {OSDEnterMainMenu,  OSDEnterAuto,       OSDEnterFuncMenu,   OSDEnterOpt1,	NULL },      //,		//Compiler no used
#else
    {OSDEnterMainMenu,  OSDEnterAuto,       OSDEnterDir1,		OSDEnterDir2,	NULL }, //  //Compiler used here
#endif
    {NULL,              NULL,               NULL,               NULL,			NULL },             //,
    {OSDExitOpt1,       OSDExitOpt1,        OSDDnOpt1,          OSDUpOpt1,		NULL },         //,
    {OSDExitOpt2,       OSDExitOpt2,        OSDDnOpt2,          OSDUpOpt2,		NULL },         //,
//----------------------------------------------------------------    
    {OSDEnterFItm,      NULL,               OSDUpFactory,    OSDDnFactory,		NULL },         //, ,  
    {OSDExitFItm,       OSDExitFItm,        OSDUpFItm ,         OSDDnFItm,		NULL },        //,  
 //----------------------------------------------------------------   
    {OSDEnterDItm,      OSDCloseAll,        OSDUpDemo,          OSDDnDemo,		NULL },    //
    {OSDExitDItm,       OSDExitDItm,        OSDUpDItm,          OSDDnDItm,		NULL },      //			//68
    
};

code void (*OSDAppRoutine[NUM_OSD_APP_EVENTS])(void) = 
 {
    OSDEnterNoSync,     	//
    OSDEnterNoCable,    	//
    OSDEnterNormal,     	//
    OSDEnterOOL,       		// george: OUTOFLIMIT
    OSDEnterOOR,        	// george: OUTOFRANCE
    OSDCloseAll,        		//
    NULL                			//
 };

code void (*OSDUnusedRoutine[])(void) = 
	{
    		OSDEnterDir1, 
    		OSDEnterDir2
	};
