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
#include "Warning.h"

/**** George statement something :
1. #ifdef X_ADS  
		{... ADS ...}
   #else
   		{... AXI ...}
   #endif

2. george define word at: ChiuDef.h file.

3. xdata UCHAR KeyComp: is //150526 george: avert the same key-value to always print("...");
4. (at \Sys\SI\NVTMODELCONFIG.H) ->  

			#if ENABLE_HDMI_PRETEST == OFF
			
				if(!((IsDPTrainingDone() == TRUE) && IsDPConnect()))
				{ 
			        ScalerPowerSaving();
			    }
			
			    //ScalerPowerSaving();
			#endif

*****/


//#define	CHANGE_TOUCH_OFF	0	//george: for touch-detect chang-event
//#define	CHANGE_TOUCH_ON		1	//george: for touch-detect chang-event

//#define FLIPW( ray ) 	( (((USHRT) (ray)[0]) * 256) + (ray)[1] ) 

//#define WORD_LO(xxx) ((byte) ((word)(xxx) & 255)) 
//#define WORD_HI(xxx) ((byte) ((word)(xxx) >> 8)) 



//******************************************************************************
// M A C R O   D E F I N I T I O N S
//******************************************************************************

//******************************************************************************
// G L O B A L   V A R I A B L E S
//******************************************************************************
xdata USHRT	ucGeorge;	//150429 George test


//******************************************************************************
// S T A T I C   V A R I A B L E S
//******************************************************************************

//******************************************************************************
// E X T E R N A L   V A R I A B L E   P R O T O T Y P E S
//******************************************************************************



//******************************************************************************
// S T A T I C   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
#if ENABLE_HDCP_TRIM_MODE == ON
static USHRT ReadScalerID(void);
#endif
#if ENABLE_ESD_PROTECT == ON
static void ESD_CHECK(void);
#endif
//******************************************************************************
// E X T E R N A L   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// F U N C T I O N   B O D Y S
//******************************************************************************

/**************************************************************************//**
 * The entry point of FALCON.
 * This function will be called by startup.a51.
 ******************************************************************************/
