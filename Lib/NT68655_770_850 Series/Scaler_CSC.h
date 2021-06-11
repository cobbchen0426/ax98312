/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/

#ifndef __SCALER_CSC_H__
#define __SCALER_CSC_H__

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************
#include "ScalerType.h"
#include "Typedef.h"

//******************************************************************************
// M A C R O   D E F I N I T I O N S
//******************************************************************************

//******************************************************************************
// D A T A   T Y P E   D E F I N E S
//******************************************************************************
/*!
 * Data type for CSC mode.
 */
typedef enum _CSC_COLOR_SPACE_ {
    CSC_YPbPr601_TO_RGB,        /*!< YPbPr 601 to RGB */
    CSC_RGB_TO_YPbPr601,        /*!< RGB to YPbPr 601 */
    CSC_YPbPr601_TO_RGB_FULL,   /*!< YPbPr 601 [16-235] to RGB [ 0-255] (with expansion) */
    CSC_YPbPr709_TO_RGB,        /*!< YPbPr 709 to RGB */
    CSC_RGB_TO_YPbPr709,        /*!< RGB to YPbPr 709 */
    CSC_YPbPr709_TO_RGB_FULL,   /*!< YPbPr 709 [16-235] to RGB [0-255] (with expansion) */
    CSC_YPbPr_TO_YPbPr_FULL,    /*!< Limit range YPbPr [ 16-235] to full range YPbPr[0-255] */
    CSC_RGB_TO_RGB_FULL,        /*!< Limit range RGB [16-235] to full range RGB [0-255] */
    CSC_xvYCC601_TO_RGB,        /*!< xvYCC601 to RGB */
    CSC_RGB_TO_xvYCC601,        /*!< RGB to xvYCC601 */
    CSC_xvYCC601_TO_RGB_FULL,   /*!< xvYCC601 to RGB with expansion */
    CSC_xvYCC709_TO_RGB,        /*!< xvYCC709 to RGB */
    CSC_RGB_TO_xvYCC709,        /*!< RGB to xvYCC709 */
    CSC_xvYCC709_TO_RGB_FULL,   /*!< xvYCC709 to RGB with expansion */
    CSC_RGB_TO_YPbPr601_FULL,   /*!< RGB to YPbPr601 with expansion */
    CSC_HDMI_AUTO_CLR_SPACE,    /*!< HDMI Auto Color Space */
    CSC_OFF                     /*!< CSC off */
} CSCColorSpace;

//******************************************************************************
// V A R I A B L E S   P R O T O T Y P E
//******************************************************************************

//******************************************************************************
// F U N C T I O N    P R O T O T Y P E S
//******************************************************************************
void SetColorSpace(void);
#if ENABLE_HDMI == ON
UCHAR GetScalerColorSpace(void);
void SetCSCColorSpace(CSCColorSpace csc);
#endif

#endif //__SCALER_CSC_H__
