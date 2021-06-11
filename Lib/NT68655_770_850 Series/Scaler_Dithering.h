/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/

#ifndef __SCALER_DITHERING_H__
#define __SCALER_DITHERING_H__

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
 * Data type of dithering.
 */
typedef enum _DITHER_TYPE_ {
    DITH_TP_RDM,    /*!< Random dithering. */
    DITH_TP_VRDM,   /*!< Random dithering with VSync reset. */
    DITH_TP_STATIC, /*!< Static dithering. */
    DITH_TP_MIX,    /*!< Mix dithering. */
    DITH_TP_OFF     /*!< Dithering off. */
} DitherType;

//******************************************************************************
// V A R I A B L E S   P R O T O T Y P E
//******************************************************************************

//******************************************************************************
// F U N C T I O N    P R O T O T Y P E S
//******************************************************************************
void DithInit(void);
void DithSetDitherMode(DitherType type, UCHAR mode_10, UCHAR mode_01);

#endif //__SCALER_DITHERING_H__
