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
#include "ScalerReg.h"
#include "ScalerAccess.h"
#include "BFAPI.h"

//******************************************************************************
// M A C R O   D E F I N I T I O N S
//******************************************************************************
/*!
 * BFAPI Version.
 * The following string is the specific string for EasyWriter.
 * We can show the version on EasyWriter.
 */
static code UCHAR SpecTab_BFVersion[] = 
{
    0x55, 0xaa, 0x66, 0x99, __FILE__" Version 3.0.00 "__DATE__"#"
};

/*!
 * On/off the adjustment of six axle colors.
 * We turn it off now because this function is conflicting to local color adjustments.
 */
#define BFAPI_ENABLE_SIX_AXIE_ADJ 0

#define CurBFGen()   (ucBFConfig&BIT0) /*! Get the status of CM generation. */
#define CurBFWin()   ((ucBFConfig&BIT1) >> 1) /*! Get the ID of bright frame window. */
#define SetBFGen(a)  {ucBFConfig |= (a&BIT0);} /*! Set CM generation. */
#define SetBFWin(a)  {ucBFConfig = (ucBFConfig&0xFD) | ((a&BIT0) << 1);} /*! Set the ID of bright frame window. */

//******************************************************************************
// G L O B A L   V A R I A B L E S
//******************************************************************************

//******************************************************************************
// S T A T I C   V A R I A B L E S
//******************************************************************************
/*!
 * CM configurations.
 * BIT0 is for CM generation.
 * BIT1 is for ID of bright frame window.
 */
static xdata UCHAR ucBFConfig = 0;

//******************************************************************************
// E X T E R N A L   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
extern void WaitDisVSync(void);

//******************************************************************************
// F U N C T I O N   B O D Y S
//******************************************************************************

/**************************************************************************//**
 * Initialize bright-frame related registers (all color to default state.
 * CM generation :
 *   BF_ONE_GEN : NT68168/NT68668/NT68669/NT68671~3/NT68690 or older.
 *   BF_TWO_GEN : NT68169/NT68650/NT68660/NT68676/NT68652/NT68750/NT68360 or later.
 * @param gen Generation of CM.
 ******************************************************************************/
void BFAPI_Init(BFGeneration gen)
{
    UCHAR tmpReg;

    SetBFGen(gen);
    BFAPI_SetActiveWindow(BF_WINDOW_2);
    BFAPI_SetWindowSize(BF_WINDOW_INIT);
    BFAPI_ColorEnhance(BF_COLOR_INIT);
    BFAPI_SetPreACEMode(0); // Reset I-Gamma
    BFAPI_DisableACEMode();
    BFAPI_SetHHTable(0);
    BFAPI_SetHSTable(0);
    BFAPI_SetHITable(0);
    BFAPI_DisableCM(CM_ALL);
    BFAPI_SetYPeaking(0);
    BFAPI_SetActiveWindow(BF_WINDOW_1);
    BFAPI_SetWindowSize(BF_WINDOW_INIT);
    BFAPI_ColorEnhance(BF_COLOR_INIT);
    BFAPI_SetPreACEMode(0); // Reset I-Gamma
    BFAPI_DisableACEMode();
    BFAPI_SetHHTable(0);
    BFAPI_SetHSTable(0);
    BFAPI_SetHITable(0);
    BFAPI_DisableCM(CM_ALL);
    BFAPI_SetYPeaking(0);

    tmpReg = SC_BF_WIN_BORDER_CTRL;
    SC_BF_WIN_BORDER_CTRL = tmpReg & (~0xC0);
    SC_BF_WIN_BORDER_EN = 0x00; // Disable Border Type

    BFAPI_DisableWindow(BF_WINDOW_1);
    BFAPI_DisableWindow(BF_WINDOW_2);
}

/**************************************************************************//**
 * Enable BF window.
 * @param bfw The ID of bright frame window (BF_WINDOW_1 or BF_WINDOW_2).
 ******************************************************************************/
