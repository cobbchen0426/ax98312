/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/
#ifndef __BOARD_CONFIG_H__
#define __BOARD_CONFIG_H__

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************
#include "McuAPI.h"			// \Lib	( "8051.h", "McuReg.h", "Typedef.h" )
#include "Scaler.h"			// \Lib\NT68655_770_850 Series
#include "Typedef.h"		// \Lib

//******************************************************************************
// G L O B A L   D E F I N I T I O N S
//******************************************************************************
//Crystal Clock
#define REF_CLK                 12000000

//Scaler
#define PCBA_SCALER             NT68857

//Combine 8 bits into 1 byte
#define BitsToByte(b7,b6,b5,b4,b3,b2,b1,b0) ((b7<<7)|(b6<<6)|(b5<<5)|(b4<<4)|(b3<<3)|(b2<<2)|(b1<<1)|b0)



#if (BUILD_CUSTOMER == X_INP_VDH) || (BUILD_CUSTOMER == X_INP_DHP)	//X_ADS_AD907, X_ADS_AD908
	#define PORT_A_DEFAULT_OUT      BitsToByte( LOW,  LOW, HIGH, HIGH,  LOW, HIGH, HIGH, HIGH)		//150427 George [default-out-level], HIGH, HIGH)
	#define PORT_B_DEFAULT_OUT      BitsToByte(HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH)
	#define PORT_C_DEFAULT_OUT      BitsToByte( LOW, HIGH, HIGH,  LOW, HIGH, HIGH,  LOW, HIGH)	//150504 Geirge BitsToByte(LOW, HIGH, HIGH,LOW, HIGH, HIGH, LOW, HIGH)     //141208 mike 
	#define PORT_D_DEFAULT_OUT      BitsToByte(HIGH, HIGH, HIGH,  LOW, HIGH, HIGH, HIGH, HIGH)
	#define PORT_E_DEFAULT_OUT      BitsToByte(HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH)
	#define PORT_A_DEFAULT_DIR      BitsToByte( OUT, OUT,  OUT,  OUT,  OUT,   OUT,  OUT,   IN)	//150427 George [IN/OUT Config],  IN,  IN)  
	#define PORT_B_DEFAULT_DIR      BitsToByte( OUT, OUT,  OUT,  OUT,   IN,   OUT,   IN,   IN)
	#define PORT_C_DEFAULT_DIR      BitsToByte( OUT,  IN,  OUT,  OUT,  OUT,   OUT,  OUT,  OUT)	//150504 George BitsToByte( OUT, OUT, OUT, OUT, OUT,  OUT, OUT, OUT)
	#define PORT_D_DEFAULT_DIR      BitsToByte( OUT, OUT,  OUT,  OUT,  OUT,   OUT,  OUT,  OUT)
	#define PORT_E_DEFAULT_DIR      BitsToByte(  IN,  IN,   IN,   IN,   IN,   OUT,   IN,  OUT)
	 
	#define PORT_A_DEFAULT_PP       BitsToByte( LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW, HIGH)		//150427 George [don't know], LOW, HIGH)
	#define PORT_B_DEFAULT_PP       BitsToByte(HIGH, HIGH,  LOW,  LOW,  LOW, HIGH, HIGH,  LOW)		//150504 George PB1 is ALS.  LOW,  LOW)
	#define PORT_C_DEFAULT_PP       BitsToByte(HIGH, HIGH, HIGH, HIGH,  LOW,  LOW,  LOW,  LOW) 	//150504 George BitsToByte(HIGH, HIGH, HIGH,  HIGH,  LOW,  LOW,  LOW,  LOW)     //141210 mike 
	#define PORT_D_DEFAULT_PP       BitsToByte( LOW,  LOW,  LOW, HIGH,  LOW,  LOW,  LOW,  LOW)
	#define PORT_E_DEFAULT_PP       BitsToByte( LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW)
	#define PORT_3_DEFAULT_PP       BitsToByte( LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW)     //130702 mike 
	
	#define PORT_A_DEFAULT_PU       BitsToByte( LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW, HIGH)		//150427 George  [don't know], LOW, HIGH)
	#define PORT_B_DEFAULT_PU       BitsToByte( LOW,  LOW,  LOW,  LOW,  LOW, HIGH,  LOW,  LOW)
	#define PORT_C_DEFAULT_PU       BitsToByte(HIGH, HIGH,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW)	 	//150504 George BitsToByte(HIGH,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW)
	#define PORT_D_DEFAULT_PU       BitsToByte(HIGH, HIGH,  LOW, HIGH, HIGH, HIGH, HIGH, HIGH)
	#define PORT_E_DEFAULT_PU       BitsToByte( LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW)
	#define PORT_3_DEFAULT_PU       BitsToByte( LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW)
	

