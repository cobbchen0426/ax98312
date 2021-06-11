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
// G L O B A L   D E F I N I T I O N S
//******************************************************************************
enum {
    OSD_SUBMENU_1,
    OSD_SUBMENU_2,
    OSD_SUBMENU_3,
    OSD_SUBMENU_4,
    OSD_SUBMENU_5,
    OSD_SUBMENU_6,
    OSD_SUBMENU_7,
    OSD_MAIN_ITEMS,
    OSD_DLG_BRIGHTNESS,
    OSD_DLG_CONTRAST,

#if ALS_EnDis == ALSMODE

#elif ALS_EnDis == ALSOffSET	//don't know used where ~
	OSD_DLG_ALS_BASE_VALUE,	 	// george: F_ALSBV_03B1
#elif ALS_EnDis == ALSRange

#else	//Normal

#endif	//#if ALS_EnDis == ENABLE

    OSD_DLG_VOLUME,
    OSD_DLG_AUTOTUNE,
    OSD_DLG_85Hz,
    OSD_DLG_OUTOFRANGE,
    OSD_DLG_NOSYNC,
    OSD_DLG_NOCABLE,
    OSD_DLG_OSDLOCK,
    OSD_DLG_SLEEP,
    OSD_DLG_NOTICE,
    OSD_DLG_BURNIN,
    OSD_BF_MENU,
    OSD_SRC_MENU,
    OSD_OFF
};

enum {
    OSD_FUNCITM_1,
    OSD_FUNCITM_2,
    OSD_FUNCITM_3,
    OSD_FUNCITM_4,
    OSD_FUNCITM_5,
    OSD_FUNCITM_6,
    OSD_FUNC_ITEMS
};

#define SPACE_CHAR          0x00
#define OSD_MAIN_WIDTH      32
#define OSD_MAIN_HEIGHT     17
#define OSD_INFO_WIDTH      25
#define OSD_INFO_HEIGHT     8
#define OSD_SRC_WIDTH       18
#define OSD_SRC_HEIGHT      12
#define OSD_BF_WIDTH        18
#define OSD_BF_HEIGHT       14
#define OSD_SUB_X           5
#define OSD_SUB_Y           6
#define OSD_SUB_WIDTH       (OSD_MAIN_WIDTH-7)
#define OSD_SUB_HEIGHT      (OSD_MAIN_HEIGHT-10)
#define OSD_FUNC_WIDTH      29
#define OSD_FUNC_HEIGHT     15

#define MAX_X               (PANEL_WIDTH - (12*OSD_INFO_WIDTH))
#define MAX_Y               100 //(PANEL_HEIGHT - (18*OSD_INFO_HEIGHT)) //FEFANJACKY
#define OSD_MOVESTEP_X      6
#define OSD_MOVESTEP_Y      6
#define MAX_ROT_X           (PANEL_WIDTH - (18*OSD_INFO_HEIGHT))
#define MAX_ROT_Y           (PANEL_HEIGHT - (12*OSD_INFO_WIDTH))
#define OSD_MOVESTEP_ROT_X  OSD_MOVESTEP_Y
#define OSD_MOVESTEP_ROT_Y  OSD_MOVESTEP_X

#define MAIN_FRAME_COLOR    (((I_WHITE-1)<<8)|(I_TCYAN<<4)|0x0002)
#define TITLE_COLOR         (((I_WHITE-1)<<8)|(I_TGREEN<<4)|0x0002)
#define SUB_FRAME_COLOR     (((I_TGREEN-1)<<8)|(I_WHITE<<4)|0x0002)
#define DISABLE_COLOR       (((I_GRAY-1)<<8)|(I_WHITE<<4)|0x0002)
#define SLIDER_COLOR        (((I_MAGENTA-1)<<8)|(I_TMAGENTA<<4)|0x0002)
#define INFO_DLG_COLOR      (((I_TGREEN-1)<<8)|(I_WHITE<<4)|0x0002)
#define SRC_MENU_COLOR      (((I_TGREEN-1)<<8)|(I_WHITE<<4)|0x0002)
#define BF_MENU_COLOR       (((I_TGREEN-1)<<8)|(I_WHITE<<4)|0x0002)
#define FUNC_FRAME_COLOR    (((I_TGREEN-1)<<8)|(I_WHITE<<4)|0x0002)
#define DEMO_SELECT_COLOR (((I_RED-1)<<8)|(I_WHITE<<4)|0x0002)
#define MainIcon16Color1    (((0x10)<<8)|(I_TCYAN<<4)|0x0c|0x0002)
#define MainIcon16Color2    (((0x20)<<8)|(I_TCYAN<<4)|0x0c|0x0002)
#define MainIcon4Color1     (((0x30)<<8)|(I_TCYAN<<4)|0x08|0x0002)
#define MainIcon4Color2     (((0x34)<<8)|(I_TCYAN<<4)|0x08|0x0002)
#define MainIcon4Color3     (((0x38)<<8)|(I_TCYAN<<4)|0x08|0x0002)
#define READONLY_COLOR        (((I_BLACK-1)<<8)|(I_TBLACK<<4)|0x0002)	//george new define

// Defines for saving data
enum {
    OSDFLAG_UPD_TMG = 0x01,
    OSDFLAG_UPD_USR = 0x02,
    OSDFLAG_UPD_CAL = 0x04,
    OSDFLAG_UPD_SYS = 0x08,
    OSDFLAG_NOSYNC = 0x10,
    OSDFLAG_SYSINIT = 0x80
};

#define IsOSDUpdTmg() ((ucOSDFlags&OSDFLAG_UPD_TMG) != 0)
#define IsOSDUpdUsr() ((ucOSDFlags&OSDFLAG_UPD_USR) != 0)
#define IsOSDUpdCal() ((ucOSDFlags&OSDFLAG_UPD_CAL) != 0)
#define IsOSDUpdSys() ((ucOSDFlags&OSDFLAG_UPD_SYS) != 0)
#define IsOSDNoSync() ((ucOSDFlags&OSDFLAG_NOSYNC) != 0)
#define IsOSDSysInit() ((ucOSDFlags&OSDFLAG_SYSINIT) != 0)

#define SetOSDUpdTmgFlag() {ucOSDFlags |= OSDFLAG_UPD_TMG;}
#define SetOSDUpdUsrFlag() {ucOSDFlags |= OSDFLAG_UPD_USR;}
#define SetOSDUpdCalFlag() {ucOSDFlags |= OSDFLAG_UPD_CAL;}
#define SetOSDUpdSysFlag() {ucOSDFlags |= OSDFLAG_UPD_SYS;}
#define SetOSDNoSyncFlag() {ucOSDFlags |= OSDFLAG_NOSYNC;}
#define SetOSDSysInitFlag() {ucOSDFlags |= OSDFLAG_SYSINIT;}

#define ClearOSDUpdTmgFlag() {ucOSDFlags &= ~OSDFLAG_UPD_TMG;}
#define ClearOSDUpdUsrFlag() {ucOSDFlags &= ~OSDFLAG_UPD_USR;}
#define ClearOSDUpdCalFlag() {ucOSDFlags &= ~OSDFLAG_UPD_CAL;}
#define ClearOSDUpdSysFlag() {ucOSDFlags &= ~OSDFLAG_UPD_SYS;}
#define ClearOSDNoSyncFlag() {ucOSDFlags &= ~OSDFLAG_NOSYNC;}
#define ClearOSDSysInitFlag() {ucOSDFlags &= ~OSDFLAG_SYSINIT;}
#define ClearOSDUpdFlag() { \
    ucOSDFlags &= ~(OSDFLAG_UPD_TMG | OSDFLAG_UPD_USR | OSDFLAG_UPD_CAL | OSDFLAG_UPD_SYS); \
}
#define ClearOSDAllFlag() {ucOSDFlags = 0x00;}


#define OSDCharAndNumToIndex(arg) arg		//150813 george
//******************************************************************************
// G L O B A L   V A R I A B L E S
//******************************************************************************

//******************************************************************************
// S T A T I C   V A R I A B L E S
//******************************************************************************
static code UCHAR ucSubMenuITMPosTb1[] =			
{
    5, 6,
    5, 7,
    5, 8,
	5, 9,	//george: ALSOnOff
	5,10,	//george: ALSBaseVale
//gg_old	5,11,	//george: TouchOnOff
///	5,11,	// george_Item16
///	5,12,	// george_Item17
};
static code UCHAR ucSubMenuITMPosTb2[] = 				
{
    5, 6,
    5, 7,
    5, 8,
    5, 9,
};
//=============================			// 
static code UCHAR ucSubMenuITMPosTb3[] = 		// 
{
    5, 6,
    5, 8,
    5, 9,
    5,10,
    5,11,									
};
//-------------------------------------
static code UCHAR ucSubMenuITMPosTb4[] = 		
{
    5, 6,
    5, 7,
    5, 8,
    5, 9,
};
static code UCHAR ucSubMenuITMPosTb5[] = 		
{
    5, 6,
    5, 7,
    5, 8,
    5, 9,											//   
    5,10,											//   
	5,11,	//gg_new
};
static code UCHAR* ucSubMenuITMPosTb[] = 
{
    ucSubMenuITMPosTb1,						
    ucSubMenuITMPosTb2,						//   
    ucSubMenuITMPosTb3,						//  
    ucSubMenuITMPosTb4,						//   
    ucSubMenuITMPosTb5,						//140317 mike 
};

#if ENABLE_FUNC_OSD == ON
static code UCHAR ucFuncITMPosTb[] = {
    0, 3,
    0, 5,
    0, 7,
    0, 9,
    0,11,
    0,13,
};
#endif

static xdata UCHAR ucMenuType = OSD_SUBMENU_1;
static xdata USHRT usOSDMovingX,usOSDMovingY;
static xdata UCHAR ucOSDFlags = 0x00;

static xdata UCHAR ucPerformReset = FALSE;




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
//  void OSDTurnOnOSD(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Turn on OSD
// Notes:
//  None
//******************************************************************************
void OSDTurnOnOSD(void)
{
#if ENABLE_OSD_ROTATION == ON
    if (UserData.bOSDRotation) {
        OSDAPI_RotateOSDWin(OSD_WINDOW1, OSD_POS_ROT_270);
        OSDAPI_RotateOSDWin(OSD_WINDOW2, OSD_POS_ROT_270);
        OSDAPI_RotateOSDWin(OSD_WINDOW3, OSD_POS_ROT_270);
        OSDAPI_RotateOSDWin(OSD_WINDOW4, OSD_POS_ROT_270);
        OSDAPI_RotateOSDWin(OSD_WINDOW5, OSD_POS_ROT_270);
        OSDAPI_RotateOSDWin(OSD_WINDOW6, OSD_POS_ROT_270);
        OSDAPI_RotateOSDWin(OSD_WINDOW7, OSD_POS_ROT_270);
        OSDAPI_RotateOSDWin(OSD_WINDOW8, OSD_POS_ROT_270);
        OSDAPI_Rotated_270_OSD();
        Sleep(80);
    }
    else {
        OSDAPI_RotateOSDWin(OSD_WINDOW1, OSD_POS_ROT_OFF);
        OSDAPI_RotateOSDWin(OSD_WINDOW2, OSD_POS_ROT_OFF);
        OSDAPI_RotateOSDWin(OSD_WINDOW3, OSD_POS_ROT_OFF);
        OSDAPI_RotateOSDWin(OSD_WINDOW4, OSD_POS_ROT_OFF);
        OSDAPI_RotateOSDWin(OSD_WINDOW5, OSD_POS_ROT_OFF);
        OSDAPI_RotateOSDWin(OSD_WINDOW6, OSD_POS_ROT_OFF);
        OSDAPI_RotateOSDWin(OSD_WINDOW7, OSD_POS_ROT_OFF);
        OSDAPI_RotateOSDWin(OSD_WINDOW8, OSD_POS_ROT_OFF);
        Sleep(80);
    }
#endif //ENABLE_OSD_ROTATION == ON
#if ENABLE_DBC == ON
#if ENABLE_DBC_HW_DEBOUNCE == OFF
    ClearDBCCounter();
#endif
#endif
    OSDAPI_TurnOnOSD();
}

//******************************************************************************
// Prototype:
//  void OSDShowMainMenu(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Show main page
// Notes:
//  None
//******************************************************************************

void OSDShowMainMenu(void)
{
    UCHAR i;
    OSDWinAttr attr;
    
    OSDInitialize(FALSE);
    OSDInitFrame(OSD_MAIN_WIDTH,OSD_MAIN_HEIGHT, MAIN_FRAME_COLOR);

    OSDAPI_SelOSDWin(OSD_WINDOW8);
    RST_WINATTR_ALL(attr);
    attr.ucWinClr = I_TCYAN;
    OSDAPI_SetOSDWinAttr(attr);
    OSDAPI_SetOSDWinSize(0, 0, 31, 16);
    OSDAPI_SetOSDWinGrad(0x01, 0x00, 0x02, 0x01);

    OSDAPI_SelOSDWin(OSD_WINDOW7);
    attr.ucWinClr = I_TGREEN;
    OSDAPI_SetOSDWinAttr(attr);
    OSDAPI_SetOSDWinSize(5, 2, 29, 4);
    OSDAPI_SetOSDWinGrad(0x00, 0x00, 0x02, 0x01);

    OSDAPI_SelOSDWin(OSD_WINDOW6);
    attr.ucWinClr = I_WHITE;
    OSDAPI_SetOSDWinAttr(attr);
    OSDAPI_SetOSDWinSize(5, 5, 29, 12);
    OSDAPI_SetOSDWinGrad(0x00, 0x01, 0x01, 0x01);
    
    OSDAPI_OSDWinOn(OSD_WINDOW8);
    OSDAPI_OSDWinOn(OSD_WINDOW7);
    OSDAPI_OSDWinOn(OSD_WINDOW6);

    for(i = 0; i < OSD_MAIN_ITEMS; i++)
        OSDShowMainIcon(i, TRUE);
				
    OSDClearSubmenu();
    OSDSelectMainItem(0);			// george: F_Touch_, F_ALS_
    OSDAPI_SetIndentIndex(120);
    OSDShowResolution(15,14);
	
	   
#if OSD_SHOW_VERSION == ENABLE
		OSDAPI_ShowIndentString(FALSE, 8, 15,23,OSDCharAndNumToIndex(ucVersionText));	//150813 george

#endif		

	UserSetTransparent();

    OSDTurnOnOSD();
}

//******************************************************************************
// Prototype:
//  void OSDCloseMainMenu(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Close Main Menu
// Notes:
//  None
//******************************************************************************
void OSDCloseMainMenu(void)
{
    OSDClosed();
}

