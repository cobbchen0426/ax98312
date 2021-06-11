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

/**************************************************************************//**
 * Read 2-bytes from scaler register.
 * @return 2-bytes value.
 ******************************************************************************/
USHRT ReadShortScaler(UCHAR *address)
{
    UCHAR ch;
    USHRT value;

    ch = *address;
    address++;
    value = *address;
    value <<= 8;
    value |= ch;

    return value;
}

/**************************************************************************//**
 * Read 3-bytes from scaler register.
 * @return 3-bytes value.
 ******************************************************************************/
ULONG Read3ByteScaler(UCHAR *address)
{
    UCHAR ch;
    ULONG value;

    address += 2;
    value = *address;
    address--;
    ch = *address;
    value <<= 8;
    value |= ch;
    address--;
    ch = *address;
    value <<= 8;
    value |= ch;

    return value;
}

/**************************************************************************//**
 * Read 2-bytes from scaler register with filter.
 * @return 2-bytes value.
 ******************************************************************************/
USHRT ReadShortScalerHighLowFilter(UCHAR *address)
{
    USHRT value;
    UCHAR i=0;
    value = ReadShortScaler(address);
    while ((value != ReadShortScaler(address)) && (i < 5)) {
        value = ReadShortScaler(address);
        i++;
    }
    return value;
}

/**************************************************************************//**
 * Read 3-bytes from scaler register with filter.
 * @return 3-bytes value.
 ******************************************************************************/
ULONG Read3ByteScalerHighLowFilter(UCHAR *address)
{
    xdata ULONG value;
    xdata UCHAR i = 0;
    value = Read3ByteScaler(address);
    while ((value != Read3ByteScaler(address)) && (i < 5)) {
        value = Read3ByteScaler(address);
        i++;
    }
    return value;
}

/**************************************************************************//**
 * Write 2-bytes to scaler register.
 * @param address ID of scaler register.
 * @param value 2-bytes data.
 ******************************************************************************/
void WriteShortScaler(UCHAR *address, USHRT value)
{
    *address = (UCHAR) value;
    address++;
    *address = (UCHAR) (value>>8);
}

/**************************************************************************//**
 * Write 3-bytes to scaler register.
 * @param address ID of scaler register.
 * @param value 3-bytes data.
 ******************************************************************************/
void Write3ByteScaler(UCHAR *address, ULONG value)
{
    *address = (UCHAR)value;
    address++;
    *address = (UCHAR)(value >> 8);
    address++;
    *address = (UCHAR)(value >> 16);
}

/**************************************************************************//**
 * Write data to index port.
 * @param type Index port type.
 * @param offset Start address.
 * @param len Data size.
 * @param p Pointer to the data.
 ******************************************************************************/
void WriteScalerIndexPort(UCHAR type, USHRT offset, USHRT len, UCHAR *p)
{
    USHRT i;
    ResetWDTimer();
    SC_INDEX_CTRL = type;
    SC_INDEX_ADDR_LO = (UCHAR)offset;
    SC_INDEX_ADDR_HI = (UCHAR)(offset >> 8);
    for (i=0; i<len; i++) {
        SC_INDEX_DATA = p[i];
    }
    ResetWDTimer();          
}

#if ENABLE_OD_3D_MODE == ON
/**************************************************************************//**
 * Write data to index port.
 * This function is available when ENABLE_OD_3D_MODE is enabled.
 * @param type Index port type.
 * @param offset Start address.
 * @param len Data size.
 * @param p Pointer to the data.
 ******************************************************************************/
void WriteScalerIndexPort2(UCHAR type, USHRT offset, USHRT len, UCHAR *p)
{
    USHRT i;

    SC_INDEX_CTRL = type;
    SC_INDEX_ADDR_LO = (UCHAR)offset;
    SC_INDEX_ADDR_HI = (UCHAR)(offset >> 8);
    for (i=0; i<len; i++) {
        SC_INDEX_DATA2 = p[i];
    }
}
#endif
