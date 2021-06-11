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
enum _APPKEYEVENT_ {
    APPEVT_KEY_ONOFF,
    APPEVT_KEY_ON,
    APPEVT_KEY_OFF,
    APPEVT_KEY_SAVING,
    APPEVT_KEY_SOURCE,
    APPEVT_KEY_QUICK_ONOFF,
    APPEVT_KEY_FACTORY,
    APPEVT_KEY_WAKEUP,
    APPEVT_KEY_TIMING_SWITCH,
    APPEVT_KEY_DEMO,
    APPEVT_NONKEY,
    NUM_APP_KEY_EVENTS
} ;

enum _APPOSDEVENT_ {
    APPEVT_OSD_UPD_USR,
    APPEVT_OSD_UPD_SYS,
    APPEVT_OSD_UPD_TMG,
    APPEVT_OSD_UPD_CAL,
    APPEVT_NONOSD,
    NUM_APP_OSD_EVENTS
} ;

enum _APPDDCCIEVENT_ {
    APPEVT_DDCCI_UPD_USR,
    APPEVT_DDCCI_UPD_SYS,
    APPEVT_DDCCI_UPD_TMG,
    APPEVT_DDCCI_UPD_CAL,
    APPEVT_DDCCI_PWR_ON,
    APPEVT_DDCCI_PWR_OFF,
    APPEVT_DDCCI_PWR_SAVING,
    APPEVT_NONDDCCI,
    NUM_APP_DDCCI_EVENTS
} ;

enum {
    APPFLAG_UPD_TMG  = 0x0001,
    APPFLAG_UPD_USR  = 0x0002,
    APPFLAG_UPD_CAL  = 0x0004,
    APPFLAG_UPD_SYS  = 0x0008,
    APPFLAG_LOGO     = 0x0010,
    APPFLAG_NOSYNC   = 0x0020,
    APPFLAG_OUTRANGE = 0x0040,
    APPFLAG_SYSINIT  = 0x0080,
    APPFLAG_NOCABLE  = 0x0100
};

#define IsAPPUpdTmg()   ((usAPPFlags&APPFLAG_UPD_TMG) != 0)
#define IsAPPUpdUsr()   ((usAPPFlags&APPFLAG_UPD_USR) != 0)
#define IsAPPUpdCal()   ((usAPPFlags&APPFLAG_UPD_CAL) != 0)
#define IsAPPUpdSys()   ((usAPPFlags&APPFLAG_UPD_SYS) != 0)

#if IR_REMOT_CTL == DISABLE
	#define IsAPPLogo()     ((usAPPFlags&APPFLAG_LOGO) != 0)
#endif

#define IsAPPNoSync()   ((usAPPFlags&APPFLAG_NOSYNC) != 0)
#define IsAPPOutRange() ((usAPPFlags&APPFLAG_OUTRANGE) != 0)
#define IsAPPSysInit()  ((usAPPFlags&APPFLAG_SYSINIT) != 0)
#define IsAPPNoCable()  ((usAPPFlags&APPFLAG_NOCABLE) != 0)

#define SetAPPUpdTmgFlag()   {usAPPFlags |= APPFLAG_UPD_TMG;}
#define SetAPPUpdUsrFlag()   {usAPPFlags |= APPFLAG_UPD_USR;}
#define SetAPPUpdCalFlag()   {usAPPFlags |= APPFLAG_UPD_CAL;}
#define SetAPPUpdSysFlag()   {usAPPFlags |= APPFLAG_UPD_SYS;}
#define SetAPPLogoFlag()     {usAPPFlags |= APPFLAG_LOGO;}
#define SetAPPNoSyncFlag()   {usAPPFlags |= APPFLAG_NOSYNC;}
#define SetAPPSysInitFlag()  {usAPPFlags |= APPFLAG_SYSINIT;}
#define SetAPPOutRangeFlag() {usAPPFlags |= APPFLAG_OUTRANGE;}
#define SetAPPNoCableFlag()  {usAPPFlags |= APPFLAG_NOCABLE;}

#define ClearAPPUpdTmgFlag() {usAPPFlags &= ~APPFLAG_UPD_TMG;}
#define ClearAPPUpdUsrFlag() {usAPPFlags &= ~APPFLAG_UPD_USR;}
#define ClearAPPUpdCalFlag() {usAPPFlags &= ~APPFLAG_UPD_CAL;}
#define ClearAPPUpdSysFlag() {usAPPFlags &= ~APPFLAG_UPD_SYS;}
#define ClearAPPLogoFlag()   {usAPPFlags &= ~APPFLAG_LOGO;}
#define ClearAPPNoSyncFlag() {usAPPFlags &= ~APPFLAG_NOSYNC;}
#define ClearAPPOutRangeFlag() {usAPPFlags &= ~APPFLAG_OUTRANGE;}
#define ClearAPPSysInitFlag() {usAPPFlags &= ~APPFLAG_SYSINIT;}
#define ClearAPPNoCableFlag() {usAPPFlags &= ~APPFLAG_NOCABLE;}

#define ClearAPPUpdFlag() { \
    usAPPFlags &= ~(APPFLAG_UPD_TMG|APPFLAG_UPD_USR|APPFLAG_UPD_CAL|APPFLAG_UPD_SYS); \
}
#define ClearAPPSyncFlag() { \
    usAPPFlags &= ~(APPFLAG_NOSYNC|APPFLAG_OUTRANGE|APPFLAG_NOCABLE); \
}
#define ClearAPPAllFlag() {usAPPFlags = 0x00;}

#if USE_INTERNAL_EDID == 1
    #define EDIDProtectOn() { \
        McuSetDDCWP(MCU_DDC_0,ON); \
        McuSetDDCWP(MCU_DDC_1,ON); \
        McuSetDDCWP(MCU_DDC_2,ON); \
        McuSetDDCWP(MCU_DDC_3,ON); \
        EdidWPOn(); \
    }
    #define EDIDProtectOff() { \
        McuSetDDCWP(MCU_DDC_0,OFF); \
        McuSetDDCWP(MCU_DDC_1,OFF); \
        McuSetDDCWP(MCU_DDC_2,OFF); \
        McuSetDDCWP(MCU_DDC_3,OFF); \
        EdidWPOff(); \
    }
#else
    #define EDIDProtectOn()  EdidWPOn()
    #define EDIDProtectOff() EdidWPOff()
#endif


//******************************************************************************
// S T A T I C   V A R I A B L E S
//******************************************************************************
static code UCHAR ucKey2APPEventTable[NUM_KEY_EVENTS] = {
    APPEVT_KEY_ONOFF,           //KEYEVT_PWR
    APPEVT_NONKEY,              //KEYEVT_MENU
    APPEVT_NONKEY,              //KEYEVT_AUTO
    APPEVT_KEY_SOURCE,          //KEYEVT_INPUT,
    APPEVT_KEY_QUICK_ONOFF,     //KEYEVT_FUNC,
    APPEVT_NONKEY,              //KEYEVT_UP
    APPEVT_KEY_WAKEUP,          //KEYEVT_DOWN
    APPEVT_NONKEY,              //KEYEVT_LEFT
    APPEVT_NONKEY,              //KEYEVT_RIGHT
    APPEVT_KEY_FACTORY,         //KEYEVT_FACT
    APPEVT_NONKEY,              //KEYEVT_PWLOCK
    APPEVT_NONKEY,              //KEYEVT_OSDLOCK
    APPEVT_KEY_TIMING_SWITCH,   //KEYEVT_TIMING_SWITCH
    APPEVT_KEY_DEMO,         //KEYEVT_DEMO
    APPEVT_NONKEY               //KEYEVT_NONE
};

