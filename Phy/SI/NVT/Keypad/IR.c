/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/
/******************************************************************************/
/*       KeyPad.h                                                             */
/*       Release Date:2010/01/21       Last Maintenance:2010/07/28            */
/*       Original Version:2.0.00       Last Version:2.0.02                    */
/*       Coding By: Mingyu Huang       Maintenance By: Mingyu Huang           */
/******************************************************************************/

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************
#include "Include.h"

#if IR_REMOT_CTL == ENABLE
//******************************************************************************
// G L O B A L   D E F I N I T I O N S
//******************************************************************************
#define _TIME_BASE_
#define TIME_BASE_HOLDING_TIME	500	//428+2	//400 	//450
#define TIME_BASE_REPEAT_TIME	600	//535+2	//550	//150
#define TIME_BASE_PH_TIME		200
//******************************************************************************
// G L O B A L   V A R I A B L E S
//******************************************************************************

xdata USHRT usIRData=0;
bit bIrDetect = 0;


idata unsigned char  ucCurIRKey = 0;
idata unsigned char  ucPrevIRKey = 0;

bit bIrReleaseFlag = 0;
idata unsigned short usIRReleaseCountTimer = 0;

bit PH_Flag=0;
xdata USHRT usPHCountTimer=0;

//******************************************************************************
// S T A T I C   V A R I A B L E S
//******************************************************************************

//******************************************************************************
// E X T E R N A L   V A R I A B L E   P R O T O T Y P E S
//******************************************************************************
extern BOOL bIsAPLLPowerDown;


//******************************************************************************
// S T A T I C   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// E X T E R N A L   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************



void IR_Initalize()
{
    //initialize variables
    //printf("Initalize IR\r\n");
    bIrDetect = 0;
    ucCurIRKey = 0xFF;			//from State get CurIRKey
    usIRReleaseCountTimer = 0;



	//enable EXT INT
    INTEXT_FLG |= INTE2;
	INTEXT_EN  |= INTE2;
	
	//IT1 = 0;    
}


//void ucIRReleaseCountCheck()
//{
//	//not-thing  	   
//}


void IR_Process() 
{
    	UCHAR IRError = 0;
 static UCHAR ucPrevIRKey = 0xAA;
 static UCHAR ucNowIRKey  = 0x55;			 //  ucCurIRKey
 static UCHAR ucEquNewOldKeyCount=0;
					
	// bIrDetect set true from Int.c -> Time0()
	if(bIrDetect == 1)
	{
		if( (usIRData & 0x3100) || (usIRData & 0x3900) )	//is RC5_(Start & Toggle)
		{
	
			if( ((usIRData & RC5_ADDR_MASK) == RC5_ADDR) ) 			//is RC5_(Address)
			{

				bIrDetect = 1;
				ucNowIRKey = (UCHAR) usIRData & RC5_CMD_MASK;		//is get RC5_(CMD) inverter UCHAR type.
				

				if( ucPrevIRKey != ucNowIRKey)
				{	
					ucEquNewOldKeyCount = 0;	// Clear 
					ucPrevIRKey = ucNowIRKey;
					ucCurIRKey = 0xFF;

					usIRReleaseCountTimer = GetTimerTick();
	    			if ( ucCurIRKey!=RC5_CMD_POWER )
	        			bIrReleaseFlag = 1;

				}else
				{
					ucEquNewOldKeyCount++;	

					if(ucEquNewOldKeyCount == 1) {	//FistTime:  Run Once CurIRKey						
						ucCurIRKey = ucPrevIRKey;
					}else if(bIrReleaseFlag && ( (GetTimerTick()-usIRReleaseCountTimer)  < TIME_BASE_HOLDING_TIME) ) { //hold time		
						ucEquNewOldKeyCount = 2;
						ucCurIRKey = 0xFF;
						//bIrDetect = 0;
					}else if( ucEquNewOldKeyCount>=3 && bIrReleaseFlag && ( (GetTimerTick()-usIRReleaseCountTimer)  > TIME_BASE_REPEAT_TIME) ) {
						ucEquNewOldKeyCount = 2;	
						ucCurIRKey = ucPrevIRKey;
						usIRReleaseCountTimer = GetTimerTick() + TIME_BASE_REPEAT_TIME;
					}
				}


 				PH_Flag = 1;
				usPHCountTimer = GetTimerTick();

			 }else				
				IRError = 1;	//Fail IR_Key

		}else
			IRError = 1;	//Fail IR_Key


	}else if(bIrDetect==0 && PH_Flag==1 && ( abs(GetTimerTick() - usPHCountTimer)  > TIME_BASE_PH_TIME) )
	{
		ucEquNewOldKeyCount = 0;
		ucPrevIRKey = 0xAA;
		ucNowIRKey  = 0x55;
		ucCurIRKey  = 0xFF;

		PH_Flag  	= 0;
		bIrReleaseFlag=0;
	}


	if(IRError == 1)
	{
		ucEquNewOldKeyCount = 0;
		ucPrevIRKey =0xAA;
		ucNowIRKey  =0x55;
		bIrDetect = 0;	//FALSE;
		ucCurIRKey  = 0xFF;

		PH_Flag  	= 0;
		bIrReleaseFlag=0;		
	}

}



unsigned char IR_GET_KEY()
{
    UCHAR ucIRCode = 0xff;

	IR_Process();

    if(bIrDetect)
    {
        bIrDetect = 0;	//Clear ucIrDetect=0;

		//Get IRCode
		if(ucCurIRKey == RC5_CMD_POWER)		//KEYCODE_PWR by \Phy\SI\NVT\Keypad\NT68850_DEMO_KEYPAD\KeyPadConfig.h  define
			ucIRCode = KEYCODE_PWR;		
		else if(ucCurIRKey == RC5_CMD_MENU)
			ucIRCode = KEYCODE_MENU;
		else if(ucCurIRKey == RC5_CMD_UP)
			ucIRCode = KEYCODE_UP;
		else if(ucCurIRKey == RC5_CMD_DOWN)
			ucIRCode = KEYCODE_DOWN;
		else if(ucCurIRKey == RC5_CMD_AUTO)
			ucIRCode = KEYCODE_AUTO;
		else if(ucCurIRKey == RC5_CMD_INPUT)
			ucIRCode = KEYCODE_INPUT;		//  \Phy\SI\NVT\Keypad\NT68850_DEMO_KEYPAD\KEYPADCONFIG.H
		else
			ucIRCode = 0xFF;
	}

    return ucIRCode;
}



UCHAR ScanIrKey()
{
    UCHAR evt = IR_GET_KEY();

    return evt;
}

#endif


