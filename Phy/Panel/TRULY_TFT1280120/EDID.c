



#include "Include.h"                                                                                                              
                                                                                                                                  
                                                                                                                                  
static code UCHAR _Default_VGA_EDID[128]={                                                                 //1280X800 george                                                                                        
//1280x720@?
/* 0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x58,0xE1,0x80,0x12,0x00,0x00,0x00,0x00,
0x23,0x19,0x01,0x03,0x00,0x16,0x0E,0x78,0xE2,0x65,0x05,0x94,0x56,0x53,0x8F,0x27,
0x20,0x50,0x54,0x21,0x08,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
0x01,0x01,0x01,0x01,0x01,0x01,0xBC,0x1B,0x00,0xA0,0x50,0x20,0x17,0x30,0x30,0x20,
0x36,0x00,0xD9,0x87,0x00,0x00,0x00,0x1A,0x00,0x00,0x00,0xFD,0x00,0x3C,0x3C,0x1E,
0x32,0x08,0x00,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x00,0x00,0xFE,0x00,0x41,
0x44,0x53,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x0A,0x00,0x00,0x00,0xFE,
0x00,0x47,0x31,0x30,0x31,0x45,0x56,0x4E,0x30,0x31,0x2E,0x30,0x20,0x0A,0x00,0xB5,  */

//1280x120@50
/* 0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x58,0xE1,0x11,0x12,0x00,0x00,0x00,0x00,
0x21,0x11,0x01,0x03,0x0E,0x18,0x12,0x78,0xE8,0x9A,0xE5,0xA6,0x58,0x49,0x99,0x23,
0x11,0x50,0x54,0xAF,0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
0x01,0x01,0x01,0x01,0x01,0x01,0x08,0x07,0x00,0x8C,0x50,0x78,0x84,0x00,0x39,0x1D,
0xBF,0x00,0xF5,0xB9,0x00,0x00,0x00,0x18,0x00,0x00,0x00,0xFD,0x00,0x28,0x50,0x0C,
0x14,0x03,0x00,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x00,0x00,0xFF,0x00,0x30,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFC,
0x00,0x54,0x52,0x55,0x4C,0x59,0x20,0x31,0x32,0x38,0x30,0x20,0x20,0x0A,0x00,0xC2, */

//1280x480@30
0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x58,0xE1,0x11,0x12,0x00,0x00,0x00,0x00,
0x21,0x11,0x01,0x03,0x0E,0x18,0x12,0x78,0xE8,0x9A,0xE5,0xA6,0x58,0x49,0x99,0x23,
0x11,0x50,0x54,0xAF,0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
0x01,0x01,0x01,0x01,0x01,0x01,0xC6,0x08,0x00,0xA0,0x50,0xE0,0x28,0x10,0x28,0x28,
0x86,0x04,0xF5,0xB9,0x00,0x00,0x00,0x18,0x00,0x00,0x00,0xFD,0x00,0x14,0x50,0x0C,
0x14,0x05,0x00,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x00,0x00,0xFF,0x00,0x30,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFC,
0x00,0x54,0x52,0x55,0x4C,0x59,0x20,0x31,0x32,0x38,0x30,0x5F,0x33,0x20,0x00,0xB8,
        };                                                                                                                        
                                                                                                                                  
