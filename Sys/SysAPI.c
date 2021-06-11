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
// M A C R O   D E F I N I T I O N S
//******************************************************************************

//******************************************************************************
// G L O B A L   V A R I A B L E S
//******************************************************************************

//******************************************************************************
// S T A T I C   V A R I A B L E S
//******************************************************************************
static BOOL bIsACOnFlag = TRUE;
static UCHAR PreSetBrightnessPWMMax = FALSE;

//******************************************************************************
// E X T E R N A L   V A R I A B L E   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// S T A T I C   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// E X T E R N A L   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// F U N C T I O N   B O D Y S
//******************************************************************************

/**************************************************************************//**
 * Turn off system.
 ******************************************************************************/
void SYSAPI_SetPowerOff(void)
{
#if PWRSeq_Deug == ENABLE
printf("SYSAPI_SetPowerOff_S\n");
#endif

    McuSetIOBit(PSB_PORT, PSB_BIT, ~PSB_ACTIVE);   //FEFANJACKY ADD FOR PSB OFF
    SetVolume(0);
    ModeHandleSoftPowerOff();
    LedGreenOff();
    LedRedOff();
    AudioMuteOn();								//140325 mike 
    PanelPowerOffSequence();
    AudioPowerOff();
#if ENABLE_DIGI0_HPD == ON || ENABLE_DIGI1_HPD == ON || ENABLE_DP_HPD == ON
    SYSAPI_PerformHPDOff(FALSE);
#endif
    ScalerPowerDown();
}

/**************************************************************************//**
 * Turn on system.
 ******************************************************************************/
void SYSAPI_SetPowerOn(void)
{
//printf("Sysapi_SetPowerON()\n");	
    ModeHandleSoftPowerOn();
    LedRedOff();
    LedGreenOn();
    ScalerPowerUp();
    AudioPowerOn();
}

/**************************************************************************//**
 * Set system to power saving.
 ******************************************************************************/
void SYSAPI_PowerSaving(void)
{
//printf("Sysapi_PowerSaving()\n");	
    ModeHandlePowerSaving();
    LedGreenOff();
    LedRedOn();
    AudioMuteOn();
    PanelPowerOffSequence();
    AudioPowerOff();
    McuSetIOBit(PSB_PORT, PSB_BIT, ~PSB_ACTIVE);   //FEFANJACKY ADD FOR PSB OFF

#if ENABLE_HDMI_PRETEST == OFF
	#if BurnIn_Degub == ENABLE
		printf("AC\n");
	#endif

	if(!((IsDPTrainingDone() == TRUE) && IsDPConnect()))
	{ 

	#if BurnIn_Degub == ENABLE
		printf("AD\n");
	#endif
        ScalerPowerSaving();	//gg
    }

    //ScalerPowerSaving();
#endif

}

/**************************************************************************//**
 * Force system to power saving state even video signal is present.
 ******************************************************************************/
void SYSAPI_ForcePowerSaving(void)
{
    SetForceToSleep();
    SYSAPI_PowerSaving();
}

/**************************************************************************//**
 * Wake system up.
 ******************************************************************************/
void SYSAPI_WakeUp(void)
{
UCHAR ZpIf = GetCurrInputInterface(); //need to discuss with Nick&James
    ModeHandleSoftPowerOn();
    LedRedOff();
    LedGreenOn();
    ScalerPowerUp();
#if (INPUT_INTERFACE&INPUT_DP)
    ClrDPLink();
#endif
    SetInputInterface(ZpIf);
#if (INPUT_INTERFACE&INPUT_MHL0) || (INPUT_INTERFACE&INPUT_MHL1)
    if ( MHL_IsCDSenseFlagOn() ) 
	{
          if (( ZpIf==DIGITAL_INPUT0 && MHL_GetCbusCH() == MHL_CBUS_CH1 ) ||
             ( ZpIf==DIGITAL_INPUT1 && MHL_GetCbusCH() == MHL_CBUS_CH2 ) ) 
             {
                ResetCurTimerTick();
             }
        }
#endif
}

