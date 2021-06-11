/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/
#ifndef __3D_H__
#define __3D_H__

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************
#include "Typedef.h"

//******************************************************************************
// G L O B A L   D E F I N I T I O N S
//******************************************************************************
#define Is2DTo3DAdaptive()      (UserData.uc3DCfg & BIT0)
#define Is3DLRSwap()            (UserData.uc3DCfg & BIT1)
#define Is3DTo2DEnabled()       (UserData.uc3DCfg & BIT2)

#define TurnOn2DTo3DAdaptive()  (UserData.uc3DCfg |= BIT0)
#define TurnOn3DLRSwap()        (UserData.uc3DCfg |= BIT1)
#define TurnOn3DTo2D()          (UserData.uc3DCfg |= BIT2)

#define TurnOff2DTo3DAdaptive() (UserData.uc3DCfg &= ~BIT0)
#define TurnOff3DLRSwap()       (UserData.uc3DCfg &= ~BIT1)
#define TurnOff3DTo2D()         (UserData.uc3DCfg &= ~BIT2)

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
void InitScaler3D(void);
void Set2DTo3DMode(UCHAR mode);
void Set2DTo3DAdaptive(UCHAR enable);
void Set2DTo3DDepth(UCHAR depth);
void Set2DTo3DView(UCHAR view);
void Set3DLRSwap(UCHAR swap);
void PerformAdaptive2DTO3D(void);
void Set3DTo2DMode(UCHAR on);
UCHAR DetectAMD3DModeChange(void);

#endif //__3D_H__
