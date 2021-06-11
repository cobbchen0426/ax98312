/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/
//150426 George (DBC, Dynamic Backlight Control)
//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************
#include "Include.h"

#if ENABLE_DBC == ON

#include "DBCData.c"

//******************************************************************************
// M A C R O   D E F I N I T I O N S
//******************************************************************************
#define DEFAULT_LIMIT 0x60

//******************************************************************************
// S T A T I C   V A R I A B L E S
//******************************************************************************
static xdata UCHAR ucDBCMaxPWMDuty = 0xFF;
static xdata UCHAR ucDBCMinPWMDuty = 0x00;
static xdata UCHAR ucDBCPrevMaxPWMDuty = 0xFF;
static xdata UCHAR ucDBCULFlag = 0x00;
static BOOL bDBCCtrl;
static UCHAR ucDBCEffective, ucDBCYAverage, ucPWMactive, ucDBCSceneYAvg;
#if IS_NT68770_SERIES || IS_NT68850_SERIES || IS_NT68655_SERIES || IS_NT68150_SERIES || IS_NT68790_SERIES
static xdata UCHAR ucDBCSceneChanged = 0x0;
static xdata UCHAR ucDBCPrevSceneChanged = 0x80;
#endif
//******************************************************************************
// G L O B A L   V A R I A B L E S
//******************************************************************************

//******************************************************************************
// S T A T I C   V A R I A B L E S
//******************************************************************************
    
//******************************************************************************
// E X T E R N A L   V A R I A B L E   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// S T A T I C   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
static void DBCLimitTracker(void);

//******************************************************************************
// E X T E R N A L   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// Prototype: 
//  void InitDBC(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Load DBC table to scaler
// Notes:
//  None
//******************************************************************************
void InitDBC(void)
{
    DBCAPI_LoadTable(&DBCTable);
    DBCAPI_ConfigPWM(BRIGHTNESS_FR_PWM_FREQ, DBC_DIV_4X);
#if IS_NT68770_SERIES || IS_NT68850_SERIES || IS_NT68655_SERIES || IS_NT68661_SERIES || IS_NT68150_SERIES || IS_NT68790_SERIES
    DBCAPI_SetSavingRatio(DBC_SAVING_MODE_2,0);
    DBCAPI_SetPWMAdjustment(4, 1);
#else
    DBCAPI_SetSavingRatio(DBC_SAVING_MODE_2,0);
    DBCAPI_SetPWMAdjustment(0, 1);
#endif
    DBCAPI_SetPWMInvert(BKL_PWM_POL ? FALSE : TRUE);
    DBCAPI_SetDistortion(0x0F);
    ucDBCPrevMaxPWMDuty = ucDBCMaxPWMDuty;
    DBCAPI_SetDBCMinMax(ucDBCMinPWMDuty, ucDBCMaxPWMDuty);
#if ENABLE_DBC_HW_DEBOUNCE == ON
#if IS_NT68770_SERIES || IS_NT68850_SERIES || IS_NT68655_SERIES || IS_NT68150_SERIES || IS_NT68790_SERIES
    DBCAPI_SetDebouncingMode(5,5);
#else
    DBCAPI_SetDebouncingMode(4,4);
#endif
#endif

#if IS_NT68770_SERIES || IS_NT68850_SERIES || IS_NT68655_SERIES || IS_NT68150_SERIES || IS_NT68790_SERIES
    DBCAPI_SetNLGain(2);
    //DBCAPI_EnableNLGain();
    DBCAPI_SetNLGainBreak(0, 1);	// Mars Adjust for on/off difference luma
    DBCAPI_SetLUTGray2PWMLim(0);
    DBCAPI_SetLUTGray2GainLim(0);
    DBCAPI_SetLUTRef(1);
    SC_OSD_FRAME2_FUNC_CTRL |= BIT2;
#endif
    // Hotfix to solve the issue of temporal abnormal image caused by abnormal DBC data gain after AC on.
    DBCAPI_EnableDBC();
    WaitDisVSync();
    DBCAPI_DisableDBC();
}

