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
// G L O B A L   D E F I N I T I O N S
//******************************************************************************
#define DBC_ULTRA_LOW
#ifdef DBC_ULTRA_LOW
#define DBC_TIME_TO_OFF     10000
#define DBC_BACKLIGHT_OFF   ULTRA_MIN_BACKLIGHT_VALUE
#define DBC_LTHD_BLANK      4
#define DBC_HTHD_BLANK      7
#endif
#define MapDBCBacklight(s)  ((ULONG)s * (1023 - MIN_BACKLIGHT_VALUE) / 1023 + MIN_BACKLIGHT_VALUE)

//******************************************************************************
// S T A T I C   V A R I A B L E S
//******************************************************************************
static code IGBlock IGModes[NUMBER_IG_MODES] = {
    {16,   0,  16,  88, 156, 228, 300, 368, 440, 508, 584, 652, 724, 796, 864, 936,1008,1024}, //IG_STD_1
    {16,   0,  16,  32, 112, 192, 272, 352, 432, 512, 592, 672, 752, 832, 912, 992,1008,1024}, //IG_STD_2
    {16,   0,  58, 116, 168, 228, 288, 356, 428, 504, 584, 660, 732, 800, 860, 920, 972,1024}, //IG_S_CURVE
    {16,   0,  58, 128, 216, 288, 352, 412, 468, 520, 568, 620, 676, 736, 800, 872, 964,1024}, //IG_RS_CURVE
    {16,   0,  48, 100, 152, 204, 260, 320, 380, 440, 504, 572, 640, 712, 784, 864, 964,1024}, //IG_RC_CURVE
    {16,   0,  84, 164, 240, 312, 384, 452, 520, 584, 648, 708, 764, 820, 876, 928, 976,1024}, //IG_C_CURVE
    {16,   0,  64, 116, 184, 252, 332, 408, 472, 552, 620, 676, 732, 800, 860, 920, 972,1024}, //IG_NVT_CURVE_1
    {16,   0,  48, 108, 164, 228, 276, 340, 408, 488, 540, 596, 664, 736, 804, 876, 948,1024}, //IG_NVT_CURVE_2
    {16,   0,  64, 128, 192, 256, 320, 384, 448, 512, 576, 640, 704, 768, 832, 896, 960,1024}, //IG_DEFAULT
};

static code UCHAR DefaultMinIGPoints[] = {
    40, 40, 52, 52, 58, 58, 58, 58, 58, 58, 58, 58, 52, 40, 40, 40
};

static code HHBlock HHModes[NUMBER_HH_MODES] = {
    {
        24,
        0x00,
        0x00,0x04,0x02,0x04,
        0x18,0x20,0x88,0x04,
        0x08,0x04,0x00,0x00,
        0x00,0x08,0x10,0x08,
        0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x10,
    },{
        24,
        0x00,
        0x00,0x04,0x02,0x04,
        0x18,0x20,0x83,0x04,
        0x08,0x04,0x00,0x00,
        0x00,0x08,0x10,0x08,
        0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x10,
    },{
        24,
        0x00,
        0x00,0x04,0x02,0x04,
        0x18,0x20,0x83,0x04,
        0x08,0x04,0x00,0x00,
        0x00,0x08,0x10,0x08,
        0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x10,
    },
};

static code HSBlock HSModes[NUMBER_HS_MODES] = {
    {
        24,
        0x00,
        0x98,0x90,0x88,0xA0,
        0xa8,0xa8,0x90,0x88,
        0x90,0x88,0x80,0x80,
        0x80,0x90,0xa0,0x90,
        0x80,0x80,0x80,0x80,
        0x80,0x80,0x80,0x90,
    },{
        24,
        0x00,
        0x8e,0x90,0x70,0xA0,
        0xa8,0xa8,0x98,0x88,
        0x90,0x88,0x80,0x80,
        0x80,0x90,0xa0,0x90,
        0x80,0x80,0x80,0x80,
        0x80,0x80,0x80,0x90,
    },{
        24,
        0x00,
        0x8e,0x90,0x70,0xA0,
        0xa8,0xa8,0x98,0x88,
        0x90,0x88,0x80,0x80,
        0x80,0x90,0xa0,0x90,
        0x80,0x80,0x80,0x80,
        0x80,0x80,0x80,0x90,
    },
};