void BFAPI_EnableWindow(BFWindow bfw)
{
    UCHAR tmpReg1, tmpReg2;

    tmpReg1 = SC_BRIGHT_FRM_CTRL;

    tmpReg1 |= 0x10; // Reference to display

    tmpReg2 = SC_BF_WIN_BORDER_CTRL;
    switch (bfw) {
        case BF_WINDOW_1:
            SC_BRIGHT_FRM_CTRL = tmpReg1 | BRIGHT_FRM1_EN;
            SC_BF_WIN_BORDER_CTRL = tmpReg2 | 0x03;
            break;
        case BF_WINDOW_2:
            SC_BRIGHT_FRM_CTRL = tmpReg1 | BRIGHT_FRM2_EN;
            SC_BF_WIN_BORDER_CTRL = tmpReg2 | 0x0C;
            break;
    }
}

/**************************************************************************//**
 * Disable BF window.
 * @param bfw The ID of bright frame window (BF_WINDOW_1 or BF_WINDOW_2).
 ******************************************************************************/
void BFAPI_DisableWindow(BFWindow bfw)
{
    UCHAR tmpReg1;

    tmpReg1 = SC_BRIGHT_FRM_CTRL;
    if (bfw == BF_WINDOW_1)
        SC_BRIGHT_FRM_CTRL = tmpReg1 & (~BRIGHT_FRM1_EN);
    else
        SC_BRIGHT_FRM_CTRL = tmpReg1 & (~BRIGHT_FRM2_EN);
}

/**************************************************************************//**
 * Specify a bright frame window for color adjustments.
 * @param bfw The ID of bright frame window (BF_WINDOW_1 or BF_WINDOW_2).
 ******************************************************************************/
void BFAPI_SetActiveWindow(BFWindow bfw)
{
    UCHAR tmpReg1;

    SetBFWin(bfw);

    tmpReg1 = SC_BRIGHT_FRM_SEL;
    if (bfw == BF_WINDOW_1)
        SC_BRIGHT_FRM_SEL = tmpReg1 & 0xfe;
    else
        SC_BRIGHT_FRM_SEL = tmpReg1 | 0x01;
}

/**************************************************************************//**
 * Set bright frame window size.
 *   BF_WINDOW_FULLSCREEN : Full screen.
 *   BF_WINDOW_LEFTSIZE   : Left-side screen.
 *   BF_WINDOW_RIGHTSIZE  : Right-side screen.
 *   BF_WINDOW_INIT       : Full screen.
 *
 * BF_WINDOW_INIT is different from BF_WINDOW_FULLSCREEN.
 * The h/w start positions are zero when the type is BF_WINDOW_INIT.
 * And the h/w start positions of BF_WINDOW_FULLSCREEN depended on the display aspect ratio.
 * We use BF_WINDOW_INIT only when system is in initial stage.
 * Other stages, e.x. normal display, use the other three type.
 *
 * @param type Bright frame window size.
 ******************************************************************************/
void BFAPI_SetWindowSize(BFWSize type)
{
    USHRT width, height;
    USHRT hstart, tmphs, vstart, tmpvs;

    width = (USHRT) SC_DH_BG_WID_HI * 256 + SC_DH_BG_WID_LO;
    height = (USHRT) SC_DV_BG_LEN_HI * 256 + SC_DV_BG_LEN_LO;

    if (type == BF_WINDOW_INIT) {
        hstart = 0;
        vstart = 0;
    }
    else {
        // If display is over-scan, the BG begin is larger than ACT begin.
        // If display is under-scan, the BG begin is smaller than ACT begin.
        // If display is normal, the BG begin is equal to ACT begin.
        // The hstart and vstart of BF window must consider the all the above conditions.
        hstart = (USHRT) SC_GRAPHIC_DISP_HOR_ACT_BEG_HI * 256
                         + SC_GRAPHIC_DISP_HOR_ACT_BEG_LO;
        tmphs = ((USHRT) SC_DH_BG_BEG_HI * 256 + SC_DH_BG_BEG_LO);
        if (hstart < tmphs) {
            hstart = 0; // BF HStart under over-scan display.
        }
        else {
            hstart -= tmphs; // BF HStart under under-scan and normal display.
        }
        vstart = (USHRT) SC_GRAPHIC_DISP_VER_ACT_BEG_HI * 256
                         + SC_GRAPHIC_DISP_VER_ACT_BEG_LO;
        tmpvs = ((USHRT) SC_DV_BG_BEG_HI * 256 + SC_DV_BG_BEG_LO);
        if (vstart < tmpvs) {
            vstart = 0;
        }
        else {
            vstart -= tmpvs;
        }
        width = width - 2 * hstart;
        height = height - 2 * vstart;
    }

    if (type == BF_WINDOW_FULLSCREEN) {
        BFAPI_SetCustomWindow(hstart, vstart, width, height);
    }
    else if (type == BF_WINDOW_LEFTSIZE) {
        width >>= 1;
        BFAPI_SetCustomWindow(hstart, vstart, width, height);
    }
    else if (type == BF_WINDOW_RIGHTSIZE) {
        width >>= 1;
        BFAPI_SetCustomWindow(hstart + width, vstart, width, height);
    }
}

