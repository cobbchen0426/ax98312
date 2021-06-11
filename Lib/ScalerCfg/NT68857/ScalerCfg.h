/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/
#ifndef __SCALERCFG_H__
#define __SCALERCFG_H__

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************
#include "Typedef.h"

//******************************************************************************
// G L O B A L   D E F I N I T I O N S
//******************************************************************************

/*******************************************************************************
                             Configurations of MCU
*******************************************************************************/
#define FE2P_SRAM_ADDR          0xA800 // Size 0x800
#define GP_SRAM_ADDR            0xA000 // Size 0x800

//UART Output Selection
#define MCU_UART_OUTPUT         0 //TX/RX

//MCU Configuration
#define MCU_CLK_TIMES           4 //MCU CLOCK = MCU_CLK_TIMES * REF_CLK
#define MCU_T0_SPEED            	(REF_CLK/12000*MCU_CLK_TIMES)		
#define MCU_UART_BAUD_RATE      4800 //Bit per second

#define DDCCI_BUFFER_SIZE       40
#define DDCCI_ADDR              0x6E

/*******************************************************************************
                            Configurations of Scaler
*******************************************************************************/
//Scaler selection
#define SCALER_TEXT             "NT68857"

//Input source type multi-selection
						     // INPUT_VGA0, INPUT_VGA1, INPUT_DIG0, INPUT_DIG1, INPUT_YPbPr0, INPUT_YPbPr1
							 //(INPUT_VGA0|INPUT_YPbPr0|INPUT_DIG0|INPUT_DIG1|INPUT_MHL0|INPUT_DP)
#define INPUT_INTERFACE        (INPUT_VGA0|INPUT_YPbPr0|INPUT_DIG0|INPUT_DIG1|INPUT_MHL0|INPUT_DP)

//DVI Sync/DE mode selection
//  DVI_HV_MODE or DVI_DE_MODE or DVI_HVDE_MODE
#define DVI_MODE                DVI_HVDE_MODE

/*******************************************************************************
                         Enable/Disable Platform Features
*******************************************************************************/
//NEW MCU IO (PUSH PULL/OPEN DRAIN)
#define ENABLE_NEW_MCU_IO       ON //ON/OFF
//LOW POWER MODE
#define ENABLE_LOW_PWR_MODE     ON //ON/OFF
//CUT POWER ARCHITECTURE
#define ENABLE_CUT_POWER_ARCH   ON //ON/OFF
//System 5V check
#define ENABLE_CHECK_SYS5V      ON //ON/OFF
#define ENABLE_LPD              ON //ON/OFF		//george: test-#warning never compiler-here.	LPD: low power detection
//HDCP
#define ENABLE_HDCP             ON //ON/OFF
#define ENABLE_HDCP_KEY_DCRPT   ON //ON/OFF
#define ENABLE_DEMO_HDCP_KEY    ON //ON/OFF
#define ENABLE_NVT_HDCP_WRITER  ON //ON/OFF
#define ENABLE_HDCP_TRIM_MODE   ON //ON/OFF
//Gamma
#define ENABLE_GAMMA            ON //ON/OFF
#define ENABLE_PRE_REV_GAMMA    ON //ON/OFF
//OD
#define ENABLE_OD               OFF //ON/OFF
#define ENABLE_OD_TRANSFORM     OFF //ON/OFF
#define ENABLE_OD_MOTION_CHK    OFF //ON/OFF
#define ENABLE_MMU              ON //ON/OFF
//FE2P
#define ENABLE_FE2P             ON //ON/OFF
#define ENABLE_DIRECT_FE2P      ON //ON/OFF 
                                    // For FE2P direct mode, there are three attentions
                                    //   1. Fe2p Lib need 3.02 or new edition.
                                    //   2. KeilC bank space 0x3C000~0x3FFFF.
                                    //   3. NT68168/NT68668/NT68671~5 can not be applied this feature.
