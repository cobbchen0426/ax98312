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
 * Turn on MCU PWM.
 * @param mask Each bit indicates one PWM channel, Bit 0: PWM0, Bit 1: PWM1, ..., Bit 11: PWM11.
 ******************************************************************************/
void McuEnablePWM(USHRT mask)
{
    if (mask & BIT0) {
        ENPWM_LB |= BIT0; //Enable PWM 0
    }
    if (mask & BIT1) {
        ENPWM_LB |= BIT1; //Enable PWM 1
    }
    if (mask & BIT2) {
        ENPWM_HB |= BIT0; //Enable PWM 2
    }
    if (mask & BIT3) {
        ENPWM_HB |= BIT1; //Enable PWM 3
    }
    if (mask & BIT4) {
        ENPWM_HB |= BIT2; //Enable PWM 4
    }
    if (mask & BIT5) {
        ENPWM_HB |= BIT3; //Enable PWM 5
    }
    if (mask & BIT6) {
        ENPWM_HB |= BIT4; //Enable PWM 6
    }
    if (mask & BIT7) {
        ENPWM_HB |= BIT5; //Enable PWM 7
    }
    if (mask & (BIT0<<8)) {
        ENPWM_HB |= BIT6; //Enable PWM 8
    }
    if (mask & (BIT1<<8)) {
        ENPWM_HB |= BIT7; //Enable PWM 9
    }
    if (mask & (BIT2<<8)) {
        ENPWM_UB |= BIT0; //Enable PWM 10
    }
    if (mask & (BIT3<<8)) {
        ENPWM_UB |= BIT1; //Enable PWM 11
    }
}

/**************************************************************************//**
 * Turn off MCU PWM.
 * @param mask Each bit indicates one PWM channel, Bit 0: PWM0, Bit 1: PWM1, ..., Bit 11: PWM11.
 ******************************************************************************/
void McuDisablePWM(USHRT mask)
{
    if (mask & BIT0) {
        ENPWM_LB &= ~BIT0; //Disable PWM 0
    }
    if (mask & BIT1) {
        ENPWM_LB &= ~BIT1; //Disable PWM 1
    }
    if (mask & BIT2) {
        ENPWM_HB &= ~BIT0; //Disable PWM 2
    }
    if (mask & BIT3) {
        ENPWM_HB &= ~BIT1; //Disable PWM 3
    }
    if (mask & BIT4) {
        ENPWM_HB &= ~BIT2; //Disable PWM 4
    }
    if (mask & BIT5) {
        ENPWM_HB &= ~BIT3; //Disable PWM 5
    }
    if (mask & BIT6) {
        ENPWM_HB &= ~BIT4; //Disable PWM 6
    }
    if (mask & BIT7) {
        ENPWM_HB &= ~BIT5; //Disable PWM 7
    }
    if (mask & (BIT0<<8)) {
        ENPWM_HB &= ~BIT6; //Disable PWM 8
    }
    if (mask & (BIT1<<8)) {
        ENPWM_HB &= ~BIT7; //Disable PWM 9
    }
    if (mask & (BIT2<<8)) {
        ENPWM_UB &= ~BIT0; //Disable PWM 10
    }
    if (mask & (BIT3<<8)) {
        ENPWM_UB &= ~BIT1; //Disable PWM 11
    }
}

/**************************************************************************//**
 * Set the duty of MCU PWM.
 * @param channel PWM channel.
 * @param value PWM duty. The range is 0x00 ~ 0xFF.
 ******************************************************************************/
void McuSetPWM(UCHAR channel, UCHAR value)
{
    switch (channel) {
        case MCU_PWM_0:
            PWM_REG0 = value;
            break;

        case MCU_PWM_1:
            PWM_REG1 = value;
            break;

        case MCU_PWM_2:
            PWM_REG2 = value;
            break;

        case MCU_PWM_3:
            PWM_REG3 = value;
            break;

        case MCU_PWM_4:
            PWM_REG4 = value;
            break;

        case MCU_PWM_5:
            PWM_REG5 = value;
            break;

        case MCU_PWM_6:
            PWM_REG6 = value;
            break;

        case MCU_PWM_7:
            PWM_REG7 = value;
            break;

        case MCU_PWM_8:
            PWM_REG8 = value;
            break;

        case MCU_PWM_9:
            PWM_REG9 = value;
            break;

        case MCU_PWM_10:
            PWM_REG10 = value;
            break;

        case MCU_PWM_11:
            PWM_REG11 = value;
            break;
    }
}
