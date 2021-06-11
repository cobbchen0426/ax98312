



#include "Include.h"


static code UCHAR _Default_VGA_EDID[128]={
	0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x3A,0xD4,0x5A,0x66,0x01,0x00,0x00,0x00,
	0x03,0x16,0x01,0x03,0x0E,0x5D,0x34,0x78,0xEA,0x63,0x95,0xA1,0x54,0x52,0x9E,0x26,
	0x0A,0x50,0x54,0xA3,0x08,0x00,0x81,0x80,0xD1,0xC0,0xB3,0x00,0x01,0x01,0x01,0x01,
	0x01,0x01,0x01,0x01,0x01,0x01,0x02,0x3A,0x80,0x18,0x71,0x38,0x2D,0x40,0x58,0x2C,
	0x45,0x00,0xA2,0x0B,0x32,0x00,0x00,0x1E,0x66,0x21,0x50,0xB0,0x51,0x00,0x1B,0x30,
	0x40,0x70,0x36,0x00,0xA2,0x0B,0x32,0x00,0x00,0x1E,0x00,0x00,0x00,0xFD,0x00,0x32,
	0x41,0x1E,0x64,0x16,0x00,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x00,0x00,0xFC,
	0x00,0x54,0x55,0x53,0x20,0x4C,0x34,0x32,0x58,0x58,0x58,0x0A,0x0A,0x0A,0x00,0xF6,
	};
	
static code UCHAR _Default_DVI_EDID[128]={
   	0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x12,0xC9,0x20,0x19,0x00,0x00,0x00,0x00, 
	0x29,0x12,0x01,0x03,0x80,0x2F,0x1A,0x78,0xE8,0xC7,0x20,0xA4,0x55,0x49,0x99,0x27, 
	0x13,0x50,0x54,0xAB,0x88,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01, 
	0x01,0x01,0x01,0x01,0x01,0x01,0x1A,0x36,0x80,0xA0,0x70,0x38,0x1F,0x40,0x30,0x20, 
	0x36,0x00,0xD9,0x28,0x11,0x00,0x00,0x1A,0x00,0x00,0x00,0xFD,0x00,0x38,0x4C,0x2F, 
	0x44,0x10,0x00,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x66,0x21,0x56,0xAA,0x51,0x00, 
	0x1E,0x30,0x46,0x8F,0x33,0x00,0xBA,0x88,0x21,0x00,0x00,0x1E,0x7C,0x2E,0x90,0xA0, 
	0x60,0x1A,0x1E,0x40,0x30,0x20,0x36,0x00,0xD9,0x28,0x11,0x00,0x00,0x1A,0x00,0x9D, 
};

