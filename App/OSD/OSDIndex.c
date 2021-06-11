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
// G L O B A L   D E F I N I T I O N S
//******************************************************************************
#define _0xE8 0x00
#define _0x901F 0x01
#define _0x9078 0x02
#define _0xE0 0x03
#define _0xE1 0x04
#define _0x9AD8 0x05
#define _0xE4 0x06
#define _0xE7 0x07
#define _0xE9 0x08
#define _0x0001 0x09
#define _0x9ED8 0x0A
#define _0xED 0x0B
#define _0xF1 0x0C
#define _0xF3 0x0D
#define _0x7B80 0x0E
#define _0xFA 0x0F
#define _0xFC 0x10
#define _0x91CF 0x11
#define _0x92B3 0x12
#define _0x9510 0x13
#define _0x958B 0x14
#define _0x9593 0x15
#define _0x95F4 0x16
#define _0x96E2 0x17
#define _0x9752 0x18
#define _0x97F3 0x19
#define _0x9810 0x1A
#define _0x986F 0x1B
#define _0x9AD4 0x1C
#define _0x9AD5 0x1D
#define _0x9AD6 0x1E
#define _0x570D 0x1F
#define _0x0002 0x3C
#define _0x0003 0x3E
#define _0x983B 0x5B
#define _0x7387 0x5C
#define _0x9891 0x5D
#define _0x85CD 0x5E
#define _0x663E 0x5F
#define _0x90E8 0x60
#define _0x3044 0x7B
#define _0x3048 0x7C
#define _0x304F 0x7D
#define _0x3055 0x7E
#define _0x305D 0x7F
#define _0x306E 0x80
#define _0x306F 0x81
#define _0x30A3 0x82
#define _0x30A4 0x83
#define _0x30A7 0x84
#define _0x30AB 0x85
#define _0x30B3 0x86
#define _0x30B6 0x87
#define _0x30B9 0x88
#define _0x30BA 0x89
#define _0x30C7 0x8A
#define _0x30C8 0x8B
#define _0x30CB 0x8C
#define _0x30D5 0x8D
#define _0x30D7 0x8E
#define _0x30E1 0x8F
#define _0x30E5 0x90
#define _0x30E6 0x91
#define _0x30E9 0x92
#define _0x30EA 0x93
#define _0x30EB 0x94
#define _0x30EC 0x95
#define _0x30F3 0x96
#define _0x4E00 0x97
#define _0x4E0D 0x98
#define _0x4E2D 0x99
#define _0x4E3B 0x9A
#define _0x4E86 0x9B
#define _0x4EAE 0x9C
#define _0x4ED6 0x9D
#define _0x4F18 0x9E
#define _0x4F4D 0x9F
#define _0x4F53 0xA0
#define _0x4F55 0xA1
#define _0x4F7F 0xA2
#define _0x503C 0xA3
#define _0x50CF 0xA4
#define _0x512A 0xA5
#define _0x5168 0xA6
#define _0x5176 0xA7
#define _0x51E0 0xA8
#define _0x51FA 0xA9
#define _0x5229 0xAA
#define _0x52A8 0xAB
#define _0x52D5 0xAC
#define _0x5316 0xAD
#define _0x5355 0xAE
#define _0x53CA 0xAF
#define _0x53F7 0xB0
#define _0x5426 0xB1
#define _0x5468 0xB2
#define _0x548C 0xB3
#define _0x55AE 0xB4
#define _0x56DE 0xB5
#define _0x56F4 0xB6
#define _0x5782 0xB7
#define _0x5831 0xB8
#define _0x590D 0xB9
#define _0x5B9A 0xBA
#define _0x5BF9 0xBB
#define _0x5C0D 0xBC
#define _0x5E73 0xBD
#define _0x5E7E 0xBE
#define _0x5EA6 0xBF
#define _0x5F00 0xC0
#define _0x5F31 0xC1
#define _0x5F37 0xC2
#define _0x5F69 0xC3
#define _0x5FA9 0xC4
#define _0x6062 0xC5
#define _0x60C5 0xC6
#define _0x62E9 0xC7
#define _0x64C7 0xC8
#define _0x6548 0xC9
#define _0x6570 0xCA
#define _0x6574 0xCB
#define _0x6587 0xCC
#define _0x65E0 0xCD
#define _0x65E5 0xCE
#define _0x65F6 0xCF
#define _0x660E 0xD0
#define _0x662F 0xd1
#define _0x6642 0xD2
#define _0x6781 0xD3
#define _0x67D4 0xD4
#define _0x6975 0xD5
#define _0x6BD4 0xD6
#define _0x6C34 0xD7
#define _0x6CE2 0xD8
#define _0x7121 0xD9
#define _0x7528 0xDA
#define _0x76F4 0xDB
#define _0x76F8 0xDC
#define _0x793A 0xDD
#define _0x79BB 0xDE
#define _0x7BC4 0xDF
#define _0x7D05 0xE0
#define _0x7D20 0xE1
#define _0x7D42 0xE2
#define _0x7DA0 0xE3
#define _0x7E41 0xE4
#define _0x7EA2 0xE5
#define _0x7EFF 0xE6
#define _0x7F6E 0xE7
#define _0x8005 0xE8
#define _0x80FD 0xE9
#define _0x81EA 0xEA
#define _0x8272 0xEB
#define _0x8282 0xEC
#define _0x8303 0xED
#define _0x83DC 0xEE
#define _0x84DD 0xEF
#define _0x865F 0xF0
#define _0x8868 0xF1
#define _0x8A00 0xF2
#define _0x8A0A 0xF3
#define _0x8A2D 0xF4
#define _0x8A9E 0xF5
#define _0x8ABF 0xF6
#define _0x8BA4 0xF7
#define _0x8BAF 0xF8
#define _0x8BBE 0xF9
#define _0x8BED 0xFA
#define _0x8C03 0xFB
#define _0x8D64 0xFC
#define _0x8D85 0xFD
#define _0x8F1D 0xFE
#define _0x9009 0xFF

//******************************************************************************
// G L O B A L   V A R I A B L E S
//******************************************************************************
code UCHAR LuminanceTab1[]={9,"Luminance"};
#if 1														
code UCHAR LuminanceTab2[]={10,"Luminancia"};
code UCHAR LuminanceTab3[]={10,'L','u','m','i','n','o','s','i','t',0x11};
code UCHAR LuminanceTab4[]={11,"Leuchtkraft"};
code UCHAR LuminanceTab5[]={10,'L','u','m','i','n','o','s','i','t',0x13};
code UCHAR LuminanceTab6[]={10,'L','u','m','i','n',0x1f,"ncia"};
code UCHAR LuminanceTab7[]={7,0x7b,'p',0x82,'o','c',0x83,0x84};
code UCHAR LuminanceTab8[]={3, CHINESE_TABLE, 0x27,0x52};
#endif

code UCHAR PictureTab1[]={7,"Picture"};
#if 0
code UCHAR PictureTab2[]={6,"Imagen"};
code UCHAR PictureTab3[]={5,"Image"};
code UCHAR PictureTab4[]={4,"Bild"};
code UCHAR PictureTab5[]={8,"Immagine"};
code UCHAR PictureTab6[]={6,"Imagem"};
code UCHAR PictureTab7[]={6,0x7f,0x8e,'o',0x8f,'p','.'};
code UCHAR PictureTab8[]={3, CHINESE_TABLE, 0x9b, 0x9c};
#endif

code UCHAR ColorTTab1[]={5,"Color"};							
#if 1
code UCHAR ColorTTab2[]={5,"Color"};
code UCHAR ColorTTab3[]={7,"Couleur"};
code UCHAR ColorTTab4[]={5,"Farbe"};
code UCHAR ColorTTab5[]={6,"Colore"};
code UCHAR ColorTTab6[]={3,"Cor"};
code UCHAR ColorTTab7[]={4,0x88,0x89,'e',0x83};
code UCHAR ColorTTab8[]={3, CHINESE_TABLE, 0x75, 0x86};
#endif

code UCHAR OSDSettingTab1[]={12,"OSD Settings"};
#if 1														
code UCHAR OSDSettingTab2[]={11,"Ajustes OSD"};
code UCHAR OSDSettingTab3[]={12,'R',0x11,"glages OSD"};
code UCHAR OSDSettingTab4[]={17,"OSD Einstellungen"};
code UCHAR OSDSettingTab5[]={16,"Impostazioni OSD"};
code UCHAR OSDSettingTab6[]={15,'D','e','f','i','n','i',0x0f,0x0c,"es OSDs"};
code UCHAR OSDSettingTab7[]={14,'H','a','c',0x83,'p','o',0x92,0x82,'a',' ',0x90,'e',0x86,0x91};
code UCHAR OSDSettingTab8[]={6, 'O','S','D',CHINESE_TABLE, 0x8c, 0x4a};
#endif

code UCHAR SetupTab1[]={5,"Setup"};
#if 1														  
code UCHAR SetupTab2[]={10,"Configurar"};
code UCHAR SetupTab3[]={13,"Configuration"};
code UCHAR SetupTab4[]={11,"Einrichtung"};
code UCHAR SetupTab5[]={14,"Configurazione"};
code UCHAR SetupTab6[]={10,"Configurar"};
code UCHAR SetupTab7[]={9,'H','a','c',0x83,'p','o',0x92,0x82,'a'};
code UCHAR SetupTab8[]={3,CHINESE_TABLE, 0x8c, 0x4a};
#endif

code UCHAR FactoryTab1[]={7,"Factory"};
//code UCHAR FactoryTab2[]={5,"Factory"};
//code UCHAR FactoryTab3[]={5,"Factory"};
//code UCHAR FactoryTab4[]={5,"Factory"};
//code UCHAR FactoryTab5[]={5,"Factory"};
//code UCHAR FactoryTab6[]={5,"Factory"};
//code UCHAR FactoryTab7[]={5,"Factory"};
//code UCHAR FactoryTab8[]={5,"Factory"};
code UCHAR DemoTab1[]={4,"Demo"};
code UCHAR *MainMenuStrTab[]={
    LuminanceTab1,LuminanceTab2,LuminanceTab3,LuminanceTab4,LuminanceTab5,LuminanceTab6,LuminanceTab7,LuminanceTab8,
    PictureTab1,PictureTab1,PictureTab1,PictureTab1,PictureTab1,PictureTab1,PictureTab1,PictureTab1,
    ColorTTab1,ColorTTab2,ColorTTab3,ColorTTab4,ColorTTab5,ColorTTab6,ColorTTab7,ColorTTab8,
    OSDSettingTab1,OSDSettingTab2,OSDSettingTab3,OSDSettingTab4,OSDSettingTab5,OSDSettingTab6,OSDSettingTab7,OSDSettingTab8,
    SetupTab1,SetupTab2,SetupTab3,SetupTab4,SetupTab5,SetupTab6,SetupTab7,SetupTab8,
    FactoryTab1,FactoryTab1,FactoryTab1,FactoryTab1,FactoryTab1,FactoryTab1,FactoryTab1,FactoryTab1,
    DemoTab1,DemoTab1,DemoTab1,DemoTab1,DemoTab1,DemoTab1,DemoTab1,DemoTab1,
};

code UCHAR BrightnessStr1[]={10,"Brightness"};
#if 1															
code UCHAR BrightnessStr2[]={6,"Brillo"};
code UCHAR BrightnessStr3[]={10,'L','u','m','i','n','o','s','i','t',0x11};
code UCHAR BrightnessStr4[]={10,"Helligkeit"};
code UCHAR BrightnessStr5[]={10,'L','u','m','i','n','o','s','i','t',0x13};
code UCHAR BrightnessStr6[]={6,"Brilho"};
code UCHAR BrightnessStr7[]={7,0x7b,'p',0x82,'o','c',0x83,0x84};
code UCHAR BrightnessStr8[]={3, CHINESE_TABLE, 0x27,0x52};
#endif
code UCHAR *BrightnessStrTab[]={BrightnessStr1,BrightnessStr2,BrightnessStr3,BrightnessStr4,BrightnessStr5,BrightnessStr6,BrightnessStr7,BrightnessStr8};

code UCHAR ContrastStr1[]={8,"Contrast"};
#if 1															
code UCHAR ContrastStr2[]={9,"Contraste"};
code UCHAR ContrastStr3[]={9,"Contraste"};
code UCHAR ContrastStr4[]={8,"Kontrast"};
code UCHAR ContrastStr5[]={9,"Contrasto"};
code UCHAR ContrastStr6[]={9,"Contraste"};
code UCHAR ContrastStr7[]={8,'K','o',0x86,0x83,'p','a','c',0x83};
code UCHAR ContrastStr8[]={4, CHINESE_TABLE, 0x4b, 0x6e, 0x52};
#endif
code UCHAR *ContrastStrTab[]={ContrastStr1,ContrastStr2,ContrastStr3,ContrastStr4,ContrastStr5,ContrastStr6,ContrastStr7,ContrastStr8};