/**************************************************************************//**
 * Check system 5V is present or not.
 * If 5V is absent, reset system in time.
 ******************************************************************************/
void SYSAPI_CheckSysPower(void)
{
//return;	//(at McuCheck5V()) -> ext. return TRUE;	//150526 george   to test re-boot factor.
    // Restart system if system 5V is absent
    if (McuCheck5V() == FALSE) {

        //((void (code*)(void))0)();
        while(1);   // Use WDT to reset instead of jump (void *) 0
                    // Because WDT is similar to HW reset. Whole HW system will
                    // be reset, but "Jump to zero" can not.
    }
}

#if ENABLE_SET_PWM_MAX_BUFFER == ON
/**************************************************************************//**
 * Set Brightness to 1023 Polling
 ******************************************************************************/
void SetBrightnessPWMMax()
{
	UCHAR port;
	if(GetSCID() == SCID_770_E)					//140313 mike  SCID_770_E==>SCID_850_D
	{											//150525 George GetSCID()=SCID_850_D=0x21; SCID_770_E=0x10 so~ condition no run this loop
												//george: debug-tool-read: in_GetSCID() -> SC_CHIP_ID= 0xb,  SC_REVISION_ID= 0x3, SCID_850_D= 0x21
    	if(PreSetBrightnessPWMMax == TRUE)
        {   
            if (GetGlobalTimer(GLOBAL_TMR_PWM_MAX_UPDATE) == 0)
		    { 
             	PreSetBrightnessPWMMax = FALSE;
                if( GetScalerPWM(port) == 1020)
		        {
                     SetBrightness(1023);
                }
             }
         }
	}	
}
#endif



//CHIU

void SYSAPI_SetInverterVal(UCHAR val)
{
	#if BKL_PWM_POL == HIGH	
	  SetScalerPWM(BKL_PWM_PORT, (unsigned short)(val) << 2);  
	#elif  BKL_PWM_POL == PWM								//140314 mike 
	  SetScalerPWM(BKL_PWM_PORT, (unsigned short)(val) << 2);  	
	#else
	  SetScalerPWM(BKL_PWM_PORT, (unsigned short)(~val) << 2);
	#endif

#if PWRSeq_Deug == ENABLE
printf("+++Set-Inverter\n");
#endif
}

/**************************************************************************//**
 * Set brightness.
 * @param br Brightness. The range is 0 ~ 1023.
 * printf("\nKEY_MIN_LEVEL2   131205==%x\n\r",(unsigned short)KEY_MIN_LEVEL2);    //140304 MIKE 
 ******************************************************************************/
