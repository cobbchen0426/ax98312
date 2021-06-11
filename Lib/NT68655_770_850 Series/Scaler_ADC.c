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
#include "ScalerProfile.h"

//******************************************************************************
// M A C R O   D E F I N I T I O N S
//******************************************************************************

//******************************************************************************
// G L O B A L   V A R I A B L E S
//******************************************************************************
/*!
 * Values for the counter of HSync frequency.
 * This value is from the HSync counter, of sync processor, multiplying by 8192.
 * Not from HPLL directly.
 */
xdata ULONG ulHFreqCounter;

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

//******************************************************************************
// F U N C T I O N   B O D Y S
//******************************************************************************

/**************************************************************************//**
 * Initialize ADC-related registers.
 ******************************************************************************/
void ADCInit(void)
{
    SC_ADC_TEST1 = SCREG_002_210M;
    SC_ADC_TEST2 = SCREG_005_210M;
    SC_ADC_OP_CURRENT = SCREG_1F1_210M;
    SC_ADC_TEST2_CTRL = SCREG_1F3;
    SC_ADC_REG_1D = SCREG_1EA;
    SC_ADC_COMP_CTRL = SCREG_1EB;
    SC_ADC_BAND_GAP = SCREG_1ED_INIT;
    SC_ADC_CTRL_OPTION1 = 0x30;
    SC_ADC_CTRL_OPTION2 = 0x04;
    SC_ADC_CTRL_OPTION3 = 0x90;
//#if (ENABLE_INTERNAL_LDO == ON) || (ENABLE_INTERNAL_ADC_LDO == ON)
//    SC_GI_CLK_MASK_WID = SCREB_039_INT_LDO;
//    SC_ADC_LDO = SCREB_B63_INT_LDO;
//#else
    SC_GI_CLK_MASK_WID = SCREB_039_EXT_LDO;
    SC_ADC_LDO = SCREB_B63_EXT_LDO;
//#endif

    VGA_PowerOn();

    SC_ADC_BW_CTRL = 0x07;
    SC_CLAMP_BEGIN = 0x0C;
    SC_CLAMP_WIDTH = 0x81;
    SC_SOG_CLAMPING_CTRL = SCREG_011;
    SC_SOG_GLITCH_MASK_LO = 0x55;
    SC_SOG_DIGITAL_FILTER_CTRL = 0x00;
    SC_SOG_SLICER_CTRL = 0x00;

    SC_HPLL_CTRL1 = SCREG_0D0;
    SC_HPLL_CTRL2 = 0xC0;
    SC_HPLL_CTRL3 = 0x00;
    SC_HPLL_PHASE_CTRL = 0x38;
#if IS_NT68850_SERIES || IS_NT68790_SERIES
    SC_HPLL_PHASE_CTRL1 = 0x00;
    SC_HPLL_PHASE_CTRL2 = 0x04;
    SC_HPLL_PHASE_CTRL1 = 0x40;
    SC_HPLL_PHASE_CTRL2 = 0x04;
    SC_HPLL_PHASE_CTRL1 = 0x80;
    SC_HPLL_PHASE_CTRL2 = 0x04;
#else
    SC_HPLL_PHASE_CTRL1 = 0x00;
    SC_HPLL_PHASE_CTRL2 = 0x00;
    SC_HPLL_PHASE_CTRL1 = 0x40;
    SC_HPLL_PHASE_CTRL2 = 0x00;
    SC_HPLL_PHASE_CTRL1 = 0x80;
    SC_HPLL_PHASE_CTRL2 = 0x00;
#endif
    SC_HPLL_FREQ_CTRL = SCREG_0D1;

    SchmittTriggerPowerOn();
    SetADCInput(ADC_INPUT_EXT_RGB);
}

/**************************************************************************//**
 * Get the input htotal of analog input.
 * @return Input htotal of analog input.
 ******************************************************************************/
