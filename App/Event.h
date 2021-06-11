/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/

#ifndef __EVENT_H__
#define __EVENT_H__

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************

//******************************************************************************
// M A C R O   D E F I N I T I O N S
//******************************************************************************
/*!
 * Global events.
 */
typedef enum _GLOBAL_EVENT_ {
    APP_RELATED_EVENT = 0x00,
    APPEVT_PW_ON = APP_RELATED_EVENT,
    APPEVT_PW_OFF,
    APPEVT_PW_SAVING,
    APPEVT_NO_SYNC,
    APPEVT_NO_CABLE,
    APPEVT_UNSTABLE,
    APPEVT_PRE,		//Perform routines before display
    APPEVT_NML,
    APPEVT_OOL,		//APPIsOutOfLimit()
    APPEVT_OOR,		//IsOutOfRange()
    APPEVT_NONE,
    APPEVT_END,
    KEY_RELATED_EVENT = 0x20,
    KEYEVT_PWR = KEY_RELATED_EVENT,
    KEYEVT_MENU,
    KEYEVT_AUTO,		//george 0x22
    KEYEVT_INPUT,
    KEYEVT_FUNC,
    KEYEVT_UP,
    KEYEVT_DOWN,
    KEYEVT_LEFT,
    KEYEVT_RIGHT,
    KEYEVT_FACT,
    KEYEVT_PWLOCK,
    KEYEVT_OSDLOCK,
    KEYEVT_TIMING_SWITCH,
    KEYEVT_DEMO,
    KEYEVT_NONE,		//george 0x2e
    KEYEVT_END,
    OSD_RELATED_EVENT = 0x40,
    OSDEVT_UPD_USR = OSD_RELATED_EVENT,
    OSDEVT_UPD_SYS,
    OSDEVT_UPD_TMG,
    OSDEVT_UPD_CAL,
    OSDEVT_NONE,
    OSDEVT_END,
    DDCCI_RELATED_EVENT = 0x60,
    DDCCIEVT_UPD_USR = DDCCI_RELATED_EVENT,
    DDCCIEVT_UPD_SYS,
    DDCCIEVT_UPD_TMG,
    DDCCIEVT_UPD_CAL,
    DDCCIEVT_PWR_ON,
    DDCCIEVT_PWR_OFF,
    DDCCIEVT_PWR_SAVING,
    DDCCIEVT_NONE,
    DDCCIEVT_END,
/*
	ALS_RELATED_EVENT = 0x70,	  	// 20150522 George Create for Ambient Light Sensor
	ALSEVT_FUN_ON = ALS_RELATED_EVENT,
	ALSEVT_FUN_OFF,
	APPEVT_NO_SYNC,
    APPEVT_UNSTABLE,
    APPEVT_NONE,
    ALSEVT_END,		*/
    NO_EVENT = 0xFF
} GlobalEvent;

#define NUM_APP_EVENTS      (APPEVT_END-APP_RELATED_EVENT) /*!< Number of APP events. */
#define NUM_KEY_EVENTS      (KEYEVT_END-KEY_RELATED_EVENT) /*!< Number of KEY events. */ 		//140318 mike  0x2f -0x20
#define NUM_OSD_EVENTS      (OSDEVT_END-OSD_RELATED_EVENT) /*!< Number of OSD events. */
#define NUM_DDCCI_EVENTS    (DDCCIEVT_END-DDCCI_RELATED_EVENT) /*!< Number of DDCCi events. */

#define GetGlobalEvent(e)   (e&0xE0) /*!< Get event type. */
#define GetLocalEvent(e)    (e&0x1F) /*!< Get event ID. */

//******************************************************************************
// D A T A   T Y P E   D E F I N E S
//******************************************************************************

//******************************************************************************
// V A R I A B L E S   P R O T O T Y P E
//******************************************************************************

//******************************************************************************
// F U N C T I O N   P R O T O T Y P E S
//******************************************************************************

#endif //__EVENT_H__
