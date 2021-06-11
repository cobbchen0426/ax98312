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

#if ENABLE_SCALER_3D == ON
//******************************************************************************
// M A C R O   D E F I N I T I O N S
//******************************************************************************
#define SetHDMI3DFlag() (ucScaler3DStatus |= BIT0)
#define IsHDMI3DFlag()  (ucScaler3DStatus & BIT0)
#define SetAMD3DFlag()  (ucScaler3DStatus |= BIT1)
#define IsAMD3DFlag()   (ucScaler3DStatus & BIT1)
#define Set2DTo3DFlag() (ucScaler3DStatus |= BIT2)
#define Is2DTo3DFlag()  (ucScaler3DStatus & BIT2)
#define Set2DToFSFlag() (ucScaler3DStatus |= BIT3)
#define Is2DToFSFlag()  (ucScaler3DStatus & BIT3)
#define SetSBSFlag()    (ucScaler3DStatus |= BIT4)
#define IsSBSFlag()     (ucScaler3DStatus & BIT4)
#define SetTBFlag()     (ucScaler3DStatus |= BIT5)
#define IsTBFlag()      (ucScaler3DStatus & BIT5)

#define Set3DTo2DFlag() (ucScaler3DStatus |= BIT7)
#define Clr3DTo2DFlag() (ucScaler3DStatus &= ~BIT7)
#define Is3DTo2DFlag()  (ucScaler3DStatus & BIT7)

#define ClrAll3DFlag() (ucScaler3DStatus &= 0x80)
#define Is3DFlag() (ucScaler3DStatus & 0x3F)

//******************************************************************************
// G L O B A L   V A R I A B L E S
//******************************************************************************

//******************************************************************************
// S T A T I C   V A R I A B L E S
//******************************************************************************
static xdata UCHAR ucHDMI3DFormat;
static xdata UCHAR ucScaler3DStatus;
static xdata UCHAR uc2DTo3DFlag = 0;
//******************************************************************************
// E X T E R N A L   V A R I A B L E   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// S T A T I C   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
static BOOL SC3DAPI_CheckHDMI3DInfoFrame(void);
static void SC3DAPI_ConfigFrameDown(UCHAR freq);
static void SC3DAPI_ConfigScaling(UCHAR hfactor, UCHAR vfactor, UCHAR ratio);
static void SC3DAPI_ConfigPreFRC(UCHAR hratio, UCHAR vratio);
static void SC3DAPI_ConfigPostFRC(void);
static void SC3DAPI_ConfigFIFO(void);
static void SC3DAPI_ConfigFRCLock(void);
static void SC3DAPI_AutoFrameDown(void);

//******************************************************************************
// E X T E R N A L   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
//******************************************************************************
// Prototype: 
//  void SC3DAPI_Init(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Initialize 3D register
// Notes:
//  None
//******************************************************************************
void SC3DAPI_Init(void)
{
    ClrAll3DFlag();
}

#if ENABLE_SHUTTER_3D == ON
//******************************************************************************
// Prototype: 
//  void SC3DAPI_InitSyncSignal(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Initialize IR registers
// Notes:
//  None
//******************************************************************************
void SC3DAPI_InitSyncSignal(void)
{
    UCHAR xdata *ptr;
    UCHAR i;
    code UCHAR init_table[] = {
      //0x26, 0x28, 0x33, 0x20, 0x40, 0x01, 0x00, 0x00, 0x00, 0x00, 0x28, 0x38, 0x26, 0x01, 0xFF, 0xFF,
        0x00, 0x00, 0x33, 0x20, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4A, 0x65, 0x26, 0x01, 0xFF, 0xFF,
        0xFF, 0x0F, 0x0F, 0xFF, 0xFF, 0x0F, 0xF0, 0x7F, 0xFF, 0x0F, 0xFF, 0x80, 0xFF, 0x00, 0x00, 0x00
    };

    ptr = SC_3D_SHUTTER_GLASS_CTRL;
    for (i = 0; i < sizeof(init_table); i++) {
        *ptr = init_table[i];
        ptr++;
    }
}

//******************************************************************************
// Prototype:
//  void SC3DAPI_SelSyncPort(SC3DSyncPort port)
// Parameters:
//  port : output port
// Return:
//  None
// Purpose:
//  Select 3D sync signal output port
// Notes:
//  None
//******************************************************************************
void SC3DAPI_SelSyncPort(SC3DSyncPort port)
{
    switch(port) {
        case SC3D_SYNC_VOUT :
            SC_3D_SHUTTER_GLASS_CTRL[0] |= BIT1;
            SC_MCU_IO_CTRL3 = (SC_MCU_IO_CTRL3 & 0xFC) | 0x01; // For V_OUT
            break;
        case SC3D_SYNC_LOUT :
            SC_3D_SHUTTER_GLASS_CTRL[0] |= BIT1;
            SC_MCU_IO_CTRL4 = (SC_MCU_IO_CTRL4 & 0x3F) | 0x40; // For L_OUT
            break;
        case SC3D_SYNC_ROUT :
            SC_3D_SHUTTER_GLASS_CTRL[0] |= BIT1;
            SC_MCU_IO_CTRL4 = (SC_MCU_IO_CTRL4 & 0xCF) | 0x10; // For R_OUT
            break;
        case SC3D_SYNC_IROUT :
            SC_3D_SHUTTER_GLASS_CTRL[0] |= BIT0;
            SC_MCU_IO_CTRL3 = (SC_MCU_IO_CTRL3 & 0xF3) | 0x04; // For IR_TX
            break;
        case SC3D_TVIR_OUT :
            SC_TVIR_ENABLE |= BIT1;
            SC_TVIR_POLARITY |= BIT1;
            SC_MCU_IO_CTRL4 = (SC_MCU_IO_CTRL4 & 0x3F) | 0x80; // For TVIR_OUT
            break;
    };
}

//******************************************************************************
// Prototype:
//  void SC3DAPI_SetSyncDuty(USHRT on, USHRT off)
// Parameters:
//  on :
//  off :
// Return:
//  None
// Purpose:
//
// Notes:
//  None
//******************************************************************************
void SC3DAPI_SetSyncDuty(USHRT on, USHRT off)
{
    SC_3D_SHUTTER_GLASS_CTRL[0x0A] = on;
    SC_3D_SHUTTER_GLASS_CTRL[0x0B] = off;
}

//******************************************************************************
// Prototype:
//  void SC3DAPI_SetTVIRDelay(USHRT vsync, UCHAR delay)
// Parameters:
//  vsync : the unit is VSync freq x 10
//  delay : The range is 0~100(0% ~ 100%)
// Return:
//  None
// Purpose:
//  Set TVIR delay
// Notes:
//  None
//******************************************************************************
void SC3DAPI_SetTVIRDelay(USHRT vsync, UCHAR delay)
{
    ULONG clk = GetCPUClcok();//REF_CLK * MCU_CLK_TIMES;

    clk = (clk * 10 / vsync);
    clk = clk * delay / 100;

    SC_TVIR_PORT1_DELAY_LO = (clk & 0xFF);
    SC_TVIR_PORT1_DELAY_MI = (clk >> 8) & 0xFF;
    SC_TVIR_PORT1_DELAY_HI = (clk >> 16) & 0xFF;
    SC_TVIR_PORT2_DELAY_LO = (clk & 0xFF);
    SC_TVIR_PORT2_DELAY_MI = (clk >> 8) & 0xFF;
    SC_TVIR_PORT2_DELAY_HI = (clk >> 16) & 0xFF;
    SC_TVIR_PORT3_DELAY_LO = (clk & 0xFF);
    SC_TVIR_PORT3_DELAY_MI = (clk >> 8) & 0xFF;
    SC_TVIR_PORT3_DELAY_HI = (clk >> 16) & 0xFF;
}

//******************************************************************************
// Prototype: 
//  void SC3DAPI_InvSyncLR(UCHAR inv)
// Parameters:
//  inv : invert or not
// Return:
//  None
// Purpose:
//  Invert 3D L/R output sync 
// Notes:
//  None
//******************************************************************************
void SC3DAPI_InvSyncLR(UCHAR inv)
{
    if (inv) {
        SC_3D_SHUTTER_GLASS_CTRL[0x08] |= BIT5;
    }
    else {
        SC_3D_SHUTTER_GLASS_CTRL[0x08] &= ~BIT5;
    }
}
#endif