code UCHAR GammaStr1[]={5,"Gamma"};
#if 0
code UCHAR GammaStr2[]={5,"Gamma"};
code UCHAR GammaStr3[]={5,"Gamma"};
code UCHAR GammaStr4[]={5,"Gamma"};
code UCHAR GammaStr5[]={5,"Gamma"};
code UCHAR GammaStr6[]={5,"Gamma"};
code UCHAR GammaStr7[]={5,"Gamma"};
code UCHAR GammaStr8[]={5,"Gamma"};
#endif
code UCHAR *GammaStrTab[]={GammaStr1,GammaStr1,GammaStr1,GammaStr1,GammaStr1,GammaStr1,GammaStr1,GammaStr1};




#if ALS_EnDis == ALSMODE
	//method(1) ALS Mode Select
	code UCHAR ALSMdStr1[]={13, "Ambient Sense"};	//{17,"Auto dimming mode"};								
	code UCHAR *ALSMdStrTab[]={ALSMdStr1,ALSMdStr1,ALSMdStr1,ALSMdStr1,ALSMdStr1,ALSMdStr1,ALSMdStr1,ALSMdStr1};
	code UCHAR ALS_OFF_Str[]  = {3, "Off"};
	code UCHAR ALS_Indoor_Str[] = {7, "In-Door"};
	code UCHAR ALS_Outdoor_Str[] = {8,"Out-Door"};
	code UCHAR *ALSItemStrTab[]={ALS_OFF_Str,ALS_Indoor_Str,ALS_Outdoor_Str};

#elif ALS_EnDis == ALSOffSET	
	code UCHAR ALSSWStr1[]={12,"Auto dimming"};																		//george: F_ALSOnOff_02
	code UCHAR *ALSOnOffStrTab[]={ALSSWStr1,ALSSWStr1,ALSSWStr1,ALSSWStr1,ALSSWStr1,ALSSWStr1,ALSSWStr1,ALSSWStr1};	//george: F_ALSOnOff_02
	
	//method(2) ALS Base Value Modify.
	code UCHAR ALSBVStr1[]={24,"Auto dimming base offset"};																	//george: F_ALSBV_02
	code UCHAR *ALSBVStrTab[]={ALSBVStr1,ALSBVStr1,ALSBVStr1,ALSBVStr1,ALSBVStr1,ALSBVStr1,ALSBVStr1,ALSBVStr1};	//george: F_ALSBV_02
#elif ALS_EnDis == ALSRange
	//method(3) ALS ADS LS3101
	code UCHAR ALSSWStr1[]={12,"Auto dimming"};																		//george: F_ALSOnOff_02
	code UCHAR *ALSOnOffStrTab[]={ALSSWStr1,ALSSWStr1,ALSSWStr1,ALSSWStr1,ALSSWStr1,ALSSWStr1,ALSSWStr1,ALSSWStr1};	//george: F_ALSOnOff_02
#else	//Normal

#endif	//#if ALS_EnDis == ENABLE


#if TOUCH_EnDis == ENABLE
	code UCHAR TouchSWStr1[]={12,"Touch On/Off"};											 										//george: F_Touch_02
	code UCHAR *TouchSWStrTab[]={TouchSWStr1,TouchSWStr1,TouchSWStr1,TouchSWStr1,TouchSWStr1,TouchSWStr1,TouchSWStr1,TouchSWStr1};	//george: F_Touch_02
#endif //#if TOUCH_EnDis == ENABLE



/// code UCHAR GItem16Str1[]={7,"GItem16"};																							// george_Item16
/// code UCHAR *GItem16StrTab[]={GItem16Str1,GItem16Str1,GItem16Str1,GItem16Str1,GItem16Str1,GItem16Str1,GItem16Str1,GItem16Str1};	// george_Item16

/// code UCHAR GItem17Str1[]={7,"GItem17"};																							// george_Item17
/// code UCHAR *GItem17StrTab[]={GItem17Str1,GItem17Str1,GItem17Str1,GItem17Str1,GItem17Str1,GItem17Str1,GItem17Str1,GItem17Str1};	// george_Item17

code UCHAR SRStr1[]={9,"Sharpness"};								
code UCHAR *SRStrTab[]={SRStr1,SRStr1,SRStr1,SRStr1,SRStr1,SRStr1,SRStr1,SRStr1};


#if ENABLE_SR
code UCHAR SRDemoStr1[]={20,"SuperResolution Demo"};
code UCHAR *SRDemoStrTab[]={SRDemoStr1,SRDemoStr1,SRDemoStr1,SRDemoStr1
                           ,SRDemoStr1,SRDemoStr1,SRDemoStr1,SRDemoStr1};

code UCHAR SR_OFF_Str[] = {3, "Off"};
code UCHAR SR_WEAK_Str[] = {4, "Weak"};
code UCHAR SR_MEDIAN_Str[] = {6, "Median"};
code UCHAR SR_STRONG_Str[] = {6, "Strong"};
code UCHAR SR_STRONGEST_Str[] = {9, "Strongest"};
code UCHAR *SRItemStrTab[]={SR_OFF_Str,SR_WEAK_Str,SR_MEDIAN_Str,SR_STRONG_Str,SR_STRONGEST_Str};
#endif


#if 0
code UCHAR SaturationStr1[]={10,"Saturation"};
code UCHAR SaturationStr2[]={10,'S','a','t','u','r','a','c','i',0x08,'n'};
code UCHAR SaturationStr3[]={10,"Saturation"};
code UCHAR SaturationStr4[]={13,'F','a','r','b','s',0x0e,'t','t','i','g','u','n','g'};
code UCHAR SaturationStr5[]={11,"Saturazione"};
code UCHAR SaturationStr6[]={9,'S','a','t','u','r','a',0x0f,0x1a,'o'};
code UCHAR SaturationStr7[]={12,'H','a','c',0x80,0x99,'e',0x86,0x86,'o','c',0x83,0x84};
code UCHAR SaturationStr8[]={10,"Saturation"};
code UCHAR *SaturationStrTab[]={SaturationStr1,SaturationStr2,SaturationStr3,SaturationStr4,SaturationStr5,SaturationStr6,SaturationStr7,SaturationStr8};

code UCHAR TintStr1[]={4,"Tint"};
code UCHAR TintStr2[]={5,"Tinte"};
code UCHAR TintStr3[]={6,"Teinte"};
code UCHAR TintStr4[]={7,"Farbton"};
code UCHAR TintStr5[]={5,"Tinta"};
code UCHAR TintStr6[]={10,"Tonalidade"};
code UCHAR TintStr7[]={7,'O',0x83,0x83,'e',0x86,'o',0x82};
code UCHAR TintStr8[]={4,"Tint"};
code UCHAR *TintStrTab[]={TintStr1,TintStr2,TintStr3,TintStr4,TintStr5,TintStr6,TintStr7,TintStr8};
#endif

code UCHAR DBC_Str1[]={3,"DBC"};
code UCHAR *DBC_StrTab[]={DBC_Str1,DBC_Str1,DBC_Str1,DBC_Str1,DBC_Str1,DBC_Str1,DBC_Str1,DBC_Str1};

code UCHAR DCR_Str1[]={3,"DCR"};
code UCHAR *DCR_StrTab[]={DCR_Str1,DCR_Str1,DCR_Str1,DCR_Str1,DCR_Str1,DCR_Str1,DCR_Str1,DCR_Str1};


code UCHAR PhaseStr1[]={5,"Phase"};
#if 0
code UCHAR PhaseStr2[]={4,"Fase"};
code UCHAR PhaseStr3[]={5,"Phase"};
code UCHAR PhaseStr4[]={5,"Phase"};
code UCHAR PhaseStr5[]={4,"Fase"};
code UCHAR PhaseStr6[]={4,"Fase"};
code UCHAR PhaseStr7[]={4,0x9a,'a',0x8e,'a'};
code UCHAR PhaseStr8[]={3, CHINESE_TABLE, 0x79, 0x29};
#endif
code UCHAR *PhaseStrTab[]={PhaseStr1,PhaseStr1,PhaseStr1,PhaseStr1,PhaseStr1,PhaseStr1,PhaseStr1,PhaseStr1};

code UCHAR ClockStr1[]={5,"Clock"};
#if 0
code UCHAR ClockStr2[]={5,"Reloj"};
code UCHAR ClockStr3[]={7,"Horloge"};
code UCHAR ClockStr4[]={4,"Takt"};
code UCHAR ClockStr5[]={5,"Clock"};
code UCHAR ClockStr6[]={7,'R','e','l',0x08,'g','i','o'};
code UCHAR ClockStr7[]={7,0x9d,'a','c',0x83,'o',0x83,'a'};
code UCHAR ClockStr8[]={3, CHINESE_TABLE, 0x64, 0x51};
#endif
code UCHAR *ClockStrTab[]={ClockStr1,ClockStr1,ClockStr1,ClockStr1,ClockStr1,ClockStr1,ClockStr1,ClockStr1};

code UCHAR HPosStr1[]={11,"H. Position"};
#if 0
code UCHAR HPosStr2[]={11,'P','o','s','i','c','i',0x08,'n',' ','H','.'};
code UCHAR HPosStr3[]={11,"Position H."};
code UCHAR HPosStr4[]={11,"H. Position"};
code UCHAR HPosStr5[]={15,"Posizione Oriz."};
code UCHAR HPosStr6[]={10,'P','o','s','i',0x0f,0x1a,'o',' ','H','.'};
code UCHAR HPosStr7[]={12,0x7d,'.',' ',0x8a,'o',0x8b,'o',0x8c,'e',0x86,0x85,'e'};
code UCHAR HPosStr8[]={5, CHINESE_TABLE, 0x6f, 0x50, 0x29, 0x82 };
#endif
code UCHAR *HPosStrTab[]={HPosStr1,HPosStr1,HPosStr1,HPosStr1, HPosStr1,HPosStr1,HPosStr1,HPosStr1}; 

code UCHAR VPosStr1[]={11,"V. Position"};
#if 0
code UCHAR VPosStr2[]={11,'P','o','s','i','c','i',0x08,'n',' ','V','.',};
code UCHAR VPosStr3[]={11,"Position V."};
code UCHAR VPosStr4[]={11,"V. Position"};
code UCHAR VPosStr5[]={15,"Posizione Vert."};
code UCHAR VPosStr6[]={10,'P','o','s','i',0x0f,0x1a,'o',' ','V','.'};
code UCHAR VPosStr7[]={11,'B','.',' ',0x8a,'o',0x8b,'o',0x8c,'e',0x86,0x85,'e'};
code UCHAR VPosStr8[]={5, CHINESE_TABLE, 0x44, 0x78, 0x29, 0x82};
#endif
code UCHAR *VPosStrTab[]={VPosStr1,VPosStr1,VPosStr1,VPosStr1,VPosStr1,VPosStr1,VPosStr1,VPosStr1}; 

code UCHAR ColorTempStr1[]={17,"Color Temperature"};
#if 1																
code UCHAR ColorTempStr2[]={17,"Temperatura Color"};
code UCHAR ColorTempStr3[]={22,'t','e','m','p',0x11,'r','a','t','u','r','e',' ','d','e',' ','c','o','u','l','e','u','r'};
code UCHAR ColorTempStr4[]={14,"Farbtemperatur"};
code UCHAR ColorTempStr5[]={18,"Temperatura colore"};
code UCHAR ColorTempStr6[]={18,'T','e','m','p','e','r','a','t','u','r','a',' ','d','e',' ','C',0x1b,'r'};
code UCHAR ColorTempStr7[]={20,0x98,0x89,'e',0x83,'o',0x89,'a',0x96,' ',0x83,'e',0x90,0x8a,'e','p','a',0x83,'y','p','a'};
code UCHAR ColorTempStr8[]={3, CHINESE_TABLE, 0x86, 0x12};
#endif
code UCHAR *ColorTempStrTab[]={ColorTempStr1,ColorTempStr2,ColorTempStr3,ColorTempStr4,ColorTempStr5,ColorTempStr6,ColorTempStr7,ColorTempStr8};

code UCHAR UserDefine1[]={11,"User Define"};
#if 1																		
code UCHAR UserDefine2[]={13,"Personalizado"};
code UCHAR UserDefine3[]={18,'D',0x11,'f','i','n','i',' ','p','a','r',' ','u','t','i','l','i','s','.'};
code UCHAR UserDefine4[]={17,"Benutzerdefiniert"};
code UCHAR UserDefine5[]={14,"Personalizzato"};
code UCHAR UserDefine6[]={13,"Personalizado"};
code UCHAR UserDefine7[]={6,'O','c','o',0x8f,0x80,0x92};
code UCHAR UserDefine8[]={5, CHINESE_TABLE, 0x76, 0x58, 0x4a, 0x26};
#endif
code UCHAR *UserDefineStrTab[]={UserDefine1,UserDefine2,UserDefine3,UserDefine4,UserDefine5,UserDefine6,UserDefine7,UserDefine8};

