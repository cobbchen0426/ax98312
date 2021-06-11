/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/

#ifndef __MCU_REG_H__
#define __MCU_REG_H__

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************
#include "Typedef.h"

//******************************************************************************
// M A C R O   D E F I N I T I O N S
//******************************************************************************

//******************************************************************************
// D A T A   T Y P E   D E F I N E S
//******************************************************************************

//******************************************************************************
// V A R I A B L E S   P R O T O T Y P E
//******************************************************************************
//GPIO PORT CONTROL REGISTERS
extern xdata UCHAR volatile PortA;
extern xdata UCHAR volatile PortB;
extern xdata UCHAR volatile PortC;
extern xdata UCHAR volatile PortD;
extern xdata UCHAR volatile PortE;
//GPIO PORT DIRECTION CONTROL REGISTERS
extern xdata UCHAR volatile RDPA_REG;
extern xdata UCHAR volatile RDPB_REG;
extern xdata UCHAR volatile RDPC_REG;
extern xdata UCHAR volatile RDPD_REG;
extern xdata UCHAR volatile RDPE_REG;
//WATCH-DOG TIMER CONTROL REGISTER
extern xdata UCHAR volatile CLR_WDT;
//A/D CONVERTER CONTROL REGISTERS
extern xdata UCHAR volatile ADC_CON;
extern xdata UCHAR volatile ADC_CON2;
extern xdata UCHAR volatile ADC_REG0;
extern xdata UCHAR volatile ADC_REG1;
extern xdata UCHAR volatile ADC_REG2;
extern xdata UCHAR volatile ADC_REG3;
extern xdata UCHAR volatile ADC_REG4;
extern xdata UCHAR volatile ADC_REG5;
extern xdata UCHAR volatile ADC_REG6;
extern xdata UCHAR volatile ADC_REG7;
//PWM CHANNEL ENABLE CONTROL REGISTERS
extern xdata UCHAR volatile ENPWM_LB;
extern xdata UCHAR volatile ENPWM_HB;
extern xdata UCHAR volatile ENPWM_UB;
//PWM CHANNEL CONTROL REGISTERS
extern xdata UCHAR volatile PWM_REG0;
extern xdata UCHAR volatile PWM_REG1;
extern xdata UCHAR volatile PWM_REG2;
extern xdata UCHAR volatile PWM_REG3;
extern xdata UCHAR volatile PWM_REG4;
extern xdata UCHAR volatile PWM_REG5;
extern xdata UCHAR volatile PWM_REG6;
extern xdata UCHAR volatile PWM_REG7;
extern xdata UCHAR volatile PWM_REG8;
extern xdata UCHAR volatile PWM_REG9;
extern xdata UCHAR volatile PWM_REG10;
extern xdata UCHAR volatile PWM_REG11;
//DDC PORT-0 CONTROL REGISTERS
extern xdata UCHAR volatile DDC_CTL0;
extern xdata UCHAR volatile DDC_ADDR0;
//DDC PORT-1 CONTROL REGISTERS
extern xdata UCHAR volatile DDC_CTL1;
extern xdata UCHAR volatile DDC_ADDR1;
//DDC PORT-2 CONTROL REGISTERS
extern xdata UCHAR volatile DDC_CTL2;
extern xdata UCHAR volatile DDC_ADDR2;
//DDC PORT-3 CONTROL REGISTERS
extern xdata UCHAR volatile DDC_CTL3;
extern xdata UCHAR volatile DDC_ADDR3;
//INTERRUPT SOURCE CONTROL REGISTER
extern xdata UCHAR volatile INT_SRC;
    #define INT_IIC2        0x80
    #define INT_IIC3        0x40
    #define INT_IIC0        0x20
    #define INT_EXT         0x10
    #define INT_HDMI        0x08
    #define INT_COP         0x04
    #define INT_IIC1        0x02
    #define INT_SC          0x01