/**************************************************************************//**
 * Set user-defined bright frame window size. The unit is pixel.
 * @param x Horizontal start position of BF window on display.
 * @param y Vertical start position of BF window on display.
 * @param width Width of BF window on display.
 * @param height Height of BF window on display.
 ******************************************************************************/
void BFAPI_SetCustomWindow(USHRT x, USHRT y, USHRT width, USHRT height)
{
    SC_BRIGHT_FRM_HS_LO = (UCHAR)x;
    SC_BRIGHT_FRM_HS_HI = (UCHAR)(x>>8);
    SC_BRIGHT_FRM_HW_LO = (UCHAR)width;
    SC_BRIGHT_FRM_HW_HI = (UCHAR)(width>>8);
    SC_BRIGHT_FRM_VS_LO = (UCHAR)y;
    SC_BRIGHT_FRM_VS_HI = (UCHAR)(y>>8);
    SC_BRIGHT_FRM_VH_LO = (UCHAR)height;
    SC_BRIGHT_FRM_VH_HI = (UCHAR)(height>>8);
}

/**************************************************************************//**
 * Enable one or more CM functions.
 * The functions are
 *   CM_BR  - brightness
 *   CM_CN  - contrast
 *   CM_HUE - hue
 *   CM_SAT - saturation
 *   CM_INT - intensity
 *   CM_HH  - hue adjustment on hue
 *   CM_HS  - saturation adjustment on hue
 *   CM_HI  - intensity adjustment on hue
 *   CM_ALL - all function
 * @param func One or more CM functions.
 ******************************************************************************/
void BFAPI_EnableCM(UCHAR func)
{
    if (func & CM_BR) {
        SC_CM_COLOR_CTRL |= BIT6;
    }
    if (func & CM_CN) {
        SC_CM_COLOR_CTRL |= BIT5;
    }
    if (func & CM_HUE) {
        SC_CM_COLOR_CTRL |= BIT4;
    }
    if (func & CM_SAT) {
        SC_CM_COLOR_CTRL |= BIT3;
    }
    if (func & CM_INT) {
        SC_CM_COLOR_CTRL |= BIT2;
    }
    if (func & CM_HH) {
        SC_CM_COLOR_ENHANCEMENT_CTRL |= (BIT7|BIT0);
    }
    if (func & CM_HS) {
        SC_CM_COLOR_ENHANCEMENT_CTRL |= (BIT6|BIT0);
    }
    if (CurBFGen() != BF_ONE_GEN) {
        if (func & CM_HI) {
            SC_CM_COLOR_ENHANCEMENT_CTRL |= (BIT4|BIT0);
        }
    }
}

/**************************************************************************//**
 * Disable one or more CM functions.
 * The functions are
 *   CM_BR  - brightness
 *   CM_CN  - contrast
 *   CM_HUE - hue
 *   CM_SAT - saturation
 *   CM_INT - intensity
 *   CM_HH  - hue adjustment on hue
 *   CM_HS  - saturation adjustment on hue
 *   CM_HI  - intensity adjustment on hue
 *   CM_ALL - all function
 * @param func One or more CM functions.
 ******************************************************************************/
