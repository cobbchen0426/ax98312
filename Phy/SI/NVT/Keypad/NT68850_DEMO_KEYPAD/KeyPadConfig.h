/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/
#ifndef __KEYPAD_CONFIG_H__
#define __KEYPAD_CONFIG_H__

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************
#include "Board.h"
#include "Typedef.h"

//******************************************************************************
// G L O B A L   D E F I N I T I O N S
//******************************************************************************
/*******************************************************************************
                         Specific ADC code of AD key
*******************************************************************************/

#define KEY_TYP_LEVEL0      0x00 //140304 mike   
#define KEY_TYP_LEVEL1      0x0D //140304 mike 
#define KEY_TYP_LEVEL2      0x1E//140304 mike
#define KEY_TYP_LEVEL3      0x35 //140304 mike 
#define KEY_TYP_LEVEL4      0x54 //140304 mike 
#define KEY_TYP_LEVEL5      0x7F //140304 mike


/*******************************************************************************
                           Specific key stable time
*******************************************************************************/
#define KEY_STABLE_TIME     50

/*******************************************************************************
                            Specific keypad layout
*******************************************************************************/
//(1) Do not apply any change to BTN_CODE_#
#define BTN_CODE_1          0x01
#define BTN_CODE_2          0x02	//KEYCODE_PWR
#define BTN_CODE_3          0x04	//KEYCODE_MENU
#define BTN_CODE_4          0x08	//KEYCODE_DOWN
#define BTN_CODE_5          0x10	//KEYCODE_UP
#define BTN_CODE_6          0x20	//KEYCODE_AUTO
#define BTN_CODE_7          0x40
#define BTN_CODE_8          0x80


//(2) Define active AD key:   "No-used here"
//  a. Define (at KeyPad.c)     => L0: ADGRP1_CODE_1,		L1: ADGRP1_CODE_2,		L2: ADGRP1_CODE_3,		L3: ADGRP1_CODE_4,		L4: ADGRP1_CODE_5
//  b. Define (atKEYPADCONFIG.H)=>     BTN_CODE_2: Power,		BTN_CODE_3: Menu,		BTN_CODE_4: sel-,		BTN_CODE_5: sel+,		BTN_CODE_6: auto

/*	No-used here
	#define ADGRP1_CODE_1       BTN_CODE_2
	#define ADGRP1_CODE_2       BTN_CODE_3			// 0x04
	#define ADGRP1_CODE_3       BTN_CODE_4			// 0x08
	//===========================
	#define ADGRP1_CODE_4       BTN_CODE_5			//140304 mike  RIGH KEY      0X10
	#define ADGRP1_CODE_5       BTN_CODE_6 			//140304 mike  AUTO KEY      0X20
*/
	//===========================			
	#define ADGRP2_CODE_1       BTN_CODE_5
	#define ADGRP2_CODE_2       BTN_CODE_6
	#define ADGRP2_CODE_3       BTN_CODE_7



//(3) Define active IO key
#define IOBTN_CODE_1        BTN_CODE_1
#define IOBTN_CODE_2        0x00
#define IOBTN_CODE_3        0x00
#define IOBTN_CODE_4        0x00
#define IOBTN_CODE_5        0x00
#define IOBTN_CODE_6        0x00
#define IOBTN_CODE_7        0x00
#define IOBTN_CODE_8        0x00

// Use the following defines to change the order of keypad layout
//	//------------------------------------------------------------fefanjacky
//	#ifdef USE_X19N_BOARD
//	#define KEYCODE_UP          ADGRP2_CODE_2
//	#define KEYCODE_DOWN        ADGRP2_CODE_1
//	#else
//	#define KEYCODE_UP         BTN_CODE_5		//140304 mike ADGRP1_CODE_1
//	#define KEYCODE_DOWN       BTN_CODE_4		//140304 mike  ADGRP2_CODE_2
//	#endif
//	//------------------------------------------------------------------------
	#define KEYCODE_PWR        BTN_CODE_2		//140304 mike IOBTN_CODE_1
	#define KEYCODE_MENU       BTN_CODE_3		//140304 mike ADGRP1_CODE_1
	#define KEYCODE_AUTO       BTN_CODE_6 		//140304 mike  ADGRP1_CODE_3
	#define KEYCODE_INPUT      BTN_CODE_7		//	0x00
	#define KEYCODE_FUNC       0x00

	#define KEYCODE_UP         BTN_CODE_5		//140304 mike ADGRP1_CODE_1
	#define KEYCODE_DOWN       BTN_CODE_4		//140304 mike  ADGRP2_CODE_2



#define KEYCODE_LEFT        0x00
#define KEYCODE_RIGHT       0x00
#define KEYCODE_FACT        (KEYCODE_PWR|KEYCODE_MENU)		//140304 mike  
#define KEYCODE_DEMO        (KEYCODE_PWR|KEYCODE_AUTO)		//140304 mike  
#define KEYCODE_PWLOCK      0x00
#define KEYCODE_OSDLOCK     0x00
#define KEYCODE_TMG_SW      0x00


#define KEYCODE_DIR_MUTE        0xF0		//150511  George
#define KEYCODE_DIR_VOLUME_UP   0xF1
#define KEYCODE_DIR_VOLUME_DOWN 0xF2
#define KEYCODE_DIR_SCALING_TYPE    0xF3
#define KEYCODE_DIR_SENSEYE     0xF4
#define KEYCODE_DIR_BRIGHTNESS  0xF5
#define KEYCODE_DIR_CONTRAST    0xF6
#define KEYCODE_DIR_EXIT        0xF7
#define KEYCODE_DIR_INPUT       0xF9
#define KEYCODE_DIR_ENTER       0xFA


#endif //__KEYPAD_CONFIG_H__