void SetBrightness(USHRT br)
{
UCHAR port;
#if ENABLE_SCALER_LEDDRV_ANA_MODE == ON		// george: It's no compiler here.
    SetLEDDRVCurrent(br);
#else  
  port = GetSCID();
 //-----------------------------------------
 #if ENABLE_SET_PWM_MAX_BUFFER == ON

	if(GetSCID() == SCID_770_E)					//140313 mike  SCID_770_E==>SCID_850_D
	{
		if(GetScalerPWM(BKL_PWM_PORT) == 0 && br == 1023)
	    {   
			br = 1020;
            PreSetBrightnessPWMMax = TRUE;
            SetGlobalTimer(GLOBAL_TMR_PWM_MAX_UPDATE,6000);    
        }
		else 
		{
			if(br == 1023)
			{    
            	if(GetGlobalTimer(GLOBAL_TMR_PWM_MAX_UPDATE) != 0)
				{
                	br = 1020;  
                }
           	}
	   		else 
			{
                PreSetBrightnessPWMMax = FALSE;
                SetGlobalTimer(GLOBAL_TMR_PWM_MAX_UPDATE,0);
            }
		}
	}
#endif

//-------------------------------------------------
	//CHIU DISABLE FOR SET INVERTER VALUE
#if BKL_PWM_POL == HIGH
    SetScalerPWM(BKL_PWM_PORT, 1020);	//br);
#elif  BKL_PWM_POL == PWM								
    SetScalerPWM(BKL_PWM_PORT, (unsigned short)br);		//br);
#else
    SetScalerPWM(BKL_PWM_PORT, 0);	//(1023 - br));
#endif


//-------------------------------------------------
//P320HVN02 _0
//==========================
  SC_SRGB_CTRL = 0x29;
  SC_SRGB_COEF_OFFSET = 138; //r							//141212 mike for 313 329
  SC_SRGB_CTRL = 0x2b;									//FOR AUO_P320HVN02 _0
  SC_SRGB_COEF_OFFSET = 136; //g
  SC_SRGB_CTRL = 0x2d;
  SC_SRGB_COEF_OFFSET = 135; //b
//========================== 
/*
  SC_SRGB_CTRL = 0x29;
  SC_SRGB_COEF_OFFSET = 134; //r							//141212 mike for 313 329
  SC_SRGB_CTRL = 0x2b;									//FOR AUO_P550HVN03_V0
  SC_SRGB_COEF_OFFSET = 132; //g
  SC_SRGB_CTRL = 0x2d;
  SC_SRGB_COEF_OFFSET = 130; //b
*/
//===========================					//140313 mike ADJ T-CON 
/*
  SC_SRGB_CTRL = 0x29;
  SC_SRGB_COEF_OFFSET = 142; //r							//140326 mike for 313 329
  SC_SRGB_CTRL = 0x2b;
  SC_SRGB_COEF_OFFSET = 140; //g
  SC_SRGB_CTRL = 0x2d;
  SC_SRGB_COEF_OFFSET = 137; //b
  */
//-----------------------------

//-----------------------------
/* 
  SC_SRGB_CTRL = 0x29;
  SC_SRGB_COEF_OFFSET = 152; //r		.305					//140326 mike for 313 329
  SC_SRGB_CTRL = 0x2b;
  SC_SRGB_COEF_OFFSET = 149; //g        .348
  SC_SRGB_CTRL = 0x2d;
  SC_SRGB_COEF_OFFSET = 137; //b
    */
//============================
#endif//ENABLE_SCALER_LEDDRV_ANA_MODE == ON

#if ENABLE_LD == ON
    LDAPI_SetBrightness(br >> 2);
#endif

//g printf("+++SetBrightness\n");
}

/**************************************************************************//**
 * Get brightness.
 * @return Value of brightness. The range is 0 ~ 1023.
 ******************************************************************************/
/*
USHRT GetBrightness(void)
{
#if BKL_PWM_POL == HIGH
    return GetScalerPWM(BKL_PWM_PORT);
#else
    return (1023-GetScalerPWM(BKL_PWM_PORT));
#endif
}
*/

/**************************************************************************//**
 * Set the PWM frequency.
 * @param enable TRUE to set frequency for normal display. FALSE to set frequency for free run.
 ******************************************************************************/
void SetBLPwmByInputVSync(UCHAR enable) 			//140313 mike 
{
#if ENABLE_SCALER_LEDDRV == ON
    if (enable == TRUE) 
	{
        	SetLEDDriverFreq(BRIGHTNESS_ND_PWM_FREQ);
    	}
    else 
		{
        		SetLEDDriverFreq(BRIGHTNESS_FR_PWM_FREQ);
    		}
#else
    if (enable == TRUE) 
	   	{
        		ConfigScalerPWM(BKL_PWM_PORT, BKL_PWM_OUTPUT_PIN, BRIGHTNESS_ND_PWM_FREQ);
    		}
    else 
		{
        		ConfigScalerPWM(BKL_PWM_PORT, BKL_PWM_OUTPUT_PIN, BRIGHTNESS_FR_PWM_FREQ);
    		}
#endif
}

/**************************************************************************//**
 * Set audio volume.
 * @param value Value of audio volume. The range is 0 ~ 1023.
 *140429 mike     (((osd value)*Vmax)/100 )+Vmin =output  
 ******************************************************************************/
