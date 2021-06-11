/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/
#ifndef __OSD_VIEW_H__
#define __OSD_VIEW_H__

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************
#include "Typedef.h"
#include "OSDFont.h"

//******************************************************************************
// G L O B A L   D E F I N I T I O N S
//******************************************************************************
#define OSDFocusItm11 OSDFocusBr
#define OSDFocusItm12 OSDFocusCn
#define OSDFocusItm13 OSDFocusSR		//                     original-is : OSDFocusGamma

#if ALS_EnDis == ALSMODE
   #define OSDFocusItm14 OSDFocusALSMode	//george: F_ALSOnOff_03A    original-is : OSDFocusDCR
#elif ALS_EnDis == ALSOffSET	
	#define OSDFocusItm14 OSDFocusALSOnOff	//george: F_ALSOnOff_03A    original-is : OSDFocusDCR
#elif ALS_EnDis == ALSRange
	#define OSDFocusItm14 OSDFocusALSOnOff	
#else	//Normal

#endif	//#if ALS_EnDis == ENABLE


//#define OSDFocusItm15 OSDFocusALSBV 	//george: F_ALSBV_03A
//gg_old #define OSDFocusItm16 OSDFocusTouch 	//george: F_Touch_03A  original-is : ALS_ OSDFocusSR
/// #define OSDFocusItm17 OSDFocusALS	// george_Item17 

#define OSDFocusItm21 OSDFocusPhase
#define OSDFocusItm22 OSDFocusClock
#define OSDFocusItm23 OSDFocusHPos
#define OSDFocusItm24 OSDFocusVPos
#define OSDFocusItm31 OSDFocusClrTmp
#define OSDFocusItm32 OSDFocusRGain
#define OSDFocusItm33 OSDFocusGGain
#define OSDFocusItm34 OSDFocusBBain
#define OSDFocusItm41 OSDFocusOSDHPos
#define OSDFocusItm42 OSDFocusOSDVPos
#define OSDFocusItm43 OSDFocusOSDTran
#define OSDFocusItm44 OSDFocusTimer
//#define OSDFocusItm45 OSDFocusOSDRotation
//-----------------------------------------

#define OSDFocusItm51 OSDFocusLang
#define OSDFocusItm52 OSDFocusVolume
#define OSDFocusItm53 OSDFocusMute						
#define OSDFocusItm54 OSDFocusInput
//#define OSDFocusItm55 OSDFocusOverscan
//#define OSDFocusItm56 OSDFocusOD
#define OSDFocusItm57 OSDFocusReset	

#if TOUCH_EnDis == ENABLE
	#define OSDFocusItm58 OSDFocusTouch	//gg_new
#endif //#if TOUCH_EnDis == ENABLE

#if ENABLE_ASPECT_RATIO == ON		//george 20160217
	#define OSDFocusItm59 OSDFocusAspRatio	
#endif

//------------------------------------------
#define OSDUpItm11    OSDBrightnessUp
#define OSDDnItm11    OSDBrightnessDown
#define OSDUpItm12    OSDContrastUp
#define OSDDnItm12    OSDContrastDown
#define OSDUpItm13    OSDSRUp		//						original-is : OSDGammaUp
#define OSDDnItm13    OSDSRDown		//						original-is : OSDGammaDown

#if ALS_EnDis == ALSMODE
	#define OSDUpItm14    OSDALSModeUp		
	#define OSDDnItm14    OSDALSModeDown	
#elif ALS_EnDis == ALSOffSET	
	#define OSDUpItm14    OSDALSOnOffUp		//george: F_ALSOnOff_04C	 	original-is : OSDDCRUp
	#define OSDDnItm14    OSDALSOnOffDown	//george: F_ALSOnOff_04D	 	original-is : OSDDCRDown
#elif ALS_EnDis == ALSRange
	#define OSDUpItm14    OSDALSOnOffUp		
	#define OSDDnItm14    OSDALSOnOffDown	
#else	//Normal

#endif	//#if ALS_EnDis == ENABLE


