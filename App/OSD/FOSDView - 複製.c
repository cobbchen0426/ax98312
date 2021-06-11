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
#include "string.h"

//******************************************************************************
// M A C R O   D E F I N I T I O N S
//******************************************************************************
enum OSD_FACTORY {
    mfRESET,
    mfAUTO,
    mfGAINR,    mfGAING,    mfGAINB,
    mfOFFSETR,  mfOFFSETG,  mfOFFSETB,
    mf6500R,    mf6500G,    mf6500B,
    mf7500R,    mf7500G,    mf7500B,
    mf9300R,    mf9300G,    mf9300B,
    mfSRGBR,    mfSRGBG,    mfSRGBB,
    mfRETURN
};

typedef struct _LIGHTBAR_ {
    UCHAR x;
    UCHAR y;
    UCHAR len;
} LightBar ;

#define SetFactUpdFlag()    {ucUpdateFlag = 1;}
#define ClearFactUpdFlag()  {ucUpdateFlag = 0;}

//******************************************************************************
// G L O B A L   V A R I A B L E S
//******************************************************************************

//******************************************************************************
// S T A T I C   V A R I A B L E S
//******************************************************************************
static code UCHAR ucModelText[]={7,"NOVATEK"};
static code UCHAR ucVersionText[]={16,'V',VERSION+'0','.',(REVERSION>>4)+'0',(REVERSION&0x0F)+'0',' ',DATE};
static code UCHAR ucScalerText[]={7,SCALER_TEXT};
static code UCHAR ucPanelText[]={4, "DEMO"};
static code UCHAR ucAutoLevelText[]={10,"Auto Level"};
static code UCHAR ucBurnInText[]={6,"Burnin"};
static code UCHAR ucBrightnessText[]= {6,"Bright."};
static code UCHAR ucContrastText[]= {6,"Contr."};
static code UCHAR ucGainText[]={4,"Gain"};
static code UCHAR ucOffsetText[]={6,"Offset"};
static code UCHAR ucSRGBText[]={4,"sRGB"};
static code UCHAR ucColor5000Text[]={4,"5000"};
static code UCHAR ucColor6500Text[]={4,"6500"};
static code UCHAR ucColor7500Text[]={4,"7500"};
static code UCHAR ucColor8200Text[]={4,"8200"};
static code UCHAR ucColor9300Text[]={4,"9300"};
static code UCHAR ucColor11500Text[]={5,"11500"};
static code UCHAR ucAddressText[]={5,"Addr."};
static code UCHAR ucWRText[]={2,"WR"};
static code UCHAR ucResetText[]={5,"Reset"};
static code UCHAR ucPOTText[]={3,"POT"};
static code UCHAR ucExitText[] = {9,"Save&Exit"};
static code UCHAR ucH_Text[]={1,"H"};
static code UCHAR ucR_Text[]={1,"R"};
static code UCHAR ucG_Text[]={1,"G"};
static code UCHAR ucB_Text[]={1,"B"};
static code UCHAR ucSymbol1[]={1,"="};
static code UCHAR ucYesText[]={3,"YES"};
static code UCHAR ucNoText[]={2,"NO"};
static code UCHAR ucOkText[]={2,"OK"};

code LightBar LBar[] = {
    {0, 4,7},
    {0, 5,7},
    {7, 7,1},{12, 7,1},{17, 7,1},
    {7, 8,1},{12, 8,1},{17, 8,1},
    {7, 9,1},{12, 9,1},{17, 9,1},
    {7,10,1},{12,10,1},{17,10,1},
    {7,11,1},{12,11,1},{17,11,1},
    {7,12,1},{12,12,1},{17,12,1},
    {0,14,7},
};

static xdata UCHAR ucUpdateFlag;
static xdata UCHAR ucFactoryIndex;
static xdata USHRT usRegAddr;
static xdata UCHAR ucRegValue;

//******************************************************************************
// E X T E R N A L   V A R I A B L E   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// S T A T I C   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
static void FactorySelect(void);
static void FactoryUnSelect(void);
static void FactorySelectValue(void);
static void FactoryUnSelectValue(void);
static void FactoryShowValue(UCHAR index, USHRT value);
static void FactoryShowBurnin(void);
static void FactoryShowAutoColor(UCHAR result);
static void FactoryValueUp(UCHAR *val);
static void FactoryValueDown(UCHAR *val);
static void FactorySetValue(void);