static code UCHAR _Default_DVI_EDID[128]={                                                                 //1280X800 george       

//1280x480@30
0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x12,0xC9,0x80,0x12,0x00,0x00,0x00,0x00,
0x23,0x19,0x01,0x03,0x80,0x16,0x0E,0x78,0xE2,0x65,0x05,0x94,0x56,0x53,0x8F,0x27,
0x20,0x50,0x54,0x21,0x08,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
0x01,0x01,0x01,0x01,0x01,0x01,0xC6,0x08,0x00,0xA0,0x50,0xE0,0x28,0x10,0x28,0x28,
0x86,0x04,0xD9,0x87,0x00,0x00,0x00,0x1C,0x00,0x00,0x00,0xFD,0x00,0x14,0x50,0x0C,
0x14,0x05,0x00,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x00,0x00,0xFE,0x00,0x44,
0x56,0x49,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x0A,0x00,0x00,0x00,0xFE,
0x00,0x54,0x52,0x55,0x4C,0x59,0x20,0x31,0x32,0x38,0x30,0x20,0x44,0x0A,0x00,0x83,

// 1280x800  
/* 0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x12,0xC9,0x80,0x12,0x00,0x00,0x00,0x00,
0x23,0x19,0x01,0x03,0x80,0x16,0x0E,0x78,0xE2,0x65,0x05,0x94,0x56,0x53,0x8F,0x27,
0x20,0x50,0x54,0x21,0x08,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
0x01,0x01,0x01,0x01,0x01,0x01,0xBC,0x1B,0x00,0xA0,0x50,0x20,0x17,0x30,0x30,0x20,
0x36,0x00,0xD9,0x87,0x00,0x00,0x00,0x1A,0x00,0x00,0x00,0xFD,0x00,0x3C,0x3C,0x1E,
0x32,0x08,0x00,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x00,0x00,0xFE,0x00,0x44,
0x56,0x49,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x0A,0x00,0x00,0x00,0xFE,
0x00,0x47,0x31,0x30,0x31,0x45,0x56,0x4E,0x30,0x31,0x2E,0x30,0x20,0x0A,0x00,0x88,   */

//1280x768@60
/* 0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x12,0xC9,0x80,0x12,0x00,0x00,0x00,0x00,
0x23,0x19,0x01,0x03,0x80,0x16,0x0E,0x78,0xE2,0x65,0x05,0x94,0x56,0x53,0x8F,0x27,
0x20,0x50,0x54,0x21,0x08,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
0x01,0x01,0x01,0x01,0x01,0x01,0xA9,0x1A,0x00,0x80,0x51,0x00,0x1E,0x30,0x40,0x80,
0x37,0x00,0xD9,0x87,0x00,0x00,0x00,0x1A,0x00,0x00,0x00,0xFD,0x00,0x3B,0x4B,0x1E,
0x3E,0x0B,0x00,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x00,0x00,0xFE,0x00,0x44,
0x56,0x49,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x0A,0x00,0x00,0x00,0xFE,
0x00,0x47,0x31,0x30,0x31,0x45,0x56,0x4E,0x30,0x31,0x2E,0x30,0x20,0x0A,0x00,0x46,
*/

//1280x720@60
/* 0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x12,0xC9,0x80,0x12,0x00,0x00,0x00,0x00,
0x23,0x19,0x01,0x03,0x80,0x16,0x0E,0x78,0xE2,0x65,0x05,0x94,0x56,0x53,0x8F,0x27,
0x20,0x50,0x54,0x21,0x08,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x19,0x00,0xA0,0x50,0xD0,0x15,0x20,0x30,0x20,
0x25,0x00,0xD9,0x87,0x00,0x00,0x00,0x1A,0x00,0x00,0x00,0xFD,0x00,0x3B,0x3C,0x1E,
0x32,0x08,0x00,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x00,0x00,0xFE,0x00,0x44,
0x56,0x49,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x0A,0x00,0x00,0x00,0xFE,
0x00,0x47,0x31,0x30,0x31,0x45,0x56,0x4E,0x30,0x31,0x2E,0x30,0x20,0x0A,0x00,0xBA,
*/

//1280x720@50
/* 0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x12,0xC9,0x80,0x12,0x00,0x00,0x00,0x00,
0x23,0x19,0x01,0x03,0x80,0x16,0x0E,0x78,0xE2,0x65,0x05,0x94,0x56,0x53,0x8F,0x27,
0x20,0x50,0x54,0x21,0x08,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
0x01,0x01,0x01,0x01,0x01,0x01,0xA2,0x17,0x00,0x60,0x51,0xD0,0x18,0x20,0x30,0x80,
0x3A,0x00,0xD9,0x87,0x00,0x00,0x00,0x18,0x00,0x00,0x00,0xFD,0x00,0x3B,0x3C,0x1E,
0x37,0x08,0x00,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x00,0x00,0xFE,0x00,0x44,
0x56,0x49,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x0A,0x00,0x00,0x00,0xFE,
0x00,0x47,0x31,0x30,0x31,0x45,0x56,0x4E,0x30,0x31,0x2E,0x30,0x20,0x0A,0x00,0xDE,  */

//1280x120@50
/* 0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x12,0xC9,0x80,0x12,0x00,0x00,0x00,0x00,
0x23,0x19,0x01,0x03,0x80,0x16,0x0E,0x78,0xE2,0x65,0x05,0x94,0x56,0x53,0x8F,0x27,
0x20,0x50,0x54,0x21,0x08,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
0x01,0x01,0x01,0x01,0x01,0x01,0x08,0x07,0x00,0x8C,0x50,0x78,0x84,0x00,0x39,0x1D,
0xBF,0x00,0xD9,0x87,0x00,0x00,0x00,0x1C,0x00,0x00,0x00,0xFD,0x00,0x28,0x50,0x0C,
0x14,0x03,0x00,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x00,0x00,0xFE,0x00,0x44,
0x56,0x49,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x0A,0x00,0x00,0x00,0xFE,
0x00,0x54,0x52,0x55,0x4C,0x59,0x20,0x31,0x32,0x38,0x30,0x20,0x44,0x0A,0x00,0x25, */

};                                                                                                                                
                                                                                                                                  
