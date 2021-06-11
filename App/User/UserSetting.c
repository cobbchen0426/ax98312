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
#define CheckMaxRange(a,b) {if (a > b) a = b;}

#define PHASE_SCOPE   (MAXIMUM_PHASE-MINIMUM_PHASE)
#define CLOCK_SCOPE   (InputTiming.usHTotalMax-InputTiming.usHTotalMin)
#define HPOSN_SCOPE   (InputTiming.usHStartMax-InputTiming.usHStartMin)
#define VPOSN_SCOPE   (InputTiming.usVStartMax-InputTiming.usVStartMin)

//******************************************************************************
// S T A T I C   V A R I A B L E S
//******************************************************************************
static code tINPUTPORT ucInputPortTable[] = {
    //ucInputPort,            ucPortName;
#if (MODEL_INPUT_VGA0 != INPUT_SC_NULL)    
    ANALOG_SEP_INPUT0,    MODEL_INPUT_VGA0,
#endif
#if (MODEL_INPUT_VGA1 != INPUT_SC_NULL)    
    ANALOG_SEP_INPUT1,    MODEL_INPUT_VGA1,
#endif
#if (MODEL_INPUT_DIG0 != INPUT_SC_NULL)    
    DIGITAL_INPUT0,       MODEL_INPUT_DIG0,
#endif
#if (MODEL_INPUT_DIG1 != INPUT_SC_NULL)    
    DIGITAL_INPUT1,       MODEL_INPUT_DIG1,
#endif

#if OSD_DP_SHOW == ENABLE		//ggg
	#if (MODEL_INPUT_DIG2 != INPUT_SC_NULL)    
	    DISPLAY_PORT_INPUT,   MODEL_INPUT_DIG2,
	#endif
#else
	
#endif

#if (MODEL_INPUT_YPbPr0 != INPUT_SC_NULL)    
    ANALOG_YPBPR_INPUT0,  MODEL_INPUT_YPbPr0,
#endif
#if (MODEL_INPUT_YPbPr1 != INPUT_SC_NULL)    
    ANALOG_YPBPR_INPUT1,  MODEL_INPUT_YPbPr1,
#endif
};

//******************************************************************************
// Prototype: 
//  UCHAR GetPortTabIntertface(UCHAR PortName)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
UCHAR GetPortTabIntertface(UCHAR PortName)
{
    UCHAR i;
    for (i = 0; i < (sizeof(ucInputPortTable) / sizeof(tINPUTPORT)); i++) {
       if (ucInputPortTable[i].ucPortName == PortName) {
          return ucInputPortTable[i].ucInputPort;
       }
    }
    
    UserData.ucInputSource = ucInputPortTable[0].ucPortName;
    return ucInputPortTable[0].ucInputPort;
}

//******************************************************************************
// Prototype: 
//  
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
void UserSetBrightness(void)
{
    CheckMaxRange(UserData.ucBrightness,MAXIMUM_BRIGHTNESS);
	if(UserData.ucBrightness==0)
	SetBrightness(0);
	else	
    SetBrightness(GetBrightness1023());
}

//******************************************************************************
// Prototype: 
//  
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
void UserSetContrast(void)
{
    CheckMaxRange(UserData.ucContrast,MAXIMUM_CONTRAST);
    MTXAPI_SetContrast(GetContrast255());
}

//******************************************************************************
// Prototype: 
//  
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
void UserSetPhase(void)
{
    CheckMaxRange(InputTiming.ucPhase,MAXIMUM_PHASE);
    SetADCPhase(InputTiming.ucPhase);
#if ENABLE_ESD_PROTECT == ON
    ReadESDCheckSum();
#endif
}

//******************************************************************************
// Prototype: 
//  void UserSetPhase100(UCHAR value)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
void UserSetPhase100(UCHAR value)
{
    if (value > 100) value = 100;
    InputTiming.ucPhase = (USHRT)value*MAXIMUM_PHASE/100;
    UserSetPhase();    
}

//******************************************************************************
// Prototype: 
//  
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
void UserSetClock(void)
{
    //CheckMaxRange(InputTiming.usHTotal,InputTiming.usHTotalMax);
    SetADCPLL2(InputTiming.usHTotal);
#if ENABLE_ESD_PROTECT == ON
    ReadESDCheckSum();
#endif
}

