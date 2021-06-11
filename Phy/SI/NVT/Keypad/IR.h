/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/
/******************************************************************************/
/*       KeyPad.h                                                             */
/*       Release Date:2010/01/21       Last Maintenance:2010/07/28            */
/*       Original Version:2.0.00       Last Version:2.0.01                    */
/*       Coding By: Mingyu Huang       Maintenance By: Mingyu Huang           */
/******************************************************************************/
#if IR_REMOT_CTL == ENABLE

#ifndef __IR_H__
#define __IR_H__

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************
#include "IR.h"

//******************************************************************************
// G L O B A L   D E F I N I T I O N S
//******************************************************************************

#define IR_FORMAT_NEC               0
#define IR_FORMAT_RC5               1
#define IR_FORMAT_RCA               2
#define IR_FORMAT_TOSHIBA      	    3
#define IR_FORMAT_MITSUBISHI        4

#define IR_FORMAT_SELECT     IR_FORMAT_RC5	//IR_FORMAT_NEC



#if IR_FORMAT_SELECT == IR_FORMAT_RC5
	#define RC5_ADDR		0x01C0	// RC5 Address	: 5bit_0x07 -> 16bit_0x01C0		//AXI_Remote-Controller_Common-Address: 0x07
	#define RC5_ADDR_MASK	0x07C0	// 0x07C0		: 0000  0111  1100  0000

	// RC5 CMD    : 6bit	//	
	#define RC5_CMD_MASK	0x003F
	#define RC5_CMD_POWER   0x00
	#define RC5_CMD_MENU	0x09
	#define RC5_CMD_UP		0x0E
	#define RC5_CMD_DOWN	0x0C
	#define RC5_CMD_AUTO	0x11	// EXIT
	#define RC5_CMD_INPUT	0x03
	
	#define IR_REPEAT_COUNTER    100 //3
#endif


//******************************************************************************
// E X T E R N A L   G L O B A L   V A R I A B L E S
//******************************************************************************


extern bit bIrDetect;

extern idata unsigned char  ucPrevIRKey;
extern idata unsigned char  ucCurIRKey;


//******************************************************************************
// E X T E R N A L   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
extern code unsigned char IR_KeyTab[];
	
extern void IR_Initalize( void );
//extern void ucIRReleaseCountCheck( void );
extern void IR_Process ( void );
extern unsigned char IR_GET_KEY( void );
extern UCHAR ScanIrKey( void );


#endif //__IR_H__

#endif