void main(void)
{
  ucGeorge=0;	//150429 George



    // According to our MCU spec, we must set the type of bank allocation first.
    // Therefore, we set BankSet(0x22) first. (We MUST set it first!)
    BankSet(0x22);

    DisableInterrupt();
#if ENABLE_HDCP_TRIM_MODE == ON
    ucEFUSE_ID = (UCHAR)(ReadScalerID()>>8);
#endif

    McuInitialize();

#if (ENABLE_DIGI1_HPD == ON) || (ENABLE_DIGI0_HPD == ON) || (ENABLE_DP_HPD == ON)
    SYSAPI_PerformHPDOff(TRUE);			// AC off/on set hot plug Pin off(Low)    
#endif    

#if	PWROn_Debug == ENABLE
    printf("Start Program0509\r\n");
#endif 

//=====================
//#ifdef XRS232
//     ucUARTRxIn = 0 ;					//140701 mike 
//#endif
//=====================
    RamInitialize();		//printf("00-1\n");
    EnableInterrupt();		//printf("00-2\n");
    ScalerInitialize();		//printf("00-3\n");
    NvramLoadData();		//printf("00-4\n");
    UserData.bPowerStatus = ON;  //fefanjacky ADD for dc-on power is on
    Custom_System_Init();	//printf("00-5\n");

    APPInitSystem();		//printf("00-6\n");

//#if MCU_UART_OUTPUT != 0    //140304 mike 
#if	PWROn_Debug == ENABLE
   printf("Start Program\r\n");
#endif
//#endif     	 				//140304 mike

	SC_MCU_IO_CTRL5 &=  ~(BIT3 | BIT2);	//150504 George	 , used PC6 / INTE2	   ( McuMisc.c -> McuInitLPD() )


	#if (ALS_EnDis == ALSMODE) || (ALS_EnDis == ALSOffSET)
		CM3218Initialize();
	#elif ALS_EnDis == ALSRange
		//LS3101 don't need Initialize.
	#endif	//#if ALS_EnDis == ENABLE



	//Run \App\APPCtrl.c -> IR_Initalize()
	#if (XRS232==LWO_RS232)
	mPrintStr("------FW Startng------");
	#endif
	
    while (1) 
	{

			ResetWDTimer();	
	      	ModeHandler();					//140319 mike check sysnc
	     	EventHandler();
	      	SYSAPI_CheckSysPower();			//140319 mike check system power 

		#if ENABLE_ESD_PROTECT == ON
	       	 ESD_CHECK();
		#endif

		#if((INPUT_INTERFACE&INPUT_DP)  && ENABLE_DP_AUX_MONITOR==ON)   	
       		DP_Aux_Channel_Monitor();    
		#endif   

		//Ambient-Light-Sensor Process.	
		#if (ALS_EnDis == ALSMODE) || (ALS_EnDis == ALSOffSET)
			CM3218_Process();	//george: F_CM3218_03
		#elif ALS_EnDis == ALSRange
			LS3101_Process();
		#endif	//#if ALS_EnDis == ENABLE


		//UART Command Analyze Process.
		#if (XRS232 == ADS_RS232)
				Analy_CMD();
		#elif (XRS232 == LWO_RS232)
				UartHandler();
		#endif //#if (XRS232 == ENABLE)



		ucGeorge++;
	//	if( ucGeorge == 1500)
		{	
			
		}
	
		if(ucGeorge == 3000)	//1000)
		{	//ucGeorge=100;	
			ucGeorge=0;	
			if(UserDataWriteFlag)
			{
				UserDataWriteFlag=0;
				NvramWriteUserData(&UserData);
			}
			//printf("ratio= %d\n", (USHRT)UserData.ucOSDTimer*100/MAXIMUM_OSD_TIMER;);
//			printf("OSDTimer= %d\n", (USHRT)UserData.ucOSDTimer);

//printf("ucModeHdlrState= %d\n", (USHRT) ucModeHdlrState);

			//printf("UserData[]= %d\n", (USHRT)sizeof(NvramUserData));	
			//printf("usADBoardID_Hi[]= %x\n", (USHRT) (UserData.usADBoardID & 0xFF00) );
			//printf("usADBoardID_Low[]= %x\n\n", (USHRT) (UserData.usADBoardID & 0x00FF) );
			//printf("usADBoardID_Hi[]= %x\n", (UCHAR) (UserData.usADBoardID >> 8) );

			

//			printf("UserData.ucInputSource= %d\n", (USHRT)UserData.ucInputSource);
			//printf("ucModeHdlrState= %d\n", (USHRT) ucModeHdlrState);
			////	OSDShowResolution(0,0);	//george 15,14);
/*			printf(" %dx%d@%d.%dHz, %d.%dkHz, Pol:%x\n",InputTiming.usModeHActive,
                                  InputTiming.usModeVActive,
                                  InputTiming.usVSyncFreq/10, 
                                  InputTiming.usVSyncFreq%10,
								  InputTiming.usHSyncFreq/10,
								  InputTiming.usHSyncFreq%10,
								  InputTiming.ucHVPolarity);
  
		//Debug Printer Process.   
			#if (ALS_EnDis == ALSMODE) || (ALS_EnDis == ALSOffSET)
//				CM3218_Print();
			#elif ALS_EnDis == ALSRange
	//gg			 LS3101_Print();
			#endif	//#if ALS_EnDis == ENABLE

			#if (XRS232 == ENABLE)
//				DBG_Print();
				//printf("Sou= %d\n", (USHRT) UserData.ucInputSource);
			#endif //#if (XRS232 == ENABLE)
//			printf("State= %d\n", (USHRT)SystemData.bDemo);
*/
		}


	} //While(1) End
}//main() END





