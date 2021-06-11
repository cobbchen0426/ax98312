/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/
#ifndef __SCALER_PROFILE_NT68655_H__
#define __SCALER_PROFILE_NT68655_H__

//******************************************************************************
// G L O B A L   D E F I N I T I O N S
//******************************************************************************
// ADC Related
#if ENABLE_INTERNAL_ADC_LDO == ON
#define SCREG_002_135M 0x04
#define SCREG_005_135M 0x15
#define SCREG_1F1_135M 0x3C
#define SCREG_002_165M 0x04
#define SCREG_005_165M 0x15
#define SCREG_1F1_165M 0x3C
#define SCREG_002_190M 0x04
#define SCREG_005_190M 0x15
#define SCREG_1F1_190M 0x3C
#define SCREG_002_210M 0x04
#define SCREG_005_210M 0x15
#define SCREG_1F1_210M 0x3C
#define SCREG_002_245M 0x04
#define SCREG_005_245M 0x15
#define SCREG_1F1_245M 0x3C
#else
#define SCREG_002_135M 0x03
#define SCREG_005_135M 0x15
#define SCREG_1F1_135M 0x3C
#define SCREG_002_165M 0x03
#define SCREG_005_165M 0x15
#define SCREG_1F1_165M 0x3C
#define SCREG_002_190M 0x03
#define SCREG_005_190M 0x15
#define SCREG_1F1_190M 0x3C
#define SCREG_002_210M 0x03
#define SCREG_005_210M 0x15
#define SCREG_1F1_210M 0x3C
#define SCREG_002_245M 0x03
#define SCREG_005_245M 0x15
#define SCREG_1F1_245M 0x3C
#endif

#define SCREG_00E_PU   (SC_ADC_POWER_UP | 0x47)
#define SCREG_00E_PD   (SC_ADC_POWER_UP & ~0x47)
#define SCREG_011      0xAC
#define SCREG_012_PD   0x81
#define SCREG_012_LP   0xC0

#define SCREG_1EA      SC_ADC_REG_1D
#define SCREG_1EB      0x02
#define SCREG_1ED      (SC_ADC_BAND_GAP|BIT3)

#if ENABLE_LD == ON
#define SCREG_1ED_INIT     (SC_ADC_BAND_GAP|BIT3|BIT0)  
#else
#define SCREG_1ED_INIT      (SC_ADC_BAND_GAP|BIT3|BIT1|BIT0)
#endif

#define SCREG_055_PU 0x10
#define SCREG_055_PD 0x00
#define SCREG_056_PU 0x0F
#define SCREG_056_PD 0x04
#define SCREG_057_INT_LDO 0xE3
#define SCREG_057_EXT_LDO 0xA3

#define SCREB_B61_PU 0x00
#define SCREB_B61_PD 0x2F
#define SCREB_B62_PU 0x05
#define SCREB_B62_PD 0xFA
#define SCREB_B63_INT_LDO 0x04
#define SCREB_B63_EXT_LDO 0x04

#define SCREB_039_INT_LDO 0x00
#define SCREB_039_EXT_LDO 0x00

#define SCREG_0D0 0x21
#define SCREG_0D1 0x13

#if IS_NT68850_SERIES
#define SCREG_025_A 0x00
#define SCREG_038_A 0x10
#else
#define SCREG_025_A 0x40
#define SCREG_038_A 0x00
#endif
#define SCREG_025_D 0x40
#define SCREG_038_D 0x00

//SR
#define SCREG_EA0      0x40

// LVDS Related
#define SCREG_1EF      0x04
#define SCREG_1F3      0x00
#define SCREG_1F4      0x42
#define SCREG_1F5      0x40
#define SCREG_1F8      0x03
#define SCREG_1F9      0x00
#define SCREG_1FA      0x00
#define SCREG_1FD      0x00

