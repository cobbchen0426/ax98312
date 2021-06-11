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
/*!
 * Data type for the API of OSD window rotation.
 * This type is used in the OSDAPI.c only.
 */
typedef enum _OSDWIN_DEGREE_ {
    OSD_WIN_DEGREE_0,   /*!< Rotate 0 degree. */
    OSD_WIN_DEGREE_90,  /*!< Rotate 90 degree. */
    OSD_WIN_DEGREE_180, /*!< Rotate 180 degree. */
    OSD_WIN_DEGREE_270, /*!< Rotate 270 degree. */
    NUM_OSD_WIN_DEGREE  /*!< Number of rotation modes for OSD windows. */
} OSDWinDegree;

/*!
 * Macro function to set indent OSD attribute.
 * This macro is used in the OSDAPI.c only.
 */
#define SetIndentAlign(a) (ucOSDConfig = (ucOSDConfig&0xFC)|(a&0x03))
/*!
 * Macro function to get indent OSD attribute.
 * This macro is used in the OSDAPI.c only.
 */
#define GetIndentAlign()  (ucOSDConfig & 0x03)
/*!
 * Macro function to set OSD rotation attribute.
 * This macro is used in the OSDAPI.c only.
 */
#define SetOSDPosRot(r) (ucOSDConfig = (ucOSDConfig&0xF3)|((r&0x03) << 2))
/*!
 * Macro function to get OSD rotation attribute.
 * This macro is used in the OSDAPI.c only.
 */
#define GetOSDPosRot()  ((ucOSDConfig & 0x0C) >> 2)
/*!
 * Macro function to set the attribute of OSD window rotation.
 * This macro is used in the OSDAPI.c only.
 */
#define SetOSDWinRotStatus(i, r) { \
        USHRT __mask__; \
        UCHAR __id__; \
        __id__ = i * 2; \
        __mask__ = 0x0003 << __id__; \
        __mask__ = ~__mask__; \
        usOSDWinRotStatus &= __mask__; \
        __mask__ = r; \
        usOSDWinRotStatus |= (__mask__ << __id__); \
    }
/*!
 * Macro function to get the attribute of OSD window rotation.
 * This macro is used in the OSDAPI.c only.
 */
#define GetOSDWinRotStatus(i) ((usOSDWinRotStatus >> (i * 2)) & 0x0003)


//******************************************************************************
// G L O B A L   V A R I A B L E S
//******************************************************************************

//******************************************************************************
// S T A T I C   V A R I A B L E S
//******************************************************************************
static xdata UCHAR ucOSDConfig = (OSD_POS_ROT_OFF << 2) | OSD_ALIGN_LEFT; /*!< Variable for OSD indent status and OSD rotation status. */
static xdata USHRT usOSDWinRotStatus = 0x0000; /*!< Rotation status of each OSD window. */
static xdata UCHAR ucOSDFontHeight; /*!< Variable for OSD font height. */
static xdata UCHAR ucOSDFontWidth;  /*!< Variable for OSD font width. */
static xdata UCHAR ucOSDHeight;     /*!< Variable for OSD height. Unit is OSD font height. */
static xdata UCHAR ucOSDWidth;      /*!< Variable for OSD width. Unit is OSD font width. */
static xdata UCHAR ucWinUnitWidth;  /*!< Variable for the pixel number of the unit of OSD window width. */
static xdata UCHAR ucWinUnitHeight; /*!< Variable for the pixel number of the unit of OSD window height. */

//******************************************************************************
// E X T E R N A L   V A R I A B L E   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// S T A T I C   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
static void OSDAPI_RotateOSDWinPosition(USHRT sx, USHRT sy, USHRT ex, USHRT ey, OSDWinDegree degree, UCHAR rot);

//******************************************************************************
// E X T E R N A L   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// F U N C T I O N   B O D Y S
//******************************************************************************

/**************************************************************************//**
 * Set 1/2/3/4-bits OSD font start address in OSD sram.
 * @param type Bits size per font.
 * @param addr Start address of x-bits OSD font.
 ******************************************************************************/
void OSDAPI_SetFontAddress(OSDFontBits type, USHRT addr)
{
    switch (type) {
        case OSD_FONTBITS_1b:
            SC_OSD_FONT1B_ADDR_LO = addr & 0x00ff;
            SC_OSD_FONT1B_ADDR_HI = (addr & 0xff00) >> 8;
            break;
        case OSD_FONTBITS_2b:
            SC_OSD_FONT2B_ADDR_LO = addr & 0x00ff;
            SC_OSD_FONT2B_ADDR_HI = (addr & 0xff00) >> 8;
            break;
        case OSD_FONTBITS_3b:
            SC_OSD_SEPARATE_ROW_CTRL |= BIT7;
            SC_OSD_FONT4B_ADDR_LO = addr & 0x00ff;
            SC_OSD_FONT4B_ADDR_HI = (addr & 0xff00) >> 8;
            break;
        case OSD_FONTBITS_4b:
            SC_OSD_SEPARATE_ROW_CTRL &= ~BIT7;
            SC_OSD_FONT4B_ADDR_LO = addr & 0x00ff;
            SC_OSD_FONT4B_ADDR_HI = (addr & 0xff00) >> 8;
            break;
        default:
            break;
    }
}

/**************************************************************************//**
 * Clear user-defined area of OSD sram by scaler.
 ******************************************************************************/
void OSDAPI_ClearOSD(void)
{
    OSDAPI_OSDPowerOn();
    SC_OSD_CODE_FC = 0x00;
    SC_OSD_CODE_FC_CTL |= BIT0;
    while ((SC_OSD_CODE_FC_CTL & BIT0) == BIT0) {
        // Do something to avoid dead loop here
    }
}

/**************************************************************************//**
 * Indicate OSD width.
 * @param width OSD width.
 ******************************************************************************/
void OSDAPI_SetOSDWidth(UCHAR width)
{
    ucOSDWidth = width;
}

/**************************************************************************//**
 * Indicate OSD height.
 * @param height OSD height.
 ******************************************************************************/
void OSDAPI_SetOSDHeight(UCHAR height)
{
    ucOSDHeight = height;
}

/**************************************************************************//**
 * Get OSD width.
 * @return OSD width.
 ******************************************************************************/
UCHAR OSDAPI_GetOSDWidth(void)
{
    return ucOSDWidth;
}

/**************************************************************************//**
 * Get OSD height.
 * @return OSD height.
 ******************************************************************************/
UCHAR OSDAPI_GetOSDHeight(void)
{
    return ucOSDHeight;
}

/**************************************************************************//**
 * Indicate OSD font size. There are four types of OSD font size,
 * 10x16, 10x18, 12x16, 12x18.
 * @param size OSD font size.
 ******************************************************************************/