//******************************************************************************
// Prototype:
//  void SC3DAPI_EnableAMDLRSync(UCHAR enable)
// Parameters:
//  enable : enable or not
// Return:
//  None
// Purpose:
//  Enable AMD 3D LR sync
// Notes:
//  None
//******************************************************************************
void SC3DAPI_EnableAMDLRSync(UCHAR enable)
{
    if (enable) {
        SC_3D_SHUTTER_GLASS_CTRL[0x1D] |= BIT7;
    }
    else {
        SC_3D_SHUTTER_GLASS_CTRL[0x1D] &= ~BIT7;
    }
}

//******************************************************************************
// Prototype:
//  UCHAR SC3DAPI_DetectAMD3D(void)
// Parameters:
//  None
// Return:
//  True or False
// Purpose:
//  Detect the current TMDS input is AMD 3D or not.
// Notes:
//  None
//******************************************************************************
UCHAR SC3DAPI_DetectAMD3D(void)
{
    #define AMD_DET_LOOP 4

    UCHAR i;
    
    if (!IsHDMI()) {
        SC3DAPI_EnableAMDLRSync(TRUE);
        SC3DAPI_GetAMD3DCtlStatus();

        for (i = 0; i < AMD_DET_LOOP; i++) {
            DelayVTime(3);
            if (!SC3DAPI_GetAMD3DCtlStatus()) {
                break;
            }
        }

        if (i == AMD_DET_LOOP) {
            return TRUE;
        }

        SC3DAPI_EnableAMDLRSync(FALSE);
    }
    return FALSE;
}

//******************************************************************************
// Prototype:
//  UCHAR SC3DAPI_GetAMD3DCtlStatus(void)
// Parameters:
//  None
// Return:
//  True or False
// Purpose:
//  Get the current control bit status of AMD 3D
// Notes:
//  None
//******************************************************************************
UCHAR SC3DAPI_GetAMD3DCtlStatus(void)
{
    if ((SC_HDMI_INT_STATE1[2] & BIT6) != 0x00) {
        SC_HDMI_INT_STATE1[2] = BIT6;
        return TRUE;
    }
    return FALSE;
}

#if 0
//******************************************************************************
// Prototype: 
//  static void SC3DAPI_ConfigFrameDown(UCHAR freq)
// Parameters:
//  freq : Target vsync frequency
// Return:
//  None
// Purpose:
//  Frame rate down convertion
// Notes:
//  None
//******************************************************************************
static void SC3DAPI_ConfigFrameDown(UCHAR freq)
{
    ULONG clock, tmp1, tmp2;
    USHRT lcnt, htotal, vtotal, vlock;
    float ratio;
    UCHAR i;

    lcnt = 1;
    for (i = 0; i < SC_HPLL_LINE_CNT; i++) {
        lcnt *= 2;
    }
    
    htotal = ReadShortScaler(&SC_HSDDS_DIVIDER_LO);
    clock = (ULONG)((float)lcnt * 192 * htotal / Read3ByteScaler(&SC_HS_CNT_RESULT_LO) * 1000000);

    tmp1 = (ULONG)4095 * freq;
    tmp2 = tmp1 / 2;
    
    htotal = 4095;
    vtotal = (clock + tmp2) / tmp1;
    
    if (vtotal < GetInputVTotal()) {
        vtotal = GetInputVTotal();

        tmp1 = (ULONG)vtotal * freq;
        tmp2 = tmp1 / 2;
        htotal = (clock + tmp2) / tmp1;
    }

    WriteShortScaler(&SC_PREFRC_OUTPUT_H_TOTAL_LO, htotal);
    WriteShortScaler(&SC_PREFRC_OUTPUT_V_TOTAL_LO, vtotal);
    WriteShortScaler(&SC_PREFRC_OUTPUT_H_ACTIVE_LO, ReadShortScaler(&SC_GI_CAP_HWID_LO));
    WriteShortScaler(&SC_PREFRC_OUTPUT_V_ACTIVE_LO, ReadShortScaler(&SC_GI_CAP_VLEN_LO));

#if 0
    SC_PREFRC_CONTROL = 0x01;
#else
    SC_PREFRC_CONTROL = 0x03;

    // H/V lower bound
    vlock = GetInputVTotal() - 2;
    SC_PREFRC_53A = ((vlock & 0x0F00) >> 4);
    SC_PREFRC_53B = vlock & 0xFF;
    SC_PREFRC_53C = 0x00;

    ratio = (float)freq * 10 / usVSyncFreq;
    ratio = (float)1 - ratio;

    // H/V upper bound
    vlock = (float)InputTiming.usModeVActive * ratio;
    SC_PREFRC_53D = ((vlock & 0x0F00) >> 4);
    SC_PREFRC_53E = vlock & 0xFF;
    SC_PREFRC_53F = 0x00;
#endif

    clock = Read3ByteScaler(&SC_DDDS_RATIO_LO);
    ratio = (float)freq * 11 * GetInputVTotal() / usVSyncFreq / vtotal;
    clock = (ULONG)((float)clock * ratio);
    Write3ByteScaler(&SC_DDDS_RATIO_LO, clock);
    Sleep(100);

    // Readback & set display htotal because of clock changed.
    htotal = ReadShortScalerHighLowFilter(&SC_DSP_HTOTAL_LO) & 0xFFFF;
    WriteShortScaler(&SC_DH_HTOTAL_LO, htotal);

}

//******************************************************************************
// Prototype:
//  static void SC3DAPI_AutoFrameDown(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Set frame down frequency by input v-sync frequency
// Notes:
//  None
//******************************************************************************
static void SC3DAPI_AutoFrameDown(void)
{
    if (usVSyncFreq > 620) {
        SC3DAPI_ConfigFrameDown(60);
    }
    else if (abs(usVSyncFreq - 560) < 10) {
        SC3DAPI_ConfigFrameDown(50);
    }
}

//******************************************************************************
// Prototype:
//  static void SC3DAPI_ConfigScaling(UCHAR hfactor, UCHAR vfactor, UCHAR ratio)
// Parameters:
//  hfactor :
//  vfactor :
//  ratio :
// Return:
//  None
// Purpose:
//  Config scaler clock
// Notes:
//  None
//******************************************************************************
static void SC3DAPI_ConfigScaling(UCHAR hfactor, UCHAR vfactor, UCHAR ratio)
{
    ULONG clock, tmpclk;
    USHRT i;
    USHRT dsthtotal;
    UCHAR check_fifo;

    check_fifo = FALSE;
    clock = Read3ByteScaler(&SC_DDDS_RATIO_LO);
    tmpclk = clock;
    clock = clock * ratio / 10;

    dsthtotal = ReadShortScalerHighLowFilter(&SC_DSP_HTOTAL_LO) & 0xFFFF; //2011-07-22 wasy: To prevent htotal * 2 >= 4095, or DDR counter would be fail

    // Input HTotal of FRC is limited and must be smaller than 4096.
    i = ((ULONG)dsthtotal * hfactor) >> 1;
    if (i > 4080) {
        clock = (ULONG) ((float) clock * 4080 / i);
    }

    if (clock != tmpclk) {
        check_fifo = TRUE;
    }

    if (hfactor != 2) { //must be after SetupDisplayTiming
        i = ReadShortScaler(&SC_DH_BG_WID_LO);
        WriteShortScaler(&SC_DH_BG_WID_LO, (i * hfactor) >> 1);
        i = ReadShortScaler(&SC_GRAPHIC_DISP_HOR_ACT_WID_LO);
        WriteShortScaler(&SC_GRAPHIC_DISP_HOR_ACT_WID_LO, (i * hfactor) >> 1);
        check_fifo = TRUE;
    }

    if (vfactor != 2) { //must be after SetupDisplayTiming
        i = ReadShortScaler(&SC_DV_BG_LEN_LO);
        WriteShortScaler(&SC_DV_BG_LEN_LO, (i * vfactor) >> 1);
        i = ReadShortScaler(&SC_GRAPHIC_DISP_VER_ACT_LEN_LO);
        WriteShortScaler(&SC_GRAPHIC_DISP_VER_ACT_LEN_LO, (i * vfactor) >> 1);
        check_fifo = TRUE;
    }

    if (check_fifo == TRUE) {
        Sleep(80);
        // If display clock or display active H/V are changed, we must set the display HTotal to
        // avoid the following code referring to the wrong value.
        dsthtotal = ReadShortScalerHighLowFilter(&SC_DSP_HTOTAL_LO) & 0xFFFF;
        WriteShortScaler(&SC_DH_HTOTAL_LO, dsthtotal);
        // If display clock/display active H/V are changed, we must set the scaler FIFO to
        // avoid FIFO underflow or overflow.
        CheckFIFO();
    }

    // HotFix for FP issue over Samsung's Master PG
    // Jude 2011/08/27
    if (((SC_HDMI_3D_FORMAT & 0x0F) == 0x0A) &&
        ((SC_HDMI_3D_FORMAT & 0xF0) == FRAME_PACKING) &&
        (IsInterlaced() == FALSE)) {
        SC_VCR_CTRL = 0x10;
        i = ReadShortScaler(&SC_GI_CAP_VBEGO_LO);
        SetVP(i+2);
        SC_DISPLAY_CTRL &= ~BIT6;
        SC_DISPLAY_VLOCK = 2;
        WriteShortScaler(&SC_DISPLAY_HLOCK_LO, 0);
    }
}

