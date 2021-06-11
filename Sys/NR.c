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
#include "Include.h"

#if ENABLE_NR_BYTIMING == ON

//******************************************************************************
// M A C R O   D E F I N I T I O N S
//******************************************************************************

//******************************************************************************
// S T A T I C   V A R I A B L E S
//******************************************************************************

//******************************************************************************
// G L O B A L   V A R I A B L E S
//******************************************************************************

//******************************************************************************
// S T A T I C   V A R I A B L E S
//******************************************************************************
static code NRTiming NRTimingList[] = {
    {
        0xFFFF,
        {
            ADC_BW_AUTO,
            ON,
            NR_MODE_1,
            NR_CFG_NR2_EN|NR_CFG_ROUND|NR_CFG_EDGE_DET|NR_CFG_NR_DITH_EN|NR_CFG_JC_EN|NR_CFG_GC_EN,
            0x04,
            0x03,
            0x02,
            0x03,
            0x01,
            0x0A,
            0x04
        },
        {
            DITH_TP_VRDM,
            0x00,
            0x00
        }
    }
};

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
 * Set the NR of the analog input timing (mode index).
 ******************************************************************************/
void SetNRByAnalogTiming(void)
{
    USHRT i, num;

    num = sizeof(NRTimingList)/sizeof(NRTiming);

    for (i = 0; i < num; i++) {
        if ((NRTimingList[i].usModeIndex == InputTiming.usModeIndex) ||
            (NRTimingList[i].usModeIndex == 0xFFFF)) {
            // Set ADC bandwidth & ground sampling
            SetADCBandWidth(NRTimingList[i].NR.ucADCBandwidth);
            EnableADCGndSampling(NRTimingList[i].NR.ucGndSampling);
            // Set ADC NR
            NRSetNRType(NRTimingList[i].NR.ucNRType, NRTimingList[i].NR.ucNRCfg);
            NRSetEdgeThr(NRTimingList[i].NR.ucNREdgeThr);
            NRSetNRThr(NRTimingList[i].NR.ucNRTh);
            NRSetJCLvl(NRTimingList[i].NR.ucJCLvl);
            NRSetNR2Thr(NRTimingList[i].NR.ucNR2Th);
            NRSetGCCfg(NRTimingList[i].NR.ucGCWin, NRTimingList[i].NR.ucGCPkThr, NRTimingList[i].NR.ucGCLpThr);

            // Set dithering type
				if(DT158 != 0x00)	//george_TRULY_TFT1280120
			{
					DithSetDitherMode(NRTimingList[i].Dither.ucDitherType, NRTimingList[i].Dither.ucMode_10, NRTimingList[i].Dither.ucMode_01);
			}

            break;
        }
    }
}

/**************************************************************************//**
 * Set the NR of the digital input timing (mode index).
 ******************************************************************************/
void SetNRByDigitalTiming(void)
{
    NRSetNRType(NR_MODE_OFF, 0x00);
    DithSetDitherMode(DITH_TP_VRDM, 0x00, 0x00);
}
#endif //ENABLE_NR_BYTIMING == ON