#elif BUILD_CUSTOMER == X_INP_DH	//X_AXI	// 20150608 george-create: for AX98310	
	#define PORT_A_DEFAULT_OUT      BitsToByte( LOW,  LOW, HIGH, HIGH,  LOW, HIGH, HIGH, HIGH)		//150427 George [default-out-level], HIGH, HIGH)
	#define PORT_B_DEFAULT_OUT      BitsToByte(HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH)
	#define PORT_C_DEFAULT_OUT      BitsToByte( LOW, HIGH, HIGH,  LOW, HIGH, HIGH,  LOW, HIGH)	//150504 Geirge BitsToByte(LOW, HIGH, HIGH,LOW, HIGH, HIGH, LOW, HIGH)     //141208 mike 
	#define PORT_D_DEFAULT_OUT      BitsToByte(HIGH, HIGH, HIGH,  LOW, HIGH, HIGH, HIGH, HIGH)
	#define PORT_E_DEFAULT_OUT      BitsToByte(HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH)
	#define PORT_A_DEFAULT_DIR      BitsToByte( OUT,  OUT,  OUT,  OUT,  OUT,  OUT,  OUT,   IN)	//150427 George [IN/OUT Config],  IN,  IN)  
	#define PORT_B_DEFAULT_DIR      BitsToByte( OUT,  OUT,  OUT,  OUT,   IN,  OUT,   IN,   IN)
	#define PORT_C_DEFAULT_DIR      BitsToByte( OUT,   IN,  OUT,  OUT,  OUT,  OUT,  OUT,  OUT)	//150504 George BitsToByte( OUT, OUT, OUT, OUT, OUT,  OUT, OUT, OUT)
	#define PORT_D_DEFAULT_DIR      BitsToByte( OUT,  OUT,  OUT,  OUT,  OUT,  OUT,  OUT,  OUT)
	#define PORT_E_DEFAULT_DIR      BitsToByte(  IN,   IN,   IN,   IN,   IN,  OUT,   IN,  OUT)
	 
	#define PORT_A_DEFAULT_PP       BitsToByte( LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW, HIGH)		//150427 George [don't know], LOW, HIGH)
	#define PORT_B_DEFAULT_PP       BitsToByte(HIGH, HIGH,  LOW,  LOW,  LOW,  LOW, HIGH,  LOW)		//150504 George PB1 is ALS.  LOW,  LOW)
	#define PORT_C_DEFAULT_PP       BitsToByte(HIGH, HIGH, HIGH, HIGH,  LOW,  LOW,  LOW,  LOW) 	//150504 George BitsToByte(HIGH, HIGH, HIGH,  HIGH,  LOW,  LOW,  LOW,  LOW)     //141210 mike 
	#define PORT_D_DEFAULT_PP       BitsToByte( LOW,  LOW,  LOW, HIGH,  LOW,  LOW,  LOW,  LOW)
	#define PORT_E_DEFAULT_PP       BitsToByte( LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW)
	#define PORT_3_DEFAULT_PP       BitsToByte( LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW)     //130702 mike 
	
	#define PORT_A_DEFAULT_PU       BitsToByte( LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW, HIGH)		//150427 George  [don't know], LOW, HIGH)
	#define PORT_B_DEFAULT_PU       BitsToByte( LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW)
	#define PORT_C_DEFAULT_PU       BitsToByte(HIGH, HIGH,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW)	 	//150504 George BitsToByte(HIGH,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW)
	#define PORT_D_DEFAULT_PU       BitsToByte(HIGH, HIGH,  LOW, HIGH, HIGH, HIGH, HIGH, HIGH)
	#define PORT_E_DEFAULT_PU       BitsToByte( LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW)
	#define PORT_3_DEFAULT_PU       BitsToByte( LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW)
	
#endif