void SetVolume(USHRT value)   //140429 mike value = osd 
{

   value=(((unsigned short)(value * MAX_VOLUME_VALUE)/100)+MIN_VOLUME_VALUE);	   //140429 mike copy from nt68667 
#if VOLUME_PWM_POL == HIGH
    SetScalerPWM(VOLUME_PWM_PORT, value);
#else
    SetScalerPWM(VOLUME_PWM_PORT, (1023-value));
#endif
//-----------------------------
#if ENABLE_SCALER_AUDIO == ON
    #if (VOLUME_PWM_PORT==PWM_A) || (VOLUME_PWM_PORT==PWM_B) || (VOLUME_PWM_PORT==PWM_C) || (VOLUME_PWM_PORT==PWM_D)
    ConfigScalerAudio(0xFFFF);  // Load default setting
    #else
    value = (ULONG) value * HDMI_AUDIO_VOLUME_RANGE / 1023;
    ConfigScalerAudio(value);
    #endif
#endif
//-----------------------------
}

/**************************************************************************//**
 * Panel power up sequence.
 * @param force TRUE to turn on backlight without checking mode handle state else FALSE.
 ******************************************************************************/
void PanelPowerOnSequence(UCHAR force)
{

    if (IsPanelPowerOn() == FALSE) 
	{
			while (GetGlobalTimer(GLOBAL_TMR_PANEL_ONOFF)) 
			{
            	ResetWDTimer();
        	}
        	PanelPowerOn();
		//===================external power 
			PS_ON();
		//===================			
        	Sleep(UserPanelData.usPowerUpPanelTime+PANEL_POWER_DELAY);
        	LvdsOn();
        	Sleep(UserPanelData.usPowerUpInvTime);
	}
    // Check sync status before turn on backlight to avoid panel flashing
    if (force == FALSE) 
	{
		if (CheckModeChangeFlag() && (GetModeHandleState() == WAIT_MODE_CHANGE)) 
		{
			return;
		}
		if ((GetInputSyncMode() == NO_SYNC) && (bIsCableConnect() == FALSE)) 
		{
			return;
		}
		if ((GetInputSyncMode() == NO_CABLE) && (bIsCableConnect() == TRUE)) 
		{
			return;
		}
	}
	
	BacklightOff();

    BacklightOn();

}

/**************************************************************************//**
 * Panel power down sequence.
 ******************************************************************************/
void PanelPowerOffSequence(void)
{
    BacklightOff();
    SetScalerPWM(BKL_PWM_PORT, 0);//(1023 - br));

    if (IsPanelPowerOn() == TRUE) 
	{
       	 Force2Background(0, 0, 0);
        	 OSDAPI_TurnOffOSD();//2011-05-11:Turn off OSD before white pattern insertion

        	switch(PANEL_PWR_OFF_SEQUENCE_MODE)
			{
          			default:
          		case PANEL_INSERT_BLACK:  
            			Sleep(UserPanelData.usPowerDownInvTime);
            			LvdsOff();
            			Sleep(UserPanelData.usPowerDownPanelTime);
            			PanelPowerOff();
			//============================141205 mike External power 	
		 		 PS_OFF();
			//============================							
          			break;           
          case PANEL_INSERT_WHITE:
            			SetPostBGColor(0xFF, 0xFF, 0xFF);//PANEL_INSERT_WHITE_DISCHARGE_ELECTRICITY 
        			Sleep(UserPanelData.usPowerDownInvTime);
        			LvdsOff();
            			SetPostBGColor(0x00, 0x00, 0x00);//PANEL_INSERT_WHITE_DISCHARGE_ELECTRICITY
            			Sleep(UserPanelData.usPowerDownPanelTime);
            			PanelPowerOff();
			//============================141205 mike External power 	
		 		 PS_OFF();
			//============================									
          			break;
          case PANEL_INSERT_WHITE|PANEL_POWER_LVDS_SWAP:
            			SetPostBGColor(0xFF, 0xFF, 0xFF);//PANEL_INSERT_WHITE_DISCHARGE_ELECTRICITY
        			Sleep(UserPanelData.usPowerDownPanelTime);
        			PanelPowerOff();
			//============================141205 mike External power 	
		 		 PS_OFF();
			//============================								
            			SetPostBGColor(0x00, 0x00, 0x00);//PANEL_INSERT_WHITE_DISCHARGE_ELECTRICITY
            			Sleep(UserPanelData.usPowerDownInvTime);
            			LvdsOff();            
          			break; 
          case PANEL_INSERT_BLACK|PANEL_POWER_LVDS_SWAP:
            			Sleep(UserPanelData.usPowerDownPanelTime);
            			PanelPowerOff();
			//============================141205 mike External power 	
		 		 PS_OFF();
			//============================			
						
            			Sleep(UserPanelData.usPowerDownInvTime);
            			LvdsOff();          
          			break;  
       		}

        	SetGlobalTimer(GLOBAL_TMR_PANEL_ONOFF, GBTM_PANEL_ONOFF);
	}
}


