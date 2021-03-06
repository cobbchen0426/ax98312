/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/
#ifndef __MODELCONFIG_H__
#define __MODELCONFIG_H__

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************
#include "ScalerCfg.h"

//******************************************************************************
// G L O B A L   D E F I N I T I O N S
//******************************************************************************

/*******************************************************************************
                              Define Board/Keypad
*******************************************************************************/
#define BOARD_TYPE                 NT68857_DEMO_BOARD
#define KEYPAD_TYPE                NT68850_DEMO_KEYPAD
					 
/*******************************************************************************
                              Model Feature On/Off
*******************************************************************************/
// Scaler
#define MD_SCALER_TYPE             NT68857

//UART Output Selection
#define MD_MCU_UART_OUTPUT         0 //TX/RX

//MCU Configuration
#define MD_MCU_CLK_TIMES           5 //MCU CLOCK = MCU_CLK_TIMES * REF_CLK
#define MD_MCU_UART_BAUD_RATE      9600 //Bit per second //140304 mike for RS232

//Input source type multi-selection
// (at \Lib\ScalerCfg\NT68857\SCALERCFG.H)     (INPUT_VGA0|INPUT_YPbPr0|INPUT_DIG0|INPUT_DIG1|INPUT_MHL0|INPUT_DP)
						    //bk    (INPUT_VGA0 | INPUT_DIG0 | INPUT_DIG1 | INPUT_MHL0 | INPUT_DP  )
#if BUILD_CUSTOMER == X_INP_DHP	//X_ADS_AD907
	#define MD_INPUT_INTERFACE    	(             INPUT_DIG0 | INPUT_DIG1 | INPUT_MHL0 | INPUT_DP  )  //150424 George(En_VGA, Dis_MHL0  Dis_DP) 	(INPUT_DIG0|INPUT_DIG1|INPUT_MHL0|INPUT_DP)   
	#define MODEL_INPUT_VGA0        INPUT_SC_NULL	//INPUT_SC_VGA
	#define OSD_DP_SHOW		ENABLE

#elif BUILD_CUSTOMER == X_INP_VDH	//X_ADS_AD908
	#define MD_INPUT_INTERFACE    	(INPUT_VGA0 | INPUT_DIG0 | INPUT_DIG1 | INPUT_MHL0 | INPUT_DP  )  //150424 George(En_VGA, Dis_MHL0  Dis_DP) 	(INPUT_DIG0|INPUT_DIG1|INPUT_MHL0|INPUT_DP)   
	#define MODEL_INPUT_VGA0        INPUT_SC_VGA	//INPUT_SC_NULL
	#define OSD_DP_SHOW		DISABLE

#elif BUILD_CUSTOMER == X_INP_DH	//X_AXI
	#define MD_INPUT_INTERFACE    	(             INPUT_DIG0 | INPUT_DIG1 | INPUT_MHL0 | INPUT_DP  )  //150424 George(En_VGA, Dis_MHL0  Dis_DP) 	(INPUT_DIG0|INPUT_DIG1|INPUT_MHL0|INPUT_DP)   
	#define MODEL_INPUT_VGA0        INPUT_SC_NULL	//INPUT_SC_VGA
	#define OSD_DP_SHOW		DISABLE
#else
#endif 



#define MODEL_INPUT_VGA1        INPUT_SC_NULL
#define MODEL_INPUT_DIG0        INPUT_SC_HDMI1				//140305 mike   

#ifdef USE_X18_BOARD
#define MODEL_INPUT_DIG1        INPUT_SC_HDMI 
#else
#define MODEL_INPUT_DIG1        INPUT_SC_DVI  
#endif 

#define MODEL_INPUT_DIG2        INPUT_SC_DP		//150424 George(Dis_DP)		INPUT_SC_DP
#define MODEL_INPUT_YPbPr0      INPUT_SC_NULL
#define MODEL_INPUT_YPbPr1      INPUT_SC_NULL
						 
