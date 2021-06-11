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

//******************************************************************************
// G L O B A L   V A R I A B L E S
//******************************************************************************

//******************************************************************************
// S T A T I C   V A R I A B L E S
//******************************************************************************
static xdata USHRT usVPOffset = 0; /*!< Offset of vertical position of the even field of interlace timing */

//******************************************************************************
// E X T E R N A L   V A R I A B L E   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// S T A T I C   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// E X T E R N A L   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// F U N C T I O N   B O D Y S
//******************************************************************************

/**************************************************************************//**
 * Initialize capture-related registers.
 ******************************************************************************/
void CAPInit(void)
{
    SC_GI_PHS_MASK = 0x00;

    SC_CAP_SWAP = 0x00;
    SC_GI_V_DE_DLY = 0x21;
    SC_GI_CAP_VBEGO_LO = 0x20;
    SC_GI_CAP_VBEGO_HI = 0x00;
    SC_GI_CAP_VBEGE_LO = 0x00;
    SC_GI_CAP_VBEGE_HI = 0x00;
    SC_GI_CAP_VLEN_LO = 0xE0;
    SC_GI_CAP_VLEN_HI = 0x01;
    SC_GI_CAP_HBEG_LO = 0x88;
    SC_GI_CAP_HBEG_HI = 0x00;
    SC_GI_CAP_HWID_LO = 0x80;
    SC_GI_CAP_HWID_HI = 0x02;
    SC_GI_ALT_CTRL = 0x00;

    SC_GPORT_CTRL = 0xA1;
    SC_DIGITAL_CTRL = 0x00;
}

/**************************************************************************//**
 * Get input capture horizontal start position.
 * @return Input capture h-start.
 ******************************************************************************/
USHRT GetInputHStart(void)
{
    return ReadShortScaler(&SC_GI_CAP_HBEG_LO);
}

/**************************************************************************//**
 * Get input capture vertical start position.
 * @return Input capture v-start.
 ******************************************************************************/
USHRT GetInputVStart(void)
{
    return ReadShortScaler(&SC_GI_CAP_VBEGO_LO);
}

/**************************************************************************//**
 * Set input capture window size.
 * @param width Capture width.
 * @param height Capture height.
 ******************************************************************************/
void SetCaptureSize(USHRT width, USHRT height)
{
    WriteShortScaler(&SC_GI_CAP_HWID_LO, width);
    WriteShortScaler(&SC_GI_CAP_VLEN_LO, height);
}

/**************************************************************************//**
 * Get input capture width.
 * @return Capture width.
 ******************************************************************************/
USHRT GetHCaptureSize(void)
{
    return ReadShortScaler(&SC_GI_CAP_HWID_LO);
}

/**************************************************************************//**
 * Get input capture height.
 * @return Capture height.
 ******************************************************************************/
USHRT GetVCaptureSize(void)
{
    return ReadShortScaler(&SC_GI_CAP_VLEN_LO);
}

/**************************************************************************//**
 * Set horizontal capture start.
 * @param pos Horizontal capture start.
 ******************************************************************************/
void SetHP(USHRT pos)
{
    WriteShortScaler(&SC_GI_CAP_HBEG_LO, pos);
}

/**************************************************************************//**
 * Set the offset of vertical position of even field.
 * @param offset Offset of vertical position.
 ******************************************************************************/
void SetEvenFieldOffset(USHRT offset)
{
    usVPOffset = offset;
}

/**************************************************************************//**
 * Set vertical capture start.
 * @param pos Vertical capture start.
 ******************************************************************************/
void SetVP(USHRT pos)
{
    //Setup odd field after even field because of double-buffer structure
    WriteShortScaler(&SC_GI_CAP_VBEGE_LO, pos + usVPOffset);
    WriteShortScaler(&SC_GI_CAP_VBEGO_LO, pos);
    ucVstart100 = (((USHRT)pos-InputTiming.usVStartMin)*100 + ((InputTiming.usVStartMax-InputTiming.usVStartMin)>>1)) / (InputTiming.usVStartMax-InputTiming.usVStartMin);
}

#if ENABLE_OVERSCAN == ON
/**************************************************************************//**
 * Enable over-sampling.
 * This function is only available when input interface is TMDS.
 ******************************************************************************/
void EnableOverSample(void)
{
    SC_CAP_SWAP |= BIT6;
}

/**************************************************************************//**
 * Disable over-sampling.
 * This function is only available when input interface is TMDS.
 ******************************************************************************/
void DisableOverSample(void)
{
    SC_CAP_SWAP &= ~BIT6;
    WaitDisVSync();
}

/**************************************************************************//**
 * Check the over-sampling is on or not.
 * This function is only available when input interface is TMDS.
 * @return TRUE if over-sampling is on else FALSE.
 ******************************************************************************/
BOOL IsOverSample(void)
{
    if ((SC_CAP_SWAP & BIT6) != 0) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}
#endif
