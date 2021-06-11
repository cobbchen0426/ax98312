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
static xdata UCHAR ucPowerState = 0;
static code UCHAR MCU_CLK[9] = CPU_CLK_TABLE;
static xdata USHRT usDPTimer = 0;
static /*xdata*/ BOOL bAudioMNChecking = FALSE;
#if EN_AUX_STROBE_FUNC == ON
xdata UCHAR bDP_AUX_DETECT = 0;
#endif

//******************************************************************************
// S T A T I C   V A R I A B L E S
//******************************************************************************
#if DP_DDC_CHANNEL == 0x00
//    xdata UCHAR volatile EDID_SRAM_DP[256] _at_ 0xF800;
    #define EDID_SRAM_DP EDID_SRAM_BUFF0
    #define DP_DDC_PORT    DDC_CTL0
    #define DP_IIC_MASK    0x0E
#elif DP_DDC_CHANNEL == 0x01
//    xdata UCHAR volatile EDID_SRAM_DP[256] _at_ 0xF900;
    #define EDID_SRAM_DP EDID_SRAM_BUFF1
    #define DP_DDC_PORT    DDC_CTL1
    #define DP_IIC_MASK    0x0D
#elif DP_DDC_CHANNEL == 0x02
//    xdata UCHAR volatile EDID_SRAM_DP[256] _at_ 0xFA00;
    #define EDID_SRAM_DP EDID_SRAM_BUFF2
    #define DP_DDC_PORT    DDC_CTL2
    #define DP_IIC_MASK    0x0B
#elif DP_DDC_CHANNEL == 0x03
//    xdata UCHAR volatile EDID_SRAM_DP[256] _at_ 0xFB00;
    #define EDID_SRAM_DP EDID_SRAM_BUFF3
    #define DP_DDC_PORT    DDC_CTL3
    #define DP_IIC_MASK    0x07
#endif

//CHIU
#if SPECIALAPP == ON
//Tatung1850x1036-NO_1920X1080
static code UCHAR _Default_DP_EDID[]={
   0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x3A,0xD4,0x5A,0x66,0x01,0x00,0x00,0x00,
   0x0F,0x17,0x01,0x04,0xA5,0x3A,0x20,0x78,0xEF,0x36,0xD5,0xA2,0x56,0x53,0x99,0x27,
   0x0D,0x50,0x54,0xA3,0x08,0x00,0x81,0x80,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
   0x01,0x01,0x01,0x01,0x01,0x01,0x09,0x3B,0x3A,0x5E,0x71,0x0C,0x6D,0x40,0x6E,0x37,
   0x85,0x04,0x40,0x44,0x21,0x00,0x00,0x18,0x66,0x21,0x50,0xB0,0x51,0x00,0x1B,0x30,
   0x40,0x70,0x36,0x00,0x40,0x44,0x21,0x00,0x00,0x1E,0x00,0x00,0x00,0xFD,0x00,0x32,
   0x41,0x1E,0x64,0x16,0x00,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x00,0x00,0xFC,
   0x00,0x54,0x55,0x53,0x20,0x4C,0x32,0x36,0x58,0x58,0x58,0x0A,0x0A,0x0A,0x01,0xA3,
   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};

#else

#include "EDID.c"		

#endif	//#if SPECIALAPP == ON

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
//  void DPInit()
// Parameters:
//
// Return:
//  None
// Purpose:
//
// Notes:
//  None
//******************************************************************************
void DPInit(void)
{
    SC_TMDS_LINK_CLK_SEL = SCREG_1E7 | BIT0;;  // dp_refclk select
    SC_DP_102F = REF_CLK*4/1000000;  // if 0x1E7[4:3] = 2'b00, dp_refclk = OSC clock*4

    DP_PowerOn();
    DPConfigAUXDetect();

#if ENABLE_DEMO_DP_EDID == ON
	{
		USHRT i;
        bit diff;
    // Init EDID data
        diff = FALSE;
		
		for (i=0; i<256; i++) {
            if ((EDID_SRAM_DP[i] != _Default_DP_EDID[i]) && (i < 8)) {//check head
                diff = TRUE;
        		EDID_SRAM_DP[i] = _Default_DP_EDID[i];
    		}	
			else if ((i > 7) && (diff == TRUE)) {//copy
				EDID_SRAM_DP[i] = _Default_DP_EDID[i];
			}
        }
    }
#endif


#if EN_AUX_STROBE_FUNC == ON
		INTSC_EN |= BIT1;		// DP_EN	
		AUX_STROBE_CTL = (DP_AUX_STROBE_EN|DP_AUX_STROBE_RST|DP_AUX_STROBE_INT_EN);	// AUX strobe enable, interrupt enable
		AUX_STROBE_CTL = (DP_AUX_STROBE_EN|DP_AUX_STROBE_INT_EN|DP_AUX_STROBE_MASK_RX);//0x1d;	// clear AUX strobe interrupt
		AUX_I2C_MANUAL = (AUX_I2C_MODE);		// enable I2C-over-AUX to manual mode
		SC_DP_RESET_FUNCTION |= DP_AUX_RST;
		SC_DP_RESET_FUNCTION &= ~DP_AUX_RST;
	#if 1
		DP_SC_REG_1224 |= (MASK_NATIVE_AUX);
		SC_DP_AUX_CTRL2 |= (DP_AUX_INTR_SEL);
	#endif
    	SC_DP_10F4 = 0xA0;
#else

	#if (ENABLE_DP_AUX_MONITOR==OFF)
			INTSC_EN &= ~BIT1;
			AUX_STROBE_CTL = 0x00;
	    #if (ENABLE_DEMO_DP_EDID == ON) || ((USE_INTERNAL_EDID == 1) && (DP_DDC_CHANNEL != 0xFF))
	    	DP_DDC_PORT |= BIT7;//DDC_CTL1 |= BIT7;
	    	IIC_MASK_CTRL = DP_IIC_MASK;//0x0D;
	    	DP_CTRL = (DP_DDC_CHANNEL << 2) | BIT1;// | BIT0;//0x06;
		#else
	    	IIC_MASK_CTRL = DP_IIC_MASK;//0x0D;
	    	DP_CTRL = (DP_DDC_CHANNEL << 2) | BIT1 | BIT0;//0x06;
		#endif
	
	#endif

#endif

    DP_ConfigAUX2IICSpeed();

    if(IsDPTrainingDone() == FALSE){
      DP_InitPHY();
      DP_InitDPCD();//DP TrainingDone don't do it
      
      SC_DP_AUX_CTRL = 0x31; // AUX
            
      DP_InitDPConfigPage();
    }
}