void BFAPI_DisableCM(UCHAR func)
{
    if (func & CM_BR) {
        SC_CM_COLOR_CTRL &= ~BIT6;
    }
    if (func & CM_CN) {
        SC_CM_COLOR_CTRL &= ~BIT5;
    }
    if (func & CM_HUE) {
        SC_CM_COLOR_CTRL &= ~BIT4;
    }
    if (func & CM_SAT) {
        SC_CM_COLOR_CTRL &= ~BIT3;
    }
    if (func & CM_INT) {
        SC_CM_COLOR_CTRL &= ~BIT2;
    }
    if (func & CM_HH) {
        SC_CM_COLOR_ENHANCEMENT_CTRL &= ~BIT7;
    }
    if (func & CM_HS) {
        SC_CM_COLOR_ENHANCEMENT_CTRL &= ~BIT6;
    }
    if (CurBFGen() != BF_ONE_GEN) {
        if (func & CM_HI) {
            SC_CM_COLOR_ENHANCEMENT_CTRL &= ~BIT4;
        }
    }
    if ((SC_CM_COLOR_ENHANCEMENT_CTRL & 0xE0) == 0x00) {
        SC_CM_COLOR_ENHANCEMENT_CTRL &= ~BIT0;
    }
}

/**************************************************************************//**
 * Set the offset of red color.
 * @param offset Value of offset adjustments. Range is 0~255. Default is 0x80.
 ******************************************************************************/
void BFAPI_SetROffset(UCHAR offset)
{
    if (offset < 0x80)
        offset |= 0x80;
    else
        offset &= ~0x80;
    SC_CM_BRIGHTNESS_RED = offset;
}

/**************************************************************************//**
 * Set the offset of green color.
 * @param offset Value of offset adjustments. Range is 0~255. Default is 0x80.
 ******************************************************************************/
void BFAPI_SetGOffset(UCHAR offset)
{
    if (offset < 0x80)
        offset |= 0x80;
    else
        offset &= ~0x80;
    SC_CM_BRIGHTNESS_GREEN = offset;
}

/**************************************************************************//**
 * Set the offset of blue color.
 * @param offset Value of offset adjustments. Range is 0~255. Default is 0x80.
 ******************************************************************************/
void BFAPI_SetBOffset(UCHAR offset)
{
    if (offset < 0x80)
        offset |= 0x80;
    else
        offset &= ~0x80;
    SC_CM_BRIGHTNESS_BLUE = offset;
}

/**************************************************************************//**
 * Set the gain of red color.
 * @param gain Value of gain adjustments. Range is 0~255. Default is 0x80.
 ******************************************************************************/
void BFAPI_SetRGain(UCHAR gain)
{
    SC_CM_CONTRAST_RED = gain;
}

/**************************************************************************//**
 * Set the gain of green color.
 * @param gain Value of gain adjustments. Range is 0~255. Default is 0x80.
 ******************************************************************************/
void BFAPI_SetGGain(UCHAR gain)
{
    SC_CM_CONTRAST_GREEN = gain;
}

/**************************************************************************//**
 * Set the gain of blue color.
 * @param gain Value of gain adjustments. Range is 0~255. Default is 0x80.
 ******************************************************************************/
void BFAPI_SetBGain(UCHAR gain)
{
    SC_CM_CONTRAST_BLUE = gain;
}

/**************************************************************************//**
 * Set global hue.
 * @param hue Value of hue adjustments. Range is 0~255. Default is 0x80.
 ******************************************************************************/
void BFAPI_SetHue(UCHAR hue)
{
    if (CurBFGen() != BF_ONE_GEN) {
        if (hue < 0x80) {
            hue = 0x80 + hue;
        }
        else {
            hue &= ~0x80;
        }
    }
    else {
        if (hue < 0x80) {
            hue = ~hue;
        }
        else {
            hue &= ~0x80;
        }
    }
    
    SC_CM_HUE = hue;
}

/**************************************************************************//**
 * Set global saturation.
 * @param sat Value of saturation adjustments. Range is 0~255. Default is 0x80.
 ******************************************************************************/
void BFAPI_SetSaturation(UCHAR sat)
{
    SC_CM_SATURATION = sat;
}

/**************************************************************************//**
 * Set global intensity.
 * @param intensity Value of intensity adjustments. Range is 0~255. Default is 0x80.
 ******************************************************************************/
void BFAPI_SetIntensity(UCHAR intensity)
{
    SC_CM_INTENSITY = intensity;
}

/**************************************************************************//**
 * Enhance sharpness of image.
 * @param shp Value of sharpness adjustments. Range is 0~15. Default is 0 (Disable sharpness).
 ******************************************************************************/
