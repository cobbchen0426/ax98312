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
#define SYNC_CHANGE_CNT     10

//******************************************************************************
// G L O B A L   V A R I A B L E S
//******************************************************************************
xdata UCHAR ucInputSyncMode = SEP_SYNC;

code UCHAR SyncSrcTbl[] = {
#if (INPUT_INTERFACE&INPUT_VGA1)
    ANALOG_SEP_INPUT1,
    ANALOG_COM_INPUT1,
    ANALOG_SOG_INPUT1,
#endif
#if (INPUT_INTERFACE&INPUT_VGA0)
    ANALOG_SEP_INPUT0,
    ANALOG_COM_INPUT0,
    ANALOG_SOG_INPUT0,
#endif
#if (INPUT_INTERFACE&INPUT_DIG1)
    DIGITAL_INPUT1,
#endif
#if (INPUT_INTERFACE&INPUT_DIG0)
    DIGITAL_INPUT0,
#endif
#if (INPUT_INTERFACE&INPUT_YPbPr1)
    ANALOG_YPBPR_INPUT1,
#endif
#if (INPUT_INTERFACE&INPUT_YPbPr0)
    ANALOG_YPBPR_INPUT0,
#endif
#if (INPUT_INTERFACE&INPUT_DP)
    DISPLAY_PORT_INPUT,
#endif
};

//******************************************************************************
// S T A T I C   V A R I A B L E S
//******************************************************************************
static xdata UCHAR ucSyncHdlrState = SEP_SYNC; //Sync handler state
static xdata UCHAR ucSyncSrcIdx = 0; //Sync source table index
static xdata UCHAR ucSyncChangeCnt = SYNC_CHANGE_CNT; //Mode change delay
static xdata USHRT usPortTimer_1ms = 0; //Port delay when changing input port
static BOOL bManualSyncSource = FALSE; //Make SyncSource searching input sync automatically or manually
static xdata USHRT usTimerTickTemp = 0;
static xdata USHRT usTMDSClock = 0;
static xdata USHRT usTMDSHrtlDE = 0;
static xdata USHRT usTMDSVrtlDE = 0;
#if ENABLE_HDMI == ON
static xdata USHRT usTMDSHtotal = 0;
static xdata USHRT usTMDSVtotal = 0;
#endif
static xdata UCHAR ucRecordSyncSrcIdx = 0xFF; //Sync source table index

//******************************************************************************
// E X T E R N A L   V A R I A B L E   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// S T A T I C   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
static UCHAR SyncSource(void);
static void SetModeChanged(void);
static UCHAR GetSameInput(void);
static UCHAR GetNextInput(void);
static void UpdateSyncSrcIdx(void);
static USHRT GetSyncSourceTimer(void);

//******************************************************************************
// E X T E R N A L   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// F U N C T I O N   B O D Y S
//******************************************************************************

