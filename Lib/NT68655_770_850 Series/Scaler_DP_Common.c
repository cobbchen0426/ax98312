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

#if (INPUT_INTERFACE&INPUT_DP)
//******************************************************************************
// M A C R O   D E F I N I T I O N S
//******************************************************************************

//******************************************************************************
// G L O B A L   V A R I A B L E S
//******************************************************************************

//******************************************************************************
// S T A T I C   V A R I A B L E S
//******************************************************************************
static UCHAR ucSetDPLink = 0;

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
//******************************************************************************
// Prototype: 
//  void SetDPLink()
// Parameters:
//
// Return:
//  None
// Purpose:
//
// Notes:
//  None
//******************************************************************************
void SetDPLink(void)
{
 ucSetDPLink = TRUE;
}

//******************************************************************************
// Prototype: 
//  void GetDPLink()
// Parameters:
//
// Return:
//  None
// Purpose:
//
// Notes:
//  None
//******************************************************************************
UCHAR GetDPLink(void)
{
 return ucSetDPLink;
}


//******************************************************************************
// Prototype: 
//  void ClrDPLink()
// Parameters:
//
// Return:
//  None
// Purpose:
//
// Notes:
//  None
//******************************************************************************
void ClrDPLink(void)
{
 ucSetDPLink = FALSE;
}


//******************************************************************************
// Prototype: 
//  void DP_InitDPCD()
// Parameters:
//
// Return:
//  None
// Purpose:
//
// Notes:
//  None
//******************************************************************************
void DP_InitDPCD(void) using 1
{
    SC_DP_DEBUG = 0x80;  // enable I2C write DPCD page
    
    SC_DP_DPCD_00000 = 0x11;  // ver 1.1
#if DP_LINKRATE == DP_162G
    SC_DP_DPCD_00001 = 0x06;  // 1.62G
#elif DP_LINKRATE == DP_270G
     SC_DP_DPCD_00001 = 0x0A;  // 2.70G
#else
     SC_DP_DPCD_00001 = 0x14;  // 5.40G
#endif
    SC_DP_DPCD_00002 = 0x80|DP_LANECNT;  // bit7=1 Enhanced Framing symbol + lane count
    SC_DP_DPCD_00003 = 0x01;  // DPCD 0x003 MAX_DOWNSPREAD = 0.5%
    SC_DP_DPCD_00004 = 0x01;  // DPCD 0x004 Number of receiver ports
    SC_DP_DPCD_00006 = 0x01;  // DPCD 0x006 ANSI_8B10B
    SC_DP_DPCD_00101 = 0x00;  // DPCD 0x101 LANE_COUNT_SET
    SC_DP_DPCD_00200 = 0x41;  // DPCD 0x200 bit6 enable CP_Ready
    SC_DP_DPCD_00201 = 0x00;  // DPCD 0x201 DEVICE_SERVICE_IRQ_VECTOR
    SC_DP_DPCD_0000D = 0x00;  // DPCD 0x00D

    SC_DP_DEBUG = 0x00;  //disable I2C write DPCD page
}

