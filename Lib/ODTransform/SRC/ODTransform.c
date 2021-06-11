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
#include "ODTransform.h"
#include "ScalerReg.h"
#include "McuAPI.h"

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
// E X T E R N A L   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************

/**************************************************************************//**
 * Write OD table from transformed OD data.
 * This function is available when ENABLE_OD_TRANSFORM is enabled.
 * @param type Index port type.
 * @param p Pointer to the data.
 * @param b3Dtype TRUE to write 3D type OD data. FALSE to 2D type.
 ******************************************************************************/
 void WriteODTransformData(unsigned char type, unsigned char *ptr, bit b3Dtype)	  
{
    unsigned short i, k, table_index;
    unsigned char xdata *index_data_ptr;
    
    index_data_ptr = &SC_INDEX_DATA;
    if (b3Dtype == 1) {
        index_data_ptr++; //SC_INDEX_DATA2
    }
    
    SC_INDEX_CTRL = type;
    SC_INDEX_ADDR_LO = 0;
    SC_INDEX_ADDR_HI = 0;

    for (k=0; k<256; k++) {

        if (k < 240) {
            i = k / 16;
            table_index = i + k;

            *index_data_ptr = ptr[table_index]+ptr[table_index+18]-ptr[table_index+1]-ptr[table_index+17];
            *index_data_ptr = ptr[table_index+1] - ptr[table_index];
            *index_data_ptr = ptr[table_index+17] - ptr[table_index];
            *index_data_ptr = ptr[table_index];
        }
        else {
            table_index = 15 + k;
            *index_data_ptr = ptr[table_index] - ptr[table_index+1];
            *index_data_ptr = ptr[table_index+1] - ptr[table_index];
            *index_data_ptr = 0x00 - ptr[table_index];
            *index_data_ptr = ptr[table_index];
        }
        ResetWDTimer();      
    }
}