//EXTERNAL INTERRUPT CONTROL REGISTERS
extern xdata UCHAR volatile INTEXT_FLG;
    #define INT_TIMEA       0x20
    #define INT_LPD         0x10
    #define INTE3           0x08
    #define INTE2           0x04
    #define INTE1           0x02
    #define INTE0           0x01
extern xdata UCHAR volatile INTEXT_EN;
	#define INTE3_EDG		0x80
	#define INTE2_EDG		0x40
	#define INTE1_EDG		0x20
	#define INTE0_EDG		0x10

//SCALER INTERRUPT CONTROL REGISTER
extern xdata UCHAR volatile INTSC_EN;
    #define HDMI_EN    0x08
    #define SC_EN      0x01
//LOW POWER DETECT
extern xdata UCHAR volatile LPD_CTRL;
extern xdata UCHAR volatile LPD0_ADJ;
//MHL INTERRUPT
extern xdata UCHAR volatile DP_SRC;
extern xdata UCHAR volatile MHL_SRC;
	#define INT_MHL          0x80
//IIC PORT-0 CONTROL REGISTERS
extern xdata UCHAR volatile IIC0_CFG;
    #define PRENACK         0x80
    #define SEND_ACK        0x40
    #define STOP            0x20
    #define RESTART         0x10
    #define IIC_400K        0x0c
    #define IIC_200K        0x08
    #define IIC_100K        0x04
    #define IIC_50K         0x00
    #define MASTER          0x02
    #define WAIT_GEN        0x01
extern xdata UCHAR volatile IIC0_STATUS;
    #define DOWRITE         0x80
    #define DOREAD          0x40
    #define TXIN_NULL       0x20
    #define TX_NULL         0x10
    #define RXIN_FULL       0x08
    #define RX_FULL         0x04
    #define BUS_START       0x02
    #define BUS_STOP        0x01
extern xdata UCHAR volatile IIC0_INT_EN;
extern xdata UCHAR volatile IIC0_INT_FLG;
    #define INTA            0x80
    #define INTTX           0x40
    #define INTRX           0x20
    #define INTNAK          0x10
    #define INTLOST         0x08
    #define SEND_START      0x02
    #define SEND_STOP       0x01
extern xdata UCHAR volatile IIC0_INT_CLR;
    #define CLR_TX_FIFO        0x04
    #define CLR_FIFO        0x02