static code CMBlock CMModes[NUMBER_CE_MODES] = {
    {// 76% NTSC
        0x80,    //R Offset
        0x80,    //G Offset
        0x80,    //B Offset
        0x80,    //R Gain
        0x80,    //G Gain
        0x80,    //B Gain
        0x80,    // Saturation
        0x80,    // Intensity
        0x80,    // Hue
        0x80,    // BlueMore
        0x80,    // GreenMore
        0x80,    // RedMore
        0x00,    // FTMore
        0x00,    // Sharpness
        0x00,    // Peaking
        0x00,    // TextEn
        BF_COLOR_NVT76,
        &IGModes[IG_DEFAULT],
        NULLPTR, // HH Table
        NULLPTR, // HS Table
        NULLPTR, // HI Table
    },{// 80% NTSC
        0x80,    //R Offset
        0x80,    //G Offset
        0x80,    //B Offset
        0x80,    //R Gain
        0x80,    //G Gain
        0x80,    //B Gain
        0x80,    // Saturation
        0x80,    // Intensity
        0x80,    // Hue
        0x80,    // BlueMore
        0x80,    // GreenMore
        0x80,    // RedMore
        0x00,    // FTMore
        0x00,    // Sharpness
        0x00,    // Peaking
        0x00,    // TextEn
        BF_COLOR_NVT80,
        &IGModes[IG_DEFAULT],
        NULLPTR, // HH Table
        NULLPTR, // HS Table
        NULLPTR, // HI Table
    },/*{// Color 1
        0x80,    //R Offset
        0x80,    //G Offset
        0x80,    //B Offset
        0x80,    //R Gain
        0x80,    //G Gain
        0x80,    //B Gain
        0x98,    // Saturation
        0x80,    // Intensity
        0x82,    // Hue
        0x80,    // BlueMore
        0x80,    // GreenMore
        0x80,    // RedMore
        0x00,    // FTMore
        0x01,    // Sharpness
        0x01,    // Peaking
        0x00,    // TextEn
        BF_COLOR_NVT72,
        &IGModes[IG_NVT_CURVE_1],
        &HHModes[HH_MODE_1],
        &HSModes[HS_MODE_1],
        NULLPTR, // HI Table
    },{// Color 2
        0x80,    //R Offset
        0x80,    //G Offset
        0x80,    //B Offset
        0x80,    //R Gain
        0x80,    //G Gain
        0x80,    //B Gain
        0x90,    // Saturation
        0x80,    // Intensity
        0x82,    // Hue
        0x80,    // BlueMore
        0x80,    // GreenMore
        0x80,    // RedMore
        0x00,    // FTMore
        0x01,    // Sharpness
        0x01,    // Peaking
        0x00,    // TextEn
        BF_COLOR_NVT72,
        &IGModes[IG_NVT_CURVE_2],
        &HHModes[HH_MODE_2],
        &HSModes[HS_MODE_2],
        NULLPTR, // HI Table
    },*/{//OFF
        0x80,    //R Offset
        0x80,    //G Offset
        0x80,    //B Offset
        0x80,    //R Gain
        0x80,    //G Gain
        0x80,    //B Gain
        0x80,    // Saturation
        0x80,    // Intensity
        0x80,    // Hue
        0x80,    // BlueMore
        0x80,    // GreenMore
        0x80,    // RedMore
        0x00,    // FTMore
        0x00,    // Sharpness
        0x00,    // Peaking
        0x00,    // TextEn
        BF_COLOR_INIT,
        &IGModes[IG_DEFAULT],
        NULLPTR, // HH Table
        NULLPTR, // HS Table
        NULLPTR, // HI Table
    },
};

//******************************************************************************
// Prototype: 
//  void InitColor(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Color setting initialization.
// Notes:
//  None
//******************************************************************************
void InitColor(void)
{
    #if ENABLE_CM2 == ON
        BFAPI_Init(BF_TWO_GEN);
    #else
        BFAPI_Init(BF_ONE_GEN);
    #endif
        BFAPI_SetActiveWindow(BF_WINDOW_2);

        // Always access global 3x3 matrix when adjust contrast and colortemp.
        // P.S. MTXAPI_EnableLocalMatrix must be after BFAPI_Init.
        MTXAPI_SelMatrix(MTX_GLOBAL);
        MTXAPI_EnableLocalMatrix(FALSE);
    }
    
