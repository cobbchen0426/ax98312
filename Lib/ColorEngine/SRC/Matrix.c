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
#include "ScalerReg.h"
#include "ScalerAccess.h"
#include "Matrix.h"
#include "stdio.h"

//******************************************************************************
// M A C R O   D E F I N I T I O N S
//******************************************************************************
/*!
 * 3x3 Matrix API Version.
 * The following string is the specific string for EasyWriter.
 * We can show the version on EasyWriter.
 */
static code UCHAR SpecTab_MTXVersion[] = {
    0x55, 0xaa, 0x66, 0x99, __FILE__" Version 3.0.00 "__DATE__"#"
};

/*!
 * Option to select how to achieve contrast adjustment by 3x3 matrix.
 * If LINEAR_RGB is defined, the MTXAPI_SetContrast provides the simple multiplication of R/G/B gain.
 * If not defined, MTXAPI_SetContrast will do color space transformation to achieve contrast adjustment.
 */
#define LINEAR_RGB

#define IsLocalMatrixAccess()  ((ucMtxCfg & BIT0) == BIT0)
#define IsGlobalMatrixAccess() ((ucMtxCfg & BIT0) == 0)

#define IsLocalMatrixEnabled()  ((ucMtxCfg & BIT1) == BIT1)

#define SetAccessMatrixType(a) {ucMtxCfg = (ucMtxCfg & 0xFE) | ((a & BIT0) ? BIT0 : 0x00);}
#define SetEnabledMatrixType(a) {ucMtxCfg = (ucMtxCfg & 0xFD) | ((a & BIT0) ? BIT1 : 0x00);}

//******************************************************************************
// G L O B A L   V A R I A B L E S
//******************************************************************************

//******************************************************************************
// S T A T I C   V A R I A B L E S
//******************************************************************************
#ifdef LINEAR_RGB
/*!
 * Default R/G/B gain.
 */
static code int iDefaultTab[3][3] = {
    {  0x1000,  0x0000,  0x0000 },
    {  0x0000,  0x1000,  0x0000 },
    {  0x0000,  0x0000,  0x1000 } 
};
#else
/*!
 *  Matrix for RGB to YUV transformation.
 */
static code int iRGB2YUV[3][3] = {
    {  0x041B,  0x0810,  0x0191 },
    { -0x025F, -0x04A7,  0x0707 },
    {  0x0707, -0x05E2, -0x0124 } 
};

/*!
 *  Matrix for YUV to RGB transformation.
 */
static code int iYUV2RGB[3][3] = {
    {  0x12A1,  0x0000,  0x1989 }, 
    {  0x12A1, -0x0644, -0x0D01 }, 
    {  0x12A1,  0x2046,  0x0000 }
};

/*!
 *  Values of sine/cosine transformation.
 */
static code int iSinCosTab[65] = {
    0x0000,0x0064,0x00C9,0x012D,0x0191,0x01F5,0x0259,0x02BC,0x031F,0x0381,
    0x03E3,0x0444,0x04A5,0x0505,0x0564,0x05C2,0x061F,0x067B,0x06D7,0x0731,
    0x078A,0x07E3,0x083A,0x088F,0x08E3,0x0937,0x0988,0x09D8,0x0A26,0x0A73,
    0x0ABF,0x0B08,0x0B50,0x0B97,0x0BDB,0x0C1E,0x0C5E,0x0C9D,0x0CDA,0x0D15,
    0x0D4D,0x0D85,0x0DB9,0x0DEC,0x0E1C,0x0E4B,0x0E77,0x0EA1,0x0EC8,0x0EEE,
    0x0F10,0x0F31,0x0F4F,0x0F6C,0x0F85,0x0F9C,0x0FB1,0x0FC4,0x0FD4,0x0FE1,
    0x0FEC,0x0FF5,0x0FFB,0x0FFE,0x1000
};
#endif