//#define OSDUpItm15    OSDALSBVUp		//george: F_ALSBV_04C
//#define OSDDnItm15    OSDALSBVDown		//george: F_ALSBV_04D
//gg_old #define OSDUpItm16    OSDTouchUp		//george: F_Touch_04C  	original-is : OSDSRUp
//gg_old #define OSDDnItm16    OSDTouchDown		//george: F_Touch_04D  	original-is : OSDSRDown

/// #define OSDUpItm17    OSDALSUp		// george_Item17
/// #define OSDDnItm17    OSDALSDown	// george_Item17


#define OSDUpItm21    OSDPhaseUp
#define OSDDnItm21    OSDPhaseDown
#define OSDUpItm22    OSDClockUp
#define OSDDnItm22    OSDClockDown
#define OSDUpItm23    OSDHPositionDown
#define OSDDnItm23    OSDHPositionUp
#define OSDUpItm24    OSDVPositionUp
#define OSDDnItm24    OSDVPositionDown
#define OSDUpItm31    OSDColorUserRGBUp				
#define OSDDnItm31    OSDColorUserRGBDown			
#define OSDUpItm32    OSDRGainUp
#define OSDDnItm32    OSDRGainDown
#define OSDUpItm33    OSDGGainUp
#define OSDDnItm33    OSDGGainDown
#define OSDUpItm34    OSDBGainUp
#define OSDDnItm34    OSDBGainDown
#define OSDUpItm41    OSDHUp
#define OSDDnItm41    OSDHDown
#define OSDUpItm42    OSDVUp
#define OSDDnItm42    OSDVDown
#define OSDUpItm43    OSDTransparentUp
#define OSDDnItm43    OSDTransparentDown
#define OSDUpItm44    OSDTimeoutUp
#define OSDDnItm44    OSDTimeoutDown
#define OSDUpItm45    OSDRotationUp
#define OSDDnItm45    OSDRotationDown
//-------------------------------------				
#define OSDUpItm51    OSDLanguageUp
#define OSDDnItm51    OSDLanguageDown
#define OSDUpItm52    OSDVolumeUp
#define OSDDnItm52    OSDVolumeDown
#define OSDUpItm53    OSDAudioMuteUp
#define OSDDnItm53    OSDAudioMuteDown
#define OSDUpItm54    OSDInputSourceUp
#define OSDDnItm54    OSDInputSourceDown
//#define OSDUpItm55    OSDOverScanUp
//#define OSDDnItm55    OSDOverScanDown
//#define OSDUpItm56    OSDODUp
//#define OSDDnItm56    OSDODDown
#define OSDUpItm57    OSDResetUp
#define OSDDnItm57    OSDResetDown

#if TOUCH_EnDis == ENABLE
	#define OSDUpItm58    OSDTouchUp  	//gg_new
	#define OSDDnItm58    OSDTouchDown	//gg_new
#endif //#if TOUCH_EnDis == ENABLE

#if ENABLE_ASPECT_RATIO == ON		//george 20160217
	#define OSDUpItm59    OSDAspectRatioUp
	#define OSDDnItm59    OSDAspectRatioDown
#endif 
//-------------------------------------
#define OSDFocusFunc1 OSDFocus3DCnv
#define OSDFuncDown1  OSD2Dto3DFmtDown
#define OSDFuncUp1    OSD2Dto3DFmtUp
#define OSDFocusFunc2 OSDFocus2Dto3DAdpt
#define OSDFuncDown2  OSD2Dto3DAdptDown 
#define OSDFuncUp2    OSD2Dto3DAdptUp   
#define OSDFocusFunc3 OSDFocus2Dto3DDepth
#define OSDFuncDown3  OSD2Dto3DDepthDown
#define OSDFuncUp3    OSD2Dto3DDepthUp
#define OSDFocusFunc4 OSDFocus2Dto3DView
#define OSDFuncDown4  OSD2Dto3DViewDown
#define OSDFuncUp4    OSD2Dto3DViewUp
#define OSDFocusFunc5 OSDFocus3DLRSwap
#define OSDFuncDown5  OSD3DLRSwapDown
#define OSDFuncUp5    OSD3DLRSwapUp
#define OSDFocusFunc6 OSDFocus3DTo2D
#define OSDFuncDown6  OSD3DTo2DDown
#define OSDFuncUp6    OSD3DTo2DUp

