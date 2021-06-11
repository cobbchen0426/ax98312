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

//******************************************************************************
// M A C R O   D E F I N I T I O N S
//******************************************************************************

#define SetFactUpdFlag()    {ucUpdateFlag = 1;}
#define ClearFactUpdFlag()  {ucUpdateFlag = 0;}

//******************************************************************************
// G L O B A L   V A R I A B L E S
//******************************************************************************
//============== CHIU
//******************************************************************************
// S T A T I C   V A R I A B L E S
//******************************************************************************


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
static code UCHAR ucExitText[] = {4,"Exit"};
static code UCHAR ucH_Text[]={1,"H"};
static code UCHAR ucR_Text[]={1,"R"};
static code UCHAR ucG_Text[]={1,"G"};
static code UCHAR ucB_Text[]={1,"B"};
static code UCHAR ucSymbol1[]={1,"="};
static code UCHAR ucYesText[]={3,"YES"};
static code UCHAR ucNoText[]={2,"NO"};
static code UCHAR ucOkText[]={2,"OK"};
static code UCHAR ucGammaText[]= {6,"GAMMA:"};
static code UCHAR ucBacklightText[]= {10,"BACKLIGHT:"};



typedef struct _LIGHTBAR_ {
    UCHAR x;
    UCHAR y;
    UCHAR len;
} LightBar ;

code LightBar LBar[] = {
	{0, 0,5},   {7, 0,10 },    {17, 0,4},
	{0, 1,6},	{10, 1,10},		//GAMMA , BACKLITE
	{7, 2,1},{12,2,1},{17,2,1},
    {7, 3,1},{12,3,1},{17,3,1},
    {7, 4,1},{12,4,1},{17,4,1},
//    {7, 5,1},{12,5,1},{17,5,1},
    {7, 5,1},{12,5,1},{17,5,1},
    {7, 6,1},{12,6,1},{17,6,1},    
    {0, 8,6},
    {0, 9,6},   
};

enum OSD_FACTORY {
	mfFIRST = 0,
	mfRESET = mfFIRST,    mfAUTO,    mfRETURN,
	mfGAMMA,	mfBACKLIGHT,
	mf6500R,    mf6500G,    mf6500B,
	mf7500R,    mf7500G,    mf7500B,
	mf9300R,    mf9300G,    mf9300B,
//	mfSRGBR,    mfSRGBG,    mfSRGBB,
	mfGAINR,    mfGAING,    mfGAINB,
    mfOFFSETR,  mfOFFSETG,  mfOFFSETB,          
    
    mfBRIGHTNESS,
    mfCONTRAST,    
    mfLAST = mfCONTRAST,
};



static xdata UCHAR ucUpdateFlag;
static xdata UCHAR ucFactoryIndex;
static xdata USHRT usRegAddr;
static xdata UCHAR ucRegValue;
static xdata OSDState usOSDState = OSD_OFF_STATE;

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
//static void FactoryShowBurnin(void);
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



//============ CHIU ================
#include "string.h"
/*
typedef struct _INPUT_TIMING_FORMAT_ {
    USHRT usHSyncFreq;
    USHRT usVSyncFreq;
    UCHAR ucHVPolarity;
    UCHAR ucHSyncWidth;
    UCHAR ucVSyncWidth;
    USHRT usHTotal;
    USHRT usVTotal;
    USHRT usModeHActive;
    USHRT usModeVActive;
    USHRT usCapHActive;
    USHRT usCapVActive;
    USHRT usHStart;
    USHRT usVStart;
    UCHAR ucPhase;
    USHRT usHTotal50;
    USHRT usHStart50;
    USHRT usVStart50;
    USHRT usHTotalMin;
    USHRT usHTotalMax;
    USHRT usHStartMin;
    USHRT usHStartMax;
    USHRT usVStartMin;
    USHRT usVStartMax;
    UCHAR ucAutoTune;
    USHRT usModeIndex;
} InputTimingFormat;
*/

//HVPolarity Definition
//#define HNVN  0x01 /*!< H/V polarities are -/-. */
//#define HNVP  0x02 /*!< H/V polarities are -/+. */
//#define HPVN  0x04 /*!< H/V polarities are +/-. */
//#define HPVP  0x08 /*!< H/V polarities are +/+. */


//extern xdata ULONG ulDisplayClk;

