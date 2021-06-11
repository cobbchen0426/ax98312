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
#define SAVE_USER_DATA      0x01
#define SAVE_TIMING_DATA    0x02
#define SAVE_CALIB_DATA     0x04
#define SAVE_SYS_DATA       0x08
#define DDCCI_PWR_ON        0x10
#define DDCCI_PWR_OFF       0x20
#define DDCCI_PWM_SAVING    0x40

#define IsDdcciUpdUsr() ((ucDdcciFlag&SAVE_USER_DATA) != 0)
#define IsDdcciUpdTmg() ((ucDdcciFlag&SAVE_TIMING_DATA) != 0)
#define IsDdcciUpdCal() ((ucDdcciFlag&SAVE_CALIB_DATA) != 0)
#define IsDdcciUpdSys() ((ucDdcciFlag&SAVE_SYS_DATA) != 0)
#define IsDdcciPwrOn() ((ucDdcciFlag&DDCCI_PWR_ON) != 0)
#define IsDdcciPwrOff() ((ucDdcciFlag&DDCCI_PWR_OFF) != 0)
#define IsDdcciPwrSaving() ((ucDdcciFlag&DDCCI_PWM_SAVING) != 0)

#define SetDdcciUpdUsrFlag() {ucDdcciFlag |= SAVE_USER_DATA;}
#define SetDdcciUpdTmgFlag() {ucDdcciFlag |= SAVE_TIMING_DATA;}
#define SetDdcciUpdCalFlag() {ucDdcciFlag |= SAVE_CALIB_DATA;}
#define SetDdcciUpdSysFlag() {ucDdcciFlag |= SAVE_SYS_DATA;}
#define SetDdcciPwrOnFlag() {ucDdcciFlag |= DDCCI_PWR_ON;}
#define SetDdcciPwrOffFlag() {ucDdcciFlag |= DDCCI_PWR_OFF;}
#define SetDdcciPwrSavingFlag() {ucDdcciFlag |= DDCCI_PWM_SAVING;}

#define ClearDdcciUpdUsrFlag() {ucDdcciFlag &= ~SAVE_USER_DATA;}
#define ClearDdcciUpdTmgFlag() {ucDdcciFlag &= ~SAVE_TIMING_DATA;}
#define ClearDdcciUpdCalFlag() {ucDdcciFlag &= ~SAVE_CALIB_DATA;}
#define ClearDdcciUpdSysFlag() {ucDdcciFlag &= ~SAVE_SYS_DATA;}
#define ClearDdcciPwrOnFlag() {ucDdcciFlag &= ~DDCCI_PWR_ON;}
#define ClearDdcciPwrOffFlag() {ucDdcciFlag &= ~DDCCI_PWR_OFF;}
#define ClearDdcciPwrSavingFlag() {ucDdcciFlag &= ~DDCCI_PWM_SAVING;}

//******************************************************************************
// G L O B A L   V A R I A B L E S
//******************************************************************************
idata UCHAR ucDdcciChannel = 0;
BOOL bDDCCmdUpdate = FALSE;
idata UCHAR ucDDCCiTxOut = 0;
idata UCHAR ucDDCCiTxIn = 0;
idata UCHAR ucDDCCiRxIn = 0;
idata UCHAR ucDDCCiRxOut = 0;
xdata UCHAR ucDDCCiTxBuffer[DDCCI_BUFFER_SIZE];
xdata UCHAR ucDDCCiRxBuffer[DDCCI_BUFFER_SIZE];

//******************************************************************************
// S T A T I C   V A R I A B L E S
//******************************************************************************
static code UCHAR ucColorTab[] = {
    0x04, 0x05, 0x06, 0x07, 0x08, 0x0A, 0x01, 0x0B
};

static xdata UCHAR ucNewControlValue = 0xFF;
static idata UCHAR ucDDCCiTxChecksum;
static idata UCHAR ucDDCCiRxChecksum;
static xdata UCHAR ucDdcciFlag = 0x00;

//static xdata UCHAR ucDDCCiPhase = 0xFF;
//static xdata UCHAR ucImageVPos = 0xFF;

//******************************************************************************
// E X T E R N A L   V A R I A B L E   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// S T A T I C   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
static void Check2BiCmd(void);
static void SendNullCmd(UCHAR SlaveAddr);
static void SendACKCmd(void);
static void SendNACKCmd(void);
static void GetVCP_Feature(void);
static void SetVCP_Feature(void);
static void SetVCP_Capabilities(void);
static void GetTiming(void);
static void SendResponseCmd(void);
//static void WaitDDCTxOut();
static void GenTxCheckSum(void);

//******************************************************************************
// E X T E R N A L   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************


//******************************************************************************
// Prototype: 
//  BOOL DDCCIUserUpdate(void)
// Parameters:
//  None
// Return:
//  Return the status of user update flag
// Purpose:
//  Check user data is updated or not
// Notes:
//  None
//******************************************************************************
BOOL DDCCIUserUpdate(void)
{
    BOOL tmp = IsDdcciUpdUsr();
    ClearDdcciUpdUsrFlag();
    return tmp;
}

//******************************************************************************
// Prototype: 
//  BOOL DDCCITmgUpdate(void)
// Parameters:
//  None
// Return:
//  Return the status of timing update flag
// Purpose:
//  Check timing data is updated or not
// Notes:
//  None
//******************************************************************************
BOOL DDCCITmgUpdate(void)
{
    BOOL tmp = IsDdcciUpdTmg();
    ClearDdcciUpdTmgFlag();
    return tmp;
}

//******************************************************************************
// Prototype: 
//  BOOL DDCCISysUpdate(void)
// Parameters:
//  None
// Return:
//  Return the status of system update flag
// Purpose:
//  Check system data is updated or not
// Notes:
//  None
//******************************************************************************
BOOL DDCCISysUpdate(void)
{
    BOOL tmp = IsDdcciUpdSys();
    ClearDdcciUpdSysFlag();
    return tmp;
}

//******************************************************************************
// Prototype: 
//  BOOL DDCCICalUpdate(void)
// Parameters:
//  None
// Return:
//  Return the status of calibration update flag
// Purpose:
//  Check calibration data is updated or not
// Notes:
//  None
//******************************************************************************
BOOL DDCCICalUpdate(void)
{
    BOOL tmp = IsDdcciUpdCal();
    ClearDdcciUpdCalFlag();
    return tmp;
}

//******************************************************************************
// Prototype:
//  BOOL DDCCIPwrOn(void)
// Parameters:
//  None
// Return:
//  Return the status of power on action from ddcci
// Purpose:
//  Power on system
// Notes:
//  None
//******************************************************************************
BOOL DDCCIPwrOn(void)
{
    BOOL tmp = IsDdcciPwrOn();
    ClearDdcciPwrOnFlag();
    return tmp;
}

