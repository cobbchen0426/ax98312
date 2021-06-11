/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/

#ifndef __8051_H__
#define __8051_H__

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************

//******************************************************************************
// M A C R O   D E F I N I T I O N S
//******************************************************************************

//******************************************************************************
// D A T A   T Y P E   D E F I N E S
//******************************************************************************

//******************************************************************************
// V A R I A B L E S   P R O T O T Y P E
//******************************************************************************
sfr ACC    = 0xE0; /*!< 8051 special function register. */
sfr B      = 0xF0; /*!< 8051 special function register. */
sfr PSW    = 0xD0; /*!< 8051 special function register. */
sfr SP     = 0x81; /*!< 8051 special function register. */
sfr DPL    = 0x82; /*!< 8051 special function register. */
sfr DPH    = 0x83; /*!< 8051 special function register. */
sfr P0     = 0x80; /*!< 8051 special function register. */
sfr P1     = 0x90; /*!< 8051 special function register. */
sfr P2     = 0xA0; /*!< 8051 special function register. */
sfr P3     = 0xB0; /*!< 8051 special function register. */
sfr IE     = 0xA8; /*!< 8051 special function register. */
sfr IP     = 0xB8; /*!< 8051 special function register. */
sfr PCON   = 0x87; /*!< 8051 special function register. */
sfr TCON   = 0x88; /*!< 8051 special function register. */
sfr TMOD   = 0x89; /*!< 8051 special function register. */
sfr TL0    = 0x8A; /*!< 8051 special function register. */
sfr TL1    = 0x8B; /*!< 8051 special function register. */
sfr TH0    = 0x8C; /*!< 8051 special function register. */
sfr TH1    = 0x8D; /*!< 8051 special function register. */
sfr T2CON  = 0xC8; /*!< 8051 special function register. */
sfr RCAP2L = 0xCA; /*!< 8051 special function register. */
sfr RCAP2H = 0xCB; /*!< 8051 special function register. */
sfr TL2    = 0xCC; /*!< 8051 special function register. */
sfr TH2    = 0xCD; /*!< 8051 special function register. */
sfr SCON   = 0x98; /*!< 8051 special function register. */
sfr SBUF   = 0x99; /*!< 8051 special function register. */
sbit CY    = 0xD7; /*!< 8051 bit addressable function register. */
sbit AC    = 0xD6; /*!< 8051 bit addressable function register. */
sbit F0    = 0xD5; /*!< 8051 bit addressable function register. */
sbit RS1   = 0xD4; /*!< 8051 bit addressable function register. */
sbit RS0   = 0xD3; /*!< 8051 bit addressable function register. */
sbit OV    = 0xD2; /*!< 8051 bit addressable function register. */
sbit P     = 0xD0; /*!< 8051 bit addressable function register. */
sbit TF1   = 0x8F; /*!< 8051 bit addressable function register. */
sbit TR1   = 0x8E; /*!< 8051 bit addressable function register. */
sbit TF0   = 0x8D; /*!< 8051 bit addressable function register. */
sbit TR0   = 0x8C; /*!< 8051 bit addressable function register. */
sbit IE1   = 0x8B; /*!< 8051 bit addressable function register. */
sbit IT1   = 0x8A; /*!< 8051 bit addressable function register. */
sbit IE0   = 0x89; /*!< 8051 bit addressable function register. */
sbit IT0   = 0x88; /*!< 8051 bit addressable function register. */
sbit TF2   = 0xCF; /*!< 8051 bit addressable function register. */
sbit EXF2  = 0xCE; /*!< 8051 bit addressable function register. */
sbit RCLK  = 0xCD; /*!< 8051 bit addressable function register. */
sbit TCLK  = 0xCC; /*!< 8051 bit addressable function register. */
sbit EXEN2 = 0xCB; /*!< 8051 bit addressable function register. */
sbit TR2   = 0xCA; /*!< 8051 bit addressable function register. */
sbit CT2   = 0xC9; /*!< 8051 bit addressable function register. */
sbit CPRL2 = 0xC8; /*!< 8051 bit addressable function register. */
sbit SM0   = 0x9F; /*!< 8051 bit addressable function register. */
sbit SM1   = 0x9E; /*!< 8051 bit addressable function register. */
sbit SM2   = 0x9D; /*!< 8051 bit addressable function register. */
sbit REN   = 0x9C; /*!< 8051 bit addressable function register. */
sbit TB8   = 0x9B; /*!< 8051 bit addressable function register. */
sbit RB8   = 0x9A; /*!< 8051 bit addressable function register. */
sbit TI    = 0x99; /*!< 8051 bit addressable function register. */
sbit RI    = 0x98; /*!< 8051 bit addressable function register. */
sbit EA    = 0xAF; /*!< 8051 bit addressable function register. */
sbit ET2   = 0xAD; /*!< 8051 bit addressable function register. */
sbit ES    = 0xAC; /*!< 8051 bit addressable function register. */
sbit ET1   = 0xAB; /*!< 8051 bit addressable function register. */
sbit EX1   = 0xAA; /*!< 8051 bit addressable function register. */
sbit ET0   = 0xA9; /*!< 8051 bit addressable function register. */
sbit EX0   = 0xA8; /*!< 8051 bit addressable function register. */
sbit PT2   = 0xBD; /*!< 8051 bit addressable function register. */
sbit PS    = 0xBC; /*!< 8051 bit addressable function register. */
sbit PT1   = 0xBB; /*!< 8051 bit addressable function register. */
sbit PX1   = 0xBA; /*!< 8051 bit addressable function register. */
sbit PT0   = 0xB9; /*!< 8051 bit addressable function register. */
sbit PX0   = 0xB8; /*!< 8051 bit addressable function register. */
sbit P00   = 0x80; /*!< 8051 GPIO. */
sbit P01   = 0x81; /*!< 8051 GPIO. */
sbit P02   = 0x82; /*!< 8051 GPIO. */
sbit P03   = 0x83; /*!< 8051 GPIO. */
sbit P04   = 0x84; /*!< 8051 GPIO. */
sbit P05   = 0x85; /*!< 8051 GPIO. */
sbit P06   = 0x86; /*!< 8051 GPIO. */
sbit P07   = 0x87; /*!< 8051 GPIO. */
sbit P10   = 0x90; /*!< 8051 GPIO. */
sbit P11   = 0x91; /*!< 8051 GPIO. */
sbit P12   = 0x92; /*!< 8051 GPIO. */
sbit P13   = 0x93; /*!< 8051 GPIO. */
sbit P14   = 0x94; /*!< 8051 GPIO. */
sbit P15   = 0x95; /*!< 8051 GPIO. */
sbit P16   = 0x96; /*!< 8051 GPIO. */
sbit P17   = 0x97; /*!< 8051 GPIO. */
sbit P20   = 0xA0; /*!< 8051 GPIO. */
sbit P21   = 0xA1; /*!< 8051 GPIO. */
sbit P22   = 0xA2; /*!< 8051 GPIO. */
sbit P23   = 0xA3; /*!< 8051 GPIO. */
sbit P24   = 0xA4; /*!< 8051 GPIO. */
sbit P25   = 0xA5; /*!< 8051 GPIO. */
sbit P26   = 0xA6; /*!< 8051 GPIO. */
sbit P27   = 0xA7; /*!< 8051 GPIO. */
sbit P30   = 0xB0; /*!< 8051 GPIO. */
sbit P31   = 0xB1; /*!< 8051 GPIO. */
sbit P32   = 0xB2; /*!< 8051 GPIO. */
sbit P33   = 0xB3; /*!< 8051 GPIO. */
sbit P34   = 0xB4; /*!< 8051 GPIO. */
sbit P35   = 0xB5; /*!< 8051 GPIO. */
sbit P36   = 0xB6; /*!< 8051 GPIO. */
sbit P37   = 0xB7; /*!< 8051 GPIO. */

//******************************************************************************
// F U N C T I O N   P R O T O T Y P E S
//******************************************************************************

#endif //__8051_H__
