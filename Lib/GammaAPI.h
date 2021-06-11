/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/

#ifndef __GAMMAAPI_H__
#define __GAMMAAPI_H__

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************
#include "Typedef.h"
#include "GammaType.h"

//******************************************************************************
// M A C R O   D E F I N I T I O N S
//******************************************************************************

//******************************************************************************
// D A T A   T Y P E   D E F I N E S
//******************************************************************************

//******************************************************************************
// V A R I A B L E S   P R O T O T Y P E
//******************************************************************************

//******************************************************************************
// F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
void GMAPI_EnableGamma(void);
void GMAPI_DisableGamma(void);
void GMAPI_LoadGamma320(Gamma320 *pgamma);

#if ENABLE_PRE_REV_GAMMA == ON
void GMAPI_EnablePreGamma(void);
void GMAPI_DisablePreGamma(void);
void GMAPI_LoadPreGamma16bit(USHRT lv, UCHAR *pregamma);
void GMAPI_EnableRevGamma(void);
void GMAPI_DisableRevGamma(void);
void GMAPI_LoadRevGamma16bit(USHRT lv, UCHAR *revgamma);
#endif

#endif //__GAMMAAPI_H__
