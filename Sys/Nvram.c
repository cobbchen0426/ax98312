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
#include "string.h"
#include "Include.h"

//******************************************************************************
// M A C R O   D E F I N I T I O N S
//******************************************************************************

//******************************************************************************
// G L O B A L   V A R I A B L E S
//******************************************************************************
/*!
 * Default value of user data.
 */
code NvramUserData UserDataDefault = {		// sizeof(don't over 31 bytes): 29 uchar	+ Add(bALSOnOff, ucALSBaseVal, bTouchOnOff)
    0x00, //UCHAR bPowerStatus : 1;
    0x00, //UCHAR bOSDLock : 1;
    0x00, //UCHAR bDDCCI : 1;
#if AUDIO_EnDis == ENABLE
    0x00, //UCHAR bAudioMute : 1;
#else
	0x01, //UCHAR bAudioMute : 1;	//(when Audio "Disable" is ucVolume = 0xFF) 
#endif

    0x00, //UCHAR bGammaOnOff : 1; 				 
    0x00, //UCHAR bLDOnOff : 1;
#if ENABLE_HDMI_PRETEST == ON
    0x00, //UCHAR bAutoSyncSource : 1;
#else
    0x01, //UCHAR bAutoSyncSource : 1;
#endif
    0x00, //UCHAR bOSDRotation : 1;
    0x00, //UCHAR bOverScan : 1;			// 9 bits

#if ALS_EnDis == ALSMODE	
#elif ALS_EnDis == ALSOffSET	
	0x01, //UCHAR bALSOnOff   : 1;			// george: F_ALSOnOff_01
#elif ALS_EnDis == ALSRange	//for ADS
	0x00, //UCHAR bALSOnOff   : 1;			
#else
#endif	//#if ALS_EnDis == ENABLE

#if TOUCH_EnDis == ENABLE
    0x01, //UCHAR bTouchOnOff : 1;			// george: F_Touch_01
#endif //#if TOUCH_EnDis == ENABLE

    0x00, //UCHAR ucDCRMode;
    0x00, //UCHAR ucLanguage;
    0x5A, //0x5A, //UCHAR ucBrightness;				
    0x5A, //UCHAR ucContrast;					
    0x1E, //UCHAR ucOSDTimer;  0x1E=30sec

#if SET_SHOW_OSD_POSITION == SET_OSD_LEFT_TOP
    00, //UCHAR ucOSDX;
    100, //UCHAR ucOSDY;
#elif  SET_SHOW_OSD_POSITION == SET_OSD_CENTER_TOP
    50, //UCHAR ucOSDX;
    96, //100, //UCHAR ucOSDY;
#else
    0x32, //UCHAR ucOSDX;
    0x32, //UCHAR ucOSDY;
#endif											

    0x00, //UCHAR ucOSDTransparent;

#if AUDIO_EnDis == ENABLE
    0x32, //UCHAR ucVolume;
#else
    0xFF, //UCHAR ucVolume;		//(when Audio "Disable" is ucVolume = 0xFF) 
#endif

    CLRTMP_6500K, //UCHAR ucColorTemp;
    0x5A, //0x46, //UCHAR ucUserRGain;
    0x5A, //0x46, //UCHAR ucUserGGain;
    0x5A, //0x46, //UCHAR ucUserBGain;
    0x32, //UCHAR ucUserROffset;				//----------------------- george 16 seats.
    0x32, //UCHAR ucUserGOffset;
    0x32, //UCHAR ucUserBOffset;
    0x00, //UCHAR ucAspectRatio;
    0x00, //UCHAR ucODMode;
    0x00, //UCHAR ucBFMode;
#if ENABLE_HDMI_PRETEST == ON
    MODEL_INPUT_DIG0, //UCHAR ucInputSource;
#else
    MODEL_INPUT_VGA0, //UCHAR ucInputSource;
#endif
    0x00, //uc2DTo3DMode;
    0x06, //uc2Dto3DDepth;
    0x06, //uc2Dto3DView;						
    0x00, //uc3DCfg;
    0x00, //ucSRMode;							//----------------------- george 25byts + 2byts(11bit)= 27 seats.


#if ALS_EnDis == ALSMODE
	0x00, //ucALSMode (0:Off, 1:InDoor, 2:OutDoor)	// george: F_ALSBV_01
#elif ALS_EnDis == ALSOffSET	
	0x00, //0x32 //UCHAR ucALSBaseVal				// george: F_ALSBV_01
#elif ALS_EnDis == ALSRange	//for ADS
	100, //70, //ALS_Brig-MAX
	  0, //30, //ALS_Brig-MIN
#else	//Normal
#endif	//#if ALS_EnDis == ENABLE

//	0x06, //AA_for test

	0xABDE,	//0x0201,	//USHRT usADBoardID;		//for customer more adboard management.

    NVRAM_FIELD_END_FLAG //USHRT usUsrEnd;		//----------------------- be used 2 seats.
};

