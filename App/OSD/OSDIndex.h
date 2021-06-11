/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/
#ifndef __OSD_INDEX_H__
#define __OSD_INDEX_H__

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************
#include "Typedef.h"


extern code UCHAR *MainMenuStrTab[];
extern code UCHAR *BrightnessStrTab[];
extern code UCHAR *ContrastStrTab[];
extern code UCHAR *GammaStrTab[];


#if ALS_EnDis == ALSMODE
	extern code UCHAR *ALSItemStrTab[];			//george: 
	extern code UCHAR *ALSMdStrTab[];
#elif ALS_EnDis == ALSOffSET	
	extern code UCHAR *ALSOnOffStrTab[];		//george: F_ALSOnOff_02
	extern code UCHAR *ALSBVStrTab[];			//george: F_ALSBV_02
#elif ALS_EnDis == ALSRange
	extern code UCHAR *ALSOnOffStrTab[];		
#else	//Normal

#endif	//#if ALS_EnDis == ENABLE


#if TOUCH_EnDis == ENABLE
	extern code UCHAR *TouchSWStrTab[];			//george: F_Touch_02
#endif //#if TOUCH_EnDis == ENABLE



//extern code UCHAR *ALSItemStrTab[];			
/// extern code UCHAR *GItem16StrTab[];		// george_Item16
/// extern code UCHAR *GItem17StrTab[];		// george_Item17

extern code UCHAR *SRStrTab[];
#if ENABLE_SR
extern code UCHAR *SRItemStrTab[];
#endif
extern code UCHAR *SaturationStrTab[];
extern code UCHAR *TintStrTab[];
extern code UCHAR *DCR_StrTab[];
extern code UCHAR *DBC_StrTab[];
extern code UCHAR *PhaseStrTab[];
extern code UCHAR *ClockStrTab[];
extern code UCHAR *HPosStrTab[];
extern code UCHAR *VPosStrTab[];
extern code UCHAR *ColorTempStrTab[];
extern code UCHAR *UserDefineStrTab[];
extern code UCHAR *sRGB_StrTab[];
extern code UCHAR *ColorTemp_StrTab[];
extern code UCHAR *RedStrTab[];
extern code UCHAR *GreenStrTab[];
extern code UCHAR *BlueStrTab[];
extern code UCHAR *HorizontalStrTab[];
extern code UCHAR *VerticalStrTab[];
extern code UCHAR *TransparencyStrTab[];
extern code UCHAR *OSDTimeStrTab[];
extern code UCHAR *OSDRotationStrTab[];
extern code UCHAR *LanguageStrTab[];
extern code UCHAR *ThrDCtrlTab[];
extern code UCHAR *ThrDCnvTab[];
extern code UCHAR *ThrDDphTab[];
extern code UCHAR *ThrDVwTab[];
extern code UCHAR *ThrDAdpTab[];
extern code UCHAR *ThrDLRTab[];
extern code UCHAR *ThrDTwoDTab[];
extern code UCHAR *ThrDCnvFmtTab[];
extern code UCHAR *InputStrTab[];
extern code UCHAR *ResetStrTab[];
extern code UCHAR *CountryStrTab[];
extern code UCHAR *SourceStrTab[];
extern code UCHAR *YesStrTab[];
extern code UCHAR *NoStrTab[];
extern code UCHAR *AutoStrTab[];
extern code UCHAR *WaitStrTab[];
extern code UCHAR *SrcAnalogStrTab[];
extern code UCHAR *SrcDigitalStrTab[];
extern code UCHAR *AttentionStrTab[];
extern code UCHAR *OnTab[];
extern code UCHAR *OffTab[];
extern code UCHAR *MuteTab[];
extern code UCHAR *OverDriverTab[];
extern code UCHAR *OverScanTab[];


#if ENABLE_ASPECT_RATIO == ON					//george 20160217
	extern code UCHAR *DisplaySizeTab[];
	extern code UCHAR *FullScreenTab[];
#endif 


extern code UCHAR *SmartFitTab[];
extern code UCHAR *Fix43Tab[];
extern code UCHAR *Smart43Tab[];
extern code UCHAR *MonitorSetupTab1[];
extern code UCHAR *ExitStrTab[];
extern code UCHAR *BackStrTab[];
extern code UCHAR *OKStrTab[];
extern code UCHAR *NextStrTab[];
extern code UCHAR *StandAloneTab[];
extern code UCHAR *OrignalColorStrTab[];
extern code UCHAR *WarmStrTab[];
extern code UCHAR *CoolStrTab[];
extern code UCHAR *VolumeStrTab[];
extern code UCHAR *AttentionStrTab[];
extern code UCHAR *OutOfRangeOverStrTab[];
extern code UCHAR *OutOfRange85HzStrTab[];
extern code UCHAR *OSD_LockStrTab[];
extern code UCHAR *NoSyncStrTab[];
extern code UCHAR *NoVideoStrTab[];
extern code UCHAR *DisconnectedStrTab[];
extern code UCHAR *BurnInStrTab[];
extern code UCHAR *DDCCiOnTab1[];
extern code UCHAR *DDCCiOffTab1[];
extern code UCHAR *BestResultStrTab[];
extern code UCHAR *sRGBWarningStrTab[];
extern code UCHAR *LTMItemStrTab[];
extern code UCHAR *BFStrTab[];
extern code UCHAR *LF_DEMO_StrTab[];
#if ENABLE_SR
extern code UCHAR *SRDemoStrTab[];
#endif

#endif //__OSD_INDEX_H__
