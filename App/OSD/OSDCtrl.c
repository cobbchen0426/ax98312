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
#include "string.h"
//******************************************************************************
// G L O B A L   D E F I N I T I O N S
//******************************************************************************

//******************************************************************************
// G L O B A L   V A R I A B L E S
//******************************************************************************

//******************************************************************************
// S T A T I C   V A R I A B L E S
//******************************************************************************
static code UCHAR ucKey2OSDEventTable[NUM_KEY_EVENTS] = {
    OSD_NONKEY_EVENT,   //KEYEVT_PWR
    OSD_MENUKEY_EVENT,  //KEYEVT_MENU
    OSD_AUTOKEY_EVENT,  //KEYEVT_AUTO
    OSD_INPUT_EVENT,    //OSD_NONKEY_EVENT,		//KEYEVT_INPUT,
    OSD_NONKEY_EVENT,   //KEYEVT_FUNC,
    OSD_UPKEY_EVENT,    //KEYEVT_UP
    OSD_DOWNKEY_EVENT,  //KEYEVT_DOWN
    OSD_NONKEY_EVENT,   //KEYEVT_LEFT
    OSD_NONKEY_EVENT,   //KEYEVT_RIGHT
    OSD_NONKEY_EVENT,   //KEYEVT_FACT
    OSD_NONKEY_EVENT,   //KEYEVT_PWLOCK
    OSD_NONKEY_EVENT,   //KEYEVT_OSDLOCK
    OSD_NONKEY_EVENT,   //KEYEVT_TIMING_SWITCH
    OSD_NONKEY_EVENT,    //KEYEVT_NONE
    OSD_NONKEY_EVENT,   //KEYEVT_DEMO
};

static code UCHAR ucApp2OSDEventTable[NUM_APP_EVENTS] = {
    OSD_OFF_EVENT,      //APPEVT_PW_ON
    OSD_OFF_EVENT,      //APPEVT_PW_OFF
    OSD_OFF_EVENT,      //APPEVT_PW_SAVING
    OSD_NO_SYNC_EVENT,  //APPEVT_NO_SYNC
    OSD_NO_CABLE_EVENT, //APPEVT_NO_CABLE
    OSD_OFF_EVENT,      //APPEVT_UNSTABLE
    OSD_NOP_EVENT,      //APPEVT_PRE
    OSD_NML_EVENT,      //APPEVT_NML
    OSD_OOL_EVENT,      //APPEVT_OOL
    OSD_OOR_EVENT,      //APPEVT_OOR
    OSD_NOP_EVENT       //APPEVT_NON
};

static xdata OSDState usOSDState = OSD_OFF_STATE;
static xdata USHRT usOSDLocalTimer;
static xdata USHRT usOSDTimer;

#if IR_REMOT_CTL == ON
extern BOOL bIR_UpDownKey;
#endif
//******************************************************************************
// S T A T I C   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
static void OSDConfigKeyBehavior(void);

//******************************************************************************
// Prototype:
//  void OSDActionDispatcher(OSDEvent event)
// Parameters:
//  event   : event to OSD action
// Return:
//  None
// Purpose:
//  Perform OSD action by input event id
// Notes:
//  None
//******************************************************************************
void OSDActionDispatcher(UCHAR event)
{
//printf("0_usOSDState= 0x%x, \t event= 0x%x\n", (USHRT)usOSDState, (USHRT)event);		//150526 george
    if ((GetModeHandleState() == SOFT_POWER_OFF) || (GetModeHandleState() == POWER_SAVING_MODE)) 
    {
//printf("1_usOSDState= 0x%x, \t event= 0x%x\n", (USHRT)usOSDState, (USHRT)event);		//150526 george
        return;
    }

	if (GetGlobalEvent(event) == KEY_RELATED_EVENT) 	//150526 george-mark: distinction EVENT_Type(this condition KEY_EVENT-type).
	{	

#if IR_REMOT_CTL == ON
//        if ( usOSDState == OSD_INFO_NOTICE_STATE || usOSDState == OSD_INFO_NONPRESET_STATE ) {
//            return;
//        }
#endif

       	event = GetLocalEvent(event);					//150526 george-mark: get detal KEY_Event value.
//printf("1_event= 0x%x\n", (USHRT)event);		
        event = ucKey2OSDEventTable[event];
//printf("2_usOSDState= 0x%x, \t event= 0x%x\n", (USHRT)usOSDState, (USHRT)event);		//150526 george


#if IR_REMOT_CTL == ON
		//mask ir_key up and down event
		if ( usOSDState==OSD_OFF_STATE && 
			 (event == OSD_UPKEY_EVENT || event == OSD_DOWNKEY_EVENT) &&
			 bIR_UpDownKey) 
		{
			 //gg1
			 //event = OSD_NONKEY_EVENT;
		}

//gg1
//		if( event == OSD_INPUT_EVENT){
//			printf("(4)_OSD_INPUT_EVENT= 0x%x \n", (USHRT) event);
//			//event = OSD_NONKEY_EVENT;
//		}
#endif


        if (event != OSD_NONKEY_EVENT) 
		{		

            	if (OSDKeyRoutine[usOSDState][event] != NULL) 
				{	
//gg1
//printf("3_usOSDState= 0x%x, \t event= 0x%x\n", (USHRT)usOSDState, (USHRT)event);		//150526 george				
//printf("(5) event= 0x%x \n", (USHRT) event);
            		#if ENABLE_INTERNAL_AUDIO_BUZZER == ON
               		 APPSetAudioBuzzer(100);											//150526 george-mark: no compiler here
            		#endif
                			(*OSDKeyRoutine[usOSDState][event])();						//george-statement: exe. *[][] funtion.
                				usOSDLocalTimer = GetTimerTick();
                				OSDConfigKeyBehavior();									//george: Ex:(Set repeat key by OSD status)
				}else
				{
					//gg1
					//printf("(5)_event is NULL, event= 0x%x \n", (USHRT) event);
				}
		}

	}//End_if(GetGlobalEvent())
    
	else if (GetGlobalEvent(event) == APP_RELATED_EVENT) 
	{
        event = GetLocalEvent(event);
        event = ucApp2OSDEventTable[event];

        if (event != OSD_NOP_EVENT) 
		{
//				printf("C00_OSDActionDispatcher -> OSDAppRoutine[event] (to OSDEnterNormal)\n");	//150526 george
				if (OSDAppRoutine[event] != NULL) 
				{
               		 (*OSDAppRoutine[event])();
               		 usOSDLocalTimer = GetTimerTick();
                		 OSDConfigKeyBehavior();
				}
		}
	}

}

//******************************************************************************
// Prototype:
//  UCHAR OSDActionDemander(void)
// Parameters:
//  None
// Return:
//  Return OSD event
// Purpose:
//  Acquire system action by OSD state
// Notes:
//  None
//******************************************************************************
UCHAR OSDActionDemander(void)
{
    UCHAR evt;

    OSDTimerRoutine();

    evt = OSDEVT_NONE;
    
    if (OSDUserUpdate()) 
	{
    	evt = OSDEVT_UPD_USR;
    } 
    else if (OSDTmgUpdate()) 
	{
    	evt = OSDEVT_UPD_TMG;
    }
    else if (OSDSysUpdate()) 
	{
    	evt = OSDEVT_UPD_SYS;
    }
    else if (OSDCalUpdate()) 
	{
    	evt = OSDEVT_UPD_CAL;
    }
    else if (OSDFactoryUpdate()) 
	{
    	evt = OSDEVT_UPD_CAL;
	}
    
	return evt;
}

