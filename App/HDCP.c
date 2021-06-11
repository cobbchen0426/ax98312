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

#if ENABLE_HDCP == ON

//******************************************************************************
// G L O B A L   D E F I N I T I O N S
//******************************************************************************
#define HDCP_KEY_OFFSET 5

//******************************************************************************
// S T A T I C   V A R I A B L E S
//******************************************************************************
static xdata USHRT usNVRamAddr_HDCP;
static xdata USHRT usHDCPChkSum1, usHDCPChkSum2 = 0;
static xdata UCHAR xdata *pHDCPbuffer;

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
// Prototype: 
//  void InitHDCP(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Load HDCP key and enable HDCP.
// Notes:
//  None
//******************************************************************************
void InitHDCP(void)
{
    pHDCPbuffer = FE2P_SRAM_ADDR + NVRAM_HDCP_ADDR;
    NvramReadHDCPdata(pHDCPbuffer);
#if ENABLE_DEMO_HDCP_KEY == ON
    WriteHDCPKey(NULL, NULL);
#else
    WriteHDCPKey(pHDCPbuffer, pHDCPbuffer + HDCP_KEY_OFFSET);
#endif
#if IS_NT68770_SERIES || IS_NT68850_SERIES || IS_NT68790_SERIES
    SC_HDCP_CTRL3 = 0x60; //CTS issue
#endif
    EnableHDCP();
}

#if ENABLE_NVT_HDCP_WRITER == ON
//******************************************************************************
// Prototype: 
//  void StartHDCPStoring(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Initiate HDCP-related parameters for storing HDCP.
// Notes:
//  None
//******************************************************************************
void StartHDCPStoring(void)
{
    pHDCPbuffer = (FE2P_SRAM_ADDR + NVRAM_HDCP_ADDR);
    usHDCPChkSum1 = 0;
    usHDCPChkSum2 = 0xFFFF;
    usNVRamAddr_HDCP = 0;
}

//******************************************************************************
// Prototype: 
//  void StoreHDCP(UCHAR *ptr, USHRT num)
// Parameters:
//  *ptr : pointer to data
//  num    : number of bytes to be stored
// Return:
//  None
// Purpose:
//  Store HDCP key.
// Notes:
//  None
//******************************************************************************
void StoreHDCP(UCHAR *ptr,  USHRT num)
{
    UCHAR i;

    for (i = 0; i < num; i++) {
        pHDCPbuffer[usNVRamAddr_HDCP] = *ptr;
        if (usNVRamAddr_HDCP < NUM_HDCP_TOTAL) {
            usHDCPChkSum1 += pHDCPbuffer[usNVRamAddr_HDCP];
        }
        usNVRamAddr_HDCP++;
        ptr++;
    }
}

//******************************************************************************
// Prototype: 
//  UCHAR CheckHDCPChkSum(void)
// Parameters:
//  None
// Return:
//  TRUR if checksum is correct. Otherwise, FALSE.
// Purpose:
//  Check HDCP checksum.
// Notes:
//  None
//******************************************************************************
UCHAR CheckHDCPChkSum(void)
{
    usHDCPChkSum2 = pHDCPbuffer[0x121];
    usHDCPChkSum2 = usHDCPChkSum2 << 8;
    usHDCPChkSum2 = usHDCPChkSum2 + pHDCPbuffer[0x122];

    if (usHDCPChkSum1 == usHDCPChkSum2) {
        NvramWriteHDCPdata(pHDCPbuffer);
        return 1;
    }
    else {
        return 0;
    }
}
#endif //#if ENABLE_NVT_HDCP_WRITER == ON

