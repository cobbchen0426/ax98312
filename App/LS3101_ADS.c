/******************************************************************************/
/*                    Axiomdisplay CO,, LTD.                                  */
/*                    All Rights Reserved                                     */
/*                    Ambient Light Sensor Device: Use ALLGUY "LS3101" (ADC)  */
/******************************************************************************/

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************
#include "Include.h"
/*
SetBrightness()									: void BacklightOn() / BacklightOff(set SetBrightness:0),  SetBrightnessPWMMax(PreSetBrightnessPWMMax=TRUE, SetBrightness())
SetScalerPWM(BKL_PWM_PORT, (unsigned short)br); : SYSAPI_SetInverterVal(), SetBrightness(), PanelPowerOffSequence(set SetScalerPWM:0)
SYSAPI_SetInverterVal()							: APPInitSystem(), FactorySetValue(), UserRecallConfiguration()
SetBrightnessPWMMax(PreSetBrightnessPWMMax=TRUE, SetBrightness()):  APPTimerRoutine() 


tack: SetScalerPWM()
	  * DisableDCR() -> UserSetBrightness();

	  (at BoardConfig.h) MCU_ADC_CON_DEFAULT
	    McuInitialize()-> McuInitADC() -> McuEnableADC(MCU_ADC_CON_DEFAULT);
 	  * McuInitialize()-> McuCheckPwrStable() -> McuCheck5V() -> McuStartADC()

*/


#if (ALS_EnDis == ALSRange)
//******************************************************************************
// M A C R O   D E F I N I T I O N S
//******************************************************************************
#define BOUNCE_FST_CNT		5		/* when bALSOnOff switch "ON" at first-timing to set BOUNCE */
#define BOUNCE_CNT			150		/* Count-out to Reflsh "NowAlsBright" value action ++ or --.: [Prefer-Range]: 100:256ms, (200:512ms), 250:640ms */
#define CNT_SENS_STABLE		1		/* when ALSDATA_TOL=0x00ff, [Prefer-Range]: 0~2 */
#define CNT_BRIG_STABLE		20		//20

#define ALSDATA_TOL			0x05	/* get ALSens_tmp Tolerance Range */

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
xdata UCHAR CntSensStable;
xdata UCHAR CntBrigStable;		/* [OUT-PUT] tmpALSdata <-> DeBounceALS <-> ALSdata(stable-value) */

xdata UCHAR	NowAlsSens, AlsSens_tmp, AlsSens_buf; // [Input]
xdata UCHAR NowAlsBright, AlsBrigTarg;			  // [Output]


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



/**************************************************************************//**
 * Set ALS Mode.
 * @param ALS mode.
 ******************************************************************************/
void LS3101_ALSOnInit(void)				//george: at OSDALSOnOffUp() or OSDALSOnOffDown()  used.
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


void LS3101_ADCReadData()
{
		McuPowerUpADC();
		McuStartADC();
		McuWaitADCComplete();

		//McuPowerDownADC();
		AlsSens_tmp = McuGetADC(LS3101_ADC);
	 	McuPowerDownADC();


}