USHRT GetAngInputHTotal(void)
{
    return ReadShortScaler(&SC_HSDDS_DIVIDER_LO);
}

/**************************************************************************//**
 * Get the ADCPLL phase setting.
 * @return ADCPLL phase setting.
 ******************************************************************************/
UCHAR GetAngInputPhase(void)
{
    return SC_HPLL_PHASE_CTRL1;
}

/**************************************************************************//**
 * Set ADC bandwidth.
 * @param bw ADC bandwidth. If bw is ADC_BW_AUTO, the bandwidth is auto-configured.
 ******************************************************************************/
void SetADCBandWidth(ADCBandW bw)
{
    ULONG pix_clk;

    if (bw == ADC_BW_AUTO) {
        /*
        Analog bandwidth select ( RGB input capacitor select )
        111 : 500 MHz
        110 : 450 MHz
        101 : 400 MHz
        100 : 350 MHz
        011 : 300 MHz
        010 : 250 MHz
        001 : 150 MHz
        000 : 75  MHz
        */
    
        pix_clk = ReadShortScaler(&SC_HSDDS_DIVIDER_LO);
        pix_clk = pix_clk * usHSyncFreq;
    
        if (pix_clk < 370000) {// < 800x600/60Hz
            bw = ADC_BW_75MHz;
        }
        else if (pix_clk < 550000) { // < 1024x760/60Hz
            bw = ADC_BW_150MHz;
        }
        else if (pix_clk < 800000) {// < 1152x8
            bw = ADC_BW_250MHz;
        }
        else if (pix_clk < 900000) {
            bw = ADC_BW_300MHz;
        }
        else if (pix_clk < 1100000) {
            bw = ADC_BW_350MHz;
        }
        else if (pix_clk < 1400000) {
            bw = ADC_BW_400MHz;
        }
        else if (pix_clk < 1800000) {
            bw = ADC_BW_450MHz;
        }
        else {
            bw = ADC_BW_500MHz;
        }
    }
    
    SC_ADC_BW_CTRL &= 0xF8;
    SC_ADC_BW_CTRL |= (bw & 0x07);

#if IS_NT68150_SERIES// internal LDO only
    if (pix_clk > 1500000) {//148.5
        SC_ADC_TEST1 = 0x05;
        SC_ADC_TEST2 = SCREG_005_210M;
        SC_ADC_CTRL2 = (~SCREG_005_210M & 0x0C) >> 2;//Reg0x01E[1,0]=!Reg0x005[3,2]
        SC_ADC_OP_CURRENT = 0x3C;
        SC_ADC_COMP_CTRL = 0x02;
        SC_ADC_BAND_GAP = SCREG_1ED;
        SC_ADC_CTRL_OPTION1 = 0x30;
        SC_ADC_CTRL_OPTION2 = 0x04;
        SC_ADC_CTRL_OPTION3 = 0x90;
        SC_GI_CLK_MASK_WID = SCREB_039_INT_LDO;
        SC_ADC_LDO = 0x04;
    }
    else {
        SC_ADC_TEST1 = SCREG_002_210M;
        SC_ADC_TEST2 = SCREG_005_210M;
        SC_ADC_CTRL2 = (~SCREG_005_210M & 0x0C) >> 2;//Reg0x01E[1,0]=!Reg0x005[3,2]
        SC_ADC_OP_CURRENT = SCREG_1F1_210M;
        SC_ADC_COMP_CTRL = SCREG_1EB;
        SC_ADC_BAND_GAP = SCREG_1ED;
        SC_ADC_CTRL_OPTION1 = 0x00;
        SC_ADC_CTRL_OPTION2 = 0x34;
        SC_ADC_CTRL_OPTION3 = 0x90;
        SC_GI_CLK_MASK_WID = SCREB_039_INT_LDO;
        SC_ADC_LDO = SCREB_B63_INT_LDO;
    }
#endif
}

/**************************************************************************//**
 * Configure ADCPLL (capture clock).
 * @param htotal Htotal of analog input.
 ******************************************************************************/
