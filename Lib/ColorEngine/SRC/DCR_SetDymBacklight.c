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
#define DBC_MAX_BACKLIGHT      1023 /*!< The maximum PWM duty. */
#define DBC_MIN_BACKLIGHT      0    /*!< The minimum PWM duty. */
#define DBC_THD_BACKLIGHT_DIFF 6    /*!< The threshold of difference of previous and current PWM duty. */
#define DBC_THD_ABRUPT_CHANGE  ((DBC_MAX_BACKLIGHT-DBC_MIN_BACKLIGHT)>>2) /*!< The threshold of abrupt change of previous and current PWM duty. */
#define DBC_STEP_SIZE          1    /*!< The step size of adjustments of PWM duty. */

//******************************************************************************
// G L O B A L   V A R I A B L E S
//******************************************************************************

//******************************************************************************
// S T A T I C   V A R I A B L E S
//******************************************************************************
static xdata USHRT usTargetBacklight;  /*!< Target PWM duty. */
static xdata USHRT usCurrentBacklight; /*!< Current PWM duty. */

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
extern SetDBCBacklight(USHRT brightness);

//******************************************************************************
// F U N C T I O N   B O D Y S
//******************************************************************************

/**************************************************************************//**
 * Periodic routine of dynamic backlight.
 ******************************************************************************/
void DCR_SetDymBacklight(void)
{
    USHRT tmp;
    static UCHAR ucUpdateBK = 0;

    if (ulCurHisgrmTotal == 0)
        return;

    tmp = (ulCurHisgrmTotal-usCurHisgrm[0])*
          (DBC_MAX_BACKLIGHT-DBC_MIN_BACKLIGHT)/
          ulCurHisgrmTotal+DBC_MIN_BACKLIGHT;

    if (tmp != usTargetBacklight) {
        usTargetBacklight = tmp;
        if (usTargetBacklight < DBC_MIN_BACKLIGHT)
            usTargetBacklight = DBC_MIN_BACKLIGHT;
        else if (usTargetBacklight > DBC_MAX_BACKLIGHT)
            usTargetBacklight = DBC_MAX_BACKLIGHT;
    }

    if ((abs(usCurrentBacklight - usTargetBacklight) < DBC_THD_BACKLIGHT_DIFF) && (ucUpdateBK == 0))
        return;

    ucUpdateBK = 1;
    if (usCurrentBacklight != usTargetBacklight) {
        if (abs(usCurrentBacklight - usTargetBacklight) < DBC_THD_ABRUPT_CHANGE) {
            if (usCurrentBacklight < usTargetBacklight) {
                usCurrentBacklight += DBC_STEP_SIZE;
                if (usCurrentBacklight > usTargetBacklight)
                    usCurrentBacklight = usTargetBacklight;
            }
            else {
                usCurrentBacklight -= DBC_STEP_SIZE;
                if (usCurrentBacklight < usTargetBacklight)
                    usCurrentBacklight = usTargetBacklight;
            }
        }
        else {
            if (usCurrentBacklight < usTargetBacklight) {
                usCurrentBacklight = usTargetBacklight;
                ucUpdateBK = 0;
            }
            else {
                usCurrentBacklight -= DBC_STEP_SIZE;
            }
        }

        SetDBCBacklight(usCurrentBacklight);
    }
    else
        ucUpdateBK = 0;
}

/**************************************************************************//**
 * Reset PWM duty of DBC function to a specific value.
 * With this function, we can apply user brightness setting as a initiator of
 * PWM duty of DBC function to avoid flicking issue when turning on the DBC.
 * @param backlight User brightness setting. Value is 0 ~ 1023.
 ******************************************************************************/
void DCR_ResetDymBacklight(USHRT backlight)
{
    usCurrentBacklight = backlight;
    DCR_SetDymBacklight();
}
