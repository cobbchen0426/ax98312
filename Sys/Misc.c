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
static xdata USHRT usGlobalTimer[NUM_GLOBAL_TMR] = 0; /*!< A list of global timers. */

//******************************************************************************
// E X T E R N A L   V A R I A B L E   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// S T A T I C   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
static void UpdateGlobalTimer(void) small;

//******************************************************************************
// E X T E R N A L   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// F U N C T I O N   B O D Y S
//******************************************************************************

/**************************************************************************//**
 * Update all global timers.
 ******************************************************************************/
static void UpdateGlobalTimer(void) small
{
    static USHRT localtimer = 0;					//george: attention: why "static" use here ?
    USHRT count, tmp;
    UCHAR i;

    tmp = GetTimerTick();
    count = tmp - localtimer;						//george: differ => newtime-localtime
    localtimer = tmp;								//george: keep newtime-value

    for (i = 0; i < NUM_GLOBAL_TMR; i++) {
        if (count > usGlobalTimer[i]) {
            usGlobalTimer[i] = 0;
        }
        else {
            usGlobalTimer[i] -= count;
        }
    }
}

/**************************************************************************//**
 * Set a timer with ID.
 * All the IDs are listed in Misc.h.
 * @param id ID of global timer.
 * @param count Value of timer.
 ******************************************************************************/
void SetGlobalTimer(GlobalTmr id, USHRT count)
{
    UpdateGlobalTimer();
    usGlobalTimer[id] = count;
}

/**************************************************************************//**
 * Get the value of the timer with ID.
 * @param id ID of global timer.
 * @return Value of the timer.
 ******************************************************************************/
USHRT GetGlobalTimer(GlobalTmr id)
{
    UpdateGlobalTimer();
    return usGlobalTimer[id];
}

/**************************************************************************//**
 * Stall the system for "delay" ms.
 * @param delay Time for delay.
 ******************************************************************************/
void Sleep(USHRT delay) small
{
    USHRT temp;

    delay++; // Make sure more than 1 ms

    temp = GetTimerTick();
    while ((GetTimerTick()-temp) < delay) {
        ResetWDTimer();
    }
    UpdateGlobalTimer();
}
