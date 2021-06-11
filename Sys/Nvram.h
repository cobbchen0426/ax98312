/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/

#ifndef __NVRAM_H__
#define __NVRAM_H__

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************
#include "InputTiming.h"
#include "Typedef.h"

//******************************************************************************
// M A C R O   D E F I N I T I O N S
//******************************************************************************
#define NVRAM_ADDR              0xA0  /*!< The slave address of NVRam (24C16). */
#define NVRAM_TIMING_ADDR       0x000 /*!< The start address of timing data in NVRam. */
#define NVRAM_TIMING_AREA       (NVRAM_USER_ADDR-NVRAM_TIMING_ADDR) /*!< The size of timing data in NVRam. */
#define NVRAM_USER_ADDR         0x260	//0x270	george 20160218		 /*!< The start address of user data in NVRam. */
#define NVRAM_CALIB_ADDR        0x290 /*!< The start address of calibration data in NVRam. */
#define NVRAM_SYSTEM_ADDR       0x2B0 /*!< The start address of system data in NVRam. */
#define NVRAM_HDCP_ADDR         0x2D0 /*!< The start address of HDCP keys in NVRam. */
#define NVRAM_VGA_EDID_ADDR     0x400 /*!< The start address of VGA edid in NVRam. */
#define NVRAM_VGA_EDID_AREA     0x80  /*!< The size of VGA edid in NVRam.*/
#define NVRAM_DVI_EDID_ADDR     0x480 /*!< The start address of DVI edid in NVRam. */
#define NVRAM_DVI_EDID_AREA     0x80  /*!< The size of DVI edid in NVRam. */
#define NVRAM_HDMI_EDID_ADDR    0x500 /*!< The start address of HDMI edid in NVRam. */
#define NVRAM_HDMI_EDID_AREA    0x100 /*!< The size of HDMI edid in NVRam.*/
#define NVRAM_END               0x7FF /*!< The end address of NVRam.*/
#define NVRAM_USER_SIZE         (NVRAM_CALIB_ADDR - NVRAM_USER_ADDR)   /*!< The size of user data in NVRam. */			//George: 0x290-0x270= 32 seats
#define NVRAM_CALIB_SIZE        (NVRAM_SYSTEM_ADDR - NVRAM_CALIB_ADDR) /*!< The size of calibration data in NVRam. */	//George: 0x2B0-0x290= 32 seats
#define NVRAM_SYSTEM_SIZE       (NVRAM_HDCP_ADDR - NVRAM_SYSTEM_ADDR)  /*!< The size of system data in NVRam. */		//George: 0x2D0-0x2B0= 32 seats

#define NVRAM_FIELD_END_FLAG    0xA5A5 /*!< The flag of the end of NvramUserData/NvramCalibData/NvramSystemData fields. */

#define NVRAM_UPDATE_FREE       0 /*!< NVRam update type: Update none. */
#define NVRAM_UPDATE_ALL        1 /*!< NVRam update type: Update all. */
#define NVRAM_UPDATE_USER       2 /*!< NVRam update type: Update user data. */



#define CM3218_ADDR              0x48  /* ALS, Ambient Light Sensor: CAPELLA: CM3218 */



//******************************************************************************
// D A T A   T Y P E   D E F I N E S
//******************************************************************************
/*!
 * Data type of timing-related fields in NVRam.
 */
typedef struct _NVRAM_TIMING_FORMAT_ {
    USHRT usHTotal;
    USHRT usHStart;
    USHRT usVStart;
    USHRT usHTotal50;
    USHRT usHStart50;
    USHRT usVStart50;
    UCHAR ucPhase;
    UCHAR ucAutoTune;
    USHRT usModeIndex;
} NvramTimingFormat;

/*!
 * Data type of user-related fields in NVRam.
 */
typedef struct _NVRAM_USER_DATA_ {	// sizeof(don't over 31 bytes):  29 uchar	+ Add(bALSOnOff, ucALSBaseVal, bTouchOnOff)
    UCHAR bPowerStatus : 1;
    UCHAR bOSDLock : 1;
    UCHAR bDDCCI : 1;
    UCHAR bAudioMute : 1;
    UCHAR bGammaOnOff : 1;
    UCHAR bLDOnOff : 1;
    UCHAR bAutoSyncSource : 1;
    UCHAR bOSDRotation : 1;
    UCHAR bOverScan : 1;					// 9 bits

#if ALS_EnDis == ALSMODE	
#elif ALS_EnDis == ALSOffSET	
	UCHAR bALSOnOff		: 1;				// george: F_ALSOnOff_01
#elif ALS_EnDis == ALSRange	//for ADS
	UCHAR bALSOnOff		: 1;				
#else
#endif	//#if ALS_EnDis == ENABLE


#if TOUCH_EnDis == ENABLE
	UCHAR bTouchOnOff	: 1;				// george: F_Touch_01
#endif //#if TOUCH_EnDis == ENABLE

    UCHAR ucDCRMode;
    UCHAR ucLanguage;
    UCHAR ucBrightness;		// George
    UCHAR ucContrast;
    UCHAR ucOSDTimer;
    UCHAR ucOSDX;
    UCHAR ucOSDY;
    UCHAR ucOSDTransparent;
    UCHAR ucVolume;
    UCHAR ucColorTemp;
    UCHAR ucUserRGain;
    UCHAR ucUserGGain;
    UCHAR ucUserBGain;
    UCHAR ucUserROffset;
    UCHAR ucUserGOffset;
    UCHAR ucUserBOffset;
    UCHAR ucAspectRatio;
    UCHAR ucODMode;
    UCHAR ucBFMode;
    UCHAR ucInputSource;
    UCHAR uc2DTo3DMode;
    UCHAR uc2Dto3DDepth;
    UCHAR uc2Dto3DView;
    UCHAR uc3DCfg;
    UCHAR ucSRMode;					//----------------------- george 25byts + 2byts(11bit)= 27 seats.

#if ALS_EnDis == ALSMODE
	UCHAR ucALSMode;		// ref. //ucALSMode (0:Off, 1:InDoor, 2:OutDoor)	// george: F_ALSBV_01
#elif ALS_EnDis == ALSOffSET	
	UCHAR  ucALSBaseVal;						// george: F_ALSBV_01			// george: F_ALS_06
#elif ALS_EnDis == ALSRange	//for ADS			
	UCHAR ucALSBrigMAX;		//ALS_Brig-MAX
	UCHAR ucALSBrigMIN;		//ALS_Brig-MIN
#else	//Normal
#endif	//#if ALS_EnDis == ENABLE

//	UCHAR AA; //AA_for test
    
	USHRT usADBoardID;		//for customer more adboard management.
    USHRT usUsrEnd;
} NvramUserData;