//******************************************************************************
// Prototype:
//  void OSDTimerRoutine(void)
// Parameters:
//  None
// Return:
//  Return OSD event
// Purpose:
//  
// Notes:
//  None
//******************************************************************************
void OSDTimerRoutine(void)
{     

    //UCHAR buff[32];      

    if ((usOSDState == OSD_OFF_STATE) ||(usOSDState == OSD_FACT_STATE) || (usOSDState == OSD_FITM_STATE)) 
	{
        		usOSDLocalTimer = GetTimerTick();
        		return;
	}
//------------------------------------------------------------//fefanjacky FOR TIMER COUNTER 100 
	if ((usOSDState == OSD_INFO_NOCABLE_STATE))  
	{
	 	  /*
        		if ((GetTimerTick()-usOSDLocalTimer) > 1000) 
				{                   
           				 if (++second == 6) 
						{
               					SYSAPI_PowerSaving();
               					second = 0;
              			 	   if (++minute == 60) 
						 	{
			      					minute = 0;
			      					++hour;
               					}
             					}

              			OSDAPI_SetIndentIndex(100);
              			OSDAPI_SetAlignType(OSD_ALIGN_LEFT);  
              			sprintf(buff + 1,"%d:%02d:%02d",hour,minute,second);    
              			buff[0] = strlen(buff) - 1;      
   	       			OSDAPI_ShowIndentString(FALSE, 10, 5, buff[0], buff);           
            				OSDMovePosition();
            				usOSDLocalTimer = GetTimerTick();
        			}     
        		*/

		if ((GetTimerTick()-usOSDLocalTimer) > 100) 
		{
            			OSDMovePosition();
            			usOSDLocalTimer = GetTimerTick();
		}
		  
    } 
	
    else if (usOSDState == OSD_INFO_NOSYNC_STATE) 
	{

	//------------------------//fefanjacky FOR TIMER COUNTER 100
	/*
        if ((GetTimerTick()-usOSDLocalTimer) > 1000) 
		{        
           		 if (++second == 60) 
				{
               			second = 0;
              	 	if (++minute == 60) 
			   		{
			      			minute = 0;
			      			++hour;
               			}
             			}

            			OSDAPI_SetIndentIndex(100);
            			OSDAPI_SetAlignType(OSD_ALIGN_LEFT);   
            			sprintf(buff + 1,"%d:%02d:%02d",hour,minute,second);    
            			buff[0] = strlen(buff) - 1;    
   	        		OSDAPI_ShowIndentString(FALSE, 10, 6, buff[0], buff);
            			usOSDLocalTimer = GetTimerTick();
        	}
        	*/
	//--------------------------------------------------------------  

        // Remove the following for keeping "NO Sync" OSD in center 
        // Jude 2009/02/16
       // if ((GetTimerTick()-usOSDLocalTimer) > 100) 
       //       {
       // 	    OSDMovePosition();
       // 	    usOSDLocalTimer = GetTimerTick();
       // 	}
    } 
    else if (usOSDState == OSD_INFO_OUTOFRANCE_STATE) 
	{
        	if ((GetTimerTick()-usOSDLocalTimer) > 100) 
			{
            				OSDMovePosition();
            				usOSDLocalTimer = GetTimerTick();
        	}
	}
    else if (usOSDState == OSD_INFO_OUTOFLIMIT_STATE) 
	{
        	if ((GetTimerTick()-usOSDLocalTimer) > 3000) 
			{
            				OSDCloseAll();
        	}
	} 
    else if (usOSDState == OSD_INFO_NOTICE_STATE) 
	{
        	if ((GetTimerTick()-usOSDLocalTimer) > 3000) 
			{
            				OSDCloseAll();
        	}
	}
    else if (usOSDState == OSD_OPT1_STATE) 
	{
        	if ((GetTimerTick()-usOSDLocalTimer) > usOSDTimer) 
			{
            				OSDExitOpt1();
        	}
 	}
    else if (usOSDState == OSD_OPT2_STATE) 
	{
        	if ((GetTimerTick()-usOSDLocalTimer) > usOSDTimer) 
			{
            				OSDExitOpt2();
        	}
	}
    else 
	{
       	 if ((GetTimerTick()-usOSDLocalTimer) > usOSDTimer) 
			{
            			OSDCloseAll();
            			OSDConfigKeyBehavior(); // Reset key behavior after OSD time out.
			}
	}
}

//******************************************************************************
// Prototype: 
//  void OSDConfigTimeout(USHRT timer)
// Parameters:
//  timer   : OSD time out counter
// Return:
//  None
// Purpose:
//  Set OSD time out counter
// Notes:
//  None
//******************************************************************************
void OSDConfigTimeout(USHRT timer)
{
    usOSDTimer = timer;
}

//******************************************************************************
// Prototype: 
//  void OSDCloseAll(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Close all OSE
// Notes:
//  None
//******************************************************************************
void OSDCloseAll(void)
{	
      OSD_color_level= OSD_state= usOSDState = OSD_OFF_STATE;		//140304 mike factory mode
    OSDClosed();
}

//******************************************************************************
// Prototype: 
//  void OSDUpdateAutoTune(UCHAR pnt)
// Parameters:
//  pnt : percentage of AutoTune
// Return:
//  None
// Purpose:
//  Update AutoTune Progress
// Notes:
//  None
//******************************************************************************
void OSDUpdateAutoTune(UCHAR pnt)
{
    OSDUpdateAutoTuneBar(pnt);
}

//******************************************************************************
// Prototype:
//  static void OSDConfigKeyBehavior(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Set repeat key by OSD status
// Notes:
//  None
//*****************************************************************************
static void OSDConfigKeyBehavior(void)
{
    if ((usOSDState == OSD_OFF_STATE) ||(usOSDState == OSD_INFO_OUTOFLIMIT_STATE) ||
        (usOSDState == OSD_INFO_OUTOFRANCE_STATE) ||(usOSDState == OSD_INFO_NOSYNC_STATE) ||
        (usOSDState == OSD_INFO_NOCABLE_STATE) ||(usOSDState == OSD_INFO_NOTICE_STATE) ||
        (usOSDState == OSD_INFO_SOURCE_STATE)) 
	{
        	KeySetRepeatEvent(0xFF, OFF);
        	KeySetMFuncEvent(KEYEVT_AUTO, KEYEVT_INPUT);
    }
    else 
	{
        	KeySetRepeatEvent(KEYEVT_UP, ON);
        	KeySetRepeatEvent(KEYEVT_DOWN, ON);
        	KeySetMFuncEvent(0xFF, 0x00);
    }
}

//******************************************************************************
// The following are OSD actions
//******************************************************************************
#define NextState(a,b,c) (((USHRT)c-a+1)%(b-a)+a)
#define PrevState(a,b,c) (((USHRT)c+b-2*a-1)%(b-a)+a)
#define CursorPos(a,b)   (b-a)

#define MP1CursorPos()   (CursorPos(OSD_MAIN_BEG,OSD_MAIN_1_STATE))
#define MP2CursorPos()   (CursorPos(OSD_MAIN_BEG,OSD_MAIN_2_STATE))
#define MP3CursorPos()   (CursorPos(OSD_MAIN_BEG,OSD_MAIN_3_STATE))
#define MP4CursorPos()   (CursorPos(OSD_MAIN_BEG,OSD_MAIN_4_STATE))
#define MP5CursorPos()   (CursorPos(OSD_MAIN_BEG,OSD_MAIN_5_STATE))

//******************************************************************************
// Main menu operation
//******************************************************************************

void OSDEnterDirInput(void)		//gg1
{
	OSDExitMainMenu();

	OSDEnterMainMenu();
	OSDMainMenuDown();
	OSDEnterSubMenu5();
	OSDSubMenuUp5();
	OSDEnterItm54();
}

