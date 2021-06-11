/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/

#ifndef __OSD_API_H__
#define __OSD_API_H__

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************
#include "OSDType.h"
#include "Typedef.h"
#include "Scaler.h"

//******************************************************************************
// M A C R O   D E F I N I T I O N S
//******************************************************************************
#define OSD_RAM_SIZE     6144 /*!< Define scaler OSD sram size. The unit is 3-bytes. */
#define OSD_ROT_RAM_SIZE 6135 /*!< Define scaler OSD sram size when OSD rotation is enabled. The unit is 3-bytes. */

#define OSDSRAM_ADDR_CEILING(a)     (((a + 8) / 9) * 9) /*!< Ceiling the OSD address to the multiple of 9. */
#define OSDSRAM_ADDR_FLOOR(a)       (((a) / 9) * 9)  /*!< Flooring the OSD address to the multiple of 9. */

#define SET_WINATTR_BEVEL(a)        (a.ucWinAttr |=  BIT0) /*!< Enable the bolder attribute of OSD window. */
#define CLR_WINATTR_BEVEL(a)        (a.ucWinAttr &= ~BIT0) /*!< Disable the bolder attribute of OSD window. */
#define CHK_WINATTR_BEVEL(a)        (a.ucWinAttr &   BIT0) /*!< Check the bolder attribute of OSD window. */
#define SET_WINATTR_FADEINOUT(a)    (a.ucWinAttr |=  BIT1) /*!< Enable the fading attribute of OSD window. */
#define CLR_WINATTR_FADEINOUT(a)    (a.ucWinAttr &= ~BIT1) /*!< Disable the fading attribute of OSD window. */
#define CHK_WINATTR_FADEINOUT(a)    (a.ucWinAttr &   BIT1) /*!< Check the fading attribute of OSD window. */
#define SET_WINATTR_SHADOW(a)       (a.ucWinAttr |=  BIT2) /*!< Enable the shadow attribute of OSD window. */
#define CLR_WINATTR_SHADOW(a)       (a.ucWinAttr &= ~BIT2) /*!< Disable the shadow attribute of OSD window. */
#define CHK_WINATTR_SHADOW(a)       (a.ucWinAttr &   BIT2) /*!< Check the shadow attribute of OSD window. */
#define SET_WINATTR_BEVEL_SHADOW_TRANS(a)       (a.ucWinAttr |=  BIT3) /*!< Enable bevel/shadow translucent attribute of OSD window. */
#define CLR_WINATTR_BEVEL_SHADOW_TRANS(a)       (a.ucWinAttr &= ~BIT3) /*!< Disable bevel/shadow translucent attribute of OSD window. */
#define CHK_WINATTR_BEVEL_SHADOW_TRANS(a)       (a.ucWinAttr &   BIT3) /*!< Check bevel/shadow translucent attribute of OSD window. */
#define RST_WINATTR_ALL(a)          {a.ucWinAttr = 0x00; \
                                     a.ucWinClr = 0x00; \
                                     a.ucBorderAttr = 0x00; \
                                     a.ucRBorderClr = 0x00; \
                                     a.ucLBorderClr = 0x00;}  /*!< Clear all the attribute of OSD window. */
#define SET_BEVEL_TYPE(a,t)         {a.ucBorderAttr &= 0x0F; \
                                     a.ucBorderAttr |= ((t<<4)&0x30);} /*!< Set the type of window bolder. */
#define SET_BEVEL_WIDTH(a,w)        {a.ucBorderAttr &= 0xF0; \
                                     a.ucBorderAttr |= (w&0x0F);} /*!< Set the width of window bolder. */

