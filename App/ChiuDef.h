//============================================================================================================
//SCALER_TYPE=NT68857,NT68857_DEMO,NVT_1920X1080,FLASH_BANK=4
//============================================================================================================

//==================== George Define Start ====================
//------------------------------- xxx_Debug :	ENABLE: show printf()      DISABLE: hide printf();  -------------------------------
#define Key_Debug		DISABLE		//george: can search this word.   Mark-Disable_#define, will be non-Key_Debug.
#define PWRSeq_Deug		DISABLE		//	{ PWR Key action (PowerOff): SYSAPI_SetPowerOff(), LedGreenOff(), AudioMuteOn(). }
									//	{ PWR Key action (PowerOn) : LedGreenOn(), AudioMuteOn(), SYSAPI_SetInverterVal(), CheckADCPLLOutOfRange(),  SetHmask(), HwAutoOffset(), AudioMuteOff();   
									//                               APPSyncPublisher()-> case SOFT_POWER_OFF:,  ModeHandler()->case SOFT_POWER_OFF:,    }

#define PWROn_Debug		DISABLE		//

#define OSD_Debug		DISABLE		//  {	OSDPerformNormal(), OSDEnterNormal()  }

#define AutoTune_Debug	DISABLE		//ENABLE: show printf()      DISABLE: hide printf();
							// { Start:  OSDEnterAuto()_S,  OSDPerformAuto()_S,  UserPerformAutoTune()_S, 
							//   			01_AutoTune(),  03_AutoPosition(), 
							//	 			18_SetHmask(), 05_MeasureImageSize(), 06_AutoClock(), 15_AutoClockByPhase(), { 20_SetADCPLL2(), 16_CheckPhaseData(), } , 07_AutoPhaseFineTune(), 03_AutoPosition(), 
							//   			18_SetHmask(), 05_MeasureImageSize(), 02_AutoTuneComplete(), 
							//	 End  :  UserPerformAutoTune()_End, OSDPerformAuto()_End, OSDEnterAuto()_End }

#define BurnIn_Degub	DISABLE		// Burn In Mode Trace

#define OTHER_Degub		DISABLE		// Burn In Mode Trace
//-----------  Debug printf() Info.  -----------------------------------------------------------------------------------------------------------------
			//printf("Timing[]= %d\n", (USHRT)sizeof(NvramTimingFormat));	//NvramWriteTimingData()	//NvramClearTiming()
			//printf("UserData[]= %d\n", (USHRT)sizeof(NvramUserData));	

			//(at Nvram.c) : UserDataDefault
			//(at Nvram.h) : NvramUserData

			//(at Nvram.c) : CalibDataDefault
			//(at Nvram.h) : NvramCalibData


			//(at Nvram.c) : SystemDataDefault
			//(at Nvram.h) : NvramSystemData			


			//(at Nvram.h) : NvramTimingFormat
//---------------------------------------------------------------------------------------------------------------------------- 
	//Input Interface Hide:
	// at \Sys\SI\NVT\NT68857_DEMOModelConfig.h -> 

//---------------------------------------------------------------------------------------------------------------------------
#define	ALSMODE				2
#define ALSOffSET			3
#define ALSRange			4		//(for ADS LS3101) Ambient-Light-Sensor: include -> ucALSBrigMAX, ucALSBrigMIN
#define ALS_EnDis			DISABLE	//ALSRange		//	ENABLE:{ ALSMODE(CM3218_ALSMode.c for AXI) or ALSOffSET(CM3218_ALSOffset.c for George) or ALSRange(LS3101_ADS.c for ADS) },	DISABLE	

#define AUDIO_EnDis			ENABLE		//when set DISABLE, must check Panel-> EDID.c (HDMI port)
//		 OSD_SHOW_AUDIO
#define IR_REMOT_CTL		ENABLE	//ENABLE	DISABLE					////#define ENABLE_IR               ON	//OFF	 //150511  George		// \Lib\ScalerCfg\NT68857\ScalerCfg.h	

// #define OSD_DP_SHOW		DISABLE   (at \App\User\UserSetting.c)
#define OSD_SHOW_VERSION	ENABLE   //ENABLE	//(at \App\OSD\OSDView.c) & (at \Sys\ModeConfig.c)	(at \App\User\UserSetting.c)

#define PIR_EnDis			DISABLE		// not coding


#define TOUCH_EnDis			DISABLE	//ENABLE	DISABLE   (for : when (BUILD_CUSTOMER == X_AXI)  Only.  it is about show osd item priority.  