//******************************************************************************
// Prototype:
//  void OSDShowMainIcon(UCHAR id, UCHAR act)
// Parameters:
//  id  : id of main icon to be displayed
//  act : indicate the item is in active state or not
// Return:
//  None
// Purpose:
//  Draw main items
// Notes:
//  None
//******************************************************************************
void OSDShowMainIcon(UCHAR id, UCHAR act)
{
    #define NFONTS_PER_MITEM    6
    #define NFONTS_PER_ROW       3
    #define NROWS_PER_MITEM     2
    
    code UCHAR ucMItemIndexTb[OSD_MAIN_ITEMS][NFONTS_PER_MITEM] = 
    {
        {0x00, 0x01, 0x02, 0x03, 0x00, 0x04},
        {0x05, 0x01, 0x06, 0x02, 0x03, 0x04},
        {0x05, 0x06, 0x07, 0x08, 0x09, 0x0A},
        {0x07, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F},
        {0x10, 0x11, 0x12, 0x13, 0x14, 0x15},
        {0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    };
    code USHRT usAnalogMItemAttrTb[OSD_MAIN_ITEMS][NFONTS_PER_MITEM] = 
   {
        {MainIcon4Color1,  MainIcon4Color1,  MainIcon4Color1,  MainIcon4Color1,  MainIcon16Color1, MainIcon4Color1 },
        {MainIcon4Color2,  MainIcon16Color1, MainIcon4Color2,  MainIcon16Color1, MainIcon16Color1, MainIcon16Color1},
        {MainIcon16Color1, MainIcon16Color1, MainIcon16Color1, MainIcon16Color1, MainIcon16Color1, MainIcon16Color1},
        {MainIcon4Color2,  MainIcon16Color1, MainIcon16Color1, MainIcon16Color1, MainIcon16Color1, MainIcon16Color1},
        {MainIcon16Color1, MainIcon16Color1, MainIcon16Color1, MainIcon16Color1, MainIcon16Color1, MainIcon16Color1},
        {0x0000,0x0000,0x0000,0x0000,0x0000,0x0000},
    };
    code USHRT usDigitalMItemAttrTb[OSD_MAIN_ITEMS][NFONTS_PER_MITEM] = 
   {
        {MainIcon4Color1,  MainIcon4Color1,  MainIcon4Color1,  MainIcon4Color1,  MainIcon16Color1, MainIcon4Color1 },
        {MainIcon4Color3,  MainIcon16Color2, MainIcon4Color3,  MainIcon16Color2, MainIcon16Color2, MainIcon16Color2},
        {MainIcon16Color1, MainIcon16Color1, MainIcon16Color1, MainIcon16Color1, MainIcon16Color1, MainIcon16Color1},
        {MainIcon4Color2,  MainIcon16Color1, MainIcon16Color1, MainIcon16Color1, MainIcon16Color1, MainIcon16Color1},
        {MainIcon16Color1, MainIcon16Color1, MainIcon16Color1, MainIcon16Color1, MainIcon16Color1, MainIcon16Color1},
        {0x0000,0x0000,0x0000,0x0000,0x0000,0x0000},
    };
    
    code UCHAR ucMItemTb[OSD_MAIN_ITEMS][2] = {
      //x   y
      { 1,  1},
      { 1,  4},
      { 1,  7},
      { 1, 10},
      { 1, 13},
      { 0,  0},
    };
    
    UCHAR i, j, fonts, x, y;
    UCHAR icon_buff[NFONTS_PER_ROW];
    USHRT attr_buff[NFONTS_PER_ROW];
    USHRT *p_attr;

    if ((id == OSD_SUBMENU_6) || (id == OSD_SUBMENU_7)) {
        return;
    }
    
    if (UserData.ucInputSource == INPUT_SC_VGA) {
        p_attr = usAnalogMItemAttrTb[id];
    } 
    else {
        p_attr = usDigitalMItemAttrTb[id];
    }
    
    x = ucMItemTb[id][0];
    y = ucMItemTb[id][1];
    
    fonts = NFONTS_PER_MITEM;
    
    if (act == TRUE) {
        for (i = 0; i < NROWS_PER_MITEM; i++) {
            for (j = 0; j < NFONTS_PER_ROW; j++) {
                icon_buff[j] = ucMItemIndexTb[id][i*NFONTS_PER_ROW+j];
                attr_buff[j] = p_attr[i*NFONTS_PER_ROW+j];
            }
            OSDAPI_FillLineAttrList(x, y+i, NFONTS_PER_ROW, attr_buff);
            OSDAPI_WriteXYString(FALSE, x, y+i, NFONTS_PER_ROW, icon_buff);
        }
    }
}

//******************************************************************************
// Prototype:
//  void OSDSelectMainItem(UCHAR id) 
// Parameters:
//  id  : current cursor position
// Return:
//  None
// Purpose:
//  Activate the selected main item
// Notes:
//  None
//******************************************************************************
void OSDSelectMainItem(UCHAR id) 
{
    static code UCHAR D[]={1,"D"};

    OSDWinAttr attr;

    if (id != OSD_SUBMENU_6) 
	{
       	OSDAPI_SelOSDWin(OSD_WINDOW1);
        	RST_WINATTR_ALL(attr);
        	attr.ucWinClr = I_TCYAN;
        	SET_WINATTR_BEVEL(attr);
        	SET_BEVEL_TYPE(attr,0);
        	SET_BEVEL_WIDTH(attr,1);
        	attr.ucRBorderClr = I_RED;
        	attr.ucLBorderClr = I_RED;
        	OSDAPI_SetOSDWinAttr(attr);
        	OSDAPI_SetOSDWinSize(1, id*3+0x01, 3, id*3+0x02);
        	OSDAPI_OSDWinOn(OSD_WINDOW1);
    }
//=====================================osd color 	
	if(id==2)
	{
           OSD_color_level=0;                                   // 
	}
//======================================	
			OSDShowSubMenu(id);			// george: ALS_4
    if (SystemData.bDemo == TRUE)
	{
#if BurnIn_Degub == ENABLE
	printf("gg_OSD_Demo\n");
#endif

		if(id == OSD_SUBMENU_7) 
		{
    	     		OSDAPI_SetIndentIndex(150);
                	OSDAPI_SetAlignType(OSD_ALIGN_LEFT);
                	OSDAPI_SetFontAttr(DEMO_SELECT_COLOR);
    	     		OSDAPI_ShowIndentString(TRUE, 0, 16, D[0], D);
		}
		else 
	   	{
    	     		OSDAPI_SetIndentIndex(150);
            		OSDAPI_SetAlignType(OSD_ALIGN_LEFT);
            		OSDAPI_SetFontAttr(MAIN_FRAME_COLOR);
    	     		OSDAPI_ShowIndentString(TRUE, 0, 16, D[0], D);
       	}
    }
    ucMenuType = id;
}

//******************************************************************************
// Prototype:
//  void OSDUnselectMainItem(UCHAR id);
// Parameters:
//  id  : current cursor position
// Return:
//  None
// Purpose:
//  unactivate the selected main item
// Notes:
//  None
//******************************************************************************
void OSDUnselectMainItem(UCHAR id)
{
    id = 0;
    OSDClearSubmenu();
    OSDAPI_OSDWinOff(OSD_WINDOW1);
}

//******************************************************************************
// Prototype:
//  void OSDShowSubMenu(UCHAR id)
// Parameters:
//  id  : main item id
// Return:
//  None
// Purpose:
//  Show sub menu 
// Notes:
//  None
//******************************************************************************
void OSDShowSubMenu(UCHAR id)								//    
{
    OSDAPI_SetIndentIndex(32);
    OSDAPI_SetAlignType(OSD_ALIGN_CENTER);
    OSDAPI_FillLineAttr(5,3,OSD_SUB_WIDTH,TITLE_COLOR);
    OSDAPI_WriteXYRepeatChar(FALSE, 5, 3, OSD_SUB_WIDTH, SPACE_CHAR);
    OSDAPI_ShowIndentString(FALSE, 5, 3, OSD_SUB_WIDTH, MainMenuStrTab[id*NUM_OSDLANGS+UserData.ucLanguage]);
    
    OSDAPI_SetIndentIndex(48);

    switch(id) 
	{
        case OSD_SUBMENU_1: 

		#if ALS_EnDis == ALSMODE
			OSDAPI_ShowIndentString(FALSE, ucSubMenuITMPosTb[id][0], ucSubMenuITMPosTb[id][1], OSD_SUB_WIDTH, BrightnessStrTab[UserData.ucLanguage]);
            OSDAPI_ShowIndentString(FALSE, ucSubMenuITMPosTb[id][2], ucSubMenuITMPosTb[id][3], OSD_SUB_WIDTH, ContrastStrTab[UserData.ucLanguage]);
			OSDAPI_ShowIndentString(FALSE, ucSubMenuITMPosTb[id][4], ucSubMenuITMPosTb[id][5], OSD_SUB_WIDTH, SRStrTab[UserData.ucLanguage]);		
			OSDAPI_ShowIndentString(FALSE, ucSubMenuITMPosTb[id][6], ucSubMenuITMPosTb[id][7], OSD_SUB_WIDTH, ALSMdStrTab[UserData.ucLanguage]); 
		#elif ALS_EnDis == ALSOffSET	
			if(UserData.bALSOnOff == OFF)
            	OSDAPI_ShowIndentString(FALSE, ucSubMenuITMPosTb[id][0], ucSubMenuITMPosTb[id][1], OSD_SUB_WIDTH, BrightnessStrTab[UserData.ucLanguage]);
			else
				OSDAPI_ShowIndentString(FALSE, ucSubMenuITMPosTb[id][0], ucSubMenuITMPosTb[id][1], OSD_SUB_WIDTH, ALSBVStrTab[UserData.ucLanguage]);	//george: F_ALSBV_04F

            OSDAPI_ShowIndentString(FALSE, ucSubMenuITMPosTb[id][2], ucSubMenuITMPosTb[id][3], OSD_SUB_WIDTH, ContrastStrTab[UserData.ucLanguage]);
			OSDAPI_ShowIndentString(FALSE, ucSubMenuITMPosTb[id][4], ucSubMenuITMPosTb[id][5], OSD_SUB_WIDTH, SRStrTab[UserData.ucLanguage]);
            OSDAPI_ShowIndentString(FALSE, ucSubMenuITMPosTb[id][6], ucSubMenuITMPosTb[id][7], OSD_SUB_WIDTH, ALSOnOffStrTab[UserData.ucLanguage]); //george: F_ALSOnOff_02		
		#elif ALS_EnDis == ALSRange
			OSDAPI_ShowIndentString(FALSE, ucSubMenuITMPosTb[id][0], ucSubMenuITMPosTb[id][1], OSD_SUB_WIDTH, BrightnessStrTab[UserData.ucLanguage]);
            OSDAPI_ShowIndentString(FALSE, ucSubMenuITMPosTb[id][2], ucSubMenuITMPosTb[id][3], OSD_SUB_WIDTH, ContrastStrTab[UserData.ucLanguage]);
			OSDAPI_ShowIndentString(FALSE, ucSubMenuITMPosTb[id][4], ucSubMenuITMPosTb[id][5], OSD_SUB_WIDTH, SRStrTab[UserData.ucLanguage]);		
			OSDAPI_ShowIndentString(FALSE, ucSubMenuITMPosTb[id][6], ucSubMenuITMPosTb[id][7], OSD_SUB_WIDTH, ALSOnOffStrTab[UserData.ucLanguage]); 
		#else	//Normal
			OSDAPI_ShowIndentString(FALSE, ucSubMenuITMPosTb[id][0], ucSubMenuITMPosTb[id][1], OSD_SUB_WIDTH, BrightnessStrTab[UserData.ucLanguage]);
            OSDAPI_ShowIndentString(FALSE, ucSubMenuITMPosTb[id][2], ucSubMenuITMPosTb[id][3], OSD_SUB_WIDTH, ContrastStrTab[UserData.ucLanguage]);
			OSDAPI_ShowIndentString(FALSE, ucSubMenuITMPosTb[id][4], ucSubMenuITMPosTb[id][5], OSD_SUB_WIDTH, SRStrTab[UserData.ucLanguage]);
		#endif	//#if ALS_EnDis == ENABLE


// old no used			OSDAPI_ShowIndentString(FALSE, ucSubMenuITMPosTb[id][8], ucSubMenuITMPosTb[id][9], OSD_SUB_WIDTH, ALSBVStrTab[UserData.ucLanguage]);	//george: F_ALSBV_02
//gg_old			OSDAPI_ShowIndentString(FALSE, ucSubMenuITMPosTb[id][8], ucSubMenuITMPosTb[id][9],OSD_SUB_WIDTH, TouchSWStrTab[UserData.ucLanguage]);	//george: F_Touch_02
/// *Delete     OSDAPI_ShowIndentString(FALSE, ucSubMenuITMPosTb[id][10], ucSubMenuITMPosTb[id][11], OSD_SUB_WIDTH, GItem16StrTab[UserData.ucLanguage]); //george_Item16
/// OSDAPI_ShowIndentString(FALSE, ucSubMenuITMPosTb[id][12], ucSubMenuITMPosTb[id][13], OSD_SUB_WIDTH, GItem17StrTab[UserData.ucLanguage]); //george_Item17
            break;
        case OSD_SUBMENU_2: 
            OSDAPI_ShowIndentString(FALSE, ucSubMenuITMPosTb[id][0], ucSubMenuITMPosTb[id][1], OSD_SUB_WIDTH, PhaseStrTab[UserData.ucLanguage]);
            OSDAPI_ShowIndentString(FALSE, ucSubMenuITMPosTb[id][2], ucSubMenuITMPosTb[id][3], OSD_SUB_WIDTH, ClockStrTab[UserData.ucLanguage]);
            OSDAPI_ShowIndentString(FALSE, ucSubMenuITMPosTb[id][4], ucSubMenuITMPosTb[id][5], OSD_SUB_WIDTH, HPosStrTab[UserData.ucLanguage]);
            OSDAPI_ShowIndentString(FALSE, ucSubMenuITMPosTb[id][6], ucSubMenuITMPosTb[id][7], OSD_SUB_WIDTH, VPosStrTab[UserData.ucLanguage]);
            break;
        case OSD_SUBMENU_3: 
	            OSDAPI_ShowIndentString(FALSE, ucSubMenuITMPosTb[id][0], ucSubMenuITMPosTb[id][1], OSD_SUB_WIDTH, ColorTempStrTab[UserData.ucLanguage]);   
			if(OSD_color_level<2)
   			{
             	 	switch(	UserData.ucColorTemp)
					{
             	    	case 0:
                			OSDAPI_FillLineAttr(ucSubMenuITMPosTb[id][2], ucSubMenuITMPosTb[id][3], OSD_SUB_WIDTH,DISABLE_COLOR);
			                break;
		     			case 1: 			 		
                			OSDAPI_FillLineAttr(ucSubMenuITMPosTb[id][4], ucSubMenuITMPosTb[id][5], OSD_SUB_WIDTH,DISABLE_COLOR);
                     		break;
		     			case 2: 			 					
                			OSDAPI_FillLineAttr(ucSubMenuITMPosTb[id][6], ucSubMenuITMPosTb[id][7], OSD_SUB_WIDTH,DISABLE_COLOR);
			                break;
		     			case 3: 			 		
                			OSDAPI_FillLineAttr(ucSubMenuITMPosTb[id][8], ucSubMenuITMPosTb[id][9], OSD_SUB_WIDTH,DISABLE_COLOR);
			                break;	
             	 	}
              OSDAPI_ShowIndentString(FALSE, ucSubMenuITMPosTb[id][2], ucSubMenuITMPosTb[id][3], OSD_SUB_WIDTH, ColorTemp_StrTab[0*NUM_OSDLANGS+UserData.ucLanguage]);
			  OSDAPI_ShowIndentString(FALSE, ucSubMenuITMPosTb[id][4], ucSubMenuITMPosTb[id][5], OSD_SUB_WIDTH, ColorTemp_StrTab[1*NUM_OSDLANGS+UserData.ucLanguage]);
			  OSDAPI_ShowIndentString(FALSE, ucSubMenuITMPosTb[id][6], ucSubMenuITMPosTb[id][7], OSD_SUB_WIDTH, ColorTemp_StrTab[2*NUM_OSDLANGS+UserData.ucLanguage]);  
			  OSDAPI_ShowIndentString(FALSE, ucSubMenuITMPosTb[id][8], ucSubMenuITMPosTb[id][9], OSD_SUB_WIDTH, ColorTemp_StrTab[3*NUM_OSDLANGS+UserData.ucLanguage]);  			
   			}

			if (OSD_color_level>=2)	 
 	     	{
				OSDAPI_ShowIndentString(FALSE, ucSubMenuITMPosTb[id][2], ucSubMenuITMPosTb[id][3], OSD_SUB_WIDTH, RedStrTab[UserData.ucLanguage]);
            	OSDAPI_ShowIndentString(FALSE, ucSubMenuITMPosTb[id][4], ucSubMenuITMPosTb[id][5], OSD_SUB_WIDTH, GreenStrTab[UserData.ucLanguage]);
            	OSDAPI_ShowIndentString(FALSE, ucSubMenuITMPosTb[id][6], ucSubMenuITMPosTb[id][7], OSD_SUB_WIDTH, BlueStrTab[UserData.ucLanguage]);		
		 	}
            break;		
        case OSD_SUBMENU_4: 
            OSDAPI_ShowIndentString(FALSE, ucSubMenuITMPosTb[id][0], ucSubMenuITMPosTb[id][1], OSD_SUB_WIDTH, HorizontalStrTab[UserData.ucLanguage]);
            OSDAPI_ShowIndentString(FALSE, ucSubMenuITMPosTb[id][2], ucSubMenuITMPosTb[id][3], OSD_SUB_WIDTH, VerticalStrTab[UserData.ucLanguage]);
            OSDAPI_ShowIndentString(FALSE, ucSubMenuITMPosTb[id][4], ucSubMenuITMPosTb[id][5], OSD_SUB_WIDTH, TransparencyStrTab[UserData.ucLanguage]);
            OSDAPI_ShowIndentString(FALSE, ucSubMenuITMPosTb[id][6], ucSubMenuITMPosTb[id][7], OSD_SUB_WIDTH, OSDTimeStrTab[UserData.ucLanguage]);
            break;
 //--------------------------------------------------------------------------------------------------------  
        case OSD_SUBMENU_5: 
			#if (BUILD_CUSTOMER == X_INP_DHP) || (BUILD_CUSTOMER == X_INP_VDH)	//X_ADS_AD907, X_ADS_AD908
					#if AUDIO_EnDis == ENABLE
				            OSDAPI_ShowIndentString(FALSE, ucSubMenuITMPosTb[id][0], ucSubMenuITMPosTb[id][1], OSD_SUB_WIDTH, LanguageStrTab[UserData.ucLanguage]);
							OSDAPI_ShowIndentString(FALSE, ucSubMenuITMPosTb[id][2], ucSubMenuITMPosTb[id][3], OSD_SUB_WIDTH, VolumeStrTab[UserData.ucLanguage]);    
							OSDAPI_ShowIndentString(FALSE, ucSubMenuITMPosTb[id][4], ucSubMenuITMPosTb[id][5], OSD_SUB_WIDTH, MuteTab[UserData.ucLanguage]);		
				            OSDAPI_ShowIndentString(FALSE, ucSubMenuITMPosTb[id][6], ucSubMenuITMPosTb[id][7], OSD_SUB_WIDTH, InputStrTab[UserData.ucLanguage]);
				            OSDAPI_ShowIndentString(FALSE, ucSubMenuITMPosTb[id][8], ucSubMenuITMPosTb[id][9], OSD_SUB_WIDTH, ResetStrTab[UserData.ucLanguage]);
		
						#if ENABLE_ASPECT_RATIO == ON		//george 20160217
							OSDAPI_ShowIndentString(FALSE, ucSubMenuITMPosTb[id][10], ucSubMenuITMPosTb[id][11], OSD_SUB_WIDTH, DisplaySizeTab[UserData.ucLanguage]);
						#endif
		
					#else	//audio_osd-item_disable
				            OSDAPI_ShowIndentString(FALSE, ucSubMenuITMPosTb[id][0], ucSubMenuITMPosTb[id][1], OSD_SUB_WIDTH, LanguageStrTab[UserData.ucLanguage]);
				            OSDAPI_ShowIndentString(FALSE, ucSubMenuITMPosTb[id][2], ucSubMenuITMPosTb[id][3], OSD_SUB_WIDTH, InputStrTab[UserData.ucLanguage]);
				            OSDAPI_ShowIndentString(FALSE, ucSubMenuITMPosTb[id][4], ucSubMenuITMPosTb[id][5], OSD_SUB_WIDTH, ResetStrTab[UserData.ucLanguage]);
		
						#if ENABLE_ASPECT_RATIO == ON		//george 20160217
							OSDAPI_ShowIndentString(FALSE, ucSubMenuITMPosTb[id][6], ucSubMenuITMPosTb[id][7], OSD_SUB_WIDTH, DisplaySizeTab[UserData.ucLanguage]);
						#endif 
		
					#endif	//#if AUDIO_EnDis == ENABLE
			#elif BUILD_CUSTOMER == X_INP_DH	//X_AXI
					#if AUDIO_EnDis == ENABLE
				            OSDAPI_ShowIndentString(FALSE, ucSubMenuITMPosTb[id][0], ucSubMenuITMPosTb[id][1], OSD_SUB_WIDTH, LanguageStrTab[UserData.ucLanguage]);
							OSDAPI_ShowIndentString(FALSE, ucSubMenuITMPosTb[id][2], ucSubMenuITMPosTb[id][3], OSD_SUB_WIDTH, VolumeStrTab[UserData.ucLanguage]);    
							OSDAPI_ShowIndentString(FALSE, ucSubMenuITMPosTb[id][4], ucSubMenuITMPosTb[id][5], OSD_SUB_WIDTH, MuteTab[UserData.ucLanguage]);		
				            OSDAPI_ShowIndentString(FALSE, ucSubMenuITMPosTb[id][6], ucSubMenuITMPosTb[id][7], OSD_SUB_WIDTH, InputStrTab[UserData.ucLanguage]);
				            OSDAPI_ShowIndentString(FALSE, ucSubMenuITMPosTb[id][8], ucSubMenuITMPosTb[id][9], OSD_SUB_WIDTH, ResetStrTab[UserData.ucLanguage]);
		
						#if TOUCH_EnDis == ENABLE
							OSDAPI_ShowIndentString(FALSE, ucSubMenuITMPosTb[id][10],ucSubMenuITMPosTb[id][11],OSD_SUB_WIDTH, TouchSWStrTab[UserData.ucLanguage]);	//george: F_Touch_02  //gg_new
						#endif //#if TOUCH_EnDis == ENABLE

						#if ENABLE_ASPECT_RATIO == ON		//george 20160217
							OSDAPI_ShowIndentString(FALSE, ucSubMenuITMPosTb[id][12], ucSubMenuITMPosTb[id][13], OSD_SUB_WIDTH, DisplaySizeTab[UserData.ucLanguage]);
						#endif		
		
					#else	//audio_osd-item_disable
				            OSDAPI_ShowIndentString(FALSE, ucSubMenuITMPosTb[id][0], ucSubMenuITMPosTb[id][1], OSD_SUB_WIDTH, LanguageStrTab[UserData.ucLanguage]);
				            OSDAPI_ShowIndentString(FALSE, ucSubMenuITMPosTb[id][2], ucSubMenuITMPosTb[id][3], OSD_SUB_WIDTH, InputStrTab[UserData.ucLanguage]);
				            OSDAPI_ShowIndentString(FALSE, ucSubMenuITMPosTb[id][4], ucSubMenuITMPosTb[id][5], OSD_SUB_WIDTH, ResetStrTab[UserData.ucLanguage]);		
		
						#if TOUCH_EnDis == ENABLE
							OSDAPI_ShowIndentString(FALSE, ucSubMenuITMPosTb[id][6],ucSubMenuITMPosTb[id][7],OSD_SUB_WIDTH, TouchSWStrTab[UserData.ucLanguage]);	//george: F_Touch_02  //gg_new
						#endif //#if TOUCH_EnDis == ENABLE

						#if ENABLE_ASPECT_RATIO == ON		//george 20160217
							OSDAPI_ShowIndentString(FALSE, ucSubMenuITMPosTb[id][8], ucSubMenuITMPosTb[id][9], OSD_SUB_WIDTH, DisplaySizeTab[UserData.ucLanguage]);
						#endif
		
					#endif	//#if AUDIO_EnDis == ENABLE
			#else

			#endif




            break;
//---------------------------------------------------------------------------------------------------------			
        case OSD_SUBMENU_6:
            break;
        case OSD_SUBMENU_7:
            break;
        default :
            break;
    }
}


//******************************************************************************
// Prototype: 
//  void OSDFocusMain(UCHAR id)
// Parameters:
//  id      : main page id
// Return:
//  None
// Purpose:
//  Focus on main page
// Notes:
//  None
//******************************************************************************
void OSDFocusMain(UCHAR id)
{
    id = 0;
    OSDAPI_OSDWinOff(OSD_WINDOW2);
}

//******************************************************************************
// Prototype: 
//  void OSDFocusSub(UCHAR id)
// Parameters:
//  id      : sub item id
// Return:
//  None
// Purpose:
//  Focus on sub item
// Notes:
//  None
//******************************************************************************
void OSDFocusSub(UCHAR id)
{
    OSDWinAttr attr;

    OSDAPI_SelOSDWin(OSD_WINDOW2);
    
    RST_WINATTR_ALL(attr);
    attr.ucWinClr = I_WHITE;
    SET_WINATTR_BEVEL(attr);
    SET_BEVEL_TYPE(attr,0);
    SET_BEVEL_WIDTH(attr,1);
    attr.ucRBorderClr = I_MAGENTA;
    attr.ucLBorderClr = I_MAGENTA;
    OSDAPI_SetOSDWinAttr(attr);
    
    OSDSelectSubItem(id);
}

//******************************************************************************
// Prototype: 
//  void OSDUnselectSubItem(UCHAR id)
// Parameters:
//  id      : sub item id
// Return:
//  None
// Purpose:
//  Unselect item
// Notes:
//  None
//******************************************************************************
void OSDUnselectSubItem(UCHAR id)
{
    id = 0;
    OSDAPI_OSDWinOff(OSD_WINDOW2);
}

//******************************************************************************
// Prototype: 
//  void OSDSelectSubItem(UCHAR id)
// Parameters:
//  id      : sub item id
// Return:
//  None
// Purpose:
//  Select item
// Notes:
//  None
//******************************************************************************
void OSDSelectSubItem(UCHAR id)
{
    UCHAR x, y;

    OSDAPI_SelOSDWin(OSD_WINDOW2);
    
    x = ucSubMenuITMPosTb[ucMenuType][id*2];
    y = ucSubMenuITMPosTb[ucMenuType][id*2+1];
    
    OSDAPI_SetOSDWinSize(x, y, 29, y);
    
    OSDAPI_OSDWinOn(OSD_WINDOW2);
}

//******************************************************************************
// Prototype: 
//  void OSDExitItms(UCHAR pg, UCHAR itm)
// Parameters:
//  pg      : main page id
//  itm     : sub item id
// Return:
//  None
// Purpose:
//  Exit item state and go back to sub page state
// Notes:
//  None
//******************************************************************************
void OSDExitItms(UCHAR pg, UCHAR itm)
{
    OSDClearSubmenu();
    OSDShowSubMenu(pg);
    OSDSelectSubItem(itm);

    if ((pg == OSD_SUBMENU_4) && (itm == 5))					
	{
       	 OSDTurnOnOSD();
	}
}

//******************************************************************************
// Prototype:
//  BOOL OSDIsMainItemValid(UCHAR id)
// Parameters:
//  id      : OSD cursor position on man page
// Return:
//  Check current position is valid or not
// Purpose:
//  Check OSD cursor can move to "id" or not
// Notes:
//  None
//******************************************************************************
BOOL OSDIsMainItemValid(UCHAR id)
{
    if (id == OSD_SUBMENU_6) 
	{
        if (SystemData.bFactory == FALSE) 
		{
        	return FALSE;
        }
    }
    else if (id == OSD_SUBMENU_7) 
	{
    	if (SystemData.bDemo == FALSE) 
		{
        	return FALSE;
        }    
   	}
    else if (id == OSD_SUBMENU_2) 
	{
    	if (GetInputSyncMode() == DIG_SYNC) 
	 	{
        	return FALSE;
        }
   	}

    return TRUE;
}

//******************************************************************************
// Prototype:
//  BOOL OSDIsSubItemValid(UCHAR id)
// Parameters:
//  id      : OSD cursor position on sub page
// Return:
//  Check current position is valid or not
// Purpose:
//  Check OSD cursor can move to "id" or not
// Notes:
//  None
//******************************************************************************
BOOL OSDIsSubItemValid(UCHAR id)
{
    if (ucMenuType == OSD_SUBMENU_3) 
	{
		if ((UserData.ucColorTemp != CLRTMP_USER) && (id > 0)) 				
	    {
              return FALSE;
		}
		if((OSD_color_level !=2)&&(UserData.ucColorTemp==CLRTMP_USER)&& (id > 0))
	    {
              return FALSE;
		}		   	

	}
    return TRUE;
}

#if ENABLE_FUNC_OSD == ON
void OSDShowFuncMenu(void)
{
    OSDWinAttr attr;
    
    OSDInitialize(FALSE);
    OSDInitFrame(OSD_FUNC_WIDTH,OSD_FUNC_HEIGHT, FUNC_FRAME_COLOR);

    RST_WINATTR_ALL(attr);
    
    OSDAPI_SelOSDWin(OSD_WINDOW8);
    attr.ucWinClr = I_TGREEN;
    OSDAPI_SetOSDWinAttr(attr);
    OSDAPI_SetOSDWinSize(0, 0, OSD_FUNC_WIDTH, 4);
    OSDAPI_SetOSDWinGrad(0x00, 0x00, 0x02, 0x01);

    OSDAPI_SelOSDWin(OSD_WINDOW7);
    attr.ucWinClr = I_WHITE;
    OSDAPI_SetOSDWinAttr(attr);
    OSDAPI_SetOSDWinSize(0, 3, OSD_FUNC_WIDTH, OSD_FUNC_HEIGHT);
    OSDAPI_SetOSDWinGrad(0x00, 0x01, 0x01, 0x01);
    
    OSDAPI_OSDWinOn(OSD_WINDOW8);
    OSDAPI_OSDWinOn(OSD_WINDOW7);

    OSDAPI_SetIndentIndex(32);
    OSDAPI_SetAlignType(OSD_ALIGN_CENTER);
    OSDAPI_FillLineAttr(0, 1, OSD_FUNC_WIDTH, TITLE_COLOR);
    OSDAPI_WriteXYRepeatChar(FALSE, 0, 1, OSD_FUNC_WIDTH, SPACE_CHAR);
    OSDAPI_ShowIndentString(FALSE, 0, 1, OSD_FUNC_WIDTH, ThrDCtrlTab[UserData.ucLanguage]);

    OSDShowFuncItems();
    UserSetTransparent();

    OSDTurnOnOSD();    
}

void OSDCloseFuncMenu(void)
{
    OSDClosed();
}

void OSDClearFuncMenu(void)
{
    UCHAR i;
    OSDAPI_OSDWinOff(OSD_WINDOW2);
    for (i = 3; i < OSD_FUNC_HEIGHT; i++) {
        OSDAPI_WriteXYRepeatChar(FALSE, 0, i, OSD_FUNC_WIDTH, SPACE_CHAR);
        OSDAPI_FillLineAttr(0, i, OSD_FUNC_WIDTH, FUNC_FRAME_COLOR);
    }
}

void OSDFocusFuncMenu(UCHAR id)
{
    OSDClearFuncMenu();
    OSDShowFuncItems();
    OSDSelectFuncItem(id);
}

void OSDShowFuncItems(void)
{
    UCHAR i;
    
    OSDAPI_SetAlignType(OSD_ALIGN_CENTER);
    OSDAPI_SetIndentIndex(48);
    
    for (i = 0; i < OSD_FUNC_ITEMS; i++) {
        if (OSDIsFuncItemValid(i)) {
            OSDAPI_FillLineAttr(ucFuncITMPosTb[2 * i], ucFuncITMPosTb[2 * i + 1], OSD_FUNC_WIDTH, FUNC_FRAME_COLOR);
        }
        else {
            OSDAPI_FillLineAttr(ucFuncITMPosTb[2 * i], ucFuncITMPosTb[2 * i + 1], OSD_FUNC_WIDTH, DISABLE_COLOR);
        }
    }
    OSDAPI_ShowIndentString(FALSE, ucFuncITMPosTb[0], ucFuncITMPosTb[1], OSD_FUNC_WIDTH, ThrDCnvTab[UserData.ucLanguage]);
    OSDAPI_ShowIndentString(FALSE, ucFuncITMPosTb[2], ucFuncITMPosTb[3], OSD_FUNC_WIDTH, ThrDAdpTab[UserData.ucLanguage]);
    OSDAPI_ShowIndentString(FALSE, ucFuncITMPosTb[4], ucFuncITMPosTb[5], OSD_FUNC_WIDTH, ThrDDphTab[UserData.ucLanguage]);
    OSDAPI_ShowIndentString(FALSE, ucFuncITMPosTb[6], ucFuncITMPosTb[7], OSD_FUNC_WIDTH, ThrDVwTab[UserData.ucLanguage]);
    OSDAPI_ShowIndentString(FALSE, ucFuncITMPosTb[8], ucFuncITMPosTb[9], OSD_FUNC_WIDTH, ThrDLRTab[UserData.ucLanguage]);
    OSDAPI_ShowIndentString(FALSE, ucFuncITMPosTb[10], ucFuncITMPosTb[11], OSD_FUNC_WIDTH, ThrDTwoDTab[UserData.ucLanguage]);
}

void OSDSelectFuncItem(UCHAR id)
{
    OSDWinAttr attr;
    UCHAR x, y;

    OSDAPI_SelOSDWin(OSD_WINDOW2);

    RST_WINATTR_ALL(attr);
    attr.ucWinClr = I_WHITE;
    SET_WINATTR_BEVEL(attr);
    SET_BEVEL_TYPE(attr,0);
    SET_BEVEL_WIDTH(attr,1);
    attr.ucRBorderClr = I_MAGENTA;
    attr.ucLBorderClr = I_MAGENTA;
    OSDAPI_SetOSDWinAttr(attr);
    
    x = ucFuncITMPosTb[id*2];
    y = ucFuncITMPosTb[id*2+1];
    
    OSDAPI_SetOSDWinSize(x, y, OSD_FUNC_WIDTH, y);
    
    OSDAPI_OSDWinOn(OSD_WINDOW2);
}

void OSDUnselectFuncItem(UCHAR id)
{
    id = 0;
    OSDAPI_OSDWinOff(OSD_WINDOW2);
}

BOOL OSDIsFuncItemValid(UCHAR id)
{
#if (ENABLE_SCALER_3D == ON) && (ENABLE_3D_CNV == ON)
    if (SC3DAPI_IsHDMI3D() || SC3DAPI_IsAMD3D()) {
        if ((id != OSD_FUNCITM_5) && (id != OSD_FUNCITM_6)) {
            return FALSE;
        }
    }
    else if (SC3DAPI_Is2DTo3D()) {
        return TRUE;
    }
    else if (SC3DAPI_IsDisplay3D()) {
        if ((id == OSD_FUNCITM_2) || (id == OSD_FUNCITM_3) || (id == OSD_FUNCITM_4)) {
            return FALSE;
        }
    }
    else {
        if (id != OSD_FUNCITM_1) {
            return FALSE;
        }
    }
#else
    id = 0;
#endif    
    return TRUE;
}
#endif
//******************************************************************************
// Prototype: 
//  BOOL OSDUserUpdate(void)
// Parameters:
//  None
// Return:
//  return TRUE or FALSE to indicate data should be updated or not
// Purpose:
//  Check user data need to be updated or not
// Notes:
//  None
//******************************************************************************
BOOL OSDUserUpdate(void)
{
    BOOL tmp = IsOSDUpdUsr();
    ClearOSDUpdUsrFlag();
    return tmp;
}

//******************************************************************************
// Prototype: 
//  BOOL OSDTmgUpdate(void)
// Parameters:
//  None
// Return:
//  return TRUE or FALSE to indicate data should be updated or not
// Purpose:
//  Check timing data need to be updated or not
// Notes:
//  None
//******************************************************************************
BOOL OSDTmgUpdate(void)
{
    BOOL tmp = IsOSDUpdTmg();
    ClearOSDUpdTmgFlag();
    return tmp;
}

//******************************************************************************
// Prototype: 
//  BOOL OSDSysUpdate(void)
// Parameters:
//  None
// Return:
//  return TRUE or FALSE to indicate data should be updated or not
// Purpose:
//  Check system data need to be updated or not
// Notes:
//  None
//******************************************************************************
BOOL OSDSysUpdate(void)
{
    BOOL tmp = IsOSDUpdSys();
    ClearOSDUpdSysFlag();
    return tmp;
}

//******************************************************************************
// Prototype: 
//  BOOL OSDCalUpdate(void)
// Parameters:
//  None
// Return:
//  return TRUE or FALSE to indicate data should be updated or not
// Purpose:
//  Check cal data need to be updated or not
// Notes:
//  None
//******************************************************************************
BOOL OSDCalUpdate(void)
{
    BOOL tmp = IsOSDUpdCal();
    ClearOSDUpdCalFlag();
    return tmp;
}

//******************************************************************************
// Prototype:
//  void OSDClosed(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Close OSD & do something necessary
// Notes:
//  None
//******************************************************************************
void OSDClosed(void)
{
//printf("OSDClosed_S\n");	//150526 george
#if ENABLE_DBC == ON
#if ENABLE_DBC_HW_DEBOUNCE == OFF
    ClearDBCCounter();
#endif
#endif
    OSDAPI_TurnOffOSD();
    OSDAPI_OSDWinOff(OSD_WIN_OFF);
    ucMenuType = OSD_OFF;
//printf("OSDClosed_E\n");	//150526 george
}

//******************************************************************************
// Prototype:
//  void OSDInitialize(BOOL bForceInit)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Initial OSD Font & Palette
// Notes:
//  None
//******************************************************************************
void OSDInitialize(BOOL bForceInit)
{
    if (!IsOSDSysInit() || bForceInit) 
	{
       	SetOSDSysInitFlag();
        	OSDAPI_SetFontSize(OSD_FONT_12X18);
        	OSDAPI_SetOSDWinSizeUnit(12,18);
        	OSDAPI_LoadPalette(&ucOSDPalette);
        
        //frame size = w:32 h:17
        //one bit size = (188)x18/2 = 1692
        //two bit size = 8*18 = 144
        //four bit size= 22*18*2=792
    #if ENABLE_OSD_ROTATION == ON
        	OSDAPI_Set1BitFontAddr(OSDSRAM_ADDR_CEILING(OSDAPI_GetOSDFrameSize(32, 17)));
        	OSDAPI_Set2BitsFontAddr(OSDSRAM_ADDR_FLOOR(OSD_ROT_RAM_SIZE - 792 - 144));
        	OSDAPI_Set4BitsFontAddr(OSDSRAM_ADDR_FLOOR(OSD_ROT_RAM_SIZE - 792));
    #else
        	OSDAPI_Set1BitFontAddr(OSDAPI_GetOSDFrameSize(32, 17));
        	OSDAPI_Set2BitsFontAddr(OSD_RAM_SIZE - 792 - 144);
        	OSDAPI_Set4BitsFontAddr(OSD_RAM_SIZE - 792);
    #endif
        	OSDAPI_LoadFont(OSD_FONT_NORMAL, &ucOneBitFontTable);
        	OSDAPI_LoadFont(OSD_FONT_NORMAL, &ucTwoBitsFontTable);
        	OSDAPI_LoadFont(OSD_FONT_NORMAL, &ucFourBitsFontTable);
        	OSDAPI_SetIndentFont(usArialFontTable, ucArialWidthTable);
        	OSDAPI_SetOSDFadeInOut(0, 0, 0, 0, OSD_FADE_LEFT_BOT);
	}
}

//******************************************************************************
// Prototype:
//  void OSDInitFrame(UCHAR osdw, UCHAR osdh, USHRT clr)
// Parameters:
//  osdw    : OSD width
//  osdh    : OSD height
//  clr     : OSD color
// Return:
//  None
// Purpose:
//  Initial OSD width, height andf color
// Notes:
//  None
//******************************************************************************
void OSDInitFrame(UCHAR osdw, UCHAR osdh, USHRT clr)
{
    OSDAPI_TurnOffOSD();
    OSDAPI_OSDWinOff(OSD_WIN_OFF);
    OSDAPI_SetOSDWidth(osdw);
    OSDAPI_SetOSDHeight(osdh);
    OSDAPI_SetPosition(UserData.ucOSDX,UserData.ucOSDY);
    OSDAPI_SetFontAttr(clr);
    OSDAPI_ClearOSD();
}

//******************************************************************************
// Prototype:
//  void OSDClearSubmenu(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Clear sub menu
// Notes:
//  None
//******************************************************************************
void OSDClearSubmenu(void)
{
    UCHAR i;
    OSDAPI_OSDWinOff(OSD_WINDOW2);
    for (i = 0; i < OSD_SUB_HEIGHT; i++) {
        OSDAPI_WriteXYRepeatChar(FALSE, OSD_SUB_X,OSD_SUB_Y+i,OSD_SUB_WIDTH,SPACE_CHAR);
        OSDAPI_FillLineAttr(OSD_SUB_X,OSD_SUB_Y+i,OSD_SUB_WIDTH,SUB_FRAME_COLOR);
    }
}

//******************************************************************************
// Prototype: 
//  void OSDShowNum(UCHAR x, UCHAR y, UCHAR value)
// Parameters:
//  x       : x position
//  y       : y position
//  value   : value to be show
// Return:
//  None
// Purpose:
//  Show number on the specific position x,y
// Notes:
//  None
//******************************************************************************
void OSDShowNum(UCHAR x, UCHAR y, UCHAR value)
{
    UCHAR i;
    UCHAR buff[4];

    sprintf(buff,"%3d",(USHRT)value);

    for(i=0; i<3; i++){
        if(buff[i] == 0x20)
            buff[i] = 0;
        else
            buff[i] = buff[i] - 0x28;
    }
    
    OSDAPI_WriteXYString(FALSE, x, y, 3, buff);
}

//******************************************************************************
// Prototype: 
//  void OSDShowSliderBar(UCHAR x, UCHAR y, UCHAR value)
// Parameters:
//  x       : x position
//  y       : y position
//  value   : value to be show
// Return:
//  None
// Purpose:
//  Show slider bar on the specific position x,y
// Notes:
//  None
//******************************************************************************
void OSDShowSliderBar(UCHAR x, UCHAR y, UCHAR value)
{
    #define SLIDE_BAR_WIDTH     15
    #define SLIDE_VALUE_RANGE   100
    #define SLIDE_REMAINDER     (SLIDE_VALUE_RANGE/5)

    UCHAR i, k;
    USHRT m;

	
#if ALS_EnDis == ALSMODE	/* Modify Bar_Color for readyOnly */	  //OSD_state=usOSDState = OSD_DIRECT_1_STATE;  and  //OSD_state=usOSDState = OSD_ITEM_1_1_STATE;
	if( (UserData.ucALSMode==INDOOR || UserData.ucALSMode==OUTDOOR) && (OSD_state==OSD_ITEM_1_1_STATE || OSD_state==OSD_DIRECT_1_STATE) )	
		OSDAPI_SetFontAttr(READONLY_COLOR);	//(2)_READONLY_COLOR (when at OSDFocusBr() )
	else  		//ALS_OFF )	
		OSDAPI_SetFontAttr(SLIDER_COLOR);	//(1)_Normal

#elif ALS_EnDis == ALSOffSET	
	if( (UserData.bALSOnOff== ON)  && (OSD_state==OSD_ITEM_1_1_STATE || OSD_state==OSD_DIRECT_1_STATE) ) {
		if( x==10 && y==8+3 )
			OSDAPI_SetFontAttr(READONLY_COLOR);	//READONLY_COLOR 
		else
			OSDAPI_SetFontAttr(SLIDER_COLOR);	//Normal
	}else {
		OSDAPI_SetFontAttr(SLIDER_COLOR);	//Normal
	}

#elif ALS_EnDis == ALSRange
	if( (UserData.bALSOnOff== ON) && (OSD_state==OSD_ITEM_1_1_STATE || OSD_state==OSD_DIRECT_1_STATE) )	
		OSDAPI_SetFontAttr(READONLY_COLOR);	//(2)_READONLY_COLOR (when at OSDFocusBr() )
	else  		//ALS_OFF )	
		OSDAPI_SetFontAttr(SLIDER_COLOR);	//(1)_Normal

#else	//Normal
	OSDAPI_SetFontAttr(SLIDER_COLOR);	//Normal
#endif	//#if ALS_EnDis == ENABLE


    // Avoid input value is over SLIDE_VALUE_RANGE
    if (value > SLIDE_VALUE_RANGE) {
        value = SLIDE_VALUE_RANGE;
    }

    m = (USHRT) y * OSDAPI_GetOSDWidth() + x;
    OSDAPI_InitSeqWriteCodeFCAttr(m);

    OSDAPI_SeqWriteCodeFCAttr(0x01);
    m = value * SLIDE_BAR_WIDTH;
    k = m / SLIDE_VALUE_RANGE;
    for (i = 0; i < k; i++) {
        OSDAPI_SeqWriteCodeFCAttr(0x06);
    }
    if (i < SLIDE_BAR_WIDTH) {
        k = (m % SLIDE_VALUE_RANGE) / SLIDE_REMAINDER;
        switch (k) {
            case 0:
                OSDAPI_SeqWriteCodeFCAttr(0x02);
                break;
            case 1:
                OSDAPI_SeqWriteCodeFCAttr(0x03);
                break;
            case 2:
                OSDAPI_SeqWriteCodeFCAttr(0x04);
                break;
            case 3:
                OSDAPI_SeqWriteCodeFCAttr(0x05);
                break;
            case 4:
                OSDAPI_SeqWriteCodeFCAttr(0x06);
                break;
        }
        i++;
        for (i; i < SLIDE_BAR_WIDTH; i++) {
            OSDAPI_SeqWriteCodeFCAttr(0x02);
        }
    }
    OSDAPI_SeqWriteCodeFCAttr(0x07);
}

//******************************************************************************
// Prototype: 
//  void OSDShowDialog(UCHAR dlg)
// Parameters:
//  dlg     : information type
// Return:
//  None
// Purpose:
//  Show information OSD
// Notes:
//  None
//******************************************************************************
void OSDShowDialog(UCHAR dlg)
{

    OSDWinAttr attr;

    OSDInitialize(FALSE);
    OSDInitFrame(OSD_INFO_WIDTH, OSD_INFO_HEIGHT, INFO_DLG_COLOR);
    if (dlg == OSD_DLG_NOTICE) 
	{
       	 OSDAPI_SetPosition(99,100);	//george 99,98);
		 //OSDAPI_SetPosition(99,96);	//george 99,98);
    }
    else 
	{	
		#if  SET_SHOW_OSD_POSITION == SET_OSD_LEFT_TOP
			OSDAPI_SetPosition(50,100);	//george 50,98); //(50,50);  FEFANJACKY
		#elif SET_SHOW_OSD_POSITION == SET_OSD_CENTER_TOP
			OSDAPI_SetPosition(50,88);	//george 50,98); //(50,50);  FEFANJACKY
		#else		//(Normal)
			OSDAPI_SetPosition(50,100);	//george 50,98); //(50,50);  FEFANJACKY
		#endif			
    }
    OSDAPI_FillLineAttr(0,0,OSD_INFO_WIDTH, TITLE_COLOR);
    OSDAPI_FillLineAttr(0,1,OSD_INFO_WIDTH, TITLE_COLOR);
    OSDAPI_FillLineAttr(0,2,OSD_INFO_WIDTH, TITLE_COLOR);

    OSDAPI_SelOSDWin(OSD_WINDOW7);
    RST_WINATTR_ALL(attr);
    attr.ucWinClr = I_TGREEN;
    OSDAPI_SetOSDWinAttr(attr);
    OSDAPI_SetOSDWinSize(0, 0, OSD_INFO_WIDTH-1, 2);
    OSDAPI_SetOSDWinGrad(0x00, 0x00, 0x02, 0x01);

    OSDAPI_SelOSDWin(OSD_WINDOW6);
    attr.ucWinClr = I_WHITE;
    OSDAPI_SetOSDWinAttr(attr);
    OSDAPI_SetOSDWinSize(0, 3, OSD_INFO_WIDTH-1, OSD_INFO_HEIGHT);
    OSDAPI_SetOSDWinGrad(0x00, 0x01, 0x01, 0x01);

    OSDAPI_OSDWinOn(OSD_WINDOW7);
    OSDAPI_OSDWinOn(OSD_WINDOW6);

    OSDAPI_SetIndentIndex(32);
    OSDAPI_SetAlignType(OSD_ALIGN_CENTER);

    ucMenuType = dlg;
    switch(dlg) {
        case OSD_DLG_BRIGHTNESS:
	            OSDAPI_ShowIndentString(FALSE, 0, 1, OSD_INFO_WIDTH, 
	                                    BrightnessStrTab[UserData.ucLanguage]);
				
			#if ALS_EnDis == ALSMODE
				//	OSDShowSliderBar(5,5, UserData.ucBrightness);
			       // OSDShowNum(11,6, UserData.ucBrightness);								
				if(UserData.ucALSMode== ALS_OFF){

				        OSDShowSliderBar(5, 5, UserData.ucBrightness);
				        OSDShowNum(11,6, UserData.ucBrightness);
				}else{
				        OSDShowSliderBar(5, 5, NowAlsBright);
				        OSDShowNum(11,6, NowAlsBright);
				}

			#elif ALS_EnDis == ALSOffSET	
				if( UserData.bALSOnOff == OFF )			//george: add_condition to run "UserData.ucBrightness"
				{
		            OSDShowSliderBar(5,5, UserData.ucBrightness);
		            OSDShowNum(11,6, UserData.ucBrightness);
	
				}else{									//george: F_ALSBV_04F,  ALS to run "ucALSOnSetBrigVal"
	//	            OSDShowSliderBar(5,5, UserData.ucALSBaseVal);		//ucALSOnSetBrigVal);
	//	            OSDShowNum(11,6, UserData.ucALSBaseVal);			//ucALSOnSetBrigVal);
				}
							
			#elif ALS_EnDis == ALSRange
				if(UserData.bALSOnOff== OFF){

				        OSDShowSliderBar(5, 5, UserData.ucBrightness);
				        OSDShowNum(11,6, UserData.ucBrightness);
				}else{
				        OSDShowSliderBar(5, 5, NowAlsBright);
				        OSDShowNum(11,6, NowAlsBright);
				}

			#else	//Normal
				OSDShowSliderBar(5,5, UserData.ucBrightness);
		        OSDShowNum(11,6, UserData.ucBrightness);						
			#endif	//#if ALS_EnDis == ENABLE

            break;
        case OSD_DLG_CONTRAST  :
            OSDAPI_ShowIndentString(FALSE, 0, 1, OSD_INFO_WIDTH, 
                                    ContrastStrTab[UserData.ucLanguage]);
            OSDShowSliderBar(5,5, UserData.ucContrast);
            OSDShowNum(11,6, UserData.ucContrast);
            break;
        case OSD_DLG_VOLUME    :
            OSDAPI_ShowIndentString(FALSE, 0, 1, OSD_INFO_WIDTH, 
                                    VolumeStrTab[UserData.ucLanguage]);
            OSDShowSliderBar(5,5, UserData.ucVolume);
            OSDShowNum(11,6, UserData.ucVolume);
            break;
        case OSD_DLG_AUTOTUNE  :
            OSDAPI_ShowIndentString(FALSE, 0, 1, OSD_INFO_WIDTH, 
                                    AutoStrTab[UserData.ucLanguage]);
            OSDAPI_ShowIndentString(FALSE, 0, 5, OSD_INFO_WIDTH, 
                                    WaitStrTab[UserData.ucLanguage]);
            break;
        case OSD_DLG_85Hz :
            OSDAPI_ShowIndentString(FALSE, 0, 1, OSD_INFO_WIDTH, 
                                    AttentionStrTab[UserData.ucLanguage]);
            OSDAPI_ShowIndentString(FALSE, 0, 5, OSD_INFO_WIDTH, 
                                    OutOfRange85HzStrTab[UserData.ucLanguage]);
            break;
        case OSD_DLG_OUTOFRANGE:
            OSDAPI_ShowIndentString(FALSE, 0, 1, OSD_INFO_WIDTH, 
                                    AttentionStrTab[UserData.ucLanguage]);
            OSDAPI_ShowIndentString(FALSE, 0, 5, OSD_INFO_WIDTH, 
                                    OutOfRangeOverStrTab[UserData.ucLanguage]);
            break;
        case OSD_DLG_NOSYNC    :
            OSDAPI_ShowIndentString(FALSE, 0, 1, OSD_INFO_WIDTH, 
                                    AttentionStrTab[UserData.ucLanguage]);
            OSDAPI_ShowIndentString(FALSE, 0, 5, OSD_INFO_WIDTH, 
                                    NoVideoStrTab[UserData.ucLanguage]);
            break;
        case OSD_DLG_NOCABLE   :
        	
//            OSDAPI_ShowIndentString(FALSE, 0, 1, OSD_INFO_WIDTH, 
//                                    AttentionStrTab[UserData.ucLanguage]);
//            OSDAPI_ShowIndentString(FALSE, 0, 4, OSD_INFO_WIDTH, 
//                                    DisconnectedStrTab[UserData.ucLanguage]);  

#if BurnIn_Degub == ENABLE
	printf("CC-2\n");
#endif

			//CHIU        	
        	{
        	  code UCHAR time_str[] = {12,"HOUR:MIN:SEC"};
        	  OSDAPI_ShowIndentString(FALSE, 0, 1, OSD_INFO_WIDTH, DisconnectedStrTab[UserData.ucLanguage]);      
        	  OSDAPI_ShowIndentString(FALSE, 0, 4, OSD_INFO_WIDTH, time_str);
            }
            break;
#if 0            
        case OSD_DLG_OSDLOCK   :
            OSDAPI_ShowIndentString(FALSE, 0, 1, OSD_INFO_WIDTH, 
                                    AttentionStrTab[UserData.ucLanguage]);
            OSDAPI_ShowIndentString(FALSE, 0, 5, OSD_INFO_WIDTH, 
                                    OSD_LockStrTab[UserData.ucLanguage]);
            break;
#endif

        case OSD_DLG_SLEEP:
            OSDAPI_ShowIndentString(FALSE, 0, 1, OSD_INFO_WIDTH, 
                                    AttentionStrTab[UserData.ucLanguage]);
            OSDAPI_ShowIndentString(FALSE, 0, 5, OSD_INFO_WIDTH, 
                                    NoSyncStrTab[UserData.ucLanguage]);
            break;


        case OSD_DLG_NOTICE:      										
            OSDAPI_ShowIndentString(FALSE, 0, 1, OSD_INFO_WIDTH, InputStrTab[UserData.ucLanguage]);
#if (INPUT_INTERFACE&INPUT_MHL0) || (INPUT_INTERFACE&INPUT_MHL1)
            if((UserData.ucInputSource != INPUT_SC_DP) && (GetInputSyncMode() == DIG_SYNC) && MHL_IsMHLInput() ) 
			{
                	code UCHAR MHL_StrTab1[]={3,"MHL"};
                	OSDAPI_ShowIndentString(FALSE, 0, 5, OSD_INFO_WIDTH, MHL_StrTab1);
            }
            else 
		 	{
                	OSDAPI_ShowIndentString(FALSE, 0, 5, OSD_INFO_WIDTH, 
                                    SourceStrTab[UserData.ucInputSource*NUM_OSDLANGS+UserData.ucLanguage]);
            }
#else
            OSDAPI_ShowIndentString(FALSE, 0, 5, OSD_INFO_WIDTH, 
                                    SourceStrTab[UserData.ucInputSource*NUM_OSDLANGS+UserData.ucLanguage]);

#endif
            break;


        case OSD_DLG_BURNIN:

#if BurnIn_Degub == ENABLE
	printf("DD-2\n");
#endif
        	{
        	  code UCHAR time_str[] = {12,"HOUR:MIN:SEC"};
        	  OSDAPI_ShowIndentString(FALSE, 0, 1, OSD_INFO_WIDTH, BurnInStrTab[UserData.ucLanguage]);      
        	  OSDAPI_ShowIndentString(FALSE, 0, 4, OSD_INFO_WIDTH, time_str);
        	}
            break;


#if ALS_EnDis == ALSMODE

#elif ALS_EnDis == ALSOffSET	//don't know used where ~
		case OSD_DLG_ALS_BASE_VALUE:		// george: F_ALSBV_03B1
            OSDAPI_ShowIndentString(FALSE, 0, 1, OSD_INFO_WIDTH, 
                                    ALSBVStrTab[UserData.ucLanguage]);
									//george: F_ALSBV_04F,  ALS to run "ucALSOnSetBrigVal"
	            OSDShowSliderBar(5,5, UserData.ucALSBaseVal);
	            OSDShowNum(11,6, UserData.ucALSBaseVal);

			break;
#else	//Normal

#endif	//#if ALS_EnDis == ENABLE


        default:
            break;
        
    }

    OSDTurnOnOSD();
}


//******************************************************************************
// Prototype: 
//  void OSDMovePosition(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
void OSDMovePosition(void)
{
    USHRT lmt_x, lmt_y, stp_x, stp_y;

#if ENABLE_OSD_ROTATION == ON
    if (UserData.bOSDRotation) {
        lmt_x = MAX_ROT_X;
        lmt_y = MAX_ROT_Y;
        stp_x = OSD_MOVESTEP_ROT_X;
        stp_y = OSD_MOVESTEP_ROT_Y;
    }
    else {
        lmt_x = MAX_X;
        lmt_y = MAX_Y;
        stp_x = OSD_MOVESTEP_X;
        stp_y = OSD_MOVESTEP_Y;
    }
#else
    lmt_x = MAX_X;
    lmt_y = MAX_Y;
    stp_x = OSD_MOVESTEP_X;
    stp_y = OSD_MOVESTEP_Y;
#endif

    if(usOSDMovingX < 0x8000){
        usOSDMovingX += stp_x;
        if(usOSDMovingX >= lmt_x){
            usOSDMovingX = 0x8000+lmt_x;
        }
    }
    else{
        usOSDMovingX -= stp_x;
        if(usOSDMovingX < 0x8000){
            usOSDMovingX = 1;
        }
    }   
    if(usOSDMovingY < 0x8000){
        usOSDMovingY += stp_y;  
        if(usOSDMovingY >= lmt_y){
            usOSDMovingY = 0x8000+lmt_y;
        }
    }
    else{
        usOSDMovingY -= stp_y;  
        if(usOSDMovingY <0x8000){
            usOSDMovingY = 1;
        }
    }
    
    OSDAPI_SetRowPosition(usOSDMovingX&0x7fff, usOSDMovingY&0x7fff);
}



//******************************************************************************
// Prototype: 
//  
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
void OSDFocusBr(void)
{
    OSDClearSubmenu();

#if ALS_EnDis == ALSMODE
	OSDShowBrightness(TRUE);

#elif ALS_EnDis == ALSOffSET	
	if(UserData.bALSOnOff == ON)
		OSDShowALSBV(TRUE);			// george: F_ALSBV_03B
	else
		OSDShowBrightness(TRUE);

#elif ALS_EnDis == ALSRange
	OSDShowBrightness(TRUE);

#else	//Normal
	OSDShowBrightness(TRUE);
#endif	//#if ALS_EnDis == ENABLE

}

void OSDFocusCn(void)
{
    OSDClearSubmenu();
    OSDShowContrast(TRUE);
}

//void OSDFocusGamma(void)
//{
//    OSDClearSubmenu();
//    OSDShowGamma(TRUE);
//}



#if ALS_EnDis == ALSMODE
	void OSDFocusALSMode(void)
	{
		OSDClearSubmenu();
		OSDShowALSMode(TRUE);
	}	
	
#elif ALS_EnDis == ALSOffSET	
	void OSDFocusALSOnOff(void)			// george: F_ALSOnOff_03A
	{
	    OSDClearSubmenu();
	    OSDShowALSOnOff(TRUE);
	}

#elif ALS_EnDis == ALSRange
	void OSDFocusALSOnOff(void)			// george: F_ALSOnOff_03A
	{
	    OSDClearSubmenu();
	    OSDShowALSOnOff(TRUE);
	}

#else	//Normal

#endif	//#if ALS_EnDis == ENABLE


/* void OSDFocusALSBV(void)			//george: F_ALSBV_03A
{
    OSDClearSubmenu();
    OSDShowALSBV(TRUE);
} */


#if TOUCH_EnDis == ENABLE
	void OSDFocusTouch(void)			//george: F_Touch_03A
	{
	    OSDClearSubmenu();
	    OSDShowTouch(TRUE);
	}
#endif //#if TOUCH_EnDis == ENABLE

			 


/*
void OSDFocusGItem16(void)			// george_Item16
{
    OSDClearSubmenu();
    OSDShowALS(TRUE);
}

void OSDFocusGItem17(void)			// george_Item17
{
    OSDClearSubmenu();
    OSDShowALS(TRUE);
}
*/

void OSDFocusSR(void)
{
#if ENABLE_SR
    OSDClearSubmenu();
    OSDShowSR(TRUE);
#endif
}

void OSDFocusPhase(void)
{
    OSDClearSubmenu();
    OSDShowPhase(TRUE);
}

void OSDFocusClock(void)
{
    OSDClearSubmenu();
    OSDShowClock(TRUE);
}

void OSDFocusHPos(void)
{
    OSDClearSubmenu();
    OSDShowHPos(TRUE);
}

void OSDFocusVPos(void)
{
    OSDClearSubmenu();
    OSDShowVPos(TRUE);
}

void OSDFocusClrTmp(void)
{
    OSDClearSubmenu();
    OSDShowClrTmp(TRUE);
}

void OSDFocusRGain(void)
{
    OSDClearSubmenu();
    OSDShowRGain(TRUE);
}

void OSDFocusGGain(void)
{
    OSDClearSubmenu();
    OSDShowGGain(TRUE);
}

void OSDFocusBBain(void)
{
    OSDClearSubmenu();
    OSDShowBGain(TRUE);
}

void OSDFocusOSDHPos(void)
{
    OSDClearSubmenu();
    OSDShowOSDHPos(TRUE);
}

void OSDFocusOSDVPos(void)
{
    OSDClearSubmenu();
    OSDShowOSDVPos(TRUE);
}

void OSDFocusOSDTran(void)
{
    OSDClearSubmenu();
    OSDShowOSDTran(TRUE);
}

void OSDFocusTimer(void)
{
    OSDClearSubmenu();
    OSDShowTimer(TRUE);
}

//void OSDFocusOSDRotation(void)
//{
//    OSDClearSubmenu();
//    OSDShowOSDRotation(TRUE);
//}

void OSDFocusLang(void)
{
    OSDClearSubmenu();
    OSDShowLang(TRUE);
}
//---------------------------------			
void OSDFocusVolume(void)		
{
    OSDClearSubmenu();
    OSDShowVolume(TRUE);
}
//---------------------------------
void OSDFocusMute(void)					
{
    OSDClearSubmenu();
    OSDShowMute(TRUE);
}

void OSDFocusInput(void)					
{
    OSDClearSubmenu();
    OSDShowInput(TRUE);
}

//void OSDFocusDCR(void)
//{
//    OSDClearSubmenu();
//    OSDShowDCR(TRUE);
//}

#if ENABLE_ASPECT_RATIO == ON		//george 20160217
	void OSDFocusAspRatio(void)
	{
	    OSDClearSubmenu();
	    OSDShowAspRatio(TRUE);
	}
#endif

//void OSDFocusOverscan(void)
//{
//    OSDClearSubmenu();
//    OSDShowOverScan(TRUE);
//}

//void OSDFocusOD(void)
//{
//    OSDClearSubmenu();
//    OSDShowOD(TRUE);
//}

void OSDFocusReset(void)
{
    OSDClearSubmenu();
    OSDShowReset(TRUE);
}


#if ENABLE_FUNC_OSD == ON
void OSDFocus3DCnv(void)
{
    OSDClearFuncMenu();
    OSDShowThrDCnvMenu(TRUE);
}

void OSDFocus2Dto3DAdpt(void)
{
    OSDClearFuncMenu();
    OSDShow2Dto3DAdpt(TRUE);
}

void OSDFocus2Dto3DDepth(void)
{
    OSDClearFuncMenu();
    OSDShow2Dto3DDepth(TRUE);
}

void OSDFocus2Dto3DView(void)
{
    OSDClearFuncMenu();
    OSDShow2Dto3DView(TRUE);
}

void OSDFocus3DLRSwap(void)
{
    OSDClearFuncMenu();
    OSDShow3DLRSwap(TRUE);
}

void OSDFocus3DTo2D(void)
{
    OSDClearFuncMenu();
    OSDShow3DTo2D(TRUE);
}
#endif


void OSDShowResolution(UCHAR x, UCHAR y)
{
    UCHAR i;
    UCHAR buff[32];

    sprintf(buff,"n%dx%d@%d.%dHz",InputTiming.usModeHActive,
                                  InputTiming.usModeVActive,
                                  InputTiming.usVSyncFreq/10, 
                                  InputTiming.usVSyncFreq%10);
    
    for(i=0; i<32; i++) {
        if(buff[i] == 0)
            break;
    }
    
    buff[0] = i - 1;
    OSDAPI_SetAlignType(OSD_ALIGN_RIGHT);
#ifdef USE_X19N_BOARD
    y = 1; 
    OSDAPI_ShowIndentString(FALSE, x, y, 15, buff);
#else
    OSDAPI_ShowIndentString(FALSE, x, y, 15, buff);
#endif
}

void OSDShowBrightness(UCHAR redraw)
{
    if (redraw)
    {
        OSDAPI_SetIndentIndex(48);
        OSDAPI_SetAlignType(OSD_ALIGN_LEFT);
        OSDAPI_ShowIndentString(FALSE, 5, 6, OSD_SUB_WIDTH, 
                                BrightnessStrTab[UserData.ucLanguage]);
    }
	 
	#if ALS_EnDis == ALSMODE
		if(UserData.ucALSMode== ALS_OFF)
		{
			    if (ucMenuType == OSD_DLG_BRIGHTNESS) {
			        OSDShowSliderBar(5, 5, UserData.ucBrightness);
			        OSDShowNum(11,6, UserData.ucBrightness);
			    }else {
			        OSDShowSliderBar(10,8, UserData.ucBrightness);
			        OSDShowNum(25,6, UserData.ucBrightness);
			    }	
		}else{
			    if (ucMenuType == OSD_DLG_BRIGHTNESS) {
			        OSDShowSliderBar(5, 5, NowAlsBright);
			        OSDShowNum(11,6, NowAlsBright);
			    }else {
			        OSDShowSliderBar(10,8, NowAlsBright);
			        OSDShowNum(25,6, NowAlsBright);
			    }
		}

	#elif ALS_EnDis == ALSOffSET	
	    if (ucMenuType == OSD_DLG_BRIGHTNESS) {
	        OSDShowSliderBar(5, 5, UserData.ucBrightness);
	        OSDShowNum(11,6, UserData.ucBrightness);
	    }else {
	        OSDShowSliderBar(10,8, UserData.ucBrightness);
	        OSDShowNum(25,6, UserData.ucBrightness);
	    }	

	#elif ALS_EnDis == ALSRange
		if(UserData.bALSOnOff== OFF)
		{
			    if (ucMenuType == OSD_DLG_BRIGHTNESS) {
			        OSDShowSliderBar(5, 5, UserData.ucBrightness);
			        OSDShowNum(11,6, UserData.ucBrightness);
			    }else {
			        OSDShowSliderBar(10,8, UserData.ucBrightness);
			        OSDShowNum(25,6, UserData.ucBrightness);
			    }		
		}else{
			    if (ucMenuType == OSD_DLG_BRIGHTNESS) {
			        OSDShowSliderBar(5, 5, NowAlsBright);
			        OSDShowNum(11,6, NowAlsBright);
			    }else {
			        OSDShowSliderBar(10,8, NowAlsBright);
			        OSDShowNum(25,6, NowAlsBright);
			    }
		}						 

	#else	//Normal

	    if (ucMenuType == OSD_DLG_BRIGHTNESS) {
	        OSDShowSliderBar(5, 5, UserData.ucBrightness);
	        OSDShowNum(11,6, UserData.ucBrightness);
	    }else {
	        OSDShowSliderBar(10,8, UserData.ucBrightness);
	        OSDShowNum(25,6, UserData.ucBrightness);
	    }
	#endif	//#if ALS_EnDis == ENABLE
}


void OSDShowContrast(UCHAR redraw)
{
    if (redraw)
    {
        OSDAPI_SetIndentIndex(48);
        OSDAPI_SetAlignType(OSD_ALIGN_LEFT);
        OSDAPI_ShowIndentString(FALSE, 5, 6, OSD_SUB_WIDTH, 
                                ContrastStrTab[UserData.ucLanguage]);
    }
    if (ucMenuType == OSD_DLG_CONTRAST) {
        OSDShowSliderBar(5, 5, UserData.ucContrast);
        OSDShowNum(11, 6, UserData.ucContrast);
    }
    else {
        OSDShowSliderBar(10,8, UserData.ucContrast);
        OSDShowNum(25,6, UserData.ucContrast);
    }
}

void OSDShowVolume(UCHAR redraw)
{
    if (redraw)
    {
        OSDAPI_SetIndentIndex(48);
        OSDAPI_SetAlignType(OSD_ALIGN_LEFT);
        OSDAPI_ShowIndentString(FALSE, 5, 6, OSD_SUB_WIDTH, 
                                VolumeStrTab[UserData.ucLanguage]);
    }
    if (ucMenuType == OSD_DLG_VOLUME) {
        OSDShowSliderBar(5, 5, UserData.ucVolume);
        OSDShowNum(11, 6, UserData.ucVolume);
    }
    else {
        OSDShowSliderBar(10,8, UserData.ucVolume);
        OSDShowNum(25,6, UserData.ucVolume);
    }
}

//void OSDShowGamma(UCHAR redraw)
//{
//    if (redraw)
//    {
//        OSDAPI_SetIndentIndex(48);
//        OSDAPI_SetAlignType(OSD_ALIGN_LEFT);
//        OSDAPI_ShowIndentString(FALSE, 5, 6, OSD_SUB_WIDTH, 
//                                GammaStrTab[UserData.ucLanguage]);
//    }
//
//    OSDAPI_SetAlignType(OSD_ALIGN_CENTER);
//    OSDAPI_SetIndentIndex(64);
//    OSDAPI_ShowIndentString(FALSE, 5, 8, OSD_SUB_WIDTH, OffTab[UserData.ucLanguage]);
//    OSDAPI_ShowIndentString(FALSE, 5,10, OSD_SUB_WIDTH, OnTab[UserData.ucLanguage]);
//
//    OSDAPI_SelOSDWin(OSD_WINDOW2);
//    OSDAPI_SetOSDWinSize( 5, 8+2*UserData.bGammaOnOff, 
//                         29, 8+2*UserData.bGammaOnOff);
//    OSDAPI_OSDWinOn(OSD_WINDOW2);
//}




#if ALS_EnDis == ALSMODE
	//method(1) ALS Mode Select
	void OSDShowALSMode(UCHAR redraw)
	{	
	    if (redraw)
	    {
	        OSDAPI_SetIndentIndex(48);
	        OSDAPI_SetAlignType(OSD_ALIGN_LEFT);
	        OSDAPI_ShowIndentString(FALSE, 5, 6, OSD_SUB_WIDTH, 
	                                ALSMdStrTab[UserData.ucLanguage]);
	    }
	
	    OSDAPI_SetAlignType(OSD_ALIGN_CENTER);
	    OSDAPI_SetIndentIndex(64);
	    OSDAPI_ShowIndentString(FALSE, 5, 8, OSD_SUB_WIDTH, ALSItemStrTab[0]);
	    OSDAPI_ShowIndentString(FALSE, 5, 9, OSD_SUB_WIDTH, ALSItemStrTab[1]);
	    OSDAPI_ShowIndentString(FALSE, 5,10, OSD_SUB_WIDTH, ALSItemStrTab[2]);    
        
	
	    OSDAPI_SelOSDWin(OSD_WINDOW2);
	    OSDAPI_SetOSDWinSize( 5, 8+UserData.ucALSMode, 
	                         29, 8+UserData.ucALSMode);
	    OSDAPI_OSDWinOn(OSD_WINDOW2);
	}
#elif ALS_EnDis == ALSOffSET

	void OSDShowALSOnOff(UCHAR redraw)				// george: F_ALSOnOff_03B				++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	{
	    if (redraw)
	    {
	        OSDAPI_SetIndentIndex(48);
	        OSDAPI_SetAlignType(OSD_ALIGN_LEFT);
	        OSDAPI_ShowIndentString(FALSE, 5, 6, OSD_SUB_WIDTH, 
	                                ALSOnOffStrTab[UserData.ucLanguage]);
	    }
	
	    OSDAPI_SetAlignType(OSD_ALIGN_CENTER);
	    OSDAPI_SetIndentIndex(64);
	    OSDAPI_ShowIndentString(FALSE, 5, 8, OSD_SUB_WIDTH, OffTab[UserData.ucLanguage]);
	    OSDAPI_ShowIndentString(FALSE, 5,10, OSD_SUB_WIDTH, OnTab[UserData.ucLanguage]);
	
	    OSDAPI_SelOSDWin(OSD_WINDOW2);
	    OSDAPI_SetOSDWinSize( 5, 8+2*UserData.bALSOnOff, 
	                         29, 8+2*UserData.bALSOnOff);
	    OSDAPI_OSDWinOn(OSD_WINDOW2);
	}

	//method(2) ALS Base Value Modify.
	void OSDShowALSBV(UCHAR redraw)				// george: F_ALSBV_03B				++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	{
	    if (redraw)
	    {							  
	        OSDAPI_SetIndentIndex(48);
	        OSDAPI_SetAlignType(OSD_ALIGN_LEFT);
	        OSDAPI_ShowIndentString(FALSE, 5, 6+1, OSD_SUB_WIDTH, 
	                                ALSBVStrTab[UserData.ucLanguage]);		// change to used BrightnessStrTab[]  
			//show now brightness 
	        OSDAPI_ShowIndentString(FALSE, 5, 6+4, OSD_SUB_WIDTH, 
	                                BrightnessStrTab[UserData.ucLanguage]);
	    }


		{//modify
		    if (ucMenuType == OSD_DLG_ALS_BASE_VALUE) {							// george: F_ALSBV_03B1	,	why used this condition?
		        OSDShowSliderBar(5, 5, UserData.ucALSBaseVal);
		        OSDShowNum(11, 6, UserData.ucALSBaseVal);
		    }
		    else 
			{
		        OSDShowSliderBar(10,8, UserData.ucALSBaseVal);
		        OSDShowNum(25+2,6+2, UserData.ucALSBaseVal);
		    }

			{//add
		        OSDShowSliderBar(10,8+3, NowAlsBright);
		        OSDShowNum(25+2,6+5, NowAlsBright);
		    }		
		}			
	}

