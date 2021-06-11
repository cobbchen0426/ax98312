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

#define KEY_MIN_LEVEL0 ((KEY_TYP_LEVEL0+KEY_TYP_LEVEL1)/2)      // (0x00+0x0d)/2 = 13/2 = 6
#define KEY_MIN_LEVEL1 ((KEY_TYP_LEVEL1+KEY_TYP_LEVEL2)/2)      // (0x0d+0x1E)/2 = 43/2 = 21
#define KEY_MIN_LEVEL2 ((KEY_TYP_LEVEL2+KEY_TYP_LEVEL3)/2)      // (0x1e+0x35)/2 = 83/2 = 41
#define KEY_MIN_LEVEL3 ((KEY_TYP_LEVEL3+KEY_TYP_LEVEL4)/2)      // (0x35+0x54)/2 = 137/2 = 68
#define KEY_MIN_LEVEL4 ((KEY_TYP_LEVEL4+KEY_TYP_LEVEL5)/2)      // (0x54+0x7F)/2 = 211/2 = 105




//******************************************************************************
// G L O B A L   V A R I A B L E S
//******************************************************************************
#if MD_ENABLE_AO_DETECT == ON
bit bWaitPowerKeyRelease;
xdata USHRT usAOTimer;
#endif

bit bKeyAutoTuneFlag=0;		//150526 george
//******************************************************************************
// S T A T I C   V A R I A B L E S
//******************************************************************************

//******************************************************************************
// E X T E R N A L   V A R I A B L E   P R O T O T Y P E S
//******************************************************************************
#if Key_Debug == ENABLE
//extern xdata UCHAR KeyComp;	//150526 george test
xdata UCHAR KeyComp;	//150526 george : avert the same key-value to always print("...");
#endif
//******************************************************************************
// S T A T I C   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// E X T E R N A L   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// Prototype: 
//  static UCHAR GetIOKeyCode(UCHAR btn)
// Parameters:
//  None
// Return:
//  Key Code
// Purpose:
//  Get key code
// Notes:
//  None
//******************************************************************************
/* gg static UCHAR GetIOKeyCode(UCHAR btn)
{
    static code UCHAR ucIOKeyMap[9][3] = {
        {IOBTN_1_PORT,  IOBTN_1_BIT,  IOBTN_1_ACTIVE},
        {IOBTN_2_PORT,  IOBTN_2_BIT,  IOBTN_2_ACTIVE},
        {IOBTN_3_PORT,  IOBTN_3_BIT,  IOBTN_3_ACTIVE},
        {IOBTN_4_PORT,  IOBTN_4_BIT,  IOBTN_4_ACTIVE},
        {IOBTN_5_PORT,  IOBTN_5_BIT,  IOBTN_5_ACTIVE},
        {IOBTN_6_PORT,  IOBTN_6_BIT,  IOBTN_6_ACTIVE},
        {IOBTN_7_PORT,  IOBTN_7_BIT,  IOBTN_7_ACTIVE},
        {IOBTN_8_PORT,  IOBTN_8_BIT,  IOBTN_8_ACTIVE},
        {MCU_PORT_NULL, 0,            0             },
    };

    UCHAR port, pin, act, i;

    // Decode btn id to IOKeyMap order
    port = btn;
    for (i = 0; i < 8; i++) {
        if (port & BIT0) {
            break;
        }
        port >>= 1;
    }

    port = ucIOKeyMap[i][0];
    pin  = ucIOKeyMap[i][1];
    act  = ucIOKeyMap[i][2];

    if ((port != MCU_PORT_NULL) &&
        (McuGetIOBit(port, pin) == act)) {
        return btn;
    }
    else {
        return 0x00;
    }
} */

