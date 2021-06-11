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

extern code ModeTableFormat ModeTable[];

//******************************************************************************
// S T A T I C   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
static UCHAR GetAverageInputVSyncWidth(void);
static void CopyModeTable(UCHAR index);
static UCHAR GetNextSimilarTiming(void);
static BOOL IsNonSupportMode(USHRT mode);
static UCHAR SearchModeIndex(USHRT mode);

//******************************************************************************
// E X T E R N A L   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// F U N C T I O N   B O D Y S
//******************************************************************************

/**************************************************************************//**
 * Search current timing in mode table and read back current timing information from NVRam.
 ******************************************************************************/
void ModeSearch(void)
{
    SetupInterlace();

#if ENABLE_HDMI == ON
    // For HDMI model, we must set 0x6B5 in SetColorSpace before reading
    // 0x03C/0x03D for pixel repetition timing.
    SetCSCColorSpace(CSC_HDMI_AUTO_CLR_SPACE);
#endif

    if (GetInputSyncMode() != DIG_SYNC) { //Analog Input
        BOOL found_in_mode_table;
        UCHAR i, j, k;
        UCHAR vsync_width;
        USHRT vtotal, vtotal_diff = 0xFFFF;
        ULONG weight, min_weight = 0xFFFFFFFF;
// printf("MS_VGA\n"); //g
        vsync_width = GetAverageInputVSyncWidth();
        found_in_mode_table = FALSE;

        for (i=0; ModeTable[i].usHSyncFreq != 0xFFFF; i++) {
            
            
            //If mode is not support, go to next mode.  
            //if (IsNonSupportMode(ModeTable[i].usModeIndex))          continue;	//CHIU DISABLE
            
            //Compare interlaced.
            if (IsInterlaced() != (ModeTable[i].usModeIndex & BIT0)) {
                continue;
            }
            //Record the mode with nearest VTotal
            if ((InputTiming.usVTotal>ModeTable[i].usModeVActive) && (abs(InputTiming.usVTotal-ModeTable[i].usVTotal)<vtotal_diff)) {
                vtotal_diff = abs(InputTiming.usVTotal-ModeTable[i].usVTotal);
                j = i;
            }
            //Compare HSync Frequency
            if (abs(InputTiming.usHSyncFreq-ModeTable[i].usHSyncFreq) > ModeTable[i].ucHSyncTolerance) {
                continue;
            }
            //Compare VSync Frequency
            if (abs(InputTiming.usVSyncFreq-ModeTable[i].usVSyncFreq) > ModeTable[i].ucVSyncTolerance) {
                continue;
            }
            //Compare HSync/VSync Polarity
            if ((GetInputSyncMode()==SEP_SYNC) && (InputTiming.ucHVPolarity&ModeTable[i].ucHVPolarity) == 0x00) {
                // Don't check sync polarity in composite/sog sync mode
                continue;
            }
            //Compare VTotal
            vtotal = InputTiming.usVTotal;
            if (IsInterlaced() == TRUE) {
                vtotal <<= 1;
            }
            if (vtotal <= ModeTable[i].usModeVActive) {
                // Input vtotal must be larger than input vactive
                continue;
            }

            found_in_mode_table = TRUE; //Found one timing that satisfies the constrain in mode table
            weight = abs(InputTiming.usHSyncFreq-ModeTable[i].usHSyncFreq) + abs(InputTiming.usVSyncFreq-ModeTable[i].usVSyncFreq);
            weight += abs(InputTiming.usVTotal-ModeTable[i].usVTotal) << 2;
            weight = weight * 100 + abs(vsync_width-ModeTable[i].ucVSyncWidth);

            if (weight < min_weight) {
                min_weight = weight; //Record the min weight and mode table index
                k = i;
            }
        }

        //Found current timing in ModeTable
        if (found_in_mode_table == TRUE) {
            CopyModeTable(k);
            if (NvramReadTimingData(&InputTiming) == FALSE) { //can not find current timing in Nvram
                NvramWriteTimingData(&InputTiming);
            }
        }
        else { //Can not find current timing in ModeTable (It's a new timing)
            CopyModeTable(j); //Copy the timing data from the mode with nearest VTotal
            InputTiming.usModeIndex = _NEW_MODE | (InputTiming.usModeIndex>>8);
            //Read current timing data from NVRAM. If the timing data doesn't exist, initialize the Nvram
            if (NvramReadTimingData(&InputTiming) == FALSE) {
                //Write the initialized nvram into Nvram
                NvramWriteTimingData(&InputTiming);
            }
        }
    }
    else { //Digital Input
        UCHAR i;
        USHRT vactive = GetDigInputVActive();
 
// printf("MS_DVI\n"); //g
        if (IsInterlaced()) {
            vactive = vactive * 2;
        }

        InputTiming.usModeHActive = GetDigInputHActive();
        InputTiming.usModeVActive = vactive;
        InputTiming.usCapHActive = InputTiming.usModeHActive;
        InputTiming.usCapVActive = InputTiming.usModeVActive;
        InputTiming.usHStart = 0;
        InputTiming.usVStart = 0x1E0;
        InputTiming.usHStart50 = InputTiming.usHStart;
        InputTiming.usVStart50 = InputTiming.usVStart;
        InputTiming.usModeIndex = _NEW_MODE;
        for (i = 0; ModeTable[i].usHSyncFreq != 0xFFFF; i++) {
            if ((abs(InputTiming.usModeHActive - ModeTable[i].usCapHActive) <= 5) && // To distinguish 1360x768 & 1366x768
                (abs(InputTiming.usModeVActive - ModeTable[i].usCapVActive) <= 6) && // Force 720x486 to be recognized as 720x480
                (abs(InputTiming.usHSyncFreq - ModeTable[i].usHSyncFreq) < 10) &&
                (abs(InputTiming.usVSyncFreq - ModeTable[i].usVSyncFreq) < 10)) {
                InputTiming.usModeHActive = ModeTable[i].usModeHActive;
                InputTiming.usModeVActive = ModeTable[i].usModeVActive;
                InputTiming.usModeIndex = ModeTable[i].usModeIndex;
                break;
            }
        }
    }
}

