/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/
#ifndef __NON_SUPPORT_TIMING_LIST_H__
#define __NON_SUPPORT_TIMING_LIST_H__

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************
#include "ModeTable.h"

//******************************************************************************
// G L O B A L   D E F I N I T I O N S
//******************************************************************************
typedef struct {
    UCHAR ucResolution;
    USHRT usNonSupportMode;
} NonSupportMode;

#define RES_1024X768_NONSUPPORT_LIST  {RES_1024X768 , 0xFFFF}
#define RES_1280X1024_NONSUPPORT_LIST {RES_1280X1024, 0xFFFF}
#define RES_1366X768_NONSUPPORT_LIST  {RES_1366X768 , 0xFFFF}
#define RES_1400X1050_NONSUPPORT_LIST {RES_1400X1050, 0xFFFF}
#define RES_1440X900_NONSUPPORT_LIST  {RES_1440X900 , 0xFFFF}
#define RES_1600X900_NONSUPPORT_LIST  {RES_1600X900 , 0xFFFF}
#define RES_1680X1050_NONSUPPORT_LIST {RES_1680X1050, _1400x1050_60HZ_RB}, \
                                      {RES_1680X1050, _1400x1050_60HZ}, \
                                      {RES_1680X1050, _1400x1050_75HZ}
#define RES_1920X1080_NONSUPPORT_LIST {RES_1920X1080, _1400x1050_60HZ_RB}, \
                                      {RES_1920X1080, _1400x1050_60HZ}, \
                                      {RES_1920X1080, _1400x1050_75HZ}
#define RES_1920X1200_NONSUPPORT_LIST {RES_1920X1200, 0xFFFF}

#endif //__NON_SUPPORT_TIMING_LIST_H__