void SetADCPLL(USHRT htotal)
{
#define HSYNC_BAND_LOW  ((float)REF_CLK/12000000*250)
#define HSYNC_BAND_MID  ((float)REF_CLK/12000000*500)

    ULONG pixel_rate;

    if (usHSyncFreq < HSYNC_BAND_LOW) {
        SC_HPLL_LINE_CNT = 0x0A; //1024 Lines
    }
    else if (usHSyncFreq < HSYNC_BAND_MID) {
        SC_HPLL_LINE_CNT = 0x0B; //2048 Lines
    }
    else {
        SC_HPLL_LINE_CNT = 0x0C; //4096 Lines
    }
    SC_HPLL_FREQ_CTRL &= ~BIT6; //Enable updating HS_CNT
    pixel_rate = ReadShortScaler(&SC_GI_HCNT_LO) & 0x1FFF;
    if ((pixel_rate == 0x1FFF) || (pixel_rate == 0)) {
        ulHFreqCounter = 0xFFFFFFFF;
    }
    else {
        ulHFreqCounter = (ULONG)pixel_rate * 8192;
    }
    WriteShortScaler(&SC_HSDDS_DIVIDER_LO, htotal);

    pixel_rate = htotal;
    pixel_rate = pixel_rate * usHSyncFreq;

#undef HSYNC_BAND_LOW
#undef HSYNC_BAND_MID
}

/**************************************************************************//**
 * Set ADCPLL phase.
 * @param phase ADCPLL phase.
 ******************************************************************************/
void SetADCPhase(UCHAR phase)
{
    SC_HPLL_PHASE_CTRL1 = phase;
    ucADCPhase100 = ((USHRT)phase * 100 + (MAXIMUM_PHASE>>1)) / MAXIMUM_PHASE;
}

/**************************************************************************//**
 * Wait until HPLL stable.
 * The maximum waiting time is 300ms.
 * The minimum waiting time is 30ms.
 * This function can not be performed prior to SetADCPLL.
 ******************************************************************************/
void WaitHPLLstable(void)
{
    ULONG hcounter;
    USHRT localtimer;

    localtimer = GetTimerTick();
    do {
        hcounter = Read3ByteScaler(&SC_HS_CNT_RESULT_LO);
        if (SC_HPLL_LINE_CNT == 0x0A) {//1024 line
            hcounter <<= 2;
        }
        else if (SC_HPLL_LINE_CNT == 0x0B) {//2048 line
            hcounter <<= 1;
        }
        if (labs(hcounter - ulHFreqCounter ) < 8192) {
            if ((GetTimerTick()-localtimer) > 30) {//minimum 30ms
                break;
            }
        }
    } while ((GetTimerTick()-localtimer) < 300);//maximum 300ms
}

/**************************************************************************//**
 * Set the ADC gain of red channel.
 * @param gain Gain value.
 ******************************************************************************/
void SetADCRGain(UCHAR gain)
{
    SC_RGAIN_HI = gain;
}

/**************************************************************************//**
 * Set the ADC gain of green channel.
 * @param gain Gain value.
 ******************************************************************************/
void SetADCGGain(UCHAR gain)
{
    SC_GGAIN_HI = gain;
}

/**************************************************************************//**
 * Set the ADC gain of blue channel.
 * @param gain Gain value.
 ******************************************************************************/
void SetADCBGain(UCHAR gain)
{
    SC_BGAIN_HI = gain;
}

/**************************************************************************//**
 * Set the ADC offset of red channel.
 * @param offset Offset value.
 ******************************************************************************/
void SetADCROffset(UCHAR offset)
{
    SC_ROFFSET = offset;
}

/**************************************************************************//**
 * Set the ADC offset of green channel.
 * @param offset Offset value.
 ******************************************************************************/
void SetADCGOffset(UCHAR offset)
{
    SC_GOFFSET = offset;
}