#define KEY_LED_Flash		DISABLE	//ENABLE: AXI_AX98310_request-Flash,   DISABLE: non-Flash

#define VGA_GetMode_AutoTurn	OFF	//ON: Normal(VGA-GetMode-Run-AutoTurn).  OFF:  FF: AXI-request (don't run AutoTurn).


//OSD Key Order
#define ADS_OSD_Order			1
#define AXI_AX98310_Order		2	//AXI_Membrane_Parts: 97421127100E,    at Model: P6105DPR-24VDC,  used_5key_2LED_G
#define AXI_P6105	 			3	//AXI_Membrane_Parts: 97421127100E,    at Model: P6105, P6171,	  used_5key_2LED_G+Y
#define OSDKey_Order		AXI_P6105
							

#define ADS_RS232			2
#define	LWO_RS232			3
#define XRS232				LWO_RS232	//ENABLE(ADS_RS232, LWO_RS232)	DISABLE(slow Show OSD... why???  )		// (at ScalerCfg.h)   UART Output Selection: #define MCU_UART_OUTPUT       0 //TX/RX
									// Search: #if MCU_UART_OUTPUT != 0
									// (at MODELCONFIG.H) UART Output Selection: #define MD_MCU_UART_OUTPUT      0 //TX/RX
									// (at McuInitMisc) -> UART_MUX = MCU_UART_OUTPUT; 		//Uart output: IIC channel
									// (at Scaler_Power.c) ScalerPowerDown(): dis_McuPowerDownAPLL();   dis_SetLowPowerMode(TRUE);

#define ASPECT_RATIO_EnDis 	DISABLE	//ENABLE	DISABLE	(normal: Disable)
//#define ENABLE_ASPECT_RATIO		ON	//george 20160217  ,  Function: (at \Lib\ScalerCfg\NT68857\SCALERCFG.H) 			
//PS: a. when (BUILD_CUSTOMER == X_AXI), no OSD-AspectRatio(DisplaySize).  Becouse OSD-Item-No. by Touch be used.
//    b. it is about show osd item priority.


//====================================== For Customer Special Function ==========================
#define NORMAL				0
#define	SET_OSD_LEFT_TOP	2
#define	SET_OSD_CENTER_TOP	3
#define SET_SHOW_OSD_POSITION	NORMAL	//Other(else):NORMAL,	SET_OSD_LEFT_TOP,	SET_OSD_CENTER_TOP
//===============================================================================================

//Power Supply 
//PS_OFF()	,(at \Phy\SI\NVT\Board-> Board.c)	//for AD907_CN8_P4pin(PC4) Only : 
//PanelPowerOffSequence() -> case_PANEL_INSERT_BLACK:
//							 case_PANEL_INSERT_WHITE: 
//							 case_case PANEL_INSERT_WHITE|PANEL_POWER_LVDS_SWAP:
//							 case_case PANEL_INSERT_BLACK|PANEL_POWER_LVDS_SWAP:
							/* ref.  McuSetIOBit(PSB_PORT...) : (1).	SYSAPI_PowerSaving(), SYSAPI_SetPowerOff(), MCU_PORT_D, LedGreenOn(), ScalerPowerDown(), 
							                                    (2).    ScalerPowerUp(), 
							*/


#define BRIG_MIN_0		1
#define BRIG_MIN_1		4	// at OSD Brightness = 0% ---> PWM = 1%
#define BRIG_MIN_5		2	// at OSD_Brightness = 0% ---> PWM = 5%
#define BRIG_MIN_10		3	// at OSD_Brightness = 0% ---> PWM = 10%
#define BRIG_MIN_SEL	BRIG_MIN_1		//BRIG_MIN_5
// (at \App\User\UserSetting.h) Brightness_PWM_MinimumValue ===>  #define GetBrightness1023() ( Remap100ToAny(UserData.ucBrightness, 1023 - MIN_BACKLIGHT_VALUE) + MIN_BACKLIGHT_VALUE )


//VDHP: VGA, DVI, HDMI, DP
#define X_INP_DHP	1		//input: DVI+HDMI+DP  	X_ADS_AD907
#define X_INP_VDH	2		//input: VGA+DVI+HDMI	X_ADS_AD908, AXI_AX98312
#define X_INP_DH	3		//input: DVI+HDMI		X_AXI_AX98310+AX93175

#define BUILD_CUSTOMER		X_INP_VDH		//X_AXI	//X_ADS_AD908	//X_ADS_AD907,  X_ADS_AD908 or X_AXI  (mark: different parts.)