//******************************************************************************
// Prototype:
//  BOOL DDCCIPwrOff(void)
// Parameters:
//  None
// Return:
//  Return the status of power off action from ddcci
// Purpose:
//  Power off system
// Notes:
//  None
//******************************************************************************
BOOL DDCCIPwrOff(void)
{
    BOOL tmp = IsDdcciPwrOff();
    ClearDdcciPwrOffFlag();
    return tmp;
}

//******************************************************************************
// Prototype:
//  BOOL DDCCIPwrSaving(void)
// Parameters:
//  None
// Return:
//  Return the status of power saving action from ddcci
// Purpose:
//  Force system into power saving state
// Notes:
//  None
//******************************************************************************
BOOL DDCCIPwrSaving(void)
{
    BOOL tmp = IsDdcciPwrSaving();
    ClearDdcciPwrSavingFlag();
    return tmp;
}

//******************************************************************************
// Prototype: 
//  void DDCCiUpdateNotice(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  Inform DDCCi that user data is out of date.
// Notes:
//  None
//******************************************************************************
void DDCCiUpdateNotice(void)
{
    ucNewControlValue = 0x02;
}

//******************************************************************************
// Prototype: 
//  void CheckDDC2Bi(void)
// Parameters:
//  None
// Return:
//  None
// Purpose:
//  DDCCi routine
// Notes:
//  None
//******************************************************************************
void CheckDDC2Bi(void)
{
#if 1
    UCHAR len;

    if (bDDCCmdUpdate) {
        len = 0;
        SetGlobalTimer(GLOBAL_TMR_LOCAL, GBTM_DDCCI_BUS_TIMEOUT);
        while (bDDCCmdUpdate && GetGlobalTimer(GLOBAL_TMR_LOCAL)) {
            ResetWDTimer();
            if (ucDDCCiRxIn > 1) {
                len = (ucDDCCiRxBuffer[1] & 0x7F) + 3;
            }
            if (len != ucDDCCiRxIn) {
            switch(ucDdcciChannel) {
                case 0: if ((IIC0_STATUS & BUS_STOP) != BUS_STOP) continue; break;
                case 1: if ((IIC1_STATUS & BUS_STOP) != BUS_STOP) continue; break;
                case 2: if ((IIC2_STATUS & BUS_STOP) != BUS_STOP) continue; break;
                case 3: if ((IIC3_STATUS & BUS_STOP) != BUS_STOP) continue; break;
                default://DP AUX
                    continue;
                    break;
                }
            }
            bDDCCmdUpdate = FALSE;

            if (ucDDCCiRxIn != 0) {
                ucDDCCiRxIn = 0;
                ucDDCCiRxChecksum = 0;
                len = (ucDDCCiRxBuffer[1] & 0x7F) + 3;
                while (len) {
                    ucDDCCiRxChecksum ^= ucDDCCiRxBuffer[--len];
                }
                Check2BiCmd();
            }
        }
        
        if(ucDdcciFlag != 0){ //for fe2p save delay
            SetGlobalTimer(GLOBAL_TMR_DATA_UPDATE, GBTM_DATA_UPDATE);
           }    
    }
    else {
        if(GetGlobalTimer(GLOBAL_TMR_LOCAL) == 0){
            McuIICReleaseSCL(MCU_IIC_CON_DEFAULT);
        }
        McuIICPreSendACK(MCU_IIC_CON_DEFAULT);
    }
#else
    UCHAR cmd;
    BOOL i;

    while (bDDCCmdUpdate) {
        bDDCCmdUpdate = FALSE;
        //Wait stop
        i = FALSE;

        SetGlobalTimer(GLOBAL_TMR_LOCAL, GBTM_DDCCI_BUS_TIMEOUT);
        do {
            if((ucDdcciChannel == 0)&&((IIC0_STATUS & BUS_STOP) != 0)){
               i = TRUE;
               break;
            }
            else if((ucDdcciChannel == 1)&&((IIC1_STATUS & BUS_STOP) != 0)){
               i = TRUE;
               break;
            }
            else if((ucDdcciChannel == 2)&&((IIC2_STATUS & BUS_STOP) != 0)){
               i = TRUE;
               break;
            }
            else if((ucDdcciChannel == 3)&&((IIC3_STATUS & BUS_STOP) != 0)){
               i = TRUE;
               break;
            }
            ResetWDTimer();
        } while (GetGlobalTimer(GLOBAL_TMR_LOCAL));

        if ((i==TRUE) && (ucDDCCiRxIn!=0)) { //receive
            ucDDCCiRxChecksum = 0;
            ucDDCCiRxOut = 0;
            cmd = (ucDDCCiRxBuffer[1] & 0x7F) + 3;
            if (ucDDCCiRxIn > cmd) {
                ucDDCCiRxIn = cmd;
            }
            while (ucDDCCiRxIn != ucDDCCiRxOut) {
                cmd = ucDDCCiRxBuffer[ucDDCCiRxOut++];
                ucDDCCiRxChecksum ^= cmd;
                if(ucDDCCiRxOut > DDCCI_BUFFER_SIZE-1)
                    ucDDCCiRxOut = 2;
            }
            ucDDCCiRxIn = 0;
            Check2BiCmd();
        }
    }

    McuIICReleaseSCL(MCU_IIC_CON_DEFAULT);
#endif
}

void Check2BiCmd(void)
{
        SendNullCmd(DDCCI_ADDR);
    if (ucDDCCiRxChecksum == DDCCI_ADDR) {
//        SendNullCmd(DDCCI_ADDR);
        switch (ucDDCCiRxBuffer[2]) {
            case CMDOP_GET_VCP: //GetVCP_Feature
                GetVCP_Feature();
                break;
            case CMDOP_SET_VCP: //SetVCP_Feature
                SetVCP_Feature();
                break;
            case CMDOP_GET_TIMING: //GetTiming
                GetTiming();
                break;
            case CMDOP_SAVE: //SaveCurrentSetting
                SetDdcciUpdUsrFlag();
                if (GetInputSyncMode() != DIG_SYNC) {
                    SetDdcciUpdTmgFlag();
                }
                break;
            case CMDOP_SET_CAP: //VCPcapability
                SetVCP_Capabilities();
                break;
            default:
                return; //DO NOT GO TO OSD_OFF()
                break;
        }
        OSDCloseAll();
    }
}

void SendNullCmd(UCHAR SlaveAddr)
{
    ucDDCCiTxBuffer[0] = SlaveAddr;
    ucDDCCiTxBuffer[1] = 0x80;
    ucDDCCiTxOut = 0;
    ucDDCCiTxIn = 2;
    GenTxCheckSum();
}

