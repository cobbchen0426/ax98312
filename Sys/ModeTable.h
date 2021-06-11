/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/

#ifndef __MODETABLE_H__
#define __MODETABLE_H__

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************
#include "Typedef.h"

//******************************************************************************
// M A C R O   D E F I N I T I O N S
//******************************************************************************
#define _640x350_70HZ       0x0100 /*!< The mode index of preset timing. */
#define _640x400_70HZ       0x0200 /*!< The mode index of preset timing. */
#define _720x400_70HZ       0x0300 /*!< The mode index of preset timing. */
#define _640x350_85HZ       0x0400 /*!< The mode index of preset timing. */
#define _640x400_85HZ       0x0500 /*!< The mode index of preset timing. */
#define _720x400_85HZ       0x0600 /*!< The mode index of preset timing. */

#ifdef SGD_GVTW70SNAD1E0
	#define _800x480_60HZ		0x0700	//george
#else
	#define _640x480_60HZ       0x0700 /*!< The mode index of preset timing. */
#endif


#define _720x480P_60HZ      0x0800 /*!< The mode index of preset timing. */
#define _640x480_66HZ       0x0900 /*!< The mode index of preset timing. */
#define _640x480_72HZ       0x0A00 /*!< The mode index of preset timing. */
#define _640x480_75HZ       0x0B00 /*!< The mode index of preset timing. */
#define _640x480_85HZ       0x0C00 /*!< The mode index of preset timing. */
#define _640x500_57HZ       0x0D00 /*!< The mode index of preset timing. */
#define _832x624_75HZ       0x0E00 /*!< The mode index of preset timing. */
#define _800x600_56HZ       0x0F00 /*!< The mode index of preset timing. */
#define _800x600_60HZ       0x1000 /*!< The mode index of preset timing. */
#define _800x600_72HZ       0x1100 /*!< The mode index of preset timing. */
#define _800x600_75HZ       0x1200 /*!< The mode index of preset timing. */
#define _800x600_85HZ       0x1300 /*!< The mode index of preset timing. */
#define _848x480_60HZ       0x1400 /*!< The mode index of preset timing. */
#define _848x480_60HZ_RB    0x1500 /*!< The mode index of preset timing. */
#define _848x480_70HZ       0x1600 /*!< The mode index of preset timing. */
#define _848x480_72HZ       0x1700 /*!< The mode index of preset timing. */
#define _848x480_75HZ       0x1800 /*!< The mode index of preset timing. */
#define _720x576_60HZ       0x1900 /*!< The mode index of preset timing. */
#define _1024x768_43HZ_I    0x1A01 /*!< The mode index of preset timing. */
#define _1024x768_60HZ      0x1B00 /*!< The mode index of preset timing. */
#define _1024x768_70HZ      0x1C00 /*!< The mode index of preset timing. */
#define _1024x768_72HZ      0x1D00 /*!< The mode index of preset timing. */
#define _1024x768_75HZ      0x1E00 /*!< The mode index of preset timing. */
#define _1024x768_85HZ      0x1F00 /*!< The mode index of preset timing. */
#define _1280x768_85HZ      0x2000 /*!< The mode index of preset timing. */
#define _1152x720_60HZ      0x2100 /*!< The mode index of preset timing. */
#define _1280x720_60HZ      0x2200 /*!< The mode index of preset timing. */
#define _1152x864_70HZ      0x2300 /*!< The mode index of preset timing. */
#define _1152x864_75HZ      0x2400 /*!< The mode index of preset timing. */
#define _1152x864_85HZ      0x2500 /*!< The mode index of preset timing. */
#define _1152x870_75HZ      0x2600 /*!< The mode index of preset timing. */
#define _1152x900_66HZ      0x2700 /*!< The mode index of preset timing. */
#define _1152x900_76HZ      0x2800 /*!< The mode index of preset timing. */
#define _1440x900_75HZ      0x2900 /*!< The mode index of preset timing. */
#define _1280x720_75HZ      0x2A00 /*!< The mode index of preset timing. */
#define _1280x768_60HZ_RB   0x2B00 /*!< The mode index of preset timing. */
#define _1280x768_60HZ      0x2C00 /*!< The mode index of preset timing. */
#define _1360x768_60HZ      0x2D00 /*!< The mode index of preset timing. */
#define _1366x768_60HZ      0x2E00 /*!< The mode index of preset timing. */
#define _1280x768_75HZ      0x2F00 /*!< The mode index of preset timing. */
#define _1280x800_60HZ_RB   0x3000 /*!< The mode index of preset timing. */
#define _1280x800_60HZ      0x3100 /*!< The mode index of preset timing. */
#define _1280x800_62HZ      0x3200 /*!< The mode index of preset timing. */
#define _1280x800_72HZ      0x3300 /*!< The mode index of preset timing. */
#define _1280x800_75HZ      0x3400 /*!< The mode index of preset timing. */
#define _1280x800_85HZ      0x3500 /*!< The mode index of preset timing. */
#define _1280x960_60HZ      0x3600 /*!< The mode index of preset timing. */
#define _1280x960_85HZ      0x3700 /*!< The mode index of preset timing. */
#define _1280x1024_60HZ     0x3800 /*!< The mode index of preset timing. */
#define _1280x1024_70HZ_RB  0x3900 /*!< The mode index of preset timing. */
#define _1280x1024_70HZ     0x3A00 /*!< The mode index of preset timing. */
#define _1280x1024_72HZ     0x3B00 /*!< The mode index of preset timing. */
#define _1280x1024_75HZ     0x3C00 /*!< The mode index of preset timing. */
#define _1280x1024_76HZ     0x3D00 /*!< The mode index of preset timing. */
#define _1280x1024_85HZ     0x3E00 /*!< The mode index of preset timing. */
#define _1400x1050_60HZ_RB  0x3F00 /*!< The mode index of preset timing. */
#define _1680x1050_60HZ_RB  0x4000 /*!< The mode index of preset timing. */
#define _1400x1050_60HZ     0x4100 /*!< The mode index of preset timing. */
#define _1680x1050_60HZ     0x4200 /*!< The mode index of preset timing. */
#define _1400x1050_75HZ     0x4300 /*!< The mode index of preset timing. */
#define _1680x1050_75HZ     0x4400 /*!< The mode index of preset timing. */
#define _1400x1050_85HZ     0x4500 /*!< The mode index of preset timing. */
#define _1440x900_60HZ_RB   0x4600 /*!< The mode index of preset timing. */
#define _1600x900_60HZ      0x4700 /*!< The mode index of preset timing. */
#define _1440x900_60HZ      0x4800 /*!< The mode index of preset timing. */
#define _1600x1000_60HZ_RB  0x4900 /*!< The mode index of preset timing. */
#define _1600x1000_60HZ     0x4A00 /*!< The mode index of preset timing. */
#define _1600x1000_75HZ     0x4B00 /*!< The mode index of preset timing. */
#define _1600x1200_60HZ_RB  0x4C00 /*!< The mode index of preset timing. */
#define _1920x1200_60HZ_RB  0x4D00 /*!< The mode index of preset timing. */
#define _1600x1200_60HZ     0x4E00 /*!< The mode index of preset timing. */
#define _1600x1200_65HZ     0x4F00 /*!< The mode index of preset timing. */
#define _1600x1200_70HZ     0x5000 /*!< The mode index of preset timing. */
#define _1600x1200_75HZ     0x5100 /*!< The mode index of preset timing. */
#define _1600x1280_60HZ     0x5200 /*!< The mode index of preset timing. */
#define _1920x1080_60HZ_RB  0x5300 /*!< The mode index of preset timing. */
#define _1920x1080_60HZ     0x5400 /*!< The mode index of preset timing. */
#define _1920x1200_50HZ_RB  0x5500 /*!< The mode index of preset timing. */
#define _1920x1200_60HZ     0x5600 /*!< The mode index of preset timing. */
#define _1920x1080P_60HZ    0x5700 /*!< The mode index of preset timing. */
#define _720x576P_50HZ      0x5800 /*!< The mode index of preset timing. */
#define _1280x720P_50HZ     0x5900 /*!< The mode index of preset timing. */
#define _1920x1080P_50HZ    0x5A00 /*!< The mode index of preset timing. */
#define _720x480I_60HZ      0x5B01 /*!< The mode index of preset timing. */
#define _1440x480I_60HZ     0x5C01 /*!< The mode index of preset timing. */
#define _2880x480I_60HZ     0x5D01 /*!< The mode index of preset timing. */
#define _1920x1080I_60HZ    0x5E01 /*!< The mode index of preset timing. */
#define _720x576I_50HZ      0x5F01 /*!< The mode index of preset timing. */
#define _1440x576I_50HZ     0x6001 /*!< The mode index of preset timing. */
#define _2880x576I_50HZ     0x6101 /*!< The mode index of preset timing. */
#define _1920x1080I_50HZ_RB 0x6201 /*!< The mode index of preset timing. */
#define _1920x1080I_50HZ    0x6301 /*!< The mode index of preset timing. */
#define _2048x1152_60HZ_RB  0x6400 /*!< The mode index of preset timing. */
#define _2048x1152_60HZ     0x6500 /*!< The mode index of preset timing. */
#define _1280x600_60HZ      0x6600 /*!< The mode index of preset timing. */
#define _1024x600_60HZ      0x6700 /*!< The mode index of preset timing. */
#define _1024x768_76HZ      0x6800 /*!< The mode index of preset timing. */
#define _1152x864_60HZ      0x6900 /*!< The mode index of preset timing. */
#define _1280x768_70HZ      0x6A00 /*!< The mode index of preset timing. */
#define _1280x768_72HZ      0x6B00 /*!< The mode index of preset timing. */
#define _1280x1024_67HZ     0x6C00 /*!< The mode index of preset timing. */
#define _720x576P_60HZ      0x6D00 /*!< The mode index of preset timing. */
#define _1280x960_75HZ      0x6E00 /*!< The mode index of preset timing. */
#define _1920x1080I_50HZ125 0x6F01 /*!< The mode index of preset timing. */
#define _1850x1036_60HZ		0x6F02 /*!< The mode index of preset timing. */