//******************************************************************************
// Prototype: 
//  UCHAR ScanKeyPad(void)
// Parameters:
//  None
// Return:
//  Key value
// Purpose:
//  Scan the keypad
// Notes:
//  None
//******************************************************************************
UCHAR ScanKeyPad(void)
{
    static UCHAR key_buffer;
    USHRT local_timer;
    UCHAR key_temp, key_stable_time;

    local_timer = GetTimerTick();
    key_stable_time = 0;
    do 
	{    
		 ResetWDTimer();				//150526 george-add, can't delete this, If del will reboot again... again... again.
       	 key_temp = GetKey();

		if(  (bKeyAutoTuneFlag == 1) && (key_temp != key_buffer) && (key_temp==ADGRP1_CODE_5) ) 
		{		//150536 george-create-condition-block (include-var: bKeyAutoTuneFlag)
			bKeyAutoTuneFlag = 0;
			key_buffer = key_temp;
			break;
		}

        if (key_temp != key_buffer) 	//george-statement, (key_temp as key_buffer) have-different condition: true, run-update-key-value.
	    {								//george, ***(this condition for key-press-down:valid); (if key-press-up: key_temp=zero, return key_buffer will be zero)*** 
			{	//150526 george
				#if Key_Debug == ENABLE
					if(key_temp!=0)
						printf("    key2_temp= 0x%x\n", (USHRT)key_temp);	//150526 george
				#endif
			}
            		key_buffer = key_temp;
            		local_timer = GetTimerTick();
            		key_stable_time = KEY_STABLE_TIME;				//150526 george-statement: check-ok_KEY-stable.
        }
    } 
while ((key_stable_time!=0) && ((GetTimerTick()-local_timer) < key_stable_time));
//-----------------------------------------------------------------------
//AO DETECT : Power key detect///////
#if MD_ENABLE_AO_DETECT == ON
//150526 george-statement: this block-cod no compiler.
    if (bWaitPowerKeyRelease == TRUE) {//wait release
        key_buffer &= ~KEYCODE_PWR;
        if ((GetTimerTick() - usAOTimer) > AO_KEY_DEBOUNCE_TIME) {//AO timeout
            if ((AO_DETECT & BIT2) != 0) {
                AO_DETECT |= BIT2;
                usAOTimer = GetTimerTick();
            }
            else {
                bWaitPowerKeyRelease = FALSE;
            }
        }
    }
    else {
        if ((key_buffer & KEYCODE_PWR) != 0x00) {
            Sleep(AO_KEY_DEBOUNCE_TIME); //wait HW debounce
        }
        if ((AO_DETECT & BIT2) != 0) {
            key_buffer |= KEYCODE_PWR;
//            printf("key\r\n");
        }
    }
#endif
/////////////////////////////////////


    return key_buffer;
}