void OSDShowInTiming(void)
{
//	UCHAR i;
    UCHAR buff[32];
	char pol;
	
	OSDAPI_SetAlignType(OSD_ALIGN_LEFT);
	
	//SHOW H
	pol = InputTiming.ucHVPolarity & 0x0C ? '+' : '-';
    sprintf(buff,"nH(%c)%d %d %d %d",  
    pol,InputTiming.usHSyncFreq, InputTiming.usHStart, InputTiming.usModeHActive,InputTiming.usHTotal);        
    buff[0] = strlen(buff) - 1;    OSDAPI_ShowIndentString(FALSE, 0, LBar[mfLAST].y+1, buff[0] , buff);		
	
	
	//SHOW V
	pol = InputTiming.ucHVPolarity & 0x03 ? '+' : '-';
    sprintf(buff,"nV(%c)%d %d %d %d",  
    pol,InputTiming.usVSyncFreq, InputTiming.usVStart, InputTiming.usModeVActive,InputTiming.usVTotal);
    buff[0] = strlen(buff) - 1;    OSDAPI_ShowIndentString(FALSE, 0, LBar[mfLAST].y+2, buff[0] , buff);		
	
	//SHOW OTHER
	sprintf(buff,"n(%d)(%d)",  
	InputTiming.usModeIndex,0);
	buff[0] = strlen(buff) - 1;    OSDAPI_ShowIndentString(FALSE, 0, LBar[mfLAST].y+3, buff[0] , buff);		
}
//
void ShowGammaValue(void)
{	
	static code UCHAR ucGamma0Text[]= {3,"1.9"};
	static code UCHAR ucGamma1Text[]= {3,"2.0"};
	static code UCHAR ucGamma2Text[]= {3,"2.1"};
	static code UCHAR ucGamma3Text[]= {3,"2.2"};	//CalibData.ucGammaVal=3
	static code UCHAR ucGamma4Text[]= {3,"2.3"};
	static code UCHAR ucGamma5Text[]= {3,"2.4"};
	static code UCHAR ucGamma6Text[]= {3,"2.5"};
	
	static code UCHAR *tab[] = {ucGamma0Text,ucGamma1Text,ucGamma2Text,ucGamma3Text,ucGamma4Text,ucGamma5Text,ucGamma6Text,};
	
	OSDAPI_SetIndentIndex(100);
    OSDAPI_SetAlignType(OSD_ALIGN_LEFT);
    
    OSDAPI_ShowIndentString(FALSE, 7, LBar[mfGAMMA].y,1,tab[CalibData.ucGammaVal]);    
   
}


