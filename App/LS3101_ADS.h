/******************************************************************************/
/*                    Axiomdisplay CO,, LTD.                                  */
/*                    All Rights Reserved                                     */
/*                    Ambient Light Sensor Device: Use ALLGUY "LS3101" (ADC)  */
/******************************************************************************/
#ifndef __LS3101_H__
#define __LS3101_H__

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************
#include "Typedef.h"

#if (ALS_EnDis == ALSRange)




	#if BRIG_MIN_SEL == BRIG_MIN_10
		#define GetNowAlsBright1023() ( Remap100ToAny(NowAlsBright, 1023 - MIN_BACKLIGHT_VALUE) + MIN_BACKLIGHT_VALUE )	// george: F_ALSBV_04E

	#elif BRIG_MIN_SEL == BRIG_MIN_5
		#define GetNowAlsBright1023() ( Remap100ToAny(NowAlsBright, 1023 - MIN_BACKLIGHT_VALUE) + (MIN_BACKLIGHT_VALUE/2) )	// george: F_ALSBV_04E

	#elif BRIG_MIN_SEL == BRIG_MIN_0
		#define GetNowAlsBright1023() ( Remap100ToAny(NowAlsBright, 1023 - MIN_BACKLIGHT_VALUE) )	// george: F_ALSBV_04E
	#endif

//******************************************************************************
// G L O B A L   D E F I N I T I O N S
//******************************************************************************

//******************************************************************************
// G L O B A L   V A R I A B L E S
//******************************************************************************

//******************************************************************************
// S T A T I C   V A R I A B L E S
//******************************************************************************

//******************************************************************************
// E X T E R N A L   V A R I A B L E   P R O T O T Y P E S
//******************************************************************************
//xxxxxxx no-used *******  extern xdata UCHAR ucALSOnSetBrigVal;	//for replace UserData.ucBrightness to set brightness
extern xdata UCHAR NowAlsBright;


//******************************************************************************
// S T A T I C   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// E X T E R N A L   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
extern void LS3101_ALSOnInit(void);
extern void SetNowALSBrig(void);
extern void LS3101_Process(void);

//extern void LS3101_Print(void);


#endif //#if ALS_EnDis == ENABLE

#endif //__GAMMA_H__