void OSDEnterMainMenu(void)  //jacky for factory 
{
    if (SystemData.bFactory == FALSE) 
	{ 
    		//printf("OSDEnterMainMenu\n\r");
    		OSD_state=usOSDState = OSD_MAIN_1_STATE;	//140304 mike factory mode
    		OSDShowMainMenu();
  	} 
	else 
  	{
    		OSD_state=usOSDState = OSD_FACT_STATE;	//140304 mike factory mode
    		OSDShowFactory();
  	}
}

void OSDExitMainMenu(void)
{
    //printf("OSDExitMainMenu\n\r");
    OSD_color_level= OSD_state=usOSDState = OSD_OFF_STATE; 		//140304 mike factory mode
    OSDCloseMainMenu();
}

void OSDMainMenuUp(void)
{
    //printf("OSDMainMenuUp\n\r");
    OSDUnselectMainItem(CursorPos(OSD_MAIN_BEG,usOSDState));
    while (1) 
	{
       	 OSD_state=usOSDState = NextState(OSD_MAIN_BEG,OSD_MAIN_END,usOSDState);  //MBEG=1 , MEND=8 ,if usOSDState =3
		if (OSDIsMainItemValid(CursorPos(OSD_MAIN_BEG,usOSDState)) == TRUE)
		{
           	   		break;
		}		   
	}
	OSDSelectMainItem(CursorPos(OSD_MAIN_BEG,usOSDState));
}

void OSDMainMenuDown(void)
{
    //printf("OSDMainMenuDown\n\r");
    OSDUnselectMainItem(CursorPos(OSD_MAIN_BEG,usOSDState));
    while (1) 
	{
        	OSD_state=usOSDState = PrevState(OSD_MAIN_BEG,OSD_MAIN_END,usOSDState);
        if (OSDIsMainItemValid(CursorPos(OSD_MAIN_BEG,usOSDState)) == TRUE)
            break;
    }
    OSDSelectMainItem(CursorPos(OSD_MAIN_BEG,usOSDState));
}
//******************************************************************************
// Submenu 1 Operation
//******************************************************************************
void OSDEnterSubMenu1(void)
{
    //printf("\t OSDEnterSubMenu1\n\r");
    OSD_state=usOSDState = OSD_MAIN_1_1_STATE;
    OSDFocusSub(CursorPos(OSD_MAIN_END,usOSDState));
}

void OSDExitSubMenu1(void)
{
    //printf("\t OSDExitSubMenu1\n\r");
    OSD_state=usOSDState = OSD_MAIN_1_STATE;
    OSDFocusMain(CursorPos(OSD_MAIN_BEG,usOSDState));
}

void OSDSubMenuUp1(void)
{
    //printf("\t OSDSubMenuUp1\n\r");
    OSDUnselectSubItem(CursorPos(OSD_MAIN_END,usOSDState));
    while (1) 
	{
         OSD_state= usOSDState = NextState(OSD_MAIN_END,OSD_MAIN_1_END,usOSDState);
        if (OSDIsSubItemValid(CursorPos(OSD_MAIN_END,usOSDState)) == TRUE)
            break;
	}
    OSDSelectSubItem(CursorPos(OSD_MAIN_END,usOSDState));
}

void OSDSubMenuDown1(void)
{
    //printf("\t OSDSubMenuDown1\n\r");
    OSDUnselectSubItem(CursorPos(OSD_MAIN_END,usOSDState));
    while (1) 
	{
           OSD_state=usOSDState = PrevState(OSD_MAIN_END,OSD_MAIN_1_END,usOSDState);
        if (OSDIsSubItemValid(CursorPos(OSD_MAIN_END,usOSDState)) == TRUE)
            break;
	}
    OSDSelectSubItem(CursorPos(OSD_MAIN_END,usOSDState));
}

//******************************************************************************
// Submenu 2 Operation
//******************************************************************************
void OSDEnterSubMenu2(void)
{
    //printf("\t OSDEnterSubMenu2\n\r");
    OSD_state=usOSDState = OSD_MAIN_2_1_STATE;
    OSDFocusSub(CursorPos(OSD_MAIN_1_END,usOSDState));
}

void OSDExitSubMenu2(void)
{
    //printf("\t OSDExitSubMenu2\n\r");
	OSD_state= usOSDState = OSD_MAIN_2_STATE;
    OSDFocusMain(CursorPos(OSD_MAIN_BEG,usOSDState));
}

void OSDSubMenuUp2(void)
{
	//printf("\t OSDSubMenuUp2\n\r");
    OSDUnselectSubItem(CursorPos(OSD_MAIN_1_END,usOSDState));
    while (1) {
        OSD_state=usOSDState = NextState(OSD_MAIN_1_END,OSD_MAIN_2_END,usOSDState);
        if (OSDIsSubItemValid(CursorPos(OSD_MAIN_1_END,usOSDState)) == TRUE)
            break;
    }
    OSDSelectSubItem(CursorPos(OSD_MAIN_1_END,usOSDState));
}

void OSDSubMenuDown2(void)
{
 	//printf("\t OSDSubMenuDown2\n\r");
    OSDUnselectSubItem(CursorPos(OSD_MAIN_1_END,usOSDState));
    while (1) {
        OSD_state=usOSDState = PrevState(OSD_MAIN_1_END,OSD_MAIN_2_END,usOSDState);
        if (OSDIsSubItemValid(CursorPos(OSD_MAIN_1_END,usOSDState)) == TRUE)
            break;
    }
    OSDSelectSubItem(CursorPos(OSD_MAIN_1_END,usOSDState));
}

//******************************************************************************
// Submenu 3 Operation entry to color sub menu 
//******************************************************************************
void OSDEnterSubMenu3(void)
{
 #ifdef colortemp 			               			//140509 mike           
      //printf("OSDEnterSubMenu3\n\r");
 #endif
 	//printf("OSDEnterSubMenu3\n\r");
	OSD_color_level=1;  
   	OSD_state=usOSDState = OSD_MAIN_3_1_STATE;
	OSDFocusSub(CursorPos(OSD_MAIN_2_END,usOSDState));
	OSDFocusItm31();				//140425 mike  #define OSDFocusItm31 OSDFocusClrTmp
}

void OSDExitSubMenu3(void)
{
  #ifdef colortemp 			               			//140509 mike           
        //printf("\OSDExitSubMenu3\n\r");
  #endif
	//printf("\OSDExitSubMenu3\n\r");
	OSD_color_level=0;												//140507 mike   
	OSD_state=usOSDState = OSD_MAIN_3_STATE;	
	OSDClearSubmenu();
	OSDShowSubMenu(02);				//140422 mike 
}
//=====================140508 mike 
void OSDSubMenuUp3(void)
{
 #ifdef colortemp 			               			//140509 mike           
    	//printf("OSDSubMenuUp3\n\r");
 #endif
    OSDColorTempUp();
  
}

void OSDSubMenuDown3(void)
{
 #ifdef colortemp 			               			//140509 mike           
    	//printf("OSDSubMenuDown3\n\r");
 #endif
    OSDColorTempDown();
}
//---------------------------140508 mike 

