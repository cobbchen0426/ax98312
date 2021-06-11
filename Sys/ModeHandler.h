/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/

#ifndef __MODEHANDLER_H__
#define __MODEHANDLER_H__

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************
#include "Typedef.h"

//******************************************************************************
// M A C R O   D E F I N I T I O N S
//******************************************************************************
#define WAIT_MODE_CHANGE   1 /*!< State of mode handler. */
#define WAIT_SYNC_STABLE   2 /*!< State of mode handler. */
#define SYNC_IS_STABLE     3 /*!< State of mode handler. */
#define POWER_SAVING_MODE  4 /*!< State of mode handler. */
#define WAIT_DISPLAY_READY 5 /*!< State of mode handler. */
#define SOFT_POWER_ON      6 /*!< State of mode handler. */
#define SOFT_POWER_OFF     7 /*!< State of mode handler. */

//******************************************************************************
// D A T A   T Y P E   D E F I N E S
//******************************************************************************

//******************************************************************************
// V A R I A B L E S   P R O T O T Y P E
//******************************************************************************
extern xdata UCHAR ucModeHdlrState;
//******************************************************************************
// F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
void ModeHandler(void);
void ModeHandlePowerSaving(void);
void ModeHandleSoftPowerOn(void);
void ModeHandleSoftPowerOff(void);
UCHAR GetModeHandleState(void);
void HoldModeDisplay(void);
void ContinueModeDisplay(void);

#endif //__MODEHANDLER_H__