void OSDAPI_SetFontSize(OSDFontSize size)
{
    UCHAR ctrl;
    ctrl = SC_OSD_SPACE_CTL & 0x3F;
    switch (size) {
        case OSD_FONT_10X16:
            ucOSDFontWidth = 10;
            ucOSDFontHeight = 16;
            SC_OSD_SPACE_CTL = ctrl | BIT7 | BIT6;
            break;
        case OSD_FONT_10X18:
            ucOSDFontWidth = 10;
            ucOSDFontHeight = 18;
            SC_OSD_SPACE_CTL = ctrl | BIT6;
            break;
        case OSD_FONT_12X16:
            ucOSDFontWidth = 12;
            ucOSDFontHeight = 16;
            SC_OSD_SPACE_CTL = ctrl | BIT7;
            break;
        case OSD_FONT_12X18:
            ucOSDFontWidth = 12;
            ucOSDFontHeight = 18;
            SC_OSD_SPACE_CTL = ctrl;
            break;
        default:
            break;
    };
}

/**************************************************************************//**
 * Get OSD font width. The value is \a 10 or \a 12.
 * @return OSD font width.
 ******************************************************************************/
UCHAR OSDAPI_GetOSDFontWidth(void)
{
    return ucOSDFontWidth;
}

/**************************************************************************//**
 * Get OSD font height. The value is \a 16 or \a 18.
 * @return OSD font height.
 ******************************************************************************/
UCHAR OSDAPI_GetOSDFontHeight(void)
{
    return ucOSDFontHeight;
}

/**************************************************************************//**
 * Set OSD rotation.
 * @param rot OSD rotation mode.
 ******************************************************************************/
void OSDAPI_RotateOSDPosition(OSDPosRotation rot)
{
    SetOSDPosRot(rot);
}

/**************************************************************************//**
 * Set OSD position on screen.
 * @param x x position of OSD on screen. Step unit is font width.
 * @param y y position of OSD on screen. Step unit is font height.
 ******************************************************************************/
void OSDAPI_SetPosition(USHRT x, USHRT y)        
{
#define OSDPOS_BOUNDRY(a,b,c) ((a < (b * c)) ? 0 : (a - b * c))

    USHRT fw, fh, ow, oh;
    USHRT xy;

    OSDAPI_OSDPowerOn(); 
    fw = OSDAPI_GetOSDFontWidth();
    fh = OSDAPI_GetOSDFontHeight();
    ow = OSDAPI_GetOSDWidth();
    oh = OSDAPI_GetOSDHeight();
    switch(GetOSDPosRot()) 
	{
        //case OSD_POS_ROT_90: // 90
        //    break;
        //case OSD_POS_ROT_180: //180
        //    break;
        case OSD_POS_ROT_270: //270
            xy = PANEL_WIDTH - OSD_YPOS_TOP_OFFSET - OSD_YPOS_BOTTOM_OFFSET;
            xy = (ULONG) OSDPOS_BOUNDRY(xy, fh, oh) * (OSD_POS_STEPS - y) / OSD_POS_STEPS;
            xy += OSD_YPOS_TOP_OFFSET;
            SC_OSD_HS_LO = (xy & 0x00FF);
            SC_OSD_HS_HI = (xy & 0xFF00) >> 8;
            SC_OSD_HW = ow - 1;
            xy = PANEL_HEIGHT - OSD_XPOS_LEFT_OFFSET - OSD_XPOS_RIGHT_OFFSET;
            xy = (ULONG) OSDPOS_BOUNDRY(xy, fw, ow) * x / OSD_POS_STEPS;
            xy += OSD_XPOS_RIGHT_OFFSET;
            SC_OSD_VS_LO = (xy & 0x00FF);
            SC_OSD_VS_HI = (xy & 0xFF00) >> 8;
            SC_OSD_VH = oh - 1;
            break;
        default:
            xy = PANEL_WIDTH - OSD_XPOS_LEFT_OFFSET - OSD_XPOS_RIGHT_OFFSET;
            xy = (ULONG) OSDPOS_BOUNDRY(xy, fw, ow) * x / OSD_POS_STEPS;
            xy += OSD_XPOS_LEFT_OFFSET;
            SC_OSD_HS_LO = (xy & 0x00FF);
            SC_OSD_HS_HI = (xy & 0xFF00) >> 8;
            SC_OSD_HW = ow - 1;
            xy = PANEL_HEIGHT - OSD_YPOS_TOP_OFFSET - OSD_YPOS_BOTTOM_OFFSET;
            xy = (ULONG) OSDPOS_BOUNDRY(xy, fh, oh) * (OSD_POS_STEPS - y) / OSD_POS_STEPS;
            xy += OSD_YPOS_TOP_OFFSET;

#if  SET_SHOW_OSD_POSITION == SET_OSD_LEFT_TOP
            SC_OSD_VS_LO = 1;
            SC_OSD_VS_HI = 0;
#elif SET_SHOW_OSD_POSITION == SET_OSD_CENTER_TOP
            SC_OSD_VS_LO = (xy & 0x00FF);
            SC_OSD_VS_HI = (xy & 0xFF00) >> 8;
#else		//(Normal)
            SC_OSD_VS_LO = (xy & 0x00FF);
            SC_OSD_VS_HI = (xy & 0xFF00) >> 8;
#endif
            SC_OSD_VH = oh - 1;
            break;
    }

    WaitDisVSync();  // Always waiting display VSync to insure OSD H/V has been
                     // loaded into scaler.
                     // Jude 2010/10/08
#undef OSDPOS_BOUNDRY
}

/**************************************************************************//**
 * Set OSD position on screen.
 * @param x x position of OSD on screen. Step unit is one pixel.
 * @param y y position of OSD on screen. Step unit is one pixel.
 ******************************************************************************/
void OSDAPI_SetRowPosition(USHRT x, USHRT y)
{
    SC_OSD_HS_LO = (x & 0x00FF);
    SC_OSD_HS_HI = (x & 0xFF00) >> 8;
    SC_OSD_HW = ucOSDWidth - 1;
    SC_OSD_VS_LO = (y & 0x00FF);
    SC_OSD_VS_HI = (y & 0xFF00) >> 8;
    SC_OSD_VH = ucOSDHeight - 1;
    WaitDisVSync();
}

/**************************************************************************//**
 * Show string at (x,y) on OSD.
 * @param attr Set OSD attributes at font(x,y).
 * @param x x position of string on OSD.
 * @param y y position of string on OSD.
 * @param len Number of characters of the string.
 * @param pstr Point to a list of font index.
 ******************************************************************************/
