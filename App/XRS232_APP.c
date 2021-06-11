/******************************************************************************/
/*                    Axiomdisplay CO,, LTD.                                  */
/*                    All Rights Reserved                                     */
/*                    XRS232 Remote Controller APP Function                   */
/******************************************************************************/

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************
#include "Include.h"


#if (XRS232 == ADS_RS232)
//******************************************************************************
// M A C R O   D E F I N I T I O N S
//******************************************************************************

//******************************************************************************
// S T A T I C   V A R I A B L E S
//******************************************************************************

xdata UCHAR tmp=0;
//******************************************************************************
// G L O B A L   V A R I A B L E S
//******************************************************************************


//******************************************************************************
// S T A T I C   V A R I A B L E S
//******************************************************************************
    
//******************************************************************************
// E X T E R N A L   V A R I A B L E   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// S T A T I C   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// E X T E R N A L   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************




void Analy_CMD(void)
{

	UCHAR i=0,CkCRC=0;

	UCHAR tmp=0, bbuf[4];
	 
	if(	tmp=UART_Getchar(bbuf) )	// if tmp = true, have data
	{

//		putchar(bbuf[0]);	//CMD
//		putchar(bbuf[1]);	//Index
//		putchar(bbuf[2]);	//Value
//		putchar(bbuf[3]);	//CRC

//		putchar(bbuf[4]);	
//		if( (bbuf[0]==0x01) && (bbuf[1]==0x80) )	//for UserData.usADBoardID (2 Bytes)
//		{
//			CkCRC = 0x100 - bbuf[0] - bbuf[1] - bbuf[2] - bbuf[3];
//			if(CkCRC != bbuf[4]){
//				return;
//			}
//		}else										// Other: Normal Function item (1 Bytes)
		{
			CkCRC = 0x100 - bbuf[0] - bbuf[1] - bbuf[2];
	
			if(CkCRC != bbuf[3]){
				return;
			}		
		}



		if(bbuf[0] == 0x00) //Read -> putchar()
		{
			switch(bbuf[1]) //Focus_Item
			{						  //Focus_value_return;
				case 0x10:	
					#if ALS_EnDis == ALSMODE	
								 if(UserData.ucALSMode==ALS_OFF)
								 	{ putchar(0xAA);	putchar(UserData.ucBrightness);	putchar( 0x100-UserData.ucBrightness);	break;	}	//Brightness
								 else if(UserData.ucALSMode==INDOOR || UserData.ucALSMode==OUTDOOR)
									{ putchar(0xAA);	putchar(NowAlsBright);	putchar( 0x100-NowAlsBright);	break;	}					// ALS_Brightness

					#elif ALS_EnDis == ALSOffSET	
								if(UserData.bALSOnOff == OFF)
								 	{ putchar(0xAA);	putchar(UserData.ucBrightness);	putchar( 0x100-UserData.ucBrightness);	break;	}	//Brightness
								 else if(UserData.bALSOnOff == ON)
									{ putchar(0xAA);	putchar(NowAlsBright);	putchar( 0x100-NowAlsBright);	break;	}					// ALS_Brightness

					#elif ALS_EnDis == ALSRange	//for ADS
								if(UserData.bALSOnOff == OFF)
								 	{ putchar(0xAA);	putchar(UserData.ucBrightness);	putchar( 0x100-UserData.ucBrightness);	break;	}	//Brightness
								 else if(UserData.bALSOnOff == ON)
									{ putchar(0xAA);	putchar(NowAlsBright);	putchar( 0x100-NowAlsBright);	break;	}					// ALS_Brightness				
					#else
						{ putchar(0xAA);	putchar(UserData.ucBrightness);	putchar( 0x100-UserData.ucBrightness);	break;	}	//Brightness
					#endif	//#if ALS_EnDis == ENABLE				


				case 0x11:	putchar(0xAA);	putchar(UserData.ucContrast);	putchar( 0x100-UserData.ucContrast);	break;	//Contrast
				//case 0x17:	break;	//AutoTurn;	 don't need Read.

				case 0x20:	{	if(UserData.ucColorTemp == 0)		tmp = 2;	// NT68856=0_6500k, APP=0_9300k				//ColorTemp
								else if(UserData.ucColorTemp == 1)	tmp = 1;	// NT68856=1_7500k, APP=1_7500k
								else if(UserData.ucColorTemp == 2)	tmp = 0;	// NT68856=2_9300k, APP=2_6500k
								else if(UserData.ucColorTemp == 3)	tmp = 3;	// NT68856=3_UserMode, APP=3_none.

								putchar(0xAA);	putchar(tmp);	putchar( 0x100-tmp);	
								break;	
							}

				case 0x21:  putchar(0xAA); putchar(UserData.ucUserRGain);	putchar( 0x100 - UserData.ucUserRGain);	break;	//ColorTemp-User: R-Gain	//george 160216 
				case 0x22:  putchar(0xAA); putchar(UserData.ucUserGGain);	putchar( 0x100 - UserData.ucUserGGain);	break;	//ColorTemp-User: G-Gain	//george 160216 
				case 0x23:  putchar(0xAA); putchar(UserData.ucUserBGain);	putchar( 0x100 - UserData.ucUserBGain);	break;	//ColorTemp-User: B-Gain	//george 160216 
				
				case 0x24:  putchar(0xAA); putchar(UserData.ucSRMode);		putchar( 0x100 - UserData.ucSRMode);	break;	//Sharpness: Off/Weak/Median/Strong/Strongest	//george 160216 							

				case 0x25:  putchar(0xAA);	putchar(0xFF);	putchar(0x01);			break;		//Saturation: "Disable" (for Video-Decoder Input)	//george 160216
				case 0x26:  putchar(0xAA);	putchar(0xFF);	putchar(0x01);			break;		//Hue       : "Disable" (for Video-Decoder Input)	//george 160216

				case 0x40:	{	//InputSource
								if( (ucModeHdlrState == POWER_SAVING_MODE) || (ucModeHdlrState == WAIT_SYNC_STABLE) )	// at PowerSaving Mode
								{
									putchar(0xAA);	putchar(0xFF);	putchar( 0x100-0xFF);		break; 	
								}else{
									if(UserData.ucInputSource == 0)			tmp = 0;	// NT68856=0_VGA,  APP=0_VGA			
									else if(UserData.ucInputSource == 2)	tmp = 1;	// NT68856=2_DVI,  APP=1_DVI
									else if(UserData.ucInputSource == 5)	tmp = 2;	// NT68856=5_HDMI, APP=2_none
									else if(UserData.ucInputSource == 9)	tmp = 3;	// NT68856=9_DP,   APP=3_none
									else tmp = 0xff;	// NT68856= don't know 
									putchar(0xAA);	putchar(tmp);	putchar( 0x100-tmp);		break; 
								}
							}
 
 				case 0x41:	{	// tell APP input supply item. (VGA/DVI....)
								// 8bit: MSB(x    x      x        x)  (x   x    x    x)LSB 
								//          (USB, YPbPr, S-Video, AV) (DP, HDI, DVI, VGA)
																
							#if BUILD_CUSTOMER == X_INP_DHP
								tmp = 0x0E;							
							#elif BUILD_CUSTOMER == X_INP_VDH
								tmp = 0x07;							
							#elif BUILD_CUSTOMER == X_INP_DH
								tmp = 0x0F;								
							#else
							#endif 

								putchar(0xAA);	putchar(tmp);	putchar( 0x100-tmp);		break;
							}

 				case 0x42:	{	//OSD Language
								//ADS-XRS232_Spec.:	0_English, 4_Espanol ,1_Franch, 2_Deutsch, 3_Italiano, 5_Portugues, 6_Pyccknn, 7_China
								// NT68856_Code	  :	0_English, 1_Espanol ,2_Franch, 3_Deutsch, 4_Italiano, 5_Portugues, 6_Pyccknn, 7_China

								if(UserData.ucLanguage == 1)		tmp = 4;	//Espanol
								else if(UserData.ucLanguage == 2)	tmp = 1;	//Frach
								else if(UserData.ucLanguage == 3)	tmp = 2;	//Deutsch
								else if(UserData.ucLanguage == 4)	tmp = 3;	//Italiano
								else
									tmp = UserData.ucLanguage;					//Other no-change: 0_English, 5_Portugues, 6_Pyccknn, 7_China

								putchar(0xAA);	putchar(tmp);	putchar( 0x100-tmp);		break;
							}

 				case 0x43:	{	//OSD Time Out 
								tmp = UserData.ucOSDTimer;
								putchar(0xAA);	putchar(tmp);	putchar( 0x100-tmp);		break;
							}


 				case 0x44:	{	//Aspect Ratio 	
								//Spec.			: 0_Full,		 1_4:3,			 2_16:9
								//Now Code		: 0_FullScreen,  1_Smart-Fit, 	 2_4:3,   3_Smart-4:3
								//tmp = UserData.ucxxx;
								if(ENABLE_ASPECT_RATIO == ON){
									tmp = UserData.ucAspectRatio;
									putchar(0xAA);	putchar(tmp);	putchar( 0x100-tmp);		break;
								}else{
									putchar(0xAA);	putchar(0xFF);	putchar( 0x100-tmp);		break;	//Aspect Ratio: "Disable"
								}								
							}

				case 0x50:	{																								//Auto Diming
							#if ALS_EnDis == ALSMODE
								putchar(0xAA);	putchar( (UserData.ucALSMode >0) ?1 :0);	putchar( 0x100 - ((UserData.ucALSMode >0) ?1 :0) );		
							#elif ALS_EnDis == ALSOffSET	
								putchar(0xAA);	putchar(UserData.bALSOnOff);				putchar( 0x100 - UserData.bALSOnOff);
							#elif ALS_EnDis == ALSRange
								putchar(0xAA);	putchar(UserData.bALSOnOff);				putchar( 0x100 - UserData.bALSOnOff);
							#else	//Normal
								putchar(0xAA);	putchar(0xFF);	putchar(0x01);												//Disable ALS
							#endif	//#if ALS_EnDis == ENABLE
								break;	
							}

				case 0x51:	putchar(0xAA);	putchar(0xFF);	putchar(0x01);			break;									//PIR: "Disable"
				case 0x52:	putchar(0xAA);	putchar(0xFF);	putchar(0x01);			break;									//Video-Disable(Detect)	(0x52), "Disable"

				case 0x60:	{
								if(UserData.ucVolume == 0xFF)
									tmp = 0xFF;					//Audio: "Disable" (when ucVolume = 0xFF)
								else
									tmp = UserData.ucVolume;
								
								putchar(0xAA);	putchar(tmp);	putchar( 0x100 - UserData.ucVolume);		break;			//Audio: Volume
							}

				case 0x61:	{
								if(UserData.ucVolume == 0xFF)
									tmp = 0xFF;					//Audio: "Disable" (when ucVolume = 0xFF)
								else 
									tmp = UserData.bAudioMute;
									
								
								putchar(0xAA);	putchar(tmp);	putchar( 0x100 - UserData.bAudioMute);		break;			//Audio: Mute
							}

				//case 0x70:	break;	//OSD-Recall;	 don't need Read.

				case 0x80:	//AD Board ID (Low-Byte ) 
							putchar(0xAA);	
							tmp = UserData.usADBoardID;			putchar(tmp);	//putchar((UCHAR)UserData.usADBoardID);	
							putchar( 0x100 - (UCHAR)UserData.usADBoardID);
							break;

				case 0x81:	//AD Board ID (Hi-Byte ) 							
							putchar(0xAA);	
							tmp = UserData.usADBoardID >> 8;	putchar(tmp);	
							putchar( 0x100 - (UCHAR)(UserData.usADBoardID >> 8) );
							break;

				case 0xE1:	putchar(0xAA);	putchar(UserData.bPowerStatus);	putchar( 0x100-UserData.bPowerStatus);	break;	//Power_Status

			#if ALS_EnDis == ALSRange 
				case 0x12:	putchar(0xAA);	putchar(UserData.ucALSBrigMAX);	putchar(0x100-UserData.ucALSBrigMAX);	break;	//Bright_MAX (0x12), set "100%"
				case 0x13:	putchar(0xAA);	putchar(UserData.ucALSBrigMIN);	putchar(0x100-UserData.ucALSBrigMIN);	break;	//Bright_MIN (0x13), set "0%"
			#else	//Normal: Disable ALS
				case 0x12:	putchar(0xAA);	putchar(100);	putchar(0x100-100);			break;	//test Disable: ALSBirgMAX=100
				case 0x13:	putchar(0xAA);	putchar(0);		putchar(0x100-0);			break;	//test Disable: ALSBirgMIN=0
			#endif

				default:
					//gg ucUARTRxIn=0; ucIsRecivCMDSS=0; return;
					break;
			}//End switch(bbuf[1])
		}

		else if (bbuf[0] == 0x01) //Write -> set UserData.
		{						  // *ref.  (at EventHandle.c -> EventHandler()): Rule => ....if(IsAPPUpdUsr())  -> NvramWriteUserData(&UserData);
			switch(bbuf[1]) //Focus_Item
			{
				
				case 0x10:								//Brightness
						if(bbuf[2] > 100)
							bbuf[2] = 100;
					#if ALS_EnDis == ALSMODE	
						if(UserData.ucALSMode==ALS_OFF)
						{	UserData.ucBrightness=bbuf[2];	UserSetBrightness();	NvramWriteUserData(&UserData);	}
					#elif ALS_EnDis == ALSOffSET	
						if(UserData.bALSOnOff == OFF)
						{  	UserData.ucBrightness=bbuf[2];	UserSetBrightness();	NvramWriteUserData(&UserData);	}
					#elif ALS_EnDis == ALSRange	//for ADS
						if(UserData.bALSOnOff == OFF)
						{	UserData.ucBrightness=bbuf[2];	UserSetBrightness();	NvramWriteUserData(&UserData);	}
					#else
						{	UserData.ucBrightness=bbuf[2];	UserSetBrightness();	NvramWriteUserData(&UserData);	}//UART_NvRamUpdate();	//can't find: SetOSDUpdUsrFlag();
					#endif	//#if ALS_EnDis == ENABLE	
					break;

				case 0x11:									//Contrast
							if(bbuf[2] > 100)
								bbuf[2] = 100;
							UserData.ucContrast = bbuf[2];	UserSetContrast();	NvramWriteUserData(&UserData);	break;					
					
					
				case 0x17:	UserPerformAutoTune();	break;	//Autotune Active (0x17),  when "VGA-Input" used.


				case 0x20:	{								//ColorTemp
								if(bbuf[2] >= 4)
									break;

								if(bbuf[2] == 0)		tmp = 2;	// NT68856=0_6500k, APP=0_9300k									
								else if(bbuf[2] == 1)	tmp = 1;	// NT68856=1_7500k, APP=1_7500k
								else if(bbuf[2] == 2)	tmp = 0;	// NT68856=2_9300k, APP=2_6500k
								else if(bbuf[2] == 3)	tmp = 3;	// NT68856=3_UserMode, APP=3_none.

								UserData.ucColorTemp=tmp;	UserSetColorTemp();	NvramWriteUserData(&UserData);	break;									
							}

				case 0x21:  if(bbuf[2] > 100)				//ColorTemp-User: R-Gain	//george 160216 
								break;
							UserData.ucUserRGain=bbuf[2];	UserSetRGain();		NvramWriteUserData(&UserData);	break;
				
				case 0x22:  if(bbuf[2] > 100)				//ColorTemp-User: G-Gain	//george 160216
								break;
							UserData.ucUserGGain=bbuf[2];	UserSetGGain();		NvramWriteUserData(&UserData);	break;

				case 0x23:  if(bbuf[2] > 100)				//ColorTemp-User: B-Gain	//george 160216 
								break;
							UserData.ucUserBGain=bbuf[2];	UserSetBGain();		NvramWriteUserData(&UserData);	break;

				case 0x24:  if(bbuf[2] >= 5)				//Sharpness: Off/Weak/Median/Strong/Strongest	//george 160216 							
								break;
							UserData.ucSRMode=bbuf[2];		UserSetSR();		NvramWriteUserData(&UserData);	break;

				case 0x25:  break;	//Saturation : "Disable" (for Video-Decoder Input)	//george 160216
				case 0x26:  break;	//Hue        : "Disable" (for Video-Decoder Input)	//george 160216

				case 0x40:	{	if(bbuf[2] >= 8)			//InputSource (0x40)	//george 160216
									break;

								if(bbuf[2] == 0)		UserData.ucInputSource =INPUT_SC_VGA;	// NT68856=0_VGA,  APP=0_VGA
								else if(bbuf[2] == 1)	UserData.ucInputSource =INPUT_SC_DVI;	// NT68856=2_DVI,  APP=1_DVI
								else if(bbuf[2] == 2)	UserData.ucInputSource =INPUT_SC_HDMI1;	// NT68856=5_HDMI, APP=2_none
								else if(bbuf[2] == 3)	UserData.ucInputSource =INPUT_SC_DP;	// NT68856=9_DP,   APP=3_none
								
								//UserData.ucInputSource = GetInputPortName((GetInputPortIndex(UserData.ucInputSource)+1)%NUM_INPUT_SC);
            					UserSetInputSource();
								//NvramWriteUserData(&UserData);		//	no need write.  ???				
								break;
							}
											
				//case 0x41:	break;	//Input Support item;	 can't Write

 				case 0x42:	{	//OSD Language
								//ADS-XRS232_Spec.:	0_English, 4_Espanol ,1_Franch, 2_Deutsch, 3_Italiano, 5_Portugues, 6_Pyccknn, 7_China
								// NT68856_Code	  :	0_English, 1_Espanol ,2_Franch, 3_Deutsch, 4_Italiano, 5_Portugues, 6_Pyccknn, 7_China

								if(bbuf[2] >= 9)
									break;

								if(bbuf[2] == 4)		UserData.ucLanguage =1;	//Espanol
								else if(bbuf[2] == 1)	UserData.ucLanguage =2;	//Frach
								else if(bbuf[2] == 2)	UserData.ucLanguage =3;	//Deutsch
								else if(bbuf[2] == 3)	UserData.ucLanguage =4;	//Italiano
								else 
									 UserData.ucLanguage = bbuf[2];				//Other no-change: 0_English, 5_Portugues, 6_Pyccknn, 7_China
								
								NvramWriteUserData(&UserData);	break;
							}

 				case 0x43:	{	//OSD Time Out 
								if(bbuf[2] <= 5)		UserData.ucOSDTimer =5;		//  5sec (min.)
								else if(bbuf[2] >= 60)	UserData.ucOSDTimer =60;	// 60sec (max.)
								else 
									 UserData.ucOSDTimer = bbuf[2];					// between 5 ~ 60 sec
								
								NvramWriteUserData(&UserData);	break;
							}

 				case 0x44:	{	//Aspect Ratio 	
								if(bbuf[2] >= 3)
									break;

								if(ENABLE_ASPECT_RATIO == ON){
									UserData.ucAspectRatio = bbuf[2];	UserSetAspectRatio();	break;
								}else{
									break;	//Aspect Ratio: "Disable"
								}
							}
																																			
				case 0x50:	{							//Auto-Dimming (0x50)
							#if ALS_EnDis == ALSMODE				
								if(bbuf[2] >= 3)
									break;
								if(bbuf[2] == 0x00)	{ UserData.ucALSMode = ALS_OFF;  /* SetOSDUpdUsrFlag(); */	UserSetBrightness(); NvramWriteUserData(&UserData); }
								if(bbuf[2] == 0x01)	{ UserData.ucALSMode = INDOOR;   /* SetOSDUpdUsrFlag(); */	CM3218_ALSOnInit();  NvramWriteUserData(&UserData); }	// set Default: INDOOR mode
//OUTDOOR								  if(bbuf[2] == 0x02)	{ UserData.ucALSMode = OUTDOOR;   /* SetOSDUpdUsrFlag(); */	CM3218_ALSOnInit();  NvramWriteUserData(&UserData); }	// set Default: INDOOR mode
								//if(bbuf[2] == 0xFF)	{   break; }	// don't need do something					
							#elif ALS_EnDis == ALSOffSET	
								if(bbuf[2] >= 2)
									break;
								if(bbuf[2] == 0x00)	{ UserData.bALSOnOff = OFF;  /* SetOSDUpdUsrFlag(); */	UserSetBrightness(); NvramWriteUserData(&UserData); }
								if(bbuf[2] == 0x01)	{ UserData.bALSOnOff = ON;   /* SetOSDUpdUsrFlag(); */	CM3218_ALSOnInit();  NvramWriteUserData(&UserData); }	
								//if(bbuf[2] == 0xFF)	{   break; }	// don't need do something					
							#elif ALS_EnDis == ALSRange
								if(bbuf[2] >= 2)
									break;
								if(bbuf[2] == 0x00)	{ UserData.bALSOnOff = OFF;  /* SetOSDUpdUsrFlag(); */	UserSetBrightness(); NvramWriteUserData(&UserData); }
								if(bbuf[2] == 0x01)	{ UserData.bALSOnOff = ON;   /* SetOSDUpdUsrFlag(); */	LS3101_ALSOnInit();  NvramWriteUserData(&UserData); }	
								//if(bbuf[2] == 0xFF)	{   break; }	// don't need do something					
							#else	//Normal
					
							#endif	//#if ALS_EnDis == ENABLE
							}
								break;

				case 0x51:								//PIR (0x51)
					break;

				case 0x52: 								//Video-Disable(Detect)	(0x52)
					break; 
						 					
				case 0x53: 
							#if ALS_EnDis == ALSOffSET
								if(bbuf[2] > 100)		//Auto-Dimming : when Code-Build -> ALSOffSET 
								break;
								
								UserData.ucALSBaseVal=bbuf[2];	NvramWriteUserData(&UserData);	break;
							#endif

 				case 0x60:	{	//Audio: Volume	(when ucVolume=0xFF is "Disable)
								if(bbuf[2] > 100)
									break;

								UserData.ucVolume = bbuf[2];	NvramWriteUserData(&UserData);	break;
								
							}

 				case 0x61:	{	//Audio: Mute
								if(bbuf[2] >= 2)
									break;

								if(bbuf[2] == 0)		
										UserData.bAudioMute = 0;
									else
										UserData.bAudioMute = 1;
								
								NvramWriteUserData(&UserData);	
								break;
							}

				case 0x70:	{	//OSD-Recall (Write Only)  at: UserRecallConfiguration()
								if(bbuf[2] == 1)
									UserRecallConfiguration();
							 	break;	
							}

				case 0x80:	//AD Board ID (Low-Byte ) 
							{	
								UserData.usADBoardID &= 0xFF00;
								UserData.usADBoardID |= bbuf[2];								
							 	break;	
							}

				case 0x81:	//AD Board ID (Hi-Byte ) 
							{	
								UserData.usADBoardID &= 0x00FF;
								UserData.usADBoardID |= (USHRT)bbuf[2] << 8;
							 	break;	
							}

				case 0xE1:								//Power_Status
				//putchar(0xAA);	putchar(UserData.bPowerStatus);	putchar( 0x100-UserData.bPowerStatus);	
					if(bbuf[2]== 0x01)	//UserData.bPowerStatus == ON)
					{
			            //can't find: APPSetSystemPowerState(APPSTATE_PWR_ON);
			            //can't find: SetGlobalTimer(GLOBAL_TMR_DATA_UPDATE, GBTM_DATA_UPDATE);
			            //can't find: SetAPPUpdUsrFlag(); 
						           
						UserData.bPowerStatus = ON;
            			SYSAPI_SetPowerOn();
            			UserSetInputSource();
            			//APPEnterPowerOnLogo();
					}else if(bbuf[2]== 0x00)	//else if (UserData.bPowerStatus == OFF)
					{
			            //can't find: APPSetSystemPowerState(APPSTATE_PWR_OFF);
			            //can't find: SetGlobalTimer(GLOBAL_TMR_DATA_UPDATE, GBTM_DATA_UPDATE);
			            //can't find: SetAPPUpdUsrFlag(); 					
						//if (IsAPPLogo()) 
						{
			            //    APPEscapePowerOnLogo();
						}
			            UserData.bPowerStatus = OFF;
			            SYSAPI_SetPowerOff();
					}
					break;

			#if ALS_EnDis == ALSRange
				case 0x12:								//Bright_MAX (0x12)
					if(bbuf[2] > 100)		 
						break;
					UserData.ucALSBrigMAX = bbuf[2]; 
				    NvramWriteUserData(&UserData);		//can't find: SetOSDUpdUsrFlag();
					break;

				case 0x13:								//Bright_MIN (0x13)
					if(bbuf[2] > 100)		 
						break;
					UserData.ucALSBrigMIN = bbuf[2]; 
					NvramWriteUserData(&UserData);		//can't find: SetOSDUpdUsrFlag();
					break;
			#else	//Normal: Disable ALS
				case 0x12: break;
				case 0x13: break;
			#endif 

				default:
					//gg ucUARTRxIn=0; ucIsRecivCMDSS=0; return;
					break;
			}// End switch()
		}
	}//End tmp=UART_Getchar(bbuf) == TRUE

}




/*
void DBG_Print(void)
{
//	UCHAR ckDevice=0;	//, tmp=0;
//	static UCHAR i=0;
//	 printf("AlsSens_tmp= %4x, AlsSens_buf= %4x, NowAlsSens= %4x, NowAlsBright=%d, div_ALSBaseVal= %d%\n", AlsSens_tmp, AlsSens_buf, NowAlsSens, (USHRT)NowAlsBright, (USHRT)(div_ALSBaseVal) );	
	
//	ckDevice = NvramCheckDevice(0x90);

//	printf("Ck_Dvi= %d, AlsSens_tmp= %4x, NowAlsSens= %4x, %5u, NowAlsBright=%d \n", (USHRT)ckDevice, AlsSens_tmp, (USHRT)NowAlsSens, NowAlsSens, (USHRT)NowAlsBright );	
//	putchar('2');
}
*/

#endif //#if XRS232