void LS3101_Process(void)
{
	
	// if ALS: LS3101 OFF return;
	if(UserData.bALSOnOff == OFF)	return;

	//(A) Check Device		:  ADC don't need check device.
	//(B) LS3101 Initialize	:  ADC no I2C don't need init.


	//(C) (at SS=2) LS3101 Read Data  //Delay time by ADC ...//(need Delay > 400ms)
	// (1). [IN-PUT] : Count-out to Reflish "ALSens" Value.  to IIC none busy.	
	if(--DeBuncSens == 0)
	{	
		DeBuncSens = BOUNCE_CNT;

		ResetWDTimer();				
		LS3101_ADCReadData();

		if( AlsSens_tmp <= ALSDATA_TOL ) 				// if TRUE: limit AlsSens_tmp = ALSDATA_TOL;
			AlsSens_tmp = ALSDATA_TOL;
		else if( AlsSens_tmp > (0x7f-ALSDATA_TOL) ) 	// if TRUE: limit AlsSens_tmp = (0x7f-ALSDATA_TOL);
			AlsSens_tmp = (0x7f-ALSDATA_TOL);
		
		if( (AlsSens_buf+ALSDATA_TOL >= AlsSens_tmp ) && (AlsSens_tmp >= AlsSens_buf-ALSDATA_TOL) ) 	// if TRUE: the "AlsSens_tmp" Value Stable.
		{

			if( --CntSensStable == 0 ) 						// [ OK ]: ths "CntSensStable" times equal  "CNT_SENS_STABLE-1", then set "NowAlsSens" Value Stable.
			{
				CntSensStable = CNT_SENS_STABLE;
				NowAlsSens    = AlsSens_buf;


	// (2). [CONVERTER]:
				{ //George_Source
/*					if( NowAlsSens > 125 )		
						AlsBrigTarg = 100;			// ADC_115_steps = 240 ~370 Lux
					else if( NowAlsSens > 100 )		// ADC_110_steps = 200 Lux
						AlsBrigTarg = 90;
					else if( NowAlsSens > 90 )	
						AlsBrigTarg = 80;
					else if( NowAlsSens > 80 )	
						AlsBrigTarg = 70;
					else if( NowAlsSens > 70 )	
						AlsBrigTarg = 60;
					else if( NowAlsSens > 60 )	
						AlsBrigTarg = 50;
					else if( NowAlsSens > 50 )	
						AlsBrigTarg = 40;
					else if( NowAlsSens > 40 )	
						AlsBrigTarg = 30;
					else if( NowAlsSens > 30 )	
						AlsBrigTarg = 20;
					else if( NowAlsSens > 20 )	
						AlsBrigTarg = 10;
					else if( NowAlsSens < 10 )	
						AlsBrigTarg = 0;
*/


					// by RK = 1k ohm ( max. 900 lux = 1.3V)
					if( NowAlsSens > 38 )		
						AlsBrigTarg = 100;			// ADC_115_steps = 240 ~370 Lux
					else if( NowAlsSens > 34 )		// ADC_110_steps = 200 Lux
						AlsBrigTarg = 90;
					else if( NowAlsSens > 30 )	
						AlsBrigTarg = 80;
					else if( NowAlsSens > 26 )	
						AlsBrigTarg = 70;
					else if( NowAlsSens > 23 )	
						AlsBrigTarg = 60;
					else if( NowAlsSens > 19 )	
						AlsBrigTarg = 50;
					else if( NowAlsSens > 15 )	
						AlsBrigTarg = 40;
					else if( NowAlsSens > 12 )	
						AlsBrigTarg = 30;
					else if( NowAlsSens > 8 )	
						AlsBrigTarg = 20;
					else if( NowAlsSens >= 4 )	
						AlsBrigTarg = 10;
					else if( NowAlsSens < 4 )	
						AlsBrigTarg = 0;


					// by RK = 10k ohm ( max. 250 lux = 2.5V)
/*					if( NowAlsSens > 113)	//> 120 )		
						AlsBrigTarg = 100;			// ADC_115_steps = 240 ~370 Lux
					else if( NowAlsSens > 108 )		// ADC_110_steps = 200 Lux
						AlsBrigTarg = 90;
					else if( NowAlsSens > 96 )	
						AlsBrigTarg = 80;
					else if( NowAlsSens > 85 )	
						AlsBrigTarg = 70;
					else if( NowAlsSens > 73 )	
						AlsBrigTarg = 60;
					else if( NowAlsSens > 62 )	
						AlsBrigTarg = 50;
					else if( NowAlsSens > 50 )	
						AlsBrigTarg = 40;
					else if( NowAlsSens > 38 )	
						AlsBrigTarg = 30;
					else if( NowAlsSens > 27 )	
						AlsBrigTarg = 20;
					else if( NowAlsSens > 15 )	
						AlsBrigTarg = 10;
					else if( NowAlsSens < 15 )	
						AlsBrigTarg = 0;			
*/
				}
				//-------------------------------------------
						/*  AlsBrigTarg fine-tuning value.  */
				{


					if(AlsBrigTarg >= UserData.ucALSBrigMAX)	//TRUE: limit AlsBrigTarg MAX-Value by ucALSBrigMAX.
						AlsBrigTarg = UserData.ucALSBrigMAX;
					if(AlsBrigTarg <= UserData.ucALSBrigMIN)	//TRUE: limit AlsBrigTarg MAX-Value by ucALSBrigMIN.
						AlsBrigTarg = UserData.ucALSBrigMIN;
				}
				//-----------------------------------------
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

	//(4). Update show OSD_Brightness_Bar/Num. (for readyonly)
		if( (OSD_state==OSD_ITEM_1_1_STATE) || (OSD_state==OSD_DIRECT_1_STATE) )
		{									//a. trace_rule: OSDFocusBr() -> OSDShowBrightness(TRUE)
			OSDShowBrightness(FALSE);		//b. trace_rule: OSDShowDir1()-> OSDShowDialog(OSD_DLG_BRIGHTNESS);

		}

	}//End if(--CntBrigStable == 0)

}//End void LS3101_Process().







//void LS3101_Print(void)
//{

//	printf("AlsSens_tmp= %4x, NowAlsSens= %4x, %5u, NowAlsBright=%x \n", (USHRT)AlsSens_tmp, (USHRT)NowAlsSens, NowAlsSens, (USHRT)NowAlsBright );	
//printf("AlsBrigTarg=%d  ", (USHRT)AlsBrigTarg);	

//	printf("AlsSens_tmp= %d, NowAlsBright=%d \n", (USHRT)AlsSens_tmp, (USHRT)NowAlsBright );	


//LS3101_ADCReadData();
//printf("AlsSens_tmp= %3d, ", (USHRT) AlsSens_tmp);


//printf("ucALSBrigMAX= %d,  ucALSBrigMIN= %d, bTouchOnOff= %d, bALSOnOff= %d, AA=%d\n", (USHRT) UserData.ucALSBrigMAX, (USHRT) UserData.ucALSBrigMIN, (USHRT) UserData.bTouchOnOff, (USHRT) UserData.bALSOnOff, (USHRT)UserData.AA);
//printf("ucALSBrigMAX= %d,  ucALSBrigMIN= %d, bTouchOnOff= %d, bALSOnOff= %d\n", (USHRT) UserData.ucALSBrigMAX, (USHRT) UserData.ucALSBrigMIN, (USHRT) UserData.bTouchOnOff, (USHRT) UserData.bALSOnOff);
//}	

#endif //#if ALS_EnDis == ENABLE