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
#include "ScalerProfile.h"

#if ENABLE_SCALER_LEDDRV == ON

//******************************************************************************
// M A C R O   D E F I N I T I O N S
//******************************************************************************
#define OVP_MAX_VOLTAGE (PANEL_LED_VOLTAGE_MAX * 1.13 + 1.5) /*!< The target voltage of OVP threshold. */
#define OVP_TYP_VOLTAGE (PANEL_LED_VOLTAGE_TYP * 1.06 + 1.5) /*!< The target voltage of OVP threshold. */
#define OVP_TH_MAX_VOL  24 /*!< The maximum value of OVP threshold. */
#define OVP_TH_MIN_VOL  8  /*!< The minimum value of OVP threshold. */
#define OVP_TH_STEPS    (OVP_TH_MAX_VOL - OVP_TH_MIN_VOL) /*!< Number of steps of OVP threshold. */
#define OVP_SD_VOLTAGE  (PANEL_LED_VOLTAGE_MAX * 1.15 + 1.5) /*!< The target voltage of OVP shutdown. */
#define OVP_SD_MAX_VOL  250 /*!< The maximum value of OVP shutdown. */
#define OVP_SD_MIN_VOL  120 /*!< The maximum value of OVP shutdown. */
#define OVP_SD_STEPS    (OVP_SD_MAX_VOL - OVP_SD_MIN_VOL) /*!< Number of steps of OVP shutdown. */

//******************************************************************************
// G L O B A L   V A R I A B L E S
//******************************************************************************

//******************************************************************************
// S T A T I C   V A R I A B L E S
//******************************************************************************
/*!
 * The LED driver initial table.
 * The values are recommended by APN.
 */
static code UCHAR ucLEDDrvInitTable[37] = LED_DRV_REG_TABLE;
#if ENABLE_SCALER_LEDDRV_ANA_MODE == ON
static xdata USHRT usLEDCurrentlimit = 0;
#endif

//******************************************************************************
// E X T E R N A L   V A R I A B L E   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// S T A T I C   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
static UCHAR GetLEDOVPTH(BOOL type, USHRT r1, USHRT r2);
static UCHAR GetLEDOVPSD(USHRT r1, USHRT r2);
static UCHAR GetLEDCurrent(UCHAR current);

//******************************************************************************
// E X T E R N A L   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// F U N C T I O N   B O D Y S
//******************************************************************************

/**************************************************************************//**
 * Get LED OVP threshold.
 * Recommend detection voltage of OVP_TH = VLED_Max * 1.08 + 1.5V.
 * @param type TRUE to get high threshold, FALSE to get low threshold
 * @param r1 Resistor value of OVP on the PCBA.
 * @param r2 Resistor value of OVP on the PCBA.
 * @return Value of OVP threshold.
 ******************************************************************************/
static UCHAR GetLEDOVPTH(BOOL type, USHRT r1, USHRT r2)
{
    float ovp_th;
    UCHAR tmpreg;

    if (type == HIGH) {
        ovp_th = (float) 10 * OVP_MAX_VOLTAGE * r1 / (r1 + r2); // 0.1 volts
    }
    else {
        ovp_th = (float) 10 * OVP_TYP_VOLTAGE * r1 / (r1 + r2); // 0.1 volts
    }

    if (ovp_th > OVP_TH_MAX_VOL) {
        ovp_th = OVP_TH_MAX_VOL;
    }
    else if (ovp_th < OVP_TH_MIN_VOL) {
        ovp_th = OVP_TH_MIN_VOL;
    }

    tmpreg = (ovp_th - OVP_TH_MIN_VOL) * 127 / OVP_TH_STEPS;

    if (tmpreg > 127) {
        tmpreg = 127;
    }

    return tmpreg;
}

/**************************************************************************//**
 * Get LED OVP shutdown.
 * OVP_SD (V) = 1.2V,1.4V,1.6V,1.8V,1.95V,2.1V,2.3V,2.5V.
 * @param r1 Resistor value of OVP on the PCBA.
 * @param r2 Resistor value of OVP on the PCBA.
 * @return Value of OVP shutdown.
 ******************************************************************************/