//******************************************************************************
// Prototype: 
//  UCHAR GetKey(void)
// Parameters:
//  None
// Return:
//  Key value
// Purpose:
//  Scan the keypad
// Notes:
//  None
//******************************************************************************
UCHAR GetKey(void)
{
    UCHAR key, adc_level;

    key = 0;

    // Perform AD Key decode
    McuPowerUpADC();
    McuStartADC();
    McuWaitADCComplete();
    McuPowerDownADC();
    adc_level = McuGetADC(KEY_GROUP1_ADC);





//===================================== power key,  (ADGRP1_CODE_1:0x02, "Power key") =====================================================
    if (adc_level < KEY_MIN_LEVEL0)										//( x < 6)      set ===> 
	{
		key |= ADGRP1_CODE_1;

		#if Key_Debug == ENABLE
			printf("__key= 'power-key'__\n");
			//printf("Power-Key_KEY_MIN_LEVEL0   131205==%x\n\r",(unsigned short)KEY_MIN_LEVEL0);		//140304 MIKE  0
		#endif
    }

//===================================== ADS:(ADGRP1_CODE_2,"menu");  AXI:(factory-mode)or(ADGRP1_CODE_5,"auto key")========================
    else if (adc_level > KEY_MIN_LEVEL0 && adc_level < KEY_MIN_LEVEL1)	//( 6 < x < 21) 
#if BUILD_CUSTOMER == X_ADS
	{	// ----------------------------- For ADS set= key is (ADGRP1_CODE_2:0x04, "menu")
			key |= ADGRP1_CODE_2;
	              
			#if Key_Debug == ENABLE  									
				if(KeyComp != key){
					printf("__ADS-key= 'menu'__\n");    //140304 MIKE  2				
					//printf("KEY_MIN_LEVEL2   131205==%x\n\r",(unsigned short)KEY_MIN_LEVEL2);    //140304 MIKE  2
				}
				KeyComp = key;
			#endif							

    }
#elif BUILD_CUSTOMER == X_AXI	 	//george-create: for AX98310  "the same: #ifdef X_ADS"

	{	// ----------------------------- For AXI_AX98310 set= key is (ADGRP1_CODE_2:0x04, "menu")
			key |= ADGRP1_CODE_2;
	              
			#if Key_Debug == ENABLE  									
				if(KeyComp != key){
					printf("__AXI-key= 'menu'__\n");    //140304 MIKE  2				
					//printf("KEY_MIN_LEVEL2   131205==%x\n\r",(unsigned short)KEY_MIN_LEVEL2);    //140304 MIKE  2
				}
				KeyComp = key;
			#endif							
    }	
#else  
    {	// ----------------------------- For Axiomtek set= key is (factory-mode) or (ADGRP1_CODE_5:0x20, "auto key")
		if (OSD_state==0)
		{
				Factory_key_time=GetTimerTick();                                               //140304 mike 
   		 		
		 		while (((adc_level > KEY_MIN_LEVEL0) && (adc_level < KEY_MIN_LEVEL1)) && ((GetTimerTick() - Factory_key_time)<2500 ))
          		{
              			Sleep(10);
					McuPowerUpADC();
              			McuStartADC();
              			McuWaitADCComplete();
              			McuPowerDownADC();
		  			adc_level = McuGetADC(KEY_GROUP1_ADC);
		 		} 
                      
				if((GetTimerTick() - Factory_key_time) > 2500 )	  
				{
					key  =   (KEYCODE_PWR|KEYCODE_MENU);	  //140304 mike for factory mode  1|2=3

					#if Key_Debug == ENABLE
						printf("__AXI-key= 'Factory-Mode'__\n");
	       	     		//printf("ADC_REG2 auto KEY  ++  auto=Factory=%d\n\r",(unsigned short)(GetTimerTick() - Factory_key_time)); 
					#endif
			    }
	    }
		else
		{
				key |= ADGRP1_CODE_5;

				#if Key_Debug == ENABLE
					if(KeyComp != key){
						printf("__AXI-key= 'auto'__\n");
						//printf("KEY_MIN_LEVEL1   131205==%x\n\r",(unsigned short)KEY_MIN_LEVEL1);   //140304 MIKE
					}
					KeyComp = key;
				#endif			   
    	}
    }										
#endif	

//===================================== ADS:(ADGRP1_CODE_3:0x08, "sel-");	 AXI:(ADGRP1_CODE_2:0x04, "menu") =============================
    else if (adc_level > KEY_MIN_LEVEL1 && adc_level < KEY_MIN_LEVEL2)	//( 21 < x < 41)
#if BUILD_CUSTOMER == X_ADS
	{	// ----------------------------- For ADS set= key is (ADGRP1_CODE_3, "sel-")
   
        		key |= ADGRP1_CODE_3;

				#if Key_Debug == ENABLE
					if(KeyComp != key){
						printf("__ADS-key= 'sel-'__\n");
					}
					KeyComp = key;
				#endif
    }
#elif BUILD_CUSTOMER == X_AXI		//george-create: for AX98310   
    {	// ----------------------------- For AXI_AX98310 set= key is (factory-mode) or (ADGRP1_CODE_5:0x20, "auto key")
		if (OSD_state==0)
		{
				Factory_key_time=GetTimerTick();                                               //140304 mike 
   		 		
		 		while (((adc_level > KEY_MIN_LEVEL1) && (adc_level < KEY_MIN_LEVEL2)) && ((GetTimerTick() - Factory_key_time)<2500 ))
          		{
              			Sleep(10);
					McuPowerUpADC();
              			McuStartADC();
              			McuWaitADCComplete();
              			McuPowerDownADC();
		  			adc_level = McuGetADC(KEY_GROUP1_ADC);
		 		} 
                      
/*				if((GetTimerTick() - Factory_key_time) > 2500 )	  
				{
					key  =   (KEYCODE_PWR|KEYCODE_MENU);	  //140304 mike for factory mode  1|2=3

					#ifdef Key_Debug
						printf("__AXI-key= 'Factory-Mode'__\n");
	       	     		//printf("ADC_REG2 auto KEY  ++  auto=Factory=%d\n\r",(unsigned short)(GetTimerTick() - Factory_key_time)); 
					#endif
			    }  */

			if(  ((GetTimerTick()-Factory_key_time) > 200)  && ((GetTimerTick()-Factory_key_time) < 1000 )	)		//key set => "auto",   150526 george-create-condition: if{} only.
			{	
				bKeyAutoTuneFlag = 1;   //150529 george, when return to ScanKeyPad() will do (key_buffer = key_temp)
				key |= ADGRP1_CODE_5;	//150529 george, ** add this for situation:  [at OSD_State=0, press this key to AutoTune_at_VGA]
				
				#if Key_Debug == ENABLE
					if(KeyComp != key){
						printf("__ADS-key1= 'auto'__\n");
					}
					KeyComp = key;
				#endif
				
			}                      
			else if((GetTimerTick() - Factory_key_time) > 2500 )	//key seet => (factory-mode, key= (0x04 | 0x20) = 0x06)
			{
				key  =   (KEYCODE_PWR|KEYCODE_MENU);					
				//george test,  key  = KEYCODE_DEMO;	//george: (KEYCODE_PWR|KEYCODE_AUTO)	
				#if Key_Debug == ENABLE
						printf("__ADS-key= 'Factory-Mode'__\n");
			       		//printf("ADC_REG2 auto KEY  ++  auto=Factory=%d\n\r",(unsigned short)(GetTimerTick() - Factory_key_time)); 	 //george-stement: two-time-show-this-print_will-ext->(factorymode).
				#endif

			}

	    }
		else
		{
				key |= ADGRP1_CODE_5;

				#if Key_Debug == ENABLE
					if(KeyComp != key){
						printf("__AXI-key2= 'auto'__\n");
						//printf("KEY_MIN_LEVEL1   131205==%x\n\r",(unsigned short)KEY_MIN_LEVEL1);   //140304 MIKE
					}
					KeyComp = key;
				#endif			   
    	}
    }
#else
	{	//-------------------------------------	For Axiomtek set= key is (ADGRP1_CODE_2:0x04, "menu")
        		key |= ADGRP1_CODE_2;
								
				#if Key_Debug == ENABLE
					if(KeyComp != key){
						printf("__AXI-key= 'menu'__\n");    //140304 MIKE  2					   
					}
					KeyComp = key;
				#endif
    }
#endif

//===================================== (ADGRP1_CODE_4:0x10, "sel+") ======================================================================
 else if (adc_level > KEY_MIN_LEVEL2 && adc_level < KEY_MIN_LEVEL3)		//( 41 < x < 68) set ===> 
	{	 
		key |= ADGRP1_CODE_4;

		#if Key_Debug == ENABLE
			if(KeyComp != key){
				printf("__key= 'sel+'__\n");    //140304 MIKE  2				   
			}
			KeyComp = key;
		#endif
    }	
    		
        //--------------------------------------------  sel+ key (disable factory key)
		/*     
             else if (adc_level > KEY_MIN_LEVEL2 && adc_level < KEY_MIN_LEVEL3) 
                        {		 
        		   key |= ADGRP1_CODE_4;
                      #ifdef Key_Debug               			//140304 mike       sel+      
	          //       printf("\nADC_KEY_GROUP1_ADC ==> RIGHT  131205==%x\n\r",(unsigned short)adc_level);
	                 printf("KEY_MIN_LEVEL2   131205==%x\n\r",(unsigned short)KEY_MIN_LEVEL3);     //140304 mike  3
                      #endif
	      	       }	
		*/

//===================================== ADS:(ADGRP1_CODE_5:0x20, "auto") or (factory-mode);	 AXI:(ADGRP1_CODE_3, "sel-") =============================
    else if (adc_level > KEY_MIN_LEVEL3 && adc_level <= KEY_MIN_LEVEL4) 	//( 68 < x < 105)
#if BUILD_CUSTOMER == X_ADS
	{	// ----------------------------- For ADS set= key is (ADGRP1_CODE_5:0x20, "auto" / "exit") or (factory-mode)
		if (OSD_state==0)
		{
          	Factory_key_time=GetTimerTick();                                               //140304 mike 
			while (((adc_level > KEY_MIN_LEVEL3) && (adc_level < KEY_MIN_LEVEL4)) && ((GetTimerTick() - Factory_key_time)<2500 ))
          	{  
		      			//printf("\n%d\n\r",(unsigned short)(GetTimerTick() - Factory_key_time)); 
	            			//printf("ADC_REG2  SEL+ KEY     131227==%x\n\r",(unsigned short)adc_level);      
	              			Sleep(10);
						McuPowerUpADC();
	              			McuStartADC();
	              			McuWaitADCComplete();
	              			McuPowerDownADC();
			  			adc_level = McuGetADC(KEY_GROUP1_ADC);
						//if((GetTimerTick() - Factory_key_time)>3000 )	 
						//{
						//	break;
						//}		 
			} 

			if(  ((GetTimerTick()-Factory_key_time) > 200)  && ((GetTimerTick()-Factory_key_time) < 1000 )	)		//key set => "auto",   150526 george-create-condition: if{} only.
			{	
				bKeyAutoTuneFlag = 1;   //150529 george, when return to ScanKeyPad() will do (key_buffer = key_temp)
				key |= ADGRP1_CODE_5;	//150529 george, ** add this for situation:  [at OSD_State=0, press this key to AutoTune_at_VGA]
				
				#if Key_Debug == ENABLE
					if(KeyComp != key){
						printf("__ADS-key= 'auto'__\n");
					}
					KeyComp = key;
				#endif
				
			}                      
			else if((GetTimerTick() - Factory_key_time) > 2500 )	//key seet => (factory-mode, key= (0x04 | 0x20) = 0x06)
			{
				key  =   (KEYCODE_PWR|KEYCODE_MENU);					
				//george test,  key  = KEYCODE_DEMO;	//george: (KEYCODE_PWR|KEYCODE_AUTO)	
				#if Key_Debug == ENABLE
						printf("__ADS-key= 'Factory-Mode'__\n");
			       		//printf("ADC_REG2 auto KEY  ++  auto=Factory=%d\n\r",(unsigned short)(GetTimerTick() - Factory_key_time)); 	 //george-stement: two-time-show-this-print_will-ext->(factorymode).
				#endif

			}
		}
		else
		{ 	
				key |= ADGRP1_CODE_5;								//key set => "exit", (when (OSD_state > 0)
				
				#if Key_Debug == ENABLE
					if(KeyComp != key){
						printf("__ADS-key= 'exit'__\n");
			       		//printf("KEY_MIN_LEVEL1   131205==%x\n\r",(unsigned short)KEY_MIN_LEVEL1);   //140304 MIKE  1		   
					}
					KeyComp = key;
				#endif
		}
    }
#elif BUILD_CUSTOMER == X_AXI		//george-create: for AX98310   "the same: #else"
	{   //-------------------------------------	For AXI_AX98310 set= key is (ADGRP1_CODE_3, "sel-")   
   		key |= ADGRP1_CODE_3;
		   	 	  
		#if Key_Debug == ENABLE
			if(KeyComp != key){
				printf("__AXI-key= 'sel-'__\n");    //140304 MIKE  2
			}
			KeyComp = key;
		#endif
    }
#else	
	{   //-------------------------------------	For Axiomtek set= key is (ADGRP1_CODE_3, "sel-")   
   		key |= ADGRP1_CODE_3;
		   	 	  
		#if Key_Debug == ENABLE
			if(KeyComp != key){
				printf("__AXI-key= 'sel-'__\n");    //140304 MIKE  2
			}
			KeyComp = key;
		#endif
    }		
#endif
	
//----------------------------------
//KEY GROUP2 ADC FUNCTION  140304 mike
//----------------------------------
#if ALS_EnDis == ALSRange
	// disable KEY_GROUP2_ADC, change to LS3101 Light-Sensor
#else
if(0)	//150526 george , Disable this KEY-GROUP2 function.
{
    adc_level = McuGetADC(KEY_GROUP2_ADC);
    if (adc_level < KEY_MIN_LEVEL0) {
        key |= ADGRP2_CODE_1;
    }
    else if (adc_level > KEY_MIN_LEVEL0 && adc_level < KEY_MIN_LEVEL1) {
        key |= ADGRP2_CODE_2;
    }
    else if (adc_level > KEY_MIN_LEVEL1 && adc_level < KEY_MIN_LEVEL2) {
        key |= ADGRP2_CODE_3;
    }
}
#endif	//#if ALS_EnDis == ENABLE

    // Perform IO Key decode
    //140317 mike 
    /*
    key |= GetIOKeyCode(IOBTN_CODE_1);
    key |= GetIOKeyCode(IOBTN_CODE_2);
    key |= GetIOKeyCode(IOBTN_CODE_3);
    key |= GetIOKeyCode(IOBTN_CODE_4);
    key |= GetIOKeyCode(IOBTN_CODE_5);
    key |= GetIOKeyCode(IOBTN_CODE_6);
    key |= GetIOKeyCode(IOBTN_CODE_7);
    key |= GetIOKeyCode(IOBTN_CODE_8);
     */ //140317 mike 

    return key;
}

#if MD_ENABLE_AO_DETECT == ON
bit CheckFactoryMode(void)
{
    if (GetKey() == (KEYCODE_FACT & ~KEYCODE_PWR)) {
        return TRUE;
    }
    return FALSE;
    }
#endif

