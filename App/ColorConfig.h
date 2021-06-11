/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/
#ifndef __COLOR_CONFIG_H__
#define __COLOR_CONFIG_H__

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************
#include "Typedef.h"
#include "ColorEngine.h"

//******************************************************************************
// G L O B A L   D E F I N I T I O N S
//******************************************************************************
enum {
    CE_NTSC_76,
    CE_NTSC_80,
//    CE_NVTCLR_1,
//    CE_NVTCLR_2,
    CE_OFF,
    NUMBER_CE_MODES    
} ;

enum {
    IG_STD_1,
    IG_STD_2,
    IG_S_CURVE,
    IG_RS_CURVE,
    IG_RC_CURVE,
    IG_C_CURVE,
    IG_NVT_CURVE_1,
    IG_NVT_CURVE_2,
    IG_DEFAULT,
    NUMBER_IG_MODES
} ;

enum {
    HH_MODE_1,
    HH_MODE_2,
    HH_MODE_3,
    NUMBER_HH_MODES
} ;

enum {
    HS_MODE_1,
    HS_MODE_2,
    HS_MODE_3,
    NUMBER_HS_MODES
} ;
/*
enum {
    CLRTMP_5000K,
    CLRTMP_6500K,
    CLRTMP_7500K,
    CLRTMP_8200K,
    CLRTMP_9300K,
    CLRTMP_11500K,
    CLRTMP_sRGB,
    CLRTMP_USER,
    NUMBER_CLRTMP
} ;
*/

enum {
    CLRTMP_6500K,
    CLRTMP_7500K,
    CLRTMP_9300K,
//    CLRTMP_sRGB,
    CLRTMP_USER,
    NUMBER_CLRTMP
} ;


typedef struct _CM_BLOCK_ {
    UCHAR ROffset;
    UCHAR GOffset;
    UCHAR BOffset;
    UCHAR RGain;
    UCHAR GGain;
    UCHAR BGain;
    UCHAR Saturation;
    UCHAR Intensity;
    UCHAR Hue;
    UCHAR BlueMore;
    UCHAR GreenMore;
    UCHAR RedMore;
    UCHAR FTMore;
    UCHAR Sharpness;
    UCHAR Peaking;
    UCHAR TextEn;
    BFColorExMode ClrMode;
    IGBlock *pIG;
    HHBlock *pHH;
    HSBlock *pHS;
    HIBlock *pHI;
} CMBlock;

//******************************************************************************
// E X T E R N A L   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
void InitColor(void);
void SetThemeMode(UCHAR mode);
void PerformDCR(UCHAR reset);
void DisableDCR(void);
void SetDBCBacklight(USHRT brightness);
void SetColorTemperature(UCHAR mode);

#endif //__COLOR_CONFIG_H__