//============ CHIU ================






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
    UCHAR i;

    OSDAPI_TurnOffOSD();
    OSDInitFrame(OSD_FACTORY_W,OSD_FACTORY_H,FACTORY_FRAME_COLOR);
    OSDAPI_SetPosition(99,98);
    // ----------------------------------------

    OSDAPI_SetIndentIndex(32);
    OSDAPI_SetAlignType(OSD_ALIGN_LEFT);
	
	//SAME AS BRIGHTNESS
   	OSDAPI_ShowIndentString(TRUE, 10, LBar[mfBRIGHTNESS].y,1,ucModelText);    	OSDAPI_ShowIndentString(FALSE,10 + 5, LBar[mfBRIGHTNESS].y,1,ucDateText);  
   	//SAME AS CONTRAST
    OSDAPI_ShowIndentString(TRUE, 10, LBar[mfCONTRAST].y,1,ucPanelText); 
        
    OSDAPI_ShowIndentString(FALSE, LBar[mfGAMMA].x, LBar[mfGAMMA].y,1,ucGammaText); 
    ShowGammaValue();
    
    
    
    OSDAPI_ShowIndentString(FALSE, LBar[mfBACKLIGHT].x, LBar[mfBACKLIGHT].y,1,ucBacklightText);     
    FactoryShowValue(mfBACKLIGHT, (USHRT)(CalibData.ucBacklite));
    
    
    OSDAPI_ShowIndentString(FALSE, 0, LBar[mf6500R].y,1,ucColor6500Text);
    OSDAPI_ShowIndentString(FALSE, 0, LBar[mf7500R].y,1,ucColor7500Text);
    OSDAPI_ShowIndentString(FALSE, 0, LBar[mf9300R].y,1,ucColor9300Text);
    //OSDAPI_ShowIndentString(FALSE, 0, LBar[mfSRGBR].y,1,ucSRGBText);  
    OSDAPI_ShowIndentString(FALSE, 0, LBar[mfGAINR].y,1,ucGainText);
    OSDAPI_ShowIndentString(FALSE, 0, LBar[mfOFFSETR].y,1,ucOffsetText);     

    OSDAPI_ShowIndentString(FALSE, LBar[mfBRIGHTNESS].x, LBar[mfBRIGHTNESS].y,1,ucBrightnessText);
    OSDAPI_ShowIndentString(FALSE, LBar[mfCONTRAST].x, LBar[mfCONTRAST].y,1,ucContrastText);
    
    OSDAPI_ShowIndentString(FALSE, LBar[mfRESET].x, LBar[mfRESET].y,1,ucResetText);
    OSDAPI_ShowIndentString(FALSE, LBar[mfAUTO].x, LBar[mfAUTO].y,1,ucAutoLevelText);
	OSDAPI_ShowIndentString(FALSE, LBar[mfRETURN].x, LBar[mfRETURN].y,1,ucExitText); 

	//SHOW R,G,B TEXT		
    for (i=0;i<5;i++)
        OSDAPI_ShowIndentString(FALSE, LBar[mf6500R].x,  LBar[mf6500R].y+i,1,ucR_Text);
    for (i=0;i<5;i++)
        OSDAPI_ShowIndentString(FALSE, LBar[mf6500G].x,  LBar[mf6500R].y+i,1,ucG_Text);
    for (i=0;i<5;i++)
        OSDAPI_ShowIndentString(FALSE, LBar[mf6500B].x,  LBar[mf6500R].y+i,1,ucB_Text);	
	
	//SHOW R,G,B VALUE
    FactoryShowValue(mfGAINR, (USHRT)(CalibData.ucADCRGain));
    FactoryShowValue(mfGAING, (USHRT)(CalibData.ucADCGGain));
    FactoryShowValue(mfGAINB, (USHRT)(CalibData.ucADCBGain));
    FactoryShowValue(mfOFFSETR, (USHRT)(CalibData.ucADCROffset));
    FactoryShowValue(mfOFFSETG, (USHRT)(CalibData.ucADCGOffset));
    FactoryShowValue(mfOFFSETB, (USHRT)(CalibData.ucADCBOffset));
    FactoryShowValue(mf9300R, (USHRT)CalibData.uc9300KRGain);
    FactoryShowValue(mf9300G, (USHRT)CalibData.uc9300KGGain);
    FactoryShowValue(mf9300B, (USHRT)CalibData.uc9300KBGain);
    FactoryShowValue(mf7500R, (USHRT)CalibData.uc7500KRGain);
    FactoryShowValue(mf7500G, (USHRT)CalibData.uc7500KGGain);
    FactoryShowValue(mf7500B, (USHRT)CalibData.uc7500KBGain);
    FactoryShowValue(mf6500R, (USHRT)CalibData.uc6500KRGain);
    FactoryShowValue(mf6500G, (USHRT)CalibData.uc6500KGGain);
    FactoryShowValue(mf6500B, (USHRT)CalibData.uc6500KBGain);
