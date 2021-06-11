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
// G L O B A L   D E F I N I T I O N S
//******************************************************************************

//******************************************************************************
// S T A T I C   V A R I A B L E S
//******************************************************************************
static idata USHRT *pIndentFontBase;
static idata UCHAR *pIndentWidthBase;
static idata USHRT usIndentFontIndex = 0;
static idata UCHAR ucIndentStringLen = 0;
static idata UCHAR ucIndentWidth = 0;
static xdata USHRT usIndentFontBuffer[18];

//******************************************************************************
// S T A T I C   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
static void OSDAPI_LoadIndentFont(void) small;

//******************************************************************************
// Prototype: 
//  void OSDAPI_SetIndentTable(UCHAR id)
// Parameters:
//
// Return:
//  None
// Purpose:
//  
// Notes:
//  None
//******************************************************************************
void OSDAPI_SetIndentTable(UCHAR id)
{
    if (id == CHINESE_TABLE)
        OSDAPI_SetIndentFont(usArialFontChineseTable, NULL);
    else
        OSDAPI_SetIndentFont(usArialFontTable, ucArialWidthTable);
}

//******************************************************************************
// Prototype:
//  void OSDAPI_SetIndentIndex(USHRT index)
// Parameters:
//  index   : start font index of a indent string
// Return:
//  None
// Purpose:
//  Set start font index of a indent string
// Notes:
//  None
//******************************************************************************
void OSDAPI_SetIndentIndex(USHRT index)
{
    usIndentFontIndex = index;
}

//******************************************************************************
// Prototype:
//  void OSDAPI_SetIndentIndex(USHRT index)
// Parameters:
//  index   : start font index of a indent string
// Return:
//  None
// Purpose:
//  Set start font index of a indent string
// Notes:
//  None
//******************************************************************************
/*
USHRT OSDAPI_GetIndentIndex(void)
{
    return usIndentFontIndex;
}
*/

//******************************************************************************
// Prototype:
//  void OSDAPI_SetIndentIndex(USHRT index)
// Parameters:
//  index   : start font index of a indent string
// Return:
//  None
// Purpose:
//  Set start font index of a indent string
// Notes:
//  None
//******************************************************************************
/*
void OSDAPI_SetIndentStringLen(UCHAR len)
{
    ucIndentStringLen = len;
}
*/

//******************************************************************************
// Prototype:
//  void OSDAPI_SetIndentIndex(USHRT index)
// Parameters:
//  index   : start font index of a indent string
// Return:
//  None
// Purpose:
//  Set start font index of a indent string
// Notes:
//  None
//******************************************************************************
/*
UCHAR OSDAPI_GetIndentStringLen(void)
{
    return ucIndentStringLen;
}
*/

//******************************************************************************
// Prototype:
//  void OSDAPI_SetIndentWidth(UCHAR width)
// Parameters:
//  width   : indent string width
// Return:
//  None
// Purpose:
//  Set indent string width
// Notes:
//  None
//******************************************************************************
void OSDAPI_SetIndentWidth(UCHAR width)
{
    ucIndentWidth = width;
}

//******************************************************************************
// Prototype:
//  void OSDAPI_SetIndentWidth(UCHAR width)
// Parameters:
//  width   : indent string width
// Return:
//  None
// Purpose:
//  Set indent string width
// Notes:
//  None
//******************************************************************************
/*
UCHAR OSDAPI_GetIndentWidth(void)
{
    return ucIndentWidth;
}
*/

//******************************************************************************
// Prototype:
//  void OSDAPI_SetIndentFont(USHRT *pfont, UCHAR *pwidth)
// Parameters:
//  *pfont   : pointer to font table
//  *pwidth  : pointer to font width table
// Return:
//  None
// Purpose:
//  Set indent font table & width table
// Notes:
//  None
//******************************************************************************
void OSDAPI_SetIndentFont(USHRT *pfont, UCHAR *pwidth)
{
    pIndentFontBase = pfont;
    pIndentWidthBase = pwidth;
}

