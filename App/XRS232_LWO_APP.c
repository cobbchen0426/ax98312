/******************************************************************************/
/*                    Axiomdisplay CO,, LTD.                                  */
/*                    All Rights Reserved                                     */
/*                    XRS232 Remote Controller APP Function                   */
/******************************************************************************/

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************
#include "Include.h"


#if (XRS232 == LWO_RS232)

/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/
/******************************************************************************/
/*       Uart.c                                                                 */
/*       Release Date:2015/09/11       Last Maintenance:2015/09/11            */
/*       Original Version:2.2.00       Last Version:2.2.00                    */
/*       Coding By: Cobb               Maintenance By: Cobb                   */
/******************************************************************************/

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************
#include "Include.h"

//******************************************************************************
// S T A T I C   V A R I A B L E S
//******************************************************************************

void SupportACK(void)
{
/*
	sPutChar('+');
	sPutChar(0x0d);
*/
	BYTE checksum=0,i;
	WORD temp;
	

	r_UartCommand.Buffer[_UART_CMD_INDEX5_]=0xff;		// ack 
	for(i=0;i<7;i++)
	{
		checksum = checksum +r_UartCommand.Buffer[i];
	}
	temp = 0x100- (WORD)checksum;
	r_UartCommand.Buffer[_UART_CMD_INDEX7_] = (BYTE)temp;
	for(i=0;i<8;i++)
	{
	sPutChar(r_UartCommand.Buffer[i]);
	}
//	TI=1;

}

void NoSupportACK(void)
{
//	sPutChar('-');
//	sPutChar(0x0d);
 	BYTE i;
	g_UartCommand.Index = 0; // reset index of command buffer
	r_UartCommand.Index = 0; // reset index of command buffer


	for(i=0;i<8;i++)
	{
		g_UartCommand.Buffer[i]=0;
		r_UartCommand.Buffer[i]=0;
	}

}

void ReturnCommand(int wTemp)
{
	int i;
	xdata BYTE bData[6];
		
	bData[0]=0x35;
	bData[1]=wTemp/1000+0x30;
	bData[2]=wTemp/100 + 0x30;
	bData[3]=(wTemp%100)/10 + 0x30;
	bData[4]=wTemp%10+ 0x30;
	bData[5]=0x0d;
	
	for(i=0;i<6;i++)
		sPutChar(bData[i]);

}

