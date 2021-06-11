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
enum _DDCCIOSDEVENT_ {
    DDCCIEVT_OSD_UPD_USR,
    DDCCIEVT_OSD_UPD_SYS,
    DDCCIEVT_OSD_UPD_TMG,
    DDCCIEVT_OSD_UPD_CAL,
    DDCCIEVT_NONOSD,
    NUM_DDCCI_OSD_EVENTS
} ;

enum _DDCCI_ACTION_ {
    DDCCIATN_UPD_USR,
    DDCCIATN_UPD_SYS,
    DDCCIATN_UPD_TMG,
    DDCCIATN_UPD_CAL,
    DDCCI_NON_ACTION,
    NUM_DDCCI_ACTION
} ;

//******************************************************************************
// G L O B A L   V A R I A B L E S
//******************************************************************************

//******************************************************************************
// S T A T I C   V A R I A B L E S
//******************************************************************************
static code UCHAR ucOSD2DDCCiEventTable[NUM_OSD_EVENTS] = {
    DDCCIEVT_OSD_UPD_USR, //OSDEVT_UPD_USR,
    DDCCIEVT_OSD_UPD_SYS, //OSDEVT_UPD_SYS,
    DDCCIEVT_OSD_UPD_TMG, //OSDEVT_UPD_TMG,
    DDCCIEVT_OSD_UPD_CAL, //OSDEVT_UPD_CAL,
    DDCCIEVT_NONOSD,      //OSD_NON_EVENT,
};

static code UCHAR ucDDCCiOSDActionTable[NUM_DDCCI_OSD_EVENTS] = {
    DDCCIATN_UPD_USR,   //DDCCIEVT_OSD_UPD_USR,
    DDCCIATN_UPD_SYS,   //DDCCIEVT_OSD_UPD_SYS,
    DDCCIATN_UPD_TMG,   //DDCCIEVT_OSD_UPD_TMG,
    DDCCIATN_UPD_CAL,   //DDCCIEVT_OSD_UPD_CAL,
    DDCCI_NON_ACTION    //DDCCIEVT_NONOSD,
};

//******************************************************************************
// E X T E R N A L   V A R I A B L E   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// S T A T I C   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
static void DDCCiTimerRoutine(void);

//******************************************************************************
// E X T E R N A L   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************


//******************************************************************************
// Prototype: 
//  void DDCCiActionDispatcher(UCHAR event)
// Parameters:
//  event   : event from system
// Return:
//  None
// Purpose:
//  DDDCCi action dispatcher
// Notes:
//  None
//******************************************************************************
void DDCCiActionDispatcher(UCHAR event)
{
    UCHAR act = DDCCI_NON_ACTION;
    
    if (GetGlobalEvent(event) == KEY_RELATED_EVENT) {
    }

    else if (GetGlobalEvent(event) == OSD_RELATED_EVENT) {
        event = GetLocalEvent(event);
        event = ucOSD2DDCCiEventTable[event];
        if (event != DDCCIEVT_NONOSD) {
            act = ucDDCCiOSDActionTable[event];
            //printf("DDCCiActionDispatcher->OSDEvent(%bx) Action(%bx)\n\r", event, act);
        }
    }

    else {
    }
    
    switch(act) {
        case DDCCIATN_UPD_USR:
        case DDCCIATN_UPD_SYS:
        case DDCCIATN_UPD_TMG:
        case DDCCIATN_UPD_CAL:
            DDCCiUpdateNotice();
            break;
        case DDCCI_NON_ACTION:
        default :
            break;
    }
}

//******************************************************************************
// Prototype: 
//  UCHAR DDCCiActionDemander(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Return gloabl event to system
// Notes:
//  None
//******************************************************************************
UCHAR DDCCiActionDemander(void)
{
    UCHAR evt = DDCCIEVT_NONE;
    
    DDCCiTimerRoutine();
    
    if (DDCCIUserUpdate()) {
        evt = DDCCIEVT_UPD_USR;
    } 
    else if (DDCCITmgUpdate()) {
        evt = DDCCIEVT_UPD_TMG;
    }
    else if (DDCCISysUpdate()) {
        evt = DDCCIEVT_UPD_SYS;
    }
    else if (DDCCICalUpdate()) {
        evt = DDCCIEVT_UPD_CAL;
    }
    else if (DDCCIPwrOn()) {
        evt = DDCCIEVT_PWR_ON;
    }
    else if (DDCCIPwrOff()) {
        evt = DDCCIEVT_PWR_OFF;
    }
    else if (DDCCIPwrSaving()) {
        evt = DDCCIEVT_PWR_SAVING;
    }
    
    return evt;
}

//******************************************************************************
// Prototype: 
//  void DDCCiTimerRoutine(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Periodic DDCCi actions
// Notes:
//  None
//******************************************************************************
void DDCCiTimerRoutine(void)
{
    CheckDDC2Bi();
}
