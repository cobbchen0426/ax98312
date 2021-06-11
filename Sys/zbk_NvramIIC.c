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

#if ENABLE_FE2P == OFF		//george: no-compiler-here.	( Because ENABLE_FE2P = ON )
//******************************************************************************
// M A C R O   D E F I N I T I O N S
//******************************************************************************
#if NVRAM_SCL_PORT == MCU_PORT_A
    #define SCL_DIR_PORT    RDPA_REG
    #define SCL_PORT        PortA
#elif NVRAM_SCL_PORT == MCU_PORT_B
    #define SCL_DIR_PORT    RDPB_REG
    #define SCL_PORT        PortB
#elif NVRAM_SCL_PORT == MCU_PORT_C
    #define SCL_DIR_PORT    RDPC_REG
    #define SCL_PORT        PortC
#elif NVRAM_SCL_PORT == MCU_PORT_D
    #define SCL_DIR_PORT    RDPD_REG
    #define SCL_PORT        PortD
#elif NVRAM_SCL_PORT == MCU_PORT_E
    #define SCL_DIR_PORT    RDPE_REG
    #define SCL_PORT        PortE
#elif NVRAM_SCL_PORT == MCU_PORT_3
    #define SCL_PORT        P3
#endif
#if NVRAM_SDA_PORT == MCU_PORT_A
    #define SDA_DIR_PORT    RDPA_REG
    #define SDA_PORT        PortA
#elif NVRAM_SDA_PORT == MCU_PORT_B
    #define SDA_DIR_PORT    RDPB_REG
    #define SDA_PORT        PortB
#elif NVRAM_SDA_PORT == MCU_PORT_C
    #define SDA_DIR_PORT    RDPC_REG
    #define SDA_PORT        PortC
#elif NVRAM_SDA_PORT == MCU_PORT_D
    #define SDA_DIR_PORT    RDPD_REG
    #define SDA_PORT        PortD
#elif NVRAM_SDA_PORT == MCU_PORT_E
    #define SDA_DIR_PORT    RDPE_REG
    #define SDA_PORT        PortE
#elif NVRAM_SDA_PORT == MCU_PORT_3
    #define SDA_PORT        P3
#endif

#if NVRAM_SCL_PORT == MCU_PORT_3
#define IIC_SCL_IN
#define IIC_SCL_OUT
#define IIC_SCL_HIGH    (SCL_PORT |= NVRAM_SCL_BIT)
#define IIC_SCL_LOW     (SCL_PORT &= ~NVRAM_SCL_BIT)
#else
#define IIC_SCL_IN      (SCL_DIR_PORT |= NVRAM_SCL_BIT)
#define IIC_SCL_OUT     (SCL_DIR_PORT &= ~NVRAM_SCL_BIT)
#define IIC_SCL_HIGH    (SCL_PORT = (SCL_PORT | SCL_DIR_PORT) | NVRAM_SCL_BIT)
#define IIC_SCL_LOW     (SCL_PORT = (SCL_PORT | SCL_DIR_PORT) & ~NVRAM_SCL_BIT)
#endif
#define IIC_SCL_STATUS  (SCL_PORT & NVRAM_SCL_BIT)

#if NVRAM_SDA_PORT == MCU_PORT_3
#define IIC_SDA_IN
#define IIC_SDA_OUT
#define IIC_SDA_HIGH    (SDA_PORT |= NVRAM_SDA_BIT)
#define IIC_SDA_LOW     (SDA_PORT &= ~NVRAM_SDA_BIT)
#else
#define IIC_SDA_IN      (SDA_DIR_PORT |= NVRAM_SDA_BIT)
#define IIC_SDA_OUT     (SDA_DIR_PORT &= ~NVRAM_SDA_BIT)
#define IIC_SDA_HIGH    (SDA_PORT = (SDA_PORT | SDA_DIR_PORT) | NVRAM_SDA_BIT)
#define IIC_SDA_LOW     (SDA_PORT = (SDA_PORT | SDA_DIR_PORT) & ~NVRAM_SDA_BIT)
#endif
#define IIC_SDA_STATUS  (SDA_PORT & NVRAM_SDA_BIT)

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
static void NvramIICDelay(void);
static void NvramIICStart(void);
static void NvramIICStop(void);
static UCHAR NvramIICWriteByte(UCHAR value);
static UCHAR NvramIICReadByte(UCHAR ack);