void OSDAPI_WriteXYString(BOOL attr, UCHAR x, UCHAR y, UCHAR len, UCHAR *pstr)
{
    UCHAR i;
    USHRT m;

    ResetWDTimer();
    m = (USHRT) y * ucOSDWidth + x;

    if (attr == TRUE) {
        SC_INDEX_CTRL = 0x90;
    }
    else {
        SC_INDEX_CTRL = 0x40;
    }
    SC_INDEX_ADDR_LO = (UCHAR) m;
    SC_INDEX_ADDR_HI = (UCHAR)(m >> 8);

    for (i = 0; i < len; i++) {
        SC_INDEX_DATA = pstr[i];
    }
    ResetWDTimer();
}

/**************************************************************************//**
 * Show string at (x,y) on OSD with specified alignment.
 * @param attr Set OSD attributes at OSD(x,y).
 * @param x x position of string on OSD.
 * @param y y position of string on OSD.
 * @param len Length of the string.
 * @param pstr Point to a list of font index.
 * @param align_len Length of the alignment.
 ******************************************************************************/
/*
void OSDAPI_WriteXYStringAlign(BOOL attr, UCHAR x, UCHAR y, UCHAR len, UCHAR *pstr, UCHAR align_len)
{
    UCHAR new_x;

    if (align_len < len) { //Error handling
        align_len = len;
    }

    switch (GetIndentAlign()) {
        case OSD_ALIGN_LEFT:
            new_x = x;
            break;

        case OSD_ALIGN_RIGHT:
            new_x = x + (align_len-len);
            break;

        case OSD_ALIGN_CENTER:
            new_x = x + (align_len-len)/2;
            break;
    }

    OSDAPI_WriteXYRepeatChar(attr, x, y, align_len, 0x00);
    OSDAPI_WriteXYString(attr, new_x, y, len, pstr);
}
*/

/**************************************************************************//**
 * Show string. The x/y information is composed in the string.
 * @param attr Set OSD attributes.
 * @param pstr point to a list of font index with (x,y,len).
 ******************************************************************************/
/*
void OSDAPI_WriteString(BOOL attr, UCHAR *pstr)
{
    UCHAR i, l;
    USHRT m;

    ResetWDTimer();
    m = pstr[2] * ucOSDWidth + pstr[1];

    if (attr == TRUE) {
        SC_INDEX_CTRL = 0x90;
    }
    else {
        SC_INDEX_CTRL = 0x40;
    }
    SC_INDEX_ADDR_LO = (UCHAR) m;
    SC_INDEX_ADDR_HI = (UCHAR)(m >> 8);

    l = pstr[0] + 1;
    for (i = 3; i < l; i++) {
        SC_INDEX_DATA = pstr[i];
    }
    ResetWDTimer();
}
*/

/**************************************************************************//**
 * Show a string with same characters on OSD.
 * @param attr Set OSD attributes.
 * @param x x position of string on OSD.
 * @param y y position of string on OSD.
 * @param num Number of characters to be displayed on OSD.
 * @param ch The character to be showed on OSD.
 ******************************************************************************/
void OSDAPI_WriteXYRepeatChar(BOOL attr, UCHAR x, UCHAR y, UCHAR num, UCHAR ch)
{
    UCHAR i;
    USHRT m;

    ResetWDTimer();
    m = y * ucOSDWidth + x;

    if (attr == TRUE) {
        SC_INDEX_CTRL = 0x90;
    }
    else {
        SC_INDEX_CTRL = 0x40;
    }
    SC_INDEX_ADDR_LO = (UCHAR) m;
    SC_INDEX_ADDR_HI = (UCHAR)(m >> 8);

    for (i = 0; i < num; i++) {
        SC_INDEX_DATA = ch;
    }
    ResetWDTimer();
}

/**************************************************************************//**
 * Show character at OSD(x,y).
 * @param attr Set OSD attributes.
 * @param x x position of char on OSD.
 * @param y y position of char on OSD.
 * @param ch The character to be showed on OSD.
 ******************************************************************************/
/*
void OSDAPI_WriteXYChar(BOOL attr, UCHAR x, UCHAR y, UCHAR ch)
{
    USHRT m;

    ResetWDTimer();
    m = y * ucOSDWidth + x;

    if (attr == TRUE) {
        SC_INDEX_CTRL = 0x90;    
    }
    else {
        SC_INDEX_CTRL = 0x40;
    }
    SC_INDEX_ADDR_LO = (UCHAR) m;
    SC_INDEX_ADDR_HI = (UCHAR)(m >> 8);
    SC_INDEX_DATA = ch;
    ResetWDTimer();
}
*/

/**************************************************************************//**
 * Set same OSD font attributes to a string at OSD(x,y).
 * @param x x position of a string on OSD.
 * @param y y position of a string on OSD.
 * @param num Length of a string.
 * @param attr Set OSD attributes.
 ******************************************************************************/
void OSDAPI_FillLineAttr(UCHAR x, UCHAR y, UCHAR num, USHRT attr)
{
    UCHAR i;
    USHRT m;

    ResetWDTimer();
    m = y * ucOSDWidth + x;

    SC_INDEX_CTRL = 0x70;
    SC_INDEX_ADDR_LO = (UCHAR) m;
    SC_INDEX_ADDR_HI = (UCHAR)(m >> 8);
    for (i = 0; i < num; i++) {
        SC_INDEX_DATA = (UCHAR) attr;
        SC_INDEX_DATA = (UCHAR)(attr >> 8);
    }
    ResetWDTimer();
}

/**************************************************************************//**
 * Set font attributes with a list of attribute settings.
 * @param x x start position of a string on OSD.
 * @param y y start position of a string on OSD.
 * @param num Length of a string.
 * @param ptr Pointer to the list of font attributes.
 ******************************************************************************/
void OSDAPI_FillLineAttrList(UCHAR x, UCHAR y, UCHAR num, USHRT *ptr)
{
    UCHAR i;
    USHRT m;

    ResetWDTimer();
    m = y * ucOSDWidth + x;

    SC_INDEX_CTRL = 0x70;
    SC_INDEX_ADDR_LO = (UCHAR) m;
    SC_INDEX_ADDR_HI = (UCHAR)(m >> 8);

    for (i = 0; i < num; i++) {
        SC_INDEX_DATA = (UCHAR) *ptr;
        SC_INDEX_DATA = (UCHAR)(*ptr >> 8);
        ptr++;
    }
    ResetWDTimer();
}

/**************************************************************************//**
 * Indicate position alignment, right, left or center, on OSD.
 * @param algn Position alignment on OSD.
 ******************************************************************************/
void OSDAPI_SetAlignType(OSDAlignment algn)
{
    SetIndentAlign(algn);
}

/**************************************************************************//**
 * Return position alignment, right, left or center, on OSD.
 * @return Position alignment. OSD_ALIGN_LEFT, OSD_ALIGN_RIGHT or OSD_ALIGN_CENTER.
 ******************************************************************************/
