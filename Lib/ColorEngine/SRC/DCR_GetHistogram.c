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
#include "stdio.h"
#include "math.h"
#include "ScalerReg.h"
#include "BFAPI.h"
#include "DCR.h"

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
extern xdata ULONG ulCurHisgrmTotal;
extern xdata USHRT usCurHisgrm[BF_IG_PARTITIONS];

//******************************************************************************
// S T A T I C   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// E X T E R N A L   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// F U N C T I O N   B O D Y S
//******************************************************************************

/**************************************************************************//**
 * Get the value of n'th histogram.
 * @param index Index of histogram. The range is 0~15.
 * @return Value of n'th histogram.
 ******************************************************************************/
USHRT DCR_GetHistogram(UCHAR index)
{
    if (index < BF_IG_PARTITIONS)
        return usCurHisgrm[index];
    return 0;
}

/**************************************************************************//**
 * Get total histogram.
 * @return Total histogram.
 ******************************************************************************/
ULONG DCR_GetTotalHistogram(void)
{
    return ulCurHisgrmTotal;
}