code UCHAR StrTab11500K[]={6,"11500K"};
code UCHAR StrTab9300K[]={5,"9300K"};
code UCHAR StrTab8200K[]={5,"8200K"};
code UCHAR StrTab7500K[]={5,"7500K"};
code UCHAR StrTab6500K[]={5,"6500K"};
code UCHAR StrTab5000K[]={5,"5000K"};
code UCHAR sRGB_Str1[]={4,"sRGB"};
code UCHAR sRGB_Str2[]={4,"SRGB"};
code UCHAR *sRGB_StrTab[]={sRGB_Str1,sRGB_Str1,sRGB_Str1,sRGB_Str1,sRGB_Str1,sRGB_Str2,sRGB_Str1,sRGB_Str1};

code UCHAR *ColorTemp_StrTab[]={
StrTab6500K,StrTab6500K,StrTab6500K,StrTab6500K,StrTab6500K,StrTab6500K,StrTab6500K,StrTab6500K,
StrTab7500K,StrTab7500K,StrTab7500K,StrTab7500K,StrTab7500K,StrTab7500K,StrTab7500K,StrTab7500K,
StrTab9300K,StrTab9300K,StrTab9300K,StrTab9300K,StrTab9300K,StrTab9300K,StrTab9300K,StrTab9300K,
UserDefine1,UserDefine2,UserDefine3,UserDefine4,UserDefine5,UserDefine6,UserDefine7,UserDefine8,
};


code UCHAR RedStr1[]={3,"Red"};
#if 1																		
code UCHAR RedStr2[]={4,"Rojo"};
code UCHAR RedStr3[]={5,"Rouge"};
code UCHAR RedStr4[]={3,"Rot"};
code UCHAR RedStr5[]={5,"Rosso"};
code UCHAR RedStr6[]={8,"Vermelho"};
code UCHAR RedStr7[]={3,"Kp."};
code UCHAR RedStr8[]={2, CHINESE_TABLE, 0xa5};
#endif
code UCHAR *RedStrTab[]={RedStr1,RedStr2,RedStr3,RedStr4,RedStr5,RedStr6,RedStr7,RedStr8};

code UCHAR GreenStr1[]={5,"Green"};
#if 1																		
code UCHAR GreenStr2[]={5,"Verde"};
code UCHAR GreenStr3[]={4,"Vert"};
code UCHAR GreenStr4[]={4,'G','r',0x17,'n'};
code UCHAR GreenStr5[]={5,"Verde"};
code UCHAR GreenStr6[]={5,"Verde"};
code UCHAR GreenStr7[]={4,0x94,'e',0x8b,'.'};
code UCHAR GreenStr8[]={2, CHINESE_TABLE, 0xa6};
#endif
code UCHAR *GreenStrTab[]={GreenStr1,GreenStr2,GreenStr3,GreenStr4,GreenStr5,GreenStr6,GreenStr7,GreenStr8};

code UCHAR BlueStr1[]={4,"Blue"};
#if 1
code UCHAR BlueStr2[]={4,"Azul"};
code UCHAR BlueStr3[]={4,"Bleu"};
code UCHAR BlueStr4[]={4,"Blau"};
code UCHAR BlueStr5[]={3,"Blu"};
code UCHAR BlueStr6[]={4,"Azul"};
code UCHAR BlueStr7[]={4,'C',0x85,0x86,'.'};
code UCHAR BlueStr8[]={2, CHINESE_TABLE, 0xa7 };
#endif
code UCHAR *BlueStrTab[]={BlueStr1,BlueStr2,BlueStr3,BlueStr4,BlueStr5,BlueStr6,BlueStr7,BlueStr8};

code UCHAR HorizontalStrTab1[]={10,"Horizontal"};
#if 1																
code UCHAR HorizontalStrTab2[]={10,"Horizontal"};
code UCHAR HorizontalStrTab3[]={11,"Horizontale"};
code UCHAR HorizontalStrTab4[]={10,"Horizontal"};
code UCHAR HorizontalStrTab5[]={11,"Orizzontale"};
code UCHAR HorizontalStrTab6[]={10,"Horizontal"};
code UCHAR HorizontalStrTab7[]={14,0x7d,'o','p',0x85,0x8e,'o',0x86,0x83,'a',0x8b,0x84,0x86,'o','e'};
code UCHAR HorizontalStrTab8[]={3, CHINESE_TABLE, 0x6f, 0x50};
#endif
code UCHAR *HorizontalStrTab[]={HorizontalStrTab1,HorizontalStrTab2,HorizontalStrTab3,HorizontalStrTab4,HorizontalStrTab5,HorizontalStrTab6,HorizontalStrTab7,HorizontalStrTab8};

code UCHAR VerticalStrTab1[]={8,"Vertical"};
#if 1																
code UCHAR VerticalStrTab2[]={8,"Vertical"};
code UCHAR VerticalStrTab3[]={9,"Verticale"};
code UCHAR VerticalStrTab4[]={8,"Vertikal"};
code UCHAR VerticalStrTab5[]={9,"Verticale"};
code UCHAR VerticalStrTab6[]={8,"Vertical"};
code UCHAR VerticalStrTab7[]={12,'B','e','p',0x83,0x85,0x82,'a',0x8b,0x84,0x86,'o','e'};
code UCHAR VerticalStrTab8[]={3, CHINESE_TABLE, 0x44, 0x78};
#endif
code UCHAR *VerticalStrTab[]={VerticalStrTab1,VerticalStrTab2,VerticalStrTab3,VerticalStrTab4,VerticalStrTab5,VerticalStrTab6,VerticalStrTab7,VerticalStrTab8};

code UCHAR TransparencyStrTab1[]={12,"Transparency"};
#if 1																
code UCHAR TransparencyStrTab2[]={13,"Transparencia"};
code UCHAR TransparencyStrTab3[]={11,"Transparent"};
code UCHAR TransparencyStrTab4[]={11,"Transparenz"};
code UCHAR TransparencyStrTab5[]={11,"Trasparenza"};
code UCHAR TransparencyStrTab6[]={13,'T','r','a','n','s','p','a','r',0x09,'n','c','i','a'};
code UCHAR TransparencyStrTab7[]={12,0xa1,'p','o',0x8e,'p','a',0x95,0x86,'o','c',0x83,0x84};
code UCHAR TransparencyStrTab8[]={4, CHINESE_TABLE, 0x11, 0x1b, 0x52};
#endif
code UCHAR *TransparencyStrTab[]={TransparencyStrTab1,TransparencyStrTab2,TransparencyStrTab3,TransparencyStrTab4,TransparencyStrTab5,TransparencyStrTab6,TransparencyStrTab7,TransparencyStrTab8};

code UCHAR OSDTimeStrTab1[]={12,"OSD Time Out"};
#if 1																
code UCHAR OSDTimeStrTab2[]={11,"Apagado OSD"};
code UCHAR OSDTimeStrTab3[]={14,"OSD Temps mort"};
code UCHAR OSDTimeStrTab4[]={14,"OSD Zeitablauf"};
code UCHAR OSDTimeStrTab5[]={12,"Time out OSD"};
code UCHAR OSDTimeStrTab6[]={19,"Limite de Tempo OSD"};
code UCHAR OSDTimeStrTab7[]={12,'T','a',0x92,0x90,'a','y',0x83,' ',0x90,'e',0x86,0x91};
code UCHAR OSDTimeStrTab8[]={6,'O','S','D',CHINESE_TABLE, 0x0f, 0x64};
#endif
code UCHAR *OSDTimeStrTab[]={OSDTimeStrTab1,OSDTimeStrTab2,OSDTimeStrTab3,OSDTimeStrTab4,OSDTimeStrTab5,OSDTimeStrTab6,OSDTimeStrTab7,OSDTimeStrTab8};

code UCHAR OSDRotationStrTab1[]={12,"OSD Rotation"};
#if 0
code UCHAR OSDRotationStrTab2[]={12,"OSD Rotation"};
code UCHAR OSDRotationStrTab3[]={12,"OSD Rotation"};
code UCHAR OSDRotationStrTab4[]={12,"OSD Rotation"};
code UCHAR OSDRotationStrTab5[]={12,"OSD Rotation"};
code UCHAR OSDRotationStrTab6[]={12,"OSD Rotation"};
code UCHAR OSDRotationStrTab7[]={12,"OSD Rotation"};
code UCHAR OSDRotationStrTab8[]={12,"OSD Rotation"};
#endif
code UCHAR *OSDRotationStrTab[]={OSDRotationStrTab1,OSDRotationStrTab1,OSDRotationStrTab1,OSDRotationStrTab1,OSDRotationStrTab1,OSDRotationStrTab1,OSDRotationStrTab1,OSDRotationStrTab1};

#if MD_ENABLE_FUNC_OSD == ON
code UCHAR ThrDCtrlStr1[]={14,"3D Control Pad"};
code UCHAR ThrDCtrlStr2[]={14,"3D Control Pad"};
code UCHAR ThrDCtrlStr3[]={14,"3D Control Pad"};
code UCHAR ThrDCtrlStr4[]={14,"3D Control Pad"};
code UCHAR ThrDCtrlStr5[]={14,"3D Control Pad"};
code UCHAR ThrDCtrlStr6[]={14,"3D Control Pad"};
code UCHAR ThrDCtrlStr7[]={14,"3D Control Pad"};
code UCHAR ThrDCtrlStr8[]={14,"3D Control Pad"};
code UCHAR *ThrDCtrlTab[]={ThrDCtrlStr1,ThrDCtrlStr2,ThrDCtrlStr3,ThrDCtrlStr4,ThrDCtrlStr5,ThrDCtrlStr6,ThrDCtrlStr7,ThrDCtrlStr8};

code UCHAR ThrDCnvStr1[]={12,"3D Convertor"};
code UCHAR ThrDCnvStr2[]={12,"3D Convertor"};
code UCHAR ThrDCnvStr3[]={12,"3D Convertor"};
code UCHAR ThrDCnvStr4[]={12,"3D Convertor"};
code UCHAR ThrDCnvStr5[]={12,"3D Convertor"};
code UCHAR ThrDCnvStr6[]={12,"3D Convertor"};
code UCHAR ThrDCnvStr7[]={12,"3D Convertor"};
code UCHAR ThrDCnvStr8[]={12,"3D Convertor"};
code UCHAR *ThrDCnvTab[]={ThrDCnvStr1,ThrDCnvStr2,ThrDCnvStr3,ThrDCnvStr4,ThrDCnvStr5,ThrDCnvStr6,ThrDCnvStr7,ThrDCnvStr8};

code UCHAR ThrDAdpStr1[]={14,"2D-3D Adaptive"};
code UCHAR ThrDAdpStr2[]={14,"2D-3D Adaptive"};
code UCHAR ThrDAdpStr3[]={14,"2D-3D Adaptive"};
code UCHAR ThrDAdpStr4[]={14,"2D-3D Adaptive"};
code UCHAR ThrDAdpStr5[]={14,"2D-3D Adaptive"};
code UCHAR ThrDAdpStr6[]={14,"2D-3D Adaptive"};
code UCHAR ThrDAdpStr7[]={14,"2D-3D Adaptive"};
code UCHAR ThrDAdpStr8[]={14,"2D-3D Adaptive"};
code UCHAR *ThrDAdpTab[]={ThrDAdpStr1,ThrDAdpStr2,ThrDAdpStr3,ThrDAdpStr4,ThrDAdpStr5,ThrDAdpStr6,ThrDAdpStr7,ThrDAdpStr8};

code UCHAR ThrDDphStr1[]={11,"2D-3D Depth"};
code UCHAR ThrDDphStr2[]={11,"2D-3D Depth"};
code UCHAR ThrDDphStr3[]={11,"2D-3D Depth"};
code UCHAR ThrDDphStr4[]={11,"2D-3D Depth"};
code UCHAR ThrDDphStr5[]={11,"2D-3D Depth"};
code UCHAR ThrDDphStr6[]={11,"2D-3D Depth"};
code UCHAR ThrDDphStr7[]={11,"2D-3D Depth"};
code UCHAR ThrDDphStr8[]={11,"2D-3D Depth"};
code UCHAR *ThrDDphTab[]={ThrDDphStr1,ThrDDphStr2,ThrDDphStr3,ThrDDphStr4,ThrDDphStr5,ThrDDphStr6,ThrDDphStr7,ThrDDphStr8};

code UCHAR ThrDVwStr1[]={10,"2D-3D View"};
code UCHAR ThrDVwStr2[]={10,"2D-3D View"};
code UCHAR ThrDVwStr3[]={10,"2D-3D View"};
code UCHAR ThrDVwStr4[]={10,"2D-3D View"};
code UCHAR ThrDVwStr5[]={10,"2D-3D View"};
code UCHAR ThrDVwStr6[]={10,"2D-3D View"};
code UCHAR ThrDVwStr7[]={10,"2D-3D View"};
code UCHAR ThrDVwStr8[]={10,"2D-3D View"};
code UCHAR *ThrDVwTab[]={ThrDVwStr1,ThrDVwStr2,ThrDVwStr3,ThrDVwStr4,ThrDVwStr5,ThrDVwStr6,ThrDVwStr7,ThrDVwStr8};