UCHAR OSDAPI_GetAlignType(void)
{
    return GetIndentAlign();
}

#if ENABLE_OSD_ROTATION == ON
/**************************************************************************//**
 * Rotate OSD font.
 * @param[out] des Pointer to destination font buffer.
 * @param[in] src Pointer to source font buffer.
 ******************************************************************************/
void OSDAPI_RotateFont(UCHAR *des, UCHAR *src)
{
#define B0(a) (a&0x01)
#define B1(a) ((a&0x02)>>1)
#define B2(a) ((a&0x04)>>2)
#define B3(a) ((a&0x08)>>3)
#define B4(a) ((a&0x10)>>4)
#define B5(a) ((a&0x20)>>5)
#define B6(a) ((a&0x40)>>6)
#define B7(a) ((a&0x80)>>7)

    des[26] = (B4(src[25])<<7) | (B0(src[24])<<6) | (B4(src[22])<<5) | (B0(src[21])<<4) | 
              (B4(src[19])<<3) | (B0(src[18])<<2) | (B4(src[16])<<1) | (B0(src[15])<<0);
    des[25] = (B4(src[13])<<7) | (B0(src[12])<<6) | (B4(src[10])<<5) | (B0(src[ 9])<<4) | 
              (B4(src[ 7])<<3) | (B0(src[ 6])<<2) | (B4(src[ 4])<<1) | (B0(src[ 3])<<0);
    des[24] = (B4(src[ 1])<<7) | (B0(src[ 0])<<6) | (B5(src[25])<<5) | (B1(src[24])<<4) | 
              (B5(src[22])<<3) | (B1(src[21])<<2) | (B5(src[19])<<1) | (B1(src[18])<<0);
    des[23] = (B5(src[16])<<7) | (B1(src[15])<<6) | (B5(src[13])<<5) | (B1(src[12])<<4) | 
              (B5(src[10])<<3) | (B1(src[ 9])<<2) | (B5(src[ 7])<<1) | (B1(src[ 6])<<0);
    des[22] = (B5(src[ 4])<<7) | (B1(src[ 3])<<6) | (B5(src[ 1])<<5) | (B1(src[ 0])<<4) | 
              (B6(src[25])<<3) | (B2(src[24])<<2) | (B6(src[22])<<1) | (B2(src[21])<<0);
    des[21] = (B6(src[19])<<7) | (B2(src[18])<<6) | (B6(src[16])<<5) | (B2(src[15])<<4) | 
              (B6(src[13])<<3) | (B2(src[12])<<2) | (B6(src[10])<<1) | (B2(src[ 9])<<0);
    des[20] = (B6(src[ 7])<<7) | (B2(src[ 6])<<6) | (B6(src[ 4])<<5) | (B2(src[ 3])<<4) | 
              (B6(src[ 1])<<3) | (B2(src[ 0])<<2) | (B7(src[25])<<1) | (B3(src[24])<<0);
    des[19] = (B7(src[22])<<7) | (B3(src[21])<<6) | (B7(src[19])<<5) | (B3(src[18])<<4) | 
              (B7(src[16])<<3) | (B3(src[15])<<2) | (B7(src[13])<<1) | (B3(src[12])<<0);
    des[18] = (B7(src[10])<<7) | (B3(src[ 9])<<6) | (B7(src[ 7])<<5) | (B3(src[ 6])<<4) | 
              (B7(src[ 4])<<3) | (B3(src[ 3])<<2) | (B7(src[ 1])<<1) | (B3(src[ 0])<<0);
    des[17] = (B0(src[26])<<7) | (B4(src[24])<<6) | (B0(src[23])<<5) | (B4(src[21])<<4) | 
              (B0(src[20])<<3) | (B4(src[18])<<2) | (B0(src[17])<<1) | (B4(src[15])<<0);  
    des[16] = (B0(src[14])<<7) | (B4(src[12])<<6) | (B0(src[11])<<5) | (B4(src[ 9])<<4) | 
              (B0(src[ 8])<<3) | (B4(src[ 6])<<2) | (B0(src[ 5])<<1) | (B4(src[ 3])<<0);   
    des[15] = (B0(src[ 2])<<7) | (B4(src[ 0])<<6) | (B1(src[26])<<5) | (B5(src[24])<<4) | 
              (B1(src[23])<<3) | (B5(src[21])<<2) | (B1(src[20])<<1) | (B5(src[18])<<0);
    des[14] = (B1(src[17])<<7) | (B5(src[15])<<6) | (B1(src[14])<<5) | (B5(src[12])<<4) | 
              (B1(src[11])<<3) | (B5(src[ 9])<<2) | (B1(src[ 8])<<1) | (B5(src[ 6])<<0);
    des[13] = (B1(src[ 5])<<7) | (B5(src[ 3])<<6) | (B1(src[ 2])<<5) | (B5(src[ 0])<<4) | 
              (B2(src[26])<<3) | (B6(src[24])<<2) | (B2(src[23])<<1) | (B6(src[21])<<0);
    des[12] = (B2(src[20])<<7) | (B6(src[18])<<6) | (B2(src[17])<<5) | (B6(src[15])<<4) | 
              (B2(src[14])<<3) | (B6(src[12])<<2) | (B2(src[11])<<1) | (B6(src[ 9])<<0);
    des[11] = (B2(src[ 8])<<7) | (B6(src[ 6])<<6) | (B2(src[ 5])<<5) | (B6(src[ 3])<<4) | 
              (B2(src[ 2])<<3) | (B6(src[ 0])<<2) | (B3(src[26])<<1) | (B7(src[24])<<0);
    des[10] = (B3(src[23])<<7) | (B7(src[21])<<6) | (B3(src[20])<<5) | (B7(src[18])<<4) | 
              (B3(src[17])<<3) | (B7(src[15])<<2) | (B3(src[14])<<1) | (B7(src[12])<<0);
    des[ 9] = (B3(src[11])<<7) | (B7(src[ 9])<<6) | (B3(src[ 8])<<5) | (B7(src[ 6])<<4) | 
              (B3(src[ 5])<<3) | (B7(src[ 3])<<2) | (B3(src[ 2])<<1) | (B7(src[ 0])<<0);    
    des[ 8] = (B4(src[26])<<7) | (B0(src[25])<<6) | (B4(src[23])<<5) | (B0(src[22])<<4) | 
              (B4(src[20])<<3) | (B0(src[19])<<2) | (B4(src[17])<<1) | (B0(src[16])<<0);
    des[ 7] = (B4(src[14])<<7) | (B0(src[13])<<6) | (B4(src[11])<<5) | (B0(src[10])<<4) | 
              (B4(src[ 8])<<3) | (B0(src[ 7])<<2) | (B4(src[ 5])<<1) | (B0(src[ 4])<<0);
    des[ 6] = (B4(src[ 2])<<7) | (B0(src[ 1])<<6) | (B5(src[26])<<5) | (B1(src[25])<<4) | 
              (B5(src[23])<<3) | (B1(src[22])<<2) | (B5(src[20])<<1) | (B1(src[19])<<0);
    des[ 5] = (B5(src[17])<<7) | (B1(src[16])<<6) | (B5(src[14])<<5) | (B1(src[13])<<4) | 
              (B5(src[11])<<3) | (B1(src[10])<<2) | (B5(src[ 8])<<1) | (B1(src[ 7])<<0);
    des[ 4] = (B5(src[ 5])<<7) | (B1(src[ 4])<<6) | (B5(src[ 2])<<5) | (B1(src[ 1])<<4) | 
              (B6(src[26])<<3) | (B2(src[25])<<2) | (B6(src[23])<<1) | (B2(src[22])<<0);
    des[ 3] = (B6(src[20])<<7) | (B2(src[19])<<6) | (B6(src[17])<<5) | (B2(src[16])<<4) | 
              (B6(src[14])<<3) | (B2(src[13])<<2) | (B6(src[11])<<1) | (B2(src[10])<<0);
    des[ 2] = (B6(src[ 8])<<7) | (B2(src[ 7])<<6) | (B6(src[ 5])<<5) | (B2(src[ 4])<<4) | 
              (B6(src[ 2])<<3) | (B2(src[ 1])<<2) | (B7(src[26])<<1) | (B3(src[25])<<0);
    des[ 1] = (B7(src[23])<<7) | (B3(src[22])<<6) | (B7(src[20])<<5) | (B3(src[19])<<4) | 
              (B7(src[17])<<3) | (B3(src[16])<<2) | (B7(src[14])<<1) | (B3(src[13])<<0);
    des[ 0] = (B7(src[11])<<7) | (B3(src[10])<<6) | (B7(src[ 8])<<5) | (B3(src[ 7])<<4) | 
              (B7(src[ 5])<<3) | (B3(src[ 4])<<2) | (B7(src[ 2])<<1) | (B3(src[ 1])<<0);

#undef B0
#undef B1
#undef B2
#undef B3
#undef B4
#undef B5
#undef B6
#undef B7
}