//******************************************************************************
// Prototype: 
//  void SyncHandler(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Handle input sync
// Notes:
//  None
//******************************************************************************
void SyncHandler(void)
{
    switch (ucSyncHdlrState) 
	{
        case NO_SYNC:
        case NO_CABLE:
        case UNKNOWN_SYNC:
	// printf("  131120 SyncHdlrState =   NO_SYNC:=  NO_CABLE:=   UNKNOWN_SYNC:===> %X\n",(unsigned short)ucSyncHdlrState); 		 
            ucSyncHdlrState = SyncSource();
			//printf("140319 ucSyncHdlrState = SyncSource();==> %X\n",(unsigned short)ucSyncHdlrState); 

            ucInputSyncMode = ucSyncHdlrState;
            usTMDSClock = TMDS_GetClock();

            // The following "get DE" function must be after SyncSource!
            // Because of some TMDS setting in SyncSource may affect HDE/VDE value and will cause infinitely mode changed.
		#if (INPUT_INTERFACE&INPUT_DP)
            		if ( GetCurrInputInterface() == DISPLAY_PORT_INPUT ) 
				{
                			usTMDSHrtlDE = GetDPInputHDEImmediate();
               		 	usTMDSVrtlDE = GetDPInputVDEImmediate();
					//printf("SyncHdlrState =#if (INPUT_INTERFACE&INPUT_DP)===> %X\n",(unsigned short)ucSyncHdlrState); 				
              		}
            		else
            	#endif
            			{
        				#if ENABLE_HDMI == ON
                			usTMDSHtotal = GetDigInputHTotalImmediate();
                			usTMDSVtotal = GetDigInputVTotalImmediate();
        				#endif
                			usTMDSHrtlDE = GetDigInputHActiveImmediate();
                			usTMDSVrtlDE = GetDigInputVActiveImmediate();
            			}
           		 break;

        case SEP_SYNC:
        case COM_SYNC:
        case SOG_SYNC:
        case DIG_SYNC:

            			if (CheckModeChange() == TRUE) 
					{
               				 SetModeChanged();
              			}
            			break;

        	default:
            			break;
    	}
}

//******************************************************************************
// Prototype: 
//  static BOOL CheckModeChange(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Check input timing was changed or not
// Notes:
//  None
//******************************************************************************
BOOL CheckModeChange(void)
{
    if (ucSyncHdlrState == DIG_SYNC) 
	{
        if (IsForceToSleep() == TRUE) 
		{
            ClearModeChangeFlag();
            TMDS_EnableSCDT();
            McuScalerIntEnable();
            // Monitor the variation of TMDS clock under power saving mode
			if (abs(TMDS_GetClock() - usTMDSClock) > 2) 
			{
            	return TRUE;
            }
        }
#if (INPUT_INTERFACE&INPUT_DP)
        else if ( GetCurrInputInterface() == DISPLAY_PORT_INPUT ) 
		{
        	if (abs(GetDPInputHDEImmediate() - usTMDSHrtlDE) > 2) 
				
			{
			
            	return TRUE;
            }
           	if (abs(GetDPInputVDEImmediate() - usTMDSVrtlDE) > 1) 
		  	{
		  	
            	return TRUE;
            }
        }
#endif        
        else {

        // The HDMISoftReset is used to recover the abnormal states of HDMI circuit. When HDMI circuit
        // is under abnormal states, the H/V total are unstable. So, we monitor H/V total and reset HDMI
        // circuit when H/V total is unstable.
            // Monitor the variation of TMDS DE under normal display
            
        	if (abs(GetDigInputHActiveImmediate() - usTMDSHrtlDE) > 2) 
		  	{
		  	
            	return TRUE;
            }
            if (abs(GetDigInputVActiveImmediate() - usTMDSVrtlDE) > 1) 
			{
			
            	return TRUE;
            }
			
#if ENABLE_HDMI == ON
            // Monitor the variation of TMDS DE under normal display
	#if ENABLE_SCALER_3D == ON
        	if (SC3DAPI_IsActiveSpaceChanged()) 
			{
            	return TRUE;
            }
	#endif
            // The HTotal is unstable when input is deepcolor(e.x. For NT68360 the diff range is 0~10).
            // For fitting all scaler characteristic, we choose the value of HTotal tolerance as 16.
            if (abs(GetDigInputHTotalImmediate() - usTMDSHtotal) > 16) 
			{
				
            	HDMISoftReset();
                return TRUE;
           	}
            // The VTotal is unstable when input is interlace format.  we choose the value of VTotal
            // tolerance as 4.
            if (abs(GetDigInputVTotalImmediate() - usTMDSVtotal) > 4) 
			{
			
            	HDMISoftReset();
            	return TRUE;
            }
#endif
        }
    }

    if (CheckModeChangeFlag() == TRUE) {

        return TRUE;
    }

    return FALSE;
}

