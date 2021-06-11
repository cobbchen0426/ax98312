

//CHIU DEFINE 

//-----------------------------------	06N		//150907 george
#if defined(SRP_LQ064V3DG01)				
	#include "SRP_LQ064V3DG01\EDID.c" 

//-----------------------------------	07W		//150108 mike
#elif defined(D_FG0700A2DSSWBG02)				
	#include "D_FG0700A2DSSWBG02\EDID.c" 
#elif defined (AUO_G070VW01_V0)
	#include "AUO_G070VW01_V0\EDID.c"			//150113 mike	
#elif defined(SGD_GVTW70SNAD1E0)
	#include "SGD_GVTW70SNAD1E0\EDID.c"			//160106 george
//------------------------------------	10"
#elif defined(CMO_G104X1_L04)				
	#include "CMO_G104X1_L04\EDID.c"	   		//150813 george

#elif defined(IVO_M101NWWB_R3)				
	#include "IVO_M101NWWB_R3\EDID.c"	   		//160309 george

//------------------------------------	15"
#elif defined(AUO_G151EVN01_720)				
	#include "AUO_G151EVN01_720\EDID.c"
#elif defined(AUO_G151EVN01_1024)				
	#include "AUO_G151EVN01_1024\EDID.c"
#elif defined(AUO_G150XTN05_V0)
	#include "AUO_G150XTN05_V0\EDID.c"   			//15" 140515 mike 
//------------------------------------	17"	
#elif defined (AUO_G170ETN01_V0)
	#include "AUO_G170ETN01_V0\EDID.c"			//140303 mike 1280x1024

#elif defined (TRULY_TFT1280120)
	#include "TRULY_TFT1280120\EDID.c"			//george 1280x120 (1280x1024)

//------------------------------------	17.3"
#elif defined (PET_OT173ZFDDLN_00)
	#include "PET_OT173ZFDDLN_00\EDID.c"			//150202 mike 1920x1080

//------------------------------------	19W" 
#elif defined (LWO_EWK_1902C)
	#include "LWO_EWK-1902C\EDID.c"				//160223 george 1920x360
//------------------------------------ 	21.5"
#elif defined(LG_LM215WF3_SLK1)		
	#include "LG_LM215WF3-SLK1\EDID.c"	
#elif defined(LG_LM215WF3_SLC1)		
	#include "LG_LM215WF3-SLC1\EDID.c"
#elif defined(PET_OT215ZFWDLV_02)				
	#include "PET_OT215ZFWDLV_02\EDID.c"			//150105 mike 	
//------------------------------------	22"ÿ
#elif defined (CMO_M220ZGE_L20)
#include "CMO_M220ZGE_L20\EDID.c"		
//------------------------------------	23"
#elif defined(LG_LM230WF3_SLD1)				
	#include "LG_LM230WF3_SLD1\EDID.c"
//------------------------------------   	27"		
#elif defined(AUO_P270HVN010)	
	#include "AUO_P270HVN010\EDID.c"		
#elif defined(LG_LM270WF5_SLM1)				
	#include "LG_LM270WF5_SLM1\EDID.c"
//------------------------------------   	29"		//151117 george
#elif defined(INL_S290AJ1_LE1)	
	#include "INL_S290AJ1-LE1\EDID.c"		

//------------------------------------  	32"
#elif defined(LD320EUN_SEM1)				
	#include "LD320EUN_SEM1\EDID.c"	
#elif defined(LC320EUN_SEM2)				
	#include "LC320EUN_SEM2\EDID.c"	
#elif defined(LC320WXN_SCA4)				
	#include "LC320WXN_SCA4\EDID.c"
//------------------------------------  	38"
#elif defined(TX38D09VM0CAA)				
	#include "TX38D09VM0CAA\EDID.c"	
//------------------------------------  	42"	
#elif defined(LC420EUN_SFM1)				
	#include "LC420EUN_SFM1\EDID.c"
//------------------------------------	46"
#elif defined(AUO_P460HVN03_V0)
       #include "AUO_P460HVN03_V0\EDID.c"			//141211 mike
//------------------------------------  	55"	
#elif defined(LC550EUN_SFM2)				
	#include "LC550EUN_SFM2\EDID.c"

#endif

