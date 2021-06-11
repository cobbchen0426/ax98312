/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/

#ifndef __BF_TYPE_H__
#define __BF_TYPE_H__

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************
#include "Typedef.h"

//******************************************************************************
// M A C R O   D E F I N I T I O N S
//******************************************************************************

//******************************************************************************
// D A T A   T Y P E   D E F I N E S
//******************************************************************************
/*!
 * Data type of CM generation.
 */
typedef enum _BF_GEN_ {
    BF_ONE_GEN, /*!< First generation CM. */
    BF_TWO_GEN  /*!< Second generation CM. */
} BFGeneration;

/*!
 * Data type of bright frame window ID.
 */
typedef enum _BF_WINDOW_ {
    BF_WINDOW_1, /*!< BF window 1. */
    BF_WINDOW_2  /*!< BF window 2. */
} BFWindow;

/*!
 * Data type of bright frame window size.
 * BF_WINDOW_FULLSCREEN and BF_WINDOW_INIT are different.
 * Please refer the description of BFAPI_SetWindowSize for details.
 */
typedef enum _BF_WINDOW_SIZE_ {
    BF_WINDOW_FULLSCREEN, /*!< Full screen bright frame window. */
    BF_WINDOW_LEFTSIZE,   /*!< Left-side screen bright frame window. */
    BF_WINDOW_RIGHTSIZE,  /*!< Right-side screen bright frame window. */
    BF_WINDOW_INIT        /*!< Full screen bright frame window. */
} BFWSize;

/*!
 * Data type of color extension.
 */
typedef enum _BF_COLOR_EN_MODE_ {
    BF_COLOR_NVT72, /*!< NTSC 72% color gamut. */
    BF_COLOR_NVT74, /*!< NTSC 74% color gamut. */
    BF_COLOR_NVT76, /*!< NTSC 76% color gamut. */
    BF_COLOR_NVT78, /*!< NTSC 78% color gamut. */
    BF_COLOR_NVT80, /*!< NTSC 80% color gamut. */
    BF_COLOR_INIT,  /*!< Original color gamut of panel. */
    BF_COLOR_OFF    /*!< Color extension off. */
} BFColorExMode;

/*!
 * Data type of six axle color adjustments.
 */
typedef enum _BF_SIXAXIE_ITEM_ {
    BF_SIXAXIE_RED,    /*!< The axle of red color. */
    BF_SIXAXIE_YELLOW, /*!< The axle of yellow color. */
    BF_SIXAXIE_GREEN,  /*!< The axle of green color. */
    BF_SIXAXIE_CYAN,   /*!< The axle of cyan color. */
    BF_SIXAXIE_BLUE,   /*!< The axle of blue color. */
    BF_SIXAXIE_MANG    /*!< The axle of magenta color. */
} BFSixAxie;

/*!
 * Data type of the style of dynamic i-gamma adjustment.
 */
typedef enum _ACE_TYPE_ {
    ACE_SMOOTH, /*!< Step by step adjustment of dynamic i-gamma. */
    ACE_ONE     /*!< One time adjustment of dynamic i-gamma. */
} ACEType;

/*!
 * Data type of local 3x3 matrix.
 */
typedef struct _LOCAL_MATRIX_ {
    USHRT Rows[3][4]; /*!< Value of each item of 3x3 matrix. */
} LocalMatrix;

/*!
 * Data type of i-gamma.
 */
typedef struct _IG_BLOCK_ {
    UCHAR NumIG;      /*!< Number of i-gamma segments. The value must be fixed as 16. */
    USHRT IGamma[17]; /*!< Value of each item of i-gamma. */
} IGBlock;

/*!
 * Data type of local hue.
 */
typedef struct _HH_BLOCK_ {
    UCHAR ucNumHH;       /*!< Number of local hue segments. 0 < ucNumHH <= 24 . */
    UCHAR ucOffset;      /*!< Offset of local hue segments. 0 < ucOffset < 24 - ucNumHH. */
    UCHAR ucHHTable[24]; /*!< Value of each item of local hue. */
} HHBlock;

/*!
 * Data type of local saturation.
 */
typedef struct _HS_BLOCK_ {
    UCHAR ucNumHS;       /*!< Number of local saturation segments. 0 < ucNumHS <= 24 . */
    UCHAR ucOffset;      /*!< Offset of local saturation segments. 0 < ucOffset < 24 - ucNumHS. */
    UCHAR ucHSTable[24]; /*!< Value of each item of local saturation. */
} HSBlock;

/*!
 * Data type of local intensity.
 */
typedef struct _HI_BLOCK_ {
    UCHAR ucNumHI;       /*!< Number of local intensity segments. 0 < ucNumHI <= 24 . */
    UCHAR ucOffset;      /*!< Offset of local intensity segments. 0 < ucOffset < 24 - ucNumHI. */
    UCHAR ucHITable[17]; /*!< Value of each item of local intensity. */
} HIBlock;

//******************************************************************************
// V A R I A B L E S   P R O T O T Y P E
//******************************************************************************

//******************************************************************************
// F U N C T I O N   P R O T O T Y P E S
//******************************************************************************

#endif //__BF_TYPE_H__