//******************************************************************************
// Prototype: 
//  static UCHAR SyncSource(void)
// Parameters:
//  None
// Return:
//  Sync status(NO_SYNC/NO_CABLE/SEP_SYNC/COM_SYNC/SOG_SYNC/DIG_SYNC)
// Purpose:
//  Check and search input sync in SyncSrcTbl
// Notes:
//  None
//******************************************************************************
static UCHAR SyncSource(void)
{
    UCHAR sync, next_sync_idx;

    //CheckInputSync will return NO_SYNC/SEP_SYNC/COM_SYNC/SOG_SYNC/DIG_SYNC
    sync = CheckInputSync();
	//   printf("sync = CheckInputSync();140319=> %X\n",(unsigned short)sync); 

    if (sync == NO_SYNC) 
	{
         if (bIsCableConnect() == FALSE) 
		{
            		sync = NO_CABLE;
		    // printf("140319  SyncSource==>sync = NO_CABLE;===>%x \n",(unsigned short)ucSyncChangeCnt);			
        	}
        	if (ucSyncChangeCnt > 0) 
			{
            			ucSyncChangeCnt--;
        		}
        else 
		{		    
		    //	printf("140319  else  SyncSource==>sync = NO_CABLE;===>%x \n",(unsigned short)ucSyncChangeCnt);			

            			UpdateSyncSrcIdx();
            			usPortTimer_1ms = GetSyncSourceTimer();
            		if (((GetTimerTick()-usTimerTickTemp)<usPortTimer_1ms) || (bManualSyncSource==TRUE)) 
				{
                			next_sync_idx = GetSameInput();
                			//RecordCurrentSource(FALSE);
                			if (ucSyncSrcIdx != next_sync_idx) 
					{
                    				ucSyncSrcIdx = next_sync_idx;
                    				SetInputInterface(SyncSrcTbl[ucSyncSrcIdx]);
                			}
            			}
            	else 
			{
                		if (ucRecordSyncSrcIdx < sizeof(SyncSrcTbl)) 
					{
                    				// Do not change the sequence of the following statements.
                    				// Return back to Record source index.
                    				next_sync_idx = ucRecordSyncSrcIdx;
                    				RecordCurrentSource(FALSE);
                			}
                	else 
				{
                			next_sync_idx = GetNextInput();
                		}
                	if (ucSyncSrcIdx != next_sync_idx) 
				{
                    			ucSyncSrcIdx = next_sync_idx;
                    			SetInputInterface(SyncSrcTbl[ucSyncSrcIdx]);
                		#if (ENABLE_DIGI1_HPD == ON) || (ENABLE_DIGI0_HPD == ON) || (ENABLE_DP_HPD == ON) 
                    			SYSAPI_PerformHPDOff(FALSE);
                		#endif
                		}
                		usTimerTickTemp = GetTimerTick();
            		}
#if (INPUT_INTERFACE&INPUT_MHL0) || (INPUT_INTERFACE&INPUT_MHL1)
            if ( ((SyncSrcTbl[ucSyncSrcIdx]==DIGITAL_INPUT0) && MHLIsCBus1On() ) || ((SyncSrcTbl[ucSyncSrcIdx]==DIGITAL_INPUT1) &&  MHLIsCBus2On() )) {
                if ( GetCbusConnectStatus() == MHL_PATH_EN ) 
			{
                    		ResetCurTimerTick();
                	}
            }
#endif
        }
    }

	#if (ENABLE_DIGI1_HPD == ON) || (ENABLE_DIGI0_HPD == ON) || (ENABLE_DP_HPD == ON)
    		if ( sync == UNKNOWN_SYNC) 					//need to discuss with Nick&James
			{ 
        			SYSAPI_PerformHPDOn(); 
    			}
    	else 
		{
    			if (bIsHPDActive() == FALSE) 
				{
        				if (GetGlobalTimer(GLOBAL_TMR_HPD) > 0) 
						{
            						sync = NO_SYNC;
            						 if (bIsCableConnect() == FALSE) 
								{
               							 sync = NO_CABLE;
           						 	}
        					}
        				else 
						{
           						 SYSAPI_PerformHPDOn(); 
        					}
    					}
    		}
#endif
	   //printf("140319 return sync;=> %X\n",(unsigned short)sync); 
    return sync;
}

