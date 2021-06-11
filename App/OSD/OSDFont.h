/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/
#ifndef __OSD_FONT_H__
#define __OSD_FONT_H__

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************
#include "Typedef.h"
#include "OSDType.h"

//******************************************************************************
// G L O B A L   D E F I N I T I O N S
//******************************************************************************
#define BLACK       0x0000
#define RED         0xF800
#define GREEN       0x07E0
#define BLUE        0x001F
#define CYAN        (BLUE|GREEN)
#define MAGENTA     (RED|BLUE)
#define YELLOW      (RED|GREEN)
#define WHITE       (RED|GREEN|BLUE)
#define TBLACK      BLACK
#define TRED        0x7800
#define TGREEN      0x01E0
#define TBLUE       0x000F
#define TCYAN       (TBLUE|TGREEN)
#define TMAGENTA    (TRED|TBLUE)
#define TYELLOW     (TRED|TGREEN)
#define GRAY        (TRED|TGREEN|TBLUE)

#define I_BLACK     0
#define I_GREEN     1
#define I_RED       2
#define I_BLUE      3
#define I_CYAN      4
#define I_MAGENTA   5
#define I_YELLOW    6
#define I_WHITE     7
#define I_TBLACK    8
#define I_TRED      9
#define I_TGREEN    10
#define I_TBLUE     11
#define I_TCYAN     12
#define I_TMAGENTA  13
#define I_TYELLOW   14
#define I_GRAY      15


//******************************************************************************
// E X T E R N A L   V A R I A B L E   P R O T O T Y P E S
//******************************************************************************
extern code OSDPaletteTable ucOSDPalette;
extern code OSDFontTable ucOneBitFontTable;
extern code OSDFontTable ucTwoBitsFontTable;
extern code OSDFontTable ucFourBitsFontTable;
extern code UCHAR ucArialWidthTable[];
extern code USHRT usArialFontTable[];
extern code USHRT usArialFontChineseTable[];

#endif //__OSD_FONT_H__