static code UCHAR _Default_HDMI_EDID[256]={                                                                 //1024X768 mike      
0X00,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X00,0X21,0XA9,0X24,0X10,0X00,0X00,0X00,0X00, 
0X14,0X18,0X01,0X03,0X80,0X1F,0X17,0X78,0XEA,0X9A,0XE5,0XA6,0X58,0X49,0X99,0X23, 
0X11,0X50,0X54,0XBD,0XCE,0X00,0X01,0X01,0X01,0X01,0X01,0X01,0X01,0X01,0X01,0X01, 
0X01,0X01,0X01,0X01,0X01,0X01,0X64,0X19,0X00,0X40,0X41,0X00,0X26,0X30,0X18,0X88, 
0X36,0X00,0X30,0XE4,0X10,0X00,0X00,0X18,0X00,0X00,0X00,0XFD,0X00,0X38,0X4C,0X1F, 
0X3E,0X08,0X00,0X0A,0X20,0X20,0X20,0X20,0X20,0X20,0X00,0X00,0X00,0XFF,0X00,0X30, 
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XFC, 
0X00,0X31,0X30,0X32,0X34,0X78,0X37,0X36,0X38,0X20,0X20,0X20,0X20,0X0A,0X01,0X3E,                                          
	0x02,0x03,0x22,0xF1,0x4F,0x90,0x05,0x04,0x03,0x02,0x01,0x11,0x12,0x13,0x14,0x06,
	0x07,0x15,0x16,0x1F,0x23,0x09,0x07,0x07,0x65,0x03,0x0C,0x00,0x10,0x00,0x83,0x01,
	0x00,0x00,0x02,0x3A,0x80,0x18,0x71,0x38,0x2D,0x40,0x58,0x2C,0x45,0x00,0x13,0x2B,
	0x21,0x00,0x00,0x1F,0x01,0x1D,0x80,0x18,0x71,0x1C,0x16,0x20,0x58,0x2C,0x25,0x00,
	0x13,0x2B,0x21,0x00,0x00,0x9F,0x01,0x1D,0x00,0x72,0x51,0xD0,0x1E,0x20,0x6E,0x28,
	0x55,0x00,0x13,0x2B,0x21,0x00,0x00,0x1E,0x8C,0x0A,0xD0,0x8A,0x20,0xE0,0x2D,0x10,
	0x10,0x3E,0x96,0x00,0x13,0x2B,0x21,0x00,0x00,0x18,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE7,

};                                                                                                                                
                                                                                                                                  
//DISPLAYPORT EDID                                                                                                                
static code UCHAR _Default_DP_EDID[]={                                                                      //1024X768 mike      
0X00,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X00,0X12,0X70,0X24,0X10,0X00,0X00,0X00,0X00, 
0X14,0X18,0X01,0X03,0X80,0X1F,0X17,0X78,0XEA,0X9A,0XE5,0XA6,0X58,0X49,0X99,0X23, 
0X11,0X50,0X54,0XBD,0XCE,0X00,0X01,0X01,0X01,0X01,0X01,0X01,0X01,0X01,0X01,0X01, 
0X01,0X01,0X01,0X01,0X01,0X01,0X64,0X19,0X00,0X40,0X41,0X00,0X26,0X30,0X18,0X88, 
0X36,0X00,0X30,0XE4,0X10,0X00,0X00,0X18,0X00,0X00,0X00,0XFD,0X00,0X38,0X4C,0X1F, 
0X3E,0X08,0X00,0X0A,0X20,0X20,0X20,0X20,0X20,0X20,0X00,0X00,0X00,0XFF,0X00,0X30, 
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XFC, 
0X00,0X31,0X30,0X32,0X34,0X78,0X37,0X36,0X38,0X20,0X20,0X20,0X20,0X0A,0X01,0X86,                                          
        0x02, 0x03, 0x13, 0xF0, 0x83, 0x01, 0x00, 0x00, 0x23, 0x09, 0x07, 0x07, 0x46, 0x90, 0x1F, 0x03,                           
        0x12, 0x14, 0x05, 0x02, 0x3A, 0x80, 0x18, 0x71, 0x38, 0x2D, 0x40, 0x58, 0x2C, 0x45, 0x00, 0xDD,                           
        0x0C, 0x11, 0x00, 0x00, 0x1A, 0x8C, 0x0A, 0xD0, 0x8A, 0x20, 0xE0, 0x2D, 0x10, 0x10, 0x3E, 0x96,                           
        0x00, 0xDD, 0x0C, 0x11, 0x00, 0x00, 0x18, 0x8C, 0x0A, 0xD0, 0x90, 0x20, 0x40, 0x31, 0x20, 0x0C,                           
        0x40, 0x55, 0x00, 0xDD, 0x0C, 0x11, 0x00, 0x00, 0x18, 0x02, 0x3A, 0x80, 0xD0, 0x72, 0x38, 0x2D,                           
        0x40, 0x10, 0x2C, 0x45, 0x80, 0xDD, 0x0C, 0x11, 0x00, 0x00, 0x1A, 0x01, 0x1D, 0x80, 0xD0, 0x72,                           
        0x1C, 0x16, 0x20, 0x2C, 0x10, 0x25, 0x20, 0xDD, 0x0C, 0x11, 0x00, 0x00, 0x9E, 0x01, 0x1D, 0x80,                           
        0x18, 0x71, 0x1C, 0x16, 0x20, 0x58, 0x2C, 0x25, 0x00, 0xDD, 0x0C, 0x11, 0x00, 0x00, 0x9E, 0x16,                           
};                                                                                                                                
                                                                                                                                  