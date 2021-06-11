/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/
#ifndef __UTILITIES_H__
#define __UTILITIES_H__

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************
#include "Typedef.h"

//******************************************************************************
// E X T E R N A L   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
#define Remap100ToAny(a,b) (((ULONG)(a)*(b)+50)/100)
#define Remap100To1023(a)  Remap100ToAny(a,1023)
#define Remap100To800(a)   Remap100ToAny(a,800)
#define Remap100To255(a)   Remap100ToAny(a,255)
#define Remap100To225(a)   Remap100ToAny(a,225)
#define Remap100To200(a)   Remap100ToAny(a,200)
#define Remap100To63(a)    Remap100ToAny(a,63)

#define RemapAnyTo100(a,b) (((ULONG)(a)*100+(b/2))/b)
#define Remap255To100(a)   RemapAnyTo100(a,255)
#define Remap200To100(a)   RemapAnyTo100(a,200)
#define Remap63To100(a)    RemapAnyTo100(a,63)

#define SramDebug(x, y)    { UCHAR xdata *Ptr; \
                             Ptr = x; \
                             *Ptr = y; }

#endif //__UTILITIES_H__