//******************************************************************************
// Prototype: 
//  void SetThemeMode(UCHAR mode)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Set Color Theme
// Notes:
//  None
//******************************************************************************
void SetThemeMode(UCHAR mode)
{
    BFAPI_EnableCM(CM_ALL);
    BFAPI_SetROffset(CMModes[mode].ROffset);
    BFAPI_SetGOffset(CMModes[mode].GOffset);
    BFAPI_SetBOffset(CMModes[mode].BOffset);
    BFAPI_SetRGain(CMModes[mode].RGain);
    BFAPI_SetGGain(CMModes[mode].GGain);
    BFAPI_SetBGain(CMModes[mode].BGain);
    BFAPI_SetHue(CMModes[mode].Hue);
    BFAPI_SetSaturation(CMModes[mode].Saturation);
    BFAPI_SetIntensity(CMModes[mode].Intensity);
    BFAPI_CorrectFleshTone(CMModes[mode].FTMore);
    BFAPI_EnhanceRed(CMModes[mode].RedMore);
    BFAPI_EnhanceGreen(CMModes[mode].GreenMore);
    BFAPI_EnhanceBlue(CMModes[mode].BlueMore);
    BFAPI_SetSharpness(CMModes[mode].Sharpness);
    BFAPI_SetYPeaking(CMModes[mode].Peaking);
    BFAPI_SetTextEnhancement(CMModes[mode].TextEn);
    BFAPI_ColorEnhance(CMModes[mode].ClrMode);
    if (UserData.ucDCRMode != BKL_CTRL_DCR)
        BFAPI_SetPreACEMode(CMModes[mode].pIG);
    BFAPI_SetHHTable(CMModes[mode].pHH);
    BFAPI_SetHSTable(CMModes[mode].pHS);
    BFAPI_SetHITable(CMModes[mode].pHI);
    BFAPI_SetWindowSize(BF_WINDOW_FULLSCREEN);
    BFAPI_EnableWindow(BF_WINDOW_2);
}

//#if ENABLE_DBC == OFF
#ifdef DBC_ULTRA_LOW
//******************************************************************************
// Prototype: 
//  static BOOL IsBlankVideo(void)
// Parameters:
//  None
// Return:
//  Return TRUE/FALSE
// Purpose:
//  Check the current input video is blank or not.
// Notes:
//  None
//******************************************************************************
static BOOL IsBlankVideo(void)
{
    static BOOL blank_flag = FALSE;
    UCHAR rcode, gcode, bcode;

    if (DCR_IsReadyToGetMax()) {
        rcode = DCR_GetRMax();
        gcode = DCR_GetGMax();
        bcode = DCR_GetBMax();

        if ((rcode < DBC_LTHD_BLANK) && (gcode < DBC_LTHD_BLANK) && (bcode < DBC_LTHD_BLANK)) {
            blank_flag = TRUE;
        }
        else if ((rcode > DBC_HTHD_BLANK) || (gcode > DBC_HTHD_BLANK) || (bcode > DBC_HTHD_BLANK)) {
            blank_flag = FALSE;
        }
    }

    return blank_flag;
}

//******************************************************************************
// Prototype:
//  static void PerformDBC(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Periodic DBC routine
// Notes:
//  None
//******************************************************************************
static void PerformDBC(void)
{
    static BOOL is_spr_dcr = FALSE;
    static xdata USHRT local_timer = 0;

    if (!IsBlankVideo()) {
        local_timer = GetTimerTick();

        if (is_spr_dcr) {
            is_spr_dcr = FALSE;
            DCR_ResetDymBacklight(0);
        }
    }
    else {
        if ((GetTimerTick() - local_timer) > DBC_TIME_TO_OFF) {
            local_timer = GetTimerTick();
            if (is_spr_dcr == FALSE) {
                is_spr_dcr = TRUE;
                SetBrightness(DBC_BACKLIGHT_OFF);
            }
        }
    }

    if (is_spr_dcr == FALSE) {
        DCR_SetDymBacklight();
    }
}
#endif

//******************************************************************************
// Prototype:
//  void PerformDCR(UCHAR reset)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Periodic DCR routine
// Notes:
//  None
//******************************************************************************
void PerformDCR(UCHAR reset)
{
    if (reset) {
        DCR_SetDynACEType(ACE_SMOOTH);
        DCR_SetDynACEPnts(DefaultMinIGPoints);
    }

    if ( UserData.ucDCRMode == BKL_CTRL_DCR ) {
        DCR_UpdateHistogram(reset);
        DCR_SetDymACE(reset);
        if (reset) {
            DCR_ResetDymBacklight(GetBrightness1023());
        }
        else {
        #ifdef DBC_ULTRA_LOW
            PerformDBC();
        #else
            DCR_SetDymBacklight();
        #endif
        }
    }
}

