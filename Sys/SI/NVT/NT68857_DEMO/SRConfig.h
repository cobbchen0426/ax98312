/******************************************************************************/
/*                       Novatek MicroElectronics Corp.                       */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*                 TEL:886-3-567-0889       FAX:886-3-577-0132                */
/*                            All Rights Reserved                             */
/******************************************************************************/
#ifndef __SRCONFIG_H__
#define __SRCONFIG_H__

#define ENABLE_SR_CUSTOM_SETTING OFF

#if ENABLE_SR_CUSTOM_SETTING == ON
#define SR_MDN_1     { \
            0x00,/* ucCutOffTH */ \
            0x00,/* ucCutOffSlop */ \
            0x0000, /* usVarTH */ \
            0x00, /* ucHiVarGain */ \
            0x00 /* ucLoVarGain */ \
    }

#define SR_USMRegion_1     { \
            0x70,/* ucCutOffTH */ \
            0x0086,/* usVarTH */ \
            0x0A, /* ucHiVarGain */ \
            0x07 /* ucLoVarGain */ \
    }

#define SR_USMRegion_2     { \
            0x60,/* ucCutOffTH */ \
            0x0086,/* usVarTH */ \
            0x0A, /* ucHiVarGain */ \
            0x07 /* ucLoVarGain */ \
    }

#define SR_USMRegion_3     { \
            0x48,/* ucCutOffTH */ \
            0x0086,/* usVarTH */ \
            0x0A, /* ucHiVarGain */ \
            0x07 /* ucLoVarGain */ \
    }

#define SR_USMRegion_4     { \
            0x30,/* ucCutOffTH */ \
            0x0086,/* usVarTH */ \
            0x0A, /* ucHiVarGain */ \
            0x07 /* ucLoVarGain */ \
    }

#define SR_USMGain_1     { \
            0x12,/* ucCutOffTH */ \
            0x00B8,/* usVarTH */ \
            0x0E, /* ucHiVarGain */ \
            0x01 /* ucLoVarGain */ \
    }

#define SR_USMGain_2     { \
            0x24,/* ucCutOffTH */ \
            0x00B8,/* usVarTH */ \
            0x0E, /* ucHiVarGain */ \
            0x02 /* ucLoVarGain */ \
    }

#define SR_USMGain_3     { \
            0x2A,/* ucCutOffTH */ \
            0x00B8,/* usVarTH */ \
            0x0E, /* ucHiVarGain */ \
            0x03 /* ucLoVarGain */ \
    }

#define SR_USMGain_4     { \
            0x35,/* ucCutOffTH */ \
            0x00B8,/* usVarTH */ \
            0x0E, /* ucHiVarGain */ \
            0x04 /* ucLoVarGain */ \
    }
#endif

#endif //__SRCONFIG_H__