#define OSDUpDir1     OSDBrightnessUp
#define OSDDnDir1     OSDBrightnessDown
#define OSDUpDir2     OSDContrastUp
#define OSDDnDir2     OSDContrastDown
#define OSDUpDir3     OSDVolumeUp
#define OSDDnDir3     OSDVolumeDown
#define OSDUpOpt1     OSDBFMenuITMUp
#define OSDDnOpt1     OSDBFMenuITMDn
#define OSDUpOpt2     OSDSourceMenuITMUp
#define OSDDnOpt2     OSDSourceMenuITMDn
#define OSDConfirmItm11   OSDDummyFunction
#define OSDConfirmItm12   OSDDummyFunction
#define OSDConfirmItm13   OSDDummyFunction
#define OSDConfirmItm14   OSDDummyFunction	//george: F_ALSOnOff_04B
#define OSDConfirmItm15   OSDDummyFunction	//george: F_ALSBV_04B
//gg_old  #define OSDConfirmItm16   OSDDummyFunction	//george: F_Touch_04B
/// #define OSDConfirmItm17   OSDDummyFunction	// george_Item17

#define OSDConfirmItm21   OSDDummyFunction
#define OSDConfirmItm22   OSDDummyFunction
#define OSDConfirmItm23   OSDDummyFunction
#define OSDConfirmItm24   OSDDummyFunction
#define OSDConfirmItm31   OSDDummyFunction
#define OSDConfirmItm32   OSDDummyFunction
#define OSDConfirmItm33   OSDDummyFunction
#define OSDConfirmItm34   OSDDummyFunction
#define OSDConfirmItm41   OSDDummyFunction
#define OSDConfirmItm42   OSDDummyFunction
#define OSDConfirmItm43   OSDDummyFunction
#define OSDConfirmItm44   OSDDummyFunction
//#define OSDConfirmItm45   OSDConfirmOSDRotation
//--------------------------------------------		
#define OSDConfirmItm51   OSDConfirmLanguage		
#define OSDConfirmItm52   OSDDummyFunction			 
#define OSDConfirmItm53   OSDDummyFunction			
#define OSDConfirmItm54   OSDConfirmInput			
#define OSDConfirmItm55   OSDDummyFunction
#define OSDConfirmItm56   OSDDummyFunction
#define OSDConfirmFunc1   OSDConfirm3DCnvMode
#define OSDConfirmFunc2   OSDDummyFunction
#define OSDConfirmFunc3   OSDDummyFunction
#define OSDConfirmItm57   OSDConfirmRecall			
#define OSDConfirmItm58   OSDDummyFunction	//gg_new			
#define OSDConfirmItm59   OSDDummyFunction	//george 20160217			

//--------------------------------------------
#define OSDConfirmOpt1     OSDDummyFunction
#define OSDConfirmOpt2     OSDConfirmInput

///////////////////////////////////////////////////
enum {
    CHINESE_TABLE = 0xf0,
    COMMON_TABLE = 0xf1
};

//******************************************************************************
// E X T E R N A L   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
extern void OSDTurnOnOSD(void);
extern void OSDShowMainMenu(void);
extern void OSDCloseMainMenu(void);
extern void OSDShowMainIcon(UCHAR id, UCHAR act);
extern void OSDSelectMainItem(UCHAR id);
extern void OSDUnselectMainItem(UCHAR id);
extern void OSDShowSubMenu(UCHAR id);
extern void OSDClearSubmenu(void);
extern void OSDFocusMain(UCHAR id);
extern void OSDFocusSub(UCHAR id);
extern void OSDUnselectSubItem(UCHAR id);
extern void OSDSelectSubItem(UCHAR id);
extern void OSDExitItms(UCHAR pg, UCHAR itm);
extern BOOL OSDIsMainItemValid(UCHAR id);
extern BOOL OSDIsSubItemValid(UCHAR id);

