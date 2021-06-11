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

#if ENABLE_MMU == ON
//******************************************************************************
// M A C R O   D E F I N I T I O N S
//******************************************************************************
#define MMUDRAMIF_NUM     11
#define MMUDQSDelay_NUM   11 
#define MMUPLL_NUM        16
#define MMUPLLSKEW_NUN    3
#define MMUPLLFREQ_NUM    4

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
static void MMUCalculateBW(USHRT frchtot);

//******************************************************************************
// E X T E R N A L   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
void MMUConfigFIFO();
//******************************************************************************
// F U N C T I O N   B O D Y S
//******************************************************************************

/**************************************************************************//**
 * Get MMU DRAM I/F Control Setting
 ******************************************************************************/
UCHAR GetMMUDRAMIF(UCHAR point)
{
    UCHAR ucSCID = GetSCID();
    code UCHAR MMUDRAMIF[][MMUDRAMIF_NUM]={ //770
#if IS_NT68770_SERIES    
     //=======[ 770E ]========     
       SCREG_580_E,
       SCREG_581_E,
       SCREG_582_E,
       SCREG_583_E,
       SCREG_584_E,
       SCREG_585_E,
       SCREG_586_E,
       SCREG_587_E,
       SCREG_588_E,
       SCREG_589_E,
       SCREG_58A_E, 
     //=======[ 770G ]========     
       SCREG_580_G,
       SCREG_581_G,
       SCREG_582_G,
       SCREG_583_G,
       SCREG_584_G,
       SCREG_585_G,
       SCREG_586_G,
       SCREG_587_G,
       SCREG_588_G,
       SCREG_589_G,
       SCREG_58A_G,
     //=======[ 770H ]========     
       SCREG_580_H,    
       SCREG_581_H,    
       SCREG_582_H,    
       SCREG_583_H,    
       SCREG_584_H,    
       SCREG_585_H,    
       SCREG_586_H,    
       SCREG_587_H,    
       SCREG_588_H,    
       SCREG_589_H,    
       SCREG_58A_H,   
       
#elif IS_NT68850_SERIES || IS_NT68790_SERIES
       //=======[ 850 ]========     
       SCREG_580,
       SCREG_581,
       SCREG_582,
       SCREG_583,
       SCREG_584,
       SCREG_585,
       SCREG_586,
       SCREG_587,
       SCREG_588,
       SCREG_589,
       SCREG_58A, 
#endif       
     }; 

     if((ucSCID & 0x0F) > (((sizeof(MMUDRAMIF)/sizeof(MMUDRAMIF[0][0]))/MMUDRAMIF_NUM)-1)){
       return MMUDRAMIF[0][point]; 
     } 

     return MMUDRAMIF[ucSCID & 0x0F][point];   
}
        
/**************************************************************************//**
 * Get MMU DQS Delay Control Setting
 ******************************************************************************/
UCHAR GetMMUDQSDelay(UCHAR point)
{
    UCHAR ucSCID = GetSCID();
    code UCHAR MMUDQSDelay[][MMUDQSDelay_NUM]={
#if IS_NT68770_SERIES    
     //=======[ 770E ]========     
       SCREG_5F0_E,
       SCREG_5F1_E,
       SCREG_5F2_E,
       SCREG_5F3_E,
       SCREG_5F4_E,
       SCREG_5F5_E,
       SCREG_5F6_E,
       SCREG_5F7_E,
       SCREG_5F8_E,
       SCREG_5F9_E,
       SCREG_5FA_E,
     //=======[ 770G ]========     
       SCREG_5F0_G,
       SCREG_5F1_G,
       SCREG_5F2_G,
       SCREG_5F3_G,
       SCREG_5F4_G,
       SCREG_5F5_G,
       SCREG_5F6_G,
       SCREG_5F7_G,
       SCREG_5F8_G,
       SCREG_5F9_G,
       SCREG_5FA_G,
     //=======[ 770H ]========     
       SCREG_5F0_H,                
       SCREG_5F1_H,                
       SCREG_5F2_H,                
       SCREG_5F3_H,                
       SCREG_5F4_H,                
       SCREG_5F5_H,                
       SCREG_5F6_H,                
       SCREG_5F7_H,                
       SCREG_5F8_H,                
       SCREG_5F9_H,                
       SCREG_5FA_H, 
        
#elif IS_NT68850_SERIES || IS_NT68790_SERIES
     //=======[ 850 ]========     
       SCREG_5F0,
       SCREG_5F1,
       SCREG_5F2,
       SCREG_5F3,
       SCREG_5F4,
       SCREG_5F5,
       SCREG_5F6,
       SCREG_5F7,
       SCREG_5F8,
       SCREG_5F9,
       SCREG_5FA, 
#endif       
     }; 
        
     if((ucSCID & 0x0F) > (((sizeof(MMUDQSDelay)/sizeof(MMUDQSDelay[0][0]))/MMUDQSDelay_NUM)-1)){
        return MMUDQSDelay[0][point]; 
     }  
         
     return MMUDQSDelay[ucSCID & 0x0F][point];   
}