//==================== Show Factory Mode F/W-Version & Panel-ModelName : ====================
//(at \Sys\ModeConfig.c) -> code UCHAR ucModelText[]={4,"X??W"};


//==================== George Define End ====================

//--------------------- Special Panel Define ---------------------------------------------------------------
#ifdef SPECIAL_TRULY_TFT1280120		/*  #ifdef TRULY_TFT1280120  ....  */
	#define	TRULY_TFT1280120
	//Version: XXW		
#endif



//--------------------- Normal Panel Define ---------------------------------------------------------------
#define	USE_X10N_BOARD         // VGA / DVI  /DP
//#define	USE_X18_BOARD         // VGA / HDMI / DP
//#define	USE_X19N_BOARD
//------------------------------------------------------------------------------------
#ifdef USE_X19N_BOARD
#define	SET_OSD_LEFT_TOP	//by Panel.h set define it.
#endif

//------------------------------------------------------------------------------------
#ifdef X06N
#define SRP_LQ064V3DG01    //150907 george
#endif 
//------------------------------------------------------------------------------------
#ifdef X07W
//#define D_FG0700A2DSSWBG02    //150108 mike 
//#define AUO_G070VW01_V0			//800x480
//#define AUO_G057VN01_V1			//800x480
#define SGD_GVTW70SNAD1E0		//800x480@60
#endif 
//-----------------------------
//#define AUO_G151EVN01_720       	//GAMMA 2.3 		X19N AD-BOARD 1280*720
//#define AUO_G151EVN01_1024      	//GAMMA 2.3 		X19N AD-BOARD 1280*1024

#ifdef X10N
#define   CMO_G104X1_L04         	//150813 george 1024x768
#endif

#ifdef X10W
#define   IVO_M101NWWB_R3         	//160309 george 1280x800	// Panel-ModelName: M101NWWB R3
#endif

#ifdef X15N
#define   AUO_G150XTN05_V0         //140515 mikex 1024
#endif
//-----------------------------
#ifdef X17N						//140515 mike 
#define	AUO_G170ETN01_V0		//140303 mike  gamma 2.2 1280
#endif 

//-----------------------------
#ifdef X19W						// LWO_EWK-1902C
#define	LWO_EWK_1902C			//george 20160223
#endif 

//-----------------------------
#ifdef X173
#define	PET_OT173ZFDDLN_00	//150202 mike 1920x1080 
#endif 
//-----------------------------
#ifdef X215
#define PET_OT215ZFWDLV_02	//150105 mike 
#endif
//-----------------------------
#ifdef X22W
#define CMO_M220ZGE_L20			//140611 mike gamma 2.2 1680
#endif
//-----------------------------
#ifdef X29CutW
#define INL_S290AJ1_LE1			//151117 george
#endif
//-----------------------------

#ifdef X46W
#define AUO_P460HVN03_V0		//141211 mike  
		//if-used= "AUO_P550HVN01_V2, 10->8bit, JEIDA => Panel.h set PANEL_BIT_SHIFT = 1"
#endif


//-----------------------------
//#define LG_LM215WF3_SLK1        	//GAMMA 2.1
//#define LG_LM215WF3_SLC1        	//GAMMA 2.1
//-----------------------------
//#define LG_LM230WF3_SLD1		//GAMMA 2.0
//-----------------------------
//#define AUO_P270HVN010		  	//GAMMA 2.2		//SPECIALAPP  ON   1850X1036
//#define LG_LM270WF5_SLM1		//GAMMA 2.0
//-----------------------------
//#define LC320EUN_SEM2           	//GAMMA 2.4
//#define LC320WXN_SCA4
//#define LD320EUN_SEM1           	//GAMMA 2.4
//-----------------------------
//#define TX38D09VM0CAA			//GAMMA 2.3 		X19N AD-BOARD 1280*242
//-----------------------------
//#define LC420EUN_SFM1           	//GAMMA 2.3
//-----------------------------
//#define LC550EUN_SFM2           	//GAMMA 2.3
//================================================================================================================ 
#ifdef AUO_P270HVN010
	#define SPECIALAPP                 ON		//ON/OFF  //FEFANJACKY FOR 27" TO 26" 1850x1036@60
#else
	#define SPECIALAPP                 OFF		//ON/OFF  //FEFANJACKY FOR 27" TO 26" 1850x1036@60
#endif
//==================================================================================================================


