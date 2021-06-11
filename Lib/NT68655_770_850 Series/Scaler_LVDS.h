/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/

#ifndef __SCALER_LVDS_H__
#define __SCALER_LVDS_H__

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
 * Data type for LVDS swing.
 */
typedef enum _LVDS_SWING_{
    LVDS_SWING_220, /*!< LVDS swing 220mV. */
    LVDS_SWING_250, /*!< LVDS swing 250mV. */
    LVDS_SWING_300, /*!< LVDS swing 300mV. */
    LVDS_SWING_350, /*!< LVDS swing 350mV. */
    LVDS_SWING_400, /*!< LVDS swing 400mV. */
    LVDS_SWING_450, /*!< LVDS swing 450mV. */
    LVDS_SWING_500, /*!< LVDS swing 500mV. */
    LVDS_SWING_550, /*!< LVDS swing 550mV. */
    LVDS_SWING_600, /*!< LVDS swing 600mV. */
    LVDS_SWING_650, /*!< LVDS swing 650mV. */
    LVDS_SWING_700, /*!< LVDS swing 700mV. */
    LVDS_SWING_750, /*!< LVDS swing 750mV. */
    LVDS_SWING_800, /*!< LVDS swing 800mV. */
    NUM_LVDS_SWING  /*!< Number of LVDS swing setting. */
} LVDSSwing;

/*!
 * Data type for LVDS clock/data skew swing.
 */
typedef enum _LVDS_DELAY_{
    LVDS_DELAY_OFF = 0x00,  /*!< Turn off LVDS skew setting. */
    LVDS_DELAY_1_STAGE,     /*!< Stage 1 of LVDS skew setting. */
    LVDS_DELAY_2_STAGE,     /*!< Stage 2 of LVDS skew setting. */
    LVDS_DELAY_3_STAGE,     /*!< Stage 3 of LVDS skew setting. */
    LVDS_DELAY_4_STAGE,     /*!< Stage 4 of LVDS skew setting. */
    LVDS_DELAY_5_STAGE,     /*!< Stage 5 of LVDS skew setting. */
    LVDS_DELAY_6_STAGE,     /*!< Stage 6 of LVDS skew setting. */
    LVDS_DELAY_7_STAGE      /*!< Stage 7 of LVDS skew setting. */
} LVDSDelay;

//******************************************************************************
// V A R I A B L E S   P R O T O T Y P E
//******************************************************************************

//******************************************************************************
// F U N C T I O N    P R O T O T Y P E S
//******************************************************************************
void LVDSInit(void);
void LvdsOff(void);
void LvdsOn(void);
void SetLvdsSwing(LVDSSwing swing);
void SetLvdsClkDelay(LVDSDelay delay);
void SetLvdsDataDelay(LVDSDelay delay);
void SetLvdsP2SByDCLK(void);
void SetLvdsChPolSwap(void);

#endif //__SCALER_LVDS_H__
