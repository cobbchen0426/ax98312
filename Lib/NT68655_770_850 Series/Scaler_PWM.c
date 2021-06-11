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

//******************************************************************************
// M A C R O   D E F I N I T I O N S
//******************************************************************************

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

//******************************************************************************
// F U N C T I O N   B O D Y S
//******************************************************************************

#if ENABLE_PWM_SMOOTH == ON
/**************************************************************************//**
 * Configure the smooth of the PWM duty.
 * @param port PWM output port.
 * @param step PWM value change step. (00=1 step, 01=2 steps, 10=4 steps, 11=8 steps)
 * @param repeat Repeat times of each step. (00=disable, 01=1 time, 10=2 times, 11=4 times)
 ******************************************************************************/
void SmoothScalerPWM(UCHAR port, UCHAR step, UCHAR repeat)
{
    UCHAR ch;

    if (step > 3) {
        step = 3;
    }
    if (repeat > 3) {
        repeat = 3;
    }
    if (port == PWM_A) {
        SC_PWMA_CTRL6 &= 0xF0;
        ch = (step << 2 | repeat);
        SC_PWMA_CTRL6 |= ch;
    }
    else if (port == PWM_B) {
        SC_PWMB_CTRL6 &= 0xF0;
        ch = (step << 2 | repeat);
        SC_PWMB_CTRL6 |= ch;
    }
    else if (port == PWM_C) {
        SC_PWMC_CTRL6 &= 0xF0;
        ch = (step << 2 | repeat);
        SC_PWMC_CTRL6 |= ch;
    }
    else if (port == PWM_D) {
        SC_PWMD_CTRL6 &= 0xF0;
        ch = (step << 2 | repeat);
        SC_PWMD_CTRL6 |= ch;
    }
}
#endif

/**************************************************************************//**
 * Configure the PWM output frequency.
 * @param port PWM output port. (e.x. PWMA, PWMB etc...)
 * @param pin PWM output pin.
 * @param freq Output frequency of PWM.
 ******************************************************************************/