//******************************************************************************
// Prototype: 
//  void UserSetClock100(UCHAR value)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
void UserSetClock100(UCHAR value)
{
    if (value > 100) value = 100;
    InputTiming.usHTotal = (USHRT)value*CLOCK_SCOPE/100+InputTiming.usHTotalMin;
    UserSetClock();
}

//******************************************************************************
// Prototype: 
//  
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
void UserSetHPosition(void)
{
    //CheckMaxRange(InputTiming.usHStart,InputTiming.usHStartMax);
    SetHP(InputTiming.usHStart);
}

//******************************************************************************
// Prototype: 
//  void UserSetHPosn100(UCHAR value)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
void UserSetHPosn100(UCHAR value)
{
    if (value > 100) value = 100;
    value = 100-value;
    InputTiming.usHStart = (USHRT)value*HPOSN_SCOPE/100+InputTiming.usHStartMin;
    UserSetHPosition();    
}

//******************************************************************************
// Prototype: 
//  
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
void UserSetVPosition(void)
{
    //CheckMaxRange(InputTiming.usVStart,InputTiming.usVStartMax);
    SetVP(InputTiming.usVStart);
}

//******************************************************************************
// Prototype: 
//  void UserSetVPosn100(UCHAR value)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
void UserSetVPosn100(UCHAR value)
{
    if (value > 100) value = 100;
    InputTiming.usVStart = (USHRT)value*VPOSN_SCOPE/100+InputTiming.usVStartMin;
    UserSetVPosition();    
}

//******************************************************************************
// Prototype: 
//  void UserSetADCGainOffset(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Set ADC gain/offset
// Notes:
//  None
//******************************************************************************
void UserSetADCGainOffset(void)
{
    SetADCRGain(CalibData.ucADCRGain);
    SetADCGGain(CalibData.ucADCGGain);
    SetADCBGain(CalibData.ucADCBGain);
    SetADCROffset(CalibData.ucADCROffset);
    SetADCGOffset(CalibData.ucADCGOffset);
    SetADCBOffset(CalibData.ucADCBOffset);
}

//******************************************************************************
// Prototype: 
//  
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
void UserSetColorTemp(void)
{
    CheckMaxRange(UserData.ucColorTemp,MAXIMUM_CLR_TEMP);
    SetColorTemperature(UserData.ucColorTemp);

}

//******************************************************************************
// Prototype: 
//  
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
void UserSetRGain(void)
{
    CheckMaxRange(UserData.ucUserRGain,MAXIMUM_USER_RGAIN);
    MTXAPI_SetRGain(GetRGain255()+1);
}

//******************************************************************************
// Prototype: 
//  
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
void UserSetGGain(void)
{
    CheckMaxRange(UserData.ucUserGGain,MAXIMUM_USER_GGAIN);
    MTXAPI_SetGGain(GetGGain255()+1);
}

//******************************************************************************
// Prototype: 
//  
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
void UserSetBGain(void)
{
    CheckMaxRange(UserData.ucUserBGain,MAXIMUM_USER_BGAIN);
    MTXAPI_SetBGain(GetBGain255()+1);
}

//******************************************************************************
// Prototype: 
//  
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
void UserSetROffset(void)
{
    CheckMaxRange(UserData.ucUserROffset,MAXIMUM_USER_ROFFSET);
    MTXAPI_SetROffset(GetROffset255());
}

//******************************************************************************
// Prototype: 
//  
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
void UserSetGOffset(void)
{
    CheckMaxRange(UserData.ucUserGOffset,MAXIMUM_USER_GOFFSET);
    MTXAPI_SetGOffset(GetGOffset255());
}

//******************************************************************************
// Prototype: 
//  
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
void UserSetBOffset(void)
{
    CheckMaxRange(UserData.ucUserBOffset,MAXIMUM_USER_BOFFSET);
    MTXAPI_SetBOffset(GetBOffset255());
}

//******************************************************************************
// Prototype: 
//  
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
void UserSetOSDH(void)
{
    CheckMaxRange(UserData.ucOSDX,MAXIMUM_OSD_HPOS);
    CheckMaxRange(UserData.ucOSDY,MAXIMUM_OSD_VPOS);
    OSDAPI_SetPosition(UserData.ucOSDX, UserData.ucOSDY);
}

//******************************************************************************
// Prototype: 
//  
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
void UserSetOSDV(void)
{
    UserSetOSDH();
}