//******************************************************************************
// E X T E R N A L   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// Prototype:
//  UCHAR OSDFactoryUpdate(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Return flag for informing system to save caldata
// Notes:
//  None
//******************************************************************************
UCHAR OSDFactoryUpdate(void)
{
    UCHAR tmp;
    tmp = ucUpdateFlag;
    ClearFactUpdFlag();
    return tmp;
}


//******************************************************************************
// Prototype:
//  void OSDShowFactory(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Show Factory OSD
// Notes:
//  None
//******************************************************************************
void OSDShowFactory(void)
{
 //   UCHAR i;
	unsigned char i,j;
	xdata unsigned char FHbuff[20],FVbuff[20];


    OSDAPI_TurnOffOSD();
    OSDInitFrame(OSD_FACTORY_W,OSD_FACTORY_H,FACTORY_FRAME_COLOR);
    OSDAPI_SetPosition(99,98);
    // ----------------------------------------

    OSDAPI_SetIndentIndex(32);
    OSDAPI_SetAlignType(OSD_ALIGN_LEFT);

    OSDAPI_ShowIndentString(FALSE,  0, 0,1,ucModelText);
    OSDAPI_ShowIndentString(FALSE, 10, 0,1,ucVersionText);
//===HSync======================================FEFANJACKY===============

    if(SC_GI_SYNC_STATUS & BIT0 == 1)
       sprintf(FHbuff+1,"HSync: + %d KHz ",usHSyncFreq);
    else
       sprintf(FHbuff+1,"HSync: - %d KHz ",usHSyncFreq);

	FHbuff[0] = strlen(FHbuff+1);

	for(j = 1;j < (FHbuff[0]+1); j++)
	{
		if (FHbuff[j] == 'K') {
           FHbuff[j-1] = FHbuff[j-2];
           FHbuff[j-2] = '.';
           j= FHbuff[0]+1;
        }
	}
		
    OSDAPI_ShowIndentString(FALSE,0,1,1,FHbuff);  
//===VSync======================================FEFANJACKY===============

    if(SC_GI_SYNC_STATUS & BIT1 == 1)
       sprintf(FVbuff+1,"VSync: + %d Hz ",usVSyncFreq);
    else
       sprintf(FVbuff+1,"VSync: - %d Hz ",usVSyncFreq);

	FVbuff[0] = strlen(FVbuff+1);

	for(j = 1;j < (FVbuff[0]+1); j++)
	{
		if (FVbuff[j] == 'H') {
           FVbuff[j-1] = FVbuff[j-2];
		   FVbuff[j-2] = '.';
           j= FVbuff[0]+1;
        }
	}		
    OSDAPI_ShowIndentString(FALSE,0,2,1,FVbuff);  
//=======================================================================
    OSDAPI_ShowIndentString(FALSE, LBar[mfRESET].x, LBar[mfRESET].y,1,ucResetText);
    OSDAPI_ShowIndentString(FALSE, LBar[mfAUTO].x, LBar[mfAUTO].y,1,ucAutoLevelText);

    OSDAPI_ShowIndentString(FALSE, 0, 7,1,ucGainText);
    OSDAPI_ShowIndentString(FALSE, 0, 8,1,ucOffsetText);
    OSDAPI_ShowIndentString(FALSE, 0, 9,1,ucColor6500Text);
    OSDAPI_ShowIndentString(FALSE, 0,10,1,ucColor7500Text);
    OSDAPI_ShowIndentString(FALSE, 0,11,1,ucColor9300Text);
    OSDAPI_ShowIndentString(FALSE, 0,12,1,ucSRGBText);
    OSDAPI_ShowIndentString(FALSE, LBar[mfRETURN].x, LBar[mfRETURN].y,1,ucExitText);

    for (i=0;i<6;i++)
        OSDAPI_ShowIndentString(FALSE,  7,  7+i,1,ucR_Text);
    for (i=0;i<6;i++)
        OSDAPI_ShowIndentString(FALSE, 12,  7+i,1,ucG_Text);
    for (i=0;i<6;i++)
        OSDAPI_ShowIndentString(FALSE, 17,  7+i,1,ucB_Text);

    FactoryShowValue(mfGAINR, (USHRT)(CalibData.ucADCRGain));
    FactoryShowValue(mfGAING, (USHRT)(CalibData.ucADCGGain));
    FactoryShowValue(mfGAINB, (USHRT)(CalibData.ucADCBGain));
    FactoryShowValue(mfOFFSETR, (USHRT)(CalibData.ucADCROffset));
    FactoryShowValue(mfOFFSETG, (USHRT)(CalibData.ucADCGOffset));
    FactoryShowValue(mfOFFSETB, (USHRT)(CalibData.ucADCBOffset));
    FactoryShowValue(mf6500R, (USHRT)CalibData.uc6500KRGain);
    FactoryShowValue(mf6500G, (USHRT)CalibData.uc6500KGGain);
    FactoryShowValue(mf6500B, (USHRT)CalibData.uc6500KBGain);
    FactoryShowValue(mf7500R, (USHRT)CalibData.uc7500KRGain);
    FactoryShowValue(mf7500G, (USHRT)CalibData.uc7500KGGain);
    FactoryShowValue(mf7500B, (USHRT)CalibData.uc7500KBGain);
    FactoryShowValue(mf9300R, (USHRT)CalibData.uc9300KRGain);
    FactoryShowValue(mf9300G, (USHRT)CalibData.uc9300KGGain);
    FactoryShowValue(mf9300B, (USHRT)CalibData.uc9300KBGain);
    FactoryShowValue(mfSRGBR, (USHRT)CalibData.ucsRGBRGain);
    FactoryShowValue(mfSRGBG, (USHRT)CalibData.ucsRGBGGain);
    FactoryShowValue(mfSRGBB, (USHRT)CalibData.ucsRGBBGain);

    ucFactoryIndex = mfAUTO;
    FactorySelect();

    OSDTurnOnOSD();
}