void ConfigScalerPWM(UCHAR port, UCHAR pin, ULONG freq)
{
    ULONG total_div;
    UCHAR div_hi, div_lo, pwm_ctrl;
    USHRT base_div;
    UCHAR reg = 0x00;
    //=============
    //check freq
    //=============
    total_div = (float)REF_CLK / freq - 0.5;
    if (total_div >= 1024) 
	{
         pwm_ctrl = 10;
         base_div = 1024;
	}
    else if (total_div >= 256) 
	{
         pwm_ctrl = 8;
         base_div = 256;
	}
    else 
	{
        pwm_ctrl = 4;
        base_div = 16;
	}
    total_div = (float)REF_CLK / base_div / freq - 0.5;
    for (pwm_ctrl; pwm_ctrl<15; pwm_ctrl++) 
	{
		if (total_div > 1023) 
		{
			total_div >>= 1;
		}
        else 
		{
			break;
        }
	}
        //----------------------------------- 

    switch (port) 
	{
        		case PWM_A:
            					reg = SC_PWMA_CTRL2 & 0xC0;
            					break;
        		case PWM_B:
            					reg = SC_PWMB_CTRL2 & 0xC0;
            					break;
        		case PWM_C:
            					reg = SC_PWMC_CTRL2 & 0xC0;
            					break;
        		case PWM_D:
            					reg = SC_PWMD_CTRL2 & 0xC0;
            					break;
        		default:
            					reg = 0x00;//error
            				return;
            			break;
	}
//----------------------------------------
    //if (total_div != 0)
        //total_div = total_div - 1; //00h->1, 01h->2,...
    
    div_hi = ((total_div >> 4) & 0x30);
    div_lo = (UCHAR)total_div;
    reg = reg | pwm_ctrl | div_hi; 
            
    switch (port) 
	{
        		case PWM_A:
            					SC_PWMA_CTRL2 = reg;
            					SC_PWMA_CTRL3 = div_lo;
            					break;
        		case PWM_B:
            					SC_PWMB_CTRL2 = reg;
            					SC_PWMB_CTRL3 = div_lo;
            					break;
        		case PWM_C:
            					SC_PWMC_CTRL2 = reg;
            					SC_PWMC_CTRL3 = div_lo;
            					break;
        		case PWM_D:
            					SC_PWMD_CTRL2 = reg;
            					SC_PWMD_CTRL3 = div_lo;
            					break;
        			default:								//error
            					break;
	}
        //----------------------------------
	 //select PWM PORT ENBALE 
        //-----------------------------------
    switch (pin)                                        //
	{
        			case PWMA_PIN_69:
            							SC_MCU_IO_CTRL3 &= ~(BIT7|BIT6);
            							SC_MCU_IO_CTRL3 |= BIT6;
            							break;
        			case PWMB_PIN_65:
            							SC_MCU_IO_CTRL5 &= ~(BIT5|BIT4);
            							SC_MCU_IO_CTRL5 |= BIT4;
            							break;
        			case PWMB_PIN_66:
            							SC_MCU_IO_CTRL4 &= ~(BIT7|BIT6);
            							SC_MCU_IO_CTRL4 |= BIT6;
           							 break;
       			 case PWMC_PIN_121:
#if IS_NT68770_SERIES
            			SC_MCU_IO_CTRL4 &= ~(BIT1|BIT0);
            			SC_MCU_IO_CTRL4 |= BIT1;
		#else
            			SC_MCU_IO_CTRL4 &= ~(BIT1|BIT0);
            			SC_MCU_IO_CTRL4 |= BIT0;
#endif
            							break;
        case PWMC_PIN_124:
            					SC_MCU_IO_CTRL3 &= ~(BIT3|BIT2);
            					SC_MCU_IO_CTRL3 |= BIT2;
            							break;
        case PWMD_PIN_43:
           					 SC_MCU_IO_CTRL5 &= ~(BIT7|BIT6);
            					SC_MCU_IO_CTRL5 |= BIT7;
           							 break;
        case PWMD_PIN_50:
           					 SC_MCU_IO_CTRL1 &= ~(BIT1|BIT0);
            					SC_MCU_IO_CTRL1 |= BIT0;
            							break;
            
            
        case PWMA_PIN_67:
            SC_MCU_IO_CTRL3 &= ~(BIT7|BIT6);
            SC_MCU_IO_CTRL3 |= BIT6;
            break;
        case PWMA_PIN_109:
            SC_MCU_IO_CTRL4 &= ~(BIT7|BIT6);
            SC_MCU_IO_CTRL4 |= BIT6;
            break;
        case PWMA_PIN_127:
            SC_MCU_IO_CTRL3 &= ~(BIT3|BIT2);
            SC_MCU_IO_CTRL3 |= BIT2;
            break;
        case PWMB_PIN_27:
            SC_MCU_IO_CTRL2 &= ~(BIT7|BIT6);
            SC_MCU_IO_CTRL2 |= BIT6;
            break;
        case PWMB_PIN_42:
            SC_MCU_IO_CTRL3 &= ~(BIT1|BIT0);
            SC_MCU_IO_CTRL3 |= BIT0;
            break;
        case PWMC_PIN_6:
            SC_MCU_IO_CTRL2 &= ~(BIT5|BIT4);
            SC_MCU_IO_CTRL2 |= BIT4;
            break;
        case PWMC_PIN_104:
            SC_MCU_IO_CTRL1 &= ~(BIT7|BIT6);
            SC_MCU_IO_CTRL1 |= BIT6;
            break;
        case PWMD_PIN_125:									
            					SC_MCU_IO_CTRL1 &= ~(BIT3|BIT2);
            					SC_MCU_IO_CTRL1 |= BIT2;			//george-mark: set_PA2*/PWMD*	SpacPage=P310
            					break;
        case PWMD_PIN_66:
            SC_MCU_IO_CTRL1 &= ~(BIT5|BIT4);
            SC_MCU_IO_CTRL1 |= BIT4;
            break;
        case PWMA_PIN_22:
            SC_MCU_IO_CTRL1 &= ~(BIT5|BIT4);
            SC_MCU_IO_CTRL1 |= BIT4;
            break;
        case PWMB_PIN_64:
            SC_MCU_IO_CTRL1 &= ~(BIT3|BIT2);
            SC_MCU_IO_CTRL1 |= BIT2;
            break;


    }

    pin = 0; // Disable compile warning only.
}

/**************************************************************************//**
 * Set PWM duty.
 * @param port PWM output port. (e.x. PWMA, PWMB etc...)
 * @param value PWM duty.
 ******************************************************************************/
void SetScalerPWM(UCHAR port, USHRT value)    
{
    switch (port) {
        case PWM_A:
            SC_PWMA_CTRL5 = ((UCHAR)value & 0x03);
            SC_PWMA_CTRL4 = (value >> 2);
            break;
        case PWM_B:
            SC_PWMB_CTRL5 = ((UCHAR)value & 0x03);
            SC_PWMB_CTRL4 = (value >> 2);
            break;
        case PWM_C:
            SC_PWMC_CTRL5 = ((UCHAR)value & 0x03);
            SC_PWMC_CTRL4 = (value >> 2);
            break;
        case PWM_D:
            SC_PWMD_CTRL5 = ((UCHAR)value & 0x03);
            SC_PWMD_CTRL4 = (value >> 2);
            break;  
    }
}