static USHRT usMtxGain[3] = {0x100,0x100,0x100}; /*!< The preset R/G/B gain values. */
static UCHAR ucMtxOffset[3] = {0x80,0x80,0x80};  /*!< The preset R/G/B offset valuse. */
static UCHAR ucMtxCn = 0x80;  /*!< The preset contrast value. */
static UCHAR ucMtxCfg = 0;    /*!< The status of local/global matrix. */
#ifndef LINEAR_RGB
static UCHAR ucMtxSat = 0x80; /*!< The preset saturation value. */
static UCHAR ucMtxHue = 0x00; /*!< The preset hue value. */
#endif

//******************************************************************************
// E X T E R N A L   V A R I A B L E   P R O T O T Y P E S
//******************************************************************************

//******************************************************************************
// S T A T I C   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
#ifndef LINEAR_RGB
static int Sine(UCHAR alpha);
static int Cosine(UCHAR alpha);
static void Product(int *first, int * second, int *result);
#endif

//******************************************************************************
// E X T E R N A L   F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
extern void WaitDisVSync(void);

//******************************************************************************
// F U N C T I O N   B O D Y S
//******************************************************************************

#ifndef LINEAR_RGB
/**************************************************************************//**
 * Get the value of sine(a).
 * @return Value of sine(a).
 ******************************************************************************/
static int Sine(UCHAR alpha)
{
    UCHAR value = alpha & 0x3f;
    switch(alpha & 0xC0) {
        case 0x00:
            return(iSinCosTab[value]);
            break;
        case 0x40:
            return(iSinCosTab[(64 - value)]);
            break;
        case 0x80:
            return(-iSinCosTab[value]);
            break;
        case 0xC0:
        default :
            return(-iSinCosTab[(64 - value)]);
            break;
    }
}

/**************************************************************************//**
 * Get the value of cosine(a).
 * @return Value of cosine(a).
 ******************************************************************************/
static int Cosine(UCHAR alpha)
{
    return (Sine(alpha + 64));
}

/**************************************************************************//**
 * Function for matrix multiplication.
 *   C = A x B
 * @param frist Pointer to the 3x3 matrix.
 * @param second Pointer to the 3x3 matrix.
 * @param[out] result Pointer to the output buffer.
 ******************************************************************************/
static void Product(int *first, int *second, int *result)
{
    UCHAR i,j,k;
    long res;
    for( i=0;i<3;i++){
        for( j=0;j<3;j++) {
            res = 0;
            for( k=0;k<3;k++) {
                res += (long)*(first + i*3 + k) * (long)*(second + k*3 + j);
            }
            *(result + i*3 + j) = ((res + 2048)>>12);
        }
    }
}
#endif

/**************************************************************************//**
 * Set contrast variable and no update to scaler.
 * The bypass point is 128.
 * @param cn The value of contrast.
 ******************************************************************************/
void MTXAPI_SetContrastValue(UCHAR cn)
{
    ucMtxCn = cn;
}

/**************************************************************************//**
 * Set contrast variable and update scaler immediately.
 * The bypass point is 128.
 * @param cn The value of contrast.
 ******************************************************************************/
