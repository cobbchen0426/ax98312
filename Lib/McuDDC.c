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
#define EN_DDC        0x80 /*!< Mask for DDC control register. */
#define WPT_DDC       0x40 /*!< Mask for DDC control register. */
#define LEN_256       0x20 /*!< Mask for DDC control register. */
#define MODE_DDC2     0x10 /*!< Mask for DDC control register. */
#define EN_BACK       0x08 /*!< Mask for DDC control register. */
#define INTV_CLK      0x04 /*!< Mask for DDC control register. */
#define CLR_PTR       0x02 /*!< Mask for DDC control register. */
#define CLR_UPD       0x01 /*!< Mask for DDC control register. */
#define UPD_DDC       0x01 /*!< Mask for DDC control register. */

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
 * Turn on MCU DDC.
 * @param mask Each bit indicates one DDC channel, Bit 0: DDC0, Bit 1: DDC1, ..., Bit 3: DDC3.
 ******************************************************************************/
void McuEnableDDC(UCHAR mask)
{
    if ((mask & BIT0) && (MCU_UART_OUTPUT != 1)) {
        DDC_CTL0 |= BIT7;
    }
    if ((mask & BIT1) && (MCU_UART_OUTPUT != 2)) {
        DDC_CTL1 |= BIT7;
    }
    if ((mask & BIT2) && (MCU_UART_OUTPUT != 3)) {
        DDC_CTL2 |= BIT7;
    }
    if ((mask & BIT3) && (MCU_UART_OUTPUT != 4)) {
        DDC_CTL3 |= BIT7;
    }
}

/**************************************************************************//**
 * Turn off MCU DDC.
 * @param mask Each bit indicates one DDC channel, Bit 0: DDC0, Bit 1: DDC1, ..., Bit 3: DDC3.
 ******************************************************************************/
void McuDisableDDC(UCHAR mask)
{
    if (mask & BIT0) {
        DDC_CTL0 &= ~BIT7;
    }
    if (mask & BIT1) {
        DDC_CTL1 &= ~BIT7;
    }
    if (mask & BIT2) {
        DDC_CTL2 &= ~BIT7;
    }
    if (mask & BIT3) {
        DDC_CTL3 &= ~BIT7;
    }
}

/**************************************************************************//**
 * Configure MCU DDC channel.
 * @param channel DDC channel ID.
 * @param address DDC address, 0xA0, 0xA2, ..., 0xAE.
 * @param ext_edid  1: EDID is 256 bytes, 0: EDID is 128 bytes
 ******************************************************************************/
void McuSetDDC(UCHAR channel, UCHAR address, UCHAR ext_edid)
{
    UCHAR i, ctrl_byte;

    //Avoid error address
    if (0xA0 != (address & 0xF1)) {
        address = 0xA0;
    }
    i = address & 0x0E;
    address = (i << 4) | i;
    ext_edid &= BIT0;
    ctrl_byte = (ext_edid == 1) ? 0x73 : 0x53;

    switch (channel) {
        case MCU_DDC_0:
            DDC_CTL0 = (DDC_CTL0 & BIT7) | ctrl_byte;
            DDC_ADDR0 = address;
            break;

        case MCU_DDC_1:
            DDC_CTL1 = (DDC_CTL1 & BIT7) | ctrl_byte;
            DDC_ADDR1 = address;
            break;

        case MCU_DDC_2:
            DDC_CTL2 = (DDC_CTL2 & BIT7) | ctrl_byte;
            DDC_ADDR2 = address;
            break;

        case MCU_DDC_3:
            DDC_CTL3 = (DDC_CTL3 & BIT7) | ctrl_byte;
            DDC_ADDR3 = address;
            break;
    }
}

#if USE_INTERNAL_EDID == 1
/**************************************************************************//**
 * Turn on/off the write protection function of specified DDC channel.
 * @param channel DDC channel ID.
 * @param wp TRUE to enable the protection else FALSE.
 ******************************************************************************/
void McuSetDDCWP(UCHAR channel, UCHAR wp)
{
    UCHAR ctrl_byte;

    ctrl_byte = wp == 1 ? 0x40 : 0x00;

    switch (channel) {
        case MCU_DDC_0:
            DDC_CTL0 = (DDC_CTL0 & 0xBC) | ctrl_byte;
            break;

        case MCU_DDC_1:
            DDC_CTL1 = (DDC_CTL1 & 0xBC) | ctrl_byte;
            break;

        case MCU_DDC_2:
            DDC_CTL2 = (DDC_CTL2 & 0xBC) | ctrl_byte;
            break;

        case MCU_DDC_3:
            DDC_CTL3 = (DDC_CTL3 & 0xBC) | ctrl_byte;
            break;
    }
}

/**************************************************************************//**
 * Check EDID is updated or not.
 * @return TRUE if EDID is updated else FALSE.
 ******************************************************************************/
BOOL McuCheckDDCUpdate(void)
{
    UCHAR tmp, backup;
    UCHAR *pddc;
    UCHAR *pstat;
    USHRT timer;

    if ((DDC_CTL0 & UPD_DDC) != 0) {
        pddc = &DDC_CTL0;
        pstat = &IIC0_STATUS;
    }
    else if ((DDC_CTL1 & UPD_DDC) != 0) {
        pddc = &DDC_CTL1;
        pstat = &IIC1_STATUS;
    }
    else if ((DDC_CTL2 & UPD_DDC) != 0) {
        pddc = &DDC_CTL2;
        pstat = &IIC2_STATUS;
    }
    else if ((DDC_CTL3 & UPD_DDC) != 0) {
        pddc = &DDC_CTL3;
        pstat = &IIC3_STATUS;
    }
    else {
        return FALSE;
    }

    backup = *pddc & 0x3C;
    *pddc = (EN_DDC | backup | CLR_UPD);
    tmp = *pstat & 0x03;

    timer = GetTimerTick();
    while ((GetTimerTick() - timer) < 500) {
        ResetWDTimer();
        if ((*pstat & 0x03) != tmp) {
            tmp = *pstat & 0x03;
            timer = GetTimerTick();
        }
        if ((*pddc & UPD_DDC) != 0) {
            *pddc = (EN_DDC | backup | CLR_UPD);
            timer = GetTimerTick();
        }
    }

    return TRUE;
}
#endif