//================================140509 mike
void OSDColorUserRGBUp(void)
{
 #ifdef colortemp 			               			//140509 mike           
       //printf("140509 OSDColorUserRGBUp\n\r");		//140509 mike		
 #endif      

	if(UserData.ucColorTemp==3)									//140508 mike  
	{
    	OSD_color_level=2;									//140507 mike 
    	OSD_color_RGB++;

		if (( OSD_color_RGB > MAXIMUM_CLR_TEMP) ||( OSD_color_RGB < 0))
    	{
			   OSD_color_RGB  = 1;
    	}		
    		OSDExitItms(MP3CursorPos(), CursorPos(0,OSD_color_RGB));
	}
}
//-----------------------------140509 mike 
void OSDColorUserRGBDown(void)
{
 #ifdef colortemp 			               			//140509 mike           
       //printf("140509 OSDColorUserRGBDown\n\r");	//140509 mike	
 #endif      

	if(UserData.ucColorTemp==3)									//140508 mike  
	{
		OSD_color_level=2;									//140507 mike 
    	OSD_color_RGB--;

	 	if (( OSD_color_RGB > MAXIMUM_CLR_TEMP) ||( OSD_color_RGB < 1))
    	{
			   OSD_color_RGB  = 3;
    	}		
    		OSDExitItms(MP3CursorPos(), CursorPos(0,OSD_color_RGB));
	}       
}
//================================140509 mike 
/*
void OSDSubMenuUp3(void)
{
    		printf("OSDSubMenuUp3\n\r");
    OSDUnselectSubItem(CursorPos(OSD_MAIN_2_END,usOSDState));
    while (1) 
		{
       	    OSD_state=usOSDState = NextState(OSD_MAIN_2_END,OSD_MAIN_3_END,usOSDState);
//		    printf("140421 OSDSubMenuUp3===>while (1)=======>OSD_state=%x ;\n\r",(unsigned short)OSD_state);		//140421 mike					
       	 if (OSDIsSubItemValid(CursorPos(OSD_MAIN_2_END,usOSDState)) == TRUE)
            			break;
    		}
    	OSDSelectSubItem(CursorPos(OSD_MAIN_2_END,usOSDState));
}

void OSDSubMenuDown3(void)
{
    printf("OSDSubMenuDown3\n\r");
    OSDUnselectSubItem(CursorPos(OSD_MAIN_2_END,usOSDState));
    while (1) 
		{
        		OSD_state=usOSDState = PrevState(OSD_MAIN_2_END,OSD_MAIN_3_END,usOSDState);
//		    	printf("140421 OSDSubMenuDown3===>while (1)=======>OSD_state=%x ;\n\r",(unsigned short)OSD_state);		//140421 mike					
        	 if (OSDIsSubItemValid(CursorPos(OSD_MAIN_2_END,usOSDState)) == TRUE)
            		break;
    		}
    OSDSelectSubItem(CursorPos(OSD_MAIN_2_END,usOSDState));
}
*/
//====================140508 mike 
//******************************************************************************
// Submenu 4 Operation
//******************************************************************************
void OSDEnterSubMenu4(void)
{
    OSD_state=usOSDState = OSD_MAIN_4_1_STATE;
    OSDFocusSub(CursorPos(OSD_MAIN_3_END,usOSDState));
}

void OSDExitSubMenu4(void)
{
    OSD_state=usOSDState = OSD_MAIN_4_STATE;
    OSDFocusMain(CursorPos(OSD_MAIN_BEG,usOSDState));
}

void OSDSubMenuUp4(void)
{
    OSDUnselectSubItem(CursorPos(OSD_MAIN_3_END,usOSDState));
    while (1) {
        OSD_state=usOSDState = NextState(OSD_MAIN_3_END,OSD_MAIN_4_END,usOSDState);
        if (OSDIsSubItemValid(CursorPos(OSD_MAIN_3_END,usOSDState)) == TRUE)
            break;
    }
    OSDSelectSubItem(CursorPos(OSD_MAIN_3_END,usOSDState));
}

void OSDSubMenuDown4(void)
{
    OSDUnselectSubItem(CursorPos(OSD_MAIN_3_END,usOSDState));
    while (1) {
        OSD_state=usOSDState = PrevState(OSD_MAIN_3_END,OSD_MAIN_4_END,usOSDState);
        if (OSDIsSubItemValid(CursorPos(OSD_MAIN_3_END,usOSDState)) == TRUE)
            break;
    }
    OSDSelectSubItem(CursorPos(OSD_MAIN_3_END,usOSDState));
}

//******************************************************************************
// Submenu 5 Operation
//******************************************************************************
void OSDEnterSubMenu5(void)
{	
    OSD_state=usOSDState = OSD_MAIN_5_1_STATE;
    OSDFocusSub(CursorPos(OSD_MAIN_4_END,usOSDState));
}

void OSDExitSubMenu5(void)
{	
    OSD_state=usOSDState = OSD_MAIN_5_STATE;
    OSDFocusMain(CursorPos(OSD_MAIN_BEG,usOSDState));
}

void OSDSubMenuUp5(void)
{	
    OSDUnselectSubItem(CursorPos(OSD_MAIN_4_END,usOSDState));
    while (1) 
		{
               OSD_state=usOSDState = NextState(OSD_MAIN_4_END,OSD_MAIN_5_END,usOSDState);
            if (OSDIsSubItemValid(CursorPos(OSD_MAIN_4_END,usOSDState)) == TRUE)
                 break;
        }
    OSDSelectSubItem(CursorPos(OSD_MAIN_4_END,usOSDState));
}

void OSDSubMenuDown5(void)
{	
    OSDUnselectSubItem(CursorPos(OSD_MAIN_4_END,usOSDState));
    while (1)
	{
            OSD_state=usOSDState = PrevState(OSD_MAIN_4_END,OSD_MAIN_5_END,usOSDState);
        if (OSDIsSubItemValid(CursorPos(OSD_MAIN_4_END,usOSDState)) == TRUE)
            break;
       }
         OSDSelectSubItem(CursorPos(OSD_MAIN_4_END,usOSDState));
}

//******************************************************************************
// Operations of sub-items in submenu 1
//******************************************************************************
void OSDEnterItm11(void)
{
//printf("OSDEnterItem11\n");
    OSD_state=usOSDState = OSD_ITEM_1_1_STATE;
    OSDFocusItm11();
}

void OSDExitItm11(void)
{
    OSDConfirmItm11();
    OSD_state=usOSDState = OSD_MAIN_1_1_STATE;
    OSDExitItms(MP1CursorPos(), CursorPos(OSD_MAIN_END,usOSDState));
}

void OSDEnterItm12(void)
{
    OSD_state=usOSDState = OSD_ITEM_1_2_STATE;
    OSDFocusItm12();
}

void OSDExitItm12(void)
{
//printf("_OSDExitItm12_\n");
    OSDConfirmItm12();
    OSD_state= usOSDState = OSD_MAIN_1_2_STATE;
    OSDExitItms(MP1CursorPos(), CursorPos(OSD_MAIN_END,usOSDState));
}

void OSDEnterItm13(void)
{
//printf("_OSDEnterItm13_: Sharp\n");
    OSD_state=usOSDState = OSD_ITEM_1_3_STATE;
    OSDFocusItm13();
}

void OSDExitItm13(void)
{
//printf("_OSDExitItm13_: Sharp\n");
	usOSDState = OSD_MAIN_1_3_STATE;
    OSDConfirmItm13();

    OSDExitItms(MP1CursorPos(), CursorPos(OSD_MAIN_END,usOSDState));
}



#if ALS_EnDis == ALSMODE
	void OSDEnterItm14(void)				// george: F_ALSOnOff_04A
	{
	    OSD_state=usOSDState = OSD_ITEM_1_4_STATE;	
	    OSDFocusItm14();
	}
	
	void OSDExitItm14(void)					//george: F_ALSOnOff_04B
	{
		usOSDState = OSD_MAIN_1_4_STATE;			
	    OSDConfirmItm14();
	    OSDExitItms(MP1CursorPos(), CursorPos(OSD_MAIN_END,usOSDState));
	}
