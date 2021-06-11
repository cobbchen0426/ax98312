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
// S T A T I C   V A R I A B L E S
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
 * Initialize NR-related registers.
 ******************************************************************************/
void NRInit(void)
{
    SC_NR_CTRL = 0x00;
    SC_NR_THR_CTRL1 = 0x00;
    SC_JITTER_CTRL = 0x00;
    SC_NR_THR_CTRL2 = 0x00;
    SC_NR3_CTRL1 = 0x00;
    SC_NR3_CTRL2 = 0x00;
}

/**************************************************************************//**
 * Set NR type.
 * The type is one of 
 *     NR_MODE_OFF, 
 *     NR_MODE_1, 
 *     NR_MODE_2 and
 *     NR_MODE_3.
 * The configuration is multi-selection of
 *     NR_CFG_RDM_TP,
 *     NR_CFG_NR2_EN,
 *     NR_CFG_ROUND,
 *     NR_CFG_EDGE_DET,
 *     NR_CFG_NR_DITH_EN,
 *     NR_CFG_JC_EN and
 *     NR_CFG_GC_EN.
 * @param type NR type.
 * @param cfg NR configuration.
 ******************************************************************************/
void NRSetNRType(NRType type, UCHAR cfg)
{
    SC_NR_CTRL = type | (cfg & 0xF0);

    if (cfg & NR_CFG_NR_DITH_EN) {
        SC_NR_THR_CTRL2 |= BIT4;
    }
    else {
        SC_NR_THR_CTRL2 &= ~BIT4;
    }

    if (cfg & NR_CFG_JC_EN) {
        SC_JITTER_CTRL |= BIT4;
    }
    else {
        SC_JITTER_CTRL &= ~BIT4;
    }

    // APN resuests it
    SC_NR_THR_CTRL2 &= ~BIT5;
}

/**************************************************************************//**
 * Set the value of edge detection threshold.
 * @param value The value of edge detection threshold.
 ******************************************************************************/
void NRSetEdgeThr(UCHAR value)
{
    SC_NR_THR_CTRL1 &= 0x0F;
    SC_NR_THR_CTRL1 |= (value <<4);
}

/**************************************************************************//**
 * Set the threshold of filter adjustment.
 * @param value The threshold of filter adjustment.
 ******************************************************************************/
void NRSetNRThr(UCHAR value)
{
    SC_NR_THR_CTRL1 &= 0xF0;
    SC_NR_THR_CTRL1 |= (value & 0x0F);
}

/**************************************************************************//**
 * Set the value of jitter correction level.
 * @param value The value of jitter correction level.
 ******************************************************************************/
void NRSetJCLvl(UCHAR value)
{
    SC_JITTER_CTRL &= 0xF0;
    SC_JITTER_CTRL |= (value & 0x0F);
}

/**************************************************************************//**
 * Set the threshold of NR2 filter adjustment.
 * @param value The threshold of NR2 filter adjustment.
 ******************************************************************************/
void NRSetNR2Thr(UCHAR value)
{
    SC_NR_THR_CTRL2 &= 0xF0;
    SC_NR_THR_CTRL2 |= (value & 0x0F);
}

/**************************************************************************//**
 * Configure ghost canceling filter.
 * @param win The active position of ghost canceling filter.
 * @param pk_thr The peak threshold.
 * @param lf_thr The low pass filter threshold.
 ******************************************************************************/
void NRSetGCCfg(UCHAR win, UCHAR pk_thr, UCHAR lf_thr)
{
    SC_NR3_CTRL1 = 0x98;
    SC_NR3_CTRL1 |= (win & 0x07);

    if (pk_thr > 60) {
        pk_thr = 60;
    }

    if (lf_thr > 60) {
        lf_thr = 60;
    }

    pk_thr = (pk_thr + 2) / 4;
    lf_thr = (lf_thr + 2) / 4;

    SC_NR3_CTRL2 = (pk_thr << 4) | lf_thr;
}
