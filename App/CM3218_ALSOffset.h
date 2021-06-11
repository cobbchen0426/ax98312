/******************************************************************************/
/*                    Axiomdisplay CO,, LTD.                                  */
/*                    All Rights Reserved                                     */
/*                    Ambient Light Sensor Device: Use CAPELLA "CM3218"(I2C)  */
/******************************************************************************/
#ifndef __CM3218_H__
#define __CM3218_H__

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************
#include "Typedef.h"

#if (ALS_EnDis == ALSOffSET)

#define GetNowAlsBright1023() ( Remap100ToAny(NowAlsBright, 1023 - MIN_BACKLIGHT_VALUE) + MIN_BACKLIGHT_VALUE )	// george: F_ALSBV_04E

#define DIVBASE		5	// 5: (100/5)=20 steps,  10: (100/10)=10 steps. 
#define RATIO 		1   // 1

//#define GetALSBaseValue1023() ( Remap100ToAny(UserData.ucALSBaseVal, 1023 - MIN_BACKLIGHT_VALUE) + MIN_BACKLIGHT_VALUE )	// george: F_ALSBV_04E
//#define GetNowAlsBrig1023() ( Remap100ToAny(NowAlsBright, 1023 - MIN_BACKLIGHT_VALUE) + MIN_BACKLIGHT_VALUE )	// george: F_ALSBV_04E
//  #define Remap100ToAny(a,b) (((ULONG)(a)*(b)+50)/100)

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
extern xdata USHRT CkDevice_timer;

//******************************************************************************
// S T A T I C   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// E X T E R N A L   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
extern void CM3218Initialize(void);
extern void CM3218_BacklightOn_Init(void);
extern void CM3218_ALSOnInit(void);
extern void SetNowALSBrig(void);
extern void CM3218_Process(void);

//extern void Analy_CMD(void);
extern void CM3218_Print(void);



#endif //#if ALS_EnDis == ENABLE

#endif //__GAMMA_H__