#ifdef TRULY_TFT1280120
	#define _1280x120_50HZ		0x7000 /*!< The mode index of preset timing. */		//george_TRULY_TFT1280120
	#define _1280x120_99HZ		0x7100 /*!< The mode index of preset timing. */		//george_TRULY_TFT1280120
	#define _1280x720_50HZ		0x7200 /*!< The mode index of preset timing. */		//george_TRULY_TFT1280120
	#define _1280x720_20HZ		0x7300 /*!< The mode index of preset timing. */		//george_TRULY_TFT1280120
	#define _1280x480_30HZ		0x7400 /*!< The mode index of preset timing. */		//george_TRULY_TFT1280120
#endif



#define _NEW_MODE           0xFF00 /*!< The mode index of non-preset timing. */

//******************************************************************************
// D A T A   T Y P E   D E F I N E S
//******************************************************************************
/*
 * Data type of H/V information of the present timing.
 */
typedef struct {
    UCHAR ucSampling; /*! OFF/x2/x3 .*/
    USHRT usHSyncFreq; /*!< Frequency of horizontal sync. */
    USHRT usVSyncFreq; /*!< Frequency of vertical sync. */
    UCHAR ucHVPolarity; /*!< H/V polarities. */
    UCHAR ucHSyncWidth; /*!< Horizontal sync width. */
    UCHAR ucVSyncWidth; /*!< Vertical sync width. */
    USHRT usHTotal; /*!< Horizontal total pixels. */
    USHRT usVTotal; /*!< Vertical total lines. */
    USHRT usModeHActive; /*!< Horizontal resolution. */
    USHRT usModeVActive; /*!< Vertical resolution. */
    USHRT usCapHActive; /*!< Horizontal capture width. */
    USHRT usCapVActive; /*!< Vertical capture height. */
    USHRT usHStart; /*!< Horizontal start position. */
    USHRT usVStart; /*!< Vertical start position. */
    UCHAR ucHSyncTolerance; /*!< Frequency tolerance of horizontal sync. */
    UCHAR ucVSyncTolerance; /*!< Frequency tolerance of Vertical sync. */
    UCHAR ucVTotalTolerance; /*!< Tolerance of vertical lines. */
    USHRT usModeIndex; /*!< The id of the present timing. */
} ModeTableFormat;

//******************************************************************************
// V A R I A B L E S   P R O T O T Y P E
//******************************************************************************

//******************************************************************************
// F U N C T I O N   P R O T O T Y P E S
//******************************************************************************

#endif //__MODETABLE_H__