void ReplyNA()
{
    ucDDCCiTxBuffer[3] = 0x01; //result code = unsupported
    ucDDCCiTxBuffer[6] = 0x00; //maximumHi
    ucDDCCiTxBuffer[7] = 0xFF; //maximumLo
    ucDDCCiTxBuffer[8] = 0x00;
    ucDDCCiTxBuffer[9] = 0x00;
}

void GetVCP_Feature(void)
{
    USHRT temp;

    //WaitDDCTxOut();
    
    ucDDCCiTxBuffer[0] = ACCESSBUS_ADDR;
    ucDDCCiTxBuffer[1] = 0x88;
    ucDDCCiTxBuffer[2] = CMDOP_VCP_RPL;
    ucDDCCiTxBuffer[3] = 0x00; //result code = no error
    ucDDCCiTxBuffer[4] = ucDDCCiRxBuffer[3];
    ucDDCCiTxBuffer[5] = 0x00; //vcp type = set parameter
    ucDDCCiTxOut = 0;
    ucDDCCiTxIn = 10;

    switch(ucDDCCiRxBuffer[3]){
    case VCPOP_NEW_CTRL:    //0x02
        ucDDCCiTxBuffer[6] = 0x00;        //maximumHi
        ucDDCCiTxBuffer[7] = 0xff;        //maximumLo
        ucDDCCiTxBuffer[8] = 0x00;        //
        ucDDCCiTxBuffer[9] = ucNewControlValue;        //0xff no user control are present
        break;
    case VCPOP_COLOR_INC:    //0x0B
        ucDDCCiTxBuffer[6] = 0xff;        //maximumHi
        ucDDCCiTxBuffer[7] = 0xff;        //maximumLo
        ucDDCCiTxBuffer[8] = 0x00;        //
        ucDDCCiTxBuffer[9] = 0x32;        //each step = 50
        break;
    case VCPOP_COLOR_REQ:    //0x0C
        ucDDCCiTxBuffer[6] = 0x00;        //maximumHi
        ucDDCCiTxBuffer[7] = 0xAA;        //maximumLo
        ucDDCCiTxBuffer[8] = 0x00;        //

        switch (UserData.ucColorTemp) {
/*
            case CLRTMP_5000K:
            ucDDCCiTxBuffer[9] = 40;
                break;
*/
            case CLRTMP_6500K:
            ucDDCCiTxBuffer[9] = 70;
                break;
            case CLRTMP_7500K:
            ucDDCCiTxBuffer[9] = 90;
                break;
/*
            case CLRTMP_8200K:
            ucDDCCiTxBuffer[9] = 104;
                break;
*/
            case CLRTMP_9300K:
            ucDDCCiTxBuffer[9] = 126;
                break;
/*
            case CLRTMP_11500K:
            ucDDCCiTxBuffer[9] = 170;
                break;
*/
            default:
            ucDDCCiTxBuffer[9] = 70;
        break;
        }

        break;

    case VCPOP_CLOCK:    //clock
        if (GetInputSyncMode() == DIG_SYNC) {
            ReplyNA();
        }
        else{
            ucDDCCiTxBuffer[6] = 0x00;        //maximumHi
            ucDDCCiTxBuffer[7] = 100;        //maximumLo
            ucDDCCiTxBuffer[8] = 0x00;        //clockHi
            ucDDCCiTxBuffer[9] = UserGetNormalClock();
        }
        break;
    case VCPOP_BRIGHT:    //brightness
        ucDDCCiTxBuffer[6] = 0x00;        //maximumHi
        ucDDCCiTxBuffer[7] = 100;        //maximumLo
        ucDDCCiTxBuffer[8] = 0x00;        //brightnessHi
        ucDDCCiTxBuffer[9] = UserData.ucBrightness;    //brightnessLo
        UserData.ucDCRMode = BKL_CTRL_OFF;
        break;
    case VCPOP_CONTRAST:    //contrast
        ucDDCCiTxBuffer[6] = 0x00;        //maximumHi
        ucDDCCiTxBuffer[7] = 100;        //maximumLo
        ucDDCCiTxBuffer[8] = 0x00;        //contrastHi
        ucDDCCiTxBuffer[9] = UserData.ucContrast;    //contrastLo
        break;
    case VCPOP_SEL_COLOR:    //select color preset
        ucDDCCiTxBuffer[6] = 0x00;        //maximumHi
        ucDDCCiTxBuffer[7] = 0x0B;        //maximumLo
        ucDDCCiTxBuffer[8] = 0x00;        //colorinputHi
        ucDDCCiTxBuffer[9] = ucColorTab[UserData.ucColorTemp];
        break;
    case VCPOP_RGAIN:    //Red gain
        ucDDCCiTxBuffer[6] = 0x00;        //maximumHi
        ucDDCCiTxBuffer[7] = 100;        //maximumLo
        ucDDCCiTxBuffer[8] = 0x00;        //R_GainHi
        ucDDCCiTxBuffer[9] = UserData.ucUserRGain;    //R_GainLo    2006-11-28 VISTA
        break;
    case VCPOP_GGAIN:    //Green gain
        ucDDCCiTxBuffer[6] = 0x00;        //maximumHi
        ucDDCCiTxBuffer[7] = 100;        //maximumLo
        ucDDCCiTxBuffer[8] = 0x00;        //G_GainHi
        ucDDCCiTxBuffer[9] = UserData.ucUserGGain;    //G_GainLo    2006-11-28 VISTA
        break;
    case VCPOP_BGAIN:    //Blue gain
        ucDDCCiTxBuffer[6] = 0x00;        //maximumHi
        ucDDCCiTxBuffer[7] = 100;        //maximumLo
        ucDDCCiTxBuffer[8] = 0x00;        //B_GainHi
        ucDDCCiTxBuffer[9] = UserData.ucUserBGain;    //B_GainLo    2006-11-28 VISTA
        break;
    case VCPOP_AUTO_COLOR:            
    case VCPOP_AUTO_SET:    //autoaetup
        if (GetInputSyncMode() != DIG_SYNC) {
            ucDDCCiTxBuffer[6] = 0x00;        //maximumHi
            ucDDCCiTxBuffer[7] = 0x01;        //maximumLo
            ucDDCCiTxBuffer[8] = 0x00;        //autoaetupHi
            ucDDCCiTxBuffer[9] = 0x00;        //autoaetupLo
        }
        else{
            ReplyNA();
        }
        break;
    case VCPOP_RECALL:    //factory reset        //2004-01-27 add facrory reset
    case VCPOP_RECALL_BC:
    case VCPOP_RECALL_COLOR:
    case VCPOP_END:
        ucDDCCiTxBuffer[6] = 0x00;        //maximumHi
        ucDDCCiTxBuffer[7] = 0x01;        //maximumLo
        ucDDCCiTxBuffer[8] = 0x00;        //autoaetupHi
        ucDDCCiTxBuffer[9] = 0x00;        //autoaetupLo
        break;
    case VCPOP_RECALL_HV_POS:
        if (GetInputSyncMode() == DIG_SYNC) {
            ReplyNA();
        }
        else{
            ucDDCCiTxBuffer[6] = 0x00;        //maximumHi
            ucDDCCiTxBuffer[7] = 0x01;        //maximumLo
            ucDDCCiTxBuffer[8] = 0x00;        //autoaetupHi
            ucDDCCiTxBuffer[9] = 0x00;        //autoaetupLo
        }
        break;
    case VCPOP_H_POS:    //horizontal position
        if (GetInputSyncMode() == DIG_SYNC) {
            ReplyNA();
        }
        else{
            ucDDCCiTxBuffer[6] = 0x00;    //maximumHi
            ucDDCCiTxBuffer[7] = 100;        //maximumLo
            ucDDCCiTxBuffer[8] = 0x00;    //HpHi
            ucDDCCiTxBuffer[9] = UserGetNormalHPosn();
        }
        break;
    case VCPOP_V_POS:    //vertical position
        if (GetInputSyncMode() == DIG_SYNC) {
            ReplyNA();
        }
        else{
            ucDDCCiTxBuffer[6] = 0x00;    //maximumHi
            ucDDCCiTxBuffer[7] = 100;        //maximumLo
            ucDDCCiTxBuffer[8] = 0x00;    //VpHi
            // We return ucImageVPos to DT tool for passing DT
            // If the difference is larget then 2, we return actual value!
            //if (abs(ucImageVPos-UserGetNormalVPosn()) > 2)
            //    ucImageVPos = UserGetNormalVPosn();
            ucDDCCiTxBuffer[9] = ucVstart100;//ucImageVPos;
        }
        break;
    case VCPOP_H_PHASE:    //phase
        if (GetInputSyncMode() == DIG_SYNC) {
            ReplyNA();
        }
        else{
            ucDDCCiTxBuffer[6] = 0x00;        //maximumHi
            ucDDCCiTxBuffer[7] = 100;        //maximumLo
            ucDDCCiTxBuffer[8] = 0x00;        //phaseHi
            // We return ucDDCCiPhase to DT tool for passing DT
            // If the difference is larget then 2, we return actual value!
            //if (abs(ucDDCCiPhase-UserGetNormalPhase()) > 2)
            //    ucDDCCiPhase = UserGetNormalPhase();
            ucDDCCiTxBuffer[9] = ucADCPhase100;//ucDDCCiPhase;
        }
        break;
    case VCPOP_ACTIVE_CTRL:        //0x52
        ucDDCCiTxBuffer[6] = 0x00;        //maximumHi
        ucDDCCiTxBuffer[7] = 0xff;        //maximumLo
        ucDDCCiTxBuffer[8] = 0x00;        //
        ucDDCCiTxBuffer[9] = 0x00;
        break;
    case VCPOP_INPUT:        //0x60
        ucDDCCiTxBuffer[6] = 0x00;        //maximumHi
        ucDDCCiTxBuffer[7] = 0x03;        //maximumLo
        ucDDCCiTxBuffer[8] = 0x00;        //
        if (UserData.ucInputSource == GetInputPortName(0)) {
            ucDDCCiTxBuffer[9] = 0x01;//analog
        }
        else if (UserData.ucInputSource == GetInputPortName(1)) {//else if (UserData.ucInputSource == INPUT_SC_DVI) {
            ucDDCCiTxBuffer[9] = 0x03;        //digital
        }
        else {//if (UserData.ucInputSource == INPUT_SC_HDMI) {
            ucDDCCiTxBuffer[9] = 0x04;//digital
        }
        break;
    case VCPOP_ROFFSET:        //0x6C
        ucDDCCiTxBuffer[6] = 0x00;        //maximumHi
        ucDDCCiTxBuffer[7] = 100;        //maximumLo
        ucDDCCiTxBuffer[8] = 0x00;        //B_GainHi
        ucDDCCiTxBuffer[9] = UserData.ucUserROffset;
        break;
    case VCPOP_GOFFSET:        //0x6E
        ucDDCCiTxBuffer[6] = 0x00;        //maximumHi
        ucDDCCiTxBuffer[7] = 100;        //maximumLo
        ucDDCCiTxBuffer[8] = 0x00;        //B_GainHi
        ucDDCCiTxBuffer[9] = UserData.ucUserGOffset;
        break;
    case VCPOP_BOFFSET:        //0x70
        ucDDCCiTxBuffer[6] = 0x00;        //maximumHi
        ucDDCCiTxBuffer[7] = 100;        //maximumLo
        ucDDCCiTxBuffer[8] = 0x00;        //B_GainHi
        ucDDCCiTxBuffer[9] = UserData.ucUserBOffset;
        break;
    case VCPOP_H_FREQ:
        ucDDCCiTxBuffer[6] = 0xff;
        temp = InputTiming.usHSyncFreq * 100;
        ucDDCCiTxBuffer[7] = (UCHAR)((ULONG)InputTiming.usHSyncFreq * 100>>16);
        ucDDCCiTxBuffer[8] = (UCHAR)(temp>>8);
        ucDDCCiTxBuffer[9] = (UCHAR)temp;
        break;
    case VCPOP_V_FREQ:
        ucDDCCiTxBuffer[6] = 0xff;
        ucDDCCiTxBuffer[7] = 0xff;
        temp = InputTiming.usVSyncFreq * 10;
        ucDDCCiTxBuffer[8] = (UCHAR)(temp>>8);
        ucDDCCiTxBuffer[9] = (UCHAR)temp;
        break;
    case VCPOP_PANEL_PIXEL:    //0xB2
        ucDDCCiTxBuffer[6] = 0x00;        //maximumHi
        ucDDCCiTxBuffer[7] = 0x08;        //maximumLo
        ucDDCCiTxBuffer[8] = 0x00;        //
        ucDDCCiTxBuffer[9] = 0x01;        //RGB vertical stripe
        break;
    case VCPOP_DISP_TYPE:    //0xB6
        ucDDCCiTxBuffer[6] = 0x00;        //maximumHi
        ucDDCCiTxBuffer[7] = 0x04;        //maximumLo
        ucDDCCiTxBuffer[8] = 0x00;        //displaytypeHi
        ucDDCCiTxBuffer[9] = 0x03;        //displaytypeLo
        break;
    case VCPOP_AUDIO:    //volume
        ucDDCCiTxBuffer[6] = 0x00;        //maximumHi
        ucDDCCiTxBuffer[7] = 100;        //maximumLo
        ucDDCCiTxBuffer[8] = 0x00;        //VolumeHi
        ucDDCCiTxBuffer[9] = UserData.ucVolume;    //VolumeLo 
        break;
    case VCPOP_MUTE:    //Mute
        ucDDCCiTxBuffer[6] = 0x00;        //maximumHi
        ucDDCCiTxBuffer[7] = 0x02;        //maximumLo
        ucDDCCiTxBuffer[8] = 0x00;        //VolumeHi
        ucDDCCiTxBuffer[9] = 2-(UCHAR)UserData.bAudioMute;    //VolumeLo
        break;
    case VCPOP_USE_TIME:    //usage time
        ucDDCCiTxBuffer[6] = 0xff;        //maximumHi
        ucDDCCiTxBuffer[7] = 0xff;        //maximumLo
        temp = SystemData.usPowerOnTimerH;
        ucDDCCiTxBuffer[8] = (UCHAR)(temp >> 8);        //displaytimeHi
        ucDDCCiTxBuffer[9] = (UCHAR)temp;        //displaytimeLo
        break;
    case VCPOP_APP_KEY:    //Application enable key
        ucDDCCiTxBuffer[6] = 0xff;        //maximumHi
        ucDDCCiTxBuffer[7] = 0xff;        //maximumLo
        ucDDCCiTxBuffer[8] = 0x00;        //
        ucDDCCiTxBuffer[9] = 0x6F;        //Philips Application enable key = 0x6f
        break;
    case VCPOP_CTRL_TYPE:    //0xC8
        ucDDCCiTxBuffer[6] = 0xff;        //maximumHi
        ucDDCCiTxBuffer[7] = 0xff;        //maximumLo
        ucDDCCiTxBuffer[8] = 0x00;        //
        ucDDCCiTxBuffer[9] = 0x12;        //DEFINE FOR PHILIPS BY PORTRAIT
        break;
    case VCPOP_FW_LEVEL:    //0xC9F/W level
        ucDDCCiTxBuffer[6] = 0xff;        //maximumHi
        ucDDCCiTxBuffer[7] = 0xff;        //maximumLo
        ucDDCCiTxBuffer[8] = (UCHAR)(FIRMWARE_VER>>8);
        ucDDCCiTxBuffer[9] = (UCHAR)FIRMWARE_VER;
        break;
    case VCPOP_OSD_LOCK:
        ucDDCCiTxBuffer[6] = 0x00;        //maximumHi
        ucDDCCiTxBuffer[7] = 0x02;        //maximumLo
        ucDDCCiTxBuffer[8] = 0x00;        //level 3
        ucDDCCiTxBuffer[9] = 2-(UCHAR)UserData.bOSDLock;
        break;
    case VCPOP_LANGUAGE:
        ucDDCCiTxBuffer[6] = 0x00;        //maximumHi
        ucDDCCiTxBuffer[7] = 0xff;        //maximumLo
        ucDDCCiTxBuffer[8] = 0x00;        //level 3

        switch (UserData.ucLanguage) {
            case OSDLANG_ENGLISH:
            ucDDCCiTxBuffer[9] = 0x02;
                break;
            case OSDLANG_FRENCH:
            ucDDCCiTxBuffer[9] = 0x03;
                break;
            case OSDLANG_GERMAN:
            ucDDCCiTxBuffer[9] = 0x04;
                break;
            case OSDLANG_ITALIAN:
            ucDDCCiTxBuffer[9] = 0x05;
                break;
            case OSDLANG_PORTUGUESE:
            ucDDCCiTxBuffer[9] = 0x08;
                break;
            case OSDLANG_RUSSIAN:
            ucDDCCiTxBuffer[9] = 0x09;
                break;
            case OSDLANG_SPANISH:
            ucDDCCiTxBuffer[9] = 0x0A;
                break;
            case OSDLANG_SCHINESE:
            ucDDCCiTxBuffer[9] = 0x0D;
                break;
            default:
                ucDDCCiTxBuffer[9] = 0x02;
                break;
        }

        break;
    case VCPOP_POWER_MODE:
        ucDDCCiTxBuffer[6] = 0x00;        //maximumHi
        ucDDCCiTxBuffer[7] = 0x04;        //maximumLo
        ucDDCCiTxBuffer[8] = 0x00;        //
        if (GetModeHandleState() == SOFT_POWER_OFF) {
                ucDDCCiTxBuffer[9] = 0x04;        //power status off
        }
        else if (GetModeHandleState() == POWER_SAVING_MODE) {
                ucDDCCiTxBuffer[9] = 0x02;        //power status standby
        }
        else {
            ucDDCCiTxBuffer[9] = 0x01;        //power status on
        }
        break;
    case VCPOP_SMARTIMAGE:
        ucDDCCiTxBuffer[6] = 0x00;
        ucDDCCiTxBuffer[7] = NUMBER_CE_MODES;
        ucDDCCiTxBuffer[8] = 0x00;        //level 3
/*        if (UserData.ucBFMode == CE_NTSC_76)
            ucDDCCiTxBuffer[9] = 0x01;
        else if (UserData.ucBFMode == CE_NTSC_80)
            ucDDCCiTxBuffer[9] = 0x02;
        else if (UserData.ucBFMode == CE_NVTCLR_1)
            ucDDCCiTxBuffer[9] = 0x03;
        else if (UserData.ucBFMode == CE_NVTCLR_2)
            ucDDCCiTxBuffer[9] = 0x08;
        else
            ucDDCCiTxBuffer[9] = 0x00;*/
        ucDDCCiTxBuffer[9] = UserData.ucBFMode;
        break;
    case VCPOP_MCC20:    //0xDF
        ucDDCCiTxBuffer[6] = 0xff;        //maximumHi
        ucDDCCiTxBuffer[7] = 0xff;        //maximumLo
        ucDDCCiTxBuffer[8] = 0x02;        //Version 2
        ucDDCCiTxBuffer[9] = 0x01;        //reversion 0
        break;
    default:
        ReplyNA();
        break;
    }
    GenTxCheckSum();
}