/*!
 * Data type of calibration-related fields in NVRam.
 */
typedef struct _NVRAM_CAL_DATA_ {		// sizeof: 31 uchar
    UCHAR ucADCRGain;
    UCHAR ucADCGGain;
    UCHAR ucADCBGain;
    UCHAR ucADCROffset;
    UCHAR ucADCGOffset;
    UCHAR ucADCBOffset;
    UCHAR uc5000KRGain;
    UCHAR uc5000KGGain;
    UCHAR uc5000KBGain;
    UCHAR uc6500KRGain;
    UCHAR uc6500KGGain;
    UCHAR uc6500KBGain;
    UCHAR uc7500KRGain;
    UCHAR uc7500KGGain;
    UCHAR uc7500KBGain;
    UCHAR uc8200KRGain;
    UCHAR uc8200KGGain;
    UCHAR uc8200KBGain;
    UCHAR uc9300KRGain;
    UCHAR uc9300KGGain;
    UCHAR uc9300KBGain;
    UCHAR uc11500KRGain;
    UCHAR uc11500KGGain;
    UCHAR uc11500KBGain;
    UCHAR ucsRGBRGain;
    UCHAR ucsRGBGGain;
    UCHAR ucsRGBBGain;
        
    //ADD BY CHIU
    UCHAR ucGammaVal;
    UCHAR ucBacklite;  
    
    USHRT usCalEnd;
} NvramCalibData;

/*!
 * Data type of system-related fields in NVRam.
 */
typedef struct _NVRAM_SYS_DATA_ {		// sizeof: 22 uchar
    UCHAR bFactory : 1;
    UCHAR bDemo: 1;
    UCHAR bDFR: 1;				//DFR, Double Frame Rate
    UCHAR bSR: 1;
    UCHAR bBurnIn : 1;
    UCHAR bShowLogo : 1;
    UCHAR ucPowerOnTimerM;
    USHRT usPowerOnTimerH;
    UCHAR ucPOTimerM_FE2P;
    USHRT usPOTimerH_FE2P;
    UCHAR ucTimingWriteIdx;
    USHRT usFirmwareVer; //Firmware version.
    USHRT usNvramID; //NVRAM is empty or not. This flag should be placed at the end of SystemData.
    USHRT usChkSum;
    USHRT usNVUsrSize;
    USHRT usNVCalSize;
    USHRT usNVSysSize;
    USHRT usSysEnd;
} NvramSystemData;

//******************************************************************************
// V A R I A B L E S   P R O T O T Y P E
//******************************************************************************
extern code NvramUserData UserDataDefault;
extern code NvramCalibData CalibDataDefault;
extern code NvramSystemData SystemDataDefault;

//******************************************************************************
// F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
void NvramWrite(USHRT addr, USHRT len, UCHAR *ptr);
void NvramRead(USHRT addr, USHRT len, UCHAR *ptr);
void NvramLoadData(void);
void NvramInitialize(UCHAR type);
void NvramClearTiming(void);
BOOL NvramReadTimingData(InputTimingFormat *ptr);
void NvramWriteTimingData(InputTimingFormat *ptr);
void NvramReadUserData(NvramUserData *ptr);
void NvramWriteUserData(NvramUserData *ptr);
void NvramReadCalibData(NvramCalibData *ptr);
void NvramWriteCalibData(NvramCalibData *ptr);
void NvramReadSystemData(NvramSystemData *ptr);
void NvramWriteSystemData(NvramSystemData *ptr);
void NvramDumpToSram(void);
void NvramWriteHDCPdata(UCHAR *ptr);
void NvramReadHDCPdata(UCHAR *ptr);
#if USE_INTERNAL_EDID == 1
void NvramSaveEDID(void);
void NvramLoadEDID(void);
#endif

#endif //__NVRAM_H__
