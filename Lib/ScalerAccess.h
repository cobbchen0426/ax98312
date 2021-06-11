/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/

#ifndef __SCALERACCESS_H__
#define __SCALERACCESS_H__

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

//******************************************************************************
// F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
USHRT ReadShortScaler(UCHAR *address);
ULONG Read3ByteScaler(UCHAR *address);
USHRT ReadShortScalerHighLowFilter(UCHAR *address);
ULONG Read3ByteScalerHighLowFilter(UCHAR *address);
void WriteShortScaler(UCHAR *address, USHRT value);
void Write3ByteScaler(UCHAR *address, ULONG value);
void WriteScalerIndexPort(UCHAR type, USHRT offset, USHRT len, UCHAR *p);
void WriteScalerIndexPort2(UCHAR type, USHRT offset, USHRT len, UCHAR *p);

#endif //__SCALERACCESS_H__
