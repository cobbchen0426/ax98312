/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/

#ifndef __SCALER_TYPE_H__
#define __SCALER_TYPE_H__
/*! @file ScalerType.h
 * This file include the scaler common defines.
 */

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************
#include "Typedef.h"

//******************************************************************************
// M A C R O   D E F I N I T I O N S
//******************************************************************************
// Scaler series ID
#define SCALER_SERIES_MASK  0xF80
#define NT68168_SERIES      0x080
#define NT68668_SERIES      0x100
#define NT68669_SERIES      0x180
#define NT68660_SERIES      0x200
#define NT68620_SERIES      0x210
#define NT68650_SERIES      0x280
#define NT68671_SERIES      0x300
#define NT68674_SERIES      0x380
#define NT68676_SERIES      0x400
#define NT68750_SERIES      0x480
#define NT68360_SERIES      0x500
#define NT68652_SERIES      0x580
#define NT68169_SERIES      0x600
#define NT68770_SERIES      0x680
#define NT68850_SERIES      0x700
#define NT68655_SERIES      0x780
#define NT68661_SERIES      0x800
#define NT68150_SERIES      0x880
#define NT68370_SERIES      0x900
#define NT68790_SERIES      0x980

// Scaler ID
#define NT68168             0x080
#define NT68668             0x100
#define NT68669             0x180
#define NT68660             0x200
#define NT68620             0x201
#define NT68650             0x280
#define NT68671             0x300
#define NT68672             0x301
#define NT68673             0x302
#define NT68674             0x380
#define NT68675             0x381
#define NT68676             0x400
#define NT68677             0x401
#define NT68678             0x402
#define NT68679             0x403
#define NT68776             0x404
#define NT68777             0x405
#define NT68778             0x406
#define NT68779             0x407
#define NT68750             0x480
#define NT68751             0x481
#define NT68752             0x482
#define NT68753             0x483
#define NT68360             0x500
#define NT68361             0x501
#define NT68652             0x580
#define NT68169             0x600
#define NT68770             0x680
#define NT68771             0x681
#define NT68772             0x682
#define NT68773             0x683
#define NT68774             0x684
#define NT68775             0x685
#define NT68781             0x686
#define NT68785             0x687
#define NT68850             0x700
#define NT68851             0x701
#define NT68852             0x702
#define NT68853             0x703
#define NT68854             0x704
#define NT68855             0x705
#define NT68856             0x706	//george-mar-here
#define NT68857             0x707
#define NT68859             0x708
#define NT68655             0x780
#define NT68656             0x781
#define NT68661             0x800
#define NT68150             0x880
#define NT68370             0x900
#define NT68790             0x980

#define IS_NT68168_SERIES   ((SCALER_TYPE&SCALER_SERIES_MASK) == NT68168_SERIES)
#define IS_NT68668_SERIES   ((SCALER_TYPE&SCALER_SERIES_MASK) == NT68668_SERIES)
#define IS_NT68669_SERIES   ((SCALER_TYPE&SCALER_SERIES_MASK) == NT68669_SERIES)
#define IS_NT68620_SERIES   ((SCALER_TYPE&SCALER_SERIES_MASK) == NT68620_SERIES)
#define IS_NT68660_SERIES   ((SCALER_TYPE&SCALER_SERIES_MASK) == NT68660_SERIES)
#define IS_NT68650_SERIES   ((SCALER_TYPE&SCALER_SERIES_MASK) == NT68650_SERIES)
#define IS_NT68671_SERIES   ((SCALER_TYPE&SCALER_SERIES_MASK) == NT68671_SERIES)
#define IS_NT68674_SERIES   ((SCALER_TYPE&SCALER_SERIES_MASK) == NT68674_SERIES)
#define IS_NT68676_SERIES   ((SCALER_TYPE&SCALER_SERIES_MASK) == NT68676_SERIES)
#define IS_NT68750_SERIES   ((SCALER_TYPE&SCALER_SERIES_MASK) == NT68750_SERIES)
#define IS_NT68360_SERIES   ((SCALER_TYPE&SCALER_SERIES_MASK) == NT68360_SERIES)
#define IS_NT68652_SERIES   ((SCALER_TYPE&SCALER_SERIES_MASK) == NT68652_SERIES)
#define IS_NT68169_SERIES   ((SCALER_TYPE&SCALER_SERIES_MASK) == NT68169_SERIES)
#define IS_NT68770_SERIES   ((SCALER_TYPE&SCALER_SERIES_MASK) == NT68770_SERIES)
#define IS_NT68850_SERIES   ((SCALER_TYPE&SCALER_SERIES_MASK) == NT68850_SERIES)	//george-mark-here		0xF80==0x700
#define IS_NT68655_SERIES   ((SCALER_TYPE&SCALER_SERIES_MASK) == NT68655_SERIES)
#define IS_NT68661_SERIES   ((SCALER_TYPE&SCALER_SERIES_MASK) == NT68661_SERIES)
#define IS_NT68150_SERIES   ((SCALER_TYPE&SCALER_SERIES_MASK) == NT68150_SERIES)
#define IS_NT68370_SERIES   ((SCALER_TYPE&SCALER_SERIES_MASK) == NT68370_SERIES)
#define IS_NT68790_SERIES   ((SCALER_TYPE&SCALER_SERIES_MASK) == NT68790_SERIES)

//DVI Sync/DE Mode Selection
#define DVI_HV_MODE         1 //sync mode
#define DVI_DE_MODE         2 //DE mode
#define DVI_HVDE_MODE       3 //sync+DE mode

//Interface
#define INPUT_NONE          0x0000
#define INPUT_VGA0          0x0001
#define INPUT_VGA1          0x0002
#define INPUT_DIG0          0x0004
#define INPUT_DIG1          0x0008
#define INPUT_YPbPr0        0x0010
#define INPUT_YPbPr1        0x0020
#define INPUT_MHL0          0x0040
#define INPUT_MHL1          0x0080
#define INPUT_DP            0x0100
#define INPUT_DP1           0x0200

//Input Port Definition
#define ANALOG_SEP_INPUT0   0x11
#define ANALOG_COM_INPUT0   0x12
#define ANALOG_SOG_INPUT0   0x13
#define DIGITAL_INPUT0      0x21
#define ANALOG_SEP_INPUT1   0x31
#define ANALOG_COM_INPUT1   0x32
#define ANALOG_SOG_INPUT1   0x33
#define DIGITAL_INPUT1      0x41
#define ANALOG_YPBPR_INPUT0 0x51
#define ANALOG_YPBPR_INPUT1 0x61
#define DISPLAY_PORT_INPUT  0x71
#define DISPLAY_PORT_INPUT1  0x81
#define PORT_MASK           0xF0
#define PORT_NULL           0xFF

//Error Code
#define INTERFACE_ERROR     0x01

//Audio Out Selection
#define LINE_OUT            1
#define IIS_OUT             2

//Audio Line In Selection
#define LINE_IN1            0x00
#define LINE_IN2            0x10

//******************************************************************************
// D A T A   T Y P E   D E F I N E S
//******************************************************************************

//******************************************************************************
// V A R I A B L E S   P R O T O T Y P E
//******************************************************************************

//******************************************************************************
// F U N C T I O N   P R O T O T Y P E S
//******************************************************************************

#endif //__SCALER_TYPE_H__
