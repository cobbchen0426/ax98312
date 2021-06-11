/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/

#ifndef __OSD_TYPE_H__
#define __OSD_TYPE_H__

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
 * Data type for OSD rotation.
 */
typedef enum _OSDPOSROTATION_ {
    OSD_POS_ROT_OFF, /*!< Rotation off.*/
    OSD_POS_ROT_90,  /*!< Rotate 90 degree. */
    OSD_POS_ROT_180, /*!< Rotate 180 degree. */
    OSD_POS_ROT_270  /*!< Rotate 270 degree. */
} OSDPosRotation;

/*!
 * Data type for OSD indent alignment.
 */
typedef enum _OSDALIGNMENT_ {
    OSD_ALIGN_LEFT,  /*!< Left alignment.*/
    OSD_ALIGN_RIGHT, /*!< Right alignment.*/
    OSD_ALIGN_CENTER /*!< Center alignment.*/
} OSDAlignment;

/*!
 * Data type for OSD font style.
 */
typedef enum _OSDFONTTYPE_ {
    OSD_FONT_NORMAL,    /*!< Normal OSD font.*/
    OSD_FONT_COMPRESSED /*!< Compressed OSD font.*/
} OSDFontType;

/*!
 * Data type for OSD font dimension.
 */
typedef enum _OSDFONTSIZE_ {
    OSD_FONT_10X16, /*!< 10x16 OSD font.*/
    OSD_FONT_10X18, /*!< 10x18 OSD font.*/
    OSD_FONT_12X16, /*!< 12x16 OSD font.*/
    OSD_FONT_12X18  /*!< 12x18 OSD font.*/
} OSDFontSize;

/*!
 * Data type for the bit size of OSD font.
 */
typedef enum _OSDFONTBITS_ {
    OSD_FONTBITS_1b = 0xA0, /*!< 1-bit OSD font.*/
    OSD_FONTBITS_2b = 0xB0, /*!< 2-bits OSD font.*/
    OSD_FONTBITS_3b = 0xC0, /*!< 3-bits OSD font.*/
    OSD_FONTBITS_4b = 0xC1  /*!< 4-bits OSD font.*/
} OSDFontBits;

/*!
 * Data type of OSD window ID.
 */
typedef enum _OSDWIN_ {
    OSD_WINDOW1 = 0x00,
    OSD_WINDOW2,
    OSD_WINDOW3,
    OSD_WINDOW4,
    OSD_WINDOW5,
    OSD_WINDOW6,
    OSD_WINDOW7,
    OSD_WINDOW8,
    OSD_WIN_OFF
} OSDWindow;

/*!
 * Data type for OSD fade direction.
 */
typedef enum _OSDFADEDIRECTION_ {
    OSD_FADE_LEFT_TOP,    /*!< Left-Top corner.*/
    OSD_FADE_RIGHT_TOP, /*!< Right-Top corner.*/
    OSD_FADE_LEFT_BOT, /*!< Left-Bottom corner.*/
    OSD_FADE_RIGHT_BOT /*!< Right-Bottom corner.*/
} OSDFadeDirection;

/*!
 * Data type of OSD window attributes.
 */
typedef struct _OSDWINATTR_ {
    UCHAR ucWinAttr; /*!< Window attributes. */
    UCHAR ucWinClr; /*!< Window control. */
    UCHAR ucBorderAttr; /*!< Bolder attributes. */
    UCHAR ucRBorderClr; /*!< Right bolder control. */
    UCHAR ucLBorderClr; /*!< Left bolder control. */
} OSDWinAttr;

/*!
 * Data type of OSD attributes.
 */
typedef struct _OSDPALETTETABLE_{
    USHRT usTableSize; /*!< Overall table size in bytes. */
    USHRT usOffset; /*!< Offset in the OSD palette sram. */
    UCHAR *ucTable; /*!< Pointer to the OSD palette table. */
} OSDPaletteTable;

/*!
 * Data type of OSD font list.
 */
typedef struct _OSDFONTTABLE_{
    USHRT usTableSize; /*!< Overall table size in bytes. */
    OSDFontBits ucFontBits; /*!< OSD bit size of this table. */
    USHRT usOffset; /*!< Offset in the OSD font sram. */
    UCHAR *ucTable; /*!< Pointer to the OSD font table. */
} OSDFontTable;

//******************************************************************************
// V A R I A B L E S   P R O T O T Y P E
//******************************************************************************

//******************************************************************************
// F U N C T I O N   P R O T O T Y P E S
//******************************************************************************

#endif //__OSD_TYPE_H__