#if ENABLE_SET_PWM_MAX_BUFFER == ON
/**************************************************************************//**
 * Get current PWM duty setting.
 * @return PWM duty setting.
 ******************************************************************************/
USHRT GetScalerPWM(UCHAR port)
{
    USHRT pwm;
    UCHAR ch;

    switch (port) {
        case PWM_A:
            pwm = SC_PWMA_CTRL4;
            ch = SC_PWMA_CTRL5 & 0x03;
            pwm = (pwm << 2) | ch;
            break;
        case PWM_B:
            pwm = SC_PWMB_CTRL4;
            ch = SC_PWMB_CTRL5 & 0x03;
            pwm = (pwm << 2) | ch;
            break;
        case PWM_C:
            pwm = SC_PWMC_CTRL4;
            ch = SC_PWMC_CTRL5 & 0x03;
            pwm = (pwm << 2) | ch;
            break;
        case PWM_D:
            pwm = SC_PWMD_CTRL4;
            ch = SC_PWMD_CTRL5 & 0x03;
            pwm = (pwm << 2) | ch;
            break;
        default:
            pwm = 0;//error
            break;
    }

    return pwm;
}
#endif

/**************************************************************************//**
 * Enable PWM function.
 * @param port PWM output port. (e.x. PWMA, PWMB etc...)
 ******************************************************************************/
void EnableScalerPWM(UCHAR port)
{
    switch (port) {
        case PWM_A:
            SC_PWMA_CTRL1 = (SC_PWMA_CTRL1 & 0xFC) | BIT7;
            break;
        case PWM_B:
            SC_PWMB_CTRL1 = (SC_PWMB_CTRL1 & 0xFC) | BIT7;
            break;
        case PWM_C:
            SC_PWMC_CTRL1 = (SC_PWMC_CTRL1 & 0xFC) | BIT7;
            break;
        case PWM_D:
            SC_PWMD_CTRL1 = (SC_PWMD_CTRL1 & 0xFC) | BIT7;
            break;
        default:
        case PWM_ALL:
            SC_PWMA_CTRL1 = (SC_PWMA_CTRL1 & 0xFC) | BIT7;
            SC_PWMB_CTRL1 = (SC_PWMB_CTRL1 & 0xFC) | BIT7;
            SC_PWMC_CTRL1 = (SC_PWMC_CTRL1 & 0xFC) | BIT7;
            SC_PWMD_CTRL1 = (SC_PWMD_CTRL1 & 0xFC) | BIT7;
            break;
    }
}

/**************************************************************************//**
 * Disable PWM function.
 * @param port PWM output port. (e.x. PWMA, PWMB etc...)
 ******************************************************************************/
void DisableScalerPWM(UCHAR port)
{
    switch (port) {
        case PWM_A:
    SC_PWMA_CTRL1 = (SC_PWMA_CTRL1 & 0x7C) | 0x03; //clock off
            break;
        case PWM_B:
    SC_PWMB_CTRL1 = (SC_PWMB_CTRL1 & 0x7C) | 0x03; //clock off
            break;
        case PWM_C:
    SC_PWMC_CTRL1 = (SC_PWMC_CTRL1 & 0x7C) | 0x03; //clock off
            break;
        case PWM_D:
    SC_PWMD_CTRL1 = (SC_PWMD_CTRL1 & 0x7C) | 0x03; //clock off
            break;
        default:
        case PWM_ALL:
            SC_PWMA_CTRL1 = (SC_PWMA_CTRL1 & 0x7C) | 0x03; //clock off
            SC_PWMB_CTRL1 = (SC_PWMB_CTRL1 & 0x7C) | 0x03; //clock off
            SC_PWMC_CTRL1 = (SC_PWMC_CTRL1 & 0x7C) | 0x03; //clock off
            SC_PWMD_CTRL1 = (SC_PWMD_CTRL1 & 0x7C) | 0x03; //clock off
            break;
    }
}

/**************************************************************************//**
 * Set the function of VSync-reset PWM duty.
 * @param port PWM output port.
 * @param on TRUE to turn on VSync-reset function else FALSE.
 ******************************************************************************/
void SetVSyncResetPWM(UCHAR port, UCHAR on)
{
    on &= BIT0;

    switch (port) {
        case PWM_A:
            SC_PWMA_CTRL1 = (SC_PWMA_CTRL1 & 0xDF) | (on << 5);
            break;
        case PWM_B:
            SC_PWMB_CTRL1 = (SC_PWMB_CTRL1 & 0xDF) | (on << 5);
            break;
        case PWM_C:
            SC_PWMC_CTRL1 = (SC_PWMC_CTRL1 & 0xDF) | (on << 5);
            break;
        case PWM_D:
            SC_PWMD_CTRL1 = (SC_PWMD_CTRL1 & 0xDF) | (on << 5);
            break;
    }
}