void SetVCP_Feature(void)
{
    USHRT k;

    switch (ucDDCCiRxBuffer[3]) {
        case VCPOP_NEW_CTRL:
            if (ucDDCCiRxBuffer[4] == 0) {
                if (ucDDCCiRxBuffer[5] == 1 ||
                    ucDDCCiRxBuffer[5] == 2 ||
                    ucDDCCiRxBuffer[5] == 0xff) {
                    ucNewControlValue = ucDDCCiRxBuffer[5];
                }
            }
            break;
        case VCPOP_RECALL: //recall
            UserRecallConfiguration();
            SetDdcciUpdUsrFlag();
            break;
        case VCPOP_RECALL_BC: //recall brightness/contrast
            UserData.ucBrightness = UserDataDefault.ucBrightness;
            UserData.ucContrast = UserDataDefault.ucContrast;
            UserSetContrast();
            UserSetBrightness();
            SetDdcciUpdUsrFlag();
            break;
        case VCPOP_RECALL_HV_POS:
            if (GetInputSyncMode() != DIG_SYNC) {
                UserRecallHVPosition();
                //ucImageVPos = UserGetNormalVPosn();
                //ucDDCCiPhase = UserGetNormalPhase();
                //SetDdcciUpdTmgFlag();
            }
            break;
        case VCPOP_RECALL_COLOR: //0x08
            UserRecallColor();
            SetDdcciUpdUsrFlag();
            break;
        case VCPOP_COLOR_REQ: //0x0C
            k = 3000 + (USHRT) ucDDCCiRxBuffer[5] * 50;
            if (ucDDCCiRxBuffer[4] != 0)
                k = 0xffff;
//            if (k < 5750)
//                UserData.ucColorTemp = CLRTMP_5000K;
            if (k < 7000)
                UserData.ucColorTemp = CLRTMP_6500K;
            else if (k < 7850)
                UserData.ucColorTemp = CLRTMP_7500K;
//            else if (k < 8750)
//               UserData.ucColorTemp = CLRTMP_8200K;
            else if (k < 10400)
                UserData.ucColorTemp = CLRTMP_9300K;
//           else
//               UserData.ucColorTemp = CLRTMP_11500K;
            UserSetColorTemp();
            SetDdcciUpdUsrFlag();
            break;
        case VCPOP_CLOCK: //clock
            if (ucDDCCiRxBuffer[5] > 100) { 
                ucDDCCiRxBuffer[5] = 100;
            }
            UserSetClock100(ucDDCCiRxBuffer[5]);
            SetDdcciUpdTmgFlag();
            break;
        case VCPOP_BRIGHT: //brightness
/*
            if (UserData.ucColorTemp == CLRTMP_sRGB) { //sRGB
                UserData.ucColorTemp = CLRTMP_6500K;
                UserSetColorTemp();
            }
*/
            UserData.ucBrightness = ucDDCCiRxBuffer[5]; //brightnessLo
            if (UserData.ucBrightness > MAXIMUM_BRIGHTNESS) {
                UserData.ucBrightness = MAXIMUM_BRIGHTNESS;
            }
            else if (UserData.ucBrightness < MINIMUM_BRIGHTNESS) {
                UserData.ucBrightness = MINIMUM_BRIGHTNESS;
            }
            UserSetBrightness();
            SetDdcciUpdUsrFlag();
            break;
        case VCPOP_CONTRAST: //contrast
/*
            if (UserData.ucColorTemp == CLRTMP_sRGB) { //sRGB
                UserData.ucColorTemp = CLRTMP_6500K;
                UserSetColorTemp();
            }
*/          
            UserData.ucContrast = ucDDCCiRxBuffer[5];//contrastLo
            if (UserData.ucContrast > MAXIMUM_CONTRAST) {
                UserData.ucContrast = MAXIMUM_CONTRAST;
            }
            else if (UserData.ucContrast < MINIMUM_CONTRAST) {
                UserData.ucContrast = MINIMUM_CONTRAST;
            }
            UserSetContrast();
            SetDdcciUpdUsrFlag();
            break;
        case VCPOP_SEL_COLOR: //color input
        /*
         01 : sRGB, 02 : Display native, 03 : 4000 K, 04 : 5000 K, 05 : 6500 K, 06 : 7500 K, 07 : 8200 K,
         08 : 9300 K, 09 : 10000 K, 0A : 11500 K, 0B : User 1, 0C : User 2, 0D : User 3
         */
            switch (ucDDCCiRxBuffer[5]) {
//                case 0x01:
//                    k = CLRTMP_sRGB;
//                    break;
                    //        case 0x02:
                    //            k = COLOR_ORIGIN;
                    //            break;
//                case 0x04:
//                    k = CLRTMP_5000K;
//                    break;
                case 0x05:
                    k = CLRTMP_6500K;
                    break;
                case 0x06:
                    k = CLRTMP_7500K;
                    break;
//                case 0x07:
//                   k = CLRTMP_8200K;
//                    break;
                case 0x08:
                    k = CLRTMP_9300K;
                    break;
//                case 0x0A:
//                    k = CLRTMP_11500K;
//                    break;
                case 0x0B:
                    k = CLRTMP_USER;
                    break;
                default:
                    k = UserData.ucColorTemp;
                    break;
            }
            if (UserData.ucColorTemp != k) {
                UserData.ucColorTemp = k;
                UserSetColorTemp();
                SetDdcciUpdUsrFlag();
            }
            break;
        case VCPOP_RGAIN: //red
            if (UserData.ucColorTemp != CLRTMP_USER) {
                UserData.ucColorTemp = CLRTMP_USER;
            }

            if (ucDDCCiRxBuffer[5] > 100)
                ucDDCCiRxBuffer[5] = 100;
            UserData.ucUserRGain = ucDDCCiRxBuffer[5];
            UserSetRGain();
            SetDdcciUpdUsrFlag();
            break;
        case VCPOP_GGAIN: //green
            if (UserData.ucColorTemp != CLRTMP_USER) {
                UserData.ucColorTemp = CLRTMP_USER;
            }

            if (ucDDCCiRxBuffer[5] > 100) {
                ucDDCCiRxBuffer[5] = 100;
            }
            UserData.ucUserGGain = ucDDCCiRxBuffer[5];
            UserSetGGain();
            SetDdcciUpdUsrFlag();
            break;
        case VCPOP_BGAIN: //blue
            if (UserData.ucColorTemp != CLRTMP_USER) {
                UserData.ucColorTemp = CLRTMP_USER;
            }

            if (ucDDCCiRxBuffer[5] > 100) {
                ucDDCCiRxBuffer[5] = 100;
            }
            UserData.ucUserBGain = ucDDCCiRxBuffer[5];
            UserSetBGain();
            SetDdcciUpdUsrFlag();
            break;
        case VCPOP_AUTO_SET: //autosetup
            if (GetInputSyncMode() != DIG_SYNC) {
                UserPerformAutoTune();
                //ucImageVPos = UserGetNormalVPosn();
                //ucDDCCiPhase = UserGetNormalPhase();
                SetDdcciUpdTmgFlag();
            }
            break;
        case VCPOP_AUTO_COLOR: // auto color
            if (GetInputSyncMode() != DIG_SYNC) {
                OSDCloseAll();
                AutoColor();
            }
            SetDdcciUpdCalFlag();
            break;
        case VCPOP_H_POS: //horizontal position
            if (ucDDCCiRxBuffer[5] > 100) {
                ucDDCCiRxBuffer[5] = 100;
            }
            UserSetHPosn100(ucDDCCiRxBuffer[5]);
            SetDdcciUpdTmgFlag();
            break;
        case VCPOP_V_POS: //vertical position    //2005-01-24 mingyu
            if (ucDDCCiRxBuffer[5] > 100) {
                ucDDCCiRxBuffer[5] = 100;
            }
            //ucImageVPos = ucDDCCiRxBuffer[5];
            UserSetVPosn100(ucDDCCiRxBuffer[5]);
            ucVstart100 = ucDDCCiRxBuffer[5];
            SetDdcciUpdTmgFlag();
            break;
        case VCPOP_H_PHASE: //phase
            if (ucDDCCiRxBuffer[5] > 100) {
                ucDDCCiRxBuffer[5] = 100;
            }
            //ucDDCCiPhase = ucDDCCiRxBuffer[5];
            UserSetPhase100(ucDDCCiRxBuffer[5]);
            ucADCPhase100 = ucDDCCiRxBuffer[5];
            SetDdcciUpdTmgFlag();
            break;
        case VCPOP_INPUT: // Jude 07/25/2006
            if (ucDDCCiRxBuffer[5] == 0x03) {
                UserData.ucInputSource = GetInputPortName(1);//INPUT_SC_DVI;
            }
            else if (ucDDCCiRxBuffer[5] == 0x11) {//v05_120608_1430_OSD#6
                UserData.ucInputSource = GetInputPortName(2);//INPUT_SC_HDMI;
            }
            else if(ucDDCCiRxBuffer[5] == 0x01){
                UserData.ucInputSource = GetInputPortName(0);//INPUT_SC_VGA;
            }
            UserSetInputSource();
            SetDdcciUpdUsrFlag();
            break;
        case VCPOP_ROFFSET:
            if (ucDDCCiRxBuffer[5] > 100) {
                ucDDCCiRxBuffer[5] = 100;
            }
            UserData.ucUserROffset = ucDDCCiRxBuffer[5];
            UserSetROffset();
            SetDdcciUpdUsrFlag();
            break;
        case VCPOP_GOFFSET:
            if (ucDDCCiRxBuffer[5] > 100) {
                ucDDCCiRxBuffer[5] = 100;
            }
            UserData.ucUserGOffset = ucDDCCiRxBuffer[5];
            UserSetGOffset();
            SetDdcciUpdUsrFlag();
            break;
        case VCPOP_BOFFSET:
            if (ucDDCCiRxBuffer[5] > 100) {
                ucDDCCiRxBuffer[5] = 100;
            }
            UserData.ucUserBOffset = ucDDCCiRxBuffer[5];
            UserSetBOffset();
            SetDdcciUpdUsrFlag();
            break;
        case VCPOP_OSD_LOCK: //0xCA
            if (ucDDCCiRxBuffer[5] == 1) {
                UserData.bOSDLock = 1;
            }
            else if (ucDDCCiRxBuffer[5] == 2) {
                UserData.bOSDLock = 0;
            }
            SetDdcciUpdUsrFlag();
            break;
        case VCPOP_LANGUAGE:

            switch (ucDDCCiRxBuffer[5]) {
                case 0x02:
                UserData.ucLanguage = OSDLANG_ENGLISH;
                    break;
                case 0x03:
                UserData.ucLanguage = OSDLANG_FRENCH;
                    break;
                case 0x04:
                UserData.ucLanguage = OSDLANG_GERMAN;
                    break;
                case 0x05:
                UserData.ucLanguage = OSDLANG_ITALIAN;
                    break;
                case 0x08:
                UserData.ucLanguage = OSDLANG_PORTUGUESE;
                    break;
                case 0x09:
                UserData.ucLanguage = OSDLANG_RUSSIAN;
                    break;
                case 0x0A:
                UserData.ucLanguage = OSDLANG_SPANISH;
                    break;
                case 0x0D:
                UserData.ucLanguage = OSDLANG_SCHINESE;
                    break;
                default:
                    UserData.ucLanguage = OSDLANG_ENGLISH;
                    break;
            }

            UserSetLanguage();
            SetDdcciUpdUsrFlag();
            break;
        case VCPOP_POWER_MODE: //0xD6
            if (ucDDCCiRxBuffer[5] == 1) { //power status on
                if ((GetModeHandleState() == SOFT_POWER_OFF) ||
                    (GetModeHandleState() == POWER_SAVING_MODE)) {
                    SetDdcciPwrOnFlag();
                }
            }
            else if (ucDDCCiRxBuffer[5] == 2) { //power status standby
                if (GetModeHandleState() != POWER_SAVING_MODE) {
                    SetDdcciPwrSavingFlag();
                }
            }
            else if (ucDDCCiRxBuffer[5] == 4) { //power status off
                if (GetModeHandleState() != SOFT_POWER_OFF) {
                    SetDdcciPwrOffFlag();
                }
            }
            break;
        case VCPOP_SMARTIMAGE:
            //if ( ucDDCCiRxBuffer[5]==0x00 )
            //    UserData.ucBFMode = LF_MODE_OFF;
            //else if ( ucDDCCiRxBuffer[5]==0x01 )
            //    UserData.ucBFMode = LF_MODE_OFFICE_WORK;
            //else if ( ucDDCCiRxBuffer[5]==0x02 )
            //    UserData.ucBFMode = LF_MODE_ImageViewing;
            //else if ( ucDDCCiRxBuffer[5]==0x03 )
            //    UserData.ucBFMode = LF_MODE_Entertainment;
            //else if ( ucDDCCiRxBuffer[5]==0x08 )
            //    UserData.ucBFMode = LF_MODE_Economic;
            UserData.ucBFMode = ucDDCCiTxBuffer[5];
            UserSetBF();
            SetDdcciUpdUsrFlag();
            break;
        case VCPOP_AUDIO: //volume
            UserData.ucVolume = ucDDCCiRxBuffer[5]; //volumeLo
            if (UserData.bAudioMute) {
                UserData.bAudioMute = FALSE;
            }
            UserSetVolume();
            SetDdcciUpdUsrFlag();
            break;
        case VCPOP_MUTE:
            if (ucDDCCiRxBuffer[5] == 1) {
                UserData.bAudioMute = 1;
            }
            else if (ucDDCCiRxBuffer[5] == 2) {
                UserData.bAudioMute = 0;
            }
            UserSetAudioMute();
            SetDdcciUpdUsrFlag();
            break;
#if ENABLE_NVT_HDCP_WRITER == ON
        case VCPOP_NVT_HDCP_START:
            StartHDCPStoring();
            break;
        case VCPOP_NVT_HDCP_WRITE:
            StoreHDCP(ucDDCCiRxBuffer + 4, (ucDDCCiRxBuffer[1] & 0x7f) - 2);
            break;
        case VCPOP_NVT_HDCP_CHKSUM:
            ucDDCCiTxBuffer[0] = ACCESSBUS_ADDR;
            ucDDCCiTxBuffer[1] = 0x82;
            ucDDCCiTxBuffer[2] = CMDOP_SET_VCP;
            if (CheckHDCPChkSum() != 0)
                ucDDCCiTxBuffer[3] = 0xef;
            else
                ucDDCCiTxBuffer[3] = 0xff;
            ucDDCCiTxOut = 0;
            ucDDCCiTxIn = 4;
            GenTxCheckSum();
            break;
#endif
    }
}

