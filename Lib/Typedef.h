/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/

#ifndef __TYPEDEF_H__
#define __TYPEDEF_H__

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************

//******************************************************************************
// M A C R O   D E F I N I T I O N S
//******************************************************************************
typedef bit              BOOL;
typedef unsigned char    UCHAR;
typedef unsigned char *  PUCHAR;
typedef unsigned short   USHRT;
typedef unsigned short * PUSHRT;
typedef unsigned long    ULONG;
typedef unsigned long *  PULONG;

//------cobb
typedef  unsigned char BYTE;
typedef  unsigned int  WORD;
typedef  unsigned long DWORD;

typedef union _WB
{
 BYTE b[2];	
 WORD w;
 void code* pt;
}tdfWB;

typedef union _DWB
{
 BYTE   b[4];	
 WORD   w[2]; 
 DWORD   d; 
 void code* pt[2];
}tdfDWB;


//Boolean Constants
#define TRUE            1
#define FALSE           0
#define ON              1
#define OFF             0
#define YES             1
#define NO              0
#define PWM		2					//140314 mike for PWM
#define HIGH            1
#define LOW             0
#define IN              1
#define OUT             0
#define NACK            1
#define ACK             0
#define x2              2
#define x3              3
#define ENABLE			1		//george
#define DISABLE			0		//george

//Bit Mask
#define BIT0            ((UCHAR)0x01)
#define BIT1            ((UCHAR)0x02)
#define BIT2            ((UCHAR)0x04)
#define BIT3            ((UCHAR)0x08)
#define BIT4            ((UCHAR)0x10)
#define BIT5            ((UCHAR)0x20)
#define BIT6            ((UCHAR)0x40)
#define BIT7            ((UCHAR)0x80)
//null constants
#define NULLPTR         0

//******************************************************************************
// D A T A   T Y P E   D E F I N E S
//******************************************************************************

//******************************************************************************
// V A R I A B L E S   P R O T O T Y P E
//******************************************************************************

//******************************************************************************
// F U N C T I O N   P R O T O T Y P E S
//******************************************************************************

#endif //__TYPEDEF_H__