//******************************************************************************
// Prototype: 
//  void EnableDBC(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Enable DBC function
// Notes:
//  None
//******************************************************************************
void EnableDBC(void)
{
#if IS_NT68770_SERIES || IS_NT68850_SERIES || IS_NT68655_SERIES || IS_NT68661_SERIES || IS_NT68150_SERIES || IS_NT68790_SERIES
    SC_DBC_EXT_CTRL &= ~(BIT7);
    DBCAPI_SetDistortion(0x00);
    DBCAPI_SetSavingRatio(DBC_SAVING_MODE_MAX,0);
#else
    DBCAPI_SetDistortion(0x00);
    DBCAPI_SetSavingRatio(DBC_SAVING_MODE_2,0);
#endif
#if ENABLE_DBC_HW_DEBOUNCE == OFF
    ClearDBCCounter();
#endif
    // Disable abrupt change to avoid image flicking when scene changed or turning off DPS.
    //DBCAPI_EnableAbruptChange(8);
#if IS_NT68770_SERIES || IS_NT68850_SERIES || IS_NT68655_SERIES || IS_NT68150_SERIES || IS_NT68790_SERIES
    ucDBCMaxPWMDuty = GetBrightness1023() >> 2;
    ucDBCMinPWMDuty = 0;
    ucDBCPrevMaxPWMDuty = ucDBCMaxPWMDuty;
    DBCAPI_SetDBCMinMax(ucDBCMinPWMDuty, ucDBCMaxPWMDuty);
	  SC_DBC_PWM_LUT_LIM = 0x40;
	  SC_DBC_GRAY_LUT_LIM = 0x40;
    DBCAPI_EnableAbruptChange(8);
	  DBCAPI_SetAbruptStep(1);	// Mars Add for abrupt change step
	  DBCAPI_SetAbruptMode(1);
    DBCAPI_SetPWMAdjustment(0, 1);
#else
    DBCAPI_DisableAbruptChange();
    ucDBCMaxPWMDuty = GetBrightness1023() >> 2;
    ucDBCMinPWMDuty = MIN_BACKLIGHT_VALUE >> 2;
    ucDBCPrevMaxPWMDuty = ucDBCMaxPWMDuty;
    DBCAPI_SetDBCMinMax(ucDBCMinPWMDuty, ucDBCMaxPWMDuty);
#endif 

#if DBC_TABLE_GENERATION != 0
    DBCLimitTracker();
#endif
    
    // Force the following order of enabling DBC function to avoid temporal image flicking
    DBCAPI_EnableDBC();
    DBCAPI_EnableDBCPWM(BKL_PWM_PORT, BKL_PWM_OUTPUT_PIN);
    DBCAPI_EnableRGBCompensation();
#ifdef PWM_REF_DBC
	SetReferenceDBCDuty(BKL_PWM_PORT, TRUE);
#endif
    ucDBCULFlag = BIT7 | BIT0;
}

//******************************************************************************
// Prototype: 
//  void DisableDBC(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Disable DBC function
// Notes:
//  None
//******************************************************************************
void DisableDBC(void)
{
    DBCAPI_DisableDBC();
//  DBCAPI_DisableDBCPWM(BKL_PWM_OUTPUT_PIN);
    DBCAPI_DisableDBCPWM(BKL_PWM_PORT,BKL_PWM_OUTPUT_PIN);

    DBCAPI_DisableRGBCompensation();
    DBCAPI_DisableAbruptChange();
#ifdef PWM_REF_DBC
    SetReferenceDBCDuty(BKL_PWM_PORT, FALSE);
#endif
}