static code APPAction ucAPPKeyActionTable[NUM_APP_KEY_EVENTS] = {
    APPATN_PWR_ONOFF,       //APPEVT_KEY_ONOFF
    APPATN_PWR_ON,          //APPEVT_KEY_ON
    APPATN_PWR_OFF,         //APPEVT_KEY_OFF
    APPATN_PWR_SAVING,      //APPEVT_KEY_SAVING
    APPATN_CH_SOURCE,       //APPEVT_KEY_SOURCE
    APPATN_QUICK_ONOFF,     //APPEVT_KEY_QUICK_ONOFF
    APPATN_SET_FACTORY,     //APPEVT_KEY_FACTORY
    APPATN_WAKEUP,          //APPEVT_KEY_WAKEUP
    APPATN_TIMING_SWITCH,   //APPEVT_KEY_TIMING_SWITCH
    APPATN_SET_DEMO,             //APPEVT_KEY_DEMO
    APP_NON_ACTION          //APPEVT_NONKEY
};

static code UCHAR ucOSD2APPEventTable[NUM_OSD_EVENTS] = {
    APPEVT_OSD_UPD_USR, //OSDEVT_UPD_USR,
    APPEVT_OSD_UPD_SYS, //OSDEVT_UPD_SYS,
    APPEVT_OSD_UPD_TMG, //OSDEVT_UPD_TMG,
    APPEVT_OSD_UPD_CAL, //OSDEVT_UPD_CAL,
    APPEVT_NONOSD       //OSD_NON_EVENT,
};

static code APPAction ucAPPOSDActionTable[NUM_APP_OSD_EVENTS] = {
    APPATN_UPD_USR,     //APPEVT_OSD_UPD_USR,
    APPATN_UPD_SYS,     //APPEVT_OSD_UPD_SYS,
    APPATN_UPD_TMG,     //APPEVT_OSD_UPD_TMG,
    APPATN_UPD_CAL,     //APPEVT_OSD_UPD_CAL,
    APP_NON_ACTION      //APPEVT_NONOSD,
};

static code UCHAR ucDDCCi2APPEventTable[NUM_DDCCI_EVENTS] = {
    APPEVT_DDCCI_UPD_USR, //DDCCIEVT_UPD_USR,
    APPEVT_DDCCI_UPD_SYS, //DDCCIEVT_UPD_SYS,
    APPEVT_DDCCI_UPD_TMG, //DDCCIEVT_UPD_TMG,
    APPEVT_DDCCI_UPD_CAL, //DDCCIEVT_UPD_CAL,
    APPEVT_DDCCI_PWR_ON, //DDCCIEVT_PWR_ON,
    APPEVT_DDCCI_PWR_OFF, //DDCCIEVT_PWR_OFF,
    APPEVT_DDCCI_PWR_SAVING, //DDCCIEVT_PWR_SAVING,
    APPEVT_NONDDCCI       //DDCCIEVT_NON,
};

static code UCHAR ucAPPDDCCiActionTable[NUM_APP_DDCCI_EVENTS] = {
    APPATN_UPD_USR, //APPEVT_DDCCI_UPD_USR,
    APPATN_UPD_SYS, //APPEVT_DDCCI_UPD_SYS,
    APPATN_UPD_TMG, //APPEVT_DDCCI_UPD_TMG,
    APPATN_UPD_CAL, //APPEVT_DDCCI_UPD_CAL,
    APPATN_PWR_ON, //APPEVT_DDCCI_PWR_ON,
    APPATN_PWR_OFF, //APPEVT_DDCCI_PWR_OFF,
    APPATN_FORCE_PWR_SAVING, //APPEVT_DDCCI_PWR_SAVING,
    APP_NON_ACTION  //APPEVT_NONDDCCI,
};

static BOOL bIsAPPFirstCalled = TRUE;
static xdata USHRT usAPPFlags = 0x0000;
static xdata UCHAR ucCurSyncState  = 0xFF;
static xdata UCHAR ucPOTCnt_20s = 0;

#if ENABLE_INTERNAL_AUDIO_BUZZER
static BOOL bIsBuzzerEnable = FALSE;
#endif

//******************************************************************************
// E X T E R N A L   V A R I A B L E   P R O T O T Y P E S
//******************************************************************************
#if MD_ENABLE_AO_DETECT == ON
extern bit bWaitPowerKeyRelease;
extern xdata USHRT usAOTimer;
#endif

//******************************************************************************
// S T A T I C   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
static void APPTimerRoutine(void);
static void APPSetSystemPowerState(APPPwrState state);
static UCHAR APPSyncPublisher(void);
static void APPEnterPowerOnLogo(void);
static void APPEscapePowerOnLogo(void);
static void APPClosePowerOnLogo(void);
static void APPTasksBeforeDisplay(void);
static void APPTasksAfterDisplay(void);
static void APPTasksAfterMute(void);
static void APPToggleFactoryMode(void);
static void APPToggleDemoMode(void);
static void APPPerformBurnIn(UCHAR Clr);
static void APPCountRedLed(BOOL rst);
static BOOL APPIsOutOfLimit(void);
#if ENABLE_HW_CEC == ON
static void APPPerformCECReq(void);
#endif
#if ENABLE_SELF_AUTOCOLOR == ON
static void APPIntAutoColor(void);
#endif

