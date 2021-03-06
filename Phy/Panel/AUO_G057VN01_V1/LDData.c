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

#if ENABLE_LD == ON
//******************************************************************************
// G L O B A L   D E F I N I T I O N S
//******************************************************************************
#define LD_H_ZONES   4
#define LD_V_ZONES   1
#define LD_H_SAMPLES 24
#define LD_V_SAMPLES 17
#define LD_H_BOUND   0x28
#define LD_V_BOUND   0x1C

#define LD_DIM01_DEF 0x04
#define LD_DIM23_DEF 0x0E
#define LD_DIM45_DEF 0x00
#define LD_DIM67_DEF 0x00

//******************************************************************************
// S T A T I C   V A R I A B L E S
//******************************************************************************
static code LDTable LightProfile = {
    { //data2lum 0x01
        0x05, 0x00, 0x1C, 0x00, 0x36, 0x00, 0x58, 0x00, 0x77, 0x00, 0x8E, 0x00, 0xA6, 0x00, 0xC1, 0x00, 
        0xDE, 0x00, 0xFD, 0x00, 0x1D, 0x01, 0x40, 0x01, 0x64, 0x01, 0x8A, 0x01, 0xB2, 0x01, 0xDD, 0x01, 
        0x08, 0x02, 0x36, 0x02, 0x66, 0x02, 0x98, 0x02, 0xCB, 0x02, 0x00, 0x03, 0x54, 0x03, 0xC9, 0x03, 
        0x12, 0x00, 0x28, 0x00, 0x46, 0x00, 0x6C, 0x00, 0x82, 0x00, 0x9A, 0x00, 0xB4, 0x00, 0xCF, 0x00, 
        0xED, 0x00, 0x0D, 0x01, 0x2E, 0x01, 0x52, 0x01, 0x77, 0x01, 0x9E, 0x01, 0xC7, 0x01, 0xF2, 0x01, 
        0x1F, 0x02, 0x4E, 0x02, 0x7F, 0x02, 0xB1, 0x02, 0xE5, 0x02, 0x1C, 0x03, 0x8D, 0x03, 0xFF, 0x03, 
    },
    { //lum2gain 0x02
        0xFF, 0x01, 0x22, 0x01, 0xD4, 0x00, 0xB0, 0x00, 0x9A, 0x00, 0x8B, 0x00, 0x80, 0x00, 0x78, 0x00, 
        0x71, 0x00, 0x6B, 0x00, 0x66, 0x00, 0x61, 0x00, 0x5E, 0x00, 0x5A, 0x00, 0x57, 0x00, 0x55, 0x00, 
        0x52, 0x00, 0x44, 0x00, 0x3C, 0x00, 0x36, 0x00, 0x32, 0x00, 0x2F, 0x00, 0x2C, 0x00, 0x29, 0x00, 
        0x28, 0x00, 0x26, 0x00, 0x24, 0x00, 0x23, 0x00, 0x22, 0x00, 0x21, 0x00, 0x20, 0x00
    },
    { //nonlinear_gain 0x03
        0xFF, 0x01, 0xFF, 0x01, 0xFF, 0x01, 0xFF, 0x01, 0xFF, 0x01, 0xFF, 0x01, 0xB8, 0x01, 0x82, 0x01, 
        0x58, 0x01, 0x37, 0x01, 0x1C, 0x01, 0x06, 0x01, 0xF3, 0x00, 0xE3, 0x00, 0xD5, 0x00, 0xC8, 0x00, 
        0xBE, 0x00, 0x86, 0x00, 0x68, 0x00, 0x56, 0x00, 0x4A, 0x00, 0x40, 0x00, 0x39, 0x00, 0x34, 0x00, 
        0x2F, 0x00, 0x2C, 0x00, 0x28, 0x00, 0x26, 0x00, 0x23, 0x00, 0x21, 0x00, 0x20, 0x00
     },
    { //light profile
0x77, 0x36, 0xf5, 0x00, 0x0b, 0x77, 0x36, 0xf5, 0x00, 0x0b, 0x76, 0x0e, 0x05, 0x81, 0x0d, 
0x63, 0x16, 0x05, 0xc1, 0x11, 0x42, 0x2e, 0x25, 0x01, 0x18, 0x16, 0x62, 0x65, 0xc1, 0x1e, 
0xe6, 0x8d, 0xb5, 0xc1, 0x26, 0xb5, 0xb1, 0x45, 0x82, 0x2e, 0x83, 0xd1, 0x45, 0x03, 0x35, 
0x4e, 0xd5, 0x95, 0xc4, 0x3c, 0x21, 0xb5, 0x25, 0xc6, 0x43, 0xf5, 0x94, 0xe5, 0xc7, 0x49, 
0xd1, 0x5c, 0xd5, 0x89, 0x4e, 0xa9, 0x0c, 0x25, 0x4c, 0x54, 0x85, 0xc0, 0x84, 0x8e, 0x58, 
0x64, 0x50, 0x74, 0x11, 0x5c, 0x4c, 0xe0, 0x43, 0xd4, 0x5d, 0x37, 0x78, 0x43, 0x97, 0x5d, 
0x28, 0xf8, 0x52, 0x1a, 0x5d, 0x1d, 0x80, 0x42, 0x9d, 0x5b, 0x17, 0x08, 0x32, 0xe0, 0x58, 
0x14, 0x94, 0xe1, 0x22, 0x56, 0x11, 0x30, 0xf1, 0xe4, 0x54, 0x10, 0xe4, 0x10, 0x66, 0x55, 
0x10, 0xbc, 0xd0, 0xe5, 0x58, 0x10, 0xbc, 0xd0, 0xe5, 0x58, 0x77, 0x36, 0xf5, 0x00, 0x0b, 
0x77, 0x36, 0xf5, 0x00, 0x0b, 0x76, 0x0e, 0x05, 0x81, 0x0d, 0x63, 0x16, 0x05, 0xc1, 0x11, 
0x42, 0x2e, 0x25, 0x01, 0x18, 0x16, 0x62, 0x65, 0xc1, 0x1e, 0xe6, 0x8d, 0xb5, 0xc1, 0x26, 
0xb5, 0xb1, 0x45, 0x82, 0x2e, 0x83, 0xd1, 0x45, 0x03, 0x35, 0x4e, 0xd5, 0x95, 0xc4, 0x3c, 
0x21, 0xb5, 0x25, 0xc6, 0x43, 0xf5, 0x94, 0xe5, 0xc7, 0x49, 0xd1, 0x5c, 0xd5, 0x89, 0x4e, 
0xa9, 0x0c, 0x25, 0x4c, 0x54, 0x85, 0xc0, 0x84, 0x8e, 0x58, 0x64, 0x50, 0x74, 0x11, 0x5c, 
0x4c, 0xe0, 0x43, 0xd4, 0x5d, 0x37, 0x78, 0x43, 0x97, 0x5d, 0x28, 0xf8, 0x52, 0x1a, 0x5d, 
0x1d, 0x80, 0x42, 0x9d, 0x5b, 0x17, 0x08, 0x32, 0xe0, 0x58, 0x14, 0x94, 0xe1, 0x22, 0x56, 
0x11, 0x30, 0xf1, 0xe4, 0x54, 0x10, 0xe4, 0x10, 0x66, 0x55, 0x10, 0xbc, 0xd0, 0xe5, 0x58, 
0x10, 0xbc, 0xd0, 0xe5, 0x58, 0x89, 0xe6, 0x14, 0x01, 0x0b, 0x89, 0xe6, 0x14, 0x01, 0x0b, 
0x85, 0xda, 0x04, 0x01, 0x0d, 0x74, 0xe6, 0x14, 0x41, 0x10, 0x4b, 0x26, 0x35, 0x01, 0x16, 
0x20, 0x5a, 0x65, 0xc1, 0x1c, 0xf0, 0x95, 0xb5, 0xc1, 0x23, 0xb7, 0xcd, 0x55, 0x02, 0x2c, 
0x7d, 0xf1, 0x25, 0x03, 0x35, 0x4c, 0xfd, 0x35, 0x44, 0x3c, 0x1e, 0xd9, 0xc5, 0xc5, 0x43, 
0xf2, 0xb8, 0x55, 0x87, 0x4a, 0xc8, 0x80, 0x55, 0x89, 0x50, 0x9c, 0x24, 0x05, 0x8c, 0x56, 
0x7d, 0xc0, 0x74, 0xce, 0x5a, 0x5f, 0x4c, 0x44, 0x51, 0x5e, 0x47, 0xd0, 0x43, 0x14, 0x60, 
0x34, 0x60, 0x63, 0x57, 0x5f, 0x27, 0xd8, 0x82, 0x9a, 0x5e, 0x1e, 0x60, 0xc2, 0x5d, 0x5b, 
0x18, 0xe4, 0xb1, 0xe0, 0x58, 0x14, 0x70, 0x91, 0xa3, 0x55, 0x12, 0x1c, 0xd1, 0x65, 0x52, 
0x11, 0xd8, 0x70, 0x67, 0x50, 0x11, 0xb8, 0x20, 0xa7, 0x53, 0x11, 0xb8, 0x20, 0xa7, 0x53, 
0x9e, 0x96, 0x14, 0xc1, 0x0a, 0x9e, 0x96, 0x14, 0xc1, 0x0a, 0x9d, 0x86, 0x14, 0x01, 0x0c, 
0x84, 0xba, 0x24, 0xc1, 0x0e, 0x58, 0x1a, 0x45, 0x41, 0x13, 0x2c, 0x62, 0x65, 0x41, 0x19, 
0xf2, 0xb1, 0xc5, 0x41, 0x21, 0xb7, 0xfd, 0x35, 0x82, 0x29, 0x7f, 0x29, 0xd6, 0x42, 0x32, 
0x4c, 0x39, 0xb6, 0x83, 0x3a, 0x1a, 0x21, 0xf6, 0x84, 0x43, 0xe9, 0xf8, 0xa5, 0x86, 0x4b, 
0xb8, 0xb0, 0xd5, 0x88, 0x53, 0x91, 0x48, 0x55, 0xcb, 0x59, 0x72, 0xd4, 0x14, 0xce, 0x5d, 
0x55, 0x48, 0xf4, 0x50, 0x62, 0x3f, 0xc8, 0x13, 0x54, 0x63, 0x2f, 0x40, 0x33, 0x57, 0x63, 
0x24, 0xa8, 0xa2, 0xda, 0x61, 0x1d, 0x20, 0x32, 0xde, 0x5d, 0x19, 0xb0, 0x71, 0xe1, 0x58, 
0x15, 0x48, 0x71, 0x64, 0x54, 0x13, 0xf8, 0xe0, 0x26, 0x50, 0x12, 0xc4, 0xd0, 0xe8, 0x4b, 
0x12, 0xb8, 0x90, 0xa8, 0x4d, 0x12, 0xb8, 0x90, 0xa8, 0x4d, 0xba, 0x2a, 0x14, 0x81, 0x0a, 
0xba, 0x2a, 0x14, 0x81, 0x0a, 0xb7, 0x2a, 0x24, 0x01, 0x0b, 0x96, 0x8a, 0x24, 0x41, 0x0d, 
0x6a, 0xf6, 0x44, 0x01, 0x11, 0x35, 0x6a, 0x65, 0x81, 0x16, 0xfc, 0xd5, 0xa5, 0x01, 0x1d, 
0xbc, 0x29, 0x06, 0x42, 0x26, 0x84, 0x61, 0x86, 0xc2, 0x2e, 0x49, 0x79, 0x36, 0x43, 0x39, 
0x0f, 0x79, 0x46, 0x84, 0x43, 0xde, 0x44, 0xc6, 0x05, 0x4d, 0xaa, 0xf4, 0xe5, 0x87, 0x56, 
0x83, 0x78, 0x35, 0xca, 0x5e, 0x62, 0xec, 0x04, 0x8d, 0x64, 0x4a, 0x5c, 0x44, 0x90, 0x66, 
0x37, 0xb8, 0x93, 0x53, 0x68, 0x2a, 0x04, 0x73, 0x57, 0x67, 0x22, 0x6c, 0x32, 0xdb, 0x63, 
0x1c, 0xdc, 0xf1, 0x5e, 0x5f, 0x18, 0x74, 0x71, 0xe2, 0x58, 0x15, 0x18, 0xe1, 0xa5, 0x51, 
0x13, 0xdc, 0xa0, 0xe8, 0x4a, 0x13, 0xbc, 0x60, 0xea, 0x45, 0x12, 0xb0, 0xa0, 0xea, 0x45, 
0x12, 0xb0, 0xa0, 0xea, 0x45, 0xdf, 0x9a, 0x13, 0x41, 0x0a, 0xdf, 0x9a, 0x13, 0x41, 0x0a, 
0xd4, 0xc6, 0x23, 0x01, 0x0a, 0xb0, 0x3a, 0x24, 0xc1, 0x0b, 0x7d, 0xd6, 0x44, 0x41, 0x0e, 
0x43, 0x6e, 0x65, 0xc1, 0x12, 0x03, 0xf6, 0x95, 0x81, 0x19, 0xc1, 0x5d, 0xe6, 0x41, 0x22, 
0x84, 0xa9, 0x36, 0x82, 0x2b, 0x41, 0xdd, 0xc6, 0xc2, 0x36, 0x04, 0xd5, 0x96, 0x43, 0x43, 
0xcb, 0x98, 0x16, 0x45, 0x4f, 0x9c, 0x3c, 0xe6, 0x86, 0x59, 0x74, 0xac, 0x55, 0xc9, 0x62, 
0x54, 0x0c, 0x05, 0x0c, 0x6a, 0x3e, 0x54, 0x54, 0xcf, 0x6d, 0x2f, 0x8c, 0x73, 0x93, 0x6d, 
0x25, 0xd0, 0x62, 0x17, 0x6c, 0x1f, 0x30, 0x62, 0x9b, 0x67, 0x1a, 0xa4, 0x71, 0x5f, 0x61, 
0x17, 0x3c, 0x61, 0xe3, 0x58, 0x14, 0xec, 0x10, 0xe7, 0x4f, 0x13, 0xc0, 0x40, 0x2a, 0x46, 
0x12, 0xac, 0x40, 0xac, 0x3f, 0x13, 0xa4, 0xd0, 0xac, 0x3d, 0x13, 0xa4, 0xd0, 0xac, 0x3d, 
0xfe, 0x26, 0x23, 0x81, 0x09, 0xfe, 0x26, 0x23, 0x81, 0x09, 0xf2, 0x5a, 0x13, 0x81, 0x09, 
0xc9, 0xea, 0x13, 0xc1, 0x0a, 0x8f, 0xae, 0x34, 0x81, 0x0c, 0x50, 0x6a, 0x55, 0x01, 0x10, 
0x09, 0x1e, 0x76, 0x01, 0x16, 0xc5, 0x9d, 0xc6, 0xc1, 0x1d, 0x7e, 0x05, 0x17, 0xc2, 0x27, 
0x3a, 0x39, 0x77, 0x02, 0x34, 0xf1, 0x44, 0x37, 0x83, 0x42, 0xb7, 0x0c, 0x37, 0x84, 0x50, 
0x8a, 0x94, 0xf6, 0x45, 0x5c, 0x63, 0xe8, 0x15, 0x48, 0x68, 0x45, 0x08, 0x45, 0x0b, 0x71, 
0x33, 0x30, 0xb4, 0x4e, 0x75, 0x2a, 0x54, 0xd3, 0xd2, 0x74, 0x22, 0x98, 0xf2, 0x16, 0x72, 
0x1d, 0xf8, 0x41, 0x1b, 0x6c, 0x19, 0x6c, 0xc1, 0xdf, 0x63, 0x16, 0x0c, 0x21, 0x24, 0x59, 
0x14, 0xd4, 0x30, 0xe8, 0x4c, 0x13, 0xac, 0xb0, 0xab, 0x41, 0x13, 0xa4, 0x60, 0x6e, 0x37, 
0x13, 0xa0, 0x10, 0xef, 0x34, 0x13, 0xa0, 0x10, 0xef, 0x34, 0x1e, 0xab, 0x22, 0x41, 0x09, 
0x1e, 0xab, 0x22, 0x41, 0x09, 0x0f, 0xef, 0x12, 0x01, 0x09, 0xe2, 0x9a, 0x13, 0x81, 0x09, 
0xa6, 0x6a, 0x24, 0x41, 0x0b, 0x60, 0x56, 0x45, 0x81, 0x0d, 0x15, 0x2e, 0x66, 0x41, 0x12, 
0xc9, 0xe5, 0x96, 0x01, 0x19, 0x78, 0x79, 0xd7, 0x01, 0x23, 0x23, 0xc5, 0x57, 0x82, 0x31, 
0xdf, 0xc0, 0xd7, 0xc2, 0x40, 0xa5, 0x84, 0x97, 0x03, 0x50, 0x7a, 0xe4, 0xf6, 0x44, 0x5f, 
0x56, 0x20, 0x16, 0x07, 0x6c, 0x3c, 0x10, 0xf5, 0x09, 0x78, 0x2e, 0x14, 0x84, 0x0d, 0x7d, 
0x26, 0x1c, 0xa3, 0x11, 0x7e, 0x20, 0x60, 0x42, 0xd6, 0x78, 0x1b, 0xb0, 0x31, 0x5b, 0x71, 
0x18, 0x2c, 0x51, 0xe0, 0x65, 0x15, 0xe4, 0xf0, 0xa4, 0x58, 0x13, 0xb8, 0x90, 0x69, 0x49, 
0x12, 0xa0, 0x40, 0x6d, 0x3c, 0x12, 0x94, 0x30, 0x70, 0x31, 0x13, 0x98, 0x60, 0x31, 0x2c, 
0x13, 0x98, 0x60, 0x31, 0x2c, 0x40, 0x2f, 0x12, 0xc1, 0x08, 0x40, 0x2f, 0x12, 0xc1, 0x08, 
0x27, 0x97, 0x02, 0xc1, 0x08, 0xfe, 0x36, 0x03, 0x01, 0x09, 0xbf, 0x16, 0x14, 0x81, 0x0a, 
0x70, 0x2e, 0x25, 0x81, 0x0c, 0x1f, 0x42, 0x46, 0x01, 0x0f, 0xc8, 0x25, 0x87, 0x81, 0x15, 
0x68, 0xe5, 0xc7, 0x81, 0x20, 0x14, 0x51, 0x18, 0x82, 0x2d, 0xcc, 0x58, 0x98, 0x02, 0x3d, 
0x90, 0x04, 0x28, 0x03, 0x4f, 0x64, 0x50, 0x07, 0xc4, 0x61, 0x46, 0x34, 0x16, 0xc6, 0x72, 
0x35, 0x0c, 0xb5, 0x08, 0x7f, 0x2a, 0xe0, 0x33, 0x8c, 0x86, 0x23, 0xe4, 0x82, 0xd0, 0x86, 
0x1d, 0x08, 0x62, 0x95, 0x82, 0x1a, 0x6c, 0x21, 0x1b, 0x76, 0x16, 0x04, 0xa1, 0xa0, 0x67, 
0x14, 0xc8, 0xd0, 0x25, 0x57, 0x13, 0xa8, 0xe0, 0x2a, 0x45, 0x12, 0x98, 0xe0, 0x6e, 0x36, 
0x12, 0x90, 0x10, 0x32, 0x2a, 0x13, 0x90, 0xa0, 0xb3, 0x23, 0x13, 0x90, 0xa0, 0xb3, 0x23, 
0x5b, 0xcb, 0x11, 0x41, 0x08, 0x5b, 0xcb, 0x11, 0x41, 0x08, 0x45, 0x2b, 0x02, 0x01, 0x08, 
0x13, 0xef, 0x02, 0x41, 0x08, 0xd3, 0xda, 0x13, 0x41, 0x09, 0x7c, 0x16, 0x35, 0xc1, 0x0a, 
0x20, 0x5a, 0x46, 0x41, 0x0d, 0xbb, 0x91, 0x67, 0x81, 0x12, 0x57, 0x8d, 0xa8, 0xc1, 0x1a, 
0xfa, 0x1c, 0xf9, 0xc1, 0x27, 0xb5, 0x08, 0x59, 0xc2, 0x38, 0x7a, 0x94, 0xd8, 0xc2, 0x4c, 
0x50, 0x98, 0x97, 0x03, 0x64, 0x3c, 0x48, 0xe6, 0xc4, 0x78, 0x2f, 0xf0, 0x64, 0x87, 0x87, 
0x26, 0xa8, 0xa3, 0x4a, 0x91, 0x20, 0xa0, 0x22, 0x4f, 0x91, 0x1c, 0xc0, 0x81, 0xd4, 0x8a, 
0x17, 0x28, 0x51, 0x5b, 0x7a, 0x15, 0xdc, 0x90, 0xa1, 0x66, 0x13, 0xb4, 0x80, 0xe7, 0x51, 
0x12, 0xa0, 0x50, 0x2c, 0x40, 0x11, 0x90, 0xa0, 0x30, 0x30, 0x12, 0x84, 0xd0, 0xf3, 0x23, 
0x12, 0x88, 0x40, 0xf5, 0x1d, 0x12, 0x88, 0x40, 0xf5, 0x1d, 0x6c, 0x8f, 0x11, 0xc1, 0x07, 
0x6c, 0x8f, 0x11, 0xc1, 0x07, 0x5f, 0xc7, 0x01, 0xc1, 0x07, 0x34, 0x73, 0x02, 0xc1, 0x07, 
0xf1, 0x72, 0x03, 0x81, 0x08, 0x98, 0xba, 0x14, 0x01, 0x0a, 0x2c, 0x42, 0x26, 0x41, 0x0c, 
0xb9, 0xcd, 0x67, 0x41, 0x0f, 0x4a, 0x15, 0x89, 0x01, 0x16, 0xe7, 0xc8, 0xd9, 0x41, 0x22, 
0x9a, 0xdc, 0x39, 0xc2, 0x32, 0x61, 0x18, 0xa9, 0x82, 0x4b, 0x46, 0xdc, 0x37, 0xc3, 0x63, 
0x36, 0x48, 0x36, 0x04, 0x7d, 0x2c, 0xc8, 0x14, 0x06, 0x90, 0x24, 0x6c, 0x03, 0x09, 0x9c, 
0x1e, 0x24, 0x22, 0x8e, 0x9d, 0x1a, 0x68, 0xf1, 0x13, 0x93, 0x17, 0xf8, 0xd0, 0x5a, 0x7f, 
0x14, 0xcc, 0x00, 0x22, 0x66, 0x13, 0xa4, 0xc0, 0xe8, 0x4d, 0x11, 0x94, 0x60, 0xee, 0x38, 
0x12, 0x88, 0x60, 0x72, 0x29, 0x12, 0x84, 0x40, 0x35, 0x1e, 0x12, 0x84, 0x60, 0xb6, 0x19, 
0x12, 0x84, 0x60, 0xb6, 0x19, 0x77, 0x67, 0x11, 0x81, 0x07, 0x77, 0x67, 0x11, 0x81, 0x07, 
0x71, 0x87, 0x01, 0x41, 0x07, 0x50, 0x0b, 0xf2, 0x80, 0x07, 0x0e, 0x07, 0xf3, 0x40, 0x08, 
0xb0, 0x66, 0x14, 0x41, 0x09, 0x35, 0x32, 0x36, 0xc1, 0x0a, 0xb3, 0x09, 0x48, 0x81, 0x0d, 
0x37, 0xa5, 0x79, 0x01, 0x12, 0xcc, 0xa4, 0xba, 0xc1, 0x1b, 0x7a, 0xb0, 0x1a, 0x02, 0x2e, 
0x52, 0xb4, 0x69, 0x82, 0x46, 0x3d, 0x2c, 0xf8, 0x02, 0x62, 0x30, 0x54, 0xa6, 0x03, 0x80, 
0x28, 0x88, 0xc4, 0x44, 0x9a, 0x22, 0xe8, 0xc2, 0xc7, 0xa9, 0x1d, 0xd0, 0x41, 0x8c, 0xaa, 
0x19, 0x28, 0x81, 0x12, 0x9d, 0x15, 0xe0, 0x30, 0xda, 0x83, 0x14, 0xb8, 0x80, 0x62, 0x65, 
0x12, 0x98, 0x40, 0xea, 0x48, 0x11, 0x84, 0x50, 0x30, 0x32, 0x11, 0x80, 0x90, 0x74, 0x21, 
0x11, 0x80, 0x90, 0x76, 0x19, 0x12, 0x80, 0xf0, 0xb6, 0x17, 0x12, 0x80, 0xf0, 0xb6, 0x17, 
0x7c, 0x4f, 0x11, 0xc1, 0x07, 0x7c, 0x4f, 0x11, 0xc1, 0x07, 0x7e, 0x53, 0x01, 0x41, 0x07, 
0x6e, 0x9f, 0xf1, 0xc0, 0x06, 0x34, 0x77, 0xf2, 0xc0, 0x07, 0xcf, 0xf6, 0x03, 0xc1, 0x08, 
0x49, 0xf6, 0x15, 0x01, 0x0a, 0xab, 0x45, 0x38, 0x01, 0x0c, 0x1f, 0x35, 0x6a, 0x41, 0x0f, 
0xa4, 0x98, 0xbb, 0x81, 0x16, 0x60, 0xa0, 0xeb, 0x41, 0x26, 0x46, 0x70, 0x3a, 0x82, 0x3e, 
0x36, 0x70, 0xb8, 0x82, 0x60, 0x2c, 0x48, 0x46, 0x43, 0x83, 0x25, 0xf4, 0x23, 0xc4, 0xa6, 
0x1f, 0x60, 0xe2, 0x85, 0xba, 0x1b, 0x74, 0x41, 0xca, 0xb8, 0x18, 0xfc, 0xd0, 0xd0, 0xa6, 
0x15, 0xcc, 0x40, 0xd9, 0x88, 0x13, 0xac, 0xe0, 0xe2, 0x64, 0x11, 0x90, 0xd0, 0x6b, 0x43, 
0x10, 0x80, 0xa0, 0x72, 0x29, 0x10, 0x78, 0x70, 0xb6, 0x1a, 0x11, 0x78, 0xa0, 0xb7, 0x15, 
0x12, 0x80, 0x80, 0x77, 0x15, 0x12, 0x80, 0x80, 0x77, 0x15, 0x87, 0x2b, 0x11, 0x41, 0x07, 
0x87, 0x2b, 0x11, 0x41, 0x07, 0x8b, 0x2b, 0xf1, 0xc0, 0x06, 0x82, 0x53, 0xe1, 0xc0, 0x06, 
0x54, 0x03, 0xf2, 0x00, 0x07, 0xf5, 0x6e, 0x03, 0xc1, 0x07, 0x49, 0xfe, 0x15, 0x81, 0x09, 
0x8f, 0xc5, 0x38, 0x01, 0x0b, 0xed, 0x14, 0x6b, 0xc1, 0x0d, 0x80, 0x7c, 0x9c, 0xc1, 0x11, 
0x4f, 0x80, 0xbc, 0x41, 0x1d, 0x3c, 0x28, 0x0b, 0x42, 0x36, 0x32, 0xd4, 0x78, 0x42, 0x5c, 
0x29, 0xdc, 0x05, 0xc3, 0x8b, 0x22, 0x74, 0xb3, 0x43, 0xb1, 0x1d, 0xdc, 0xc1, 0xc4, 0xc7, 
0x1a, 0x24, 0xd1, 0xc7, 0xc7, 0x16, 0xe0, 0x40, 0x4e, 0xb3, 0x14, 0xb8, 0x40, 0x58, 0x8e, 
0x12, 0x9c, 0xf0, 0xe3, 0x61, 0x11, 0x8c, 0x20, 0x6e, 0x3a, 0x10, 0x78, 0x00, 0x75, 0x20, 
0x10, 0x74, 0xc0, 0xb7, 0x15, 0x10, 0x70, 0x50, 0xb8, 0x13, 0x11, 0x78, 0x40, 0x38, 0x13, 
0x11, 0x78, 0x40, 0x38, 0x13, 0x91, 0x0f, 0x01, 0xc1, 0x06, 0x91, 0x0f, 0x01, 0xc1, 0x06, 
0x96, 0x0b, 0xe1, 0x40, 0x06, 0x90, 0x23, 0xe1, 0x40, 0x06, 0x77, 0x7f, 0xe1, 0xc0, 0x06, 
0x1d, 0xd7, 0xf2, 0x80, 0x07, 0x64, 0xa2, 0x05, 0xc1, 0x08, 0x7a, 0x2d, 0x29, 0x01, 0x0a, 
0xc4, 0xdc, 0x4b, 0x01, 0x0c, 0x60, 0x2c, 0x7d, 0x41, 0x0f, 0x44, 0x30, 0xbd, 0x01, 0x15, 
0x36, 0x10, 0xfc, 0x81, 0x29, 0x2d, 0x18, 0x49, 0x02, 0x5a, 0x25, 0x94, 0xb5, 0x82, 0x92, 
0x1f, 0xc4, 0x52, 0x83, 0xbe, 0x1c, 0x60, 0x21, 0x44, 0xd2, 0x18, 0x00, 0xd1, 0x85, 0xd2, 
0x15, 0xc8, 0x40, 0x0b, 0xc1, 0x12, 0xa8, 0xa0, 0x56, 0x96, 0x11, 0x90, 0x30, 0xe5, 0x5d, 
0x11, 0x80, 0xe0, 0x30, 0x30, 0x0f, 0x74, 0x20, 0x77, 0x18, 0x0e, 0x6c, 0xb0, 0xf8, 0x12, 
0x0f, 0x68, 0x20, 0x39, 0x11, 0x11, 0x74, 0xc0, 0x78, 0x11, 0x11, 0x74, 0xc0, 0x78, 0x11, 
0x92, 0x07, 0x01, 0x01, 0x07, 0x92, 0x07, 0x01, 0x01, 0x07, 0x9f, 0xef, 0xe0, 0xc0, 0x05, 
0x9a, 0x03, 0xd1, 0x00, 0x06, 0x88, 0x3f, 0xe1, 0x80, 0x06, 0x56, 0xf7, 0xf1, 0x40, 0x07, 
0x91, 0xfa, 0x04, 0x01, 0x08, 0x58, 0xc5, 0x19, 0x41, 0x09, 0x8a, 0xd8, 0x3c, 0x01, 0x0b, 
0x4f, 0x8c, 0x6d, 0xc1, 0x0d, 0x3d, 0x90, 0x9d, 0x41, 0x11, 0x31, 0xe8, 0xdc, 0xc1, 0x1d, 
0x2a, 0xc8, 0x29, 0x42, 0x50, 0x23, 0x1c, 0x85, 0x42, 0x9b, 0x1e, 0xe8, 0x11, 0x83, 0xcd, 
0x1b, 0x18, 0xb1, 0xc3, 0xd8, 0x18, 0xe4, 0xa0, 0x04, 0xd9, 0x15, 0xb8, 0xd0, 0xc7, 0xcf, 
0x12, 0x9c, 0x00, 0x94, 0xa1, 0x11, 0x88, 0xa0, 0xa7, 0x54, 0x10, 0x80, 0x70, 0x34, 0x22, 
0x0f, 0x70, 0x20, 0xb8, 0x14, 0x0e, 0x68, 0x30, 0x39, 0x11, 0x0e, 0x64, 0xb0, 0x79, 0x0f, 
0x11, 0x6c, 0x10, 0xb9, 0x10, 0x11, 0x6c, 0x10, 0xb9, 0x10, 0x95, 0xff, 0x00, 0xc1, 0x06, 
0x95, 0xff, 0x00, 0xc1, 0x06, 0xa2, 0xe7, 0xd0, 0xc0, 0x05, 0x9d, 0xf7, 0xd0, 0x00, 0x06, 
0x90, 0x1f, 0xe1, 0x80, 0x06, 0x7d, 0x63, 0xe1, 0x00, 0x07, 0xe4, 0xb2, 0x03, 0xc1, 0x07, 
0x1e, 0xb5, 0x1a, 0xc1, 0x08, 0x60, 0x88, 0x3d, 0x81, 0x0a, 0x47, 0xc8, 0x5d, 0x41, 0x0c, 
0x38, 0xbc, 0x9d, 0xc1, 0x0f, 0x2e, 0x8c, 0xcd, 0x81, 0x14, 0x28, 0x00, 0x0b, 0xc2, 0x3d, 
0x22, 0x2c, 0x64, 0x02, 0xab, 0x1e, 0x54, 0xd1, 0xc2, 0xd7, 0x19, 0xfc, 0x60, 0x43, 0xdc, 
0x17, 0xd0, 0x30, 0x44, 0xdc, 0x14, 0xb0, 0x70, 0x05, 0xda, 0x12, 0x94, 0x40, 0x0f, 0xb5, 
0x11, 0x84, 0x20, 0xec, 0x42, 0x10, 0x7c, 0x20, 0xb7, 0x17, 0x0f, 0x6c, 0xb0, 0xb8, 0x12, 
0x0e, 0x64, 0x80, 0x39, 0x10, 0x0e, 0x64, 0xf0, 0x79, 0x0e, 0x11, 0x70, 0x50, 0x79, 0x0f, 
0x11, 0x70, 0x50, 0x79, 0x0f, 0x9d, 0xe7, 0xf0, 0x80, 0x06, 0x9d, 0xe7, 0xf0, 0x80, 0x06, 
0xa1, 0xe3, 0xe0, 0x00, 0x06, 0x9e, 0xf3, 0xe0, 0xc0, 0x05, 0x94, 0x0f, 0xe1, 0x80, 0x06, 
0x85, 0x3f, 0xf1, 0x00, 0x07, 0x3c, 0x4f, 0x02, 0x01, 0x08, 0x8d, 0xf0, 0x2c, 0x01, 0x09, 
0x52, 0xc4, 0x3d, 0x41, 0x0a, 0x42, 0xe0, 0x5d, 0x01, 0x0c, 0x36, 0xd8, 0x8d, 0xc1, 0x0e, 
0x2d, 0xc8, 0xbd, 0x41, 0x11, 0x27, 0xa4, 0x0c, 0xc2, 0x23, 0x22, 0x6c, 0x52, 0x42, 0xc7, 
0x1d, 0x24, 0xb1, 0x82, 0xdb, 0x19, 0xec, 0x30, 0x03, 0xde, 0x17, 0xd0, 0xf0, 0x43, 0xdd, 
0x13, 0xac, 0xc0, 0x44, 0xdd, 0x12, 0x94, 0x40, 0x08, 0xd1, 0x11, 0x84, 0x70, 0xb3, 0x25, 
0x10, 0x7c, 0xd0, 0xf7, 0x14, 0x10, 0x6c, 0xd0, 0xf8, 0x11, 0x0f, 0x68, 0x90, 0x79, 0x0f, 
0x0f, 0x64, 0xe0, 0x79, 0x0e, 0x10, 0x68, 0xc0, 0x79, 0x0e, 0x10, 0x68, 0xc0, 0x79, 0x0e, 
0x9d, 0xe7, 0xf0, 0x80, 0x06, 0x9d, 0xe7, 0xf0, 0x80, 0x06, 0xa1, 0xe3, 0xe0, 0x00, 0x06, 
0x9e, 0xf3, 0xe0, 0xc0, 0x05, 0x94, 0x0f, 0xe1, 0x80, 0x06, 0x85, 0x3f, 0xf1, 0x00, 0x07, 
0x3c, 0x4f, 0x02, 0x01, 0x08, 0x8d, 0xf0, 0x2c, 0x01, 0x09, 0x52, 0xc4, 0x3d, 0x41, 0x0a, 
0x42, 0xe0, 0x5d, 0x01, 0x0c, 0x36, 0xd8, 0x8d, 0xc1, 0x0e, 0x2d, 0xc8, 0xbd, 0x41, 0x11, 
0x27, 0xa4, 0x0c, 0xc2, 0x23, 0x22, 0x6c, 0x52, 0x42, 0xc7, 0x1d, 0x24, 0xb1, 0x82, 0xdb, 
0x19, 0xec, 0x30, 0x03, 0xde, 0x17, 0xd0, 0xf0, 0x43, 0xdd, 0x13, 0xac, 0xc0, 0x44, 0xdd, 
0x12, 0x94, 0x40, 0x08, 0xd1, 0x11, 0x84, 0x70, 0xb3, 0x25, 0x10, 0x7c, 0xd0, 0xf7, 0x14, 
0x10, 0x6c, 0xd0, 0xf8, 0x11, 0x0f, 0x68, 0x90, 0x79, 0x0f, 0x0f, 0x64, 0xe0, 0x79, 0x0e, 
0x10, 0x68, 0xc0, 0x79, 0x0e, 0x10, 0x68, 0xc0, 0x79, 0x0e, 
    }      
};

#endif //ENABLE_LD == ON