code UCHAR ThrDLRStr1[]={8,"L/R Swap"};
code UCHAR ThrDLRStr2[]={8,"L/R Swap"};
code UCHAR ThrDLRStr3[]={8,"L/R Swap"};
code UCHAR ThrDLRStr4[]={8,"L/R Swap"};
code UCHAR ThrDLRStr5[]={8,"L/R Swap"};
code UCHAR ThrDLRStr6[]={8,"L/R Swap"};
code UCHAR ThrDLRStr7[]={8,"L/R Swap"};
code UCHAR ThrDLRStr8[]={8,"L/R Swap"};
code UCHAR *ThrDLRTab[]={ThrDLRStr1,ThrDLRStr2,ThrDLRStr3,ThrDLRStr4,ThrDLRStr5,ThrDLRStr6,ThrDLRStr7,ThrDLRStr8};

code UCHAR ThrDTwoDStr1[]={5,"3D-2D"};
code UCHAR ThrDTwoDStr2[]={5,"3D-2D"};
code UCHAR ThrDTwoDStr3[]={5,"3D-2D"};
code UCHAR ThrDTwoDStr4[]={5,"3D-2D"};
code UCHAR ThrDTwoDStr5[]={5,"3D-2D"};
code UCHAR ThrDTwoDStr6[]={5,"3D-2D"};
code UCHAR ThrDTwoDStr7[]={5,"3D-2D"};
code UCHAR ThrDTwoDStr8[]={5,"3D-2D"};
code UCHAR *ThrDTwoDTab[]={ThrDTwoDStr1,ThrDTwoDStr2,ThrDTwoDStr3,ThrDTwoDStr4,ThrDTwoDStr5,ThrDTwoDStr6,ThrDTwoDStr7,ThrDTwoDStr8};

code UCHAR ThrDCnvFmtStr1[]={3,"Off"};
code UCHAR ThrDCnvFmtStr2[]={8,"2D To 3D"};
code UCHAR ThrDCnvFmtStr3[]={12,"Side by Side"};
code UCHAR ThrDCnvFmtStr4[]={10,"Top/Bottom"};
code UCHAR ThrDCnvFmtStr5[]={14,"Frame Sequence"};
code UCHAR *ThrDCnvFmtTab[]={ThrDCnvFmtStr1,ThrDCnvFmtStr2,ThrDCnvFmtStr3,ThrDCnvFmtStr4,ThrDCnvFmtStr5};
#endif

code UCHAR LanguageStrTab1[]={8,"Language"};
code UCHAR LanguageStrTab2[]={6,"Idioma"};
code UCHAR LanguageStrTab3[]={6,"Langue"};
code UCHAR LanguageStrTab4[]={7,"Sprache"};
code UCHAR LanguageStrTab5[]={6,"Lingua"};
code UCHAR LanguageStrTab6[]={6,"Idioma"};
code UCHAR LanguageStrTab7[]={7,'P','y','c','c',0x82,0x85,0x92};
code UCHAR LanguageStrTab8[]={3, CHINESE_TABLE, 0x8d, 0x8b};
code UCHAR *LanguageStrTab[]={LanguageStrTab1,LanguageStrTab2,LanguageStrTab3,LanguageStrTab4,LanguageStrTab5,LanguageStrTab6,LanguageStrTab7,LanguageStrTab8};

code UCHAR InputStrTab1[]={5,"Input"};
code UCHAR InputStrTab2[]={7,"Entrada"};
code UCHAR InputStrTab3[]={6,'E','n','t','r',0x11,'e'};
code UCHAR InputStrTab4[]={7,"Eingang"};
code UCHAR InputStrTab5[]={8,"Ingresso"};
code UCHAR InputStrTab6[]={7,"Entrada"};
code UCHAR InputStrTab7[]={4,'B','x','o',0x81};
code UCHAR InputStrTab8[]={3, CHINESE_TABLE, 0x90, 0x31 };
code UCHAR *InputStrTab[]={InputStrTab1,InputStrTab2,InputStrTab3,InputStrTab4,InputStrTab5,InputStrTab6,InputStrTab7,InputStrTab8};

code UCHAR ResetStrTab1[]={5,"Reset"};
code UCHAR ResetStrTab2[]={8,"Reinicio"};
code UCHAR ResetStrTab3[]={7,'R',0x11,"init."};    
code UCHAR ResetStrTab4[]={12,'Z','u','r',0x17,"cksetzen"};    
code UCHAR ResetStrTab5[]={5,"Reset"};
code UCHAR ResetStrTab6[]={9,"Reiniciar"};    
code UCHAR ResetStrTab7[]={5,'C',0x8f,'p','o','c'};
code UCHAR ResetStrTab8[]={3, CHINESE_TABLE, 0x49, 0x82};
code UCHAR *ResetStrTab[]={ResetStrTab1,ResetStrTab2,ResetStrTab3,ResetStrTab4,ResetStrTab5,ResetStrTab6,ResetStrTab7,ResetStrTab8};

code UCHAR EN_String[]={7,"English"};
code UCHAR ES_String[]={7,'E','s','p','a',0x19,'o','l'};
code UCHAR FR_String[]={8,'F','r','a','n',0x0f,'a','i','s'};
code UCHAR DE_String[]={7,"Deutsch"};
code UCHAR IT_String[]={8,"Italiano"};
code UCHAR PO_String[]={9,'P','o','r','t','u','g','u',0x09,'s'};
code UCHAR PY_String[]={7,'P','y','c','c',0x82,0x85,0x92};    
code UCHAR CH_String[]={5, CHINESE_TABLE,0x17,0x18,0x19,0x2f};   
code UCHAR *CountryStrTab[]={EN_String,ES_String,FR_String,DE_String,IT_String,PO_String,PY_String,CH_String};

code UCHAR VGA_StrTab0[]={5,"D-SUB"};
code UCHAR VGA_StrTab1[]={7,"D-SUB 1"};
code UCHAR DVI_StrTab0[]={3,"DVI"};
code UCHAR DVI_StrTab1[]={5,"DVI 1"};
code UCHAR HDMI_StrTab0[]={4,"HDMI"};
code UCHAR HDMI_StrTab1[]={4,"HDMI"};				
code UCHAR HDMI_StrTab2[]={6,"HDMI 2"};
code UCHAR YPBPR_StrTab0[]={5,"YPbPr"};
code UCHAR YPBPR_StrTab1[]={7,"YPbPr 1"};

code UCHAR DP_StrTab11[]={2,"DP"};

code UCHAR *SourceStrTab[]={
    VGA_StrTab0,    VGA_StrTab0,    VGA_StrTab0,    VGA_StrTab0,    VGA_StrTab0,    VGA_StrTab0,    VGA_StrTab0,    VGA_StrTab0,    
    VGA_StrTab1, VGA_StrTab1, VGA_StrTab1, VGA_StrTab1, VGA_StrTab1, VGA_StrTab1,VGA_StrTab1,VGA_StrTab1,
    DVI_StrTab0,    DVI_StrTab0,    DVI_StrTab0,    DVI_StrTab0,    DVI_StrTab0,    DVI_StrTab0,    DVI_StrTab0,    DVI_StrTab0,    
    DVI_StrTab1, DVI_StrTab1, DVI_StrTab1, DVI_StrTab1, DVI_StrTab1, DVI_StrTab1,DVI_StrTab1,DVI_StrTab1,
    HDMI_StrTab0,   HDMI_StrTab0,   HDMI_StrTab0,   HDMI_StrTab0,   HDMI_StrTab0,   HDMI_StrTab0,   HDMI_StrTab0,   HDMI_StrTab0,   
    HDMI_StrTab1, HDMI_StrTab1, HDMI_StrTab1, HDMI_StrTab1, HDMI_StrTab1, HDMI_StrTab1,HDMI_StrTab1,HDMI_StrTab1,
    HDMI_StrTab2,   HDMI_StrTab2,   HDMI_StrTab2,   HDMI_StrTab2,   HDMI_StrTab2,   HDMI_StrTab2,   HDMI_StrTab2,   HDMI_StrTab2,   
    YPBPR_StrTab0,  YPBPR_StrTab0,  YPBPR_StrTab0,  YPBPR_StrTab0,  YPBPR_StrTab0,  YPBPR_StrTab0,  YPBPR_StrTab0,  YPBPR_StrTab0,  
    YPBPR_StrTab1, YPBPR_StrTab1, YPBPR_StrTab1, YPBPR_StrTab1, YPBPR_StrTab1, YPBPR_StrTab1,YPBPR_StrTab1,YPBPR_StrTab1,
    DP_StrTab11,    DP_StrTab11,    DP_StrTab11,    DP_StrTab11,    DP_StrTab11,    DP_StrTab11,    DP_StrTab11,    DP_StrTab11,    
};


code UCHAR YesStr1[]={3,"Yes"};
code UCHAR YesStr2[]={2,'S',0x12};
code UCHAR YesStr3[]={3,"Oui"};
code UCHAR YesStr4[]={2,"Ja"};
code UCHAR YesStr5[]={2,'S',0x12};
code UCHAR YesStr6[]={3,"Sim"};
code UCHAR YesStr7[]={2,0x87,'a'};
code UCHAR YesStr8[]={2, CHINESE_TABLE, 0x65};
code UCHAR *YesStrTab[]={YesStr1,YesStr2,YesStr3,YesStr4,YesStr5,YesStr6,YesStr7,YesStr8};

code UCHAR NoStr1[]={2,"No"};
code UCHAR NoStr2[]={2,"No"};
code UCHAR NoStr3[]={3,"Non"};
code UCHAR NoStr4[]={4,"Nein"};
code UCHAR NoStr5[]={2,"No"};
code UCHAR NoStr6[]={3,'N',0x1a,'o'};
code UCHAR NoStr7[]={3,'H','e',0x83};
code UCHAR NoStr8[]={2, CHINESE_TABLE, 0x3d};
code UCHAR *NoStrTab[]={NoStr1,NoStr1,NoStr3,NoStr4,NoStr1,NoStr6,NoStr7,NoStr8};

code UCHAR AutoStr11[]={15,"Auto Adjustment"};
code UCHAR AutoStr12[]={17,'A','j','u','s','t','e',' ','a','u','t','o','m',0x13,"tico"};
code UCHAR AutoStr13[]={22,"Ajustement Automatique"};
code UCHAR AutoStr14[]={24,"Automatische Einstellung"};
code UCHAR AutoStr15[]={22,"Regolazione automatica"};
code UCHAR AutoStr16[]={17,'A','j','u','s','t','e',' ','A','u','t','o','m',0x13,"tico"};
code UCHAR AutoStr17[]={13,'A',0x89,0x83,'o',0x86,'a','c',0x83,'p','o',0x92,0x82,'a'};    
code UCHAR AutoStr18[]={5, CHINESE_TABLE, 0x85, 0x36, 0x8f, 0x60};

code UCHAR *AutoStrTab[]={
    AutoStr11,AutoStr12,AutoStr13,AutoStr14,AutoStr15,AutoStr16,AutoStr17,AutoStr18,
};

code UCHAR WaitStr11[]={11,"Please Wait"};
code UCHAR WaitStr12[]={11,"Please Wait"};
code UCHAR WaitStr13[]={11,"Please Wait"};
code UCHAR WaitStr14[]={11,"Please Wait"};
code UCHAR WaitStr15[]={11,"Please Wait"};
code UCHAR WaitStr16[]={11,"Please Wait"};
code UCHAR WaitStr17[]={11,"Please Wait"};
code UCHAR WaitStr18[]={11,"Please Wait"};

code UCHAR *WaitStrTab[]={
    WaitStr11,WaitStr12,WaitStr13,WaitStr14,WaitStr15,WaitStr16,WaitStr17,WaitStr18,
};


code UCHAR SrcAnalogStr1[]={    10,"VGA(D-SUB)"};
code UCHAR *SrcAnalogStrTab[]={    SrcAnalogStr1,SrcAnalogStr1,SrcAnalogStr1,SrcAnalogStr1,SrcAnalogStr1,SrcAnalogStr1,SrcAnalogStr1,SrcAnalogStr1};

code UCHAR SrcDigitalStr1[]={    12,"Digital(DVI)"};
code UCHAR SrcDigitalStr3[]={    14,'N','u','m',0x12,"rique(DVI)"};
code UCHAR SrcDigitalStr5[]={    13,"Digitale(DVI)"};
code UCHAR SrcDigitalStr7[]={    13,0x10,0x0d,0x9d,'p','o',0x0f,'o',0x1a,"(DVI)"};
code UCHAR SrcDigitalStr8[]={    7,0xbb,0xa4,"(DVI)"};
code UCHAR *SrcDigitalStrTab[]={    SrcDigitalStr1,SrcDigitalStr1,SrcDigitalStr3,SrcDigitalStr1,SrcDigitalStr5,SrcDigitalStr1,SrcDigitalStr7,SrcDigitalStr8};