//******************************************************************************
// E X T E R N A L   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// Prototype:
//  void APPInitSystem(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Initial all system configuration
// Notes:
//  None
//******************************************************************************
void APPInitSystem(void)
{

    // Initial PWM of backlight control
#if ENABLE_PWM_SMOOTH == ON
    SmoothScalerPWM(BKL_PWM_PORT, 0, 1);//NT68667, 673 and 675 no this function
#endif
    SetBLPwmByInputVSync(FALSE);
    SetVSyncResetPWM(BKL_PWM_PORT, OFF);	//ON);      //150114 mike 

    // Initial PWM of volume control
    ConfigScalerPWM(VOLUME_PWM_PORT, VOLUME_PWM_OUTPUT_PIN, VOLUME_PWM_FREQ);
    SetVSyncResetPWM(VOLUME_PWM_PORT, OFF);
//===================PWM Function ====
//    ConfigScalerPWM(BKL_PWM_PORT, PWMD_PIN_125, BRIGHTNESS_FR_PWM_FREQ);		//140314 mike for PWM
//    SetVSyncResetPWM(BKL_PWM_PORT,OFF);											//140314 mike for PWM
//================================ 
    UserSetOSDH();
    UserSetOSDV();
    UserSetTransparent();
    UserSetTimeout();
    UserSetOSDRotation();

// We move the LOGO to the begin of APPInitSystem to reduce the power on time.

#if MD_ENABLE_AO_DETECT == ON

    if ((AO_DETECT & BIT2) != 0) 
    {
        AO_DETECT |= BIT2;
        bWaitPowerKeyRelease = TRUE;
        usAOTimer = GetTimerTick();
		if (UserData.bPowerStatus == OFF) 
		{
              UserData.bPowerStatus = ON;
              SetAPPUpdUsrFlag();
            if (CheckFactoryMode() == TRUE) 
			{
                APPToggleFactoryMode();
                SetAPPUpdSysFlag();
			}
		}
    }
    else{
        		bWaitPowerKeyRelease = FALSE;
	}

    if (SystemData.bFactory == TRUE) 
	{
		if ((AO_DETECT & BIT4) != 0) 
		{
			do{
    				ResetWDTimer();
        			AO_DETECT |= BIT4;
    				Sleep(AO_KEY_DEBOUNCE_TIME); //wait HW debounce
			} while ((AO_DETECT & BIT4) != 0);

        	if (UserData.bPowerStatus == OFF) 
	     	{
            		UserData.bPowerStatus = ON;
            		SetAPPUpdUsrFlag();
            	if (CheckFactoryMode() == TRUE) 
		 		{
                	APPToggleFactoryMode();
                	SetAPPUpdSysFlag();
            	}
            }
        }
    }
#endif

    if (UserData.bPowerStatus == ON)
	{
        	LedGreenOn();
        if (bIsAPPFirstCalled) 
		{
        	APPEnterPowerOnLogo();
        }
        else {
        	OSDInitialize(TRUE);
        }
    }

    // Enable Audio Power
    AudioPowerOn();

    #if ENABLE_HDCP == ON
    #if ENABLE_HDCP_TRIM_MODE == ON
        ucEFUSETrimSucess = 0xFF;
        if ((GetSCID() == SCID_661) && (GetEFUSE_SCID() == SCID_661)) {//NT68661
            ucEFUSETrimSucess = InitHDCPTrimKey();
        }
        else if ((GetSCID() == SCID_655) && (GetEFUSE_SCID() == SCID_655)) {//NT68655
            ucEFUSETrimSucess = InitHDCPTrimKey();
        }
        else if (GetSCID() == SCID_770_G) {//NT6877x Version G/...
            ucEFUSETrimSucess = InitHDCPTrimKey();
        }
        else if ((GetSCID() == SCID_850) && (GetEFUSE_SCID() == SCID_850)) {//NT68655
            ucEFUSETrimSucess = InitHDCPTrimKey();
        }
        else
    #endif
        {
    		InitHDCP();
        }
    #endif

#if ENABLE_PRE_REV_GAMMA == ON
    LoadPreGamma();
    LoadRevGamma();
#endif

#if ENABLE_GAMMA == ON
    LoadGamma();
#endif

    InitColor();
#if ENABLE_DBC == ON
    InitDBC();
#endif

#if ENABLE_LD == ON
    InitLD();
#endif

#if ENABLE_SR == ON
    InitSR();
#endif

#if ENABLE_3D_CNV == ON
    InitScaler3D();
#endif

    // Initial user data
    UserSetADCGainOffset();
//150114 mike    UserSetBrightness();
    UserSetContrast();
    UserSetColorTemp();
//    UserSetOSDH();
//    UserSetOSDV();
//    UserSetTransparent();
//    UserSetTimeout();
//    UserSetOSDRotation();
    //UserSetAudioMute();
    UserSetVolume();

#if ENABLE_ASPECT_RATIO == ON	//george 20160217
    UserSetAspectRatio();
#endif

    UserSetOD();
    //UserSetBF();    // Move UserSetBF to APPTasksBeforeDisplay to avoid wrong BF window setting
    //UserSetDCR();   // Move UserSetDCR to APPTasksBeforeDisplay to avoid DCR/DBC in showing logo period
    UserSetGamma();
    UserSetInputSource();
    
    //CHIU INITINAL INVERTER VALUE
    SYSAPI_SetInverterVal(CalibData.ucBacklite);   
    
    
#if ENABLE_3D_CNV == ON
    UserSet2DTo3DMode();
    UserSet2DTo3DAdaptive();
    UserSet2DTo3DDepth();
    UserSet2DTo3DView();
    UserSet3DLRSwap();
    UserSet3DTo2D();
#endif    
    SetSyncSource(UserData.bAutoSyncSource);
    
    // Init key configuration
    KeySetRepeatEvent(0xFF, OFF);
    KeySetHoldEvent(0xFF, OFF);
    KeySetMFuncEvent(0xFF, 0x00);
    KeySetHoldTime(KEY_HOLD_TIME);
    KeySetRepeatTime(KEY_REPEAT_TIME);
    KeySetLongPressTime(KEY_LONG_PRESS_TIME);

#if ENABLE_HW_CEC == ON
    APPRequestCECAct(CECATN_SET_LANGUAGE);
#endif
    
    if (SystemData.bFactory) {
        EDIDProtectOff();
#if ENABLE_SELF_AUTOCOLOR == ON
        APPIntAutoColor();
#endif
    }

    if (UserData.bPowerStatus != ON) {
        SYSAPI_SetPowerOff();
    }
	
#if (INPUT_INTERFACE&INPUT_DP)
    else {
        DPHPDOn();
    }
#endif

#if ((INPUT_INTERFACE&INPUT_MHL0) || (INPUT_INTERFACE&INPUT_MHL1))// && ENABLE_HDMI_PRETEST == ON
    ToggleRxSense();
#endif

#if IR_REMOT_CTL == ON		//150521 George

	//IR_Initalize()
	{
		//enable EXT INT
    	INTEXT_FLG |= INTE2;
		INTEXT_EN  |= INTE2;
	}
#endif


    bIsAPPFirstCalled = FALSE;
}

