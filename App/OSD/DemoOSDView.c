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
enum OSD_DEMO {
    mdDFR,
    mdSR,
};

typedef struct _DLIGHTBAR_ {
    UCHAR x;
    UCHAR y;
    UCHAR len;
} DLightBar ;

//******************************************************************************
// G L O B A L   V A R I A B L E S
//******************************************************************************

//******************************************************************************
// S T A T I C   V A R I A B L E S
//******************************************************************************
static code UCHAR ucDFRText[]={3,"DFR"};	//DFR, Double Frame Rate
static code UCHAR ucSRText[]={2,"SR"};		//SR, SR Mode, (Super Resoulation 0xEA0) for video performance enhancement
static code UCHAR ucYesText[]={3,"YES"};
static code UCHAR ucNoText[]={2,"NO"};


code DLightBar DLBar[] = {
    {0, 4,7},
    {0, 5,7},
};
static xdata UCHAR ucDemoIndex;

#define dDFRAddress 0xF8
#define dSRAddress   dDFRAddress+3
//******************************************************************************
// E X T E R N A L   V A R I A B L E   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// S T A T I C   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
static void DemoSelect(void);
static void DemoUnSelect(void);
static void DemoShowDFR(void);
static void DemoShowSR(void);
static void DemoSelectValue(void);
static void DemoUnSelectValue(void);
static void DemoSetValue(void);

//******************************************************************************
// E X T E R N A L   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************



//******************************************************************************
// Prototype:
//  void OSDShowDemo(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Show Factory OSD
// Notes:
//  None
//******************************************************************************
void OSDShowDemo(void)
{
    OSDAPI_TurnOffOSD();
    OSDInitFrame(OSD_DEMO_W,OSD_DEMO_H,DEMO_FRAME_COLOR);
    OSDAPI_SetPosition(1,98);
    // ----------------------------------------

    OSDAPI_SetIndentIndex(32);
    OSDAPI_SetAlignType(OSD_ALIGN_LEFT);

    OSDAPI_ShowIndentString(FALSE, DLBar[mdDFR].x, DLBar[mdDFR].y,1,ucDFRText);
    OSDAPI_ShowIndentString(FALSE, DLBar[mdSR].x, DLBar[mdSR].y,1,ucSRText);	
    DemoShowDFR();
    DemoShowSR();
	
    DemoSelect();
    OSDTurnOnOSD();
}
//******************************************************************************
// Prototype:
//  void OSDDemoUp(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
void OSDDemoUp(void)
{
    DemoUnSelect();
    if(--ucDemoIndex > mdSR)
        ucDemoIndex = mdSR;
    DemoSelect();

}

//******************************************************************************
// Prototype:
//  void OSDDemoDown(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
void OSDDemoDown(void)
{
    DemoUnSelect();
    if(++ucDemoIndex > mdSR)
        ucDemoIndex = mdDFR;
    DemoSelect();


}
//******************************************************************************
// Prototype:
//  void DemoSelect(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
void DemoSelect(void)
{
    OSDAPI_FillLineAttr(DLBar[ucDemoIndex].x, DLBar[ucDemoIndex].y,
                        DLBar[ucDemoIndex].len,DEMO_ITEM_COLOR);
}
//******************************************************************************
// Prototype:
//  void DemoUnSelect(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
void DemoUnSelect(void)
{
    OSDAPI_FillLineAttr(DLBar[ucDemoIndex].x, DLBar[ucDemoIndex].y,
                        DLBar[ucDemoIndex].len,DEMO_FRAME_COLOR);
}
//******************************************************************************
// Prototype:
//  void DemoShowDFR(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
void DemoShowDFR(void)
{
    OSDAPI_SetIndentIndex(dDFRAddress);
    OSDAPI_SetAlignType(OSD_ALIGN_LEFT);
    if (SystemData.bDFR == 1)
        OSDAPI_ShowIndentString(FALSE, DLBar[mdDFR].x+8,DLBar[mdDFR].y, 3, ucYesText);
    else
        OSDAPI_ShowIndentString(FALSE,DLBar[mdDFR].x+8, DLBar[mdDFR].y, 3, ucNoText);
}
//******************************************************************************
// Prototype:
//  void DemoShowSR(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
void DemoShowSR(void)
{
    OSDAPI_SetIndentIndex(dSRAddress);
    OSDAPI_SetAlignType(OSD_ALIGN_LEFT);
    if (SystemData.bSR == 1)
        OSDAPI_ShowIndentString(FALSE, DLBar[mdSR].x+8,DLBar[mdSR].y, 3, ucYesText);
    else
        OSDAPI_ShowIndentString(FALSE,DLBar[mdSR].x+8, DLBar[mdSR].y, 3, ucNoText);
}
//******************************************************************************
// Prototype:
//  void OSDDemoEnterItm(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
void OSDDemoEnterItm(void)
{
        DemoUnSelect();
        DemoSelectValue();
}
//******************************************************************************
// Prototype:
//  void DemoSelectValue(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
void DemoSelectValue(void)
{
    if ((ucDemoIndex == mdDFR) || (ucDemoIndex == mdSR)) {
        OSDAPI_FillLineAttr(DLBar[ucDemoIndex].x+DLBar[ucDemoIndex].len,
                            DLBar[ucDemoIndex].y,
                            5, DEMO_ITEM_COLOR);
    }
}
//******************************************************************************
// Prototype:
//  void DemoUnSelectValue(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
void DemoUnSelectValue(void)
{
    if ((ucDemoIndex == mdDFR) || (ucDemoIndex == mdSR)) {
        OSDAPI_FillLineAttr(DLBar[ucDemoIndex].x+DLBar[ucDemoIndex].len,
                            DLBar[ucDemoIndex].y,
                            5, DEMO_FRAME_COLOR);
    }
}
//******************************************************************************
// Prototype:
//  void OSDDemoExitItm(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
void OSDDemoExitItm(void)
{
    DemoUnSelectValue();
    DemoSelect();
}
//******************************************************************************
// Prototype:
//  void OSDDemoExitItm(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
void OSDDemoItmUp(void)
{
    switch(ucDemoIndex) {
        case mdDFR:
            SystemData.bDFR= ~SystemData.bDFR;
            DemoShowDFR();
            break;
        case mdSR:
            SystemData.bSR= ~SystemData.bSR;
            DemoShowSR();
            break;
        default:break;
    }
    DemoSetValue();
}
//******************************************************************************
// Prototype:
//  void OSDDemoExitItm(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
void OSDDemoItmDown(void)
{
    switch(ucDemoIndex) {
        case mdDFR:
            SystemData.bDFR= ~SystemData.bDFR;
            DemoShowDFR();
            break;
        case mdSR:
            SystemData.bSR= ~SystemData.bSR;
            DemoShowSR();
            break;
        default:break;
    }
    DemoSetValue();
}
//******************************************************************************
// Prototype:
//  void DemoSetValue(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  None
// Notes:
//  None
//******************************************************************************
void DemoSetValue(void)
{
    switch(ucDemoIndex) {
        case mdDFR:
            break;
	 case mdSR:
	     break;
	 default:break;
    }
}