//******************************************************************************
// E X T E R N A L   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// F U N C T I O N   B O D Y S
//******************************************************************************

/**************************************************************************//**
 * Set IIC SCL to high and wait SCL to high.
 ******************************************************************************/
static void SetIICSCLHigh(void)
{
    idata USHRT loop;

    IIC_SCL_HIGH;
    loop = 0;
    while ((IIC_SCL_STATUS == LOW) && (--loop != 0)) {
        _nop_();
        _nop_();
    }
}

/**************************************************************************//**
 * IIC delay: 6 NOPs.
 ******************************************************************************/
static void NvramIICDelay(void)
{
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
}

/**************************************************************************//**
 * Create IIC start pulse.
 ******************************************************************************/
static void NvramIICStart(void)
{
    UCHAR i;
    
    IIC_SDA_HIGH;
    SetIICSCLHigh();
    IIC_SDA_IN;
    NvramIICDelay();
    i = 0;
    while ((IIC_SDA_STATUS==LOW) && (i<9)) { //Gen 9 clock
        IIC_SCL_LOW;
        NvramIICDelay();
        SetIICSCLHigh();
        i++;
    }
    IIC_SDA_OUT;
    IIC_SDA_LOW;
    NvramIICDelay();
    IIC_SCL_LOW;
}

/**************************************************************************//**
 * Create IIC stop pulse.
 ******************************************************************************/
static void NvramIICStop(void)
{
    IIC_SDA_LOW;
    NvramIICDelay();
    SetIICSCLHigh();
    NvramIICDelay();
    IIC_SDA_HIGH;
}

/**************************************************************************//**
 * Write one byte data through software IIC channel.
 * @param value Data to be sent.
 * @return ACK or NACK.
 ******************************************************************************/
static UCHAR NvramIICWriteByte(UCHAR value)
{
    idata UCHAR i, result;
    code UCHAR Tbl[] = {BIT7, BIT6, BIT5, BIT4, BIT3, BIT2, BIT1, BIT0};

    for (i=0 ; i<8 ;i++) {
        NvramIICDelay();
        IIC_SCL_LOW;
        NvramIICDelay();
        if (value & Tbl[i]) {
            IIC_SDA_HIGH;
        }
        else {
            IIC_SDA_LOW;
        }
        NvramIICDelay();
        SetIICSCLHigh();
    }
    NvramIICDelay();
    IIC_SCL_LOW;
    NvramIICDelay();
    IIC_SDA_LOW; //Avoid pulse
    IIC_SDA_IN; //Release SDA bus
    IIC_SDA_HIGH;
    //9th clock
    NvramIICDelay();
    SetIICSCLHigh();
    NvramIICDelay();
    if (IIC_SDA_STATUS == LOW) {
        result = ACK;
    }
    else {
        i = 7;
        while (IIC_SDA_STATUS && i) {
            NvramIICDelay();
            i--;
        }
        if (i == 0) {
            result = NACK;
        }
        else {
            result = ACK;
        }
    }
    IIC_SCL_LOW;
    IIC_SDA_OUT;
    IIC_SDA_LOW;
    NvramIICDelay();
    
    return result;
}

/**************************************************************************//**
 * Read one byte data through software IIC channel
 * @param ack TRUE if system has to send ACK back else FALSE..
 ******************************************************************************/