#define MCU_ADC_CON_DEFAULT     BitsToByte( LOW, LOW,  LOW,  LOW, HIGH, LOW, HIGH,  HIGH)		// ADC3:5V-DET, ADC1:ALS,  ADC0:OSD
#define POWER_DETEC_ADC         MCU_ADC_3
#define POWER_THRESHOLD         0x40
#define LPD_INPUT_PIN           0 				//0/1
#define LPD_THRESHOLD           0xDB

#define MCU_PWM_CON_DEFAULT     BitsToByte( LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW)<<8 | \
                                				  BitsToByte( LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW)
#define MCU_PWM_0_DEFAULT       0x00
#define MCU_PWM_1_DEFAULT       0x00
#define MCU_PWM_2_DEFAULT       0x00
#define MCU_PWM_3_DEFAULT       0x00
#define MCU_PWM_4_DEFAULT       0x00
#define MCU_PWM_5_DEFAULT       0x00
#define MCU_PWM_6_DEFAULT       0x00
#define MCU_PWM_7_DEFAULT       0x00
#define MCU_PWM_8_DEFAULT       0x00
#define MCU_PWM_9_DEFAULT       0x00
#define MCU_PWM_10_DEFAULT      0x00
#define MCU_PWM_11_DEFAULT      0x00

//Each bit indicates one DDC channel,               NONE  NONE  NONE  NONE  DDC3  DDC2  DDC1  DDC0
#define MCU_DDC_CON_DEFAULT     BitsToByte( LOW,  LOW,  LOW,  LOW, LOW,  HIGH, HIGH,  HIGH)		//150424 George, DDC0 is LOW)      

//DDC I2C slave address
#define MCU_DDC0_ADDRESS        0xA0 	//Same as 24C02
#define MCU_DDC0_EDIDLEN        0 	   	//EDID Length: 0:128 bytes, 1:256 bytes
//------------------------
#define MCU_DDC1_ADDRESS        0xA0
#ifdef USE_X18_BOARD
#define MCU_DDC1_EDIDLEN        1
#else
#define MCU_DDC1_EDIDLEN        0
#endif
//------------------------
#define MCU_DDC2_ADDRESS        0xA0
#define MCU_DDC2_EDIDLEN        1
//------------------------
#define MCU_DDC3_ADDRESS        0xA0
#define MCU_DDC3_EDIDLEN        1
//------------------------
#define MCU_IIC_CON_DEFAULT     BitsToByte( LOW,  LOW,  LOW,  LOW, LOW, HIGH, HIGH, HIGH)
#define MCU_IIC0_ADDRESS        0x6E
#define MCU_IIC1_ADDRESS        0x6E
#define MCU_IIC2_ADDRESS        0x6E
#define MCU_IIC3_ADDRESS        0x6E

//Use internal EDID
#define USE_INTERNAL_EDID       1
#define VGA_DDC_CHANNEL         0x00	//150423 George(En_VGA)     0xFF // Channel from 0 ~ 3 

#ifdef USE_X18_BOARD
#define DVI_DDC_CHANNEL         0xFF // 0xFF means no use
#define HDMI_DDC_CHANNEL        0x01
#else
#define DVI_DDC_CHANNEL         0x01 // 0xFF means no use
#define HDMI_DDC_CHANNEL        0x02	
#endif

#define DP_DDC_CHANNEL          0x03	//150424 George(define at Scaler_DP.c)		0x03     
#define MHL_DDC_CHANNEL         0x00	//150424 George(define at MHL.c)	0x00