//******************************************************************************
// Prototype:
//  static void SC3DAPI_ConfigPreFRC(UCHAR hratio, UCHAR vratio)
// Parameters:
//  hratio :
//  vratio :
// Return:
//  None
// Purpose:
//  Config pre-frc clock
// Notes:
//  None
//******************************************************************************
static void SC3DAPI_ConfigPreFRC(UCHAR hratio, UCHAR vratio)
{
    USHRT htotal, vtotal;
    USHRT i;

    i = ReadShortScaler(&SC_GI_CAP_HWID_LO);
    i = i * hratio / 2;
    WriteShortScaler(&SC_PREFRC_OUTPUT_H_ACTIVE_LO, i);

    i = ReadShortScaler(&SC_GI_CAP_VLEN_LO);
    i = i * vratio / 2;
    WriteShortScaler(&SC_PREFRC_OUTPUT_V_ACTIVE_LO, i);

    SC_3D_FORMAT_CTRL |= BIT7; //pre_3d enable for pre-frc
    SC_PREFRC_CONTROL = 0x41;

    Sleep(85);//
    htotal = ReadShortScaler(&SC_PREFRC_OUTPUT_H_TOTAL_LO);

    vtotal = ReadShortScaler(&SC_PREFRC_OUTPUT_V_TOTAL_LO);
    vtotal = vtotal / 2;
    SC_PREFRC_CONTROL = 0x03; //set fifo manual mode to set correct  H/V Total
    WriteShortScaler(&SC_PREFRC_OUTPUT_H_TOTAL_LO, htotal);
    WriteShortScaler(&SC_PREFRC_OUTPUT_V_TOTAL_LO, vtotal);
    
    // Delay Here. Because display htotal will be unstable in a short minutes when turn on pre-FRC
    // Jude 2011/08/27
    Sleep(100);

    // Readback & set display htotal because of clock changed.
    htotal = ReadShortScalerHighLowFilter(&SC_DSP_HTOTAL_LO) & 0xFFFF;
    WriteShortScaler(&SC_DH_HTOTAL_LO, htotal);
}

//******************************************************************************
// Prototype:
//  static void SC3DAPI_ConfigPostFRC(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Config post-frc clock
// Notes:
//  None
//******************************************************************************
static void SC3DAPI_ConfigPostFRC(void)
{
#ifndef FRC_VBI_RATIO
#define FRC_VBI_RATIO 10 // This value must higher than 10
#endif

    UCHAR lock;
    USHRT htotal, vtotal, i, lcnt, vsync_x10;
    ULONG clock;
    float vsync;

    // Flag to turn on/off lock mode
    lock = TRUE;

    if ((SC_PREFRC_CONTROL & BIT0) != 0x00) {
        htotal = ReadShortScaler(&SC_HSDDS_DIVIDER_LO);
        lcnt = 1;
        for (i = 0; i < SC_HPLL_LINE_CNT; i++) {
            lcnt *= 2;
        }
        clock = (ULONG)((float)lcnt * 192 * htotal / Read3ByteScaler(&SC_HS_CNT_RESULT_LO) * 1000000);
        
        htotal = ReadShortScaler(&SC_PREFRC_OUTPUT_H_TOTAL_LO);
        vtotal = ReadShortScaler(&SC_PREFRC_OUTPUT_V_TOTAL_LO);
    
        vsync = (float)clock / htotal / vtotal;
        vsync_x10 = (USHRT)(vsync * 10);
    }
    else {
        vsync_x10 = usVSyncFreq;
    }

#if ENABLE_SHUTTER_3D == ON
    if ((abs(vsync_x10 - 250) < 5) ||
        (abs(vsync_x10 - 500) < 12) ||
        (abs(vsync_x10 - 1000) < 12)) {
        htotal = UserPanelData.usTypHTotal * 6 / 5;
        vtotal = UserPanelData.usTypVTotal;
    }
    else {
        htotal = UserPanelData.usTypHTotal;
        vtotal = UserPanelData.usTypVTotal;
    }
    vtotal = vtotal * FRC_VBI_RATIO / 10;
    clock = 297000000L;
    clock = clock * FRC_VBI_RATIO / 10;
    lock = FALSE;
#else
    htotal = UserPanelData.usTypHTotal; //ReadShortScaler(&SC_DSP_HTOTAL_LO) & 0xFFFE;
    vtotal = ReadShortScaler(&SC_DV_TOTAL_LO);

    if (vsync_x10 > 855) {
        clock = (float) htotal * vtotal * vsync_x10 / 20;
    }
    else if (vsync_x10 < 320) {
        clock = (float) htotal * vtotal * vsync_x10 / 5;
    }
    else {
        clock = (float) htotal * vtotal * vsync_x10 / 10;
    }

    if ((clock > UserPanelData.ulMaxPClk) ||
        (clock < UserPanelData.ulMinPClk)) {
        htotal = UserPanelData.usTypHTotal;
        vtotal = UserPanelData.usTypVTotal;
        clock = (ULONG)UserPanelData.usTypHTotal * UserPanelData.usTypVTotal * 60;
        lock = FALSE;
    }
#endif
    SetDisplayDCLK(clock);
    //Setup FRC H/V Total
    WriteShortScaler(&SC_FRC_OUTPUT_H_TOTAL_LO, htotal);
    WriteShortScaler(&SC_FRC_OUTPUT_V_TOTAL_LO, vtotal);
    //Setup FRC H/V Active
    i = UserPanelData.usWidth;
    WriteShortScaler(&SC_FRC_OUTPUT_H_ACTIVE_LO, i);
    i = UserPanelData.usHeight;
    WriteShortScaler(&SC_FRC_OUTPUT_V_ACTIVE_LO, i);

    //Setup FRC H/V front porch
    i = htotal - ReadShortScaler(&SC_FRC_OUTPUT_H_ACTIVE_LO) - ReadShortScaler(&SC_DH_BG_BEG_LO);
    SC_FRC_H_FRONT_PORCH_LSB = (UCHAR)i;
    SC_FRC_VH_FRONT_PORCH_MSB = (UCHAR)((i >> 8) & 0x000F);
    i = vtotal - ReadShortScaler(&SC_FRC_OUTPUT_V_ACTIVE_LO) - ReadShortScaler(&SC_DV_BG_BEG_LO);
    SC_FRC_V_FRONT_PORCH_LSB = (UCHAR)i;
    SC_FRC_VH_FRONT_PORCH_MSB |= (UCHAR)((i >> 4) & 0x00F0);

    Sleep(20);

    // We must turn on the FRC lock mode to avoid the "Frame Tier" issue when display is 3D or 2D interlace.
    if ((Is3DFlag() || IsInterlaced()) && (lock == TRUE)) {
        SC_FRC_CTRL = 0x53;
    }
    else {
        SC_FRC_CTRL = 0x13;

        vsync = (float)clock / htotal / vtotal;
        vsync *= 10;
        if (vsync < vsync_x10) {
            // Set FRC up/down
            SC_FRC_CTRL |= BIT5;
        }
    }

    SC_FRC_RESET = 0x01;
}