#define MD_ENABLE_LOW_PWR_MODE     ON //ON/OFF
#define MD_ENABLE_CHECK_SYS5V      OFF //ON/OFF
#define MD_ENABLE_LPD              OFF //ON/OFF Only NT68650, NT68660 and newer scaler can define ON
#define MD_ENABLE_HDCP             ON //ON/OFF
#define MD_ENABLE_HDCP_KEY_DCRPT   ON //ON/OFF
#define MD_ENABLE_DEMO_HDCP_KEY    ON //ON/OFF
#define MD_ENABLE_NVT_HDCP_WRITER  OFF //ON/OFF
#define MD_ENABLE_HDCP_TRIM_MODE   OFF //ON/OFF
#define MD_ENABLE_GAMMA            ON //ON/OFF
#define MD_ENABLE_OD               OFF //ON/OFF
#define MD_ENABLE_OD_TRANSFORM     OFF //ON/OFF
#define MD_ENABLE_MMU              OFF //ON/OFF
#define MD_ENABLE_FE2P             ON //ON/OFF  //FE2P V3041 DC-IN AUTO-TUNE ,USE V2411
#define MD_ENABLE_DIRECT_FE2P      OFF //ON/OFF 
#define MD_ENABLE_HDMI             ON //ON/OFF
#define MD_ENABLE_HDMI_PRETEST     OFF //ON/OFF
#define MD_ENABLE_HW_CEC           OFF //ON/OFF
#define MD_ENABLE_DBC              OFF //ON/OFF
#define MD_ENABLE_DBC_HW_DEBOUNCE  ON //ON/OFF
#define MD_ENABLE_DIGI1_HPD        ON //ON/OFF
#define MD_ENABLE_DIGI0_HPD        ON //ON/OFF
#define MD_ENABLE_DP_HPD           ON //ON/OFF
#define MD_ENABLE_DP_ADV_HPD       ON //ON/OFF
#define MD_ENABLE_SCALER_AUDIO     ON //ON/OFF 
#define MD_ENABLE_INTERNAL_AUDIO_BUZZER OFF //ON/OFF Only HDMI can define it ON
#define MD_ENABLE_OSD_WINDOWS      ON //ON/OFF
#define MD_ENABLE_OSD_ROTATION     OFF //ON/OFF
#define MD_ENABLE_OSD_MIRROR       OFF //ON/OFF
#define MD_ENABLE_OSD_FLIP         OFF //ON/OFF
#define MD_ENABLE_INTERNAL_LDO     OFF //ON/OFF
#define MD_ENABLE_INTERNAL_ADC_LDO OFF //ON/OFF
#define MD_ENABLE_EMBEDDED_CHECKSUM OFF //ON/OFF
#define MD_ENABLE_OVERSCAN         ON //ON/OFF Only NT68676 can define ON
#define MD_ENABLE_PWM_SMOOTH       OFF //ON/OFF Must be defined as OFF over NT68671~5
#define MD_ENABLE_FLASH_IDLE_MODE  ON //ON/OFF Only NT68660 & NT68650 can define ON
#define MD_ENABLE_NR_BYTIMING      ON //ON/OFF
#define MD_ENABLE_LD               OFF //ON/OFF Only NT68750 can define ON
#define MD_ENABLE_SR               ON //ON/OFF Only NT68750 can define ON
#define MD_ENABLE_SELF_AUTOCOLOR   OFF //ON/OFF
#define MD_ENABLE_HW_AUTOCOLOR     OFF //ON/OFF
#define MD_ENABLE_SCALER_3D        ON //ON/OFF
#define MD_ENABLE_PREFRC	       OFF //ON/OFF
#define MD_ENABLE_DFR              OFF //ON/OFF
#define MD_ENABLE_DEMO_DP_EDID     ON //OFF //ON/OFF		//150424 George(OFF, Dis_DP)	//ON
#define MD_ENABLE_DEMO_MHL_EDID    ON //OFF //ON/OFF		//150424 George(OFF, Dis_MHL)	//ON
#define MD_ENABLE_DP_AUX_MONITOR   OFF //ON/OFF 


//Over scan ratio
//  0 ~ 10 %
#define OVER_SCAN_RATIO         5
//#define FRC_V_FREQ				60
//#define FRC_NACT_MIN            480
//#define FRC_NACT_MAX            620//760


/*******************************************************************************
                               Define F/W Version
*******************************************************************************/
//Version and Date
#define VERSION                 0x01	//0x02
#define REVERSION               0x00	//0x20
#define FIRMWARE_VER            (VERSION<<8 | REVERSION)
//#define DATE                    "2015-09-22"	//"2013-11-12"  //"2010-10-01"



/*******************************************************************************
                      Define Limitations for Out Of Range
*******************************************************************************/
//OOR: H/V frequency limitation, pixel clock limitation
#define MIN_H_FREQ              150	// 80 //g 140	//george 150 //0.1KHz
#define MAX_H_FREQ              947 //0.1KHz
#define MIN_V_FREQ              200	//170 // 200 //0.1Hz
#define MAX_V_FREQ              860	//1200	//george 860 //0.1Hz
#define MAX_ANALONG_PIXEL_CLOCK 205 //MHz

/*******************************************************************************
                      Define Limitations for Out Of Limit
*******************************************************************************/
#define MIN_V_FREQ_LMT          500	//170 //200 //g 500 //0.1Hz
#define MAX_V_FREQ_LMT          840	//990	//george 840 //0.1Hz