#if (ENABLE_DIGI1_HPD == ON) || (ENABLE_DIGI0_HPD == ON) || (ENABLE_DP_HPD == ON)
/**************************************************************************//**
 * Pull up HDP pin.
 ******************************************************************************/
void SYSAPI_PerformHPDOn(void)
{
	#if ENABLE_DIGI0_HPD == ON
    	//if (GetCurrInputInterface() == DIGITAL_INPUT0) {
        	Digi0HPDOn();
    	//}
	#endif

	#if ENABLE_DIGI1_HPD == ON
    	//if (GetCurrInputInterface() == DIGITAL_INPUT1) {
    	    Digi1HPDOn();
    	//}
	#endif

	#if ENABLE_DP_HPD == ON
    	//if (GetCurrInputInterface() == DISPLAY_PORT_INPUT) {
    	    DPHPDOn();
    	//}
	#endif
}

/**************************************************************************//**
 * Pull low HDP pin.
 ******************************************************************************/
void SYSAPI_PerformHPDOff(UCHAR force)
{
    UCHAR curr_interface = GetCurrInputInterface();
    
    // We have to hide the SystemData variables in the future :)
	if (force == TRUE) 
	{
		#if ENABLE_DIGI0_HPD == ON
            Digi0HPDOff();
		#endif

		#if ENABLE_DIGI1_HPD == ON
            Digi1HPDOff();
		#endif

		#if ENABLE_DP_HPD == ON
            DPHPDOff();
		#endif
		
		SetGlobalTimer(GLOBAL_TMR_HPD, HPD_LOW_PERIOD);
	}    
	else {

		#if ENABLE_DIGI0_HPD == ON
        	if ((curr_interface == DIGITAL_INPUT0) && IsDigital0Connect()) {
            	Digi0HPDOff();
                SetGlobalTimer(GLOBAL_TMR_HPD, HPD_LOW_PERIOD);
			}
		#endif

		#if ENABLE_DIGI1_HPD == ON
        	if ((curr_interface == DIGITAL_INPUT1) && IsDigital1Connect()) {
            	Digi1HPDOff();            
                SetGlobalTimer(GLOBAL_TMR_HPD, HPD_LOW_PERIOD);
			}
		#endif

		#if ENABLE_DP_HPD == ON
    		#if ENABLE_DP_ADV_HPD == ON
                if ((curr_interface == DISPLAY_PORT_INPUT) && IsDPConnect()) {
                    if ((IsDPTrainingDone() == FALSE) && (!IsZpMode())) {
                    	DPHPDOff();
                    	SetGlobalTimer(GLOBAL_TMR_HPD, DP_HPD_LOW_PERIOD);
                	}
       			}
    		#endif

			if (UserData.bPowerStatus == OFF) {
				DPHPDOff();
				SetGlobalTimer(GLOBAL_TMR_HPD, DP_HPD_LOW_PERIOD);
			}
		#endif
	}
}

#endif