//******************************************************************************
// Prototype:
//  void APPActionDispatcher(UCHAR event)
// Parameters:
//  event   : Perform system action by global event id
// Return:
//  None
// Purpose:
//  Dispatch action to system. ex: power saving, power off etc...
// Notes:
//  None
//******************************************************************************
void APPActionDispatcher(UCHAR event)
{
    APPAction act = APP_NON_ACTION;


    if (GetGlobalEvent(event) == KEY_RELATED_EVENT) {

//gg1
if(event == KEYEVT_INPUT){
	event = KEYEVT_NONE; 
	//printf("(Z)_KEYEVT_INPUT_\n");
	//if run event = KEYEVT_INPUT will be reboot MCU.  why?
}
        event = GetLocalEvent(event);
        event = ucKey2APPEventTable[event];
        if (event != APPEVT_NONKEY) {
            act = ucAPPKeyActionTable[event];		//george: 10 state
            //printf("APPActionDispatcher->KeyEvent(%bx) Action(%bx)\n\r", event, act);

#if BurnIn_Degub == ENABLE
	printf("APP= %d\n", (USHRT) act);
#endif
        }
    }
    else if (GetGlobalEvent(event) == OSD_RELATED_EVENT) {
        event = GetLocalEvent(event);
        event = ucOSD2APPEventTable[event];
        if (event != APPEVT_NONOSD) {
            act = ucAPPOSDActionTable[event];		//george: 4 state
            //printf("APPActionDispatcher->OSDEvent(%bx) Action(%bx)\n\r", event, act);
        }
    }
    else if (GetGlobalEvent(event) == DDCCI_RELATED_EVENT) {
        event = GetLocalEvent(event);
        event = ucDDCCi2APPEventTable[event];
        if (event != APPEVT_NONDDCCI) {
            act = ucAPPDDCCiActionTable[event];		//george: 6 state
            //printf("APPActionDispatcher->DDCCiEvent(%bx) Action(%bx)\n\r", event, act);
        }
    }
    else {
    }

    switch(act) 
	{
		case APPATN_SET_DEMO:	//CHIU MENU + PWR BURNIN MODE
#if BurnIn_Degub == ENABLE
	printf("******Burn-In-Mode*******\n");	//george  no-used
#endif	 		
            APPToggleDemoMode();            
            APPSetSystemPowerState(APPSTATE_PWR_ON);
            SetGlobalTimer(GLOBAL_TMR_DATA_UPDATE, GBTM_DATA_UPDATE);
            SetAPPUpdSysFlag();
			OSDShowNoCable(); //gg

#if BurnIn_Degub == ENABLE
	printf("FF\n");
#endif

//            OSDShowNoCable();	//CHIU FIX STRING ERROR
	     break;


        case APPATN_SET_FACTORY:
             APPToggleFactoryMode();
#if BurnIn_Degub == ENABLE
	printf("------FACTORY-Mode----\n");	//george
#endif			 
            //APPSetSystemPowerState(APPSTATE_PWR_ON);  //FEFANJACKY DEL
            SetGlobalTimer(GLOBAL_TMR_DATA_UPDATE, GBTM_DATA_UPDATE);
            SetAPPUpdSysFlag();
            OSDEnterFactory();   //fefanjacky add for into factory mode
            break;


        case APPATN_PWR_ONOFF:
        #if ENABLE_HW_CEC == ON
            APPRequestCECAct(CECATN_STANDBY); // The standby command must be prior to system standby command!! // Jude 2009/03/08
        #endif
            APPSetSystemPowerState(APPSTATE_PWR_ONOFF);
            SetGlobalTimer(GLOBAL_TMR_DATA_UPDATE, GBTM_DATA_UPDATE);
            SetAPPUpdUsrFlag();
            break;
        case APPATN_PWR_ON:
            APPSetSystemPowerState(APPSTATE_PWR_ON);
            SetGlobalTimer(GLOBAL_TMR_DATA_UPDATE, GBTM_DATA_UPDATE);
            SetAPPUpdUsrFlag();         
            break;
        case APPATN_PWR_OFF:
            APPSetSystemPowerState(APPSTATE_PWR_OFF);
            SetGlobalTimer(GLOBAL_TMR_DATA_UPDATE, GBTM_DATA_UPDATE);
            SetAPPUpdUsrFlag();
            break;
        case APPATN_PWR_SAVING:
#if BurnIn_Degub == ENABLE
	printf("AA\n");
#endif
            APPSetSystemPowerState(APPSTATE_PWR_SAVING);
            break;
        case APPATN_FORCE_PWR_SAVING:
            APPSetSystemPowerState(APPSTATE_FORCE_PWR_SAVING);
            break;
        case APPATN_CH_SOURCE:
            UserData.ucInputSource = GetInputPortName((GetInputPortIndex(UserData.ucInputSource)+1)%NUM_INPUT_SC);
            UserSetInputSource();
            break;
        case APPATN_QUICK_ONOFF:
#if ENABLE_3D_CNV == ON
            if (UserData.uc2DTo3DMode != THR_D_CNV_2D_TO_3D) {
                UserData.uc2DTo3DMode = THR_D_CNV_2D_TO_3D;
            }
            else {
                UserData.uc2DTo3DMode = THR_D_CNV_OFF;
            }
            UserSet2DTo3DMode();
            SetModeChangeFlag();
            SetAPPUpdUsrFlag();
#endif
            break;
        case APPATN_UPD_USR:
            SetGlobalTimer(GLOBAL_TMR_DATA_UPDATE, GBTM_DATA_UPDATE);
            SetAPPUpdUsrFlag();
            break;
        case APPATN_WAKEUP:
            APPSetSystemPowerState(APPSTATE_WAKEUP);
            break;
        case APPATN_UPD_SYS:
            SetGlobalTimer(GLOBAL_TMR_DATA_UPDATE, GBTM_DATA_UPDATE);
            SetAPPUpdSysFlag();
            break;
        case APPATN_UPD_TMG:
            SetGlobalTimer(GLOBAL_TMR_DATA_UPDATE, GBTM_DATA_UPDATE);
            SetAPPUpdTmgFlag();
            break;
        case APPATN_UPD_CAL:
            SetGlobalTimer(GLOBAL_TMR_DATA_UPDATE, GBTM_DATA_UPDATE);
            SetAPPUpdCalFlag();
            break;
        case APPATN_TIMING_SWITCH:
            SimilarTimingSwitch();
            break;
        case APP_NON_ACTION:

        default :

            break;
    }

}

//******************************************************************************
// Prototype:
//  UCHAR APPActionDemander(void)
// Parameters:
//  None
// Return:
//  system event
// Purpose:
//  Return system event to other handlers.
// Notes:
//  None
//******************************************************************************
UCHAR APPActionDemander(void)
{
    UCHAR evt;

    // acquire System status
    evt = APPSyncPublisher();
    //   printf("140319 evt = APPSyncPublisher();===> %X\n",(unsigned short)evt); 

    // APPSyncPublisher must be prior to APPTimerRoutine!
    // Otherwise, system may go to power saving state while sync present!
    APPTimerRoutine();  //fefanjacky

    return evt;
}

