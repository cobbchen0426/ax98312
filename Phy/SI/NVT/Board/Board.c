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
#if PANEL_POWER_PORT == MCU_PORT_NULL
static bit bPanelPower = (~PANEL_POWER_ACTIVE & BIT0);
#endif

static BOOL bTouchState = OFF;		//george-create
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
// Prototype: 
//  BOOL bIsCableConnect(void)
// Parameters:
//  None
// Return:
//  TRUE/FALSE
// Purpose:
//  Determine the cable connection
// Notes:
//  None
//******************************************************************************
BOOL bIsCableConnect(void)							 
{
    if (SystemData.bFactory == TRUE)  
	 return (bIsVGAConnect() | IsDigital1Connect() | IsDigital0Connect() | IsDPConnect()); 	
  else	
 	 return (1);			
   }

//******************************************************************************
// Prototype: 
//  BOOL bIsVGAConnect(void)
// Parameters:
//  None
// Return:
//  TRUE/FALSE
// Purpose:
//  Determine the VGA cable connection
// Notes:
//  None
//******************************************************************************
BOOL bIsVGAConnect(void)
{
#if VGA_CABLE_PORT == MCU_PORT_NULL
#if IS_NT68150_SERIES
    UCHAR level;
    ADC_5V_EN |= BIT0;//5V ADC
    ADC_CON |= BIT0; //Enable ADC 0
    McuPowerUpADC();
    McuStartADC();
    McuWaitADCComplete();
    McuPowerDownADC();
    level = McuGetADC(MCU_ADC_0);
    ADC_CON &= ~BIT0; //Disable ADC 0
    if (level > VGA_DET_LEVEL) 
		{
    			return FALSE;
    		}
    else 
		{
        		return TRUE;
    		}
	    #else
    		return FALSE;
	#endif
#else
    if (McuGetIOBit(VGA_CABLE_PORT, VGA_CABLE_BIT) == VGA_CABLE_ACTIVE) 
	{
        	return TRUE;
       }
    else 
		{
        		return FALSE;
    		}
#endif
}

//******************************************************************************
// Prototype: 
//  BOOL IsDigital1Connect(void)
// Parameters:
//  None
// Return:
//  TRUE/FALSE
// Purpose:
//  Determine the digital interface 1 cable connection
// Notes:
//  None
//******************************************************************************
BOOL IsDigital1Connect(void)
{
#if DIGI1_CABLE_PORT == MCU_PORT_NULL
    return FALSE;
#else
    if (McuGetIOBit(DIGI1_CABLE_PORT, DIGI1_CABLE_BIT) == DIGI1_CABLE_ACTIVE) 
	{
		#if (INPUT_INTERFACE&INPUT_MHL1)
        if ( MHLIsCBus2On() == ON && !IsMHL1Connect()) 
		{
            		return FALSE;
        	}
#endif
        	return TRUE;
    	}
    else 
	  	{
           		return FALSE;
    		}
#endif
}

//******************************************************************************
// Prototype: 
//  BOOL IsDigital0Connect(void)
// Parameters:
//  None
// Return:
//  TRUE/FALSE
// Purpose:
//  Determine the digital interface 0 cable connection
// Notes:
//  None
//******************************************************************************
BOOL IsDigital0Connect(void)
{
#if DIGI0_CABLE_PORT == MCU_PORT_NULL
    return FALSE;
#else
    if (McuGetIOBit(DIGI0_CABLE_PORT, DIGI0_CABLE_BIT) == DIGI0_CABLE_ACTIVE) 
	{
	#if (INPUT_INTERFACE&INPUT_MHL0)
       	 if ( MHLIsCBus1On() == ON && !IsMHL0Connect()) 
		 	{
            			return FALSE;
    			}
#endif
            return TRUE;
      }
    else 
		{
        		return FALSE;
    		}
#endif
}