extern void OSDShowFuncMenu(void);
extern void OSDCloseFuncMenu(void);
extern void OSDClearFuncMenu(void);
extern void OSDFocusFuncMenu(UCHAR id);
extern void OSDShowFuncItems(void);
extern void OSDSelectFuncItem(UCHAR id);
extern void OSDUnselectFuncItem(UCHAR id);
extern BOOL OSDIsFuncItemValid(UCHAR id);

extern BOOL OSDUserUpdate(void);
extern BOOL OSDTmgUpdate(void);
extern BOOL OSDSysUpdate(void);
extern BOOL OSDCalUpdate(void);

extern void OSDClosed(void);
extern void OSDInitialize(BOOL bForceInit);
extern void OSDInitFrame(UCHAR osdw, UCHAR osdh, USHRT clr);
extern void OSDMovePosition(void);

extern void OSDShowNum(UCHAR x, UCHAR y, UCHAR value);
extern void OSDShowSliderBar(UCHAR x, UCHAR y, UCHAR value);

extern void OSDFocusBr(void);
extern void OSDFocusCn(void);
//extern void OSDFocusGamma(void);


#if ALS_EnDis == ALSMODE
	extern void OSDFocusALSMode(void);	

#elif ALS_EnDis == ALSOffSET	
	extern void OSDFocusALSOnOff(void);	//george: F_ALSOnOff_03A
	extern void OSDFocusALSBV(void);	//george: F_ALSBV_03A

#elif ALS_EnDis == ALSRange
	extern void OSDFocusALSOnOff(void);	

#else	//Normal

#endif	//#if ALS_EnDis == ENABLE



#if TOUCH_EnDis == ENABLE
	extern void OSDFocusTouch(void);	//george: F_Touch_03A
#endif //#if TOUCH_EnDis == ENABLE



/// extern void OSDFocusGItem16(void);	// george_Item16
/// extern void OSDFocusGItem17(void);	// george_Item17

extern void OSDFocusSR(void);
extern void OSDFocusPhase(void);
extern void OSDFocusClock(void);
extern void OSDFocusHPos(void);
extern void OSDFocusVPos(void);
extern void OSDFocusClrTmp(void);
extern void OSDFocusRGain(void);
extern void OSDFocusGGain(void);
extern void OSDFocusBBain(void);
extern void OSDFocusOSDHPos(void);
extern void OSDFocusOSDVPos(void);
extern void OSDFocusOSDTran(void);
extern void OSDFocusTimer(void);
//extern void OSDFocusOSDRotation(void);
extern void OSDFocusLang(void);
//-----------------------------------
extern void OSDFocusVolume(void);			
//-----------------------------------
extern void OSDFocusMute(void);
extern void OSDFocusInput(void);
//extern void OSDFocusDCR(void);

#if ENABLE_ASPECT_RATIO == ON		//george 20160217
	extern void OSDFocusAspRatio(void);
#endif

//extern void OSDFocusOverscan(void);
//extern void OSDFocusOD(void);
extern void OSDFocusReset(void);
extern void OSDFocus3DCnv(void);
extern void OSDFocus2Dto3DAdpt(void);
extern void OSDFocus2Dto3DDepth(void);
extern void OSDFocus2Dto3DView(void);
extern void OSDFocus3DLRSwap(void);
extern void OSDFocus3DTo2D(void);

extern void OSDShowResolution(UCHAR x, UCHAR y);
extern void OSDShowBrightness(UCHAR redraw);
extern void OSDShowContrast(UCHAR redraw);
extern void OSDShowVolume(UCHAR redraw);
//extern void OSDShowGamma(UCHAR redraw);

#if ALS_EnDis == ALSMODE
	extern void OSDShowALSMode(UCHAR redraw);		// george: F_ALSBV_03B