static code UCHAR _Default_HDMI_EDID[256]={

    /*	0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x3A,0xD4,0x5A,0x66,0x01,0x00,0x00,0x00,
    	0x03,0x16,0x01,0x03,0x80,0x5D,0x34,0x78,0xEF,0x63,0x95,0xA1,0x54,0x52,0x9E,0x26,
    	0x0A,0x50,0x54,0xA3,0x08,0x00,0x81,0x80,0xD1,0xC0,0xB3,0x00,0x01,0x01,0x01,0x01,
    	0x01,0x01,0x01,0x01,0x01,0x01,0x02,0x3A,0x80,0x18,0x71,0x38,0x2D,0x40,0x58,0x2C,
    	0x45,0x00,0xBA,0x89,0x21,0x00,0x00,0x1E,0x66,0x21,0x50,0xB0,0x51,0x00,0x1B,0x30,
    	0x40,0x70,0x36,0x00,0xBA,0x89,0x21,0x00,0x00,0x1E,0x00,0x00,0x00,0xFD,0x00,0x32,
    	0x41,0x1E,0x64,0x16,0x00,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x00,0x00,0xFC,
    	0x00,0x54,0x55,0x53,0x20,0x4C,0x34,0x32,0x58,0x58,0x58,0x0A,0x0A,0x0A,0x00,0x75,*/

//Source
//   	0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x20,0x8D,0x20,0x19,0x00,0x00,0x00,0x00, 
//	0x29,0x12,0x01,0x03,0x80,0x2F,0x1A,0x78,0xE8,0xC7,0x20,0xA4,0x55,0x49,0x99,0x27, 
//	0x13,0x50,0x54,0xAB,0x88,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01, 
//	0x01,0x01,0x01,0x01,0x01,0x01,0x1A,0x36,0x80,0xA0,0x70,0x38,0x1F,0x40,0x30,0x20, 
//	0x36,0x00,0xD9,0x28,0x11,0x00,0x00,0x1A,0x00,0x00,0x00,0xFD,0x00,0x38,0x4C,0x2F, 
//	0x44,0x10,0x00,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x66,0x21,0x56,0xAA,0x51,0x00, 
//	0x1E,0x30,0x46,0x8F,0x33,0x00,0xBA,0x88,0x21,0x00,0x00,0x1E,0x7C,0x2E,0x90,0xA0, 
//	0x60,0x1A,0x1E,0x40,0x30,0x20,0x36,0x00,0xD9,0x28,0x11,0x00,0x00,0x1A,0x00,0xCB, 
//    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

//1920x1080, include-Audio
0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x20,0x8D,0x20,0x19,0x00,0x00,0x00,0x00,
0x29,0x12,0x01,0x03,0x80,0x2F,0x1A,0x78,0xEA,0xC7,0x20,0xA4,0x55,0x49,0x99,0x27,
0x13,0x50,0x54,0xAB,0x88,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
0x01,0x01,0x01,0x01,0x01,0x01,0x1A,0x36,0x80,0xA0,0x70,0x38,0x1F,0x40,0x30,0x20,
0x36,0x00,0xD9,0x28,0x11,0x00,0x00,0x1A,0x00,0x00,0x00,0xFD,0x00,0x38,0x4C,0x2F,
0x44,0x10,0x00,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x66,0x21,0x56,0xAA,0x51,0x00,
0x1E,0x30,0x46,0x8F,0x33,0x00,0xBA,0x88,0x21,0x00,0x00,0x1E,0x7C,0x2E,0x90,0xA0,
0x60,0x1A,0x1E,0x40,0x30,0x20,0x36,0x00,0xD9,0x28,0x11,0x00,0x00,0x1A,0x01,0xC8,
0x02,0x03,0x22,0xF1,0x4F,0x90,0x05,0x04,0x03,0x02,0x01,0x11,0x12,0x13,0x14,0x06,
0x07,0x15,0x16,0x1F,0x23,0x09,0x07,0x07,0x65,0x03,0x0C,0x00,0x10,0x00,0x83,0x01,
0x00,0x00,0x02,0x3A,0x80,0x18,0x71,0x38,0x2D,0x40,0x58,0x2C,0x45,0x00,0x13,0x2B,
0x21,0x00,0x00,0x1F,0x01,0x1D,0x80,0x18,0x71,0x1C,0x16,0x20,0x58,0x2C,0x25,0x00,
0x13,0x2B,0x21,0x00,0x00,0x9F,0x01,0x1D,0x00,0x72,0x51,0xD0,0x1E,0x20,0x6E,0x28,
0x55,0x00,0x13,0x2B,0x21,0x00,0x00,0x1E,0x8C,0x0A,0xD0,0x8A,0x20,0xE0,0x2D,0x10,
0x10,0x3E,0x96,0x00,0x13,0x2B,0x21,0x00,0x00,0x18,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE7,



/*
    0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x09, 0xD1, 0x25, 0x78, 0x45, 0x54, 0x00, 0x00,                               
    0x24, 0x12, 0x01, 0x03, 0x80, 0x35, 0x1E, 0x78, 0x2E, 0x60, 0x81, 0xA6, 0x56, 0x4A, 0x9C, 0x25,                               
    0x12, 0x50, 0x54, 0xA5, 0x6B, 0x80, 0x71, 0x00, 0x81, 0xC0, 0x81, 0x40, 0x81, 0x80, 0xA9, 0xC0,                               
    0xB3, 0x00, 0xD1, 0xC0, 0x01, 0x01, 0x02, 0x3A, 0x80, 0x18, 0x71, 0x38, 0x2D, 0x40, 0x58, 0x2C,                               
    0x45, 0x00, 0x13, 0x2B, 0x21, 0x00, 0x00, 0x1A, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x30, 0x30, 0x30,                               
    0x30, 0x30, 0x30, 0x30, 0x30, 0x53, 0x4C, 0x30, 0x0A, 0x20, 0x00, 0x00, 0x00, 0xFD, 0x00, 0x32,                               
    0x4C, 0x18, 0x53, 0x11, 0x00, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0xFC,                               
    0x00, 0x42, 0x65, 0x6E, 0x51, 0x20, 0x45, 0x57, 0x32, 0x34, 0x33, 0x30, 0x0A, 0x20, 0x01, 0x7B,                               
    0x02, 0x03, 0x22, 0xF1, 0x4F, 0x90, 0x05, 0x04, 0x03, 0x02, 0x01, 0x11, 0x12, 0x13, 0x14, 0x06,                               
    0x07, 0x15, 0x16, 0x1F, 0x23, 0x09, 0x07, 0x07, 0x65, 0x03, 0x0C, 0x00, 0x10, 0x00, 0x83, 0x01,                               
    0x00, 0x00, 0x02, 0x3A, 0x80, 0x18, 0x71, 0x38, 0x2D, 0x40, 0x58, 0x2C, 0x45, 0x00, 0x13, 0x2B,                               
    0x21, 0x00, 0x00, 0x1F, 0x01, 0x1D, 0x80, 0x18, 0x71, 0x1C, 0x16, 0x20, 0x58, 0x2C, 0x25, 0x00,                               
    0x13, 0x2B, 0x21, 0x00, 0x00, 0x9F, 0x01, 0x1D, 0x00, 0x72, 0x51, 0xD0, 0x1E, 0x20, 0x6E, 0x28,                               
    0x55, 0x00, 0x13, 0x2B, 0x21, 0x00, 0x00, 0x1E, 0x8C, 0x0A, 0xD0, 0x8A, 0x20, 0xE0, 0x2D, 0x10,                               
    0x10, 0x3E, 0x96, 0x00, 0x13, 0x2B, 0x21, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                               
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE7,
*/
};