#elif ALS_EnDis == ALSRange
	void OSDShowALSOnOff(UCHAR redraw)				// george: F_ALSOnOff_03B				++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	{
	    if (redraw)
	    {
	        OSDAPI_SetIndentIndex(48);
	        OSDAPI_SetAlignType(OSD_ALIGN_LEFT);
	        OSDAPI_ShowIndentString(FALSE, 5, 6, OSD_SUB_WIDTH, 
	                                ALSOnOffStrTab[UserData.ucLanguage]);
	    }
	
	    OSDAPI_SetAlignType(OSD_ALIGN_CENTER);
	    OSDAPI_SetIndentIndex(64);
	    OSDAPI_ShowIndentString(FALSE, 5, 8, OSD_SUB_WIDTH, OffTab[UserData.ucLanguage]);
	    OSDAPI_ShowIndentString(FALSE, 5,10, OSD_SUB_WIDTH, OnTab[UserData.ucLanguage]);
	
	    OSDAPI_SelOSDWin(OSD_WINDOW2);
	    OSDAPI_SetOSDWinSize( 5, 8+2*UserData.bALSOnOff, 
	                         29, 8+2*UserData.bALSOnOff);
	    OSDAPI_OSDWinOn(OSD_WINDOW2);
	}

#else	//Normal

