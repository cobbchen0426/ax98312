/******************************************************************************/
/*             Novatek MicroElectronics Corp.                          */
/*       6F, No. 1-2, Innovation Road I, Science-Based Industrial Park,       */
/*                         HsinChu 300, Taiwan, R.O.C.                        */
/*    TEL:886-3-567-0889       FAX:886-3-577-0132                      */
/*    All Rights Reserved                                              */
/******************************************************************************/

#ifndef _FE2P_LIB_H
#define _FE2P_LIB_H

//******************************************************************************
// I N C L U D E   F I L E S
//******************************************************************************

//******************************************************************************
// M A C R O   D E F I N I T I O N S
//******************************************************************************
#define UNKNOWN_FLASH   0x00 /*!< Flash ID. */
#define PMC_1M          0x10 /*!< PMC Flash ID. */
#define PMC_2M          0x11 /*!< PMC Flash ID. */
#define PMC_4M          0x12 /*!< PMC Flash ID. */
#define PMC_LD1M        0x14 /*!< PMC Flash ID. */
#define PMC_LD2M        0x15 /*!< PMC Flash ID. */
#define PMC_UNKNOWN     0x1F /*!< PMC Flash ID. */
#define SST_1M          0x20 /*!< SST Flash ID. */
#define SST_2M          0x21 /*!< SST Flash ID. */
#define SST_UNKNOWN     0x2F /*!< SST Flash ID. */
#define MXIC_1M         0x30 /*!< MXIC Flash ID. */
#define MXIC_2M         0x31 /*!< MXIC Flash ID. */
#define MXIC_4M         0x32 /*!< MXIC Flash ID. */
#define MXIC_2M_2026    0x33 /*!< MXIC Flash ID. */
#define MXIC_UNKNOWN    0x3F /*!< MXIC Flash ID. */
#define WINB_1M         0x40 /*!< Winbond Flash ID. */
#define WINB_2M         0x41 /*!< Winbond Flash ID. */
#define WINB_4M         0x42 /*!< Winbond Flash ID. */
#define WINB_8M_X         0x43 /*!< Winbond Flash ID. */
#define WINB_8M_Q         0x44 /*!< Winbond Flash ID. */
#define WINB_2M_W25X21CL    0x4C /*!< Winbond Flash ID. */
#define WINB_4M_W25X41CL    0x4D /*!< Winbond Flash ID. */
#define WINB_UNKNOWN    0x4F /*!< Winbond Flash ID. */
#define EON_1M          0x50 /*!< EON Flash ID. */
#define EON_2M          0x51 /*!< EON Flash ID. */
#define EON_UNKNOWN     0x5F /*!< EON Flash ID. */
#define AMIC_1M         0x60 /*!< AMIC Flash ID. */
#define AMIC_2M         0x61 /*!< AMIC Flash ID. */		// George
#define AMIC_4M         0x62 /*!< AMIC Flash ID. */
#define AMIC_UNKNOWN    0x6F /*!< AMIC Flash ID. */
#define ESMT_2M		0x71 /*!< ESMT Flash ID. */
#define ESMT_4M         0x72 /*!< ESMT Flash ID. */
#define ESMT_8M         0x73 /*!< ESMT Flash ID. */
#define ESMT_UNKNOWN    0x7F /*!< ESMT Flash ID. */
#define GD_1M		0x80 /*!< GD Flash ID. */
#define GD_2M		0x81 /*!< GD Flash ID. */
#define GD_4M           0x82 /*!< GD Flash ID. */
#define GD_UNKNOWN      0x8F /*!< GD Flash ID. */
#define NTS_1M		0x90 /*!< NTS Flash ID. */
#define NTS_2M		0x91 /*!< NTS Flash ID. */
#define NTS_4M                    0x92 /*!< NTS Flash ID. */
#define NTS_UNKNOWN      0x9F /*!< NTS Flash ID. */
#define FDN_1M		0xA0 /*!< Fudan Flash ID. */
#define FDN_2M		0xA1 /*!< Fudan Flash ID. */
#define FDN_4M                    0xA2 /*!< Fudan Flash ID. */
#define FDN_UNKNOWN      0xAF /*!< Fudan Flash ID. */

#define FLASH_AMIC_SR_COMMAND      0
#define FLASH_W25X21CL_SR_COMMAND  0
//******************************************************************************
// D A T A   T Y P E   D E F I N E S
//******************************************************************************

//******************************************************************************
// V A R I A B L E S   P R O T O T Y P E
//******************************************************************************

//******************************************************************************
// F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
void Fe2p_WriteEnable(void);
void Fe2p_SectorErase(unsigned short Sector,  unsigned char ucProtectFlag);
void Fe2p_ByteWrite(unsigned short Ptr, unsigned char Data, unsigned char ucProtectFlag);
void Fe2p_PageWrite(unsigned short Faddr, unsigned short Saddr, unsigned char Length, unsigned char ucProtectFlag);
void Fe2p_ByteRead(unsigned short Ptr,unsigned char *Data);
void Fe2p_PageRead(unsigned short Ptr,unsigned char *Data, unsigned short Length);
unsigned char Fe2p_Init( unsigned char ucProtectFlag);
void Fe2p_SetProtect(unsigned char ucProtectFlag);
void PMC_Sector_Unlock(unsigned short addr_15_0);
void PMC_Sector_Lock(void);
unsigned short Fe2p_Get_Lib_Ver(void);
void Fe2p_Set_SPI_CMD_buffer_addr(unsigned short buff_addr);
unsigned char Fe2p_RDSR(void);
void Fe2p_SetOffset(unsigned long offset);

#endif