#define OSDAPI_Rotated_OSD_Off()       (SC_OSD_CTRL1 = SC_OSD_CTRL1 & 0x1F) /*!< Disable OSD rotation. */
#define OSDAPI_Rotated_90_OSD()        (SC_OSD_CTRL1 = (SC_OSD_CTRL1 & 0x1F) | BIT7) /*!< Rotate OSD 90 degree. */
#define OSDAPI_Rotated_180_OSD()       (SC_OSD_CTRL1 = (SC_OSD_CTRL1 & 0x1F) | BIT6 | BIT5) /*!< Rotate OSD 180 degree. */
#define OSDAPI_Rotated_270_OSD()       (SC_OSD_CTRL1 = (SC_OSD_CTRL1 & 0x1F) | BIT7 | BIT6 | BIT5) /*!< Rotate OSD 270 degree. */
#define OSDAPI_TurnOnRotated_90_OSD()  {SC_OSD_FRAME2_FUNC_CTRL &=~BIT7; (SC_OSD_CTRL1 = (SC_OSD_CTRL1 & 0x1F) | BIT7 | BIT0);} /*!< Rotate OSD 90 degree and show OSD. */
#define OSDAPI_TurnOnRotated_180_OSD() {SC_OSD_FRAME2_FUNC_CTRL &=~BIT7; (SC_OSD_CTRL1 = (SC_OSD_CTRL1 & 0x1F) | BIT6 | BIT5 | BIT0);} /*!< Rotate OSD 180 degree and show OSD. */
#define OSDAPI_TurnOnRotated_270_OSD() {SC_OSD_FRAME2_FUNC_CTRL &=~BIT7; (SC_OSD_CTRL1 = (SC_OSD_CTRL1 & 0x1F) | BIT7 | BIT6 | BIT5 | BIT0);} /*!< Rotate OSD 270 degree and show OSD. */
#define OSDAPI_TurnOnOSD()             (SC_OSD_CTRL1 |= BIT0); /*!< TRUE if OSD is on else FALSE. */
#define OSDAPI_TurnOffOSD()            {SC_OSD_CTRL1 &= ~(BIT7 | BIT6 | BIT5 | BIT0); WaitDisVSync(); OSDAPI_OSDPowerOff(); } /*!< Turn off OSD*/
#define OSDAPI_OSDPowerOn()            {SC_OSD_FRAME2_FUNC_CTRL &= ~BIT7; WaitDisVSync(); } //Only work for nt68661/nt68770 or newer ICs
#define OSDAPI_OSDPowerOff()            (SC_OSD_FRAME2_FUNC_CTRL |= BIT7) //Only work for nt68661/nt68770 or newer ICs
#define OSDAPI_IsOSDOn()               (SC_OSD_CTRL1 & BIT0) /*!< TRUE if OSD is on else FALSE. */
#define OSDAPI_SetFontAttr(a)          WriteShortScaler(&SC_OSD_ATTRIBUTE_LO, a) /*!< Set OSD font attribute. */

#define OSDAPI_GetOSDFrameSize(w,h) ((USHRT)w * h + 1) /*!< Get OSD frame size in OSD sram. Unit is 3-bytes. */
#define OSDAPI_Set1BitFontAddr(a)   OSDAPI_SetFontAddress(OSD_FONTBITS_1b, a) /*!< Set the start address of 1-bit font. */
#define OSDAPI_Set2BitsFontAddr(a)  OSDAPI_SetFontAddress(OSD_FONTBITS_2b, a) /*!< Set the start address of 2-bits font. */
#define OSDAPI_Set3BitsFontAddr(a)  OSDAPI_SetFontAddress(OSD_FONTBITS_3b, a) /*!< Set the start address of 3-bits font. */
#define OSDAPI_Set4BitsFontAddr(a)  OSDAPI_SetFontAddress(OSD_FONTBITS_4b, a) /*!< Set the start address of 4-bits font. */

/*!
 * Initial the offset of sequential write of OSD font index with attributes from scaler register.
 */
#define OSDAPI_InitSeqWriteCodeFCAttr(i) { \
            SC_INDEX_CTRL = 0x90; \
            SC_INDEX_ADDR_LO = i & 0xFF; \
            SC_INDEX_ADDR_HI = (i >> 8) & 0xFF; \
        }
/*!
 * Initial the offset of sequential write of OSD font index and attributes.
 */
#define OSDAPI_InitSeqWriteCodeAttr(i) { \
            SC_INDEX_CTRL = 0x80; \
            SC_INDEX_ADDR_LO = i & 0xFF; \
            SC_INDEX_ADDR_HI = (i >> 8) & 0xFF; \
        }
/*!
 * Initial the offset of sequential write of OSD attributes.
 */
#define OSDAPI_InitSeqWriteAttr(i) { \
            SC_INDEX_CTRL = 0x70; \
            SC_INDEX_ADDR_LO = i & 0xFF; \
            SC_INDEX_ADDR_HI = (i >> 8) & 0xFF; \
        }
/*!
 * Initial the offset of sequential write of OSD font index.
 */
#define OSDAPI_InitSeqWriteCode(i) { \
            SC_INDEX_CTRL = 0x40; \
            SC_INDEX_ADDR_LO = i & 0xFF; \
            SC_INDEX_ADDR_HI = (i >> 8) & 0xFF; \
        }

/*!
 * Write OSD font index sequentially.
 */
#define OSDAPI_SeqWriteCodeFCAttr(c) (SC_INDEX_DATA = c)
/*!
 * Write OSD font index and attributes sequentially.
 */