//******************************************************************************
// Prototype:
//  void OSDFactoryUp(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
void OSDFactoryUp(void)
{
    FactoryUnSelect();
    if(--ucFactoryIndex > mfRETURN)
        ucFactoryIndex = mfRETURN;
    FactorySelect();

    if(ucFactoryIndex == mf6500B){
        UserData.ucColorTemp = CLRTMP_6500K;
        UserSetColorTemp();
    }
    else if(ucFactoryIndex == mf7500B){
        UserData.ucColorTemp = CLRTMP_7500K;
        UserSetColorTemp();
    }
    else if(ucFactoryIndex == mf9300B){
        UserData.ucColorTemp = CLRTMP_9300K;
        UserSetColorTemp();
    }
    else if(ucFactoryIndex == mfSRGBB){
        UserData.ucColorTemp = CLRTMP_sRGB;
        UserSetColorTemp();
    }
/*
    else if(ucFactoryIndex == mf5000B){
        UserData.ucColorTemp = CLRTMP_5000K;
        UserSetColorTemp();
    }
    else if(ucFactoryIndex == mf8200B){
        UserData.ucColorTemp = CLRTMP_8200K;
        UserSetColorTemp();
    }
    else if(ucFactoryIndex == mf11500B){
        UserData.ucColorTemp = CLRTMP_11500K;
        UserSetColorTemp();
    }
*/
    else if(ucFactoryIndex == mfOFFSETB){
        UserData.ucColorTemp = CLRTMP_6500K;
        UserSetColorTemp();
    }
}

