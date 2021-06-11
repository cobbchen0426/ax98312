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

#if ENABLE_FE2P == ON

//******************************************************************************
// M A C R O   D E F I N I T I O N S
//******************************************************************************
#define FE2P_BUFFER_ADDR FE2P_SRAM_ADDR  /*!< The base address of FE2P buffer in the sram. */
#define VALID_FLAG_ADDR  0x7FF           /*!< Mask for the address */
#define BLOCK0           0x0000          /*!< The address of block 0 */
#define BLOCK1           0x1800          /*!< The address of block 1 */
#define BLOCK2           0x0800          /*!< The address of block 2 */
#define BLOCK3           0x2000          /*!< The address of block 3 */
#define BLOCK4           0x1000          /*!< The address of block 4 */
#define BLOCK5           0x2800          /*!< The address of block 5 */
#define BLOCK6           0x3000          /*!< The address of block 6 */
#define BLOCK7           0x3800          /*!< The address of block 7 */
#define FE2P_SAVE_TIME   100             /*!< Delay time to save data from sram to flash. Current setting is 1s(100x10ms). */
#define MAXBLOCK         5               /*!<
                                          *   The max number of valid blocks.
                                          *   If flash is 2banks, the number is 1.
                                          *   If flash is 4banks, the number is 5.
                                          *   The block 6 and block 7 are used for POT when flash is 4banks.
                                          */
#define TIMEBLOCK        BLOCK6          /*!< POT block. The block can be 0/2/4/6. So far, we use 6 as default. */
#define TIME_FLAG_ADDR   0x0FFF          /*!< The valid tag for POT block */

//******************************************************************************
// G L O B A L   V A R I A B L E S
//******************************************************************************

//******************************************************************************
// S T A T I C   V A R I A B L E S
//******************************************************************************
static BOOL  bFE2P_Save;                 /*!<
                                          * The flag of "save the data from sram to flash".
                                          * The flag will be raised after system perform FE2P_NvramWrite.
                                          * The flag will be cleared after system perform FE2P_SaveToFlash.
                                          */
static xdata UCHAR ucFE2P_Valid_Block;   /*!<
                                          * This is the id of current valid block.
                                          * After FE2P_SaveToFlash, the id will be assigned as the id of next valid block.
                                          */
static xdata UCHAR ucFE2P_Buffer[2048] _at_ FE2P_BUFFER_ADDR; /*!< The FE2P buffer in the sram. The buffer is located at FE2P_BUFFER_ADDR */
static xdata UCHAR ucFlashID = UNKNOWN_FLASH; /*!< Flash ID after system performs Fe2p_Init. */

#if ENABLE_DIRECT_FE2P == ON
/*!
 * The start address of a block which we choose under directly FE2P mode. The unit is 4KB.
 * So far, we choose latest 16KB of a flash as FE2P flash.
 */
#define DAOF 60
/*!
 * The key words for FE2P mode identification.
 * EasyWrite will search the key words in the HEX code(or binary code) and turn on/off direct FE2P protection.
 */
static code UCHAR ucFE2PTable[] = {0x55, 0xaa, 0x66, 0x99, 'D', 'A', 'O', 'F', DAOF, 0x54};
#else
/*!
 * The key words for FE2P mode identification.
 * EasyWrite will search the key words in the HEX code(or binary code) and turn on/off FE2P protection.
 */
static code UCHAR ucFE2PTable[] = {0x55, 0xaa, 0x66, 0x99, 'F', 'E', '2', 'P', 0x0B};
#endif

//******************************************************************************
// E X T E R N A L   V A R I A B L E   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// S T A T I C   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
static UCHAR FE2P_CheckValidBlock(void);
static void FLASH_WP_ON(void);
static void FLASH_WP_OFF(void);
static void FLASH_InitProtection(void);
static void FLASH_ProtectOff(USHRT offset);
static void FLASH_ProtectOn(void);

//******************************************************************************
// E X T E R N A L   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// F U N C T I O N   B O D Y S
//******************************************************************************

/**************************************************************************//**
 * Initialize the Flash protection (set status register and address).
 ******************************************************************************/
static void FLASH_InitProtection(void)
{
    // Use the follow coding way to avoid compile warning when ENABLE_DIRECT_FE2P is OFF
    UCHAR opt = ENABLE_DIRECT_FE2P;

    if (opt == ON) {
        Fe2p_SetOffset(0x3C000);
    }

    FLASH_ProtectOn();
}

/**************************************************************************//**
 * Turn off Flash protection.
 * Pull low the protection control pin and disable SR protection.
 * @param offset The offset of blocks to be protected off.
 ******************************************************************************/