//******************************************************************************
// Prototype: 
//  void DP_PowerOn()
// Parameters:
//
// Return:
//  None
// Purpose:
//
// Notes:
//  None
//******************************************************************************
void DP_PowerOn(void)
{
    DP_CLKOn();
    DPPHY_PowerOn();
}

//******************************************************************************
// Prototype: 
//  void DP_PowerOFF()
// Parameters:
//
// Return:
//  None
// Purpose:
//
// Notes:
//  None
//******************************************************************************
void DP_PowerOFF(void)
{
    DP_CLKOff();
    DPPHY_PowerOff();
}

//******************************************************************************
// Prototype: 
//  void GetDPInputHDEImmediate()
// Parameters:
//
// Return:
//  None
// Purpose:
//
// Notes:
//  None
//******************************************************************************
USHRT GetDPInputHDEImmediate(void)
{
    return (SC_DP_1089<<8)+(SC_DP_108A);
}

//******************************************************************************
// Prototype: 
//  void GetDPInputVDEImmediate()
// Parameters:
//
// Return:
//  None
// Purpose:
//
// Notes:
//  None
//******************************************************************************
USHRT GetDPInputVDEImmediate(void)
{
    return (SC_DP_108B<<8)+(SC_DP_108C);
}

//******************************************************************************
// Prototype: 
//  void DP_GetClock()
// Parameters:
//
// Return:
//  None
// Purpose:
//
// Notes:
//  None
//******************************************************************************
USHRT DP_GetClock(void)
{
#if 0
	#if REF_CLK==12000000
	    if ((SC_DP_10F2 & BIT6) != 0) {
	        return SC_DP_10F5;
	    }
	#else

		#define OSC_FREQ_RATIO ((float)REF_CLK/12000000)
	    if ((SC_DP_10F2 & BIT6) != 0) {
	        return (USHRT)(SC_DP_10F5*OSC_FREQ_RATIO);
	    }

	#undef OSC_FREQ_RATIO

	#endif

    return 0;

#else
	#define DP162M 162000000
	#define DP270M 270000000
	#define DP540M 540000000

    xdata ULONG M, N, ulDPClock;

    M = SC_DP_PLL_M_VID_HI;
    M <<= 8;
    M |= SC_DP_PLL_M_VID_MI;
    M <<= 8;
    M |= SC_DP_PLL_M_VID_LO;

    N = SC_DP_PLL_N_VID_HI;
    N <<= 8;
    N |= SC_DP_PLL_N_VID_MI;
    N <<= 8;
    N |= SC_DP_PLL_N_VID_LO;

    switch (SC_DP_MISC_CTRL&0x03) {
    case 0:
        ulDPClock = (double)DP162M*M/N;
        break;
    case 1:
        ulDPClock = (double)DP270M*M/N;
        break;
    case 2:
        ulDPClock = (double)DP540M*M/N;
        break;
    }
    //printf("M = %ld, N = %ld, DPCLK = %ld\r\n",M,N,ulDPClock);
    return (USHRT)(ulDPClock/1000000);
#endif
}