//******************************************************************************
// Prototype:
//  void OSDAPI_LoadIndentFont(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Load run-time-gererated OSD font to OSD SRam in scaler
// Notes:
//  None
//******************************************************************************
static void OSDAPI_LoadIndentFont(void) small
{
    UCHAR i,ch,height;

    ResetWDTimer();
    SC_INDEX_CTRL = 0xA0;
    SC_INDEX_ADDR_LO = (UCHAR)usIndentFontIndex; //Index low
    SC_INDEX_ADDR_HI = (UCHAR)(usIndentFontIndex>>8); //Index high

#if ENABLE_OSD_ROTATION == ON
    if ((SC_OSD_CTRL1&BIT7) != 0) {
        UCHAR buffer[27];
        OSDAPI_RotateIdentFont(buffer,usIndentFontBuffer);
        for (i=0; i<27; i++) {
            SC_INDEX_DATA = buffer[i];
        }        
    }
    else 
#endif //ENABLE_OSD_ROTATION == ON
    {
        height = OSDAPI_GetOSDFontHeight();
        for(i=0; i<height; i++) {
            usIndentFontBuffer[i] >>= 4;
            SC_INDEX_DATA = (UCHAR)usIndentFontBuffer[i]; //1'st byte
            ch = (UCHAR)(usIndentFontBuffer[i]>>8) & 0x0F;
            i++;
            ch |= ((UCHAR)usIndentFontBuffer[i] & 0xF0);
            SC_INDEX_DATA = ch; //2'nd byte
            ch = (UCHAR)((usIndentFontBuffer[i]>>8) & 0x00FF);
            SC_INDEX_DATA = ch; //3'th byte
        }
    }
    usIndentFontIndex++;
    ucIndentStringLen++;
}

//******************************************************************************
// Prototype: 
//  void OSDAPI_SetIndentString(UCHAR *ptr) small
// Parameters:
//  *ptr  : pointer to font index of indent string
// Return:
//  None
// Purpose:
//  Pre-load font data of indent string in scaler.
// Notes:
//  None
//******************************************************************************
void OSDAPI_SetIndentString(UCHAR *ptr) small
{
    UCHAR i, l, w, k, Row, wd_point, height;
    USHRT m;
    UCHAR table;

    table = COMMON_TABLE;//Defualt COMMON_TABLE
    OSDAPI_SetIndentTable(COMMON_TABLE);

    ucIndentStringLen = 0;
    //string width
    m = 0;
    l = ptr[0] + 1;
    for (i=1; i<l; i++) {
        if (ptr[i] == CHINESE_TABLE)
            table = CHINESE_TABLE;
        else if (ptr[i] == COMMON_TABLE)
            table = COMMON_TABLE;
        //else if ((ptr[i] != CHINESE_TABLE)&&(ptr[i] != COMMON_TABLE)) {
        else {
            k = ptr[i];
            if (table == CHINESE_TABLE)
                m += 16;
            else
                m += pIndentWidthBase[k];
        }
    }
    //Alignment
    if (OSDAPI_GetAlignType() == 0) { //Left
        wd_point = 0;
    }
    else if(OSDAPI_GetAlignType() == 1) { //Right
        m = (USHRT)ucIndentWidth * 12 - m;
        wd_point = m % 12;
    }
    else if(OSDAPI_GetAlignType() == 2) { //Center
        m = (USHRT)ucIndentWidth * 12 - m;
        k = m / 12;
        wd_point = m % 12;
        if((k & BIT0) != 0) {
            wd_point += 12;
        }
        wd_point >>= 1;
    }

    height = OSDAPI_GetOSDFontHeight();
    for(Row=0; Row<height; Row++) {
        usIndentFontBuffer[Row] = 0;
    }

    table = COMMON_TABLE;//Defualt COMMON_TABLE
    OSDAPI_SetIndentTable(COMMON_TABLE);
	
    //write font
    for (i=1; i<l; i++) {
        if (ptr[i] == CHINESE_TABLE) {
            OSDAPI_SetIndentTable(CHINESE_TABLE);
            table = CHINESE_TABLE;
        }
        else if (ptr[i] == COMMON_TABLE) {
            OSDAPI_SetIndentTable(COMMON_TABLE);
            table = COMMON_TABLE;
        }
        else {
            k = ptr[i];
            if (table == CHINESE_TABLE)
                w = 16;
            else
                w = pIndentWidthBase[k]; //get font font width

            m = k * height;

            if(wd_point == 0) {
                for(Row=0; Row<height; Row++) {
                    usIndentFontBuffer[Row] = pIndentFontBase[m+Row];
                }
            }
            else {
                for(Row=0; Row<height; Row++) {
                    usIndentFontBuffer[Row] |= (pIndentFontBase[m+Row] >> wd_point);
                }
            }
            wd_point += w;
            do {

                if(wd_point == 12) { //buffer full?
                    OSDAPI_LoadIndentFont();
                    wd_point = 0;
                }
                else if(wd_point> 12) {
                    OSDAPI_LoadIndentFont();
                    wd_point -= 12;
                    for(Row=0; Row<height; Row++) {
                        usIndentFontBuffer[Row] =
                        (pIndentFontBase[m+Row] << (w - wd_point));
                    }
                }
            }while(wd_point>11);
        }
    }
    ResetWDTimer();
    //write back space
    if(wd_point != 0) {
        OSDAPI_LoadIndentFont();
        wd_point = 0;
    }
}