/**************************************************************************//**
 * Rotate indent OSD font.
 * @param[out] des Pointer to destination font buffer.
 * @param[in] src Pointer to source font buffer.
 ******************************************************************************/
void OSDAPI_RotateIdentFont(UCHAR *des, USHRT *src)
{
    UCHAR i,buffer[27];

    for (i = 0; i < 9; i++) {
        buffer[3*i]   = (UCHAR)(src[2*i]>>4);
        buffer[3*i+1] = (UCHAR)((src[2*i+1]&0x00F0) | (src[2*i]>>12));
        buffer[3*i+2] = (UCHAR)(src[2*i+1]>>8);
    }
    OSDAPI_RotateFont(des, buffer);
}
#endif //ENABLE_OSD_ROTATION == ON

#if ENABLE_OSD_MIRROR == ON
/**************************************************************************//**
 * Reverse the bit string of a character.
 * @param target The original character.
 * @return Reversed character.
 ******************************************************************************/
static UCHAR OSDAPI_ReverseChar(UCHAR target)
{
    UCHAR tmp,i;
    
    tmp = 0;    
    for (i = 0; i < 8; i++) {
        tmp = (tmp << 1) | ((target>>i)&0x01);
    }
        
    return tmp;
}

/**************************************************************************//**
 * Reverse the bit string of a short(2 x character).
 * @param target The original short.
 * @return Reversed short.
 ******************************************************************************/
static USHRT OSDAPI_ReverseShort(USHRT target)
{
    USHRT tmp;
    UCHAR i;
    tmp = 0;
        
    for (i = 0; i < 16; i++) {
        tmp = (tmp << 1) | ((target>>i)&0x01);
    }
    
    return tmp;
}

/**************************************************************************//**
 * Mirror one OSD font.
 * @param[out] des Pointer to destination font buffer.
 * @param[in] src Pointer to source font buffer.
 * @param width OSD font width (10 or 12).
 ******************************************************************************/
void OSDAPI_MirrorFont(UCHAR *des, UCHAR *src, UCHAR width)
{
    UCHAR i;
    UCHAR tmp1,tmp2,tmp3;
    UCHAR mrr1,mrr2,mrr3;

    for (i = 0; i < 9; i++) {
        tmp1 = OSDAPI_ReverseChar(src[i*3+0]);
        tmp2 = OSDAPI_ReverseChar(src[i*3+1]);
        tmp3 = OSDAPI_ReverseChar(src[i*3+2]);
        mrr1 = ((tmp2&0xf0) >> 4) | ((tmp1&0x0f) << 4);
        mrr2 = ((tmp1&0xf0) >> 4) | ((tmp3&0x0f) << 4);
        mrr3 = ((tmp3&0xf0) >> 4) | ((tmp2&0x0f) << 4);
        des[i*3+0] = (mrr1 << (12-width));
        des[i*3+1] = (mrr2 << (12-width));
        des[i*3+2] = (mrr3 << (12-width));
    }
}

/**************************************************************************//**
 * Mirror one indent OSD font.
 * @param[out] des Pointer to destination font buffer.
 * @param[in] src Pointer to source font buffer.
 * @param width indent OSD font width.
 ******************************************************************************/
void OSDAPI_MirrorIdentFont(USHRT *des, USHRT *src, UCHAR width)
{
    UCHAR i;
    for (i = 0; i < 18; i++) {
        des[i] = (OSDAPI_ReverseShort(src[i]) << (16-width));
    }
}
#endif //ENABLE_OSD_MIRROR == ON

#if ENABLE_OSD_FLIP == ON
/**************************************************************************//**
 * Flip one OSD font.
 * @param[out] des Pointer to destination font buffer.
 * @param[in] src Pointer to source font buffer.
 * @param height OSD font height.
 ******************************************************************************/
void OSDAPI_FlipFont(UCHAR *des, UCHAR *src, UCHAR height)
{
    UCHAR buffer[27], i;
    
    for (i = 0; i < (height/2*3); i++) {
        buffer[i] = src[height/2*3-1-i];
    }
    for (i = 0; i < height/2; i++) {
        des[i*3]   = ((buffer[i*3+1]&0xf0)>>4)+((buffer[i*3]&0x0f)<<4);
        des[i*3+1] = ((buffer[i*3]&0xf0)>>4)+((buffer[i*3+2]&0x0f)<<4);
        des[i*3+2] = ((buffer[i*3+2]&0xf0)>>4)+((buffer[i*3+1]&0x0f)<<4);
    }
}