//******************************************************************************
// Prototype: 
//  
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
void UserSetTransparent(void)
{
    OSDWindow id;
    CheckMaxRange(UserData.ucOSDTransparent,MAXIMUM_OSD_TRANS);
    OSDAPI_SetOSDFgBgTran(UserData.ucOSDTransparent);
    OSDAPI_SetOSDSpecialBgTran(0xFF);
    for (id = OSD_WINDOW1; id <= OSD_WINDOW8; id++) {
        OSDAPI_SelOSDWin(id);
        OSDAPI_SetOSDWinTran(UserData.ucOSDTransparent);
    }
}

//******************************************************************************
// Prototype: 
//  
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
void UserSetTimeout(void)
{
    OSDConfigTimeout((USHRT)UserData.ucOSDTimer*1000);
}

//******************************************************************************
// Prototype: 
//  
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
void UserSetOSDRotation(void)
{
    if (UserData.bOSDRotation) {
        OSDAPI_RotateOSDPosition(OSD_POS_ROT_270);
    }
    else {
        OSDAPI_RotateOSDPosition(OSD_POS_ROT_OFF);
    }

#if 0
    if (OSDAPI_IsOSDOn()) {
        OSDAPI_TurnOffOSD();
        OSDTurnOnOSD();
    }
#endif
}

//******************************************************************************
// Prototype: 
//  
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
void UserSetLanguage(void)
{
    CheckMaxRange(UserData.ucLanguage,MAXIMUM_OSD_LANG);
#if ENABLE_HW_CEC == ON
    APPRequestCECAct(CECATN_SET_LANGUAGE);
#endif
}

//******************************************************************************
// Prototype:
//
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
void UserSetAudioMute(void)
{	

    if (UserData.bAudioMute == TRUE) 
    {
        AudioMuteOn();					//140325 mike 
    }
    else 
	{   
		AudioMuteOff();
    }
}

//******************************************************************************
// Prototype: 
//  void UserSetDCR(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
void UserSetDCR(void)
{
#if ENABLE_DBC == ON
    if ( UserData.ucDCRMode == BKL_CTRL_DBC ) {
        DisableDCR();
        EnableDBC();
    }
    else if ( UserData.ucDCRMode == BKL_CTRL_DCR ) {
        DisableDBCSmooth(TRUE);
        PerformDCR(1);
    }
    else {
        DisableDCR();
        DisableDBCSmooth(TRUE);
    }
#else
    if ( UserData.ucDCRMode == BKL_CTRL_DCR ) {
        PerformDCR(1);
    }
    else {
        DisableDCR();
    }
#endif
}

//******************************************************************************
// Prototype: 
//  void UserSetLD(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Set LD mode
// Notes:
//  None
//******************************************************************************
#if ENABLE_LD == ON
void UserSetLD(void)
{
//    SetLDMode(UserData.ucLDOnOff);
        SetLDMode(UserData.ucBFMode);
}
#endif

//******************************************************************************
// Prototype:
//  void UserSetAspectRatio(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
void UserSetAspectRatio(void)
{
    SetDisplayMode(UserData.ucAspectRatio);

    // Resize BF window by current aspect ratio.
    BFAPI_SetActiveWindow(BF_WINDOW_2);
    BFAPI_SetWindowSize(BF_WINDOW_FULLSCREEN);
#if ENABLE_ESD_PROTECT == ON
    ReadESDCheckSum();
#endif
}

//******************************************************************************
// Prototype:
//  void UserSetOverScan(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
#if ENABLE_OVERSCAN == ON		//150114 mike
//void UserSetOverScan(void)
//{
//    BacklightOff();
//    //WaitDisVSync();
//    //DisplayMuteImage();
//    //WaitDisVSync();
//    WaitDisVSync();
//    GraphicDisplayWindowDisable();
//    CheckOverScan();
//    SetHmask();
//    SetupDisplayTiming(InputTiming.usHTotal50);
//    Sleep(80);
//    //WaitDisVSync();
//    //DisplayNormalImage();
//    WaitDisVSync();
//    GraphicDisplayWindowEnable();
//    BacklightOn();
//}
#endif

//******************************************************************************
// Prototype: 
//  
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
void UserSetGamma(void)
{
    if (UserData.bGammaOnOff == 1)
        GMAPI_EnableGamma();
    else
        GMAPI_DisableGamma();
}



#if ALS_EnDis == ALSMODE
	void UserSetALSMode(void)
	{
		//ref. SetSRMode(UserData.ucSRMode);
		SetALSMode();	//UserData.ucALSMode);
	}