/*!
 * Default value of calibration data.
 */
code NvramCalibData CalibDataDefault = {		// sizeof: 31 uchar
    0x80, //UCHAR ucADCRGain;
    0x80, //UCHAR ucADCGGain;
    0x80, //UCHAR ucADCBGain;
    0x80, //UCHAR ucADCROffset;
    0x80, //UCHAR ucADCGOffset;
    0x80, //UCHAR ucADCBOffset;
    0xFF, //UCHAR uc5000KRGain;
    0xFF, //UCHAR uc5000KGGain;
    0xF0, //UCHAR uc5000KBGain;
    FACTORY_6500K_R, //UCHAR uc6500KRGain;
    FACTORY_6500K_G, //UCHAR uc6500KGGain;
    FACTORY_6500K_B, //UCHAR uc6500KBGain;
    FACTORY_7500K_R, //UCHAR uc7500KRGain;
    FACTORY_7500K_G, //UCHAR uc7500KGGain;
    FACTORY_7500K_B, //UCHAR uc7500KBGain;
    0xF8, //UCHAR uc8200KRGain;
    0xF8, //UCHAR uc8200KGGain;
    0xFF, //UCHAR uc8200KBGain;
    FACTORY_9300K_R, //UCHAR uc9300KRGain;
    FACTORY_9300K_G, //UCHAR uc9300KGGain;
    FACTORY_9300K_B, //UCHAR uc9300KBGain;
    0xF0, //UCHAR uc11500KRGain;
    0xF0, //UCHAR uc11500KGGain;
    0xFF, //UCHAR uc11500KBGain;
    255, //UCHAR ucsRGBRGain;
    255, //UCHAR ucsRGBGGain;
    255, //UCHAR ucsRGBBGain;
    
    //ADD BY CHIU
    DEFAULT_GAMMA_INDEX,		//UCHAR ucGammaVal; 
    DEFAULT_INVERTER_VAL,		//UCHAR ucBacklite;
    
    
    NVRAM_FIELD_END_FLAG //USHRT usCalEnd;
};

/*!
 * Default value of system data.
 */
code NvramSystemData SystemDataDefault = {		// sizeof: 22 uchar
    0x00,   //UCHAR bFactory : 1;
    0x00,  //UCHAR bDemo : 1;
    0x00,  //UCHAR bDFR: 1;
    0x00,  //UCHAR bSR: 1;
    0x00,   //UCHAR bBurnIn : 1;
    0x00,   //UCHAR bShowLogo : 1;
    0x00,   //UCHAR ucPowerOnTimerM;
    0x0000, //USHRT usPowerOnTimerH;
    0x00,   //UCHAR ucPOTimerM_FE2P;
    0x0000, //USHRT usPOTimerH_FE2P;
    0x00,   //UCHAR ucTimingWriteIdx;
    FIRMWARE_VER, //USHRT usFirmwareVer;
    0x55AA, //USHRT usNvramID;
    0xFFFF, //USHRT usChkSum;
    NVRAM_USER_ADDR+sizeof(NvramUserData),		//addr: 0x270 george
    NVRAM_CALIB_ADDR+sizeof(NvramCalibData),	//addr: 0x290 george
    NVRAM_SYSTEM_ADDR+sizeof(NvramSystemData),	//addr: 0x2B0 george
    NVRAM_FIELD_END_FLAG  //USHRT usSysEnd;
};

//******************************************************************************
// S T A T I C   V A R I A B L E S
//******************************************************************************
//CHIU 
#define	DefaultEDID 		ON


//--FEFANJACKY for 1850x1036 -------------------------------------------------
//Tatung1850x1036-NO_1920X1080
#if SPECIALAPP == ON
static code UCHAR _Default_VGA_EDID[128]={	
   0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x3A,0xD4,0x5A,0x66,0x01,0x00,0x00,0x00,
   0x0F,0x17,0x01,0x03,0x0E,0x3A,0x20,0x78,0xEA,0x36,0xD5,0xA2,0x56,0x53,0x99,0x27,
   0x0D,0x50,0x54,0xA3,0x08,0x00,0x81,0x80,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
   0x01,0x01,0x01,0x01,0x01,0x01,0x09,0x3B,0x3A,0x5E,0x71,0x0C,0x6D,0x40,0x6E,0x37,
   0x85,0x04,0x40,0x44,0x21,0x00,0x00,0x18,0x66,0x21,0x50,0xB0,0x51,0x00,0x1B,0x30,
   0x40,0x70,0x36,0x00,0x40,0x44,0x21,0x00,0x00,0x1E,0x00,0x00,0x00,0xFD,0x00,0x32,
   0x41,0x1E,0x64,0x16,0x00,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x00,0x00,0xFC,
   0x00,0x54,0x55,0x53,0x20,0x4C,0x32,0x36,0x58,0x58,0x58,0x0A,0x0A,0x0A,0x00,0x41,
};

