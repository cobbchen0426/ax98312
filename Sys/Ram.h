/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/

#ifndef __RAM_H__
#define __RAM_H__

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************
#include "InputTiming.h"
#include "Typedef.h"

//******************************************************************************
// M A C R O   D E F I N I T I O N S
//******************************************************************************
typedef struct{
    UCHAR ucInputPort;
    UCHAR ucPortName;
}tINPUTPORT;

enum  InputPortNum {
  _0_Port,
  _1_Port,
  _2_Port,
  _3_Port,
  _4_Port,
};

typedef struct {
    UCHAR bHotKeySource : 1;
} tCUSTOM_SYS;

//******************************************************************************
// D A T A   T Y P E   D E F I N E S
//******************************************************************************

//******************************************************************************
// V A R I A B L E S   P R O T O T Y P E
//******************************************************************************
extern xdata InputTimingFormat InputTiming;
extern xdata NvramUserData UserData;
extern xdata NvramCalibData CalibData;
extern xdata NvramSystemData SystemData;
extern xdata PanelData UserPanelData;
extern xdata UCHAR ucADCPhase100;
extern xdata UCHAR ucVstart100;
extern xdata tCUSTOM_SYS Custom_System;
//===============================
extern xdata unsigned char 	OSD_state;                    		//140304 mike 
extern xdata unsigned char   OSD_color_level; 			//140429 mike 
extern xdata unsigned char   OSD_color_RGB;           		 //140509 mike 
extern xdata unsigned char  	Factory_key;               		//140304 mike 
extern xdata unsigned short  Factory_key_time;     		//140304 mike 
//===============================
//RS232
//gg extern xdata unsigned char 	ucUARTRxIn;                    		//140701 mike 

extern xdata unsigned char reserve_osd_inputsource;	//george

#if ENABLE_HDCP_TRIM_MODE == ON
extern xdata UCHAR ucEFUSE_ID;
extern xdata UCHAR ucEFUSETrimSucess;
#endif

//******************************************************************************
// F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
void RamInitialize(void);

#endif //__RAM_H__
