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
#define CSC_SIM_CTRL BIT7 //0x055

//******************************************************************************
// G L O B A L   V A R I A B L E S
//******************************************************************************

//******************************************************************************
// S T A T I C   V A R I A B L E S
//******************************************************************************
static xdata CSCColorSpace ucCSCClrSpace = CSC_HDMI_AUTO_CLR_SPACE; /*!< Variable of CSC mode. */

//******************************************************************************
// E X T E R N A L   V A R I A B L E   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// S T A T I C   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
static xdata UCHAR ucAVIClrSpace = 0xFF;

//******************************************************************************
// E X T E R N A L   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// F U N C T I O N   B O D Y S
//******************************************************************************
static void SetHDMISRCSC(void);
static void SetVGADVISRCSC(void);
#if (INPUT_INTERFACE&INPUT_DP) && ENABLE_SR == ON
static void SetDPSRCSC(void);
#endif

#if ENABLE_HDMI == ON
//******************************************************************************
// Prototype: 
//  void GetScalerColorSpace(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//******************************************************************************
UCHAR GetScalerColorSpace(void)
{
   return ucAVIClrSpace;
}

/**************************************************************************//**
 * Configure the CSC mode.
 * @param csc CSC mode.
 ******************************************************************************/
void SetCSCColorSpace(CSCColorSpace csc)
{
    ucCSCClrSpace = csc;
    SetColorSpace();
}

#endif

/**************************************************************************//**
 * According to ucCSCClrSpace, set color space automatically.
 * If CSC mode is auto:
 *  - If input interface is HDMI, the color space is configured automatically according to AVI packets.
 *  - If input interface is DVI, forcing the color space as RGB.
 *  - If input interface is YPbPr, the color space is configured automatically according to input resolution.
 *  - If input interface is DSub, forcing the color space as RGB.
 * If CSC mode is manual:
 *  - If input interface is HDMI, the color space is configured manually.
 *  - If input interface is DVI, the color space is configured manually.
 *  - If input interface is YPbPr, the color space is configured manually.
 *  - If input interface is DSub, forcing the color space as RGB.
 ******************************************************************************/