code UCHAR AttentionStr1[]={    9,"ATTENTION"};
code UCHAR AttentionStr2[]={    8,'A','T','E','N','C','I',0x0b,'N'};
code UCHAR AttentionStr4[]={    7,"ACHTUNG"};
code UCHAR AttentionStr5[]={    10,"ATTENZIONE"};
code UCHAR AttentionStr6[]={    7,'A','T','E','N',0x1f,0x04,'O'};
code UCHAR AttentionStr7[]={    8,'B','H',0x7f,'M','A','H',0x7f,'E'};
code UCHAR AttentionStr8[]={    3, CHINESE_TABLE, 0x70, 0x57};
code UCHAR *AttentionStrTab[]={    AttentionStr1,AttentionStr2,AttentionStr1,AttentionStr4,AttentionStr5,AttentionStr6,AttentionStr7,AttentionStr8};

code UCHAR OnStr1[]={ 2, "On"};
code UCHAR OnStr2[]={ 8, "Activado"};
code UCHAR OnStr3[]={ 6, 'A','c','t','i','v',0x12};
code UCHAR OnStr4[]={ 3, "Ein"};
code UCHAR OnStr5[]={ 8, "Attivato"};
code UCHAR OnStr6[]={ 6, "Ligado"};
code UCHAR OnStr7[]={ 4, 'B',0x82,0x8b,'.'};
code UCHAR OnStr8[]={ 2, CHINESE_TABLE, 0x61 };
code UCHAR *OnTab[] = {OnStr1, OnStr2, OnStr3, OnStr4, OnStr5, OnStr6,OnStr7,OnStr8};

code UCHAR OffStr1[]={ 3, "Off"};
code UCHAR OffStr2[]={11, "Desactivado"};
code UCHAR OffStr3[]={10, 'D',0x12,'s','a','c','t','i','v',0x12,'e'};
code UCHAR OffStr4[]={ 3, "Aus"};
code UCHAR OffStr5[]={11, "Disattivato"};
code UCHAR OffStr6[]={ 9, "Desligado"};
code UCHAR OffStr7[]={ 5, 'B',0x80,0x82,0x8b,'.'};
code UCHAR OffStr8[]={ 2, CHINESE_TABLE, 0x5d};
code UCHAR *OffTab[] = {OffStr1, OffStr2, OffStr3, OffStr4, OffStr5, OffStr6,OffStr7,OffStr8};

code UCHAR MuteStr1[]={ 4, "Mute"};
code UCHAR MuteStr2[]={ 8, "Silencio"};
code UCHAR MuteStr3[]={ 8, "Sourdine"};
code UCHAR MuteStr4[]={14, "Stummschaltung"};
code UCHAR MuteStr5[]={10, "Silenzioso"};
code UCHAR MuteStr6[]={ 9, "Silenciar"};
code UCHAR MuteStr7[]={ 9,0x9e,'e',0x8e,' ',0x8e,0x89,'y',0x82,'a'};
code UCHAR MuteStr8[]={ 3, CHINESE_TABLE, 0x55, 0x56};
code UCHAR *MuteTab[] = {MuteStr1, MuteStr2, MuteStr3, MuteStr4, MuteStr5, MuteStr6, MuteStr7, MuteStr8};

code UCHAR OverDriverStr1[]={ 11, "Over Driver"};
#if 0
code UCHAR OverDriverStr2[]={ 11, "Over Driver"};
code UCHAR OverDriverStr3[]={ 11, "Over Driver"};
code UCHAR OverDriverStr4[]={ 11, "Over Driver"};
code UCHAR OverDriverStr5[]={ 11, "Over Driver"};
code UCHAR OverDriverStr6[]={ 11, "Over Driver"};
code UCHAR OverDriverStr7[]={ 11, "Over Driver"};
code UCHAR OverDriverStr8[]={ 11, "Over Driver"};
#endif
code UCHAR *OverDriverTab[] = {OverDriverStr1, OverDriverStr1, OverDriverStr1, OverDriverStr1, OverDriverStr1, OverDriverStr1, OverDriverStr1, OverDriverStr1};

code UCHAR OverScanStr1[]={ 9, "Over Scan"};
code UCHAR *OverScanTab[] = {OverScanStr1, OverScanStr1, OverScanStr1, OverScanStr1, OverScanStr1, OverScanStr1, OverScanStr1, OverScanStr1};


#if ENABLE_ASPECT_RATIO == ON		//george 20160217
	code UCHAR DisplaySizeStr1[]={12, "Display Size"};
	//#if 0
	code UCHAR DisplaySizeStr2[]={12, "Display Size"};
	code UCHAR DisplaySizeStr3[]={12, "Display Size"};
	code UCHAR DisplaySizeStr4[]={12, "Display Size"};
	code UCHAR DisplaySizeStr5[]={12, "Display Size"};
	code UCHAR DisplaySizeStr6[]={12, "Display Size"};
	code UCHAR DisplaySizeStr7[]={12, "Display Size"};
	code UCHAR DisplaySizeStr8[]={12, "Display Size"};
	//#endif
	code UCHAR *DisplaySizeTab[] = {DisplaySizeStr1, DisplaySizeStr1, DisplaySizeStr1, DisplaySizeStr1, DisplaySizeStr1, DisplaySizeStr1, DisplaySizeStr1, DisplaySizeStr1};
	
	
	code UCHAR FullScreenStr1[]={11, "Full Screen"};
	//#if 0
	code UCHAR FullScreenStr2[]={17, "Pantalla Completa"};
	code UCHAR FullScreenStr3[]={11, 'P','l','e','i','n',' ',0x05,'c','r','a','n'};
	code UCHAR FullScreenStr4[]={8, "Vollbild"};
	code UCHAR FullScreenStr5[]={14, "Schermo Intero"};
	code UCHAR FullScreenStr6[]={12, 'E','c','r',0x1a,' ','I','n','t','e','i','r','o'};
	code UCHAR FullScreenStr7[]={12, 0x8d,'o',0x8b,0x86,0x80,0x92,' ',0x8e,0x82,'p','a',0x86};
	code UCHAR FullScreenStr8[]={11, "Full Screen"};
	//#endif
	//code UCHAR *FullScreenTab[] = {FullScreenStr1, FullScreenStr1, FullScreenStr1, FullScreenStr1, FullScreenStr1, FullScreenStr1, FullScreenStr1, FullScreenStr1};
	code UCHAR *FullScreenTab[] = {FullScreenStr1, FullScreenStr2, FullScreenStr3, FullScreenStr4, FullScreenStr5, FullScreenStr6, FullScreenStr7, FullScreenStr8};

#endif



code UCHAR SmartFitStr1[]={9, "Smart Fit"};
#if 0
code UCHAR SmartFitStr2[]={9, "Smart Fit"};
code UCHAR SmartFitStr3[]={9, "Smart Fit"};
code UCHAR SmartFitStr4[]={9, "Smart Fit"};
code UCHAR SmartFitStr5[]={9, "Smart Fit"};
code UCHAR SmartFitStr6[]={9, "Smart Fit"};
code UCHAR SmartFitStr7[]={9, "Smart Fit"};
code UCHAR SmartFitStr8[]={9, "Smart Fit"};
#endif
code UCHAR *SmartFitTab[] = {SmartFitStr1, SmartFitStr1, SmartFitStr1, SmartFitStr1, SmartFitStr1, SmartFitStr1, SmartFitStr1, SmartFitStr1};

code UCHAR Fix43Str1[]={3, "4:3"};
code UCHAR Fix43Str2[]={3, "4:3"};
code UCHAR Fix43Str3[]={3, "4:3"};
code UCHAR Fix43Str4[]={3, "4:3"};
code UCHAR Fix43Str5[]={3, "4:3"};
code UCHAR Fix43Str6[]={3, "4:3"};
code UCHAR Fix43Str7[]={3, "4:3"};
code UCHAR Fix43Str8[]={3, "4:3"};
code UCHAR *Fix43Tab[] = {Fix43Str1, Fix43Str2, Fix43Str3, Fix43Str4, Fix43Str5, Fix43Str6, Fix43Str7, Fix43Str8};

code UCHAR Smart43Str1[]={9, "Smart 4:3"};
#if 0
code UCHAR Smart43Str2[]={9, "Smart 4:3"};
code UCHAR Smart43Str3[]={9, "Smart 4:3"};
code UCHAR Smart43Str4[]={9, "Smart 4:3"};
code UCHAR Smart43Str5[]={9, "Smart 4:3"};
code UCHAR Smart43Str6[]={9, "Smart 4:3"};
code UCHAR Smart43Str7[]={9, "Smart 4:3"};
code UCHAR Smart43Str8[]={9, "Smart 4:3"};
#endif
code UCHAR *Smart43Tab[] = {Smart43Str1, Smart43Str1, Smart43Str1, Smart43Str1, Smart43Str1, Smart43Str1, Smart43Str1, Smart43Str1};
#if 0
code UCHAR MT01[]={    13,"Monitor Setup"};
code UCHAR MT02[]={    21,'C','o','n','f','i','g','u','r','a','c','i',0x08,"n Monitor"};
code UCHAR MT03[]={    22,"Configuration Moniteur"};
code UCHAR MT04[]={    13,"Monitor-Setup"};
code UCHAR MT05[]={    13,"Setup Monitor"};
code UCHAR MT06[]={    23,'C','o','n','f','i','g','u','r','a',0x0f,0x1a,"o Do Monitor"};
code UCHAR MT07[]={    18,'H','a','c',0x83,'p','o',0x92,0x82,'a',' ','M','o',0x86,0x85,0x83,'o','p','a'};
code UCHAR MT08[]={    6, CHINESE_TABLE, 0x66, 0x7c, 0x40, 0x8c, 0x82};
code UCHAR *MonitorSetupTab1[]={MT01,MT02,MT03,MT04,MT05,MT06,MT07,MT08};

code UCHAR ExitTab1[]={4,"Exit"};
code UCHAR ExitTab2[]={6,"Cerrar"};
code UCHAR ExitTab3[]={6,"Fermer"};
code UCHAR ExitTab4[]={7,"Beenden"};
code UCHAR ExitTab5[]={6,"Uscita"};
code UCHAR ExitTab6[]={4,"Sair"};
code UCHAR ExitTab7[]={5,'B',0x80,'x','o',0x81};
code UCHAR ExitTab8[]={3, CHINESE_TABLE, 0x96, 0x32};
code UCHAR *ExitStrTab[]={ExitTab1,ExitTab2,ExitTab3,ExitTab4,ExitTab5,ExitTab6,ExitTab7,ExitTab8};
code UCHAR BackTab1[]={4,"Back"};
code UCHAR BackTab2[]={5,'A','t','r',0x13,'s'};
code UCHAR BackTab3[]={6,"Retour"};
code UCHAR BackTab4[]={6,'Z','u','r',0x17,'c','k'};
code UCHAR BackTab5[]={8,"Indietro"};
code UCHAR BackTab6[]={6,"Voltar"};
code UCHAR BackTab7[]={5,'H','a',0x8e,'a',0x81};
code UCHAR BackTab8[]={3, CHINESE_TABLE, 0x94, 0x41};
code UCHAR *BackStrTab[]={BackTab1,BackTab2,BackTab3,BackTab4,BackTab5,BackTab6,BackTab7,BackTab8};
code UCHAR OKTab1[]={2,"OK"};
//code UCHAR OKTab2[]={2,"OK"};
//code UCHAR OKTab3[]={2,"OK"};
//code UCHAR OKTab4[]={2,"OK"};
//code UCHAR OKTab5[]={2,"OK"};
//code UCHAR OKTab6[]={2,"OK"};
//code UCHAR OKTab7[]={2,"OK"};
code UCHAR OKTab8[]={2,0x02,0x03};    //6,'O','K','(',0x02,0x03,')'};
code UCHAR *OKStrTab[]={OKTab1,OKTab1,OKTab1,OKTab1,OKTab1,OKTab1,OKTab1,OKTab8};
code UCHAR NextTab1[]={4,"Next"};
code UCHAR NextTab2[]={9,"Siguiente"};
code UCHAR NextTab3[]={7,"Suivant"};
code UCHAR NextTab4[]={6,"Weiter"};
code UCHAR NextTab5[]={6,"Avanti"};
code UCHAR NextTab6[]={8,"Seguinte"};
code UCHAR NextTab7[]={5,0x87,'a',0x8b,'e','e'};
code UCHAR NextTab8[]={4, CHINESE_TABLE, 0x05, 0x06, 0x07 };
code UCHAR *NextStrTab[]={NextTab1,NextTab2,NextTab3,NextTab4,NextTab5,NextTab6,NextTab7,NextTab8};



