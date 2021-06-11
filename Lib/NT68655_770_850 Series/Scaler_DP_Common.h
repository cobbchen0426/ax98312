/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/

#ifndef __SCALER_DP_COMMON_H__
#define __SCALER_DP_COMMON_H__

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************
#include "ScalerType.h"
#include "Typedef.h"

//******************************************************************************
// M A C R O   D E F I N I T I O N S
//******************************************************************************
#define DP_162G      1
#define DP_270G      2
#define DP_540G      3

#define DP_1LANE     1
#define DP_2LANE     2
#define DP_4LANE     4

#define DP_LINKRATE DP_270G
#define DP_LANECNT  DP_4LANE

//******************************************************************************
// D A T A   T Y P E   D E F I N E S
//******************************************************************************

//******************************************************************************
// V A R I A B L E S   P R O T O T Y P E
//******************************************************************************

//******************************************************************************
// F U N C T I O N    P R O T O T Y P E S
//******************************************************************************
void SetDPLink(void);
UCHAR GetDPLink(void);
void ClrDPLink(void);
void DP_InitDPCD(void);
void DP_InitDPConfigPage(void);
void DP_InitPHY(void);
void DPPHY_PowerOn(void);
void DPPHY_PowerOff(void);
void DP_ConfigAUX2IICSpeed(void);
void DP_CLKOn(void);
void DP_CLKOff(void);

#endif