#endif	//#if ALS_EnDis == ENABLE




#if TOUCH_EnDis == ENABLE
	void OSDShowTouch(UCHAR redraw)			// george: F_Touch_03B				++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	{
	    if (redraw)
	    {
	        OSDAPI_SetIndentIndex(48);
	        OSDAPI_SetAlignType(OSD_ALIGN_LEFT);
	        OSDAPI_ShowIndentString(FALSE, 5, 6, OSD_SUB_WIDTH, 
	                                TouchSWStrTab[UserData.ucLanguage]);	//george: F_Touch_02
	    }
	
	    OSDAPI_SetAlignType(OSD_ALIGN_CENTER);
	    OSDAPI_SetIndentIndex(64);
	    OSDAPI_ShowIndentString(FALSE, 5, 8, OSD_SUB_WIDTH, OffTab[UserData.ucLanguage]);
	    OSDAPI_ShowIndentString(FALSE, 5,10, OSD_SUB_WIDTH, OnTab[UserData.ucLanguage]);
	
	    OSDAPI_SelOSDWin(OSD_WINDOW2);
	    OSDAPI_SetOSDWinSize( 5, 8+2*UserData.bTouchOnOff, 
	                         29, 8+2*UserData.bTouchOnOff);
	    OSDAPI_OSDWinOn(OSD_WINDOW2);
	}