//******************************************************************************
// Prototype: 
//  BOOL IsDPConnect(void)
// Parameters:
//  None
// Return:
//  TRUE/FALSE
// Purpose:
//  Determine the DP interface cable connection
// Notes:
//  None
//******************************************************************************
BOOL IsDPConnect(void)
{
#if (INPUT_INTERFACE&INPUT_DP)
	#if DP_CABLE_PORT == MCU_PORT_NULL
		return FALSE;
	#else
	    if (McuGetIOBit(DP_CABLE_PORT, DP_CABLE_BIT) == DP_CABLE_ACTIVE) 
		{
	        	return TRUE;
		}
	    else 
		{
	        	return FALSE;
		}
	#endif
#else
    	return FALSE;
#endif
}

//******************************************************************************
// Prototype: 
//  BOOL IsPanelPowerOn(void)
// Parameters:
//  None
// Return:
//  TRUE/FALSE
// Purpose:
//  Check panel power.
// Notes:
//  None
//******************************************************************************
BOOL IsPanelPowerOn(void)
{
#if PANEL_POWER_PORT == MCU_PORT_NULL
    return bPanelPower;
#else
    if (McuGetIOBit(PANEL_POWER_PORT, PANEL_POWER_BIT) == PANEL_POWER_ACTIVE) {
        return TRUE;
    }
    else {
        return FALSE;
    }
#endif
}

//******************************************************************************
// Prototype: 
//  void LedGreenOn(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Turn on the green LED.
// Notes:
//  None
//******************************************************************************
void LedGreenOn(void)
{
#if PWRSeq_Deug == ENABLE
printf("___LedGreenOn_____\n");
#endif
    McuSetIOBit(LED_GREEN_PORT, LED_GREEN_BIT, LED_GREEN_ACTIVE);
    McuSetIOBit(PSB_PORT, PSB_BIT, PSB_ACTIVE);   //FEFANJACKY ADD FOR PSB ON
}

//******************************************************************************
// Prototype: 
//  void LedGreenOn(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Turn off the green LED.
// Notes:
//  None
//******************************************************************************
void LedGreenOff(void)
{
#if PWRSeq_Deug == ENABLE
printf("___LedGreenOff_____\n");
#endif 
    McuSetIOBit(LED_GREEN_PORT, LED_GREEN_BIT, ~LED_GREEN_ACTIVE);
}

//******************************************************************************
// Prototype: 
//  void LedRedOn(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Turn on the red LED.
// Notes:
//  None
//******************************************************************************
void LedRedOn(void)
{		//PortA = PortA | RDPA_REG | BIT7;	 
#if KEY_LED_Flash == DISABLE		//X_ADS_AD907,  X_ADS_AD908
	McuSetIOBit(LED_RED_PORT, LED_RED_BIT, LED_RED_ACTIVE);
#elif KEY_LED_Flash == ENABLE    	//for AXI AX98310 request-Flash
	// don't do-somthing.  //for AXI request function: Hide LedRed and at_PowerSaving_flash_LedGreen.
#endif
}

//******************************************************************************
// Prototype: 
//  void LedRedOff(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Turn off the red LED.
// Notes:
//  None
//******************************************************************************
void LedRedOff(void)
{	//PortA = (PortA | RDPA_REG) & (~BIT7);

#if KEY_LED_Flash == DISABLE		//X_ADS_AD907,  X_ADS_AD908
	McuSetIOBit(LED_RED_PORT, LED_RED_BIT, ~LED_RED_ACTIVE);
#elif KEY_LED_Flash == ENABLE    	//for AXI AX98310 request-Flash
	// don't do-somthing.  //for AXI request function: Hide LedRed and at_PowerSaving_flash_LedGreen.
#endif
}