static void FLASH_ProtectOff(USHRT offset)
{
    switch (ucFlashID) {
        case PMC_LD1M:
        case PMC_LD2M:
            PMC_Sector_Lock();
            PMC_Sector_Unlock(offset & 0xF000);
            break;
#if ENABLE_DIRECT_FE2P == ON
        case AMIC_2M:
            if ((Fe2p_RDSR() & BIT7) != 0x00) {
                FLASH_WP_OFF();
            }

            Fe2p_SetProtect(0x64);
            break;
#endif
        case MXIC_2M_2026:
            //if ((Fe2p_RDSR() & BIT7) != 0x00) {//v03_120317_1358_SYS#1
                FLASH_WP_OFF();
           // }
            break;
        default:
            if ((Fe2p_RDSR() & BIT7) != 0x00) {
                FLASH_WP_OFF();
            }

            Fe2p_SetProtect(0x00); //Samuel-2010-03-29: For flash data protection
            break;
    }
}

/**************************************************************************//**
 * Turn on the Flash protection.
 * Pull up the protection control pin and enable SR protection.
 ******************************************************************************/
static void FLASH_ProtectOn(void)
{
    switch (ucFlashID) {
        case PMC_LD1M:
        case PMC_LD2M:
            PMC_Sector_Lock();
            break;
        case MXIC_2M_2026:
            break;
        case AMIC_2M:
        default:
            if ((Fe2p_RDSR() & BIT7) != 0x00) {
                FLASH_WP_OFF();
            }
            Fe2p_SetProtect(0x1C); //Samuel-2010-03-29: For flash data protection
            break;
    }
    FLASH_WP_ON(); //Samuel-2008-08-14: Enable Flash Write Protection After FE2P Write
}

/**************************************************************************//**
 * Initialize FE2P variables and load whole configurations from flash to sram.
 ******************************************************************************/
void FE2P_RamInitialize(void)
{
    USHRT i;
    //Fe2p Initial value
    bFE2P_Save = FALSE;
    ucFE2P_Valid_Block = 0;
    for (i = 0; i < 2048; i++) {
        ucFE2P_Buffer[i] = 0xFF;
    }

    ResetWDTimer();
    Fe2p_Set_SPI_CMD_buffer_addr(FE2P_CMD_BUFFER_ADDR);

    ucFlashID = Fe2p_Init(2);
    if (ucFlashID == UNKNOWN_FLASH) { //Samuel-2010-03-29: For flash data protection
        //If we found an unknown flash, force WDT happened.
        while (bFE2P_Save == 0) {};
    }

    FLASH_InitProtection();
    Fe2p_Get_Lib_Ver();

    ucFE2P_Valid_Block = FE2P_CheckValidBlock();
    if (ucFE2P_Valid_Block > MAXBLOCK) {
        ucFE2P_Valid_Block = 0;
        NvramInitialize(NVRAM_UPDATE_ALL);
    }
    else {
        if (ucFE2P_Valid_Block == 0) {
            Fe2p_PageRead(BLOCK0, ucFE2P_Buffer, 2048); //block0 first 2k
        }
        else if (ucFE2P_Valid_Block == 1) {
            Fe2p_PageRead(BLOCK1, ucFE2P_Buffer, 2048); //block1 first 2k
        }
        else if (ucFE2P_Valid_Block == 2) {
            Fe2p_PageRead(BLOCK2, ucFE2P_Buffer, 2048); //block0 second 2k
        }
        else if (ucFE2P_Valid_Block == 3) {
            Fe2p_PageRead(BLOCK3, ucFE2P_Buffer, 2048); //block0 second 2k
        }
        else if (ucFE2P_Valid_Block == 4) {
            Fe2p_PageRead(BLOCK4, ucFE2P_Buffer, 2048); //block0 second 2k
        }
        else if (ucFE2P_Valid_Block == 5) {
            Fe2p_PageRead(BLOCK5, ucFE2P_Buffer, 2048); //block0 second 2k
        }
        else if (ucFE2P_Valid_Block == 6) {
            Fe2p_PageRead(BLOCK6, ucFE2P_Buffer, 2048); //block0 second 2k
        }
        else {
            Fe2p_PageRead(BLOCK7, ucFE2P_Buffer, 2048); //block1 second 2k
        }
    }
}

/**************************************************************************//**
 * Check FE2P blocks is valid or not.
 * @return The first valid block (The value is one of 0 to 7). If there is no valid block, the value will be 0xFF.
 ******************************************************************************/
