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
#define OVERALL      1024 /*!< The total weighting of i-gamma. 64 * 16 = 1024. */

//******************************************************************************
// G L O B A L   V A R I A B L E S
//******************************************************************************

//******************************************************************************
// S T A T I C   V A R I A B L E S
//******************************************************************************
static UCHAR ucMinIGTable[BF_IG_PARTITIONS];  /*!< The minimum weighting of each segment of i-gamma. */
static USHRT usLowerBond = 0;                 /*!< The sum of minimum weighting of each segment of i-gamma. */
static xdata USHRT usNewIG[BF_IG_PARTITIONS]; /*!< New i-gamma curve. */
static xdata USHRT usCurIG[BF_IG_PARTITIONS]; /*!< The present i-gamma curve. */
static BOOL bUpdateIG = FALSE;                /*!< Flag to indicate the update of i-gamma is completed or not. */
static xdata ACEType ucACEMode = ACE_SMOOTH;  /*!< The type of ACE update. */

//******************************************************************************
// E X T E R N A L   V A R I A B L E   P R O T O T Y P E S
//******************************************************************************
extern xdata ULONG ulCurHisgrmTotal;
extern xdata USHRT usCurHisgrm[BF_IG_PARTITIONS];
extern xdata USHRT usPrvHisgrm[BF_IG_PARTITIONS];

//******************************************************************************
// S T A T I C   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
static BOOL DCR_NewIGByHistogram(void);

//******************************************************************************
// E X T E R N A L   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
extern void WaitDisVSync(void);

//******************************************************************************
// F U N C T I O N   B O D Y S
//******************************************************************************

/**************************************************************************//**
 * According to the present histogram, calculate new i-gamma.
 * This function also detect the scene is changed or not.
 * @return TRUE if scene changed else FALSE.
 ******************************************************************************/
static BOOL DCR_NewIGByHistogram(void)
{
    BOOL pure;
    UCHAR i;

    if (usLowerBond == 0) {
        // Reset minimum default value of each IG point
        DCR_SetDynACEPnts(NULL);
    }

    if (DCR_IsSceneChanged()) {
        DCR_UpdatePrevHistogram();
        pure = FALSE;
        for (i = 0; i < BF_IG_PARTITIONS; i++) {
            //usNewIG[i] = ((ULONG)OVERALL-usLowerBond)*
            //            usCurHisgrm[i]/ulCurHisgrmTotal+
            //            ucMinIGTable[i];
            usNewIG[i] = ((ULONG)OVERALL-usLowerBond)*
                         usCurHisgrm[i]/ulCurHisgrmTotal;

            // Detect full-screen pure color by histogram.
            // ((OVERALL-usLowerBond)*0.8) is around 160.
            if (usNewIG[i] > 160) {
                pure = TRUE;
                break;
            }

            usNewIG[i] += ucMinIGTable[i];

            if (i == 0) {
                continue;
            }
            usNewIG[i] += usNewIG[i-1];
        }

        // Reset IG to default if full-screen pure color is detected.
        if (pure) {
            for (i = 0; i < BF_IG_PARTITIONS; i++) {
                usNewIG[i] = ((USHRT)i+1)*(OVERALL/BF_IG_PARTITIONS);
            }
        }

        return TRUE;
    }
    
    return FALSE;
}

/**************************************************************************//**
 * Set type of ACE update.
 * Update type is
 *   ACE_SMOOTH : IG curve changed smoothly.
 *   ACE_ONE    : IG curve changed immediately.
 * @param type The type of ACE update.
 ******************************************************************************/
void DCR_SetDynACEType(ACEType type)
{
    ucACEMode = type;
}

/**************************************************************************//**
 * Set list of minimum weighting of each segment of i-gamma.
 * @param ptr Pointer to minimum weightings of each segment of i-gamma.
 ******************************************************************************/
void DCR_SetDynACEPnts(UCHAR * ptr)
{
    UCHAR i;

    usLowerBond = 0;
    if (ptr == NULL) {
        for (i = 0; i < BF_IG_PARTITIONS; i++) {
            ucMinIGTable[i] = ((OVERALL / BF_IG_PARTITIONS) * 9 + 5) / 10;
            usLowerBond += ucMinIGTable[i];
        }
    }
    else {
        for (i = 0; i < BF_IG_PARTITIONS; i++) {
            ucMinIGTable[i] = ptr[i];
            usLowerBond += ucMinIGTable[i];
        }
    }
}

/**************************************************************************//**
 * Periodic routine for dynamic i-gamma.
 * @param reset TRUE to reset the state of dynamic i-gamma else FALSE.
 ******************************************************************************/
void DCR_SetDymACE(UCHAR reset)
{
    UCHAR i, reg;
    USHRT tmp_cur, tmp_new;

    if (reset) {
        for (i = 0; i < BF_IG_PARTITIONS; i++) {
            usCurIG[i] = ((USHRT)i+1)*(OVERALL/BF_IG_PARTITIONS);
            usNewIG[i] = usCurIG[i];
        }
    }

    if (DCR_NewIGByHistogram() || reset || bUpdateIG) {
        bUpdateIG = FALSE;
        if (ucACEMode == ACE_SMOOTH) {
            for (i = 0; i < BF_IG_PARTITIONS; i++) {
                tmp_cur = usCurIG[i];
                tmp_new = usNewIG[i];
                if (tmp_cur > tmp_new) {
                    if ((tmp_cur-tmp_new) > 4)
                        usCurIG[i] -= 4;
                    else
                        usCurIG[i] = usNewIG[i];
                    bUpdateIG = TRUE;
                }
                else if (tmp_cur < tmp_new) {
                    if ((tmp_new-tmp_cur) > 4)
                        usCurIG[i] += 4;
                    else 
                        usCurIG[i] = usNewIG[i];
                    bUpdateIG = TRUE;
                }
            }
        }
        else {
            for (i = 0; i < BF_IG_PARTITIONS; i++) {
                usCurIG[i] = usNewIG[i];
            }            
        }
        
        reg = SC_ACE_FUNC_CTRL2 & 0x0F;
        if ((SC_BRIGHT_FRM_SEL&BIT0) == BIT0)
            reg |= 0x20;
        reg |= 0x50;
        SC_ACE_FUNC_CTRL2 = reg;
        
        // Write I-Gamma //
        SC_ACE_DATA_PORT = 0x00;
        SC_ACE_DATA_PORT = 0x00;
        for (i = 0; i < (BF_IG_PARTITIONS-1); i++) {
            SC_ACE_DATA_PORT = usCurIG[i] & 0xFF;
            SC_ACE_DATA_PORT = usCurIG[i] >> 8;
        }
        SC_ACE_DATA_PORT = 0x00;
        SC_ACE_DATA_PORT = 0x04;
        
        // Update I-Gamma
        SC_ACE_FUNC_CTRL2 = reg | 0x90;
        WaitDisVSync();
        BFAPI_EnableACEMode();
        SC_ACE_FUNC_CTRL2 &= ~BIT7;
    }
}