/**************************************************************************//**
 * Get average input VSync width.
 * @return VSync width.
 ******************************************************************************/
static UCHAR GetAverageInputVSyncWidth(void)
{
    #define TOTAL_COUNT  20
    #define STABLE_COUNT 3

    USHRT sum_vsync_width;
    UCHAR tmp_vsync_width, prv_vsync_width;
    UCHAR counter;
    UCHAR stable_flag;
    UCHAR vsync_width_0, vsync_width_1;

    sum_vsync_width = 0;
    prv_vsync_width = GetInputVSyncWidth();

    stable_flag = TRUE;
    vsync_width_0 = 0xFF;
    vsync_width_1 = 0xFF;

    for (counter = 0; counter < TOTAL_COUNT; counter++) {

        tmp_vsync_width = GetInputVSyncWidth();

        if (tmp_vsync_width != prv_vsync_width) {
            stable_flag = FALSE; //VSW stable
        }

        if ((TRUE == stable_flag) && (counter > STABLE_COUNT)) {
            prv_vsync_width++;
            return prv_vsync_width;
        }

        if (0xFF == vsync_width_0) {
            vsync_width_0 = tmp_vsync_width;
        }
        else if (vsync_width_0 != tmp_vsync_width) {
            if (0xFF == vsync_width_1) {
                vsync_width_1 = tmp_vsync_width;
            }
            else if (vsync_width_1 != tmp_vsync_width) {
                prv_vsync_width = ((vsync_width_0 + vsync_width_1 + tmp_vsync_width) / 3) + 1;
                return prv_vsync_width;
            }
            else {
                //tmp_vsync_width equal to  vsync_width_1
            }
        }
        else {
            //tmp_vsync_width equal to  vsync_width_0
        }

        sum_vsync_width += tmp_vsync_width;
        DelayVTime(1);
    }

    prv_vsync_width = (sum_vsync_width + (counter / 2)) / counter;
    prv_vsync_width++;

    return prv_vsync_width;

    #undef TOTAL_COUNT
    #undef STABLE_COUNT
}

/**************************************************************************//**
 * Copy the timing information from NVRam to InputTiming.
 * @param index Timing index in mode table.
 ******************************************************************************/