//******************************************************************************
// Prototype:
//  void OSDFactoryDown(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
void OSDFactoryDown(void)
{
    FactoryUnSelect();
    if(++ucFactoryIndex > mfRETURN)
        ucFactoryIndex = mfRESET;
    FactorySelect();

    if(ucFactoryIndex == mf6500R){
        UserData.ucColorTemp = CLRTMP_6500K;
        UserSetColorTemp();
    }
    else if(ucFactoryIndex == mf7500R){
        UserData.ucColorTemp = CLRTMP_7500K;
        UserSetColorTemp();
    }
    else if(ucFactoryIndex == mf9300R){
        UserData.ucColorTemp = CLRTMP_9300K;
        UserSetColorTemp();
    }
    else if(ucFactoryIndex == mfSRGBR){
        UserData.ucColorTemp = CLRTMP_sRGB;
        UserSetColorTemp();
    }
/*
    else if(ucFactoryIndex == mf5000R){
        UserData.ucColorTemp = CLRTMP_5000K;
        UserSetColorTemp();
    }
    else if(ucFactoryIndex == mf8200R){
        UserData.ucColorTemp = CLRTMP_8200K;
        UserSetColorTemp();
    }
    else if(ucFactoryIndex == mf11500R){
        UserData.ucColorTemp = CLRTMP_11500K;
        UserSetColorTemp();
    }
    else if(ucFactoryIndex == mfADDRESS){
        UserData.ucColorTemp = CLRTMP_6500K;
        UserSetColorTemp();
    }
*/
    else if(ucFactoryIndex == mfRETURN){
        UserData.ucColorTemp = CLRTMP_6500K;
        UserSetColorTemp();
    }
}

//******************************************************************************
// Prototype:
//  void OSDFactoryEnterItm(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
void OSDFactoryEnterItm(void)
{
    UCHAR auto_color;

    if(ucFactoryIndex == mfAUTO) {
        OSDAPI_TurnOffOSD();
        auto_color = AutoColor();
        if (auto_color) {
            CalibData.ucADCRGain = GetADCRGain();
            CalibData.ucADCGGain = GetADCGGain();
            CalibData.ucADCBGain = GetADCBGain();
            CalibData.ucADCROffset = GetADCROffset();
            CalibData.ucADCGOffset = GetADCGOffset();
            CalibData.ucADCBOffset = GetADCBOffset();
            SetFactUpdFlag();
        }
//        OSDShowFactory();  //fefanjacky
        OSDEnterFactory();  //fefanjacky
        FactoryShowAutoColor(auto_color);
        return;
    }
    else if(ucFactoryIndex == mfRESET){
        NvramInitialize(NVRAM_UPDATE_ALL);  //fefanjacky
        NvramLoadData();                    //fefanjacky
        OSDAPI_TurnOffOSD();
        UserRecallConfiguration();
         //OSDShowFactory(); //fefanjacky
        OSDEnterFactory();  //fefanjacky      
        SetFactUpdFlag();
        return;
    }
    else if(ucFactoryIndex == mfRETURN){
         SystemData.bFactory = FALSE; 
         //UserData.ucColorTemp = CLRTMP_6500K; //FEFANJACKY
         //UserSetColorTemp(); //FEFANJACKY      
         OSDCloseAll();  //jacky
         DPHPDOff();  //jacky add for factory to user mode not into dp mode
        return;
    }
    else {
        FactoryUnSelect();
        FactorySelectValue();
    }
}

//******************************************************************************
// Prototype:
//  void OSDFactoryExitItm(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
void OSDFactoryExitItm(void)
{
    FactoryUnSelectValue();
    FactorySelect();
}