#endif //#if TOUCH_EnDis == ENABLE


/*
void OSDShowGItem16(UCHAR redraw)			// george_Item16
{
    if (redraw)
    {
        OSDAPI_SetIndentIndex(48);
        OSDAPI_SetAlignType(OSD_ALIGN_LEFT);
        OSDAPI_ShowIndentString(FALSE, 5, 6, OSD_SUB_WIDTH, 
                                GItem16StrTab[UserData.ucLanguage]);
    }

    OSDAPI_SetAlignType(OSD_ALIGN_CENTER);
    OSDAPI_SetIndentIndex(64);
    OSDAPI_ShowIndentString(FALSE, 5, 8, OSD_SUB_WIDTH, OffTab[UserData.ucLanguage]);
    OSDAPI_ShowIndentString(FALSE, 5,10, OSD_SUB_WIDTH, OnTab[UserData.ucLanguage]);

    OSDAPI_SelOSDWin(OSD_WINDOW2);
    OSDAPI_SetOSDWinSize( 5, 8+2*UserData.ucALSMode, 
                         29, 8+2*UserData.ucALSMode);	  // george: re-write-code "UserData.xxx"
    OSDAPI_OSDWinOn(OSD_WINDOW2);
}

void OSDShowGItem17(UCHAR redraw)			// george_Item17
{
    if (redraw)
    {
        OSDAPI_SetIndentIndex(48);
        OSDAPI_SetAlignType(OSD_ALIGN_LEFT);
        OSDAPI_ShowIndentString(FALSE, 5, 6, OSD_SUB_WIDTH, 
                                GItem17StrTab[UserData.ucLanguage]);
    }

    OSDAPI_SetAlignType(OSD_ALIGN_CENTER);
    OSDAPI_SetIndentIndex(64);
    OSDAPI_ShowIndentString(FALSE, 5, 8, OSD_SUB_WIDTH, OffTab[UserData.ucLanguage]);
    OSDAPI_ShowIndentString(FALSE, 5,10, OSD_SUB_WIDTH, OnTab[UserData.ucLanguage]);

    OSDAPI_SelOSDWin(OSD_WINDOW2);
    OSDAPI_SetOSDWinSize( 5, 8+2*UserData.ucALSMode, 
                         29, 8+2*UserData.ucALSMode);	  // george: re-write-code "UserData.xxx"
    OSDAPI_OSDWinOn(OSD_WINDOW2);
}
*/



#if ENABLE_SR
void OSDShowSR(UCHAR redraw)
{	
    if (redraw)
    {
        OSDAPI_SetIndentIndex(48);
        OSDAPI_SetAlignType(OSD_ALIGN_LEFT);
        OSDAPI_ShowIndentString(FALSE, 5, 6, OSD_SUB_WIDTH, 
                                SRStrTab[UserData.ucLanguage]);
    }

    OSDAPI_SetAlignType(OSD_ALIGN_CENTER);
    OSDAPI_SetIndentIndex(64);
    OSDAPI_ShowIndentString(FALSE, 5, 8, OSD_SUB_WIDTH, SRItemStrTab[0]);
    OSDAPI_ShowIndentString(FALSE, 5, 9, OSD_SUB_WIDTH, SRItemStrTab[1]);
    OSDAPI_ShowIndentString(FALSE, 5,10, OSD_SUB_WIDTH, SRItemStrTab[2]);    
    OSDAPI_ShowIndentString(FALSE, 5,11, OSD_SUB_WIDTH, SRItemStrTab[3]);    
    OSDAPI_ShowIndentString(FALSE, 5,12, OSD_SUB_WIDTH, SRItemStrTab[4]);        

    OSDAPI_SelOSDWin(OSD_WINDOW2);
    OSDAPI_SetOSDWinSize( 5, 8+UserData.ucSRMode, 
                         29, 8+UserData.ucSRMode);
    OSDAPI_OSDWinOn(OSD_WINDOW2);
}
#endif

void OSDShowPhase(UCHAR redraw)
{
    UCHAR phase;
    
    if (redraw)
    {
        OSDAPI_SetIndentIndex(48);
        OSDAPI_SetAlignType(OSD_ALIGN_LEFT);
        OSDAPI_ShowIndentString(FALSE, 5, 6, OSD_SUB_WIDTH, 
                                PhaseStrTab[UserData.ucLanguage]);
    }
    
    phase = UserGetNormalPhase();
    
    OSDShowSliderBar(10, 8, phase);
    OSDShowNum(25, 6, phase);
}

void OSDShowClock(UCHAR redraw)
{
    UCHAR clock;
    
    if (redraw)
    {
        OSDAPI_SetIndentIndex(48);
        OSDAPI_SetAlignType(OSD_ALIGN_LEFT);
        OSDAPI_ShowIndentString(FALSE, 5, 6, OSD_SUB_WIDTH, ClockStrTab[UserData.ucLanguage]);
    }

    clock = UserGetNormalClock();

    OSDShowSliderBar(10, 8, clock);
    OSDShowNum(25, 6, clock);
}

void OSDShowHPos(UCHAR redraw)
{
    UCHAR pos;
    
    if (redraw)
    {
        OSDAPI_SetIndentIndex(48);
        OSDAPI_SetAlignType(OSD_ALIGN_LEFT);
        OSDAPI_ShowIndentString(FALSE, 5, 6, OSD_SUB_WIDTH, HPosStrTab[UserData.ucLanguage]);
    }

    pos = UserGetNormalHPosn();
    
    OSDShowSliderBar(10, 8, pos);
    OSDShowNum(25, 6, pos);
}

void OSDShowVPos(UCHAR redraw)
{
    UCHAR pos;

    if (redraw)
    {
        OSDAPI_SetIndentIndex(48);
        OSDAPI_SetAlignType(OSD_ALIGN_LEFT);
        OSDAPI_ShowIndentString(FALSE, 5, 6, OSD_SUB_WIDTH, VPosStrTab[UserData.ucLanguage]);
    }

    pos = UserGetNormalVPosn();

    OSDShowSliderBar(10,8, pos);
    OSDShowNum(25,6, pos);
}

void OSDShowClrTmp(UCHAR redraw)
{
    UCHAR tmp;

	if (redraw)
    {
        OSDAPI_SetIndentIndex(48);
//g OSDAPI_SetAlignType(OSD_ALIGN_LEFT);
		OSDAPI_SetAlignType(OSD_ALIGN_CENTER);
        OSDAPI_ShowIndentString(FALSE, 5, 6, OSD_SUB_WIDTH, ColorTempStrTab[UserData.ucLanguage]);
 #ifdef colortemp 			               			//140509 mike           
    	 //printf("140421 mike OSDShowClrTmp ====>if (redraw);\n\r");		
 #endif   	 
    }
    
    tmp = UserData.ucColorTemp;
    OSDAPI_SetAlignType(OSD_ALIGN_CENTER);
    OSDAPI_SetIndentIndex(64);
        OSDAPI_ShowIndentString(FALSE, 5, 8, OSD_SUB_WIDTH, ColorTemp_StrTab[0*NUM_OSDLANGS+UserData.ucLanguage]);
        OSDAPI_ShowIndentString(FALSE, 5, 9, OSD_SUB_WIDTH, ColorTemp_StrTab[1*NUM_OSDLANGS+UserData.ucLanguage]);
        OSDAPI_ShowIndentString(FALSE, 5,10, OSD_SUB_WIDTH, ColorTemp_StrTab[2*NUM_OSDLANGS+UserData.ucLanguage]);
        OSDAPI_ShowIndentString(FALSE, 5,11, OSD_SUB_WIDTH, ColorTemp_StrTab[3*NUM_OSDLANGS+UserData.ucLanguage]);
 #ifdef colortemp 			               			       //140509 mike           
      //printf("140429 mike OSDShowClrTmp ;\n\r");		//140421 mike	
 #endif     
    OSDAPI_SelOSDWin(OSD_WINDOW2);
    OSDAPI_SetOSDWinSize(5, 8+tmp, 29, 8+tmp);
    OSDAPI_OSDWinOn(OSD_WINDOW2);
}

void OSDShowRGain(UCHAR redraw)
{
    if (redraw)
    {
        OSDAPI_SetIndentIndex(48);
        OSDAPI_SetAlignType(OSD_ALIGN_LEFT);
        OSDAPI_ShowIndentString(FALSE, 5, 6, OSD_SUB_WIDTH, RedStrTab[UserData.ucLanguage]);
    }
    OSDShowSliderBar(10,8, UserData.ucUserRGain);
    OSDShowNum(25,6, UserData.ucUserRGain);
}

void OSDShowGGain(UCHAR redraw)
{
    if (redraw)
    {
        OSDAPI_SetIndentIndex(48);
        OSDAPI_SetAlignType(OSD_ALIGN_LEFT);
        OSDAPI_ShowIndentString(FALSE, 5, 6, OSD_SUB_WIDTH, GreenStrTab[UserData.ucLanguage]);
    }
    OSDShowSliderBar(10,8, UserData.ucUserGGain);
    OSDShowNum(25,6, UserData.ucUserGGain);
}

void OSDShowBGain(UCHAR redraw)
{
    if (redraw)
    {
        OSDAPI_SetIndentIndex(48);
        OSDAPI_SetAlignType(OSD_ALIGN_LEFT);
        OSDAPI_ShowIndentString(FALSE, 5, 6, OSD_SUB_WIDTH, BlueStrTab[UserData.ucLanguage]);
    }
    OSDShowSliderBar(10,8, UserData.ucUserBGain);
    OSDShowNum(25,6, UserData.ucUserBGain);
}

void OSDShowOSDHPos(UCHAR redraw)
{
    if (redraw)
    {
        OSDAPI_SetIndentIndex(48);
        OSDAPI_SetAlignType(OSD_ALIGN_LEFT);
        OSDAPI_ShowIndentString(FALSE, 5, 6, OSD_SUB_WIDTH, HorizontalStrTab[UserData.ucLanguage]);
    }
    OSDShowSliderBar(10,8, UserData.ucOSDX);
    OSDShowNum(25,6, UserData.ucOSDX);
}

void OSDShowOSDVPos(UCHAR redraw)
{
    if (redraw)
    {
        OSDAPI_SetIndentIndex(48);
        OSDAPI_SetAlignType(OSD_ALIGN_LEFT);
        OSDAPI_ShowIndentString(FALSE, 5, 6, OSD_SUB_WIDTH, VerticalStrTab[UserData.ucLanguage]);
    }
    OSDShowSliderBar(10,8, UserData.ucOSDY);
    OSDShowNum(25,6, UserData.ucOSDY);
}

void OSDShowOSDTran(UCHAR redraw)
{
    UCHAR ratio;
    if (redraw)
    {
        OSDAPI_SetIndentIndex(48);
        OSDAPI_SetAlignType(OSD_ALIGN_LEFT);
        OSDAPI_ShowIndentString(FALSE, 5, 6, OSD_SUB_WIDTH, TransparencyStrTab[UserData.ucLanguage]);
    }
    ratio = (USHRT)UserData.ucOSDTransparent*100/MAXIMUM_OSD_TRANS;
    OSDShowSliderBar(10,8, ratio);
    OSDShowNum(25,6, UserData.ucOSDTransparent);
}

void OSDShowTimer(UCHAR redraw)
{
    UCHAR ratio;
    if (redraw)
    {
        OSDAPI_SetIndentIndex(48);
        OSDAPI_SetAlignType(OSD_ALIGN_LEFT);
        OSDAPI_ShowIndentString(FALSE, 5, 6, OSD_SUB_WIDTH, OSDTimeStrTab[UserData.ucLanguage]);
    }
    ratio = (USHRT)UserData.ucOSDTimer*100/MAXIMUM_OSD_TIMER;
    OSDShowSliderBar(10,8, ratio);
    OSDShowNum(25,6, UserData.ucOSDTimer);
}

//void OSDShowOSDRotation(UCHAR redraw)
//{
//    if (redraw)
//    {
//        OSDAPI_SetIndentIndex(48);
//        OSDAPI_SetAlignType(OSD_ALIGN_LEFT);
//        OSDAPI_ShowIndentString(FALSE, 5, 6, OSD_SUB_WIDTH, OSDRotationStrTab[UserData.ucLanguage]);
//    }
//
//    OSDAPI_SetAlignType(OSD_ALIGN_CENTER);
//    OSDAPI_SetIndentIndex(64);
//    OSDAPI_ShowIndentString(FALSE, 5, 8, OSD_SUB_WIDTH, OffTab[UserData.ucLanguage]);
//    OSDAPI_ShowIndentString(FALSE, 5,10, OSD_SUB_WIDTH, OnTab[UserData.ucLanguage]);
//
//    OSDAPI_SelOSDWin(OSD_WINDOW2);
//    OSDAPI_SetOSDWinSize( 5, 8+2*UserData.bOSDRotation,
//                         29, 8+2*UserData.bOSDRotation);
//    OSDAPI_OSDWinOn(OSD_WINDOW2);
//}

void OSDShowLang(UCHAR redraw)
{
    UCHAR tmp;
    if (redraw)
    {
        OSDAPI_SetIndentIndex(48);
        OSDAPI_SetAlignType(OSD_ALIGN_LEFT);
        OSDAPI_ShowIndentString(FALSE, 5, 6, OSD_SUB_WIDTH, LanguageStrTab[UserData.ucLanguage]);
    }

    OSDAPI_SetAlignType(OSD_ALIGN_CENTER);
    OSDAPI_SetIndentIndex(64);
    OSDAPI_ShowIndentString(FALSE,  5, 8, OSD_SUB_WIDTH/2, CountryStrTab[OSDLANG_ENGLISH]);
    OSDAPI_ShowIndentString(FALSE, 17, 8, OSD_SUB_WIDTH/2, CountryStrTab[OSDLANG_SPANISH]);
    OSDAPI_ShowIndentString(FALSE,  5, 9, OSD_SUB_WIDTH/2, CountryStrTab[OSDLANG_FRENCH]);
    OSDAPI_ShowIndentString(FALSE, 17, 9, OSD_SUB_WIDTH/2, CountryStrTab[OSDLANG_GERMAN]);
    OSDAPI_ShowIndentString(FALSE,  5,10, OSD_SUB_WIDTH/2, CountryStrTab[OSDLANG_ITALIAN]);
    OSDAPI_ShowIndentString(FALSE, 17,10, OSD_SUB_WIDTH/2, CountryStrTab[OSDLANG_PORTUGUESE]);
    OSDAPI_ShowIndentString(FALSE,  5,11, OSD_SUB_WIDTH/2, CountryStrTab[OSDLANG_RUSSIAN]);
    OSDAPI_ShowIndentString(FALSE, 17,11, OSD_SUB_WIDTH/2, CountryStrTab[OSDLANG_SCHINESE]);

    tmp = UserData.ucLanguage / 2;
    OSDAPI_SelOSDWin(OSD_WINDOW2);
    if ((UserData.ucLanguage&BIT0) == 0)
        OSDAPI_SetOSDWinSize( 5, 8+tmp, 16, 8+tmp);
    else
        OSDAPI_SetOSDWinSize(17, 8+tmp, 29, 8+tmp);
    OSDAPI_OSDWinOn(OSD_WINDOW2);
}

void OSDShowMute(UCHAR redraw)
{
    if (redraw)
    {
        OSDAPI_SetIndentIndex(48);
        OSDAPI_SetAlignType(OSD_ALIGN_LEFT);
        OSDAPI_ShowIndentString(FALSE, 5, 6, OSD_SUB_WIDTH, MuteTab[UserData.ucLanguage]);
    }

    OSDAPI_SetAlignType(OSD_ALIGN_CENTER);
    OSDAPI_SetIndentIndex(64);
    OSDAPI_ShowIndentString(FALSE, 5, 8, OSD_SUB_WIDTH, OffTab[UserData.ucLanguage]);
    OSDAPI_ShowIndentString(FALSE, 5,10, OSD_SUB_WIDTH, OnTab[UserData.ucLanguage]);

    OSDAPI_SelOSDWin(OSD_WINDOW2);
    OSDAPI_SetOSDWinSize( 5, 8+2*UserData.bAudioMute,
                         29, 8+2*UserData.bAudioMute);
    OSDAPI_OSDWinOn(OSD_WINDOW2);
}

void OSDShowInput(UCHAR redraw)							//140318  
{
    UCHAR i,len = CheckTotalPortNum();

    if (redraw)
    {
        OSDAPI_SetIndentIndex(48);
        OSDAPI_SetAlignType(OSD_ALIGN_LEFT);
        OSDAPI_ShowIndentString(FALSE, 5, 6, OSD_SUB_WIDTH, InputStrTab[UserData.ucLanguage]);
    }
    
    OSDAPI_SetAlignType(OSD_ALIGN_CENTER);
    OSDAPI_SetIndentIndex(64);

    for (i=0; i<len; i++ ) 
	{
         OSDAPI_ShowIndentString(FALSE,5,8+i,OSD_SUB_WIDTH,SourceStrTab[UserData.ucLanguage+GetInputPortName(i)*NUM_OSDLANGS]);
    }

    OSDAPI_SelOSDWin(OSD_WINDOW2);
    OSDAPI_SetOSDWinSize( 5, 8+GetInputPortIndex(UserData.ucInputSource), 
                         29, 8+GetInputPortIndex(UserData.ucInputSource));
    OSDAPI_OSDWinOn(OSD_WINDOW2);
}

