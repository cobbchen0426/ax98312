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

//******************************************************************************
// S T A T I C   V A R I A B L E S
//******************************************************************************
static xdata ULONG ulDisplayClk; /*!< Variable of display clock. */
static xdata UCHAR ucAspRatioMode = ASP_RATIO_FULL; /*!< Variable of aspect ratio mode. */
static xdata USHRT usDisRatio = 0; /*!< Variable of the ratio of H/V. */

//******************************************************************************
// E X T E R N A L   V A R I A B L E   P R O T O T Y P E S
//******************************************************************************
extern xdata ULONG ulHFreqCounter;

//******************************************************************************
// S T A T I C   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
static void SetDPLL(void);
static void CheckInterlacedSignalField(void);
static void SetFixHR2(void);
static void CheckFIFO(void);

//******************************************************************************
// E X T E R N A L   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// F U N C T I O N   B O D Y S
//******************************************************************************

/**************************************************************************//**
 * Initialize display-related registers.
 * Through this function, the scaler will be under free-run mode and output black screen.
 ******************************************************************************/
void DisplayInit(void)
{
    SC_FIFO_FLAG = 0x03;
    SC_FIFO_FLAG_EN = 0x00;
    EnableDPLL();

    SC_INTE_CTRL = 0x00;
    SC_BK_H_SHAP_CTRL |= BIT7;
    SC_DISP_DRIVE_CTRL = PANEL_PAD_DRIVE;
    SC_DISPLAY_POL_CTRL = (PANEL_DISP_DE_POL << 7) | (PANEL_DISP_HSYNC_POL << 5) | (PANEL_DISP_VSYNC_POL << 4);
    SC_DISPLAY_CLK_CTRL = 0x40;

    SC_DISPLAY_CHANNEL = BIT6;//(BIT5|BIT6);
#if (INPUT_INTERFACE&INPUT_DP)
    SC_DP_FAST_MUTE_CTRL = SCREG_B88;
#endif

    SC_DISP_SWAP = DT16A;

    SC_GRAPHIC_DISP_WIN_CTRL = 0x07;

    SC_HR_CTRL = 0x00;
    SC_RESIDUAL_DISP_HOR_SYNC_CTRL = 0x00;

    SC_FIFO_CTRL1 &= ~BIT6;
    SC_FIFO_CTRL1 |= BIT5;

    DisplayMuteImage();
    LoadDefaultPanelData();
    SetFreeRunClk();
    SetDclkSSC(UserPanelData.ucSpreadSpectrumCtrl);
    SC_DITHER_TP_GRAY_LVL_LO = 0x00;
    SC_DITHER_TP_GRAY_LVL_HI = 0x00;
}

/**************************************************************************//**
 * Turn off DPLL (display PLL).
 ******************************************************************************/
void DisableDPLL(void)
{
    UCHAR tmpReg0f0, tmpReg101, tmpReg065;
    
    tmpReg0f0 = SC_DPLL_CTRL1;
    tmpReg101 = SC_POWER_CTRL1;
    tmpReg065 = SC_GAMMA_CTRL;
    
    if ((tmpReg0f0 & BIT0) != 0) {
        // Do anything necessary here
        #if ENABLE_GAMMA
        SC_GAMMA_CTRL = 0x00;
        #endif    
        
        // Disable DPLL sequence
        SC_POWER_CTRL1 = tmpReg101 | BIT0;
        SC_DPLL_CTRL1 = tmpReg0f0 & ~BIT0;

        #if ENABLE_GAMMA
        SC_GAMMA_CTRL = tmpReg065;
        #endif    
    }
}

/**************************************************************************//**
 * Turn on DPLL (display PLL).
 ******************************************************************************/
void EnableDPLL(void)
{
    UCHAR tmpReg0f0, tmpReg101, tmpReg065;

    tmpReg0f0 = SC_DPLL_CTRL1;
    tmpReg101 = SC_POWER_CTRL1;
    tmpReg065 = SC_GAMMA_CTRL;

    if ((tmpReg0f0 & BIT0) == 0) {
        #if ENABLE_GAMMA
        SC_GAMMA_CTRL = 0x00;
        #endif    
        // Enable DPLL sequence
        SC_DPLL_CTRL1 = tmpReg0f0 | BIT0;
        SC_POWER_CTRL1 = tmpReg101 & ~BIT0;
        Sleep(5);

        // Do anything necessary here
        #if ENABLE_GAMMA
        SC_GAMMA_CTRL = tmpReg065;
        #endif    
    }    
}

/**************************************************************************//**
 * Turn on DCLK (display clock).
 ******************************************************************************/
void EnableDclk(void)
{
    SC_POWER_CTRL1 &= ~BIT0;
}

/**************************************************************************//**
 * Initialize display h/v parameters according to the panel spec.
 ******************************************************************************/
void LoadDefaultPanelData(void)
{
    UCHAR ch;
    ch = 0x61;

    if (UserPanelData.bBitShift == TRUE) 	    
	{
          ch |= BIT7;						
       }
    else 
	{
          ch &= ~BIT7;
       }
    if (UserPanelData.ucColorDepth == 8)  
	{ 	
        	ch &= ~BIT3;
    	}
    else 
	{
        	ch |= BIT3;
    	}
    if (UserPanelData.bDualPortLVDS == TRUE)  
	{
               ch &= ~BIT2;
       }
    else 
	{
        	ch |= BIT2;
    	}
    if (UserPanelData.bDEMode == TRUE) 	           
	{
        	ch |= BIT1;
    	}
    else
	{
        	ch &= ~BIT1;
    	}
    SC_DISPLAY_CTRL = ch;					  

    //Display VTotal
    WriteShortScaler(&SC_DV_TOTAL_LO, UserPanelData.usTypVTotal);
    //Display VSync Width
    SC_DV_VS_WID = (UCHAR) UserPanelData.usMinVSyncWidth;
    //Display Background Window Vertical Begin
    WriteShortScaler(&SC_DV_BG_BEG_LO, UserPanelData.usMinVSyncWidth + UserPanelData.usMinVSyncBackPorch);
    //Display Background Window Vertical Length
    WriteShortScaler(&SC_DV_BG_LEN_LO, UserPanelData.usHeight);
    //Display Active Window Vertical Begin
    WriteShortScaler(&SC_GRAPHIC_DISP_VER_ACT_BEG_LO, UserPanelData.usMinVSyncWidth + UserPanelData.usMinVSyncBackPorch);
    //Display Active Window Vertical Length
    WriteShortScaler(&SC_GRAPHIC_DISP_VER_ACT_LEN_LO, UserPanelData.usHeight);
    //Display HTotal
    WriteShortScaler(&SC_DH_HTOTAL_LO, UserPanelData.usTypHTotal);
    //Display HSync Width
    SC_DH_HS_WID = (UCHAR) UserPanelData.usMinHSyncWidth;
    //Display Background Window Horizontal Begin
    WriteShortScaler(&SC_DH_BG_BEG_LO, UserPanelData.usMinHSyncWidth + UserPanelData.usMinHSyncBackPorch);
    //Display Background Window Horizontal Width
    WriteShortScaler(&SC_DH_BG_WID_LO, UserPanelData.usWidth);
    //Display Active Window Horizontal Begin
    WriteShortScaler(&SC_GRAPHIC_DISP_HOR_ACT_BEG_LO, UserPanelData.usMinHSyncWidth + UserPanelData.usMinHSyncBackPorch);
    //Display Active Window Horizontal Width
    WriteShortScaler(&SC_GRAPHIC_DISP_HOR_ACT_WID_LO, UserPanelData.usWidth);
    //Free run htotal
    WriteShortScaler(&SC_FREE_RUN_HTOTAL_LO, PANEL_TYP_HTOTAL);
}