/**************************************************************************//**
 * Get MMU PLL Control Setting
 ******************************************************************************/
UCHAR GetMMUPLL(UCHAR point)
{
    UCHAR ucSCID = GetSCID();
    code UCHAR MMUPLL[][MMUPLL_NUM]={
#if IS_NT68770_SERIES    
     //=======[ 770E ]========     
       SCREG_B80_E,
       SCREG_B81_E,
       SCREG_B82_E,
       SCREG_B83_E,
       SCREG_B84_E,
       SCREG_B85_E,
       SCREG_B86_E,
       SCREG_B87_E,
       SCREG_B88_E,
       SCREG_B89_E,
       SCREG_B8A_E,
       SCREG_B8B_E,
       SCREG_B8C_E,
       SCREG_B8D_E,
       SCREG_B8E_E,
       SCREG_B8F_E,
     //=======[ 770G ]========     
       SCREG_B80_G,
       SCREG_B81_G,
       SCREG_B82_G,
       SCREG_B83_G,
       SCREG_B84_G,
       SCREG_B85_G,
       SCREG_B86_G,
       SCREG_B87_G,
       SCREG_B88_G,
       SCREG_B89_G,
       SCREG_B8A_G,
       SCREG_B8B_G,
       SCREG_B8C_G,
       SCREG_B8D_G,
       SCREG_B8E_G,
       SCREG_B8F_G,
    //=======[ 770H ]========   
       SCREG_B80_H,
       SCREG_B81_H,
       SCREG_B82_H,
       SCREG_B83_H,
       SCREG_B84_H,
       SCREG_B85_H,
       SCREG_B86_H,
       SCREG_B87_H,
       SCREG_B88_H,
       SCREG_B89_H,
       SCREG_B8A_H,
       SCREG_B8B_H,
       SCREG_B8C_H,
       SCREG_B8D_H,
       SCREG_B8E_H,
       SCREG_B8F_H,
       
#elif IS_NT68850_SERIES || IS_NT68790_SERIES
     //=======[ 850 ]========     
       SCREG_B80,
       SCREG_B81,
       SCREG_B82,
       SCREG_B83,
       SCREG_B84,
       SCREG_B85,
       SCREG_B86,
       SCREG_B87,
       SCREG_B88,
       SCREG_B89,
       SCREG_B8A,
       SCREG_B8B,
       SCREG_B8C,
       SCREG_B8D,
       SCREG_B8E,
       SCREG_B8F, 
#endif       
     };   

     if((ucSCID & 0x0F) > (((sizeof(MMUPLL)/sizeof(MMUPLL[0][0]))/MMUPLL_NUM)-1)){
        return MMUPLL[0][point]; 
     }   
        
     return MMUPLL[ucSCID & 0x0F][point];   
}

/**************************************************************************//**
 * Get MMU PLL SKEW Setting
 ******************************************************************************/