//******************************************************************************
// Prototype: 
//  void OSDAPI_ShowIndents(BOOL attr, UCHAR x, UCHAR y) small
// Parameters:
//  attr: set OSD attributes
//  x   : x position on OSD
//  y   : y position on OSD
// Return:
//  None
// Purpose:
//  Show pre-load indent string.
// Notes:
//  None
//******************************************************************************
void OSDAPI_ShowIndents(BOOL attr, UCHAR x, UCHAR y) small
{
    UCHAR i,l;

    UCHAR ch;
    USHRT m,temp;
    ResetWDTimer();

    temp = usIndentFontIndex - ucIndentStringLen;

    m = y * OSDAPI_GetOSDWidth() + x;

    if (attr == TRUE) {
        SC_INDEX_CTRL = 0x90;
    }
    else {
        SC_INDEX_CTRL = 0x40;
    }
    SC_INDEX_ADDR_LO = (UCHAR)m;
    SC_INDEX_ADDR_HI = (UCHAR)(m >> 8);

    //Alignment
    if(OSDAPI_GetAlignType() == 0) { //Left
        l = 0;
    }
    else if(OSDAPI_GetAlignType() == 1) { //Right
        l = ucIndentWidth - ucIndentStringLen;
    }
    else if(OSDAPI_GetAlignType() == 2) { //Center
        l = (ucIndentWidth - ucIndentStringLen) >> 1;
    }
    //write front space
    for(i=0; i<l; i++) {
        SC_INDEX_DATA = 0x00;
    }
    //write font index
    for(i=0; i<ucIndentStringLen; i++) {
        ch = (UCHAR)(temp + i);
        SC_INDEX_DATA = ch;
    }
    //write back space
    i = l + ucIndentStringLen;
    for(i; i<ucIndentWidth; i++) {
        SC_INDEX_DATA = 0x00;
    }
    ResetWDTimer();
}

//******************************************************************************
// Prototype:
//  void OSDAPI_ShowIndentString(BOOL attr, UCHAR x, UCHAR y, UCHAR len, UCHAR *ptr)
// Parameters:
//  attr: set OSD attributes
//  x   : x position on OSD
//  y   : y position on OSD
//  len : length of indent string
//  *ptr  : pointer to font index of indent string
// Return:
//  None
// Purpose:
//  Show indent string
// Notes:
//  None
//******************************************************************************
void OSDAPI_ShowIndentString(BOOL attr, UCHAR x, UCHAR y, UCHAR len, UCHAR *p) small
{
    OSDAPI_SetIndentWidth(len);
    OSDAPI_SetIndentString(p);
    OSDAPI_ShowIndents(attr, x, y);
}
