/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/

#ifndef __DCR_H__
#define __DCR_H__

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
BOOL DCR_UpdateHistogram(UCHAR reset);
USHRT DCR_GetHistogram(UCHAR index);
void DCR_UpdatePrevHistogram(void);
USHRT DCR_GetHistogramDiff(UCHAR index);
BOOL DCR_IsSceneChanged(void);
ULONG DCR_GetTotalHistogram(void);
void DCR_SetDynACEType(ACEType type);
void DCR_SetDynACEPnts(UCHAR * ptr);
void DCR_SetDymACE(UCHAR reset);
void DCR_SetDymBacklight(void);
void DCR_ResetDymBacklight(USHRT backlight);
BOOL DCR_IsReadyToGetMax(void);
UCHAR DCR_GetRMax(void);
UCHAR DCR_GetGMax(void);
UCHAR DCR_GetBMax(void);

#endif //__DCR_H__