static UCHAR GetLEDOVPSD(USHRT r1, USHRT r2)
{
    code UCHAR OVP_SD_Tab[] = {120, 140, 160, 180, 195, 210, 230, 250};
    float ovp_sd;
    UCHAR tmpreg;

    ovp_sd = (float) 100 * OVP_SD_VOLTAGE * r1 / (r1 + r2); // 0.1 volts

    if (ovp_sd > OVP_SD_MAX_VOL) {
        ovp_sd = OVP_SD_MAX_VOL;
    }
    else if (ovp_sd < OVP_SD_MIN_VOL) {
        ovp_sd = OVP_SD_MIN_VOL;
    }

    for (tmpreg = 0; tmpreg < (sizeof(OVP_SD_Tab) / sizeof(OVP_SD_Tab[0])); tmpreg++) {
        if (OVP_SD_Tab[tmpreg] >= ovp_sd) {
            break;
        }
    }

    if (tmpreg >= (sizeof(OVP_SD_Tab) / sizeof(OVP_SD_Tab[0]))) {
        tmpreg = (sizeof(OVP_SD_Tab) / sizeof(OVP_SD_Tab[0])) - 1;
    }

    tmpreg = (SC_LED_PROTECT_CTRL2 & 0x8F)| (tmpreg << 4);

    return tmpreg;
}

/**************************************************************************//**
 * Translate the panel current to LED driver current setting.
 * Per channel current(mA) = (0xE04 x 0.003353V + 0.015V)/5.7ohm.
 * V_ref = 98% x current
 * @param current Current in panel spec. The unit is mA.
 * @return Value of LED current.
 ******************************************************************************/
static UCHAR GetLEDCurrent(UCHAR current)
{
#define RFB   51 // 5.1 ohm
    
    ULONG v_ref;
    UCHAR tmpreg;

    v_ref = (ULONG)98*(RFB+6)*current;

    tmpreg = (UCHAR)(((ULONG)v_ref - 15000)* 255 /855000);

    return tmpreg;

#undef RFB
}

/**************************************************************************//**
 * Initialize LED driver registers.
 ******************************************************************************/
void InitLEDDriver(void)
{
    UCHAR xdata *ptr;
    UCHAR i, mask, str;

    mask = 1;
    str = 0;
    for (i = 0; i++; i < 8) {
        if ((PCBA_LEDSTR_EN & mask) != 0) {
            str++;
        }
        mask *= 2;
    }
    str /= PCBA_LEDSTR_PARALLEL;
    if (str != PANEL_LED_STR_NO) {
        // XXX
        // How to indicate the error of LED string setting.
    }

    ptr = &SC_LEDDRIVER_ENABLE;
    for (i = 0; i < sizeof(ucLEDDrvInitTable); i++) {
        ptr[i] = ucLEDDrvInitTable[i];
    }

    
    ptr[1] = PCBA_LEDSTR_EN;
    ptr[4] = GetLEDCurrent(PANEL_LED_BINCURRENT/PCBA_LEDSTR_PARALLEL);
    ptr[5] = GetLEDOVPTH(HIGH, OVP_RLOWER, OVP_RUPPER);
    ptr[7] = GetLEDOVPSD(OVP_RLOWER, OVP_RUPPER);

#if ENABLE_SCALER_LEDDRV_ANA_MODE == ON
    ptr[6] &= ~BIT7;//0xE06
#if ENABLE_DBC == ON
    SC_VREF_VOLTAGE_MODE3 = 0x0D;//0xE24
#else
    SC_VREF_VOLTAGE_MODE3 = 0x0C;//0xE24
#endif
    SC_TRIMMING_CONTROL = 0x37;//0xE20
    SC_PWMA_CTRL5 = 0x00; //0x44C
    SC_PWMA_CTRL4 = 0xFF; //0x44B
    SC_LD_CTRL &= ~BIT0; //0xE50
    usLEDCurrentlimit = ptr[4];
#endif   
}

/**************************************************************************//**
 * Turn on/off LED driver.
 * @param on TRUE to turn on LED driver else FALSE.
 ******************************************************************************/
