/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/
#ifndef __USER_SETTING_H__
#define __USER_SETTING_H__

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************
#include "Typedef.h"

//******************************************************************************
// G L O B A L   D E F I N I T I O N S
//******************************************************************************

#define INPUT_SC_VGA    	    0	//v
#define INPUT_SC_VGA1   	    1
#define INPUT_SC_DVI    	    2	//v
#define INPUT_SC_DVI1   	    3
#define INPUT_SC_HDMI   	    4
#define INPUT_SC_HDMI1  	    5	//v
#define INPUT_SC_HDMI2  	    6
#define INPUT_SC_YPbPr  	    7
#define INPUT_SC_YPbPr1 	    8
#define INPUT_SC_DP                 9 
#define NUM_INPUT_SC    	   10
#define INPUT_SC_NULL   	   11


enum {
    OSDLANG_ENGLISH,
    OSDLANG_SPANISH,
    OSDLANG_FRENCH,
    OSDLANG_GERMAN,
    OSDLANG_ITALIAN,
    OSDLANG_PORTUGUESE,
    OSDLANG_RUSSIAN,
    OSDLANG_SCHINESE,
    NUM_OSDLANGS
};

enum {
    DSP_SIZE_FULL,
    DSP_SIZE_SMART,
    DSP_SIZE_43,
    DSP_SIZE_SMART_43,
    NUM_DSP_SIZE
};

enum {
    BKL_CTRL_OFF,
    BKL_CTRL_DCR,
    BKL_CTRL_DBC,
    NUM_BKL_CTRL_SIZE
};
/*
enum {
    INPUT_SC_VGA,
    INPUT_SC_DVI,
    INPUT_SC_HDMI,
    INPUT_SC_YPbPr,
    INPUT_SC_DISPLAYPORT,
    NUM_INPUT_SC
};
*/
enum {
    THR_D_CNV_OFF,
    THR_D_CNV_2D_TO_3D,
    THR_D_CNV_SIDEBYSIDE,
    THR_D_CNV_TOPBOT,
    THR_D_CNV_FRAME_SEQ,
    NUM_THR_D_CNV
};

#ifdef XRev						//150105 mike 
	#define GetBrightness1023() ( Remap100ToAny((100-UserData.ucBrightness), 1023 - MIN_BACKLIGHT_VALUE) + MIN_BACKLIGHT_VALUE )
#else 
	#if BRIG_MIN_SEL == BRIG_MIN_10
		#define GetBrightness1023() ( Remap100ToAny(UserData.ucBrightness, 1023 - MIN_BACKLIGHT_VALUE) + MIN_BACKLIGHT_VALUE )

	#elif BRIG_MIN_SEL == BRIG_MIN_5
		#define GetBrightness1023() ( Remap100ToAny(UserData.ucBrightness, 1023 - MIN_BACKLIGHT_VALUE) + (MIN_BACKLIGHT_VALUE/2) )

	#elif BRIG_MIN_SEL == BRIG_MIN_1
		#define GetBrightness1023() ( Remap100ToAny(UserData.ucBrightness, 1023 - MIN_BACKLIGHT_VALUE) + 5 )


	#elif BRIG_MIN_SEL == BRIG_MIN_0
		#define GetBrightness1023() ( Remap100ToAny(UserData.ucBrightness, 1023 - MIN_BACKLIGHT_VALUE)  )
	#endif
#define GetALSBaseValue1023() ( Remap100ToAny(UserData.ucALSBaseVal, 1023 - MIN_BACKLIGHT_VALUE) + MIN_BACKLIGHT_VALUE )	// george: F_ALSBV_04E
#endif 

