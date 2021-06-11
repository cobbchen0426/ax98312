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

#if ENABLE_SCALER_3D == ON
//******************************************************************************
// G L O B A L   D E F I N I T I O N S
//******************************************************************************

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
static UCHAR uc3DCnvtMode = 0;

//******************************************************************************
// E X T E R N A L   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************

#if ENABLE_3D_CNV == ON
//******************************************************************************
// Prototype: 
//  void InitScaler3D(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Initial scaler 3D
// Notes:
//  None
//******************************************************************************
void InitScaler3D(void)
{
    uc3DCnvtMode = 0;

#if ENABLE_SHUTTER_3D == ON
    SC3DAPI_InitSyncSignal();
    SC3DAPI_SelSyncPort(SC3D_SYNC_IROUT);
    SC3DAPI_SetSyncDuty(PANEL_TYP_VTOTAL >> 5, (PANEL_TYP_VTOTAL >> 4) + (PANEL_TYP_VTOTAL >> 5));
#endif
}

//******************************************************************************
// Prototype: 
//  void Set2DTo3DMode(UCHAR mode)
// Parameters:
//  mode : 2D to 3D mode
// Return:
//  None
// Purpose:
//  Set 2D to 3D mode
// Notes:
//  None
//******************************************************************************
void Set2DTo3DMode(UCHAR mode)
{
    switch(mode) {
        case THR_D_CNV_2D_TO_3D:
            SetThemeMode(3);
            break;
        case THR_D_CNV_SIDEBYSIDE:
            break;
        case THR_D_CNV_TOPBOT:
            break;
        case THR_D_CNV_FRAME_SEQ:
            break;
        default :
            return;
    }
    
    uc3DCnvtMode = mode;
}

//******************************************************************************
// Prototype: 
//  void Set2DTo3DAdaptive(UCHAR enable)
// Parameters:
//  enable : TRUE or FALSE for enabling/disabling adaptive mode
// Return:
//  None
// Purpose:
//  Enable/disable adaptive mode
// Notes:
//  None
//******************************************************************************
void Set2DTo3DAdaptive(UCHAR enable)
{
    enable = 0;
}

//******************************************************************************
// Prototype: 
//  void Set2DTo3DDepth(UCHAR depth)
// Parameters:
//  depth : depth of 2D to 3D mode. The range is 0~10
// Return:
//  None
// Purpose:
//  Set depth of 2D to 3D mode
// Notes:
//  None
//******************************************************************************
void Set2DTo3DDepth(UCHAR depth)
{
    if (depth > MAXIMUM_2DTO3D_DEPTH) {
        depth = MAXIMUM_2DTO3D_DEPTH;
    }
    else if (depth < MINIMUM_2DTO3D_DEPTH) {
        depth = MINIMUM_2DTO3D_DEPTH;
    }
    SC3DAPI_Set2DTo3DDepthLvl(depth);
}

//******************************************************************************
// Prototype: 
//  void Set2DTo3DView(UCHAR view)
// Parameters:
//  view : view of 2D to 3D mode. The range is 0~11
// Return:
//  None
// Purpose:
//  Set view of 2D to 3D mode
// Notes:
//  None
//******************************************************************************
void Set2DTo3DView(UCHAR view)
{
    if (view > MAXIMUM_2DTO3D_VIEW) {
        view = MAXIMUM_2DTO3D_VIEW;
    }
    else if (view < MINIMUM_2DTO3D_VIEW) {
        view = MINIMUM_2DTO3D_VIEW;
    }
    
    SC3DAPI_Set2DTo3DViewPoint(view);
}

//******************************************************************************
// Prototype: 
//  void PerformAdaptive2DTO3D(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Perform adaptive 3D function
// Notes:
//  None
//******************************************************************************
void PerformAdaptive2DTO3D(void)
{
    if (uc3DCnvtMode == THR_D_CNV_2D_TO_3D) {
        SC3DAPI_Update2DTo3DGlobalCounter();
        if (Is2DTo3DAdaptive()) {
            SC3DAPI_SetDym2Dto3DDepthLvl(TRUE);
        }
        else {
            SC3DAPI_SetDym2Dto3DDepthLvl(FALSE);
        }
        SC3DAPI_Set2DTo3DBorder();
    }
}

//******************************************************************************
// Prototype:
//  void Set3DLRSwap(UCHAR swap)
// Parameters:
//  swap : swap or not
// Return:
//  None
// Purpose:
//  Swap L/R frame
// Notes:
//  None
//******************************************************************************
void Set3DLRSwap(UCHAR swap)
{
    SC3DAPI_SwapLR(swap);
}

//******************************************************************************
// Prototype:
//  void Set3DTo2DMode(UCHAR on)
// Parameters:
//  on : ON / OFF
// Return:
//  None
// Purpose:
//  Turn on/off 3D to 2D
// Notes:
//  None
//******************************************************************************
void Set3DTo2DMode(UCHAR on)
{
    SC3DAPI_Set3DTo2D(on & BIT0);
}
#endif

#if ENABLE_DVI_DUAL_LINK == ON
//******************************************************************************
// Prototype:
//  UCHAR DetectAMD3DModeChange(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Detect AMD 3D mode change
// Notes:
//  None
//******************************************************************************
UCHAR DetectAMD3DModeChange(void)
{
    static xdata USHRT mode_change_cnt = 0;

    if ((GetCurrInputInterface() == DIGITAL_INPUT1) && (IsHDMI() == FALSE)) {

        if (GetGlobalTimer(GLOBAL_TMR_AMD_3D) != 0) {
            return FALSE;
        }
        // We check AMD 3D flag status every 2.5 frames.
        SetGlobalTimer(GLOBAL_TMR_AMD_3D, 25000 / InputTiming.usVSyncFreq);

        if (SC3DAPI_IsAMD3D() != SC3DAPI_GetAMD3DCtlStatus()) {
            mode_change_cnt++;
        }
        else {
            mode_change_cnt = 0;
        }

        if (mode_change_cnt > 4) {
            mode_change_cnt = 0;
            return TRUE;
        }
    }

    return FALSE;
}
#endif //ENABLE_DVI_DUAL_LINK
#endif //ENABLE_SCALER_3D == ON
