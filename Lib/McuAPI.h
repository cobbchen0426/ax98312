/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/

#ifndef __MCU_API_H__
#define __MCU_API_H__

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************
#include "8051.h"
#include "McuReg.h"
#include "Typedef.h"

//******************************************************************************
// M A C R O   D E F I N I T I O N S
//******************************************************************************
#define MCU_PORT_A    1     /*!< MCU GPIO port. */
#define MCU_PORT_B    2     /*!< MCU GPIO port. */
#define MCU_PORT_C    3     /*!< MCU GPIO port. */
#define MCU_PORT_D    4     /*!< MCU GPIO port. */
#define MCU_PORT_E    5     /*!< MCU GPIO port. */
#define MCU_PORT_3    6     /*!< MCU GPIO port. */
#define MCU_PORT_NULL 0xFF  /*!< MCU GPIO port. */
#define MCU_ADC_0     1     /*!< MCU ADC channel. */
#define MCU_ADC_1     2     /*!< MCU ADC channel. */
#define MCU_ADC_2     3     /*!< MCU ADC channel. */
#define MCU_ADC_3     4     /*!< MCU ADC channel. */
#define MCU_ADC_4     5     /*!< MCU ADC channel. */
#define MCU_ADC_5     6     /*!< MCU ADC channel. */
#define MCU_ADC_6     7     /*!< MCU ADC channel. */
#define MCU_ADC_7     8     /*!< MCU ADC channel. */
#define MCU_ADC_NULL  0xFF  /*!< MCU ADC channel. */
#define MCU_PWM_0     1     /*!< MCU PWM channel. */
#define MCU_PWM_1     2     /*!< MCU PWM channel. */
#define MCU_PWM_2     3     /*!< MCU PWM channel. */
#define MCU_PWM_3     4     /*!< MCU PWM channel. */
#define MCU_PWM_4     5     /*!< MCU PWM channel. */
#define MCU_PWM_5     6     /*!< MCU PWM channel. */
#define MCU_PWM_6     7     /*!< MCU PWM channel. */
#define MCU_PWM_7     8     /*!< MCU PWM channel. */
#define MCU_PWM_8     9     /*!< MCU PWM channel. */
#define MCU_PWM_9     10    /*!< MCU PWM channel. */
#define MCU_PWM_10    11    /*!< MCU PWM channel. */
#define MCU_PWM_11    12    /*!< MCU PWM channel. */
#define MCU_PWM_NULL  0xFF  /*!< MCU PWM channel. */
#define MCU_DDC_0     1     /*!< MCU DDC channel. */
#define MCU_DDC_1     2     /*!< MCU DDC channel. */
#define MCU_DDC_2     3     /*!< MCU DDC channel. */
#define MCU_DDC_3     4     /*!< MCU DDC channel. */
#define MCU_IIC_0     1     /*!< MCU IIC channel. */
#define MCU_IIC_1     2     /*!< MCU IIC channel. */
#define MCU_IIC_2     3     /*!< MCU IIC channel. */
#define MCU_IIC_3     4     /*!< MCU IIC channel. */

#define BankSet(k)          BANK_SET = k /*!< Set the type of bank allocation. */
#define ResetWDTimer()      CLR_WDT = 0x55	//george stop it:  0x55 /*!< Clear watch-dog timer. */
#define EnableInterrupt()   EA = 1 /*!< Enable MCU interrupt. */
#define DisableInterrupt()  EA = 0 /*!< Disable MCU interrupt. */


#define McuScalerIntEnable()  { SC_SYNC_INT_FLAG1 = 0x3F; \
                                SC_SYNC_INT_FLAG2 = 0x1F; \
								INTSC_EN |= SC_EN;} /*!< Turn on scaler-related interrupt. */		

#define McuScalerIntDisable()   INTSC_EN &= ~SC_EN  /*!< Turn off scaler-related interrupt. */
#if 0
#define McuScalerHDMIIntEnable()  INTSC_EN |= INT_HDMI  /*!< Turn off HDMI-related interrupt. */
#define McuScalerHDMIIntDisable() INTSC_EN &= ~INT_HDMI /*!< Turn off HDMI-related interrupt. */
#endif

//******************************************************************************
// D A T A   T Y P E   D E F I N E S
//******************************************************************************

//******************************************************************************
// V A R I A B L E S   P R O T O T Y P E
//******************************************************************************

//******************************************************************************
// F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
void McuEnableADC(UCHAR mask);
void McuDisableADC(UCHAR mask);
void McuStartADC(void);
void McuWaitADCComplete(void);
UCHAR McuGetADC(UCHAR channel);
void McuPowerUpADC(void);
void McuPowerDownADC(void);
void McuEnableDDC(UCHAR mask);
void McuDisableDDC(UCHAR mask);
void McuSetDDC(UCHAR channel, UCHAR address, UCHAR ext_edid);
void McuSetDDCWP(UCHAR channel, UCHAR wp);
BOOL McuCheckDDCUpdate(void);
void McuEnableIIC(UCHAR mask);
void McuDisableIIC(UCHAR mask);
void McuSetIIC(UCHAR channel, UCHAR address);
void McuIICPreSendACK(UCHAR mask);
void McuIICReleaseSCL(UCHAR mask);
void McuSetIOByte(UCHAR port, UCHAR value);
void McuSetIOBit(UCHAR port, UCHAR mask, UCHAR value);
void McuSetIODirByte(UCHAR port, UCHAR value);
//void McuSetIODirBit(UCHAR port, UCHAR mask, UCHAR value);
BOOL McuGetIOBit(UCHAR port, UCHAR mask);
void McuCfgIOType(UCHAR port, UCHAR pp, UCHAR pu);
void McuEnablePWM(USHRT mask);
void McuDisablePWM(USHRT mask);
void McuSetPWM(UCHAR channel, UCHAR value);
void McuInitLPD(void);

#endif //__MCU_API_H__