UCHAR GetMMUPLLSKEW(UCHAR point)
{
    UCHAR ucSCID = GetSCID();
    code UCHAR MMUPLLSKEW[][MMUPLLSKEW_NUN]={
#if IS_NT68770_SERIES    
     //=======[ 770E ]========     
       SCREG_B90_E,
       SCREG_B91_E,
       SCREG_B92_E,
     //=======[ 770G ]========     
       SCREG_B90_G,
       SCREG_B91_G,
       SCREG_B92_G, 
     //=======[ 770H ]========     
       SCREG_B90_H,
       SCREG_B91_H,
       SCREG_B92_H,
        
#elif IS_NT68850_SERIES || IS_NT68790_SERIES
     //=======[ 850 ]========     
       SCREG_B90,
       SCREG_B91,
       SCREG_B92,
#endif       
     };   

    if((ucSCID & 0x0F) > (((sizeof(MMUPLLSKEW)/sizeof(MMUPLLSKEW[0][0]))/MMUPLLSKEW_NUN)-1)){
        return MMUPLLSKEW[0][point]; 
    }   

    return MMUPLLSKEW[ucSCID &0x0F][point];   
}

/**************************************************************************//**
 * Get Memory PLL Frequency Control Setting
 ******************************************************************************/
UCHAR GetMMUPLLFREQ(UCHAR point)
{
    UCHAR ucSCID = GetSCID();
    code UCHAR MMUPLLFREQ[][MMUPLLFREQ_NUM]={
#if IS_NT68770_SERIES    
     //=======[ 770E ]========     
       SCREG_B31_E,
       SCREG_B32_E,
       SCREG_B33_E,
       SCREG_B34_E,
     //=======[ 770G ]========     
       SCREG_B31_G,
       SCREG_B32_G,
       SCREG_B33_G,
       SCREG_B34_G,
    //=======[ 770H ]========     
       SCREG_B31_H,
       SCREG_B32_H,
       SCREG_B33_H,
       SCREG_B34_H,
        
#elif IS_NT68850_SERIES || IS_NT68790_SERIES
     //=======[ 850 ]========     
       SCREG_B31,
       SCREG_B32,
       SCREG_B33,
       SCREG_B34,
#endif       
     };  

    if((ucSCID & 0x0F) > (((sizeof(MMUPLLFREQ)/sizeof(MMUPLLFREQ[0][0]))/MMUPLLFREQ_NUM)-1)){
        return MMUPLLFREQ[0][point]; 
    }    
    
    return MMUPLLFREQ[ucSCID & 0x0F][point];   
}
        
/**************************************************************************//**
 * Initialize MMU-related registers.
 ******************************************************************************/
void MMUInitialize(void)
{
UCHAR volatile xdata *ptr;
UCHAR i;
    ptr = 0x8B31;
    for (i=0; i<MMUPLLFREQ_NUM; i++) {
        *ptr = GetMMUPLLFREQ(i);
        ptr++;
    }

    ptr = &SC_DRAM_INTERFACE_LO;//0x8580;
    for (i=0; i<MMUDRAMIF_NUM; i++) {
        *ptr = GetMMUDRAMIF(i);
        ptr++;
    }


    ptr = &SC_MMU_DLL_CTRL;//0x8B80;
    for (i=0; i<MMUPLL_NUM; i++) {
        *ptr = GetMMUPLL(i);
        ptr++;
    }
        
    ptr = &SC_DRAM_CLOCK_CTRL; //0x85F0;
    for (i=0; i<MMUDQSDelay_NUM; i++) {
        *ptr = GetMMUDQSDelay(i);
        ptr++;
    }

    ptr = &SC_MMU_PLL_SKEW5;//0x8B90;
    for (i=0; i<MMUPLLSKEW_NUN; i++) {
        *ptr = GetMMUPLLSKEW(i);
        ptr++;
    }

    
    
#if 0//IS_NT68850_SERIES
     SC_MMU_B4E = 0x80;
#endif

    SC_DVI2_ZERO_POWER_DETECT = SCREG_B5E;
//    SC_DRAM_INTERFACE_LO &= BIT0;
//    SC_DRAM_INTERFACE_LO |= BIT0;

    
    MMUPowerOn();
    
    MMUConfigFIFO();

    Write3ByteScaler(&SC_FRAME_BUFFER1L_BASE_ADDR_FRC_LO, 0x00000000);
    Write3ByteScaler(&SC_FRAME_BUFFER2L_BASE_ADDR_FRC_LO, 0x00040000);
    Write3ByteScaler(&SC_FRAME_BUFFER_BASE_ADDR_OD_LO, 0x00060000);
}