//******************************************************************************
// Prototype:
//  void OSDFactoryItmUp(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
void OSDFactoryItmUp(void)
{
    switch(ucFactoryIndex) {
/*
        case mfBURNING:
            SystemData.bBurnIn = ~SystemData.bBurnIn;
            FactoryShowBurnin();
            break;
*/
        case mfGAINR:
            FactoryValueUp(&CalibData.ucADCRGain);
            FactoryShowValue(mfGAINR, (USHRT)CalibData.ucADCRGain);
            break;
        case mfGAING:
            FactoryValueUp(&CalibData.ucADCGGain);
            FactoryShowValue(mfGAING, (USHRT)CalibData.ucADCGGain);
            break;
        case mfGAINB:
            FactoryValueUp(&CalibData.ucADCBGain);
            FactoryShowValue(mfGAINB, (USHRT)CalibData.ucADCBGain);
            break;
        case mfOFFSETR:
            FactoryValueUp(&CalibData.ucADCROffset);
            FactoryShowValue(mfOFFSETR, (USHRT)CalibData.ucADCROffset);
            break;
        case mfOFFSETG:
            FactoryValueUp(&CalibData.ucADCGOffset);
            FactoryShowValue(mfOFFSETG, (USHRT)CalibData.ucADCGOffset);
            break;
        case mfOFFSETB:
            FactoryValueUp(&CalibData.ucADCBOffset);
            FactoryShowValue(mfOFFSETB, (USHRT)CalibData.ucADCBOffset);
            break;
        case mf9300R:
            FactoryValueUp(&CalibData.uc9300KRGain);
            FactoryShowValue(mf9300R, (USHRT)CalibData.uc9300KRGain);
            break;
        case mf9300G:
            FactoryValueUp(&CalibData.uc9300KGGain);
            FactoryShowValue(mf9300G, (USHRT)CalibData.uc9300KGGain);
            break;
        case mf9300B:
            FactoryValueUp(&CalibData.uc9300KBGain);
            FactoryShowValue(mf9300B, (USHRT)CalibData.uc9300KBGain);
            break;
        case mf7500R:
            FactoryValueUp(&CalibData.uc7500KRGain);
            FactoryShowValue(mf7500R, (USHRT)CalibData.uc7500KRGain);
            break;
        case mf7500G:
            FactoryValueUp(&CalibData.uc7500KGGain);
            FactoryShowValue(mf7500G, (USHRT)CalibData.uc7500KGGain);
            break;
        case mf7500B:
            FactoryValueUp(&CalibData.uc7500KBGain);
            FactoryShowValue(mf7500B, (USHRT)CalibData.uc7500KBGain);
            break;
        case mf6500R:
            FactoryValueUp(&CalibData.uc6500KRGain);
            FactoryShowValue(mf6500R, (USHRT)CalibData.uc6500KRGain);
            break;
        case mf6500G:
            FactoryValueUp(&CalibData.uc6500KGGain);
            FactoryShowValue(mf6500G, (USHRT)CalibData.uc6500KGGain);
            break;
        case mf6500B:
            FactoryValueUp(&CalibData.uc6500KBGain);
            FactoryShowValue(mf6500B, (USHRT)CalibData.uc6500KBGain);
            break;
        case mfSRGBR:
            FactoryValueUp(&CalibData.ucsRGBRGain);
            FactoryShowValue(mfSRGBR, (USHRT)CalibData.ucsRGBRGain);
            break;
        case mfSRGBG:
            FactoryValueUp(&CalibData.ucsRGBGGain);
            FactoryShowValue(mfSRGBG, (USHRT)CalibData.ucsRGBGGain);
            break;
        case mfSRGBB:
            FactoryValueUp(&CalibData.ucsRGBBGain);
            FactoryShowValue(mfSRGBB, (USHRT)CalibData.ucsRGBBGain);
            break;
/*
        case mf5000R:
            FactoryValueUp(&CalibData.uc5000KRGain);
            FactoryShowValue(mf5000R, (USHRT)CalibData.uc5000KRGain);
            break;
        case mf5000G:
            FactoryValueUp(&CalibData.uc5000KGGain);
            FactoryShowValue(mf5000G, (USHRT)CalibData.uc5000KGGain);
            break;
        case mf5000B:
            FactoryValueUp(&CalibData.uc5000KBGain);
            FactoryShowValue(mf5000B, (USHRT)CalibData.uc5000KBGain);
            break;
        case mf8200R:
            FactoryValueUp(&CalibData.uc8200KRGain);
            FactoryShowValue(mf8200R, (USHRT)CalibData.uc8200KRGain);
            break;
        case mf8200G:
            FactoryValueUp(&CalibData.uc8200KGGain);
            FactoryShowValue(mf8200G, (USHRT)CalibData.uc8200KGGain);
            break;
        case mf8200B:
            FactoryValueUp(&CalibData.uc8200KBGain);
            FactoryShowValue(mf8200B, (USHRT)CalibData.uc8200KBGain);
            break;
        case mf11500R:
            FactoryValueUp(&CalibData.uc11500KRGain);
            FactoryShowValue(mf11500R, (USHRT)CalibData.uc11500KRGain);
            break;
        case mf11500G:
            FactoryValueUp(&CalibData.uc11500KGGain);
            FactoryShowValue(mf11500G, (USHRT)CalibData.uc11500KGGain);
            break;
        case mf11500B:
            FactoryValueUp(&CalibData.uc11500KBGain);
            FactoryShowValue(mf11500B, (USHRT)CalibData.uc11500KBGain);
            break;
        case mfADDRESS:
            FactoryShowValue(mfADDRESS, (USHRT)usRegAddr);
            break;
        case mfWR:
            FactoryShowValue(mfWR, (USHRT)ucRegValue);
            break;
*/
    }
    FactorySetValue();
}