//******************************************************************************
// Prototype:
//  void APPTimerRoutine(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Periodic routine.
// Notes:
//  None
//******************************************************************************
void APPTimerRoutine(void)
{

#if ENABLE_SET_PWM_MAX_BUFFER == ON
    SetBrightnessPWMMax();
#endif

#if (INPUT_INTERFACE&INPUT_DP)											//20150522 George (complier-be-used)
    DPHandler();
#endif

#if (INPUT_INTERFACE&INPUT_MHL0) || (INPUT_INTERFACE&INPUT_MHL1)		//20150522 George (complier-be-used)
    MHLHandler();
#endif

    // Check EDID update and write it to nvram immediately
#if USE_INTERNAL_EDID == 1												//20150522 George (complier-be-used)
    if (SystemData.bFactory && (McuCheckDDCUpdate() != 0)) 
	{
        	 NvramSaveEDID();
    }
#endif

#if ENABLE_HW_CEC == ON													//20150522 George (complier-non-used)
    APPPerformCECReq();
#endif

#if ENABLE_INTERNAL_AUDIO_BUZZER == ON									//20150522 George (complier-non-used)

    APPCountAudioBuzzer();
#endif

    if ((GetGlobalTimer(GLOBAL_TMR_POT_CNT) == 0) && (IsPanelPowerOn())) 
	{
        SetGlobalTimer(GLOBAL_TMR_POT_CNT, GBTM_POT_CNT);
        ucPOTCnt_20s++;

        if (ucPOTCnt_20s > 3) 
        {
            ucPOTCnt_20s = 1;
            SystemData.ucPowerOnTimerM++;

			#if ENABLE_FE2P == ON												//20150522 George (complier-be-used)
	            RecordTimeScale();
			#endif

            if (SystemData.ucPowerOnTimerM > 59) 
            {
                SystemData.ucPowerOnTimerM = 0;
                if (SystemData.usPowerOnTimerH != 0xffff) 
                {
                   	 SystemData.usPowerOnTimerH++;

					#if ENABLE_FE2P == ON											//20150522 George (complier-be-used)
		                    if ((SystemData.usPowerOnTimerH % POT_SAVE_H) == 0) 	// Save POT time every 5460 hour (4095*8/6)
		                    { 
		                        	SystemData.ucPOTimerM_FE2P = SystemData.ucPowerOnTimerM;
		                        	SystemData.usPOTimerH_FE2P = SystemData.usPowerOnTimerH;
		                        	NvramWriteSystemData(&SystemData);
		                        	FE2P_SaveToFlash();
		                        	EraseTimeScale();
		                    }
					#else
							SetAPPUpdSysFlag(); // Save POT time every hours
					#endif
                }
            }
        }
    }

    if (GetGlobalTimer(GLOBAL_TMR_DATA_UPDATE) == 0) 
	{
        SetGlobalTimer(GLOBAL_TMR_DATA_UPDATE, GBTM_DATA_UPDATE);
        if (IsAPPUpdTmg() &&
            (GetInputSyncMode() != DIG_SYNC) &&
            ((GetModeHandleState() == WAIT_DISPLAY_READY) || (GetModeHandleState() == WAIT_MODE_CHANGE))) {
            NvramWriteTimingData(&InputTiming);
            //printf("APPTimerRoutine->Update Timing\n\r");
        }
        if (IsAPPUpdUsr()) {
            NvramWriteUserData(&UserData);
            //printf("APPTimerRoutine->Update UserData\n\r");
        }
        if (IsAPPUpdCal()) {
            NvramWriteCalibData(&CalibData);
            //printf("APPTimerRoutine->Update Cal\n\r");
        }
        if (IsAPPUpdSys()) {
            NvramWriteSystemData(&SystemData);
            //printf("APPTimerRoutine->Update System\n\r");
        }
        ClearAPPUpdFlag();

    #if ENABLE_FE2P == ON
        FE2P_SaveToFlash();
    #endif
    }

    if (IsAPPLogo()) 
	{
        if (GetGlobalTimer(GLOBAL_TMR_LOGO_TIMEOUT) == 0) {
            APPClosePowerOnLogo();
        }
    }

    else if (IsAPPNoSync())
	{
		#if ENABLE_HDMI_PRETEST == OFF
	
			#if (INPUT_INTERFACE&INPUT_MHL0) || (INPUT_INTERFACE&INPUT_MHL1)
			        if ( IsMHL0Connect() || IsMHL1Connect() ) {
			           // do not enter power saving if MHL cable connected
			        }
			        else
			#endif
	
	        if (GetGlobalTimer(GLOBAL_TMR_PWR_SAVING) == 0) 
			{
	            //printf("APPTimerRoutine->Enter Power Saving State\n\r");
				
				#if BurnIn_Degub == ENABLE
					printf("GG\n");
				#endif
	
	            APPSetSystemPowerState(APPSTATE_PWR_SAVING);									
	            ClearAPPNoSyncFlag();
	            SetGlobalTimer(GLOBAL_TMR_LED_FLASH, GBTM_LED_FLASH);
	            APPCountRedLed(TRUE);
	        }
		#endif
    }
	
	
	else if (IsAPPNoCable()) 
	{
		if (SystemData.bFactory)    //fefanjacky
		//if (SystemData.bDemo) 
		{
			if (GetGlobalTimer(GLOBAL_TMR_PWR_SAVING) == 0) 
			{			
				#if BurnIn_Degub == ENABLE
					printf("APPTimerRoutine->Burn In Pattern\n\r");
				#endif
                APPPerformBurnIn(0);
                SetGlobalTimer(GLOBAL_TMR_PWR_SAVING, GBTM_FACT_BURNIN);
			}
		}
    }
    
	
	else if (IsAPPOutRange()) 
	{
		if (GetGlobalTimer(GLOBAL_TMR_PWR_SAVING) == 0) 
		{
            		 //printf("APPTimerRoutine->Enter Power Saving State\n\r");
            		 APPSetSystemPowerState(APPSTATE_FORCE_PWR_SAVING);
            		 ClearAPPOutRangeFlag();
		}
    }
    else if (GetModeHandleState() == POWER_SAVING_MODE) 
	{
		if (GetGlobalTimer(GLOBAL_TMR_LED_FLASH) == 0) 
		{
    				SetGlobalTimer(GLOBAL_TMR_LED_FLASH, GBTM_LED_FLASH);
    				APPCountRedLed(FALSE);
		}
	}
    else if (GetModeHandleState() == WAIT_MODE_CHANGE) 
	{
    	#if ENABLE_DBC == ON
        	if ( UserData.ucDCRMode == BKL_CTRL_DBC ) 
			{
            			DBCBrightnessTracker();
        		#if ENABLE_DBC_HW_DEBOUNCE == OFF
            			AntiNoiseDBC();
        		#endif
			}
        	else 
			{
            			DisableDBCSmooth(FALSE);
            			PerformDCR(0);
			}

	    #else
			PerformDCR(0);
	    #endif

		#if IR_REMOT_CTL == ON
			//ucIRReleaseCountCheck();
		#endif

		#if ENABLE_3D_CNV == ON
    		PerformAdaptive2DTO3D();
		#endif

		#if (ENABLE_LD == ON)&& (ENABLE_DYNAMIC_LD == ON) 
			if(UserData.ucBFMode != LD_OFF) 
			{
					PerformDynamicLD();
			}
		#endif
    }


/*	if (GetGlobalTimer(GLOBAL_TMR_USR1) == 0) 				//george
	{
//        
		printf("#_GLOBAL_TMR_USR1_Test\n");
		SetGlobalTimer(GLOBAL_TMR_USR1, GBTM_ALS_UPDATE);
	}*/

}

//******************************************************************************
// Prototype:
//  void APPSetSystemPowerState(APPPwrState state)
// Parameters:
//  state   : system power state
// Return:
//  None
// Purpose:
//  Set system power state
// Notes:
//  None
//******************************************************************************
void APPSetSystemPowerState(APPPwrState state)
{

    switch(state) 
	{
        case APPSTATE_PWR_ONOFF:
			if (GetModeHandleState() != SOFT_POWER_OFF) 
			{
				if (IsAPPLogo()) 
			    {
                    	APPEscapePowerOnLogo();
				}
               			UserData.bPowerStatus = OFF;
//---------------------------------------------------------------------------------
//printf("_APP-S_PWR_ON/OFF:_\n");	//kk
               			SystemData.bFactory = FALSE; //FEFANJACKY ADD 2013-05015
						APPPerformBurnIn(1); 		 //george 20160215, clear ucBurnInPtnID value
                		SystemData.bDemo = FALSE;
                		SetAPPUpdSysFlag();
//---------------------------------------------------------------------------------
                		SYSAPI_SetPowerOff();
			
			}
            else 
			{
                		UserData.bPowerStatus = ON;
                		SYSAPI_SetPowerOn();
                		UserSetInputSource();
                		APPEnterPowerOnLogo();
			
            }
            break;

        case APPSTATE_PWR_OFF:
//printf("_APP-S_PWR_OFF:_\n");	//kk
			if (IsAPPLogo()) 
			{
                APPEscapePowerOnLogo();
			}
            UserData.bPowerStatus = OFF;
            SYSAPI_SetPowerOff();
            break;

        case APPSTATE_PWR_ON:
//printf("_APP-S_PWR_ON:_\n");	//kk
            UserData.bPowerStatus = ON;
            SYSAPI_SetPowerOn();
            UserSetInputSource();
            APPEnterPowerOnLogo();
//g	printf("0514_A00\n");
            break;
        
		case APPSTATE_PWR_SAVING:
//kk printf("bDemo= %d\n", (USHRT)SystemData.bDemo);
//printf("_APP-S_PWR_Saving:_\n");	//kk
#if BurnIn_Degub == ENABLE
	printf("AB\n");
#endif
            SYSAPI_PowerSaving();
            break;

        case APPSTATE_FORCE_PWR_SAVING:
//printf("_APP-S_Foree_PWR_Saving:_\n");	//kk
            SYSAPI_ForcePowerSaving();
            break;

        case APPSTATE_WAKEUP:
//printf("_APP-S_Wakeup:_\n");	//kk
            if (GetModeHandleState() == POWER_SAVING_MODE) 
			{ 
                	SYSAPI_SetPowerOn();
                	UserSetInputSource();
			}
            break;
        default :
            break;
    }
}
//******************************************************************************
// Prototype:
//  void APPResendAppSync(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Re-send APP-level sync state.
// Notes:
//  This function is called externally by OSD
//******************************************************************************
void APPResendAppSync(void)
{
    ucCurSyncState  = 0xFF;
}

