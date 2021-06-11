/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/

#ifndef __NVRAM_IIC_H__
#define __NVRAM_IIC_H__

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
//void NvramWriteIICSeq(UCHAR slave, UCHAR addr, USHRT len, UCHAR *ptr);	  //george-test
//void NvramReadIICSeq(UCHAR slave, UCHAR addr, USHRT len, UCHAR *ptr);	  //george-test
BOOL NvramCheckDevice(UCHAR slave);		//george-test

void WriteIICWordSeq(UCHAR slave, UCHAR addr, USHRT ptr);
void ReadIICWordSeq(UCHAR slave, UCHAR addr, USHRT *ptr);
void ReadIICCM3218ARA(UCHAR slave, UCHAR ara_data);	//george-create

#endif //__NVRAM_IIC_H__
