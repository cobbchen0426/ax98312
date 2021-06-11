/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/

#ifndef __MATRIX_H__
#define __MATRIX_H__

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
/*!
 * Data type for 3x3 matrix.
 */
typedef enum _MTX_TYPE_ {
    MTX_GLOBAL,   /*!< Global matrix. */
    MTX_LOCAL,    /*!< Local matrix. */
    NUM_MTX_TYPE  /*!< Number of matrix types. */
} MTXType;

//******************************************************************************
// V A R I A B L E S   P R O T O T Y P E
//******************************************************************************

//******************************************************************************
// F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
void MTXAPI_SetContrastValue(UCHAR cn);
void MTXAPI_SetContrast(UCHAR cn);
void MTXAPI_SetRGain(USHRT gn);
void MTXAPI_SetGGain(USHRT gn);
void MTXAPI_SetBGain(USHRT gn);
void MTXAPI_SetRGBGainValue(USHRT r,USHRT g,USHRT b);
void MTXAPI_SetRGBGain(USHRT r,USHRT g,USHRT b);
void MTXAPI_SetROffset(UCHAR off);
void MTXAPI_SetGOffset(UCHAR off);
void MTXAPI_SetBOffset(UCHAR off);
void MTXAPI_SetRGBOffsetValue(UCHAR r, UCHAR g, UCHAR b);
void MTXAPI_SetRGBOffset(UCHAR r, UCHAR g, UCHAR b);
void MTXAPI_SetSat(UCHAR sa);
void MTXAPI_SetHue(UCHAR hu);
void MTXAPI_SelMatrix(MTXType type);
void MTXAPI_EnableLocalMatrix(UCHAR en);

#endif //__MATRIX_H__