static void CopyModeTable(UCHAR index)
{
//printf("VGA_CpModTab_i= %d\n", (USHRT) index);	//g
    InputTiming.usModeHActive = ModeTable[index].usModeHActive;
    InputTiming.usModeVActive = ModeTable[index].usModeVActive;
    InputTiming.usCapHActive = ModeTable[index].usCapHActive;
    InputTiming.usCapVActive = ModeTable[index].usCapVActive;
    InputTiming.usHTotal = ModeTable[index].usHTotal;
    InputTiming.usHStart = ModeTable[index].usHStart;
    InputTiming.usVStart = ModeTable[index].usVStart;
    InputTiming.usHTotal50 = ModeTable[index].usHTotal;
    InputTiming.usHStart50 = ModeTable[index].usHStart;
    InputTiming.usVStart50 = ModeTable[index].usVStart;
    InputTiming.ucPhase = 0x20;
    
#if VGA_GetMode_AutoTurn == OFF
	InputTiming.ucAutoTune = 1;	//for AXI request
#elif VGA_GetMode_AutoTurn == ON
	InputTiming.ucAutoTune = 0;	//Normal
#endif

    InputTiming.usModeIndex = ModeTable[index].usModeIndex;

    if (ModeTable[index].ucSampling != OFF) {
        InputTiming.usCapHActive = InputTiming.usCapHActive*ModeTable[index].ucSampling;
        InputTiming.usHTotal = InputTiming.usHTotal*ModeTable[index].ucSampling;
        InputTiming.usHStart = InputTiming.usHStart*ModeTable[index].ucSampling;
        InputTiming.usHTotal50 = InputTiming.usHTotal50*ModeTable[index].ucSampling;
        InputTiming.usHStart50 = InputTiming.usHStart50*ModeTable[index].ucSampling;
    }    
}

/**************************************************************************//**
 * Get the index of next similar timing in the mode table.
 * 0x00 ~ 0xFE: The index of next similar timing.
 * 0xFF: We can not find next similar timing in the mode table. There may be no similar timing or it's a new timing.
 * @return Timing index in the mode table.
 ******************************************************************************/
static UCHAR GetNextSimilarTiming(void)
{
    BOOL found=FALSE;
    UCHAR i;

    for (i=0; ModeTable[i].usHSyncFreq != 0xFFFF; i++) {
        //Find current input timing first
        if (InputTiming.usModeIndex == ModeTable[i].usModeIndex) {
            found = TRUE;
            break;
        }
    }

    if (found == TRUE) {
        for (i++; ; i++) {
            if (ModeTable[i].usHSyncFreq == 0xFFFF) { //End of the mode table
                i = 0;
            }
            if (InputTiming.usModeIndex == ModeTable[i].usModeIndex) {
                return 0xFF;
            }
            else if ((InputTiming.usModeIndex>>8) == (ModeTable[i].usModeIndex>>8)) {
                return i;
            }
        }
    }
    else {
        return 0xFF;
    }
}

/**************************************************************************//**
 * Switch to next similar timing in the mode table.
 ******************************************************************************/
void SimilarTimingSwitch(void)
{
    UCHAR next_similar_timing;

    if (GetInputSyncMode() == DIG_SYNC) { 
        return;
    }

    next_similar_timing = GetNextSimilarTiming();
    if (next_similar_timing == 0xFF) {
        return;
    }
    else {
        CopyModeTable(next_similar_timing);
        NvramWriteTimingData(&InputTiming);
        SetInputInterface(GetCurrInputInterface());
    }
}

/**************************************************************************//**
 * Check the system can support the present timing or not.
 * @param mode Mode index.
 ******************************************************************************/
static BOOL IsNonSupportMode(USHRT mode)
{
    #define NUM_NONSPPRT_MODE (sizeof(NonSupportModeList)/sizeof(NonSupportMode))

    code NonSupportMode NonSupportModeList[] = {
        RES_1024X768_NONSUPPORT_LIST,
        RES_1280X1024_NONSUPPORT_LIST,
        RES_1366X768_NONSUPPORT_LIST,
        RES_1400X1050_NONSUPPORT_LIST,
        RES_1440X900_NONSUPPORT_LIST,
        RES_1600X900_NONSUPPORT_LIST,
        RES_1680X1050_NONSUPPORT_LIST,
        RES_1920X1080_NONSUPPORT_LIST,
        RES_1920X1200_NONSUPPORT_LIST
    };

    UCHAR i;

    for (i = 0; i < NUM_NONSPPRT_MODE; i++) {
        if (PANEL_RESOLUTION == NonSupportModeList[i].ucResolution) {
            if (mode == NonSupportModeList[i].usNonSupportMode) {
                return TRUE;
            }
        }
    }

    return FALSE;

    #undef NUM_NONSPPRT_MODE
}

#if 0
/**************************************************************************//**
 * Search the timing index in the mode table with a given mode index.
 * @mode Mode index.
 ******************************************************************************/
static UCHAR SearchModeIndex(USHRT mode)
{
    UCHAR i;
    for (i = 0; ModeTable[i].usHSyncFreq != 0xFFFF; i++) {
        if (mode == ModeTable[i].usModeIndex) {
            break;
        }
    }

    if (ModeTable[i].usHSyncFreq == 0xFFFF) {
        i = 0xFF;
    }

    return i;
}
#endif