void SetColorSpace(void)
{
#if !IS_NT68150_SERIES
    UCHAR current_input_interface, ch, repeat;
    USHRT input_hactive, input_vactive;


    current_input_interface = GetCurrInputInterface();
    if ((current_input_interface == DIGITAL_INPUT0) || (current_input_interface == DIGITAL_INPUT1)) {
        
         ucAVIClrSpace = (SC_HDMI_AVI[0] & 0x60); 
         
        if (ucCSCClrSpace == CSC_OFF) {
            SC_VI_AUTO_CTRL &= ~BIT5; // Set auto-detection data path before CSC
            SC_CSC_CTRL1 = 0x00;
            SC_CSC_CTRL2 = 0x00;
            // Set video mute data for AVMute
            SC_VIDEO_BLANK_BLUE = 0x00;
            SC_VIDEO_BLANK_GREEN = 0x00;
            SC_VIDEO_BLANK_RED = 0x00;
        }
        else if (ucCSCClrSpace == CSC_HDMI_AUTO_CLR_SPACE) {
            if (IsHDMIVideo()) { //HDMI & YCbCr color
                // --------------------------
                // Auto IN_CSC with SR mode
#if ENABLE_SR == ON
                SetHDMISRCSC();
#else
                SC_HDMI_AUTO_CTRL |= BIT2; //set auto csc
                SC_TMDS_AUTO_CSC = 0x0E;
#endif
                // Set video mute data for AVMute
                SC_VIDEO_BLANK_BLUE = 0x80;
                SC_VIDEO_BLANK_GREEN = 0x00;
                SC_VIDEO_BLANK_RED = 0x80;
            }
            else { //DVI | HDMI RGB color
                SC_VI_AUTO_CTRL &= ~BIT5; // Set auto-detection data path before CSC  
#if ENABLE_SR == ON
                if ((SC_HDMI_DET & BIT1) != 0) { //HDMI RGB color
                    SetHDMISRCSC();
                }
                else { //dvi
                    SetVGADVISRCSC();
                }
#else
//                SC_HDMI_AUTO_CTRL |= BIT2; //set auto csc
//                SC_TMDS_AUTO_CSC = 0x0E;
                SC_HDMI_AUTO_CTRL &= ~BIT2; //set auto csc
                SC_TMDS_AUTO_CSC = 0x0E;
                if ((SC_HDMI_DET & BIT1) != 0) {
                    if ((SC_HDMI_AVI[2] & 0x0C) == 0x04) { // Limit RGB to Full RGB
                        SC_CSC_CTRL1 = 0xB8;
                        SC_CSC_CTRL2 = 0x19;
                    }
                    else {
                        SC_CSC_CTRL1 = 0x00;
                        SC_CSC_CTRL2 = 0x00;
                    }
                }
                else {
                    SC_CSC_CTRL1 = 0x00;
                    SC_CSC_CTRL2 = 0x00;
                }
#endif
                // Set video mute data for AVMute
                SC_VIDEO_BLANK_BLUE = 0x00;
                SC_VIDEO_BLANK_GREEN = 0x00;
                SC_VIDEO_BLANK_RED = 0x00;
            }
        }
        else {
            SC_VI_AUTO_CTRL |= BIT5; // Set auto-detection data path after CSC
            SC_CSC_CTRL1 = BIT7 | ((ucCSCClrSpace & 0x0F) << 3);
            SC_CSC_CTRL2 = 0x19;

            // Set video mute data for AVMute
            switch(ucCSCClrSpace) {
                case CSC_YPbPr601_TO_RGB:
                case CSC_YPbPr601_TO_RGB_FULL:
                case CSC_YPbPr709_TO_RGB:
                case CSC_YPbPr709_TO_RGB_FULL:
                case CSC_YPbPr_TO_YPbPr_FULL:
                case CSC_xvYCC601_TO_RGB:
                case CSC_xvYCC601_TO_RGB_FULL:
                case CSC_xvYCC709_TO_RGB:
                case CSC_xvYCC709_TO_RGB_FULL:
                    SC_VIDEO_BLANK_BLUE = 0x80;
                    SC_VIDEO_BLANK_GREEN = 0x00;
                    SC_VIDEO_BLANK_RED = 0x80;
                    break;
                default :
                    SC_VIDEO_BLANK_BLUE = 0x00;
                    SC_VIDEO_BLANK_GREEN = 0x00;
                    SC_VIDEO_BLANK_RED = 0x00;
                    break;
            }
        }
//////////////////////////////////////////////////////////////////////////
        if ((SC_HDMI_DET & BIT1) != 0) {
            if (ucAVIClrSpace == BIT5) {//4:2:2
                SC_CSC_CTRL2 |= BIT5;
            }
            //Set repeat for Manual CSC mode
            ch = SC_HDMI_AVI[4] & 0x0F;
            repeat = SC_HDMI_CLK_INT & 0x0F;//default: No Repetition
            if (ch == 0x01) {//pixel sent 2 times
                repeat |= 0x50;
            }
            else if (ch == 0x03) {//pixel sent 4 times
                repeat |= 0xF0;
            }
            SC_HDMI_CLK_INT = repeat;
        }
        else {
            SC_HDMI_CLK_INT &= 0x0F;
        }
///////////////////////////////////////////////////////////////////////////
    }
    else if ((current_input_interface == ANALOG_YPBPR_INPUT0) || (current_input_interface == ANALOG_YPBPR_INPUT1)) {
        input_hactive = ReadShortScaler(&SC_GI_CAP_HWID_LO);
        input_vactive = ReadShortScaler(&SC_GI_CAP_VLEN_LO);
    	if (((input_hactive == 1920) && (input_vactive == 1080)) || ((input_hactive == 1280) && (input_vactive == 720))){
    		SC_CLAMP_BEGIN = 0x24;
    	}
    	else{
    		SC_CLAMP_BEGIN = 0x01;
    	}
        Sleep(20);
        
        if (ucCSCClrSpace == CSC_OFF) {
            SC_VI_AUTO_CTRL &= ~BIT5; // Set auto-detection data path before CSC
            SC_CSC_CTRL1 = 0x00;
            SC_CSC_CTRL2 = 0x00;
        }
        else if (ucCSCClrSpace == CSC_HDMI_AUTO_CLR_SPACE) {
            SC_VI_AUTO_CTRL &= ~BIT5; // Set auto-detection data path before CSC

            SC_DEI_CSC_CTRL = 0x19;
            SC_CSC_CTRL2 = 0x00;//|CSC_SIM_CTRL;
            SC_CSC_CTRL1 = 0x00;
            if (((input_hactive == 1920) && (input_vactive == 1080)) || ((input_hactive == 1280) && (input_vactive == 720))){ //ITU709
                SC_SR_AUTO_CSC_CTRL = 0x31;
            }
            else { //ITU601
                SC_SR_AUTO_CSC_CTRL = 0x01;
            }
        }
        else {
            SC_VI_AUTO_CTRL &= ~BIT5; // Set auto-detection data path before CSC
            SC_CSC_CTRL1 = BIT7 | ((ucCSCClrSpace & 0x0F) << 3);
            SC_CSC_CTRL2 = 0x19;
        }
    }
#if (INPUT_INTERFACE&INPUT_DP)
    else if (current_input_interface == DISPLAY_PORT_INPUT) {
#if ENABLE_SR == ON
        SetDPSRCSC();
#else
        SC_DP_CSC_AUTO_CONF |= BIT0;
#endif
    }
#endif
    else { // VGA
        SC_VI_AUTO_CTRL &= ~BIT5; // Set auto-detection data path before CSC    
#if ENABLE_SR == ON
        SetVGADVISRCSC();
#else
        SC_CSC_CTRL2 = 0x00|CSC_SIM_CTRL;
        SC_DEI_CSC_CTRL = 0x00;
        SC_CSC_CTRL1 = 0x00;
        SC_TMDS_AUTO_CSC = 0x00;
        SC_SR_AUTO_CSC_CTRL |= BIT0;
#endif
    }
#else
    code int SDTVcolorTab[] = {
        1.371*1024+0.5,0.698*1024+0.5,0.336*1024+0.5,1.732*1024+0.5,
    };

    code int HDTVcolorTab[] = {
        1.540*1024+0.5,0.459*1024+0.5,0.183*1024+0.5,1.816*1024+0.5,
    };

    UCHAR current_input_interface;
    USHRT input_hactive, input_vactive;

    current_input_interface = GetCurrInputInterface();
    if ((current_input_interface == ANALOG_YPBPR_INPUT0) || (current_input_interface == ANALOG_YPBPR_INPUT1)) {
        input_hactive = ReadShortScaler(&SC_GI_CAP_HWID_LO);
        input_vactive = ReadShortScaler(&SC_GI_CAP_VLEN_LO);
    	if (((input_hactive == 1920) && (input_vactive == 1080)) || ((input_hactive == 1280) && (input_vactive == 720))){
    		SC_CLAMP_BEGIN = 0x24;
    	}
    	else{
    		SC_CLAMP_BEGIN = 0x01;
}
        Sleep(20);
        
        if (ucCSCClrSpace == CSC_OFF) {
            SC_VI_AUTO_CTRL &= ~BIT5; // Set auto-detection data path before CSC
            SC_CSC_CTRL1 = 0x00;
            SC_CSC_CTRL2 = 0x00;
        }
        else if (ucCSCClrSpace == CSC_HDMI_AUTO_CLR_SPACE) {
            SC_VI_AUTO_CTRL &= ~BIT5; // Set auto-detection data path before CSC
            SC_DEI_CSC_CTRL = 0x09;
            SC_CSC_CTRL1 = 0x00;
            SC_CSC_CTRL2 = 0x00;
            if (((input_hactive == 1920) && (input_vactive == 1080)) || ((input_hactive == 1280) && (input_vactive == 720))){ //ITU709
                WriteShortScaler(&SC_DEI_COLOR_COFFA_LO,HDTVcolorTab[0]);
                WriteShortScaler(&SC_DEI_COLOR_COFFB_LO,HDTVcolorTab[1]);
                WriteShortScaler(&SC_DEI_COLOR_COFFC_LO,HDTVcolorTab[2]);
                WriteShortScaler(&SC_DEI_COLOR_COFFD_LO,HDTVcolorTab[3]);
            }
            else {//ITU 601
                WriteShortScaler(&SC_DEI_COLOR_COFFA_LO,SDTVcolorTab[0]);
                WriteShortScaler(&SC_DEI_COLOR_COFFB_LO,SDTVcolorTab[1]);
                WriteShortScaler(&SC_DEI_COLOR_COFFC_LO,SDTVcolorTab[2]);
                WriteShortScaler(&SC_DEI_COLOR_COFFD_LO,SDTVcolorTab[3]);
            }
        }
        else {
            SC_VI_AUTO_CTRL &= ~BIT5; // Set auto-detection data path before CSC
            SC_CSC_CTRL1 = BIT7 | ((ucCSCClrSpace & 0x0F) << 3);
            SC_CSC_CTRL2 = 0x19;
        }
    }
    else { // VGA
        SC_VI_AUTO_CTRL &= ~BIT5; // Set auto-detection data path before CSC    
        SC_DEI_CSC_CTRL = 0x00;
        SC_CSC_CTRL1 = 0x00;
        SC_CSC_CTRL2 = 0x00;
    }
#endif

    //CSCDitherManualModeEn();
}