//******************************************************************************
// Prototype:
//  static void SC3DAPI_ConfigFIFO(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Config MMU FIFO
// Notes:
//  None
//******************************************************************************
static void SC3DAPI_ConfigFIFO(void)
{
    // When we turn on Pre-FRC, we must turn off OD to avoid the issue of insufficient DDR BW.
    if (((SC_PREFRC_CONTROL & BIT0) != 0x00) && ((SC_FRC_CTRL & BIT0) != 0x00)) {
        SC_OD_CONFIGURATION &= ~BIT0;
    }
    else {
        SC_OD_CONFIGURATION |= BIT0;
        SC_OD_BTC_CONFIGURATION = 0x70;
    }

    if ((SC_OD_CONFIGURATION & BIT0) != 0x00) {
        if ((SC_PREFRC_CONTROL & BIT0) != 0x00) {
            MMUConfigFIFO(MMU_FIFO_PRE_OD);
            MMUConfigFrameBufAddr(MMU_FRAME_ADDR_PRE_OD);
        }
        else {
            MMUConfigFIFO(MMU_FIFO_OD_POST);
            MMUConfigFrameBufAddr(MMU_FRAME_ADDR_OD_POST);
        }
    }
    else {
        MMUConfigFIFO(MMU_FIFO_PRE_POST);
        MMUConfigFrameBufAddr(MMU_FRAME_ADDR_PRE_POST);
    }
}

//******************************************************************************
// Prototype:
//  static void SC3DAPI_ConfigFRCLock(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Config FRC lock position
// Notes:
//  None
//******************************************************************************
static void SC3DAPI_ConfigFRCLock(void)
{
    USHRT hlock, vlock;
    
    if ((SC_FRC_CTRL & BIT6) != 0x00) {
        hlock = 0;
        vlock = ReadShortScaler(&SC_DV_BG_BEG_LO);
        vlock += ReadShortScaler(&SC_DV_BG_LEN_LO);

        if (IsTBFlag()) {
            vlock /= 2;
        }
    }
    else {
        hlock = 0x0FFF;
        vlock = 0x0FFF;
    }

    SC_FRC_H_POINT1_LO = (UCHAR)hlock;
    SC_FRC_POINT1_HI &= 0xF0;
    SC_FRC_POINT1_HI |= (UCHAR)((hlock >> 8) & 0x000F);

    SC_FRC_V_POINT1_LO = (UCHAR) vlock;
    SC_FRC_POINT1_HI &= 0x0F;
    SC_FRC_POINT1_HI |= (UCHAR)((vlock >> 4) & 0x00F0);
    SC_FRC_V_POINT2_LO = (UCHAR) vlock;
    SC_FRC_POINT2_HI &= 0x0F;
    SC_FRC_POINT2_HI |= (UCHAR)((vlock >> 4) & 0x00F0);
}
#endif

//******************************************************************************
// Prototype: 
//  void SC3DAPI_Setup3DMode(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Setup 3D mode display clk
// Notes:
//******************************************************************************
void SC3DAPI_Setup3DMode(void)
{
//    UCHAR type;

    ClrAll3DFlag();

    if (SC3DAPI_IsHDMI3DMode() == FALSE) { //If input is not HDMI 3D format, then exit directly
        if (SC3DAPI_DetectAMD3D()) {
//            type = (FRAME_PACKING>>4)&0x0F;
            SetAMD3DFlag();
        }
        else {
            // 2D Mode
//            type = 0x00;
        } 
    }
    else {
        switch (SC_HDMI_3D_FORMAT & 0xF0) { //Check 3D Format
            case FRAME_PACKING:
            case FIELD_ALTERNATIVE:
            case L_DEPT:
                break;
            case LINE_ALTERNATIVE:
                break;
            case SIDE_BY_SIDE_FULL:
            case SIDE_BY_SIDE_HALF:
                SetSBSFlag();
                break;
            case TOP_BOTTOM:
                SetTBFlag();
                break;
            default:
                break;
        }
//        type = SC_HDMI_3D_FORMAT>>4;
        SetHDMI3DFlag();
    }

//    SC3DAPI_ConfigScaling(scaling_vector[type][0], scaling_vector[type][1], scaling_vector[type][2]);
}

#if ENABLE_3D_CNV == ON
//******************************************************************************
// Prototype: 
//  void SC3DAPI_Set3DTo2D(UCHAR enable)
// Parameters:
//  enable : Enable or disable 3D to 2D function
// Return:
//  None
// Purpose:
//  Turn on/off 3D to 2D
// Notes:
//******************************************************************************
void SC3DAPI_Set3DTo2D(UCHAR enable)
{
    if (enable) {
        SC_3D_CNV_2D |= BIT1;
        Set3DTo2DFlag();
    }
    else {
        SC_3D_CNV_2D &= ~BIT1;
        Clr3DTo2DFlag();
    }
}
#endif

//******************************************************************************
// Prototype:
//  void SC3DAPI_TurnOff3DMode(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  off 3D mode display
// Notes:
//******************************************************************************
void SC3DAPI_TurnOff3DMode(void)
{
    LoadDefaultPanelData();

#if ENABLE_SHUTTER_3D == ON
    SC3DAPI_InvSyncLR(FALSE);
#endif
    SC3DAPI_EnableAMDLRSync(FALSE);

#if ENABLE_3D_CNV == ON
    SC3DAPI_Enable2DTo3D(FALSE);
#endif

    ClrAll3DFlag();
}

