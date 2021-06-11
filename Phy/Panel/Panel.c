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

//******************************************************************************
// G L O B A L   V A R I A B L E S
//******************************************************************************
code PanelData PanelDataDefault = {
    PANEL_LVDS_SWING, //UCHAR ucLVDS_Swing : 5;
    PANEL_DUAL_PORT_LVDS, //UCHAR bDualPortLVDS : 1;
    0x01, //UCHAR bEnableSSC : 1;
    PANEL_DE_MODE, //UCHAR bDEMode : 1;
    PANEL_PORT_SWAP, //UCHAR bPortSwap : 1;
    PANEL_BIT_SHIFT, //UCHAR bBitShift : 1;
    PANEL_COLOR_DEPTH, //UCHAR ucColorDepth;
    PANEL_WIDTH, //USHRT usWidth;
    PANEL_HEIGHT, //USHRT usHeight;
    PANEL_MIN_LVDS_CLK, //ULONG ulMinPClk;
    PANEL_MAX_LVDS_CLK, //ULONG ulMaxPClk;
    PANEL_MIN_HTOTAL, //USHRT usMinHTotal;
    PANEL_TYP_HTOTAL, //USHRT usTypHTotal;
    PANEL_MAX_HTOTAL, //USHRT usMaxHTotal;
    PANEL_HSYNC_WIDTH, //USHRT usMinHSyncWidth;
    PANEL_HSYNC_BACKPORCH, //USHRT usMinHSyncBackPorch;
    PANEL_MIN_VTOTAL, //USHRT usMinVTotal;
    PANEL_TYP_VTOTAL, //USHRT usTypVTotal;
    PANEL_MAX_VTOTAL, //USHRT usMaxVTotal;
    PANEL_VSYNC_WIDTH, //USHRT usMinVSyncWidth;
    PANEL_VSYNC_BACKPORCH, //USHRT usMinVSyncBackPorch;
    (ULONG)PANEL_FRC_OUTPUT_VSYNC*PANEL_TYP_VTOTAL, //ULONG ulFreeRunH_Freq;
    PANEL_POWER_UP_TIME, //USHRT usPowerUpPanelTime;
    PANEL_INVTER_UP_TIME, //USHRT usPowerUpInvTime;
    PANEL_POWER_DOWN_TIME, //USHRT usPowerDownPanelTime;
    PANEL_INVTER_DOWN_TIME, //USHRT usPowerDownInvTime;
    PANEL_OFF_ON_TIME,//USHRT usPowerOffOnPanelTime
    PANEL_DCLK_SSC //UCHAR ucSpreadSpectrumCtrl;
};
//******************************************************************************
// S T A T I C   V A R I A B L E S
//******************************************************************************

//******************************************************************************
// E X T E R N A L   V A R I A B L E   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// S T A T I C   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// E X T E R N A L   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************