/**************************************************************************//**
 * Flip one indent OSD font.
 * @param[out] des Pointer to destination font buffer.
 * @param[in] src Pointer to source font buffer.
 * @param height indent OSD font height.
 ******************************************************************************/
void OSDAPI_FlipIdentFont(USHRT *des, USHRT *src, UCHAR height)
{
    UCHAR i;
    
    for (i = 0; i < (height/2); i++) {
        des[i] = src[height-1-i];
        des[height-1-i] = src[i];
    }
}
#endif //ENABLE_OSD_FLIP == ON

#if ENABLE_OSD_WINDOWS == ON
/**************************************************************************//**
 * Turn on OSD window.
 * @param id Window ID.
 ******************************************************************************/
void OSDAPI_OSDWinOn(OSDWindow id)
{
    switch (id) {
        case OSD_WINDOW1:
            SC_OSD_CTRL1 |= BIT1;
            break;
        case OSD_WINDOW2:
            SC_OSD_CTRL1 |= BIT2;
            break;
        case OSD_WINDOW3:
            SC_OSD_CTRL1 |= BIT3;
            break;
        case OSD_WINDOW4:
            SC_OSD_CTRL1 |= BIT4;
            break;
        case OSD_WINDOW5:
            SC_OSD_WIN_SEL |= BIT4;
            break;
        case OSD_WINDOW6:
            SC_OSD_WIN_SEL |= BIT5;
            break;
        case OSD_WINDOW7:
            SC_OSD_WIN_SEL |= BIT6;
            break;
        case OSD_WINDOW8:
            SC_OSD_WIN_SEL |= BIT7;
            break;
        default:
            break;
    }
}

/**************************************************************************//**
 * Turn off OSD window.
 * @param id Window ID.
 ******************************************************************************/
void OSDAPI_OSDWinOff(OSDWindow id)
{
    switch (id) {
        case OSD_WINDOW1:
            SC_OSD_CTRL1 &= ~BIT1;
            break;
        case OSD_WINDOW2:
            SC_OSD_CTRL1 &= ~BIT2;
            break;
        case OSD_WINDOW3:
            SC_OSD_CTRL1 &= ~BIT3;
            break;
        case OSD_WINDOW4:
            SC_OSD_CTRL1 &= ~BIT4;
            break;
        case OSD_WINDOW5:
            SC_OSD_WIN_SEL &= ~BIT4;
            break;
        case OSD_WINDOW6:
            SC_OSD_WIN_SEL &= ~BIT5;
            break;
        case OSD_WINDOW7:
            SC_OSD_WIN_SEL &= ~BIT6;
            break;
        case OSD_WINDOW8:
            SC_OSD_WIN_SEL &= ~BIT7;
            break;
        case OSD_WIN_OFF:
        default:
            SC_OSD_CTRL1 &= 0xE1;
            SC_OSD_WIN_SEL &= 0x0F;
            break;
    }
}

/**************************************************************************//**
 * Select the accessible OSD window.
 * @param id Window ID.
 ******************************************************************************/
void OSDAPI_SelOSDWin(OSDWindow id)
{
    if (id > OSD_WINDOW8)
        return;
    SC_OSD_WIN_SEL = (SC_OSD_WIN_SEL & 0xf8) | id;
}

/**************************************************************************//**
 * Set OSD window width/height unit.
 * @param width Set unit size (number of pixels) of window width.
 * @param height Set unit size(number of pixels) of window height.
 ******************************************************************************/
void OSDAPI_SetOSDWinSizeUnit(UCHAR width, UCHAR height)
{
    ucWinUnitWidth  = width;
    ucWinUnitHeight = height;
}

/**************************************************************************//**
 * Set OSD window position and size.
 * The units of position and size are set by OSDAPI_SetOSDWinSizeUnit.
 * @param sx Start position of x.
 * @param sy Start position of y.
 * @param ex End position of x.
 * @param ey End position of y.
 ******************************************************************************/
void OSDAPI_SetOSDWinSize(USHRT sx, USHRT sy, USHRT ex, USHRT ey)
{
#if ENABLE_OSD_ROTATION == ON
    UCHAR id, rot;

    sx = sx * ucWinUnitWidth;
    ex = (ex + 1) * ucWinUnitWidth;
    sy = sy * ucWinUnitHeight;
    ey = (ey + 1) * ucWinUnitHeight;

    switch(GetOSDPosRot()) {
        case OSD_POS_ROT_90:
            OSDAPI_RotateOSDWinPosition(sx, sy, ex, ey, OSD_WIN_DEGREE_90, FALSE);
            break;
        case OSD_POS_ROT_180:
            OSDAPI_RotateOSDWinPosition(sx, sy, ex, ey, OSD_WIN_DEGREE_180, FALSE);
            break;
        case OSD_POS_ROT_270:
            OSDAPI_RotateOSDWinPosition(sx, sy, ex, ey, OSD_WIN_DEGREE_270, FALSE);
            break;
        default :
            OSDAPI_RotateOSDWinPosition(sx, sy, ex, ey, OSD_WIN_DEGREE_0, FALSE);
            break;
    }

    id = (SC_OSD_WIN_SEL & 0x07);
    rot = GetOSDPosRot();
    SetOSDWinRotStatus(id, rot);
#else
    USHRT tmp1;

    sx = sx * ucWinUnitWidth;
    ex = (ex + 1) * ucWinUnitWidth;
    sy = sy * ucWinUnitHeight;
    ey = (ey + 1) * ucWinUnitHeight;

    SC_OSD_WIN_HOR_START_LO = (UCHAR)sx;
    SC_OSD_WIN_HOR_END_LO = (UCHAR)ex;
    tmp1 = ((sx >> 8) & 0x000F) | ((ex >> 4) & 0x00F0);
    SC_OSD_WIN_HOR_HI = (UCHAR)tmp1;
    SC_OSD_WIN_VER_START_LO = (UCHAR)sy;
    SC_OSD_WIN_VER_END_LO = (UCHAR)ey;
    tmp1 = ((sy >> 8) & 0x000F) | ((ey >> 4) & 0x00F0);
    SC_OSD_WIN_VER_HI = (UCHAR)tmp1;

    WaitDisVSync();
#endif //ENABLE_OSD_ROTATION == ON
}

/**************************************************************************//**
 * Set attribute of the selected window.
 * @param attr OSD window attribute.
 ******************************************************************************/