static code UCHAR _Default_DVI_EDID[128]={
   0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x3A,0xD4,0x5A,0x66,0x01,0x00,0x00,0x00,
   0x0F,0x17,0x01,0x03,0x80,0x3A,0x20,0x78,0xEA,0x36,0xD5,0xA2,0x56,0x53,0x99,0x27,
   0x0D,0x50,0x54,0xA3,0x08,0x00,0x81,0x80,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
   0x01,0x01,0x01,0x01,0x01,0x01,0x09,0x3B,0x3A,0x5E,0x71,0x0C,0x6D,0x40,0x6E,0x37,
   0x85,0x04,0x40,0x44,0x21,0x00,0x00,0x18,0x66,0x21,0x50,0xB0,0x51,0x00,0x1B,0x30,
   0x40,0x70,0x36,0x00,0x40,0x44,0x21,0x00,0x00,0x1E,0x00,0x00,0x00,0xFD,0x00,0x32,
   0x41,0x1E,0x64,0x16,0x00,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x00,0x00,0xFC,
   0x00,0x54,0x55,0x53,0x20,0x4C,0x32,0x36,0x58,0x58,0x58,0x0A,0x0A,0x0A,0x00,0xCF,
};

static code UCHAR _Default_HDMI_EDID[256]={
    0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x09, 0xD1, 0x25, 0x78, 0x45, 0x54, 0x00, 0x00,                               
    0x24, 0x12, 0x01, 0x03, 0x80, 0x35, 0x1E, 0x78, 0x2E, 0x60, 0x81, 0xA6, 0x56, 0x4A, 0x9C, 0x25,                               
    0x12, 0x50, 0x54, 0xA5, 0x6B, 0x80, 0x71, 0x00, 0x81, 0xC0, 0x81, 0x40, 0x81, 0x80, 0xA9, 0xC0,                               
    0xB3, 0x00, 0xD1, 0xC0, 0x01, 0x01, 0x02, 0x3A, 0x80, 0x18, 0x71, 0x38, 0x2D, 0x40, 0x58, 0x2C,                               
    0x45, 0x00, 0x13, 0x2B, 0x21, 0x00, 0x00, 0x1A, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x30, 0x30, 0x30,                               
    0x30, 0x30, 0x30, 0x30, 0x30, 0x53, 0x4C, 0x30, 0x0A, 0x20, 0x00, 0x00, 0x00, 0xFD, 0x00, 0x32,                               
    0x4C, 0x18, 0x53, 0x11, 0x00, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0xFC,                               
    0x00, 0x42, 0x65, 0x6E, 0x51, 0x20, 0x45, 0x57, 0x32, 0x34, 0x33, 0x30, 0x0A, 0x20, 0x01, 0x7B,                               
    0x02, 0x03, 0x22, 0xF1, 0x4F, 0x90, 0x05, 0x04, 0x03, 0x02, 0x01, 0x11, 0x12, 0x13, 0x14, 0x06,                               
    0x07, 0x15, 0x16, 0x1F, 0x23, 0x09, 0x07, 0x07, 0x65, 0x03, 0x0C, 0x00, 0x10, 0x00, 0x83, 0x01,                               
    0x00, 0x00, 0x02, 0x3A, 0x80, 0x18, 0x71, 0x38, 0x2D, 0x40, 0x58, 0x2C, 0x45, 0x00, 0x13, 0x2B,                               
    0x21, 0x00, 0x00, 0x1F, 0x01, 0x1D, 0x80, 0x18, 0x71, 0x1C, 0x16, 0x20, 0x58, 0x2C, 0x25, 0x00,                               
    0x13, 0x2B, 0x21, 0x00, 0x00, 0x9F, 0x01, 0x1D, 0x00, 0x72, 0x51, 0xD0, 0x1E, 0x20, 0x6E, 0x28,                               
    0x55, 0x00, 0x13, 0x2B, 0x21, 0x00, 0x00, 0x1E, 0x8C, 0x0A, 0xD0, 0x8A, 0x20, 0xE0, 0x2D, 0x10,                               
    0x10, 0x3E, 0x96, 0x00, 0x13, 0x2B, 0x21, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                               
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE7,
};

#else

#include "EDID.c"		

#endif