//******************************************************************************
// Prototype: 
//  void PanelPowerOn(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Turn on the panel power.
// Notes:
//  None
//******************************************************************************
void PanelPowerOn(void)
{
#if PANEL_POWER_PORT == MCU_PORT_NULL
    bPanelPower = PANEL_POWER_ACTIVE & BIT0;
#else
    McuSetIOBit(PANEL_POWER_PORT, PANEL_POWER_BIT, PANEL_POWER_ACTIVE);
#endif
}

//******************************************************************************
// Prototype: 
//  void PanelPowerOff(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Turn off the panel power.
// Notes:
//  None
//******************************************************************************
void PanelPowerOff(void)
{
#if PANEL_POWER_PORT == MCU_PORT_NULL
    bPanelPower = ~PANEL_POWER_ACTIVE & BIT0;
#else
    McuSetIOBit(PANEL_POWER_PORT, PANEL_POWER_BIT, ~PANEL_POWER_ACTIVE);
#endif
}
//===================141205 mike 
 //46W   PORT C4  	#PS_Signal 
 //===================
void PS_OFF(void)
{
    unsigned char port;
	port = PortC;
	port |= RDPC_REG;
	port &= ~ BIT4;
	PortC= port;
}
void PS_ON(void)
{
     unsigned char port;	
	port = PortC;
	port |= RDPC_REG;
	port |=BIT4;
	PortC= port;
}
//======================//141205 mike
//******************************************************************************
// Prototype: 
//  void BacklightOn(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Turn on the backlight.
// Notes:
//  None
//******************************************************************************
void BacklightOn(void)
{

#if ENABLE_SCALER_LEDDRV == ON
    LEDDriverOnOff(ON);
#else
    McuSetIOBit(BACKLIGHT_PORT, BACKLIGHT_BIT, BACKLIGHT_ACTIVE);
#endif

#if ENABLE_ESD_PROTECT == ON
    ReadESDCheckSum();
#endif


#if ALS_EnDis == ALSMODE
	if(UserData.ucALSMode == OFF){
		SetBrightness(GetBrightness1023());
	}else {	//if(UserData.ucALSMode == INDOOR || UserData.ucALSMode == OUTDOOR) {								//george: F_CM3218_01					  				//george: F_CM3218_ALSMODE
		CM3218_BacklightOn_Init();
		SetNowALSBrig();
	}
#elif ALS_EnDis == ALSOffSET	
	if(UserData.bALSOnOff == OFF){
		SetBrightness(GetBrightness1023());
	}else {						  				//george: F_CM3218_01
		CM3218_ALSOnInit();
		CM3218_BacklightOn_Init();
	}
#elif ALS_EnDis == ALSRange	//for ADS
	SetBrightness(GetBrightness1023());		// _CCC_
#else	//Normal
	SetBrightness(GetBrightness1023());
#endif	//#if ALS_EnDis == ENABLE	


}

//******************************************************************************
// Prototype: 
//  void BacklightOff(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Turn off the backlight.
// Notes:
//  None
//******************************************************************************
void BacklightOff(void)
{
	#if ENABLE_SCALER_LEDDRV == ON
	    LEDDriverOnOff(OFF);
	#else
	    McuSetIOBit(BACKLIGHT_PORT, BACKLIGHT_BIT, ~BACKLIGHT_ACTIVE);
	    SetBrightness(0);
	#endif
}

#if ENABLE_ESD_PROTECT == ON
//******************************************************************************
// Prototype: 
//  BOOL IsBackLightOn(void)
// Parameters:
//  None
// Return:
//  TRUE/FALSE
// Purpose:
//  Check panel power.
// Notes:
//  None
//******************************************************************************
BOOL IsBackLightOn(void)
{
    if (McuGetIOBit(BACKLIGHT_PORT, BACKLIGHT_BIT) == BACKLIGHT_ACTIVE) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}
#endif

//******************************************************************************
// Prototype: 
//  void AudioPowerOn(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Turn on the Audio AMP power.
// Notes:
//  None
//******************************************************************************
void AudioPowerOn(void)
{
    McuSetIOBit(AMP_PWR_PORT, AMP_PWR_BIT, AMP_PWR_ACTIVE);
}

