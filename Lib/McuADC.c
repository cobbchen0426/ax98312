/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************
#include "Include.h"

//******************************************************************************
// M A C R O   D E F I N I T I O N S
//******************************************************************************

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

//******************************************************************************
// F U N C T I O N   B O D Y S
//******************************************************************************

/**************************************************************************//**
 * Turn on MCU ADC.
 * @param mask Each bit indicates one ADC channel, Bit 0: ADC0, Bit 1: ADC1, ..., Bit 7: DDC7.
 ******************************************************************************/
void McuEnableADC(UCHAR mask)
{
    if (mask & BIT0) {
        ADC_CON |= BIT0; //Enable ADC 0
    }
    if (mask & BIT1) {
        ADC_CON |= BIT1; //Enable ADC 1
    }
    if (mask & BIT2) {
        ADC_CON |= BIT2; //Enable ADC 2
    }
    if (mask & BIT3) {
        ADC_CON |= BIT3; //Enable ADC 3
    }
    if (mask & BIT4) {
        ADC_CON2 |= BIT0; //Enable ADC 4
    }
    if (mask & BIT5) {
        ADC_CON2 |= BIT1; //Enable ADC 5
    }
    if (mask & BIT6) {
        ADC_CON2 |= BIT2; //Enable ADC 6
    }
    if (mask & BIT7) {
        ADC_CON2 |= BIT3; //Enable ADC 7
    }
}

/**************************************************************************//**
 * Turn off MCU ADC.
 * @param mask Each bit indicates one ADC channel, Bit 0: ADC0, Bit 1: ADC1, ..., Bit 7: DDC7.
 ******************************************************************************/
void McuDisableADC(UCHAR mask)
{
    if (mask & BIT0) {
        ADC_CON &= ~BIT0; //Disable ADC 0
    }
    if (mask & BIT1) {
        ADC_CON &= ~BIT1; //Disable ADC 1
    }
    if (mask & BIT2) {
        ADC_CON &= ~BIT2; //Disable ADC 2
    }
    if (mask & BIT3) {
        ADC_CON &= ~BIT3; //Disable ADC 3
    }
    if (mask & BIT4) {
        ADC_CON2 &= ~BIT0; //Disable ADC 4
    }
    if (mask & BIT5) {
        ADC_CON2 &= ~BIT1; //Disable ADC 5
    }
    if (mask & BIT6) {
        ADC_CON2 &= ~BIT2; //Disable ADC 6
    }
    if (mask & BIT7) {
        ADC_CON2 &= ~BIT3; //Disable ADC 7
    }
}

/**************************************************************************//**
 * Start to convert analog signal into a 7-bits digital code.
 ******************************************************************************/
void McuStartADC(void)
{
    ADC_CON |= BIT7;	//george ($F00B, bit7: STRT_ADC)
}

/**************************************************************************//**
 * Wait until the ADC complete A/D conversion.
 ******************************************************************************/
void McuWaitADCComplete(void)
{
#if IS_NT68168_SERIES

#define ADC_CONVERT_READY   ((ADC_CON&BIT7)!=0)
#else
#define ADC_CONVERT_READY   ((ADC_REG3&BIT7)!=0)		//complier use this,  george ($F00F, bit7:CMP_ADC)
#endif
	//Sleep(1);	//150526 george	 1ms. can't not use Sleep(1), it will be f/w not normal-work.
    while (ADC_CONVERT_READY == 0) {

        // Remove WDT reset to avoid system handing over here if ADC were abnormal.
        // So far, this issue never happened.
        // Jude 2011/06/10
        //ResetWDTimer();
    }
}

/**************************************************************************//**
 * Get the value of specified ADC channel.
 * @param channel ADC channel.
 * @return ADC value.
 ******************************************************************************/
UCHAR McuGetADC(UCHAR channel)
{
    UCHAR result;

    switch (channel) {
        case MCU_ADC_0:
            result = (ADC_REG0&0x7F);
            break;

        case MCU_ADC_1:
            result = (ADC_REG1&0x7F);
            break;

        case MCU_ADC_2:
            result = (ADC_REG2&0x7F);
            break;

        case MCU_ADC_3:
            result = (ADC_REG3&0x7F);
            break;

        case MCU_ADC_4:
            result = (ADC_REG4&0x7F);
            break;

        case MCU_ADC_5:
            result = (ADC_REG5&0x7F);
            break;

        case MCU_ADC_6:
            result = (ADC_REG6&0x7F);
            break;

        case MCU_ADC_7:
            result = (ADC_REG7&0x7F);
            break;
        default :
            result = 0x7F;
            break;
    }
    
    return result;
}

/**************************************************************************//**
 * Turn on MCU ADC power.
 ******************************************************************************/
void McuPowerUpADC(void)
{
    LDO_ADJ |= BIT4;		//george  ($F050, bit4:ADC_PU)
}

/**************************************************************************//**
 * Turn off MCU ADC power.
 ******************************************************************************/
void McuPowerDownADC(void)
{
    LDO_ADJ &= ~BIT4;
}