/*******************************************************************************
                                Sync-Stable Time
                             Time To Change Source
                                 HPD Low Period
*******************************************************************************/
//Timer for waiting sync stable
#define SYNC_STABLE_TIME        100//ms

//Changing PORT delay when searching input sync (VGA-->DVI-->HDMI-->...)
#define SYNCSRC_TIME_ANALOG0    1000  //1000
#define SYNCSRC_TIME_DIGITAL0   3000    //500
#define SYNCSRC_TIME_ANALOG1    1000    //500
#define SYNCSRC_TIME_DIGITAL1   3000 //HDMI=3000; DVI=1000
#define SYNCSRC_TIME_DP         3000 //3000

//Low Period when performing HPD on/off/on
#define HPD_LOW_PERIOD          500
#define DP_HPD_LOW_PERIOD       100

//#if (HPD_LOW_PERIOD > SYNCSRC_TIME_DIGITAL0)
//#error "HPD_LOW_PERIOD is over SYNCSRC_TIME_DIGITAL0"
//#endif
#if (HPD_LOW_PERIOD > SYNCSRC_TIME_DIGITAL1)
#error "HPD_LOW_PERIOD is over SYNCSRC_TIME_DIGITAL1"
#endif

/*******************************************************************************
                   Configurations of Scaler Audio
*******************************************************************************/
#define HDMI_AUDIO_VOLUME_RANGE 1023
#define DEF_HDMI_DIG_VOL        0X4000      			//140625 mike 0x8000  audio 
#define DEF_HDMI_ANA_VOL        0x0A

/*******************************************************************************
                Configurations of Volume & Backlight
*******************************************************************************/
//Volume Control
#define MAX_VOLUME_VALUE        300           //140708 mike  250==>1.5V
#define MIN_VOLUME_VALUE        220		//140328 mike 0==>20
#define VOLUME_PWM_FREQ         40000
//Backlight Control
#define BRIGHTNESS_FR_PWM_FREQ  200	//((USHRT)PANEL_FRC_OUTPUT_VSYNC*4/10)
#define BRIGHTNESS_ND_PWM_FREQ  200	//((USHRT) 200 )	//((USHRT)InputTiming.usVSyncFreq*4/10)

/*******************************************************************************
                Minimum Luminance-Related Setting
*******************************************************************************/

#define ULTRA_MIN_BACKLIGHT_VALUE BACKLIGHT_OFF_PWM_DUTY
#ifdef XRev														//150105 mike
#define BACKLIGHT_OFF_PWM_DUTY   0							//140314 mike 223 ==> 50 
#define MIN_BACKLIGHT_VALUE      (BACKLIGHT_OFF_PWM_DUTY )   	//150105 mike
#else															//150105 mike
#define BACKLIGHT_OFF_PWM_DUTY  50							//140314 mike 223 ==> 50 
#define MIN_BACKLIGHT_VALUE      (BACKLIGHT_OFF_PWM_DUTY + 50)	//150105 mike
#endif 															//150105 mike
#define MIN_CONTRAST_VALUE      28
#define MIN_GAIN_VALUE          40				//140428 mike 
#define MIN_OFFSET_VALUE        28

/*******************************************************************************
                           Allocate TX/RX buffer size
*******************************************************************************/
#define UART_TX_BUFFER_SIZE  10	//gg 16
#define UART_RX_BUFFER_SIZE 20	//gg 56

/*******************************************************************************
                          FE2P direct mode area configure
*******************************************************************************/
#define FE2P_DIRECTMODE_OFFSET 0x3C000 //Start Address
#define FE2P_DIRECTMODE_LEN    16 //Unit: 1K

//******************************************************************************
// G L O B A L   V A R I A B L E S
//******************************************************************************

//******************************************************************************
// S T A T I C   V A R I A B L E S
//******************************************************************************

//******************************************************************************
// E X T E R N A L   V A R I A B L E   P R O T O T Y P E S
//******************************************************************************
//============== CHIU	(from \App\OSD\FOSDView.c  ->  STATIC   VARIABLES) =======
	extern code UCHAR ucModelText[];
	extern code UCHAR ucPanelText[];
	extern code UCHAR ucDateText[];

#if OSD_SHOW_VERSION == ENABLE
	extern code UCHAR ucVersionText[];		// (at OSDView.c) -> OSDShowMainMenu() -> 	OSDAPI_ShowIndentString(...)
#endif
		
//============== CHIU	  
//******************************************************************************
// S T A T I C   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// E X T E R N A L   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************


#endif //__MODELCONFIG_H__