#elif ALS_EnDis == ALSOffSET	
	void OSDEnterItm14(void)				// george: F_ALSOnOff_04A
	{
	    OSD_state=usOSDState = OSD_ITEM_1_4_STATE;	
	    OSDFocusItm14();
	}
	
	void OSDExitItm14(void)					//george: F_ALSOnOff_04B
	{
		usOSDState = OSD_MAIN_1_4_STATE;			
	    OSDConfirmItm14();
	    OSDExitItms(MP1CursorPos(), CursorPos(OSD_MAIN_END,usOSDState));
	}
#elif ALS_EnDis == ALSRange
	void OSDEnterItm14(void)				// george: F_ALSOnOff_04A
	{
	    OSD_state=usOSDState = OSD_ITEM_1_4_STATE;	
	    OSDFocusItm14();
	}
	
	void OSDExitItm14(void)					//george: F_ALSOnOff_04B
	{
		usOSDState = OSD_MAIN_1_4_STATE;			
	    OSDConfirmItm14();
	    OSDExitItms(MP1CursorPos(), CursorPos(OSD_MAIN_END,usOSDState));
	}
#else	//Normal

#endif	//#if ALS_EnDis == ENABLE



/* void OSDEnterItm15(void)				//george: F_ALSBV_04A
{
	OSD_state=usOSDState = OSD_ITEM_1_5_STATE;	 
    OSDFocusItm15();
}

void OSDExitItm15(void)					//george: F_ALSBV_04B
{
	OSDConfirmItm15();
    OSD_state=usOSDState = OSD_MAIN_1_5_STATE;	
    OSDExitItms(MP1CursorPos(), CursorPos(OSD_MAIN_END,usOSDState));
} */


//----------------------------------------- george_Item16 ,  george_Item17
//gg_old
/*
void OSDEnterItm16(void)				//george: F_Touch_04A
{
// old    OSD_state=usOSDState = OSD_ITEM_1_6_STATE;
// old   OSDFocusItm16(); 
    OSD_state=usOSDState = OSD_ITEM_1_6_STATE;	//george: F_Touch_04A1 -> OSD_ITEM_1_5_STATE
    OSDFocusItm16();
}

void OSDExitItm16(void)					//george: F_Touch_04B
{
//old    OSDConfirmItm16();
//old    OSD_state=usOSDState = OSD_MAIN_1_6_STATE;
//old    OSDExitItms(MP1CursorPos(), CursorPos(OSD_MAIN_END,usOSDState));

    OSDConfirmItm16();
    OSD_state=usOSDState = OSD_MAIN_1_6_STATE;	//george: F_Touch_04B1 -> OSD_MAIN_1_6_STATE
    OSDExitItms(MP1CursorPos(), CursorPos(OSD_MAIN_END,usOSDState));
}  */


/*
void OSDEnterItm17(void)
{
    OSD_state=usOSDState = OSD_ITEM_1_7_STATE;
    OSDFocusItm17();
}

void OSDExitItm17(void)
{
    OSDConfirmItm17();
    OSD_state=usOSDState = OSD_MAIN_1_7_STATE;
    OSDExitItms(MP1CursorPos(), CursorPos(OSD_MAIN_END,usOSDState));
}
*/


//******************************************************************************
// Operations of sub-items in submenu 2
//******************************************************************************
void OSDEnterItm21(void)
{
    OSD_state=usOSDState = OSD_ITEM_2_1_STATE;
    OSDFocusItm21();
}

void OSDExitItm21(void)
{
    OSDConfirmItm21();
    OSD_state=usOSDState = OSD_MAIN_2_1_STATE;
    OSDExitItms(MP2CursorPos(), CursorPos(OSD_MAIN_1_END,usOSDState));
}

void OSDEnterItm22(void)
{
    OSD_state=usOSDState = OSD_ITEM_2_2_STATE;
    OSDFocusItm22();
}

void OSDExitItm22(void)
{
    OSDConfirmItm22();
    OSD_state=usOSDState = OSD_MAIN_2_2_STATE;
    OSDExitItms(MP2CursorPos(), CursorPos(OSD_MAIN_1_END,usOSDState));
}

void OSDEnterItm23(void)
{
    OSD_state=usOSDState = OSD_ITEM_2_3_STATE;
    OSDFocusItm23();
}

void OSDExitItm23(void)
{
    OSDConfirmItm23();
   OSD_state= usOSDState = OSD_MAIN_2_3_STATE;
    OSDExitItms(MP2CursorPos(), CursorPos(OSD_MAIN_1_END,usOSDState));
}

void OSDEnterItm24(void)
{
    OSD_state=usOSDState = OSD_ITEM_2_4_STATE;
    OSDFocusItm24();
}

void OSDExitItm24(void)
{
    OSDConfirmItm24();
    OSD_state=usOSDState = OSD_MAIN_2_4_STATE;
    OSDExitItms(MP2CursorPos(), CursorPos(OSD_MAIN_1_END,usOSDState));
}

//******************************************************************************
// Operations of sub-items in submenu 3
//******************************************************************************
void OSDEnterItm31(void)
{
/*   //140507 mike 
  if( OSD_color_level==1)  
  {
    OSD_color_level++;
    printf("140429 OSDEnterItm31=%x ;\n\r",(unsigned short)OSD_state);		//140421 mike					
    OSD_state=usOSDState = OSD_ITEM_3_1_STATE;
    OSDFocusItm31();				//140425 mike  #define OSDFocusItm31 OSDFocusClrTmp
    printf("140421 OSDEnterItm31=%x , color = %x;\n\r",(unsigned short)OSD_state,(unsigned short)OSD_color_level);		//140421 mike
  	}
*/
//============================140507 mike 	OSD_color_level=1;  
    OSDConfirmItm31();
	
	if(UserData.ucColorTemp==3)									//140508 mike  
	{
    	OSD_color_level=2;									//140507 mike 
    	OSD_state=usOSDState = OSD_ITEM_3_1_STATE;
    	OSDExitItms(MP3CursorPos(), CursorPos(OSD_ITEM_3_1_STATE,usOSDState)+1);
		OSD_color_RGB=1;
	}
	else
	{
	
	}
 #ifdef colortemp 			               			//140509 mike           
	printf("140429 OSDEnterItm 31 RGB=%x  color = %x;\n\r",(unsigned short)OSD_state,(unsigned short)OSD_color_level);		//140421 mike					
#endif
//============================
}
//=================140508 
void OSDExitItm31(void)
{ 

	if(OSD_color_level==2)									//140508 mike 
		OSD_color_level--;                             		//140508 mike 
    OSDConfirmItm31();
    OSD_state=usOSDState = UserData.ucColorTemp;
    OSDExitItms(MP3CursorPos(), CursorPos(OSD_MAIN_2_END,usOSDState));
 #ifdef colortemp 			               			//140509 mike           	
    printf("140429 OSDExitItm31=%x ;\n\r",(unsigned short)OSD_state);		//140421 mike	
 #endif   
}
//----------------------140508
/*
void OSDExitItm31(void)
{  
  if(OSD_color_level==2)									//140508 mike 
     OSD_color_level--;                                                		//140508 mike 
    OSDConfirmItm31();
    OSD_state=usOSDState = OSD_MAIN_3_1_STATE;
    OSDExitItms(MP3CursorPos(), CursorPos(OSD_MAIN_2_END,usOSDState));
    printf("140429 OSDExitItm31=%x ;\n\r",(unsigned short)OSD_state);		//140421 mike					
}
*/
//=================140508
void OSDEnterItm32(void)
{
	if( OSD_color_level==2)  
	{
  	//  OSD_color_level++;
		OSD_state=usOSDState = OSD_ITEM_3_2_STATE;
    	OSDFocusItm32();
	 #ifdef colortemp 			               			//140509 mike           
	 	printf("140429 OSDEnterItm32=%x ;\n\r",(unsigned short)OSD_state);		//140421 mike		
	 #endif
	}
}