//******************************************************************************
// Prototype: 
//  void DisableDCR(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Recall brightness setting while turn off DCR function
// Notes:
//  None
//******************************************************************************
void DisableDCR(void)
{
    UserSetBF();

#if ALS_EnDis == ALSMODE
	if(UserData.ucALSMode == ALS_OFF) {
    	UserSetBrightness();
	}else {  //if(UserData.ucALSMode == INDOOR || UserData.ucALSMode == OUTDOOR) {								//george: F_CM3218_01
		CM3218_BacklightOn_Init();
		SetNowALSBrig();
	}
#elif ALS_EnDis == ALSOffSET	
	if(UserData.bALSOnOff == OFF) {
    	UserSetBrightness();
	}else{								//george: F_CM3218_01
		CM3218_BacklightOn_Init();
		SetNowALSBrig();
	}
#elif ALS_EnDis == ALSRange
	if(UserData.bALSOnOff == OFF) {
    	UserSetBrightness();
	}else {  //if(UserData.ucALSMode == INDOOR || UserData.ucALSMode == OUTDOOR) {								//george: F_CM3218_01
		LS3101_ALSOnInit();
		SetNowALSBrig();
	}
#else	//Normal
	UserSetBrightness();
#endif	//#if ALS_EnDis == ENABLE


}

//******************************************************************************
// Prototype: 
//  void SetDBCBacklight(USHRT brightness)
// Parameters:
//  brightness : range is 0~1023
// Return:
//  None
// Purpose:
//  This is call-back function for ColorEngine library.
// Notes:
//  None
//******************************************************************************
void SetDBCBacklight(USHRT brightness)
{
    // Remap backlight is to avoid backlight shutdown
    brightness = MapDBCBacklight(brightness);
    SetBrightness(brightness);
}
//#endif //ENABLE_DBC == OFF

//******************************************************************************
// Prototype: 
//  void SetColorTemperature(UCHAR mode)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Set Color Temperature
// Notes:
//  None
//******************************************************************************
void SetColorTemperature(UCHAR mode)
{
    USHRT r,g,b;
    switch (mode) {
/*
        case CLRTMP_5000K:
            r = CalibData.uc5000KRGain;
            g = CalibData.uc5000KGGain;
            b = CalibData.uc5000KBGain;
            break;
*/
        case CLRTMP_6500K:
            r = CalibData.uc6500KRGain;
            g = CalibData.uc6500KGGain;
            b = CalibData.uc6500KBGain;
            break;
        case CLRTMP_7500K:
            r = CalibData.uc7500KRGain;
            g = CalibData.uc7500KGGain;
            b = CalibData.uc7500KBGain;
            break;
/*
        case CLRTMP_8200K:
            r = CalibData.uc8200KRGain;
            g = CalibData.uc8200KGGain;
            b = CalibData.uc8200KBGain;
            break;
*/
        case CLRTMP_9300K:
            r = CalibData.uc9300KRGain;
            g = CalibData.uc9300KGGain;
            b = CalibData.uc9300KBGain;
            break;
/*
        case CLRTMP_11500K:
            r = CalibData.uc11500KRGain;
            g = CalibData.uc11500KGGain;
            b = CalibData.uc11500KBGain;
            break;
*/
/*
        case CLRTMP_sRGB:
            r = CalibData.ucsRGBRGain;
            g = CalibData.ucsRGBGGain;
            b = CalibData.ucsRGBBGain;
            break;
*/
        case CLRTMP_USER:
        default:
            r = (USHRT)GetRGain255();
            g = (USHRT)GetGGain255();
            b = (USHRT)GetBGain255();
            break;
    };
    
    // To bypass the 3x3 matrix, we need to assign 0x100 to MTXAPI_SetRGBGain.
    // However, the max gain value in this function is 0xFF.
    // So, we plus one to achieve bypassing 3x3 matrix
    // Jude 2011/07/28
    MTXAPI_SetRGBGain(r + 1,g + 1,b + 1);
}
