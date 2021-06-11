/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/
#ifndef __IVO_M101NWWB_R3__
#define __IVO_M101NWWB_R3__

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************

//******************************************************************************
// G L O B A L   D E F I N I T I O N S
//******************************************************************************
#define PANEL_NAME              "M101NWWB R3"
#define PANEL_TYPE              (AUO|RES_1280X800)	//(AUO|RES_1280X1024)
#define PANEL_DUAL_PORT_LVDS    	0	//1
#define PANEL_COLOR_DEPTH       	8
#define PANEL_DE_MODE           	0
#define PANEL_PORT_SWAP         	0
#define PANEL_BIT_SHIFT         	0

#define PANEL_WIDTH             	1280
#define PANEL_HEIGHT            	800	//1024

#define PANEL_MIN_LVDS_CLK       	90000000 //Hz
#define PANEL_MAX_LVDS_CLK      	135000000  //Hz

#define PANEL_MIN_HTOTAL          	1410	//1400	//1520
#define PANEL_TYP_HTOTAL          	1440	//1420	//1688
#define PANEL_MAX_HTOTAL         	1470	//1480	//2048

#define PANEL_MIN_VTOTAL        	815		//1038
#define PANEL_TYP_VTOTAL        	823		//1066
#define PANEL_MAX_VTOTAL        	1023	//2048

#define PANEL_HSYNC_WIDTH      	 	((PANEL_MIN_HTOTAL - PANEL_WIDTH) / 3 / 8) * 8
#define PANEL_HSYNC_BACKPORCH   	((PANEL_MIN_HTOTAL - PANEL_WIDTH) / 3 / 8) * 8
#define PANEL_HACTIVE_BEG       	PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACKPORCH

#define PANEL_VSYNC_WIDTH       	2
#define PANEL_VSYNC_BACKPORCH   	3
#define PANEL_VACTIVE_BEG       	PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACKPORCH

#define PANEL_DISP_HSYNC_POL    	0 //0:Active low, 1:Active high
#define PANEL_DISP_VSYNC_POL    	0 //0:Active low, 1:Active high
#define PANEL_DISP_DE_POL       	1 //0:Active low, 1:Active high

#define PANEL_FRC_OUTPUT_VSYNC  	600 //0.1Hz
#define PANEL_PAD_DRIVE         	0x00

#define PANEL_LVDS_SWING        	LVDS_SWING_450
#define PANEL_DCLK_SSC          	0x2D

#define DT16A                   	0x00
#define DT158                   	0x33
#define DT1D8                   	0x00
#define DT1DA                   	0x90	//0x00
#define DT1DB                   	0x00	//0x90

#define PANEL_POWER_UP_TIME    		25
#define PANEL_INVTER_UP_TIME    	100
#define PANEL_POWER_DOWN_TIME   	25
#define PANEL_INVTER_DOWN_TIME  	100
#define PANEL_OFF_ON_TIME       	1000

#define ADC_OFFSET_ADJ          	4
#define ADC_GAIN_ADJ            	0

#define	DEFAULT_INVERTER_VAL	255

#define GAMMA_TOTAL_STEP		7		//1.9~2.5
#define	DEFAULT_GAMMA_INDEX		3		//1.9/2.0/2.1/2.2/2.3/2.4/2.5

#define FACTORY_6500K_R			147	// FuncBuf[pCONTRAST] 6500K R
#define FACTORY_6500K_G			145	// FuncBuf[pCONTRAST] 6500K G
#define FACTORY_6500K_B			152	// FuncBuf[pCONTRAST] 6500K B
#define FACTORY_7500K_R			134	// FuncBuf[pCONTRAST] 7500K R
#define FACTORY_7500K_G			138	// FuncBuf[pCONTRAST] 7500K G
#define FACTORY_7500K_B			152	// FuncBuf[pCONTRAST] 7500K B		
#define FACTORY_9300K_R			121	// FuncBuf[pCONTRAST] 9300K R
#define FACTORY_9300K_G			127	// FuncBuf[pCONTRAST] 9300K G
#define FACTORY_9300K_B			152	// FuncBuf[pCONTRAST] 9300K B

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

#endif //__AUO_G170ETN01 V0
