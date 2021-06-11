/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/

#ifndef __SYS_API_H__
#define __SYS_API_H__

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************
#include "ModeHandler.h"
#include "SyncHandler.h"

//******************************************************************************
// M A C R O   D E F I N I T I O N S
//******************************************************************************

//******************************************************************************
// D A T A   T Y P E   D E F I N E S
//******************************************************************************

//******************************************************************************
// V A R I A B L E S   P R O T O T Y P E
//******************************************************************************

//******************************************************************************
// F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
void SYSAPI_SetPowerOff(void);
void SYSAPI_SetPowerOn(void);
void SYSAPI_PowerSaving(void);
void SYSAPI_ForcePowerSaving(void);
void SYSAPI_WakeUp(void);
void SYSAPI_CheckSysPower(void);
void PanelPowerOnSequence(UCHAR force);
void PanelPowerOffSequence(void);
void SetBrightness(USHRT br);
//USHRT GetBrightness(void);
void SetBLPwmByInputVSync(UCHAR enable);
void SetVolume(USHRT value);
void SYSAPI_PerformHPDOn(void);
void SYSAPI_PerformHPDOff(UCHAR force);
#if ENABLE_SET_PWM_MAX_BUFFER == ON
void SetBrightnessPWMMax();
#endif

//CHIU
void SYSAPI_SetInverterVal(UCHAR val);

#endif //__SYS_API_H__