#elif ALS_EnDis == ALSOffSET	
	extern void OSDShowALSOnOff(UCHAR redraw);		// george: F_ALSOnOff_03B
	extern void OSDShowALSBV(UCHAR redraw);		// george: F_ALSBV_03B

#elif ALS_EnDis == ALSRange
	extern void OSDShowALSOnOff(UCHAR redraw);		

#else	//Normal

#endif	//#if ALS_EnDis == ENABLE


#if TOUCH_EnDis == ENABLE
	extern void OSDShowTouch(UCHAR redraw);			// goerge: F_Touch_03B
#endif //#if TOUCH_EnDis == ENABLE


/// extern void OSDShowGItem16(UCHAR redraw);	// george_Item16
/// extern void OSDShowGItem17(UCHAR redraw);	// george_Item17

#if ENABLE_SR
extern void OSDShowSR(UCHAR redraw);
#endif
extern void OSDShowPhase(UCHAR redraw);
extern void OSDShowClock(UCHAR redraw);
extern void OSDShowHPos(UCHAR redraw);
extern void OSDShowVPos(UCHAR redraw);
extern void OSDShowClrTmp(UCHAR redraw);
extern void OSDShowRGain(UCHAR redraw);
extern void OSDShowGGain(UCHAR redraw);
extern void OSDShowBGain(UCHAR redraw);
extern void OSDShowOSDHPos(UCHAR redraw);
extern void OSDShowOSDVPos(UCHAR redraw);
extern void OSDShowOSDTran(UCHAR redraw);
extern void OSDShowTimer(UCHAR redraw);
//extern void OSDShowOSDRotation(UCHAR redraw);
extern void OSDShowLang(UCHAR redraw);
extern void OSDShowThrDCnvMenu(UCHAR redraw);
extern void OSDShow2Dto3DAdpt(UCHAR redraw);
extern void OSDShow2Dto3DDepth(UCHAR redraw);
extern void OSDShow2Dto3DView(UCHAR redraw);
extern void OSDShow3DLRSwap(UCHAR redraw);
extern void OSDShow3DTo2D(UCHAR redraw);
extern void OSDShowMute(UCHAR redraw);
extern void OSDShowInput(UCHAR redraw);
//extern void OSDShowDCR(UCHAR redraw);

#if ENABLE_ASPECT_RATIO == ON		//george 20160217
	extern void OSDShowAspRatio(UCHAR redraw);
#endif

//extern void OSDShowOverScan(UCHAR redraw);
//extern void OSDShowOD(UCHAR redraw);
extern void OSDShowReset(UCHAR redraw);

extern void OSDBrightnessUp(void);
extern void OSDBrightnessDown(void);
extern void OSDContrastUp(void);
extern void OSDContrastDown(void);
extern void OSDVolumeUp(void);
extern void OSDVolumeDown(void);
//extern void OSDGammaUp(void);
//extern void OSDGammaDown(void);


#if ALS_EnDis == ALSMODE
	extern void OSDALSModeUp(void);		//george: 
	extern void OSDALSModeDown(void);		//george: 
#elif ALS_EnDis == ALSOffSET	
	extern void OSDALSOnOffUp(void);		//george: F_ALSOnOff_04C
	extern void OSDALSOnOffDown(void);		//george: F_ALSOnOff_04D
	
	extern void OSDALSBVUp(void);			//george: F_ALSBV_04C
	extern void OSDALSBVDown(void);			//george: F_ALSBV_04D

#elif ALS_EnDis == ALSRange
	extern void OSDALSOnOffUp(void);		//george: F_ALSOnOff_04C
	extern void OSDALSOnOffDown(void);		//george: F_ALSOnOff_04D

#else	//Normal

#endif	//#if ALS_EnDis == ENABLE


#if TOUCH_EnDis == ENABLE
	extern void OSDTouchUp(void);			//george: F_Touch_04C
	extern void OSDTouchDown(void);			//george: F_Touch_04D
#endif //#if TOUCH_EnDis == ENABLE

/// extern void OSDGItem16Up(void);		// george_Item16
/// extern void OSDGItem16Down(void);	// george_Item16