// TMDS Related
#define SCREG_303_LF   (SC_DVI_CTRL_303 | BIT7)
#define SCREG_303_HF   (SC_DVI_CTRL_303 & ~BIT7)
#define SCREG_331      0x05
#define SCREG_333_PU   0x9F
#define SCREG_333_PD   0x00
#define SCREG_333_LP0  0x07
#define SCREG_333_LP1  0x07
#define SCREG_334_PU   0xF1
#define SCREG_334_PD   0x00
#define SCREG_334_LF   (SC_DVI_CTRL_334 | BIT2)
#define SCREG_334_HF   (SC_DVI_CTRL_334 & ~BIT2)
#define SCREG_335_PU   0x00
#define SCREG_335_PD   0x00
#define SET_SCREG_335_LF  {SC_DVI_CTRL_335 = 0x30; SC_DVI_CTRL_335 = 0x10;}
#define SET_SCREG_335_HF  {SC_DVI_CTRL_335 = 0x30; SC_DVI_CTRL_335 = 0x20;}
#define SCREG_336_PU   0x58
#define SCREG_336_PD   0x08
#define SCREG_336_LP0  0x48 //different than SCREG_336_PU, BIT4 will cause more power consumption
#define SCREG_336_LP1  0x48 //different than SCREG_336_PU, BIT4 will cause more power consumption

#define TMDS_BANDWIDTH_SEGMENT 80

// LDO Related
#if REF_CLK < 13000000
#define SCREG_B40      0x05
#else
#define SCREG_B40      0x04
#endif
#define SCREG_B41      0x07
#define SCREG_B42      (SC_MPLL_CTRL_B42 & ~BIT2)
#define SCREG_B43      0x19

// HDCP Related
#define SCREG_643      SC_HDCP_CTRL
#define HDCP_CLK_INV   0x00

#define DEFAULT_CLKIMP1     0x14
#define DEFAULT_CLKIMP2     0x11
#define DEFAULT_CLKIMP3     0x0D
#define DEFAULT_DATAIMP1    0x14
#define DEFAULT_DATAIMP2    0x11
#define DEFAULT_DATAIMP3    0x0D
#define DEFAULT_EQBIAS1     0xB8
#define DEFAULT_EQBIAS2     0x38
#define DEFAULT_EQBIAS3     0x78
#define DEFAULT_EQBIAS4     0xB8
#define DEFAULT_EQBIAS5     0xE8
#define DEFAULT_EQRF1       0x80
#define DEFAULT_EQRF2       0xF0
#define DEFAULT_EQRF3       0x0F
#define DEFAULT_EQRF4       0x08
#define DEFAULT_EQRF5       0x0F

//******************************************************************************
// MMU Configure SDR
//******************************************************************************
//MMU_DRAMIF 
#define SCREG_580_E 0x89
#define SCREG_581_E 0x13 //0x12
#define SCREG_582_E 0x33
#define SCREG_583_E 0x00
#define SCREG_584_E 0x00
#define SCREG_585_E 0x20
#define SCREG_586_E 0x00
#define SCREG_587_E 0x00
#define SCREG_588_E 0x00
#define SCREG_589_E 0x02
#define SCREG_58A_E 0x01

#define SCREG_580_G 0x89
#define SCREG_581_G 0x13 //0x12
#define SCREG_582_G 0x33
#define SCREG_583_G 0x00
#define SCREG_584_G 0x00
#define SCREG_585_G 0x20
#define SCREG_586_G 0x00
#define SCREG_587_G 0x00
#define SCREG_588_G 0x00
#define SCREG_589_G 0x02
#define SCREG_58A_G 0x01

#define SCREG_580_H 0x89
#define SCREG_581_H 0x13 //0x12
#define SCREG_582_H 0x33
#define SCREG_583_H 0x00
#define SCREG_584_H 0x00
#define SCREG_585_H 0x20
#define SCREG_586_H 0x00
#define SCREG_587_H 0x00
#define SCREG_588_H 0x00
#define SCREG_589_H 0x02
#define SCREG_58A_H 0x01