#if ENABLE_3D_CNV == ON
//******************************************************************************
// Prototype:
//  void SC3DAPI_Enable2DTo3D(UCHAR enable)
// Parameters:
//  enable : TRUE or FALSE to enable/disable 2D to 3D function
// Return:
//  None
// Purpose:
//  Enable/disable 2D to 3D function
// Notes:
//******************************************************************************
void SC3DAPI_Enable2DTo3D(UCHAR enable)
{
    code UCHAR uc2Dto3DTable[] = {
      //f00h,f01h,f02h,f03h,f04h,f05h,f06h,f07h,f08h,f09h,f0ah,f0bh,f0ch,f0dh,f0eh,f0fh,
        0x7f,0x00,0xaa,0x00,0x20,0x38,0xC0,0x34,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0xff,
    
      //f10h,f11h,f12h,f13h,f14h,f15h,f16h,f17h,f18h,f19h,f1ah,f1bh,f1ch,f1dh,f1eh,f1fh,
        0xff,0xff,0x54,0x14,0x80,0x00,0x80,0xf0,0x10,0x08,0x08,0x00,0x80,0xf8,0x10,0x08,

      //f20h,f21h,f22h,f23h,f24h,f25h,f26h,f27h,f28h,f29h,f2ah,f2bh,f2ch,f2dh,f2eh,f2fh,
        0x08,0x00,0x80,0xf8,0x10,0x08,0x08,0x00,0x80,0xf0,0x10,0x08,0x00,0x10,0x80,0xf0,
     
      //f30h,f31h,f32h,f33h,f34h,f35h,f36h,f37h,f38h,f39h,f3ah,f3bh,f3ch,f3dh,f3eh,f3fh,
        0x10,0x00,0x08,0x9f,0x00,0x04,0x06,0x00,0x01,0x00,0x00,0x00,0xf0,0x00,0x00,0xf0,

      //f40h,f41h,f42h,f43h,f44h,f45h,f46h,f47h,f48h,f49h,f4ah,f4bh,f4ch,f4dh,f4eh,f4fh,
        0x66,0x62,0x5a,0x4e,0x41,0x32,0x25,0x1a,0x11,0x00,0x00,0xf0,0x00,0x00,0x00,0xf0,

      //f50h,f51h,f52h,f53h,f54h,f55h,f56h,f57h,f58h,f59h,f5ah,f5bh,f5ch,f5dh,f5eh,f5fh,
        0x10,0x18,0x00,0x2e,0x45,0x70,0x48,0x3e,0x70,0x00,0x00,0x00,0x00,0xC0,0x01,0x21,

      //f60h,f61h,f62h,f63h,f64h,f65h,f66h,f67h,f68h,f69h,f6ah,f6bh,f6ch,f6dh,f6eh,f6fh,
        0x03,0x00,0xe6,0x54,0xd6,0xff,0x00,0x11,0xcf,0x00,0x00,0x32,0x18,0x06,0x0C,0x14,

      //f70h,f71h,f72h,f73h,f74h,f75h,f76h,f77h,f78h,f79h,f7ah,f7bh,f7ch,f7dh,f7eh,f7fh,
        0x38,0x37,0x35,0x33,0x30,0x2d,0x29,0x25,0x20,0x1c,0x18,0x14,0x11,0x0e,0x0b,0x08,

      //f80h,f81h,f82h,f83h,f84h,f85h,f86h,f87h,f88h,f89h,f8ah,f8bh,f8ch,f8dh,f8eh,f8fh,
        0x59,0x00,0x50,0x4e,0x4a,0x43,0x3b,0x32,0x28,0x20,0x18,0x11,0x0c,0x08,0x03,0x03,

      //f90h,f91h,f92h,f93h,f94h,f95h,f96h,f97h,f98h,f99h,f9ah,f9bh,f9ch,f9dh,f9eh,f9fh,
        0x02,0x01,0x00,0x00,0x40,0x40,0x20,0x00,0x00,0x40,0x40,0x20,0x34,0x2e,0x20,0x11,

      //fa0h,fa1h,fa2h,fa3h,fa4h,fa5h,fa6h,fa7h,fa8h,fa9h,faah,fabh,fach,fadh,faeh,fafh,
        0x07,0x44,0x37,0x1c,0x40,0x32,0x96,0x0f,0x10,0x04,0x00,0x40,0x0f,0x30,0x18,0xa0,

      //fb0h,fb1h,fb2h,fb3h,fb4h,fb5h,fb6h,fb7h,fb8h,fb9h,fbah,fbbh,fbch,fbdh,fbeh,fbfh,
        0x1f,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0xbf,0x00,0x4f,0x00,0x00,0x00,0x00,0x00,

      //fc0h,fc1h,fc2h,fc3h,fc4h,fc5h,fc6h,fc7h,fc8h,fc9h,fcah,fcbh,fcch,fcdh,fceh,fcfh,
        0xb6,0x7c,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x90,0xb9,0x02,0x30,

      //fd0h,fd1h,fd2h,fd3h,fd4h,fd5h,fd6h,fd7h,fd8h,fd9h,fdah,fdbh,fdch,fddh,fdeh,fdfh,
        0x9a,0x00,0x69,0x75,0x00,0xcc,0x7a,0x00,0x7c,0x38,0x00,0x08,0x00,0xd4,0x08,0xff,

      //fe0h,fe1h,fe2h,fe3h,fe4h,fe5h,fe6h,fe7h,fe8h,fe9h,feah,febh,fech,fedh,feeh,fefh,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

      //ff0h,ff1h,ff2h,ff3h,ff4h,ff5h,ff6h,ff7h,ff8h,ff9h,ffah,ffbh,ffch,ffdh,ffeh,fffh,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x56,0x0f,
    };

    USHRT i;
    UCHAR *p;
    
    if (enable) {
        SC_BIST_CTRL2 = 0x00;
        SC_SCALER_DE_EXT_2DTO3D = 0x10;
    #if ENABLE_SHUTTER_3D == ON //frame packing panel
        SC_MICRO_RETARDED_CTRL = 0x00;
    #else //retarder panel
        SC_MICRO_RETARDED_CTRL = 0xF4;
    #endif
    
        p = &SC_2Dto3D_ENABLE_CONTROL;
        for (i = 0; i < 256; i++) {
            *p = uc2Dto3DTable[i];
            p++;
            ResetWDTimer();
        }
    }
    else {
        SC_BIST_CTRL2 |= 0x02;
    }
}

xdata UCHAR volatile _2DT3D_REG_13 _at_ 0x8F13;
xdata UCHAR volatile _2DT3D_REG_14 _at_ 0x8F14;
xdata UCHAR volatile _2DT3D_REG_50 _at_ 0x8F50;
xdata UCHAR volatile _2DT3D_REG_51 _at_ 0x8F51;
xdata UCHAR volatile _2DT3D_REG_52 _at_ 0x8F52;
xdata UCHAR volatile _2DT3D_REG_53 _at_ 0x8F53;
xdata UCHAR volatile _2DT3D_REG_54 _at_ 0x8F54;
xdata UCHAR volatile _2DT3D_REG_55 _at_ 0x8F55;
xdata UCHAR volatile _2DT3D_REG_56 _at_ 0x8F56;
xdata UCHAR volatile _2DT3D_REG_57 _at_ 0x8F57;
xdata UCHAR volatile _2DT3D_REG_58 _at_ 0x8F58;
xdata UCHAR volatile _2DT3D_REG_6C _at_ 0x8F6C;
xdata UCHAR volatile _2DT3D_REG_6D _at_ 0x8F6D;
xdata UCHAR volatile _2DT3D_REG_6E _at_ 0x8F6E;
xdata UCHAR volatile _2DT3D_REG_6F _at_ 0x8F6F;
xdata UCHAR volatile _2DT3D_REG_C4 _at_ 0x8FC4;
xdata UCHAR volatile _2DT3D_REG_C5 _at_ 0x8FC5;
xdata UCHAR volatile _2DT3D_REG_C7 _at_ 0x8FC7;
xdata UCHAR volatile _2DT3D_REG_C8 _at_ 0x8FC8;
xdata UCHAR volatile _2DT3D_REG_CA _at_ 0x8FCA;
xdata UCHAR volatile _2DT3D_REG_CB _at_ 0x8FCB;
xdata UCHAR volatile _2DT3D_REG_DD _at_ 0x8FDD;
xdata UCHAR volatile _2DT3D_REG_DE _at_ 0x8FDE;
xdata UCHAR volatile _2DT3D_REG_04 _at_ 0x8F04;

xdata ULONG volatile glb_level;
xdata ULONG volatile glb_max_0;
xdata ULONG volatile glb_max_1;
xdata ULONG volatile glb_max;
xdata ULONG volatile glb_counter;
xdata ULONG volatile glb_reg_50;
xdata ULONG volatile glb_reg_51;
xdata ULONG volatile glb_reg_52;

//******************************************************************************
// Prototype:
//  void SC3DAPI_Set2DTo3DViewPoint(UCHAR vpoint)
// Parameters:
//  vpoint : value of view point. Range is 0 ~ 11
// Return:
//  None
// Purpose:
//  Set view point
// Notes:
//******************************************************************************
void SC3DAPI_Set2DTo3DViewPoint(UCHAR vpoint)
{
    glb_reg_52 = vpoint < 6 ? (5 - vpoint) * 5 + 64 : (vpoint - 5) * 5;
}

//******************************************************************************
// Prototype:
//  void SC3DAPI_Set2DTo3DDepthLvl(UCHAR dlvl)
// Parameters:
//  dlvl : value of depth level. Range is 0 ~ 10.
// Return:
//  None
// Purpose:
//  Set depth level
// Notes:
//******************************************************************************
void SC3DAPI_Set2DTo3DDepthLvl(UCHAR dlvl)
{
    glb_reg_50 = dlvl * 8/10;
    glb_reg_51 = dlvl * 4;
}

//******************************************************************************
// Prototype:
//  void SC3DAPI_Set2DTo3DBorder(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Config left/right border size
// Notes:
//******************************************************************************
void SC3DAPI_Set2DTo3DBorder(void)
{
#define MIN_BORDER 0x14

    _2DT3D_REG_53 = MIN_BORDER & 0xFF;
    _2DT3D_REG_54 = (UserPanelData.usWidth - MIN_BORDER) & 0xFF;
    _2DT3D_REG_55 = (((UserPanelData.usWidth - MIN_BORDER) >> 4) & 0xF0) | (MIN_BORDER >> 8);
    _2DT3D_REG_56 = MIN_BORDER & 0xFF;
    _2DT3D_REG_57 = (UserPanelData.usWidth - MIN_BORDER) & 0xFF;
    _2DT3D_REG_58 = (((UserPanelData.usWidth - MIN_BORDER) >> 4) & 0xF0) | (MIN_BORDER >> 8);
}