//=======================================================================================================================
#if ENABLE_HDCP_TRIM_MODE == ON
//NT68850=0x0B
//NT68770=0x0C
//NT68655=0x0D
USHRT ReadScalerID(void)
{ 
USHRT scaler_id = 0x0000;
UCHAR tmp_0xF04C, tmp_0x8D55, tmp_0x8D50, tmp_0x8101, tmp_0x8102, tmp_0x8641;
//12MHz
    SC_ADC_ZERO_POWER_CTRL |= 0x81;
    tmp_0xF04C = CPU_CLK;
    CPU_CLK = 0x10;
    tmp_0x8101 = SC_POWER_CTRL1;
    SC_POWER_CTRL1 = 0x00;
    tmp_0x8102 = SC_POWER_CTRL2;
    SC_POWER_CTRL2 |= BIT1;
    tmp_0x8641 = SC_HDCP_INPUT_CTRL;
    SC_HDCP_INPUT_CTRL |= BIT7;
//
    tmp_0x8D55 = SC_HDCP_TRIM_CTRL2;
    SC_HDCP_TRIM_CTRL2 &= ~BIT6;
// 
    tmp_0x8D50 = SC_HDCP_TRIM_CTRL;
    SC_HDCP_TRIM_CTRL |= BIT0;
    SC_HDCP_TRIM_CTRL &= ~BIT1;
//address
    SC_HDCP_TRIM_ADDR = 0x91;
//read enable
    SC_HDCP_TRIM_CTRL |= BIT6;
//read data hi
    scaler_id = SC_HDCP_TRIM_DATA_HI;
    scaler_id <<= 8;
//read data lo
    if((SC_HDCP_TRIM_DATA_LO & 0x0F) == 0x0F) {
        scaler_id |= (SC_HDCP_TRIM_DATA_LO>>4);
    }
    else {
        scaler_id |= SC_HDCP_TRIM_DATA_LO;
    }
    SC_HDCP_TRIM_CTRL = tmp_0x8D50;
    SC_HDCP_TRIM_CTRL2 = tmp_0x8D55;
    CPU_CLK = tmp_0xF04C;
    SC_HDCP_INPUT_CTRL = tmp_0x8641;
    SC_POWER_CTRL1 = tmp_0x8101;
    SC_POWER_CTRL2 = tmp_0x8102;
    return scaler_id; 
}
#endif


#if ENABLE_ESD_PROTECT == ON
void ESD_CHECK(void)
{
    static UCHAR ucPreOSDRAMCheckSum;
    UCHAR ucNowOSDRAMCheckSum;
    if (IsBackLightOn() == TRUE) {
        if (SC_INDEX_CTRL != 0x8C) {// read OSD SRAM
            ucNowOSDRAMCheckSum = ReadOSDCheckSum();
            ucPreOSDRAMCheckSum = ucNowOSDRAMCheckSum;
//            printf("OSDRAMCheckSumN1=%x\r\n", (USHRT)ucNowOSDRAMCheckSum);
        }
        else {
            ucNowOSDRAMCheckSum = ReadOSDCheckSum();
//            printf("OSDRAMCheckSumN2=%x\r\n", (USHRT)ucNowOSDRAMCheckSum);
            if (ucPreOSDRAMCheckSum != ucNowOSDRAMCheckSum) {
//                printf("ucPreOSDRAMCheckSum=%x\r\n", (USHRT)ucPreOSDRAMCheckSum);
//                printf("ucNowOSDRAMCheckSum=%x\r\n", (USHRT)ucNowOSDRAMCheckSum);
                ucPreOSDRAMCheckSum = ucNowOSDRAMCheckSum;
                //Error////////////////////////////////////////////
                while(1){};
                ///////////////////////////////////////////////////
            }
        }

    }
    else {
        ClearESDCKStatus();
    }
#if 1
    CLR_WDT2 = 0x55;
    WDT2_SEL = WDT2SELECT;
#endif
}
#endif