//HDMI
#define ENABLE_HDMI             ON //ON/OFF
#define ENABLE_HDMI_PRETEST     ON //ON/OFF
#define ENABLE_HDMI_AUDIO_CK_RCVY OFF //ON/OFF
//CEC
#define ENABLE_HW_CEC           ON //ON/OFF
//DBC
#define ENABLE_DBC              OFF //ON/OFF
#define ENABLE_DBC_HW_DEBOUNCE  ON //ON/OFF
#define DBC_TABLE_GENERATION    2  //0 for NT68676 or older scalers
                                   //1 for NT68360/NT68750/NT68650/NT68660
                                   //2 for NT68169/NT68652 or later scalers
//HPD
#define ENABLE_DIGI1_HPD        ON //ON/OFF
#define ENABLE_DIGI0_HPD        ON //ON/OFF
#define ENABLE_DP_HPD           ON //ON/OFF
#define ENABLE_DP_ADV_HPD       ON //ON/OFF
//SCALER AUDIO CONTROL
#define ENABLE_SCALER_AUDIO     ON //ON/OFF
#define ENABLE_INTERNAL_AUDIO_BUZZER ON //ON/OFF Only HDMI can define it ON
//OSD
#define ENABLE_OSD_WINDOWS      ON //ON/OFF
#define ENABLE_OSD_ROTATION     ON //ON/OFF
#define ENABLE_OSD_MIRROR       OFF //ON/OFF
#define ENABLE_OSD_FLIP         ON //ON/OFF
//CM
#define ENABLE_CM2              ON //ON/OFF
//SR
#define ENABLE_SR               ON //ON/OFF Only NT68750 can define ON
//LDO
#define ENABLE_INTERNAL_LDO     ON //ON/OFF
#define ENABLE_INTERNAL_ADC_LDO ON //ON/OFF

//SERIAL INTERRUPT
#define ENABLE_SERIAL_INT       ON //ON/OFF				

//EMBEDDED CHECKSUM
#define ENABLE_EMBEDDED_CHECKSUM ON //ON/OFF

//SCALING
#define ENABLE_OVERSCAN         ON //ON/OFF Only NT68676 can define ON
//LED DRIVER
#define ENABLE_SCALER_LEDDRV    OFF //ON/OFF Only NT68650 can define ON
#define ENABLE_LD               OFF //ON/OFF Only NT68750 can define ON
#define ENABLE_DYNAMIC_LD       OFF //ON/OFF
//PWM SMOOTH
#define ENABLE_PWM_SMOOTH       ON //ON/OFF Must be defined as OFF over NT68671~5
//FLASH IDLE MODE
#define ENABLE_FLASH_IDLE_MODE  ON //ON/OFF Only NT68660 & NT68650 can define ON
//PANEL SPEC
#define ENABLE_FIT_ALL_PANEL_SPEC ON //ON/OFF
//INTERNAL AUTOCOLOR
#define ENABLE_SELF_AUTOCOLOR   ON //ON/OFF
#define ENABLE_HW_AUTOCOLOR     OFF //ON/OFF
#if ENABLE_HW_AUTOCOLOR == ON
#undef ENABLE_SELF_AUTOCOLOR
#define ENABLE_SELF_AUTOCOLOR   ON
#endif
// 3D FORMAT INPUT
#define ENABLE_SCALER_3D        ON //ON/OFF
//FRC
#define ENABLE_PREFRC		OFF //ON/OFF
//DFR
#define ENABLE_DFR              OFF //ON/OFF

//ASPECT_RATIO :
#if ASPECT_RATIO_EnDis == ENABLE 
	#define ENABLE_ASPECT_RATIO		ON		//george 20160217
#else
	#define ENABLE_ASPECT_RATIO		OFF		//george 20160217
#endif
/*******************************************************************************
                     Platform Feature Dependency Setting
                     This is automatically set by compiler
*******************************************************************************/
#if DVI_MODE == DVI_DE_MODE
#undef ENABLE_OVERSCAN
#define ENABLE_OVERSCAN         OFF
#endif




#if IR_REMOT_CTL == ENABLE
	#define ENABLE_NEW_TIMER        ON			 //150511  George 
	#define CS107US                 214	//107	//100	 //150511  George
#else
	#define ENABLE_NEW_TIMER        OFF			 //150511  George 
#endif

/*******************************************************************************
                         FE2P-related configurations
*******************************************************************************/
#define FE2P_CMD_BUFFER_ADDR    0xF880

#endif //__SCALERCFG_H__