void OSDExitItm32(void)
{
	if(UserData.ucColorTemp==3)									//140508 mike  
	{
    	OSD_color_level=2;									//140507 mike 
    	OSD_state=usOSDState = OSD_ITEM_3_1_STATE;
		OSDExitItms(MP3CursorPos(), CursorPos(0,OSD_color_RGB));
	}
 #ifdef colortemp 			               			//140509 mike           
    printf("140421 OSDExitItm32=%x ;\n\r",(unsigned short)OSD_state);		//140421 mike	
 #endif   
}

void OSDEnterItm33(void)
{
  if( OSD_color_level==2)  
  {
    OSD_state=usOSDState = OSD_ITEM_3_3_STATE;
    OSDFocusItm33();
 #ifdef colortemp 			               			//140509 mike           
    printf("140421 OSDEnterItm33=%x , color = %x;\n\r",(unsigned short)OSD_state,(unsigned short)OSD_color_level);		//140421 mike					
#endif
  }
}
//-------------------------OSDEnterItm331  140430 mike for color 
void OSDEnterItm331(void)
{  
    OSDConfirmItm31();

	if (OSD_color_RGB ==1)
   	{
       	OSD_state=usOSDState =     OSD_ITEM_3_2_STATE;
		OSDFocusRGain();						//140509 mike 
   	}
   	else if(OSD_color_RGB ==2)
   	{
   		OSD_state=usOSDState =     OSD_ITEM_3_3_STATE;
		OSDFocusGGain();						//140509 mike 
   	}
   	else if(OSD_color_RGB ==3)
   	{
   		OSD_state=usOSDState =     OSD_ITEM_3_4_STATE;
		OSDFocusBBain();						//140509 mike 
   	}
 #ifdef colortemp 			               			//140509 mike           
    printf("140429 OSDEnterItm331=%x  color = %x;\n\r",(unsigned short)OSD_state,(unsigned short)OSD_color_level);		//140421 mike					
#endif
}
void OSDEnterItm332(void)
{
  /*  //140509 mike 
    OSDConfirmItm32();
    OSD_state=usOSDState = OSD_MAIN_3_2_STATE;
    OSDExitItms(MP3CursorPos(), CursorPos(OSD_MAIN_2_END,usOSDState));
   */
 #ifdef colortemp 			               			//140509 mike           
   printf("140429 OSDEnterItm332=%x ;\n\r",(unsigned short)OSD_state);		//140421 mike					
#endif
}
void OSDEnterItm333(void)
{
/*   //140509 mike 
    OSDConfirmItm31();
    OSD_state=usOSDState = OSD_MAIN_3_1_STATE;
    OSDExitItms(MP3CursorPos(), CursorPos(OSD_MAIN_2_END,usOSDState));
*/
 #ifdef colortemp 			               			//140509 mike           
	printf("140429 OSDEnterItm333=%x ;\n\r",(unsigned short)OSD_state);		//140421 mike					
#endif
}
void OSDEnterItm334(void)
{
/*   //140509 mike 
    OSDConfirmItm34();
    OSD_state=usOSDState = OSD_MAIN_3_4_STATE;
    OSDExitItms(MP3CursorPos(), CursorPos(OSD_MAIN_2_END,usOSDState));
*/
 #ifdef colortemp 			               			//140509 mike           
    printf("140429 OSDEnterItm334=%x ;\n\r",(unsigned short)OSD_state);		//140421 mike					
#endif
}

//-------------------------

void OSDExitItm33(void)
{
/*
     OSD_color_level--;
    OSDConfirmItm33();
    OSD_state=usOSDState = OSD_MAIN_3_3_STATE;
    OSDExitItms(MP3CursorPos(), CursorPos(OSD_MAIN_2_END,usOSDState));
*/
if(UserData.ucColorTemp==3)									//140508 mike  
	{
    		OSD_color_level=2;									//140507 mike 
    		OSD_state=usOSDState = OSD_ITEM_3_1_STATE;
		OSDExitItms(MP3CursorPos(), CursorPos(0,OSD_color_RGB));
	}
 #ifdef colortemp 			               			//140509 mike           
    printf("140421 OSDExitItm33=%x ;\n\r",(unsigned short)OSD_state);		//140421 mike	
 #endif   
}

void OSDEnterItm34(void)
{
    OSD_state=usOSDState = OSD_ITEM_3_4_STATE;
    OSDFocusItm34();
 #ifdef colortemp 			               			//140509 mike           
    printf("140421 OSDEnterItm34=%x ;\n\r",(unsigned short)OSD_state);		//140421 mike						
#endif	
}

void OSDExitItm34(void)
{
/*
     OSD_color_level--;
    OSDConfirmItm34();
    OSD_state=usOSDState = OSD_MAIN_3_4_STATE;
    OSDExitItms(MP3CursorPos(), CursorPos(OSD_MAIN_2_END,usOSDState));
*/
	if(UserData.ucColorTemp==3)									//140508 mike  
	{
    		OSD_color_level=2;									//140507 mike 
    		OSD_state=usOSDState = OSD_ITEM_3_1_STATE;
  
		OSDExitItms(MP3CursorPos(), CursorPos(0,OSD_color_RGB));
	}
 #ifdef colortemp 			               			//140509 mike           
    printf("140421 OSDExitItm34=%x ;\n\r",(unsigned short)OSD_state);		//140421 mike	
 #endif   
	
}

//******************************************************************************
// Operations of sub-items in submenu 4
//******************************************************************************
void OSDEnterItm41(void)
{
    OSD_state=usOSDState = OSD_ITEM_4_1_STATE;
    OSDFocusItm41();
}

void OSDExitItm41(void)
{
    OSDConfirmItm41();
   OSD_state= usOSDState = OSD_MAIN_4_1_STATE;
    OSDExitItms(MP4CursorPos(), CursorPos(OSD_MAIN_3_END,usOSDState));
}

void OSDEnterItm42(void)
{
    OSD_state=usOSDState = OSD_ITEM_4_2_STATE;
    OSDFocusItm42();
}

void OSDExitItm42(void)
{
    OSDConfirmItm42();
    OSD_state=usOSDState = OSD_MAIN_4_2_STATE;
    OSDExitItms(MP4CursorPos(), CursorPos(OSD_MAIN_3_END,usOSDState));
}

void OSDEnterItm43(void)
{
    OSD_state=usOSDState = OSD_ITEM_4_3_STATE;
    OSDFocusItm43();
}

void OSDExitItm43(void)
{
    OSDConfirmItm43();
    OSD_state=usOSDState = OSD_MAIN_4_3_STATE;
    OSDExitItms(MP4CursorPos(), CursorPos(OSD_MAIN_3_END,usOSDState));
}

void OSDEnterItm44(void)
{
    OSD_state=usOSDState = OSD_ITEM_4_4_STATE;
    OSDFocusItm44();
}

void OSDExitItm44(void)
{
    OSDConfirmItm44();
    OSD_state=usOSDState = OSD_MAIN_4_4_STATE;
    OSDExitItms(MP4CursorPos(), CursorPos(OSD_MAIN_3_END,usOSDState));
}