void OSDAPI_SetOSDWinAttr(OSDWinAttr attr)
{
    SC_OSD_WIN_COLOR = attr.ucWinClr;
    if (CHK_WINATTR_BEVEL(attr)) {
        SC_OSD_WIN_ATTRIBUTE |= BIT7;
    }
    else {
        SC_OSD_WIN_ATTRIBUTE &= ~BIT7;
    }
    
    if (CHK_WINATTR_FADEINOUT(attr)) {
        SC_OSD_WIN_ATTRIBUTE |= BIT0;
    }
    else {
        SC_OSD_WIN_ATTRIBUTE &= ~BIT0;
    }

    if (CHK_WINATTR_SHADOW(attr)) {
        SC_OSD_WIN_ATTRIBUTE |= BIT1;
    }
    else {
        SC_OSD_WIN_ATTRIBUTE &= ~BIT1;
    }

    if (CHK_WINATTR_BEVEL_SHADOW_TRANS(attr)) {
        SC_OSD_CODE_FC_CTL |= BIT2;
    }
    else {
        SC_OSD_CODE_FC_CTL &= ~BIT2;
    }

    //SC_OSD_WIN_ATTRIBUTE |= BIT4;   // Force translucent for window
    SC_OSD_WIN_ATTRIBUTE |= ((attr.ucBorderAttr & 0x30) << 1); // Bevel Type
    SC_OSD_WIN_BEVEL_WIDTH = attr.ucBorderAttr & 0x07; // Bevel Width
    SC_OSD_WIN_BEVEL_COLOR_R = attr.ucRBorderClr;
    SC_OSD_WIN_BEVEL_COLOR_L = attr.ucLBorderClr;
}

/**************************************************************************//**
 * Set OSD window transparency.
 * @param tran Level of OSD window transparency. Range is 0 to 8.
 ******************************************************************************/
void OSDAPI_SetOSDWinTran(UCHAR tran)
{
    if (tran == 0xFF) {
        return;
    }
    else if (tran > 8) {
        tran = 8;
    }

    if (tran == 0) {
        SC_OSD_TRANSLUCENT_CTL &= 0xC7;//TP_LEVEL_TWO
        SC_OSD_WIN_ATTRIBUTE &= ~BIT4;//WIN_MIX
    }
    else {
        SC_OSD_TRANSLUCENT_CTL = (SC_OSD_TRANSLUCENT_CTL & 0xC7) | ((tran - 1) << 3);//TP_LEVEL_TWO
        SC_OSD_WIN_ATTRIBUTE |= BIT4;//WIN_MIX
    }
}

/**************************************************************************//**
 * Set gradient color of window.
 * @param dir Left-right or top-button direction.
 * @param inc Increase or decrease gray variance.
 * @param step Increase/decrease gray levels per step.
 * @param pixel Number of pixel per step.
 ******************************************************************************/
void OSDAPI_SetOSDWinGrad(UCHAR dir, UCHAR inc, UCHAR step, UCHAR pixel)
{
#if ENABLE_OSD_ROTATION == ON
    switch(GetOSDPosRot()) {
        case OSD_POS_ROT_90:
            dir = ~dir;
            break;
        case OSD_POS_ROT_180:
            inc = ~inc;
            break;
        case OSD_POS_ROT_270:
            dir = ~dir;
            //inc = ~inc;
            break;
        default:
            break;
    }
#endif //ENABLE_OSD_ROTATION == ON

    SC_OSD_WIN_GRADIENT_CTRL = 0x00;
    OSDAPI_TurnOnOffOSDWinGrad(ON);
    SC_OSD_WIN_GRADIENT_CTRL |= ((dir&BIT0)<<4);
    SC_OSD_WIN_GRADIENT_RED_COLOR = ((pixel&0x1F) | ((inc&BIT0) << 7));
    SC_OSD_WIN_GRADIENT_GREEN_COLOR = ((pixel&0x1F) | ((inc&BIT0) << 7));
    SC_OSD_WIN_GRADIENT_BLUE_COLOR = ((pixel&0x1F) | ((inc&BIT0) << 7));
    SC_OSD_WIN_GRADIENT_RED_STEP = step;
    SC_OSD_WIN_GRADIENT_GREEN_STEP = step;
    SC_OSD_WIN_GRADIENT_BLUE_STEP = step;
}

/**************************************************************************//**
 * Turn on/off OSD gradient function.
 * @param on On/off OSD gradient.
 ******************************************************************************/
void OSDAPI_TurnOnOffOSDWinGrad(UCHAR on)
{
    if (on) {
        SC_OSD_WIN_GRADIENT_CTRL |= 0x2F;
    }
    else {
        SC_OSD_WIN_GRADIENT_CTRL &= 0xD0;
    }
}

#if ENABLE_OSD_ROTATION == ON
/**************************************************************************//**
 * Rotate selected OSD window.
 * @param id Window ID.
 * @param rot Rotation degree.
 ******************************************************************************/
void OSDAPI_RotateOSDWin(OSDWindow id, OSDPosRotation rot)
{
    USHRT sx, sy, ex, ey, tmp;
    UCHAR dir;
    OSDPosRotation prev_rot;
    OSDWinDegree degree;

    if (id > OSD_WINDOW8) {
        return;
    }

    OSDAPI_SelOSDWin(id);

    tmp = (USHRT)SC_OSD_WIN_HOR_HI;
    sx = ((tmp & 0x0F) << 8) + SC_OSD_WIN_HOR_START_LO;
    ex = ((tmp & 0xF0) << 4) + SC_OSD_WIN_HOR_END_LO;
    tmp = (USHRT)SC_OSD_WIN_VER_HI;
    sy = ((tmp & 0x0F) << 8) + SC_OSD_WIN_VER_START_LO;
    ey = ((tmp & 0xF0) << 4) + SC_OSD_WIN_VER_END_LO;

    prev_rot = GetOSDWinRotStatus(id);
    degree = (NUM_OSD_WIN_DEGREE + rot - prev_rot) % NUM_OSD_WIN_DEGREE;

    if ((prev_rot == OSD_POS_ROT_90) || (prev_rot == OSD_POS_ROT_270)) {
        dir = TRUE;
    }
    else {
        dir = FALSE;
    }
    OSDAPI_RotateOSDWinPosition(sx, sy, ex, ey, degree, dir);

    if ((degree == OSD_WIN_DEGREE_90) || (degree == OSD_WIN_DEGREE_270)) {
        dir = !(SC_OSD_WIN_GRADIENT_CTRL & BIT4);
        SC_OSD_WIN_GRADIENT_CTRL &= ~BIT4;
        SC_OSD_WIN_GRADIENT_CTRL |= (dir << 4);
    }

//    SC_OSD_WIN_GRADIENT_RED_COLOR = ((pixel&0x1F) | ((inc&BIT0) << 7));
//    SC_OSD_WIN_GRADIENT_GREEN_COLOR = ((pixel&0x1F) | ((inc&BIT0) << 7));
//    SC_OSD_WIN_GRADIENT_BLUE_COLOR = ((pixel&0x1F) | ((inc&BIT0) << 7));

    SetOSDWinRotStatus(id, rot);
}

