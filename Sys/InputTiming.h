/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/

#ifndef __INPUT_TIMING_H__
#define __INPUT_TIMING_H__

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
 * Data type for timing information.
 */
typedef struct _INPUT_TIMING_FORMAT_ {
    USHRT usHSyncFreq;
    USHRT usVSyncFreq;
    UCHAR ucHVPolarity;
    UCHAR ucHSyncWidth;
    UCHAR ucVSyncWidth;
    USHRT usHTotal;
    USHRT usVTotal;
    USHRT usModeHActive;
    USHRT usModeVActive;
    USHRT usCapHActive;
    USHRT usCapVActive;
    USHRT usHStart;
    USHRT usVStart;
    UCHAR ucPhase;
    USHRT usHTotal50;
    USHRT usHStart50;
    USHRT usVStart50;
    USHRT usHTotalMin;
    USHRT usHTotalMax;
    USHRT usHStartMin;
    USHRT usHStartMax;
    USHRT usVStartMin;
    USHRT usVStartMax;
    UCHAR ucAutoTune;
    USHRT usModeIndex;
} InputTimingFormat;

//******************************************************************************
// V A R I A B L E S   P R O T O T Y P E
//******************************************************************************

//******************************************************************************
// F U N C T I O N   P R O T O T Y P E S
//******************************************************************************

#endif //__INPUT_TIMING_H__
