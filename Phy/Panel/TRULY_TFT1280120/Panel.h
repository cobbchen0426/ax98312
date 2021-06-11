/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/
#ifndef __AUO_G150XTN05_V0__
#define __AUO_G150XTN05_V0__

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************
//#define	SET_OSD_LEFT_TOP		//SET FOR SMALL PANEL
//******************************************************************************
// G L O B A L   D E F I N I T I O N S
//******************************************************************************
#define PANEL_NAME              "AUO_G101EVN01_0"		// Actuality TRULY_TFT1280120
#define PANEL_TYPE              (AUO|RES_1280X800)		// 1280x120@100
#define PANEL_DUAL_PORT_LVDS    0		
#define PANEL_COLOR_DEPTH       8
#define PANEL_DE_MODE           0	//1
#define PANEL_PORT_SWAP         0
#define PANEL_BIT_SHIFT         0	//1


#define PANEL_WIDTH             1280
#define PANEL_HEIGHT            120	//800

#define PANEL_MIN_LVDS_CLK       8000000 //g 15000000 //Hz
#define PANEL_MAX_LVDS_CLK      80000000 //Hz	//80000000 //Hz

#define PANEL_MIN_HTOTAL        1400
#define PANEL_TYP_HTOTAL        1420 //1400 //g 1460 //1632
#define PANEL_MAX_HTOTAL        1480	//1470

#define PANEL_MIN_VTOTAL        208	//815
#define PANEL_TYP_VTOTAL        182 //178 //208	//790	//823
#define PANEL_MAX_VTOTAL        200	//800	//1023
									   
#define PANEL_HSYNC_WIDTH       29 //g 10	//128 //32	// ((PANEL_MIN_HTOTAL - PANEL_WIDTH) / 3 / 8) * 8
#define PANEL_HSYNC_BACKPORCH   54 //g 62 //g 70	//54	//176 //80 //george ((PANEL_MIN_HTOTAL - PANEL_WIDTH) / 3 / 8) * 8
#define PANEL_HACTIVE_BEG       PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACKPORCH

#define PANEL_VSYNC_WIDTH       16  //7
#define PANEL_VSYNC_BACKPORCH   3 //20
#define PANEL_VACTIVE_BEG       PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACKPORCH  //fefanjacky modify for dp first line flash

#define PANEL_DISP_HSYNC_POL    0 //0:Active low, 1:Active high
#define PANEL_DISP_VSYNC_POL    0 //0:Active low, 1:Active high
#define PANEL_DISP_DE_POL       1 //0:Active low, 1:Active high

#define PANEL_FRC_OUTPUT_VSYNC  500 //480 //560	//g  560 //g 990	//600 //0.1Hz
#define PANEL_PAD_DRIVE         0x00

#define PANEL_LVDS_SWING        LVDS_SWING_450
#define PANEL_DCLK_SSC          0x71	//0x2D

#define DT16A                   0x10 	//Display Port Control(A /B Port Swap Control)	//140515 mike
#define DT158                   0x00	//Display Dithering Control	//0x33				// (at \Sys\NR.c -> SetNRByAnalogTiming)
#define DT1D8                   0x00
#define DT1DA                   0x90	//Display Random Dithering Control
#define DT1DB                   0x00	//Gamma Dithering Control

#define PANEL_POWER_UP_TIME     20   // 0< TIME <50ms
#define PANEL_INVTER_UP_TIME    520  //    TIME >500ms
#define PANEL_POWER_DOWN_TIME   20   // 0< TIME <50ms   
#define PANEL_INVTER_DOWN_TIME  250  //    TIME >200ms
#define PANEL_OFF_ON_TIME       1000

#define ADC_OFFSET_ADJ          4
#define ADC_GAIN_ADJ            0

	//-----------------------------------------------------
#define	DEFAULT_INVERTER_VAL	255

#define GAMMA_TOTAL_STEP		7		//1.9~2.5
#define	DEFAULT_GAMMA_INDEX		3		//1.9=0 2.0=1 2.1=2 2.2=3 2.3=4 2.4=5 2.5=6

#define FACTORY_6500K_R			137	// FuncBuf[pCONTRAST] 6500K R
#define FACTORY_6500K_G			141	// FuncBuf[pCONTRAST] 6500K G
#define FACTORY_6500K_B			146	// FuncBuf[pCONTRAST] 6500K B
#define FACTORY_7500K_R			126	// FuncBuf[pCONTRAST] 7500K R
#define FACTORY_7500K_G			133	// FuncBuf[pCONTRAST] 7500K G
#define FACTORY_7500K_B			146	// FuncBuf[pCONTRAST] 7500K B		
#define FACTORY_9300K_R			115	// FuncBuf[pCONTRAST] 9300K R
#define FACTORY_9300K_G			131	// FuncBuf[pCONTRAST] 9300K G
#define FACTORY_9300K_B			146	// FuncBuf[pCONTRAST] 9300K B
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
