/******************************************************************************/
/*                    Axiomdisplay CO,, LTD.                                  */
/*                    All Rights Reserved                                     */
/*                    Ambient Light Sensor Device: Use CAPELLA "CM3218"(I2C)  */
/******************************************************************************/

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************
#include "Include.h"
//#include <math.h>		//george: ALS  used_function: abs(x)
/*
SetBrightness()									: void BacklightOn() / BacklightOff(set SetBrightness:0),  SetBrightnessPWMMax(PreSetBrightnessPWMMax=TRUE, SetBrightness())
SetScalerPWM(BKL_PWM_PORT, (unsigned short)br); : SYSAPI_SetInverterVal(), SetBrightness(), PanelPowerOffSequence(set SetScalerPWM:0)
SYSAPI_SetInverterVal()							: APPInitSystem(), FactorySetValue(), UserRecallConfiguration()
SetBrightnessPWMMax(PreSetBrightnessPWMMax=TRUE, SetBrightness()):  APPTimerRoutine() 


tack: SetScalerPWM()
	  * DisableDCR() -> UserSetBrightness();

no used:  void OSDShowDir4(void)  , but used void OSDShowDir1(void);
*/



#if (ALS_EnDis == ALSOffSET)
//******************************************************************************
// M A C R O   D E F I N I T I O N S
//******************************************************************************
#define CM3218_DEVICE	0x90		/* Slave_Address(8bit): 0x90 */
#define CM3218_CMD_00	0x00		/* Set ALS_SM, ALS_IT, ALS_PERS, INT_En/Dis, Power-On/ShutDown */
#define CM3218_CMD_HTWS	0x01		/* (when INT Enable) High Threshold Window setting. */
#define CM3218_CMD_LTWS	0x02		/* (when INT Enable) Low Threshold Window setting.  */
#define CM3218_CMD_03	0x03		/* Default Setting : 0x0000 */
#define CM3218_CMD_READ	0x04		/* CM3218 Output Data */
#define ALS_SHUTDOWN	0x1005		/* 0x1005 =>  Sen*0.5,  INT_Dis,  PWR_Shutdown */
#define DEFAULT_SET		0x0000		/* 0x1005 =>  Sen*0.5,  INT_Dis,  PWR_Shutdown */
#define ALS_INIT0		0x1084		/* 0x1084 => ALS_SM:10(*0.5),  ALS_IT:10,  ALS_PERS:00,  "INT_Dis", Power-On */
#define ALS_INIT1		0x0084		/* 0x0084 => ALS_SM:00(*1  ),  ALS_IT:10,  ALS_PERS:00,  "INT_Dis", Power-On */
#define ALS_INIT2		0x0884		/* 0x0084 => ALS_SM:00(*2  ),  ALS_IT:10,  ALS_PERS:00,  "INT_Dis", Power-On */

#define BOUNCE_FST_CNT		5		/* when bALSOnOff switch "ON" at first-timing to set BOUNCE */
#define BOUNCE_CNT			200		/* Count-out to Reflsh "NowAlsBright" value action ++ or --.: [Prefer-Range]: 50,100,(150) */
#define CNT_SENS_STABLE		2		/* when ALSDATA_TOL=0x00ff, [Prefer-Range]: 0~2 */
#define CNT_BRIG_STABLE		25		//100

#define ALSDATA_TOL			0x00ff	/* get ALSens_tmp Tolerance Range */

//-------------------------------------------------
#define CheckNowAlsBrigMaxRange(a,b) {if (a > b) a = b;}
#define MAXIMUM_ALS_BRIG	100		/* ALS auto-dim BRIG. MAX */
//******************************************************************************
// S T A T I C   V A R I A B L E S
//******************************************************************************

//******************************************************************************
// G L O B A L   V A R I A B L E S
//******************************************************************************
// Is --/++ DeBuncSens or CntBrigStable at Time0 / Time1 .
xdata UCHAR DeBuncSens;			/* [IN-PUT ] tmpALSdata <-> DeBounceALS <-> ALSdata(stable-value) */
xdata UCHAR CntBrigStable;			/* [OUT-PUT] tmpALSdata <-> DeBounceALS <-> ALSdata(stable-value) */
xdata UCHAR CntSensStable;
xdata USHRT	NowAlsSens, AlsSens_tmp, AlsSens_buf; //, ALSdata_buffer ;

xdata UCHAR  NowAlsBright=0, AlsBrigTarg=0;	/* (ALSBright + UserData.ucALSBaseVal) = ALSBrigTarg(set target pwm) */

																												//xdata UCHAR div_ALSBaseVal=0; //new add
