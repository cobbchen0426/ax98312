/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************
#include "Include.h"

//******************************************************************************
// M A C R O   D E F I N I T I O N S
//******************************************************************************

//******************************************************************************
// G L O B A L   V A R I A B L E S
//******************************************************************************

//******************************************************************************
// S T A T I C   V A R I A B L E S
//******************************************************************************

//******************************************************************************
// E X T E R N A L   V A R I A B L E   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// S T A T I C   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// E X T E R N A L   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// F U N C T I O N   B O D Y S
//******************************************************************************

/**************************************************************************//**
 * Load OSD palette to scaler sram
 * @param pbuf Pointer to OSD palette data.
 ******************************************************************************/
void OSDAPI_LoadPalette(OSDPaletteTable *pbuf)
{
    idata USHRT i,l;

    ResetWDTimer();
#if IS_NT68770_SERIES || IS_NT68850_SERIES || IS_NT68655_SERIES || IS_NT68150_SERIES || IS_NT68790_SERIES
    OSDAPI_OSDPowerOn();
#endif
    l = pbuf->usTableSize;
    SC_INDEX_CTRL = 0xD0;
    SC_INDEX_ADDR_LO = pbuf->usOffset & 0x00FF;
    SC_INDEX_ADDR_HI = (pbuf->usOffset & 0xFF00) >> 8;
    for (i = 0; i < l; i++) {
        SC_INDEX_DATA = pbuf->ucTable[i];
    }
    ResetWDTimer();
}

/**************************************************************************//**
 * Load OSD font to scaler sram
 * @param type OSD_FONT_COMPRESSED if font is compressed else OSD_FONT_NORMAL.
 * @param pbuf Pointer to OSD font data.
 ******************************************************************************/
void OSDAPI_LoadFont(OSDFontType type, OSDFontTable *pbuf)
{
    UCHAR temp, l;
    idata USHRT i,len;

    ResetWDTimer();
#if IS_NT68770_SERIES || IS_NT68850_SERIES || IS_NT68655_SERIES || IS_NT68150_SERIES || IS_NT68790_SERIES
    OSDAPI_OSDPowerOn();
#endif
    len = pbuf->usTableSize;
    SC_INDEX_CTRL = pbuf->ucFontBits & 0xF0;
    SC_INDEX_ADDR_LO = pbuf->usOffset & 0x00FF;
    SC_INDEX_ADDR_HI = (pbuf->usOffset & 0xFF00) >> 8;

    if (type == OSD_FONT_NORMAL) {
        for (i = 0; i < len; i++) {
            SC_INDEX_DATA = pbuf->ucTable[i];
        }
    }
    else {
        for (i=0; i<len; i++) {
            temp = pbuf->ucTable[i];
            if ((temp == 0x00) || (temp == 0xFF)) {
                i++;
                l = pbuf->ucTable[i]; //length
                do {
                    SC_INDEX_DATA = temp;
                    l--;
                } while (l != 0);
            }
            else {
                SC_INDEX_DATA = temp;
            }
        }
    }
    ResetWDTimer();
}