//******************************************************************************
// Prototype: 
//  void DisableDBCSmooth(UCHAR reset)
// Parameters:
//  reset : flag to reset parameters
// Return:
//  None
// Purpose:
//  Disable DBC function smoothly
// Notes:
//  None
//******************************************************************************
void DisableDBCSmooth(UCHAR reset)
{
#if IS_NT68770_SERIES || IS_NT68850_SERIES || IS_NT68655_SERIES || IS_NT68150_SERIES || IS_NT68790_SERIES
	static BOOL delay_off_flag = FALSE;
	static UCHAR CurTarget;
	if (reset) {
		delay_off_flag = TRUE;
		CurTarget = 0;
	}
	if (delay_off_flag) {
		SC_DBC_EXT_CTRL &= ~(BIT6);	
		DBCAPI_SetPWMAdjustment(0, 2);
		DBCAPI_SetDistortion(0);
		DBCAPI_SetSavingRatio(0,0);
		DBCAPI_DisableNLGain();
		CurTarget++;
		SC_DBC_PWM_LUT_LIM = CurTarget;
		SC_DBC_GRAY_LUT_LIM = CurTarget;
		if(CurTarget == 0xFF)
		{
			//SC_PWMA_CTRL4 = SC_DBC_PWM_ACT;
/*
			SC_DBC_CTRL &= ~(BIT0|BIT1);			// 0x430 	DBC Disable
			SC_LEDDIMMING_CTRL &= ~(BIT7);	// 0xE12
*/
                        DisableDBC();
			delay_off_flag = FALSE;
			CurTarget = 0;
			SC_DBC_PWM_LUT_LIM = CurTarget;
			SC_DBC_GRAY_LUT_LIM = CurTarget;
		}
	}
#else
    static BOOL delay_off_flag = FALSE;
    static UCHAR prev_pmw;
    USHRT tmp_pwm;
    
    if (reset) {
        // Hotfix to avoid image flick when switching PWM between PWM_A/B and DBC.
        //  a) Force PWM duty of PWM_A/B being same with the duty of DBC PWM.
        //  b) Reseting PWM on VSync must be turned on.
        prev_pmw = DBCAPI_GetActPWM();
        tmp_pwm = ((USHRT)DBCAPI_GetPWMOffset() + prev_pmw) % 256;
        tmp_pwm = (ULONG)tmp_pwm * 1023 / 255;
        SmoothScalerPWM(BKL_PWM_PORT, 0, 0);
        SetBrightness(tmp_pwm);
        WaitDisVSync();
//      DBCAPI_DisableDBCPWM(BKL_PWM_OUTPUT_PIN);
	DBCAPI_DisableDBCPWM(BKL_PWM_PORT,BKL_PWM_OUTPUT_PIN);
        SmoothScalerPWM(BKL_PWM_PORT, 3, 2);
        UserSetBrightness();
        // Hotfix to avoid image flick before turning off DBC data gain function.
        //  a) Use DBC PWM minimum limitation to force DBC data gain turning to default smoothly.
        //  b) Toggle saving ratio to force DBC varing PWM duty to minimum limitation.
        DBCAPI_SetPWMAdjustment(0, 2);
        DBCAPI_SetDBCMinMax(0xFF, 0xFF);
        DBCAPI_SetDistortion(0x00);
        delay_off_flag = TRUE;
        SetGlobalTimer(GLOBAL_TMR_DBC_OFF, GBTM_DBC_OFF);
    }

    if (delay_off_flag) {
        if ((GetGlobalTimer(GLOBAL_TMR_DBC_OFF) == 0) ||
            (DBCAPI_GetActPWM() == 0xFF)) {
            DisableDBC();
            delay_off_flag = FALSE;
        }
        else if (prev_pmw == DBCAPI_GetActPWM()){
            // Toggle saving ratio if active PMW doesn't move to 0xFF.
            DBCAPI_SetSavingRatio(DBC_SAVING_MODE_MAX,0);
            WaitDisVSync();
            DBCAPI_SetSavingRatio(DBC_SAVING_MODE_2,0);
            WaitDisVSync();
        }
        else {
            prev_pmw = DBCAPI_GetActPWM();
        }
    }
#endif
}

#if ENABLE_DBC_HW_DEBOUNCE == OFF
//******************************************************************************
// Prototype: 
//  void AntiNoiseDBC(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  F/W based noise debounce function.
// Notes:
//  None
//******************************************************************************
#define DBC_ADJ_ON                  1
#define DBC_ADJ_OFF                 0
#define DBC_AVERAGE_NOISE_LEVEL     2
#define DBC_EFFECTIVE_NOISE_LEVEL   5
#define DBC_PWM_NOISE_LEVEL         1
#define DBC_SCENE_CHANGED_LEVEL     5