//MMU_DQSDelay
#define SCREG_5F0_E 0x00
#define SCREG_5F1_E 0x00
#define SCREG_5F2_E 0x00
#define SCREG_5F3_E 0x00
#define SCREG_5F4_E 0xB3
#define SCREG_5F5_E 0x33
#define SCREG_5F6_E 0x00
#define SCREG_5F7_E 0x81
#define SCREG_5F8_E 0x40
#define SCREG_5F9_E 0x01
#define SCREG_5FA_E 0x02

#define SCREG_5F0_G 0x00
#define SCREG_5F1_G 0x00
#define SCREG_5F2_G 0x00
#define SCREG_5F3_G 0xC0
#define SCREG_5F4_G 0xB3
#define SCREG_5F5_G 0x33
#define SCREG_5F6_G 0x00
#define SCREG_5F7_G 0x89
#define SCREG_5F8_G 0x40
#define SCREG_5F9_G 0x01
#define SCREG_5FA_G 0x0D

#define SCREG_5F0_H 0x00
#define SCREG_5F1_H 0x00
#define SCREG_5F2_H 0x00
#define SCREG_5F3_H 0xC0
#define SCREG_5F4_H 0xB3
#define SCREG_5F5_H 0x33
#define SCREG_5F6_H 0x00
#define SCREG_5F7_H 0x89
#define SCREG_5F8_H 0x40
#define SCREG_5F9_H 0x01
#define SCREG_5FA_H 0x0D


//MMU_PLL
#define SCREG_B80_E 0xF8
#define SCREG_B81_E 0x40
#define SCREG_B82_E 0x20
#define SCREG_B83_E 0x0E
#define SCREG_B84_E 0x43
#define SCREG_B85_E 0x10
#define SCREG_B86_E 0x32
#define SCREG_B87_E 0x53
#define SCREG_B88_E 0x51
#define SCREG_B89_E 0xFF
#define SCREG_B8A_E 0x16
#define SCREG_B8B_E 0x00
#define SCREG_B8C_E 0x00
#define SCREG_B8D_E 0x00
#define SCREG_B8E_E 0x00
#define SCREG_B8F_E 0x00

#define SCREG_B80_G 0xF8
#define SCREG_B81_G 0x43
#define SCREG_B82_G 0x20
#define SCREG_B83_G 0x0E
#define SCREG_B84_G 0x43
#define SCREG_B85_G 0x10
#define SCREG_B86_G 0x32
#define SCREG_B87_G 0x53
#define SCREG_B88_G 0x55
#define SCREG_B89_G 0xFF
#define SCREG_B8A_G 0x16
#define SCREG_B8B_G 0x00
#define SCREG_B8C_G 0x00
#define SCREG_B8D_G 0x00
#define SCREG_B8E_G 0x00
#define SCREG_B8F_G 0x00

#define SCREG_B80_H 0xF8  
#define SCREG_B81_H 0x43  
#define SCREG_B82_H 0x20  
#define SCREG_B83_H 0x0E  
#define SCREG_B84_H 0x43  
#define SCREG_B85_H 0x10  
#define SCREG_B86_H 0x32  
#define SCREG_B87_H 0x53  
#define SCREG_B88_H 0x55  
#define SCREG_B89_H 0xFF  
#define SCREG_B8A_H 0x16  
#define SCREG_B8B_H 0x00  
#define SCREG_B8C_H 0x00  
#define SCREG_B8D_H 0x00  
#define SCREG_B8E_H 0x00  
#define SCREG_B8F_H 0x00  

//MMU_PLLSKEW
#define SCREG_B90_E 0x14
#define SCREG_B91_E 0x14
#define SCREG_B92_E 0x00

#define SCREG_B90_G 0x14
#define SCREG_B91_G 0x14
#define SCREG_B92_G 0x00

#define SCREG_B90_H 0x14 
#define SCREG_B91_H 0x14 
#define SCREG_B92_H 0x00 

