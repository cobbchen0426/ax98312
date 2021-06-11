/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/

#ifndef __MISC_H__
#define __MISC_H__

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************
#include "Include.h"

//******************************************************************************
// M A C R O   D E F I N I T I O N S
//******************************************************************************

//******************************************************************************
// D A T A   T Y P E   D E F I N E S
//******************************************************************************
/*!
 * Data type of the ID of global timers.
 */
typedef enum _GLOBAL_TMR_{
    GLOBAL_TMR_BUZZER_TIME,    /*!< Timer for buzzer.  */
    GLOBAL_TMR_DATA_UPDATE,    /*!< Timer for data update. */
    GLOBAL_TMR_LED_FLASH,      /*!< LED blinking timer. */
    GLOBAL_TMR_LOCAL,          /*!< Local timer. */
    GLOBAL_TMR_LOGO_TIMEOUT,   /*!< Logo timeout timer. */
    GLOBAL_TMR_OSD_TIMEOUT,    /*!< OSD timeout timer. */
    GLOBAL_TMR_PANEL_ONOFF,    /*!< Timer for panel power on/off sequence.  */
    GLOBAL_TMR_POT_CNT,        /*!< Timer for POT function. */
    GLOBAL_TMR_APPSYNC_STABLE, /*!< Sync stable timer in APP. */
    GLOBAL_TMR_PWR_SAVING,     /*!< Timer for power saving. */
    GLOBAL_TMR_DBC_STABLE,     /*!< Timer for DBC function. */
    GLOBAL_TMR_DBC_OFF,        /*!< Timer for DBC function. */
    GLOBAL_TMR_HDMI_FS_MUTE,   /*!< Timer for HDMI audio sampling rate detection. */
    GLOBAL_TMR_MMU_ECC,        /*!< Timer for MMU error detection. */
    GLOBAL_TMR_AMD_3D,         /*!< Timer for AMD 3D detection. */
    GLOBAL_TMR_USR1,           /*!< User defined timer 1. */
    GLOBAL_TMR_USR2,           /*!< User defined timer 2. */
    GLOBAL_TMR_HPD,            /*!< Hot Plug Pull Low timers */
    GLOBAL_TMR_MHL_HPD,      /*!< MHL ClrHPD and SetHPD timer */
    GLOBAL_TMR_PWM_MAX_UPDATE,  /*!< Brightness Set Max timer */
    GLOBAL_TMR_CHECK_AUX,       /*!< Aux checking workaroud for 850 cut3 */    
    NUM_GLOBAL_TMR             /*!< Number of global timers. */
} GlobalTmr;

//******************************************************************************
// V A R I A B L E S   P R O T O T Y P E
//******************************************************************************

//******************************************************************************
// F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
void Sleep(USHRT delay) small;
void SetGlobalTimer(GlobalTmr id, USHRT count);
USHRT GetGlobalTimer(GlobalTmr id);

#endif //__MISC_H__