/**************************************************************************//**
 * Set the ADC offset of blue channel.
 * @param offset Offset value.
 ******************************************************************************/
void SetADCBOffset(UCHAR offset)
{
    SC_BOFFSET = offset;
}

/**************************************************************************//**
 * Get the ADC gain of red channel.
 * @return Gain value.
 ******************************************************************************/
UCHAR GetADCRGain(void)
{
    return SC_RGAIN_HI;
}

/**************************************************************************//**
 * Get the ADC gain of green channel.
 * @return Gain value.
 ******************************************************************************/
UCHAR GetADCGGain(void)
{
    return SC_GGAIN_HI;
}

/**************************************************************************//**
 * Get the ADC gain of blue channel.
 * @return Gain value.
 ******************************************************************************/
UCHAR GetADCBGain(void)
{
    return SC_BGAIN_HI;
}

/**************************************************************************//**
 * Get the ADC offset of red channel.
 * @return Offset value.
 ******************************************************************************/
UCHAR GetADCROffset(void)
{
    return SC_ROFFSET;
}

/**************************************************************************//**
 * Get the ADC offset of green channel.
 * @return Offset value.
 ******************************************************************************/
UCHAR GetADCGOffset(void)
{
    return SC_GOFFSET;
}

/**************************************************************************//**
 * Get the ADC offset of blue channel.
 * @return Offset value.
 ******************************************************************************/
UCHAR GetADCBOffset(void)
{
    return SC_BOFFSET;
}

/**************************************************************************//**
 * Enable or disable ADC ground sampling.
 * @param enable TRUE to enable ADC ground sampling else FALSE.
 ******************************************************************************/
void EnableADCGndSampling(UCHAR enable)
{
    if (enable) {
        SC_ADC_CTRL &= ~BIT0;
    }
    else {
        SC_ADC_CTRL |= BIT0;
    }
}

/**************************************************************************//**
 * Turn on ADCPLL and ADC power.
 ******************************************************************************/
void VGA_PowerOn(void)
{
    SC_POWER_CTRL2 |= (BIT6 | BIT3);
    SC_ADC_POWER_UP = SCREG_00E_PU;
}

/**************************************************************************//**
 * Turn off ADCPLL and ADC power.
 ******************************************************************************/
void VGA_PowerOff(void)
{
    SC_POWER_CTRL2 &= ~(BIT6 | BIT3);
    SC_ADC_POWER_UP = SCREG_00E_PD;
}

/**************************************************************************//**
 * Check the ADC power is on or not.
 * @return TRUE if ADC power is on else FALSE.
 ******************************************************************************/
/* 
BOOL IsADCPowerOn(void)
{
    return ((SC_ADC_POWER_UP & 0x07) != 0x00);
}
*/

/**************************************************************************//**
 * Turn on HSync and VSync schmitt Trigger circuits.
 ******************************************************************************/
void SchmittTriggerPowerOn(void)
{
    SC_HS_TRIG_LEVEL = 0x37;
    SC_VS_TRIG_LEVEL = 0x37;
}

/**************************************************************************//**
 * Turn off HSync and VSync schmitt Trigger circuits.
 ******************************************************************************/
void SchmittTriggerPowerOff(void)
{
    SC_HS_TRIG_LEVEL = 0x88;
    SC_VS_TRIG_LEVEL = 0x88;
}

/**************************************************************************//**
 * Set ADC input source.
 * The input can be one of 
 *     ADC_INPUT_INT_GND,
 *     ADC_INPUT_RST_RGB,
 *     ADC_INPUT_INT_WHITE and 
 *     ADC_INPUT_EXT_RGB
 * @param input ADC input source.
 ******************************************************************************/
void SetADCInput(ADCInput input)
{
    if (input >= ADC_NUM_INPUT) {
        input = ADC_INPUT_EXT_RGB;
    }

    SC_ADC_INPUT_CTRL = (SC_ADC_INPUT_CTRL & 0xFC) | input;
}