#if 0
//******************************************************************************
// Prototype: 
//  void DPSetPowerState()
// Parameters:
//
// Return:
//  None
// Purpose:
//
// Notes:
//  None
//******************************************************************************
void DPSetPowerState(void)
{
    SC_DP_DEBUG = 0x80; //0x1030 enable I2C write DPCD page
    ucPowerState = SC_DP_DPCD_00600;
    SC_DP_DEBUG = 0x00; //0x1030 disable I2C write DPCD page
}

//******************************************************************************
// Prototype: 
//  void DPGetPowerState()
// Parameters:
//
// Return:
//  None
// Purpose:
//
// Notes:
//  None
//******************************************************************************
UCHAR DPGetPowerState(void)
{
    return ucPowerState;
}
#endif
//******************************************************************************
// Prototype: 
//  void DPConfigAUXDetect()
// Parameters:
//
// Return:
//  None
// Purpose:
//
// Notes:
//  None
//******************************************************************************
void DPConfigAUXDetect(void)
{
    BOOL bEnAUXInt=0;
    float fRatio;
    fRatio = (float)MCU_CLK[MCU_CLK_TIMES]/12;

    if (IsZpMode()) {
        SC_DP_AUX_PULSEWIDTH_LO_THD = 0x01;
        SC_DP_AUX_PULSEWIDTH_HI_THD = 0x05;
        if ((UserData.bAutoSyncSource == TRUE)
            ||((UserData.bAutoSyncSource == FALSE) && GetCurrInputInterface()==DISPLAY_PORT_INPUT )
            ) {
            SC_DP_AUX_PRECHARGE_NUM = 0x06 | BIT7; // Enable DP AUX detect interrupt
            bEnAUXInt = 1;
        }
        else {
        SC_DP_AUX_PRECHARGE_NUM = 0x06;
            bEnAUXInt = 0;
        }
    }
    else {
        SC_DP_AUX_PULSEWIDTH_LO_THD = 0x09 * fRatio;
        SC_DP_AUX_PULSEWIDTH_HI_THD = 0x0F * fRatio;
        SC_DP_AUX_PRECHARGE_NUM = 0x09;
        bEnAUXInt = 0;
    }
    if (IsDPAUXDetect()) {
        ClearDPAUXDetect();
    }
    
    if(bEnAUXInt){
        INTSC_EN |= BIT1;
    }
    else{
        INTSC_EN &= ~BIT1;
    }
    
    SC_DP_AUX_DETECT = 0x01; //DP_AUX_DET_EN & pre_charge_reach
}

//******************************************************************************
// Prototype: 
//  void DPConfigFIFO()
// Parameters:
//
// Return:
//  None
// Purpose:
//
// Notes:
//  None
//******************************************************************************
void DPConfigFIFO(void)
{
    USHRT VBlankCNT;

    SC_DP_DE_START_POS = GetDPInputHDEImmediate()/24;

    VBlankCNT = GetDigInputVTotalImmediate() - GetDPInputVDEImmediate() + 2;
    SC_DP_VS_BLANK_CNT_LO = VBlankCNT&0xFF;
    SC_DP_AUX_CTRL2 &= 0xF0;
    SC_DP_AUX_CTRL2 |= (VBlankCNT&0xF00) >> 8;

    SC_DP_VIDEO_FIFO_INT = 0x03;
}

//******************************************************************************
// Prototype: 
//  void DPConfigHWHPD()
// Parameters:
//
// Return:
//  None
// Purpose:
//
// Notes:
//  None
//******************************************************************************
void DPConfigHWHPD(BOOL enable)
{
    if (enable == TRUE) {
        DP_CTRL |= BIT4; // DP HPD_PAD enable
    }
    else {
        DP_CTRL &= ~BIT4; // DP HPD_PAD disable
    }
}

//******************************************************************************
// Prototype: 
//  BOOL IsDPTrainingDone()
// Parameters:
//
// Return:
//  None
// Purpose:
//
// Notes:
//  None
//******************************************************************************
BOOL IsDPTrainingDone(void)
{		  		  

#if 0

    UCHAR Reg0x10A6;
    SC_DP_TEST_MODE_EN = 0x55;//enter dp_text_read_mode 
    SC_DP_TEST_MODE_EN = 0x88;//enter dp_text_write_mode 
    SC_DP_PHY_CTRL1 &= 0x3F;
    Reg0x10A6 = SC_DP_PHY_CTRL6;
    SC_DP_TEST_MODE_EN = 0xaa;//leave dp_text_write_mode 
    SC_DP_TEST_MODE_EN = 0xbb;//leave dp_text_read_mode 
    if ((Reg0x10A6 & 0x30) == 0x30) {
        return TRUE;
    }
    else {
        return FALSE;
    }
#else

    UCHAR ucLaneCount;
    BOOL bTrainingStatus = TRUE;

    ucLaneCount = (SC_DP_MISC_CTRL&0x1C)>>2;
    if ((ucLaneCount == 0) || (ucLaneCount > 4)) {
        return FALSE;
    }

    SC_DP_TEST_MODE_EN = 0x55;//enter dp_text_read_mode 
    SC_DP_TEST_MODE_EN = 0x88;//enter dp_text_write_mode

    do {
        SC_DP_PHY_CTRL1 &= 0x3F;
        SC_DP_PHY_CTRL1 |= (--ucLaneCount) << 6;
        if ((SC_DP_PHY_CTRL6 & 0x30) != 0x30) {
            bTrainingStatus = FALSE;
            break;
        }
    } while(ucLaneCount != 0);

    SC_DP_TEST_MODE_EN = 0xaa;//leave dp_text_write_mode 
    SC_DP_TEST_MODE_EN = 0xbb;//leave dp_text_read_mode

    return bTrainingStatus;
#endif
}

