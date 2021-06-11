/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/

#ifndef __SCALER_PROFILE_H__
#define __SCALER_PROFILE_H__
/*! @file ScalerProfile.h
 * This file includes the scaler profile by SCALER_TYPE.
 */

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************
#include "ScalerType.h"

#if (SCALER_TYPE == NT68168)
#include "ScalerProfile_NT68168.h"
#elif (SCALER_TYPE == NT68668)
#include "ScalerProfile_NT68668.h"
#elif (SCALER_TYPE == NT68669)
#include "ScalerProfile_NT68669.h"
#elif (SCALER_TYPE == NT68660)
#include "ScalerProfile_NT68660.h"
#elif (SCALER_TYPE == NT68650)
#include "ScalerProfile_NT68650.h"
#elif (SCALER_TYPE == NT68620)
#include "ScalerProfile_NT68620.h"
#elif (SCALER_TYPE == NT68671)
#include "ScalerProfile_NT68671.h"
#elif (SCALER_TYPE == NT68672)
#include "ScalerProfile_NT68672.h"
#elif (SCALER_TYPE == NT68673)
#include "ScalerProfile_NT68673.h"
#elif (SCALER_TYPE == NT68674)
#include "ScalerProfile_NT68674.h"
#elif (SCALER_TYPE == NT68675)
#include "ScalerProfile_NT68675.h"
#elif (SCALER_TYPE == NT68676)
#include "ScalerProfile_NT68676.h"
#elif (SCALER_TYPE == NT68677)
#include "ScalerProfile_NT68677.h"
#elif (SCALER_TYPE == NT68678)
#include "ScalerProfile_NT68678.h"
#elif (SCALER_TYPE == NT68679)
#include "ScalerProfile_NT68679.h"
#elif (SCALER_TYPE == NT68776)
#include "ScalerProfile_NT68776.h"
#elif (SCALER_TYPE == NT68777)
#include "ScalerProfile_NT68777.h"
#elif (SCALER_TYPE == NT68778)
#include "ScalerProfile_NT68778.h"
#elif (SCALER_TYPE == NT68779)
#include "ScalerProfile_NT68779.h"
#elif (SCALER_TYPE == NT68750)
#include "ScalerProfile_NT68750.h"
#elif (SCALER_TYPE == NT68751)
#include "ScalerProfile_NT68751.h"
#elif (SCALER_TYPE == NT68752)
#include "ScalerProfile_NT68752.h"
#elif (SCALER_TYPE == NT68753)
#include "ScalerProfile_NT68753.h"
#elif (SCALER_TYPE == NT68360)
#include "ScalerProfile_NT68360.h"
#elif (SCALER_TYPE == NT68361)
#include "ScalerProfile_NT68361.h"
#elif (SCALER_TYPE == NT68652)
#include "ScalerProfile_NT68652.h"
#elif (SCALER_TYPE == NT68169)
#include "ScalerProfile_NT68169.h"
#elif (SCALER_TYPE == NT68661)
#include "ScalerProfile_NT68661.h"
#elif (SCALER_TYPE == NT68655)
#include "ScalerProfile_NT68655.h"
#elif (SCALER_TYPE == NT68770)
#include "ScalerProfile_NT68770.h"
#elif (SCALER_TYPE == NT68771)
#include "ScalerProfile_NT68771.h"
#elif (SCALER_TYPE == NT68772)
#include "ScalerProfile_NT68772.h"
#elif (SCALER_TYPE == NT68773)
#include "ScalerProfile_NT68773.h"
#elif (SCALER_TYPE == NT68774)
#include "ScalerProfile_NT68774.h"
#elif (SCALER_TYPE == NT68775)
#include "ScalerProfile_NT68775.h"
#elif (SCALER_TYPE == NT68781)
#include "ScalerProfile_NT68781.h"
#elif (SCALER_TYPE == NT68785)
#include "ScalerProfile_NT68785.h"
#elif (SCALER_TYPE == NT68850)
#include "ScalerProfile_NT68850.h"
#elif (SCALER_TYPE == NT68851)
#include "ScalerProfile_NT68851.h"
#elif (SCALER_TYPE == NT68852)
#include "ScalerProfile_NT68852.h"
#elif (SCALER_TYPE == NT68853)
#include "ScalerProfile_NT68853.h"
#elif (SCALER_TYPE == NT68854)
#include "ScalerProfile_NT68854.h"
#elif (SCALER_TYPE == NT68855)
#include "ScalerProfile_NT68855.h"
#elif (SCALER_TYPE == NT68856)
#include "ScalerProfile_NT68856.h"
#elif (SCALER_TYPE == NT68857)
#include "ScalerProfile_NT68857.h"
#elif (SCALER_TYPE == NT68859)
#include "ScalerProfile_NT68859.h"
#elif (SCALER_TYPE == NT68150)
#include "ScalerProfile_NT68150.h"
#elif (SCALER_TYPE == NT68370)
#include "ScalerProfile_NT68370.h"
#elif (SCALER_TYPE == NT68790)
#include "ScalerProfile_NT68790.h"
#else
#error "Please assign scaler type!"
#endif

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

#endif //__SCALER_PROFILE_H__
