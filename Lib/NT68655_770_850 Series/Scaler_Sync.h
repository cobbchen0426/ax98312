/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/

#ifndef __SCALER_SYNC_H__
#define __SCALER_SYNC_H__

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

//******************************************************************************
// V A R I A B L E S   P R O T O T Y P E
//******************************************************************************
extern xdata USHRT usHSyncFreq;
extern xdata USHRT usVSyncFreq;

//******************************************************************************
// F U N C T I O N    P R O T O T Y P E S
//******************************************************************************
void SyncInit(void);
USHRT GetInputHFreq(void);
USHRT GetInputVFreq(void);
UCHAR GetInputHSyncWidth(void);
UCHAR GetInputVSyncWidth(void);
UCHAR GetInputHVPolarity(void);
USHRT GetInputVTotal(void);
void SetupHSyncOverflowMask(UCHAR on);
UCHAR CheckInputSync(void);
BOOL ZpVGA0SyncDetect(void);
BOOL ZpDVI0SyncDetect(void);
BOOL ZpVGA1SyncDetect(void);
BOOL ZpDVI1SyncDetect(void);
BOOL ZpDPSyncDetect(void);
void SetupInterlace(void);
BOOL IsInterlaceSyncPreset(void);
BOOL IsInterlaced(void);
void EnableSyncProcFreeRun(UCHAR enable);
void DelayVTime(UCHAR n) small;

#endif //__SCALER_SYNC_H__