//MMU_PLLFREQ
#define SCREG_B31_E 0xAA
#define SCREG_B32_E 0xAA
#define SCREG_B33_E 0x36
#define SCREG_B34_E 0x00

#define SCREG_B31_G 0xAA
#define SCREG_B32_G 0xAA
#define SCREG_B33_G 0x34
#define SCREG_B34_G 0x00

#define SCREG_B31_H 0xAA
#define SCREG_B32_H 0xAA
#define SCREG_B33_H 0x34
#define SCREG_B34_H 0x00


//MIO PAD SELEST
#define SCREG_B5E 0x82

//******************************************************************************
// CPU Clock support 
//******************************************************************************
#define CPU_CLK_TABLE { \
            12,12,24,32,48,64,96,12,12 \
        }

//******************************************************************************
// LED driver default setting 
//******************************************************************************
#define LED_DRV_REG_TABLE { \
                0x00,0x0F,0xFF,0x00,0x20,0x40,0xA9,0x4A,0xC4,0x37,0x3A,0x00,0x70,0x00,0x00,0x00, \
            0x0F,0x00,0x0D,0x00,0x00,0xFF,0x00,0xCC,0x00,0x80,0x00,0xE5,0x2E,0x0F,0xFF,0xE0,  \
                0x00,0x0B,0x40,0x00,0x02 \
        }

//******************************************************************************
// SR default setting 
//******************************************************************************
#ifndef SR_MDN_1
#define SR_MDN_1     { \
            0x00,/* CutOffTH */ \
            0x00,/* CutOffSlop */ \
            0x000, /* VarTH */ \
            0x00, /* HiVarGain */ \
            0x00 /* LoVarGain */ \
    }
#endif

#ifndef SR_USMRegion_1
#define SR_USMRegion_1     { \
            0x70,/* ucCutOffTH */ \
            0x0086,/* usVarTH */ \
            0x0A, /* ucHiVarGain */ \
            0x07 /* ucLoVarGain */ \
    }
#endif

#ifndef SR_USMRegion_2
#define SR_USMRegion_2     { \
            0x60,/* ucCutOffTH */ \
            0x0086,/* usVarTH */ \
            0x0A, /* ucHiVarGain */ \
            0x07 /* ucLoVarGain */ \
    }
#endif

#ifndef SR_USMRegion_3
#define SR_USMRegion_3     { \
            0x48,/* ucCutOffTH */ \
            0x0086,/* usVarTH */ \
            0x0A, /* ucHiVarGain */ \
            0x07 /* ucLoVarGain */ \
    }
#endif

#ifndef SR_USMRegion_4
#define SR_USMRegion_4     { \
            0x30,/* ucCutOffTH */ \
            0x0086,/* usVarTH */ \
            0x0A, /* ucHiVarGain */ \
            0x07 /* ucLoVarGain */ \
    }
#endif

#ifndef SR_USMGain_1
#define SR_USMGain_1     { \
            0x12,/* ucCutOffTH */ \
            0x00B8,/* usVarTH */ \
            0x0E, /* ucHiVarGain */ \
            0x01 /* ucLoVarGain */ \
    }
#endif

#ifndef SR_USMGain_2
#define SR_USMGain_2     { \
            0x24,/* ucCutOffTH */ \
            0x00B8,/* usVarTH */ \
            0x0E, /* ucHiVarGain */ \
            0x02 /* ucLoVarGain */ \
    }
#endif

#ifndef SR_USMGain_3
#define SR_USMGain_3     { \
            0x2A,/* ucCutOffTH */ \
            0x00B8,/* usVarTH */ \
            0x0E, /* ucHiVarGain */ \
            0x03 /* ucLoVarGain */ \
    }
#endif

#ifndef SR_USMGain_4
#define SR_USMGain_4     { \
            0x35,/* ucCutOffTH */ \
            0x00B8,/* usVarTH */ \
            0x0E, /* ucHiVarGain */ \
            0x04 /* ucLoVarGain */ \
    }
#endif

#endif //__SCALER_PROFILE_NT68655_H__