#elif ALS_EnDis == ALSOffSET	
	void UserSetALSOnOff(void)				//george: F_ALSOnOff_04E
	{
		// george: don't need set H/W, so don't care here.s
	    if (UserData.bALSOnOff == ON) 
	    {
	        //xxxOn();					
	    }
	    else 
		{   
			//xxxOff();
	    }
	}

//	void UserSetALSBaseVal(void)					// george: F_ALSBV_04E
//	{
//	    CheckMaxRange(UserData.ucALSBaseVal,MAXIMUM_ALSBV);
//	    SetBrightness(GetALSBaseValue1023());
//	}

#elif ALS_EnDis == ALSRange
	void UserSetALSOnOff(void)				//george: F_ALSOnOff_04E
	{
		//
	}
#else	//Normal

#endif	//#if ALS_EnDis == ENABLE




#if TOUCH_EnDis == ENABLE
void UserSetTouch(void)					//george: F_Touch_04E
{
    if (UserData.bTouchOnOff == 1)
        TouchOnOff(ON);
    else
        TouchOnOff(OFF);
}
#endif	//#if TOUCH_EnDis == ENABLE

//******************************************************************************
// Prototype: 
//  void UserSetOD(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
void UserSetOD(void)
{
#if ENABLE_OD == ON
    if (UserData.ucODMode == ON) {
        SetODMode(0);
    }
    else {
        ODAPI_DisableOD();
    }
#endif
}

//******************************************************************************
// Prototype: 
//  void UserSetVolume(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
void UserSetVolume(void)
{
    CheckMaxRange(UserData.ucVolume,MAXIMUM_VOLUME);
        SetVolume(UserData.ucVolume);
}

//******************************************************************************
// Prototype: 
//  void UserRecallConfiguration(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
void UserRecallConfiguration(void)
{
	UCHAR tmp=0;
#if OSD_Debug == ENABLE
	printf("UserRecallConfiguration_S\n");	//150527 george
#endif
	tmp = UserData.ucInputSource;
    UserData = UserDataDefault;        

	UserData.ucInputSource = tmp;
    UserSetBrightness();  
    UserSetContrast();
    UserSetGamma();
    UserSetColorTemp(); 
    UserSetOSDH();
    UserSetOSDV();
    UserSetTransparent();
    UserSetTimeout();
    UserSetOSDRotation();
    UserSetVolume();
    UserSetAudioMute();
    UserSetDCR();
    UserSetAspectRatio();
    
    //UserSetOD();
    //UserSetBF();
#if ENABLE_SR == ON
    //UserSetSR();
#endif
#if ENABLE_3D_CNV == ON
    //UserSet2DTo3DMode();
    UserSet2DTo3DAdaptive();
    UserSet2DTo3DDepth();
    UserSet2DTo3DView();
    UserSet3DLRSwap();
    UserSet3DTo2D();

#endif    
      
    NvramClearTiming(); //To avoid previous wrong Nvram data

    /* We disable writing timing info to nvram in recall to avoid wrong timing info writing to nvram again
    //Samuel-2010-02-09: When factory reset in DVI/HDMI, the timing information should not be written into nvram.
    if (GetInputSyncMode() != DIG_SYNC) { 
        NvramWriteTimingData(&InputTiming);
    }
    */

    UserPerformAutoTune();  //fefanjacky for tatung user mode not autotune 
    
    //CHIU RECALL
    SYSAPI_SetInverterVal(CalibData.ucBacklite);
        UserSetBrightness();  


#if OSD_Debug == ENABLE
	printf("UserRecallConfiguration_E\n");	//150527 george
#endif
}

//******************************************************************************
// Prototype: 
//  void UserRecallColor(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
void UserRecallColor(void)
{
    UserData.ucUserROffset = UserDataDefault.ucUserROffset;
    UserData.ucUserGOffset = UserDataDefault.ucUserGOffset;
    UserData.ucUserBOffset = UserDataDefault.ucUserBOffset;
    UserSetROffset();
    UserSetGOffset();
    UserSetBOffset();
    UserData.ucBrightness = UserDataDefault.ucBrightness;
    UserData.ucContrast = UserDataDefault.ucContrast;
    //UserSetContrast();
    UserData.ucUserRGain = UserDataDefault.ucUserRGain;
    UserData.ucUserGGain = UserDataDefault.ucUserGGain;
    UserData.ucUserBGain = UserDataDefault.ucUserBGain;
    UserData.ucColorTemp = UserDataDefault.ucColorTemp;
    UserSetColorTemp();
    UserSetBrightness();
}

