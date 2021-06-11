/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/
#ifndef __KEY_CTRL_H__
#define __KEY_CTRL_H__

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************
#include "Typedef.h"

//******************************************************************************
// G L O B A L   D E F I N I T I O N S
//******************************************************************************
#define KEY_HOLD_TIME           500
#define KEY_REPEAT_TIME         50
#define KEY_LONG_PRESS_TIME     2000
//******************************************************************************
// G L O B A L   V A R I A B L E S
//******************************************************************************
#if Key_Debug == ENABLE
extern UCHAR GGKeyCode;	//150526 george test
extern BOOL bGeorge;	//150429 George test
#endif
//******************************************************************************
// E X T E R N A L   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
extern void KeyActionDispatcher(UCHAR event);
extern UCHAR KeyActionDemander(void);
extern void KeySetRepeatEvent(UCHAR evt, UCHAR rpt);
extern void KeySetLockEvent(UCHAR evt, UCHAR lock);
extern void KeySetHoldEvent(UCHAR evt, UCHAR hold);
extern void KeySetMFuncEvent(UCHAR major, UCHAR minor);
extern void KeySetHoldTime(USHRT time);
extern void KeySetRepeatTime(USHRT time);
extern void KeySetLongPressTime(USHRT time);

#endif //__KEY_CTRL_H__
