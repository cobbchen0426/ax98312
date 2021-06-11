/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/
#ifndef __SCALERCFG_DUMMY_H__
#define __SCALERCFG_DUMMY_H__

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************
#include "ScalerType.h"

#if SCALER_TYPE == NT68168
#include "NT68168\ScalerCfg.h"
#elif SCALER_TYPE == NT68650
#include "NT68650\ScalerCfg.h"
#elif SCALER_TYPE == NT68620
#include "NT68620\ScalerCfg.h"
#elif SCALER_TYPE == NT68660
#include "NT68660\ScalerCfg.h"
#elif SCALER_TYPE == NT68668
#include "NT68668\ScalerCfg.h"
#elif SCALER_TYPE == NT68669
#include "NT68669\ScalerCfg.h"
#elif SCALER_TYPE == NT68671
#include "NT68671\ScalerCfg.h"
#elif SCALER_TYPE == NT68672
#include "NT68672\ScalerCfg.h"
#elif SCALER_TYPE == NT68673
#include "NT68673\ScalerCfg.h"
#elif SCALER_TYPE == NT68674
#include "NT68674\ScalerCfg.h"
#elif SCALER_TYPE == NT68675
#include "NT68675\ScalerCfg.h"
#elif SCALER_TYPE == NT68676
#include "NT68676\ScalerCfg.h"
#elif SCALER_TYPE == NT68677
#include "NT68677\ScalerCfg.h"
#elif SCALER_TYPE == NT68776
#include "NT68776\ScalerCfg.h"
#elif SCALER_TYPE == NT68777
#include "NT68777\ScalerCfg.h"
#elif SCALER_TYPE == NT68778
#include "NT68778\ScalerCfg.h"
#elif SCALER_TYPE == NT68779
#include "NT68779\ScalerCfg.h"
#elif SCALER_TYPE == NT68750
#include "NT68750\ScalerCfg.h"
#elif SCALER_TYPE == NT68751
#include "NT68751\ScalerCfg.h"
#elif SCALER_TYPE == NT68752
#include "NT68752\ScalerCfg.h"
#elif SCALER_TYPE == NT68753
#include "NT68753\ScalerCfg.h"
#elif SCALER_TYPE == NT68360
#include "NT68360\ScalerCfg.h"
#elif SCALER_TYPE == NT68361
#include "NT68361\ScalerCfg.h"
#elif SCALER_TYPE == NT68652
#include "NT68652\ScalerCfg.h"
#elif SCALER_TYPE == NT68169
#include "NT68169\ScalerCfg.h"
#elif SCALER_TYPE == NT68661
#include "NT68661\ScalerCfg.h"
#elif SCALER_TYPE == NT68770
#include "NT68770\ScalerCfg.h"
#elif SCALER_TYPE == NT68771
#include "NT68771\ScalerCfg.h"
#elif SCALER_TYPE == NT68772
#include "NT68772\ScalerCfg.h"
#elif SCALER_TYPE == NT68773
#include "NT68773\ScalerCfg.h"
#elif SCALER_TYPE == NT68774
#include "NT68774\ScalerCfg.h"
#elif SCALER_TYPE == NT68775
#include "NT68775\ScalerCfg.h"
#elif SCALER_TYPE == NT68781
#include "NT68781\ScalerCfg.h"
#elif SCALER_TYPE == NT68785
#include "NT68785\ScalerCfg.h"
#elif SCALER_TYPE == NT68850
#include "NT68850\ScalerCfg.h"
#elif SCALER_TYPE == NT68851
#include "NT68851\ScalerCfg.h"
#elif SCALER_TYPE == NT68852
#include "NT68852\ScalerCfg.h"
#elif SCALER_TYPE == NT68853
#include "NT68853\ScalerCfg.h"
#elif SCALER_TYPE == NT68854
#include "NT68854\ScalerCfg.h"
#elif SCALER_TYPE == NT68855
#include "NT68855\ScalerCfg.h"
#elif SCALER_TYPE == NT68856
#include "NT68856\ScalerCfg.h"

#elif SCALER_TYPE == NT68857 		//george-mark-here
#include "NT68857\ScalerCfg.h"