#define OSDAPI_SeqWriteCodeAttr(c, a) { \
            SC_INDEX_DATA = c; \
            SC_INDEX_DATA = a & 0xFF; \
            SC_INDEX_DATA = (a >> 8) & 0xFF; \
            ResetWDTimer();\
        }
/*!
 * Write OSD attributes sequentially.
 */
#define OSDAPI_SeqWriteAttr(a) { \
            SC_INDEX_DATA = a & 0xFF; \
            SC_INDEX_DATA = (a >> 8) & 0xFF; \
            ResetWDTimer();\
        }
/*!
 * Write OSD font index sequentially.
 */
#define OSDAPI_SeqWriteCode(c) (SC_INDEX_DATA = c)

//******************************************************************************
// D A T A   T Y P E   D E F I N E S
//******************************************************************************

//******************************************************************************
// V A R I A B L E S   P R O T O T Y P E
//******************************************************************************

//******************************************************************************
// F U N C T I O N    P R O T O T Y P E S
//******************************************************************************
void OSDAPI_SetFontAddress(OSDFontBits type, USHRT addr);
void OSDAPI_ClearOSD(void);
void OSDAPI_SetOSDWidth(UCHAR width);
void OSDAPI_SetOSDHeight(UCHAR height);
UCHAR OSDAPI_GetOSDWidth(void);
UCHAR OSDAPI_GetOSDHeight(void);
void OSDAPI_SetFontSize(OSDFontSize size);
UCHAR OSDAPI_GetOSDFontWidth(void);
UCHAR OSDAPI_GetOSDFontHeight(void);
void OSDAPI_RotateOSDPosition(OSDPosRotation rot);
void OSDAPI_SetPosition(USHRT x, USHRT y);
void OSDAPI_SetRowPosition(USHRT x, USHRT y);
void OSDAPI_SetAlignType(OSDAlignment algn);
UCHAR OSDAPI_GetAlignType(void);
void OSDAPI_WriteXYString(BOOL attr, UCHAR x, UCHAR y, UCHAR len, UCHAR *pstr);
//void OSDAPI_WriteXYStringAlign(BOOL attr, UCHAR x, UCHAR y, UCHAR len, UCHAR *pstr, UCHAR align_len);
//void OSDAPI_WriteString(BOOL attr, UCHAR *pstr);
void OSDAPI_WriteXYRepeatChar(BOOL attr, UCHAR x, UCHAR y, UCHAR num, UCHAR ch);
//void OSDAPI_WriteXYChar(BOOL attr, UCHAR x, UCHAR y, UCHAR ch);
void OSDAPI_FillLineAttr(UCHAR x, UCHAR y, UCHAR num, USHRT attr);
void OSDAPI_FillLineAttrList(UCHAR x, UCHAR y, UCHAR num, USHRT *ptr);
void OSDAPI_RotateFont(UCHAR *des, UCHAR *src);
void OSDAPI_RotateIdentFont(UCHAR *des, USHRT *src);
void OSDAPI_MirrorFont(UCHAR *des, UCHAR *src, UCHAR width);
void OSDAPI_MirrorIdentFont(USHRT *des, USHRT *src, UCHAR width);
void OSDAPI_FlipFont(UCHAR *des, UCHAR *src, UCHAR height);
void OSDAPI_FlipIdentFont(USHRT *des, USHRT *src, UCHAR height);
void OSDAPI_OSDWinOn(OSDWindow id);
void OSDAPI_OSDWinOff(OSDWindow id);
void OSDAPI_SelOSDWin(OSDWindow id);
void OSDAPI_SetOSDWinSizeUnit(UCHAR width, UCHAR height);
void OSDAPI_SetOSDWinSize(USHRT sx, USHRT sy, USHRT ex, USHRT ey);
void OSDAPI_SetOSDWinAttr(OSDWinAttr attr);
void OSDAPI_SetOSDWinTran(UCHAR tran);
void OSDAPI_SetOSDWinGrad(UCHAR dir, UCHAR inc, UCHAR step, UCHAR pixel);
void OSDAPI_TurnOnOffOSDWinGrad(UCHAR on);
void OSDAPI_RotateOSDWin(OSDWindow id, OSDPosRotation rot);
void OSDAPI_SetHVZoom(UCHAR times);
void OSDAPI_SetOSDFgBgTran(UCHAR tran);
void OSDAPI_SetOSDSpecialBgTran(UCHAR tran);
void OSDAPI_SetOSDFadeInOut(UCHAR vspeed, UCHAR hspeed, UCHAR vstep, UCHAR hstep, UCHAR dir);

#endif //__OSD_API_H__