//******************************************************************************
// Prototype: 
//  void UserRecallHVPosition(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Rcall H/V position 
// Notes:
//  None
//******************************************************************************
void UserRecallHVPosition(void)
{
    InputTiming.usHTotal = InputTiming.usHTotal50;
    InputTiming.usHStart = InputTiming.usHStart50;
    InputTiming.usVStart = InputTiming.usVStart50;
    InputTiming.ucPhase = 32;
    SetADCPLL2(InputTiming.usHTotal);
    SetHP(InputTiming.usHStart);
    SetVP(InputTiming.usVStart);
    SetADCPhase(InputTiming.ucPhase);
#if ENABLE_ESD_PROTECT == ON
    ReadESDCheckSum();
#endif
}

//******************************************************************************
// Prototype: 
//  void UserPerformAutoTune(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
void UserPerformAutoTune(void)
{
#if AutoTune_Debug == ENABLE
printf("UserPerformAutoTune_S\n");	//150526 george
#endif

    if (IsAutoTuneValid()) 
	{

        InputTiming.ucAutoTune = AutoTune();

    #if ENABLE_ESD_PROTECT == ON
        ReadESDCheckSum();
    #endif
        if (InputTiming.ucAutoTune) 
		{
            InputTiming.usHTotal = GetAngInputHTotal();
            InputTiming.usHStart = GetInputHStart();
            InputTiming.usVStart = GetInputVStart();
            InputTiming.ucPhase = GetAngInputPhase();
            InputTiming.usHTotal50 = InputTiming.usHTotal;
            InputTiming.usHStart50 = InputTiming.usHStart;
            InputTiming.usVStart50 = InputTiming.usVStart;
            SetMinMax();
        }
    }

#if AutoTune_Debug == ENABLE
printf("UserPerformAutoTune_E\n");	//150526 george
#endif
}

//******************************************************************************
// Prototype: 
//  void UserSetBF(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
void UserSetBF(void)
{
    CheckMaxRange(UserData.ucBFMode,MAXIMUM_BF_MODE);
    SetThemeMode(UserData.ucBFMode);
}

//******************************************************************************
// Prototype:
//  void UserSetSR(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Set SR mode
// Notes:
//  None
//******************************************************************************
#if ENABLE_SR == ON
void UserSetSR(void)
{
    SetSRMode(UserData.ucSRMode);
}
#endif

//******************************************************************************
// Prototype: 
//  void UserSet2DTo3DMode(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Set 2D to 3D mode
// Notes:
//  None
//******************************************************************************
#if ENABLE_3D_CNV == ON
void UserSet2DTo3DMode(void)
{
    CheckMaxRange(UserData.uc2DTo3DMode, MAXIMUM_2DTO3D_MODE);
    Set2DTo3DMode(UserData.uc2DTo3DMode);
}
#endif

//******************************************************************************
// Prototype: 
//  void UserSet2DTo3DAdaptive(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Enable 2D to 3D adpative mode
// Notes:
//  None
//******************************************************************************
#if ENABLE_3D_CNV == ON
void UserSet2DTo3DAdaptive(void)
{
    if (Is2DTo3DAdaptive()) {
        Set2DTo3DAdaptive(TRUE);
    }
    else {
        Set2DTo3DAdaptive(FALSE);
    }
}
#endif

//******************************************************************************
// Prototype: 
//  void UserSet2DTo3DDepth(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Set 2D to 3D mode
// Notes:
//  None
//******************************************************************************
#if ENABLE_3D_CNV == ON
void UserSet2DTo3DDepth(void)
{
    CheckMaxRange(UserData.uc2Dto3DDepth, MAXIMUM_2DTO3D_DEPTH);
    Set2DTo3DDepth(UserData.uc2Dto3DDepth);
}
#endif

//******************************************************************************
// Prototype: 
//  void UserSet2DTo3DView(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Set 2D to 3D mode
// Notes:
//  None
//******************************************************************************
#if ENABLE_3D_CNV == ON
void UserSet2DTo3DView(void)
{
    CheckMaxRange(UserData.uc2Dto3DView, MAXIMUM_2DTO3D_VIEW);
    Set2DTo3DView(UserData.uc2Dto3DView);
}
#endif