//******************************************************************************
// E X T E R N A L   V A R I A B L E   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// S T A T I C   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
static UCHAR NvramIsEmpty(void);
static void NvramValidCheck(void);
static void NvramClearAll(void);
static void NvramWpOn(void);
static void NvramWpOff(void);

//******************************************************************************
// E X T E R N A L   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// F U N C T I O N   B O D Y S
//******************************************************************************

/**************************************************************************//**
 * Write the data to NVRam.
 * @param addr Address in NVRam.
 * @param len Length of the data array.
 * @param ptr Pointer to the data array.
 ******************************************************************************/
void NvramWrite(USHRT addr, USHRT len, UCHAR *ptr)
{
#if ENABLE_FE2P == ON
    FE2P_NvramWrite(addr, len, ptr);
#else
    #define PAGE_SIZE   16
    UCHAR slave, remainder;
    USHRT local_timer;

    NvramWpOff();
    while (len) {
        remainder = PAGE_SIZE - (addr % PAGE_SIZE);
        if (remainder > len) {
            remainder = len;
        }
        slave =  NVRAM_ADDR | (UCHAR)((addr>>7) & 0x0E);
        NvramWriteIICSeq(slave, addr, remainder, ptr);
        addr += remainder;
        ptr += remainder;
        len -= remainder;
        local_timer = GetTimerTick();
        do {
            if (NvramCheckDevice(NVRAM_ADDR)) {
                break;
            }
        } while ((GetTimerTick()-local_timer) < 20);
    }
    NvramWpOn();
#endif
}

/**************************************************************************//**
 * Read the data from NVRam.
 * @param addr Address in NVRam.
 * @param len Length of the data array.
 * @param[out] ptr Pointer to the data array.
 ******************************************************************************/
void NvramRead(USHRT addr, USHRT len, UCHAR *ptr)
{
#if ENABLE_FE2P == ON
    FE2P_NvramRead(addr, len, ptr);
#else
    UCHAR slave;

    slave = NVRAM_ADDR | (((UCHAR)(addr>>8)) << 1);
    NvramReadIICSeq(slave, addr, len, ptr);
#endif
}




/**************************************************************************//**
 * Check the NVRam is empty or not
 * If NVRam is empty, load default values.
 * If NVRam is no empty, read back the user/system/... data from NVRam.
 ******************************************************************************/
void NvramLoadData(void)
{
    if (NvramIsEmpty() == NVRAM_UPDATE_ALL) 
	{
       	NvramClearAll(); 					//To avoid previous wrong Nvram data
        	NvramInitialize(NVRAM_UPDATE_ALL);
	  #if ENABLE_FE2P == ON
        	EraseTimeScale();
	  #endif
    }
    else if (NvramIsEmpty() == NVRAM_UPDATE_USER) 
	{
        	NvramClearTiming(); 				//To avoid previous wrong Nvram data
        	NvramInitialize(NVRAM_UPDATE_USER);
   	}

    NvramReadUserData(&UserData);
    NvramReadCalibData(&CalibData);
    NvramReadSystemData(&SystemData);
    NvramValidCheck();
    //...
#if ENABLE_FE2P == ON
    DecodeTimeScale();
#endif
}

//CHIU
code char TimeVER[] = __TIME__;
code char DateVER[] = __DATE__;
//USE DATE AND TIME FOR FIRMWARE VERSION CHECK
UCHAR GetFirmwareVer(void)
{
	UCHAR temp,i;
		
	temp = 0;		
	for(i=0 ; i < strlen(TimeVER) ;i++)
	{
		temp += TimeVER[i];	
	}
	
	for(i=0 ; i < strlen(DateVER) ;i++)
	{
		temp += DateVER[i];	
	}
	
	return temp;
}


/**************************************************************************//**
 * Check the NVRam is empty or not.
 * @return TRUE if NVRam is empty else FALSE.
 ******************************************************************************/
static UCHAR NvramIsEmpty(void)
{
    NvramSystemData system_data;
    USHRT nvram_id;

    do {
        NvramReadSystemData(&system_data);
        nvram_id = system_data.usNvramID;
        NvramReadSystemData(&system_data);
    } while (nvram_id != system_data.usNvramID);

    if (nvram_id != SystemDataDefault.usNvramID) {
        return NVRAM_UPDATE_ALL;
    }
    else if (system_data.usNVSysSize != SystemDataDefault.usNVSysSize) {
        return NVRAM_UPDATE_ALL;
    }
    else if (system_data.usNVCalSize != SystemDataDefault.usNVCalSize) {
        return NVRAM_UPDATE_ALL;
    }
    else if (system_data.usNVUsrSize != SystemDataDefault.usNVUsrSize) {
        return NVRAM_UPDATE_USER;
    }
    //CHIU    
    else if (system_data.usFirmwareVer != GetFirmwareVer() ) 
    {
    	return NVRAM_UPDATE_ALL;		
    }
    
    /*
    else if (system_data.usFirmwareVer != SystemDataDefault.usFirmwareVer) {
        //return NVRAM_UPDATE_USER;  
        
        return NVRAM_UPDATE_ALL;	
    }
    */
    
    
    
    
#if ENABLE_EMBEDDED_CHECKSUM == ON
    else if (system_data.usChkSum != GetEmbeddedCheckSum()) {
        return NVRAM_UPDATE_USER;
    }
#endif
    else {
        return NVRAM_UPDATE_FREE;
    }
}