static UCHAR NvramIICReadByte(UCHAR ack)
{
    UCHAR i, result;

    ack &= BIT0;
    IIC_SDA_IN;
    IIC_SDA_HIGH;
    for (i=0; i<8; i++) {
        result <<= 1;
        SetIICSCLHigh();
        NvramIICDelay();
        if (IIC_SDA_STATUS == LOW) {
            result &= 0xFE; //SDA = 0
        }
        else {
            result |= 0x01; //SDA = 1
        }
        IIC_SCL_LOW;
        NvramIICDelay();
    }
    IIC_SDA_OUT;
    if (ack == ACK) {
        IIC_SDA_LOW;
    }
    else {
        IIC_SDA_HIGH;
    }
    NvramIICDelay();
    SetIICSCLHigh();
    NvramIICDelay();
    IIC_SCL_LOW;
    NvramIICDelay();
    
    return result;
}

#undef SCL_DIR_PORT
#undef SCL_PORT
#undef SDA_DIR_PORT
#undef SDA_PORT
#undef IIC_SCL_IN
#undef IIC_SCL_OUT
#undef IIC_SCL_HIGH
#undef IIC_SCL_LOW
#undef IIC_SCL_STATUS
#undef IIC_SDA_IN
#undef IIC_SDA_OUT
#undef IIC_SDA_HIGH
#undef IIC_SDA_LOW
#undef IIC_SDA_STATUS

/**************************************************************************//**
 * Write data to Nvram.
 * @param slave Device address.
 * @param addr Address of NVRam.
 * @param len Length of the data array.
 * @param ptr Pointer to the data array.
 ******************************************************************************/
void NvramWriteIICSeq(UCHAR slave, UCHAR addr, USHRT len, UCHAR *ptr)
{
    USHRT i;

    //IIC start condition
    NvramIICStart();

    //Write the device address, retry if fail
    for (i=0; i<10; i++) {
        if (NvramIICWriteByte(slave) == ACK) {
            break;
        }
        NvramIICDelay();
    }
    if (i == 10) { //The device doesn't exist
        NvramIICStop();
        return;
    }

    //Write address
    NvramIICWriteByte(addr);

    //Write bytes sequentially
    i = 0;
    while (i < len) {
        ResetWDTimer();
        NvramIICWriteByte(ptr[i]);
        i++;
    }

    //IIC stop condition
    NvramIICStop();
}

/**************************************************************************//**
 * Read data from Nvram.
 * @param slave Device address.
 * @param addr Address of NVRam.
 * @param len Length of the data array.
 * @param[out] ptr Pointer to the data array.
 ******************************************************************************/
void NvramReadIICSeq(UCHAR slave, UCHAR addr, USHRT len, UCHAR *ptr)
{
    USHRT i;

    //IIC start condition
    NvramIICStart();

    //Write the device address, retry if fail
    for (i=0; i<10; i++) {
        if (NvramIICWriteByte(slave) == ACK) {
            break;
        }
        NvramIICDelay();
    }
    if (i == 10) { //The device doesn't exist
        NvramIICStop();
        return;
    }

    //Write address
    NvramIICWriteByte(addr);

    //IIC start condition
    NvramIICStart();

    //Write the device address(R), retry if fail
    for (i=0; i<10; i++) {
        if (NvramIICWriteByte(slave|BIT0) == ACK) {
            break;
        }
        NvramIICDelay();
    }

    i = 0;
    while (i < len) {
        ResetWDTimer();
        if (i == (len-1) ) { //Last byte
            ptr[i] = NvramIICReadByte(NACK);
        }
        else {
            ptr[i] = NvramIICReadByte(ACK);
        }
        i++;
    }

    //IIC stop condition
    NvramIICStop();
}

/**************************************************************************//**
 * Check the IIC device is alive or not.
 * @param slave Device address.
 * @return TRUE if the device is alive else FALSE.
 ******************************************************************************/
BOOL NvramCheckDevice(UCHAR slave)
{
    BOOL device;

    NvramIICStart();
    NvramIICStop();
    NvramIICDelay();
    NvramIICStart();
    if (NvramIICWriteByte(slave) != 0) {
        device = FALSE;
    }
    else {
        device = TRUE;
    }
    NvramIICStop();
    NvramIICDelay();
    NvramIICStart();
    NvramIICStop();
 
    return device;
}

#endif //ENABLE_FE2P == OFF