//void OSDEnterItm45(void)
//{
//    OSD_state=usOSDState = OSD_ITEM_4_5_STATE;
//    OSDFocusItm45();
//}
//
//void OSDExitItm45(void)
//{
//    OSDConfirmItm45();		// (at OSDView.h) #define OSDConfirmItm45   OSDConfirmOSDRotation
//    OSDExitItms(MP4CursorPos(), CursorPos(OSD_MAIN_3_END,usOSDState));
//}

//******************************************************************************
// Operations of sub-items in submenu 5
//******************************************************************************
void OSDEnterItm51(void)								//140325 mike language
{
    OSD_state=usOSDState = OSD_ITEM_5_1_STATE;
    OSDFocusItm51();
}

void OSDExitItm51(void)								//140325 mike language
{
    OSDConfirmItm51();
    OSD_state=usOSDState = OSD_MAIN_5_1_STATE;
    OSDExitItms(MP5CursorPos(), CursorPos(OSD_MAIN_4_END,usOSDState));
}



#if AUDIO_EnDis == ENABLE
	void OSDEnterItm52(void)								//140325 mike volume 							
	{
	    OSD_state=usOSDState = OSD_ITEM_5_2_STATE;
	    OSDFocusItm52();
	}
	
	void OSDExitItm52(void)								//140325 mke volume 
	{
	    OSDConfirmItm52();
	    OSD_state=usOSDState = OSD_MAIN_5_2_STATE;									
	    OSDExitItms(MP5CursorPos(), CursorPos(OSD_MAIN_4_END,usOSDState));
	}
	
	void OSDEnterItm53(void)											//140317 mike for mute									
	{
	    OSD_state=usOSDState = OSD_ITEM_5_3_STATE;
	    OSDFocusItm53();
	}
	
	void OSDExitItm53(void)
	{
	    OSDConfirmItm53();
	    OSD_state=usOSDState = OSD_MAIN_5_3_STATE;
	    OSDExitItms(MP5CursorPos(), CursorPos(OSD_MAIN_4_END,usOSDState));
	}
#else	//audio_osd-item_disable

#endif	//#if AUDIO_EnDis == ENABLE



void OSDEnterItm54(void)										//140318 mike input 
{
	reserve_osd_inputsource = UserData.ucInputSource; //george
    OSD_state=usOSDState = OSD_ITEM_5_4_STATE;
    OSDFocusItm54();
}

void OSDExitItm54(void)										//140318 mike input 
{	UserData.ucInputSource = reserve_osd_inputsource;  //george
    //george OSDConfirmItm54();
    OSD_state=usOSDState = OSD_MAIN_5_4_STATE;									
    OSDExitItms(MP5CursorPos(), CursorPos(OSD_MAIN_4_END,usOSDState));
}



//void OSDEnterItm55(void)
//{
//   OSD_state=usOSDState = OSD_ITEM_5_5_STATE;
//    OSDFocusItm55();
//}
//
//void OSDExitItm55(void)
//{
//    OSDConfirmItm55();
//    OSDExitItms(MP5CursorPos(), CursorPos(OSD_MAIN_4_END,usOSDState));
//}
//
//void OSDEnterItm56(void)
//{
//    OSD_state=usOSDState = OSD_ITEM_5_6_STATE;
//    OSDFocusItm56();
//}
//
//void OSDExitItm56(void)
//{
//    OSDConfirmItm56();
//    OSDExitItms(MP5CursorPos(), CursorPos(OSD_MAIN_4_END,usOSDState));
//}

void OSDEnterItm57(void)
{
    OSD_state=usOSDState = OSD_ITEM_5_7_STATE;
    OSDFocusItm57();
}

/*void OSDExitItm57(void)
{
    OSDConfirmItm57();
   OSD_state=usOSDState = OSD_MAIN_5_7_STATE;
    OSDExitItms(MP5CursorPos(), CursorPos(OSD_MAIN_4_END,usOSDState));
} */

void OSDExitItm57(void)
{
//    OSDConfirmItm57();
   OSD_state=usOSDState = OSD_MAIN_5_7_STATE;
    OSDExitItms(MP5CursorPos(), CursorPos(OSD_MAIN_4_END,usOSDState));
}

void OSDExeItm57(void)
{
   OSDConfirmItm57();
   OSD_state=usOSDState = OSD_MAIN_5_7_STATE;
   OSDExitItms(MP5CursorPos(), CursorPos(OSD_MAIN_4_END,usOSDState));
}

#if TOUCH_EnDis == ENABLE
	void OSDEnterItm58(void)	//gg_new			//george: F_Touch_04A
	{
	    OSD_state=usOSDState = OSD_ITEM_5_8_STATE;	//george: F_Touch_04A1 -> OSD_ITEM_1_5_STATE
	    OSDFocusItm58();
	}
	
	void OSDExitItm58(void)		//gg_new			//george: F_Touch_04B
	{
	    OSDConfirmItm58();
	    OSD_state=usOSDState = OSD_MAIN_5_8_STATE;	//george: F_Touch_04B1 -> OSD_MAIN_1_6_STATE
	    OSDExitItms(MP5CursorPos(), CursorPos(OSD_MAIN_4_END,usOSDState));
	}
#endif //#if TOUCH_EnDis == ENABLE


#if ENABLE_ASPECT_RATIO == ON		//george 20160217
	void OSDEnterItm59(void)						//george: F_Touch_04A
	{
	    OSD_state=usOSDState = OSD_ITEM_5_9_STATE;	//george: F_Touch_04A1 -> OSD_ITEM_1_5_STATE
	    OSDFocusItm59();
	}
	
	void OSDExitItm59(void)		//gg_new			//george: F_Touch_04B
	{
	    OSDConfirmItm59();
	    OSD_state=usOSDState = OSD_MAIN_5_9_STATE;	//george: F_Touch_04B1 -> OSD_MAIN_1_6_STATE
	    OSDExitItms(MP5CursorPos(), CursorPos(OSD_MAIN_4_END,usOSDState));
	}
#endif

#if ENABLE_FUNC_OSD == ON
//******************************************************************************
// Function Menu Operations
//******************************************************************************
void OSDEnterFuncMenu(void)
{
    OSD_state=usOSDState = OSD_FUNC_1_STATE;
    while (1) {
        if (OSDIsFuncItemValid(CursorPos(OSD_FUNC_BEG,usOSDState)) == TRUE)
            break;
        OSD_state=usOSDState = NextState(OSD_FUNC_BEG,OSD_FUNC_END,usOSDState);
    }    
    OSDShowFuncMenu();
    OSDSelectFuncItem(CursorPos(OSD_FUNC_BEG,usOSDState));
}

void OSDExitFuncMenu(void)
{
    OSD_state=usOSDState = OSD_OFF_STATE;
    OSDCloseFuncMenu();
}

void OSDFuncMenuUp(void)
{
    OSDUnselectFuncItem(CursorPos(OSD_FUNC_BEG,usOSDState));
    while (1) {
        OSD_state=usOSDState = NextState(OSD_FUNC_BEG,OSD_FUNC_END,usOSDState);
        if (OSDIsFuncItemValid(CursorPos(OSD_FUNC_BEG,usOSDState)) == TRUE)
            break;
    }
    OSDSelectFuncItem(CursorPos(OSD_FUNC_BEG,usOSDState));
}

void OSDFuncMenuDown(void)
{
    OSDUnselectFuncItem(CursorPos(OSD_FUNC_BEG,usOSDState));
    while (1) {
        OSD_state=usOSDState = PrevState(OSD_FUNC_BEG,OSD_FUNC_END,usOSDState);
        if (OSDIsFuncItemValid(CursorPos(OSD_FUNC_BEG,usOSDState)) == TRUE)
            break;
    }
    OSDSelectFuncItem(CursorPos(OSD_FUNC_BEG,usOSDState));
}

