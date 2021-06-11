/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/

#ifndef __BF_API_H__
#define __BF_API_H__

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************
#include "Typedef.h"
#include "BFType.h"

//******************************************************************************
// M A C R O   D E F I N I T I O N S
//******************************************************************************
#define BF_IDV_COLOR_NUMBER 24 /*!< Define the number of individual color adjustments. This value is fixed. */
#define BF_IG_PARTITIONS 16 /*!< Define the number of i-gamma segments. This value is fixed. */

#define CM_BR   0x01 /*!< ON/off mask of CM sub-functions. This is brightness function of CM. */
#define CM_CN   0x02 /*!< ON/off mask of CM sub-functions. This is contrast function of CM. */
#define CM_HUE  0x04 /*!< ON/off mask of CM sub-functions. This is hue function of CM. */
#define CM_SAT  0x08 /*!< ON/off mask of CM sub-functions. This is saturation function of CM. */
#define CM_INT  0x10 /*!< ON/off mask of CM sub-functions. This is intensity function of CM. */
#define CM_HH   0x20 /*!< ON/off mask of CM sub-functions. This is local hue function of CM. */
#define CM_HS   0x40 /*!< ON/off mask of CM sub-functions. This is local saturation function of CM. */
#define CM_HI   0x80 /*!< ON/off mask of CM sub-functions. This is local intensity function of CM. */
#define CM_ALL  0xFF /*!< ON/off mask of CM sub-functions. This is all function of CM. */

//******************************************************************************
// D A T A   T Y P E   D E F I N E S
//******************************************************************************

//******************************************************************************
// V A R I A B L E S   P R O T O T Y P E
//******************************************************************************

//******************************************************************************
// F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
void BFAPI_Init(BFGeneration gen);
void BFAPI_EnableWindow(BFWindow bfw);
void BFAPI_DisableWindow(BFWindow bfw);
void BFAPI_SetActiveWindow(BFWindow bfw);
void BFAPI_SetWindowSize(BFWSize type);
void BFAPI_SetCustomWindow(USHRT x, USHRT y, USHRT width, USHRT height);
void BFAPI_EnableCM(UCHAR func);
void BFAPI_DisableCM(UCHAR func);
void BFAPI_SetROffset(UCHAR offset);
void BFAPI_SetGOffset(UCHAR offset);
void BFAPI_SetBOffset(UCHAR offset);
void BFAPI_SetRGain(UCHAR gain);
void BFAPI_SetGGain(UCHAR gain);
void BFAPI_SetBGain(UCHAR gain);
void BFAPI_SetHue(UCHAR hue);
void BFAPI_SetSaturation(UCHAR sat);
void BFAPI_SetIntensity(UCHAR intensity);
void BFAPI_SetSharpness(UCHAR shp);
void BFAPI_SetYPeaking(UCHAR yp);
void BFAPI_SetTextEnhancement(UCHAR txt);
void BFAPI_CorrectFleshTone(UCHAR value);
void BFAPI_EnhanceRed(UCHAR value);
void BFAPI_EnhanceGreen(UCHAR value);
void BFAPI_EnhanceBlue(UCHAR value);
void BFAPI_SixAxieAdjustment(BFSixAxie item, UCHAR more);
void BFAPI_SetHHTable(HHBlock *ptr);
void BFAPI_SetHSTable(HSBlock *ptr);
void BFAPI_SetHITable(HIBlock *ptr);
void BFAPI_ColorEnhance(BFColorExMode mode);
void BFAPI_SetLocalMatrix(LocalMatrix *ptr);
void BFAPI_EnableACEMode(void);
void BFAPI_DisableACEMode(void);
void BFAPI_SetPreACEMode(IGBlock *mode);

#endif //__BF_API_H__