//******************************************************************************
// Prototype: 
//  BOOL IsDPAUXDetect(void)
// Parameters:
//
// Return:
//  None
// Purpose:
//
// Notes:
//  None
//******************************************************************************
BOOL IsDPAUXDetect(void)
{
    if ((SC_DP_AUX_DETECT & BIT7) != 0) {
        return TRUE;
    }
#if EN_AUX_STROBE_FUNC == ON
    else if (bDP_AUX_DETECT == 1) {
        return TRUE;
    }
#endif
    else {
        return FALSE;
    }
}

//******************************************************************************
// Prototype: 
//  void ClearDPAUXDetect()
// Parameters:
//
// Return:
//  None
// Purpose:
//
// Notes:
//  None
//******************************************************************************
void ClearDPAUXDetect(void)
{
    SC_DP_AUX_DETECT |= BIT1;
    Sleep(1);
    SC_DP_AUX_DETECT &= ~BIT1; 
#if EN_AUX_STROBE_FUNC == ON
    bDP_AUX_DETECT = 0;
#endif
}

//******************************************************************************
// Prototype: 
//  void DPHandler()
// Parameters:
//
// Return:
//  None
// Purpose:
//
// Notes:
//  None
//******************************************************************************
void DPHandler(void)
{
    static BOOL bauxactived = FALSE;

    if (IsZpMode() == FALSE) {
         if (IsDPTrainingDone()) {
             if (GetSCID()== SCID_850_C) {
                 if ((SC_DP_INT_GROUP_4&BIT6) == 0x40) { // only for Cut3
                     SC_DP_DEBUG = 0x80;
                     SC_DP_DPCD_00201 |= BIT2;
                     SC_DP_DEBUG = 0x00;
                     SC_DP_1000 &= ~BIT5;
                     SC_DP_DEBUG = 0x40;
                     Sleep(5);
                     SC_DP_1000 |= BIT5;
                     SC_DP_DEBUG = 0x80;
                     SC_DP_DPCD_00201 &= ~BIT2;
                     SC_DP_DEBUG = 0x00;
                     SC_DP_INT_GROUP_4 = 0x40;
                 }
             }
         }
         else {
             if (GetCurrInputInterface() != DISPLAY_PORT_INPUT) {
                 if (((SC_POWER_CTRL3&0x07) != 0x00) && (IsDPAUXDetect() == TRUE)) {
                     DP_PowerOn();
                 }
                 else if (((SC_POWER_CTRL3&0x07) != 0x07) && (IsDPAUXDetect() == FALSE)) {
                     if ((GetTimerTick() - usDPTimer) > WAITDPTIME) {
                         DP_PowerOFF();
                     }
                 }
                 if (IsDPAUXDetect()) {
                     ClearDPAUXDetect();
                     usDPTimer = GetTimerTick();
                 }
             }
         }
     
         if (GetCurrInputInterface() == DISPLAY_PORT_INPUT && GetModeHandleState() == WAIT_MODE_CHANGE) {
             DP_AudioMNChecker();
             if (IsDPAUXDetect()) {
                 bauxactived = TRUE;
                 ClearDPAUXDetect();
                 SetGlobalTimer(GLOBAL_TMR_CHECK_AUX, 2000);
             }
             if (GetGlobalTimer(GLOBAL_TMR_CHECK_AUX) == 0) {
                 if (bauxactived == TRUE) {
                     SC_DP_RESET_FUNCTION |= BIT0;
                     SC_DP_RESET_FUNCTION &= ~BIT0; 
                     bauxactived = FALSE;
                 }
             } 
         }
     }
}

//******************************************************************************
// Prototype: 
//  void DPConfigCRC()
// Parameters:
//
// Return:
//  None
// Purpose:
//
// Notes:
//  None
//******************************************************************************
void DPConfigCRC(void)
{
#ifdef ENABLE_DP_LINKER_LAYER_CTS
    if ((((SC_DP_MSA_MISC0&0x06) == 0x02) && ((SC_DP_MSA_MISC0&0xF0) != 0x50))
        || ((SC_DP_MSA_MISC0&0xFE) == 0x48)) { // YCbCr 4:2:2 & CEA RGB 10bits disable crc support
        SC_DP_DEBUG = 0x80; //0x1030 enable I2C write DPCD page
        SC_DP_DPCD_00246 = 0x00;//ReadScaler(0x1100+0x52)&(~BIT5));
        SC_DP_DEBUG = 0x00; //0x1030 disable I2C write DPCD page
    }
    else {
        SC_DP_DEBUG = 0x80; //0x1030 enable I2C write DPCD page
        SC_DP_DPCD_00246 = 0x20;//ReadScaler(0x1100+0x52)|BIT5);
        SC_DP_DEBUG = 0x00; //0x1030 disable I2C write DPCD page
    }
#endif
}