//******************************************************************************
// Prototype: 
//  void AudioPowerOff(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Turn off the Audio AMP power.
// Notes:
//  None
//******************************************************************************
void AudioPowerOff(void)
{
    McuSetIOBit(AMP_PWR_PORT, AMP_PWR_BIT, ~AMP_PWR_ACTIVE);
}

//******************************************************************************
// Prototype: 
//  void AudioAMP_Off(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Mute the Audio AMP.
// Notes:
//  None
//******************************************************************************
void AudioMuteOn(void)						
{
    McuSetIOBit(AMP_MUTE_PORT, AMP_MUTE_BIT, AMP_MUTE_ACTIVE);
#if PWRSeq_Deug == ENABLE
	printf("_Audio-MUTE_\n");
#endif
}

//******************************************************************************
// Prototype: 
//  void AudioAMP_On(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Turn on the Audio AMP.
// Notes:
//  None
//******************************************************************************
void AudioMuteOff(void)
{
    McuSetIOBit(AMP_MUTE_PORT, AMP_MUTE_BIT, ~AMP_MUTE_ACTIVE);
#if PWRSeq_Deug == ENABLE
	printf("_Audio-Un-MUTE_\n");
#endif
}

//******************************************************************************
// Prototype: 
//  void EdidWPOn(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  
// Notes:
//  None
//******************************************************************************
void EdidWPOn(void)
{
    McuSetIOBit(EDID_WP_PORT, EDID_WP_BIT, EDID_WP_ACTIVE);
}

//******************************************************************************
// Prototype: 
//  void EdidWPOff(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  
// Notes:
//  None
//******************************************************************************
void EdidWPOff(void)
{
    McuSetIOBit(EDID_WP_PORT, EDID_WP_BIT, ~EDID_WP_ACTIVE);
}

#if ENABLE_CUT_POWER_ARCH == ON
//******************************************************************************
// Prototype: 
//  void PowerMOSOn(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Turn on the power MOS
// Notes:
//  None
//******************************************************************************
void PowerMOSOn(void)
{
    McuSetIOBit(POWER_MOS_PORT, POWER_MOS_BIT, POWER_MOS_ACTIVE);
}

//******************************************************************************
// Prototype: 
//  void PowerMOSOff(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Turn off the power MOS
// Notes:
//  None
//******************************************************************************
void PowerMOSOff(void)
{
    McuSetIOBit(POWER_MOS_PORT, POWER_MOS_BIT, ~POWER_MOS_ACTIVE);
}
#endif

#if ENABLE_DIGI1_HPD == ON
//******************************************************************************
// Prototype: 
//  void Digi1HPDOn(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Set hot plug in active state (connected)
// Notes:
//  None
//******************************************************************************
void Digi1HPDOn(void)
{
    McuSetIOBit(DIG1_HPD_PORT, DIG1_HPD_BIT, DIG1_HPD_ACTIVE);
}

//******************************************************************************
// Prototype: 
//  void Digi1HPDOff(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Set hot plug in inactive state (disconnected)
// Notes:
//  None
//******************************************************************************
void Digi1HPDOff(void)
{
    McuSetIOBit(DIG1_HPD_PORT, DIG1_HPD_BIT, ~DIG1_HPD_ACTIVE);
}
#endif

#if ENABLE_DIGI0_HPD == ON
//******************************************************************************
// Prototype: 
//  void Digi0HPDOn(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Set hot plug in active state (connected)
// Notes:
//  None
//******************************************************************************
void Digi0HPDOn(void)
{
    McuSetIOBit(DIG0_HPD_PORT, DIG0_HPD_BIT, DIG0_HPD_ACTIVE);
}