void AntiNoiseDBC(void)
{
    UCHAR effective, average, pwm_active;

    average = DBCAPI_GetAverageY();
    effective = DBCAPI_GetEffectiveColor();
    pwm_active = DBCAPI_GetActPWM();

    if ((ucDBCULFlag & BIT7) != 0) {
        ucDBCULFlag &= ~BIT7;
        ucDBCSceneYAvg = 0;
        DCR_UpdateHistogram(TRUE);
    }
    else if (DCR_UpdateHistogram(FALSE)) {
        UCHAR i;

        if (DCR_IsSceneChanged() || 
            (abs(ucDBCSceneYAvg - average) > DBC_SCENE_CHANGED_LEVEL))  {
            UCHAR tmp_flag = ucDBCULFlag;
            USHRT total, sum;

            DCR_UpdatePrevHistogram();
            ucDBCSceneYAvg = average;

            // Check the percentage of high gray level (Y14~Y15).
            // If the percentage is greater than 10.9375%, we guess the the content is bright majority and set distortion as 0.
            sum = 0;
            ucDBCULFlag &= ~BIT2;
            for (i = 14; i < BF_IG_PARTITIONS; i++) {
                sum += DCR_GetHistogram(i);
            }
            total = (DCR_GetTotalHistogram() >> 3) - (DCR_GetTotalHistogram() >> 6);
            if (sum < total) {
                ucDBCULFlag |= BIT2;
            }

            // Check the percentage of high gray level (Y12~Y15).
            // If the percentage is greater than 25%, we guess the the content is bright majority and set distortion as 0.
            sum = 0;
            ucDBCULFlag &= ~BIT1;
            for (i = 12; i < BF_IG_PARTITIONS; i++) {
                sum += DCR_GetHistogram(i);
            }
            total = DCR_GetTotalHistogram() >> 2;
            if (sum < total) {
                ucDBCULFlag |= BIT1;
            }

            // Check if the majority of content are single gray or not.
            // We define the threshold as 80% of total histogram
            ucDBCULFlag &= ~BIT0;
            total = DCR_GetTotalHistogram() / 10;
            for (i = 1; i < BF_IG_PARTITIONS; i++) {
                sum = (DCR_GetHistogram(i) + DCR_GetHistogram(i - 1)) / total;
                if (sum > 7) {
                    ucDBCULFlag |= BIT0;
                    break;
                }
            }

            if (ucDBCULFlag != tmp_flag) {
                ucDBCYAverage = 0x00;
            }
        }
    }

    if (abs(ucDBCYAverage - average) < DBC_AVERAGE_NOISE_LEVEL) {
        // Y average no change
        if (bDBCCtrl == TRUE) {
            if (abs(pwm_active - ucPWMactive) > DBC_PWM_NOISE_LEVEL) {
                ucPWMactive = pwm_active;
                SetGlobalTimer(GLOBAL_TMR_DBC_STABLE, GBTM_DBC_STABLE);
            }
            else if (GetGlobalTimer(GLOBAL_TMR_DBC_STABLE) == 0) {
                bDBCCtrl = FALSE;
                DBCAPI_SetPWMAdjustment(0, DBC_ADJ_OFF);
            }
        }

        if (abs(ucDBCEffective - effective) > DBC_EFFECTIVE_NOISE_LEVEL) {
            bDBCCtrl = TRUE;
            ucDBCEffective = effective;
            DBCAPI_SetPWMAdjustment(0, DBC_ADJ_ON);
            SetGlobalTimer(GLOBAL_TMR_DBC_STABLE, GBTM_DBC_STABLE);
        }
    }
    else {
        bDBCCtrl = TRUE;
        ucDBCYAverage = average;
        DBCAPI_SetPWMAdjustment(0, DBC_ADJ_ON);
        SetGlobalTimer(GLOBAL_TMR_DBC_STABLE, GBTM_DBC_STABLE);

        // Dynamic adjusting distortion to fit the power consumption spec and
        // lumimance spec of LGE
        if (ucDBCYAverage > 0xE0) {
            DBCAPI_SetDistortion(0x00);
            DBCAPI_SetSavingRatio(DBC_SAVING_MODE_MAX, 3);
        }
        else {
            if ((ucDBCULFlag & BIT1) && (ucDBCULFlag & BIT2)) {
                DBCAPI_SetDistortion(0x0F);
                DBCAPI_SetSavingRatio(DBC_SAVING_MODE_2, 3);
            }
            else {
                DBCAPI_SetDistortion(0x03);
                DBCAPI_SetSavingRatio(DBC_SAVING_MODE_MAX, 3);
            }
        }
    }
}