void MTXAPI_SetContrast(UCHAR cn)
{
    UCHAR i,j;
    int temp;
    int result[3][3];

    #ifndef LINEAR_RGB
    int adjust[3][3];
    int UVrotated[3][3];
    #endif
    
    //ucMtxCn = cn;
    MTXAPI_SetContrastValue(cn);
    
    #ifdef LINEAR_RGB
    for(i=0; i<3; i++) {
        for(j=0; j<3; j++) {
            result[i][j] = iDefaultTab[i][j];
        }
    }

    result[0][0] = (int)((float)result[0][0] * cn / 128 + 0.5);
    result[1][1] = (int)((float)result[1][1] * cn / 128 + 0.5);
    result[2][2] = (int)((float)result[2][2] * cn / 128 + 0.5);
    #else
    for(i=0; i<3; i++) {
        UVrotated[i][0] = 0;
    }
    for(i=0; i<3; i++) {
        UVrotated[0][i] = 0;
    }
    
    UVrotated[1][1] = (((((long)ucMtxSat<<5) * (long)Cosine(ucMtxHue))+2048)>>12);
    UVrotated[1][2] = (((((long)ucMtxSat<<5) * (long)Sine(ucMtxHue))+2048)>>12);
    UVrotated[2][1] = (((-(long)Sine(ucMtxHue)*((long)ucMtxSat<<5))+2048)>>12);
    UVrotated[2][2] = ((( (long)Cosine(ucMtxHue)*((long)ucMtxSat<<5))+2048)>>12);

    Product(&UVrotated[0][0], &iRGB2YUV[0][0], &adjust[0][0]);

    for(i=0; i<3; i++) {
        adjust[0][i] =((((long)iRGB2YUV[0][i]*((long)cn << 5))+2048)>>12);
    }
    Product(&iYUV2RGB[0][0],&adjust[0][0],&result[0][0]);
    #endif

    if (IsLocalMatrixAccess()) 
	{
       	 SC_SRGB_CTRL |= BIT6;
    	}
    else 
	{
        	SC_SRGB_CTRL &= ~BIT6;
    	}
    if (IsLocalMatrixEnabled()) 
	{
       	 SC_SRGB_CTRL |= BIT7;
    	}
    else 
	{
       	 SC_SRGB_CTRL &= ~BIT7;
    	}
    		SC_SRGB_CTRL |= BIT0;

    for(i=0; i<3; i++) 
	{
        	SC_SRGB_CTRL = (SC_SRGB_CTRL & 0xF1) | (i * 2);
           for(j=0; j<3; j++)
		{
            		temp = (((((long) (result[i][j] + 8) >> 4) * ((long) usMtxGain[i] << 4)) + 2048) >> 12);
            if (temp < 0) 
			{
               		temp = temp ^ 0xffff;
                		temp += 1;
                		temp |= 0xf400;
            		}
           	 WriteShortScaler((&SC_SRGB_COEF_R_LO + (j * 2)), temp);
        	}
    	}

    WaitDisVSync();
    SC_SRGB_CTRL |= BIT3;
}

/**************************************************************************//**
 * Set the gain of red color and update scaler immediately.
 * The bypass point is 256.
 * @param gn The value of gain. Range is 0~512.
 ******************************************************************************/
void MTXAPI_SetRGain(USHRT gn)
{
    usMtxGain[0] = gn;
    MTXAPI_SetContrast(ucMtxCn);
}

/**************************************************************************//**
 * Set the gain of green color and update scaler immediately.
 * The bypass point is 256.
 * @param gn The value of gain. Range is 0~512.
 ******************************************************************************/
void MTXAPI_SetGGain(USHRT gn)
{
    usMtxGain[1] = gn;
    MTXAPI_SetContrast(ucMtxCn);
}

/**************************************************************************//**
 * Set the gain of blue color and update scaler immediately.
 * The bypass point is 256.
 * @param gn The value of gain. Range is 0~512.
 ******************************************************************************/
void MTXAPI_SetBGain(USHRT gn)
{
    usMtxGain[2] = gn;
    MTXAPI_SetContrast(ucMtxCn);
}

/**************************************************************************//**
 * Set the gains of R/G/B color and no update to scaler.
 * The bypass point is 255.
 * @param r The value of red gain. Range is 0~255.
 * @param g The value of green gain. Range is 0~255.
 * @param b The value of blue gain. Range is 0~255.
 ******************************************************************************/
void MTXAPI_SetRGBGainValue(USHRT r,USHRT g,USHRT b)
{
    usMtxGain[0] = r;
    usMtxGain[1] = g;
    usMtxGain[2] = b;
}

/**************************************************************************//**
 * Set the gains of R/G/B color and update scaler immediately.
 * The bypass point is 255.
 * @param r The value of red gain. Range is 0~255.
 * @param g The value of green gain. Range is 0~255.
 * @param b The value of blue gain. Range is 0~255.
 ******************************************************************************/
void MTXAPI_SetRGBGain(USHRT r,USHRT g,USHRT b)
{
    MTXAPI_SetRGBGainValue(r, g, b);
    MTXAPI_SetContrast(ucMtxCn);
}

