/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/

#ifndef __INT_H__
#define __INT_H__

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************
#include "Typedef.h"
//#include "App\ChiuDef.h"

//******************************************************************************
// G L O B A L   D E F I N I T I O N S
//******************************************************************************
	typedef enum _UartCommadEnumType
	{
//	    _UART_CMD_START_,
	    _UART_CMD_INDEX0_,
	    _UART_CMD_INDEX1_,
	    _UART_CMD_INDEX2_,
	    _UART_CMD_INDEX3_,
	    _UART_CMD_INDEX4_,
	    _UART_CMD_INDEX5_, 
	    _UART_CMD_INDEX6_,
	    _UART_CMD_INDEX7_,                        
	    _UART_CMD_LENGTH_
	}UartCommadEnumType;
	
	
	typedef struct _UartCommadType
	{
	    BYTE Buffer[_UART_CMD_LENGTH_];  // command buffer
	                                     // [Length] -[Command]- [Value1] - [Value2] - [Value3] - [CR]
	    BYTE Index;                     // buffer index
	
	}UartCommadType;

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
// E X T E R N A L   V A R I A B L E   P R O T O T Y P E S
//******************************************************************************

/* extern idata UCHAR ucUARTTxOut;
extern idata UCHAR ucUARTTxIn;
extern idata UCHAR ucUARTRxOut;
extern idata UCHAR ucUARTRxIn;	//
extern xdata UCHAR ucUARTTxBuffer[UART_TX_BUFFER_SIZE];
extern xdata UCHAR ucUARTRxBuffer[UART_RX_BUFFER_SIZE];
extern xdata UCHAR ucIsTransDisabled;
extern xdata BOOL ucIsRecivCMDSS;	//gg
*/

#if (XRS232 == ADS_RS232)
	extern idata UCHAR ucUARTTxOut;
	extern idata UCHAR ucUARTTxIn;								//ext
	extern idata UCHAR ucUARTRxOut;
	extern idata UCHAR ucUARTRxIn;	//
	extern xdata UCHAR ucUARTTxBuffer[UART_TX_BUFFER_SIZE];
	extern xdata UCHAR ucUARTRxBuffer[UART_RX_BUFFER_SIZE];
	extern xdata UCHAR ucIsTransDisabled;
	extern idata UCHAR ucIsRecivCMDSS;	//gg					//ext


#elif (XRS232 == LWO_RS232)
	extern UartCommadType xdata g_UartCommand,r_UartCommand; // Uart command struct
	extern bit gbUartDetected,UserDataWriteFlag; // decode command flag
	extern xdata UCHAR checksumtemp;
#endif
//

//=== from Cobb define ====
#define mPrintfByte(abString, bVar)\
        {\
	       sPutStr(abString);\
	       sPutByteHex(bVar);\
	       sPutChar('\r');\
               sPutChar('\n');\
	}
#define mPrintStr(abString)\
        {\
	       sPutStr(abString);\
	       sPutChar('\r');\
               sPutChar('\n');\
        }	
#define mPrintfWord(abString, bVar)\
        {\	
	       sPutStr(abString);\
	       sPutWordHex(bVar);\
	       sPutChar('\r');\
               sPutChar('\n');\	
        }\	        
        
#define mPrintfWordDec(abString, bVar)\        
         {\	
	       sPutStr(abString);\
	       sPutWordDec(bVar);\
	       sPutChar('\r');\
               sPutChar('\n');\	
        }\		




//******************************************************************************
// F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
USHRT GetTimerTick(void);
BOOL CheckModeChangeFlag(void);
void ClearModeChangeFlag(void);
void SetModeChangeFlag(void);

#if (INPUT_INTERFACE&INPUT_MHL0) || (INPUT_INTERFACE&INPUT_MHL1)
void SetMHLTimerTick();
USHRT GetTimerTickInt();
#endif

#if ((INPUT_INTERFACE&INPUT_DP) && ENABLE_DP_AUX_MONITOR==ON)
extern void  move_aux_packet(void);  
#endif

extern char UART_Putchar(UCHAR c);	//george: 
extern UCHAR UART_Getchar(UCHAR *ptr);


#if (XRS232 == ADS_RS232)
	extern UCHAR UART_Getchar(UCHAR *ptr);
	extern char UART_Putchar(UCHAR c);	//george: 		
#elif (XRS232 == LWO_RS232)
	extern void sPutChar(BYTE bTmp);
	extern void sPutStr(BYTE code *ptTmpStr);
	extern void sPutByteHex(BYTE bHex);     	
	extern void sPutWordHex(WORD wHex);
	extern void sPutWordDec(WORD wHex);		
#endif //#if (XRS232 == ENABLE)

#endif //__INT_H__