//******************************************************************************
// Prototype: 
//  static void SetModeChanged(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Set some flags to indicate that input timing was changed
// Notes:
//  None
//******************************************************************************
static void SetModeChanged(void)
{
    Force2Background(0, 0, 0); //Mute screen and display black pattern
    ucSyncHdlrState = NO_SYNC;
    ucInputSyncMode = NO_SYNC;
    ucSyncChangeCnt = SYNC_CHANGE_CNT;
    usPortTimer_1ms = GetSyncSourceTimer();
    usTimerTickTemp = GetTimerTick();
    ClearModeChangeFlag(); //Clear mode change flag
    ClearForceToSleep();
}

//******************************************************************************
// Prototype: 
//  static UCHAR GetSameInput(void)
// Parameters:
//  None
// Return:
//  The sync index in SyncSrcTbl
// Purpose:
//  Search next input sync belonged to the same input interface in SyncSrcTbl
// Notes:
//  None
//******************************************************************************
static UCHAR GetSameInput(void)
{
    UCHAR i, j;

    for (i=1; i<=sizeof(SyncSrcTbl); i++) {
        j = (ucSyncSrcIdx+i) % sizeof(SyncSrcTbl);
        if ((SyncSrcTbl[j]&PORT_MASK) == (SyncSrcTbl[ucSyncSrcIdx]&PORT_MASK)) {
            //SyncSrcTbl[j] is the next sync that we found in the same interface.
            //Ex. Seperate -> Composite -> SOG -> Seperate -> Composite -> ...
            return j;
        }
    }

    //Error handling, program should not run to here.
    return ucSyncSrcIdx;
}

//******************************************************************************
// Prototype: 
//  static UCHAR GetNextInput(void)
// Parameters:
//  None
// Return:
//  The sync index in SyncSrcTbl
// Purpose:
//  Search next input sync belonged to the different input interface in 
//  SyncSrcTbl
// Notes:
//  None
//******************************************************************************
static UCHAR GetNextInput(void)
{
     UCHAR i, j,K,L;
    for (i=1; i<=sizeof(SyncSrcTbl); i++) 
	{
	 K=(ucSyncSrcIdx+i) ;
		  L=sizeof(SyncSrcTbl);
       	 j = (ucSyncSrcIdx+i) % sizeof(SyncSrcTbl);
        if ((SyncSrcTbl[j]&PORT_MASK) != (SyncSrcTbl[ucSyncSrcIdx]&PORT_MASK)) 
		{
            		return j;
        	}
    	}

    ucSyncSrcIdx = GetSameInput();
    //If we can not find next input in SyncSrcTbl, return current input.
    return ucSyncSrcIdx;
}

//******************************************************************************
// Prototype: 
//  void SetSyncSource(UCHAR Type)
// Parameters:
//  Type : AUTO_SYNC/MANUAL_SYNC
// Return:
//  None
// Purpose:
//  Make SyncSource searching input sync automatically or manually
// Notes:
//  None
//******************************************************************************
void SetSyncSource(UCHAR Type)
{
#if ENABLE_HDMI_PRETEST == ON
    Type = MANUAL_SYNC;
#endif
    if (Type == AUTO_SYNC) {
        bManualSyncSource = FALSE;
    }
    else {
        bManualSyncSource = TRUE;
    }
}

