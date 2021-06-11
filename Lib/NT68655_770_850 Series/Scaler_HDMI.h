/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/

#ifndef __SCALER_HDMI_H__
#define __SCALER_HDMI_H__

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************
#include "ScalerType.h"
#include "Typedef.h"

//******************************************************************************
// M A C R O   D E F I N I T I O N S
//******************************************************************************
#define AUDIO_IN_CH_MASK  0xF0 /*!< Audio channel input mask. */
#define AUDIO_IN_DISABLE  0x00 /*!< Audio input is none. */
#define AUDIO_IN_LINE1    0x10 /*!< Audio input from line-in 1. */
#define AUDIO_IN_LINE2    0x20 /*!< Audio input from line-in 2. */
#define AUDIO_IN_DSD      0x30 /*!< Audio input from DSD */
#define AUDIO_IN_HDMI     0x40 /*!< Audio input from HDMI. */
#define AUDIO_OUT_CH_MASK 0x0F /*!< Audio channel output mask. */
#define AUDIO_OUT_DISABLE 0x00 /*!< Audio output is none. */
#define AUDIO_OUT_LINEOUT 0x01 /*!< Audio output to line-out. */
#define AUDIO_OUT_IIS     0x02 /*!< Audio output to IIS. */
#define AUDIO_OUT_DSD     0x03 /*!< Audio output to DSD. */


#define DEEP_COLOR_24BIT_DUALLink  0x01
#define DEEP_COLOR_24BIT  0x02
#define DEEP_COLOR_30BIT  0x10
#define DEEP_COLOR_36BIT  0x20
#define DEEP_COLOR_48BIT  0x30

//******************************************************************************
// D A T A   T Y P E   D E F I N E S
//******************************************************************************
/*!
 * Data type for audio in/output channels.
 */
typedef enum _AUDIO_IN_OUT_CH_ {
    AUDIO_IN_OUT_DISABLE = 0x00,                                 /*!< Audio channel disabled. */
    AUDIO_LINEIN1_LINOUT = (AUDIO_IN_LINE1 | AUDIO_OUT_LINEOUT), /*!< Audio channel is from line-in 1 to line-out. */
    AUDIO_LINEIN2_LINOUT = (AUDIO_IN_LINE2 | AUDIO_OUT_LINEOUT), /*!< Audio channel is from line-in 2 to line-out. */
    AUDIO_DSD_LINEOUT = (AUDIO_IN_DSD | AUDIO_OUT_LINEOUT),      /*!< Audio channel is from DSD to line-out. */
    AUDIO_DSD_IIS = (AUDIO_IN_DSD | AUDIO_OUT_IIS),              /*!< Audio channel is from DSD to IIS. */
    AUDIO_DSD_DSD = (AUDIO_IN_DSD | AUDIO_OUT_DSD),              /*!< Audio channel is from DSD to DSD. */
    AUDIO_HDMI_LINOUT = (AUDIO_IN_HDMI | AUDIO_OUT_LINEOUT),     /*!< Audio channel is from HDMI to line-out. */
    AUDIO_HDMI_IIS = (AUDIO_IN_HDMI | AUDIO_OUT_IIS),            /*!< Audio channel is from HDMI to IIS. */
    AUDIO_HDMI_DSD = (AUDIO_IN_HDMI | AUDIO_OUT_DSD)             /*!< Audio channel is from HDMI to DSD. */
} AudioInOutChannel;

//******************************************************************************
// V A R I A B L E S   P R O T O T Y P E
//******************************************************************************

//******************************************************************************
// F U N C T I O N    P R O T O T Y P E S
//******************************************************************************
//UCHAR GetSCDeepColor(void);
void HDMIInit(void);
void HdmiHandler(void);
USHRT TMDSDeepColorDetection(void);
void HDMIEnablePreambleDetection(UCHAR enable);
void HDMIEnableAVC(UCHAR enable);
void HDMISoftReset(void);
void ConfigScalerAudio(USHRT value);
BOOL IsHDMIDataMute(void);
#if 0
void HDMIEnableAVMuteInt(UCHAR enable);
#endif
void ClearHDMIStatus(void);
void ScalerAudioPowerOff(void);
void ScalerAudioPowerOn(void);
void ScalerAudioSelect(AudioInOutChannel ch);
BOOL IsHDMI(void);
void EnableVCSAudioBuzzer(USHRT freq);
void DisableVCSAudioBuzzer(void);
BOOL IsHDMIVideo(void);
void HDMIAPI_MuteUnmatchedFs(void);

#endif //__SCALER_HDMI_H__