//******************************************************************************
// Prototype:
//  void OSDFactoryItmDown(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
void OSDFactoryItmDown(void)
{
    switch(ucFactoryIndex) {
/*
        case mfBURNING:
            SystemData.bBurnIn = ~SystemData.bBurnIn;
            FactoryShowBurnin();
            break;
*/
        case mfGAINR:
            FactoryValueDown(&CalibData.ucADCRGain);
            FactoryShowValue(mfGAINR, (USHRT)CalibData.ucADCRGain);
            break;
        case mfGAING:
            FactoryValueDown(&CalibData.ucADCGGain);
            FactoryShowValue(mfGAING, (USHRT)CalibData.ucADCGGain);
            break;
        case mfGAINB:
            FactoryValueDown(&CalibData.ucADCBGain);
            FactoryShowValue(mfGAINB, (USHRT)CalibData.ucADCBGain);
            break;
        case mfOFFSETR:
            FactoryValueDown(&CalibData.ucADCROffset);
            FactoryShowValue(mfOFFSETR, (USHRT)CalibData.ucADCROffset);
            break;
        case mfOFFSETG:
            FactoryValueDown(&CalibData.ucADCGOffset);
            FactoryShowValue(mfOFFSETG, (USHRT)CalibData.ucADCGOffset);
            break;
        case mfOFFSETB:
            FactoryValueDown(&CalibData.ucADCBOffset);
            FactoryShowValue(mfOFFSETB, (USHRT)CalibData.ucADCBOffset);
            break;
        case mf9300R:
            FactoryValueDown(&CalibData.uc9300KRGain);
            FactoryShowValue(mf9300R, (USHRT)CalibData.uc9300KRGain);
            break;
        case mf9300G:
            FactoryValueDown(&CalibData.uc9300KGGain);
            FactoryShowValue(mf9300G, (USHRT)CalibData.uc9300KGGain);
            break;
        case mf9300B:
            FactoryValueDown(&CalibData.uc9300KBGain);
            FactoryShowValue(mf9300B, (USHRT)CalibData.uc9300KBGain);
            break;
        case mf7500R:
            FactoryValueDown(&CalibData.uc7500KRGain);
            FactoryShowValue(mf7500R, (USHRT)CalibData.uc7500KRGain);
            break;
        case mf7500G:
            FactoryValueDown(&CalibData.uc7500KGGain);
            FactoryShowValue(mf7500G, (USHRT)CalibData.uc7500KGGain);
            break;
        case mf7500B:
            FactoryValueDown(&CalibData.uc7500KBGain);
            FactoryShowValue(mf7500B, (USHRT)CalibData.uc7500KBGain);
            break;
        case mf6500R:
            FactoryValueDown(&CalibData.uc6500KRGain);
            FactoryShowValue(mf6500R, (USHRT)CalibData.uc6500KRGain);
            break;
        case mf6500G:
            FactoryValueDown(&CalibData.uc6500KGGain);
            FactoryShowValue(mf6500G, (USHRT)CalibData.uc6500KGGain);
            break;
        case mf6500B:
            FactoryValueDown(&CalibData.uc6500KBGain);
            FactoryShowValue(mf6500B, (USHRT)CalibData.uc6500KBGain);
            break;
        case mfSRGBR:
            FactoryValueDown(&CalibData.ucsRGBRGain);
            FactoryShowValue(mfSRGBR, (USHRT)CalibData.ucsRGBRGain);
            break;
        case mfSRGBG:
            FactoryValueDown(&CalibData.ucsRGBGGain);
            FactoryShowValue(mfSRGBG, (USHRT)CalibData.ucsRGBGGain);
            break;
        case mfSRGBB:
            FactoryValueDown(&CalibData.ucsRGBBGain);
            FactoryShowValue(mfSRGBB, (USHRT)CalibData.ucsRGBBGain);
            break;
/*
        case mf5000R:
            FactoryValueDown(&CalibData.uc5000KRGain);
            FactoryShowValue(mf5000R, (USHRT)CalibData.uc5000KRGain);
            break;
        case mf5000G:
            FactoryValueDown(&CalibData.uc5000KGGain);
            FactoryShowValue(mf5000G, (USHRT)CalibData.uc5000KGGain);
            break;
        case mf5000B:
            FactoryValueDown(&CalibData.uc5000KBGain);
            FactoryShowValue(mf5000B, (USHRT)CalibData.uc5000KBGain);
            break;
        case mf8200R:
            FactoryValueDown(&CalibData.uc8200KRGain);
            FactoryShowValue(mf8200R, (USHRT)CalibData.uc8200KRGain);
            break;
        case mf8200G:
            FactoryValueDown(&CalibData.uc8200KGGain);
            FactoryShowValue(mf8200G, (USHRT)CalibData.uc8200KGGain);
            break;
        case mf8200B:
            FactoryValueDown(&CalibData.uc8200KBGain);
            FactoryShowValue(mf8200B, (USHRT)CalibData.uc8200KBGain);
            break;
        case mf11500R:
            FactoryValueDown(&CalibData.uc11500KRGain);
            FactoryShowValue(mf11500R, (USHRT)CalibData.uc11500KRGain);
            break;
        case mf11500G:
            FactoryValueDown(&CalibData.uc11500KGGain);
            FactoryShowValue(mf11500G, (USHRT)CalibData.uc11500KGGain);
            break;
        case mf11500B:
            FactoryValueDown(&CalibData.uc11500KBGain);
            FactoryShowValue(mf11500B, (USHRT)CalibData.uc11500KBGain);
            break;
        case mfADDRESS:
            FactoryShowValue(mfADDRESS, (USHRT)usRegAddr);
            break;
        case mfWR:
            FactoryShowValue(mfWR, (USHRT)ucRegValue);
            break;
*/
    }
    FactorySetValue();
}