//******************************************************************************
// Prototype: 
//  void DP_AudioSetMNValue(UCHAR table_idx)
// Parameters:
//
// Return:
//  None
// Purpose:
//
// Notes:
//  None
//******************************************************************************
void DP_AudioSetMNValue(UCHAR table_idx)
{
code DP_audio_mn DP_Audio_MN_tbl[] = {
    //32K                   44.1K                48K              88.2K               96K            176K                196K
    {0x0C, 0xF3}, {0x11, 0xD7}, {0x13, 0x6B}, {0x23, 0xAE}, {0x26, 0xD6}, {0x47, 0x5C}, {0x4D, 0xAB},  //1.62G
    {0x07, 0xC5}, {0x0A, 0xB5}, {0x0B, 0xA7}, {0x15, 0x68}, {0x17, 0x4E}, {0x2A, 0xD1}, {0x2E, 0x9A},  //2.7G
};

    //N value is always set to 32768
    SC_DP_MANUAL_NAUD_HI = 0x00;     
    SC_DP_MANUAL_NAUD_MI = 0x80; 
    SC_DP_MANUAL_NAUD_LO = 0x00; 

    //M value setting
    SC_DP_MANUAL_MAUD_HI = 0x00;         
    SC_DP_MANUAL_MAUD_MI = DP_Audio_MN_tbl[table_idx].DP_Audio_M_MSB; 
    SC_DP_MANUAL_MAUD_LO = DP_Audio_MN_tbl[table_idx].DP_Audio_M_LSB; 
}

//******************************************************************************
// Prototype: 
//  void DP_AudioSetDefault(void)
// Parameters:
//
// Return:
//  None
// Purpose:
//
// Notes:
//  None
//******************************************************************************
void DP_AudioSetDefault(void)
{
    UCHAR ucspeed;

    ucspeed = SC_DP_MISC_CTRL & (BIT1|BIT0);
    
    switch (ucspeed) {
        case 0: // 1.62
            DP_AudioSetMNValue(DPAUD_M_48k_1_62G);
            break;
        case 1:// 2.7
        default:
            DP_AudioSetMNValue(DPAUD_M_48k_2_7G);
            break;
        case 2:// 5.4
            DP_AudioSetMNValue(DPAUD_M_48k_2_7G);//no use  
            break;
    }
}

//******************************************************************************
// Prototype: 
//  void DP_AudioSetAudioPath(UCHAR ucpath)
// Parameters:
//
// Return:
//  None
// Purpose:
//
// Notes:
//  None
//******************************************************************************
void DP_AudioSetAudioPath(UCHAR ucpath)
{
    SC_DP_CRPLL = 0x15; //clk path    

    if (ucpath == DPAUD_path_auto) {
        SC_DP_PLL_CTRL &= ~BIT6; //auto            
    }
    else {//manual
        SC_DP_PLL_CTRL |= BIT6; //manual    
    }
}

//******************************************************************************
// Prototype: 
//  void DP_AudioMNCheckerInit(void)
// Parameters:
//
// Return:
//  None
// Purpose:
//
// Notes:
//  None
//******************************************************************************
void DP_AudioMNCheckerInit(void)
{
    //printf("DP_AudioMNCheckerInit\r\n"); 
    SC_DP_AUDIO_FIFO_CTRL |= BIT6; //audio fifo mute
    SC_DP_INT_GROUP_3 = 0xFF; //Clear interrupt group 2 status

    DP_AudioSetAudioPath(DPAUD_path_auto);

    bAudioMNChecking = TRUE;   
}

//******************************************************************************
// Prototype: 
//  UCHAR DP_AudioGetFIFOStatus(BOOL bquickcheck) 
// Parameters:
//
// Return:
//  None
// Purpose:
//
// Notes:
//  None
//******************************************************************************
UCHAR DP_AudioGetFIFOStatus(BOOL bquickcheck) 
{
    UCHAR ucfifo_readstatus;

    if (!bquickcheck) {
        SC_DP_AUDIO_FIFO_CTRL &= ~BIT7; //audio fifo off
        SC_DP_AUDIO_DAC_CTRL &= ~ BIT7; //audio DAC off    
        SC_DP_AUDIO_DAC_CTRL |= BIT7; //audio DAC on
        SC_DP_AUDIO_FIFO_CTRL |= BIT7; //audio fifo on    
        SC_DP_AUDIO_ERROR_FLAG = 0xFF;
        Sleep(40);
    }
    ucfifo_readstatus = SC_DP_AUDIO_ERROR_FLAG & (BIT6|BIT2);
    //printf("ucfifo_readstatus  = %bx\r\n", ucfifo_readstatus);

    if (ucfifo_readstatus == BIT6) {
        return DPAUD_fifo_overflow;
    }
    else if (ucfifo_readstatus == BIT2) {
        return DPAUD_fifo_underflow;
    }
    else if (ucfifo_readstatus == 0x00) {
        return DPAUD_fifo_balance;
    }
    else {
        return DPAUD_fifo_unknown;
    }
}