/*
void WaitDDCTxOut()
{
    USHRT local_timer;
    local_timer = GetTimerTick();
    do {
        if (ucDDCCiTxOut == 0) {
            break;
        }
        ResetWDTimer();
    } while((GetTimerTick() - local_timer) < 100);
}
*/

void SetVCP_Capabilities(void)
{
    code UCHAR ucVCPCapTab_Analog[]={
        "(prot(monitor)"
        "type(lcd)"
        "model(FALCON)"
        "cmds(01 02 03 07 0C 4E F3 E3)"
        "vcp(02 04 05 06 08 0B 0C 0E 10 12 14(01 04 05 06 07 08 0A 0B) 16 18 1A 1E 20 30 3E 6C 6E 70 "
        "AC AE B6 C0 C6 C8 C9 CA CC(00 02 03 04 05 08 09 0A 0D) D6(01 04) DC(00 01 02 03 04) DF "
        "60(01 03) "
        "62 8D "
        "FF)"
        "mswhql(1)mccs_ver(2.0)asset_eep(32)mpu_ver(01))"
    };
    code UCHAR ucVCPCapTab_DVI[]={
        "(prot(monitor)"
        "type(lcd)"
        "model(FALCON)"
        "cmds(01 02 03 07 0C 4E F3 E3)"
        "vcp(02 04 05 08 0B 0C 10 12 14(01 04 05 06 07 08 0A 0B) 16 18 1A 6C 6E 70 "
        "AC AE B6 C0 C6 C8 C9 CA CC(00 02 03 04 05 08 09 0A 0D) D6(01 04) DC(00 01 02 03 04) DF "
        "60(01 03) "
        "62 8D "
        "FF)"
        "mswhql(1)mccs_ver(2.0)asset_eep(32)mpu_ver(01))"
    };
    
    UCHAR i;
    USHRT l,offset;
 
    //WaitDDCTxOut();
    
    if (GetInputSyncMode() == DIG_SYNC) {
        l = sizeof(ucVCPCapTab_DVI)-1;
    }
    else {
        l = sizeof(ucVCPCapTab_Analog)-1;
    }
    offset = ucDDCCiRxBuffer[3];
    offset <<= 8;
    offset |= ucDDCCiRxBuffer[4];
    ucDDCCiTxBuffer[0] = ACCESSBUS_ADDR;
    ucDDCCiTxBuffer[2] = 0xe3;
    ucDDCCiTxBuffer[3] = ucDDCCiRxBuffer[3];
    ucDDCCiTxBuffer[4] = ucDDCCiRxBuffer[4];
    ucDDCCiTxOut = 0;
    if(offset > l){        //end of data
        l = 32;
        ucDDCCiTxBuffer[1] = 0xa3;
        ucDDCCiTxIn = 37;
        for(i=0; i<l; i++){
            ucDDCCiTxBuffer[5+i] = 0x20;
        }
        GenTxCheckSum();
    }
    else{
        l = l - offset;
        if(l > 32){    //max.
            l = 32;
            ucDDCCiTxBuffer[1] = 0xa3;
            ucDDCCiTxIn = 37;
        }
        else{
            ucDDCCiTxBuffer[1] = 0x83 + l;
            ucDDCCiTxIn = l + 5;
        }
        
        if (GetInputSyncMode() == DIG_SYNC) {
            for(i=0; i<l; i++){
                ucDDCCiTxBuffer[5+i] = ucVCPCapTab_DVI[offset+i];
            }
        }
        else{
            for(i=0; i<l; i++){
                ucDDCCiTxBuffer[5+i] = ucVCPCapTab_Analog[offset+i];
            }
        }
        GenTxCheckSum();
    }
}