//DISPLAYPORT EDID
static code UCHAR _Default_DP_EDID[]={ 

   	      /*0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x3A, 0xD4, 0x5A, 0x66, 0x01, 0x00, 0x00, 0x00, 
		0x03, 0x16, 0x01, 0x04, 0xA5, 0x5D, 0x34, 0x78, 0xEF, 0x63, 0x95, 0xA1, 0x54, 0x52, 0x9E, 0x26, 
		0x0A, 0x50, 0x54, 0xA3, 0x08, 0x00, 0x81, 0x80, 0xD1, 0xC0, 0xB3, 0x00, 0x01, 0x01, 0x01, 0x01, 
		0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x3A, 0x80, 0x18, 0x71, 0x38, 0x2D, 0x40, 0x58, 0x2C, 
		0x45, 0x00, 0xBA, 0x89, 0x21, 0x00, 0x00, 0x1E, 0x66, 0x21, 0x50, 0xB0, 0x51, 0x00, 0x1B, 0x30, 
		0x40, 0x70, 0x36, 0x00, 0xBA, 0x89, 0x21, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0xFD, 0x00, 0x32, 
		0x41, 0x1E, 0x64, 0x16, 0x00, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0xFC, 
		0x00, 0x54, 0x55, 0x53, 0x20, 0x4C, 0x34, 0x32, 0x58, 0x58, 0x58, 0x0A, 0x0A, 0x0A, 0x01, 0x4E, */

   		0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x12,0x70,0x20,0x19,0x00,0x00,0x00,0x00, 
		0x29,0x12,0x01,0x03,0x80,0x2F,0x1A,0x78,0xE8,0xC7,0x20,0xA4,0x55,0x49,0x99,0x27, 
		0x13,0x50,0x54,0xAB,0x88,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01, 
		0x01,0x01,0x01,0x01,0x01,0x01,0x1A,0x36,0x80,0xA0,0x70,0x38,0x1F,0x40,0x30,0x20, 
		0x36,0x00,0xD9,0x28,0x11,0x00,0x00,0x1A,0x00,0x00,0x00,0xFD,0x00,0x38,0x4C,0x2F, 
		0x44,0x10,0x00,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x66,0x21,0x56,0xAA,0x51,0x00, 
		0x1E,0x30,0x46,0x8F,0x33,0x00,0xBA,0x88,0x21,0x00,0x00,0x1E,0x7C,0x2E,0x90,0xA0, 
		0x60,0x1A,0x1E,0x40,0x30,0x20,0x36,0x00,0xD9,0x28,0x11,0x00,0x00,0x1A,0x00,0xF6, 

	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  
};

