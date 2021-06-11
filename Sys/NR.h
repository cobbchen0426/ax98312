/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/

#ifndef __NR_H__
#define __NR_H__

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************
#include "Scaler.h"
#include "Typedef.h"

//******************************************************************************
// M A C R O   D E F I N I T I O N S
//******************************************************************************

//******************************************************************************
// D A T A   T Y P E   D E F I N E S
//******************************************************************************
/*!
 * Data type for NR settings.
 */
typedef struct _NR_CFG_ {
    ADCBandW ucADCBandwidth;    // 0x010[2:0] ADC bandwidth type
    UCHAR ucGndSampling;        // 0x000[0] ADC ground sampling on/off
    NRType ucNRType;            // 0x068[1:0] NR filter type
    UCHAR ucNRCfg;              // 0x068[7] NR_CFG_RDM_TP      Random generator type
                                // 0x068[6] NR_CFG_NR2_EN      NR2 on/off
                                // 0x068[5] NR_CFG_ROUND       NR round calculation on/off
                                // 0x068[4] NR_CFG_EDGE_DET    NR edge detection on/off
                                // 0x06A[4] NR_CFG_JC_EN       Jitter correction on/off
                                // 0x06B[4] NR_CFG_NR_DITH_EN  NR dithering on/off
                                // 0x06B[5] NR_CFG_GC_EN       Ghost canceling on/off
    UCHAR ucNREdgeThr;          // 0x069[7:4] Edge threshold of the NR filter
    UCHAR ucNRTh;               // 0x069[3:0] Threshold of NR filter
    UCHAR ucJCLvl;              // 0x06A[3:0] Jitter correction level
    UCHAR ucNR2Th;              // 0x06B[3:0] Threshold of NR2 filter
    UCHAR ucGCWin;              // 0x06E[2:0] Ghost canceling window size. The value is 3~6
    UCHAR ucGCPkThr;            // 0x06F[7:4] Peak level of ghost canceling
    UCHAR ucGCLpThr;            // 0x06F[3:0] threshold of low pass filter of ghost canceling
} NRCfg;

/*!
 * Data type for dithering settings.
 */
typedef struct _DITHER_CFG_ {
    DitherType ucDitherType;
    UCHAR ucMode_10;
    UCHAR ucMode_01;
} DitherCfg;

/*!
 * Data type of NR of each timing.
 */
typedef struct _NR_TIMING_ {
    USHRT usModeIndex;
    NRCfg NR;
    DitherCfg Dither;
} NRTiming;


//******************************************************************************
// V A R I A B L E S   P R O T O T Y P E
//******************************************************************************

//******************************************************************************
// F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
void SetNRByAnalogTiming(void);
void SetNRByDigitalTiming(void);

#endif //__NR_H__