//******************************************************************************
// Prototype: 
//  void UserSet3DLRSwap(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Set 2D to 3D mode
// Notes:
//  None
//******************************************************************************
#if ENABLE_3D_CNV == ON
void UserSet3DLRSwap(void)
{
    if (Is3DLRSwap()) {
        Set3DLRSwap(TRUE);
    }
    else {
        Set3DLRSwap(FALSE);
    }
}
#endif

//******************************************************************************
// Prototype: 
//  void UserSet3DTo2D(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Set 3D to 2D mode
// Notes:
//  None
//******************************************************************************
#if ENABLE_FUNC_OSD == ON && ENABLE_3D_CNV == ON
void UserSet3DTo2D(void)
{
    if (Is3DTo2DEnabled()) {
        Set3DTo2DMode(TRUE);
    }
    else {
        Set3DTo2DMode(FALSE);
    }
}
#endif

//******************************************************************************
// Prototype: 
//  void UserSetInputSource(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
void UserSetInputSource(void)
{

#if (INPUT_INTERFACE&INPUT_MHL0) || (INPUT_INTERFACE&INPUT_MHL1)
    if (MHL_IsMHLPathEnable() ) 
     {
        Force2Background(0, 0, 0); //Mute screen and display black pattern
        MHLClearHPD();
     }
#endif
    AudioMuteOn();								
    SetInputInterface(GetPortTabIntertface(UserData.ucInputSource));
}

//******************************************************************************
// Prototype: 
//  UCHAR UserGetInputSource(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
UCHAR UserGetInputSource(void)
{
    UCHAR i;
    UCHAR src = GetCurrInputInterface();
    UCHAR num = sizeof(ucInputPortTable)/sizeof(tINPUTPORT);

    for (i = 0; i < num; i++) {
        if ((src & PORT_MASK) == (ucInputPortTable[i].ucInputPort & PORT_MASK)) {
            break;
        }
    }
    
    if (i < num){
        return ucInputPortTable[i].ucPortName;
    }
    
    return INPUT_SC_VGA;
}

//******************************************************************************
// Prototype: 
//  void UserSetAudioChannel(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Set audio input/output channel
// Notes:
//  None
//******************************************************************************
void UserSetAudioChannel(void)
{
#if ENABLE_SCALER_AUDIO == ON
#if AUDIO_OUT == IIS_OUT
    ScalerAudioSelect(AUDIO_HDMI_IIS);
#else
    #if AUDIO_LINE_IN == LINE_IN1
    switch(UserGetInputSource()) {
        case INPUT_SC_VGA:	 // 20150519 George [VGA-Port, Ext.-Line-in]
            ScalerAudioSelect(AUDIO_LINEIN1_LINOUT);
            break;
        case INPUT_SC_DVI:	  // 20150519 George [DVI-Port, check_no-sound]
            //20150519 George, ScalerAudioSelect(AUDIO_HDMI_LINOUT);		printf("_DVI_Line-IN_");
			ScalerAudioSelect(AUDIO_LINEIN1_LINOUT);	
            break;
        case INPUT_SC_DVI1:
            ScalerAudioSelect(AUDIO_HDMI_LINOUT);		
            break;
        case INPUT_SC_HDMI:
            ScalerAudioSelect(AUDIO_HDMI_LINOUT);		
            break;
        case INPUT_SC_HDMI1: // 20150519 George [HDMI-Port, sound on HDMI cable]
            ScalerAudioSelect(AUDIO_HDMI_LINOUT);		
            break;
        case INPUT_SC_HDMI2:
            ScalerAudioSelect(AUDIO_HDMI_LINOUT);		
            break;
        case INPUT_SC_YPbPr:
            ScalerAudioSelect(AUDIO_LINEIN1_LINOUT);
            break;
        case INPUT_SC_DP:
            ScalerAudioSelect(AUDIO_HDMI_LINOUT);		
            break;
        default:
            break;
    }
    #else
    switch(UserGetInputSource()) {
        case INPUT_SC_VGA:
            ScalerAudioSelect(AUDIO_LINEIN2_LINOUT);
            break;
        case INPUT_SC_DVI:
            ScalerAudioSelect(AUDIO_HDMI_LINOUT);
            break;
        case INPUT_SC_DVI1:
            ScalerAudioSelect(AUDIO_HDMI_LINOUT);
            break;
        case INPUT_SC_HDMI:
            ScalerAudioSelect(AUDIO_HDMI_LINOUT);
            break;
        case INPUT_SC_HDMI1:
            ScalerAudioSelect(AUDIO_HDMI_LINOUT);
            break;
        case INPUT_SC_HDMI2:
            ScalerAudioSelect(AUDIO_HDMI_LINOUT);
            break;
        case INPUT_SC_YPbPr:
            ScalerAudioSelect(AUDIO_LINEIN2_LINOUT);
            break;
        case INPUT_SC_DP:
            ScalerAudioSelect(AUDIO_HDMI_LINOUT);
            break;
        default:
            break;
    }
    #endif
#endif
#endif
}

