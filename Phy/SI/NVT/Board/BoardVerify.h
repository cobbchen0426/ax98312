/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/
#ifndef __BOARD_VFY_H__
#define __BOARD_VFY_H__

#if PCBA_SCALER != SCALER_TYPE
#error "Scaler on PCBA doesn't match with the scaler type in KeilC! Please make sure what scaler you use!"
#endif

#endif //__BOARD_VFY_H__