void GetTiming(void)
{
    USHRT temp;
    UCHAR pol;

    ucDDCCiTxBuffer[0] = ACCESSBUS_ADDR;
    ucDDCCiTxBuffer[1] = 0x06;
    ucDDCCiTxBuffer[2] = 0x4e;

    if (InputTiming.ucHVPolarity == HPVP) {
        pol = 0x03;
    }
    else if (InputTiming.ucHVPolarity == HPVN) {
        pol = 0x01;
    }
    else if (InputTiming.ucHVPolarity == HNVP) {
        pol = 0x02;
    }
    else {
        pol = 0x00;
    }

    if (IsOutOfRange() == FALSE) {
        ucDDCCiTxBuffer[3] = pol;
    }
    else {
        ucDDCCiTxBuffer[3] = pol | BIT7;
    }
    
    temp = InputTiming.usHSyncFreq * 10;
    ucDDCCiTxBuffer[4] = (UCHAR)(temp >> 8);
    ucDDCCiTxBuffer[5] = (UCHAR)temp;
    temp = InputTiming.usVSyncFreq * 10;
    ucDDCCiTxBuffer[6] = (UCHAR)(temp >> 8);
    ucDDCCiTxBuffer[7] = (UCHAR)temp;
    ucDDCCiTxOut = 0;
    ucDDCCiTxIn = 8;
    GenTxCheckSum();
}

void GenTxCheckSum(void)
{
    UCHAR i;
    ucDDCCiTxChecksum = 0x50;
    for(i=0; i<ucDDCCiTxIn; i++) {
        ucDDCCiTxChecksum ^= ucDDCCiTxBuffer[i];
    }
    ucDDCCiTxBuffer[i] = ucDDCCiTxChecksum;
}