//******************************************************************************
// Prototype:
//  void ClearDBCCounter(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Clear DBC counter & reset status
// Notes:
//  None
//******************************************************************************
void ClearDBCCounter(void)
{
    ucDBCYAverage = 0;
    ucPWMactive = 0;
    ucDBCEffective = 0;
    bDBCCtrl = TRUE;
    DBCAPI_SetPWMAdjustment(0, DBC_ADJ_ON);
    SetGlobalTimer(GLOBAL_TMR_DBC_STABLE, GBTM_DBC_STABLE);
}
#endif //ENABLE_DBC_HW_DEBOUNCE == OFF

//******************************************************************************
// Prototype: 
//  void DBCBrightnessTracker(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Tracking user brightness and set min/max DBC PWM duty
// Notes:
//  None
//******************************************************************************
void DBCBrightnessTracker(void)
{
    UCHAR tmp_pwm;

    ucDBCMaxPWMDuty = GetBrightness1023() >> 2;
    ucDBCMinPWMDuty = MIN_BACKLIGHT_VALUE >> 2;

    if (ucDBCULFlag & BIT0) {
        tmp_pwm = ucDBCMaxPWMDuty;
    }
    else {
        tmp_pwm = (USHRT)ucDBCMaxPWMDuty * 85 / 100;
    }

    if (tmp_pwm < ucDBCMinPWMDuty) {
        tmp_pwm = ucDBCMinPWMDuty;
    }

    if (ucDBCPrevMaxPWMDuty != tmp_pwm) {
        if (ucDBCPrevMaxPWMDuty > tmp_pwm) {
            ucDBCPrevMaxPWMDuty--;
        }
        else {
            ucDBCPrevMaxPWMDuty++;
        }
        DBCAPI_SetDBCMinMax(ucDBCMinPWMDuty, ucDBCPrevMaxPWMDuty);
    #if DBC_TABLE_GENERATION != 0
        DBCLimitTracker();
    #endif

    #if ENABLE_DBC_HW_DEBOUNCE == OFF
        ClearDBCCounter();
    #endif
        WaitDisVSync();
    }
}

#if DBC_TABLE_GENERATION != 0
/**************************************************************************//**
 * Tracking DBC gray2pwm and gray2gain limit to min duty
 ******************************************************************************/
static void DBCLimitTracker(void)
{
    UCHAR i;
    static UCHAR ucDBCPrevLimit = DEFAULT_LIMIT;
    static UCHAR ucDBCPrevMimPWMDuty = MIN_BACKLIGHT_VALUE >> 2;
    
    if (SC_DBC_PWM_MIN > ucDBCPrevMimPWMDuty) { //search up from ucDBCPrevLimit
        for (i = ucDBCPrevLimit; i < 0xFF; i++) {
            if (DBCTable.ucYGrayToLum[i] >= SC_DBC_PWM_MIN) {
                ucDBCPrevLimit = i;
                break;
            }
        }
    }
    else { //search down from ucDBCPrevLimit
        for (i = ucDBCPrevLimit; i >= DEFAULT_LIMIT; i--) {
            if (DBCTable.ucYGrayToLum[i] < SC_DBC_PWM_MIN) {
                ucDBCPrevLimit = i + 1;
                break;
            }
        }
    }
    if (i <= DEFAULT_LIMIT) { //make new ucDBCPrevLimit always no less than default limit
        ucDBCPrevLimit = DEFAULT_LIMIT;
    }
    DBCAPI_SetGray2PwmLim(ucDBCPrevLimit);
    DBCAPI_SetGray2GainLim(ucDBCPrevLimit);
    ucDBCPrevMimPWMDuty = SC_DBC_PWM_MIN;
}
#endif
#else
void ForDBCCompilerCodePass(void)
{
  code UCHAR temp[]={0x00};
  UCHAR i;
  i = temp[0];
}
#endif //ENABLE_DBC == ON
