/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/

#ifndef __SCALER_ADC_H__
#define __SCALER_ADC_H__

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
 * The data type for ADC bandwidth.
 */
typedef enum _ADC_BW_ {
    ADC_BW_75MHz,  /*!< ADC bandwidth 75MHz. */
    ADC_BW_150MHz, /*!< ADC bandwidth 150MHz. */
    ADC_BW_250MHz, /*!< ADC bandwidth 250MHz. */
    ADC_BW_300MHz, /*!< ADC bandwidth 300MHz. */
    ADC_BW_350MHz, /*!< ADC bandwidth 350MHz. */
    ADC_BW_400MHz, /*!< ADC bandwidth 400MHz. */
    ADC_BW_450MHz, /*!< ADC bandwidth 450MHz. */
    ADC_BW_500MHz, /*!< ADC bandwidth 500MHz. */
    ADC_BW_AUTO    /*!< Auto ADC bandwidth. */
} ADCBandW;

/*!
 * The data type for ADC input source.
 */
typedef enum _ADC_INPUT_ {
    ADC_INPUT_INT_GND,   /*!< Internal zero voltage. */
    ADC_INPUT_RST_RGB,   /*!< External RGB with internal resistor. */
    ADC_INPUT_INT_WHITE, /*!< Internal 0.7V. */
    ADC_INPUT_EXT_RGB,   /*!< External RGB. */
    ADC_NUM_INPUT        /*!< Number of ADC input sources. */
} ADCInput;

//******************************************************************************
// V A R I A B L E S   P R O T O T Y P E
//******************************************************************************

//******************************************************************************
// F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
void ADCInit(void);
USHRT GetAngInputHTotal(void);
UCHAR GetAngInputPhase(void);
void SetADCBandWidth(ADCBandW bw);
void SetADCPLL(USHRT htotal);
void WaitHPLLstable(void);
void SetADCPhase(UCHAR phase);
void SetADCRGain(UCHAR gain);
void SetADCGGain(UCHAR gain);
void SetADCBGain(UCHAR gain);
void SetADCROffset(UCHAR offset);
void SetADCGOffset(UCHAR offset);
void SetADCBOffset(UCHAR offset);
UCHAR GetADCRGain(void);
UCHAR GetADCGGain(void);
UCHAR GetADCBGain(void);
UCHAR GetADCROffset(void);
UCHAR GetADCGOffset(void);
UCHAR GetADCBOffset(void);
void EnableADCGndSampling(UCHAR enable);
void VGA_PowerOn(void);
void VGA_PowerOff(void);
//BOOL IsADCPowerOn(void);
void SchmittTriggerPowerOn(void);
void SchmittTriggerPowerOff(void);
void SetADCInput(ADCInput input);

#endif //__SCALER_ADC_H__