/**************************************************************************//**
 * Set MMU FIFO.
 ******************************************************************************/
void MMUConfigFIFO()
{
    code UCHAR ucFIFOAddr[] = {
        0x56, 0x57, 0x58, 0x59,

        0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 
        0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8,
        0xBC, 0xBD, 0xBE, 0xBF, 0xC0, 0xC1,
    };

    code UCHAR ucFIFOValue[] = {
        0xDF,    //0x8556
        0x03,    //0x8557
        0xDF,    //0x8558
        0x03,    //0x8559

        0x3F,    //0x8595
        0xEF,    //0x8596
        0xAF,    //0x8597
        0x6F,    //0x8598
        0x9F,    //0x8599
        0x4F,    //0x859A

        0x00,    //0x85A3
        0x00,    //0x85A4
        0xD0,    //0x85A5
        0x02,    //0x85A6
        0xD1,    //0x85A7
        0xCF,    //0x85A8

        0x01,    //0x85BC
        0x00,    //0x85BD
        0xD0,    //0x85BE
        0x12,    //0x85BF
        0xD1,    //0x85C0
        0xCF,    //0x85C1
    };

    UCHAR i;
    UCHAR xdata * ptr;

    ptr = 0x8500;

    for (i = 0; i < sizeof(ucFIFOAddr); i++) {
        ptr = (UCHAR xdata *)(0x8500 + ucFIFOAddr[i]);
        *ptr = ucFIFOValue[i];
    }
}

/**************************************************************************//**
 * Turn on MMU power.
 ******************************************************************************/
void MMUPowerOn(void)
{
    SC_DRAM_MMU_REQUEST_W = 0x00;
    SC_DRAM_MMU_REQUEST_R = 0x00;
    SC_POWER_CTRL2 |= BIT2;
    SC_MCLK_RATIO_HI = GetMMUPLLFREQ(2);//SCREG_B33_G;
    SC_MMU_DLL_CTRL = GetMMUPLL(0);//SCREG_B80;
    SC_MMU_B84 = GetMMUPLL(4);//SCREG_B84;
    SC_DRAM_INTERFACE_LO = GetMMUDRAMIF(0);//SCREG_580;
    SC_DRAM_INTERFACE_HI = GetMMUDRAMIF(1);//SCREG_581;

    SC_MMU_CFG2 = 0x01;

}

/**************************************************************************//**
 * Turn off MMU power.
 ******************************************************************************/
void MMUPowerOff(void)
{
    UCHAR ucSCID=GetSCID();
    SC_OD_CONFIGURATION = 0x00;
    SC_FRC_CTRL = 0x00;
    SC_MMU_CFG2 = 0x00;
    SC_AUTO_REFLESH_CTRL = 0x00;
    SC_DRAM_MMU_REQUEST_W = 0xFF;
    SC_DRAM_MMU_REQUEST_R = 0xFF;
    SC_DRAM_MMU_MODE_2 = 0x01;
    if ((ucSCID >= SCID_850_D && ucSCID <= SCID_850_FINAL) || \
        (ucSCID >= SCID_770_H && ucSCID <= SCID_770_FINAL)) {
        SC_DRAM_INTERFACE_HI = 0x13 | BIT6;
    }
    else {
    SC_DRAM_INTERFACE_HI = 0x13;
    }
    SC_DRAM_INTERFACE_LO &= ~BIT0;//= (SCREG_580&~BIT0);
    SC_MMU_DLL_CTRL = 0x00;
    SC_MMU_B84 = 0x00;
    SC_POWER_CTRL2 &= ~BIT2;
    SC_MCLK_RATIO_HI = 0x00;
}

