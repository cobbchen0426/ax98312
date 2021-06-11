/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/

#ifndef __CEC_H__
#define __CEC_H__

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************
#include "Typedef.h"

//******************************************************************************
// M A C R O   D E F I N I T I O N S
//******************************************************************************

//******************************************************************************
// D A T A   T Y P E   D E F I N E S
//******************************************************************************
/*!
 * Data type of CEC request.
 */
typedef enum _CEC_REQUEST_ {
    CECREQ_NONE,          /*!< None. */
    CECREQ_POWERUP,       /*!< Power up request. */
    CECREQ_POWERDOWN,     /*!< Power down request. */
    CECREQ_ACTIVATE_SC,   /*!< Activating interface request. */
    CECREQ_INACTIVATE_SC, /*!< In-activating interface request. */
    CECREQ_DEVCTRL        /*!< Device control request. */
} CECRequest;

/*!
 * Data type of system action.
 */
typedef enum _CEC_ACTION_ {
    CECATN_NONE,        /*!< None. */
    CECATN_STANDBY,     /*!< Set system as standby. */
    CECATN_SET_LANGUAGE /*!< Set system language. */
} CECAction;

/*!
 * Data type of system language.
 */
typedef enum _CEC_LANGUAGE_ {
    CECLANG_ENGLISH,
    CECLANG_SPANISH,
    CECLANG_FRENCH,
    CECLANG_GERMAN,
    CECLANG_ITALIAN,
    CECLANG_PORTUGUESE,
    CECLANG_RUSSIAN,
    CECLANG_SCHINESE,
    CECLANG_SWEDISH,
    CECLANG_POLISH,
    CECLANG_CZECH,
    CECLANG_KOREAN,
    CECLANG_TCHINESE,
    CECLANG_JAPANESE,
    CECLANG_DUTCH,
    CECLANG_FINNISH,
    NUM_CEC_LANGUAGE
} CECLanguage;

#define CEC_USER_CTRL_POWER 0x40 /*!< Power command of CEC user control. */

//******************************************************************************
// V A R I A B L E S   P R O T O T Y P E
//******************************************************************************

//******************************************************************************
// F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
void InitialCEC(UCHAR CECPort);
void CECUpdateRefClock(void);
CECRequest CECHandler(void);
UCHAR CECGetActiveSC(void);
UCHAR CECGetDeviceCtlCode(void);
void CECSetStandby(void);
void CECSetOSDLanguage(CECLanguage lang);

#endif //__CEC_H__