/**************************************************************************//**
 * Set the offset of red color and update scaler immediately.
 * The bypass point is 128.
 * @param off The value of offset. Range is 0~255.
 ******************************************************************************/
void MTXAPI_SetROffset(UCHAR off)
{
    ucMtxOffset[0] = off;
    MTXAPI_SetRGBOffset(off, ucMtxOffset[1],ucMtxOffset[2]);
}

/**************************************************************************//**
 * Set the offset of green color and update scaler immediately.
 * The bypass point is 128.
 * @param off The value of offset. Range is 0~255.
 ******************************************************************************/
void MTXAPI_SetGOffset(UCHAR off)
{
    ucMtxOffset[1] = off;
    MTXAPI_SetRGBOffset(ucMtxOffset[0], off, ucMtxOffset[2]);
}

/**************************************************************************//**
 * Set the offset of blue color and update scaler immediately.
 * The bypass point is 128.
 * @param off The value of offset. Range is 0~255.
 ******************************************************************************/
void MTXAPI_SetBOffset(UCHAR off)
{
    ucMtxOffset[2] = off;
    MTXAPI_SetRGBOffset(ucMtxOffset[0], ucMtxOffset[1], off);
}

/**************************************************************************//**
 * Set the offsets of R/G/B color and no update to scaler.
 * The bypass point is 128.
 * @param r The value of red offset. Range is 0~255.
 * @param g The value of green offset. Range is 0~255.
 * @param b The value of blue offset. Range is 0~255.
 ******************************************************************************/
void MTXAPI_SetRGBOffsetValue(UCHAR r, UCHAR g, UCHAR b)
{
    ucMtxOffset[0] = r;
    ucMtxOffset[1] = g;
    ucMtxOffset[2] = b;    
}

/**************************************************************************//**
 * Set the offsets of R/G/B color and update scaler immediately.
 * The bypass point is 128.
 * @param r The value of red offset. Range is 0~255.
 * @param g The value of green offset. Range is 0~255.
 * @param b The value of blue offset. Range is 0~255.
 ******************************************************************************/
void MTXAPI_SetRGBOffset(UCHAR r, UCHAR g, UCHAR b)
{
    UCHAR i;

    MTXAPI_SetRGBOffsetValue(r, g, b);
    
    for(i=0; i<3; i++) {
        SC_SRGB_CTRL = (SC_SRGB_CTRL&0xB0) | (i*2) | BIT0;
        SC_SRGB_COEF_OFFSET = ucMtxOffset[i];
    }
    
    SC_SRGB_CTRL |= BIT3;
}

#ifndef LINEAR_RGB
/**************************************************************************//**
 * Set saturation and update scaler immediately.
 * The bypass point is 128.
 * @param sa The value of saturation. Range is 0~255.
 ******************************************************************************/
void MTXAPI_SetSat(UCHAR sa)
{
    ucMtxSat = sa;
    MTXAPI_SetContrast(ucMtxCn);
}

/**************************************************************************//**
 * Set hue and update scaler immediately.
 * The bypass point is 128.
 * @param hue The value of hue. Range is 0~255.
 ******************************************************************************/
void MTXAPI_SetHue(UCHAR hu)
{
    ucMtxHue = hu;
    MTXAPI_SetContrast(ucMtxCn);    
}
#endif

/**************************************************************************//**
 * Select which matrix to be accessed.
 * @param type MTX_GLOBAL or MTX_LOCAL
 ******************************************************************************/
void MTXAPI_SelMatrix(MTXType type)
{
    if (type < NUM_MTX_TYPE) {
        SetAccessMatrixType(type);
    }
}

/**************************************************************************//**
 * Enable/disable local matrix.
 * @param en TRUE to enable local matrix else FALSE.
 ******************************************************************************/
void MTXAPI_EnableLocalMatrix(UCHAR en)
{
    if (en) {
        SetEnabledMatrixType(MTX_LOCAL);
        SC_SRGB_CTRL |= BIT7;
    }
    else {
        SetEnabledMatrixType(MTX_GLOBAL);
	SC_SRGB_CTRL &= ~BIT7;
    }
}
