/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************
#include "Include.h"
#include "ScalerProfile.h"

//******************************************************************************
// M A C R O   D E F I N I T I O N S
//******************************************************************************
#if BACKLIGHT_ACTIVE == HIGH
    #define BLOffMacro(port) { UCHAR _temp_; \
                               _temp_ = Port##port; \
                               _temp_ |= RDP##port##_REG; \
                               _temp_ &= ~BACKLIGHT_BIT; \
                               Port##port = _temp_; }
#else
    #define BLOffMacro(port) { UCHAR _temp_; \
                               _temp_ = Port##port; \
                               _temp_ |= RDP##port##_REG; \
                               _temp_ |= BACKLIGHT_BIT; \
                               Port##port = _temp_; }
#endif
#if BACKLIGHT_PORT == MCU_PORT_A
    #define FastBLOff() BLOffMacro(A)
#elif BACKLIGHT_PORT == MCU_PORT_B
    #define FastBLOff() BLOffMacro(B)
#elif BACKLIGHT_PORT == MCU_PORT_C
    #define FastBLOff() BLOffMacro(C)
#elif BACKLIGHT_PORT == MCU_PORT_D
    #define FastBLOff() BLOffMacro(D)
#elif BACKLIGHT_PORT == MCU_PORT_E
    #define FastBLOff() BLOffMacro(E)
#elif BACKLIGHT_PORT == MCU_PORT_3
    #define FastBLOff() BLOffMacro(3)
#endif

#if ENABLE_SCALER_LEDDRV == ON
#undef FastBLOff
#define FastBLOff() {SC_LEDDRIVER_ENABLE = 0x00;}
#endif

//---------------------------------------------
#if (XRS232 == ADS_RS232)
	#define	CMD_LEN		4		//george				
#elif (XRS232 == LWO_RS232)
	UartCommadType xdata g_UartCommand,r_UartCommand; // Uart command struct
	
	bit gbUartDetected,UserDataWriteFlag=0; // decode command flag
	
	#define UART_CMD_LENGTH 	8// (g_UartCommand.Buffer[_UART_CMD_CODE_] >> 5)
	#define UART_CMD        (g_UartCommand.Buffer[_UART_CMD_CODE_] & 0x1F)
	#define UART_CMD_START		'U'
	#define UART_CMD_ACK		'F'
	#define UART_CMD_NAK		'N'
	
	#define UART_CMD_MS_RW (g_UartCommand.Buffer[_UART_CMD_INDEX1_])
	#define UART_CMD_MS_INDEX (g_UartCommand.Buffer[_UART_CMD_INDEX2_])
	#define UART_CMD_MS_DAT (g_UartCommand.Buffer[_UART_CMD_INDEX3_])
	#define UART_CMD_MS_CRC (g_UartCommand.Buffer[_UART_CMD_INDEX6_])
	#else
	idata UCHAR ucUARTTxOut=0;
	idata UCHAR ucUARTTxIn=0;
	idata UCHAR ucUARTRxOut=0;
	idata UCHAR ucUARTRxIn=0;	//
	xdata UCHAR ucUARTTxBuffer[UART_TX_BUFFER_SIZE];
	xdata UCHAR ucUARTRxBuffer[UART_RX_BUFFER_SIZE];
	xdata UCHAR ucIsTransDisabled;
	idata UCHAR ucIsRecivCMDSS=0;	//gg
	idata UCHAR ucCntCmdLen=0;	//george				
#endif //#if (XRS232 == ENABLE)

//---------------------------------------------
//******************************************************************************
// G L O B A L   V A R I A B L E S
//******************************************************************************

idata USHRT usMCUCLKDIVIDERLoop;


#if ENABLE_NEW_TIMER == ON
	//IntTimer0()
		// RC5_0.5 Cycle = 0.840ms
		// RC5_1.0 Cycle = 1.680ms ~~ 1.778ms
idata unsigned char  ucTimer_40us  		= 0;
idata unsigned char  ucTimer_40to200us  = 0;											
idata unsigned char  ucTimer_200us 		= 0;
#endif


#if IR_REMOT_CTL == ENABLE
idata UCHAR ucTimer_IR = 0xFF;
idata USHRT usData;
extern USHRT usIRData;
extern bit bIrDetect;

#endif

//******************************************************************************
// S T A T I C   V A R I A B L E S
//******************************************************************************
static BOOL bModeChanged = TRUE;
static idata USHRT volatile usTimerTick_1ms;

#if ENABLE_SERIAL_INT == ON
/* 
static idata UCHAR ucUARTTxOut;
static idata UCHAR ucUARTTxIn;
static idata UCHAR ucUARTRxOut;
static idata UCHAR ucUARTRxIn;	//
static xdata UCHAR ucUARTTxBuffer[UART_TX_BUFFER_SIZE];
static xdata UCHAR ucUARTRxBuffer[UART_RX_BUFFER_SIZE];
static xdata UCHAR ucIsTransDisabled;
static xdata BOOL ucIsRecivCMDSS;	//gg
*/

