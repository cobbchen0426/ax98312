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
// M A C R O   D E F I N I T I O N S
//******************************************************************************

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
static UCHAR EventCollector(GlobalEvent evt);
static void EventDispatcher(UCHAR evt);

//******************************************************************************
// E X T E R N A L   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// F U N C T I O N   B O D Y S
//******************************************************************************

/**************************************************************************//**
 * Deal with various events that are posted by KEY, SYNC, TIMER and etc...
 ******************************************************************************/
/*
Rule:	1. ....  OSDBrightnessUp() -> SetOSDUpdUsrFlag();
		2. OSDActionDemander() =>  {if ('OSDUserUpdate()' -> IsOSDUpdUsr() -> ClearOSDUpdUsrFlag() ) } => Get evt = OSDEVT_UPD_USR;
	then
		1. (at APPActionDispatcher()) -> (from (GetGlobalEvent(event) == OSD_RELATED_EVENT)), Get APPEVT -> case APPATN_UPD_SYS: SetAPPUpdSysFlag();
		2. (at APPTimerRoutine()) -> if(IsAPPUpdUsr())  -> NvramWriteUserData(&UserData);

*/

void EventHandler(void)
{
    UCHAR evt;
	

    evt = EventCollector(APP_RELATED_EVENT);	//printf("EH-APP-Demander_%x_S\n", (USHRT)evt);			//150526 george
    EventDispatcher(evt);						//printf("\nEH-APP-Dispatcher_%x_E\n", (USHRT)evt);		//150526 george


    evt = EventCollector(KEY_RELATED_EVENT);	//printf("EH-KEY-Demander_%x_S\n", (USHRT)evt);			//150526 george
    EventDispatcher(evt);						//printf("EH-KEY-Dispatcher_%x_E\n", (USHRT)evt);		//150526 george


    evt = EventCollector(OSD_RELATED_EVENT);	//printf("EH-OSD-Demander_%x_S\n", (USHRT)evt);			//150526 george
    EventDispatcher(evt);						//printf("EH-OSD-Dispatcher_%x_E\n", (USHRT)evt);		//150526 george

//    evt = EventCollector(DDCCI_RELATED_EVENT);  //fefanjacky for ddcci not work
//    EventDispatcher(evt);
}

/**************************************************************************//**
 * Collect the event from OSD/KEY/APP/DDCCi.
 * @param evt The type of event to be collected.
 * @return The event.
 ******************************************************************************/
static UCHAR EventCollector(GlobalEvent evt)
{
    switch (evt) {
        case OSD_RELATED_EVENT:
            evt = OSDActionDemander();
            break;
        case KEY_RELATED_EVENT:
            evt = KeyActionDemander();
            break;
        case APP_RELATED_EVENT:
            evt = APPActionDemander();
            break;
        case DDCCI_RELATED_EVENT:
            evt = DDCCiActionDemander();
            break;
        default:
            evt = NO_EVENT;
            break;
    }

    return evt;
}

/**************************************************************************//**
 * Deliver global event to OSD/KEY/APP/DDCCi.
 * @param evt The event.
 ******************************************************************************/
static void EventDispatcher(UCHAR evt)
{
    OSDActionDispatcher(evt);	
//printf("ED-osd_E\n");	//150526 george
    KeyActionDispatcher(evt);	
//printf("ED-key_E\n");	//150526 george
    APPActionDispatcher(evt);
//printf("ED-app_E\n");	//150526 george
    DDCCiActionDispatcher(evt);	

}