//    FactoryShowValue(mfSRGBR, (USHRT)CalibData.ucsRGBRGain);
//    FactoryShowValue(mfSRGBG, (USHRT)CalibData.ucsRGBGGain);
//    FactoryShowValue(mfSRGBB, (USHRT)CalibData.ucsRGBBGain);
    FactoryShowValue(mfBRIGHTNESS, (USHRT)UserData.ucBrightness);
    FactoryShowValue(mfCONTRAST, (USHRT)UserData.ucContrast);
    
    //SHOW DEBUG INPUT TIMING
  	OSDShowInTiming();
     
    
    
    ucFactoryIndex = mfFIRST;
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
    //if(--ucFactoryIndex > mfRETURN)        ucFactoryIndex = mfRETURN;
    
   	if(ucFactoryIndex == mfFIRST)	ucFactoryIndex = mfLAST;
   	else	ucFactoryIndex--;
        
    FactorySelect();

    if(ucFactoryIndex == mf9300B){
        UserData.ucColorTemp = CLRTMP_9300K;
        UserSetColorTemp();
    }
    else if(ucFactoryIndex == mf7500B){
        UserData.ucColorTemp = CLRTMP_7500K;
        UserSetColorTemp();
    }
    else if(ucFactoryIndex == mf6500B){
        UserData.ucColorTemp = CLRTMP_6500K;
        UserSetColorTemp();
    }
 //   else if(ucFactoryIndex == mfSRGBB){
 //       UserData.ucColorTemp = CLRTMP_sRGB;
 //       UserSetColorTemp();
 //  }

 //   else if(ucFactoryIndex == mf8200B){
 //       UserData.ucColorTemp = CLRTMP_8200K;
 //       UserSetColorTemp();
 //   }
 //   else if(ucFactoryIndex == mf9300B){
 //       UserData.ucColorTemp = CLRTMP_9300K;
 //       UserSetColorTemp();
 //   }
 //   else if(ucFactoryIndex == mf11500B){
 //       UserData.ucColorTemp = CLRTMP_11500K;
 //       UserSetColorTemp();
 //   }
    else if(ucFactoryIndex == mfOFFSETB){
        UserData.ucColorTemp = CLRTMP_9300K;
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
    //if(++ucFactoryIndex > mfRETURN)        ucFactoryIndex = mfFIRST;    
    
    if(ucFactoryIndex == mfLAST)	ucFactoryIndex = mfFIRST;
   	else	ucFactoryIndex++;
    
    
    FactorySelect();


    if(ucFactoryIndex == mf9300R){
        UserData.ucColorTemp = CLRTMP_9300K;
        UserSetColorTemp();
    }
    else if(ucFactoryIndex == mf7500R){
        UserData.ucColorTemp = CLRTMP_7500K;
        UserSetColorTemp();
    }
    else if(ucFactoryIndex == mf6500R){
        UserData.ucColorTemp = CLRTMP_6500K;
        UserSetColorTemp();
    }
//    else if(ucFactoryIndex == mfSRGBR){
//        UserData.ucColorTemp = CLRTMP_sRGB;
//        UserSetColorTemp();
//    }
//    else if(ucFactoryIndex == mf8200R){
//        UserData.ucColorTemp = CLRTMP_8200K;
//        UserSetColorTemp();
//    }
//    else if(ucFactoryIndex == mf9300R){
//        UserData.ucColorTemp = CLRTMP_9300K;
//        UserSetColorTemp();
//    }
 //   else if(ucFactoryIndex == mf11500R){
 //       UserData.ucColorTemp = CLRTMP_11500K;
 //       UserSetColorTemp();
 //   }
//    else if(ucFactoryIndex == mfADDRESS){
 //       UserData.ucColorTemp = CLRTMP_6500K;
 //       UserSetColorTemp();
 //   }

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
        //OSDShowFactory(); //jacky
        OSDEnterFactory();  //CHIU MOVE TO SAME POSITION
        OSDDnFactory();
        //FactoryShowAutoColor(auto_color);
        return;
    }
    else if(ucFactoryIndex == mfRESET){
        NvramInitialize(NVRAM_UPDATE_ALL);
        NvramLoadData();
        OSDAPI_TurnOffOSD();
        UserRecallConfiguration();      
        //OSDShowFactory(); //jacky
        OSDEnterFactory();  //jacky
        SetFactUpdFlag();
        NvramWriteCalibData(&CalibData);	//CHIU SAVE DATA EVERY VALUE CHANGE
        return;
    }
    else if(ucFactoryIndex == mfRETURN)
    {
    	//CHIU SET 6500 AS DEFAULT
        UserData.ucColorTemp = CLRTMP_6500K;
        UserSetColorTemp();
        SystemData.bFactory = FALSE;
        NvramWriteSystemData(&SystemData);  //jacky         
        
        //UserData.ucColorTemp = CLRTMP_6500K; //FEFANJACKY
        //UserSetColorTemp(); //FEFANJACKY     
        OSDCloseAll();  //jacky
        OSDEnterMainMenu(); //fefanjacky add for factory into user mode
        //DPHPDOff();  //jacky add for factory to user mode not into dp mode  ; // not add for windows xp
        return;   
    }
    else 
    {
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
//        case mfBURNING:
//            SystemData.bBurnIn = ~SystemData.bBurnIn;
//            FactoryShowBurnin();
//            break;
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
/*
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
*/            
         //CHIU
        case mfGAMMA:        	
        	if(CalibData.ucGammaVal < GAMMA_TOTAL_STEP - 1)		//CHECK MAX GAMMA
            {
            	CalibData.ucGammaVal++;
            }
                        
            //OSDAPI_ShowIndentString(FALSE, LBar[mfGAMMA].x+ucGammaText[0]+1, LBar[mfGAMMA].y,1,*(ucGammaTextTable + (USHRT)(CalibData.ucGammaVal) )); 
            //FactoryShowValue(mfGAMMA, (USHRT)CalibData.ucGammaVal);  
            ShowGammaValue();            
            break;
        case mfBACKLIGHT:
            FactoryValueUp(&CalibData.ucBacklite);
            FactoryShowValue(mfBACKLIGHT, (USHRT)CalibData.ucBacklite);
            break;
/*
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
*/
/*
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
*/
//        case mfADDRESS:
//            FactoryShowValue(mfADDRESS, (USHRT)usRegAddr);
//            break;
//        case mfWR:
//            FactoryShowValue(mfWR, (USHRT)ucRegValue);
//            break;
    }
    FactorySetValue();
    
    NvramWriteCalibData(&CalibData);	//CHIU SAVE DATA EVERY VALUE CHANGE
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
/*
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
*/            
        //CHIU
        case mfGAMMA:
        	if(CalibData.ucGammaVal > 0)	//CHECK MIN GAMMA
            {
            	CalibData.ucGammaVal--;
            }        
            
            //OSDAPI_ShowIndentString(FALSE, LBar[mfGAMMA].x+ucGammaText[0]+1, LBar[mfGAMMA].y,1,*(ucGammaTextTable +  (USHRT)(CalibData.ucGammaVal) ));     
            ShowGammaValue();
            
            break;
        case mfBACKLIGHT:
            FactoryValueDown(&CalibData.ucBacklite);
            FactoryShowValue(mfBACKLIGHT, (USHRT)CalibData.ucBacklite);
            break;
            
            
