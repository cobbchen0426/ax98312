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
 * Enable MCU IIC.
 * @param mask Each bit indicates one IIC channel, Bit 0: IIC0, Bit 1: IIC1, ..., Bit 3: IIC3.
 ******************************************************************************/
void McuEnableIIC(UCHAR mask)
{

    if ((mask & BIT0) && (MCU_UART_OUTPUT != 1)) {
        IIC0_ADDR |= BIT0;
        IIC0_INT_CLR = 0xFF;
        IIC0_INT_EN = 0xF8;
    }
    if ((mask & BIT1) && (MCU_UART_OUTPUT != 2)) {
        IIC1_ADDR |= BIT0;
        IIC1_INT_CLR = 0xFF;
        IIC1_INT_EN = 0xF8;
    }
    if ((mask & BIT2) && (MCU_UART_OUTPUT != 3)) {
        IIC2_ADDR |= BIT0;
        IIC2_INT_CLR = 0xFF;
        IIC2_INT_EN = 0xF8;
    }
    if ((mask & BIT3) && (MCU_UART_OUTPUT != 4)) {
        IIC3_ADDR |= BIT0;
        IIC3_INT_CLR = 0xFF;
        IIC3_INT_EN = 0xF8;
    }
}

/**************************************************************************//**
 * Disable MCU IIC.
 * @param mask Each bit indicates one IIC channel, Bit 0: IIC0, Bit 1: IIC1, ..., Bit 3: IIC3.
 ******************************************************************************/
void McuDisableIIC(UCHAR mask)
{
    if (mask & BIT0) {
        IIC0_ADDR &= ~BIT0;
    }
    if (mask & BIT1) {
        IIC1_ADDR &= ~BIT0;
    }
    if (mask & BIT2) {
        IIC2_ADDR &= ~BIT0;
    }
    if (mask & BIT3) {
        IIC3_ADDR &= ~BIT0;
    }
}

/**************************************************************************//**
 * Set the address of IIC channel.
 * @param channel IIC channel.
 * @param address IIC slave address.
 ******************************************************************************/
void McuSetIIC(UCHAR channel, UCHAR address)
{
    address &= ~BIT0;

    switch (channel) {
        case MCU_IIC_0:
            IIC0_ADDR = (IIC0_ADDR&BIT0) | address;
            break;

        case MCU_IIC_1:
            IIC1_ADDR = (IIC1_ADDR&BIT0) | address;
            break;

        case MCU_IIC_2:
            IIC2_ADDR = (IIC2_ADDR&BIT0) | address;
            break;

        case MCU_IIC_3:
            IIC3_ADDR = (IIC3_ADDR&BIT0) | address;
            break;
    }
}

/**************************************************************************//**
 * Enable "send ACK" of IIC.
 * XXX This function has special history.
 * @param mask Each bit indicates one IIC channel, Bit 0: IIC0, Bit 1: IIC1, ..., Bit 3: IIC3.
 ******************************************************************************/
void McuIICPreSendACK(UCHAR mask)
{
    if ((mask & BIT0) && (MCU_UART_OUTPUT != 1)) {
        IIC0_CFG |= SEND_ACK;
    }
    if ((mask & BIT1) && (MCU_UART_OUTPUT != 2)) {
        IIC1_CFG |= SEND_ACK;
    }
    if ((mask & BIT2) && (MCU_UART_OUTPUT != 3)) {
        IIC2_CFG |= SEND_ACK;
    }
    if ((mask & BIT3) && (MCU_UART_OUTPUT != 4)) {
        IIC3_CFG |= SEND_ACK;
    }
}

/**************************************************************************//**
 * Release SCL by clearing NACK.
 * XXX This function has special history.
 * @param mask Each bit indicates one IIC channel, Bit 0: IIC0, Bit 1: IIC1, ..., Bit 3: IIC3.
 ******************************************************************************/
void McuIICReleaseSCL(UCHAR mask)
{
    if ((mask & BIT0) && (MCU_UART_OUTPUT != 1)) {
        IIC0_INT_CLR = INTNAK;
    }
    if ((mask & BIT1) && (MCU_UART_OUTPUT != 2)) {
        IIC1_INT_CLR = INTNAK;
    }
    if ((mask & BIT2) && (MCU_UART_OUTPUT != 3)) {
        IIC2_INT_CLR = INTNAK;
    }
    if ((mask & BIT3) && (MCU_UART_OUTPUT != 4)) {
        IIC3_INT_CLR = INTNAK;
    }
}
