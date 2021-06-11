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
 * Initialize LVDS-related registers.
 ******************************************************************************/
void LVDSInit(void)
{
    SC_LVDS_MISC_CTRL1 = SCREG_1F5;
    SC_LVDS_CHARGE_PUMP_CURRENT = SCREG_1F4;
    SC_LVDS_MISC_CTRL2 = (SC_LVDS_MISC_CTRL2 & 0x38) | 0x47;
    SC_LVDS_MISC_CTRL4 = SCREG_1F8;
    SC_LVDS_MISC_CTRL5 = SCREG_1F9;
    SC_LVDS_MISC_CTRL6 = SCREG_1FA;
    SC_LVDS_PLL_CTRL = SCREG_1FD;
    SC_LVDS_RSDS_SWITCH = SCREG_1EF;
#if IS_NT68850_SERIES || IS_NT68790_SERIES
    SC_LVDS_DIV = 0x00;//APN 1.0
#endif
    SetLvdsClkDelay(LVDS_DELAY_OFF);
    SetLvdsDataDelay(LVDS_DELAY_OFF);
    SetLvdsSwing(UserPanelData.ucLVDS_Swing);
    SetLvdsChPolSwap();
}

/**************************************************************************//**
 * Turn off LVDS output.
 ******************************************************************************/
void LvdsOff(void)
{
    SC_LVDS_MISC_CTRL1 = SCREG_1F5;  //LVDS output port: pull low
    SC_LVDS_MISC_CTRL3 = 0x00;  //LVDS output port: power down
    SC_POWER_CTRL1 &= ~BIT6;        //LVDS main power off
}

/**************************************************************************//**
 * Turn on LVDS output.
 ******************************************************************************/
void LvdsOn(void)
{
    SC_POWER_CTRL1 |= BIT6;     //LVDS main power on
    SC_LVDS_MISC_CTRL3 |= 0xE0;  //LVDS output port: power on
#if IS_NT68652_SERIES || IS_NT68169_SERIES || IS_NT68661_SERIES
    SC_LVDS_MISC_CTRL2 |= 0x07;
#endif
    SC_LVDS_MISC_CTRL1 = (SCREG_1F5 & ~BIT4);  //LVDS output port: Tri-state output
    SetLvdsSwing(UserPanelData.ucLVDS_Swing);
}

/**************************************************************************//**
 * Set LVDS swing value.
 * @param swing LVDS swing.
 ******************************************************************************/
void SetLvdsSwing(LVDSSwing swing)
{
    code UCHAR ucLVDS_Swing_Table[NUM_LVDS_SWING][3] = {
      // 0x1F6[5:3], 0x1F7[2:0], 0x1B8[5:3]
        {4, 1, 1}, //LVDS_SWING_220
        {5, 1, 1}, //LVDS_SWING_250
        {4, 2, 2}, //LVDS_SWING_300
        {5, 2, 2}, //LVDS_SWING_350
        {0, 3, 3}, //LVDS_SWING_400
        {4, 3, 3}, //LVDS_SWING_450
        {5, 3, 3}, //LVDS_SWING_500
        {6, 3, 3}, //LVDS_SWING_550
        {7, 3, 3}, //LVDS_SWING_600
        {0, 4, 4}, //LVDS_SWING_650
        {4, 4, 4}, //LVDS_SWING_700
        {5, 4, 4}, //LVDS_SWING_750
        {0, 6, 6}, //LVDS_SWING_800
    };

    SC_LVDS_MISC_CTRL2 &= 0xC7;
    SC_LVDS_MISC_CTRL3 &= 0xF8;
    SC_LVDS_CTRL &= 0xC7;

    SC_LVDS_MISC_CTRL2 |= (ucLVDS_Swing_Table[swing][0] << 3);
    SC_LVDS_MISC_CTRL3 |= ucLVDS_Swing_Table[swing][1];
    SC_LVDS_CTRL |= (ucLVDS_Swing_Table[swing][2] << 3);
}

/**************************************************************************//**
 * Set the stage of LVDS clock delay.
 * @param delay Clock delay.
 ******************************************************************************/
void SetLvdsClkDelay(LVDSDelay delay)
{
    if (delay > LVDS_DELAY_7_STAGE)
        delay = LVDS_DELAY_OFF;
    SC_LVDS_CLOCK_DELAY &= 0x88;
    SC_LVDS_CLOCK_DELAY |= (delay | (delay << 4));
}

/**************************************************************************//**
 * Set the stage of LVDS data delay.
 * @param delay Data delay.
 ******************************************************************************/
void SetLvdsDataDelay(LVDSDelay delay)
{
    if (delay > LVDS_DELAY_7_STAGE)
        delay = LVDS_DELAY_OFF;
    SC_LVDS_DATA_DELAY &= 0x88;
    SC_LVDS_DATA_DELAY |= (delay | (delay << 4));
    SC_LVDS_PAD_POWER &= 0xF8;
    SC_LVDS_PAD_POWER |= delay;
}

/**************************************************************************//**
 * Set LVDS P2S-related registers.
 ******************************************************************************/
void SetLvdsP2SByDCLK(void)
{

}

/**************************************************************************//**
 * Set LVDS LVDS Channel Polarity Swap (Positive/Negative)
 ******************************************************************************/
void SetLvdsChPolSwap(void)
{
#if ENABLE_LVDS_POL_SWAP
    SC_LVDS_CTRL |= 0x80;
#endif
}