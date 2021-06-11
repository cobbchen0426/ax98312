/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/
#ifndef __GLOBAL_TIMER_DEF_H__
#define __GLOBAL_TIMER_DEF_H__

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************
#include "ModelCfg.h"

//******************************************************************************
// G L O B A L   D E F I N I T I O N S
//******************************************************************************
#define GBTM_DATA_UPDATE       1000
#define GBTM_POT_CNT           20000
#define GBTM_LED_FLASH         50
#define GBTM_FACT_BURNIN       2000
#define GBTM_APPSYNC_STABLE    6000//(SYNCSRC_TIME_ANALOG1+SYNCSRC_TIME_DIGITAL0+SYNCSRC_TIME_DIGITAL1+SYNCSRC_TIME_DP)
#define GBTM_NOSYNC_PWR_SAVING 6000//(GBTM_APPSYNC_STABLE+2000) //FEFANJACK REMOVE +2000 FOR DP-MODE POWERSAVING NOT RESTART 
#define GBTM_OOR_PWR_SAVING    60000 
#define GBTM_LOGO_TIMEOUT      3000
#define GBTM_PANEL_ONOFF       UserPanelData.usPowerOffOnPanelTime
#define GBTM_DDCCI_BUS_TIMEOUT 1000
#define GBTM_DBC_STABLE        300
#define GBTM_DBC_OFF           2000

#define GBTM_ALS_UPDATE        3000	//george

#endif //__GLOBAL_TIMER_DEF_H__