//******************************************************************************
// Prototype:
//  void SC3DAPI_Update2DTo3DGlobalCounter(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Update luma histogram
// Notes:
//******************************************************************************
void SC3DAPI_Update2DTo3DGlobalCounter(void)
{
    ULONG reg_DD, reg_DE, max, max_0, max_1;
    ULONG histogram;

    histogram = 0;

    for (glb_counter = 0; glb_counter < 16;glb_counter++) {
        _2DT3D_REG_04 = (_2DT3D_REG_04 & 0xF0) | (glb_counter >> 0); //change the luma bin
        reg_DD = _2DT3D_REG_DD;
        reg_DE = _2DT3D_REG_DE;
        max = (reg_DD >> 4) | (reg_DE << 4);
        histogram += max;
        if (max > max_0) {
            max_1 = max_0;
            max_0 = max;
        }
        else {
            if (max > max_1) {
                max_1 = max;
            }
        }
    }

    if ((max_0 * 100 / histogram) > 80) {
        uc2DTo3DFlag = 1;
    }
    else {
        uc2DTo3DFlag = 0;
    }

    glb_counter = 0;
    glb_max = max_0 + max_1;
    max_0 = 0;
    max_1 = 0;
}

//******************************************************************************
// Prototype:
//  void SC3DAPI_SetDym2Dto3DDepthLvl(UCHAR on)
// Parameters:
//  on : TRUE/FALSE to set/fix depth level
// Return:
//  None
// Purpose:
//  Set depth level dynamically
// Notes:
//******************************************************************************
void SC3DAPI_SetDym2Dto3DDepthLvl(UCHAR on)
{
#define MAX_TH        0x890
#define MIN_TH        0x690
#define TOTAL_TH      (MAX_TH - MIN_TH)
#define MIN_OFFSET_50 ((TOTAL_TH)/2)
#define MIN_OFFSET_51 ((TOTAL_TH)/2)

    ULONG ClassLevel, max;
    ULONG reg_C4, reg_C5, reg_C7, reg_C8, reg_CA, reg_CB, reg1, reg2, reg3;
    UCHAR Current_Reg_50,Current_Reg_51;
    UCHAR Target_Reg_50,Target_Reg_51;

    reg_C4 = _2DT3D_REG_C4;
    reg_C5 = _2DT3D_REG_C5;
    reg_C7 = _2DT3D_REG_C7;
    reg_C8 = _2DT3D_REG_C8;
    reg_CA = _2DT3D_REG_CA;
    reg_CB = _2DT3D_REG_CB;

    reg1 = (reg_C4 >> 4) + (reg_C5 << 4);
    reg2 = (reg_C7 >> 4) + (reg_C8 << 4);
    reg3 = (reg_CA >> 4) + (reg_CB << 4);
    Current_Reg_50 = _2DT3D_REG_50;
    Current_Reg_51 = _2DT3D_REG_51;
    ClassLevel = glb_level;
    max = glb_max;

    if ((max > MAX_TH)&&(uc2DTo3DFlag)) {
        ClassLevel = 2;
    }
    else if (((max < MAX_TH)&&(max > MIN_TH))||((!uc2DTo3DFlag)&&(max > MAX_TH))) {
        ClassLevel = 1;
    }
    else {
        ClassLevel = 0;
    }

    if ((0 < ClassLevel)) {
        if ((reg1 < 15) && (reg1 + 20 < reg3) && (reg2 + 20 < reg3)) {
            ClassLevel = 0;
        }
        if((abs(reg1 + reg3) < reg2)) {
            ClassLevel = 0;
        }
    }

    if (on == FALSE) {
        ClassLevel = 0;
    }

    if (0 == ClassLevel) {
        Target_Reg_50 = glb_reg_50;
        Target_Reg_51 = glb_reg_51;
    }
    else if (1 == ClassLevel) {
        if (max > MAX_TH) {
            Target_Reg_50 = glb_reg_50;
            Target_Reg_51 = glb_reg_51/2;
        }
        else {
            Target_Reg_50 = (glb_reg_50*((MAX_TH - glb_max)+MIN_OFFSET_50))/TOTAL_TH;
            Target_Reg_51 = (glb_reg_51*((MAX_TH - glb_max)+MIN_OFFSET_51))/TOTAL_TH;
        }
    }
    else if (2 == ClassLevel) {
        Target_Reg_50 = glb_reg_50/2;
        Target_Reg_51 = glb_reg_51/3;
    }

    //for depth smooth adjust
    if (Current_Reg_50 > Target_Reg_50) {
        Current_Reg_50--;
    }
    else if(Current_Reg_50 < Target_Reg_50) {
        Current_Reg_50++;
    }
    if(Current_Reg_51 > Target_Reg_51) {
        Current_Reg_51--;
    }
    else if(Current_Reg_51 < Target_Reg_51) {
        Current_Reg_51++;
    }

    _2DT3D_REG_50 = Current_Reg_50;
    _2DT3D_REG_51 = Current_Reg_51;
    _2DT3D_REG_52 = glb_reg_52;

    glb_level = ClassLevel;

}

//******************************************************************************
// Prototype:
//  void SC3DAPI_SwapLR(UCHAR swap)
// Parameters:
//  swap : swap or not
// Return:
//  None
// Purpose:
//  Swap L/R frame
// Notes:
//  None
//******************************************************************************
void SC3DAPI_SwapLR(UCHAR swap)
{
#if ENABLE_SHUTTER_3D == ON
    if (swap) {
    }
    else {
    }
#else
    if (swap) {
        SC_MICRO_RETARDED_CTRL &= ~BIT6;
    }
    else {
        SC_MICRO_RETARDED_CTRL |= BIT6;
    }
#endif
}
#endif

//******************************************************************************
// Prototype:
//  static BOOL SC3DAPI_CheckHDMI3DInfoFrame(void)
// Parameters:
//  None
// Return:
//  TRUE: HDMI 3D mode, FALSE: not HDMI 3D mode.
// Purpose:
//  Check HDMI 3D mode by info-frame
// Notes:
//******************************************************************************
static BOOL SC3DAPI_CheckHDMI3DInfoFrame(void)
{
    UCHAR tmpreg;

    tmpreg = SC_CP_PACKET_TYPE;

    if (SC_CP_PACKET_TYPE != 0x81) {
        SC_CP_PACKET_TYPE = 0x81;
        Sleep(50); // For 24Hz input, the VSync period is 41ms.
                   // We choose 50ms to make sure the delay meet all kinds of video timing.
    }
    if (SC_CTRL_PACKET[0] != 0x81) {
        SC_CP_PACKET_TYPE = tmpreg;
        return FALSE;
    }

    if ((SC_CTRL_PACKET[7] & 0xE0) != 0x40) {
        SC_CP_PACKET_TYPE = tmpreg;
        return FALSE;
    }

    SC_CP_PACKET_TYPE = tmpreg;
    return TRUE;
}

//******************************************************************************
// Prototype:
//  BOOL SC3DAPI_Check3DVSI(void)
// Parameters:
//  None
// Return:
//  TRUE: HDMI 3D mode, FALSE: not HDMI 3D mode.
// Purpose:
//  Check HDMI 3D mode by scaler VSI register
// Notes:
//******************************************************************************
BOOL SC3DAPI_CheckVSI3DStatus(void)
{
    // Check VSI header
    if (SC_VSI_PACKET[0] != 0x81) {
        return FALSE;
    }

    // Check 3D present or not
    if ((SC_VSI_PACKET[7] & 0xE0) != 0x40) {
        return FALSE;
    }

    // Check 3D format valid or not
    switch (SC_VSI_PACKET[8] & 0xF0) {
        case FRAME_PACKING:
        case FIELD_ALTERNATIVE:
#if ENABLE_3D_CNV_120Hz == OFF
        case LINE_ALTERNATIVE:
#endif
        case SIDE_BY_SIDE_FULL:
        case L_DEPT:
        case TOP_BOTTOM:
        case SIDE_BY_SIDE_HALF:
            return TRUE;
    }

    return FALSE;
}

