/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/
#ifndef __LC_LC550EUN_SFM2__
#define __LC_LC550EUN_SFM2__

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************

//******************************************************************************
// G L O B A L   D E F I N I T I O N S
//******************************************************************************
#define PANEL_NAME              "LC550EUN-SFM2"
#define PANEL_TYPE              (NVT|RES_1920X1080)
#define PANEL_DUAL_PORT_LVDS    1
#define PANEL_COLOR_DEPTH       8
#define PANEL_DE_MODE           1
#define PANEL_PORT_SWAP         0
#define PANEL_BIT_SHIFT         0

#define PANEL_WIDTH             1920
#define PANEL_HEIGHT            1080

#define PANEL_MIN_LVDS_CLK      110000000 //Hz
#define PANEL_MAX_LVDS_CLK      180000000 //Hz

#define PANEL_MIN_HTOTAL        2030
#define PANEL_TYP_HTOTAL        2200
#define PANEL_MAX_HTOTAL        2800

#define PANEL_MIN_VTOTAL        1110
#define PANEL_TYP_VTOTAL        1130
#define PANEL_MAX_VTOTAL        2047

#define PANEL_HSYNC_WIDTH       ((PANEL_MIN_HTOTAL - PANEL_WIDTH) / 3 / 8) * 8
#define PANEL_HSYNC_BACKPORCH   ((PANEL_MIN_HTOTAL - PANEL_WIDTH) / 3 / 8) * 8
#define PANEL_HACTIVE_BEG       PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACKPORCH

#define PANEL_VSYNC_WIDTH       2
#define PANEL_VSYNC_BACKPORCH   3
#define PANEL_VACTIVE_BEG       PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACKPORCH

#define PANEL_DISP_HSYNC_POL    0 //0:Active low, 1:Active high
#define PANEL_DISP_VSYNC_POL    0 //0:Active low, 1:Active high
#define PANEL_DISP_DE_POL       1 //0:Active low, 1:Active high

#define PANEL_FRC_OUTPUT_VSYNC  600 //0.1Hz
#define PANEL_PAD_DRIVE         0x00

#define PANEL_LVDS_SWING        LVDS_SWING_450
#define PANEL_DCLK_SSC          0x2D

#define DT16A                   0x00
#define DT158                   0x33
#define DT1D8                   0x00
#define DT1DA                   0x90
#define DT1DB                   0x00

#define PANEL_POWER_UP_TIME     25
#define PANEL_INVTER_UP_TIME    100
#define PANEL_POWER_DOWN_TIME   25
#define PANEL_INVTER_DOWN_TIME  100
#define PANEL_OFF_ON_TIME       1000

#define PANEL_LED_VOLTAGE_MAX   58
#define PANEL_LED_VOLTAGE_TYP   50
#define PANEL_LED_BINCURRENT    25
#define PANEL_LED_STR_NO        4

#define ADC_OFFSET_ADJ          4
#define ADC_GAIN_ADJ            0



#define	DEFAULT_INVERTER_VAL	255

#define GAMMA_TOTAL_STEP		7		//1.9~2.5
#define	DEFAULT_GAMMA_INDEX		4		//2.3

#define FACTORY_6500K_R			255	// FuncBuf[pCONTRAST] 6500K R
#define FACTORY_6500K_G			213	// FuncBuf[pCONTRAST] 6500K G
#define FACTORY_6500K_B			182	// FuncBuf[pCONTRAST] 6500K B
#define FACTORY_7500K_R			255	// FuncBuf[pCONTRAST] 7500K R
#define FACTORY_7500K_G			221	// FuncBuf[pCONTRAST] 7500K G
#define FACTORY_7500K_B			200	// FuncBuf[pCONTRAST] 7500K B		
#define FACTORY_9300K_R			255	// FuncBuf[pCONTRAST] 9300K R
#define FACTORY_9300K_G			224	// FuncBuf[pCONTRAST] 9300K G
#define FACTORY_9300K_B			223	// FuncBuf[pCONTRAST] 9300K B

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

#endif //__NVT_1920X1080_H__
