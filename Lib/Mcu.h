/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/

#ifndef __MCU_H__
#define __MCU_H__

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************
#include "Typedef.h"

//******************************************************************************
// M A C R O   D E F I N I T I O N S
//******************************************************************************

//******************************************************************************
// D A T A   T Y P E   D E F I N E S
//******************************************************************************

//******************************************************************************
// V A R I A B L E S   P R O T O T Y P E
//******************************************************************************
extern UCHAR ucTL0_Normal_Power;
extern UCHAR ucTH0_Normal_Power;
extern UCHAR ucTL0_LOW_POWER,ucTH0_LOW_POWER,ucTL0_LOW_POWER_3M,ucTH0_LOW_POWER_3M;

//******************************************************************************
// F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
void McuInitialize(void);
BOOL McuCheck5V(void);
void McuPowerUpAPLL(void);

#if (XRS232 == DISABLE)
void McuPowerDownAPLL(void);
#endif

ULONG GetCPUClcok(void);
UCHAR GetUARTTimer(ULONG speed);

#endif //__MCU_H__