//******************************************************************************
// Prototype: 
//  BOOL SC3DAPI_IsHDMI3DMode(void)
// Parameters:
//  None
// Return:
//  TRUE: HDMI 3D mode, FALSE: not HDMI 3D mode.
// Purpose:
//  Check HDMI 3D mode
// Notes:
//******************************************************************************
BOOL SC3DAPI_IsHDMI3DMode(void)
{
    if ((SC_HDMI_3D_FORMAT & 0x0F) != 0x0A) {
        return FALSE;
    }
    else {
        switch (SC_HDMI_3D_FORMAT & 0xF0) {
            case FRAME_PACKING:
            case FIELD_ALTERNATIVE:
#if ENABLE_3D_CNV_120Hz == OFF
            // When we support 120Hz 3D conversion, e.x. 2D to 3D/SBS/TB, the MMU setting is not proper for 3D line alternative timing.
            // Therefore, we do not support it while ENABLE_3D_CNV_120Hz is ON.
            case LINE_ALTERNATIVE:
#endif
            case SIDE_BY_SIDE_FULL:
            case L_DEPT:
            case TOP_BOTTOM:
            case SIDE_BY_SIDE_HALF:
                return TRUE;
        }
    }

    return FALSE;
}

//******************************************************************************
// Prototype: 
//  BOOL SC3DAPI_IsHDMI3DFmtChanged(void)
// Parameters:
//  None
// Return:
//  TRUE: 3D format changed, FALSE: No change.
// Purpose:
//  Check HDMI 3D format changed or not.
// Notes:
//******************************************************************************
BOOL SC3DAPI_IsHDMI3DFmtChanged(void)
{
    if ((SC_VSI_PACKET[8] & 0xF0) != ucHDMI3DFormat) {
        return TRUE;
    }

    return FALSE;
}
#if 0
//******************************************************************************
// Prototype:
//  UCHAR SC3DAPI_GetHDMI3DFormat(void)
// Parameters:
//  None
// Return:
//  HDMI 3D format
// Purpose:
//  Get HDMI 3D format
// Notes:
//******************************************************************************
UCHAR SC3DAPI_GetHDMI3DFormat(void)
{
    if ((SC_HDMI_3D_FORMAT & 0x0F) != 0x0A) {
        return 0xFF;
    }

    return (SC_HDMI_3D_FORMAT & 0xF0);
}
#endif
//******************************************************************************
// Prototype:
//  void Hdmi3DSetup(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Setup HDMI 3D mode
// Notes:
//******************************************************************************
void SC3DAPI_SetupHDMI3DMode(void)
{
    USHRT i, j, v_active, v_act_space;
#if 0
    USHRT tmp_vt, tmp_vde;
#endif
    UCHAR k;

    k = GetCurrInputInterface();
    ucHDMI3DFormat = 0xFF;

    if ((k != DIGITAL_INPUT0) && (k != DIGITAL_INPUT1)) {
        return;
    }

    // If input is HDMI 3D timing, we force scaler as pure DE mode
#if DVI_MODE == DVI_HVDE_MODE
    SC_GI_SYNC_CTRL |= BIT7;
#endif
    SC_GI_SYNC_CTRL &= ~(BIT3 | BIT2); //VSYNC: 00 = 11-bit. Overflow freq = 27.32Hz
    SC_HDMI_AUTO_CTRL |= BIT6;
    if (SC3DAPI_IsHDMI3DMode() == FALSE) {
        if (SC3DAPI_Is3DFormat() == FALSE) {
            return;
        }
    }
    else if (SC3DAPI_CheckHDMI3DInfoFrame() == FALSE) { // Double confirm the VSP info-frame to make sure the input is 3D or not.
        SC_HDMI_AUTO_CTRL &= ~BIT6;
        SC_HDMI_3D_FORMAT = 0x00;   // Clear manual 3D mode
        // Delay here to make sure the sync changed interrupt has been risen after
        // we disable scaler auto 3D mode.
        Sleep(50);
        return;
    }
    SC_GI_SYNC_CTRL |= BIT2; //VSYNC: 01 = 12-bit. Overflow freq = 13.66Hz
    ucHDMI3DFormat = SC_HDMI_3D_FORMAT & 0xF0;
    switch (ucHDMI3DFormat) { //Check 3D Format
        case FRAME_PACKING:
        case L_DEPT:
        #if DVI_MODE == DVI_HVDE_MODE
            // If input is HDMI 3D timing, we force scaler as pure DE mode
            SC_GI_SYNC_CTRL &= ~BIT7;
        #endif
#if 1
            i = GetDigInputVTotalImmediate();
            j = GetDigInputVActiveImmediate();

            v_act_space = i - j;
            if (((j - v_act_space) % 2) != 0) {
                v_act_space--;
            }

            //Setup FP progressive mode
            WriteShortScaler(&SC_HDMI_3D_DE_LENGTH_LO, (j - v_act_space) / 2);
            SC_HDMI_3D_ACTIVE_SPACE = v_act_space;

            //Setup FP interlaced mode
            SC_HDMI_3D_ACTIVE_SPACE2 = v_act_space;
            v_active = (j - (i - j) * 3) / 4;
            v_act_space = (j - v_active * 4 - v_act_space) / 2;
            SC_HDMI_3D_ACTIVE_SPACE1 = v_act_space;
            WriteShortScaler(&SC_HDMI_3D_RODD_ST_LSB, v_active);
            WriteShortScaler(&SC_HDMI_3D_LEVEN_ST_LSB, v_active * 2 + SC_HDMI_3D_ACTIVE_SPACE1);
            WriteShortScaler(&SC_HDMI_3D_REVEN_ST_LSB, v_active * 3 + SC_HDMI_3D_ACTIVE_SPACE1 + SC_HDMI_3D_ACTIVE_SPACE2);

            // Because VDE is changed, we need delay for more than one frame time to make sure
            // the sync processor already  update vsync frequency to avoid interrupt again.
            // Jude 2011/09/01
            Sleep(50); // 24Hz is 41ms around.
#else
            //Setup frame packing progressive mode
            k = 50;
            tmp_vt = GetDigInputVTotalImmediate();
            tmp_vde = GetDigInputVActiveImmediate();
            do {
                i = GetDigInputVTotalImmediate();
                j = GetDigInputVActiveImmediate();

                if ((tmp_vt != i) || (tmp_vde != j)) {
                    tmp_vt = i;
                    tmp_vde = j;
                    Sleep(5);
                }
                else if (j > i) {
                    Sleep(5);
                }
                else {
                    Sleep(1);
                }
                k--;
            } while (k != 0);
            
            k = 2;
            do {
                WriteShortScaler(&SC_HDMI_3D_DE_LENGTH_LO, j - i / 2);
                v_act_space = i - j;
                SC_HDMI_3D_ACTIVE_SPACE = v_act_space;
                //Setup frame packing interlaced mode
                SC_HDMI_3D_ACTIVE_SPACE2 = v_act_space;
                v_active = (j - (i - j) * 3) / 4;
                v_act_space = (j - v_active * 4 - v_act_space) / 2;
                SC_HDMI_3D_ACTIVE_SPACE1 = v_act_space;
                WriteShortScaler(&SC_HDMI_3D_RODD_ST_LSB, v_active);
                WriteShortScaler(&SC_HDMI_3D_LEVEN_ST_LSB, v_active * 2 + SC_HDMI_3D_ACTIVE_SPACE1);
                WriteShortScaler(&SC_HDMI_3D_REVEN_ST_LSB, v_active * 3 + SC_HDMI_3D_ACTIVE_SPACE1 + SC_HDMI_3D_ACTIVE_SPACE2);
                
                // Because VDE is changed, we need delay for more than one frame time to make sure 
                // the sync processor already  update vsync frequency to avoid interrupt again.
                // Jude 2011/09/01        
                Sleep(20);

                if ((i == GetDigInputVTotalImmediate()) &&
                    (j == GetDigInputVActiveImmediate())) {
                        break;
                }
                
                i = GetDigInputVTotalImmediate();
                j = GetDigInputVActiveImmediate();
                
                k--;
            } while (k != 0);
#endif

            break;

        case FIELD_ALTERNATIVE:
#if 1
            i = GetDigInputVTotalImmediate();
            j = GetDigInputVActiveImmediate();
            v_act_space = i - j;
            if (((j - v_act_space) % 2) != 0) {
                v_act_space--;
            }

            // Setup FA mode
            WriteShortScaler(&SC_HDMI_3D_DE_LENGTH_LO, (j - v_act_space) / 2);
            SC_HDMI_3D_ACTIVE_SPACE = v_act_space;

            // Because VDE is changed, we need delay for more than one frame time to make sure
            // the sync processor already  update vsync frequency to avoid interrupt again.
            // Jude 2011/09/01
            Sleep(50); // 24Hz is 41ms around.
#else
            k = 50;
            tmp_vt = GetDigInputVTotalImmediate();
            tmp_vde = GetDigInputVActiveImmediate();
            do {
                i = GetDigInputVTotalImmediate();
                j = GetDigInputVActiveImmediate();

                if ((tmp_vt != i) || (tmp_vde != j)) {
                    tmp_vt = i;
                    tmp_vde = j;
                    Sleep(5);
                }
                else if (j > i) {
                    Sleep(5);
                }
                else {
                    Sleep(1);
                }
                k--;
            } while (k != 0);
            
            k = 2;
            do {
                // 3d_vde = (vt - ((vt - vde) * 2 - 1)) / 2
                // 3d_vde = vde - (vt - 1) / 2
                WriteShortScaler(&SC_HDMI_3D_DE_LENGTH_LO, j - (i - 1) / 2);
                v_act_space = i - j - 1;
                SC_HDMI_3D_ACTIVE_SPACE = v_act_space;
                
                // Because VDE is changed, we need delay for more than one frame time to make sure 
                // the sync processor already  update vsync frequency to avoid interrupt again.
                // Jude 2011/09/01        
                Sleep(20);

                if ((i == GetDigInputVTotalImmediate()) &&
                    (j == GetDigInputVActiveImmediate())) {
                        break;
                }
                
                i = GetDigInputVTotalImmediate();
                j = GetDigInputVActiveImmediate();
                
                k--;
            } while (k != 0);            
#endif

            break;

        case LINE_ALTERNATIVE:
            break;

        case SIDE_BY_SIDE_FULL:
            break;

        case TOP_BOTTOM:
            break;

        case SIDE_BY_SIDE_HALF:
            break;

        default:
            break;
    }
}

