/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/

#ifndef __DBC_TYPE_H__
#define __DBC_TYPE_H__

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
 * The data type for DBC divider
 */
typedef enum _DBC_DIV_ {
    DBC_DIV_1X, /*!< Divide by 1 */
    DBC_DIV_2X, /*!< Divide by 2 */
    DBC_DIV_3X, /*!< Divide by 3 */
    DBC_DIV_4X  /*!< Divide by 4 */
} DBCDividor;

/*!
 * The data type for DBC saving ratio.
 * Y_MAX means the maximum Y of the point on the screen.
 * Y_AVG means the average Y of every points on the screen.
 */
typedef enum _DBC_SAVING_MODE_ {
    DBC_SAVING_MODE_MAX, /*!< Weighting = Y_MAX */
    DBC_SAVING_MODE_1,   /*!< Weighting = (15/16)*Y_MAX + ( 1/16)*Y_AVG */
    DBC_SAVING_MODE_2,   /*!< Weighting = (14/16)*Y_MAX + ( 2/16)*Y_AVG */
    DBC_SAVING_MODE_3,   /*!< Weighting = (12/16)*Y_MAX + ( 4/16)*Y_AVG */
    DBC_SAVING_MODE_4,   /*!< Weighting = (10/16)*Y_MAX + ( 6/16)*Y_AVG */
    DBC_SAVING_MODE_5,   /*!< Weighting = ( 8/16)*Y_MAX + ( 8/16)*Y_AVG */
    DBC_SAVING_MODE_6,   /*!< Weighting = ( 4/16)*Y_MAX + (12/16)*Y_AVG */
    DBC_SAVING_MODE_7    /*!< Weighting = Y_AVE */
} DBCSavingMode;

/*!
 * The data type for DBC table.
 */
typedef struct _DBCTAB_  {
    UCHAR ucYGrayToLum[256]; /*!< The table of Gray luminance information */
    UCHAR ucPWMToLum[256];   /*!< The table of PWM luminance information */
    UCHAR ucPWMToMult[256];  /*!< The table of PWM */
} DBCTab;

//******************************************************************************
// V A R I A B L E S   P R O T O T Y P E
//******************************************************************************

//******************************************************************************
// F U N C T I O N    P R O T O T Y P E S
//******************************************************************************

#endif //__DBC_TYPE_H__