//******************************************************************************
// Prototype: 
//  UCHAR DP_AudioMNSearch(void)
// Parameters:
//
// Return:
//  None
// Purpose:
//
// Notes:
//  None
//******************************************************************************
UCHAR DP_AudioMNSearch(void)
{
#if 1 //search table method
    UCHAR ucsearch_idx, ucspeed, ucfifo_status, i;
    UCHAR ucsearch_result = FALSE;
    
    ucspeed = SC_DP_MISC_CTRL & (BIT1|BIT0);

    if (ucspeed == 0) {//1.62g
        ucsearch_idx = DPAUD_M_32k_1_62G;
    }
    else {//2.7g
        ucsearch_idx = DPAUD_M_32k_2_7G;
    }

    SC_VPLL_CTRL &= ~BIT2;    

    for (i = ucsearch_idx ; i < ucsearch_idx+DPAUD_M_num ; i++) {

        DP_AudioSetMNValue(i);       
        ucfifo_status = DP_AudioGetFIFOStatus(FALSE); 
        //printf("ucfifo_status = %bx %bx\r\n", ucfifo_status, i);

        if (ucfifo_status == DPAUD_fifo_balance) {
            ucsearch_result = TRUE;
            break;
        }
    }

    SC_VPLL_CTRL |= BIT2;

    if (ucsearch_result == FALSE) {
        DP_AudioSetDefault();
    }

    //printf("ucsearch_result = %bx\r\n", ucsearch_result);
    return ucsearch_result;

#else //binary search method

    UCHAR ucfifo_status;
    ULONG ulaudio_n_tune = 0x004000;
    ULONG ulaudio_n_tune_upper = 0x008000, ulaudio_n_tune_bottom = 1;
    UCHAR ucsearch_result = FALSE;
    
    SC_DP_MANUAL_MAUD_LO = ulaudio_n_tune; 
    SC_DP_MANUAL_MAUD_MI = ulaudio_n_tune>>8; 
    SC_DP_MANUAL_MAUD_HI = ulaudio_n_tune>>16;     
    ucfifo_status = DP_AudioGetFIFOStatus();
        
    while (ucfifo_status  != DPAUD_fifo_balance || (ulaudio_n_tune_upper-ulaudio_n_tune_bottom) < 3) {
        if (ucfifo_status == DPAUD_fifo_underflow) {
            ulaudio_n_tune_upper = ulaudio_n_tune;
        }
        else if (ucfifo_status == DPAUD_fifo_overflow) {
            ulaudio_n_tune_bottom = ulaudio_n_tune;
        }
        else {
            DP_AudioSetDefault();
            break;
        }
        ulaudio_n_tune = (ulaudio_n_tune_upper + ulaudio_n_tune_bottom)/2;

        SC_DP_MANUAL_MAUD_LO = ulaudio_n_tune; 
        SC_DP_MANUAL_MAUD_MI = ulaudio_n_tune>>8); 
        SC_DP_MANUAL_MAUD_HI = ulaudio_n_tune>>16);     
        //printf("0x10  = %bx\r\n", ReadScaler(0x1000+0x10));
        //printf("0x11  = %bx\r\n", ReadScaler(0x1000+0x11));
        ucfifo_status = DP_AudioGetFIFOStatus();
        //printf("ucfifo_status  = %bx\r\n", ucfifo_status);
    }

    if (ucfifo_status == DPAUD_fifo_balance) {
        ucsearch_result = TRUE;
    }

    return ucsearch_result;
#endif    
}

//******************************************************************************
// Prototype: 
//  void DP_AudioMNChecker(void)
// Parameters:
//
// Return:
//  None
// Purpose:
//
// Notes:
//  None
//******************************************************************************
void DP_AudioMNChecker(void)
{
    UCHAR mn_search_result = FALSE;
    UCHAR ucfifo_status = DPAUD_fifo_unknown;
    
    if (bAudioMNChecking) {    
        if (SC_DP_INT_GROUP_3 & BIT6) { //packet recieved
            if (!(SC_DP_INT_GROUP_3 & BIT4)){//without M/N upated but with packet, enter search process
                DP_AudioSetAudioPath(DPAUD_path_manual);
             
                if (!DP_AudioMNSearch()) { //if no found in table, swich back to auto mode
                    DP_AudioSetAudioPath(DPAUD_path_auto);      
                }
            }

            SC_DP_RESET_FUNCTION |= BIT3; //audio fifo sw reset
            SC_DP_RESET_FUNCTION &= ~BIT3; //audio fifo sw reset            
            SC_DP_AUDIO_FIFO_CTRL &= ~BIT6; //audio fifo mute off        

            bAudioMNChecking = FALSE;
        }
    }
    else {
        if (SC_DP_PLL_CTRL & BIT6) {//manual mode     
            ucfifo_status = DP_AudioGetFIFOStatus(TRUE);
            if (ucfifo_status != DPAUD_fifo_balance) {
                DP_AudioMNCheckerInit();
            }
        }
    }
}