//******************************************************************************
// Prototype: 
//  void UartHandler(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Uart Handling
// Notes:
//  None
//******************************************************************************
void UartHandler(void)
{
//	int wValue;
	if(gbUartDetected)
	{

		gbUartDetected = 0;   // command  buffer clear
	

//		wValue = (g_UartCommand.Buffer[_UART_CMD_INDEX1_]-0x30)*100+(g_UartCommand.Buffer[_UART_CMD_INDEX2_]-0x30)*10+(g_UartCommand.Buffer[_UART_CMD_INDEX3_]-0x30);
//		for(i=0;i<6;i++)
//			sPutChar(g_UartCommand.Buffer[i]);

//		mPrintfWordDec("Value = ",wValue);

		switch(g_UartCommand.Buffer[_UART_CMD_INDEX2_])			// switch command 
		{
//------------------------------Set-----------------------------------		
			case 0xfe:	// power on off
				if(g_UartCommand.Buffer[_UART_CMD_INDEX5_]==0)		// write
				{
					if( (g_UartCommand.Buffer[_UART_CMD_INDEX6_]==0) && (UserData.bPowerStatus==ON) )     
					{
						SupportACK();  
						UserData.bPowerStatus = OFF;  
						SYSAPI_SetPowerOff();
					}	// power off
					else if((g_UartCommand.Buffer[_UART_CMD_INDEX6_]==1) && (UserData.bPowerStatus==OFF)) 
					{
						SupportACK();  
						UserData.bPowerStatus = ON;   
						SYSAPI_SetPowerOn();  
						UserSetInputSource();
					}// power on
				}
				else
				{
					g_UartCommand.Buffer[_UART_CMD_INDEX6_]= UserData.bPowerStatus;
					SupportACK();
				}
				break;

			case 0x02:		// input source (for Customer's Define): 000_VGA, 001_DVI, 002_USB, 003_DP, 007_OPS, 008_HDMI1, 009_HDMI2

				if(g_UartCommand.Buffer[_UART_CMD_INDEX5_]==0)		// write
				{
					if((g_UartCommand.Buffer[_UART_CMD_INDEX6_] == 0) && (UserData.ucInputSource != INPUT_SC_VGA))		
					{	
						SupportACK();	
						UserData.ucInputSource =INPUT_SC_VGA;	
						UserSetInputSource();
					}	// NT68856=0_VGA,  APP=0_VGA
					else if((g_UartCommand.Buffer[_UART_CMD_INDEX6_] == 2)  && (UserData.ucInputSource !=INPUT_SC_DVI) )	
					{
						SupportACK();	
						UserData.ucInputSource =INPUT_SC_DVI;	
						UserSetInputSource();
					}	// NT68856=2_DVI,  APP=1_DVI
				//else if((wValue == 2)&& (UserData.ucInputSource != "INPUT_USB"))  {SupportACK();	UserData.ucInputSource =INPUT_SC_DVI;	UserSetInputSource();}	// NT68856= none

				//else if((wValue == 8)  && (UserData.ucInputSource !=INPUT_SC_HDMI1)){SupportACK();	UserData.ucInputSource =INPUT_SC_HDMI1;	UserSetInputSource();}	// NT68856=5_HDMI, APP=8_HDMI1
				//else if((wValue == 6)  && (UserData.ucInputSource !=INPUT_SC_DP))	{SupportACK();	UserData.ucInputSource =INPUT_SC_DP;	UserSetInputSource();}	// NT68856=9_DP,   APP=6_DP
				
				}
				else	// read
				{
					if(UserData.ucInputSource==INPUT_SC_VGA)
						r_UartCommand.Buffer[_UART_CMD_INDEX6_]= 0;
					else if(UserData.ucInputSource==INPUT_SC_DVI)
						r_UartCommand.Buffer[_UART_CMD_INDEX6_]= 2;

					SupportACK();
				
				}
				break;

			case 0x01: 			// contrast
				if(g_UartCommand.Buffer[_UART_CMD_INDEX5_]==0)		// write
				{
					if(g_UartCommand.Buffer[_UART_CMD_INDEX6_]<=100)
					{
							
					//	mPrintfByte("Contrast = ",g_UartCommand.Buffer[_UART_CMD_INDEX6_]);
						UserData.ucContrast = g_UartCommand.Buffer[_UART_CMD_INDEX6_];
						UserSetContrast();	    
					//	NvramWriteUserData(&UserData);
						UserDataWriteFlag=1;
						SupportACK();
					}
				}
				else
				{
					r_UartCommand.Buffer[_UART_CMD_INDEX6_]= UserData.ucContrast;
					SupportACK();	
				}
				break;
			case 0x00:	// Brightness
/*			
				if(wValue<=100)
				{
					SupportACK();	
					UserData.ucBrightness = wValue;
					UserSetBrightness();	    
					NvramWriteUserData(&UserData);	//can't find: SetOSDUpdUsrFlag();			
				}
				else
				{
				
					NoSupportACK(); 
				}
*/
				if(g_UartCommand.Buffer[_UART_CMD_INDEX5_]==0)		// write
				{
					if(g_UartCommand.Buffer[_UART_CMD_INDEX6_]<=100)
					{
					
						UserData.ucBrightness = g_UartCommand.Buffer[_UART_CMD_INDEX6_];
						UserSetBrightness();		
				//		NvramWriteUserData(&UserData);
						UserDataWriteFlag=1;
						SupportACK();
					}
				}
				else
				{
					r_UartCommand.Buffer[_UART_CMD_INDEX6_]= UserData.ucBrightness;
					SupportACK();	
				}
				break;



			default:
				NoSupportACK();
				break;				
		}
	
	}
}


#endif //#if XRS232