//******************************************************************************
// Prototype: 
//  void DP_InitDPConfigPage()
// Parameters:
//
// Return:
//  None
// Purpose:
//
// Notes:
//  None
//******************************************************************************
void DP_InitDPConfigPage(void) using 1
{
    // New register mapping (2012/02/20 David)

    //BIST
    if(SC_CHIP_ID == 0x0B && SC_REVISION_ID == 0x02){ // SCID_850_C
        SC_DP_1000 = 0x27;  // Fixed VBID issue
    }
    else {
        SC_DP_1000 = 0x07;  // Fixed VBID issue
        SC_DP_FAST_MUTE_CTRL |= BIT6;
    }

    // Init..
    SC_DP_ERR_DET_CTRL |= 0x87; // enable error detection 0x33[7]=1

    // disable bit 6 (2012/02/07)
    SC_DP_ERR_DET_DISABLE |= 0x38;

    // Set HPD width
    SC_DP_HPD_IRQ_WIDTH = 0x07; // set HDP low duty.
    // cerr_detect
    SC_DP_CERR_RANGE = 0x50; // cerr_range 
    SC_DP_CERR_RST_APHY_RANGE = 0x20;
    SC_DP_CERR_CLR_PHY_RANGE = 0x30;
    SC_DP_CERR_NO_LINK_RANGE = 0x40;
    SC_DP_CERR_NO_LINK_BS_RANGE = 0x50;
    SC_DP_CERR_DET_THRESHOLD = 0x20;
    SC_DP_1001 &= 0xF0;
    SC_DP_MN_CTRL = 0x20;  // MN control new shift mode
    
    // 0x17 DE mode; 0x10 Sync mode
    SC_DP_VIDEO_CONTROL = 0x17;  // DP DE original mode

    //Audio
    SC_ACR_CLK_OUT_SEL = 0x08;  //acr clk / 2
    SC_DP_I2S_CTRL = 0x00;  // audio I2S en
    SC_DP_CLK_CYCLE_VALUE = 0x03;  // for digital audio
    SC_DP_SPDIF_CTRL = 0x00;  // audio SPDIF en
    SC_DP_DSD_CTRL = 0x00;  //audio DSD en
    SC_DP_AUDIO_DAC_CTRL = 0x80;  //audio DAC en
    SC_DP_AUDIO_FIFO_CTRL = 0x80;  // audio FIFO enable
    SC_DP_AUDIO_ERROR_FLAG = 0xff;  // Audio error flag
    SC_DP_CRPLL = 0x15;  //clk path 

    //set default M/N value
    SC_DP_PLL_CTRL |= BIT6; //default manual
    //WriteScaler(0x1000+0xd0, ReadScaler(0x1000+0xd0) | BIT3); //block
    SC_DP_MANUAL_MAUD_LO = 0xAD; 
    SC_DP_MANUAL_MAUD_MI = 0x0B; 
    SC_DP_MANUAL_MAUD_HI = 0x00; 
    SC_DP_MANUAL_NAUD_LO = 0x00; 
    SC_DP_MANUAL_NAUD_MI =0x80; 
    SC_DP_MANUAL_NAUD_HI = 0x00; 

    //NLT:NO LINK TRAINING
    SC_DP_10B0 |= BIT7;
    SC_DP_10B7 &= 0xD5; // 10b7[1] [3] [5] = 0
}

//******************************************************************************
// Prototype: 
//  void DP_InitPHY()
// Parameters:
//
// Return:
//  None
// Purpose:
//
// Notes:
//  None
//******************************************************************************
void DP_InitPHY(void) using 1
{
   //SC_DP_AUX_CTRL = 0x31; // AUX
   DPPHY_PowerOn();
    // cut3 auto EQ change back to cut2 EQ setting
   SC_DP_EQR_10B1 = 0xA6; // bit4=0,bit[3:2]=11 manual mode
   SC_DP_TEST_MODE_EN = 0x88; // DP Test mode en
   SC_DP_PHY_CTRL1 = 0x12; // bit[7:6]=00 lane 0
   SC_DP_PHY_CTRL10 = 0x10; // bit[5:3]=111 R1 1st DC gain ,R2 bit[2:0]=100
   SC_DP_PHY_CTRL11 = 0x3C; // bit[5:3]=111 C2 1st AC gain ,C2 bit[2:0]=100
   SC_DP_PHY_CTRL1 = 0x52; // bit[7:6]=01 lane 1
   SC_DP_PHY_CTRL10 = 0x10; // bit[5:3]=111 R1 1st DC gain ,R2 bit[2:0]=100
   SC_DP_PHY_CTRL11 = 0x3C; // bit[5:3]=111 C2 1st AC gain ,C2 bit[2:0]=100
   SC_DP_PHY_CTRL1 = 0x92; // bit[7:6]=10 lane 2
   SC_DP_PHY_CTRL10 = 0x10; // bit[5:3]=111 R1 1st DC gain ,R2 bit[2:0]=100
   SC_DP_PHY_CTRL11 = 0x3C; // bit[5:3]=111 C2 1st AC gain ,C2 bit[2:0]=100
   SC_DP_PHY_CTRL1 = 0xD2; // bit[7:6]=11 lane 3
   SC_DP_PHY_CTRL10 = 0x10; // bit[5:3]=111 R1 1st DC gain ,R2 bit[2:0]=100
   SC_DP_PHY_CTRL11 = 0x3C; // bit[5:3]=111 C2 1st AC gain ,C2 bit[2:0]=100
   SC_DP_TEST_MODE_EN = 0xAA; // DP Test mode dis
}

