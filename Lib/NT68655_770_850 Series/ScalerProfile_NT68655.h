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