//CHIU--------------------------------------------------------------------------------
#ifdef TX38D09VM0CAA
//Backlight control
#define BACKLIGHT_PORT 			MCU_PORT_A //C //FEFANJACKY FOR TATUNG 1280X242 PANEL
#define BACKLIGHT_BIT 			BIT2 			//1
#define BACKLIGHT_ACTIVE 		LOW
#else
//Backlight control
#define BACKLIGHT_PORT          MCU_PORT_C       
#define BACKLIGHT_BIT             BIT1
#define BACKLIGHT_ACTIVE        HIGH				//20150608, HIGH (AX98310: set_LOW, AD908_V2:set_LOW;  AD908_V1:set_High)
#endif
//--------------------------------------------------------------------------------------
//POWER SUPPLY ON                              //FEFANJACKY
#define PSB_PORT                MCU_PORT_D
#define PSB_BIT                 BIT2
#define PSB_ACTIVE              HIGH
//----------------------------------------		
//LED green control
#define LED_GREEN_PORT          MCU_PORT_A         	// 
#define LED_GREEN_BIT             BIT6                     	// 
#define LED_GREEN_ACTIVE       HIGH                		 // 
//LED red control
#define LED_RED_PORT            	  MCU_PORT_A		// 
#define LED_RED_BIT                 BIT7  			  	// 
#define LED_RED_ACTIVE           HIGH 			       // 
//----------------------------------------
//Panel power control
#define PANEL_POWER_PORT        MCU_PORT_C
#define PANEL_POWER_BIT           BIT7
#define PANEL_POWER_ACTIVE     HIGH				//  
//VGA cable connection
#define VGA_CABLE_PORT          MCU_PORT_A
#define VGA_CABLE_BIT           BIT1
#define VGA_CABLE_ACTIVE        LOW
//-----------------------------------------
//Digital interface 0 cable connection
#define DIGI0_CABLE_PORT        MCU_PORT_NULL
#define DIGI0_CABLE_BIT         BIT7
#define DIGI0_CABLE_ACTIVE      LOW
//Digital interface 1 cable connection
#define DIGI1_CABLE_PORT        MCU_PORT_E
#define DIGI1_CABLE_BIT         BIT3
#define DIGI1_CABLE_ACTIVE      LOW
//-----------------------------------------
//DP interface cable connection
#define DP_CABLE_PORT           	MCU_PORT_A				     
#define DP_CABLE_BIT            		BIT6
#define DP_CABLE_ACTIVE         	LOW
//-----------------------------------------
//NVRAM configuration
#define NVRAM_SDA_PORT          MCU_PORT_3
#define NVRAM_SDA_BIT             BIT5
#define NVRAM_SCL_PORT           MCU_PORT_3
#define NVRAM_SCL_BIT              BIT4
#define NVRAM_WP_PORT            MCU_PORT_C
#define NVRAM_WP_BIT               BIT0
#define NVRAM_WP_ACTIVE         HIGH
//FLASH
#define FLASH_WP_PORT           MCU_PORT_A
#define FLASH_WP_BIT              BIT3
#define FLASH_WP_ACTIVE        LOW
//EDID 24C02
#define EDID_WP_PORT            MCU_PORT_E
#define EDID_WP_BIT               BIT2
#define EDID_WP_ACTIVE         HIGH
//Audio configuration
#define AUDIO_LINE_IN           LINE_IN1 //(LINE_IN1/LINE_IN2)
#define AUDIO_OUT                  LINE_OUT //(LINE_OUT/IIS_OUT)
//-------------------------------------------							    
//Volume control
#define VOLUME_PWM_PORT                 PWM_A 
#define VOLUME_PWM_POL                   HIGH
#define VOLUME_PWM_OUTPUT_PIN    PWMA_PIN_67
//--------------------------------------------
//Audio mute control
/*
#define AMP_MUTE_PORT           MCU_PORT_C
#define AMP_MUTE_BIT              BIT6
#define AMP_MUTE_ACTIVE        HIGH
*/
//--------------------------------------------
//Audio mute control
#define AMP_MUTE_PORT          	MCU_PORT_A		//150427 George, MCU_PORT_C
#define AMP_MUTE_BIT            	BIT1		//150427 George, BIT6
#define AMP_MUTE_ACTIVE         	HIGH						
//--------------------------------------------
//Audio power control
#define AMP_PWR_PORT            	MCU_PORT_NULL
#define AMP_PWR_BIT             		BIT1
#define AMP_PWR_ACTIVE         	LOW
//CHIU--------------------------------------------------------------
#ifdef TX38D09VM0CAA
//DIM configuration
#define BKL_PWM_PORT 				PWM_A 
#define BKL_PWM_POL 				HIGH
#define BKL_PWM_OUTPUT_PIN 		PWMA_PIN_67 
#else
//DIM configuration
#define BKL_PWM_PORT            	PWM_D 					//
#define BKL_PWM_POL             		PWM						//    
#define BKL_PWM_OUTPUT_PIN      PWMD_PIN_125 			//
#endif
//--------------------------------------------------------------------
//Hotplug configuration
#define DIG0_HPD_PORT           MCU_PORT_NULL
#define DIG0_HPD_BIT            BIT5
#define DIG0_HPD_ACTIVE         HIGH
#define DIG1_HPD_PORT           MCU_PORT_C
#define DIG1_HPD_BIT            BIT2
#define DIG1_HPD_ACTIVE         HIGH
#define DP_HPD_PORT             MCU_PORT_D
#define DP_HPD_BIT              BIT4
#define DP_HPD_ACTIVE           HIGH
//POWER MOS configuration
#define POWER_MOS_PORT          MCU_PORT_NULL
#define POWER_MOS_BIT           BIT1
#define POWER_MOS_ACTIVE        HIGH
//FPGA configuration
#if (INPUT_INTERFACE&INPUT_DP)
#define FPGA_SDA_PORT           MCU_PORT_C
#define FPGA_SDA_BIT            BIT2
#define FPGA_SCL_PORT           MCU_PORT_C
#define FPGA_SCL_BIT            BIT3
#else
#define FPGA_SDA_PORT           MCU_PORT_3
#define FPGA_SDA_BIT            BIT4
#define FPGA_SCL_PORT           MCU_PORT_3
#define FPGA_SCL_BIT            BIT5
#endif

