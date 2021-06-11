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
/*!
 * The table of preset timings.
 */
code ModeTableFormat ModeTable[] = {

#ifdef TRULY_TFT1280120


    //george_TRULY_TFT1280120 ADD
    { //1280x120@59.6
        OFF, //ucSampling 
        126,  503, 	HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
         29,   15, //ucHSyncWidth, ucVSyncWidth
       1420,  252, //usHTotal, usVTotal
       1280,  120, //usModeHActive, usModeVActive
       1280,  120, //usCapHActive, usCapVActive
        140,  132, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1280x120_50HZ //usModeIndex
    },

    //george_TRULY_TFT1280120 ADD
    { //1280x120@98
        OFF, //ucSampling 
        146,  987, 	HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
         32,    5, //ucHSyncWidth, ucVSyncWidth
       1440,  148, //usHTotal, usVTotal
       1280,  120, //usModeHActive, usModeVActive
       1280,  120, //usCapHActive, usCapVActive
        160,   28, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1280x120_99HZ //usModeIndex
    },

    //george_TRULY_TFT1280120 ADD
    { //1280x720@50
        OFF, //ucSampling 
        370,  498, 	HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
        128,    5, //ucHSyncWidth, ucVSyncWidth
       1632,  744, //usHTotal, usVTotal
       1280,  720, //usModeHActive, usModeVActive
       1280,  720, //usCapHActive, usCapVActive
        352,   24, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1280x720_50HZ //usModeIndex
    },

    //george_TRULY_TFT1280120 ADD
    { //1280x720@20
        OFF, //ucSampling 
        152,  205, 	HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
          2,    2, //ucHSyncWidth, ucVSyncWidth
       1440,  744, //usHTotal, usVTotal
       1280,  720, //usModeHActive, usModeVActive
       1280,  720, //usCapHActive, usCapVActive
        160,   24, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1280x720_20HZ //usModeIndex
    },

    //george_TRULY_TFT1280120 ADD
    { //1280x480@30
        OFF, //ucSampling 
        155,  299, 	HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
         40,    6, //ucHSyncWidth, ucVSyncWidth
       1440,  520, //usHTotal, usVTotal
       1280,  480, //usModeHActive, usModeVActive
       1280,  480, //usCapHActive, usCapVActive
        160,   40, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1280x480_30HZ //usModeIndex
    },
#endif

    { //640x350@70
        OFF, //ucSampling    
        315,  700, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
         96,    2, //ucHSyncWidth, ucVSyncWidth
        800,  449, //usHTotal, usVTotal
        640,  350, //usModeHActive, usModeVActive
        640,  350, //usCapHActive, usCapVActive
         34,   56, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
        _640x350_70HZ //usModeIndex
    },
    { //640x350@85
        OFF, //ucSampling    
        379,  851, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
         64,    3, //ucHSyncWidth, ucVSyncWidth
        832,  445, //usHTotal, usVTotal
        640,  350, //usModeHActive, usModeVActive
        640,  350, //usCapHActive, usCapVActive
         81,   57, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
        _640x350_85HZ //usModeIndex
    },
    { //640x400@70
        OFF, //ucSampling 
        315,  700, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
         96,    2, //ucHSyncWidth, ucVSyncWidth
        800,  449, //usHTotal, usVTotal
        640,  400, //usModeHActive, usModeVActive
        640,  400, //usCapHActive, usCapVActive
         34,   32, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
        _640x400_70HZ //usModeIndex
    },


    { //640x400@85
        OFF, //ucSampling 
        379,  851, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
         64,    3, //ucHSyncWidth, ucVSyncWidth
        832,  445, //usHTotal, usVTotal
        640,  400, //usModeHActive, usModeVActive
        640,  400, //usCapHActive, usCapVActive
         82,   38, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
        _640x400_85HZ //usModeIndex
    },


#ifdef SGD_GVTW70SNAD1E0

    { //george 800x480@60
        OFF, //ucSampling 
        315,  600, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
         48,    3, //ucHSyncWidth, ucVSyncWidth
       1056,  525, //usHTotal, usVTotal
        800,  480, //usModeHActive, usModeVActive
        800,  480, //usCapHActive, usCapVActive
         88,   23, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _800x480_60HZ //usModeIndex
    },
#else
    { //640x480@60
        OFF, //ucSampling 
        315,  600, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
         96,    2, //ucHSyncWidth, ucVSyncWidth
        800,  525, //usHTotal, usVTotal
        640,  480, //usModeHActive, usModeVActive
        640,  480, //usCapHActive, usCapVActive
         34,   30, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
        _640x480_60HZ //usModeIndex
    },
#endif



    { //640x480@66
        OFF, //ucSampling 
        350,  667, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
         64,    3, //ucHSyncWidth, ucVSyncWidth
        864,  525, //usHTotal, usVTotal
        640,  480, //usModeHActive, usModeVActive
        640,  480, //usCapHActive, usCapVActive
         81,   36, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
        _640x480_66HZ //usModeIndex
    },
    { //640x480@72
        OFF, //ucSampling 
        379,  728, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
         40,    3, //ucHSyncWidth, ucVSyncWidth
        832,  520, //usHTotal, usVTotal
        640,  480, //usModeHActive, usModeVActive
        640,  480, //usCapHActive, usCapVActive
        114,   25, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
        _640x480_72HZ //usModeIndex
    },
    { //640x480@75
        OFF, //ucSampling 
        375,  750, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
         64,    3, //ucHSyncWidth, ucVSyncWidth
        840,  500, //usHTotal, usVTotal
        640,  480, //usModeHActive, usModeVActive
        640,  480, //usCapHActive, usCapVActive
        106,   13, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
        _640x480_75HZ //usModeIndex
    },
    { //640x480@85
        OFF, //ucSampling 
        433,  850, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
         56,    3, //ucHSyncWidth, ucVSyncWidth
        832,  509, //usHTotal, usVTotal
        640,  480, //usModeHActive, usModeVActive
        640,  480, //usCapHActive, usCapVActive
         66,   22, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
        _640x480_85HZ //usModeIndex
    },
    { //640x500@57
        OFF, //ucSampling 
        309,  576, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
         32,   10, //ucHSyncWidth, ucVSyncWidth
        816,  537, //usHTotal, usVTotal
        640,  500, //usModeHActive, usModeVActive
        640,  500, //usCapHActive, usCapVActive
         66,    3, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
        _640x500_57HZ //usModeIndex
    },
    { //720x400@70
        OFF, //ucSampling 
        315,  701, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
        108,    2, //ucHSyncWidth, ucVSyncWidth
        900,  449, //usHTotal, usVTotal
        720,  400, //usModeHActive, usModeVActive
        720,  400, //usCapHActive, usCapVActive
         40,   32, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
        _720x400_70HZ //usModeIndex
    },
    { //720x400@85
        OFF, //ucSampling 
        379,  850, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
         72,    2, //ucHSyncWidth, ucVSyncWidth
        936,  446, //usHTotal, usVTotal
        720,  400, //usModeHActive, usModeVActive
        720,  400, //usCapHActive, usCapVActive
         92,   39, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
        _720x400_85HZ //usModeIndex
    },
    { //832x624@75
        OFF, //ucSampling 
        497,  745, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
         64,    3, //ucHSyncWidth, ucVSyncWidth
       1152,  667, //usHTotal, usVTotal
        832,  624, //usModeHActive, usModeVActive
        832,  624, //usCapHActive, usCapVActive
        208,   26, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _832x624_75HZ //usModeIndex
    },
    { //800x600@56
        OFF, //ucSampling 
        352,  563, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
         72,    2, //ucHSyncWidth, ucVSyncWidth
       1024,  625, //usHTotal, usVTotal
        800,  600, //usModeHActive, usModeVActive
        800,  600, //usCapHActive, usCapVActive
        113,   19, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _800x600_56HZ //usModeIndex
    },
    { //800x600@60
        OFF, //ucSampling 
        379,  603, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
        128,    4, //ucHSyncWidth, ucVSyncWidth
       1056,  628, //usHTotal, usVTotal
        800,  600, //usModeHActive, usModeVActive
        800,  600, //usCapHActive, usCapVActive
         73,   20, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _800x600_60HZ //usModeIndex
    },
    { //800x600@72
        OFF, //ucSampling 
        481,  722, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
        120,    6, //ucHSyncWidth, ucVSyncWidth
       1040,  666, //usHTotal, usVTotal
        800,  600, //usModeHActive, usModeVActive
        800,  600, //usCapHActive, usCapVActive
         49,   20, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _800x600_72HZ //usModeIndex
    },
    { //800x600@75
        OFF, //ucSampling 
        469,  750, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
         80,    3, //ucHSyncWidth, ucVSyncWidth
       1056,  625, //usHTotal, usVTotal
        800,  600, //usModeHActive, usModeVActive
        800,  600, //usCapHActive, usCapVActive
        145,   18, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _800x600_75HZ //usModeIndex
    },
    { //800x600@85
        OFF, //ucSampling 
        537,  851, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
         64,    3, //ucHSyncWidth, ucVSyncWidth
       1048,  631, //usHTotal, usVTotal
        800,  600, //usModeHActive, usModeVActive
        800,  600, //usCapHActive, usCapVActive
        137,   24, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _800x600_85HZ //usModeIndex
    },
    { //848x480@60
        OFF, //ucSampling 
        310,  600, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
        112,    8, //ucHSyncWidth, ucVSyncWidth
       1088,  517, //usHTotal, usVTotal
        848,  480, //usModeHActive, usModeVActive
        848,  480, //usCapHActive, usCapVActive
         97,   20, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _848x480_60HZ //usModeIndex
    },
    { //848x480@60 Reduced Blanking
        OFF, //ucSampling 
        298,  597, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
         80,    5, //ucHSyncWidth, ucVSyncWidth
       1056,  500, //usHTotal, usVTotal
        848,  480, //usModeHActive, usModeVActive
        848,  480, //usCapHActive, usCapVActive
         90,    9, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _848x480_60HZ_RB //usModeIndex
    },
    { //848x480@70
        OFF, //ucSampling 
        350,  700, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
         88,    3, //ucHSyncWidth, ucVSyncWidth
       1072,  500, //usHTotal, usVTotal
        848,  480, //usModeHActive, usModeVActive
        848,  480, //usCapHActive, usCapVActive
         97,   13, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _848x480_70HZ //usModeIndex
    },
    { //848x480@72
        OFF, //ucSampling 
        361,  720, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
         88,    3, //ucHSyncWidth, ucVSyncWidth
       1088,  501, //usHTotal, usVTotal
        848,  480, //usModeHActive, usModeVActive
        848,  480, //usCapHActive, usCapVActive
        105,   14, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _848x480_72HZ //usModeIndex
    },
    { //848x480@75
        OFF, //ucSampling 
        377,  748, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
         80,    5, //ucHSyncWidth, ucVSyncWidth
       1088,  504, //usHTotal, usVTotal
        848,  480, //usModeHActive, usModeVActive
        848,  480, //usCapHActive, usCapVActive
        106,   13, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _848x480_75HZ //usModeIndex
    },
    { //720x576@60
        OFF, //ucSampling 
        359,  599, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
         72,    7, //ucHSyncWidth, ucVSyncWidth
        912,  599, //usHTotal, usVTotal
        720,  576, //usModeHActive, usModeVActive
        720,  576, //usCapHActive, usCapVActive
         81,   10, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
        _720x576_60HZ //usModeIndex
    },
    { //1024x768@43 Interlace
        OFF, //ucSampling 
        355,  870, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
        176,    2, //ucHSyncWidth, ucVSyncWidth
       1264,  408, //usHTotal, usVTotal
       1024,  768, //usModeHActive, usModeVActive
       1024,  768, //usCapHActive, usCapVActive
         41,   17, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1024x768_43HZ_I //usModeIndex
    },
    { //1024x768@60
        OFF, //ucSampling 
        484,  600, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
        136,    6, //ucHSyncWidth, ucVSyncWidth
       1344,  806, //usHTotal, usVTotal
       1024,  768, //usModeHActive, usModeVActive
       1024,  768, //usCapHActive, usCapVActive
        145,   26, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1024x768_60HZ //usModeIndex
    },
    { //1024x768@70
        OFF, //ucSampling 
        565,  701, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
        136,    6, //ucHSyncWidth, ucVSyncWidth
       1328,  806, //usHTotal, usVTotal
       1024,  768, //usModeHActive, usModeVActive
       1024,  768, //usCapHActive, usCapVActive
        129,   26, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1024x768_70HZ //usModeIndex
    },
    { //1024x768@72
        OFF, //ucSampling 
        577,  720, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
        112,    3, //ucHSyncWidth, ucVSyncWidth
       1360,  801, //usHTotal, usVTotal
       1024,  768, //usModeHActive, usModeVActive
       1024,  768, //usCapHActive, usCapVActive
        151,   26, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1024x768_72HZ //usModeIndex
    },
    { //1024x768@75
        OFF, //ucSampling 
        600,  750, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
         96,    3, //ucHSyncWidth, ucVSyncWidth
       1312,  800, //usHTotal, usVTotal
       1024,  768, //usModeHActive, usModeVActive
       1024,  768, //usCapHActive, usCapVActive
        160,   25, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1024x768_75HZ //usModeIndex
    },
    { //1024x768@76
        OFF, //ucSampling 
        611,  760, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
         96,    3, //ucHSyncWidth, ucVSyncWidth
       1360,  803, //usHTotal, usVTotal
       1024,  768, //usModeHActive, usModeVActive
       1024,  768, //usCapHActive, usCapVActive
        157,   28, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1024x768_76HZ //usModeIndex
    },
    { //1024x768@85
        OFF, //ucSampling 
        687,  850, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
         96,    3, //ucHSyncWidth, ucVSyncWidth
       1376,  808, //usHTotal, usVTotal
       1024,  768, //usModeHActive, usModeVActive
       1024,  768, //usCapHActive, usCapVActive
        191,   33, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1024x768_85HZ //usModeIndex
    },
    { //1152x720@60
        OFF, //ucSampling 
        449,  600, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
        112,    6, //ucHSyncWidth, ucVSyncWidth
       1488,  748, //usHTotal, usVTotal
       1152,  720, //usModeHActive, usModeVActive
       1152,  720, //usCapHActive, usCapVActive
        153,   16, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1152x720_60HZ //usModeIndex
    },
    { //1152x864@60
        OFF, //ucSampling 
        540,  600, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
         96,    3, //ucHSyncWidth, ucVSyncWidth
       1480,  900, //usHTotal, usVTotal
       1152,  864, //usModeHActive, usModeVActive
       1152,  864, //usCapHActive, usCapVActive
        160,   25, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1152x864_60HZ //usModeIndex
    },
    { //1152x864@70
        OFF, //ucSampling 
        639,  700, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
         96,    3, //ucHSyncWidth, ucVSyncWidth
       1480,  912, //usHTotal, usVTotal
       1152,  864, //usModeHActive, usModeVActive
       1152,  864, //usCapHActive, usCapVActive
        183,   41, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1152x864_70HZ //usModeIndex
    },
    { //1152x864@75
        OFF, //ucSampling 
        675,  750, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
        128,    3, //ucHSyncWidth, ucVSyncWidth
       1600,  900, //usHTotal, usVTotal
       1152,  864, //usModeHActive, usModeVActive
       1152,  864, //usCapHActive, usCapVActive
        239,   29, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1152x864_75HZ //usModeIndex
    },
    { //1152x864@85
        OFF, //ucSampling 
        771,  847, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
        120,    4, //ucHSyncWidth, ucVSyncWidth
       1552,  910, //usHTotal, usVTotal
       1152,  864, //usModeHActive, usModeVActive
       1152,  864, //usCapHActive, usCapVActive
        182,   36, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1152x864_85HZ //usModeIndex
    },
    { //1152x870@75
        OFF, //ucSampling 
        687,  751, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
        128,    3, //ucHSyncWidth, ucVSyncWidth
       1456,  915, //usHTotal, usVTotal
       1152,  870, //usModeHActive, usModeVActive
       1152,  870, //usCapHActive, usCapVActive
        128,   36, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1152x870_75HZ //usModeIndex
    },
    { //1152x900@66
        OFF, //ucSampling 
        618,  660, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
        128,    4, //ucHSyncWidth, ucVSyncWidth
       1504,  937, //usHTotal, usVTotal
       1152,  900, //usModeHActive, usModeVActive
       1152,  900, //usCapHActive, usCapVActive
        176,   28, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1152x900_66HZ //usModeIndex
    },
    { //1152x900@76
        OFF, //ucSampling 
        717,  761, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
         96,    8, //ucHSyncWidth, ucVSyncWidth
       1472,  943, //usHTotal, usVTotal
       1152,  900, //usModeHActive, usModeVActive
       1152,  900, //usCapHActive, usCapVActive
        191,   30, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1152x900_76HZ //usModeIndex
    },

  //george test
//	    { //george 1280x720@50
//	        OFF, //ucSampling 
//	        370,  498, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
//	        128,    5, //ucHSyncWidth, ucVSyncWidth
//	       1632,  744, //usHTotal, usVTotal
//	       1280,  720, //usModeHActive, usModeVActive
//	       1280,  720, //usCapHActive, usCapVActive
//	        304,   21, //usHStart, usVStart
//	         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
//	       _1280x720_60HZ //usModeIndex
//	    }, 


    { //1280x720@60
        OFF, //ucSampling 
        450,  600, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
         40,    5, //ucHSyncWidth, ucVSyncWidth
       1650,  750, //usHTotal, usVTotal
       1280,  720, //usModeHActive, usModeVActive
       1280,  720, //usCapHActive, usCapVActive
        204,   17, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1280x720_60HZ //usModeIndex
    },
    { //1280x720@75
        OFF, //ucSampling 
        565,  748, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
        128,    5, //ucHSyncWidth, ucVSyncWidth
       1696,  755, //usHTotal, usVTotal
       1280,  720, //usModeHActive, usModeVActive
       1280,  720, //usCapHActive, usCapVActive
        192,   24, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1280x720_75HZ //usModeIndex
    },
    { //1280x768@60 Reduced Blanking
        OFF, //ucSampling 
        474,  600, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
         32,    7, //ucHSyncWidth, ucVSyncWidth
       1440,  790, //usHTotal, usVTotal
       1280,  768, //usModeHActive, usModeVActive
       1280,  768, //usCapHActive, usCapVActive
         64,    9, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1280x768_60HZ_RB //usModeIndex
    },
    { //1280x768@60
        OFF, //ucSampling 
        478,  599, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
        128,    7, //ucHSyncWidth, ucVSyncWidth
       1664,  798, //usHTotal, usVTotal
       1280,  768, //usModeHActive, usModeVActive
       1280,  768, //usCapHActive, usCapVActive
        177,   17, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1280x768_60HZ //usModeIndex
    },
    { //1280x768@70
        OFF, //ucSampling 
        565,  701, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
        128,    7, //ucHSyncWidth, ucVSyncWidth
       1696,  806, //usHTotal, usVTotal
       1280,  768, //usModeHActive, usModeVActive
       1280,  768, //usCapHActive, usCapVActive
        197,   25, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1280x768_70HZ //usModeIndex
    },
    { //1280x768@72
        OFF, //ucSampling 
        577,  721, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
        128,    7, //ucHSyncWidth, ucVSyncWidth
       1696,  800, //usHTotal, usVTotal
       1280,  768, //usModeHActive, usModeVActive
       1280,  768, //usCapHActive, usCapVActive
        197,   26, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1280x768_72HZ //usModeIndex
    },
    { //1280x768@75
        OFF, //ucSampling 
        603,  749, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
        128,    7, //ucHSyncWidth, ucVSyncWidth
       1696,  805, //usHTotal, usVTotal
       1280,  768, //usModeHActive, usModeVActive
       1280,  768, //usCapHActive, usCapVActive
        192,   24, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1280x768_75HZ //usModeIndex
    },
    { //1280x768@85
        OFF, //ucSampling 
        686,  848, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
        136,    7, //ucHSyncWidth, ucVSyncWidth
       1712,  809, //usHTotal, usVTotal
       1280,  768, //usModeHActive, usModeVActive
       1280,  768, //usCapHActive, usCapVActive
        200,   28, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1280x768_85HZ //usModeIndex
    },
    { //1280x800@60 Reduced Blanking
        OFF, //ucSampling 
        493,  599, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
         32,    6, //ucHSyncWidth, ucVSyncWidth
       1440,  823, //usHTotal, usVTotal
       1280,  800, //usModeHActive, usModeVActive
       1280,  800, //usCapHActive, usCapVActive
         65,   11, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1280x800_60HZ_RB //usModeIndex
    },
    { //1280x800@60
        OFF, //ucSampling 
        497,  598, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
        128,    6, //ucHSyncWidth, ucVSyncWidth
       1680,  831, //usHTotal, usVTotal
       1280,  800, //usModeHActive, usModeVActive
       1280,  800, //usCapHActive, usCapVActive
        185,   21, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1280x800_60HZ //usModeIndex
    },
    { //1280x800@62
        OFF, //ucSampling
        520,  625, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
         72,    3, //ucHSyncWidth, ucVSyncWidth
       1696,  833, //usHTotal, usVTotal
       1280,  800, //usModeHActive, usModeVActive
       1280,  800, //usCapHActive, usCapVActive
        193,   26, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1280x800_62HZ //usModeIndex
    },
    { //1280x800@72
        OFF, //ucSampling 
        601,  720, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
        136,    3, //ucHSyncWidth, ucVSyncWidth
       1712,  834, //usHTotal, usVTotal
       1280,  800, //usModeHActive, usModeVActive
       1280,  800, //usCapHActive, usCapVActive
        200,   27, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1280x800_72HZ //usModeIndex
    },
    { //1280x800@75
        OFF, //ucSampling 
        629,  750, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
        128,    6, //ucHSyncWidth, ucVSyncWidth
       1696,  838, //usHTotal, usVTotal
       1280,  800, //usModeHActive, usModeVActive
       1280,  800, //usCapHActive, usCapVActive
        192,   26, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1280x800_75HZ //usModeIndex
    },
    { //1280x800@85
        OFF, //ucSampling 
        716,  849, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
        136,    6, //ucHSyncWidth, ucVSyncWidth
       1712,  843, //usHTotal, usVTotal
       1280,  800, //usModeHActive, usModeVActive
       1280,  800, //usCapHActive, usCapVActive
        200,   31, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1280x800_85HZ //usModeIndex
    },
    { //1280x960@60
        OFF, //ucSampling 
        600,  600, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
        112,    3, //ucHSyncWidth, ucVSyncWidth
       1800, 1000, //usHTotal, usVTotal
       1280,  960, //usModeHActive, usModeVActive
       1280,  960, //usCapHActive, usCapVActive
        295,   33, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1280x960_60HZ //usModeIndex
    },
    { //1280x960@75
        OFF, //ucSampling 
        750,  750, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
        144,    3, //ucHSyncWidth, ucVSyncWidth
       1680, 1000, //usHTotal, usVTotal
       1280,  960, //usModeHActive, usModeVActive
       1280,  960, //usCapHActive, usCapVActive
        224,   36, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1280x960_75HZ //usModeIndex
    },
    { //1280x960@85
        OFF, //ucSampling 
        859,  850, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
        160,    3, //ucHSyncWidth, ucVSyncWidth
       1728, 1011, //usHTotal, usVTotal
       1280,  960, //usModeHActive, usModeVActive
       1280,  960, //usCapHActive, usCapVActive
        205,   44, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1280x960_85HZ //usModeIndex
    },
    { //1280x1024@60
        OFF, //ucSampling 
        640,  600, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
        112,    3, //ucHSyncWidth, ucVSyncWidth
       1688, 1066, //usHTotal, usVTotal
       1280, 1024, //usModeHActive, usModeVActive
       1280, 1024, //usCapHActive, usCapVActive
        231,   35, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1280x1024_60HZ //usModeIndex
    },
    { //1280x1024@67
        OFF, //ucSampling 
        717,  672, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
        112,    3, //ucHSyncWidth, ucVSyncWidth
       1632, 1067, //usHTotal, usVTotal
       1280, 1024, //usModeHActive, usModeVActive
       1280, 1024, //usCapHActive, usCapVActive
        207,   30, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1280x1024_67HZ //usModeIndex
    },
    { //1280x1024@70 Reduced Blanking
        OFF, //ucSampling 
        749,  699, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
        160,    4, //ucHSyncWidth, ucVSyncWidth
       1696, 1072, //usHTotal, usVTotal
       1280, 1024, //usModeHActive, usModeVActive
       1280, 1024, //usCapHActive, usCapVActive
        206,   39, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1280x1024_70HZ_RB //usModeIndex
    },
    { //1280x1024@70
        OFF, //ucSampling 
        744,  700, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
        112,    5, //ucHSyncWidth, ucVSyncWidth
       1678, 1064, //usHTotal, usVTotal
       1280, 1024, //usModeHActive, usModeVActive
       1280, 1024, //usCapHActive, usCapVActive
        198,   31, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1280x1024_70HZ //usModeIndex
    },
    { //1280x1024@72
        OFF, //ucSampling 
        779,  720, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
        136,    5, //ucHSyncWidth, ucVSyncWidth
       1728, 1082, //usHTotal, usVTotal
       1280, 1024, //usModeHActive, usModeVActive
       1280, 1024, //usCapHActive, usCapVActive
        206,   49, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1280x1024_72HZ //usModeIndex
    },
    { //1280x1024@75
        OFF, //ucSampling 
        800,  750, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
        100,   20, //ucHSyncWidth, ucVSyncWidth
       1688, 1066, //usHTotal, usVTotal
       1280, 1024, //usModeHActive, usModeVActive
       1280, 1024, //usCapHActive, usCapVActive
        230,   35, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1280x1024_75HZ //usModeIndex
    },
    { //1280x1024@76
        OFF, //ucSampling 
        812,  762, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
         64,    8, //ucHSyncWidth, ucVSyncWidth
       1664, 1066, //usHTotal, usVTotal
       1280, 1024, //usModeHActive, usModeVActive
       1280, 1024, //usCapHActive, usCapVActive
        272,   29, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1280x1024_76HZ //usModeIndex
    },
    { //1280x1024@85
        OFF, //ucSampling 
        912,  850, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
        160,    3, //ucHSyncWidth, ucVSyncWidth
       1728, 1072, //usHTotal, usVTotal
       1280, 1024, //usModeHActive, usModeVActive
       1280, 1024, //usCapHActive, usCapVActive
        205,   41, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1280x1024_85HZ //usModeIndex
    },
    { //1360x768@60
        OFF, //ucSampling 
        477,  600, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
        112,    6, //ucHSyncWidth, ucVSyncWidth
       1792,  795, //usHTotal, usVTotal
       1360,  768, //usModeHActive, usModeVActive
       1360,  768, //usCapHActive, usCapVActive
        240,   15, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1360x768_60HZ //usModeIndex
    },
    { //1366x768@60
        OFF, //ucSampling 
        477,  598, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
        143,    3, //ucHSyncWidth, ucVSyncWidth
       1792,  798, //usHTotal, usVTotal
       1366,  768, //usModeHActive, usModeVActive
       1366,  768, //usCapHActive, usCapVActive
        198,   21, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1366x768_60HZ //usModeIndex
    },
    { //1400x1050@60 Reduced Blanking
        OFF, //ucSampling 
        647,  600, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
         32,    4, //ucHSyncWidth, ucVSyncWidth
       1560, 1080, //usHTotal, usVTotal
       1400, 1050, //usModeHActive, usModeVActive
       1400, 1050, //usCapHActive, usCapVActive
         63,   20, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1400x1050_60HZ_RB //usModeIndex
    },
    { //1400x1050@60
        OFF, //ucSampling 
        653,  600, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
        144,    4, //ucHSyncWidth, ucVSyncWidth
       1864, 1089, //usHTotal, usVTotal
       1400, 1050, //usModeHActive, usModeVActive
       1400, 1050, //usCapHActive, usCapVActive
        216,   29, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1400x1050_60HZ //usModeIndex
    },
    { //1400x1050@75
        OFF, //ucSampling 
        823,  749, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
        144,    4, //ucHSyncWidth, ucVSyncWidth
       1896, 1099, //usHTotal, usVTotal
       1400, 1050, //usModeHActive, usModeVActive
       1400, 1050, //usCapHActive, usCapVActive
        231,   39, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1400x1050_75HZ //usModeIndex
    },
    { //1400x1050@85
        OFF, //ucSampling 
        939,  850, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
        152,    4, //ucHSyncWidth, ucVSyncWidth
       1912, 1105, //usHTotal, usVTotal
       1400, 1050, //usModeHActive, usModeVActive
       1400, 1050, //usCapHActive, usCapVActive
        239,   45, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1400x1050_85HZ //usModeIndex
    },

    { //1440x900@60 Reduced Blanking
        OFF, //ucSampling 
        555,  599, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
         32,    6, //ucHSyncWidth, ucVSyncWidth
       1600,  926, //usHTotal, usVTotal
       1440,  900, //usModeHActive, usModeVActive
       1440,  900, //usCapHActive, usCapVActive
         64,   14, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1440x900_60HZ_RB //usModeIndex
    },
    { //1440x900@60
        OFF, //ucSampling 
        559,  599, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
        152,    6, //ucHSyncWidth, ucVSyncWidth
       1904,  934, //usHTotal, usVTotal
       1440,  900, //usModeHActive, usModeVActive
       1440,  900, //usCapHActive, usCapVActive
        216,   22, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1440x900_60HZ //usModeIndex
    },
    { //1440x900@75
        OFF, //ucSampling 
        706,  750, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
        152,    6, //ucHSyncWidth, ucVSyncWidth
       1936,  942, //usHTotal, usVTotal
       1440,  900, //usModeHActive, usModeVActive
       1440,  900, //usCapHActive, usCapVActive
        232,   30, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1440x900_75HZ //usModeIndex
    },
    { //1600x900@60
        OFF, //ucSampling 
        555,  600, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
         32,    5, //ucHSyncWidth, ucVSyncWidth
       1760,  926, //usHTotal, usVTotal
       1600,  900, //usModeHActive, usModeVActive
       1600,  900, //usCapHActive, usCapVActive
         63,   15, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1600x900_60HZ //usModeIndex
    },
    { //1600x1000@60 Reduced Blanking
        OFF, //ucSampling 
        617,  599, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
         32,    6, //ucHSyncWidth, ucVSyncWidth
       1760, 1029, //usHTotal, usVTotal
       1600, 1000, //usModeHActive, usModeVActive
       1600, 1000, //usCapHActive, usCapVActive
         63,   17, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1600x1000_60HZ_RB //usModeIndex
    },
    { //1600x1000@60
        OFF, //ucSampling 
        622,  599, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
        168,    6, //ucHSyncWidth, ucVSyncWidth
       2128, 1038, //usHTotal, usVTotal
       1600, 1000, //usModeHActive, usModeVActive
       1600, 1000, //usCapHActive, usCapVActive
        247,   26, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1600x1000_60HZ //usModeIndex
    },
    { //1600x1000@75
        OFF, //ucSampling 
        784,  748, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
        168,    6, //ucHSyncWidth, ucVSyncWidth
       2160, 1047, //usHTotal, usVTotal
       1600, 1000, //usModeHActive, usModeVActive
       1600, 1000, //usCapHActive, usCapVActive
        261,   35, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1600x1000_75HZ //usModeIndex
    },
    { //1600x1200@60 Reduced Blanking
        OFF, //ucSampling 
        740,  599, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
         32,    4, //ucHSyncWidth, ucVSyncWidth
       1760, 1235, //usHTotal, usVTotal
       1600, 1200, //usModeHActive, usModeVActive
       1600, 1200, //usCapHActive, usCapVActive
         62,   26, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1600x1200_60HZ_RB //usModeIndex
    },
    { //1600x1200@60
        OFF, //ucSampling 
        750,  600, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
        192,    4, //ucHSyncWidth, ucVSyncWidth
       2160, 1250, //usHTotal, usVTotal
       1600, 1200, //usModeHActive, usModeVActive
       1600, 1200, //usCapHActive, usCapVActive
        285,   43, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1600x1200_60HZ //usModeIndex
    },
    { //1600x1200@65
        OFF, //ucSampling 
        813,  650, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
        192,    3, //ucHSyncWidth, ucVSyncWidth
       2160, 1250, //usHTotal, usVTotal
       1600, 1200, //usModeHActive, usModeVActive
       1600, 1200, //usCapHActive, usCapVActive
        284,   43, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1600x1200_65HZ //usModeIndex
    },
    { //1600x1200@70
        OFF, //ucSampling 
        875,  700, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
        192,    3, //ucHSyncWidth, ucVSyncWidth
       2160, 1250, //usHTotal, usVTotal
       1600, 1200, //usModeHActive, usModeVActive
       1600, 1200, //usCapHActive, usCapVActive
        284,   43, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1600x1200_70HZ //usModeIndex
    },
    { //1600x1200@75
        OFF, //ucSampling 
        938,  750, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
        192,    3, //ucHSyncWidth, ucVSyncWidth
       2160, 1250, //usHTotal, usVTotal
       1600, 1200, //usModeHActive, usModeVActive
       1600, 1200, //usCapHActive, usCapVActive
        284,   43, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1600x1200_75HZ //usModeIndex
    },
    { //1680x1050@60 Reduced Blanking
        OFF, //ucSampling 
        647,  599, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
         32,    6, //ucHSyncWidth, ucVSyncWidth
       1840, 1080, //usHTotal, usVTotal
       1680, 1050, //usModeHActive, usModeVActive
       1680, 1050, //usCapHActive, usCapVActive
         63,   18, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1680x1050_60HZ_RB //usModeIndex
    },
    { //1680x1050@60
        OFF, //ucSampling 
        653,  600, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
        176,    6, //ucHSyncWidth, ucVSyncWidth
       2240, 1089, //usHTotal, usVTotal
       1680, 1050, //usModeHActive, usModeVActive
       1680, 1050, //usCapHActive, usCapVActive
        263,   27, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1680x1050_60HZ //usModeIndex
    },
    { //1680x1050@75
        OFF, //ucSampling 
        823,  749, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
        176,    6, //ucHSyncWidth, ucVSyncWidth
       2272, 1099, //usHTotal, usVTotal
       1680, 1050, //usModeHActive, usModeVActive
       1680, 1050, //usCapHActive, usCapVActive
        279,   37, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1680x1050_75HZ //usModeIndex
    },
    { //1600x1280@60
        OFF, //ucSampling 
        795,  599, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
        168,    7, //ucHSyncWidth, ucVSyncWidth
       2160, 1327, //usHTotal, usVTotal
       1600, 1280, //usModeHActive, usModeVActive
       1600, 1280, //usCapHActive, usCapVActive
        261,   34, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1600x1280_60HZ //usModeIndex
    },
    { //1920x1080@60 Reduced Blanking
        OFF, //ucSampling 
        666,  599, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
         32,    5, //ucHSyncWidth, ucVSyncWidth
       2080, 1111, //usHTotal, usVTotal
       1920, 1080, //usModeHActive, usModeVActive
       1920, 1080, //usCapHActive, usCapVActive
         64,   19, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1920x1080_60HZ_RB //usModeIndex
    },
    { //1920x1080@60
        OFF, //ucSampling 
        672,  600, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
        200,    5, //ucHSyncWidth, ucVSyncWidth
       2576, 1120, //usHTotal, usVTotal
       1920, 1080, //usModeHActive, usModeVActive
       1920, 1080, //usCapHActive, usCapVActive
        311,   29, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1920x1080_60HZ //usModeIndex
    },
    { //1920x1080P@60 //1080P
        OFF, //ucSampling 
        675,  600, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
         44,    5, //ucHSyncWidth, ucVSyncWidth
       2200, 1125, //usHTotal, usVTotal
       1920, 1080, //usModeHActive, usModeVActive
       1920, 1080, //usCapHActive, usCapVActive
        130,   33, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1920x1080P_60HZ //usModeIndex
    },
    { //1920x1200@50 Reduced Blanking
        OFF, //ucSampling 
        614,  500, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
         32,    6, //ucHSyncWidth, ucVSyncWidth
       2080, 1229, //usHTotal, usVTotal
       1920, 1200, //usModeHActive, usModeVActive
       1920, 1200, //usCapHActive, usCapVActive
         62,   17, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1920x1200_50HZ_RB //usModeIndex
    },
    { //1920x1200@60 Reduced Blanking
        OFF, //ucSampling 
        740,  600, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
         32,    6, //ucHSyncWidth, ucVSyncWidth
       2080, 1235, //usHTotal, usVTotal
       1920, 1200, //usModeHActive, usModeVActive
       1920, 1200, //usCapHActive, usCapVActive
         61,   23, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1920x1200_60HZ_RB //usModeIndex
    },
    { //1920x1200@60
        OFF, //ucSampling 
        746,  599, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
        200,    6, //ucHSyncWidth, ucVSyncWidth
       2592, 1245, //usHTotal, usVTotal
       1920, 1200, //usModeHActive, usModeVActive
       1920, 1200, //usCapHActive, usCapVActive
        318,   33, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1920x1200_60HZ //usModeIndex
    },
    { //720x480P@60
        OFF, //ucSampling 
        315,  600, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
         62,    9, //ucHSyncWidth, ucVSyncWidth
        858,  525, //usHTotal, usVTotal
        720,  480, //usModeHActive, usModeVActive
        720,  480, //usCapHActive, usCapVActive
         46,   27, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _720x480P_60HZ //usModeIndex
    },
    { //720x576P@50
        OFF, //ucSampling 
        313,  500, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
         64,    5, //ucHSyncWidth, ucVSyncWidth
        864,  625, //usHTotal, usVTotal
        720,  576, //usModeHActive, usModeVActive
        720,  576, //usCapHActive, usCapVActive
         54,   36, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _720x576P_50HZ //usModeIndex
    },
    { //720x576P@60
        OFF, //ucSampling 
        360,  600, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
         64,    5, //ucHSyncWidth, ucVSyncWidth
        912,  600, //usHTotal, usVTotal
        720,  576, //usModeHActive, usModeVActive
        720,  576, //usCapHActive, usCapVActive
         99,   15, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _720x576P_60HZ //usModeIndex
    },
    { //1280x720P@50
        OFF, //ucSampling 
        375,  500, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
         40,    5, //ucHSyncWidth, ucVSyncWidth
       1980,  750, //usHTotal, usVTotal
       1280,  720, //usModeHActive, usModeVActive
       1280,  720, //usCapHActive, usCapVActive
        205,   17, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1280x720P_50HZ //usModeIndex
    },
    { //1920x1080P@50
        OFF, //ucSampling 
        563,  500, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
         44,    5, //ucHSyncWidth, ucVSyncWidth
       2640, 1125, //usHTotal, usVTotal
       1920, 1080, //usModeHActive, usModeVActive
       1920, 1080, //usCapHActive, usCapVActive
        133,   35, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1920x1080P_50HZ //usModeIndex
    },
    { //720x480I@60
        OFF, //ucSampling 
        157,  600, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
         62,    2, //ucHSyncWidth, ucVSyncWidth
        858,  262, //usHTotal, usVTotal
        720,  480, //usModeHActive, usModeVActive
        720,  480, //usCapHActive, usCapVActive
         44,   12, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _720x480I_60HZ //usModeIndex
    },
    { //1440x480I@60
        OFF, //ucSampling 
        157,  600, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
        124,    2, //ucHSyncWidth, ucVSyncWidth
       1716,  262, //usHTotal, usVTotal
       1440,  480, //usModeHActive, usModeVActive
       1440,  480, //usCapHActive, usCapVActive
         88,   12, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1440x480I_60HZ //usModeIndex
    },
    { //2880x480I@60
        OFF, //ucSampling 
        157,  600, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
        248,    2, //ucHSyncWidth, ucVSyncWidth
       3432,  262, //usHTotal, usVTotal
       2880,  480, //usModeHActive, usModeVActive
       2880,  480, //usCapHActive, usCapVActive
        176,   12, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _2880x480I_60HZ //usModeIndex
    },
    { //1920x1080I@60
        OFF, //ucSampling 
        338,  600, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
         44,    2, //ucHSyncWidth, ucVSyncWidth
       2200,  562, //usHTotal, usVTotal
       1920, 1080, //usModeHActive, usModeVActive
       1920, 1080, //usCapHActive, usCapVActive
        133,   12, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1920x1080I_60HZ //usModeIndex
    },
    { //720x576I@50
        OFF, //ucSampling 
        157,  500, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
         63,    1, //ucHSyncWidth, ucVSyncWidth
        864,  312, //usHTotal, usVTotal
        720,  576, //usModeHActive, usModeVActive
        720,  576, //usCapHActive, usCapVActive
         56,   16, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _720x576I_50HZ //usModeIndex
    },
    { //1440x576I@50
        OFF, //ucSampling 
        157,  500, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
        126,    1, //ucHSyncWidth, ucVSyncWidth
       1728,  312, //usHTotal, usVTotal
       1440,  576, //usModeHActive, usModeVActive
       1440,  576, //usCapHActive, usCapVActive
        112,   16, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1440x576I_50HZ //usModeIndex
    },
    { //2880x576I@50
        OFF, //ucSampling 
        157,  500, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
        252,    1, //ucHSyncWidth, ucVSyncWidth
       3456,  312, //usHTotal, usVTotal
       2880,  576, //usModeHActive, usModeVActive
       2880,  576, //usCapHActive, usCapVActive
        224,   16, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _2880x576I_50HZ //usModeIndex
    },
    { //1920x1080I@50
        OFF, //ucSampling 
        322,  515, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
        168,   22, //ucHSyncWidth, ucVSyncWidth
       2304,  625, //usHTotal, usVTotal
       1920, 1080, //usModeHActive, usModeVActive
       1920, 1080, //usCapHActive, usCapVActive
        132,   12, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1920x1080I_50HZ_RB //usModeIndex
    },
    { //1920x1080I@50
        OFF, //ucSampling 
        281,  500, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
         44,    2, //ucHSyncWidth, ucVSyncWidth
       2640,  562, //usHTotal, usVTotal
       1920, 1080, //usModeHActive, usModeVActive
       1920, 1080, //usCapHActive, usCapVActive
        132,   12, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1920x1080I_50HZ //usModeIndex
    },
    { //2048x1152@60 Reduced Blanking
        OFF, //ucSampling 
        701,  599, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
         32,    3, //ucHSyncWidth, ucVSyncWidth
       2208, 1185, //usHTotal, usVTotal
       2048, 1152, //usModeHActive, usModeVActive
       2048, 1152, //usCapHActive, usCapVActive
         62,   22, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _2048x1152_60HZ_RB //usModeIndex
    },
    { //2048x1152@60
        OFF, //ucSampling 
        716,  600, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
        216,    3, //ucHSyncWidth, ucVSyncWidth
       2752, 1195, //usHTotal, usVTotal
       2048, 1152, //usModeHActive, usModeVActive
       2048, 1152, //usCapHActive, usCapVActive
        338,   32, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _2048x1152_60HZ //usModeIndex
    },
    { //1280x600@60
        OFF, //ucSampling 
        377,  600, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
        128,    5, //ucHSyncWidth, ucVSyncWidth
       1688,  628, //usHTotal, usVTotal
       1280,  600, //usModeHActive, usModeVActive
       1280,  600, //usCapHActive, usCapVActive
        81,   20, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1280x600_60HZ //usModeIndex
    },
    { //1024x600@60
        OFF, //ucSampling 
        373,  599, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
        136,    6, //ucHSyncWidth, ucVSyncWidth
       1312,  624, //usHTotal, usVTotal
       1024,  600, //usModeHActive, usModeVActive
       1024,  600, //usCapHActive, usCapVActive
        144,   11, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1024x600_60HZ //usModeIndex
    },
    { //1920x1080i@50
        OFF, //ucSampling 
        313,  500, HPVP|HPVN|HNVP|HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
        168,    5, //ucHSyncWidth, ucVSyncWidth
       2304,  625, //usHTotal, usVTotal
       1920, 1080, //usModeHActive, usModeVActive
       1920, 1080, //usCapHActive, usCapVActive
        184,   57, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1920x1080I_50HZ125 //usModeIndex
    },
    
    //CHIU ADD
    { //1850x1036@60
        OFF, //ucSampling 
        687,  600, 	HNVN, //usHSyncFreq, usVSyncFreq, ucHVPolarity
        48,    5, //ucHSyncWidth, ucVSyncWidth
       2200,  1145, //usHTotal, usVTotal
       1850, 1036, //usModeHActive, usModeVActive
       1850, 1036, //usCapHActive, usCapVActive
        192,   51, //usHStart, usVStart
         12,   12,   3, //ucHSyncTolerance, ucVSyncTolerance, ucVTotalTolerance
       _1850x1036_60HZ //usModeIndex
    },    
   
    { //End of ModeTable
       OFF, //ucSampling 
       0xFFFF, 0xFFFF, 0xFF,
         0xFF,   0xFF,
       0xFFFF, 0xFFFF,
       0xFFFF, 0xFFFF,
       0xFFFF, 0xFFFF,
       0xFFFF, 0xFFFF,
         0xFF,   0xFF, 0xFF,
       0xFFFF
    },
};

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
