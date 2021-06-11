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

//******************************************************************************
// F U N C T I O N   B O D Y S
//******************************************************************************

/**************************************************************************//**
 * According to the v start position and v active length, report the present image is full-screen or not.
 * @param v_beg Vertical start position.
 * @param v_act Vertical active length.
 * @return TRUE if the present image is v_act not full-screen else FALSE.
 ******************************************************************************/
BOOL IsVNonFullScreen(USHRT v_beg, USHRT v_act)
{
    USHRT cap_vlen;
    USHRT vtotal;
    cap_vlen = GetVCaptureSize();
    vtotal = GetInputVTotal();
    if ((v_beg > (vtotal-cap_vlen))) {
        return TRUE;
    }
    if (v_act < (cap_vlen - 10)) {
        return TRUE;
    }
    return FALSE;
}

/**************************************************************************//**
 * According to the h start position and h active length, report the present image is full-screen or not.
 * @param h_beg Horizontal start position.
 * @param h_act Horizontal active length.
 * @return TRUE if the present image h_act is not full-screen else FALSE.
 ******************************************************************************/
BOOL IsHNonFullScreen(USHRT h_beg, USHRT h_act)
{
    USHRT cap_hwid;
    cap_hwid = GetHCaptureSize();
    h_beg = 0; // Disable compile warning only.
	h_act = (ULONG)h_act * InputTiming.usHTotal50 / GetAngInputHTotal();
    if (((cap_hwid/10) < abs(cap_hwid-h_act))) {
        return TRUE;
    }
    return FALSE;
}

/**************************************************************************//**
 * According to the h/v start position and h/v active length, report the present image is full-screen or not.
 * @param h_beg Horizontal start position.
 * @param v_beg Vertical start position.
 * @param h_act Horizontal active length.
 * @param v_act Vertical active length.
 * @return TRUE if the present image is not full-screen else FALSE.
 ******************************************************************************/
/* 
BOOL IsNonFullScreen(USHRT h_beg, USHRT v_beg, USHRT h_act, USHRT v_act) 
{
    USHRT cap_hwid, cap_vlen;
    USHRT vtotal;

    cap_hwid = GetHCaptureSize();
    cap_vlen = GetVCaptureSize();
    vtotal = GetInputVTotal();

#if 0
    if ((v_beg > (vtotal-cap_vlen)) || 
        (v_beg < InputTiming.usVStartMin) || 
        (v_beg > InputTiming.usVStartMax) ||
        (h_beg < InputTiming.usHStartMin) || 
        (h_beg > InputTiming.usHStartMax) ||
        ((cap_hwid*0.06) < abs(cap_hwid-h_act)) ||
        ((cap_vlen*0.06) < abs(cap_vlen-v_act))
       ) {
        return TRUE;
    }
#else
	h_beg = 0; // Disable compile warning only.
	h_act = (ULONG)h_act * InputTiming.usHTotal50 / GetAngInputHTotal();
    if ((v_beg > (vtotal-cap_vlen)) || 
        ((cap_hwid/10) < abs(cap_hwid-h_act))) {
        return TRUE;
    }
#endif
    
    if (v_act < (cap_vlen - 10)) {
        return TRUE;
    }
    
    return FALSE;
}
*/