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

#if ENABLE_EMBEDDED_CHECKSUM == ON

//******************************************************************************
// M A C R O   D E F I N I T I O N S
//******************************************************************************
/*!
 * The bank where the checksum is.
 * The value is 0 ~ 7.
 * 0 is preferred.
 */
#define EMBEDDED_CHKSUM_BANK        0x00
#if ENABLE_FE2P == ON
#define EMBEDDED_CHKSUM_ADDR_HI     0xEE /*!< The high byte of address where the checksum is. */
#define EMBEDDED_CHKSUM_ADDR_LOW    0x00 /*!< The low byte of address where the checksum is. */
#else
#define EMBEDDED_CHKSUM_ADDR_HI     0xFE /*!< The high byte of address where the checksum is. */
#define EMBEDDED_CHKSUM_ADDR_LOW    0x00 /*!< The low byte of address where the checksum is. */
#endif

//******************************************************************************
// G L O B A L   V A R I A B L E S
//******************************************************************************

//******************************************************************************
// S T A T I C   V A R I A B L E S
//******************************************************************************
/*!
 * The string for EasyWriter to indicate where the checksum is embedded.
 */
static code UCHAR ucEmbeddedCheckSumTable[] = {
    0x55, 0xAA, 0x66, 0x99, 'C', 'H', 'K',
    EMBEDDED_CHKSUM_BANK,
    EMBEDDED_CHKSUM_ADDR_HI,
    EMBEDDED_CHKSUM_ADDR_LOW
};

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

/**************************************************************************//**
 * Get the checksum embedded in code.
 * @return The value of the checksum.
 ******************************************************************************/
USHRT GetEmbeddedCheckSum(void)
{
    USHRT checksum;
    idata UCHAR tmp;

    // Remove compile warning only
    tmp = ucEmbeddedCheckSumTable[0];

    tmp = P1;
    P1 = EMBEDDED_CHKSUM_BANK;
    checksum = *((USHRT code *)(EMBEDDED_CHKSUM_ADDR_HI*256+EMBEDDED_CHKSUM_ADDR_LOW));
    P1 = tmp;
    
    return ((checksum<<8)+(checksum>>8));
}

#endif //ENABLE_EMBEDDED_CHECKSUM == ON