//******************************************************************************
// Prototype:
//  static void APPTasksBeforeDisplay(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Perform user-specific tasks before showing images.
// Notes:
//  This function is called externally by ModeHandler
//******************************************************************************
static void APPTasksBeforeDisplay(void)
{
    // Add any user specific function here.
    SetBLPwmByInputVSync(TRUE);
    UserSetBF();
    UserSetAudioChannel();
    UserSetVolume();

#if IS_NT68661_SERIES || IS_NT68770_SERIES || IS_NT68850_SERIES || IS_NT68655_SERIES || IS_NT68790_SERIES
#if ENABLE_SR == ON    
     SetSRBlockOnOff(ON);
#endif    
#endif

}

//******************************************************************************
// Prototype:
//  static void APPTasksAfterDisplay(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Perform user-specific tasks before showing images.
// Notes:
//  This function is called externally by ModeHandler
//******************************************************************************
static void APPTasksAfterDisplay(void)
{
    // Add any user specific function here.
    UserSetAudioMute();
    UserSetDCR();
#if ENABLE_LD == ON
    UserSetLD();
#endif
#if ENABLE_SR == ON
    UserSetSR();
#endif
    RecordCurrentSource(FALSE);
}

//******************************************************************************
// Prototype:
//  static void APPTasksAfterMute(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Perform user-specific tasks After muting images.
// Notes:
//  This function is called internally by APPSyncPublisher
//******************************************************************************
static void APPTasksAfterMute(void)
{

#if ENABLE_PREFRC == ON || ENABLE_DFR == ON
    SC_FRC_CTRL = 0x00; //FRC/DFR OFF
#endif
#if ENABLE_LOW_PWR_MODE == ON
    if (IsZpMode()) {
        PowerUpRegisterAccess();
    }
#endif
#if ENABLE_LD == ON
    LDAPI_SetLDMode(LD_OFF);
#endif
#if ENABLE_SR == ON
    SetSRMode(SR_MODE_OFF);
#if IS_NT68661_SERIES || IS_NT68770_SERIES || IS_NT68850_SERIES || IS_NT68655_SERIES || IS_NT68790_SERIES
    SetSRBlockOnOff(OFF);
#endif
#endif
#if ENABLE_SCALER_3D == ON
    SC3DAPI_TurnOff3DMode();
#endif
    AudioMuteOn();									
    SetBLPwmByInputVSync(FALSE);
#if ENABLE_DBC == ON
    DisableDBC();
#else
    DisableDCR();
#endif
    BFAPI_DisableWindow(BF_WINDOW_1);
    BFAPI_DisableWindow(BF_WINDOW_2);

#if ENABLE_LOW_PWR_MODE == ON
    if (IsZpMode()) {
        PowerDownRegisterAccess();
    }
#endif
}

//******************************************************************************
// Prototype:
//  static APPEvent APPSyncPublisher(void)
// Parameters:
//  None
// Return:
//  Return sync event
// Purpose:
//  Periodically check sync state and publish event if any state changed.
// Notes:
//  None
//******************************************************************************
static UCHAR APPSyncPublisher(void)
{

    static UCHAR nosync_evt = APPEVT_NONE;
    UCHAR evt, state, mode;

    if (IsAPPLogo()) 
	{
          return APPEVT_NONE;
	}
    
    evt = APPEVT_NONE;
    state = GetModeHandleState();
    mode = (state << 4) | GetInputSyncMode();

    if (ucCurSyncState != mode) 
	{
       	nosync_evt = APPEVT_NONE;
        	ucCurSyncState = mode;
        	mode = GetInputSyncMode();

        	switch (state) 
			{
					case WAIT_MODE_CHANGE:
                			if (mode == NO_SYNC) 
					 		{
                    				evt = APPEVT_NO_SYNC;
                			}
                			else if (mode == NO_CABLE) 
							{
                    				evt = APPEVT_NO_CABLE;
                			}
                			else if (mode == OUT_SYNC) 
							{
                    				evt = APPEVT_OOR;
                			}
                			else 
							{
                    				evt = APPEVT_NML;
                			}
                			break;
					case WAIT_SYNC_STABLE:
							if (mode == NO_SYNC) 
					    	{
                    				evt = APPEVT_NO_SYNC;
                			}
                			else if (mode == NO_CABLE)
							{
                    				evt = APPEVT_NO_CABLE;
                			}
                			else 
							{
                    				evt = APPEVT_UNSTABLE;
                			}
                			break;
            		case WAIT_DISPLAY_READY:
                				evt = APPEVT_PRE;
                				break;
            		case SYNC_IS_STABLE:
                				//evt = APPEVT_NML;
                				break;
            		case POWER_SAVING_MODE:
                				evt = APPEVT_PW_SAVING;
                				break;
            		case SOFT_POWER_ON:
                				evt = APPEVT_PW_ON;
                				break;
            		case SOFT_POWER_OFF:
                				evt = APPEVT_PW_OFF;
//g putchar(0x01);
//g printf("APPSyncPublisher  SOFT_POWER_OFF\n");	//george
                				break;
            		default:
                		break;
			}

        	if (evt != APPEVT_NONE) 
			{
            		ClearAPPSyncFlag();

            		if (evt == APPEVT_PRE) 
					{
                			// Perform routines before display
                			APPTasksBeforeDisplay();
            		}
					//            else if (evt != APPEVT_NML) {
            		else if ((evt != APPEVT_NML) && (evt != APPEVT_PW_OFF) && (evt != APPEVT_PW_SAVING)) 
					{
                			// Turn off panel power and perform routines when display is absent
                			PanelPowerOffSequence();
                			APPTasksAfterMute();
            		}
            		else if (evt == APPEVT_NML) 
					{
                			APPTasksAfterDisplay();
                			if (APPIsOutOfLimit())
							{
                				evt = APPEVT_OOL;
                			}
            		}
       		}
  //      printf("APPSyncPublisher->SyncState(%bx) Event(%bx)\n\r", ucCurSyncState, evt);
    }

    // Publish nosync state after GBTM_APPSYNC_STABLE(ms)
    if ((evt == APPEVT_NO_SYNC) || (evt == APPEVT_NO_CABLE)) 
	{
        nosync_evt = evt;
        SetGlobalTimer(GLOBAL_TMR_APPSYNC_STABLE, GBTM_APPSYNC_STABLE);
        evt = APPEVT_UNSTABLE;
	}
    // Publish nosync state after 2000ms

    if (nosync_evt != APPEVT_NONE) 
	{
        if (GetGlobalTimer(GLOBAL_TMR_APPSYNC_STABLE) == 0) 
	    {
            evt = nosync_evt;
            nosync_evt = APPEVT_NONE;
            SetGlobalTimer(GLOBAL_TMR_PWR_SAVING, GBTM_NOSYNC_PWR_SAVING);
		}
	}

    if (evt == APPEVT_NO_SYNC) 
	{
        SetAPPNoSyncFlag();
	}
    else if (evt == APPEVT_NO_CABLE) 
	{
        SetAPPNoCableFlag();
	}
    else if (evt == APPEVT_OOR) 
	{
        SetGlobalTimer(GLOBAL_TMR_PWR_SAVING, GBTM_OOR_PWR_SAVING);
        SetAPPOutRangeFlag();
	}   

    return evt;

}