code UCHAR AudioTab1[]={5,"Audio"};
//code UCHAR AudioTab2[]={5,"Audio"};
//code UCHAR AudioTab3[]={5,"Audio"};
//code UCHAR AudioTab4[]={5,"Audio"};
//code UCHAR AudioTab5[]={5,"Audio"};
code UCHAR AudioTab6[]={5,0x01,"udio"};
code UCHAR AudioTab7[]={5,'A',0x97,0x81,0x85,'o'};
code UCHAR AudioTab8[]={3, CHINESE_TABLE, 0x56, 0x74,};



code UCHAR StandAloneStr1[]={ 11, "Stand-alone"};
code UCHAR StandAloneStr2[]={ 10, 'S',0x09,"lo audio"};
code UCHAR StandAloneStr3[]={   8, "Autonome"};
code UCHAR StandAloneStr4[]={ 12, 'E','i','g','e','n','s','t',0x0f,"ndig"};
code UCHAR StandAloneStr5[]={ 8, "Autonomo"};
code UCHAR StandAloneStr6[]={ 8, 'A','u','t',0x09,"nomo"};
code UCHAR StandAloneStr7[]={ 10, 'A',0x89,0x82,'o',0x82,'o',0x90,0x86,0x81,0x92};
code UCHAR StandAloneStr8[]={ 4,0xf4,0xb2,0x14,0x1a};
code UCHAR *StandAloneTab[] = {StandAloneStr1, StandAloneStr2, StandAloneStr3, StandAloneStr4, StandAloneStr5, StandAloneStr6, StandAloneStr7, StandAloneStr8};


code UCHAR T191[]={8,"Original"};
code UCHAR T192[]={8,"Original"};
code UCHAR T193[]={8,"Original"};    //9,"d'origine"};
code UCHAR T194[]={8,"Original"};    //13,"Originalfarbe"};
code UCHAR T195[]={9,"Originale"};
code UCHAR T196[]={8,"Original"};
code UCHAR T197[]={8,0x7f,'c','x','o',0x81,0x86,0x80,'e'};    //13,0x82,'c','x','o',0x84,0x89,0x83,0x95,' ',0x9b,0x8c,'e',0x86};
code UCHAR T198[]={3, CHINESE_TABLE, 0x99, 0x9a};
code UCHAR *OrignalColorStrTab[]={    T191,T192,T193,T192,T195,T192,T197,T198};


code UCHAR WarmTab1[]={4,"Warm"};
code UCHAR WarmTab2[]={8,"Caliente"};
code UCHAR WarmTab3[]={6,"Chaude"};
code UCHAR WarmTab4[]={4,"Warm"};
code UCHAR WarmTab5[]={5,"Caldo"};
code UCHAR WarmTab6[]={6,"Quente"};
code UCHAR WarmTab7[]={6,'T','e',0x8a,0x8b,0x80,0x92};
code UCHAR WarmTab8[]={3, CHINESE_TABLE, 0x01, 0x86};
code UCHAR *WarmStrTab[]={WarmTab1,WarmTab2,WarmTab3,WarmTab4,WarmTab5,WarmTab6,WarmTab7,WarmTab8};
code UCHAR CoolTab1[]={4,"Cool"};
code UCHAR CoolTab2[]={4,'F','r',0x13,'o'};
code UCHAR CoolTab3[]={6,"Froide"};
code UCHAR CoolTab4[]={4,"Kalt"};
code UCHAR CoolTab5[]={6,"Freddo"};
code UCHAR CoolTab6[]={4,"Fria"};
code UCHAR CoolTab7[]={8,'X','o',0x8b,'o',0x81,0x86,0x80,0x92};
code UCHAR CoolTab8[]={3, CHINESE_TABLE, 0x00, 0x86};
code UCHAR *CoolStrTab[]={CoolTab1,CoolTab2,CoolTab3,CoolTab4,CoolTab5,CoolTab6,CoolTab7,CoolTab8};
#endif

code UCHAR AutoSrcTab1[]={4,"AUTO"};

code UCHAR AutoSrcTab7[]={4,'A',0x89,0x83,'o'};
code UCHAR AutoSrcTab8[]={5, CHINESE_TABLE, 0x85, 0x36, 0x8f, 0x60};
code UCHAR *AutoSrcStrTab[] = {AutoSrcTab1, AutoSrcTab1, AutoSrcTab1, AutoSrcTab1, AutoSrcTab1, AutoSrcTab1,AutoSrcTab7,AutoSrcTab8};


code UCHAR VolumeStr1[]={    6,"Volume"};
code UCHAR VolumeStr2[]={    6,"Volume"};						//140318 mike volume
code UCHAR VolumeStr3[]={    6,"Volume"};						//140318 mike volume
code UCHAR VolumeStr4[]={    10,'L','A','U','T','S','T',0x02,"RKE"};
code UCHAR VolumeStr5[]={    6,"Volume"};						//140318 mike volume
code UCHAR VolumeStr6[]={    6,"Volume"};						//140318 mike volume
code UCHAR VolumeStr7[]={    9,0x7d,'P','O','M','K','O','C','T',0x7c};
code UCHAR VolumeStr8[]={    3, CHINESE_TABLE, 0x56, 0x4d};
code UCHAR *VolumeStrTab[]={    VolumeStr1,VolumeStr1,VolumeStr1,VolumeStr4,VolumeStr1,VolumeStr1,VolumeStr7,VolumeStr8};


code UCHAR NullStr[]={    1," "};

code UCHAR OutOfRangeStr11[]={25,"CANNOT DISPLAY THIS VIDEO"};
//code UCHAR OutOfRangeStr12[]={27,"NO SE PUEDE VISUALIZAR ESTE"};
//code UCHAR OutOfRangeStr13[]={16,"NE PEUT AFFICHER"};
//code UCHAR OutOfRangeStr14[]={20,"FALSCHER VIDEOMODUS,"};
//code UCHAR OutOfRangeStr15[]={24,"IMPOSSIBILE VISUALIZZARE"};
//code UCHAR OutOfRangeStr16[]={    25,'N',0x03,'O',' ',0x05,' ','P','O','S','S',0x06,"VEL VISUALIZAR"};
//code UCHAR OutOfRangeStr17[]={    26,'H','E',' ',0xa6,0x81,'A','E','T','C',0x7b,' ','O','T','O',0x9e,'P','A',0x94,0x7f,'T',0x7c,' ',0xa5,'T','O','T',};
//code UCHAR OutOfRangeStr18[]={    12, CHINESE_TABLE, 0x22, 0x83, 0x66, 0x7c, 0x6d, 0x89, 0x74, 0x6c, 0x53, COMMON_TABLE, ','};
code UCHAR OutOfRangeStr21[]={    21,"MODE, CHANGE COMPUTER"};
//code UCHAR OutOfRangeStr22[]={    14,'M','O','D','O',' ','D','E',' ','V',0x06,"DEO."};    //24,'M','O','D','O',' ','G','R',0x02,"FICO. SELECCIONE"};
//code UCHAR OutOfRangeStr23[]={    22,'C','E',' ','M','O','D','E',' ','V','I','D',0x05,'O','.',' ','C','H','O','I','S','I','R'};
//code UCHAR OutOfRangeStr24[]={    21,"BILDSCHIRMANZEIGE AUF"};
//code UCHAR OutOfRangeStr25[]={    22,'Q','U','E','S','T','O',' ','M','O','D','A','L','I','T',0x00," VIDEO,"};
//code UCHAR OutOfRangeStr26[]={    19,'E','S','T','E',' ','M','O','D','O',' ','D','E',' ','V',0x06,'D','E','O',','};
//code UCHAR OutOfRangeStr27[]={    20,'B',0x7f,0x87,'E','O','P','E',0xa0,0x7f,'M','.',' ',0x7f,0x94,'M','E','H',0x7f,'T','E'};
//code UCHAR OutOfRangeStr28[]={    12, CHINESE_TABLE, 0x8e, 0x4c, 0x77, 0x84, 0x66, 0x7c, 0x90, 0x31, 0x8c, 0x82, 0x24};
code UCHAR OutOfRangeStr31[]={    16,"DISPLAY INPUT TO"};
//code UCHAR OutOfRangeStr32[]={    39,"SELECCIONE LA ENTRADA DE LA PANTALLA DE"};
//code UCHAR OutOfRangeStr33[]={    18,'E','N','T','R',0x05,"E D'AFFICHAGE"};
code UCHAR OutOfRangeStr34[]={    14,"1680X1050@60HZ"};
//code UCHAR OutOfRangeStr35[]={    21,"CAMBIARE IMPOSTAZIONE"};
//code UCHAR OutOfRangeStr36[]={    19,'M','O','D','I','F','I','Q','U','E',' ','R','E','S','O','L','U',0x1e,0x03,'O'};
//code UCHAR OutOfRangeStr37[]={    18,'P','A',0x94,'P','E',0xa2,'E','H',' ',0x7f,'E',0x87,0x7f,'C',0x8d,0xaa,'E',0x7b};
//code UCHAR OutOfRangeStr38[]={    16,"DISPLAY INPUT TO"};
//code UCHAR OutOfRangeStr41[]={    14,"1680X1050@60Hz"};
//code UCHAR OutOfRangeStr43[]={    21,"1 680 X 1 050 @ 60 Hz"};
//code UCHAR OutOfRangeStr45[]={    24,"VIDEO SU 1680X1050@ 60HZ"};
//code UCHAR OutOfRangeStr46[]={    24,'E','C','R',0x03," PARA 1680X1050@60HZ"};
//code UCHAR OutOfRangeStr47[]={    16,'H','A','1','6','8','0','X','1','0','5','0','@','6','0',0x7d,0x88};
//code UCHAR OutOfRangeStr44[]={    10,"UMSCHALTEN"};

code UCHAR *OutOfRangeOverStrTab[]={
    OutOfRangeStr11,OutOfRangeStr11,OutOfRangeStr11,OutOfRangeStr11,OutOfRangeStr11,OutOfRangeStr11,OutOfRangeStr11,OutOfRangeStr11,
    OutOfRangeStr21,OutOfRangeStr21,OutOfRangeStr21,OutOfRangeStr21,OutOfRangeStr21,OutOfRangeStr21,OutOfRangeStr21,OutOfRangeStr21,
    OutOfRangeStr31,OutOfRangeStr31,OutOfRangeStr31,OutOfRangeStr31,OutOfRangeStr31,OutOfRangeStr31,OutOfRangeStr31,OutOfRangeStr31,
    OutOfRangeStr34,OutOfRangeStr34,OutOfRangeStr34,OutOfRangeStr34,OutOfRangeStr34,OutOfRangeStr34,OutOfRangeStr34,OutOfRangeStr34,
};


code UCHAR OutOfRange85Str11[]={    23,"THIS IS 85HZ OVERDRIVE,"};
//code UCHAR OutOfRange85Str12[]={    25,'S','O','B','R','E','E','X','P','L','O','R','A','C','I',0x0a,"N A 85 HZ."};
//code UCHAR OutOfRange85Str13[]={    30,"CECI EST LE SURBALAYAGE 85 HZ,"};
//code UCHAR OutOfRange85Str14[]={    23,"DIES IST 85HZ OVERSCAN,"};
//code UCHAR OutOfRange85Str15[]={    19,"OVERDRIVE DA 85 HZ,"};
//code UCHAR OutOfRange85Str16[]={    23,'S','O','B','R','E','X','P','L','O','R','A',0x1e,0x03,"O A 85 HZ,"};
//code UCHAR OutOfRange85Str17[]={    26,0xa0,'a','c',0x86,'o',0x86,'a',' ','8','5',0x80,0x9b,' ',0x89,'e',' ',0x8d,'p',0x88,0x93,'e',0x89,0x88,0x93,'a','.'};
//code UCHAR OutOfRange85Str17[]={    16,0x9d,'A','C','T','O','T','A',' ','8','5',' ',0x7d,0x88,' ','H','E'};
//code UCHAR OutOfRange85Str18[]={    14, CHINESE_TABLE, 0x72, 0x65, COMMON_TABLE,'8','5','H','Z', CHINESE_TABLE, 0x93, 0x92, 0x36, COMMON_TABLE, ','};
code UCHAR OutOfRange85Str21[]={    23,"CHANGE COMPUTER DISPLAY"};
//code UCHAR OutOfRange85Str22[]={    53,"SELECCIONE LA ENTRADA DE LA PANTALLA DEL ORDENADOR EN"};
//code UCHAR OutOfRange85Str23[]={    14, 'C','H','A','N','G','E','R',' ','E','N','T','R',0x05,'E'};
//code UCHAR OutOfRange85Str24[]={    22,"MONITOR-EINGANGSSIGNAL"};
//code UCHAR OutOfRange85Str25[]={    18,"IMPOSTARE INGRESSO"};
//code UCHAR OutOfRange85Str26[]={    24,'M','O','D','I','F','I','C','A','R',' ','R','E','S','O','L','U',0x1e,0x03,'O',' ','P','A','R','A'};
//code UCHAR OutOfRange85Str27[]={    19,0x82,0xa8,0x93,'e',0x89,0x88,0x86,'e',' ','p','a',0xa8,'p','e',0x9c,'e',0x89,0x88,'e',};
//code UCHAR OutOfRange85Str27[]={    19,0x8d,'P',0x7f,'M','E','H',0x7f,'M','A','.',' ',0x7f,0x94,'M','E','H',0x7f,'T','E'};
//code UCHAR OutOfRange85Str28[]={    12, CHINESE_TABLE, 0x8e, 0x4c, 0x77, 0x84, 0x66, 0x7c, 0x90, 0x31, 0x8c, 0x82, 0x24 };
code UCHAR OutOfRange85Str31[]={    23,"INPUT TO 1680X1050@60HZ"};
//code UCHAR OutOfRange85Str32[]={    14,"1680X1050@60HZ"};
//code UCHAR OutOfRange85Str33[]={    15,"D'AFFICHAGE SUR"};
//code UCHAR OutOfRange85Str34[]={    18,'A','U','F',' ','1','6','8','0','X','1','0','5','0','@','6','0','H','Z'};
//code UCHAR OutOfRange85Str35[]={    19,"SCHERMO COMPUTER SU"};
//code UCHAR OutOfRange85Str36[]={    14,'1','6','8','0','X','1','0','5','0','@','6','0','H','Z'};
//code UCHAR OutOfRange85Str37[]={    10,'P','A',0x94,'P','E',0xaa,'E','H',0x7f,'E'};
//code UCHAR OutOfRange85Str47[]={    17,'H','A',' ','1','6','8','0','X','1','0','5','0','@','6','0',0x7d,0x88};

