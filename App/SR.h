/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/
#ifndef __SR_H__
#define __SR_H__

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************
#include "Typedef.h"

//******************************************************************************
// G L O B A L   D E F I N I T I O N S
//******************************************************************************
typedef enum _SR_MODE_ {
    SR_MODE_OFF,
    SR_MODE_WEAK,
    SR_MODE_MEDIAN,
    SR_MODE_STRONG,
    SR_MODE_EXTREME,
//    SR_MODE_OFF,
    NUM_SR_MODE
} SRMode;



enum {
    MDN_MODE_1,
//    MDN_MODE_2,
    NUM_MDN_MODE
};

enum {
    USM_REGION_MODE_1,
    USM_REGION_MODE_2,
    USM_REGION_MODE_3,
    USM_REGION_MODE_4,
    NUM_USMRGN_MODE
};

enum {
    USM_GAIN_MODE_1,
    USM_GAIN_MODE_2,
    USM_GAIN_MODE_3,
    USM_GAIN_MODE_4,
    NUM_USMGAIN_MODE
};

enum {
    USM_DARK_LIMIT_OFF,
    USM_DARK_LIMIT_ON,        
};

typedef struct _SR_BLOCK_ {
    MDNBlock *pMDNLPF;
    USMRegionBlock *pSRHPRegion;
    USMGainBlock *pSRHPGain;
    USHRT usLPFGain;
    UCHAR bDarkLimit;
} SRBlock;

//******************************************************************************
// G L O B A L   V A R I A B L E S
//******************************************************************************

//******************************************************************************
// S T A T I C   V A R I A B L E S
//******************************************************************************

//******************************************************************************
// E X T E R N A L   V A R I A B L E   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// S T A T I C   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// E X T E R N A L   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
extern void InitSR(void);
extern void SetSRMode(SRMode mode);
extern void SR_Demo_Mode(void);
extern void SR_Demo_Mode_On_OFF(void);
extern void Reset_SR_Demo_Mode(void);

#if IS_NT68661_SERIES || IS_NT68770_SERIES || IS_NT68850_SERIES || IS_NT68655_SERIES || IS_NT68790_SERIES
extern void SetSRHtotal(USHRT htotal);
extern void SetSRInputTimingParameter(void);
extern void SetSRBlockOnOff(UCHAR on);
#endif

#endif //__SR_H__