//******************************************************************************
// Prototype: 
//  static void APPEnterPowerOnLogo(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Show power-on logo
// Notes:
//  None
//******************************************************************************
static void APPEnterPowerOnLogo(void)
{
    if (SystemData.bShowLogo) {
		/*
        ShowLogo();
        KeySetLockEvent(0xFF, ON);
        KeySetLockEvent(KEYEVT_PWR, OFF);
        SetAPPLogoFlag();
        HoldModeDisplay();
        SetGlobalTimer(GLOBAL_TMR_LOGO_TIMEOUT, GBTM_LOGO_TIMEOUT);
        */
    }
}

//******************************************************************************
// Prototype:
//  static void APPEscapePowerOnLogo(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Leave logo state
// Notes:
//  None
//******************************************************************************
static void APPEscapePowerOnLogo(void)
{
    KeySetLockEvent(0xFF, OFF);
    ClearAPPLogoFlag();
    ContinueModeDisplay();
}

//******************************************************************************
// Prototype: 
//  static void APPClosePowerOnLogo(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Leave logo state with OSD initialization
// Notes:
//  None
//******************************************************************************
static void APPClosePowerOnLogo(void)
{
    CloseLogo();
    APPEscapePowerOnLogo();
}

//******************************************************************************
// Prototype:
//  static void APPToggleFactoryMode(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Enter Factory Mode
// Notes:
//  None
//******************************************************************************
static void APPToggleFactoryMode(void)
{
    SystemData.bFactory = ~SystemData.bFactory;  //FEFANJACKY MODIFY 2013-05-15

//-------------------------------------------------------------------------------

    if (SystemData.bFactory) {
        EDIDProtectOff();
    }
    else {
        EDIDProtectOn();
    }
}
//******************************************************************************
// Prototype:
//  static void APPToggleDemoMode(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Enter Factory Mode
// Notes:
//  None
//******************************************************************************
static void APPToggleDemoMode(void)
{	//George: No-Used
    SystemData.bDemo = ~SystemData.bDemo;   //fefanjacky
}
//******************************************************************************
// Prototype:
//  static void APPPerformBurnIn(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Display Burn In Pattern
// Notes:
//  None
//******************************************************************************
static void APPPerformBurnIn(UCHAR Clr)
{

    code UCHAR ucBurnInPatterns[] = {
        0xFF,0xFF,0xFF,		//White
        0x00,0x00,0x00,		//Black
        0xFF,0x00,0x00,		//Red
        0x00,0xFF,0x00,		//Green
        0x00,0x00,0xFF,		//Blue
        0xFF,0xFF,0x00,		//Yellow
        0xFF,0x00,0xFF,		//Magenta
        0x00,0xFF,0xFF,		//Cyan
    };
    static UCHAR ucBurnInPtnID = 0x00;

	if(Clr==1)
	{
		ucBurnInPtnID = 0x00;
		return;
	}
    SetPostBGColor(ucBurnInPatterns[ucBurnInPtnID*3],
                   ucBurnInPatterns[ucBurnInPtnID*3+1],
                   ucBurnInPatterns[ucBurnInPtnID*3+2]);

    ucBurnInPtnID = (ucBurnInPtnID+1) % (sizeof(ucBurnInPatterns)/sizeof(char)/3);

#if BurnIn_Degub == ENABLE
	printf("BurnInPattern\n");
#endif

}

//******************************************************************************
// Prototype: 
//  static void APPCountRedLed(BOOL rst)
// Parameters:
//  rst : Reset internal counter
// Return:
//  None
// Purpose:
//  For flashing LED under power saving mode
// Notes:
//  None
//******************************************************************************
static void APPCountRedLed(BOOL rst)
{
    static UCHAR ucLedCnt = 0;


#if KEY_LED_Flash == DISABLE		
    if ((ucLedCnt>10) || rst) {
        LedRedOn();
        ucLedCnt = 0;
    }
    else {
		//LedRedOff();
        LedRedOn();
        ucLedCnt++;
    }
#elif KEY_LED_Flash == ENABLE    	//for AXI AX98310 request-Flash
    if ((ucLedCnt>10) || rst) {	
		LedGreenOn();
        ucLedCnt = 0;
    }
    else {
		LedGreenOff();
        ucLedCnt++;
    }
#endif


}

//******************************************************************************
// Prototype:
//  static BOOL APPIsOutOfLimit(void)
// Parameters:
//  None
// Return:
//  If input timing is OOL, return TRUE. Otherwise, FALSE.
// Purpose:
//  Check the input timing is out of limit or not.
// Notes:
//  None
//******************************************************************************
static BOOL APPIsOutOfLimit(void)
{
#if ENABLE_SCALER_3D == ON
    if (SC3DAPI_IsHDMI3DMode()) {
        return FALSE;
    }
#endif
    //if (InputTiming.usVSyncFreq < MIN_V_FREQ_LMT) {
    //    return TRUE;
    //}
    if (InputTiming.usVSyncFreq > MAX_V_FREQ_LMT) {
        return TRUE;
    }
    return FALSE;
}

#if ENABLE_HW_CEC == ON
//******************************************************************************
// Prototype: 
//  static void APPPerformCECReq(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Perform CEC function
// Notes:
//  None
//******************************************************************************
static void APPPerformCECReq(void)
{

#if ENABLE_LOW_PWR_MODE == ON
    // Turn on scaler register R/W power before access CEC function
    if (IsZpMode()) {
        PowerUpRegisterAccess();
    }    
#endif

    switch(CECHandler()) {
        case CECREQ_POWERUP:
            APPSetSystemPowerState(APPSTATE_PWR_ON);
            break;
        case CECREQ_POWERDOWN:
            APPSetSystemPowerState(APPSTATE_PWR_OFF);
            break;
        case CECREQ_ACTIVATE_SC:
            APPSetSystemPowerState(APPSTATE_PWR_ON);
            // We only have one HDMI interface, so we do not have to 
            // decide which interface to be activated by ID
            // Jude 2009/03/04
            //if (CECGetActiveSC() == 0) 
            UserData.ucInputSource = INPUT_SC_HDMI;
            UserSetInputSource();
            break;
        case CECREQ_DEVCTRL:
            if (CECGetDeviceCtlCode() == CEC_USER_CTRL_POWER) {
                APPSetSystemPowerState(APPSTATE_PWR_ONOFF);
            }
            break;
        case CECREQ_NONE:
        default:
            break;
    }

#if ENABLE_LOW_PWR_MODE == ON
    // Turn off scaler register R/W power after access CEC function
    if (IsZpMode()) {
        PowerDownRegisterAccess();
    }    
#endif
}