void FactorySelect(void)
{
    OSDAPI_FillLineAttr(LBar[ucFactoryIndex].x, LBar[ucFactoryIndex].y,
                        LBar[ucFactoryIndex].len,FACTORY_ITEM_COLOR);
}

void FactoryUnSelect(void)
{
    OSDAPI_FillLineAttr(LBar[ucFactoryIndex].x, LBar[ucFactoryIndex].y,
                        LBar[ucFactoryIndex].len, FACTORY_FRAME_COLOR);
}


void FactorySelectValue(void)
{
    if ((ucFactoryIndex >= mfGAINR) && (ucFactoryIndex <= mf9300B)) {
        OSDAPI_FillLineAttr(LBar[ucFactoryIndex].x+LBar[ucFactoryIndex].len,
                            LBar[ucFactoryIndex].y,
                            3, FACTORY_ITEM_COLOR);
    }
/*
    else if (ucFactoryIndex == mfBURNING) {
        OSDAPI_FillLineAttr(LBar[ucFactoryIndex].x+LBar[ucFactoryIndex].len,
                            LBar[ucFactoryIndex].y,
                            5, FACTORY_ITEM_COLOR);
    }
    else if ( ucFactoryIndex == mfWR ) {
        OSDAPI_FillLineAttr(LBar[ucFactoryIndex].x-5,
                            LBar[ucFactoryIndex].y,
                            4, FACTORY_ITEM_COLOR);
    }
*/
    else {
        OSDAPI_FillLineAttr(LBar[ucFactoryIndex].x+LBar[ucFactoryIndex].len,
                            LBar[ucFactoryIndex].y,
                            4, FACTORY_ITEM_COLOR);
    }
}