//******************************************************************************
// Prototype: 
//  BOOL SC3DAPI_IsActiveSpaceChanged(void)
// Parameters:
//  None
// Return:
//  TRUE if active space is changed. Otherwise, FALSE.
// Purpose:
//  Check active space changed or not
// Notes:
//  None
//******************************************************************************
BOOL SC3DAPI_IsActiveSpaceChanged(void)
{
    USHRT i, j, v_act_space;

    if ( !SC3DAPI_IsHDMI3D()) { //2012.05.17 Jerry+ DP_input will modechange because 0x650 error, maybe FPGA issue?
        return FALSE;
    }

    i = GetDigInputVTotalImmediate();
    j = GetDigInputVActiveImmediate();
    v_act_space = i - j;

    switch (ucHDMI3DFormat) { //Check 3D Format
        case FRAME_PACKING:
        case L_DEPT:
        case FIELD_ALTERNATIVE:
            if (abs(SC_HDMI_3D_ACTIVE_SPACE - v_act_space) > 1) {
                return TRUE;
            }
            break;
    }

    return FALSE;
}

//******************************************************************************
// Prototype: 
//  BOOL SC3DAPI_IsHDMI3D(void)
// Parameters:
//  None
// Return:
//  True or False to indicate HDMI 3D present or not.
// Purpose:
//  Check HDMI 3D present or not.
// Notes:
//  None
//******************************************************************************
BOOL SC3DAPI_IsHDMI3D(void)
{
    return IsHDMI3DFlag() ? TRUE : FALSE;
}

#if ENABLE_3D_CNV == ON
//******************************************************************************
// Prototype: 
//  BOOL SC3DAPI_IsAMD3D(void)
// Parameters:
//  None
// Return:
//  True or False to indicate AMD 3D present or not.
// Purpose:
//  Check AMD 3D present or not.
// Notes:
//  None
//******************************************************************************
BOOL SC3DAPI_IsAMD3D(void)
{
    return IsAMD3DFlag() ? TRUE : FALSE;
}

//******************************************************************************
// Prototype: 
//  BOOL SC3DAPI_Is2DTo3D(void)
// Parameters:
//  None
// Return:
//  True or False to indicate 2D to 3D is on or not.
// Purpose:
//  Check 2D to 3D is on or not.
// Notes:
//  None
//******************************************************************************
BOOL SC3DAPI_Is2DTo3D(void)
{
    return Is2DTo3DFlag() ? TRUE : FALSE;
}

//******************************************************************************
// Prototype: 
//  BOOL SC3DAPI_Is2DToFS(void)
// Parameters:
//  None
// Return:
//  True or False to indicate 2D to FS is on or not.
// Purpose:
//  Check 2D to FS is on or not.
// Notes:
//  None
//******************************************************************************
//BOOL SC3DAPI_Is2DToFS(void)
//{
//    return Is2DToFSFlag() ? TRUE : FALSE;
//}

//******************************************************************************
// Prototype: 
//  BOOL SC3DAPI_IsSBS(void)
// Parameters:
//  None
// Return:
//  True or False to indidate SBS is on or not.
// Purpose:
//  Check SBS is on or not.
// Notes:
//  None
//******************************************************************************
//BOOL SC3DAPI_IsSBS(void)
//{
//    return IsSBSFlag() ? TRUE : FALSE;
//}

//******************************************************************************
// Prototype: 
//  BOOL SC3DAPI_IsTB(void)
// Parameters:
//  None
// Return:
//  True or False to indicate TB is on or not.
// Purpose:
//  Check TB is on or not.
// Notes:
//  None
//******************************************************************************
//BOOL SC3DAPI_IsTB(void)
//{
//    return IsTBFlag() ? TRUE : FALSE;
//}
#endif //ENABLE_3D_CNV

//******************************************************************************
// Prototype: 
//  BOOL SC3DAPI_IsDisplay3D(void)
// Parameters:
//  None
// Return:
//  True or False to indicate the scaler is under 3D mode or not.
// Purpose:
//  Check the scaler is under 3D mode or not.
// Notes:
//  None
//******************************************************************************
BOOL SC3DAPI_IsDisplay3D(void)
{
    return Is3DFlag() ? TRUE : FALSE;
}

//******************************************************************************
// Prototype: 
//  BOOL SC3DAPI_Is3DTo2D(void)
// Parameters:
//  None
// Return:
//  True or False to indicate 3D to 2 on or off
// Purpose:
//  Check 3D to 2D is on or off
// Notes:
//  None
//******************************************************************************
//BOOL SC3DAPI_Is3DTo2D(void)
//{
//    return Is3DTo2DFlag() ? TRUE : FALSE;
//}

//******************************************************************************
// Prototype: 
//  BOOL SC3DAPI_Is3DFormat(void)
// Parameters:
//  None
// Return:
//  True or False to indicate 3D timing format present or not
// Purpose:
//  Check the current input is 3D timing format or not
// Notes:
//  None
//******************************************************************************
BOOL SC3DAPI_Is3DFormat(void)
{
    USHRT vde;
    vde = GetDigInputVActiveImmediate();

    if ((abs(vde - 1470) < 2) ||
        (abs(vde - 2205) < 2)) {
#if ENABLE_DVI_DUAL_LINK == ON
        if (TMDS_IsDualLink()) {
            SC_INPUT_SELECT = (SC_INPUT_SELECT & 0xF3) | 0x04;
            SC_TMDS_LINK_CLK_SEL |= BIT0;
            SC_DVI_PLL_M = 0x20;
        }
#endif
        // 3D Manual Mode
        //SC_GI_SYNC_CTRL &= ~BIT7;
        SC_HDMI_AUTO_CTRL &= ~BIT6;
        SC_HDMI_3D_FORMAT = 0x0A;

        return TRUE;
    }

    return FALSE;
}

//******************************************************************************
// Prototype:
//  BOOL SC3DAPI_IsManualHDMI3D(void)
// Parameters:
//  None
// Return:
//  True or False to indicate manual HDMI 3D format present or not
// Purpose:
//  Check the current input is manual HDMI 3D timing or not
// Notes:
//  None
//******************************************************************************
BOOL SC3DAPI_IsManualHDMI3D(void)
{
    if (((SC_HDMI_AUTO_CTRL & BIT6) == 0x00) && SC3DAPI_IsHDMI3DMode()) {
        return TRUE;
    }
    return FALSE;
}
#endif //ENABLE_SCALER_3D == ON