//xxxxxxx no-used *******  xdata UCHAR ucALSOnSetBrigVal;	//for replace UserData.ucBrightness to set brightness
//Ref: UserData.bALSOnOff				//OSDALSOnOffUp() OSDALSOnOffDown()
//Ref: ucALSBaseVal
//-----------------------------------------------


xdata USHRT CkDevice_timer=0;
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


void CM3218Initialize(void)				//george: F_CM3218_00
{
UCHAR const ARA=0x18;	//0x0C(7bit), 0x18(8bit);	//ARA, Alert Response Address
UCHAR const ARA_DATA=0x90;
	//at Initialize to Check Device:   if( NvramCheckDevice(CM3218_DEVICE) == TRUE)   "always don't used";
// [* if no device *] " ??? how to do some-thing ???


	//(1) Clear INT:  ReadByte, slave_addr:0x19, ack, Data:CM3218-AD 0x90
	ReadIICCM3218ARA(ARA, ARA_DATA);

	//(2) Shutdown ALS
	WriteIICWordSeq(CM3218_DEVICE, CM3218_CMD_00, ALS_SHUTDOWN);	//0x1005

	//(3) Default Setting
	WriteIICWordSeq(CM3218_DEVICE, CM3218_CMD_03, DEFAULT_SET);		//0x0000

	//(4) Power On:
	WriteIICWordSeq(CM3218_DEVICE, CM3218_CMD_00, ALS_INIT0);		//0x1084
	//	printf("WriteIICWordSeq_0x00= 0x%4x \n",(USHRT) ALS_INIT );
	
	DeBuncSens = BOUNCE_CNT;
	CntSensStable = CNT_SENS_STABLE;
	CntBrigStable = CNT_BRIG_STABLE;

	NowAlsSens=AlsSens_buf=AlsSens_tmp=0;
	AlsBrigTarg=NowAlsBright=0;
}

void CM3218_BacklightOn_Init(void)		//george: F_CM3218_01	//at Power-On used: BacklightOn()
{
	DeBuncSens = CntSensStable = CntBrigStable = BOUNCE_FST_CNT;
	AlsBrigTarg  = UserData.ucALSBaseVal;
	NowAlsBright = UserData.ucALSBaseVal;
}


void CM3218_ALSOnInit(void)				//george: F_CM3218_02	//at OSDALSOnOffUp() or OSDALSOnOffDown()  used.
{
	DeBuncSens = CntSensStable = CntBrigStable = BOUNCE_FST_CNT;														
	AlsBrigTarg  = UserData.ucBrightness;
	NowAlsBright = UserData.ucBrightness;			
}

void SetNowALSBrig(void)					//george: F_CM3218_01
{
	CheckNowAlsBrigMaxRange(NowAlsBright, MAXIMUM_ALS_BRIG);
	SetBrightness(GetNowAlsBright1023());
}