#if ENABLE_HDCP_TRIM_MODE == ON
//******************************************************************************
// Prototype: 
//  BOOL InitHDCPTrimKey(void)
// Parameters:
//  None
// Return:
//  return TRUE if load key successfully
// Purpose:
//  Load HDCP key and enable HDCP from E-fuse.
// Notes:
//  None
//******************************************************************************
BOOL InitHDCPTrimKey(void)
{
    UCHAR tmp_POWER_CTRL2, tmp_SC_HDCP_TRIM_CTRL2, tmp_SC_HDCP_TRIM_CTRL, tmp_LDO_ADJ, tmp_0x605, tmp_reg;
    UCHAR *p, i, tmp_0x81E7;//, tmp_0x8103, tmp_0x81FE;
    USHRT index;
#if (INPUT_INTERFACE&INPUT_DP)
    UCHAR *k;
#endif
#if ENABLE_HDCP_KEY_DCRPT == ON
    SC_HDCP_SYNC_SELECT = 0x08; // Set decryption key
#if (INPUT_INTERFACE&INPUT_DP)
    SC_DP_HDCP_CTRL = 0x28; // Set decryption key
#endif
#else
    SC_HDCP_SYNC_SELECT = 0x00; // Set non-decryption key
#if (INPUT_INTERFACE&INPUT_DP)
    SC_DP_HDCP_CTRL = 0x20; // Set non-decryption key
#endif
#endif

#if IS_NT68790_SERIES
    SC_HDCP_62E |= BIT3;
#endif

//    tmp_0x8103 = SC_POWER_CTRL3;
//    tmp_0x81FE = SC_LVDS_PAD_POWER;
    tmp_0x81E7 = SC_TMDS_LINK_CLK_SEL;
    tmp_0x605 = SC_HDMI_SOFTWARE_RESET;
    tmp_LDO_ADJ = LDO_ADJ;
    tmp_POWER_CTRL2 = SC_POWER_CTRL2;
    tmp_SC_HDCP_TRIM_CTRL2= SC_HDCP_TRIM_CTRL2;
    tmp_SC_HDCP_TRIM_CTRL= SC_HDCP_TRIM_CTRL;

    SC_HDMI_SOFTWARE_RESET &= ~(BIT7|BIT3);
    LDO_ADJ &= ~BIT7;
    SC_POWER_CTRL2 |= BIT1;
    SC_HDCP_INPUT_CTRL |= BIT7;
//    SC_POWER_CTRL3 |= BIT0;
//    SC_LVDS_PAD_POWER |= (BIT4 | BIT3);
    SC_TMDS_LINK_CLK_SEL |= BIT4;
    SC_HDCP_TRIM_CTRL2 &= ~BIT6;
    SC_HDCP_TRIM_CTRL |= BIT0;
    SC_HDCP_TRIM_CTRL &= ~BIT1;
    
    p = &SC_HDCP_BKSV;
    for (i=0; i<3; i++) {
        SC_HDCP_TRIM_ADDR = i + 140;
        SC_HDCP_TRIM_CTRL |= BIT6;
        *p = SC_HDCP_TRIM_DATA_LO;
        p++;
        *p = SC_HDCP_TRIM_DATA_HI;
        p++;
        ResetWDTimer();
    }  

#if (INPUT_INTERFACE&INPUT_DP)
    SC_DP_DEBUG |= BIT7;
    p = &SC_DP_HDCP_BKSV;
    k = &SC_HDCP_BKSV;
    for (i = 0; i < 5; i++) {
        tmp_reg = *k;
        *p = tmp_reg;
        p++;
        k++;
    }
    SC_DP_DEBUG &= ~BIT7;
#endif

    //Write Key
    tmp_reg = SC_INDEX_CTRL & 0x04;
    tmp_reg |= 0xE0;
    SC_INDEX_CTRL = tmp_reg;

    for (index=0; index<140; index++) {
        SC_HDCP_TRIM_ADDR = index;
        SC_HDCP_TRIM_CTRL |= BIT6;        
        SC_INDEX_ADDR_LO = (UCHAR)((2*index) & 0xFF);
        SC_INDEX_ADDR_HI = (UCHAR)((2*index) >> 8);
        SC_INDEX_DATA = SC_HDCP_TRIM_DATA_LO;  
        SC_INDEX_ADDR_LO = (UCHAR)((2*index+1) & 0xFF);
        SC_INDEX_ADDR_HI = (UCHAR)((2*index+1) >> 8);
        SC_INDEX_DATA = SC_HDCP_TRIM_DATA_HI;
        ResetWDTimer();
    }
// Set decryption key = 0x00, 0x00/////////////////////
        SC_INDEX_ADDR_LO = (UCHAR)((280) & 0xFF);
        SC_INDEX_ADDR_HI = (UCHAR)((280) >> 8);
        SC_INDEX_DATA = 0x00;  
        SC_INDEX_ADDR_LO = (UCHAR)((281) & 0xFF);
        SC_INDEX_ADDR_HI = (UCHAR)((281) >> 8);
        SC_INDEX_DATA = 0x00;  
////////////////////////////////////////////////////////

#if IS_NT68790_SERIES
    SC_HDCP_62E &= ~BIT3;
#endif

    EnableHDCP();
    SC_HDCP_TRIM_CTRL = tmp_SC_HDCP_TRIM_CTRL;
    SC_HDCP_TRIM_CTRL2 = tmp_SC_HDCP_TRIM_CTRL2;
    SC_HDMI_SOFTWARE_RESET = tmp_0x605;
//    SC_POWER_CTRL3 = tmp_0x8103;
//    SC_LVDS_PAD_POWER = tmp_0x81FE;
    SC_TMDS_LINK_CLK_SEL = tmp_0x81E7;
    LDO_ADJ = tmp_LDO_ADJ;
    SC_POWER_CTRL2 = tmp_POWER_CTRL2;
    Sleep(2);

    if ( SC_HDCP_BKSV == 0x00 && SC_HDCP_BKSV_B2 == 0x00 && SC_HDCP_BKSV_B3 == 0x00 ) {
        SC_HDCP_TRIM_CTRL = 0x08;
        return FALSE;
    }

    return TRUE;
}
#endif

#endif //#if ENABLE_HDCP == ON