//void OSDShowDCR(UCHAR redraw)
//{
//    if (redraw)
//    {
//        OSDAPI_SetIndentIndex(48);
//        OSDAPI_SetAlignType(OSD_ALIGN_LEFT);
//        OSDAPI_ShowIndentString(FALSE, 5, 6, OSD_SUB_WIDTH, DCR_StrTab[UserData.ucLanguage]);
//    }
//
//    OSDAPI_SetAlignType(OSD_ALIGN_CENTER);
//    OSDAPI_SetIndentIndex(64);
//    OSDAPI_ShowIndentString(FALSE, 5, 8, OSD_SUB_WIDTH, OffTab[UserData.ucLanguage]);
//    OSDAPI_ShowIndentString(FALSE, 5, 9, OSD_SUB_WIDTH, DCR_StrTab[UserData.ucLanguage]);
//    OSDAPI_ShowIndentString(FALSE, 5,10, OSD_SUB_WIDTH, DBC_StrTab[UserData.ucLanguage]);
//    
//    OSDAPI_SelOSDWin(OSD_WINDOW2);
//    OSDAPI_SetOSDWinSize( 5, 8+UserData.ucDCRMode, 
//                         29, 8+UserData.ucDCRMode);
//    OSDAPI_OSDWinOn(OSD_WINDOW2);
//}

#if ENABLE_ASPECT_RATIO == ON		//george 20160217
	void OSDShowAspRatio(UCHAR redraw)
	{
	    if (redraw)
	    {
	        OSDAPI_SetIndentIndex(48);
	        OSDAPI_SetAlignType(OSD_ALIGN_LEFT);
	        OSDAPI_ShowIndentString(FALSE, 5, 6, OSD_SUB_WIDTH, DisplaySizeTab[UserData.ucLanguage]);
	    }
	
	    OSDAPI_SetAlignType(OSD_ALIGN_CENTER);
	    OSDAPI_SetIndentIndex(64);
	    OSDAPI_ShowIndentString(FALSE, 5, 8, OSD_SUB_WIDTH, FullScreenTab[UserData.ucLanguage]);
	    OSDAPI_ShowIndentString(FALSE, 5, 9, OSD_SUB_WIDTH, SmartFitTab[UserData.ucLanguage]);
	    OSDAPI_ShowIndentString(FALSE, 5,10, OSD_SUB_WIDTH, Fix43Tab[UserData.ucLanguage]);
	    OSDAPI_ShowIndentString(FALSE, 5,11, OSD_SUB_WIDTH, Smart43Tab[UserData.ucLanguage]);
	
	    OSDAPI_SelOSDWin(OSD_WINDOW2);
	    OSDAPI_SetOSDWinSize( 5, 8+UserData.ucAspectRatio,
	                         29, 8+UserData.ucAspectRatio);
	    OSDAPI_OSDWinOn(OSD_WINDOW2);
	}
#endif

//void OSDShowOverScan(UCHAR redraw)
//{
//    if (redraw)
//    {
//        OSDAPI_SetIndentIndex(48);
//        OSDAPI_SetAlignType(OSD_ALIGN_LEFT);
//        OSDAPI_ShowIndentString(FALSE, 5, 6, OSD_SUB_WIDTH, OverScanTab[UserData.ucLanguage]);
//    }
//
//    OSDAPI_SetAlignType(OSD_ALIGN_CENTER);
//    OSDAPI_SetIndentIndex(64);
//    OSDAPI_ShowIndentString(FALSE, 5, 8, OSD_SUB_WIDTH, OffTab[UserData.ucLanguage]);
//    OSDAPI_ShowIndentString(FALSE, 5,10, OSD_SUB_WIDTH, OnTab[UserData.ucLanguage]);
//
//    OSDAPI_SelOSDWin(OSD_WINDOW2);
//    OSDAPI_SetOSDWinSize( 5, 8+2*UserData.bOverScan, 
//                         29, 8+2*UserData.bOverScan);
//    OSDAPI_OSDWinOn(OSD_WINDOW2);
//}

//void OSDShowOD(UCHAR redraw)
//{
//    if (redraw)
//    {
//        OSDAPI_SetIndentIndex(48);
//        OSDAPI_SetAlignType(OSD_ALIGN_LEFT);
//        OSDAPI_ShowIndentString(FALSE, 5, 6, OSD_SUB_WIDTH, OverDriverTab[UserData.ucLanguage]);
//    }
//
//    OSDAPI_SetAlignType(OSD_ALIGN_CENTER);
//    OSDAPI_SetIndentIndex(64);
//    OSDAPI_ShowIndentString(FALSE, 5, 8, OSD_SUB_WIDTH, OffTab[UserData.ucLanguage]);
//    OSDAPI_ShowIndentString(FALSE, 5,10, OSD_SUB_WIDTH, OnTab[UserData.ucLanguage]);
//
//    OSDAPI_SelOSDWin(OSD_WINDOW2);
//    OSDAPI_SetOSDWinSize( 5, 8+2*UserData.ucODMode, 
//                         29, 8+2*UserData.ucODMode);
//    OSDAPI_OSDWinOn(OSD_WINDOW2);
//}

void OSDShowReset(UCHAR redraw)
{
    if (redraw)
    {
        ucPerformReset = FALSE;
        OSDAPI_SetIndentIndex(48);
        OSDAPI_SetAlignType(OSD_ALIGN_LEFT);
        OSDAPI_ShowIndentString(FALSE, 5, 6, OSD_SUB_WIDTH, ResetStrTab[UserData.ucLanguage]);
    }

    OSDAPI_SetAlignType(OSD_ALIGN_CENTER);
    OSDAPI_SetIndentIndex(64);
    OSDAPI_ShowIndentString(FALSE, 5, 8, OSD_SUB_WIDTH, NoStrTab[UserData.ucLanguage]);
    OSDAPI_ShowIndentString(FALSE, 5,10, OSD_SUB_WIDTH, YesStrTab[UserData.ucLanguage]);

    OSDAPI_SelOSDWin(OSD_WINDOW2);
    OSDAPI_SetOSDWinSize( 5, 8+2*ucPerformReset, 
                         29, 8+2*ucPerformReset);
    OSDAPI_OSDWinOn(OSD_WINDOW2);
}

#if ENABLE_FUNC_OSD == ON
void OSDShowThrDCnvMenu(UCHAR redraw)
{
    if (redraw)
    {
        OSDAPI_SetIndentIndex(48);
        OSDAPI_SetAlignType(OSD_ALIGN_LEFT);
        OSDAPI_ShowIndentString(FALSE, 5, 3, OSD_FUNC_WIDTH-10, 
                                ThrDCnvTab[UserData.ucLanguage]);
    }
    
    OSDAPI_SetAlignType(OSD_ALIGN_LEFT);
    OSDAPI_SetIndentIndex(64);

    OSDAPI_ShowIndentString(FALSE, 5, 5, OSD_FUNC_WIDTH-10, ThrDCnvFmtTab[0]);
    OSDAPI_ShowIndentString(FALSE, 5, 6, OSD_FUNC_WIDTH-10, ThrDCnvFmtTab[1]);
    OSDAPI_ShowIndentString(FALSE, 5, 7, OSD_FUNC_WIDTH-10, ThrDCnvFmtTab[2]);
    OSDAPI_ShowIndentString(FALSE, 5, 8, OSD_FUNC_WIDTH-10, ThrDCnvFmtTab[3]);
    OSDAPI_ShowIndentString(FALSE, 5, 9, OSD_FUNC_WIDTH-10, ThrDCnvFmtTab[4]);
    
    OSDAPI_SelOSDWin(OSD_WINDOW2);
    OSDAPI_SetOSDWinSize(5, 5 + UserData.uc2DTo3DMode,
                         OSD_FUNC_WIDTH - 5, 5 + UserData.uc2DTo3DMode);
    OSDAPI_OSDWinOn(OSD_WINDOW2);
}

void OSDShow2Dto3DAdpt(UCHAR redraw)
{
    if (redraw)
    {
        OSDAPI_SetIndentIndex(48);
        OSDAPI_SetAlignType(OSD_ALIGN_LEFT);
        OSDAPI_ShowIndentString(FALSE, 5, 3, OSD_FUNC_WIDTH-10, 
                                ThrDAdpTab[UserData.ucLanguage]);
    }
    
    OSDAPI_SetAlignType(OSD_ALIGN_LEFT);
    OSDAPI_SetIndentIndex(64);

    OSDAPI_ShowIndentString(FALSE, 5, 6, OSD_FUNC_WIDTH-10, OffTab[UserData.ucLanguage]);
    OSDAPI_ShowIndentString(FALSE, 5, 8, OSD_FUNC_WIDTH-10, OnTab[UserData.ucLanguage]);
    
    OSDAPI_SelOSDWin(OSD_WINDOW2);
    if (Is2DTo3DAdaptive()) {
        OSDAPI_SetOSDWinSize(5, 8, OSD_FUNC_WIDTH - 5, 8);
    }
    else {
        OSDAPI_SetOSDWinSize(5, 6, OSD_FUNC_WIDTH - 5, 6);
    }
    OSDAPI_OSDWinOn(OSD_WINDOW2);
}

void OSDShow2Dto3DDepth(UCHAR redraw)
{
    UCHAR tmp;
    if (redraw)
    {
        OSDAPI_SetIndentIndex(48);
        OSDAPI_SetAlignType(OSD_ALIGN_LEFT);
        OSDAPI_ShowIndentString(FALSE, 5, 3, OSD_FUNC_WIDTH-10, 
                                ThrDDphTab[UserData.ucLanguage]);
    }
    
    tmp = UserGetNormal2DTo3DDpth();
    
    OSDShowSliderBar(5, 5, tmp);
    OSDShowNum(25, 5, tmp);
}

void OSDShow2Dto3DView(UCHAR redraw)
{
    UCHAR tmp;
    if (redraw)
    {
        OSDAPI_SetIndentIndex(48);
        OSDAPI_SetAlignType(OSD_ALIGN_LEFT);
        OSDAPI_ShowIndentString(FALSE, 5, 3, OSD_FUNC_WIDTH-10, 
                                ThrDVwTab[UserData.ucLanguage]);
    }
    
    tmp = UserGetNormal2DTo3DView();
    
    OSDShowSliderBar(5, 5, tmp);
    OSDShowNum(25, 5, tmp);
}

void OSDShow3DLRSwap(UCHAR redraw)
{
    if (redraw)
    {
        OSDAPI_SetIndentIndex(48);
        OSDAPI_SetAlignType(OSD_ALIGN_LEFT);
        OSDAPI_ShowIndentString(FALSE, 5, 3, OSD_FUNC_WIDTH-10, 
                                ThrDLRTab[UserData.ucLanguage]);
    }
    
    OSDAPI_SetAlignType(OSD_ALIGN_LEFT);
    OSDAPI_SetIndentIndex(64);

    OSDAPI_ShowIndentString(FALSE, 5, 6, OSD_FUNC_WIDTH-10, OffTab[UserData.ucLanguage]);
    OSDAPI_ShowIndentString(FALSE, 5, 8, OSD_FUNC_WIDTH-10, OnTab[UserData.ucLanguage]);
    
    OSDAPI_SelOSDWin(OSD_WINDOW2);
    if (Is3DLRSwap()) {
        OSDAPI_SetOSDWinSize(5, 8, OSD_FUNC_WIDTH - 5, 8);
    }
    else {
        OSDAPI_SetOSDWinSize(5, 6, OSD_FUNC_WIDTH - 5, 6);
    }
    OSDAPI_OSDWinOn(OSD_WINDOW2);
}

void OSDShow3DTo2D(UCHAR redraw)
{
    if (redraw)
    {
        OSDAPI_SetIndentIndex(48);
        OSDAPI_SetAlignType(OSD_ALIGN_LEFT);
        OSDAPI_ShowIndentString(FALSE, 5, 3, OSD_FUNC_WIDTH-10, 
                                ThrDTwoDTab[UserData.ucLanguage]);
    }
    
    OSDAPI_SetAlignType(OSD_ALIGN_LEFT);
    OSDAPI_SetIndentIndex(64);

    OSDAPI_ShowIndentString(FALSE, 5, 6, OSD_FUNC_WIDTH-10, OffTab[UserData.ucLanguage]);
    OSDAPI_ShowIndentString(FALSE, 5, 8, OSD_FUNC_WIDTH-10, OnTab[UserData.ucLanguage]);
    
    OSDAPI_SelOSDWin(OSD_WINDOW2);
    if (Is3DTo2DEnabled()) {
        OSDAPI_SetOSDWinSize(5, 8, OSD_FUNC_WIDTH - 5, 8);
    }
    else {
        OSDAPI_SetOSDWinSize(5, 6, OSD_FUNC_WIDTH - 5, 6);
    }
    OSDAPI_OSDWinOn(OSD_WINDOW2);
}
#endif

void OSDShowBFMenu(void)
{
    UCHAR i;
    OSDWinAttr attr;

    ucMenuType = OSD_BF_MENU;
    
    OSDInitialize(FALSE);
    OSDInitFrame(OSD_BF_WIDTH, OSD_BF_HEIGHT, BF_MENU_COLOR);
    OSDAPI_SetPosition(50, 2);

    OSDAPI_FillLineAttr(0,0,OSD_BF_WIDTH, TITLE_COLOR);
    OSDAPI_FillLineAttr(0,1,OSD_BF_WIDTH, TITLE_COLOR);
    OSDAPI_FillLineAttr(0,2,OSD_BF_WIDTH, TITLE_COLOR);

    OSDAPI_SelOSDWin(OSD_WINDOW7);
    RST_WINATTR_ALL(attr);
    attr.ucWinClr = I_TGREEN;
    OSDAPI_SetOSDWinAttr(attr);
    OSDAPI_SetOSDWinSize(0, 0, OSD_BF_WIDTH-1, 2);
    OSDAPI_SetOSDWinGrad(0x00, 0x00, 0x02, 0x01);

    OSDAPI_SelOSDWin(OSD_WINDOW6);
    attr.ucWinClr = I_WHITE;
    OSDAPI_SetOSDWinAttr(attr);
    OSDAPI_SetOSDWinSize(0, 3, OSD_BF_WIDTH-1, OSD_BF_HEIGHT);
    OSDAPI_SetOSDWinGrad(0x00, 0x01, 0x01, 0x01);

    OSDAPI_OSDWinOn(OSD_WINDOW7);
    OSDAPI_OSDWinOn(OSD_WINDOW6);

    OSDAPI_SetIndentIndex(32);
    OSDAPI_SetAlignType(OSD_ALIGN_CENTER);    

    OSDAPI_ShowIndentString(FALSE, 0, 1, OSD_BF_WIDTH,
                            BFStrTab[UserData.ucLanguage]);

    OSDAPI_SetAlignType(OSD_ALIGN_LEFT);

    for(i=0; i<NUMBER_CE_MODES; i++) {
        OSDAPI_ShowIndentString(FALSE, 3, i*2+4, OSD_BF_WIDTH,
                                LTMItemStrTab[UserData.ucLanguage*NUMBER_CE_MODES+i]);
    }
    
    OSDAPI_SelOSDWin(OSD_WINDOW2);
    RST_WINATTR_ALL(attr);
    attr.ucWinClr = I_WHITE;
    SET_WINATTR_BEVEL(attr);
    SET_BEVEL_TYPE(attr,0);
    SET_BEVEL_WIDTH(attr,1);
    attr.ucRBorderClr = I_MAGENTA;
    attr.ucLBorderClr = I_MAGENTA;
    OSDAPI_SetOSDWinAttr(attr);
    OSDAPI_SetOSDWinSize(0, UserData.ucBFMode * 2 + 4, OSD_BF_WIDTH - 1, UserData.ucBFMode * 2 + 4);
    OSDAPI_OSDWinOn(OSD_WINDOW2);

    OSDTurnOnOSD();
}

void OSDShowSourceMenu(void)
{
    UCHAR i,j,len = CheckTotalPortNum();
    OSDWinAttr attr;

    ucMenuType = OSD_SRC_MENU;
    
    OSDInitialize(FALSE);
    OSDInitFrame(OSD_SRC_WIDTH, OSD_SRC_HEIGHT, SRC_MENU_COLOR);
    OSDAPI_SetPosition(50, 2);

    OSDAPI_FillLineAttr(0,0,OSD_SRC_WIDTH, TITLE_COLOR);
    OSDAPI_FillLineAttr(0,1,OSD_SRC_WIDTH, TITLE_COLOR);
    OSDAPI_FillLineAttr(0,2,OSD_SRC_WIDTH, TITLE_COLOR);

    OSDAPI_SelOSDWin(OSD_WINDOW7);
    RST_WINATTR_ALL(attr);
    attr.ucWinClr = I_TGREEN;
    OSDAPI_SetOSDWinAttr(attr);
    OSDAPI_SetOSDWinSize(0, 0, OSD_SRC_WIDTH-1, 2);
    OSDAPI_SetOSDWinGrad(0x00, 0x00, 0x02, 0x01);

    OSDAPI_SelOSDWin(OSD_WINDOW6);
    RST_WINATTR_ALL(attr);
    attr.ucWinClr = I_WHITE;
    OSDAPI_SetOSDWinAttr(attr);
    OSDAPI_SetOSDWinSize(0, 3, OSD_SRC_WIDTH-1, OSD_SRC_HEIGHT);
    OSDAPI_SetOSDWinGrad(0x00, 0x01, 0x01, 0x01);

    OSDAPI_OSDWinOn(OSD_WINDOW7);
    OSDAPI_OSDWinOn(OSD_WINDOW6);

    OSDAPI_SetIndentIndex(32);
    OSDAPI_SetAlignType(OSD_ALIGN_CENTER);    

    OSDAPI_ShowIndentString(FALSE, 0, 1, OSD_SRC_WIDTH,
                            InputStrTab[UserData.ucLanguage]);

    for (i=0,j=0; i<len; i++,j+=2 ) {
       OSDAPI_ShowIndentString(FALSE,0,4+j,OSD_SRC_WIDTH,SourceStrTab[UserData.ucLanguage+GetInputPortName(i)*NUM_OSDLANGS]);
    }
    OSDAPI_SelOSDWin(OSD_WINDOW2);
    RST_WINATTR_ALL(attr);
    attr.ucWinClr = I_WHITE;
    SET_WINATTR_BEVEL(attr);
    SET_BEVEL_TYPE(attr,0);
    SET_BEVEL_WIDTH(attr,1);
    attr.ucRBorderClr = I_MAGENTA;
    attr.ucLBorderClr = I_MAGENTA;
    OSDAPI_SetOSDWinAttr(attr);
    OSDAPI_SetOSDWinSize(0, GetInputPortIndex(UserData.ucInputSource) * 2 + 4, OSD_SRC_WIDTH - 1, GetInputPortIndex(UserData.ucInputSource) * 2 + 4);
    OSDAPI_OSDWinOn(OSD_WINDOW2);

    OSDTurnOnOSD();
}

void OSDUpdateAutoTuneBar(UCHAR percentage)
{
    if (ucMenuType == OSD_DLG_AUTOTUNE) {
        OSDShowSliderBar(4, 4, percentage);
    }
}

//******************************************************************************
// Prototype: 
//  void OSDPerformAuto(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Perform auto tune
// Notes:
//  None
//******************************************************************************
void OSDPerformAuto(void)
{
#if AutoTune_Debug == ENABLE
printf("OSDPerformAuto_S\n");	//150526 george
#endif

    if (GetInputSyncMode() != DIG_SYNC) {
        OSDShowDialog(OSD_DLG_AUTOTUNE);
        OSDUpdateAutoTuneBar(0);
        UserPerformAutoTune();
        if (InputTiming.ucAutoTune != 0) {
            SetOSDUpdTmgFlag();
        }
    }
    OSDClosed();

#if AutoTune_Debug == ENABLE
printf("OSDPerformAuto_E\n");	//150526 george
#endif
}

//******************************************************************************
// Prototype: 
//  
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
void OSDPerformNormal(void)
{
#if OSD_Debug == ENABLE
	printf("OSDPerformNormal_S\n");		//150526 george
#endif

    if (UserData.ucInputSource != UserGetInputSource()) {
        UserData.ucInputSource = UserGetInputSource();	
        SetOSDUpdUsrFlag();
    }
    
    if ((GetInputSyncMode() != DIG_SYNC) && (InputTiming.ucAutoTune == 0))		//1150526 george-mark: AutoTune-Flag.
    {
        OSDShowDialog(OSD_DLG_AUTOTUNE);
        UserPerformAutoTune();
        OSDClosed();
        if (InputTiming.ucAutoTune != 0) {	//150526 george-mark: AutoTune-OK!!
            // Save timing data immediately for fitting some customer requirements.
            //SetOSDUpdTmgFlag();
            NvramWriteTimingData(&InputTiming);
        }
    }
    OSDShowDialog(OSD_DLG_NOTICE);	

#if OSD_Debug == ENABLE
	printf("OSDPerformNormal_E\n");		//150526 george
#endif
}

//******************************************************************************
// Prototype: 
//  void OSDShowDir1(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Show direct OSD
// Notes:
//  None
//******************************************************************************
void OSDShowDir1(void)
{	

#if ALS_EnDis == ALSMODE
	OSDShowDialog(OSD_DLG_BRIGHTNESS);

#elif ALS_EnDis == ALSOffSET	
	if( UserData.bALSOnOff == OFF )
    	OSDShowDialog(OSD_DLG_BRIGHTNESS);
	else
		OSDShowDialog(OSD_DLG_ALS_BASE_VALUE);	//george: F_ALSBV_04F

#elif ALS_EnDis == ALSRange
	OSDShowDialog(OSD_DLG_BRIGHTNESS);

#else	//Normal

	#ifdef TRULY_TFT1280120
		OSDShowDialog(OSD_DLG_BRIGHTNESS);
		OSDShowResolution(5,3);	//george 15,14);
	#else 	//Normal
		OSDShowDialog(OSD_DLG_BRIGHTNESS);
	#endif


#endif	//#if ALS_EnDis == ENABLE

}