/*
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
*/
/*
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
*/
//        case mfADDRESS:
//            FactoryShowValue(mfADDRESS, (USHRT)usRegAddr);
//            break;
//        case mfWR:
//            FactoryShowValue(mfWR, (USHRT)ucRegValue);
//            break;
    }
    FactorySetValue();
    
    NvramWriteCalibData(&CalibData);	//CHIU SAVE DATA EVERY VALUE CHANGE
}


void FactorySelect(void)
{
    OSDAPI_FillLineAttr(LBar[ucFactoryIndex].x, LBar[ucFactoryIndex].y, LBar[ucFactoryIndex].len,FACTORY_ITEM_COLOR);
}

void FactoryUnSelect(void)
{
    OSDAPI_FillLineAttr(LBar[ucFactoryIndex].x, LBar[ucFactoryIndex].y, LBar[ucFactoryIndex].len, FACTORY_FRAME_COLOR);
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
*/

    else if ( ucFactoryIndex == mfGAMMA ) {
        OSDAPI_FillLineAttr(6,
                            1,
                            3, FACTORY_ITEM_COLOR);
    }

    else {
        OSDAPI_FillLineAttr(LBar[ucFactoryIndex].x+LBar[ucFactoryIndex].len,
                            LBar[ucFactoryIndex].y,
                            4, FACTORY_ITEM_COLOR);
    }
}

void FactoryUnSelectValue(void)
{
    if ((ucFactoryIndex >= mfGAINR) && (ucFactoryIndex <= mf6500B)) {
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
*/
/*
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
    else if(index >= mf6500R &&  index <= mf9300B){
        OSDShowNum(LBar[index].x+1, LBar[index].y, value);
    }
//    else if(index == mfADDRESS){
//        OSDShowNum(LBar[index].x+LBar[index].len+2, LBar[index].y, (UCHAR)(value>>8));
//        OSDShowNum(LBar[index].x+LBar[index].len, LBar[index].y, value);
//    }
//    else if(index == mfWR){
//        OSDShowNum(LBar[index].x-5, LBar[index].y, value);
//    }
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

/*
void FactoryShowAutoColor(UCHAR result)
{
    //OSDAPI_SetIndentIndex(0xF0);
    OSDAPI_SetIndentIndex(128);
    OSDAPI_SetAlignType(OSD_ALIGN_LEFT);

    if (result == 1)
        OSDAPI_ShowIndentString(FALSE, LBar[mfAUTO].x+8, LBar[mfAUTO].y, 3, ucOkText);
    else
        OSDAPI_ShowIndentString(FALSE, LBar[mfAUTO].x+8, LBar[mfAUTO].y, 3, ucNoText);
}
*/

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
/*
        case mfSRGBR:
        case mfSRGBG:
        case mfSRGBB:
        case mf8200R:
        case mf8200G:
        case mf8200B:
        case mf9300R:
        case mf9300G:
        case mf9300B:
        case mf11500R:
        case mf11500G:
        case mf11500B:
*/
            UserSetColorTemp();
            SetFactUpdFlag();
            break;

       case mfGAMMA:
       		LoadGamma();
           break;
       case mfBACKLIGHT:
       		//CalibData.ucBacklite = CalibData.ucBacklite ? 0 : 226;
       		SYSAPI_SetInverterVal(CalibData.ucBacklite);          		    		
           break;

    }
}
