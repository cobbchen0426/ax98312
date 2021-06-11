/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/

#ifndef __SYNCHANDLER_H__
#define __SYNCHANDLER_H__

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************
#include "Typedef.h"

//******************************************************************************
// M A C R O   D E F I N I T I O N S
//******************************************************************************
//SyncMode Definition
#define NO_SYNC      1 /*!< No sync state of sync handler. */
#define SEP_SYNC     2 /*!< Separate sync state of sync handler. */
#define COM_SYNC     3 /*!< Composite sync state of sync handler. */
#define SOG_SYNC     4 /*!< SOG sync state of sync handler. */
#define DIG_SYNC     5 /*!< Digital sync state of sync handler. */
#define NO_CABLE     6 /*!< No cable state of sync handler. */
#define OUT_SYNC     7 /*!< Out of range state of sync handler. */
#define UNKNOWN_SYNC 8 /*!< Unknown state of sync handler. */

//HVPolarity Definition
#define HNVN  0x01 /*!< H/V polarities are -/-. */
#define HNVP  0x02 /*!< H/V polarities are -/+. */
#define HPVN  0x04 /*!< H/V polarities are +/-. */
#define HPVP  0x08 /*!< H/V polarities are +/+. */

//Make SyncSource searching input sync automatically or manually
#define AUTO_SYNC   1 /*!< Change interface automatically. */
#define MANUAL_SYNC 0 /*!< Change interface manually. */

//******************************************************************************
// D A T A   T Y P E   D E F I N E S
//******************************************************************************

//******************************************************************************
// V A R I A B L E S   P R O T O T Y P E
//******************************************************************************

//******************************************************************************
// F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
void SyncHandler(void);
void SetSyncSource(UCHAR type);
BOOL CheckModeChange(void);
UCHAR GetInputSyncMode(void);
void RecordCurrentSource(UCHAR enable);
#if (INPUT_INTERFACE&INPUT_MHL0) || (INPUT_INTERFACE&INPUT_MHL1) || (ENABLE_DP_HPD == ON)
void ResetCurTimerTick(void);
#endif

#endif //__SYNCHANDLER_H__