//******************************************************************************
// Prototype: 
//  void APPRequestCECAct(UCHAR act)
// Parameters:
//  act : CEC action
// Return:
//  None
// Purpose:
//  Demand CEC action to other device
// Notes:
//  None
//******************************************************************************
void APPRequestCECAct(UCHAR act)
{
    code UCHAR ucCECLanguageMap[NUM_OSDLANGS]= {
        CECLANG_ENGLISH,    //OSDLANG_ENGLISH,
        CECLANG_SPANISH,    //OSDLANG_SPANISH,
        CECLANG_FRENCH,     //OSDLANG_FRENCH,
        CECLANG_GERMAN,     //OSDLANG_GERMAN,
        CECLANG_ITALIAN,    //OSDLANG_ITALIAN,
        CECLANG_PORTUGUESE, //OSDLANG_PORTUGUESE,
        CECLANG_RUSSIAN,    //OSDLANG_RUSSIAN,
        CECLANG_SCHINESE,   //OSDLANG_SCHINESE,
    };
    
#if ENABLE_LOW_PWR_MODE == ON
    // Turn on scaler register R/W power before access CEC function
    if (IsZpMode()) {
        PowerUpRegisterAccess();
    }    
#endif
    
    switch(act) {
        case CECATN_STANDBY:
            if (GetModeHandleState() != SOFT_POWER_OFF) {
                CECSetStandby();
            }
            break;
        case CECATN_SET_LANGUAGE:
            CECSetOSDLanguage(ucCECLanguageMap[UserData.ucLanguage]);
            break;
        case CECATN_NONE:
        default:
            break;
    }

#if ENABLE_LOW_PWR_MODE == ON
    // Turn off scaler register R/W power after access CEC function
    if (IsZpMode()) {
        PowerDownRegisterAccess();
    }    
#endif

}
#endif

#if ENABLE_INTERNAL_AUDIO_BUZZER == ON
//******************************************************************************
// Prototype:
//  void APPSetAudioBuzzer(USHRT time)
// Parameters:
//  time : time in ms
// Return:
//  None
// Purpose:
//  Audio buzzer in the period of time.
// Notes:
//  None
//******************************************************************************
void APPSetAudioBuzzer(USHRT time)
{
    EnableVCSAudioBuzzer(1000);
    bIsBuzzerEnable = TRUE;
    SetGlobalTimer(GLOBAL_TMR_BUZZER_TIME, time);
}

//******************************************************************************
// Prototype:
//  void APPCountAudioBuzzer(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Turn off audio buzzer if time out.
// Notes:
//  None
//******************************************************************************
void APPCountAudioBuzzer(void)
{
    if (bIsBuzzerEnable == TRUE) {
        if (GetGlobalTimer(GLOBAL_TMR_BUZZER_TIME) == 0) {
            bIsBuzzerEnable = FALSE;
            DisableVCSAudioBuzzer();
        }
    }
}
#endif

//******************************************************************************
// Prototype:
//  static void APPIntAutoColor(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Perform internal auto color when system startup
// Notes:
//  None
//******************************************************************************
#if ENABLE_SELF_AUTOCOLOR == ON
static void APPIntAutoColor(void)
{
    if (bIsAPPFirstCalled && InternalAutoColor()) {
        CalibData.ucADCRGain = GetADCRGain();
        CalibData.ucADCGGain = GetADCGGain();
        CalibData.ucADCBGain = GetADCBGain();
        CalibData.ucADCROffset = GetADCROffset();
        CalibData.ucADCGOffset = GetADCGOffset();
        CalibData.ucADCBOffset = GetADCBOffset();
        SetAPPUpdCalFlag();
    }
}
#endif

//******************************************************************************
// Prototype:
// static void CheckTotalPortNum(void)
// Parameters:
//  None
// Return:
//  total source number
// Purpose:
//  check input source number
// Notes:
//  None
//******************************************************************************
UCHAR CheckTotalPortNum(void)
{
    UCHAR PortNum = 0;

#if ((INPUT_INTERFACE & INPUT_VGA0) == INPUT_VGA0) 	//0	VGA	v
           PortNum++;
#endif
#if ((INPUT_INTERFACE & INPUT_VGA1) == INPUT_VGA1) 
           PortNum++;
#endif
#if ((INPUT_INTERFACE & INPUT_DIG0) == INPUT_DIG0) //2 DVI	v
           PortNum++;
#endif
#if ((INPUT_INTERFACE & INPUT_DIG1) == INPUT_DIG1) //5 HDMI
           PortNum++;
#endif

#if OSD_DP_SHOW == ENABLE	//ggg
	#if ((INPUT_INTERFACE & INPUT_DP) == INPUT_DP) 				//140318 mike for input  ==>4
	           PortNum++;
	#endif
#endif

#if ((INPUT_INTERFACE & INPUT_YPbPr0) == INPUT_YPbPr0) 
           PortNum++;
#endif
#if ((INPUT_INTERFACE & INPUT_YPbPr1) == INPUT_YPbPr1) 
           PortNum++;
#endif


    return PortNum;
}

void Custom_System_Init(void)
{
//== for ?CO?XXX or uncall lib compiler pass ==== 
	{
        UCHAR array[3],tmp = 1;

        if(tmp == 0){//fix uncalled warning  
          Write3ByteScaler(array, 0xFFFFFF);  
          WriteScalerIndexPort(0xFF, 0, 3, array);
          OSDEnterDir3();
        }
	}

	{
        extern void ForDemoHDCPCompilerCodePass(void);  
        ForDemoHDCPCompilerCodePass();
	}
           
	{
        extern void ForODCompilerCodePass(void);
        ForODCompilerCodePass();
	}

	#if ENABLE_FE2P == OFF
		{
	        extern void ForFE2PCompilerCodePass();
	        ForFE2PCompilerCodePass();
		}
	#endif

	#if ENABLE_DBC == OFF
		{
	        extern void ForDBCCompilerCodePass(void);
	        ForDBCCompilerCodePass();
		}
	#endif        

	#if IS_NT68661_SERIES || \
	        IS_NT68655_SERIES || \
	        IS_NT68652_SERIES || \
	        IS_NT68169_SERIES || \
	        IS_NT68150_SERIES || \
	        IS_NT68750_SERIES || \
	        IS_NT68770_SERIES || \
	        IS_NT68850_SERIES || \
	        IS_NT68790_SERIES
	        
		#if ENABLE_LD == OFF
	       { 
	         extern void ForLDCompilerCodePass(void);
	         ForLDCompilerCodePass();
	       }
		#endif
	
		#if ENABLE_SR == OFF
	       {
	         extern void ForSRCompilerCodePass(void);  
	         ForSRCompilerCodePass();
	       }
		#endif
	
		#if IS_NT68655_SERIES || IS_NT68850_SERIES || IS_NT68770_SERIES || IS_NT68790_SERIES
			#if (INPUT_INTERFACE&INPUT_DP) != INPUT_DP
	    	  {
	    	     extern void ForDPCompilerCodePass(void);
	    	     ForDPCompilerCodePass();
	    	  }
			#endif
		#endif//IS_NT68850_SERIES
	#endif
//=========================

//Custom parameter
}

#if IR_REMOT_CTL == ENABLE
	BOOL IsAPPLogo() 
	{
	    return ((usAPPFlags&APPFLAG_LOGO) != 0);
	}
#endif

/* void UART_NvRamUpdate(void)	//george-create: for RS232 used 
{


//Rule:	1. ....  OSDBrightnessUp() -> SetOSDUpdUsrFlag();
//		2. OSDActionDemander() =>  {if ('OSDUserUpdate()' -> IsOSDUpdUsr() -> ClearOSDUpdUsrFlag() ) } => Get evt = OSDEVT_UPD_USR;
//	then
//		1. (at APPActionDispatcher()) -> (from (GetGlobalEvent(event) == OSD_RELATED_EVENT)), Get APPEVT -> case APPATN_UPD_SYS: SetAPPUpdSysFlag();
//		2. (at APPTimerRoutine()) -> if(IsAPPUpdUsr())  -> NvramWriteUserData(&UserData);


	SetGlobalTimer(GLOBAL_TMR_DATA_UPDATE, GBTM_DATA_UPDATE);
	SetAPPUpdSysFlag();
}
*/