/*idata UCHAR ucUARTTxOut;
idata UCHAR ucUARTTxIn;
idata UCHAR ucUARTRxOut;
idata UCHAR ucUARTRxIn=0;	//
xdata UCHAR ucUARTTxBuffer[UART_TX_BUFFER_SIZE];
xdata UCHAR ucUARTRxBuffer[UART_RX_BUFFER_SIZE];
xdata UCHAR ucIsTransDisabled;
idata BOOL ucIsRecivCMDSS=0;	//gg 
*/
	#if (XRS232 == ADS_RS232)
		idata UCHAR ucUARTTxOut=0;
		idata UCHAR ucUARTTxIn=0;
		idata UCHAR ucUARTRxOut=0;
		idata UCHAR ucUARTRxIn=0;	//
		xdata UCHAR ucUARTTxBuffer[UART_TX_BUFFER_SIZE];
		xdata UCHAR ucUARTRxBuffer[UART_RX_BUFFER_SIZE];
		xdata UCHAR ucIsTransDisabled;
		idata UCHAR ucIsRecivCMDSS=0;	//gg
		idata UCHAR ucCntCmdLen=0;	//george			
	#elif (XRS232 == LWO_RS232)
		xdata UCHAR checksumtemp=0;			
	#endif //#if (XRS232 == ENABLE)


#endif 



//******************************************************************************
// E X T E R N A L   V A R I A B L E   P R O T O T Y P E S
//******************************************************************************
extern BOOL bLowPowerMode;
extern BOOL bIsAPLLPowerDown;
extern idata UCHAR ucDdcciChannel;
extern BOOL bDDCCmdUpdate;
extern idata UCHAR ucDDCCiTxOut;
extern idata UCHAR ucDDCCiTxIn;
extern idata UCHAR ucDDCCiRxIn;
extern idata UCHAR ucDDCCiRxOut;
extern xdata UCHAR ucDDCCiTxBuffer[DDCCI_BUFFER_SIZE];
extern xdata UCHAR ucDDCCiRxBuffer[DDCCI_BUFFER_SIZE];


#if (INPUT_INTERFACE&INPUT_MHL0) || (INPUT_INTERFACE&INPUT_MHL1)
idata USHRT usTimerTickMHL = 0;
extern idata USHRT usCBUSTimeoutDAT;
extern idata UCHAR ucMHLConnState;
extern idata UCHAR ucCBusState;
extern xdata UCHAR ucCbusBuffer[40];
extern BOOL bStartOfFrame;
extern BOOL bDDCWriteFlag;		// David, HTC debug.
extern BOOL bPackPixelModeIntFlag;
extern BOOL bWaitACK;
extern idata USHRT usCBUSTimeoutACK;
#endif

#if (INPUT_INTERFACE&INPUT_DP)
#if EN_AUX_STROBE_FUNC == ON // AUX strobe function 
#define AUXBUFLEN 20
idata UCHAR ucAuxStrobeIndex;
xdata UCHAR ucAuxStrobeBuf[AUXBUFLEN];
idata UCHAR ucDPEDIDPtr;
extern xdata UCHAR volatile EDID_SRAM_DP[];
extern xdata UCHAR bDP_AUX_DETECT;
#endif
#endif


//******************************************************************************
// S T A T I C   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
static char UART_Putchar(UCHAR c);

//******************************************************************************
// E X T E R N A L   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// F U N C T I O N   B O D Y S
//******************************************************************************

/**************************************************************************//**
 * Mcu external interrupt 0 service routine.
 ******************************************************************************/
