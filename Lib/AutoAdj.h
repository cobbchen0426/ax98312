/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/

#ifndef __AUTOADJ_H__
#define __AUTOADJ_H__

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

//******************************************************************************
// V A R I A B L E S   P R O T O T Y P E
//******************************************************************************

//******************************************************************************
// F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
BOOL IsAutoTuneValid(void);
BOOL AutoTune(void);
BOOL AutoPosition(void);
BOOL AutoClock(void);
BOOL AutoPhaseFineTune(UCHAR len);
BOOL AutoOffset(void);
BOOL AutoGain(void);
BOOL IsAutoColorValid(void);
BOOL AutoColor(void);
BOOL InternalAutoColor(void);
BOOL DVIAutoPosition(void);
void SetHmask(void);
BOOL HwAutoOffset(void);
BOOL HWAutoGain(void);
void SetADCPLL2(USHRT htotal);
BOOL CheckADCPLLOutOfRange(USHRT htotal);

#endif //__AUTOADJ_H__