/**************************************************************************//**
 * Set the position of OSD window with rotation.
 * @param sx Start position of x.
 * @param sy Start position of y.
 * @param ex End position of x.
 * @param ey End position of y.
 * @param degree Rotation degree.
 * @param rot TRUE if OSD has been rotated 90/270 degree. Otherwise FALSE.
 ******************************************************************************/
static void OSDAPI_RotateOSDWinPosition(USHRT sx, USHRT sy, USHRT ex, USHRT ey, OSDWinDegree degree, UCHAR rot)
{
    USHRT fw, fh, ow, oh;
    USHRT tmp1, tmp2;
    UCHAR border;

    if (rot) {
        fh = OSDAPI_GetOSDFontWidth();
        fw = OSDAPI_GetOSDFontHeight();
        oh = OSDAPI_GetOSDWidth();
        ow = OSDAPI_GetOSDHeight();
    }
    else {
        fw = OSDAPI_GetOSDFontWidth();
        fh = OSDAPI_GetOSDFontHeight();
        ow = OSDAPI_GetOSDWidth();
        oh = OSDAPI_GetOSDHeight();
    }

    border = 0;
    if (SC_OSD_WIN_ATTRIBUTE & BIT7) {
        border = (SC_OSD_WIN_BEVEL_WIDTH & 0x07) + 1;
    }

    switch (degree) {
        case OSD_WIN_DEGREE_90 :
            tmp1 = sx;
            tmp2 = ex;
            sx = fh * oh - ey;
            if (sx >= border) {
                sx -= border;
            }
            ex = fh * oh - sy - border;
            sy = tmp1;
            ey = tmp2;
            break;
        case OSD_WIN_DEGREE_180 :
            tmp1 = sx;
            tmp2 = ex;
            sx = fw * ow - tmp2;
            if (sx >= border) {
                sx -= border;
            }
            ex = fw * ow - tmp1 - border;
            tmp1 = sy;
            tmp2 = ey;
            sy = fh * oh - tmp2;
            if (sy >= border) {
                sy -= border;
            }
            ey = fh * oh - tmp1 - border;
            break;
        case OSD_WIN_DEGREE_270 :
            tmp1 = sx;
            tmp2 = ex;
            sx = sy;
            ex = ey;
            sy = fw * ow - tmp2;
            if (sy >= border) {
                sy -= border;
            }
            ey = fw * ow - tmp1 - border;
            break;
        default :
            break;
    }

    SC_OSD_WIN_HOR_START_LO = (UCHAR)sx;
    SC_OSD_WIN_HOR_END_LO = (UCHAR)ex;
    tmp1 = ((sx >> 8) & 0x000F) | ((ex >> 4) & 0x00F0);
    SC_OSD_WIN_HOR_HI = (UCHAR)tmp1;
    SC_OSD_WIN_VER_START_LO = (UCHAR)sy;
    SC_OSD_WIN_VER_END_LO = (UCHAR)ey;
    tmp1 = ((sy >> 8) & 0x000F) | ((ey >> 4) & 0x00F0);
    SC_OSD_WIN_VER_HI = (UCHAR)tmp1;

    WaitDisVSync();
}
#endif //ENABLE_OSD_ROTATION == ON
#endif //ENABLE_OSD_WINDOWS == ON

/**************************************************************************//**
 * Set OSD zoom times.
 * @param times OSD zoom times. The range is 0~3.
 ******************************************************************************/
void OSDAPI_SetHVZoom(UCHAR times)
{
    if (times == 0) {
        SC_OSD_ZOOM_CTL &= ~(BIT1|BIT0);
    } 
    else {
        SC_OSD_ZOOM_CTL |= (BIT1|BIT0);
        SC_OSD_VHGLOB_ZMRNG = 0x55*times;
    }
}

/**************************************************************************//**
 * Set OSD foreground and background transparency.
 * @param tran Level of OSD fg/bg transparency. Range is 0 to 8.
 ******************************************************************************/
void OSDAPI_SetOSDFgBgTran(UCHAR tran)
{
    if (tran == 0xFF) {
        return;
    }
    else if (tran > 8) {
        tran = 8;
    }

    if (tran == 0) {
        SC_OSD_TRANSLUCENT_CTL &= 0xF8;//TP_LEVEL_ONE
        SC_OSD_CODE_FC_CTL &= ~0x30;//BG_MIX_EN and FG_MIX_EN
    }
    else {
        SC_OSD_TRANSLUCENT_CTL = (SC_OSD_TRANSLUCENT_CTL & 0xF8) | (tran - 1);//TP_LEVEL_ONE
        SC_OSD_CODE_FC_CTL |= 0x30;//BG_MIX_EN and FG_MIX_EN
    }
}
        
/**************************************************************************//**
 * Set OSD special background transparency.
 * @param tran Level of OSD special BG transparency. Range is 0 to 8.
 ******************************************************************************/
void OSDAPI_SetOSDSpecialBgTran(UCHAR tran)
{
    if (tran == 0xFF) {
        return;
        }
    else if (tran > 8) {
        tran = 8;
    }
    // NOTE:
    // This function works ONLY when the BG_INDEX[3:0] = b'0001!
    // and it can't be separately configured from WINDOW transparency! (commonly used)
    if (tran == 0) {
        SC_OSD_TRANSLUCENT_CTL &= 0xC7;//TP_LEVEL_TWO
        SC_OSD_CODE_FC_CTL &= ~BIT5;//BG_MIX_EN
    }
    else {
        SC_OSD_TRANSLUCENT_CTL = (SC_OSD_TRANSLUCENT_CTL & 0xC7) | ((tran - 1) << 3);//TP_LEVEL_TWO
        SC_OSD_CODE_FC_CTL |= BIT5;//BG_MIX_EN
    }
}

/**************************************************************************//**
 * Set OSD fade in/out.
 * @param vspeed OSD fade in/out vertical frecuency for every step
 * @param hspeed OSD fade in/out horizontal frecuency for every step
 * @param vstep OSD fade in/out vertical step
 * @param hstep OSD fade in/out horizontal step
 * @param dir OSD fade in/out direction select
 ******************************************************************************/
void OSDAPI_SetOSDFadeInOut(UCHAR vspeed, UCHAR hspeed, UCHAR vstep, UCHAR hstep, UCHAR dir)
{
    if (vstep == 0 && hstep == 0) {//disable fade in/out function
        SC_OSD_FADE_STEP = 0x00;
        SC_OSD_FADE_FREQ = 0x00;
        }
    else {
        SC_OSD_CODE_FC_CTL |= (dir & 0x03) << 6;
        SC_OSD_FADE_STEP = ((vstep & 0x0f) << 4) | (hstep & 0x0f);
        SC_OSD_FADE_FREQ = ((vspeed & 0x07) << 4) | (hspeed & 0x0f) | BIT7;
    }
}