//******************************************************************************
// Prototype:
//  UCHAR UserGetNormalPhase(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
UCHAR UserGetNormalPhase(void)
{
    //UCHAR phase;
    //phase = (USHRT) InputTiming.ucPhase * 100 / MAXIMUM_PHASE;
    //return phase;
    return ucADCPhase100;
}

//******************************************************************************
// Prototype: 
//  UCHAR UserGetNormalClock(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
UCHAR UserGetNormalClock(void)
{
    UCHAR clock;
    clock = ((USHRT) InputTiming.usHTotal - InputTiming.usHTotalMin) * 100 / CLOCK_SCOPE;
    return clock;
}

//******************************************************************************
// Prototype: 
//  UCHAR UserGetNormalHPosn(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
UCHAR UserGetNormalHPosn(void)
{
    UCHAR pos;
    pos = ((USHRT) InputTiming.usHStart - InputTiming.usHStartMin) * 100 / HPOSN_SCOPE;
    pos = 100 - pos;
    return pos;
}

//******************************************************************************
// Prototype: 
//  UCHAR UserGetNormalVPosn(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
UCHAR UserGetNormalVPosn(void)
{
    //UCHAR pos;
    //pos = ((USHRT) InputTiming.usVStart - InputTiming.usVStartMin) * 100 / VPOSN_SCOPE;
    //return pos;
    return ucVstart100;
}

//******************************************************************************
// Prototype: 
//  UCHAR UserGetNormal2DTo3DDpth(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
#if MD_ENABLE_FUNC_OSD == ON
UCHAR UserGetNormal2DTo3DDpth(void)
{
    UCHAR tmp;
    tmp = (USHRT) UserData.uc2Dto3DDepth * 100 / MAXIMUM_2DTO3D_DEPTH;
    return tmp;
}
#endif

//******************************************************************************
// Prototype: 
//  UCHAR UserGetNormal2DTo3DView(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
#if MD_ENABLE_FUNC_OSD == ON
UCHAR UserGetNormal2DTo3DView(void)
{
    UCHAR tmp;
    tmp = (USHRT) UserData.uc2Dto3DView * 100 / MAXIMUM_2DTO3D_VIEW;
    return tmp;
}
#endif


//******************************************************************************
// Prototype: 
//  UCHAR GetInputPortName(UCHAR PortIdex)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
UCHAR GetInputPortName(UCHAR PortIdex)
{
    UCHAR i,j;
    if (PortIdex >= CheckTotalPortNum()) 
	{
        return NUM_INPUT_SC;
    }
    for (j = 0;j < NUM_INPUT_SC; j++) 
	{
        for (i = 0; i < (sizeof(ucInputPortTable) / sizeof(tINPUTPORT)); i++) 
		{
            if (ucInputPortTable[i].ucPortName == INPUT_SC_NULL)
                continue;
            if (ucInputPortTable[i].ucPortName == j) 
			{
                if (PortIdex-- == 0)
                    return j;
            }
        }
    }
    
    return 0;
} 

//******************************************************************************
// Prototype: 
//  UCHAR GetInputPortIndex(UCHAR PortName)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
UCHAR GetInputPortIndex(UCHAR PortName)
{
    UCHAR i,j,count=0;
    for (j = 0; j < NUM_INPUT_SC; j++) 
	{
        for (i = 0; i < (sizeof(ucInputPortTable)/sizeof(tINPUTPORT)); i++) 
		{
            if (ucInputPortTable[i].ucPortName == INPUT_SC_NULL) 
			{
                continue;
            }
            if (ucInputPortTable[i].ucPortName == j) 
			{
                if (j == PortName) 
				{
                    return count;
                }
                count++;
            }
        }
    }
 
    return 0;
}

