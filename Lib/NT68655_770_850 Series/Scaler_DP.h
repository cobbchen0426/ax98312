/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/

#ifndef __SCALER_DP_H__
#define __SCALER_DP_H__

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************
#include "ScalerType.h"
#include "Typedef.h"

//******************************************************************************
// M A C R O   D E F I N I T I O N S
//******************************************************************************
#define DP_PHY_ADDR 0xB0
#define WAITDPTIME 2000
#define AUX2IICSPEED 550

#define EN_AUX_STROBE_FUNC OFF // cut4
//******************************************************************************
// D A T A   T Y P E   D E F I N E S
//******************************************************************************
enum {
    DPAUD_fifo_balance = 0,
    DPAUD_fifo_underflow,
    DPAUD_fifo_overflow,
    DPAUD_fifo_unknown,
};

enum {
    DPAUD_path_auto = 0,
    DPAUD_path_manual,
};

enum {
    DPAUD_M_32k_1_62G = 0,
    DPAUD_M_44k_1_62G,
    DPAUD_M_48k_1_62G,
    DPAUD_M_88k_1_62G,
    DPAUD_M_96k_1_62G,    
    DPAUD_M_176k_1_62G,    
    DPAUD_M_196k_1_62G,    
    
    DPAUD_M_num,
    
    DPAUD_M_32k_2_7G = DPAUD_M_num,
    DPAUD_M_44k_2_7G,
    DPAUD_M_48k_2_7G,
    DPAUD_M_88k_2_7G,
    DPAUD_M_96k_2_7G,
    DPAUD_M_176k_2_7G,
    DPAUD_M_196k_2_7G,

};

//******************************************************************************
// V A R I A B L E S   P R O T O T Y P E
//******************************************************************************
typedef struct _DP_AUDIO_MN_ {
    UCHAR DP_Audio_M_MSB;    
    UCHAR DP_Audio_M_LSB;
}DP_audio_mn;

//******************************************************************************
// F U N C T I O N    P R O T O T Y P E S
//******************************************************************************
void DPInit(void);
void DP_PowerOn(void);
void DP_PowerOFF(void);
USHRT GetDPInputHDEImmediate(void);
USHRT GetDPInputVDEImmediate(void);
USHRT DP_GetClock(void);
void DPSetPowerState(void);
UCHAR DPGetPowerState(void);
void DPConfigAUXDetect(void);
void DPConfigFIFO(void);
void DPConfigHWHPD(BOOL enable);
BOOL IsDPTrainingDone(void);
BOOL IsDPAUXDetect(void);
void ClearDPAUXDetect(void);
void DPHandler(void);
void DPConfigCRC(void);
void DP_AudioSetDefault(void);
void DP_AudioMNCheckerInit(void);
void DP_AudioMNChecker(void);

#if (ENABLE_DP_AUX_MONITOR==ON)
void Init_DP_Strobe(void); 
void DP_Strobe_Debug(void);
void DP_Aux_Channel_Monitor(void);
void  move_aux_packet(void);
#endif


#endif