extern xdata UCHAR volatile IIC0_TXDATA;
extern xdata UCHAR volatile IIC0_RXDATA;
extern xdata UCHAR volatile IIC0_ADDR;
//IIC PORT-1 CONTROL REGISTERS
extern xdata UCHAR volatile IIC1_CFG;
extern xdata UCHAR volatile IIC1_STATUS;
extern xdata UCHAR volatile IIC1_INT_EN;
extern xdata UCHAR volatile IIC1_INT_FLG;
extern xdata UCHAR volatile IIC1_INT_CLR;
extern xdata UCHAR volatile IIC1_TXDATA;
extern xdata UCHAR volatile IIC1_RXDATA;
extern xdata UCHAR volatile IIC1_ADDR;
//IIC PORT-2 CONTROL REGISTERS
extern xdata UCHAR volatile IIC2_CFG;
extern xdata UCHAR volatile IIC2_STATUS;
extern xdata UCHAR volatile IIC2_INT_EN;
extern xdata UCHAR volatile IIC2_INT_FLG;
extern xdata UCHAR volatile IIC2_INT_CLR;
extern xdata UCHAR volatile IIC2_TXDATA;
extern xdata UCHAR volatile IIC2_RXDATA;
extern xdata UCHAR volatile IIC2_ADDR;
//IIC PORT-3 CONTROL REGISTERS
extern xdata UCHAR volatile IIC3_CFG;
extern xdata UCHAR volatile IIC3_STATUS;
extern xdata UCHAR volatile IIC3_INT_EN;
extern xdata UCHAR volatile IIC3_INT_FLG;
extern xdata UCHAR volatile IIC3_INT_CLR;
extern xdata UCHAR volatile IIC3_TXDATA;
extern xdata UCHAR volatile IIC3_RXDATA;
extern xdata UCHAR volatile IIC3_ADDR;
//MISC CONTROL REGISTERS
extern xdata UCHAR volatile CPU_CLK;
extern xdata UCHAR volatile BANK_SET;
extern xdata UCHAR volatile DDC_THRES;
extern xdata UCHAR volatile SC_HW_RST;
extern xdata UCHAR volatile LDO_ADJ;
extern xdata UCHAR volatile IIC_MASK;
extern xdata UCHAR volatile UART_MUX;
extern xdata UCHAR volatile SC_CR_MUX;
extern xdata UCHAR volatile HDCP_MUX;
extern xdata UCHAR volatile PA47_CURR;
extern xdata UCHAR volatile SPI_CURR;
extern xdata UCHAR volatile PD46_CURR;
extern xdata UCHAR volatile CURR_ADJ1;
extern xdata UCHAR volatile CURR_ADJ2;
extern xdata UCHAR volatile SLEW_CTL;
extern xdata UCHAR volatile IIC_MASK_CTRL;
//SPI INTERFACE CONTROL REGISTERS
extern xdata UCHAR volatile SPI_OPTION;
extern xdata UCHAR volatile CORE_FIX;
extern xdata UCHAR volatile SPI_IDLE_CNT; 
//SDMA
extern xdata UCHAR volatile SDMA_TYPE;
extern xdata UCHAR volatile SDMA_TADH;
extern xdata UCHAR volatile SDMA_TADL;
extern xdata UCHAR volatile SDMA_AH;
extern xdata UCHAR volatile SDMA_AL;
extern xdata UCHAR volatile SDMA_LEN1;
extern xdata UCHAR volatile SDMA_LEN2;
extern xdata UCHAR volatile SDMA_SDIV;
//SYNC COUNTER CONTROL REGISTERS
extern xdata UCHAR volatile CNT_CTRL;
extern xdata UCHAR volatile HS_CNT_LB;
extern xdata UCHAR volatile HS_CNT_HB;
extern xdata UCHAR volatile SOG_CNT_LB;
extern xdata UCHAR volatile SOG_CNT_HB;
extern xdata UCHAR volatile VS_CNT;
//GPIO PORT TYPE CONTROL REGISTERS
extern xdata UCHAR volatile PTA_PP_REG;
extern xdata UCHAR volatile PTB_PP_REG;
extern xdata UCHAR volatile PTC_PP_REG;
extern xdata UCHAR volatile PTD_PP_REG;
extern xdata UCHAR volatile PTE_PP_REG;
extern xdata UCHAR volatile PTA_PU_REG;
extern xdata UCHAR volatile PTB_PU_REG;
extern xdata UCHAR volatile PTC_PU_REG;
extern xdata UCHAR volatile PTD_PU_REG;
extern xdata UCHAR volatile PTE_PU_REG;
extern xdata UCHAR volatile PT3_PU_REG;
extern xdata UCHAR volatile ADC_5V_EN;
//DISPLAYPORT CONTROL
extern xdata UCHAR volatile DP_CTRL;
//AO DETECT
extern xdata UCHAR volatile AO_DETECT;
//Watch-Dog #2 Timer Control Register
extern xdata UCHAR volatile CLR_WDT2;
extern xdata UCHAR volatile WDT2_SEL;
// EDID SRAM
extern xdata UCHAR volatile EDID_SRAM_BUFF0[256];
extern xdata UCHAR volatile EDID_SRAM_BUFF1[256];
extern xdata UCHAR volatile EDID_SRAM_BUFF2[256];
extern xdata UCHAR volatile EDID_SRAM_BUFF3[256];

//******************************************************************************
// F U N C T I O N   P R O T O T Y P E S
//******************************************************************************

#endif //__MCUREG_H__
