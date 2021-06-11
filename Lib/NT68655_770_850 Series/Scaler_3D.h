/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/
#ifndef __SCALER_3D_H__
#define __SCALER_3D_H__

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************
#include "Typedef.h"

//******************************************************************************
// M A C R O   D E F I N I T I O N S
//******************************************************************************
typedef enum _SC3D_SYNC_PORT_ {
    SC3D_SYNC_VOUT,
    SC3D_SYNC_LOUT,
    SC3D_SYNC_ROUT,
    SC3D_SYNC_IROUT,
    SC3D_TVIR_OUT,
    SC3D_SYNC_NONE
} SC3DSyncPort;

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

//******************************************************************************
// E X T E R N A L   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
void SC3DAPI_Init(void);
void SC3DAPI_InitSyncSignal(void);
void SC3DAPI_SelSyncPort(SC3DSyncPort port);
void SC3DAPI_SetSyncDuty(USHRT on, USHRT off);
void SC3DAPI_SetTVIRDelay(USHRT vsync, UCHAR delay);
void SC3DAPI_InvSyncLR(UCHAR inv);

void SC3DAPI_EnableAMDLRSync(UCHAR enable);
UCHAR SC3DAPI_DetectAMD3D(void);
UCHAR SC3DAPI_GetAMD3DCtlStatus(void);

void SC3DAPI_Setup3DMode(void);
void SC3DAPI_Set3DTo2D(UCHAR enable);
void SC3DAPI_TurnOff3DMode(void);

void SC3DAPI_Enable2DTo3D(UCHAR enable);
void SC3DAPI_Set2DTo3DViewPoint(UCHAR vpoint);
void SC3DAPI_Set2DTo3DDepthLvl(UCHAR dlvl);
void SC3DAPI_Set2DTo3DBorder(void);
void SC3DAPI_Update2DTo3DGlobalCounter(void);
void SC3DAPI_SetDym2Dto3DDepthLvl(UCHAR on);

BOOL SC3DAPI_CheckVSI3DStatus(void);
BOOL SC3DAPI_IsHDMI3DMode(void);
BOOL SC3DAPI_IsHDMI3DFmtChanged(void);
UCHAR SC3DAPI_GetHDMI3DFormat(void);
void SC3DAPI_SetupHDMI3DMode(void);
BOOL SC3DAPI_IsActiveSpaceChanged(void);

void SC3DAPI_SwapLR(UCHAR swap);
BOOL SC3DAPI_IsHDMI3D(void);
BOOL SC3DAPI_IsAMD3D(void);
BOOL SC3DAPI_Is2DTo3D(void);
//BOOL SC3DAPI_Is2DToFS(void);
//BOOL SC3DAPI_IsSBS(void);
//BOOL SC3DAPI_IsTB(void);
BOOL SC3DAPI_IsDisplay3D(void);
//BOOL SC3DAPI_Is3DTo2D(void);
BOOL SC3DAPI_Is3DFormat(void);
BOOL SC3DAPI_IsManualHDMI3D(void);
#endif //__SCALER_3D_H__
