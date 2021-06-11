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
#include "ScalerProfile.h"

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
 * Initialize dithering-related registers.
 ******************************************************************************/
void DithInit(void)
{
    SC_DITH_CTRL = DT158;
    SC_SRGB_DITH_CTRL = DT1D8;
    SC_DISP_RANDOM_DITH_CTRL = DT1DA;
    SC_GAMMA_DITH_CTRL = DT1DB;    //10 bit gamma dithering mode
}

/**************************************************************************//**
 * Set dithering mode.
 * @param type Dithering mode.
 * @param mode_10 10 mode when dithering mode is static.
 * @param mode_01 01 mode when dithering mode is static.
 ******************************************************************************/
void DithSetDitherMode(DitherType type, UCHAR mode_10, UCHAR mode_01)
{
    switch(type) {
        case DITH_TP_RDM:
            SC_DISP_RANDOM_DITH_CTRL = 0x10;
            SC_DITH_CTRL &= ~BIT3;
            SC_DITH_CTRL |= BIT0;
            break;
        case DITH_TP_VRDM:
            SC_DISP_RANDOM_DITH_CTRL = 0x90;
            SC_DITH_CTRL &= ~BIT3;
            SC_DITH_CTRL |= BIT0;
            break;
        case DITH_TP_STATIC:
            SC_DISP_RANDOM_DITH_CTRL = 0x00;
            mode_10 &= 0x03;
            mode_10 <<= 4;
            mode_01 &= 0x07;
            SC_GAMMA_DITH_CTRL = mode_01 | mode_10;
            SC_DITH_CTRL |= BIT3;
            break;
        case DITH_TP_MIX:
            SC_DISP_RANDOM_DITH_CTRL = 0xF4;
            mode_10 &= 0x0F;
            mode_10 <<= 4;
            SC_DITH_CTRL &= 0x0F;
            SC_DITH_CTRL |= mode_10;
            SC_DITH_CTRL &= ~BIT3;
            SC_DITH_CTRL |= BIT0;
            break;
        case DITH_TP_OFF:
        default:
            SC_DITH_CTRL &= ~(BIT3|BIT0);
            break;
    };
}