//******************************************************************************
// Prototype: 
//  void DPPHY_PowerOn()
// Parameters:
//
// Return:
//  None
// Purpose:
//
// Notes:
//  None
//******************************************************************************
void DPPHY_PowerOn(void) using 1
{
    //sel_done sequence
    SC_DP_TEST_MODE_EN = 0x88;//enter dp_text_mode 
    SC_DP_PHY_CTRL3 |= BIT3;
    SC_DP_CDR_10C2 &= (~BIT7);
    SC_DP_TEST_MODE_EN = 0xAA;//leave dp_text_mode 

/*    SC_DP_EQR_10B3 = 0xEA; // EQR
    SC_DP_EQR_10B4 = 0x66; // EQR
    SC_DP_EQR_10B5 = 0x1F; // EQR Ch0~3 Power up
    SC_DP_EQR_10B6 = 0xFF; // EQR

    SC_DP_CDR_10BA = 0xF1; // CDR Ch0~3 Power up and DP_ALL_POW
    SC_DP_CDR_10BB = 0xFF; // Lane0,1
    SC_DP_CDR_10BC = 0xFF; // Lane0,1
    SC_DP_CDR_10BE = 0x77; // CDR
    SC_DP_CDR_10BF = 0x83; // I Bias charge pump current
    SC_DP_CDR_10C0 = 0x37; // CDR
    SC_DP_CDR_10C1 = 0xE0; // CDR
    //SC_DP_CDR_10C2 = 0x67;
    SC_DP_CDR_10C2 = 0xA1;
*/
	//Yung update
    SC_DP_EQR_10B3 = 0xEA; // EQR
    SC_DP_EQR_10B4 = 0x66; // EQR
    SC_DP_EQR_10B5 = 0x1F; // EQR Ch0~3 Power up
    SC_DP_EQR_10B6 = 0xFF; // EQR

	//
    SC_DP_CDR_10BA = 0xF1; // CDR Ch0~3 Power up and DP_ALL_POW
    SC_DP_CDR_10BB = 0x77; // Enable PD COM UBG TESTBUF of lane0&1
    SC_DP_CDR_10BC = 0x77; // Enable PD COM UBG TESTBUF of lane0&1

    SC_DP_CDR_10BE = 0x77; // CDR
    SC_DP_CDR_10BF = 0x83; // I Bias charge pump current
    SC_DP_CDR_10C0 = 0x37; // CDR
    SC_DP_CDR_10C1 = 0xF0;
    SC_DP_CDR_10C2 = 0xA1;
} 

//******************************************************************************
// Prototype: 
//  void DPPHY_PowerOff()
// Parameters:
//
// Return:
//  None
// Purpose:
//
// Notes:
//  None
//******************************************************************************
void DPPHY_PowerOff(void) using 1
{
    SC_DP_EQR_10B3 = 0x84;
    SC_DP_EQR_10B4 = 0x15;
    SC_DP_EQR_10B5 = 0x00;
    SC_DP_EQR_10B6 = 0x44;
    SC_DP_CDR_10BA = 0x01;
    SC_DP_CDR_10BB = 0x00;
    SC_DP_CDR_10BC = 0x00;
    SC_DP_CDR_10BE = 0x33;
    SC_DP_CDR_10C1 = 0x7F;
    //SC_DP_CDR_10C2 = 0x26;
    SC_DP_CDR_10C2 = 0x20;

    //sel_done sequence
    SC_DP_TEST_MODE_EN = 0x88;//enter dp_text_mode 
    SC_DP_PHY_CTRL3 &= (~BIT3);
    SC_DP_CDR_10C2 |= BIT7;
    SC_DP_TEST_MODE_EN = 0xAA;//leave dp_text_mode 
}