void IntExt0(void) interrupt 0 using 1
{

	#if ENABLE_LOW_PWR_MODE == ON	//george: have compiler here.
	    SC_MCU_CLK_DIVIDER = 0x00;
	#endif

	#if IS_NT68850_SERIES 
	#if ((INPUT_INTERFACE&INPUT_DP) && ENABLE_DP_AUX_MONITOR==ON)
	    if(AUX_STROBE_CTL&BIT0) 
	    {
	    	move_aux_packet();
	    	return;
	    }
	#endif
	#endif

#if (INPUT_INTERFACE&INPUT_DP)
    // Power Up DP AUX
    if(bLowPowerMode == TRUE) 
	{
        if ((SC_DP_AUX_DETECT&0xC0) != 0) 
		{
            INTSC_EN &= ~BIT1;
            LDO_ADJ |= BIT7; //Power up APLL  //20130715_1006_SYS#3
            SC_HW_RST = 0x10;
            SC_HW_RST = 0x11;
            SC_ADC_ZERO_POWER_CTRL = 0x83;			
			
        #if ENABLE_CUT_POWER_ARCH == ON
            SC_POWER_CTRL1 |= BIT7;
            SC_CUT_POWER_CTRL |= BIT2;
            SC_CUT_POWER_CTRL |= BIT0;
            SC_ISOLATION_CONTROL = SCREB_B61_PU;
            SC_CUT_POWER_CTRL &= 0x07;
            SC_CUT_POWER_CTRL &= ~BIT1;
            SC_POWER_CTRL1 &= ~BIT7;
        #endif

            SC_POWER_CTRL1 |= BIT5;
            SC_MCU_CLK_DIVIDER = 0x00;
            SC_MPLL_X2 &= ~(BIT4|BIT3); //SC_MPLL_X2 = 0x03; 
            SC_POWER_CTRL1 &= ~(BIT5|BIT1);

            PortD = (PortD | RDPD_REG) & (~BIT4); // HPD Low  // v20_130823_1815_SYS#6
            DP_CTRL &= ~BIT4; // DP HPD_PAD disable

            SC_TMDS_LINK_CLK_SEL = SCREG_1E7 | BIT0;  // dp_refclk select
            SC_DP_102F = REF_CLK*4/1000000;  // if 0x1E7[4:3] = 2'b00, dp_refclk = OSC clock*4
            
            DP_CLKOn();  
            DP_ConfigAUX2IICSpeed();			
            DP_InitPHY();
            DP_InitDPCD();

            SC_DP_AUX_CTRL = 0x31; // AUX En

            DP_InitDPConfigPage();

            PortD = (PortD | RDPD_REG) | BIT4; // HPD High
	        DP_CTRL |= BIT4; // DP HPD_PAD enable
	        
            SetDPLink();
        }
    }
#endif	//End #if (INPUT_INTERFACE&INPUT_DP)


#if (INPUT_INTERFACE&INPUT_MHL0) || (INPUT_INTERFACE&INPUT_MHL1)
    if ((MHL_SRC & INT_MHL) != 0) 
	{
	        idata UCHAR i;
	        SC_ADC_ZERO_POWER_CTRL |= (BIT7|BIT1);
	        i = SC_CBUS_INT_FLAG;

		#if ENABLE_INT_DISCOVERY == ON
	        if ( i & DIS_INT_FLG ) {			// Discovery int.
	            CbusDiscoveryHandler();
		//          SC_CBUS_INT_EN |= DIS_INT_CLR;
	        }
		#endif


	        if ( i & TRANS_INT_FLG ) 
			{
	            if (MHL_GetMSCCmd()) {
	                CbusMSCCmdHandler();
	            }
	            else if (MHL_GetDDCCmd()) {
	                CbusDDCCmdHandler();
	            }
	            SC_CBUS_INT_EN |= TRANS_INT_CLR;
	        }

		#if 1//def E_DEBUG
			if (i & LINK_INT_FLG) 
			{
					if (SC_CBUS_LINK_INT_FLAG & CBUS_ARB_FAIL) {
						bCBusArbFailFlag = TRUE;
					}
		    		SC_CBUS_INT_EN |= LINK_INT_CLR;
			}
		#endif
    }
#endif	//End #if (INPUT_INTERFACE&INPUT_MHL0) || (INPUT_INTERFACE&INPUT_MHL1)


#if (INPUT_INTERFACE&INPUT_DP)
#if EN_AUX_STROBE_FUNC == ON // AUX strobe function 
	if(DP_SRC & BIT7) 
	{
        idata UCHAR i;
		// for INTS_SEL = command_end
//SC_DP_AUX_DETECT &= ~BIT0;//????????????????????????
		if (AUX_STROBE_CTL & BIT3) 
		{
            ucAuxStrobeIndex = 0;
			while ((AUX_STROBE_FUN & BIT0) == 0) 
			{
				if (ucAuxStrobeIndex < AUXBUFLEN) {
					ucAuxStrobeBuf[ucAuxStrobeIndex++] = AUX_STROBE_PORT;
					//*pDDCPtr1++ = ucAuxStrobeBuf[ucAuxStrobeIndex++];
				}
				else {// Read out data for empty
					i = AUX_STROBE_PORT;
				}				
			}
			AUX_STROBE_CTL |= BIT3;		// clear AUX_STROBE_INT
		}

		// decode AUX channel data.
		if ((ucAuxStrobeBuf[0] & BIT7) == 0) 		// I2C-over-AUX
		{

			if ((ucAuxStrobeBuf[0] & (BIT5|BIT4)) == 0) 	// Write
			{
				if ((ucAuxStrobeBuf[2] == 0x37) && (ucAuxStrobeIndex > 4))  {// DDC_CI Write
					// Reserved for DDC_CI Write decode....
                    ucDdcciChannel = 4;
//                    ucDDCCiRxIn = 0;
                    bDDCCmdUpdate = TRUE;
					i = ucAuxStrobeBuf[3] + 1;
					for (ucAuxStrobeIndex=0; ucAuxStrobeIndex<i; ucAuxStrobeIndex++) {
                        ucDDCCiRxBuffer[ucDDCCiRxIn++] = ucAuxStrobeBuf[4+ucAuxStrobeIndex];
	                    if (ucDDCCiRxIn > DDCCI_BUFFER_SIZE-1) {
	                        ucDDCCiRxIn = 2;
	                    }
					}
				}
				else if (ucAuxStrobeBuf[2] == 0x50) {	// EDID Write
					ucDPEDIDPtr = ucAuxStrobeBuf[4];
				}
				AUX_I2C_MANUAL = (AUX_I2C_MODE | AUX_I2C_FINSH);
			}
			else 		// Read
			{
				if (ucAuxStrobeBuf[2] == 0x50) 		// EDID Read
				{
					if (ucAuxStrobeIndex <= 3) {		// No length
						AUX_I2C_MANUAL = (AUX_I2C_MODE | AUX_I2C_FINSH);
					}
					else {
						i = ucAuxStrobeBuf[3] + 1;
						for (ucAuxStrobeIndex=0; ucAuxStrobeIndex<i; ucAuxStrobeIndex++) {
							AUX_I2C_MANUAL = (AUX_I2C_MODE);	// send ack
							AUX_I2C_DATA = EDID_SRAM_DP[ucDPEDIDPtr++];
						}
						AUX_I2C_MANUAL = (AUX_I2C_MODE | AUX_I2C_FINSH);
					}
				}
				else if (ucAuxStrobeBuf[2] == 0x37) 	// DDC_CI Read
				{
//                    ucDdcciChannel = 4;
					if (ucAuxStrobeIndex <= 3) {		// No length
						AUX_I2C_MANUAL = (AUX_I2C_MODE | AUX_I2C_FINSH);
					}
					else 
					{
						i = ucAuxStrobeBuf[3] + 1;
//                        ucDDCCiTxOut = 0;
						for (ucAuxStrobeIndex=0; ucAuxStrobeIndex<i; ucAuxStrobeIndex++) {
							AUX_I2C_MANUAL = (AUX_I2C_MODE);	// send ack
                            if (ucDDCCiTxOut != ucDDCCiTxIn) {
    							AUX_I2C_DATA = ucDDCCiTxBuffer[ucDDCCiTxOut++];
                            }
                            else {
                                AUX_I2C_DATA = ucDDCCiTxBuffer[ucDDCCiTxOut];
                                ucDDCCiTxOut = 0;
                            }
						}
						AUX_I2C_MANUAL = (AUX_I2C_MODE | AUX_I2C_FINSH);
					}					
				}

			} //End else... Read
		} //End if ((ucAuxStrobeBuf[0] & BIT7)  ....  I2C-over-AUX

		ucAuxStrobeIndex = 0;
	} //End if(DP_SRC & BIT7) 

    else if (SC_DP_AUX_DETECT & BIT7) 
	{
        SC_DP_AUX_DETECT |= BIT1;
        SC_DP_AUX_DETECT &= ~BIT1;
        bDP_AUX_DETECT = 1;
	//	INTSC_EN &= ~BIT1;
	//	AUX_STROBE_CTL = 0x00;
    }
#endif		//End #if EN_AUX_STROBE_FUNC == ON // AUX strobe function 
#endif


	if ((INT_SRC & INT_IIC0) != 0) 
	{
        ucDdcciChannel = 0;
        if (IIC0_INT_FLG & INTA) {
            IIC0_INT_CLR = INTA;
            if (IIC0_STATUS & DOWRITE) {  // Slave Addr || 0x01 ==> Read
                IIC0_INT_CLR = (INTTX | CLR_TX_FIFO);
                IIC0_TXDATA = ucDDCCiTxBuffer[0];
                IIC0_INT_EN = (INTA | INTTX);
                ucDDCCiTxOut = 1;
            }
            else {  // Slave Addr ==> Write
                IIC0_INT_EN = (INTA | INTRX);
                IIC0_CFG |= SEND_ACK;
                ucDDCCiRxIn = 0;
                bDDCCmdUpdate = TRUE;
			}
		}

        while (IIC0_INT_FLG & INTTX) {
            if (ucDDCCiTxOut != ucDDCCiTxIn) {
                IIC0_TXDATA = ucDDCCiTxBuffer[ucDDCCiTxOut++];
                IIC0_INT_CLR = INTTX;
            }
            else {
                IIC0_TXDATA = ucDDCCiTxBuffer[ucDDCCiTxOut];
                IIC0_INT_CLR = INTTX;
                ucDDCCiTxOut = 0;
			}
		}

        while (IIC0_INT_FLG & INTRX) {
            ucDDCCiRxBuffer[ucDDCCiRxIn++] = IIC0_RXDATA;
            IIC0_INT_CLR = INTRX;
            bDDCCmdUpdate = TRUE;
            if (ucDDCCiRxIn > DDCCI_BUFFER_SIZE-1) {
                ucDDCCiRxIn = 2;
            }
        } 
        if (IIC0_INT_FLG & INTNAK) {
            IIC0_INT_CLR = 0xFF;//INTNAK;
        }
        if (IIC0_INT_FLG & INTLOST) {
            IIC0_INT_CLR = 0xFF;//INTLOST;
        }
    } //End if ((INT_SRC & INT_IIC0) != 0)


    if ((INT_SRC & INT_IIC2) != 0) 
	{
        ucDdcciChannel = 2;
        if (IIC2_INT_FLG & INTA) {
            IIC2_INT_CLR = INTA;
            if (IIC2_STATUS & DOWRITE) {  // Slave Addr || 0x01 ==> Read
                IIC2_INT_CLR = (INTTX | CLR_TX_FIFO);
                IIC2_TXDATA = ucDDCCiTxBuffer[0];
                IIC2_INT_EN = (INTA | INTTX);
                ucDDCCiTxOut = 1;
            }
            else {  // Slave Addr ==> Write
                IIC2_INT_EN = (INTA | INTRX);
                IIC2_CFG |= SEND_ACK;
                ucDDCCiRxIn = 0;
                bDDCCmdUpdate = TRUE;
            }
        }

        while (IIC2_INT_FLG & INTTX) {
	            if (ucDDCCiTxOut != ucDDCCiTxIn) {
	                IIC2_TXDATA = ucDDCCiTxBuffer[ucDDCCiTxOut++];
	                IIC2_INT_CLR = INTTX;
	            }
	            else {
	                IIC2_TXDATA = ucDDCCiTxBuffer[ucDDCCiTxOut];
	                IIC2_INT_CLR = INTTX;
	                ucDDCCiTxOut = 0;
                }
		}

        while (IIC2_INT_FLG & INTRX) {
            ucDDCCiRxBuffer[ucDDCCiRxIn++] = IIC2_RXDATA;
            IIC2_INT_CLR = INTRX;
            bDDCCmdUpdate = TRUE;
            if (ucDDCCiRxIn > DDCCI_BUFFER_SIZE-1) {
                ucDDCCiRxIn = 2;
            }
        } 
        if (IIC2_INT_FLG & INTNAK) {
            IIC2_INT_CLR = 0xFF;//INTNAK;
        }
        if (IIC2_INT_FLG & INTLOST) {
            IIC2_INT_CLR = 0xFF;//INTLOST;
        }
    } //End if ((INT_SRC & INT_IIC2) != 0) 


	#if 0 //ENABLE_HDMI == ON
	    if (((INT_SRC & INT_SC) != 0) || ((INT_SRC & INT_HDMI) != 0)) {
	#else
	    if ((INT_SRC & INT_SC) != 0) {
	#endif

			#if ENABLE_FAST_BK_OFF == ON
				FastBLOff();
			#endif
		
			McuScalerIntDisable();
		
			#if 0 //ENABLE_HDMI == ON
			        McuScalerHDMIIntDisable();
			#endif

	        bModeChanged = TRUE;
	    }

	#if ENABLE_LOW_PWR_MODE == ON
	    usMCUCLKDIVIDERLoop = 0;
	#endif
}// End void IntExt0()

/**************************************************************************//**
 * Mcu external interrupt 1 service routine.
 ******************************************************************************/
void IntExt1(void) interrupt 2 using 3
{


#if ENABLE_LOW_PWR_MODE == ON
    SC_MCU_CLK_DIVIDER = 0x00;
#endif


    if ((INT_SRC & INT_IIC1) != 0) 
	{
        ucDdcciChannel = 1;
        if (IIC1_INT_FLG & INTA) {
            IIC1_INT_CLR = INTA;
            if (IIC1_STATUS & DOWRITE) {  // Slave Addr || 0x01 ==> Read
                IIC1_INT_CLR = (INTTX | CLR_TX_FIFO);
                IIC1_TXDATA = ucDDCCiTxBuffer[0];
                IIC1_INT_EN = (INTA | INTTX);
                ucDDCCiTxOut = 1;
            }
            else {  // Slave Addr ==> Write
                IIC1_INT_EN = (INTA | INTRX);
                IIC1_CFG |= SEND_ACK;
                ucDDCCiRxIn = 0;
                bDDCCmdUpdate = TRUE;
            }
        }

        while (IIC1_INT_FLG & INTTX) {
            if (ucDDCCiTxOut != ucDDCCiTxIn) {
                IIC1_TXDATA = ucDDCCiTxBuffer[ucDDCCiTxOut++];
                IIC1_INT_CLR = INTTX;
            }
            else {
                IIC1_TXDATA = ucDDCCiTxBuffer[ucDDCCiTxOut];
                IIC1_INT_CLR = INTTX;
                ucDDCCiTxOut = 0;
            }
        }

        while (IIC1_INT_FLG & INTRX) {
            ucDDCCiRxBuffer[ucDDCCiRxIn++] = IIC1_RXDATA;
            IIC1_INT_CLR = INTRX;
            bDDCCmdUpdate = TRUE;
            if (ucDDCCiRxIn > DDCCI_BUFFER_SIZE-1) {
                ucDDCCiRxIn = 2;
            }
        } 
        if (IIC1_INT_FLG & INTNAK) {
            IIC1_INT_CLR = 0xFF;//INTNAK;
        }
        if (IIC1_INT_FLG & INTLOST) {
            IIC1_INT_CLR = 0xFF;//INTLOST;
        }
    } //End if ((INT_SRC & INT_IIC1) != 0) 


    if ((INT_SRC & INT_IIC3) != 0) 
	{
        ucDdcciChannel = 3;
        if (IIC3_INT_FLG & INTA) {
            IIC3_INT_CLR = INTA;
            if (IIC3_STATUS & DOWRITE) {  // Slave Addr || 0x01 ==> Read
                IIC3_INT_CLR = (INTTX | CLR_TX_FIFO);
                IIC3_TXDATA = ucDDCCiTxBuffer[0];
                IIC3_INT_EN = (INTA | INTTX);
                ucDDCCiTxOut = 1;
            }
            else {  // Slave Addr ==> Write
                IIC3_INT_EN = (INTA | INTRX);
                IIC3_CFG |= SEND_ACK;
                ucDDCCiRxIn = 0;
                bDDCCmdUpdate = TRUE;
            }
        }

        while (IIC3_INT_FLG & INTTX) {
            if (ucDDCCiTxOut != ucDDCCiTxIn) {
                IIC3_TXDATA = ucDDCCiTxBuffer[ucDDCCiTxOut++];
                IIC3_INT_CLR = INTTX;
            }
            else {
                IIC3_TXDATA = ucDDCCiTxBuffer[ucDDCCiTxOut];
                IIC3_INT_CLR = INTTX;
                ucDDCCiTxOut = 0;
            }
        }

        while (IIC3_INT_FLG & INTRX) {
            ucDDCCiRxBuffer[ucDDCCiRxIn++] = IIC3_RXDATA;
            IIC3_INT_CLR = INTRX;
            bDDCCmdUpdate = TRUE;
            if (ucDDCCiRxIn > DDCCI_BUFFER_SIZE-1) {
                ucDDCCiRxIn = 2;
            }
        } 
        if (IIC3_INT_FLG & INTNAK) {
            IIC3_INT_CLR = 0xFF;//INTNAK;
        }
        if (IIC3_INT_FLG & INTLOST) {
            IIC3_INT_CLR = 0xFF;//INTLOST;
        }
    } //End if ((INT_SRC & INT_IIC3) != 0) 

#if ENABLE_LOW_PWR_MODE == ON
    usMCUCLKDIVIDERLoop = 0;
#endif


//---------------------------------------------
#if IR_REMOT_CTL == ON
	
   if((INT_SRC & INT_EXT) != 0) //is EX_INT
   {
   	   if((INTEXT_FLG & INTE2) != 0)//is EX_INT0 PIN
   	   {	
	   		INTEXT_EN &= ~INTE2;	//=0;	//&= ~INTE2;	//Disable INTE2			

			{// Test OK.
				if(ucTimer_IR==0xFF)
				{
					ucTimer_IR =0;	//START-interrupt IR Command
				}else if(ucTimer_IR==0xFE)
				{
					ucTimer_IR++;	// to 0xFF
					INTEXT_EN |= INTE2;
				}
			}			  
			INT_SRC = 0x00; 						//Clear interrupt source flags
			INTEXT_FLG = 0xFF;	//0xFF;	//INTEXT_FLG |= INTE2;		//Clear INT : can't delete this.

   	   }
   }
#endif 


}

/**************************************************************************//**
 * Mcu timer 0 interrupt service routine.
 ******************************************************************************/
void IntTimer0(void) interrupt 1 using 2
{
	/* (1) Timer0 Count */


#if ENABLE_NEW_TIMER == ON

	if(ucTimer_IR != 0xFF )
	{			
		++ucTimer_40us;
		if(ucTimer_40us >= 43)	//84 )		
		{
	    	ucTimer_40us = 0;		// count_1.680msec : 1 IR-Command cycle
			
			if(ucTimer_IR==0) 		// Fist Initial: Clear Data
				usData = 0;							


			if(ucTimer_IR < 13)			//Start ucTimer_IR counter 14 time
			{
				ucTimer_IR++;

				if( (PortC & BIT6) == BIT6) {	//bit High 
					usData <<= 1;					
					usData |= 0x0001;
				}
				else							//bit Low
					usData <<= 1;

			}else{						//End-interrupt IR Command
				usData = ~usData;
				usData = usData & 0x3FFF;

				//run ir.c -> IR_Process()
				usIRData = usData;
				bIrDetect = 1;

				ucTimer_IR  = 0xFF;		//End ucTimer_IR counter 14 time
				INTEXT_EN  |= INTE2;	//Enable INTE2
				INTEXT_FLG = 0xFF;		//Clear  INTE2 Flag
				INT_SRC = 0x00;			//Clear  INT_EXT Flag
				ucTimer_40us=0;
			}
		}
	} 


	++ucTimer_40to200us;
    if(bIsAPLLPowerDown == TRUE)
        ucTimer_40to200us = 0;
	else if(ucTimer_40to200us >= 5)
		ucTimer_40to200us=0;	// count_0.2msec
    else
		return;


    ++ucTimer_200us;
    if(SC_MCU_CLK_DIVIDER == 0x22 && ucTimer_200us >= 2)
        ucTimer_200us = 0;
    else if(ucTimer_200us >= 8 && bIsAPLLPowerDown == TRUE)
        ucTimer_200us = 0;
    else if( ucTimer_200us >= 5)
    	ucTimer_200us = 0;		// count_1msec	
    else
		return;


#else
	#if ENABLE_LOW_PWR_MODE == ON
		//George (Compiler use this)
		//    if (bLowPowerMode == TRUE) {//3MHz
	    if (SC_MCU_CLK_DIVIDER == 0x22) //3MHz
		{
	        TL0 = ucTL0_LOW_POWER_3M;
	        TH0 = ucTH0_LOW_POWER_3M;
	    }
	    else if (bIsAPLLPowerDown == TRUE) {
	#else
	    if (bIsAPLLPowerDown == TRUE) {
	#endif    

	        TL0 = ucTL0_LOW_POWER;
	        TH0 = ucTH0_LOW_POWER;
	    }
	    else 
		{	//source   0xEB2B: 1.005ms	(ucTL0_Normal_Power, ucTH0_Normal_Power)
			//ok       0xEB52: 1.000ms
	        TL0 = ucTL0_Normal_Power;
	        TH0 = ucTH0_Normal_Power;
	    }

    	TR0 = 1; //Start Timer 0

#endif 

	usTimerTick_1ms++;		// count_1msec ++



	/* (2) Light-Sensoer */
	#if ALS_EnDis == ALSMODE
		if(CkDevice_timer >0)
			CkDevice_timer--;
	#elif ALS_EnDis == ALSOffSET	
		if(CkDevice_timer >0)
			CkDevice_timer--;
	#elif ALS_EnDis == ALSRange
	
	#else	//Normal
	
	#endif	//#if ALS_EnDis == ENABLE


	/* (3) MHL InputSource */
	#if (INPUT_INTERFACE&INPUT_MHL0) || (INPUT_INTERFACE&INPUT_MHL1)
	    if ((ucMHLConnState == MHL_DISCOVERY_RDY) && (bCBUSAbort == 0)) 
		{
	//George (Compiler use this)
	        if ((usTimerTick_1ms - usTimerTickMHL) > SET_HPD_TIMER) //SET_HPD_TIMER
			{
	            if (!((MHL_GetMSCCmd() || MHL_GetDDCCmd()))) 
				{
	                SC_ADC_ZERO_POWER_CTRL |= (BIT7|BIT1);
	    //            MHLCbusTx(TX_DDC_CMD, CBUS_SET_HPD); //this is using 1
	                MHL_WaitCBusReady();
	                bTranCMD = 0;
	                ucCmdIndex = 0;//index to cMSCCmd
	                bCheckTimeout = 0;
	                SC_CBUS_MSC_CMD = CBUS_SET_HPD;
	                ucCBusState = CBUS_SETHPD;
	                ucMHLConnState = MHL_SET_HPD;
	                bWaitACK = 1;
	                usCBUSTimeoutACK = usTimerTick_1ms;

		    		#if 1//def E_DEBUG
		                if (bCBusArbFailFlag == TRUE) 
						{
		                    bCBusArbFailFlag = FALSE;
		                    SC_CBUS_MSC_CMD = CBUS_SET_HPD;
		                }
		    		#endif
	            }
	        }
	    }
	#endif

}//End void IntTimer0()






#if ENABLE_SERIAL_INT == ON
void IntUART(void) interrupt 4 using 1
{
	BYTE i;
	WORD wtemp;
	#if (XRS232 == ADS_RS232)
		UCHAR buf=0;
	
		if(RI)
		{
			RI=0;
			buf = SBUF;
	
			if( (buf !=0xAA) && (ucUARTRxIn == ucUARTRxOut) && (ucIsRecivCMDSS == 0) ) { 
				ucCntCmdLen = 0;
			}
			else if( (buf == 0xAA) && (ucCntCmdLen == 0) )	//george 20160219
			{
				ucUARTRxIn = ucUARTRxOut = 0;
				ucIsRecivCMDSS = 1;					// (1)_ACK	
				SBUF = 0xA0;						//send ACK
				TI=1;
			}else if(ucCntCmdLen < CMD_LEN) 		// Command length set: 4
			{			
				ucUARTRxBuffer[ucUARTRxIn] = buf;
				ucCntCmdLen++;	
			    if (++ucUARTRxIn > UART_RX_BUFFER_SIZE-1)
			        ucUARTRxIn = 0;
	
				if(ucCntCmdLen == CMD_LEN)
					ucIsRecivCMDSS = 2;				// (2)_CMD Len Finish !
			} 
		}
	
	    if (TI == 1) 
		{
        	TI = 0;
	        if (ucUARTTxIn != ucUARTTxOut) 
			{
				SBUF = ucUARTTxBuffer[ucUARTTxOut];
	            
				if (++ucUARTTxOut > UART_TX_BUFFER_SIZE-1)
	            	ucUARTTxOut = 0;
			}
	        else 
			{
				ucIsTransDisabled = 1;
			}
		}			
	#elif (XRS232 == LWO_RS232)
	 	if(RI)//!_testbit_(TI)) // check translate interrupt
		{
			RI = 0; // clear recieve interrupt

			if(g_UartCommand.Index<_UART_CMD_LENGTH_)
			g_UartCommand.Buffer[g_UartCommand.Index] = SBUF; // recieve byte
			// check command buffer index
	/*
			if(g_UartCommand.Index==0)		// Test for 'U'
				{
				if(g_UartCommand.Buffer[g_UartCommand.Index]==UART_CMD_START)
					sPutChar(UART_CMD_ACK);	// Return Ack
				else 
				{
					sPutChar(UART_CMD_NAK);								
				}
			}
					  
	
	*/		
			if (g_UartCommand.Index < _UART_CMD_LENGTH_) // still read command
			{	
		//		if(g_UartCommand.Buffer[0]==UART_CMD_START)
					if(g_UartCommand.Buffer[_UART_CMD_INDEX0_]==0x08)
					{
						g_UartCommand.Index++; // next index of command buffer					
					}
					else
					{
						g_UartCommand.Index=0;
						g_UartCommand.Buffer[_UART_CMD_INDEX0_]=0;
					}
											
				
			}
					
			
			if (g_UartCommand.Index == _UART_CMD_LENGTH_) // read command ok
				{
					for(i=0;i<7;i++)
					{
						checksumtemp = checksumtemp + g_UartCommand.Buffer[i];
						r_UartCommand.Buffer[i]=g_UartCommand.Buffer[i];
					}
				    
				    wtemp = 0x100-(WORD)checksumtemp;
			//       sPutChar('G');
			//if(g_UartCommand.Buffer[_UART_CMD_INDEX6_]==0x99)
					if(g_UartCommand.Buffer[_UART_CMD_INDEX7_]==wtemp)
					{
				gbUartDetected = TRUE; // command  buffer recieve ok
			//	sPutChar('G');
				  checksumtemp = 0;
					}
				g_UartCommand.Index = 0; // reset index of command buffer
			}	 
			
		}
/*
		if(TI)
		{
		
			TI = 0;
			if ( r_UartCommand.Index < UART_CMD_LENGTH)
			{
		  		SBUF = r_UartCommand.Buffer[r_UartCommand.Index++];
			}
			else
			{
		  		r_UartCommand.Index = 0;
			}
		}
*/
	#endif //#if (XRS232 == ENABLE)		

}//End IntUART(void) interrupt 4 using 1



	#if (XRS232 == ADS_RS232)
		UCHAR UART_Getchar(UCHAR *ptr)
		{
			UCHAR  i=0;
		
			if(ucIsRecivCMDSS < 2) {return 0;	}				// command data[] length not ready.
		
		
			if(ucIsRecivCMDSS == 2 )
			{
				while ( ucUARTRxIn != ucUARTRxOut ) 
				{	
					*ptr++ = ucUARTRxBuffer[ucUARTRxOut++];		//Start,  CMD(R/W,  Index(Item),  Value,  CRC
					
					if (ucUARTRxOut > UART_RX_BUFFER_SIZE-1)
		            	ucUARTRxOut = 0;
				}
				ucCntCmdLen=0;			// clear this is important.
				ucIsRecivCMDSS = 0;
		
				return 1;
			}
			return 0;
		}

		/**************************************************************************//**
		 * Put char into the TX buffer and enable UART transmission.
		 ******************************************************************************/
		static char UART_Putchar(UCHAR c)
		{
		    //If the buffer is full, return an error value.
		    if (((ucUARTTxIn+1)%UART_TX_BUFFER_SIZE) == ucUARTTxOut) return -1;
		
		    EA = 0;
		    ucUARTTxBuffer[ucUARTTxIn] = c;
		    if (++ucUARTTxIn > UART_TX_BUFFER_SIZE-1)
		        ucUARTTxIn = 0;
		    if (ucIsTransDisabled) 
			{
		        ucIsTransDisabled = 0;
		        TI = 1;
		    }
		    EA = 1;
		    
		    return 0;
		}
		
		/**************************************************************************//**
		 * The putchar function to replace the putchar in the standard library.
		 * @param c Character.
		 ******************************************************************************/
		char putchar(char c)
		{
		    USHRT i;
		    UCHAR k = 0;
		    while (UART_Putchar(c) != 0) 
			{
		        for (i = 0; i < 1000; i++) {}
		        if (++k > 10) {
		            TI = 1;
		        }
		    }
		    ResetWDTimer();
		    
		    return (c);
		}			
	#elif (XRS232 == LWO_RS232)
		BYTE sNibble2Ascii(BYTE bNibble)
		{
		    BYTE bAsciiChar;
		
		    if( bNibble <= 9 )
		        bAsciiChar = '0' + bNibble;
		    else
		        bAsciiChar = 'A' + (bNibble-10);
		    return bAsciiChar;
		}
		
		void sHex2Ascii(BYTE bHex, BYTE *pString)
		{
		    BYTE idata bHexTmp, bHexSize;
		    bHexTmp = bHex;
		    for( bHexSize=sizeof(bHex)*2; bHexSize > 0; --bHexSize)//Byte or WORD or DWORD
		    {
		       *(pString+bHexSize-1) = sNibble2Ascii(bHexTmp & 0x0F);
		       bHexTmp >>= 4;//right shift 4bit
		    }
		}
		
		void sPutChar(BYTE bTmp)
		{
		
		    ES = 0; // Enter Critical
		    SBUF = bTmp; // Put Char
		    while(!TI);//Wait the Transit flag be set
		    TI = 0; 
		    ES = 1; // Exit Critical
		
		}
		
		void sPutStr(BYTE code *ptTmpStr)
		{
		    BYTE bTmp; // character buffer
		
		    while (1)
		    {
		         bTmp = *ptTmpStr;// Get char
		         if (bTmp == '\0')break;          
		         sPutChar(bTmp); // Put Char
		         ptTmpStr++; // Next char
		    }
		}
		
		void sPutByteHex(BYTE bHex)
		{
		    BYTE idata abHex[2]; // output buffer
		    sHex2Ascii(bHex, abHex); // hexadecimal to ASCII code
		    sPutChar('0');
		    sPutChar('x');
		    sPutChar(abHex[0]); // high nibble
		    sPutChar(abHex[1]); // low nibble
		}
		void sPutWordHex(WORD wHex)
		{
		    UCHAR  idata abHex[2]; // output buffer
		    tdfWB idata wValue;
		
		    wValue.w=wHex;      
		    sHex2Ascii(wValue.b[0], abHex); // hexadecimal to ASCII code
		    sPutChar('0');
		    sPutChar('x');
		    sPutChar(abHex[0]); // high nibble
		    sPutChar(abHex[1]); // low nibble
		    sHex2Ascii(wValue.b[1], abHex); // hexadecimal to ASCII code 
		    sPutChar(abHex[0]); // high nibble
		    sPutChar(abHex[1]); // low nibble
		}
		
		void sPutWordDec(WORD wDec)
		{
		    tdfWB idata wValue;
		    BYTE  idata bValue;  
		    BYTE  idata bIndex;
		
		    wValue.w=wDec; 
		    if(wValue.w >= 10000)	
		     bIndex=0;
		    else if(wValue.w >= 1000)
		     bIndex=1; 
		    else if(wValue.w >= 100)  
		     bIndex=2;    		 
		    else if(wValue.w >= 10) 
		     bIndex=3;   
		    else if(wValue.w >= 1)   
		     bIndex=4;    
		    switch(bIndex)
		    {
			case 0://5 number space   
			       bValue = (wValue.w/10000) + 0x30;		// 10000
			       wValue.w%= 10000;
			       sPutChar(bValue); // 
			case 1://4 number space
			       bValue = (wValue.w/1000) + 0x30;		// 1000
			       wValue.w %= 1000;	
			       sPutChar(bValue); // 	
			case 2://3 number space 	         	
			       bValue = (wValue.w/100) + 0x30;		       // 100
			       wValue.w%= 100;	   
			       sPutChar(bValue); // 	
			case 3://2 number space   
			       bValue = (wValue.w/10) + 0x30;		       // 10
			       wValue.w %= 10;	
			       sPutChar(bValue);
			case 4://1 number space  
			       bValue =wValue.b[1] +0x30;	
			       sPutChar(bValue);	
			       break;
		     }		    
		}	
	#endif //#if (XRS232 == ENABLE)

#endif

/**************************************************************************//**
 * Get the current value of timer tick.
 * @return Timer ticks.
 ******************************************************************************/
USHRT GetTimerTick(void)
{
    idata USHRT timer;

    do {
        timer = usTimerTick_1ms;
    } while (timer != usTimerTick_1ms);

    return timer;
}

/**************************************************************************//**
 * Check the status of mode changed flag.
 * @return TRUE if mode changed flag is TRUE else FALSE.
 ******************************************************************************/
BOOL CheckModeChangeFlag(void)
{
    return bModeChanged;
}

/**************************************************************************//**
 * Clear the mode changed flag.
 ******************************************************************************/
void ClearModeChangeFlag(void)
{
    bModeChanged = FALSE;
}

/**************************************************************************//**
 * Set mode changed flag.
 * We use this function to force the system to perform the mode changed processes.
 ******************************************************************************/
void SetModeChangeFlag(void)
{
    bModeChanged = TRUE;
}


#if (INPUT_INTERFACE&INPUT_MHL0) || (INPUT_INTERFACE&INPUT_MHL1)
USHRT GetTimerTickInt() using 1
{
    return usTimerTick_1ms;
}
#endif