/**************************************************************************//**
 * Set free-run clock.
 * The clock is panel typical clock defined in panel spec.
 * This function set DCLK only and does not turn the scaler to free-run mode.
 ******************************************************************************/
void SetFreeRunClk(void)
{
    ulDisplayClk = (UserPanelData.ulFreeRunH_Freq * UserPanelData.usTypHTotal + 5) / 10;
    SetDPLL();
}

/**************************************************************************//**
 * Setup DPLL by ulDisplayClk.
 ******************************************************************************/
static void SetDPLL(void)
{
    ULONG temp;
    SC_VPLL_CTRL |= BIT3;
    temp = ((float)ulDisplayClk * 131072) / REF_CLK;

    SC_DDDS_RATIO_LO = (UCHAR) temp;
    SC_DDDS_RATIO_MI = (UCHAR) (temp >> 8);
	
    SC_DDDS_RATIO_HI = (UCHAR) (temp >> 16);
	
    SC_VPLL_CTRL &= ~BIT3;
    SetLvdsP2SByDCLK();
}

#if ENABLE_LD == ON
/**************************************************************************//**
 * Setup DPLL to the specified clock.
 * @param clk Display clock. The unit is Hz.
 ******************************************************************************/
void SetDisplayDCLK(ULONG clk)
{
    ulDisplayClk = clk;
    SetDPLL();
}
#endif

#if ENABLE_LD == ON || ENABLE_PREFRC == ON
/**************************************************************************//**
 * Get display clock.
 * @return Display clock.
 ******************************************************************************/
ULONG GetDisplayDCLK(void)
{
    return ulDisplayClk;
}
#endif


/**************************************************************************//**
 * display clock Compress.
 * @param input and display timing
 ******************************************************************************/
void DispClkCompress(tTIMING *input,tTIMING *disp)
{
#if ENABLE_PREFRC == ON || ENABLE_DFR == ON
    if (!((GetInputSyncMode() == DIG_SYNC)
#if ENABLE_PREFRC == ON        
         && (usVSyncFreq < FRC_NACT_MIN || usVSyncFreq > FRC_NACT_MAX)
#elif ENABLE_DFR == ON   
         &&(usVSyncFreq < 310)
#endif
       ))
#endif
    { 
       disp->htotal = (UserPanelData.usMinHTotal / 8) * 8 + 8;
       disp->active_height = (USHRT) (((float)disp->clock / 100 / disp->htotal) * input->active_height / usHSyncFreq + 0.5);
       disp->vtotal = ((((ULONG)input->vtotal * disp->active_height) << 4) / input->active_height + 8) >> 4;
       
       if (disp->vtotal < UserPanelData.usMinVTotal) {
           disp->active_height = (ULONG) UserPanelData.usMinVTotal * input->active_height / input->vtotal;
       }
       
       if (IsInterlaced()) {
           disp->active_height >>= 1;
       }
      
       ulDisplayClk = disp->clock;
    }
}

#if ENABLE_PREFRC == ON || ENABLE_DFR == ON 
/**************************************************************************//**
 * Setup FRC or DFR.
 * @param input and display timing
 ******************************************************************************/
void Check_PreFRC_DFR(ULONG *Dclk)
{
        if ((GetInputSyncMode() == DIG_SYNC) 
            && (IsInterlaced() == FALSE)
#if ENABLE_PREFRC == ON
            && (usVSyncFreq < FRC_NACT_MIN || usVSyncFreq > FRC_NACT_MAX)
#elif ENABLE_DFR == ON   
            && (usVSyncFreq < 310)
#endif
#if ENABLE_SCALER_3D == ON
            && (SC3DAPI_IsHDMI3DMode() == FALSE)
#endif
         ){
            MMUConfig();
            
            WriteShortScaler(&SC_DV_BG_LEN_LO, UserPanelData.usHeight); //Display Background Vertical Length
            WriteShortScaler(&SC_GRAPHIC_DISP_VER_ACT_LEN_LO, UserPanelData.usHeight); //Display Active Vertical Length
            *Dclk = (ULONG)UserPanelData.usTypHTotal * UserPanelData.usTypVTotal * FRC_V_FREQ;
        }
        else {
            SC_FRC_CTRL = 0x00;
        }
}
#endif

/**************************************************************************//**
 * Setup the display timing.
 * The function includes:
 *  - Display clock calculation.
 *  - Panel timing limitation check.
 *  - In/out clock check.
 *  - Last line (fixed residue) calculation.
 * @param htotal50 Current input htotal value.
 ******************************************************************************/