void CM3218_Process(void)					//george: F_CM3218_03
{
	//ref. SetGlobalTimer()  GetGlobalTimer() ==> UpdateGlobalTimer() ==> GetTimerTick()
	//ref. GetGlobalTimer() used at condition:  if(GetGlobalTimer(GLOBAL_TMR_LOCAL) == 0)

	static UCHAR SS=0;	/* SS=0: device_not_exist(set ALSOnOff=OFF).   SS=1: CM3218_Init  SS=2: Read_data */
	UCHAR i=0;
	
	// if ALS: CM3218 OFF return;
	if(UserData.bALSOnOff == OFF)	return;


     // ========== Reserve Code ==========
	//(A) Check Device	
	if ( CkDevice_timer == 0)
	{
		CkDevice_timer = 3000;

		for (i=0; i<5; i++) {
			if (NvramCheckDevice(CM3218_DEVICE) == TRUE) {
				if(SS==2)
					SS=2;	//no need change.
				else
					SS=1;	//CM3218 device exist.
	            break;
			}
		}

	    if (i == 5) {  
			//printf("_ALS_Device no exit!_\n");			
			SS=0;		//CM3218 device not exist.
			//------------------------------------
			UserData.bALSOnOff = OFF;
			UserSetALSOnOff();
			//SetOSDUpdUsrFlag();
			UserSetBrightness();
	        return;
	    }
	}


	//(B) CM3218 Initialize
	if(SS==1)
	{
		CM3218Initialize();
		SS=2;
	}



	if(SS==0)
		return;

	//(C) (at SS=2) CM3218 Read Data (need Delay > 400ms)
	// (1). [IN-PUT] : Count-out to Reflish "ALSens" Value.  to IIC none busy.	
	if(--DeBuncSens == 0)
	{	
		DeBuncSens = BOUNCE_CNT;

		ResetWDTimer();				
		ReadIICWordSeq(CM3218_DEVICE, CM3218_CMD_READ, &AlsSens_tmp);

		if( AlsSens_tmp < ALSDATA_TOL ) 				// if TRUE: limit AlsSens_tmp = ALSDATA_TOL
			AlsSens_tmp = ALSDATA_TOL;
		else if( AlsSens_tmp > (0xffff-ALSDATA_TOL) ) 	// if TRUE: limit AlsSens_tmp = (0xffff-ALSDATA_TOL);
			AlsSens_tmp = (0xffff-ALSDATA_TOL);
		
		if( (AlsSens_buf+ALSDATA_TOL >= AlsSens_tmp ) && (AlsSens_tmp >= AlsSens_buf-ALSDATA_TOL) ) 	// if TRUE: the "AlsSens_tmp" Value Stable.
		{

			if( --CntSensStable == 0 ) 						// [ OK ]: ths "CntSensStable" times equal  "CNT_SENS_STABLE-1", then set "NowAlsSens" Value Stable.
			{
				CntSensStable = CNT_SENS_STABLE;
				NowAlsSens    = AlsSens_buf;


	// (2). [CONVERTER]:
				/*	
					493 > X > 378 nits: factor=26.0  ==>  (374 nits) * (26.0) = AlsSens_Value(12818= 0x3212);
					374 > X > 278 nits: factor=26.1  ==>  (374 nits) * (26.1) = AlsSens_Value( 9761= 0x2621);
					278 > X > 221 nits: factor=26.2  ==>  (278 nits) * (26.2) = AlsSens_Value( 7283= 0x1C73);
					221 > X > 187 nits: factor=26.4  ==>  (221 nits) * (26.4) = AlsSens_Value( 5834= 0x16CA);
					187 > X > 110 nits: factor=26.6  ==>  (187 nits) * (26.6) = AlsSens_Value( 4974= 0x136E);
							< 110nits : factor=27.0  ==>  (110 nits) * (27.0) = AlsSens_Value( 2907= 0x0B9A);		
				*/
				/* { //George_Source
					if( NowAlsSens > 0x3212 )		//0x3212: 500nits
						AlsBrigTarg = 100;
					else if( NowAlsSens > 0x2DC0 )	//0x2DC0: 451nits
						AlsBrigTarg = 90;
					else if( NowAlsSens > 0x2990 )	//0x2990: 408nits
						AlsBrigTarg = 80;
					else if( NowAlsSens > 0x2540 )	//0x2540: 365nits
						AlsBrigTarg = 70;
					else if( NowAlsSens > 0x20E0 )	//0x20E0: 322nits
						AlsBrigTarg = 60;
					else if( NowAlsSens > 0x1C70 )	//0x1C70: 278nits
						AlsBrigTarg = 50;
					else if( NowAlsSens > 0x17F0 )	//0x17F0: 234nits
						AlsBrigTarg = 40;
					else if( NowAlsSens > 0x1360 )	//0x1360: 187nits
						AlsBrigTarg = 30;
					else if( NowAlsSens > 0x0ED0 )	//0x0ED0: 143nits
						AlsBrigTarg = 20;
					else if( NowAlsSens > 0x0A20 )	//0x0A20:  98nits
						AlsBrigTarg = 10;
					else if( NowAlsSens < 0x0A20 )	//0x07D0 )	//0x07D0:  74nits
						AlsBrigTarg = 10;
				}  */

				{ //Adam_Request
					if( NowAlsSens > 0x5034 )		//0x3212: 500nits
						AlsBrigTarg = 100;
					else if( NowAlsSens > 0x4620 )	//0x2DC0: 451nits
						AlsBrigTarg = 90;
					else if( NowAlsSens > 0x3C26 )	//0x2990: 408nits
						AlsBrigTarg = 80;
					else if( NowAlsSens > 0x3220 )	//0x2540: 365nits
						AlsBrigTarg = 70;
					else if( NowAlsSens > 0x2189 )	//0x20E0: 322nits
						AlsBrigTarg = 60;
					else if( NowAlsSens > 0x1E13 )	//0x1C70: 278nits
						AlsBrigTarg = 50;
					else if( NowAlsSens > 0x149A )	//0x17F0: 234nits
						AlsBrigTarg = 40;
					else if( NowAlsSens > 0x0F73 )	//0x1360: 187nits
						AlsBrigTarg = 30;
					else if( NowAlsSens > 0x0A4D )	//0x0ED0: 143nits
						AlsBrigTarg = 20;
					else if( NowAlsSens > 0x0834 )	//0x0A20:  98nits
						AlsBrigTarg = 10;
					else if( NowAlsSens < 0x0834 )	//0x07D0 )	//0x07D0:  74nits
						AlsBrigTarg = 0;
				}

				//==================================== ALSBaseOffsetValue ====================================
				//by ucALSBaseVal Offset (0, 5, 10, ... 100), new add (0~10 steps) to Brightness.
				{					   
					if( AlsBrigTarg + (UserData.ucALSBaseVal/DIVBASE * RATIO )  > 100)			// ALSBaseVal/10 * 1 : reduce Value
						AlsBrigTarg = 100;
					else 
						AlsBrigTarg = AlsBrigTarg + (UserData.ucALSBaseVal/DIVBASE * RATIO );	// RATIO = 1
				}

			}//End if( CntSensStable == 0 )
		}else {
			CntSensStable = CNT_SENS_STABLE;	
			AlsSens_buf   = AlsSens_tmp;
		}
	}//End if(--DeBuncSens == 0)

		
	

	// (3). [OUT-PUT]: Count-out to Reflsh "NowAlsBright" Value.	
	if(--CntBrigStable == 0)	
	{
		CntBrigStable = CNT_BRIG_STABLE;

		if(AlsBrigTarg > NowAlsBright) {
			NowAlsBright++;	
			SetNowALSBrig();
		}else if(AlsBrigTarg < NowAlsBright) {
			NowAlsBright--;
			SetNowALSBrig();
		}else{
			// when "ucALSBaseVal == NowAlsBright" to Dummy!
		}

//	//(4). Update show OSD_Brightness_Bar/Num. (for readyonly)
		if( (OSD_state==OSD_ITEM_1_1_STATE) || (OSD_state==OSD_DIRECT_1_STATE) )
		{									//a. trace_rule: OSDFocusBr() -> OSDShowBrightness(TRUE)
			//OSDShowBrightness(FALSE);		//b. trace_rule: OSDShowDir1()-> OSDShowDialog(OSD_DLG_BRIGHTNESS);
			
			OSDShowALSBV(FALSE);			//a. tacce_rule: OSDFocusBr(), OSDALSBVUp(), OSDALSBVDown() -> OSDShowALSBV(TRUE)
											//b. OSDEnterItm11() -> OSDFocusItm11() -> OSDFocusBr()	-> OSDShowALSBV(TRUE)											
		}

	}//End if(--CntBrigStable == 0)

}