//******************************************************************************
// Prototype: 
//  void OSDShowDir2(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Show direct OSD
// Notes:
//  None
//******************************************************************************
void OSDShowDir2(void)
{
    OSDShowDialog(OSD_DLG_CONTRAST);
}

//******************************************************************************
// Prototype: 
//  void OSDShowDir3(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Show direct OSD
// Notes:
//  None
//******************************************************************************
void OSDShowDir3(void)
{
    OSDShowDialog(OSD_DLG_VOLUME);
}


#if ALS_EnDis == ALSMODE

#elif ALS_EnDis == ALSOffSET	//don't know used where ~
//	void OSDShowDir4(void)					// george: F_ALSBV_03B1
//	{
//	    OSDShowDialog(OSD_DLG_ALS_BASE_VALUE);
//	}
#else	//Normal

#endif	//#if ALS_EnDis == ENABLE

//******************************************************************************
// Prototype: 
//  void OSDCloseDir(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Close direct OSD
// Notes:
//  None
//******************************************************************************
void OSDCloseDir(void)
{
    OSDClosed();
}

void OSDShowOpt1(void)
{
    OSDShowBFMenu();
}

void OSDCloseOpt1(void)
{
    OSDClosed();
}

void OSDShowOpt2(void)
{
    OSDShowSourceMenu();
}

void OSDCloseOpt2(void)
{
    OSDClosed();
}

void OSDShowNoSync(void)
{
    // Turn on LVDS first to avoid dead lock in clear OSD
    PanelPowerOnSequence(FALSE);

#if ENABLE_OSD_ROTATION == ON
    if (UserData.bOSDRotation) {
        usOSDMovingX = MAX_ROT_X / 2;
        usOSDMovingY = 0x8000 + MAX_ROT_Y / 2;
    }
    else {
        usOSDMovingX = MAX_X / 2;
        usOSDMovingY = MAX_Y / 2;
    }
#else
    usOSDMovingX = MAX_X / 2;
    usOSDMovingY = MAX_Y / 2; 
#endif

    SetPostBGColor(0x00, 0x00, 0x00);
    OSDShowDialog(OSD_DLG_NOSYNC);
}


void OSDShowNoCable(void)
{
    // Turn on LVDS first to avoid dead lock in clear OSD
    PanelPowerOnSequence(FALSE);

#if ENABLE_OSD_ROTATION == ON
    if (UserData.bOSDRotation) {
        usOSDMovingX = MAX_ROT_X / 2;
        usOSDMovingY = 0x8000+ MAX_ROT_Y / 2;
    }
    else {
        usOSDMovingX = MAX_X / 2;
        usOSDMovingY = MAX_Y / 2;
    }
#else
    usOSDMovingX = MAX_X / 2;
    usOSDMovingY = MAX_Y / 2;  
#endif
    
    SetPostBGColor(0x00, 0x00, 0x00);
    if (SystemData.bFactory)         //fefanjacky
//    if (SystemData.bDemo) //BURN IN MODE
    {        
		#if BurnIn_Degub == ENABLE
			printf("DD-1\n");
		#endif
    	OSDShowDialog(OSD_DLG_BURNIN);
    }
//    else 
//    {
//		#if BurnIn_Degub == ENABLE
//			printf("CC-1\n");
//		#endif
//        OSDShowDialog(OSD_DLG_NOCABLE);
//
//    }
//--------------------------------------------------------------------------
}

void OSDShowOOL(void)
{
#if OSD_Debug == ENABLE
	printf("OSDShowOOL_S\n");	//150527 george
#endif

    if (UserData.ucInputSource != UserGetInputSource()) 
	{
          UserData.ucInputSource = UserGetInputSource();
          SetOSDUpdUsrFlag();
        }

    if ((GetInputSyncMode() != DIG_SYNC) && (InputTiming.ucAutoTune == 0))
    {
        OSDShowDialog(OSD_DLG_AUTOTUNE);
        UserPerformAutoTune();
        OSDClosed();
        if (InputTiming.ucAutoTune != 0) 
	    {
             SetOSDUpdTmgFlag();
           }
    }

    OSDShowDialog(OSD_DLG_85Hz);

#if OSD_Debug == ENABLE
	printf("OSDShowOOL_E\n");	//150527 george
#endif
}

void OSDShowOOR(void)
{
    // Turn on LVDS first to avoid dead lock in clear OSD
    PanelPowerOnSequence(FALSE);

#if ENABLE_OSD_ROTATION == ON
    if (UserData.bOSDRotation) 
	{
         usOSDMovingX = MAX_ROT_X / 2;
         usOSDMovingY = 0x8000 + MAX_ROT_Y / 2;
        }
    else 
	 {
          usOSDMovingX = MAX_X / 2;
          usOSDMovingY = MAX_Y / 2;
        }
#else
    usOSDMovingX = MAX_X / 2;
    usOSDMovingY = MAX_Y / 2;      
#endif
    
    OSDShowDialog(OSD_DLG_OUTOFRANGE);
}

//******************************************************************************
// Prototype: 
//  Please refer to the following
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  The following are for OSD up/down operations
// Notes:
//  None
//******************************************************************************
void OSDBrightnessUp(void)
{

#if ALS_EnDis == ALSMODE
	if(UserData.ucALSMode==ALS_OFF) {						// Split ucALSMode=OFF, =Indoor/Outdoor staturation.
	    UserData.ucBrightness++;
	    if (UserData.ucBrightness > MAXIMUM_BRIGHTNESS)
	        UserData.ucBrightness  = MAXIMUM_BRIGHTNESS;
	    else {
	        OSDShowBrightness(FALSE);
	        UserSetBrightness();
	    }
		SetOSDUpdUsrFlag();
	}

#elif ALS_EnDis == ALSOffSET	
	if(UserData.bALSOnOff == ON)		//george: F_ALSBV_04C
	{
		OSDALSBVUp();					
	}
	else
	{
	    UserData.ucBrightness++;
	    if (UserData.ucBrightness > MAXIMUM_BRIGHTNESS)
	        UserData.ucBrightness  = MAXIMUM_BRIGHTNESS;
	    else {
	        OSDShowBrightness(FALSE);
	        UserSetBrightness();
	    }
		SetOSDUpdUsrFlag();
	}

#elif ALS_EnDis == ALSRange
	if(UserData.bALSOnOff==OFF) {						// Split ucALSMode=OFF, =Indoor/Outdoor staturation.
	    UserData.ucBrightness++;
	    if (UserData.ucBrightness > MAXIMUM_BRIGHTNESS)
	        UserData.ucBrightness  = MAXIMUM_BRIGHTNESS;
	    else {
	        OSDShowBrightness(FALSE);
	        UserSetBrightness();
	    }
		SetOSDUpdUsrFlag();
	}

#else	//Normal
	    UserData.ucBrightness++;
	    if (UserData.ucBrightness > MAXIMUM_BRIGHTNESS)
	        UserData.ucBrightness  = MAXIMUM_BRIGHTNESS;
	    else {
	        OSDShowBrightness(FALSE);
	        UserSetBrightness();
	    }
		SetOSDUpdUsrFlag();
#endif	//#if ALS_EnDis == ENABLE

}


void OSDBrightnessDown(void)
{
#if ALS_EnDis == ALSMODE
	if(UserData.ucALSMode==ALS_OFF) {						// Split ucALSMode=OFF, =Indoor/Outdoor staturation.
	    UserData.ucBrightness--;
	    if ((UserData.ucBrightness > MAXIMUM_BRIGHTNESS) ||
	        (UserData.ucBrightness < MINIMUM_BRIGHTNESS))
	        UserData.ucBrightness  = MINIMUM_BRIGHTNESS;
	    else {
	        OSDShowBrightness(FALSE);
	        UserSetBrightness();
	    }
	    SetOSDUpdUsrFlag();
	}

#elif ALS_EnDis == ALSOffSET	
	if(UserData.bALSOnOff == ON)		//george: F_ALSBV_04D
	{
		OSDALSBVDown();  
	}
	else
	{
	    UserData.ucBrightness--;
	    if ((UserData.ucBrightness > MAXIMUM_BRIGHTNESS) ||
	        (UserData.ucBrightness < MINIMUM_BRIGHTNESS))
	        UserData.ucBrightness  = MINIMUM_BRIGHTNESS;
	    else {
	        OSDShowBrightness(FALSE);
	        UserSetBrightness();
	    }
	    SetOSDUpdUsrFlag();
	}

#elif ALS_EnDis == ALSRange
	if(UserData.bALSOnOff==OFF) {						// Split ucALSMode=OFF, =Indoor/Outdoor staturation.
	    UserData.ucBrightness--;
	    if ((UserData.ucBrightness > MAXIMUM_BRIGHTNESS) ||
	        (UserData.ucBrightness < MINIMUM_BRIGHTNESS))
	        UserData.ucBrightness  = MINIMUM_BRIGHTNESS;
	    else {
	        OSDShowBrightness(FALSE);
	        UserSetBrightness();
	    }
	    SetOSDUpdUsrFlag();
	}

#else	//Normal
	    UserData.ucBrightness--;
	    if ((UserData.ucBrightness > MAXIMUM_BRIGHTNESS) ||
	        (UserData.ucBrightness < MINIMUM_BRIGHTNESS))
	        UserData.ucBrightness  = MINIMUM_BRIGHTNESS;
	    else {
	        OSDShowBrightness(FALSE);
	        UserSetBrightness();
	    }
	    SetOSDUpdUsrFlag();
#endif	//#if ALS_EnDis == ENABLE
}


void OSDContrastUp(void)
{
    UserData.ucContrast++;
    if (UserData.ucContrast > MAXIMUM_CONTRAST)
        UserData.ucContrast  = MAXIMUM_CONTRAST;
    else {
        OSDShowContrast(FALSE);
        UserSetContrast();
    }
    SetOSDUpdUsrFlag();
}

void OSDContrastDown(void)
{
    UserData.ucContrast--;
    if ((UserData.ucContrast > MAXIMUM_CONTRAST) ||
        (UserData.ucContrast < MINIMUM_CONTRAST))
        UserData.ucContrast  = MINIMUM_CONTRAST;
    else {
        OSDShowContrast(FALSE);
        UserSetContrast();
    }
    SetOSDUpdUsrFlag();
}

void OSDVolumeUp(void)
{
    UserData.ucVolume++;
    if (UserData.ucVolume > MAXIMUM_VOLUME)
        UserData.ucVolume  = MAXIMUM_VOLUME;
    else {
        OSDShowVolume(FALSE);
        UserSetVolume();
    }
    SetOSDUpdUsrFlag();
}

void OSDVolumeDown(void)
{
    UserData.ucVolume--;
    if ((UserData.ucVolume > MAXIMUM_VOLUME) ||
        (UserData.ucVolume < MINIMUM_VOLUME))
        UserData.ucVolume  = MINIMUM_VOLUME;
    else {
        OSDShowVolume(FALSE);
        UserSetVolume();
    }
    SetOSDUpdUsrFlag();
}

//void OSDGammaUp(void)						//+++++++++++++++++++++++++++++++++++++++++++++++++
//{
//    UserData.bGammaOnOff = ~UserData.bGammaOnOff;
//    OSDShowGamma(FALSE);
//    UserSetGamma();
//    SetOSDUpdUsrFlag();
//}
//
//void OSDGammaDown(void)
//{
//    UserData.bGammaOnOff = ~UserData.bGammaOnOff;
//    OSDShowGamma(FALSE);
//    UserSetGamma();
//    SetOSDUpdUsrFlag();
//}




#if ALS_EnDis == ALSMODE
	//method(1) ALS Mode Select
	void OSDALSModeDown(void)
	{
	    UserData.ucALSMode =
	        (UserData.ucALSMode+1) % NUM_ALS_MODE;		//ref.  about: NUM_SR_MODE,  => static code SRBlock SRModes[NUM_SR_MODE]= {
	    OSDShowALSMode(FALSE);
		
	    UserSetALSMode();		//ref. void UserSetSR(void)		=> SetSRMode(UserData.ucSRMode);
	    SetOSDUpdUsrFlag();
	}
	
	void OSDALSModeUp(void)
	{
	    UserData.ucALSMode =
	        (UserData.ucALSMode + NUM_ALS_MODE-1) % NUM_ALS_MODE;		//ref.  about: NUM_SR_MODE,  => static code SRBlock SRModes[NUM_SR_MODE]= {
	    OSDShowALSMode(FALSE);
	    UserSetALSMode();		//ref. void UserSetSR(void)		=> SetSRMode(UserData.ucSRMode);
	    SetOSDUpdUsrFlag();
	}

#elif ALS_EnDis == ALSOffSET	
	void OSDALSOnOffUp(void)				// george: F_ALSOnOff_04C
	{
		UserData.bALSOnOff = ~UserData.bALSOnOff;
	    OSDShowALSOnOff(FALSE);
	    UserSetALSOnOff();
	    SetOSDUpdUsrFlag();
	
		if(UserData.bALSOnOff == ON)		//george: F_ALSBV_04C
		{
			CM3218_ALSOnInit();		//george: F_CM3218_02
	//		UserSetALSBaseVal();
		}else
			UserSetBrightness();	
	}
	
	void OSDALSOnOffDown(void)				// george: F_ALSOnOff_04D
	{
		UserData.bALSOnOff = ~UserData.bALSOnOff;
	    OSDShowALSOnOff(FALSE);
	    UserSetALSOnOff();
	    SetOSDUpdUsrFlag();
	
		if(UserData.bALSOnOff == ON)		//george: F_ALSBV_04C
		{
			CM3218_ALSOnInit();		//george: F_CM3218_02
	//		UserSetALSBaseVal();
		}else
			UserSetBrightness();
	}

	//method(2) ALS Base Value Modify.
	void OSDALSBVUp(void)								//george: F_ALSBV_04C
	{
	    //UserData.ucALSBaseVal++;
		UserData.ucALSBaseVal = UserData.ucALSBaseVal+DIVBASE;
	    if (UserData.ucALSBaseVal > MAXIMUM_ALSBV)		//george: F_ALSBV_04C1 -> MAXIMUM_ALSBV
	        UserData.ucALSBaseVal  = MAXIMUM_ALSBV;
	    else {
	        OSDShowALSBV(FALSE);
	// don't do this.        UserSetALSBaseVal();
	    }
	    SetOSDUpdUsrFlag();
	}
	
	void OSDALSBVDown(void)								//george: F_ALSBV_04D
	{
	    //UserData.ucALSBaseVal--;
		UserData.ucALSBaseVal = UserData.ucALSBaseVal-DIVBASE;
	    if ((UserData.ucALSBaseVal > MAXIMUM_ALSBV) ||
	        (UserData.ucALSBaseVal < MINIMUM_ALSBV))	//george: F_ALSBV_04D1 -> MINIMUM_ALSBV
	        UserData.ucALSBaseVal  = MINIMUM_ALSBV;
	    else {
	        OSDShowALSBV(FALSE);
	//don't do this.        UserSetALSBaseVal();
	    }
	    SetOSDUpdUsrFlag();
	}

#elif ALS_EnDis == ALSRange
	void OSDALSOnOffUp(void)				// george: F_ALSOnOff_04C
	{
		UserData.bALSOnOff = ~UserData.bALSOnOff;
	    OSDShowALSOnOff(FALSE);
	    UserSetALSOnOff();
	    SetOSDUpdUsrFlag();
	
		if(UserData.bALSOnOff == ON)		//george: F_ALSBV_04C
		{
			LS3101_ALSOnInit();		//george: F_CM3218_02

		}else
			UserSetBrightness();	
	}
	
	void OSDALSOnOffDown(void)				// george: F_ALSOnOff_04D
	{
		UserData.bALSOnOff = ~UserData.bALSOnOff;
	    OSDShowALSOnOff(FALSE);
	    UserSetALSOnOff();
	    SetOSDUpdUsrFlag();
	
		if(UserData.bALSOnOff == ON)		//george: F_ALSBV_04C
		{
			LS3101_ALSOnInit();		//george: F_CM3218_02

		}else
			UserSetBrightness();
	}
#else	//Normal

#endif	//#if ALS_EnDis == ENABLE



#if TOUCH_EnDis == ENABLE
	void OSDTouchUp(void)						//george: F_Touch_04C  +++++++++++++++++ OSDTouch-UP/Down  ++++++++++++++++++++++++++++++++
	{
	    UserData.bTouchOnOff = ~UserData.bTouchOnOff;
	    OSDShowTouch(FALSE);
	    UserSetTouch();
	    SetOSDUpdUsrFlag();
	}
	
	void OSDTouchDown(void)						//george: F_Touch_04D
	{
	    UserData.bTouchOnOff = ~UserData.bTouchOnOff;
	    OSDShowTouch(FALSE);
	    UserSetTouch();
	    SetOSDUpdUsrFlag();
	}
#endif //#if TOUCH_EnDis == ENABLE




/*

void OSDGItem17Up(void)							// george_Item17
{
    //UserData.bTouchOnOff = ~UserData.bTouchOnOff;
    OSDShowTouch(FALSE);
    UserSetTouch();
    SetOSDUpdUsrFlag();
}

void OSDGItem17Down(void)						// george_Item17
{
    //UserData.bTouchOnOff = ~UserData.bTouchOnOff;
    OSDShowTouch(FALSE);
    //UserSetTouch();
    SetOSDUpdUsrFlag();
}
*/


//void OSDDCRUp(void)
//{
//     if(UserData.ucDCRMode == BKL_CTRL_OFF) {
//		UserData.ucDCRMode = BKL_CTRL_DBC;
//     }
//    else {
//    	UserData.ucDCRMode = (UserData.ucDCRMode-1)%NUM_BKL_CTRL_SIZE;
//    }
//    OSDShowDCR(FALSE);
//    UserSetDCR();
//    SetOSDUpdUsrFlag();
//}
//
//void OSDDCRDown(void)
//{
//    UserData.ucDCRMode=
//        (UserData.ucDCRMode+1)%NUM_BKL_CTRL_SIZE;
//    OSDShowDCR(FALSE);
//    UserSetDCR();
//    SetOSDUpdUsrFlag();
//}

void OSDSRDown(void)
{
#if ENABLE_SR == ON
    UserData.ucSRMode =
        (UserData.ucSRMode+1)%NUM_SR_MODE;
    OSDShowSR(FALSE);
    UserSetSR();
    SetOSDUpdUsrFlag();
#endif
}

void OSDSRUp(void)
{
#if ENABLE_SR == ON
    UserData.ucSRMode =
        (UserData.ucSRMode+NUM_SR_MODE-1) % NUM_SR_MODE;
    OSDShowSR(FALSE);
    UserSetSR();
    SetOSDUpdUsrFlag();
#endif
}

void OSDPhaseUp(void)
{
    InputTiming.ucPhase++;
    if (InputTiming.ucPhase > MAXIMUM_PHASE)
        InputTiming.ucPhase  = MAXIMUM_PHASE;
    else {
        UserSetPhase();
        OSDShowPhase(FALSE);        
    }
    SetOSDUpdTmgFlag();
}

void OSDPhaseDown(void)
{
    InputTiming.ucPhase--;
    if ((InputTiming.ucPhase > MAXIMUM_PHASE) ||
        (InputTiming.ucPhase < MINIMUM_PHASE))
        InputTiming.ucPhase  = MINIMUM_PHASE;
    else {
        UserSetPhase();
        OSDShowPhase(FALSE);
    }
    SetOSDUpdTmgFlag();
}

void OSDClockUp(void)
{
    InputTiming.usHTotal++;
    if (InputTiming.usHTotal > InputTiming.usHTotalMax)
        InputTiming.usHTotal  = InputTiming.usHTotalMax;
    else {
        OSDShowClock(FALSE);
        UserSetClock();
    }
    SetOSDUpdTmgFlag();
}

void OSDClockDown(void)
{
    InputTiming.usHTotal--;
    if (InputTiming.usHTotal < InputTiming.usHTotalMin)
        InputTiming.usHTotal  = InputTiming.usHTotalMin;
    else {
        OSDShowClock(FALSE);
        UserSetClock();
    }
    SetOSDUpdTmgFlag();
}

void OSDHPositionUp(void)
{
    InputTiming.usHStart++;
    if (InputTiming.usHStart > InputTiming.usHStartMax)
        InputTiming.usHStart  = InputTiming.usHStartMax;
    else {
        OSDShowHPos(FALSE);
        UserSetHPosition();
    }
    SetOSDUpdTmgFlag();
}

void OSDHPositionDown(void)
{
    InputTiming.usHStart--;
    if ((InputTiming.usHStart > InputTiming.usHStartMax) ||
        (InputTiming.usHStart < InputTiming.usHStartMin))
        InputTiming.usHStart  = InputTiming.usHStartMin;
    else {
        OSDShowHPos(FALSE);
        UserSetHPosition();
    }
    SetOSDUpdTmgFlag();
}

void OSDVPositionUp(void)
{
    InputTiming.usVStart++;
    if (InputTiming.usVStart > InputTiming.usVStartMax)
        InputTiming.usVStart  = InputTiming.usVStartMax;
    else {
        UserSetVPosition();
        OSDShowVPos(FALSE);
    }
    SetOSDUpdTmgFlag();
}

void OSDVPositionDown(void)
{
    InputTiming.usVStart--;
    if ((InputTiming.usVStart > InputTiming.usVStartMax) ||
        (InputTiming.usVStart < InputTiming.usVStartMin))
        InputTiming.usVStart  = InputTiming.usVStartMin;
    else {
        UserSetVPosition();
        OSDShowVPos(FALSE);
    }
    SetOSDUpdTmgFlag();
}