/**************************************************************************//**
 * Check size/address/the number of field are valid or not.
 * If the deployment of NVRam is invalid, hold the system!
 ******************************************************************************/
static void NvramValidCheck(void)
{
#if	PWROn_Debug == ENABLE
	printf("NvramValidCheck\n");	//150526 george
#endif

    if (UserDataDefault.usUsrEnd != NVRAM_FIELD_END_FLAG) {
		printf("WDT_Re-Boot_While(1)\n");	//150526 george
        while(1);	
    }
    if (CalibDataDefault.usCalEnd != NVRAM_FIELD_END_FLAG) {
		printf("WDT_Re-Boot_While(1)\n");	//150526 george
        while(1);
    }
    if (SystemDataDefault.usSysEnd != NVRAM_FIELD_END_FLAG) {
		printf("WDT_Re-Boot_While(1)\n");	//150526 george
        while(1);
    }
    if (sizeof(NvramUserData) > NVRAM_USER_SIZE) {
		printf("WDT_Re-Boot_While(1)\n");	//150526 george
        while(1);
    }
    if (sizeof(NvramCalibData) > NVRAM_CALIB_SIZE) {
		printf("WDT_Re-Boot_While(1)\n");	//150526 george
        while(1);
    }
    if (sizeof(NvramSystemData) > NVRAM_SYSTEM_SIZE) {
		printf("WDT_Re-Boot_While(1)\n");	//150526 george
        while(1);
    }
}

/**************************************************************************//**
 * Load the default to NVRam.
 * @param type Update type.
 ******************************************************************************/
void NvramInitialize(UCHAR type)
{
    NvramUserData user_data;
    NvramCalibData calib_data;
    NvramSystemData system_data;

    user_data = UserDataDefault;
    if (type == NVRAM_UPDATE_ALL) {
        calib_data = CalibDataDefault;
        system_data = SystemDataDefault;
    }
    else {
        NvramReadSystemData(&system_data);
        //system_data.usFirmwareVer = SystemDataDefault.usFirmwareVer;	//CHIU
        system_data.ucTimingWriteIdx = SystemDataDefault.ucTimingWriteIdx;
        system_data.usNVUsrSize = SystemDataDefault.usNVUsrSize;
        system_data.usNVCalSize = SystemDataDefault.usNVCalSize;
        system_data.usNVSysSize = SystemDataDefault.usNVSysSize;
    }

	system_data.usFirmwareVer = GetFirmwareVer();	//CHIU

#if ENABLE_EMBEDDED_CHECKSUM == ON
    system_data.usChkSum = GetEmbeddedCheckSum();
#endif
    
    NvramWriteUserData(&user_data);
    if (type == NVRAM_UPDATE_ALL) {
        NvramWriteCalibData(&calib_data);
    }
    NvramWriteSystemData(&system_data);
}

/**************************************************************************//**
 * Initialize the whole NVRam to 0xFF.
 ******************************************************************************/
static void NvramClearAll(void)
{
    UCHAR init_data[16] = {
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    };
    USHRT i;
    
    for (i=0; i<((NVRAM_END+1)/16); i++) {
        NvramWrite(16*i, 16, init_data);
    }
}

/**************************************************************************//**
 * Initialize the timing area in NVRam to 0xFF.
 ******************************************************************************/
void NvramClearTiming(void)
{
    UCHAR init_data[16] = { 
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    };
    USHRT i;
    
    for (i = 0; i < (NVRAM_TIMING_AREA / 16); i++) {
        NvramWrite(i * 16 + NVRAM_TIMING_ADDR, 16, init_data);
    }
}

/**************************************************************************//**
 * Read back the timing data from Nvram.
 * @param[out] ptr Pointer to the timing data buffer.
 ******************************************************************************/
