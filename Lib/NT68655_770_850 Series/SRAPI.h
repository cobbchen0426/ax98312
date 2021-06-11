/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/
#ifndef __SRAPI_H__
#define __SRAPI_H__

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************
#include "ScalerType.h"
#include "Typedef.h"

//******************************************************************************
// M A C R O   D E F I N I T I O N S
//******************************************************************************

//******************************************************************************
// D A T A   T Y P E   D E F I N E S
//******************************************************************************
/*!
 * Data type of SR demo zone mode.
 */
typedef enum _SR_DEMO_REGION_ {
    SR_DEMO_LEFT,  /*!< Left-side demo mode. */
    SR_DEMO_RIGHT  /*!< Right-side demo mode. */
} SRDemoRegion;

/*!
 * Data type of MDN.
 */
typedef struct _MDN_BLOCK_ {
    UCHAR ucCutOffTH;   /*!< ? */
    UCHAR ucCutOffSlop; /*!< ? */
    USHRT usVarTH;      /*!< ? */
    UCHAR ucHiVarGain;  /*!< ? */
    UCHAR ucLoVarGain;  /*!< ? */
} MDNBlock;

/*!
 * Data type of USM region.
 */
typedef struct _USM_REGION_BLOCK_ {
    UCHAR ucCutOffTH;  /*!< ? */
    USHRT usVarTH;     /*!< ? */
    UCHAR ucHiVarGain; /*!< ? */
    UCHAR ucLoVarGain; /*!< ? */
} USMRegionBlock;

/*!
 * Data type of USM gain.
 */
typedef struct _USM_GAIN_BLOCK_ {
    UCHAR ucGain;      /*!< ? */
    USHRT usVarTH;     /*!< ? */
    UCHAR ucHiVarGain; /*!< ? */
    UCHAR ucLoVarGain; /*!< ? */
} USMGainBlock;

//******************************************************************************
// V A R I A B L E S    P R O T O T Y P E
//******************************************************************************

//******************************************************************************
// F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
void SRAPI_InitSR(void);
void SRAPI_TurnOnOff(UCHAR on);
//BOOL SRAPI_IsTurnOn();
void SRAPI_SetMDNFilter(MDNBlock * ptr);
void SRAPI_SetUSMFilter(USMRegionBlock *ptr_rgn, USMGainBlock *ptr_gain);
void SRAPI_SetUSMLPThreshold(USHRT threshold);
void SRAPI_SetUSMDarkLimit(UCHAR darklimit);
void SRAPI_SetDemoRegion(UCHAR on, SRDemoRegion region ,USHRT value);
void SRAPI_SetHtotal(USHRT htotal);
void SRAPI_SetCaptureSize(USHRT width, USHRT height);
void SRAPI_SRBlockEnable(void);
void SRAPI_SRBlockDisable(void);

#endif //__SRAPI_H__