#if ENABLE_PREFRC == ON || ENABLE_DFR == ON
/**************************************************************************//**
 * Config FRC or DFR setting.
 ******************************************************************************/
void MMUConfig(void)
{
#if ENABLE_PREFRC == ON
    MMUConfigPreFRC();
#elif ENABLE_DFR == ON
    MMUConfigDFR();

#endif
}
#endif

#if ENABLE_PREFRC == ON
//******************************************************************************
// Prototype: 
//  void MMUConfigFRC( )
// Parameters:
// Return:
//  None
// Purpose:
// Notes:
//  None
//******************************************************************************
void MMUConfigPreFRC(void)
{
    ULONG clock;
    USHRT htotal, vtotal;
    USHRT vtotal_LB, vtotal_HB;

    if (usVSyncFreq < FRC_NACT_MIN || usVSyncFreq > FRC_NACT_MAX) { // FRC    
    //printf("MMUConfigPreFRC\r\n");
        vtotal = ReadShortScaler(&SC_GI_CAP_VLEN_LO) + 20;
        clock = (ULONG)UserPanelData.usTypHTotal * UserPanelData.usTypVTotal;
        htotal = clock / vtotal;

        if ( htotal > 4095 ) {
            htotal >>= 1;
            SC_FRC_CLOCK_SEL = 0x50;
        }
        else {
            SC_FRC_CLOCK_SEL = 0x40;
        }

        MMUCalculateBW(htotal);
        
        WriteShortScaler(&SC_FRC_OUTPUT_H_TOTAL_LO, htotal);
        WriteShortScaler(&SC_FRC_OUTPUT_V_TOTAL_LO, vtotal);
        WriteShortScaler(&SC_FRC_OUTPUT_H_ACTIVE_LO, ReadShortScaler(&SC_GI_CAP_HWID_LO));
        WriteShortScaler(&SC_FRC_OUTPUT_V_ACTIVE_LO, ReadShortScaler(&SC_GI_CAP_VLEN_LO));

        // Calculate FRC V point high level higher/lower bound
        vtotal_LB = vtotal - 5;        
        vtotal = GetDigInputVTotalImmediate();        
        vtotal_HB = (float)(1 - (float)FRC_V_FREQ*10/usVSyncFreq) * vtotal + 20;
        
        SC_FRC_POINT1_HI = 0x00;
        SC_FRC_H_POINT1_LO = 0x00;
        SC_FRC_POINT2_HI = 0x00;
        SC_FRC_H_POINT2_LO = 0x00;

        SC_FRC_V_POINT1_LO = (UCHAR) vtotal_LB;
        SC_FRC_POINT1_HI = (UCHAR)((vtotal_LB >> 4)&0xF0);
        SC_FRC_V_POINT2_LO = (UCHAR) vtotal_HB;
        SC_FRC_POINT2_HI = (UCHAR)((vtotal_HB >> 4)&0xF0);

        if (usVSyncFreq > 620) {
            SC_FRC_CTRL = 0x03;
        }
        else if (usVSyncFreq < 500) {
            SC_FRC_CTRL = 0x13;
        }
    }
    else {
        SC_FRC_CTRL = 0x00;
    }
}
//******************************************************************************
// Prototype: 
//  void MMUCalculateBW( )
// Parameters:
// Return:
//  None
// Purpose:
// Notes:
//  None
//******************************************************************************
static void MMUCalculateBW(USHRT frchtot)
{
#define BWlimit 202

    USHRT input_hactive, input_htotal;
    USHRT input_clk;
    ULONG ulDisplayClk;
    ULONG prefrc_wbw, prefrc_rbw, od_rwbw;
    USHRT total_bw;

    input_hactive = ReadShortScaler(&SC_GI_CAP_HWID_LO);
    input_htotal = GetDigInputHTotalImmediate();
    ulDisplayClk = (ULONG)GetDisplayDCLK()/1000000;
    input_clk = TMDS_GetClock();
    
//FRC write BW
    prefrc_wbw = (ULONG)input_clk*input_hactive/input_htotal*3;
    //printf("prefrc_wbw %ld\r\n",prefrc_wbw);
//FRC read BW
    prefrc_rbw = (ULONG)ulDisplayClk*input_hactive/frchtot*3;
    //printf("prefrc_rbw %ld\r\n",prefrc_rbw);
//OD read/write BW
    od_rwbw = (ULONG)ulDisplayClk*UserPanelData.usWidth/UserPanelData.usTypHTotal*3*2/4;
    //printf("od_rwbw %ld\r\n",od_rwbw);
//Dram_32Bit_Freq
    total_bw = (USHRT)(prefrc_wbw + prefrc_rbw + od_rwbw)/4;
    //printf("total_bw %d\r\n",total_bw);

    if ((total_bw < BWlimit) && (SC_OD_DDC_CONFIGURATION == 0x01)) {
//        ODAPI_EnableOD();
        SC_OD_CONFIGURATION |= BIT0;
    }
    else {
//        ODAPI_DisableOD();
        SC_OD_CONFIGURATION &= ~BIT0;
    }
}
#endif