BOOL NvramReadTimingData(InputTimingFormat *ptr)
{
    BOOL found=FALSE;
    UCHAR i, nvram_timing_size;
    USHRT nvram_start_addr;
    NvramTimingFormat nvram;

    nvram_timing_size = (UCHAR) sizeof(NvramTimingFormat);
    for (i=0; i<(NVRAM_TIMING_AREA/nvram_timing_size); i++) {
        nvram_start_addr = (USHRT) NVRAM_TIMING_ADDR + i*nvram_timing_size;
        NvramRead(nvram_start_addr, nvram_timing_size, (UCHAR *)&nvram);
        if (ptr->usModeIndex == nvram.usModeIndex) { //We found current mode in NVRAM
            found = TRUE;
            break;
        }
    }

    if (found == TRUE) {
        ptr->usHTotal = nvram.usHTotal;
        ptr->usHStart = nvram.usHStart;
        ptr->usVStart = nvram.usVStart;
        ptr->usHTotal50 = nvram.usHTotal50;
        ptr->usHStart50 = nvram.usHStart50;
        ptr->usVStart50 = nvram.usVStart50;
        ptr->ucPhase = nvram.ucPhase;
        ptr->ucAutoTune = nvram.ucAutoTune;
        return TRUE;
    }
    else {
        return FALSE;
    }
}

/**************************************************************************//**
 * Write the timing data to NVRam.
 * @param ptr Pointer to the timing data buffer.
 ******************************************************************************/
void NvramWriteTimingData(InputTimingFormat *ptr)
{
    BOOL found=FALSE;
    UCHAR i, nvram_timing_size;
    USHRT nvram_start_addr;
    NvramTimingFormat nvram;

    nvram_timing_size = (UCHAR) sizeof(NvramTimingFormat);
    for (i=0; i<(NVRAM_TIMING_AREA/nvram_timing_size); i++) {
        nvram_start_addr = (USHRT) NVRAM_TIMING_ADDR + i*nvram_timing_size;
        NvramRead(nvram_start_addr, nvram_timing_size, (UCHAR *)&nvram);
        if (nvram.usModeIndex == ptr->usModeIndex) { //Found the same mode index in Nvram
            found = TRUE;
            break;
        }
    }

    nvram.usHTotal = ptr->usHTotal;
    nvram.usHStart = ptr->usHStart;
    nvram.usVStart = ptr->usVStart;
    nvram.usHTotal50 = ptr->usHTotal50;
    nvram.usHStart50 = ptr->usHStart50;
    nvram.usVStart50 = ptr->usVStart50;
    nvram.ucPhase = ptr->ucPhase;
    nvram.ucAutoTune = ptr->ucAutoTune;
    nvram.usModeIndex = ptr->usModeIndex;
    
    if (found == FALSE) {
        nvram_start_addr = (USHRT) NVRAM_TIMING_ADDR + SystemData.ucTimingWriteIdx*nvram_timing_size;
        //Update system data
        SystemData.ucTimingWriteIdx = (SystemData.ucTimingWriteIdx+1) % (NVRAM_TIMING_AREA/nvram_timing_size);
        NvramWriteSystemData(&SystemData);
    }
    NvramWrite(nvram_start_addr, nvram_timing_size, (UCHAR *)&nvram);
}

/**************************************************************************//**
 * Read back the user data from Nvram.
 * @param[out] ptr Pointer to the user data buffer.
 ******************************************************************************/
void NvramReadUserData(NvramUserData *ptr)
{
    NvramRead(NVRAM_USER_ADDR, sizeof(NvramUserData), (UCHAR *)ptr);
}

/**************************************************************************//**
 * Write the user data to Nvram.
 * @param ptr Pointer to the user data buffer.
 ******************************************************************************/
void NvramWriteUserData(NvramUserData *ptr)
{
    NvramWrite(NVRAM_USER_ADDR, sizeof(NvramUserData), (UCHAR *)ptr);
}

/**************************************************************************//**
 * Read back the calibration data from Nvram.
 * @param[out] ptr Pointer to the calibration data buffer.
 ******************************************************************************/
void NvramReadCalibData(NvramCalibData *ptr)
{
    NvramRead(NVRAM_CALIB_ADDR, sizeof(NvramCalibData), (UCHAR *)ptr);
}

/**************************************************************************//**
 * Write the calibration data to Nvram.
 * @param ptr Pointer to the calibration data buffer.
 ******************************************************************************/
void NvramWriteCalibData(NvramCalibData *ptr)
{
    NvramWrite(NVRAM_CALIB_ADDR, sizeof(NvramCalibData), (UCHAR *)ptr);
}

/**************************************************************************//**
 * Read back the system data from Nvram.
 * @param[out] ptr Pointer to the system data buffer.
 ******************************************************************************/
void NvramReadSystemData(NvramSystemData *ptr)
{
    NvramRead(NVRAM_SYSTEM_ADDR, sizeof(NvramSystemData), (UCHAR *)ptr);
}