void LEDDriverOnOff(UCHAR on)
{
    UCHAR xdata *ptr;
    ptr = &SC_LEDDRIVER_ENABLE;

    if (on == ON) {
        SC_PWMA_CTRL1 = (SC_PWMA_CTRL1 & 0xFC) | 0x81;
        ptr[0x00] = 0x05; // Enable LED bias & dim
        //ptr[0x08] = 0xF4; //discharge comp disable for ver.E
        Sleep(2); //Wait bias stable
        // ptr[0x08] = 0xC4; //discharge comp disable for ver.E

        ptr[0x06] = ucLEDDrvInitTable[6] | 0x50; // Clear open & short
        ptr[0x06] = ucLEDDrvInitTable[6];
        ptr[0x02] = 0xFB;
        ptr[0x15] = 0xFF;// Clr flags
        ptr[0x00] = 0x07;// En LED Dim
        Sleep(10);
        ptr[0x02] = 0xFF;
        if ((SC_LED_OPEN_STATUS == 0x0F) || (SC_LED_SHORT_STATUS == 0x0F)) {
            ptr[0x00] = 0x06; // 0x04
            ptr[0x15] = 0xFF; // clear flag     
            ptr[0x06] = ucLEDDrvInitTable[6] | 0x50; // Clear open & short
            ptr[0x06] = ucLEDDrvInitTable[6];
            ptr[0x00] = 0x07; // enable LED DRV
        }
    }
    else {
        SC_PWMA_CTRL1 = (SC_PWMA_CTRL1 & 0x7C) | 0x01;
        SC_LEDDRIVER_ENABLE = 0x00;
    }
}

/**************************************************************************//**
 * Set the LED driver PWM frequency
 * @param freq PWM frequency (22000Hz ~ 22Hz).
 ******************************************************************************/
void SetLEDDriverFreq(USHRT freq)
{
    UCHAR ch;
    USHRT div;

    SC_PWMA_CTRL1 = (SC_PWMA_CTRL1 & 0xFC) | 0x01;
    if (freq > 22000) {
        freq = 22000;
    }
    div = (USHRT) ((float) REF_CLK * 8 / 4096 / freq - 0.5);
    ch = (div >> 4) & 0x30;
    SC_PWMA_CTRL2 = 0x0C | ch;
    SC_PWMA_CTRL3 = (UCHAR) div;
}

#if ENABLE_SCALER_LEDDRV_ANA_MODE == ON
/**************************************************************************//**
 * Set LED Current.
 * @param value is LED Drive Current setting.
 ******************************************************************************/
void SetLEDDRVCurrent(USHRT value)
{
    UCHAR *ptr;
    USHRT target_value,temp;
           
    ptr = &SC_LEDDRIVER_ENABLE;
    target_value = (ULONG)(usLEDCurrentlimit<<2)*value/1023;
    temp = (USHRT)(ptr[4] << 2)|(ptr[3] & 0x03);
    if(abs(target_value-temp) < 10){
       while(temp != target_value){
           if(target_value > temp){
               temp++;
           }
           else{
               temp--;
           }   
             WaitDisVSync();
             ptr[3] = ((UCHAR)temp & 0x03);
             ptr[4] = (temp >> 2);

       }
    }
    else{
       ptr[3] = ((UCHAR)target_value & 0x03);
       ptr[4] = (target_value >> 2);
    }
}
#endif
#endif //ENABLE_SCALER_LEDDRV == ON

#if ENABLE_SCALER_LEDDRV_IO_MODE
void LEDDRVIOPwrSav(void)
{
   SC_LEDDRIVER_ENABLE = 0x00;
}


UCHAR LEDDRVGetADC(void)
{
   McuPowerUpADC();
   McuStartADC();
   McuWaitADCComplete();
   McuPowerDownADC();

   return McuGetADC(MCU_ADC_7);
}

void LEDDRVSetIOBit(UCHAR port, UCHAR mask, UCHAR value)
{
   UCHAR *ptr;

   port = 0;
    
   ptr = &SC_LEDDRIVER_ENABLE;
   
   if (value == 1) { 
      ptr[1] = ptr[1] | mask;
   }
   else {
      ptr[1] = ptr[1] & (~mask);
   }
}

void InitLEDDriverIOCtrl(void)
{
   UCHAR *ptr,i;
   static code UCHAR ucLEDIOTable[] = {
      0x07,0x0F,0x00,0x00,0x20,0x30,0xA9,0x6A,0xC4,0x37,0x3A,0x0D,0x70,0x00,0x00,0x00,
      0x0F,0x00,0x0D,0x01,0x00,0xA0,0x00,0xCC,0x08,0x80,0x00,0x00,0x2E,0x0F,0xFF,0xE0    
   };    

   ptr = &SC_LEDDRIVER_ENABLE;
   for (i = 0; i < sizeof(ucLEDIOTable); i++) {
       ptr[i] = ucLEDIOTable[i];
   }

   SC_PWMA_CTRL5 = 0x03;//0x44C
   SC_PWMA_CTRL4 = 0xFF;//0x44B
}
#endif