void OSDColorTempUp(void)
{
 #ifdef colortemp 			               			//140509 mike           
   printf("140508 OSDColorTempUp\n\r");		//140421 mike	
   #endif
    UserData.ucColorTemp++;
   
        //---------------------------------------------------
	if (UserData.ucColorTemp > MAXIMUM_CLR_TEMP)
    {
		UserData.ucColorTemp  = MINIMUM_CLR_TEMP;
	}	
    
     OSDShowClrTmp(FALSE);
     UserSetColorTemp();
	 SetOSDUpdUsrFlag();
}

void OSDColorTempDown(void)
{
 #ifdef colortemp 			               			//140509 mike           
    printf("140508 OSDColorTempDown\n\r");		//140421 mike	
 #endif   
    UserData.ucColorTemp--;
   
    if ((UserData.ucColorTemp > MAXIMUM_CLR_TEMP) || (UserData.ucColorTemp < MINIMUM_CLR_TEMP))
	{
		UserData.ucColorTemp  = MAXIMUM_CLR_TEMP;
	}
          OSDShowClrTmp(FALSE);
          UserSetColorTemp();
          SetOSDUpdUsrFlag();
}
//---------------------------
void OSDRGainUp(void)
{
 #ifdef colortemp 			               			//140509 mike           
       printf("140509 OSDUpItm32\n\r");		//140509 mike	
 #endif      
    UserData.ucUserRGain++;
    if (UserData.ucUserRGain > MAXIMUM_USER_RGAIN)
        UserData.ucUserRGain  = MAXIMUM_USER_RGAIN;
    else 
	{
    	OSDShowRGain(FALSE);
    	UserSetRGain();
	}
    	SetOSDUpdUsrFlag();
}
//----------------------------
void OSDRGainDown(void)
{
 #ifdef colortemp 			               			//140509 mike           
        printf("140509 OSDDownItm32\n\r");		//140509 mike	
 #endif      
    UserData.ucUserRGain--;
    if ((UserData.ucUserRGain > MAXIMUM_USER_RGAIN) ||(UserData.ucUserRGain < MINIMUM_USER_RGAIN))
        UserData.ucUserRGain  = MINIMUM_USER_RGAIN;
    else 
	{
    	OSDShowRGain(FALSE);
    	UserSetRGain();
	}
   		SetOSDUpdUsrFlag();
}
//---------------------------
void OSDGGainUp(void)
{
 #ifdef colortemp 			               			//140509 mike           
        printf("140509 OSDUpItm33\n\r");		//140509 mike	
 #endif       
    UserData.ucUserGGain++;
    if (UserData.ucUserGGain > MAXIMUM_USER_GGAIN)
        UserData.ucUserGGain  = MAXIMUM_USER_GGAIN;
    else 
	{
    	OSDShowGGain(FALSE);
    	UserSetGGain();
   	}
   		SetOSDUpdUsrFlag();
}
//---------------------------
void OSDGGainDown(void)
{
 #ifdef colortemp 			               			//140509 mike           
           printf("140509 OSDdownItm33\n\r");		//140509 mike	
 #endif          
    UserData.ucUserGGain--;
    if ((UserData.ucUserGGain > MAXIMUM_USER_GGAIN) ||(UserData.ucUserGGain < MINIMUM_USER_GGAIN))
        UserData.ucUserGGain  = MINIMUM_USER_GGAIN;
    else 
	{
    	OSDShowGGain(FALSE);
    	UserSetGGain();
    }
    	SetOSDUpdUsrFlag();
}
//--------------------------
void OSDBGainUp(void)
{
 #ifdef colortemp 			               			//140509 mike           
        printf("140509 OSDUpItm34\n\r");		//140509 mike	
 #endif       
    UserData.ucUserBGain++;
    if (UserData.ucUserBGain > MAXIMUM_USER_BGAIN)
        UserData.ucUserBGain  = MAXIMUM_USER_BGAIN;
    else 
	{
        OSDShowBGain(FALSE);
       	UserSetBGain();
    }
   		SetOSDUpdUsrFlag();
}
//-------------------------
void OSDBGainDown(void)
{
 #ifdef colortemp 			               			//140509 mike           
        printf("140509 OSDdownItm34\n\r");		//140509 mike	
 #endif       
    UserData.ucUserBGain--;
    if ((UserData.ucUserBGain > MAXIMUM_USER_BGAIN) ||(UserData.ucUserBGain < MINIMUM_USER_BGAIN))
        UserData.ucUserBGain  = MINIMUM_USER_BGAIN;
    else 
	{
       	OSDShowBGain(FALSE);
       	UserSetBGain();
   	}
   		SetOSDUpdUsrFlag();
}
//-------------------------
void OSDHUp(void)
{
    UserData.ucOSDX++;
    if (UserData.ucOSDX > MAXIMUM_OSD_HPOS)
        UserData.ucOSDX  = MAXIMUM_OSD_HPOS;
    else 
	  {
        	OSDShowOSDHPos(FALSE);
        	UserSetOSDH();
    	   }
    		SetOSDUpdUsrFlag();
}

void OSDHDown(void)
{
    UserData.ucOSDX--;
    if ((UserData.ucOSDX > MAXIMUM_OSD_HPOS) ||(UserData.ucOSDX < MINIMUM_OSD_HPOS))
        UserData.ucOSDX  = MINIMUM_OSD_HPOS;
    else 
	 {
        	OSDShowOSDHPos(FALSE);
        	UserSetOSDH();
    	   }
    		SetOSDUpdUsrFlag();
}

void OSDVUp(void)							//140520 mike
{
    UserData.ucOSDY++;
    if (UserData.ucOSDY > MAXIMUM_OSD_VPOS)
        UserData.ucOSDY  = MAXIMUM_OSD_VPOS;
    else 
	{
        	OSDShowOSDVPos(FALSE);
        	UserSetOSDV();
    	}
    		SetOSDUpdUsrFlag();
}

void OSDVDown(void)						//140520 mike
{
    UserData.ucOSDY--;
    if ((UserData.ucOSDY > MAXIMUM_OSD_VPOS) ||(UserData.ucOSDY < MINIMUM_OSD_VPOS))
        UserData.ucOSDY  = MINIMUM_OSD_VPOS;
    else 
	  {
           	OSDShowOSDVPos(FALSE);
           	UserSetOSDV();
          }
    		SetOSDUpdUsrFlag();
}

void OSDTransparentUp(void)
{
    UserData.ucOSDTransparent++;
    if (UserData.ucOSDTransparent > MAXIMUM_OSD_TRANS)
        UserData.ucOSDTransparent  = MAXIMUM_OSD_TRANS;
    else {
        OSDShowOSDTran(FALSE);
        UserSetTransparent();
    }
    SetOSDUpdUsrFlag();
}

void OSDTransparentDown(void)
{
    UserData.ucOSDTransparent--;
    if ((UserData.ucOSDTransparent > MAXIMUM_OSD_TRANS) ||
        (UserData.ucOSDTransparent < MINIMUM_OSD_TRANS))
        UserData.ucOSDTransparent  = MINIMUM_OSD_TRANS;
    else {
        OSDShowOSDTran(FALSE);
        UserSetTransparent();
    }    
    SetOSDUpdUsrFlag();
}

void OSDTimeoutUp(void)
{
    UserData.ucOSDTimer++;
    if (UserData.ucOSDTimer > MAXIMUM_OSD_TIMER)
        UserData.ucOSDTimer  = MAXIMUM_OSD_TIMER;
    else {
        OSDShowTimer(FALSE);
        UserSetTimeout();
    }
    SetOSDUpdUsrFlag();
}

void OSDTimeoutDown(void)
{
    UserData.ucOSDTimer--;
    if ((UserData.ucOSDTimer > MAXIMUM_OSD_TIMER) ||
        (UserData.ucOSDTimer < MINIMUM_OSD_TIMER))
        UserData.ucOSDTimer  = MINIMUM_OSD_TIMER;
    else {
        OSDShowTimer(FALSE);
        UserSetTimeout();
    }    
    SetOSDUpdUsrFlag();
}

//void OSDRotationUp(void)
//{
//    UserData.bOSDRotation = ~UserData.bOSDRotation;
//    OSDShowOSDRotation(FALSE);
//    SetOSDUpdUsrFlag();
//}
//
//void OSDRotationDown(void)
//{
//    UserData.bOSDRotation = ~UserData.bOSDRotation;
//    OSDShowOSDRotation(FALSE);
//    SetOSDUpdUsrFlag();
//}

void OSDLanguageUp(void)
{
    UserData.ucLanguage = 
        (UserData.ucLanguage+1) % NUM_OSDLANGS;
    OSDShowLang(FALSE);
    //UserSetLanguage();
    SetOSDUpdUsrFlag();
}

void OSDLanguageDown(void)
{
    UserData.ucLanguage = 
        (UserData.ucLanguage+NUM_OSDLANGS-1) % NUM_OSDLANGS;
    OSDShowLang(FALSE);
    SetOSDUpdUsrFlag();
}

void OSDAudioMuteUp(void)
{
    UserData.bAudioMute = ~UserData.bAudioMute;
    OSDShowMute(FALSE);
    UserSetAudioMute();
    SetOSDUpdUsrFlag();
}

void OSDAudioMuteDown(void)
{
    UserData.bAudioMute = ~UserData.bAudioMute;
    OSDShowMute(FALSE);
    UserSetAudioMute();
    SetOSDUpdUsrFlag();
}

void OSDInputSourceUp(void)
{
    UCHAR Index;

    Index = GetInputPortIndex(UserData.ucInputSource);

    if (GetInputPortName(++Index) >=  NUM_INPUT_SC) {
        Index = 0;
    }

    UserData.ucInputSource = GetInputPortName(Index);
    OSDShowInput(FALSE);

}

void OSDInputSourceDown(void)
{
    UCHAR Index;

    Index = GetInputPortIndex(UserData.ucInputSource);
    if (GetInputPortName(--Index) >= NUM_INPUT_SC) {
        Index = CheckTotalPortNum()-1;
    }

    UserData.ucInputSource = GetInputPortName(Index);
    OSDShowInput(FALSE);
    //UserSetInputSource();
}

#if ENABLE_ASPECT_RATIO == ON		//george 20160217
	void OSDAspectRatioUp(void)
	{
	    UserData.ucAspectRatio =
	        (UserData.ucAspectRatio+1)%NUM_DSP_SIZE;
	    OSDShowAspRatio(FALSE);
	    UserSetAspectRatio();
	    SetOSDUpdUsrFlag();
	}
	
	void OSDAspectRatioDown(void)
	{
	    UserData.ucAspectRatio =
	        (UserData.ucAspectRatio+NUM_DSP_SIZE-1)%NUM_DSP_SIZE;
	    OSDShowAspRatio(FALSE);
	    UserSetAspectRatio();
	    SetOSDUpdUsrFlag();
	}
#endif

//void OSDOverScanUp(void)
//{
//#if ENABLE_OVERSCAN == ON
//    UserData.bOverScan = ~UserData.bOverScan;
//    OSDShowOverScan(FALSE);
//    UserSetOverScan();
//    SetOSDUpdUsrFlag();
//#endif
//}
//
//void OSDOverScanDown(void)
//{								
//#if ENABLE_OVERSCAN == ON
//    UserData.bOverScan = ~UserData.bOverScan;
//    OSDShowOverScan(FALSE);
//    UserSetOverScan();
//    SetOSDUpdUsrFlag();
//#endif
//}

//void OSDODUp(void)
//{
//    UserData.ucODMode ^= BIT0;
//    OSDShowOD(FALSE);
//    UserSetOD();
//    SetOSDUpdUsrFlag();
//}
//
//void OSDODDown(void)
//{
//    UserData.ucODMode ^= BIT0;
//    OSDShowOD(FALSE);
//    UserSetOD();
//    SetOSDUpdUsrFlag();
//}

void OSDResetUp(void)
{
    ucPerformReset ^= BIT0;
    OSDShowReset(FALSE);
    //UserRecallConfiguration();
}

void OSDResetDown(void)
{
    ucPerformReset ^= BIT0;
    OSDShowReset(FALSE);
    //UserRecallConfiguration();
}

#if ENABLE_FUNC_OSD == ON
void OSD2Dto3DFmtDown(void)
{
    UserData.uc2DTo3DMode = (UserData.uc2DTo3DMode+NUM_THR_D_CNV-1) % NUM_THR_D_CNV;
    OSDShowThrDCnvMenu(FALSE);
    //SetOSDUpdUsrFlag();
}

void OSD2Dto3DFmtUp(void)
{
    UserData.uc2DTo3DMode = (UserData.uc2DTo3DMode+1) % NUM_THR_D_CNV;
    OSDShowThrDCnvMenu(FALSE);
    //SetOSDUpdUsrFlag();
}

void OSD2Dto3DAdptDown(void)
{
#if ENABLE_3D_CNV == ON
    if (Is2DTo3DAdaptive()) {
        TurnOff2DTo3DAdaptive();
    }
    else {
        TurnOn2DTo3DAdaptive();
    }
    OSDShow2Dto3DAdpt(FALSE);
    UserSet2DTo3DAdaptive();
    SetOSDUpdUsrFlag();
#else
    OSDShow2Dto3DAdpt(FALSE);
    SetOSDUpdUsrFlag();
#endif
}

void OSD2Dto3DAdptUp(void)
{
#if ENABLE_3D_CNV == ON
    if (Is2DTo3DAdaptive()) {
        TurnOff2DTo3DAdaptive();
    }
    else {
        TurnOn2DTo3DAdaptive();
    }
    OSDShow2Dto3DAdpt(FALSE);
    UserSet2DTo3DAdaptive();
    SetOSDUpdUsrFlag();
#else
    OSDShow2Dto3DAdpt(FALSE);
    SetOSDUpdUsrFlag();
#endif
}

void OSD2Dto3DDepthDown(void)
{
    UserData.uc2Dto3DDepth--;
    if ((UserData.uc2Dto3DDepth > MAXIMUM_2DTO3D_DEPTH) ||
        (UserData.uc2Dto3DDepth < MINIMUM_2DTO3D_DEPTH))
        UserData.uc2Dto3DDepth  = MINIMUM_2DTO3D_DEPTH;
    else {
        OSDShow2Dto3DDepth(FALSE);
#if ENABLE_3D_CNV == ON
        UserSet2DTo3DDepth();
#endif
    }    
    SetOSDUpdUsrFlag();
}

void OSD2Dto3DDepthUp(void)
{
    UserData.uc2Dto3DDepth++;
    if (UserData.uc2Dto3DDepth > MAXIMUM_2DTO3D_DEPTH)
        UserData.uc2Dto3DDepth  = MAXIMUM_2DTO3D_DEPTH;
    else {
        OSDShow2Dto3DDepth(FALSE);
#if ENABLE_3D_CNV == ON
        UserSet2DTo3DDepth();
#endif
    }    
    SetOSDUpdUsrFlag();
}

void OSD2Dto3DViewDown(void)
{
    UserData.uc2Dto3DView--;
    if ((UserData.uc2Dto3DView > MAXIMUM_2DTO3D_VIEW) ||
        (UserData.uc2Dto3DView < MINIMUM_2DTO3D_VIEW))
        UserData.uc2Dto3DView  = MINIMUM_2DTO3D_VIEW;
    else {
        OSDShow2Dto3DView(FALSE);
#if ENABLE_3D_CNV == ON
        UserSet2DTo3DView();
#endif
    }    
    SetOSDUpdUsrFlag();
}

void OSD2Dto3DViewUp(void)
{
    UserData.uc2Dto3DView++;
    if (UserData.uc2Dto3DView > MAXIMUM_2DTO3D_VIEW)
        UserData.uc2Dto3DView  = MAXIMUM_2DTO3D_VIEW;
    else {
        OSDShow2Dto3DView(FALSE);
#if ENABLE_3D_CNV == ON
        UserSet2DTo3DView();
#endif
    }    
    SetOSDUpdUsrFlag();
}

void OSD3DLRSwapDown(void)
{
#if ENABLE_SCALER_3D == ON
    if (Is3DLRSwap()) {
        TurnOff3DLRSwap();
    }
    else {
        TurnOn3DLRSwap();
    }
    OSDShow3DLRSwap(FALSE);
    UserSet3DLRSwap();
    SetOSDUpdUsrFlag();
#else
    OSDShow3DLRSwap(FALSE);
    SetOSDUpdUsrFlag();
#endif
}

void OSD3DLRSwapUp(void)
{
#if ENABLE_SCALER_3D == ON
    if (Is3DLRSwap()) {
        TurnOff3DLRSwap();
    }
    else {
        TurnOn3DLRSwap();
    }
    OSDShow3DLRSwap(FALSE);
    UserSet3DLRSwap();
    SetOSDUpdUsrFlag();
#else
    OSDShow3DLRSwap(FALSE);
    SetOSDUpdUsrFlag();
#endif
}

void OSD3DTo2DDown(void)
{
#if ENABLE_SCALER_3D == ON
    if (Is3DTo2DEnabled()) {
        TurnOff3DTo2D();
    }
    else {
        TurnOn3DTo2D();
    }
    OSDShow3DTo2D(FALSE);
    UserSet3DTo2D();
    SetOSDUpdUsrFlag();
#else
    OSDShow3DTo2D(FALSE);
    SetOSDUpdUsrFlag();
#endif
}

void OSD3DTo2DUp(void)
{
#if ENABLE_SCALER_3D == ON
    if (Is3DTo2DEnabled()) {
        TurnOff3DTo2D();
    }
    else {
        TurnOn3DTo2D();
    }
    OSDShow3DTo2D(FALSE);
    UserSet3DTo2D();
    SetOSDUpdUsrFlag();
#else
    OSDShow3DTo2D(FALSE);
    SetOSDUpdUsrFlag();
#endif
}
#endif

void OSDSourceMenuITMUp(void) 
{
    UCHAR Index;

    Index = GetInputPortIndex(UserData.ucInputSource);
    if (GetInputPortName(++Index) >=  NUM_INPUT_SC) {
        Index = 0;
    }

    UserData.ucInputSource = GetInputPortName(Index);

    OSDAPI_SelOSDWin(OSD_WINDOW2);
    OSDAPI_SetOSDWinSize(0, Index * 2 + 4, OSD_SRC_WIDTH - 1, Index * 2 + 4);
    OSDAPI_OSDWinOn(OSD_WINDOW2);
}
        
void OSDSourceMenuITMDn(void) 
{
    UCHAR Index;

    Index = GetInputPortIndex(UserData.ucInputSource);
    if (GetInputPortName(--Index) >= NUM_INPUT_SC) {
        Index = CheckTotalPortNum()-1;
    }

    UserData.ucInputSource = GetInputPortName(Index);

    OSDAPI_SelOSDWin(OSD_WINDOW2);
    OSDAPI_SetOSDWinSize(0, Index * 2 + 4, OSD_SRC_WIDTH - 1, Index * 2 + 4);
    OSDAPI_OSDWinOn(OSD_WINDOW2);
}

void OSDBFMenuITMUp(void) 
{
    UserData.ucBFMode =
        (UserData.ucBFMode+1)%NUMBER_CE_MODES;

    OSDAPI_SelOSDWin(OSD_WINDOW2);
    OSDAPI_SetOSDWinSize(0, UserData.ucBFMode * 2 + 4, OSD_BF_WIDTH - 1, UserData.ucBFMode * 2 + 4);
    OSDAPI_OSDWinOn(OSD_WINDOW2);
    
#if ENABLE_LD == ON
    UserSetLD();
#else
    UserSetBF();
#endif
    SetOSDUpdUsrFlag();
}

void OSDBFMenuITMDn(void) 
{
    UserData.ucBFMode =
        (UserData.ucBFMode+NUMBER_CE_MODES-1)%NUMBER_CE_MODES;

    OSDAPI_SelOSDWin(OSD_WINDOW2);
    OSDAPI_SetOSDWinSize(0, UserData.ucBFMode * 2 + 4, OSD_BF_WIDTH - 1, UserData.ucBFMode * 2 + 4);
    OSDAPI_OSDWinOn(OSD_WINDOW2);

#if ENABLE_LD == ON
    UserSetLD();
#else
    UserSetBF();
#endif
    SetOSDUpdUsrFlag();
}

//void OSDConfirmOSDRotation(void)
//{
//    OSDAPI_TurnOffOSD();
//    UserSetOSDRotation();
//    UserSetOSDH();
//    UserSetOSDV();
//    SetOSDUpdUsrFlag();
//}

void OSDConfirmLanguage(void)
{
    UserSetLanguage();
    SetOSDUpdUsrFlag();
}

void OSDConfirmInput(void)
{

#if ENABLE_ESD_PROTECT == ON
    BacklightOff();
#endif
    // Do not change the sequence of the following statements.
    //RecordCurrentSource(TRUE);
    UserSetInputSource();
    // XXX
    // Hot-fix to solve the issue of incorrect OSD state after turning off source menu under nosync/nocable state.
    // We will improve OSD arch. to overcome this issue.
    APPResendAppSync();
    SetOSDUpdUsrFlag();
}

void OSDConfirmRecall(void)
{
    if (ucPerformReset) 
	{
       	OSDClearSubmenu();
        	OSDAPI_SetAlignType(OSD_ALIGN_CENTER);
        	OSDAPI_SetIndentIndex(64);
        	OSDAPI_ShowIndentString(FALSE, 5, 8, OSD_SUB_WIDTH, 
                                WaitStrTab[UserData.ucLanguage]);

reserve_osd_inputsource = UserData.ucInputSource; //george
        	UserRecallConfiguration();
UserData.ucInputSource = reserve_osd_inputsource;  //george

        	SetOSDUpdUsrFlag();
        if ((GetInputSyncMode() != DIG_SYNC) && (InputTiming.ucAutoTune != 0)) 
        {
            SetOSDUpdTmgFlag();
        }
    }
    //OSDClosed();
}

#if ENABLE_FUNC_OSD == ON
void OSDConfirm3DCnvMode(void)
{
#if ENABLE_3D_CNV == ON
    UserSet2DTo3DMode();
#endif
    SetOSDUpdUsrFlag();
    SetModeChangeFlag();
}
#endif