/**************************************************************************//**
 * Write the system data to Nvram.
 * @param ptr Pointer to the system data buffer.
 ******************************************************************************/
void NvramWriteSystemData(NvramSystemData *ptr)
{
    NvramWrite(NVRAM_SYSTEM_ADDR, sizeof(NvramSystemData), (UCHAR *)ptr);
}

//******************************************************************************
// Prototype: 
//  void NvramDumpToSram(void)
// Parameters:
//  void
// Return:
//  None
// Purpose:
//  Dump the Nvram data to SRAM
// Notes:
//  None
//******************************************************************************
/*
xdata UCHAR SramArea[2048] _at_ 0xA800;
void NvramDumpToSram(void)
{
    NvramRead(0, sizeof(SramArea), SramArea);
}
*/


#if ENABLE_HDCP == ON
#if ENABLE_NVT_HDCP_WRITER == ON
/**************************************************************************//**
 * Write the HDCP data to Nvram.
 * @param ptr Pointer to HDCP data.
 ******************************************************************************/
void NvramWriteHDCPdata(UCHAR *ptr)
{
    NvramWrite(NVRAM_HDCP_ADDR, NUM_HDCP_TOTAL, ptr);
}
#endif
/**************************************************************************//**
 * Read back the HDCP data from Nvram.
 * @param[out] ptr Pointer to HDCP data buffer.
 ******************************************************************************/
void NvramReadHDCPdata(UCHAR *ptr)
{
    NvramRead(NVRAM_HDCP_ADDR, NUM_HDCP_TOTAL, ptr);
}
#endif

#if USE_INTERNAL_EDID == 1
#if VGA_DDC_CHANNEL != 0xFF
/**************************************************************************//**
 * Write the VGA EDID to Nvram
 * @param ptr Pointer to VGA EDID.
 ******************************************************************************/
void NvramWriteVGAEdid(UCHAR *ptr)
{
    NvramWrite(NVRAM_VGA_EDID_ADDR, NVRAM_VGA_EDID_AREA, ptr);
}

/**************************************************************************//**
 * Read back the VGA EDID from Nvram
 * @param[out] ptr Pointer to VGA EDID.
 ******************************************************************************/
void NvramReadVGAEdid(UCHAR *ptr)
{
#if DefaultEDID == ON
    USHRT i;
    for (i=0; i<128; i++) {
        *ptr = _Default_VGA_EDID[i];
        ptr++;
    }
#else
    NvramRead(NVRAM_VGA_EDID_ADDR, NVRAM_VGA_EDID_AREA, ptr);
#endif
}
#endif

#if DVI_DDC_CHANNEL != 0xFF
/**************************************************************************//**
 * Write the DVI EDID to Nvram
 * @param ptr Pointer to DVI EDID.
 ******************************************************************************/
void NvramWriteDVIEdid(UCHAR *ptr)
{
    NvramWrite(NVRAM_DVI_EDID_ADDR, NVRAM_DVI_EDID_AREA, ptr);
}

/**************************************************************************//**
 * Read back the DVI EDID from Nvram
 * @param[out] ptr Pointer to DVI EDID.
 ******************************************************************************/
void NvramReadDVIEdid(UCHAR *ptr)
{
#if DefaultEDID == ON
    USHRT i, k;
#if DVI_DDC_CHANNEL == 0
    if (MCU_DDC0_EDIDLEN == 0) {
        k = 128;
    }
    else {
        k = 256;
    }
#endif
#if DVI_DDC_CHANNEL == 1
    if (MCU_DDC1_EDIDLEN == 0) {
        k = 128;
    }
    else {
        k = 256;
    }
#endif
#if DVI_DDC_CHANNEL == 2
    if (MCU_DDC2_EDIDLEN == 0) {
        k = 128;
    }
    else {
        k = 256;
    }
#endif
#if DVI_DDC_CHANNEL == 3
    if (MCU_DDC3_EDIDLEN == 0) {
        k = 128;
    }
    else {
        k = 256;
    }
#endif

    if (k == 128) {
        for (i=0; i<128; i++) {
            *ptr = _Default_DVI_EDID[i];
            ptr++;
        }
    }
    else {
        for (i=0; i<256; i++) {
            *ptr = _Default_HDMI_EDID[i];
            ptr++;
        }
    }
#else
    NvramRead(NVRAM_DVI_EDID_ADDR, NVRAM_DVI_EDID_AREA, ptr);
#endif
}
#endif

#if HDMI_DDC_CHANNEL != 0xFF
/**************************************************************************//**
 * Write the HDMI EDID to Nvram
 * @param ptr Pointer to HDMI EDID.
 ******************************************************************************/
void NvramWriteHDMIEdid(UCHAR *ptr)
{
    NvramWrite(NVRAM_HDMI_EDID_ADDR, NVRAM_HDMI_EDID_AREA, ptr);
}