void BFAPI_SetSharpness(UCHAR shp)
{
    UCHAR tmpReg;

    tmpReg = SC_BK_H_SHAP_CTRL & 0xA0;

    if (shp == 0) {
        SC_BK_H_SHAP_CTRL = tmpReg;
    }
    else if (shp & BIT7) {
        shp = shp & 0x0F;
        SC_BK_H_SHAP_CTRL = tmpReg | BK_H_ASRP | BK_H_SRPSMO | shp;
    }
    else {
        shp = shp & 0x0F;
        SC_BK_H_SHAP_CTRL = tmpReg | BK_H_ASRP | shp;
    }
}

/**************************************************************************//**
 * Set Y peaking.
 * @param yp Value of Y peaking adjustments. Range is 0~5. Default is 0 (Disable Y peaking).
 ******************************************************************************/
void BFAPI_SetYPeaking(UCHAR yp)
{
    if (yp == 0) {
        SC_YC_PEAKING_CTRL = 0x00;
    }
    else {
        SC_YC_PEAKING_CTRL = 0x01;
        if (yp == 1)
            yp = 0x04;
        else if (yp == 2)
            yp = 0x05;
        else
            yp = ((yp - 1) << 2) + 1;
        SC_LUMA_PEAKING_CTRL = yp;
    }
}

/**************************************************************************//**
 * Set text enhancement.
 * @param txt Value of text enhancement. Range is 0~7. Default is 0 (Disable text enhancement).
 ******************************************************************************/
void BFAPI_SetTextEnhancement(UCHAR txt)
{
    if (txt == 0) {
        SC_YC_PEAKING_CTRL &= ~BIT1;
        SC_TEXT_PEAKING_CTRL = 0x00;
        SC_UNDER_SHOOT_CLAMP_EN &= ~BIT0;
    }
    else {
        SC_YC_PEAKING_CTRL |= BIT1;
        SC_TEXT_PEAKING_CTRL = (txt  << 4) | 0x83;
        SC_UNDER_SHOOT_CLAMP_EN |= BIT0;
    }
}

#if BFAPI_ENABLE_SIX_AXIE_ADJ == 1
/**************************************************************************//**
 * Adjust hue on 6-axles colors.
 * Color ID is
 *   BF_SIXAXIE_RED,
 *   BF_SIXAXIE_YELLOW,
 *   BF_SIXAXIE_GREEN,
 *   BF_SIXAXIE_CYAN,
 *   BF_SIXAXIE_BLUE or
 *   BF_SIXAXIE_MANG.
 * @param item ID of 6-axles colors.
 * @param more Value of hue adjustment.s
 ******************************************************************************/
void BFAPI_SixAxieAdjustment(BFSixAxie item, UCHAR more)
{
    UCHAR ax0, ax1, ax2;
    UCHAR value;

    ax1 = item * 4;
    ax0 = (item * 4 + BF_IDV_COLOR_NUMBER - 1) % BF_IDV_COLOR_NUMBER;
    ax2 = (item * 4 + 1) % BF_IDV_COLOR_NUMBER;

    SC_CM_COLOR_ENHANCEMENT_CTRL &= ~BIT1;
    SC_CM_INDEX_ACCESS_CTRL = 0x01;

    if (more < 0x80)
        value = (0x7f - more) / 2;
    else
        value = 0x80 + (more - 0x80) / 2;

    SC_CM_INDEX_ACCESS_ADDR = ax0;
    SC_CM_INDEX_ACCESS_PORT = value;
    SC_CM_INDEX_ACCESS_ADDR = ax2;
    SC_CM_INDEX_ACCESS_PORT = value;

    if (more < 0x80)
        value = (0x7f - more);

    SC_CM_INDEX_ACCESS_ADDR = ax1;
    SC_CM_INDEX_ACCESS_PORT = value;

    SC_CM_COLOR_ENHANCEMENT_CTRL |= BIT1;

}
#else
/**************************************************************************//**
 * Adjust skin tone.
 * @param value Hue adjustment of skin tone. Range is 0~255. Default is 0.
 ******************************************************************************/