void CM3218_Print(void)
{
//	UCHAR ckDevice=0;	//, tmp=0;
//	static UCHAR i=0;
//	 printf("AlsSens_tmp= %4x, AlsSens_buf= %4x, NowAlsSens= %4x, NowAlsBright=%d, div_ALSBaseVal= %d%\n", AlsSens_tmp, AlsSens_buf, NowAlsSens, (USHRT)NowAlsBright, (USHRT)(div_ALSBaseVal) );	
	
//	ckDevice = NvramCheckDevice(0x90);
//	printf("Ck_Dvi= %d, AlsSens_tmp= %4x, NowAlsSens= %4x, %5u, NowAlsBright=%d \n", (USHRT)ckDevice, AlsSens_tmp, (USHRT)NowAlsSens, NowAlsSens, (USHRT)NowAlsBright );	
//  	printf("ADJ=%d,  ", (USHRT) (UserData.ucALSBaseVal-50)/5 * 1);

//	printf("Ck_Dvi= %d, AlsSens_tmp= %4x, NowAlsSens= %4x, AlsBrigTarg=%d, NowAlsBright=%d \n", (USHRT)ckDevice, AlsSens_tmp, (USHRT)NowAlsSens, (USHRT)AlsBrigTarg, (USHRT)NowAlsBright );	
//printf("Ans= %d\n", (USHRT) ReadIICCM3218ARA(0x18, 0x90) );
//	printf("ucSRMode=%d, bALSOnOff= %d\n" ,(USHRT)UserData.ucSRMode, (USHRT)UserData.bALSOnOff);
}




//	printf("UserData.ucBrightness= %d\n", (USHRT) UserData.ucBrightness);
//	printf("GetBrightness1023()  = %d\n", (USHRT) GetBrightness1023() );
//	printf("GetScalerPWM         = %d\n\n", (USHRT) GetScalerPWM(BKL_PWM_PORT) );




#endif //#if ALS_EnDis == ENABLE