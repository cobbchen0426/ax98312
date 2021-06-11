/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/

#ifndef __SCALER_NR_H__
#define __SCALER_NR_H__

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************
#include "ScalerType.h"
#include "Typedef.h"

//******************************************************************************
// M A C R O   D E F I N I T I O N S
//******************************************************************************
#define NR_CFG_RDM_TP       0x80 /*!< Random generator. */
#define NR_CFG_NR2_EN       0x40 /*!< Level 2 NR. */
#define NR_CFG_ROUND        0x20 /*!< NR round calculation. */
#define NR_CFG_EDGE_DET     0x10 /*!< NR edge detection. */
#define NR_CFG_NR_DITH_EN   0x08 /*!< NR dithering. */
#define NR_CFG_JC_EN        0x04 /*!< Jitter correction. */
#define NR_CFG_GC_EN        0x02 /*!< Ghost canceling. */

//******************************************************************************
// D A T A   T Y P E   D E F I N E S
//******************************************************************************
/*!
 * Data type of noise reduction.
 */
typedef enum _NR_TYPE_ {
    NR_MODE_OFF, /*!< NR off. */
    NR_MODE_1,   /*!< NR mode 1. */
    NR_MODE_2,   /*!< NR mode 2. */
    NR_MODE_3    /*!< NR mode 3. */
} NRType;

//******************************************************************************
// V A R I A B L E S   P R O T O T Y P E
//******************************************************************************

//******************************************************************************
// F U N C T I O N    P R O T O T Y P E S
//******************************************************************************
void NRInit(void);
void NRSetNRType(NRType type, UCHAR cfg);
void NRSetEdgeThr(UCHAR value);
void NRSetNRThr(UCHAR value);
void NRSetJCLvl(UCHAR value);
void NRSetNR2Thr(UCHAR value);
void NRSetGCCfg(UCHAR win, UCHAR pk_thr, UCHAR lf_thr);

#endif //__SCALER_NR_H__