#if (ENABLE_DP_AUX_MONITOR==ON) 
#define DP_MONITOR ON	   
#define DP_DEBUG_PORT 0   //0~ 4
#define DP_STROBE_BUFFER_NUM_2 18000//18432 //6144*24/8
#define DP_STROBE_BUFFER_SIZE 4     
//UCHAR volatile xdata  *EDID_SRAM_BUFF0=0xF800;//the address 0xF802~0xF803 is used for reading strobe packet len

#if (DP_DEBUG_PORT==1)
	USHRT volatile xdata *strobe_count=0xF902;
#elif (DP_DEBUG_PORT==2)
	USHRT volatile xdata *strobe_count=0xFA02;
#elif (DP_DEBUG_PORT==3)
	USHRT volatile xdata *strobe_count=0xFB02;
#elif (DP_DEBUG_PORT==4)
	USHRT volatile xdata *strobe_count=0xFC02;
#else
	USHRT volatile xdata *strobe_count=0xF802;
#endif
   

void Init_DP_Strobe(void)
{
	  USHRT i;  
	  CORE_FIX=0x0F;   
    //DP_CTRL=0x1B; 
	  for(i=0;i<DP_STROBE_BUFFER_SIZE;i++) 
#if (DP_DEBUG_PORT==1)
     *(EDID_SRAM_BUFF1+i)=0x00;
#elif (DP_DEBUG_PORT==2)
     *(EDID_SRAM_BUFF2+i)=0x00;
#elif (DP_DEBUG_PORT==3)
     *(EDID_SRAM_BUFF3+i)=0x00;
#elif (DP_DEBUG_PORT==4)
     *(EDID_SRAM_BUFF4+i)=0x00;
#else
	  	*(EDID_SRAM_BUFF0+i)=0x00;
#endif	  	
    SC_CR_MUX = DP_DEBUG_PORT;
    // enable internal EDID for strobe reading
#if (DP_DEBUG_PORT==1)
      DDC_CTL1 &= ~BIT7;
      McuSetDDC(MCU_DDC_1, 0xA8, 1);  // 0xA8 is special address for Strobe debug reading 
      DDC_CTL1 |= BIT7; 
#elif (DP_DEBUG_PORT==2)
      DDC_CTL2 &= ~BIT7;
      McuSetDDC(MCU_DDC_2, 0xA8, 1);  // 0xA8 is special address for Strobe debug reading 
      DDC_CTL2 |= BIT7; 
#elif (DP_DEBUG_PORT==3)
      DDC_CTL3 &= ~BIT7;
      McuSetDDC(MCU_DDC_3, 0xA8, 1);  // 0xA8 is special address for Strobe debug reading 
      DDC_CTL3 |= BIT7; 
#elif (DP_DEBUG_PORT==4)
      DDC_CTL4 &= ~BIT7;
      McuSetDDC(MCU_DDC_4, 0xA8, 1);  // 0xA8 is special address for Strobe debug reading 
      DDC_CTL4 |= BIT7; 
#else
    DDC_CTL0 &= ~BIT7;
    McuSetDDC(MCU_DDC_0, 0xA8, 1);  // 0xA8 is special address for Strobe debug reading 
    DDC_CTL0 |= BIT7;    
#endif
   #if (DP_MONITOR==ON)	 
    AUX_STROBE_CTL|=BIT0;  // 
   #endif
}

void reset_DP_Strobe(void)
{
	  USHRT i;
	  //clear buffer 
	  for(i=0;i<DP_STROBE_BUFFER_SIZE;i++) 
			#if (DP_DEBUG_PORT==1)
			     *(EDID_SRAM_BUFF1+i)=0x00;
			#elif (DP_DEBUG_PORT==2)
			     *(EDID_SRAM_BUFF2+i)=0x00;
			#elif (DP_DEBUG_PORT==3)
			     *(EDID_SRAM_BUFF3+i)=0x00;
			#elif (DP_DEBUG_PORT==4)
			     *(EDID_SRAM_BUFF4+i)=0x00;
			#else
				  	*(EDID_SRAM_BUFF0+i)=0x00;  
			#endif		  

	//clear flag         
	(*strobe_count)=0;  
	SC_INDEX_CTRL = 0x80;
	SC_INDEX_ADDR_LO = 0; 
    SC_INDEX_ADDR_HI = 0;
    AUX_STROBE_CTL |= BIT3;   
}


