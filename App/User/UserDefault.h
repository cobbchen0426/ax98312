/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/
#ifndef __USER_DEFAULT_H__
#define __USER_DEFAULT_H__

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************
#include "Typedef.h"

//******************************************************************************
// G L O B A L   D E F I N I T I O N S
//******************************************************************************
#define MAXIMUM_BRIGHTNESS   100
#define MAXIMUM_CONTRAST     100
#define MAXIMUM_PHASE         63
#define MAXIMUM_CLR_TEMP       3 //FEFANJACKY
#define MAXIMUM_USER_RGAIN   100
#define MAXIMUM_USER_GGAIN   100
#define MAXIMUM_USER_BGAIN   100
#define MAXIMUM_USER_ROFFSET 100
#define MAXIMUM_USER_GOFFSET 100
#define MAXIMUM_USER_BOFFSET 100

#if  SET_SHOW_OSD_POSITION == SET_OSD_LEFT_TOP
	#define MAXIMUM_OSD_HPOS     100
	#define MAXIMUM_OSD_VPOS     100
#elif SET_SHOW_OSD_POSITION == SET_OSD_CENTER_TOP
	#define MAXIMUM_OSD_HPOS     100
	#define MAXIMUM_OSD_VPOS     100
#else	//(Normal)
	#define MAXIMUM_OSD_HPOS     100
	#define MAXIMUM_OSD_VPOS     100
#endif


#define MAXIMUM_OSD_TRANS      4
#define MAXIMUM_OSD_TIMER     60
#define MAXIMUM_OSD_ROT        1
#define MAXIMUM_OSD_LANG       7
#define MAXIMUM_OSD_LOCK       1
#define MAXIMUM_MUTE           1
#define MAXIMUM_VOLUME       100
#define MAXIMUM_INPUT_SRC      3
#define MAXIMUM_DCR_MODE       1
#define MAXIMUM_ASPECT_RATIO   3
#define MAXIMUM_OD_MODE        1
#define MAXIMUM_BF_MODE        4
#define MAXIMUM_2DTO3D_MODE    4
#define MAXIMUM_2DTO3D_MODE    4
#define MAXIMUM_2DTO3D_ADPT    1
#define MAXIMUM_2DTO3D_DEPTH   10
#define MAXIMUM_2DTO3D_VIEW    11
#define MAXIMUM_3D_LR_SWAP     1
#define MAXIMUM_ALSBV		   100	//george: F_ALSBV_04C1

#define MINIMUM_BRIGHTNESS     0
#define MINIMUM_CONTRAST       0
#define MINIMUM_PHASE          0
#define MINIMUM_CLR_TEMP       0
#define MINIMUM_USER_RGAIN     0
#define MINIMUM_USER_GGAIN     0
#define MINIMUM_USER_BGAIN     0
#define MINIMUM_USER_ROFFSET   0
#define MINIMUM_USER_GOFFSET   0
#define MINIMUM_USER_BOFFSET   0

#if  SET_SHOW_OSD_POSITION == SET_OSD_LEFT_TOP
	#define MINIMUM_OSD_HPOS       0
	#define MINIMUM_OSD_VPOS       0
#elif SET_SHOW_OSD_POSITION == SET_OSD_CENTER_TOP
	#define MINIMUM_OSD_HPOS       0
	#define MINIMUM_OSD_VPOS       92
#else	//(Normal)
	#define MINIMUM_OSD_HPOS       0
	#define MINIMUM_OSD_VPOS       0
#endif


#define MINIMUM_OSD_TRANS      0
#define MINIMUM_OSD_ROT        0
#define MINIMUM_OSD_TIMER      5
#define MINIMUM_OSD_LANG       0
#define MIMIMUM_OSD_LOCK       0
#define MINIMUM_MUTE           0
#define MINIMUM_VOLUME         0
#define MINIMUM_INPUT_SRC      0
#define MINIMUM_DCR_MODE       0
#define MINIMUM_ASPECT_RATIO   0
#define MINIMUM_OD_MODE        0
#define MINIMUM_BF_MODE        0
#define MINIMUM_2DTO3D_MODE    0
#define MINIMUM_2DTO3D_ADPT    0
#define MINIMUM_2DTO3D_DEPTH   0
#define MINIMUM_2DTO3D_VIEW    0
#define MINIMUM_3D_LR_SWAP     0
#define MINIMUM_ALSBV          0	//0	//george: F_ALSBV_04D1
#endif //__USER_DEFAULT_H__