BOOL SetupDisplayTiming(USHRT htotal50)
{
    USHRT i;
    xdata tTIMING input,disp;
    
    UCHAR Reg0x1ED;

    xdata float temp;
    BOOL interlace;
    
    Reg0x1ED = SC_ADC_BAND_GAP;
    SC_ADC_BAND_GAP |= BIT0;
	htotal50 = 0; // Disable compiler error.
    SC_DISPLAY_CTRL |= BIT5;					//150112 mike 0x150 	//fifo auto lock, auto usHTotal	
    SC_GRAPHIC_DISP_WIN_CTRL = 0x07;

    input.active_width = ReadShortScaler(&SC_GI_CAP_HWID_LO);
    input.active_height = ReadShortScaler(&SC_GI_CAP_VLEN_LO);
    if ((input.active_height > 1024) && (input.active_width < 1280))		 //Dual link
	{ 
       	 LoadDefaultPanelData();
        	SetFreeRunClk();
        	return FALSE;
    	  }

    input.vtotal = GetInputVTotal();

    if (IsInterlaced()) 
	{
       	 interlace = TRUE;
    	}
    else 
	{
        	interlace = FALSE;
    	}

    disp.active_height = UserPanelData.usHeight; //Set the vertical active height to the Panel Height

#if ENABLE_FIT_ALL_PANEL_SPEC == ON
    disp.vtotal = ((((ULONG)input.vtotal * disp.active_height) << 4) / input.active_height + 8) >> 4;
    if (disp.vtotal > UserPanelData.usMaxVTotal) {
        disp.vtotal = UserPanelData.usMaxVTotal;
        disp.active_height = ((((ULONG)disp.vtotal * input.active_height) << 4) / input.vtotal + 8) >> 4;
    }
#endif

#if ENABLE_SCALER_3D == ON
    for (disp.htotal = (UserPanelData.usMinHTotal / 8) * 8 + 8; disp.htotal < 4080; disp.htotal += 8) {
#else
    for (disp.htotal = (UserPanelData.usMinHTotal / 8) * 8 + 8; disp.htotal < UserPanelData.usMaxHTotal; disp.htotal += 8) {
#endif
        temp = ((float)disp.htotal-0.1) * disp.active_height * 4096 / ulHFreqCounter / input.active_height;
        ulDisplayClk = (ULONG) (temp * REF_CLK * 16);
        if (interlace == TRUE) {
            ulDisplayClk <<= 1;
        }
        if (ulDisplayClk > UserPanelData.ulMinPClk) {
            break;
        }
    }

    if (disp.htotal > UserPanelData.usMaxHTotal) { //Htotal too large, dclk too small
        disp.htotal -= 8;
    }

#if ENABLE_FIT_ALL_PANEL_SPEC == ON
    if ((ulDisplayClk > UserPanelData.ulMaxPClk) || (ulDisplayClk < UserPanelData.ulMinPClk))  {
        LoadDefaultPanelData();
        SetFreeRunClk();
        return FALSE;
    }
#endif

    if (ulDisplayClk > UserPanelData.ulMaxPClk) {
       disp.clock = UserPanelData.ulMaxPClk;
#if ENABLE_SCALER_3D == ON
       if (ulDisplayClk > 285000000) {
          disp.clock = 285000000;
    }
#endif
        DispClkCompress(&input,&disp);
    }

    WriteShortScaler(&SC_DV_BG_LEN_LO, disp.active_height); //Display Background Vertical Length
    WriteShortScaler(&SC_GRAPHIC_DISP_VER_ACT_LEN_LO, disp.active_height); //Display Active Vertical Length

//-----fefanjacky for 1850x1036-----------------------------------------------------------------------------------------
#if SPECIALAPP == ON
  WriteShortScaler(&SC_GRAPHIC_DISP_VER_ACT_LEN_LO, 0x40c); //Display Active Vertical Length
#else
  WriteShortScaler(&SC_GRAPHIC_DISP_VER_ACT_LEN_LO, disp.active_height); //Display Active Vertical Length
#endif
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
#ifdef AUO_G151EVN01_720
  WriteShortScaler(&SC_GRAPHIC_DISP_VER_ACT_LEN_LO, 0x2D0); //Display Active Vertical Length
#endif
//----------------------------------------------------------------------------------------------------------------------
    temp = ((float)disp.htotal-0.1) * disp.active_height * 4096 / ulHFreqCounter / input.active_height;
    ulDisplayClk = (ULONG) (temp * REF_CLK * 16);
    
#if ENABLE_PREFRC == ON || ENABLE_DFR == ON
    Check_PreFRC_DFR(&ulDisplayClk);
#endif

    if (interlace == TRUE) {
//        SC_VCR_CTRL = 0x10;
        ulDisplayClk <<= 1;
    }
//    else {
//#if ENABLE_SR == ON
//        SC_VCR_CTRL = 0x10;
//#else
//        SC_VCR_CTRL = 0x00;
//#endif
//    }

    SetDPLL();
#if (ENABLE_SCALER_3D == ON)
    if (SC3DAPI_IsHDMI3DMode() == TRUE) {
        DelayVTime(2);
    }
#endif
    Sleep(80);

    if (CheckModeChangeFlag() == FALSE) {
        if (interlace == TRUE) { //1080i
#if ENABLE_SCALER_3D == ON
            if (SC3DAPI_IsHDMI3DMode() == TRUE) {
                SC_GPORT_CTRL &= ~BIT2;
                DelayVTime(1);
                SC_GPORT_CTRL |= BIT2;
            }
#else
            i = SC_DISPLAY_CTRL;							//150112 mike 
            SC_DISPLAY_CTRL = (i & ~BIT5); 				//Manual HTotal
#endif
        }
        else {
            i = ReadShortScalerHighLowFilter(&SC_DSP_HTOTAL_LO) & 0x0FFF;
            if (abs(i-disp.htotal) < 5) {
                disp.htotal = i;
            }
        }
        disp.vtotal = (float)ulDisplayClk * 10 / disp.htotal / usVSyncFreq + 0.5;
        
        WriteShortScaler(&SC_DV_TOTAL_LO, disp.vtotal); //Display Active Vtotal
        WriteShortScaler(&SC_DV_BG_BEG_LO, UserPanelData.usMinVSyncWidth + UserPanelData.usMinVSyncBackPorch); //Display Background VStart
        i = UserPanelData.usMinVSyncWidth + UserPanelData.usMinVSyncBackPorch + (UserPanelData.usHeight - disp.active_height) / 2;
//------fefanjacky for 1850x1036@60---------------------------------
#if SPECIALAPP == ON
        i=i+0x16;
#endif
//------------------------------------------------------------------
#ifdef AUO_G151EVN01_720  //fefanjacky for this panel dp-mode first line flash
        i=i+1;
#endif
//----------------------------------------------------------------------------------------------------------------------
        WriteShortScaler(&SC_GRAPHIC_DISP_VER_ACT_BEG_LO, i); //Display Active VStart
        WriteShortScaler(&SC_DH_HTOTAL_LO, disp.htotal); //Display Active Htotal

#if ENABLE_SCALER_3D == ON
        if (SC3DAPI_IsHDMI3DMode() == FALSE) //If input is not HDMI 3D format, then exit directly
#endif
        {
            if (disp.active_height != UserPanelData.usHeight) {
                i = SC_DISPLAY_CTRL;						//150112 mike 
                SC_DISPLAY_CTRL = (i & ~BIT5); 				//Manual HTotal
            }
        }
    }

    WriteShortScaler(&SC_DV_BG_LEN_LO, UserPanelData.usHeight); //Display Background Vertical Length

    // CheckFIFO must be prior to SetFixHR2 because FIFO lock setting!
    CheckFIFO();
    
    CheckInterlacedSignalField();

    if (CheckModeChangeFlag() == FALSE) {
        SetFixHR2();
    }
    else {
        LoadDefaultPanelData();
        SetFreeRunClk();
    }

#if ENABLE_SR == ON
     SetSRInputTimingParameter();
#endif

    SC_ADC_BAND_GAP = Reg0x1ED;
    return TRUE;
}

/**************************************************************************//**
 * Set the background color of post-pattern.
 * @param r Gray level of red color.
 * @param g Gray level of green color.
 * @param b Gray level of blue color.
 ******************************************************************************/
void SetPostBGColor(UCHAR r, UCHAR g, UCHAR b)
{
    SC_DISP_BACKGROUND_RED = r;
    SC_DISP_BACKGROUND_GREEN = g;
    SC_DISP_BACKGROUND_BLUE = b;
}

/**************************************************************************//**
 * Set the background color of post pattern, turn the scaler to free-run mode and output post-pattern.
 * @param r Gray level of red color.
 * @param g Gray level of green color.
 * @param b Gray level of blue color.
 ******************************************************************************/
void Force2Background(UCHAR r, UCHAR g, UCHAR b)
{
    if ((SC_DISPLAY_MUTE_CTRL & 0x03) != 0x02) {
        SetPostBGColor(r, g, b);
        DisplayMuteImage();
        LoadDefaultPanelData();
        SetFreeRunClk();
    }
    SC_DISPLAY_CHANNEL = BIT6;//(BIT5|BIT6); //RGB
#if (INPUT_INTERFACE&INPUT_DP)
    SC_DP_FAST_MUTE_CTRL = SCREG_B88;
#endif
}

/**************************************************************************//**
 * Wait until next display VSync pulse.
 * The maximum waiting time is 100ms.
 * If the display-related power is off, the default delay time is 40ms.
 ******************************************************************************/
void WaitDisVSync(void)
{
    USHRT temp;

    // Confirm the scaler has display VSync out or not!
    if (((SC_POWER_CTRL1 & BIT0) != 0) ||
        ((SC_DPLL_CTRL1 & BIT0) == 0) ||
        ((SC_DISPLAY_CTRL & BIT0) == 0)) {			
        Sleep(40);
        return;
    }

    ResetWDTimer();
    if ((SC_DISPLAY_POL_CTRL & BIT4) == 0x00) {
        temp = GetTimerTick();
        while ((GetTimerTick() - temp) < 50) {
            if ((SC_DISP_SYNC_STATUS & BIT7) == 0) {
                break;
            }
        }
        while ((GetTimerTick() - temp) < 100) {
            if ((SC_DISP_SYNC_STATUS & BIT7) != 0) {
                break;
            }
        }
    }
    else {
        temp = GetTimerTick();
        while ((GetTimerTick() - temp) < 50) {
            if ((SC_DISP_SYNC_STATUS & BIT7) != 0) {
                break;
            }
        }
        while ((GetTimerTick() - temp) < 100) {
            if ((SC_DISP_SYNC_STATUS & BIT7) == 0) {
                break;
            }
        }
    }
    ResetWDTimer();
}

/**************************************************************************//**
 * Disable display (mute R/G/B data).
 ******************************************************************************/
void GraphicDisplayWindowDisable(void)
{
    SC_DITHER_TOGGLE_CTRL |= BIT7;
}

/**************************************************************************//**
 * Enable display (un-mute R/G/B data).
 ******************************************************************************/
void GraphicDisplayWindowEnable(void)
{
    SC_DITHER_TOGGLE_CTRL &= ~BIT7;
}

/**************************************************************************//**
 * Check Interlaced Signal Odd/Even Field
 ******************************************************************************/
void CheckInterlacedSignalField(void)
{
//    xdata UCHAR i,j, *p, matrix[3][6], reg0x1D0;
    xdata UCHAR ssc_backup, reg0x150, reg0x154,reg0x188;
 xdata USHRT temp, tmp_ord, tmp_erd;

 if (IsInterlaced()) { //If input is interlaced
        reg0x154 = SC_DISPLAY_MUTE_CTRL;
        reg0x150 = SC_DISPLAY_CTRL;					
        reg0x188 = SC_VCR_CTRL;
/*
        reg0x1D0 = SC_SRGB_CTRL;
        for (i=0; i<3; i++) {
            SC_SRGB_CTRL = ((i * 2) + 0x01);
            p = &SC_SRGB_COEF_R_LO;
            for (j=0; j<6; j++) {
                matrix[i][j] = *p;
                *p = 0;
                p++;
            }
        }
        SC_SRGB_CTRL = 0x0D;
*/
        SC_DITHER_TOGGLE_CTRL |= BIT7;
        //for get data to calculate   
        SC_DISPLAY_MUTE_CTRL = 0x00;
 
        ssc_backup = SC_SSC_CTRL;
        DisableDclkSSC();
//        SC_DISPLAY_MUTE_CTRL = 0x00;
        if ((SC_INPUT_SELECT & 0x03) < 2) {   //analog
            SC_GRAPHIC_DISP_WIN_CTRL = 0x07;
            temp = GetInputVStart();
            SetEvenFieldOffset(0);
            SetVP(5);
/* 
            if ((SC_DISPLAY_CTRL & BIT6) == 0x00) {
                WriteShortScaler(&SC_LOCK_H_SHIFT_LO, ReadShortScalerHighLowFilter(&SC_CAP_HTOTAL_LENGTH_LO)/2);
            }
            else {
                WriteShortScaler(&SC_LOCK_H_SHIFT_LO, 0x00);
            }
*/
            DelayVTime(8);//50Hz: over 120ms, 60Hz: over 100ms. 6 times frame
            if (abs(ReadShortScalerHighLowFilter(&SC_MISC_O_RD_LO) - ReadShortScalerHighLowFilter(&SC_MISC_E_RD_LO)) > 1) {
                SetEvenFieldOffset(-1);
                SetVP(5);
                DelayVTime(8);//50Hz: over 120ms, 60Hz: over 100ms. 6 times frame
                if (abs(ReadShortScalerHighLowFilter(&SC_MISC_O_RD_LO) - ReadShortScalerHighLowFilter(&SC_MISC_E_RD_LO)) > 1) {
                    SetEvenFieldOffset(1);
                    SetVP(5);
                    DelayVTime(8);//50Hz: over 120ms, 60Hz: over 100ms. 6 times frame
                }
            }
            SetVP(temp);
            DelayVTime(8);//50Hz: over 120ms, 60Hz: over 100ms. 6 times frame
            if (abs(ReadShortScalerHighLowFilter(&SC_MISC_O_RD_LO) - ReadShortScalerHighLowFilter(&SC_MISC_E_RD_LO)) > 1) {
                SC_GRAPHIC_DISP_WIN_CTRL = 0x47;
            }
        }
    #if (INPUT_INTERFACE&INPUT_DP)
        else if ((SC_INPUT_SELECT & 0x03) == 0x03) {   //displayport
            SC_GRAPHIC_DISP_WIN_CTRL = 0x07;
        }
    #endif
        else {
            SC_GRAPHIC_DISP_WIN_CTRL = 0x07;
/*
            if ((SC_DISPLAY_CTRL & BIT6) == 0x00) {
                if ((GetVCaptureSize() == 1080) && (GetInputVTotal() > 593)) {
                    // CEA timing 39: 1920x1080i/50Hz
                    WriteShortScaler(&SC_LOCK_H_SHIFT_LO, 0x00);
                }
                else {
                    WriteShortScaler(&SC_LOCK_H_SHIFT_LO, ReadShortScalerHighLowFilter(&SC_CAP_HTOTAL_LENGTH_LO)/2);
                }
            }
            else {
                WriteShortScaler(&SC_LOCK_H_SHIFT_LO, 0x00);
            }
*/
            if (abs(ReadShortScalerHighLowFilter(&SC_GI_CAP_VBEGO_LO) - ReadShortScalerHighLowFilter(&SC_GI_CAP_VBEGE_LO)) > 0) {
                if ((SC_GI_SYNC_CTRL3 & BIT0) == 0x00) {
                    SC_GI_SYNC_CTRL3 |= BIT0;
                    temp = ReadShortScaler(&SC_GI_CAP_VBEGE_LO);
                    WriteShortScaler(&SC_GI_CAP_VBEGE_LO, ReadShortScaler(&SC_GI_CAP_VBEGO_LO));
                    WriteShortScaler(&SC_GI_CAP_VBEGO_LO, temp);
                }
            }
            else {
                SC_GI_SYNC_CTRL3 &= ~BIT0;
            }

            DelayVTime(8);//50Hz: over 120ms, 60Hz: over 100ms. 6 times frame
            tmp_ord = ReadShortScalerHighLowFilter(&SC_MISC_O_RD_LO);
            tmp_erd = ReadShortScalerHighLowFilter(&SC_MISC_E_RD_LO);

            if (abs(ReadShortScalerHighLowFilter(&SC_MISC_O_RD_LO) - ReadShortScalerHighLowFilter(&SC_MISC_E_RD_LO)) > 1) {
                SC_GRAPHIC_DISP_WIN_CTRL |= BIT6;
                DelayVTime(8);
                // If the blanking time of odd/even fields are not stable, we switch the settings of odd/even position
                // Jude 2011/10/18
                if ((abs(tmp_ord - ReadShortScalerHighLowFilter(&SC_MISC_O_RD_LO)) > 5) ||
                    (abs(tmp_erd - ReadShortScalerHighLowFilter(&SC_MISC_E_RD_LO)) > 5)) {
                    temp = ReadShortScaler(&SC_GI_CAP_VBEGE_LO);
                    WriteShortScaler(&SC_GI_CAP_VBEGE_LO, ReadShortScaler(&SC_GI_CAP_VBEGO_LO));
                    WriteShortScaler(&SC_GI_CAP_VBEGO_LO, temp);
                }
            }
        }
        SC_SSC_CTRL = ssc_backup;

        SC_DISPLAY_MUTE_CTRL = reg0x154;
        SC_DISPLAY_CTRL = reg0x150;					
        SC_VCR_CTRL = reg0x188;
/*
        for (i=0; i<3; i++) {
            SC_SRGB_CTRL = ((i * 2) + 0x01);
            p = &SC_SRGB_COEF_R_LO;
            for (j=0; j<6; j++) {
                *p = matrix[i][j];
                p++;
            }
        }
        SC_SRGB_CTRL |= BIT3;
        SC_SRGB_CTRL = reg0x1D0;        
*/  
        SC_DITHER_TOGGLE_CTRL &= ~BIT7;
    }
}

/**************************************************************************//**
 * Get display vertical DE time.
 * @return Number of counts of display clock.
 ******************************************************************************/
ULONG GetVCounter(void)
{
    xdata ULONG vtotalcounter, vtotalcounter2;
    UCHAR i;

    vtotalcounter = Read3ByteScalerHighLowFilter(&SC_VER_COUNTER_LO);
    DelayVTime(1);
    vtotalcounter2 = Read3ByteScalerHighLowFilter(&SC_VER_COUNTER_LO);
    i=0;

    while((labs(vtotalcounter - vtotalcounter2) < 0x10) && (i < 3)) {
        i++;
        vtotalcounter = Read3ByteScalerHighLowFilter(&SC_VER_COUNTER_LO);
        DelayVTime(1);
        vtotalcounter2 = Read3ByteScalerHighLowFilter(&SC_VER_COUNTER_LO);
    }
    
    vtotalcounter = (vtotalcounter + vtotalcounter2) >> 1;

    return vtotalcounter;
}

/**************************************************************************//**
 * Force the display clock to the one with desired HR2 (count of latest line).
 * We use this function to force the display residue to the value we expect.
 ******************************************************************************/
void SetFixHR2(void)
{
//    xdata UCHAR matrix[3][6], reg0x1D0;
//    xdata UCHAR j, *p;
    xdata UCHAR reg0x150, reg0x154, i,reg0x188;
    xdata USHRT gdv_act_len, vtotal, cal_hr1, cal_hr2, temp;
    xdata ULONG vtcnt, vdecnt;
    xdata signed short delta0p9hr1, deltahr2of0p9hr1, hr2of0p9hr1, delta_hr2, dsthtotal, wanted_hr2;
    xdata signed long delta_clk;

    reg0x154 = SC_DISPLAY_MUTE_CTRL;
    reg0x150 = SC_DISPLAY_CTRL;					
    reg0x188 = SC_VCR_CTRL;
/*
    reg0x1D0 = SC_SRGB_CTRL;
    for (i=0; i<3; i++) {
        SC_SRGB_CTRL = ((i * 2) + 0x01);
        p = &SC_SRGB_COEF_R_LO;
        for (j=0; j<6; j++) {
            matrix[i][j] = *p;
            *p = 0;
            p++;
        }
    }
    SC_SRGB_CTRL = 0x0D;
*/
    SC_DITHER_TOGGLE_CTRL |= BIT7;
    //for get data to calculate   
    SC_DISPLAY_MUTE_CTRL = 0x00;
    
    gdv_act_len = ReadShortScaler(&SC_GRAPHIC_DISP_VER_ACT_LEN_LO);
    WriteShortScaler(&SC_DV_BG_LEN_LO, gdv_act_len);
    SC_DISPLAY_CTRL = (reg0x150 | BIT5);							

    // Before HR2 calculation, force HR1 being closed to 0.9 V-active length.
    temp = ReadShortScalerHighLowFilter(&SC_HR_VALUE_LO);
    if (temp > (gdv_act_len * 0.9)) {
        delta0p9hr1 = temp - (gdv_act_len * 0.9);
    }
    else {
        delta0p9hr1 = temp + (gdv_act_len * 0.1);
    }
    dsthtotal = ReadShortScalerHighLowFilter(&SC_DSP_HTOTAL_LO) & 0x0FFF;
    if( (dsthtotal >= UserPanelData.usMinHTotal) && (dsthtotal <= UserPanelData.usMaxHTotal) )
	{
      		delta_clk = (float) ulDisplayClk * delta0p9hr1 / gdv_act_len / dsthtotal;
      		ulDisplayClk -= delta_clk;
      		SetDPLL();
    	}
    SC_HR_CTRL = 0x01;
    SC_VCR_CTRL = 0x06;
    Sleep(80);
    if (CheckModeChangeFlag() == FALSE) {
        dsthtotal = 0;
        vtcnt = 0;
        vdecnt = 0;
        for (i=0; i<4; i++) {
            SC_VCR_CTRL = 0x06;
            DelayVTime(1);
            dsthtotal += ReadShortScalerHighLowFilter(&SC_DSP_HTOTAL_LO);
            if (IsInterlaced()) { //If input is interlaced
                vtcnt += GetVCounter();
            }
            else {
                vtcnt += Read3ByteScalerHighLowFilter(&SC_VER_COUNTER_LO);
            }
            SC_VCR_CTRL = 0x02;
            vdecnt += Read3ByteScalerHighLowFilter(&SC_VER_COUNTER_LO);
        }    
        dsthtotal = (dsthtotal + 2) / 4;
        vtcnt = (vtcnt + 2) / 4;
        vdecnt = (vdecnt + 2) / 4;
        cal_hr1 = vdecnt % gdv_act_len;
        cal_hr2 = vtcnt % dsthtotal;
        vtotal = vtcnt / dsthtotal;

        delta0p9hr1 = (gdv_act_len * 0.9) - cal_hr1;
        deltahr2of0p9hr1 = (float)delta0p9hr1 * vtotal / gdv_act_len;
        hr2of0p9hr1 = cal_hr2 + deltahr2of0p9hr1;


        if (hr2of0p9hr1 > (dsthtotal*9/6)) {
            wanted_hr2 = dsthtotal*9/6;
        }
        else if (hr2of0p9hr1 > (dsthtotal*7/6)) {
            wanted_hr2 = dsthtotal*7/6;
        }
        else if (hr2of0p9hr1 > (dsthtotal*5/6)) {
            wanted_hr2 = dsthtotal*5/6;
        }
        else if (hr2of0p9hr1 > (dsthtotal*3/6)) {
            wanted_hr2 = dsthtotal*3/6;
        }
        else if (hr2of0p9hr1 > (dsthtotal*1/6)) {
            wanted_hr2 = dsthtotal*1/6;
        }
        else if (hr2of0p9hr1 > -(dsthtotal*1/6)) {
            wanted_hr2 = -(dsthtotal*1/6);
        }
        else if (hr2of0p9hr1 > -(dsthtotal*3/6)) {
            wanted_hr2 = -(dsthtotal*3/6);
        }
        else {
            wanted_hr2 = dsthtotal*1/6;
        }
        delta_hr2 = wanted_hr2 - cal_hr2;
        delta_clk = (float)ulDisplayClk * delta_hr2 / vtotal /dsthtotal;
        ulDisplayClk +=delta_clk;   //here is for hr2

        if (dsthtotal%2) {        //for hr1
            ulDisplayClk = (float)ulDisplayClk / dsthtotal * (dsthtotal-1);
            WriteShortScaler(&SC_DH_HTOTAL_LO, dsthtotal-1); //Display Active Htotal
        }
        else {
            WriteShortScaler(&SC_DH_HTOTAL_LO, dsthtotal); //Display Active Htotal
        }
	 BacklightOff();	   
        //g SetDPLL();

//For george modify :
#ifdef TRULY_TFT1280120
	//if(UserData.ucInputSource == 0 &&  InputTiming.usModeIndex == _1280x120_50HZ)	//Input=VGA, ModeTable[index==0]		ucInputSyncMode == 0
	if(InputTiming.usModeIndex == _1280x120_50HZ)
	{
//g		ulDisplayClk = 15000000;  //unit: hz
		//printf("set_new_DPLL= 15Mhz\n");

	}

	SetDPLL();

#else	//Normal Panel   
	SetDPLL();
#endif 


////////check/////////////////////////////////
#if 0
        SC_DISPLAY_CTRL = (reg0x150 & ~BIT5);					
        SC_HR_CTRL = 0x01;
        Sleep(80);
        cal_hr1 = ReadShortScalerHighLowFilter(&SC_HR_VALUE_LO);
        printf("cal_hr1=%d\r\n", cal_hr1);
        SC_HR_CTRL = 0x12;
        Sleep(80);
        cal_hr2 = ReadShortScalerHighLowFilter(&SC_HR_VALUE_LO);
        SC_HR_CTRL = 0x00;
        printf("cal_hr2=%d\r\n", cal_hr2);
        dsthtotal = ReadShortScalerHighLowFilter(&SC_DSP_HTOTAL_LO);
        printf("dsthtotaly=%d\r\n",dsthtotal);
#endif
///////////////////////////////////////////
    }
    SC_DISPLAY_MUTE_CTRL = reg0x154;
    SC_HR_CTRL = 0x00;
    SC_DISPLAY_CTRL = reg0x150;								
#if 0
    if (CheckModeChangeFlag() == FALSE) {
        Sleep(80);
        dsthtotal = ReadShortScalerHighLowFilter(&SC_DSP_HTOTAL_LO);
        WriteShortScaler(&SC_DH_HTOTAL_LO, dsthtotal); //Display Active Htotal
        printf("dsthtotalz=%d\r\n",dsthtotal);
    }
#endif
    WriteShortScaler(&SC_DV_BG_LEN_LO, UserPanelData.usHeight);
    SC_VCR_CTRL = reg0x188;
    SC_DITHER_TOGGLE_CTRL &= ~BIT7;
}

/**************************************************************************//**
 * Get display h/v ratio.
 * E.x. 0 means full screen.
 *      1333 means 4:3.
 *      1250 means 5:4.
 *      1600 means 16:10.
 * @return Display h/v ratio.
 ******************************************************************************/
/*
USHRT GetCustomDspRatio(void)
{
    return usDisRatio;
}
*/

/**************************************************************************//**
 * Set display h/v ratio.
 * ratio : Range is "less then 1000", or "1000 to 65535".
 *         E.x. If aspect ratio is full screen, ratio is "less then 1000". 0 is preferred.
 *              If aspect ratio is 16:10, ratio is 1600.
 *              If aspect ratio is 5:4, ratio is 1250.
 *              If aspect ratio is 4:3, ratio is 1333.
 * @param ratio Display h/v ratio.
 ******************************************************************************/
void SetCustomAspRatio(USHRT ratio)
{
    USHRT dh_bg_beg, width, begin;

#if (ENABLE_SCALER_3D == ON)
    if (SC3DAPI_IsDisplay3D()) {
        return;
    }
#endif

    usDisRatio = ratio;
    dh_bg_beg = ReadShortScaler(&SC_DH_BG_BEG_LO);

    if (ratio < 1000) {
        width = UserPanelData.usWidth;
        begin = dh_bg_beg;
    }
    else {
        width = ((ULONG)UserPanelData.usHeight * ratio + 500) / 1000;
        width &= 0xFFFE; // Force active width being even
        if (width > UserPanelData.usWidth) width = UserPanelData.usWidth;
        begin = dh_bg_beg + (UserPanelData.usWidth - width) / 2;
    }

//--FEFANJACKY for 1850x1036 -------------------------------------------------
#if SPECIALAPP == ON
        begin = dh_bg_beg + 0x23;
        width = 0x73A;
#endif
//----------------------------------------------------------------------------


#if 1
    if ((begin != ReadShortScaler(&SC_GRAPHIC_DISP_HOR_ACT_BEG_LO)) ||
        (width != ReadShortScaler(&SC_GRAPHIC_DISP_HOR_ACT_WID_LO))) {
#else
    {
#endif
        WaitDisVSync();
        GraphicDisplayWindowDisable();
        WriteShortScaler(&SC_GRAPHIC_DISP_HOR_ACT_BEG_LO, begin);
        WriteShortScaler(&SC_GRAPHIC_DISP_HOR_ACT_WID_LO, width);
        Sleep(80);
        WaitDisVSync();
        GraphicDisplayWindowEnable();
    }
}

/**************************************************************************//**
 * Set display ratio by mode.
 * If the mode is
 *   ASP_RATIO_FULL  : Display full screen.
 *   ASP_RATIO_SCALE : Keep org. display ratio.
 *   ASP_RATIO_4_3   : Force display ratio to 4:3.
 *   ASP_RATIO_SMART_4_3 : Force display ratio to 4:3 if input ratio is small 16:10.
 *   ASP_RATIO_REAL  : pixel by pixel.
 * @param aspectmode Aspect ratio mode.
 ******************************************************************************/
void SetDisplayMode(AspectRatio aspectmode)
{
    USHRT input_vactive, input_hactive, ratio;

    ucAspRatioMode = aspectmode;
    if ((SC_INPUT_SELECT & 0x03) < 2) {   //analog
        input_vactive = InputTiming.usModeVActive; 
        input_hactive = InputTiming.usModeHActive; //for double sampling (ucSampling)
    }
    else {    
        input_vactive = ReadShortScaler(&SC_GI_CAP_VLEN_LO);
        input_hactive = ReadShortScaler(&SC_GI_CAP_HWID_LO);
    }


    if (aspectmode == ASP_RATIO_SMART_4_3) {
        ratio = input_hactive * 10 / input_vactive;
        if (ratio < 16)
            aspectmode = ASP_RATIO_4_3;
        else
            aspectmode = ASP_RATIO_FULL;
    }

    if (aspectmode == ASP_RATIO_4_3) {
        ratio = 1333;
    }
    else if (aspectmode == ASP_RATIO_SCALE) {
        ratio = ((ULONG) input_hactive * 1000 + input_vactive / 2)
                / input_vactive;
    }
    else if (aspectmode == ASP_RATIO_REAL) {
        ratio = 0;
    }
    else { //Full screen
        ratio = 0;
    }

    SetCustomAspRatio(ratio);
}

/**************************************************************************//**
 * Setup aspect ratio and enable scaler fast mute function.
 ******************************************************************************/
void NormalDisplay(void)
{

//    SC_DITHER_TP_GRAY_LVL_LO = 0x00;
//    SC_DITHER_TP_GRAY_LVL_HI = 0x00;
    SC_DITHER_TOGGLE_CTRL |= BIT7;
    SC_DISPLAY_CHANNEL = 0xC0;
#if (INPUT_INTERFACE&INPUT_DP)
    if (GetCurrInputInterface() == DISPLAY_PORT_INPUT) {
        SC_DP_FAST_MUTE_CTRL |= 0x0B;
    }
#endif
    SC_DISPLAY_MUTE_CTRL = 0x00;
    //SetDisplayMode(ucAspRatioMode);
    UserSetAspectRatio();
    SetPostBGColor(0x00, 0x00, 0x00); // Set black color to avoid unexpected color from user-level burn-in mode.
    Sleep(40);
    if ((SC_INPUT_SELECT & 0x03) < 2) { //analog
        WaitHPLLstable();
        HwAutoOffset();
        if ((SC_GI_SYNC_CTRL & 0x03) == 0x01) {
            SC_HPLL_FREQ_CTRL |= BIT6; //Disable updating HS_CNT
        }
    }

    // Reduce time to detect overflow when input HSync is varied.
    SetupHSyncOverflowMask(TRUE);

//	bTouchOnOffChange = TRUE;	//150612 george
}

/**************************************************************************//**
 * Configure post-pattern and turn it on (display free-run).
 ******************************************************************************/
void DisplayPostPattern(UCHAR pattern)
{
    SC_DISPLAY_MUTE_CTRL = pattern | 0x01;
}

/**************************************************************************//**
 * Mute display with OSD enabled (display free-run).
 ******************************************************************************/
void DisplayMuteImage(void)
{
    SC_DISPLAY_MUTE_CTRL = 0x02;
}

/**************************************************************************//**
 * Turn the scaler to normal display.
 ******************************************************************************/
void DisplayNormalImage(void)
{
    WaitDisVSync();
    SC_DITHER_TOGGLE_CTRL &= ~BIT7;
}

/**************************************************************************//**
 * Enable SSC.
 ******************************************************************************/
void EnableDclkSSC(void)
{
    if (UserPanelData.bEnableSSC) {
        SC_SSC_CTRL |= BIT0;
    }
    else {
        SC_SSC_CTRL &= ~BIT0;
    }
}

/**************************************************************************//**
 * Disable SSC.
 ******************************************************************************/
void DisableDclkSSC(void)
{
    SC_SSC_CTRL &= ~BIT0;
}

/**************************************************************************//**
 * Set SSC ratio.
 * @param ratio SSC ratio.
 ******************************************************************************/
void SetDclkSSCRatio(SSCRatio ratio)
{
    SC_SSC_CTRL = (SC_SSC_CTRL & 0xE1) | ratio;
}

/**************************************************************************//**
 * Set SSC frequency.
 * @param freq SSC frequency.
 ******************************************************************************/
void SetDclkSSCFreq(SSCFreq freq)
{
    SC_SSC_CTRL = (SC_SSC_CTRL & 0x1F) | freq;
}

/**************************************************************************//**
 * Set both SSC ratio and frequency and turn SSC on.
 * @param value Combinational value of SSC ratio and frequency.
 ******************************************************************************/
void SetDclkSSC(UCHAR value)
{
    SetDclkSSCRatio(value);
    SetDclkSSCFreq(value);
    EnableDclkSSC();
}

/**************************************************************************//**
 * Set FIFO to manual lock mode if input timing is interlaced or vertical scaling down.
 ******************************************************************************/
void CheckFIFO(void)
{
#if IS_NT68150_SERIES
    if (IsInterlaced()) { //If input is interlaced. FIFO -= half htotal
        if ((GetInputVTotal() > 593) && ((GetVCaptureSize() == 1080) || (GetDigInputVActiveImmediate() == 540))) {            
            // CEA timing 39: 1920x1080i/50Hz
            SC_DISPLAY_VLOCK = 1;
            WriteShortScaler(&SC_DISPLAY_HLOCK_LO, 0);
            SC_DISPLAY_CTRL &= ~BIT6;								
            SC_DISPLAY_CTRL &= ~BIT4;								
        }
        else {
            SC_DISPLAY_CTRL |= BIT6;									
            SC_DISPLAY_CTRL |= BIT4;									
        }
    }
    else {
        SC_DISPLAY_CTRL |= BIT6;									
        SC_DISPLAY_CTRL &= ~BIT4;									
    }
#else
															//    UCHAR backup, fifo_v;
    USHRT fifo_h;												//, temp, input_vactive;
#if IS_NT68850_SERIES || IS_NT68790_SERIES
    SC_DISPLAY_HLOCK_HI &= 0x0F;
#endif

    if (IsInterlaced()) { //If input is interlaced. FIFO -= half htotal
/*
        backup = SC_SSC_CTRL;
        SC_SSC_CTRL &= ~BIT0;
        DelayVTime(4);
        temp = ReadShortScalerHighLowFilter(&SC_DISP_HLOCK_POS_R);
        fifo_v = temp >> 12;
        fifo_h = temp & 0x0FFF;
        temp = ReadShortScalerHighLowFilter(&SC_CAP_HTOTAL_LENGTH_LO);//capture htotal
        fifo_h += temp * fifo_v;
        if ((GetVCaptureSize() == 1080) && (GetInputVTotal() > 593)) {
            // CEA timing 39: 1920x1080i/50Hz
            fifo_h -= (ReadShortScalerHighLowFilter(&SC_CAP_HTOTAL_LENGTH_LO) / 2);
        }
        else {
            fifo_h -= ReadShortScalerHighLowFilter(&SC_CAP_HTOTAL_LENGTH_LO);
        }
        fifo_v = fifo_h / temp;
        fifo_h = fifo_h % temp;

        SC_DISPLAY_VLOCK = fifo_v;
        WriteShortScaler(&SC_DISPLAY_HLOCK_LO, fifo_h);
        SC_SSC_CTRL = backup;
*/
        if ((GetInputVTotal() > 593) && ((GetVCaptureSize() == 1080) || (GetDigInputVActiveImmediate() == 540))) {            
            // CEA timing 39: 1920x1080i/50Hz
            SC_DISPLAY_VLOCK = 1;
            fifo_h = ReadShortScaler(&SC_DISPLAY_HLOCK_LO) & 0xF000;
            WriteShortScaler(&SC_DISPLAY_HLOCK_LO, fifo_h);
            SC_DISPLAY_CTRL &= ~BIT6;						
            SC_DISP_DRIVE_CTRL &= ~BIT7;
        }
        else {
            SC_DISPLAY_CTRL |= BIT6;							
            SC_DISP_DRIVE_CTRL |= BIT7;
        }
    }
    else {
#if IS_NT68850_SERIES || IS_NT68790_SERIES
        SC_DISPLAY_HLOCK_HI |= BIT5;
#endif
#if (INPUT_INTERFACE&INPUT_DP)
        if (SC_FRC_CTRL != 0x00) { 							// DFR, FRC
            SC_DISPLAY_VLOCK = 1;
            fifo_h = ReadShortScaler(&SC_DISPLAY_HLOCK_LO) & 0xF000;
            WriteShortScaler(&SC_DISPLAY_HLOCK_LO, fifo_h);
            SC_DISPLAY_CTRL &= ~BIT6;						
            SC_DISP_DRIVE_CTRL &= ~BIT7;
        }
        else
#endif
        {
            SC_DISPLAY_CTRL |= BIT6;							
            SC_DISP_DRIVE_CTRL &= ~BIT7;
        }
    }
#endif
}