//code UCHAR OutOfRange85Str44[]={    6,0x02,"NDERN"};

code UCHAR *OutOfRange85HzStrTab[]={
    OutOfRange85Str11,OutOfRange85Str11,OutOfRange85Str11,OutOfRange85Str11,OutOfRange85Str11,OutOfRange85Str11,OutOfRange85Str11,OutOfRange85Str11,
    OutOfRange85Str21,OutOfRange85Str21,OutOfRange85Str21,OutOfRange85Str21,OutOfRange85Str21,OutOfRange85Str21,OutOfRange85Str21,OutOfRange85Str21,
    OutOfRange85Str31,OutOfRange85Str31,OutOfRange85Str31,OutOfRange85Str31,OutOfRange85Str31,OutOfRange85Str31,OutOfRange85Str31,OutOfRange85Str31,
    NullStr,NullStr,NullStr,NullStr,NullStr,NullStr,NullStr,NullStr,
};
#if 0
code UCHAR OSDLockStr11[]={    25,"MONITOR CONTROLS UNLOCKED"};
code UCHAR OSDLockStr12[]={    13,"CONTROLES DEL"};
code UCHAR OSDLockStr13[]={    21,"COMMANDES DU MONITEUR"};
code UCHAR OSDLockStr14[]={    20,"MONITOREINSTELLUNGEN"};
code UCHAR OSDLockStr15[]={13,"CONTROLLI DEL"};
code UCHAR OSDLockStr16[]={    20,"Controlos do monitor"};
code UCHAR OSDLockStr17[]={    15, 'K',0x0e,'o',0x12,0x0a,0x0d,' ',0x18,'o',0x0e,0x0d,0x0b,'o','p','a'};//17,'O','P',0x80,'A','H',0xa7,' ',0xa9,0x90,'P','A','B',0xa4,'E','H',0x82,0x7e};    //length!!!
code UCHAR OSDLockStr18[]={    7, CHINESE_TABLE, 0x87, 0x9d, 0x9e, 0x9f, 0x8a, 0x4f};
//code UCHAR OSDLockStr21[]={    1," "};    //8,"UNLOCKED"};
code UCHAR OSDLockStr22[]={    21,"MONITOR DESBLOQUEADOS"};
code UCHAR OSDLockStr23[]={    14,'D',0x06,'V','E','R','R','O','U','I','L','L',0x06,"ES"};
//code UCHAR OSDLockStr23[]={    11,"ACCESSIBLES"};
code UCHAR OSDLockStr24[]={    9,"ENTSPERRT"};
code UCHAR OSDLockStr25[]={    17,"MONITOR SBLOCCATI"};    
code UCHAR OSDLockStr26[]={    13,"desbloqueados"};
code UCHAR OSDLockStr27[]={    14,'p','a',0x16,0x17,0x13,'o',0x0a,0x0d,'p','o',0x11,'a',0x0e,0x08};    //23,'M','O','H',0x82,'T','O','P','A',' ','P','A',0x97,0xa1,0xa4,'O','K',0x82,'P','O','B','A','H',0xa7};    //length!!!
code UCHAR OSDLockStr28[]={    1," "};

//code UCHAR OSDLockStr31[]={    24,"OSD MAIN CONTROLS LOCKED"};        //2006-12-05 -
code UCHAR OSDLockStr31[]={    23,"MONITOR CONTROLS LOCKED"};
//code UCHAR OSDLockStr32[]={    21,"CONTROLES PRINCIPALES"};
//code UCHAR OSDLockStr33[]={    21,"COMMANDES PRINCIPALES"};
//code UCHAR OSDLockStr34[]={    22,"OSD-HAUPTEINSTELLUNGEN"};
//code UCHAR OSDLockStr35[]={    18,"COMANDI PRINCIPALI"};
//code UCHAR OSDLockStr36[]={24,"CONTROLOS PRINCIPAIS OSD"};
//code UCHAR OSDLockStr37[]={    26,'O','C','H','O','B','H',0xa7,'E',' ','O','P',0x80,'A','H',0xa7,' ',0xa9,0x90,'P','A','B',0xa4,'E','H',0x82,0x7e};
code UCHAR OSDLockStr38[]={      7, CHINESE_TABLE, 0x87, 0x9d, 0x9e, 0x9f, 0x4f, 0x4a};
//code UCHAR OSDLockStr41[]={    1," "};
code UCHAR OSDLockStr42[]={    18,"MONITOR BLOQUEADOS"};
code UCHAR OSDLockStr43[]={    12,'V','E','R','R','O','U','I','L','L',0x06,'E','S'};
code UCHAR OSDLockStr44[]={    8,"GESPERRT"};
code UCHAR OSDLockStr45[]={    16,"MONITOR BLOCCATI"};
code UCHAR OSDLockStr46[]={    10,"bloqueados"};
code UCHAR OSDLockStr47[]={    13,0x16,'a',0x17,0x13,'o',0x0a,0x0d,'p','o',0x11,'a',0x0e,0x08}; //22,'M','O','H',0x82,'T','O','P','A',' ',0x97,'A',0xa1,0xa4,'O','K',0x82,'P','O','B','A','H',0xa7};//length!!!


code UCHAR *OSD_LockStrTab[]={
    OSDLockStr11,OSDLockStr12,OSDLockStr13,OSDLockStr14,OSDLockStr15,OSDLockStr16,OSDLockStr17,OSDLockStr18,
    NullStr,OSDLockStr22,OSDLockStr23,OSDLockStr24,OSDLockStr25,OSDLockStr26,OSDLockStr27,NullStr,
    OSDLockStr31,OSDLockStr12,OSDLockStr13,OSDLockStr14,OSDLockStr15,OSDLockStr16,OSDLockStr17,OSDLockStr38,
    NullStr,OSDLockStr42,OSDLockStr43,OSDLockStr44,OSDLockStr45,OSDLockStr46,OSDLockStr47,NullStr,
};
#endif
code UCHAR NoSyncStr11[]={    19,"ENTERING SLEEP MODE"};
//code UCHAR NoSyncStr12[]={    30,'A','C','C','E','D','E','R',' ','A','L',' ','M','O','D','O',' ','D','E',' ','H','I','B','E','R','N','A','C','I',0x0a,'N'};
//code UCHAR NoSyncStr13[]={    23,"COMMUTATION MODE VEILLE"};
//code UCHAR NoSyncStr14[]={    26,"SCHLUMMERBETRIEB AKTIVIERT"};
//code UCHAR NoSyncStr15[]={    22,"INSERIMENTO MODO SLEEP"};
//code UCHAR NoSyncStr16[]={    22,"ACESSO AO TEMPORIZADOR"};
//code UCHAR NoSyncStr17[]={    24,0x90,'e','p','e','x','o',0x84,' ',0x8c,' ','p','e',0x8f,0x88,0x93,' ','o',0x8f,0x88,0x84,'a',0x89,0x88,0x99};
//code UCHAR NoSyncStr17[]={    24,0x8d,'E','P','E','X','O',0x87,' ','B',' ','P','E',0xa0,0x7f,'M',' ','O',0xa0,0x7f,0x87,'A','H',0x7f,0x7b};
//code UCHAR NoSyncStr18[]={    7, CHINESE_TABLE, 0x95, 0x31, 0x7b, 0x7a, 0x6c, 0x53};

code UCHAR *NoSyncStrTab[]={
    NoSyncStr11,NoSyncStr11,NoSyncStr11,NoSyncStr11,NoSyncStr11,NoSyncStr11  ,NoSyncStr11,NoSyncStr11
};

code UCHAR NoVideoStr11[]={    14,"NO VIDEO INPUT"};
//code UCHAR NoVideoStr12[]={    23,'N','O',' ','H','A','Y',' ','E','N','T','R','A','D','A',' ','D','E',' ','V',0x06,"DEO"};
//code UCHAR NoVideoStr13[]={    18,'P','A','S',' ','D','\'','E','N','T','R',0x05,'E',' ','V','I','D',0x80,'O'};
//code UCHAR NoVideoStr14[]={    24,"KEIN VIDEOEINGANGSSIGNAL"};
//code UCHAR NoVideoStr15[]={    21,"NESSUN INGRESSO VIDEO"};
//code UCHAR NoVideoStr16[]={    24,'N','E','N','H','U','M','A',' ','E','N','T','R','A','D','A',' ','D','E',' ','V',0x06,"DEO"};
//code UCHAR NoVideoStr17[]={    16,'H','e',0x86,' ',0x8c,0x88,0x84,'e','o','c',0x88,0x9e,0x89,'a',0x8e,'a'};
//code UCHAR NoVideoStr17[]={    16,'H','E','T',' ','B',0x7f,0x87,'E','O','C',0x7f,0x7f,'H','A',0xa1,'A'};
//code UCHAR NoVideoStr18[]={    6, CHINESE_TABLE, 0x63, 0x89, 0x74, 0x90, 0x31};

code UCHAR *NoVideoStrTab[]={
    NoVideoStr11,NoVideoStr11,NoVideoStr11,NoVideoStr11,NoVideoStr11,NoVideoStr11,NoVideoStr11,NoVideoStr11,
};


code UCHAR DisconStr11[]={    22,"CHECK CABLE CONNECTION"};
//code UCHAR DisconStr12[]={    21,'C','O','M','P','R','U','E','B','E',' ','L','A',' ','C','O','N','E','X','I',0x0a,'N'};
//code UCHAR DisconStr13[]={    18,'V',0x05,'R','I','F','I','E','R',' ','C','O','N','N','E','X','I','O','N'};
//code UCHAR DisconStr14[]={    15,'K','A','B','E','L','V','E','R','B','I','N','D','U','N','G'};
//code UCHAR DisconStr15[]={    26,"VERIFICARE IL COLLEGAMENTO"};
//code UCHAR DisconStr16[]={    27,'V','E','R','I','F','I','C','A','R',' ','A',' ','C','O','N','E','X',0x04,'O',' ','D','O',' ','C','A','B','O'};
//code UCHAR DisconStr17[]={    21,0x8d,'P','O','B','E','P',0x7c,'T','E',' ',0x8d,'O',0x87,'K',0xa1,0xa3,0x9d,'E','H',0x7f,'E'};
//code UCHAR DisconStr18[]={    7, CHINESE_TABLE, 0x6b, 0x6a, 0x77, 0x81, 0x5c, 0x3a};
//code UCHAR DisconStr21[]={    1," "};
//code UCHAR DisconStr22[]={    9,"DEL CABLE"};
//code UCHAR DisconStr23[]={    5,'C',0x18,"BLE"};
//code UCHAR DisconStr24[]={    10,0x0b,'B','E','R','P','R',0x0b,"FEN"};
//code UCHAR DisconStr25[]={    8,"DEL CAVO"};
//code UCHAR DisconStr37[]={    6,'K','A',0x91,'E',0xa1,0x7b};

code UCHAR *DisconnectedStrTab[]={
    DisconStr11,DisconStr11,DisconStr11,DisconStr11,DisconStr11,DisconStr11,DisconStr11,DisconStr11,
    NullStr,NullStr,NullStr,NullStr,NullStr,NullStr,NullStr,NullStr,
};