//******************************************************************************
// Prototype: 
//  void Digi0HPDOff(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Set hot plug in inactive state (disconnected)
// Notes:
//  None
//******************************************************************************
void Digi0HPDOff(void)
{
    McuSetIOBit(DIG0_HPD_PORT, DIG0_HPD_BIT, ~DIG0_HPD_ACTIVE);
}
#endif

#if (INPUT_INTERFACE&INPUT_DP)
//******************************************************************************
// Prototype: 
//  void DPHPDOn(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Set hot plug in active state (connected)
// Notes:
//  None
//******************************************************************************
void DPHPDOn(void)
{
    McuSetIOBit(DP_HPD_PORT, DP_HPD_BIT, DP_HPD_ACTIVE);
    if (IsZpMode() == FALSE) {
        DPConfigHWHPD(TRUE);
    }
}

#if ENABLE_DP_HPD == ON
//******************************************************************************
// Prototype: 
//  void DPHPDOff(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Set hot plug in inactive state (disconnected)
// Notes:
//  None
//******************************************************************************
void DPHPDOff(void)
{
    McuSetIOBit(DP_HPD_PORT, DP_HPD_BIT, ~DP_HPD_ACTIVE);
    DPConfigHWHPD(FALSE);
}
#endif
#endif

#if (ENABLE_DIGI1_HPD == ON) || (ENABLE_DIGI0_HPD == ON) || (ENABLE_DP_HPD == ON)
//******************************************************************************
// Prototype: 
//  BOOL bIsHPDActive(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
BOOL bIsHPDActive(void)
{
   UCHAR curr_interface = GetCurrInputInterface();
    
#if (INPUT_INTERFACE&INPUT_MHL0)
            if ( curr_interface == DIGITAL_INPUT0 && IsMHL0CableConnect() ) {
                return TRUE;
            }
#endif
#if (INPUT_INTERFACE&INPUT_MHL1)
            if ( curr_interface == DIGITAL_INPUT1 && IsMHL1CableConnect() ) {
                return TRUE;
            }
#endif

#if ENABLE_DIGI0_HPD == ON && DIG0_HPD_PORT != MCU_PORT_NULL
   if (McuGetIOBit(DIG0_HPD_PORT, DIG0_HPD_BIT) != DIG0_HPD_ACTIVE && curr_interface == DIGITAL_INPUT0) {
        return FALSE;
    }
#endif
#if ENABLE_DIGI1_HPD == ON && DIG1_HPD_PORT != MCU_PORT_NULL
   if (McuGetIOBit(DIG1_HPD_PORT, DIG1_HPD_BIT) != DIG1_HPD_ACTIVE && curr_interface == DIGITAL_INPUT1) {
        return FALSE;
    }
#endif
#if (INPUT_INTERFACE&INPUT_DP)
#if ENABLE_DP_HPD == ON && DP_HPD_PORT != MCU_PORT_NULL
   if (McuGetIOBit(DP_HPD_PORT, DP_HPD_BIT) != DP_HPD_ACTIVE && curr_interface == DISPLAY_PORT_INPUT) {
        return FALSE;
    }
#endif
#endif
    return TRUE;
}
#endif


//******************************************************************************	//150612 george:create
// Prototype: 
//  void TouchOnOff(BOOL on)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Turn On or Off the Touch Screen.
// Notes:
//  None
//******************************************************************************
#if TOUCH_EnDis == ENABLE
	void TouchOnOff(BOOL on)
	{
	//UserData.bTouchOnOff = ~UserData.bTouchOnOff;
		if(on)
		{						  
			if(bTouchState != ON )
			{
				bTouchState = ON;
				McuSetIOBit(LED_RED_PORT, LED_RED_BIT, LED_RED_ACTIVE);
			}
		}
		else
		{	
			if(bTouchState != OFF )
			{
				bTouchState = OFF;
				McuSetIOBit(LED_RED_PORT, LED_RED_BIT, ~LED_RED_ACTIVE);
			}
		}    
	}
#endif //#if TOUCH_EnDis == ENABLE