/**************************************************************************//**
 * Read back the HDMI EDID from Nvram
 * @param[out] ptr Pointer to HDMI EDID.
 ******************************************************************************/
void NvramReadHDMIEdid(UCHAR *ptr)
{
#if DefaultEDID == ON
    USHRT i;
    for (i=0; i<256; i++) {
        *ptr = _Default_HDMI_EDID[i];
        ptr++;
    }
#else
    NvramRead(NVRAM_HDMI_EDID_ADDR, NVRAM_HDMI_EDID_AREA, ptr);
#endif
}
#endif

/**************************************************************************//**
 * Save EDID from DDC buffer to NVRam
 ******************************************************************************/
void NvramSaveEDID(void)
{
#if VGA_DDC_CHANNEL == 0
    NvramWriteVGAEdid(EDID_SRAM_BUFF0);
#elif VGA_DDC_CHANNEL == 1
    NvramWriteVGAEdid(EDID_SRAM_BUFF1);
#elif VGA_DDC_CHANNEL == 2
    NvramWriteVGAEdid(EDID_SRAM_BUFF2);
#elif VGA_DDC_CHANNEL == 3
    NvramWriteVGAEdid(EDID_SRAM_BUFF3);
#endif

#if DVI_DDC_CHANNEL == 0
    NvramWriteDVIEdid(EDID_SRAM_BUFF0);
#elif DVI_DDC_CHANNEL == 1
    NvramWriteDVIEdid(EDID_SRAM_BUFF1);
#elif DVI_DDC_CHANNEL == 2
    NvramWriteDVIEdid(EDID_SRAM_BUFF2);
#elif DVI_DDC_CHANNEL == 3
    NvramWriteDVIEdid(EDID_SRAM_BUFF3);
#endif

#if HDMI_DDC_CHANNEL == 0
    NvramWriteHDMIEdid(EDID_SRAM_BUFF0);
#elif HDMI_DDC_CHANNEL == 1
    NvramWriteHDMIEdid(EDID_SRAM_BUFF1);
#elif HDMI_DDC_CHANNEL == 2
    NvramWriteHDMIEdid(EDID_SRAM_BUFF2);
#elif HDMI_DDC_CHANNEL == 3
    NvramWriteHDMIEdid(EDID_SRAM_BUFF3);
#endif
}

/**************************************************************************//**
 * Load EDID from NVRam to DDC buffer.
 ******************************************************************************/
void NvramLoadEDID(void)
{
#if VGA_DDC_CHANNEL == 0
    NvramReadVGAEdid(EDID_SRAM_BUFF0);
#elif VGA_DDC_CHANNEL == 1
    NvramReadVGAEdid(EDID_SRAM_BUFF1);
#elif VGA_DDC_CHANNEL == 2
    NvramReadVGAEdid(EDID_SRAM_BUFF2);
#elif VGA_DDC_CHANNEL == 3
    NvramReadVGAEdid(EDID_SRAM_BUFF3);
#endif

#if DVI_DDC_CHANNEL == 0
    NvramReadDVIEdid(EDID_SRAM_BUFF0);
#elif DVI_DDC_CHANNEL == 1
    NvramReadDVIEdid(EDID_SRAM_BUFF1);
#elif DVI_DDC_CHANNEL == 2
    NvramReadDVIEdid(EDID_SRAM_BUFF2);
#elif DVI_DDC_CHANNEL == 3
    NvramReadDVIEdid(EDID_SRAM_BUFF3);
#endif

#if HDMI_DDC_CHANNEL == 0
    NvramReadHDMIEdid(EDID_SRAM_BUFF0);
#elif HDMI_DDC_CHANNEL == 1
    NvramReadHDMIEdid(EDID_SRAM_BUFF1);
#elif HDMI_DDC_CHANNEL == 2
    NvramReadHDMIEdid(EDID_SRAM_BUFF2);
#elif HDMI_DDC_CHANNEL == 3
    NvramReadHDMIEdid(EDID_SRAM_BUFF3);
#endif
}
#endif
	 
#if ENABLE_FE2P == OFF
/**************************************************************************//**
 * Turn on the NVRAM write protect function.
 ******************************************************************************/
static void NvramWpOn(void)
{
    McuSetIOBit(NVRAM_WP_PORT, NVRAM_WP_BIT, NVRAM_WP_ACTIVE);
}

/**************************************************************************//**
 * Turn off the NVRAM write protect function.
 ******************************************************************************/
static void NvramWpOff(void)
{
    McuSetIOBit(NVRAM_WP_PORT, NVRAM_WP_BIT, ~NVRAM_WP_ACTIVE);
}
#endif