code UCHAR BurnInStr[]={12,"BURN IN MODE"};
code UCHAR *BurnInStrTab[]={
    BurnInStr,BurnInStr,BurnInStr,BurnInStr,BurnInStr,BurnInStr,BurnInStr,BurnInStr,
};

#if 0
code UCHAR DDCCiOn1[]={    9,"DDC/CI ON"};
code UCHAR DDCCiOn2[]={    16,"DDC/CI ENCENDIDO"};
code UCHAR DDCCiOn3[]={    13,'D','D','C','/','C','I',' ','A','L','L','U','M',0x06};
code UCHAR DDCCiOn4[]={    10,"DDC/CI EIN"};
//code UCHAR DDCCiOn5[]={    9,"DDC/CI ON"};
code UCHAR DDCCiOn6[]={    13,"DDC/CI LIGADO"};
code UCHAR DDCCiOn7[]={    10,'D','D','C','/','C','I',' ','B','K',0xa4};
code UCHAR DDCCiOn8[]={    9,'D','D','C','/','C','I',' ',0xbd,0x09,};
code UCHAR *DDCCiOnTab1[]={DDCCiOn1,DDCCiOn2,DDCCiOn3,DDCCiOn4,DDCCiOn1,DDCCiOn6,DDCCiOn7,DDCCiOn8};
code UCHAR DDCCiOff1[]={    10,"DDC/CI OFF"};
code UCHAR DDCCiOff2[]={    14,"DDC/CI APAGADO"};
code UCHAR DDCCiOff3[]={    13,'D','D','C','/','C','I',' ',0x06,"TEINT"};
code UCHAR DDCCiOff4[]={    10,"DDC/CI AUS"};
//code UCHAR DDCCiOff5[]={    10,"DDC/CI OFF"};
code UCHAR DDCCiOff6[]={    16,"DDC/CI DESLIGADO"};
code UCHAR DDCCiOff7[]={    11,'D','D','C','/','C','I',' ','B',0xa7,'K',0xa4};
code UCHAR DDCCiOff8[]={    10,'D','D','C','/','C','I',' ',CHINESE_TABLE, 0x61, 0x09}; 
code UCHAR *DDCCiOffTab1[]={DDCCiOff1,DDCCiOff2,DDCCiOff3,DDCCiOff4,DDCCiOff1,DDCCiOff6,DDCCiOff7,DDCCiOff8};

code UCHAR BestResoultionStr11[]={    18,"USE 1680X1050@60HZ"};
code UCHAR BestResoultionStr12[]={    12,"OPTIMICE CON"};
code UCHAR BestResoultionStr13[]={    21,"1680 X 1050@60HZ POUR"};
code UCHAR BestResoultionStr14[]={    15,"BESTES ERGEBNIS"};
//code UCHAR BestResoultionStr15[]={    14,"1680X1050@60Hz"};
code UCHAR BestResoultionStr16[]={    22,"UTILIZE 1680X1050@60HZ"};
code UCHAR BestResoultionStr17[]={    17,'O',0x15,'T',0x07,'M','A',0xa4,0x04,'H',0xa7,0x06,' ','P','E',0xa3,0x07,'M'};
code UCHAR BestResoultionStr18[]={    17,0x0c,0xd2,' ','1','6','8','0','X','1','0','5','0','@','6','0','H','Z'};

code UCHAR BestResoultionStr21[]={    15,"FOR BEST RESULT"};
code UCHAR BestResoultionStr22[]={    14,"1680X1050@60HZ"};
code UCHAR BestResoultionStr23[]={    13,'D','E','S',' ','R',0x06,"SULTATS"};// OPTIMAUX"};
code UCHAR BestResoultionStr25[]={    11,"CONSIGLIATO"};
code UCHAR BestResoultionStr26[]={    14,"PARA UM MELHOR"};// "};
code UCHAR BestResoultionStr28[]={    7,0x09,0xed,0x16,0xc3,0x0b,0xba,0xc5};
code UCHAR BestResoultionStr33[]={    8,"OPTIMAUX"};
code UCHAR BestResoultionStr36[]={    9,"RESULTADO"};

code UCHAR *BestResultStrTab[]={
    BestResoultionStr11,BestResoultionStr12,BestResoultionStr13,BestResoultionStr14,BestResoultionStr22,BestResoultionStr16,BestResoultionStr17,BestResoultionStr18,
    BestResoultionStr21,BestResoultionStr22,BestResoultionStr23,BestResoultionStr22,BestResoultionStr25,BestResoultionStr26,BestResoultionStr22,BestResoultionStr28,
    NullStr,NullStr,BestResoultionStr33,NullStr,NullStr,BestResoultionStr36,NullStr,NullStr,
};

code UCHAR sRGBWarningStr1[]={    22,"sRGB Value Will Change"};
//code UCHAR sRGBWarningStr2[]={    20,'s','R','G','B',' ','v','a','l','o','r','e',' ','c','a','m','b','i','e','r',0x14,};
code UCHAR sRGBWarningStr2[]={    22,'E','l',' ','v','a','l','o','r',' ','s','R','G','B',' ','c','a','m','b','i','a','r',0x14,};
code UCHAR sRGBWarningStr3[]={    24,"La valeur sRGB deviendra"};
code UCHAR sRGBWarningStr4[]={    19,'s','R','G','B',' ','W','e','r','t',' ','W','i','r','d',' ','A','u','f','.'};
code UCHAR sRGBWarningStr5[]={    20,"Modifica valore sRGB"};
code UCHAR sRGBWarningStr6[]={    20,'V','a','l','o','r',' ','S','R','G','B',' ','i','r',0x14," mudar"};
code UCHAR sRGBWarningStr7[]={    13,0x1c,0x0e,'a',0x1d,'e',0x0e,0x0d,'e',' ','s','R','G','B',};
code UCHAR sRGBWarningStr8[]={    13,'s','R','G','B',' ',CHINESE_TABLE, 0x86, 0x12, 0xa1, 0x4c, 0xa2, 0x97, 0x1a};
code UCHAR sRGBWarningStr1a[]={    8,"to 6500K"};
code UCHAR sRGBWarningStr2a[]={    6,"6500 K"};
code UCHAR sRGBWarningStr3a[]={7,"6 500 K"};
code UCHAR sRGBWarningStr4a[]={    14,'G','e',0x0f,"ndert 6500K"};
code UCHAR sRGBWarningStr5a[]={    7,"a 6500K"};
code UCHAR sRGBWarningStr6a[]={    10,"para 6500K"};
code UCHAR sRGBWarningStr7a[]={    19,0x0d,0x16,0x18,'e',0x0e,0x0d,0x0b,'c',0x1e,' ',0x09,'o',' ','6','5','0','0',' ','K'};

code UCHAR *sRGBWarningStrTab[]={
    sRGBWarningStr1,sRGBWarningStr2,sRGBWarningStr3,sRGBWarningStr4,sRGBWarningStr5,sRGBWarningStr6,sRGBWarningStr7,sRGBWarningStr8,
    sRGBWarningStr1a,sRGBWarningStr2a,sRGBWarningStr3a,sRGBWarningStr4a,sRGBWarningStr5a,sRGBWarningStr6a,sRGBWarningStr7a,sRGBWarningStr2a,
};
#endif

#if ENABLE_LD == ON   
code UCHAR LF_MITM_Str01[] = { 6, "LD OFF"};
code UCHAR LF_MITM_Str02[] = { 5, "LD ON"};
code UCHAR LF_MITM_Str03[] = { 7, "LD DEMO"};
code UCHAR *LTMItemStrTab[]={
    LF_MITM_Str01,LF_MITM_Str02,LF_MITM_Str03
};

code UCHAR BFStr0[] = {13,"Local Dimming"};
code UCHAR *BFStrTab[] = {
    BFStr0,BFStr0,BFStr0,BFStr0,BFStr0,BFStr0,BFStr0,BFStr0
};

#else
// Strings for LF Main Menu
code UCHAR LF_MITM_Str01[] = { 8, "76\% NTSC"};
code UCHAR LF_MITM_Str11[] = { 8, "76\% NTSC"};
code UCHAR LF_MITM_Str21[] = { 8, "76\% NTSC"};
code UCHAR LF_MITM_Str31[] = { 8, "76\% NTSC"};
code UCHAR LF_MITM_Str41[] = { 8, "76\% NTSC"};
code UCHAR LF_MITM_Str51[] = { 8, "76\% NTSC"};
code UCHAR LF_MITM_Str61[] = { 8, "76\% NTSC"};
code UCHAR LF_MITM_Str71[] = { 8, "76\% NTSC"};

code UCHAR LF_MITM_Str03[] = { 8, "80\% NTSC"};
code UCHAR LF_MITM_Str13[] = { 8, "80\% NTSC"};
code UCHAR LF_MITM_Str23[] = { 8, "80\% NTSC"};
code UCHAR LF_MITM_Str33[] = { 8, "80\% NTSC"};
code UCHAR LF_MITM_Str43[] = { 8, "80\% NTSC"};
code UCHAR LF_MITM_Str53[] = { 8, "80\% NTSC"};
code UCHAR LF_MITM_Str63[] = { 8, "80\% NTSC"};
code UCHAR LF_MITM_Str73[] = { 8, "80\% NTSC"};

code UCHAR LF_MITM_Str04[] = {11, "NovaColor 1"};
code UCHAR LF_MITM_Str14[] = {11, "NovaColor 1"};
code UCHAR LF_MITM_Str24[] = {11, "NovaColor 1"};
code UCHAR LF_MITM_Str34[] = {11, "NovaColor 1"};
code UCHAR LF_MITM_Str44[] = {11, "NovaColor 1"};
code UCHAR LF_MITM_Str54[] = {11, "NovaColor 1"};
code UCHAR LF_MITM_Str64[] = {11, "NovaColor 1"};
code UCHAR LF_MITM_Str74[] = {11, "NovaColor 1"};

code UCHAR LF_MITM_Str05[] = {11, "NovaColor 2"};
code UCHAR LF_MITM_Str15[] = {11, "NovaColor 2"};
code UCHAR LF_MITM_Str25[] = {11, "NovaColor 2"};
code UCHAR LF_MITM_Str35[] = {11, "NovaColor 2"};
code UCHAR LF_MITM_Str45[] = {11, "NovaColor 2"};
code UCHAR LF_MITM_Str55[] = {11, "NovaColor 2"};
code UCHAR LF_MITM_Str65[] = {11, "NovaColor 2"};
code UCHAR LF_MITM_Str75[] = {11, "NovaColor 2"};

code UCHAR LF_MITM_Str06[] = { 8, "Standard"};
code UCHAR LF_MITM_Str16[] = { 9, 'E','s','t',0x13,"ndard"};
code UCHAR LF_MITM_Str26[] = { 8, "Standard"};
code UCHAR LF_MITM_Str36[] = { 8, "Standard"};
code UCHAR LF_MITM_Str46[] = { 8, "Standard"};
code UCHAR LF_MITM_Str56[] = { 8, 'P','a','d','r',0x1a,'o'};
code UCHAR LF_MITM_Str66[] = { 8, 'C',0x83,'a',0x86,0x81,'a','p',0x83};
code UCHAR LF_MITM_Str76[] = { 3, CHINESE_TABLE, 0xac, 0xad};

code UCHAR *LTMItemStrTab[]={
    LF_MITM_Str01,LF_MITM_Str03,LF_MITM_Str04,LF_MITM_Str05,LF_MITM_Str06,
    LF_MITM_Str11,LF_MITM_Str13,LF_MITM_Str14,LF_MITM_Str15,LF_MITM_Str16,
    LF_MITM_Str21,LF_MITM_Str23,LF_MITM_Str24,LF_MITM_Str25,LF_MITM_Str26,
    LF_MITM_Str31,LF_MITM_Str33,LF_MITM_Str34,LF_MITM_Str35,LF_MITM_Str36,
    LF_MITM_Str41,LF_MITM_Str43,LF_MITM_Str44,LF_MITM_Str45,LF_MITM_Str46,
    LF_MITM_Str51,LF_MITM_Str53,LF_MITM_Str54,LF_MITM_Str55,LF_MITM_Str56,
    LF_MITM_Str61,LF_MITM_Str63,LF_MITM_Str64,LF_MITM_Str65,LF_MITM_Str66,
    LF_MITM_Str71,LF_MITM_Str73,LF_MITM_Str74,LF_MITM_Str75,LF_MITM_Str76,
};

code UCHAR BFStr0[] = {12,"Bright Frame"};
code UCHAR *BFStrTab[] = {
    BFStr0,BFStr0,BFStr0,BFStr0,BFStr0,BFStr0,BFStr0,BFStr0
};

code UCHAR *LF_DEMO_StrTab[] =
{
    LF_MITM_Str01,LF_MITM_Str03,LF_MITM_Str04,LF_MITM_Str05,LF_MITM_Str06
};

#endif


