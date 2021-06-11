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
/*!
 * Write red gamma through index port.
 */
//#define GMAPI_LoadRGM320(p) WriteScalerIndexPort(GAMMA_TBL_RED|BIT2, 0, 256, p)
/*!
 * Write green gamma through index port.
 */
//#define GMAPI_LoadGGM320(p) WriteScalerIndexPort(GAMMA_TBL_GREEN|BIT2, 0, 256, p)
/*!
 * Write blue gamma through index port.
 */
//#define GMAPI_LoadBGM320(p) WriteScalerIndexPort(GAMMA_TBL_BLUE|BIT2, 0, 256, p)
//-----------------------------------------------------------------------------
/*!
 * Write red gamma through index port.
 */
#define GMAPI_LoadRGM320(p) WriteScalerIndexPort(GAMMA_TBL_RED|BIT2, 0, 320, p)
/*!
 * Write green gamma through index port.
 */
#define GMAPI_LoadGGM320(p) WriteScalerIndexPort(GAMMA_TBL_GREEN|BIT2, 0, 320, p)
/*!
 * Write blue gamma through index port.
 */
#define GMAPI_LoadBGM320(p) WriteScalerIndexPort(GAMMA_TBL_BLUE|BIT2, 0, 320, p)

//******************************************************************************
// E X T E R N A L   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// F U N C T I O N   B O D Y S
//******************************************************************************

/**************************************************************************//**
 * Turn on gamma.
 ******************************************************************************/
void GMAPI_EnableGamma(void)
{
 SC_GAMMA_CTRL |= BIT7; 
}

/**************************************************************************//**
 * Turn off gamma.
 ******************************************************************************/
void GMAPI_DisableGamma(void)
{
#if ENABLE_10TO12_GAMMA == ON
    SC_GAMMA_CTRL |= BIT6;
    SC_GAMMA_CTRL &= ~BIT7;
#elif ENABLE_10TO10_GAMMA == ON
    SC_GAMMA_CTRL &= ~(BIT7|BIT6);
#else
    // XXX Need to check other scalers.
    SC_GAMMA_CTRL &= ~(BIT7|BIT6);
#endif
}

#if ENABLE_10TO10_GAMMA == ON
/**************************************************************************//**
 * Extend 320-bytes gamma to 1280-bytes gamma and write it to scaler.
 * @param pgamma Pointer to the 320-bytes gamma table.
 * @param channel One of GAMMA_TBL_RED, GAMMA_TBL_GREEN and GAMMA_TBL_BLUE.
 ******************************************************************************/
void GMAPI_LoadSingleTable320To1280(UCHAR *pgamma, UCHAR channel)
{
    USHRT i, j, k, addr;
    USHRT start, end, now[4];

    SC_INDEX_CTRL = (channel) | BIT2;
    SC_INDEX_ADDR_LO = 0;
    SC_INDEX_ADDR_HI = 0;

    start = 0;
    for (i = 0; i < 256; i += 4) 
	{
        	addr = i * 5 / 4;
        for (j = 0; j < 4; j++) 
		{
            		end = (pgamma[addr + 1 + j] << 2) + (((pgamma[addr]) >> (j * 2)) & 0x03);
           		 for (k = 0; k < 4; k++) 
				 {
                			now[k] = (end * k + (4 - k) * start) >> 2;
            			}

            if ((i != 0) || (j != 0)) 
		{
                SC_INDEX_DATA = (UCHAR)((now[0] & 0x03) + ((now[1] & 0x03) << 2) + ((now[2] & 0x03) << 4) + ((now[3] & 0x03) << 6));
                SC_INDEX_DATA = (UCHAR)(now[0] >> 2);
                SC_INDEX_DATA = (UCHAR)(now[1] >> 2);
                SC_INDEX_DATA = (UCHAR)(now[2] >> 2);
                SC_INDEX_DATA = (UCHAR)(now[3] >> 2);
              }

            		start = end;
           	 ResetWDTimer();
        	}
    }
    end = (end - now[0]) + end;
    if (end > 1024)
        end = 1024;
    for (k = 0; k < 4; k++) {
        now[k] = (end * k + (4 - k) * start) >> 2;
    }
    SC_INDEX_DATA = ((now[0] & 0x03) + ((now[1] & 0x03) << 2) + ((now[2] & 0x03) << 4) + ((now[3] & 0x03) << 6));
    SC_INDEX_DATA = (UCHAR) (now[0] >> 2);
    SC_INDEX_DATA = (UCHAR) (now[1] >> 2);
    SC_INDEX_DATA = (UCHAR) (now[2] >> 2);
    SC_INDEX_DATA = (UCHAR) (now[3] >> 2);
    ResetWDTimer();
}
#endif

#if ENABLE_GAMMA == ON
/**************************************************************************//**
 * Write R/G/B 320-bytes gamma tables to scaler.
 * @param pgamma Pointer to the R/G/B 320-bytes gamma table.
 ******************************************************************************/
void GMAPI_LoadGamma320(Gamma320 *pgamma)
{
    GMAPI_DisableGamma();
    Sleep(50); // 24Hz is around 41ms
#if ENABLE_10TO12_GAMMA == ON
#elif ENABLE_10TO10_GAMMA == ON
    GMAPI_LoadSingleTable320To1280(pgamma->ucRGamma, GAMMA_TBL_RED);
    GMAPI_LoadSingleTable320To1280(pgamma->ucGGamma, GAMMA_TBL_GREEN);
    GMAPI_LoadSingleTable320To1280(pgamma->ucBGamma, GAMMA_TBL_BLUE);
#else
    GMAPI_LoadRGM320(pgamma->ucRGamma);
    GMAPI_LoadGGM320(pgamma->ucGGamma);
    GMAPI_LoadBGM320(pgamma->ucBGamma);
#endif
}

#endif

#if ENABLE_PRE_REV_GAMMA == ON
void GMAPI_EnablePreGamma(void)
{
  SC_GAMMA_CTRL |= BIT0;					

}

void GMAPI_DisablePreGamma(void)
{
    SC_GAMMA_CTRL &= ~BIT0;
}

void GMAPI_LoadPreGamma16bit(USHRT lv, UCHAR *pregamma)
{
    GMAPI_DisablePreGamma();
    GMAPI_DisableRevGamma();
    Sleep(50);
    WriteScalerIndexPort(PREGAMMA_TBL_RGB|BIT2, 0, (lv<<1), pregamma);
}

void GMAPI_EnableRevGamma(void)
{
    SC_GAMMA_CTRL |= BIT2;
}

void GMAPI_DisableRevGamma(void)
{
    SC_GAMMA_CTRL &= ~BIT2;
}

void GMAPI_LoadRevGamma16bit(USHRT lv, UCHAR *revgamma)
{
    GMAPI_DisablePreGamma();
    GMAPI_DisableRevGamma();
    Sleep(50);
    WriteScalerIndexPort(REVGAMMA_TBL_RGB|BIT2, 0, (lv<<1), revgamma);
}
#endif