//Panel power extra delay (This is an extra delay according to the PCB)
#define PANEL_POWER_DELAY       200

//R1 / R2 setting for OVP
#define OVP_RLOWER              1
#define OVP_RUPPER              30

/*******************************************************************************
               HDCP-related and digital(HDMI) interface Setting
*******************************************************************************/
//HDCP MUX
#define DIGITAL_INPUT0_HDCP_MUX 2
#define DIGITAL_INPUT1_HDCP_MUX 1

//AUDIO INPUT
#define DIGITAL_INPUT0_HDMI_AUDIO 1
#define DIGITAL_INPUT1_HDMI_AUDIO 1

//DIGITAL RX0/RX2 SWAP (NT68674 series only)
#define DIGITAL0_CHANNEL_SWAP   0
#define DIGITAL1_CHANNEL_SWAP   0

//CEC Channel
#define HDMI_CEC_CHANNEL        0

//LVDS
#define ENABLE_LVDS_POL_SWAP    OFF

//MHL
#define SET_IO_VBUS_ACTIVE  HIGH /*!< VBus set high/low to charge. */

/*******************************************************************************
                           Keypad interface setting
*******************************************************************************/
// Specific AD port of AD key
#define KEY_GROUP1_ADC          MCU_ADC_0

#if (ALS_EnDis == ALSRange)
	#define LS3101_ADC          MCU_ADC_1		// LS3101: ADC Ambient-Light-Sensor

#else
	#define KEY_GROUP2_ADC          MCU_ADC_1
#endif //#if ALS_EnDis == ENABLE

// Specific IO port of IO key
#define IOBTN_1_PORT            MCU_PORT_A
#define IOBTN_1_BIT             BIT0
#define IOBTN_1_ACTIVE          LOW
#define IOBTN_2_PORT            MCU_PORT_NULL
#define IOBTN_2_BIT             BIT4
#define IOBTN_2_ACTIVE          LOW
#define IOBTN_3_PORT            MCU_PORT_NULL
#define IOBTN_3_BIT             BIT5
#define IOBTN_3_ACTIVE          LOW
#define IOBTN_4_PORT            MCU_PORT_NULL
#define IOBTN_4_BIT             BIT6
#define IOBTN_4_ACTIVE          LOW
#define IOBTN_5_PORT            MCU_PORT_NULL
#define IOBTN_5_BIT             BIT7
#define IOBTN_5_ACTIVE          LOW
#define IOBTN_6_PORT            MCU_PORT_NULL
#define IOBTN_6_BIT             BIT1
#define IOBTN_6_ACTIVE          LOW
#define IOBTN_7_PORT            MCU_PORT_NULL
#define IOBTN_7_BIT             BIT1
#define IOBTN_7_ACTIVE          LOW
#define IOBTN_8_PORT            MCU_PORT_NULL
#define IOBTN_8_BIT             BIT1
#define IOBTN_8_ACTIVE          LOW

/*******************************************************************************
                               LED String Define
*******************************************************************************/
#define PCBA_LEDSTR_PARALLEL    0
#define PCBA_LEDSTR_EN          BitsToByte(LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW)

//******************************************************************************
// G L O B A L   V A R I A B L E S
//******************************************************************************

//******************************************************************************
// S T A T I C   V A R I A B L E S
//******************************************************************************

//******************************************************************************
// E X T E R N A L   V A R I A B L E   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// S T A T I C   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// E X T E R N A L   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************

#endif //__BOARD_CONFIG_H__
