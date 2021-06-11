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
/*!
 * DCRAPI Version.
 * The following string is the specific string for EasyWriter.
 * We can show the version on EasyWriter.
 */
static code UCHAR SpecTab_DCRVersion[] = {
    0x55, 0xaa, 0x66, 0x99, __FILE__" Version 3.0.00 "__DATE__"#"
};

/*!
 * The threshold of difference of previous and current histogram.
 * 64 = 128 x 128 / 256 (128 x 128 is the size of one block.)
 */
#define ACE_THD_HIS_DIFF 64

//******************************************************************************
// G L O B A L   V A R I A B L E S
//******************************************************************************
xdata ULONG ulCurHisgrmTotal = 0;          /*!< Total count of histogram. */
xdata USHRT usCurHisgrm[BF_IG_PARTITIONS]; /*!< Values of current histogram. */
xdata USHRT usPrvHisgrm[BF_IG_PARTITIONS]; /*!< Values of previous histogram. */

//******************************************************************************
// S T A T I C   V A R I A B L E S
//******************************************************************************
static UCHAR *VersionPtr = SpecTab_DCRVersion; /*!< We use this to disable compile warning. */

//******************************************************************************
// E X T E R N A L   V A R I A B L E   P R O T O T Y P E S
//******************************************************************************

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
 * According to the present display, update Y histogram.
 * @param reset TRUE to reset the histogram buffer to default value.
 * @return TRUE if the update is completed else FALSE.
 ******************************************************************************/
BOOL DCR_UpdateHistogram(UCHAR reset)
{
    UCHAR i, tmpHis1, tmpHis2, tmpHis3;
    UCHAR reg = 0;

    if (((SC_ACE_FUNC_CTRL2 & 0x01) != 0) && (reset == 0))
        return FALSE;

    if ((SC_BRIGHT_FRM_SEL&BIT0) == BIT0)
        reg |= 0x20;
        
    SC_ACE_FUNC_CTRL2 = reg;

    // Read Histograms //
    ulCurHisgrmTotal = 0;

    if (reset) {
        for (i = 0; i < BF_IG_PARTITIONS; i++) {
            usCurHisgrm[i] = 0;
            usPrvHisgrm[i] = 0;
        }
    }
    else {
        for (i = 0; i < BF_IG_PARTITIONS; i++) {
    	    tmpHis1 = SC_ACE_DATA_PORT;
    	    tmpHis2 = SC_ACE_DATA_PORT;
    	    tmpHis3 = SC_ACE_DATA_PORT;
            usCurHisgrm[i] = (USHRT)tmpHis3*256 + tmpHis2;
            ulCurHisgrmTotal += usCurHisgrm[i];
        }
    }
        
    SC_ACE_FUNC_CTRL2 = reg | 0x01;

    return TRUE;
}

/**************************************************************************//**
 * Save the value of current histogram to the buffer of previous histogram.
 ******************************************************************************/
void DCR_UpdatePrevHistogram(void)
{
    UCHAR i;
    for (i = 0; i < BF_IG_PARTITIONS; i++) {
        usPrvHisgrm[i] = usCurHisgrm[i];
    }
}

/**************************************************************************//**
 * Get the difference between current histogram and previous histogram.
 * @param index The index of histogram.
 * @return The value of difference.
 ******************************************************************************/
USHRT DCR_GetHistogramDiff(UCHAR index)
{
    return abs(usPrvHisgrm[index] - usCurHisgrm[index]);
}

/**************************************************************************//**
 * This function is used to detect the scene changed or not..
 * @return TRUE if scene is changed else FALSE.
 ******************************************************************************/
BOOL DCR_IsSceneChanged(void)
{
    UCHAR i;
    UCHAR diff_cnt;
    UCHAR scv_diff;

    if (ulCurHisgrmTotal == 0)
        return FALSE;

    diff_cnt = 0;
    scv_diff = 0;

    // Compare Histograms //
    for (i = 0; i < BF_IG_PARTITIONS; i++) {
        if (DCR_GetHistogramDiff(i) > ACE_THD_HIS_DIFF) {
            diff_cnt++; // Counter to count the number of difference.

            // If scv_diff >= 2 means there are successive differences.
            // If yes, rise the flag of successive difference
            scv_diff++;
            if (scv_diff > 0x01) {
                scv_diff |= 0x80;
            }
        }
        else {
            scv_diff &= 0x80; // Reset the counter of successive difference
        }
    }

    if (((scv_diff & 0x80) != 0) && (diff_cnt < 3)) {
        // Check the two differences of histograms are adjacent or not.
        // If yes, it means no scene changed.
        return FALSE;
    }
    else if (diff_cnt) {
        return TRUE;
    }

    return FALSE;
}
