/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/

#ifndef __FE2P_API_H__
#define __FE2P_API_H__

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************
#include "Typedef.h"
#include "fe2p v3.13.h"

//******************************************************************************
// M A C R O   D E F I N I T I O N S
//******************************************************************************
#define POT_SAVE_COUNT 30 /*!< Time to save POT. The unit is minute */
#define POT_SAVE_H    ((ULONG)4095 * 8 * POT_SAVE_COUNT / 60) /*!< Time to save POT. The unit is hour */

#if POT_SAVE_COUNT < 10
#error "POT_SAVE_COUNT is less than 10. Please review the setting!"
#endif

//******************************************************************************
// D A T A   T Y P E   D E F I N E S
//******************************************************************************

//******************************************************************************
// V A R I A B L E S   P R O T O T Y P E
//******************************************************************************

//******************************************************************************
// F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
void FE2P_RamInitialize(void);
void FE2P_NvramWrite(USHRT Addr, USHRT Length, UCHAR *Ptr);
void FE2P_NvramRead(USHRT Addr, USHRT Length, UCHAR *Ptr);
void FE2P_SaveToFlash(void);
void RecordTimeScale(void);
void EraseTimeScale(void);
void DecodeTimeScale(void);

#endif //__FE2P_API_H__