// move AUX packets to OSD RAM
void  move_aux_packet(void) using 1
{ 
#if (DP_MONITOR==OFF)		
	UCHAR i=0;
#endif 

	if((*strobe_count)>=DP_STROBE_BUFFER_NUM_2)  //buffer is full,  continue to read Aux packet ,but does not store them
		return;

//#if IS_NT68850_SERIES 		
//		if(DP_SRC & BIT7)
//#else
//    if(INT_SRC3 & BIT0) 
//#endif	
		{  
//			if(AUX_STROBE_CTL & BIT3) //bit3:  AUX Debug path interrupt flag
			{        
					while(AUX_STROBE_CTL & BIT3)
	 				{
						#if (DP_MONITOR==OFF)				
							SC_INDEX_DATA=(AUX_STROBE_FUN&BIT3)?1:0;  // get data direction(RX or TX)
						#endif
						
							SC_INDEX_DATA=AUX_STROBE_PORT; //read strobe data

						#if (DP_MONITOR==OFF)							
							i++;
						#else
							(*strobe_count)++;
						#endif

							AUX_STROBE_CTL |= BIT3;  //clear interrupt flag
					  
					} 
				//george stop it:  CLR_WDT = 0x55;  		
			}

			#if (DP_MONITOR==OFF)			      
		      (*strobe_count)+=i*2;   
			#endif	      
	   } 
}



void DP_Strobe_Debug(void)
{   
	UCHAR i=0;
	#if (DP_DEBUG_PORT==1)
	  if((*EDID_SRAM_BUFF1)&BIT6)  //0xF900[6] is used for reset all flag and buffer
	#elif (DP_DEBUG_PORT==2)
	  if((*EDID_SRAM_BUFF2)&BIT6)  //0xFA00[6] is used for reset all flag and buffer
	#elif (DP_DEBUG_PORT==3)
	  if((*EDID_SRAM_BUFF3)&BIT6)  //0xFB00[6] is used for reset all flag and buffer
	#elif (DP_DEBUG_PORT==4)
	  if((*EDID_SRAM_BUFF4)&BIT6)  //0xFC00[6] is used for reset all flag and buffer
	#else
		if((*EDID_SRAM_BUFF0)&BIT6)  //0xF800[6] is used for reset all flag and buffer
	#endif
		{
			reset_DP_Strobe();
		}	
		//george stop it:  CLR_WDT = 0x55;
	#if (DP_DEBUG_PORT==1)
		DDC_CTL1=0xB0;
	#elif (DP_DEBUG_PORT==2)
		DDC_CTL2=0xB0;
	#elif (DP_DEBUG_PORT==3)
		DDC_CTL3=0xB0;
	#elif (DP_DEBUG_PORT==4)
		DDC_CTL4=0xB0;
	#else
		DDC_CTL0=0xB0;     
	#endif		  
		     
}



void DP_Aux_Channel_Monitor(void)
{
	  UCHAR cpu_speed,ip;        
	 
	if(AUX_STROBE_CTL&BIT0)
	{          
		#if (DP_MONITOR==ON)         
			SC_DP_AUX_CTRL2&=~BIT4;   //aux strobe listen mode
		#endif		

			cpu_speed=CPU_CLK; 

		#if IS_NT68850_SERIES			
			CPU_CLK=0x58;  //64Mhz
		#else
      		CPU_CLK=0x50;
		#endif			
		
			//use OSD RAM to store tmp AUX packets
			OSDAPI_OSDPowerOn();
			SC_INDEX_CTRL = 0x80;
			SC_INDEX_ADDR_LO = 0;
			SC_INDEX_ADDR_HI = 0;

		#if IS_NT68850_SERIES      
      		INTSC_EN|=BIT1;//DP interrrupt enable
		#else  //TC68370
      		INTSC_EN3|=BIT0;  
		#endif      
		
			AUX_STROBE_CTL = 0x07;// DP AUX STROBE    
			AUX_STROBE_CTL = 0x05;
	      	ip=IP;

		#if IS_NT68850_SERIES
			IP = 0x01;   // DP interrupt(Ext1) has the highest priority .    
		#else
			IP = 0x04; 
		#endif		  
		    
			while(AUX_STROBE_CTL&BIT0)
			{
				DP_Strobe_Debug();  
			}
	      	//backup 
	      
	      	IP=ip;
	        OSDAPI_OSDPowerOff();

		#if IS_NT68850_SERIES      
		      INTSC_EN&=~BIT1;//DP interrrupt enable
		#else  //TC68370
		      INTSC_EN3&=~BIT0;  
		#endif         
       
       
			CPU_CLK=cpu_speed;
		#if (DP_MONITOR==ON)
        	SC_DP_AUX_CTRL2|=BIT4;
		#endif
	}
}
#endif


#else 
void ForDPCompilerCodePass(void)
{
	code UCHAR temp[]={0x00};
	UCHAR i;
	i = temp[0];
}
#endif