UCHAR FE2P_CheckValidBlock(void)
{
    UCHAR Dat;
    Fe2p_ByteRead(VALID_FLAG_ADDR, &Dat);
    if (Dat == 0x55) {
        return 0;
    }

    Fe2p_ByteRead(VALID_FLAG_ADDR + BLOCK1, &Dat);
    if (Dat == 0x55) {
        return 1;
    }

    Fe2p_ByteRead(VALID_FLAG_ADDR + BLOCK2, &Dat);
    if (Dat == 0x55) {
        return 2;
    }

    Fe2p_ByteRead(VALID_FLAG_ADDR + BLOCK3, &Dat);
    if (Dat == 0x55) {
        return 3;
    }

    Fe2p_ByteRead(VALID_FLAG_ADDR + BLOCK4, &Dat);
    if (Dat == 0x55) {
        return 4;
    }

    Fe2p_ByteRead(VALID_FLAG_ADDR + BLOCK5, &Dat);
    if (Dat == 0x55) {
        return 5;
    }

    Fe2p_ByteRead(VALID_FLAG_ADDR + BLOCK6, &Dat);
    if (Dat == 0x55) {
        return 6;
    }

    Fe2p_ByteRead(VALID_FLAG_ADDR + BLOCK7, &Dat);
    if (Dat == 0x55) {
        return 7;
    }
    return 0xFF; //FE2P block damage
}

/**************************************************************************//**
 * Write data to FE2P sram
 * @param Addr   The address where the data is stored.
 * @param Length Number of data to be written.
 * @param Ptr    The pointer to data
 ******************************************************************************/
void FE2P_NvramWrite(USHRT Addr, USHRT Length, UCHAR *Ptr)
{
    USHRT i;
    for (i = 0; i < Length; i++) {
        ucFE2P_Buffer[Addr + i] = *Ptr;
        Ptr++;
    }
    bFE2P_Save = 1;
}

/**************************************************************************//**
 * Read data from FE2P sram
 * @param Addr     The address where the data is stored.
 * @param Length   Number of data to be read.
 * @param[out] Ptr The pointer to buffer
 ******************************************************************************/
void FE2P_NvramRead(USHRT Addr, USHRT Length, UCHAR *Ptr)
{
    USHRT i;
    for (i = 0; i < Length; i++) {
        *Ptr = ucFE2P_Buffer[Addr + i];
        Ptr++;
    }
}

/**************************************************************************//**
 * Dump all the user configurations from sram to flash.
 ******************************************************************************/
void FE2P_SaveToFlash(void)
{
    USHRT offset, old_offset, i;

    if (bFE2P_Save == 0) {
        return;
    }
    bFE2P_Save = 0;

    if (ucFE2P_Valid_Block > MAXBLOCK) {
        ucFE2P_Valid_Block = MAXBLOCK;
    }
    if (ucFE2P_Valid_Block == 0) {
        offset = BLOCK1; //Save to block 1
        old_offset = BLOCK0;
    }
    else if (ucFE2P_Valid_Block == 1) {
        offset = BLOCK2; //Save to block 2
        old_offset = BLOCK1;
    }
    else if (ucFE2P_Valid_Block == 2) {
        offset = BLOCK3; //Save to block 3
        old_offset = BLOCK2;
    }
    else if (ucFE2P_Valid_Block == 3) {
        offset = BLOCK4; //Save to block 4
        old_offset = BLOCK3;
    }
    else if (ucFE2P_Valid_Block == 4) {
        offset = BLOCK5; //Save to block 5
        old_offset = BLOCK4;
    }
    else if (ucFE2P_Valid_Block == 5) {
        offset = BLOCK6; //Save to block 6
        old_offset = BLOCK5;
    }
    else if (ucFE2P_Valid_Block == 6) {
        offset = BLOCK7; //Save to block 7
        old_offset = BLOCK6;
    }
    else {
        offset = BLOCK0; //Save to block 0
        old_offset = BLOCK7;
    }

    if (ucFE2P_Valid_Block == MAXBLOCK) {
        offset = BLOCK0; //Save to block 0
    }

    ResetWDTimer();

    FLASH_ProtectOff(offset);

    if ((offset & 0x0FFF) == 0x0000) {
        Fe2p_WriteEnable();
        Fe2p_SectorErase(offset, 0); //100~150ms
    }
    for (i = 0; i < 2048; i += 0x100) {
        ResetWDTimer();
        Fe2p_WriteEnable();
        Fe2p_PageWrite(i + offset, FE2P_BUFFER_ADDR + i, 0x100, 0); //256bytes 3~4.5ms
    }
    Fe2p_WriteEnable();
    Fe2p_ByteWrite(VALID_FLAG_ADDR + offset, 0x55, 0); //Set new valid flag

    FLASH_ProtectOff(old_offset);

    Fe2p_WriteEnable();
    Fe2p_ByteWrite(VALID_FLAG_ADDR + old_offset, 0x00, 0); //Clear old valid flag
    //ucFE2P_Valid_Block = (ucFE2P_Valid_Block+1) % 4;
    if (ucFE2P_Valid_Block++ >= MAXBLOCK) {
        ucFE2P_Valid_Block = 0;
    }

    FLASH_ProtectOn();

    ResetWDTimer();
}