#elif SCALER_TYPE == NT68859
#include "NT68859\ScalerCfg.h"
#elif SCALER_TYPE == NT68655
#include "NT68655\ScalerCfg.h"
#elif SCALER_TYPE == NT68150
#include "NT68150\ScalerCfg.h"
#elif SCALER_TYPE == NT68370
#include "NT68370\ScalerCfg.h"
#elif SCALER_TYPE == NT68790
#include "NT68790\ScalerCfg.h"
#else
#error "Unknown SCALER_TYPE!"
#endif

#ifndef ENABLE_NEW_MCU_IO
#define ENABLE_NEW_MCU_IO       OFF
#endif
#ifndef ENABLE_LOW_PWR_MODE
#define ENABLE_LOW_PWR_MODE     OFF
#endif
#ifndef ENABLE_CUT_POWER_ARCH
#define ENABLE_CUT_POWER_ARCH   OFF
#endif
#ifndef ENABLE_CHECK_SYS5V
#define ENABLE_CHECK_SYS5V      ON	
#endif
#ifndef ENABLE_LPD
#define ENABLE_LPD              OFF
#endif
#ifndef ENABLE_HDCP
#define ENABLE_HDCP             OFF
#endif
#ifndef ENABLE_HDCP_KEY_DCRPT
#define ENABLE_HDCP_KEY_DCRPT   OFF
#endif
#ifndef ENABLE_DEMO_HDCP_KEY
#define ENABLE_DEMO_HDCP_KEY    OFF
#endif
#ifndef ENABLE_NVT_HDCP_WRITER
#define ENABLE_NVT_HDCP_WRITER  OFF
#endif
#ifndef ENABLE_HDCP_TRIM_MODE
#define ENABLE_HDCP_TRIM_MODE  OFF
#endif
#ifndef ENABLE_GAMMA
#define ENABLE_GAMMA            OFF
#endif
#ifndef ENABLE_10TO10_GAMMA
#define ENABLE_10TO10_GAMMA     OFF
#endif
#ifndef ENABLE_10TO12_GAMMA
#define ENABLE_10TO12_GAMMA     OFF
#endif
#ifndef ENABLE_PRE_REV_GAMMA
#define ENABLE_PRE_REV_GAMMA            OFF
#endif
#ifndef ENABLE_SINGLE_DDR
#define ENABLE_SINGLE_DDR       OFF
#endif
#ifndef ENABLE_OD
#define ENABLE_OD               OFF
#endif
#ifndef ENABLE_OD_TRANSFORM
#define ENABLE_OD_TRANSFORM               OFF
#endif
#ifndef ENABLE_OD_3D_MODE
#define ENABLE_OD_3D_MODE       OFF
#endif
#ifndef ENABLE_OD_MOTION_CHK
#define ENABLE_OD_MOTION_CHK    OFF
#endif
#ifndef ENABLE_MMU
#define ENABLE_MMU              OFF
#endif
#ifndef ENABLE_MMU_ERR_RCVY
#define ENABLE_MMU_ERR_RCVY     OFF
#endif
#ifndef ENABLE_FE2P
#define ENABLE_FE2P             OFF
#endif
#ifndef ENABLE_DIRECT_FE2P
#define ENABLE_DIRECT_FE2P      OFF 
#endif
#ifndef ENABLE_DVI_DUAL_LINK
#define ENABLE_DVI_DUAL_LINK    OFF
#endif
#ifndef ENABLE_HDMI
#define ENABLE_HDMI             OFF
#endif
#ifndef ENABLE_HDMI_PRETEST
#define ENABLE_HDMI_PRETEST     OFF
#endif
#ifndef ENABLE_HDMI_AUDIO_CK_RCVY
#define ENABLE_HDMI_AUDIO_CK_RCVY OFF
#endif
#ifndef ENABLE_HDMI_AUDIO_AUTO_MUTE
#define ENABLE_HDMI_AUDIO_AUTO_MUTE OFF
#endif
#ifndef ENABLE_HDMI_FS_MUTE
#define ENABLE_HDMI_FS_MUTE     OFF
#endif
#ifndef ENABLE_HW_CEC
#define ENABLE_HW_CEC           OFF
#endif
#ifndef ENABLE_DBC
#define ENABLE_DBC              OFF
#endif
#ifndef ENABLE_DBC_HW_DEBOUNCE
#define ENABLE_DBC_HW_DEBOUNCE  OFF
#endif
#ifndef ENABLE_DIGI1_HPD
#define ENABLE_DIGI1_HPD        OFF
#endif
#ifndef ENABLE_DIGI0_HPD
#define ENABLE_DIGI0_HPD        OFF
#endif
#ifndef ENABLE_DP_HPD
#define ENABLE_DP_HPD             OFF
#endif
#ifndef ENABLE_DP_ADV_HPD
#define ENABLE_DP_ADV_HPD       OFF
#endif
#ifndef ENABLE_SCALER_AUDIO
#define ENABLE_SCALER_AUDIO     OFF
#endif
#ifndef ENABLE_INTERNAL_AUDIO_BUZZER
#define ENABLE_INTERNAL_AUDIO_BUZZER OFF
#endif
#ifndef ENABLE_OSD_WINDOWS
#define ENABLE_OSD_WINDOWS      OFF
#endif
#ifndef ENABLE_OSD_ROTATION
#define ENABLE_OSD_ROTATION     OFF
#endif
#ifndef ENABLE_OSD_MIRROR
#define ENABLE_OSD_MIRROR       OFF
#endif
#ifndef ENABLE_OSD_FLIP
#define ENABLE_OSD_FLIP         OFF
#endif
#ifndef ENABLE_CM2
#define ENABLE_CM2              OFF
#endif
#ifndef ENABLE_SR
#define ENABLE_SR               OFF
#endif
#ifndef ENABLE_INTERNAL_LDO
#define ENABLE_INTERNAL_LDO     OFF
#endif
#ifndef ENABLE_INTERNAL_ADC_LDO
#define ENABLE_INTERNAL_ADC_LDO OFF
#endif
#ifndef ENABLE_SERIAL_INT
#define ENABLE_SERIAL_INT       OFF				
#endif
#ifndef ENABLE_FAST_BK_OFF
#define ENABLE_FAST_BK_OFF      OFF
#endif
#ifndef ENABLE_EMBEDDED_CHECKSUM
#define ENABLE_EMBEDDED_CHECKSUM OFF
#endif
#ifndef ENABLE_OVERSCAN
#define ENABLE_OVERSCAN         OFF
#endif
#ifndef ENABLE_SCALER_LEDDRV
#define ENABLE_SCALER_LEDDRV    OFF
#endif
#ifndef ENABLE_SCALER_LEDDRV_ANA_MODE
#define ENABLE_SCALER_LEDDRV_ANA_MODE    OFF
#endif
//#ifndef ENABLE_SET_PWM_MAX_BUFFER
#define ENABLE_SET_PWM_MAX_BUFFER    ON 			
//#endif
#ifndef ENABLE_SCALER_LEDDRV_IO_MODE
#define ENABLE_SCALER_LEDDRV_IO_MODE    OFF
#endif
#ifndef ENABLE_LD
#define ENABLE_LD               OFF
#endif
#ifndef ENABLE_DYNAMIC_LD
#define ENABLE_DYNAMIC_LD       OFF
#endif
#ifndef ENABLE_PWM_SMOOTH
#define ENABLE_PWM_SMOOTH       OFF
#endif
#ifndef ENABLE_FLASH_IDLE_MODE
#define ENABLE_FLASH_IDLE_MODE  OFF
#endif
#ifndef ENABLE_FIT_ALL_PANEL_SPEC
#define ENABLE_FIT_ALL_PANEL_SPEC OFF
#endif
#ifndef ENABLE_SCALER_3D
#define ENABLE_SCALER_3D        OFF
#endif
#ifndef ENABLE_3D_CNV
#define ENABLE_3D_CNV           OFF
#endif
#ifndef ENABLE_3D_CNV_120Hz
#define ENABLE_3D_CNV_120Hz     OFF
#endif
#ifndef ENABLE_SHUTTER_3D
#define ENABLE_SHUTTER_3D       OFF
#endif
#ifndef ENABLE_TEN_BIT_LVDS
#define ENABLE_TEN_BIT_LVDS     OFF
#endif
#ifndef ENABLE_FOUR_PORT_LVDS
#define ENABLE_FOUR_PORT_LVDS   OFF
#endif
#ifndef ENABLE_SELF_AUTOCOLOR
#define ENABLE_SELF_AUTOCOLOR   OFF
#endif
#ifndef ENABLE_HW_AUTOCOLOR
#define ENABLE_HW_AUTOCOLOR     OFF
#endif
#ifndef ENABLE_PREFRC
#define ENABLE_PREFRC     OFF
#endif
#ifndef ENABLE_DFR
#define ENABLE_DFR     OFF
#endif

#endif //__SCALERCFG_DUMMY_H__