#if ENABLE_DFR == ON
//******************************************************************************
// Prototype: 
//  void MMUConfigDFR( )
// Parameters:
// Return:
//  None
// Purpose:
// Notes:
//  None
//******************************************************************************
void MMUConfigDFR(void)
{
    USHRT htotal, vtotal, vactive;
    UCHAR i;

    if (usVSyncFreq < 310 ) { //DFR    
    //printf("MMUConfigDFR\r\n");
        htotal = GetDigInputHTotalImmediate();
        i = 255;
        do {
//            Sleep(1);
            vtotal = GetDigInputHTotalImmediate();
            if ((htotal & 0xFFFE) == htotal) {//even
                break;
            }
            else if ((vtotal & 0xFFFE) == vtotal) {//even
                htotal = vtotal;
                break;
            }
            else {//both odd
                if (htotal != vtotal) {
                    htotal = (htotal + vtotal) / 2;
                }
            }
            i--;
        } while (i != 0);
        vtotal = GetDigInputVTotalImmediate();
        vactive = ReadShortScaler(&SC_GI_CAP_VLEN_LO);

        WriteShortScaler(&SC_FRC_OUTPUT_H_TOTAL_LO, htotal);
        WriteShortScaler(&SC_FRC_OUTPUT_V_TOTAL_LO, vtotal);
        WriteShortScaler(&SC_FRC_OUTPUT_H_ACTIVE_LO, ReadShortScaler(&SC_GI_CAP_HWID_LO));
        WriteShortScaler(&SC_FRC_OUTPUT_V_ACTIVE_LO, vactive);
        SC_FRC_CTRL = 0x43;

        SC_FRC_POINT1_HI = 0x00;
        SC_FRC_POINT1_HI |= (UCHAR)((vactive>>1)>>8)<<4;
        SC_FRC_V_POINT1_LO = (UCHAR)(vactive>>1)+2;
        SC_FRC_CLOCK_SEL &= 0x0F;
        SC_FRC_CLOCK_SEL |= 0x30;
    #if (INPUT_INTERFACE&INPUT_DP)  
        if (GetCurrInputInterface() == DISPLAY_PORT_INPUT) {
            SC_VPLL_CTRL1 |= BIT4;
        }
        else {
            SC_VPLL_CTRL1 &= ~BIT4;
        }
    #endif
    }
    else {
        SC_FRC_CTRL = 0x00;
    #if (INPUT_INTERFACE&INPUT_DP)  
        if (GetCurrInputInterface() == DISPLAY_PORT_INPUT) {
            SC_VPLL_CTRL1 &= ~BIT4;
        }
    #endif
    }
}
#endif

#endif //ENABLE_MMU == ON