void BFAPI_CorrectFleshTone(UCHAR value)
{
    xdata USHRT i;

    i = (USHRT) value * 48 / 255;

    SC_CM_COLOR_ENHANCEMENT_CTRL &= ~BIT1;
    SC_CM_INDEX_ACCESS_CTRL = 0x01;
    SC_CM_INDEX_ACCESS_ADDR = 0x00;
    SC_CM_INDEX_ACCESS_PORT = i / 2;
    SC_CM_INDEX_ACCESS_ADDR = 0x01;
    SC_CM_INDEX_ACCESS_PORT = i * 3 / 4;
    SC_CM_INDEX_ACCESS_ADDR = 0x02;
    SC_CM_INDEX_ACCESS_PORT = i;
    SC_CM_INDEX_ACCESS_ADDR = 0x03;
    SC_CM_INDEX_ACCESS_PORT = i * 3 / 4;
    SC_CM_COLOR_ENHANCEMENT_CTRL |= BIT1;
}

/**************************************************************************//**
 * Enhance saturation of red color.
 * @param value The value of saturation adjustment. Range is 0~255. Default is 128.
 ******************************************************************************/
void BFAPI_EnhanceRed(UCHAR value)
{
    xdata USHRT i;

    //red enhance
    SC_CM_COLOR_ENHANCEMENT_CTRL &= ~BIT1;
    SC_CM_INDEX_ACCESS_CTRL = 0x02;
    i = value;
    i = (i >> 1) + 0x40;
    SC_CM_INDEX_ACCESS_ADDR = 0x17;
    SC_CM_INDEX_ACCESS_PORT = i;
    SC_CM_INDEX_ACCESS_ADDR = 0x00;
    SC_CM_INDEX_ACCESS_PORT = value;
    SC_CM_INDEX_ACCESS_ADDR = 0x01;
    SC_CM_INDEX_ACCESS_PORT = i;
    SC_CM_COLOR_ENHANCEMENT_CTRL |= BIT1;
}

/**************************************************************************//**
 * Enhance saturation of green color.
 * @param value The value of saturation adjustment. Range is 0~255. Default is 128.
 ******************************************************************************/
void BFAPI_EnhanceGreen(UCHAR value)
{
    xdata USHRT i;

    //green enhance
    SC_CM_COLOR_ENHANCEMENT_CTRL &= ~BIT1;
    SC_CM_INDEX_ACCESS_CTRL = 0x02;
    SC_CM_INDEX_ACCESS_ADDR = 0x07;
    i = value;
    i = (i >> 1) + 0x40;
    SC_CM_INDEX_ACCESS_PORT = i;
    SC_CM_INDEX_ACCESS_PORT = value;
    SC_CM_INDEX_ACCESS_PORT = i;
    SC_CM_COLOR_ENHANCEMENT_CTRL |= BIT1;
}

/**************************************************************************//**
 * Enhance saturation of blue color.
 * @param value The value of saturation adjustment. Range is 0~255. Default is 128.
 ******************************************************************************/
void BFAPI_EnhanceBlue(UCHAR value)
{
    xdata USHRT i;

    //blue enhance
    SC_CM_COLOR_ENHANCEMENT_CTRL &= ~BIT1;
    SC_CM_INDEX_ACCESS_CTRL = 0x02;
    SC_CM_INDEX_ACCESS_ADDR = 0x0F;
    i = value;
    i = (i >> 1) + 0x40;
    SC_CM_INDEX_ACCESS_PORT = i;
    SC_CM_INDEX_ACCESS_PORT = value;
    SC_CM_INDEX_ACCESS_PORT = i;
    SC_CM_COLOR_ENHANCEMENT_CTRL |= BIT1;
}
#endif

/**************************************************************************//**
 * Set local hue.
 * @param ptr Pointer to the table of local hue.
 ******************************************************************************/
void BFAPI_SetHHTable(HHBlock *ptr)
{
    UCHAR num,off;
    UCHAR i;

    if (ptr != 0) {
        num = ptr->ucNumHH;
        off = ptr->ucOffset;
        if ((num+off) > 24) return;
    }
    else {
        off = 0;
        num = 24;
    }

    SC_CM_COLOR_ENHANCEMENT_CTRL &= ~BIT1;
    SC_CM_INDEX_ACCESS_CTRL = 0x01;
    SC_CM_INDEX_ACCESS_ADDR = off;
    for(i = 0; i < num; i++) {
        if (ptr != 0) {
            SC_CM_INDEX_ACCESS_PORT = ptr->ucHHTable[i];
        }
        else {
            SC_CM_INDEX_ACCESS_PORT = 0x00;
        }
    }
    SC_CM_COLOR_ENHANCEMENT_CTRL |= BIT1;
}