#if ENABLE_HDMI == ON
/**************************************************************************//**
 * Set HDMI SR CSC
 ******************************************************************************/
void SetHDMISRCSC(void)
{
    UCHAR Reg0x1ED, ch, Reg0x600, Reg0x649;
//    if ((SC_DISPLAY_MUTE_CTRL & 0x03) != 0) { //when mute
    if (((SC_DISPLAY_MUTE_CTRL & 0x03) != 0) || ((SC_HDMI_INT_STATE1[3] & BIT0) != 0)) { //when mute
        ch = SC_SR_CTRL; //set SR on
        Reg0x1ED = SC_ADC_BAND_GAP;
        SC_ADC_BAND_GAP &= ~BIT0;
        SC_SR_CTRL = 0x51;
        SC_HDMI_AUTO_CTRL |= BIT2; //set auto csc
        SC_TMDS_AUTO_CSC = 0x0E;
        SC_HDMI_RESET_CTRL &= ~BIT3;
        Sleep(50); //wait one frame
        Reg0x649 = SC_ICPCSC_AUTOSTATUS; //read Reg0x600 & Reg0x649
        Reg0x600 = SC_TMDS_AUTO_CSC;
        SC_HDMI_AUTO_CTRL &= ~BIT2;//set manual csc
        SC_TMDS_AUTO_CSC &= ~BIT1;
        SC_SR_CTRL = ch; //restore SR
        SC_ADC_BAND_GAP = Reg0x1ED;
        ch = SC_CSC_CTRL1 & 0x87; //fill Reg0x054
        SC_CSC_CTRL1 = ch | ((Reg0x649 & 0xF0) >> 1) | BIT7;
        ch = SC_SR_AUTO_CSC_CTRL & 0x0F; //fill Reg0x601
        SC_SR_AUTO_CSC_CTRL = ch | (Reg0x600 & 0xF0) | BIT0;
        if ((Reg0x600 & BIT0) == 0) { //set Reg0x053[0]
            SC_DEI_CSC_CTRL = 0x19;
        }
        else {
            SC_DEI_CSC_CTRL = 0x18;
        }
        if ((Reg0x649 & BIT0) == 0) { //set Reg0x055[0]
            SC_CSC_CTRL2 = 0x19;
        }
        else {
            SC_CSC_CTRL2 = 0x18;
        }
///////////////////////////////////////////////////////////////////////////////
#if 1//TPV Limited RGB
        if (!IsHDMIVideo()) 									//HDMI RGB color
		{ 
		if ((SC_HDMI_AVI[2] & 0x0C) == 0x04)  				// Limited RGB
               {
                	if(GetSCID() == SCID_770_E)
		     	  {
                         SC_CSC_CTRL1 = 0xF0;						//limited RGB to Ycbcr601
                       }
                else 
			 {
                    		SC_CSC_CTRL1 = 0x88;					//RGB to Ycbcr601
                	 }
                 }
            else 
		  {
                	if(GetSCID() == SCID_770_E)
			  {
                    		SC_CSC_CTRL1 = 0x88;					//Full RGB to Ycbcr601
                	  }
                else 
			 {
                           SC_CSC_CTRL1 = 0xF8;						//Full RGB to limited Ycbcr601
                       }
                 }      
 
            if(GetSCID() == SCID_770_E)
		 {
                   SC_SR_AUTO_CSC_CTRL = 0x03; 					//Ycbcr601 to RGB           
               }
            else 
		   {
                  	 SC_SR_AUTO_CSC_CTRL = 0x23; //limited Ycbcr601 to RGB           
    		  }
     }
#endif
///////////////////////////////////////////////////////////////////////////////
    }
}
#endif

