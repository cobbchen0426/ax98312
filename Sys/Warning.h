/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/

#ifndef __WARNING_H__
#define __WARNING_H__

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************

//******************************************************************************
// M A C R O   D E F I N I T I O N S
//******************************************************************************
#if MCU_UART_OUTPUT != 0
#warning "The UART port is directed to I2C port!"
#endif
#if ENABLE_DEMO_HDCP_KEY == ON
#warning "The HDCP demo key is enabled!"
#endif
#if ENABLE_NVT_HDCP_WRITER == ON
#warning "The Novatek HDCP Key receiver is enabled!"
#endif
#if ENABLE_HDMI_PRETEST == ON
#warning "The HDMI PRETEST Mode is enabled!"
#endif
#if ENABLE_DEMO_DP_EDID == ON
#warning "The DP demo EDID is enabled!"
#endif
#if ENABLE_DEMO_MHL_EDID == ON
#warning "The MHL demo EDID is enabled!"
#endif
#if ENABLE_FE2P == ON
#if ENABLE_DIRECT_FE2P == ON
#warning "The FE2P Direct Mode is enabled!"
#else
#warning "The FE2P Normal Mode is enabled!"
#endif
#endif
#if ENABLE_DP_AUX_MONITOR == ON
#warning "The AUX Strobe function is enabled!" 
#endif 


//******************************************************************************
// D A T A   T Y P E   D E F I N E S
//******************************************************************************

//******************************************************************************
// V A R I A B L E S   P R O T O T Y P E
//******************************************************************************

//******************************************************************************
// F U N C T I O N   P R O T O T Y P E S
//******************************************************************************

#endif //__WARNING_H__