void OSDEnterFunc1(void)
{
    OSD_state=usOSDState = OSD_FNITM_1_STATE;
    OSDFocusFunc1();
}

void OSDExitFunc1(void)
{
    OSDConfirmFunc1();
    OSD_state=usOSDState = OSD_FUNC_1_STATE;
    OSDFocusFuncMenu(CursorPos(OSD_FUNC_BEG,usOSDState));
}

void OSDEnterFunc2(void)
{
    OSD_state=usOSDState = OSD_FNITM_2_STATE;
    OSDFocusFunc2();
}

void OSDExitFunc2(void)
{
    OSDConfirmFunc2();
    OSD_state=usOSDState = OSD_FUNC_2_STATE;
    OSDFocusFuncMenu(CursorPos(OSD_FUNC_BEG,usOSDState));
}

void OSDEnterFunc3(void)
{
    OSD_state=usOSDState = OSD_FNITM_3_STATE;
    OSDFocusFunc3();
}

void OSDExitFunc3(void)
{
    OSDConfirmFunc3();
    OSD_state=usOSDState = OSD_FUNC_3_STATE;
    OSDFocusFuncMenu(CursorPos(OSD_FUNC_BEG,usOSDState));
}

void OSDEnterFunc4(void)
{
    OSD_state=usOSDState = OSD_FNITM_4_STATE;
    OSDFocusFunc4();
}

void OSDExitFunc4(void)
{
    OSD_state=usOSDState = OSD_FUNC_4_STATE;
    OSDFocusFuncMenu(CursorPos(OSD_FUNC_BEG,usOSDState));
}

void OSDEnterFunc5(void)
{
    OSD_state=usOSDState = OSD_FNITM_5_STATE;
    OSDFocusFunc5();
}

void OSDExitFunc5(void)
{
    OSD_state=usOSDState = OSD_FUNC_5_STATE;
    OSDFocusFuncMenu(CursorPos(OSD_FUNC_BEG,usOSDState));
}

void OSDEnterFunc6(void)
{
    OSD_state=usOSDState = OSD_FNITM_6_STATE;
    OSDFocusFunc6();
}

void OSDExitFunc6(void)
{
    OSD_state=usOSDState = OSD_FUNC_6_STATE;
    OSDFocusFuncMenu(CursorPos(OSD_FUNC_BEG,usOSDState));
}
#endif

void OSDEnterAuto(void)
{

    OSD_state=usOSDState = OSD_AUTOTUNE_STATE;	//george: OSD_AUTOTUNE_STATE=0x38

#if AutoTune_Debug == ENABLE
printf("\tOSDEnterAuto_S, usOSDState=0x%x\n", (USHRT)usOSDState);	//150526 george
#endif

    OSDPerformAuto();
    OSD_state=usOSDState = OSD_OFF_STATE;

#if AutoTune_Debug == ENABLE
printf("\tOSDEnterAuto_E, usOSDState=0x%x\n", (USHRT)usOSDState);	//150526 george
#endif
}

void OSDEnterDir1(void)						//140317 mike brightness
{
    OSD_state=usOSDState = OSD_DIRECT_1_STATE;
	if(UserData.ucBrightness==0)
	{
		UserData.ucBrightness++;
		UserSetBrightness();
	}
	OSDShowDir1();
}

void OSDEnterDir2(void)						//140317 mike contrast
{
    OSD_state=usOSDState = OSD_DIRECT_2_STATE;				
    OSDShowDir2();
}

void OSDEnterDir3(void)						//140317 mike volume
{
    OSD_state=usOSDState = OSD_DIRECT_3_STATE;
    OSDShowDir3();								
}

void OSDExitDir(void)
{
    OSD_state=usOSDState = OSD_OFF_STATE;
    OSDCloseDir();
}
void OSDEnterOpt1(void)
{
    OSD_state=usOSDState = OSD_OPT1_STATE;
    OSDShowOpt1();
}

void OSDExitOpt1(void)
{
    OSDConfirmOpt1();
    OSD_state=usOSDState = OSD_OFF_STATE;
    OSDCloseOpt1();
}

void OSDEnterOpt2(void)
{
    OSD_state=usOSDState = OSD_OPT2_STATE;
    OSDShowOpt2();
}

void OSDExitOpt2(void)
{
    OSD_state=usOSDState = OSD_OFF_STATE;
    OSDCloseOpt2();
    OSDConfirmOpt2();
}

void OSDEnterNormal(void)
{

    OSD_state=usOSDState = OSD_INFO_NOTICE_STATE;
    OSDPerformNormal();

#if OSD_Debug == ENABLE
printf("OSDEnterNormal_E\n");		//150526 george
#endif
}

void OSDEnterNoSync(void)
{
	
    second = 0;     //FEFANJACKY FOR TIMERCOUNTER
    minute = 0;
    hour = 0;

    OSD_state=usOSDState = OSD_INFO_NOSYNC_STATE;
    OSDShowNoSync();
}

void OSDEnterNoCable(void)
{
	
    second = 0;     //FEFANJACKY FOR TIMERCOUNTER
    minute = 0;
    hour = 0;

   OSD_state= usOSDState = OSD_INFO_NOCABLE_STATE;
    OSDShowNoCable();
#if BurnIn_Degub == ENABLE
	printf("EE\n");
#endif

}

void OSDEnterOOL(void)
{	
    OSD_state=usOSDState = OSD_INFO_OUTOFLIMIT_STATE;
    OSDShowOOL();
}

void OSDEnterOOR(void)
{	
    OSD_state=usOSDState = OSD_INFO_OUTOFRANCE_STATE;
    OSDShowOOR();
}

void OSDEnterFactory(void)
{

    OSD_state=OSD_state=usOSDState = OSD_FACT_STATE;
    OSDShowFactory();
}

void OSDUpFactory(void)
{

    OSD_state=usOSDState = OSD_FACT_STATE;
    OSDFactoryUp();
}

void OSDDnFactory(void)
{
    
    OSD_state=usOSDState = OSD_FACT_STATE;
    OSDFactoryDown();
}

void OSDEnterFItm(void)
{
   
   OSD_state= usOSDState = OSD_FITM_STATE;
    OSDFactoryEnterItm();
}

void OSDExitFItm(void)
{
   
    OSD_state=usOSDState = OSD_FACT_STATE;
    OSDFactoryExitItm();
}

void OSDUpFItm(void)
{

    OSD_state=usOSDState = OSD_FITM_STATE;
    OSDFactoryItmUp();
}

void OSDDnFItm(void)
{

    OSD_state=usOSDState = OSD_FITM_STATE;
    OSDFactoryItmDown();
}

void OSDEnterDemo(void)
{
  
    OSD_state=usOSDState = OSD_DEMO_STATE;
    OSDShowDemo();
}
void OSDUpDemo(void)
{
 
    OSD_state=usOSDState = OSD_DEMO_STATE;
    OSDDemoUp();
}

void OSDDnDemo(void)
{
 
    OSD_state=usOSDState = OSD_DEMO_STATE;
    OSDDemoDown();
}
void OSDEnterDItm(void)
{
    
    OSD_state=usOSDState = OSD_DITM_STATE;
    OSDDemoEnterItm();
}
void OSDExitDItm(void)
{
  
    OSD_state=usOSDState = OSD_DEMO_STATE;
    OSDDemoExitItm();
}
void OSDUpDItm(void)
{
 
   OSD_state= usOSDState = OSD_DITM_STATE;
    OSDDemoItmUp();
}

void OSDDnDItm(void)
{
   
    OSD_state=usOSDState = OSD_DITM_STATE;
    OSDDemoItmDown();
}
void OSDDummyFunction(void)
{
   
}