/// extern void OSDGItem17Up(void);		// george_Item17
/// extern void OSDGItem17Down(void);	// george_Item17

extern void OSDSRUp(void);
extern void OSDSRDown(void);
extern void OSDPhaseUp(void);
extern void OSDPhaseDown(void);
extern void OSDClockUp(void);
extern void OSDClockDown(void);
extern void OSDHPositionUp(void);
extern void OSDHPositionDown(void);
extern void OSDVPositionUp(void);
extern void OSDVPositionDown(void);
extern void OSDColorTempUp(void);
extern void OSDColorTempDown(void);

extern void OSDRGainUp(void);
extern void OSDRGainDown(void);
extern void OSDGGainUp(void);
extern void OSDGGainDown(void);
extern void OSDBGainUp(void);
extern void OSDBGainDown(void);
extern void OSDHUp(void);
extern void OSDHDown(void);
extern void OSDVUp(void);
extern void OSDVDown(void);
extern void OSDTransparentUp(void);
extern void OSDTransparentDown(void);
extern void OSDTimeoutUp(void);
extern void OSDTimeoutDown(void);
extern void OSDRotationUp(void);
extern void OSDRotationDown(void);
extern void OSDLanguageUp(void);
extern void OSDLanguageDown(void);
extern void OSDAudioMuteUp(void);
extern void OSDAudioMuteDown(void);
extern void OSDInputSourceUp(void);
extern void OSDInputSourceDown(void);
extern void OSDDCRUp(void);
extern void OSDDCRDown(void);

#if ENABLE_ASPECT_RATIO == ON		//george 20160217
	extern void OSDAspectRatioUp(void);
	extern void OSDAspectRatioDown(void);
#endif 

//extern void OSDOverScanUp(void);
//extern void OSDOverScanDown(void);
//extern void OSDODUp(void);
//extern void OSDODDown(void);
extern void OSDResetUp(void);
extern void OSDResetDown(void);

extern void OSD2Dto3DFmtDown(void);
extern void OSD2Dto3DFmtUp(void);
extern void OSD2Dto3DAdptDown(void);
extern void OSD2Dto3DAdptUp(void);
extern void OSD2Dto3DDepthDown(void);
extern void OSD2Dto3DDepthUp(void);
extern void OSD2Dto3DViewDown(void);
extern void OSD2Dto3DViewUp(void);
extern void OSD3DLRSwapDown(void);
extern void OSD3DLRSwapUp(void);
extern void OSD3DTo2DDown(void);
extern void OSD3DTo2DUp(void);

extern void OSDShowSourceMenu(void);
extern void OSDSourceMenuITMUp(void);
extern void OSDSourceMenuITMDn(void);
extern void OSDShowBFMenu(void);
extern void OSDBFMenuITMUp(void);
extern void OSDBFMenuITMDn(void);

extern void OSDUpdateAutoTuneBar(UCHAR percentage);
extern void OSDPerformAuto(void);
extern void OSDPerformNormal(void);
extern void OSDShowDir1(void);
extern void OSDShowDir2(void);
extern void OSDShowDir3(void);

#if ALS_EnDis == ALSMODE			//don't know used where ~

#elif ALS_EnDis == ALSOffSET	
//	extern void OSDShowDir4(void);	// george: F_ALSBV_03B1
#elif ALS_EnDis == ALSRange

#else	//Normal

#endif	//#if ALS_EnDis == ENABLE


extern void OSDCloseDir(void);
extern void OSDShowOpt1(void);
extern void OSDCloseOpt1(void);
extern void OSDShowOpt2(void);
extern void OSDCloseOpt2(void);

extern void OSDShowNoSync(void);
extern void OSDShowNoCable(void);
extern void OSDShowOOL(void);
extern void OSDShowOOR(void);

//extern void OSDConfirmOSDRotation(void);
extern void OSDConfirmLanguage(void);
extern void OSDConfirmInput(void);
extern void OSDConfirmRecall(void);
extern void OSDConfirm3DCnvMode(void);

#endif //__OSD_VIEW_H__
