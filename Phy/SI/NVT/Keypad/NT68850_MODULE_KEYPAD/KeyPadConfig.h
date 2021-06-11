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

#define KEY_TYP_LEVEL0      0x00 	//140304 mike 
#define KEY_TYP_LEVEL1      0x0D 	//140304 mike 
#define KEY_TYP_LEVEL2      0x1E	//140304 mike
#define KEY_TYP_LEVEL3      0x35 	//140304 mike 
#define KEY_TYP_LEVEL4      0x54 	//140304 mike 
#define KEY_TYP_LEVEL5      0x7F 	//140304 mike
/*******************************************************************************
                           Specific key stable time
*******************************************************************************/
#define KEY_STABLE_TIME     50

/*******************************************************************************
                            Specific keypad layout
*******************************************************************************/
// Do not apply any change to BTN_CODE_#
#define BTN_CODE_1          0x01
#define BTN_CODE_2          0x02
#define BTN_CODE_3          0x04
#define BTN_CODE_4          0x08
#define BTN_CODE_5          0x10
#define BTN_CODE_6          0x20
#define BTN_CODE_7          0x40
#define BTN_CODE_8          0x80

// Define active AD key
#define ADGRP1_CODE_1       BTN_CODE_2
#define ADGRP1_CODE_2       BTN_CODE_3
#define ADGRP1_CODE_3       BTN_CODE_4
#define ADGRP2_CODE_1       BTN_CODE_5
#define ADGRP2_CODE_2       BTN_CODE_6
#define ADGRP2_CODE_3       BTN_CODE_7

// Define active IO key
#define IOBTN_CODE_1        BTN_CODE_1
#define IOBTN_CODE_2        0x00
#define IOBTN_CODE_3        0x00
#define IOBTN_CODE_4        0x00
#define IOBTN_CODE_5        0x00
#define IOBTN_CODE_6        0x00
#define IOBTN_CODE_7        0x00
#define IOBTN_CODE_8        0x00

// Use the following defines to change the order of keypad layout
#define KEYCODE_PWR         IOBTN_CODE_1
#define KEYCODE_MENU        ADGRP1_CODE_1
#define KEYCODE_AUTO        ADGRP1_CODE_3
#define KEYCODE_INPUT       0x00
#define KEYCODE_FUNC        ADGRP2_CODE_2
#define KEYCODE_UP          ADGRP1_CODE_2
#define KEYCODE_DOWN        ADGRP2_CODE_1
#define KEYCODE_LEFT        0x00
#define KEYCODE_RIGHT       0x00
#define KEYCODE_FACT        (KEYCODE_PWR|KEYCODE_MENU)
#define KEYCODE_DEMO        (KEYCODE_PWR|KEYCODE_AUTO)
#define KEYCODE_PWLOCK      0x00
#define KEYCODE_OSDLOCK     0x00
#define KEYCODE_TMG_SW      0x00




#endif //__KEYPAD_CONFIG_H__