/**************************************************************************//**
 * Set local saturation.
 * @param ptr Pointer to the table of local saturation.
 ******************************************************************************/
void BFAPI_SetHSTable(HSBlock *ptr)
{
    UCHAR num,off;
    UCHAR i;

    if (ptr != 0) {
        num = ptr->ucNumHS;
        off = ptr->ucOffset;
        if ((num+off) > 24) return;
    }
    else {
        off = 0;
        num = 24;
    }

    SC_CM_COLOR_ENHANCEMENT_CTRL &= ~BIT1;
    SC_CM_INDEX_ACCESS_CTRL = 0x02;
    SC_CM_INDEX_ACCESS_ADDR = off;
    for(i = 0; i < num; i++) {
        if (ptr != 0) {
            SC_CM_INDEX_ACCESS_PORT = ptr->ucHSTable[i];
        }
        else {
            SC_CM_INDEX_ACCESS_PORT = 0x80;
        }
    }
    SC_CM_COLOR_ENHANCEMENT_CTRL |= BIT1;
}

/**************************************************************************//**
 * Set local intensity.
 * @param ptr Pointer to the table of local intensity.
 ******************************************************************************/
void BFAPI_SetHITable(HIBlock *ptr)
{
    UCHAR num,off;
    UCHAR i;

    if (CurBFGen() == BF_ONE_GEN) return;

    if (ptr != 0) {
        num = ptr->ucNumHI;
        off = ptr->ucOffset;
        if ((num+off) > 24) return;
    }
    else {
        off = 0;
        num = 24;
    }

    SC_CM_COLOR_ENHANCEMENT_CTRL &= ~BIT1;
    SC_CM_INDEX_ACCESS_CTRL = 0x00;
    SC_CM_INDEX_ACCESS_ADDR = off;
    for(i = 0; i < num; i++) {
        if (ptr != 0) {
            SC_CM_INDEX_ACCESS_PORT = ptr->ucHITable[i];
        }
        else {
            SC_CM_INDEX_ACCESS_PORT = 0x80;
        }
    }
    SC_CM_COLOR_ENHANCEMENT_CTRL |= BIT1;
}

/**************************************************************************//**
 * Set the mode of color extension.
 * The mode is
 *   BF_COLOR_NVT72,
 *   BF_COLOR_NVT74,
 *   BF_COLOR_NVT76,
 *   BF_COLOR_NVT78,
 *   BF_COLOR_NVT80 or
 *   BF_COLOR_INIT.
 *
 * @param mode The mode of color extension.
 ******************************************************************************/
void BFAPI_ColorEnhance(BFColorExMode mode)
{
    code LocalMatrix NVT72Tab = 
	{
         0x0100, 0x0000, 0x0000 , 0x0080,
         0x0000, 0x0100, 0x0000 , 0x0080,
         0x0000, 0x0000, 0x0100 , 0x0080
        };
    code LocalMatrix NVT74Tab = 
	{
         0x0131, 0x0447, 0x0016 , 0x0080,
         0x040B, 0x0117, 0x040C , 0x0080,
         0x0413, 0x000E, 0x0105 , 0x0080
       };
    code LocalMatrix NVT76Tab = 
	{
         0x0162, 0x048E, 0x002C , 0x0080,
         0x0416, 0x012E, 0x0418 , 0x0080,
         0x0427, 0x001C, 0x010B , 0x0080
       };
    code LocalMatrix NVT78Tab = 
	{
         0x0176, 0x04AB, 0x0035 , 0x0080,
         0x041D, 0x013C, 0x041F , 0x0080,
         0x0436, 0x0015, 0x0121 , 0x0080
       };
    code LocalMatrix NVT80Tab = 
	{
         0x018B, 0x04C9, 0x003E , 0x0080,
         0x0424, 0x0149, 0x0426 , 0x0080,
         0x0445, 0x000E, 0x0137 , 0x0080
       };

    code LocalMatrix* ColorEnTab[] = {&NVT72Tab, &NVT74Tab, &NVT76Tab, &NVT78Tab, &NVT80Tab};
    LocalMatrix *ptr;

    if (mode >= BF_COLOR_INIT) 
	{
          BFAPI_SetLocalMatrix(0);
       }
    else 
	{
         ptr = ColorEnTab[mode];
         BFAPI_SetLocalMatrix(ptr);
       }
}

