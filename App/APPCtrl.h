/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/
#ifndef __APP_CTRL_H__
#define __APP_CTRL_H__

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************
#include "Typedef.h"

//******************************************************************************
// G L O B A L   D E F I N I T I O N S
//******************************************************************************
typedef enum _APP_ACTION_ {
    APPATN_PWR_ONOFF,
    APPATN_PWR_ON,
    APPATN_PWR_OFF,
    APPATN_PWR_SAVING,
    APPATN_FORCE_PWR_SAVING,
    APPATN_WAKEUP,
    APPATN_CH_SOURCE,
    APPATN_QUICK_ONOFF,
    APPATN_UPD_USR,
    APPATN_UPD_SYS,
    APPATN_UPD_TMG,
    APPATN_UPD_CAL,
    APPATN_SET_FACTORY,
    APPATN_TIMING_SWITCH,
    APPATN_SET_DEMO,
    APP_NON_ACTION
} APPAction;

typedef enum _APP_PWR_STATE_ {
    APPSTATE_PWR_ONOFF,
    APPSTATE_PWR_OFF,
    APPSTATE_PWR_ON,
    APPSTATE_PWR_SAVING,
    APPSTATE_FORCE_PWR_SAVING,
    APPSTATE_WAKEUP
} APPPwrState;

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

//******************************************************************************
// E X T E R N A L   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
extern void APPInitSystem(void);
extern void APPActionDispatcher(UCHAR event);
extern UCHAR APPActionDemander(void);

// Functions for OSD to ask APP to re-send APP-level sync event
extern void APPResendAppSync(void);

// Functions for the scalers support H/W CEC
extern void APPRequestCECAct(UCHAR act);

// Functions for the scalers support internal audio test pattern
extern void APPSetAudioBuzzer(USHRT time);
extern void APPCountAudioBuzzer(void);
extern UCHAR CheckTotalPortNum(void);
extern void Custom_System_Init(void);


/* extern void UART_NvRamUpdate(void);  */		//George



#if IR_REMOT_CTL == ON
	extern BOOL IsAPPLogo(void);
#endif

#endif //__APP_CTRL_H__