void FactoryUnSelectValue(void)
{
    if ((ucFactoryIndex >= mfGAINR) && (ucFactoryIndex <= mf9300B)) {
        OSDAPI_FillLineAttr(LBar[ucFactoryIndex].x+LBar[ucFactoryIndex].len,
                            LBar[ucFactoryIndex].y,
                            3, FACTORY_FRAME_COLOR);
    }
/*
    else if (ucFactoryIndex == mfBURNING) {
        OSDAPI_FillLineAttr(LBar[ucFactoryIndex].x+LBar[ucFactoryIndex].len,
                            LBar[ucFactoryIndex].y,
                            5, FACTORY_FRAME_COLOR);
    }
    else if ( ucFactoryIndex == mfWR ) {
        OSDAPI_FillLineAttr(LBar[ucFactoryIndex].x-5,
                            LBar[ucFactoryIndex].y,
                            4, FACTORY_FRAME_COLOR);
    }
*/
    else {
        OSDAPI_FillLineAttr(LBar[ucFactoryIndex].x+LBar[ucFactoryIndex].len,
                            LBar[ucFactoryIndex].y,
                            4, FACTORY_FRAME_COLOR);
    }
}

void FactoryShowValue(UCHAR index, USHRT value)
{
    if(index >= mfGAINR &&  index <= mfOFFSETB){
        OSDShowNum(LBar[index].x+1, LBar[index].y, 255-value);
    }
    else if(index >= mfSRGBR &&  index <= mf9300B){
        OSDShowNum(LBar[index].x+1, LBar[index].y, value);
    }
/*
    else if(index == mfADDRESS){
        OSDShowNum(LBar[index].x+LBar[index].len+2, LBar[index].y, (UCHAR)(value>>8));
        OSDShowNum(LBar[index].x+LBar[index].len, LBar[index].y, value);
    }
    else if(index == mfWR){
        OSDShowNum(LBar[index].x-5, LBar[index].y, value);
    }
*/
    else{
        OSDShowNum(LBar[index].x+LBar[index].len, LBar[index].y, value);
    }
}

/*
void FactoryShowBurnin(void)
{
    OSDAPI_SetIndentIndex(0xF8);
    OSDAPI_SetAlignType(OSD_ALIGN_LEFT);
    if (SystemData.bBurnIn == 1)
        OSDAPI_ShowIndentString(FALSE, LBar[mfBURNING].x+8, LBar[mfBURNING].y, 3, ucYesText);
    else
        OSDAPI_ShowIndentString(FALSE, LBar[mfBURNING].x+8, LBar[mfBURNING].y, 3, ucNoText);
}
*/

void FactoryShowAutoColor(UCHAR result)
{
    OSDAPI_SetIndentIndex(0xF0);
    OSDAPI_SetAlignType(OSD_ALIGN_LEFT);

    if (result == 1)
        OSDAPI_ShowIndentString(FALSE, LBar[mfAUTO].x+8, LBar[mfAUTO].y, 3, ucOkText);
    else
        OSDAPI_ShowIndentString(FALSE, LBar[mfAUTO].x+8, LBar[mfAUTO].y, 3, ucNoText);
}

void FactoryValueUp(UCHAR *val)
{
    if(++(*val) == 0x00) {
        (*val) = 0xFF;
    }
}

void FactoryValueDown(UCHAR *val)
{
    if(--(*val) == 0xFF) {
        (*val) = 0;
    }
}

void FactorySetValue(void)
{
    switch(ucFactoryIndex) {
/*
        case mfBURNING:
            break;
*/
        case mfGAINR:
        case mfGAING:
        case mfGAINB:
        case mfOFFSETR:
        case mfOFFSETG:
        case mfOFFSETB:
            SetADCRGain(CalibData.ucADCRGain);
            SetADCGGain(CalibData.ucADCGGain);
            SetADCBGain(CalibData.ucADCBGain);
            SetADCROffset(CalibData.ucADCROffset);
            SetADCGOffset(CalibData.ucADCGOffset);
            SetADCBOffset(CalibData.ucADCBOffset);
            SetFactUpdFlag();
            break;
        case mf9300R:
        case mf9300G:
        case mf9300B:
        case mf7500R:
        case mf7500G:
        case mf7500B:
        case mf6500R:
        case mf6500G:
        case mf6500B:
        case mfSRGBR:
        case mfSRGBG:
        case mfSRGBB:
/*
        case mf5000R:
        case mf5000G:
        case mf5000B:
        case mf8200R:
        case mf8200G:
        case mf8200B:
        case mf11500R:
        case mf11500G:
        case mf11500B:
*/
            UserSetColorTemp();
            SetFactUpdFlag();
            break;
/*
        case mfADDRESS:
            break;
        case mfWR:
            break;
*/
    }
}