//******************************************************************************
// Prototype: 
//  static void UpdateSyncSrcIdx(void)
// Parameters:
//  void
// Return:
//  None
// Purpose:
//  Update the variable "ucSyncSrcIdx" if the input interface was changed 
//  outside of SyncSource.
// Notes:
//  None
//******************************************************************************
static void UpdateSyncSrcIdx(void)
{
    UCHAR i, curr_interface;

    curr_interface = GetCurrInputInterface();
    for (i=0; i<sizeof(SyncSrcTbl); i++) {
        if (SyncSrcTbl[i] == curr_interface) {
            ucSyncSrcIdx = i;
            return;
        }
    }
}

//******************************************************************************
// Prototype: 
//  static USHRT GetSyncSourceTimer(void)
// Parameters:
//  void
// Return:
//  The time out timer of changing input port
// Purpose:
//  Set set timer to change input port
// Notes:
//  None
//******************************************************************************
static USHRT GetSyncSourceTimer(void)
{
    UCHAR curr_interface;
    USHRT time = 0;

    curr_interface = GetCurrInputInterface();

    switch (curr_interface) {
        case ANALOG_SEP_INPUT0:
        case ANALOG_COM_INPUT0:
        case ANALOG_SOG_INPUT0:
        case ANALOG_YPBPR_INPUT0:
            time = SYNCSRC_TIME_ANALOG0;
            break;

        case DIGITAL_INPUT0:
            time = SYNCSRC_TIME_DIGITAL0;
            break;

        case ANALOG_SEP_INPUT1:
        case ANALOG_COM_INPUT1:
        case ANALOG_SOG_INPUT1:
        case ANALOG_YPBPR_INPUT1:
            time = SYNCSRC_TIME_ANALOG1;
            break;

        case DIGITAL_INPUT1:
            time = SYNCSRC_TIME_DIGITAL1;
            break;
#if (INPUT_INTERFACE&INPUT_DP)
        case DISPLAY_PORT_INPUT:
            time = SYNCSRC_TIME_DP;
            break;
#endif
        default:
            time = SYNCSRC_TIME_ANALOG0;
            break;
    }

    return time;
}

//******************************************************************************
// Prototype: 
//  UCHAR GetSyncMode(void)
// Parameters:
//  None
// Return:
//  NO_SYNC/NO_CABLE/SEP_SYNC/COM_SYNC/SOG_SYNC/DIG_SYNC/OUT_SYNC
// Purpose:
//  Return system sync state
// Notes:
//  None
//******************************************************************************
UCHAR GetInputSyncMode(void)
{
    return ucInputSyncMode;
}

#if (INPUT_INTERFACE&INPUT_MHL0) || (INPUT_INTERFACE&INPUT_MHL1) || (ENABLE_DP_HPD == ON)
//******************************************************************************
// Prototype: 
//  void ResetCurTimerTick(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Reset Change-port timer (used for MHL)
// Notes:
//  None
//******************************************************************************
void ResetCurTimerTick(void)
{
    ucSyncChangeCnt = SYNC_CHANGE_CNT;
    usPortTimer_1ms = GetSyncSourceTimer();
    usTimerTickTemp = GetTimerTick();
}
#endif

//******************************************************************************
// Prototype:
//  void RecordCurrentSource(UCHAR enable)
// Parameters:
//  enable : TRUE/FALSE
//  TRUE: Record current source index.
//  FALSE: clear Record source index.
// Return:
//  None
// Purpose:
//  Determine whether to record current sync source or not
// Notes:
//  @Param TRUE : only use to manual change input source
//******************************************************************************
void RecordCurrentSource(UCHAR enable)
{
    if (enable) {
        // We use UpdateSyncSrcIdx to make sure the range of ucSyncSrcIdx is valid or not.
        // P.S. When system AC on, ucSyncSrcIdx is 0. That is invalid for ucRecordSyncSrcIdx.
        UpdateSyncSrcIdx();
        ucRecordSyncSrcIdx = ucSyncSrcIdx;
    }
    else {
        ucRecordSyncSrcIdx = 0xFF;
    }
}
