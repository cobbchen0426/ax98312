/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/

#ifndef __SCALER_TMDS_H__
#define __SCALER_TMDS_H__

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
 *Data type for f/w-based impedance detection.
 */
typedef struct {
    UCHAR ClkIMP;
    UCHAR DataIMP;
    UCHAR IMPMode;
    UCHAR EQBias;
    UCHAR EQRF;
    UCHAR MaxGoodEye;
    USHRT SumOfEye;
    UCHAR RGBGoodEye[3];
} EyeData;

//******************************************************************************
// V A R I A B L E S   P R O T O T Y P E
//******************************************************************************

//******************************************************************************
// F U N C T I O N    P R O T O T Y P E S
//******************************************************************************
void TMDSInit(void);
void TMDSImpedanceDetection(void);
BOOL TMDSClockStable(void);
void TMDSBandwidthDetection(UCHAR reset);
USHRT GetDigInputHActive(void);
USHRT GetDigInputVActive(void);
USHRT GetDigInputHActiveImmediate(void);
USHRT GetDigInputVActiveImmediate(void);
#if ENABLE_HDMI == ON
USHRT GetDigInputHTotalImmediate(void);
USHRT GetDigInputVTotalImmediate(void);
#endif
void DVI_PowerOff(void);
void DVI_PowerOn(void);
void SetDVIPLL(void);
void TMDS_EnableSCDT(void);
USHRT TMDS_GetClock(void);

#endif //__SCALER_TMDS_H__