/**************************************************************************//**
 * Set the value of each item of 3x3 matrix in bright frame.
 * @param ptr Pointer to the table of 3x3 matrix.
 ******************************************************************************/
void BFAPI_SetLocalMatrix(LocalMatrix *ptr)
{
    code LocalMatrix DefaultTab = 
	{
        	0x0100, 0x0000, 0x0000 , 0x0080,
        	0x0000, 0x0100, 0x0000 , 0x0080,
        	0x0000, 0x0000, 0x0100 , 0x0080
    	};
    UCHAR i, j, tmpReg;

    tmpReg = SC_SRGB_CTRL & 0xF0;
    if (ptr == 0) 
	{
       	 tmpReg |= 0x41;
        	ptr = &DefaultTab;
    	}
    else 
	{
       	 tmpReg |= 0xC1;
    	}

    for (i = 0; i < 3; i++) 
	{
        	SC_SRGB_CTRL = (i * 2) | tmpReg;
          for (j = 0; j < 3; j++) 
		 {
            		WriteShortScaler((&SC_SRGB_COEF_R_LO+(j*2)),ptr->Rows[i][j]);
        	  }
        	SC_SRGB_COEF_OFFSET = ptr->Rows[i][3];
        }

    SC_SRGB_CTRL = 0x08 | (tmpReg & ~0x40);
}

/**************************************************************************//**
 * Enable i-gamma function.
 ******************************************************************************/
void BFAPI_EnableACEMode(void)
{
    UCHAR tmpReg;

    tmpReg = SC_ACE_FUNC_CTRL1;
    // Enable I-Gamma
    if (CurBFWin() == BF_WINDOW_1)
        tmpReg |= 0x01;
    else
        tmpReg |= 0x02;

#if BF_IG_PARTITIONS == 16
    tmpReg |= 0x08;
#elif  BF_IG_PARTITIONS == 8
    tmpReg |= 0x04;
#endif

    SC_ACE_FUNC_CTRL1 = tmpReg;
}

/**************************************************************************//**
 * Disable i-gamma function.
 ******************************************************************************/
void BFAPI_DisableACEMode(void)
{
    UCHAR tmpReg;

    tmpReg = SC_ACE_FUNC_CTRL1;
    // Disable I-Gamma
    if (CurBFWin() == BF_WINDOW_1)
        tmpReg &= ~BIT0;
    else
        tmpReg &= ~BIT1;
    SC_ACE_FUNC_CTRL1 = tmpReg;
}

/**************************************************************************//**
 * Set i-gamma curve.
 * @param ptr Pointer to the data of i-gamma.
 ******************************************************************************/
void BFAPI_SetPreACEMode(IGBlock *ptr)
{
    code IGBlock DefaultIG = {16, 0, 64, 128, 192, 256, 320, 384, 448, 512, 576, 640, 704, 768, 832, 896, 960,1024}; // 1:1 Linear

    UCHAR i, tmpReg;
    IGBlock *pIG;

    tmpReg = SC_ACE_FUNC_CTRL2 & 0x0E;
    if (CurBFWin() == BF_WINDOW_2)
        tmpReg |= 0x20;

    tmpReg |= 0x50; // Write Gamma
    SC_ACE_FUNC_CTRL2 = tmpReg;

    if (ptr == 0)
        pIG = &DefaultIG;
    else
        pIG = ptr;

    for (i = 0; i <= pIG->NumIG; i++) {
        SC_ACE_DATA_PORT = pIG->IGamma[i] & 0xFF;
        SC_ACE_DATA_PORT = pIG->IGamma[i] >> 8;
    }

    // Update I-Gamma
    SC_ACE_FUNC_CTRL2 = tmpReg | 0x90;
    WaitDisVSync();
    BFAPI_EnableACEMode();
    SC_ACE_FUNC_CTRL2 &= ~BIT7;
}