#define GetContrast255()   (Remap100To200(UserData.ucContrast) + MIN_CONTRAST_VALUE)
#define GetROffset255() (Remap100To200(UserData.ucUserROffset) + MIN_OFFSET_VALUE)
#define GetGOffset255() (Remap100To200(UserData.ucUserGOffset) + MIN_OFFSET_VALUE)
#define GetBOffset255() (Remap100To200(UserData.ucUserBOffset) + MIN_OFFSET_VALUE)
//------------------------------------------------------------------------------//140428 mike
#define GetRGain255() (Remap100ToAny(UserData.ucUserRGain,(140-MIN_GAIN_VALUE)) + MIN_GAIN_VALUE)
#define GetGGain255() (Remap100ToAny(UserData.ucUserGGain,(140-MIN_GAIN_VALUE)) + MIN_GAIN_VALUE)
#define GetBGain255() (Remap100ToAny(UserData.ucUserBGain,(140-MIN_GAIN_VALUE)) + MIN_GAIN_VALUE)
//------------------------------------------------------------------------------
#define IsOverScan() (UserData.bOverScan)

//******************************************************************************
// E X T E R N A L   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
extern void UserSetBrightness(void);
extern void UserSetContrast(void);
extern void UserSetPhase(void);
extern void UserSetPhase100(UCHAR value);
extern void UserSetClock(void);
extern void UserSetClock100(UCHAR value);
extern void UserSetHPosition(void);
extern void UserSetHPosn100(UCHAR value);
extern void UserSetVPosition(void);
extern void UserSetVPosn100(UCHAR value);
extern void UserSetADCGainOffset(void);
extern void UserSetColorTemp(void);
extern void UserSetRGain(void);
extern void UserSetGGain(void);
extern void UserSetBGain(void);
extern void UserSetROffset(void);
extern void UserSetGOffset(void);
extern void UserSetBOffset(void);
extern void UserSetOSDH(void);
extern void UserSetOSDV(void);
extern void UserSetTransparent(void);
extern void UserSetTimeout(void);
extern void UserSetOSDRotation(void);
extern void UserSetLanguage(void);
extern void UserSetVolume(void);
extern void UserSetAudioMute(void);
extern void UserSetDCR(void);
extern void UserSetLD(void);
extern void UserSetAspectRatio(void);
//extern void UserSetOverScan(void);
extern void UserSetGamma(void);


#if ALS_EnDis == ALSMODE
	extern void UserSetALSMode(void);
#elif ALS_EnDis == ALSOffSET	
	extern void UserSetALSOnOff(void);			// george: F_ALSOnOff_04E
	/* extern void UserSetALSBaseVal(void);		// george: F_ALSBV_04E */

#elif ALS_EnDis == ALSRange
	extern void UserSetALSOnOff(void);			
#else	//Normal

#endif	//#if ALS_EnDis == ENABLE


#if TOUCH_EnDis == ENABLE
	extern void UserSetTouch(void);				// george: F_Touch_04E
#endif //#if TOUCH_EnDis == ENABLE

extern void UserSetOD(void);
extern void UserRecallConfiguration(void);
extern void UserRecallColor();
extern void UserRecallHVPosition(void);
extern void UserPerformAutoTune(void);
extern void UserSetBF(void);
extern void UserSetSR(void);
extern void UserSet2DTo3DMode(void);
extern void UserSet2DTo3DAdaptive(void);
extern void UserSet2DTo3DDepth(void);
extern void UserSet2DTo3DView(void);
extern void UserSet3DLRSwap(void);
extern void UserSet3DTo2D(void);
extern void UserSetInputSource(void);
extern void UserSetAudioChannel(void);
extern UCHAR UserGetInputSource(void);
extern UCHAR UserGetNormalPhase(void);
extern UCHAR UserGetNormalClock(void);
extern UCHAR UserGetNormalHPosn(void);
extern UCHAR UserGetNormalVPosn(void);
extern UCHAR UserGetNormal2DTo3DDpth(void);
extern UCHAR UserGetNormal2DTo3DView(void);
extern UCHAR GetInputPortName(UCHAR PortIdex);
extern UCHAR GetInputPortIndex(UCHAR PortName);

#endif //__USER_SETTING_H__