/**************************************************************************//**
 * Activate the write protection.
 * Control the Flash protection I/O pin.
 ******************************************************************************/
static void FLASH_WP_ON(void)
{
    McuSetIOBit(FLASH_WP_PORT, FLASH_WP_BIT, FLASH_WP_ACTIVE);
}

/**************************************************************************//**
 * Inactivate the write protection.
 * Control the Flash protection I/O pin.
 ******************************************************************************/
static void FLASH_WP_OFF(void)
{
    McuSetIOBit(FLASH_WP_PORT, FLASH_WP_BIT, ~FLASH_WP_ACTIVE);
}

/**************************************************************************//**
 * Save POT counter in the Flash. (Write to flash directly.)
 ******************************************************************************/
void RecordTimeScale(void)
{
    code UCHAR scaleTab[] = {0xFE, 0xFC, 0xF8, 0xF0, 0xE0, 0xC0, 0x80, 0x00};
    USHRT offset;
    UCHAR scale, ch;
    ULONG temp;

    if ((SystemData.ucPowerOnTimerM % POT_SAVE_COUNT) != 0) {//record time scale every 10 min
        return;
    }

    //Erase if first write
    if ((SystemData.ucPowerOnTimerM == POT_SAVE_COUNT) && (SystemData.usPowerOnTimerH == 0)) {
        EraseTimeScale();
    }

    //Erase again if erase fail
    Fe2p_ByteRead(TIME_FLAG_ADDR + TIMEBLOCK, &ch);
    if (ch != 0xFF) {
        EraseTimeScale();
    }

    //write enable
    FLASH_ProtectOff(TIMEBLOCK);

    //write
    temp = (ULONG)(SystemData.usPowerOnTimerH - SystemData.usPOTimerH_FE2P) * 60 + SystemData.ucPowerOnTimerM - SystemData.ucPOTimerM_FE2P;
    if (temp != 0) {
        temp = temp - 1;
    }
    temp = temp / POT_SAVE_COUNT;
    offset = temp / 8;
    offset &= 0x0FFF;
    scale = temp % 8;
    ch = scaleTab[scale];
    Fe2p_WriteEnable();
    Fe2p_ByteWrite(TIMEBLOCK + offset, ch, 0); //Set new valid flag

    //write protect
    FLASH_ProtectOn();
}

/**************************************************************************//**
 * Erase the POT block. (Erase the flash block directly)
 ******************************************************************************/
void EraseTimeScale(void)
{
    if (FE2P_CheckValidBlock() == 0xFF) {
        SystemData.ucPowerOnTimerM = 0;
        SystemData.usPowerOnTimerH = 0;
        return;
    }

    ResetWDTimer();

    //write enable
    FLASH_ProtectOff(TIMEBLOCK);

    Fe2p_WriteEnable();
    Fe2p_ByteWrite(TIMEBLOCK + TIME_FLAG_ADDR, 0x00, 0); //Set new valid flag

    //erase
    Fe2p_WriteEnable();
    Fe2p_SectorErase(TIMEBLOCK, 0); //100~150ms

    //write protect
    FLASH_ProtectOn();

    ResetWDTimer();
}

/**************************************************************************//**
 * Decode the POT from flash.
 ******************************************************************************/
void DecodeTimeScale(void)
{
    ULONG temp;
    USHRT offset;
    UCHAR ch;

    temp = ((ULONG)SystemData.usPOTimerH_FE2P * 60 + SystemData.ucPOTimerM_FE2P) / POT_SAVE_COUNT;
    for (offset = 0; offset < 4095; offset++) {
        Fe2p_ByteRead(offset + TIMEBLOCK, &ch);
        if (ch != 0) {
            break;
        }
    }
    temp += (offset * 8);
    if (ch == 0xFE) {
        temp += 1;
    }
    else if (ch == 0xFC) {
        temp += 2;
    }
    else if (ch == 0xF8) {
        temp += 3;
    }
    else if (ch == 0xF0) {
        temp += 4;
    }
    else if (ch == 0xE0) {
        temp += 5;
    }
    else if (ch == 0xC0) {
        temp += 6;
    }
    else if (ch == 0x80) {
        temp += 7;
    }
    temp = temp * POT_SAVE_COUNT;
    SystemData.usPowerOnTimerH = temp / 60;
    SystemData.ucPowerOnTimerM = temp % 60;
}

#endif //ENABLE_FE2P == ON
