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
 * Change the output of MCU port.
 * @param port MCU I/O Port, one of MCU_PORT_A ~ MCU_PORT_E.
 * @param value Output value.
 ******************************************************************************/
void McuSetIOByte(UCHAR port, UCHAR value)
{
    switch (port) {
        case MCU_PORT_A:
            PortA = value;
            break;

        case MCU_PORT_B:
            PortB = value;
            break;

        case MCU_PORT_C:
            PortC = value;
            break;

        case MCU_PORT_D:
            PortD = value;
            break;

        case MCU_PORT_E:
            PortE = value;
            break;
#ifdef PORT_3_DEFAULT_OUT				
        case MCU_PORT_3:
            P3 = value | 0xCC ; //bit7,6,2,3 must setting 1(high).
            break;
#endif            
    }
}

/**************************************************************************//**
 * Change the output of MCU port.
 * @param port MCU I/O Port, one of MCU_PORT_A ~ MCU_PORT_E.
 * @param mask Select which bit, 0x00: bit 0, 0x01: bit 1, ... 0x80: bit 7.
 * @param value 0 or 1.
 ******************************************************************************/
void McuSetIOBit(UCHAR port, UCHAR mask, UCHAR value)
{
    value &= BIT0;

    if (value == 1) { //Set the bit to 1
        switch (port) {
            case MCU_PORT_A:
                PortA = PortA | RDPA_REG | mask;
                break;
    
            case MCU_PORT_B:
                PortB = PortB | RDPB_REG | mask;
                break;
    
            case MCU_PORT_C:
                PortC = PortC | RDPC_REG | mask;
                break;
    
            case MCU_PORT_D:
                PortD = PortD | RDPD_REG | mask;
                break;
    
            case MCU_PORT_E:
                PortE = PortE | RDPE_REG | mask;
                break;

            case MCU_PORT_3:
                P3 |= mask;
                break;
        }
    }
    else { //Set the bit to 0
        switch (port) {
            case MCU_PORT_A:
                PortA = (PortA | RDPA_REG) & (~mask);
                break;
    
            case MCU_PORT_B:
                PortB = (PortB | RDPB_REG) & (~mask);
                break;
    
            case MCU_PORT_C:
                PortC = (PortC | RDPC_REG) & (~mask);
                break;
    
            case MCU_PORT_D:
                PortD = (PortD | RDPD_REG) & (~mask);
                break;
    
            case MCU_PORT_E:
                PortE = (PortE | RDPE_REG) & (~mask);
                break;

            case MCU_PORT_3:
                P3 &= ~mask;
                break;
        }
    }
}

/**************************************************************************//**
 * Change MCU I/O direction.
 * @param port MCU I/O Port, one of MCU_PORT_A ~ MCU_PORT_E.
 * @param value It will be assigned to the direction control register of port.
 ******************************************************************************/
void McuSetIODirByte(UCHAR port, UCHAR value)
{
    switch (port) {
        case MCU_PORT_A:
            RDPA_REG = value;
            break;

        case MCU_PORT_B:
            RDPB_REG = value;
            break;

        case MCU_PORT_C:
            RDPC_REG = value;
            break;

        case MCU_PORT_D:
            RDPD_REG = value;
            break;

        case MCU_PORT_E:
            RDPE_REG = value;
            break;
    }
}

/**************************************************************************//**
 * Change single bit direction of MCU I/O port.
 * @param port MCU I/O Port, one of MCU_PORT_A ~ MCU_PORT_E.
 * @param mask Select which bit, 0x00: bit 0, 0x01: bit 1, ... 0x80: bit 7.
 * @param value 0 is output. 1 is input.
 ******************************************************************************/
/*
void McuSetIODirBit(UCHAR port, UCHAR mask, UCHAR value)
{
    value &= BIT0;

    if (value == 1) { //Set the bit to Input
        switch (port) {
            case MCU_PORT_A:
                RDPA_REG |= mask;
                break;
    
            case MCU_PORT_B:
                RDPB_REG |= mask;
                break;
    
            case MCU_PORT_C:
                RDPC_REG |= mask;
                break;
    
            case MCU_PORT_D:
                RDPD_REG |= mask;
                break;
    
            case MCU_PORT_E:
                RDPE_REG |= mask;
                break;
        }
    }
    else { //Set the bit to Output
        switch (port) {
            case MCU_PORT_A:
                RDPA_REG &= ~mask;
                break;
    
            case MCU_PORT_B:
                RDPB_REG &= ~mask;
                break;
    
            case MCU_PORT_C:
                RDPC_REG &= ~mask;
                break;
    
            case MCU_PORT_D:
                RDPD_REG &= ~mask;
                break;
    
            case MCU_PORT_E:
                RDPE_REG &= ~mask;
                break;
        }
    }
}
*/
/**************************************************************************//**
 * Get single bit of MCU I/O port.
 * @param port MCU I/O Port, one of MCU_PORT_A ~ MCU_PORT_E.
 * @param mask Select which bit, 0x00: bit 0, 0x01: bit 1, ... 0x80: bit 7.
 * @return TRUE if bit is 1 else FALSE.
 ******************************************************************************/
BOOL McuGetIOBit(UCHAR port, UCHAR mask)
{
    UCHAR result;

    switch (port) {
        case MCU_PORT_A:
            result = PortA & mask;
            break;

        case MCU_PORT_B:
            result = PortB & mask;
            break;

        case MCU_PORT_C:
            result = PortC & mask;
            break;

        case MCU_PORT_D:
            result = PortD & mask;
            break;

        case MCU_PORT_E:
            result = PortE & mask;
            break;

        case MCU_PORT_3:
            result = P3 & mask;
            break;
            
        default:
            result = 0;
            break;
    }

    if (result != 0) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}

#if ENABLE_NEW_MCU_IO == 1
/**************************************************************************//**
 * Change port type, Push-Pull or Open-Drain, of MCU I/O port.
 * @param port MCU I/O Port, one of MCU_PORT_A ~ MCU_PORT_E.
 * @param pp Push-pull or open-drain configuration.
 * @param pu Pull-up resistor configuration.
 ******************************************************************************/
void McuCfgIOType(UCHAR port, UCHAR pp, UCHAR pu)
{
    switch (port) {
        case MCU_PORT_A:
            PTA_PP_REG = pp;
            PTA_PU_REG = pu;
            break;

        case MCU_PORT_B:
            PTB_PP_REG = pp;
            PTB_PU_REG = pu;
            break;

        case MCU_PORT_C:
            PTC_PP_REG = pp;
            PTC_PU_REG = pu;
            break;

        case MCU_PORT_D:
            PTD_PP_REG = pp;
            PTD_PU_REG = pu;
            break;
        case MCU_PORT_E:
            PTE_PP_REG = pp;
            PTE_PU_REG = pu;
            break;
#ifdef PORT_3_DEFAULT_PU
        case MCU_PORT_3:
            PT3_PU_REG = pu;
            break;
#endif
    }
}
#endif