//******************************************************************************
// Prototype: 
//  void DP_ConfigAUX2IICSpeed()
// Parameters:
//
// Return:
//  None
// Purpose:
//
// Notes:
//  None
//******************************************************************************
void DP_ConfigAUX2IICSpeed(void) using 1
{
    // Init AUX to I2C clock speed.
#if AUX2IICSPEED > 500  //20130715_1006_SYS#3
    SC_DP_SCL_HI_HALF_WIDTH = 0x10;
    SC_DP_SCL_HI_WIDTH = 0x20;
    SC_DP_SDA_SETUP = 0x12;
    SC_DP_SDA_HOLD = 0x1F;
#elif AUX2IICSPEED == 500
    SC_DP_SCL_HI_HALF_WIDTH = 0x1F;
    SC_DP_SCL_HI_WIDTH = 0x2F;
    SC_DP_SDA_SETUP = 0x12;
    SC_DP_SDA_HOLD = 0x1F;
#elif AUX2IICSPEED == 400
    SC_DP_SCL_HI_HALF_WIDTH = 0x20;
    SC_DP_SCL_HI_WIDTH = 0x3C;
    SC_DP_SDA_SETUP = 0x1D;
    SC_DP_SDA_HOLD = 0x1F;
#elif AUX2IICSPEED == 300
    SC_DP_SCL_HI_HALF_WIDTH = 0x2E;
    SC_DP_SCL_HI_WIDTH = 0x50;
    SC_DP_SDA_SETUP = 0x31;
    SC_DP_SDA_HOLD = 0x1F;
#else
    SC_DP_SCL_HI_HALF_WIDTH = 0x58;//0x48;
    SC_DP_SCL_HI_WIDTH = 0xA0;//0x7D);
    SC_DP_SDA_SETUP = 0x81;//0x5E);
    SC_DP_SDA_HOLD = 0x1F;
#endif

    if(SC_CHIP_ID == 0x0B && SC_REVISION_ID == 0x02){ // SCID_850_C
#if AUX2IICSPEED < 300
        SC_DP_AUX_I2C_CTRL = 0x34;  // BIT5:differ en
#else
        SC_DP_AUX_I2C_CTRL = 0x34|BIT1|BIT0;
#endif
    }
    else {
        SC_DP_AUX_I2C_CTRL = 0x36;  // BIT5:differ en, cut4 BIT0=0
        SC_DP_MASK_AUX_I2C_RW_SEL &= ~BIT0;
        SC_DP_AUX_CTRL2 |= BIT5;
    }

    // Init Pre-charge pulse count
    SC_DP_TX_PRE_CHG_NUM = 0x19|BIT6;
    SC_DP_RX_PRE_CHG_NUM = 0x0F;
}

//******************************************************************************
// Prototype: 
//  void DP_CLKOn()
// Parameters:
//
// Return:
//  None
// Purpose:
//
// Notes:
//  None
//******************************************************************************
void DP_CLKOn(void) using 1
{
    SC_POWER_CTRL3 &= ~(BIT2|BIT1|BIT0); //CLK
    SC_LVDS_PAD_POWER &= ~BIT7; //int-dp_rck_gated
}

//******************************************************************************
// Prototype: 
//  void DP_CLKOff()
// Parameters:
//
// Return:
//  None
// Purpose:
//
// Notes:
//  None
//******************************************************************************
void DP_CLKOff(void) using 1
{
    SC_POWER_CTRL3 |= (BIT2|BIT1|BIT0); //CLK
    SC_LVDS_PAD_POWER |= BIT7; //int-dp_rck_gated
}

#else
void ForDPCompilerCodePass(void)
{
  code UCHAR temp[]={0x00};
  UCHAR i;
  i = temp[0];
}
#endif