/**************************************************************************//**
 * Set VGA DVI SR CSC.
 ******************************************************************************/
void SetVGADVISRCSC(void)
{
    if ((SC_DISPLAY_MUTE_CTRL & 0x03) != 0) { //when mute
        SC_HDMI_AUTO_CTRL &= ~BIT2;//set manual csc
        SC_TMDS_AUTO_CSC &= ~BIT1;
        SC_DEI_CSC_CTRL = 0x19;
        SC_CSC_CTRL1 = 0x88;
        SC_CSC_CTRL2 = 0x99;
        SC_SR_AUTO_CSC_CTRL = 0x03;
    }
}

#if (INPUT_INTERFACE&INPUT_DP) && ENABLE_SR == ON
/**************************************************************************//**
 * Set DP SR CSC.
 ******************************************************************************/
void SetDPSRCSC(void)
{
    UCHAR Reg0x1ED, ch, Reg0x109D, Reg0x109E;
    if ((SC_DISPLAY_MUTE_CTRL & 0x03) != 0) { //when mute
        ch = SC_SR_CTRL; //set SR on
        Reg0x1ED = SC_ADC_BAND_GAP;
        SC_ADC_BAND_GAP &= ~BIT0;
        SC_SR_CTRL = 0x51;
        SC_DP_CSC_AUTO_CONF |= BIT0; //DP CSC auto
        SC_HDMI_RESET_CTRL &= ~BIT3;
        Sleep(50); //wait one frame
        Reg0x109D = SC_DP_109D; //read Reg0x109D & Reg0x109E
        Reg0x109E = SC_DP_109E;
        SC_DP_CSC_AUTO_CONF &= ~BIT0; //DP CSC manual
        SC_SR_CTRL = ch; //restore SR
        SC_ADC_BAND_GAP = Reg0x1ED;

        ch = SC_CSC_CTRL1 & 0x87; //fill Reg0x054
        SC_CSC_CTRL1 = ch | ((Reg0x109D & 0x0F) << 3) | BIT7;
        ch = SC_SR_AUTO_CSC_CTRL & 0x0F; //fill Reg0x601
        SC_SR_AUTO_CSC_CTRL = ch | ((Reg0x109E & 0x0F) << 4) | BIT0;
        if ((Reg0x109E & BIT6) == 0) { //set Reg0x053[0]
            SC_DEI_CSC_CTRL = 0x1A;
        }
        else {
            SC_DEI_CSC_CTRL = 0x1B;
        }
        if ((Reg0x109E & BIT4) == 0) { //set Reg0x055[0]
            SC_CSC_CTRL2 = 0x1A;
        }
        else {
            SC_CSC_CTRL2 = 0x1B;
        }
        if ((Reg0x109E & BIT7) != 0) {//4:2:2
            SC_CSC_CTRL2 |= BIT5;
        }
    }
}
#endif
