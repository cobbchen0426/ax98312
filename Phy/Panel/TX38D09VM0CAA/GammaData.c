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

#if ENABLE_GAMMA == ON



static code Gamma320 GammaTabls[GAMMA_TOTAL_STEP] = { 

//1.9
{
//Red Channel
{
64, 0, 0, 0, 18, 88, 19, 20, 22, 23, 226, 24, 26, 27, 28, 16, 30, 31, 32, 33, 
48, 34, 35, 35, 37, 105, 38, 39, 40, 41, 21, 42, 43, 44, 45, 192, 46, 47, 48, 48, 
90, 49, 50, 51, 52, 27, 52, 53, 54, 55, 175, 55, 56, 57, 58, 181, 59, 60, 60, 61, 
44, 62, 62, 63, 64, 149, 65, 66, 67, 68, 83, 69, 71, 72, 73, 233, 74, 75, 76, 77, 
3, 78, 80, 81, 82, 80, 83, 84, 85, 86, 254, 87, 88, 89, 90, 252, 92, 92, 93, 94, 
79, 95, 96, 98, 99, 106, 100, 101, 102, 103, 62, 104, 105, 106, 108, 249, 109, 110, 111, 112, 
170, 113, 114, 115, 116, 67, 117, 119, 120, 121, 62, 122, 123, 124, 126, 180, 127, 128, 128, 129, 
109, 130, 130, 131, 132, 240, 133, 134, 134, 135, 22, 136, 137, 138, 139, 172, 140, 140, 141, 142, 
197, 143, 144, 145, 145, 134, 146, 147, 148, 148, 97, 149, 150, 150, 151, 175, 151, 152, 153, 154, 
21, 155, 156, 157, 158, 252, 159, 159, 160, 161, 107, 162, 163, 164, 165, 108, 166, 166, 167, 168, 
85, 169, 170, 171, 172, 172, 173, 173, 174, 175, 85, 176, 177, 178, 179, 5, 180, 181, 182, 183, 
175, 183, 184, 185, 186, 5, 187, 188, 189, 190, 108, 191, 191, 192, 193, 108, 194, 194, 195, 196, 
108, 197, 197, 198, 199, 24, 200, 200, 201, 202, 198, 202, 203, 204, 204, 177, 205, 206, 206, 207, 
177, 208, 209, 209, 210, 177, 211, 212, 212, 213, 177, 214, 215, 215, 216, 86, 217, 218, 219, 220, 
108, 221, 221, 222, 223, 108, 224, 224, 225, 226, 188, 227, 227, 228, 229, 193, 230, 231, 232, 232, 
171, 233, 234, 235, 236, 193, 237, 238, 239, 239, 63, 240, 241, 242, 244, 37, 245, 246, 247, 255, 
},

//Green Channel
{
0, 0, 0, 0, 18, 217, 18, 20, 22, 22, 68, 25, 26, 27, 29, 29, 30, 30, 33, 34, 
242, 34, 35, 36, 37, 106, 38, 40, 41, 42, 22, 42, 44, 45, 46, 2, 46, 48, 49, 50, 
109, 50, 50, 52, 53, 52, 54, 54, 54, 56, 220, 57, 57, 58, 58, 70, 60, 61, 62, 62, 
98, 62, 64, 64, 65, 237, 66, 66, 68, 69, 102, 70, 72, 73, 74, 143, 74, 76, 78, 78, 
213, 80, 81, 82, 82, 25, 84, 85, 86, 88, 96, 89, 90, 90, 92, 33, 93, 94, 94, 96, 
240, 97, 98, 98, 100, 247, 101, 102, 102, 104, 155, 105, 106, 108, 109, 1, 110, 111, 113, 114, 
50, 114, 115, 116, 118, 102, 118, 120, 121, 122, 192, 124, 125, 126, 126, 74, 128, 129, 130, 130, 
179, 130, 132, 132, 133, 9, 134, 134, 136, 137, 119, 137, 138, 138, 140, 225, 141, 142, 142, 142, 
138, 144, 145, 146, 146, 219, 146, 148, 149, 149, 121, 150, 150, 150, 152, 240, 153, 154, 154, 155, 
106, 156, 157, 158, 159, 5, 160, 161, 162, 163, 172, 164, 164, 165, 166, 177, 167, 168, 168, 169, 
170, 170, 171, 172, 173, 177, 174, 175, 175, 176, 170, 177, 178, 179, 180, 22, 181, 182, 183, 184, 
188, 185, 185, 186, 187, 90, 188, 189, 190, 191, 177, 192, 193, 193, 194, 97, 195, 196, 196, 197, 
108, 198, 198, 199, 200, 44, 201, 201, 202, 203, 203, 203, 204, 205, 205, 6, 206, 207, 208, 209, 
27, 209, 210, 211, 212, 27, 212, 213, 214, 215, 23, 215, 216, 217, 218, 188, 219, 219, 220, 221, 
197, 222, 223, 224, 224, 198, 225, 226, 227, 227, 6, 228, 229, 230, 231, 91, 231, 232, 233, 234, 
192, 235, 236, 237, 237, 22, 238, 239, 240, 241, 64, 242, 243, 244, 245, 41, 246, 247, 248, 255, 
},

//Blue Channel
{
128, 0, 0, 0, 21, 96, 22, 23, 24, 25, 14, 26, 27, 29, 30, 22, 31, 32, 33, 34, 
51, 34, 36, 36, 38, 25, 39, 40, 41, 42, 0, 43, 44, 45, 46, 176, 47, 48, 48, 49, 
197, 50, 51, 52, 52, 246, 53, 54, 54, 55, 86, 56, 57, 58, 59, 28, 60, 60, 61, 62, 
7, 62, 63, 64, 65, 229, 66, 67, 68, 69, 148, 71, 72, 73, 74, 254, 75, 76, 77, 78, 
0, 80, 81, 82, 83, 229, 84, 85, 86, 87, 3, 88, 90, 91, 92, 240, 93, 94, 94, 95, 
164, 97, 98, 99, 100, 234, 101, 102, 103, 104, 164, 106, 107, 108, 109, 3, 110, 112, 113, 114, 
76, 115, 115, 117, 118, 58, 119, 120, 121, 123, 229, 124, 125, 126, 127, 134, 128, 129, 130, 130, 
241, 131, 132, 132, 133, 22, 134, 135, 136, 137, 188, 138, 138, 139, 140, 22, 141, 142, 143, 144, 
27, 144, 145, 146, 147, 216, 148, 148, 149, 149, 246, 150, 151, 151, 152, 106, 153, 154, 155, 156, 
21, 157, 158, 159, 160, 240, 161, 162, 162, 163, 27, 164, 165, 166, 167, 255, 167, 168, 169, 170, 
91, 171, 172, 173, 174, 60, 175, 175, 176, 178, 240, 179, 180, 180, 181, 90, 182, 183, 184, 185, 
1, 186, 187, 188, 189, 192, 190, 191, 192, 192, 178, 193, 194, 194, 195, 177, 196, 197, 197, 198, 
177, 199, 200, 200, 201, 109, 202, 202, 203, 204, 28, 205, 205, 206, 207, 27, 207, 208, 209, 210, 
47, 210, 211, 212, 213, 27, 213, 214, 215, 216, 188, 217, 217, 218, 219, 198, 220, 221, 222, 222, 
198, 223, 224, 225, 225, 198, 226, 227, 228, 228, 198, 229, 230, 231, 231, 26, 232, 233, 234, 235, 
108, 236, 236, 237, 238, 107, 238, 239, 240, 241, 1, 242, 243, 244, 245, 63, 245, 246, 247, 255, 
},

},
//1.9

//2.0
{
//Red Channel
{
192, 0, 0, 0, 17, 246, 18, 19, 20, 21, 167, 22, 24, 25, 26, 76, 28, 28, 30, 31, 
177, 32, 33, 33, 34, 166, 35, 36, 37, 38, 111, 39, 40, 41, 42, 193, 43, 44, 45, 45, 
111, 46, 47, 48, 49, 188, 50, 50, 51, 52, 108, 53, 53, 54, 55, 172, 56, 56, 57, 58, 
181, 59, 60, 60, 61, 24, 62, 62, 63, 64, 64, 65, 66, 67, 68, 249, 69, 70, 71, 72, 
3, 73, 75, 76, 77, 165, 78, 79, 80, 81, 234, 82, 83, 84, 85, 67, 86, 88, 89, 90, 
21, 91, 92, 93, 94, 64, 95, 96, 97, 98, 174, 99, 100, 101, 102, 14, 103, 104, 106, 107, 
57, 108, 109, 110, 112, 252, 113, 113, 114, 115, 147, 116, 118, 119, 120, 14, 121, 122, 124, 125, 
41, 126, 127, 128, 129, 203, 129, 130, 131, 131, 90, 132, 133, 134, 135, 188, 136, 136, 137, 138, 
22, 139, 140, 141, 142, 108, 143, 143, 144, 145, 177, 146, 147, 147, 148, 28, 149, 149, 150, 151, 
107, 151, 152, 153, 154, 5, 155, 156, 157, 158, 252, 159, 159, 160, 161, 111, 162, 163, 164, 165, 
172, 166, 166, 167, 168, 170, 169, 170, 171, 172, 193, 173, 174, 175, 175, 15, 176, 177, 179, 180, 
175, 180, 181, 182, 183, 86, 184, 185, 186, 187, 0, 188, 189, 190, 191, 27, 191, 192, 193, 194, 
27, 194, 195, 196, 197, 108, 198, 198, 199, 200, 24, 201, 201, 202, 203, 27, 203, 204, 205, 206, 
27, 206, 207, 208, 209, 91, 209, 210, 211, 212, 24, 213, 213, 214, 215, 252, 216, 216, 217, 218, 
91, 219, 220, 221, 222, 172, 223, 223, 224, 225, 241, 226, 227, 227, 228, 22, 229, 230, 231, 232, 
192, 233, 234, 235, 235, 107, 236, 237, 238, 239, 233, 240, 241, 242, 243, 36, 245, 246, 247, 255, 
},

//Green Channel
{
64, 0, 0, 0, 17, 232, 18, 18, 20, 21, 186, 22, 24, 25, 26, 21, 28, 29, 30, 32, 
220, 33, 33, 34, 34, 213, 36, 37, 38, 38, 218, 40, 41, 42, 42, 128, 44, 45, 46, 46, 
108, 47, 48, 49, 50, 178, 50, 51, 52, 53, 120, 54, 54, 54, 56, 220, 57, 57, 58, 58, 
118, 60, 61, 61, 62, 46, 62, 62, 64, 65, 88, 66, 66, 68, 69, 13, 70, 70, 73, 74, 
82, 74, 75, 77, 78, 191, 78, 80, 81, 82, 140, 84, 84, 86, 86, 213, 88, 89, 90, 90, 
218, 92, 93, 94, 94, 213, 96, 97, 98, 98, 32, 101, 102, 102, 104, 176, 105, 106, 106, 108, 
75, 109, 110, 111, 113, 8, 114, 114, 116, 117, 236, 118, 118, 120, 121, 86, 122, 124, 125, 126, 
111, 126, 128, 129, 130, 30, 130, 130, 132, 133, 183, 133, 134, 134, 136, 33, 137, 138, 138, 139, 
219, 140, 141, 142, 142, 113, 144, 145, 145, 146, 135, 146, 148, 149, 149, 120, 150, 150, 150, 152, 
191, 152, 153, 154, 155, 90, 156, 157, 158, 159, 1, 160, 161, 162, 163, 176, 164, 165, 165, 166, 
241, 167, 168, 168, 169, 255, 170, 171, 172, 173, 22, 174, 175, 176, 177, 80, 178, 179, 180, 181, 
240, 182, 183, 183, 184, 106, 185, 186, 187, 188, 85, 189, 190, 191, 192, 108, 193, 193, 194, 195, 
108, 196, 196, 197, 198, 124, 199, 199, 200, 201, 108, 202, 202, 203, 204, 27, 204, 205, 206, 207, 
175, 207, 208, 209, 210, 177, 211, 212, 212, 213, 177, 214, 215, 215, 216, 86, 217, 218, 219, 220, 
241, 221, 222, 222, 223, 198, 224, 225, 226, 226, 27, 227, 228, 229, 230, 172, 231, 231, 232, 233, 
90, 234, 235, 236, 237, 240, 238, 239, 239, 240, 63, 241, 242, 243, 245, 41, 246, 247, 248, 255, 
},

//Blue Channel
{
64, 0, 0, 0, 21, 171, 21, 22, 23, 24, 101, 25, 26, 27, 28, 182, 29, 30, 31, 32, 
177, 33, 34, 34, 35, 234, 36, 37, 38, 39, 90, 40, 41, 42, 43, 240, 44, 45, 45, 46, 
27, 47, 48, 49, 50, 27, 50, 51, 52, 53, 199, 53, 54, 55, 55, 91, 56, 57, 58, 59, 
28, 60, 60, 61, 62, 198, 62, 63, 64, 64, 80, 66, 67, 68, 69, 14, 70, 71, 73, 74, 
80, 75, 76, 77, 78, 170, 79, 80, 81, 82, 62, 83, 84, 85, 87, 85, 88, 89, 90, 91, 
21, 92, 93, 94, 95, 228, 96, 97, 98, 99, 255, 100, 101, 102, 103, 228, 105, 106, 107, 108, 
83, 109, 111, 112, 113, 65, 114, 115, 116, 117, 62, 118, 119, 120, 122, 249, 123, 124, 125, 126, 
44, 128, 128, 129, 130, 27, 130, 131, 132, 133, 188, 134, 134, 135, 136, 22, 137, 138, 139, 140, 
188, 141, 141, 142, 143, 198, 144, 145, 146, 146, 198, 147, 148, 149, 149, 177, 150, 151, 151, 152, 
85, 153, 154, 155, 156, 0, 157, 158, 159, 160, 240, 161, 162, 162, 163, 27, 164, 165, 166, 167, 
63, 167, 168, 169, 171, 172, 172, 172, 173, 174, 85, 175, 176, 177, 178, 90, 179, 180, 181, 182, 
1, 183, 184, 185, 186, 3, 186, 188, 189, 190, 124, 191, 191, 192, 193, 177, 194, 195, 195, 196, 
177, 197, 198, 198, 199, 177, 200, 201, 201, 202, 109, 203, 203, 204, 205, 172, 206, 206, 207, 208, 
177, 209, 210, 210, 211, 177, 212, 213, 213, 214, 6, 215, 216, 217, 218, 176, 219, 220, 220, 221, 
197, 222, 223, 224, 224, 198, 225, 226, 227, 227, 26, 228, 229, 230, 231, 175, 231, 232, 233, 234, 
197, 235, 236, 237, 237, 6, 238, 239, 240, 241, 240, 242, 243, 243, 244, 63, 245, 246, 247, 255, 
},
},
//2.0

//2.1
{
//Red Channel
{
0, 0, 0, 0, 0, 218, 16, 17, 18, 19, 90, 20, 21, 23, 24, 233, 25, 26, 27, 28, 
186, 29, 30, 31, 32, 177, 33, 34, 34, 35, 170, 36, 37, 38, 39, 198, 40, 41, 42, 42, 
107, 43, 44, 45, 46, 177, 47, 48, 48, 49, 177, 50, 51, 51, 52, 109, 53, 53, 54, 55, 
108, 56, 56, 57, 58, 97, 59, 60, 60, 61, 203, 61, 62, 63, 63, 170, 64, 65, 66, 67, 
67, 68, 70, 71, 72, 165, 73, 74, 75, 76, 254, 77, 78, 79, 80, 255, 81, 82, 83, 84, 
80, 86, 87, 88, 89, 106, 90, 91, 92, 93, 69, 94, 95, 96, 97, 254, 98, 99, 100, 101, 
15, 102, 103, 105, 106, 57, 107, 108, 109, 111, 0, 112, 113, 114, 115, 144, 116, 117, 118, 119, 
79, 120, 121, 123, 124, 186, 125, 126, 127, 128, 97, 129, 130, 130, 131, 188, 132, 132, 133, 134, 
22, 135, 136, 137, 138, 188, 139, 139, 140, 141, 22, 142, 143, 144, 145, 107, 145, 146, 147, 148, 
219, 148, 149, 150, 150, 22, 151, 152, 153, 154, 0, 155, 156, 157, 158, 255, 158, 159, 160, 161, 
111, 162, 163, 164, 165, 241, 166, 167, 167, 168, 255, 169, 170, 171, 172, 90, 173, 174, 175, 176, 
165, 177, 178, 179, 180, 86, 181, 182, 183, 184, 0, 185, 186, 187, 188, 240, 189, 190, 190, 191, 
27, 192, 193, 194, 195, 27, 195, 196, 197, 198, 108, 199, 199, 200, 201, 44, 202, 202, 203, 204, 
108, 205, 205, 206, 207, 188, 208, 208, 209, 210, 197, 211, 212, 213, 213, 6, 214, 215, 216, 217, 
0, 218, 219, 220, 221, 111, 221, 222, 223, 224, 241, 225, 226, 226, 227, 90, 228, 229, 230, 231, 
85, 232, 233, 234, 235, 1, 236, 237, 238, 239, 83, 239, 241, 242, 243, 35, 244, 246, 247, 255, 
},

//Green Channel
{
0, 0, 0, 0, 0, 25, 16, 17, 18, 20, 243, 20, 22, 22, 24, 152, 26, 26, 28, 29, 
188, 30, 30, 32, 33, 136, 34, 34, 36, 36, 246, 37, 38, 38, 40, 38, 41, 42, 42, 43, 
223, 44, 45, 46, 46, 69, 48, 49, 50, 50, 135, 50, 52, 53, 53, 120, 54, 54, 54, 56, 
220, 57, 57, 58, 58, 117, 60, 61, 61, 62, 222, 62, 62, 64, 64, 203, 65, 66, 67, 68, 
168, 70, 70, 72, 73, 61, 74, 74, 76, 78, 18, 78, 80, 81, 82, 82, 82, 84, 85, 86, 
127, 86, 88, 89, 90, 124, 91, 92, 93, 94, 171, 94, 96, 97, 98, 132, 100, 101, 102, 102, 
213, 104, 105, 106, 106, 163, 108, 110, 110, 112, 118, 113, 114, 114, 116, 54, 117, 118, 118, 121, 
236, 122, 122, 124, 125, 210, 126, 127, 129, 129, 137, 130, 130, 132, 132, 33, 133, 134, 134, 136, 
223, 136, 137, 138, 138, 133, 140, 141, 142, 142, 108, 144, 144, 145, 146, 178, 146, 148, 148, 149, 
52, 150, 150, 150, 151, 171, 152, 153, 154, 155, 85, 156, 157, 158, 159, 5, 160, 161, 162, 163, 
176, 164, 165, 165, 166, 6, 167, 168, 169, 170, 20, 171, 172, 173, 174, 175, 174, 175, 176, 177, 
254, 178, 179, 180, 181, 171, 182, 183, 184, 185, 85, 186, 187, 188, 189, 21, 190, 191, 192, 193, 
27, 193, 194, 195, 196, 108, 197, 197, 198, 199, 177, 200, 201, 201, 202, 108, 203, 203, 204, 205, 
172, 206, 206, 207, 208, 22, 209, 210, 211, 212, 107, 212, 213, 214, 215, 252, 216, 216, 217, 218, 
175, 219, 220, 221, 222, 193, 223, 224, 225, 225, 91, 226, 227, 228, 229, 240, 230, 231, 231, 232, 
170, 233, 234, 235, 236, 90, 237, 238, 239, 240, 165, 241, 242, 243, 244, 35, 245, 247, 248, 255, 
},

//Blue Channel
{
0, 0, 0, 0, 0, 155, 18, 19, 20, 21, 96, 22, 23, 24, 25, 169, 26, 27, 28, 29, 
41, 30, 31, 32, 33, 107, 33, 34, 35, 36, 85, 37, 38, 39, 40, 172, 41, 41, 42, 43, 
5, 44, 45, 46, 47, 31, 47, 48, 49, 50, 31, 50, 51, 52, 53, 199, 53, 54, 55, 55, 
22, 56, 57, 58, 59, 200, 60, 60, 61, 61, 177, 62, 63, 63, 64, 250, 65, 66, 67, 68, 
80, 70, 71, 72, 73, 234, 74, 75, 76, 77, 195, 78, 80, 81, 81, 79, 82, 83, 85, 86, 
169, 87, 88, 89, 90, 170, 91, 92, 93, 94, 229, 95, 96, 97, 98, 0, 100, 101, 102, 103, 
228, 104, 105, 106, 107, 148, 109, 110, 111, 112, 154, 113, 114, 115, 116, 79, 117, 118, 120, 121, 
62, 122, 123, 124, 126, 197, 127, 128, 129, 129, 177, 130, 131, 131, 132, 86, 133, 134, 135, 136, 
240, 137, 138, 138, 139, 90, 140, 141, 142, 143, 177, 144, 145, 145, 146, 181, 147, 148, 148, 149, 
109, 150, 150, 151, 152, 85, 153, 154, 155, 156, 0, 157, 158, 159, 160, 0, 161, 162, 163, 164, 
111, 164, 165, 166, 167, 85, 168, 169, 170, 171, 5, 172, 173, 174, 175, 15, 175, 176, 178, 179, 
1, 180, 181, 182, 183, 255, 183, 184, 185, 186, 0, 188, 189, 190, 191, 108, 192, 192, 193, 194, 
188, 195, 195, 196, 197, 193, 198, 199, 200, 200, 178, 201, 202, 202, 203, 197, 204, 205, 206, 206, 
6, 207, 208, 209, 210, 107, 210, 211, 212, 213, 172, 214, 214, 215, 216, 106, 217, 218, 219, 220, 
241, 221, 222, 222, 223, 6, 224, 225, 226, 227, 107, 227, 228, 229, 230, 240, 231, 232, 232, 233, 
107, 234, 235, 236, 237, 240, 238, 239, 239, 240, 234, 241, 242, 243, 244, 63, 245, 246, 247, 255, 
},
},
//2.1

//2.2
{
//Red Channel
{
0, 0, 0, 0, 0, 197, 17, 17, 18, 18, 142, 19, 20, 22, 22, 237, 24, 24, 25, 26, 
251, 27, 28, 29, 30, 202, 31, 32, 33, 33, 6, 34, 35, 36, 37, 143, 37, 38, 40, 40, 
245, 41, 42, 42, 43, 22, 44, 45, 46, 47, 27, 47, 48, 49, 50, 219, 50, 51, 52, 52, 
178, 53, 54, 54, 55, 176, 56, 57, 57, 58, 118, 59, 60, 60, 61, 200, 62, 62, 63, 63, 
170, 64, 65, 66, 67, 79, 68, 69, 71, 72, 85, 73, 74, 75, 76, 169, 77, 78, 79, 80, 
170, 81, 82, 83, 84, 15, 85, 86, 88, 89, 20, 90, 91, 92, 93, 48, 94, 95, 95, 97, 
169, 98, 99, 100, 101, 234, 102, 103, 104, 105, 164, 107, 108, 109, 110, 255, 111, 112, 113, 114, 
79, 115, 116, 118, 119, 62, 120, 121, 122, 124, 185, 125, 126, 127, 128, 109, 129, 129, 130, 131, 
188, 132, 132, 133, 134, 86, 135, 136, 137, 138, 240, 139, 140, 140, 141, 90, 142, 143, 144, 145, 
108, 146, 146, 147, 148, 28, 149, 149, 150, 151, 171, 151, 152, 153, 154, 170, 155, 156, 157, 158, 
86, 159, 160, 161, 162, 5, 163, 164, 165, 166, 171, 166, 167, 168, 169, 191, 170, 171, 172, 173, 
86, 174, 175, 176, 177, 170, 178, 179, 180, 181, 170, 182, 183, 184, 185, 85, 186, 187, 188, 189, 
21, 190, 191, 192, 193, 111, 193, 194, 195, 196, 240, 197, 198, 198, 199, 198, 200, 201, 202, 202, 
198, 203, 204, 205, 205, 26, 206, 207, 208, 209, 188, 210, 210, 211, 212, 197, 213, 214, 215, 215, 
63, 216, 217, 218, 220, 175, 220, 221, 222, 223, 5, 224, 225, 226, 227, 191, 227, 228, 229, 230, 
234, 231, 232, 233, 234, 191, 235, 236, 237, 238, 78, 239, 240, 242, 243, 18, 244, 246, 247, 255, 
},

//Green Channel
{
0, 0, 0, 0, 0, 133, 17, 17, 18, 18, 151, 18, 21, 22, 22, 202, 24, 25, 26, 26, 
213, 28, 29, 30, 30, 69, 32, 33, 34, 34, 199, 34, 36, 37, 37, 130, 38, 40, 41, 41, 
201, 42, 42, 43, 44, 38, 45, 46, 46, 48, 156, 49, 49, 50, 50, 24, 51, 52, 53, 54, 
137, 54, 54, 56, 56, 225, 57, 58, 58, 58, 118, 60, 61, 61, 62, 222, 62, 62, 64, 64, 
203, 65, 66, 68, 68, 152, 70, 70, 72, 73, 237, 74, 74, 76, 77, 2, 78, 79, 81, 82, 
2, 82, 83, 85, 86, 102, 86, 88, 89, 90, 107, 90, 92, 93, 94, 87, 94, 96, 97, 98, 
191, 98, 100, 101, 102, 140, 103, 104, 106, 106, 42, 108, 109, 110, 111, 33, 113, 114, 114, 115, 
240, 117, 118, 118, 120, 155, 121, 122, 124, 125, 193, 126, 128, 129, 129, 137, 130, 130, 132, 132, 
33, 133, 134, 134, 135, 223, 136, 137, 138, 138, 133, 140, 141, 142, 142, 124, 143, 144, 145, 146, 
178, 146, 148, 148, 149, 120, 150, 150, 150, 152, 240, 153, 154, 154, 155, 255, 156, 157, 158, 159, 
255, 160, 161, 162, 163, 91, 164, 165, 166, 167, 60, 168, 168, 169, 171, 192, 172, 173, 174, 174, 
235, 175, 176, 177, 178, 243, 179, 181, 181, 182, 255, 183, 184, 185, 186, 170, 187, 188, 189, 190, 
106, 191, 192, 193, 194, 188, 195, 195, 196, 197, 197, 198, 199, 200, 200, 198, 201, 202, 203, 203, 
22, 204, 205, 206, 207, 191, 207, 208, 209, 210, 22, 211, 212, 213, 214, 107, 214, 215, 216, 217, 
169, 218, 219, 220, 221, 5, 222, 223, 224, 225, 175, 225, 226, 227, 228, 21, 229, 230, 231, 232, 
0, 233, 234, 235, 236, 1, 237, 238, 239, 240, 144, 241, 242, 243, 244, 35, 245, 247, 248, 255, 
},

//Blue Channel
{
0, 0, 0, 0, 0, 181, 20, 20, 20, 21, 144, 22, 23, 24, 24, 70, 25, 26, 27, 28, 
12, 29, 29, 31, 32, 182, 32, 33, 33, 34, 241, 35, 36, 36, 37, 111, 38, 39, 40, 41, 
172, 42, 42, 43, 44, 193, 45, 46, 47, 47, 198, 48, 49, 50, 50, 113, 51, 52, 52, 53, 
28, 54, 54, 55, 56, 107, 56, 57, 58, 59, 220, 60, 60, 61, 61, 178, 62, 63, 63, 64, 
234, 65, 66, 67, 68, 83, 69, 71, 72, 73, 149, 74, 75, 76, 77, 254, 78, 79, 80, 81, 
254, 82, 83, 84, 85, 84, 87, 88, 89, 90, 21, 91, 92, 93, 94, 144, 95, 96, 97, 98, 
255, 99, 100, 101, 102, 67, 103, 105, 106, 107, 78, 108, 109, 111, 112, 1, 113, 114, 115, 116, 
57, 117, 118, 119, 121, 228, 122, 123, 124, 125, 180, 127, 128, 128, 129, 177, 130, 131, 131, 132, 
21, 133, 134, 135, 136, 252, 137, 137, 138, 139, 90, 140, 141, 142, 143, 241, 144, 145, 145, 146, 
134, 147, 148, 149, 149, 177, 150, 151, 151, 152, 170, 153, 154, 155, 156, 170, 157, 158, 159, 160, 
170, 161, 162, 163, 164, 193, 165, 166, 167, 167, 3, 168, 170, 171, 172, 252, 173, 173, 174, 175, 
15, 176, 177, 179, 180, 0, 181, 182, 183, 184, 0, 185, 186, 187, 188, 85, 189, 190, 191, 192, 
172, 193, 193, 194, 195, 193, 196, 197, 198, 198, 27, 199, 200, 201, 202, 27, 202, 203, 204, 205, 
111, 205, 206, 207, 208, 193, 209, 210, 211, 211, 26, 212, 213, 214, 215, 15, 215, 216, 218, 219, 
188, 220, 220, 221, 222, 22, 223, 224, 225, 226, 175, 226, 227, 228, 229, 5, 230, 231, 232, 233, 
192, 234, 235, 236, 236, 90, 237, 238, 239, 240, 149, 241, 242, 243, 244, 58, 245, 246, 247, 255, 

},
},
//2.2

//2.3
{
//Red Channel
{
0, 0, 0, 0, 0, 20, 0, 17, 17, 18, 155, 18, 19, 20, 21, 192, 22, 23, 24, 24, 
188, 26, 26, 27, 28, 90, 29, 30, 31, 32, 199, 32, 33, 34, 34, 6, 35, 36, 37, 38, 
112, 39, 40, 40, 41, 172, 42, 42, 43, 44, 177, 45, 46, 46, 47, 113, 48, 49, 49, 50, 
44, 51, 51, 52, 53, 135, 53, 54, 55, 55, 193, 56, 57, 58, 58, 118, 59, 60, 60, 61, 
216, 62, 62, 63, 63, 170, 64, 65, 66, 67, 15, 68, 69, 71, 72, 64, 73, 74, 75, 76, 
149, 77, 78, 79, 80, 85, 81, 82, 83, 84, 58, 85, 86, 87, 89, 0, 90, 91, 92, 93, 
255, 93, 94, 95, 96, 100, 98, 99, 100, 101, 165, 102, 103, 104, 105, 147, 106, 108, 109, 110, 
255, 111, 112, 113, 114, 78, 115, 116, 118, 119, 57, 120, 121, 122, 124, 185, 125, 126, 127, 128, 
97, 129, 130, 130, 131, 240, 132, 133, 133, 134, 106, 135, 136, 137, 138, 5, 139, 140, 141, 142, 
191, 142, 143, 144, 145, 193, 146, 147, 148, 148, 177, 149, 150, 150, 151, 5, 152, 153, 154, 155, 
0, 156, 157, 158, 159, 64, 160, 161, 162, 163, 241, 164, 165, 165, 166, 234, 167, 168, 169, 170, 
175, 171, 172, 173, 174, 234, 175, 176, 177, 178, 240, 180, 181, 181, 182, 255, 183, 184, 185, 186, 
3, 187, 189, 190, 191, 188, 192, 192, 193, 194, 197, 195, 196, 197, 197, 107, 198, 199, 200, 201, 
108, 202, 202, 203, 204, 241, 205, 206, 206, 207, 90, 208, 209, 210, 211, 241, 212, 213, 213, 214, 
234, 215, 216, 217, 218, 175, 219, 220, 221, 222, 90, 223, 224, 225, 226, 1, 227, 228, 229, 230, 
0, 231, 232, 233, 234, 85, 235, 236, 237, 238, 57, 239, 240, 241, 243, 29, 244, 245, 247, 255, 

},

//Green Channel
{
0, 0, 0, 0, 0, 0, 0, 17, 17, 18, 238, 18, 18, 20, 21, 173, 22, 22, 24, 25, 
89, 26, 26, 28, 29, 56, 30, 30, 31, 33, 226, 33, 34, 34, 34, 134, 36, 37, 38, 38, 
112, 39, 41, 41, 42, 162, 42, 44, 44, 45, 200, 46, 46, 48, 48, 210, 49, 50, 50, 50, 
33, 52, 53, 53, 54, 206, 54, 54, 55, 56, 34, 57, 58, 58, 59, 71, 60, 61, 62, 62, 
30, 62, 62, 64, 65, 203, 65, 66, 68, 68, 91, 69, 70, 72, 73, 157, 74, 74, 76, 77, 
253, 78, 78, 80, 81, 253, 82, 82, 84, 85, 22, 86, 88, 89, 90, 23, 90, 92, 93, 94, 
2, 94, 96, 97, 98, 127, 98, 100, 101, 102, 191, 102, 104, 105, 106, 25, 108, 109, 110, 111, 
32, 113, 114, 114, 115, 176, 117, 118, 118, 120, 155, 121, 122, 124, 125, 193, 126, 128, 129, 129, 
137, 130, 130, 131, 132, 33, 133, 134, 134, 136, 220, 137, 137, 138, 138, 154, 140, 141, 142, 142, 
65, 144, 145, 146, 146, 215, 146, 148, 149, 149, 201, 150, 150, 151, 152, 170, 153, 154, 155, 156, 
150, 157, 158, 159, 160, 170, 161, 162, 163, 164, 6, 165, 166, 167, 168, 15, 168, 169, 171, 172, 
240, 173, 174, 174, 175, 15, 176, 177, 179, 180, 5, 181, 182, 183, 184, 0, 185, 186, 187, 188, 
84, 189, 190, 191, 192, 241, 193, 194, 194, 195, 22, 196, 197, 198, 199, 108, 200, 200, 201, 202, 
176, 203, 204, 204, 205, 5, 206, 207, 208, 209, 240, 210, 211, 211, 212, 26, 213, 214, 215, 216, 
64, 217, 218, 219, 220, 5, 221, 222, 223, 224, 252, 225, 225, 226, 227, 170, 228, 229, 230, 231, 
165, 232, 233, 234, 235, 170, 236, 237, 238, 239, 78, 240, 241, 243, 244, 18, 245, 247, 248, 255, 
},

//Blue Channel
{
0, 0, 0, 0, 0, 212, 0, 20, 20, 20, 226, 21, 22, 22, 23, 113, 24, 25, 25, 26, 
198, 27, 28, 29, 29, 30, 30, 31, 32, 33, 178, 33, 34, 34, 35, 5, 36, 37, 38, 39, 
24, 40, 40, 41, 42, 27, 42, 43, 44, 45, 108, 46, 46, 47, 48, 28, 49, 49, 50, 51, 
139, 51, 52, 53, 53, 97, 54, 55, 55, 56, 172, 57, 57, 58, 59, 29, 60, 60, 61, 62, 
178, 62, 63, 63, 64, 250, 65, 66, 67, 68, 83, 69, 71, 72, 73, 149, 74, 75, 76, 77, 
170, 78, 79, 80, 81, 234, 82, 83, 84, 85, 0, 87, 88, 89, 90, 5, 91, 92, 93, 94, 
76, 95, 95, 97, 98, 174, 99, 100, 101, 102, 78, 103, 104, 106, 107, 14, 108, 109, 111, 112, 
0, 113, 114, 115, 116, 57, 117, 118, 119, 121, 233, 122, 123, 124, 125, 132, 127, 128, 129, 129, 
177, 130, 131, 131, 132, 90, 133, 134, 135, 136, 1, 137, 138, 139, 140, 191, 140, 141, 142, 143, 
22, 144, 145, 146, 147, 27, 147, 148, 149, 150, 91, 150, 151, 152, 153, 85, 154, 155, 156, 157, 
85, 158, 159, 160, 161, 85, 162, 163, 164, 165, 240, 166, 167, 167, 168, 0, 170, 171, 172, 173, 
60, 174, 174, 175, 177, 84, 178, 179, 180, 181, 85, 182, 183, 184, 185, 250, 186, 187, 188, 189, 
179, 190, 192, 192, 193, 5, 194, 195, 196, 197, 175, 197, 198, 199, 200, 177, 201, 202, 202, 203, 
197, 204, 205, 206, 206, 171, 207, 208, 209, 210, 197, 211, 212, 213, 213, 171, 214, 215, 216, 217, 
191, 218, 219, 220, 221, 86, 222, 223, 224, 225, 240, 226, 227, 227, 228, 170, 229, 230, 231, 232, 
170, 233, 234, 235, 236, 5, 237, 238, 239, 240, 80, 241, 242, 243, 244, 58, 245, 246, 247, 255, 
},
},
//2.3

//2.4
{
//Red Channel
{
0, 0, 0, 0, 0, 80, 0, 0, 17, 17, 112, 18, 19, 19, 20, 232, 21, 21, 22, 23, 
198, 24, 25, 26, 26, 87, 27, 28, 29, 30, 44, 31, 31, 32, 33, 199, 33, 34, 35, 35, 
86, 36, 37, 38, 39, 28, 40, 40, 41, 42, 27, 42, 43, 44, 45, 107, 45, 46, 47, 48, 
203, 48, 49, 50, 50, 118, 51, 52, 52, 53, 24, 54, 54, 55, 56, 22, 56, 57, 58, 59, 
139, 59, 60, 61, 61, 220, 62, 62, 63, 63, 255, 64, 65, 66, 67, 79, 68, 69, 71, 72, 
85, 73, 74, 75, 76, 165, 77, 78, 79, 80, 86, 81, 82, 83, 84, 62, 85, 86, 87, 89, 
0, 90, 91, 92, 93, 255, 93, 94, 95, 96, 164, 98, 99, 100, 101, 234, 102, 103, 104, 105, 
148, 107, 108, 109, 110, 255, 111, 112, 113, 114, 147, 115, 117, 118, 119, 78, 120, 121, 123, 124, 
206, 125, 126, 128, 128, 178, 129, 130, 130, 131, 21, 132, 133, 134, 135, 240, 136, 137, 137, 138, 
171, 139, 140, 141, 142, 5, 143, 144, 145, 146, 47, 146, 147, 148, 149, 27, 149, 150, 151, 152, 
0, 153, 154, 155, 156, 0, 157, 158, 159, 160, 84, 161, 162, 163, 164, 240, 165, 166, 166, 167, 
15, 168, 169, 171, 172, 240, 173, 174, 174, 175, 144, 177, 178, 179, 180, 170, 181, 182, 183, 184, 
234, 185, 186, 187, 188, 207, 189, 190, 192, 192, 90, 193, 194, 195, 196, 240, 197, 198, 198, 199, 
22, 200, 201, 202, 203, 107, 203, 204, 205, 206, 1, 207, 208, 209, 210, 188, 211, 211, 212, 213, 
150, 214, 215, 216, 217, 254, 218, 219, 220, 221, 170, 222, 223, 224, 225, 86, 226, 227, 228, 229, 
165, 230, 231, 232, 233, 15, 234, 235, 237, 238, 224, 239, 240, 241, 242, 28, 244, 245, 247, 255, 
},

//Green Channel
{
0, 0, 0, 0, 0, 80, 0, 0, 17, 17, 184, 18, 18, 18, 20, 45, 21, 21, 22, 24, 
220, 25, 25, 26, 26, 177, 28, 29, 29, 30, 27, 30, 32, 33, 34, 141, 34, 34, 35, 36, 
34, 37, 38, 38, 40, 156, 41, 41, 42, 42, 24, 43, 44, 45, 46, 110, 46, 46, 48, 49, 
39, 49, 50, 50, 51, 118, 52, 53, 53, 54, 30, 54, 54, 56, 57, 55, 57, 58, 58, 60, 
72, 61, 61, 62, 62, 34, 62, 63, 64, 65, 8, 66, 66, 68, 69, 152, 70, 70, 72, 73, 
173, 74, 74, 76, 77, 253, 78, 78, 80, 81, 254, 82, 82, 84, 85, 86, 86, 88, 89, 90, 
23, 90, 92, 93, 94, 2, 94, 96, 97, 98, 127, 98, 100, 101, 102, 191, 102, 104, 105, 106, 
41, 108, 109, 110, 111, 33, 113, 114, 114, 115, 244, 117, 118, 118, 120, 232, 122, 122, 124, 125, 
22, 126, 128, 129, 130, 205, 130, 130, 132, 132, 119, 133, 134, 134, 136, 33, 137, 138, 138, 140, 
236, 141, 141, 142, 142, 155, 144, 145, 146, 146, 96, 147, 149, 149, 150, 110, 150, 150, 152, 153, 
85, 154, 155, 156, 157, 85, 158, 159, 160, 161, 170, 162, 163, 164, 165, 5, 166, 167, 168, 169, 
84, 170, 171, 172, 173, 5, 174, 175, 176, 177, 233, 178, 179, 180, 181, 255, 182, 183, 184, 185, 
255, 186, 187, 188, 189, 0, 191, 192, 193, 194, 107, 194, 195, 196, 197, 1, 198, 199, 200, 201, 
27, 201, 202, 203, 204, 172, 205, 205, 206, 207, 170, 208, 209, 210, 211, 21, 212, 213, 214, 215, 
60, 216, 216, 217, 219, 4, 220, 221, 222, 223, 0, 224, 225, 226, 227, 255, 227, 228, 229, 230, 
63, 231, 232, 233, 235, 84, 236, 237, 238, 239, 53, 240, 241, 242, 244, 29, 245, 246, 248, 255, 
},

//Blue Channel
{
0, 0, 0, 0, 0, 80, 0, 0, 20, 20, 135, 20, 21, 22, 22, 108, 23, 23, 24, 25, 
108, 26, 26, 27, 28, 152, 29, 29, 30, 31, 217, 32, 32, 33, 33, 178, 34, 35, 35, 36, 
5, 37, 38, 39, 40, 199, 40, 41, 42, 42, 198, 43, 44, 45, 45, 198, 46, 47, 48, 48, 
177, 49, 50, 50, 51, 220, 52, 52, 53, 53, 182, 54, 55, 55, 56, 241, 57, 58, 58, 59, 
33, 60, 61, 61, 62, 246, 62, 63, 63, 64, 254, 65, 66, 67, 68, 80, 70, 71, 72, 73, 
149, 74, 75, 76, 77, 170, 78, 79, 80, 81, 234, 82, 83, 84, 85, 3, 86, 88, 89, 90, 
4, 91, 92, 93, 94, 79, 94, 95, 97, 98, 170, 99, 100, 101, 102, 78, 103, 104, 106, 107, 
78, 108, 109, 111, 112, 0, 113, 114, 115, 116, 57, 117, 118, 119, 121, 57, 122, 123, 124, 126, 
197, 127, 128, 129, 129, 198, 130, 131, 132, 132, 175, 133, 134, 135, 136, 86, 137, 138, 139, 140, 
1, 141, 142, 143, 144, 175, 144, 145, 146, 147, 177, 148, 149, 149, 150, 252, 151, 151, 152, 153, 
15, 154, 155, 157, 158, 64, 159, 160, 161, 162, 5, 163, 164, 165, 166, 60, 167, 167, 168, 170, 
21, 171, 172, 173, 174, 144, 175, 176, 177, 178, 255, 179, 180, 181, 182, 63, 183, 184, 185, 187, 
165, 188, 189, 190, 191, 22, 192, 193, 194, 195, 188, 196, 196, 197, 198, 26, 199, 200, 201, 202, 
107, 202, 203, 204, 205, 1, 206, 207, 208, 209, 191, 209, 210, 211, 212, 22, 213, 214, 215, 216, 
165, 217, 218, 219, 220, 86, 221, 222, 223, 224, 192, 225, 226, 227, 227, 255, 228, 229, 230, 231, 
255, 232, 233, 234, 235, 191, 236, 237, 238, 239, 62, 240, 241, 242, 244, 37, 245, 246, 247, 255,  
},
},
//2.4


//2.5
{
//Red Channel
{
0, 0, 0, 0, 0, 192, 0, 0, 0, 16, 175, 16, 17, 18, 18, 209, 19, 20, 21, 21, 
25, 22, 23, 24, 25, 91, 25, 26, 27, 28, 172, 29, 29, 30, 31, 220, 32, 32, 33, 33, 
182, 34, 35, 35, 36, 5, 37, 38, 39, 40, 134, 40, 41, 42, 42, 177, 43, 44, 44, 45, 
129, 46, 47, 48, 48, 109, 49, 49, 50, 51, 139, 51, 52, 53, 53, 109, 54, 54, 55, 56, 
95, 56, 57, 58, 59, 200, 60, 60, 61, 61, 29, 62, 62, 63, 64, 240, 65, 66, 66, 67, 
80, 69, 70, 71, 72, 85, 73, 74, 75, 76, 169, 77, 78, 79, 80, 170, 81, 82, 83, 84, 
14, 85, 86, 88, 89, 0, 90, 91, 92, 93, 60, 94, 94, 95, 97, 169, 98, 99, 100, 101, 
250, 102, 103, 104, 105, 228, 107, 108, 109, 110, 0, 112, 113, 114, 115, 228, 116, 117, 118, 119, 
164, 121, 122, 123, 124, 19, 125, 127, 128, 129, 199, 129, 130, 131, 131, 175, 132, 133, 134, 135, 
86, 136, 137, 138, 139, 1, 140, 141, 142, 143, 188, 144, 144, 145, 146, 198, 147, 148, 149, 149, 
242, 150, 151, 151, 152, 15, 153, 154, 156, 157, 64, 158, 159, 160, 161, 85, 162, 163, 164, 165, 
0, 166, 167, 168, 169, 101, 170, 171, 172, 173, 149, 174, 175, 176, 177, 3, 178, 180, 181, 182, 
80, 183, 184, 185, 186, 169, 187, 188, 189, 190, 175, 191, 192, 193, 194, 5, 195, 196, 197, 198, 
176, 199, 200, 200, 201, 5, 202, 203, 204, 205, 191, 205, 206, 207, 208, 170, 209, 210, 211, 212, 
21, 213, 214, 215, 216, 233, 217, 218, 219, 220, 255, 221, 222, 223, 224, 170, 225, 226, 227, 228, 
63, 229, 230, 231, 233, 164, 234, 235, 236, 237, 142, 238, 239, 241, 242, 24, 244, 245, 247, 255, 

},

//Green Channel
{
0, 0, 0, 0, 0, 192, 0, 0, 0, 16, 95, 16, 17, 18, 18, 39, 18, 20, 21, 22, 
193, 22, 23, 25, 25, 9, 26, 26, 28, 29, 119, 29, 30, 30, 32, 136, 33, 33, 34, 34, 
179, 34, 35, 36, 37, 9, 38, 38, 39, 41, 230, 41, 42, 42, 42, 113, 44, 45, 45, 46, 
131, 46, 48, 49, 49, 120, 50, 50, 50, 52, 72, 53, 53, 54, 54, 99, 54, 55, 56, 57, 
120, 58, 58, 58, 60, 136, 61, 61, 62, 62, 99, 62, 63, 64, 65, 8, 66, 66, 67, 69, 
172, 70, 70, 72, 73, 237, 74, 74, 76, 77, 2, 78, 80, 81, 82, 50, 82, 84, 84, 86, 
86, 86, 88, 89, 90, 107, 90, 92, 93, 94, 86, 94, 96, 97, 98, 191, 98, 100, 101, 102, 
204, 103, 104, 106, 106, 110, 108, 109, 110, 112, 118, 113, 114, 114, 116, 6, 117, 118, 119, 121, 
61, 122, 122, 124, 126, 43, 126, 128, 129, 130, 94, 130, 130, 132, 133, 200, 134, 134, 135, 136, 
183, 137, 138, 138, 140, 118, 141, 142, 142, 144, 33, 145, 146, 146, 147, 139, 148, 149, 150, 150, 
7, 150, 152, 153, 154, 85, 155, 156, 157, 158, 165, 159, 160, 161, 162, 174, 163, 164, 165, 166, 
85, 167, 168, 169, 170, 190, 171, 172, 173, 174, 234, 175, 176, 177, 178, 84, 180, 181, 182, 183, 
165, 184, 185, 186, 187, 254, 188, 189, 190, 191, 188, 193, 193, 194, 195, 86, 196, 197, 198, 199, 
193, 200, 201, 202, 202, 22, 203, 204, 205, 206, 0, 207, 208, 209, 210, 192, 211, 212, 213, 213, 
239, 214, 215, 216, 217, 19, 218, 220, 221, 222, 0, 223, 224, 225, 226, 0, 227, 228, 229, 230, 
148, 231, 232, 233, 234, 62, 235, 236, 237, 239, 208, 240, 241, 242, 243, 29, 245, 246, 248, 255, 

},

//Blue Channel
{
0, 0, 0, 0, 0, 64, 0, 0, 0, 19, 241, 19, 20, 20, 20, 141, 21, 21, 23, 23, 
108, 24, 24, 25, 26, 92, 27, 27, 28, 29, 124, 30, 30, 31, 32, 135, 32, 33, 34, 34, 
108, 35, 35, 36, 37, 128, 38, 39, 40, 40, 109, 41, 41, 42, 43, 108, 44, 44, 45, 46, 
44, 47, 47, 48, 49, 199, 49, 50, 51, 51, 34, 52, 53, 53, 54, 199, 54, 55, 56, 56, 
6, 57, 58, 59, 60, 98, 60, 61, 61, 62, 199, 62, 63, 64, 64, 3, 65, 67, 68, 69, 
100, 70, 71, 72, 73, 169, 74, 75, 76, 77, 190, 78, 79, 80, 81, 250, 82, 83, 84, 85, 
84, 87, 88, 89, 90, 5, 91, 92, 93, 94, 144, 95, 96, 97, 98, 255, 99, 100, 101, 102, 
147, 103, 105, 106, 107, 83, 108, 110, 111, 112, 149, 113, 114, 115, 116, 147, 117, 119, 120, 121, 
147, 122, 124, 125, 126, 27, 127, 128, 129, 130, 91, 130, 131, 132, 133, 1, 134, 135, 136, 137, 
240, 138, 139, 139, 140, 191, 141, 142, 143, 144, 22, 145, 146, 147, 148, 27, 148, 149, 150, 151, 
255, 151, 152, 153, 154, 15, 155, 156, 158, 159, 84, 160, 161, 162, 163, 22, 164, 165, 166, 167, 
148, 168, 169, 170, 171, 170, 172, 173, 174, 175, 78, 176, 177, 179, 180, 165, 181, 182, 183, 184, 
14, 185, 186, 188, 189, 85, 190, 191, 192, 193, 192, 194, 195, 196, 196, 191, 197, 198, 199, 200, 
5, 201, 202, 203, 204, 175, 204, 205, 206, 207, 86, 208, 209, 210, 211, 5, 212, 213, 214, 215, 
80, 216, 217, 218, 219, 86, 220, 221, 222, 223, 21, 224, 225, 226, 227, 0, 228, 229, 230, 231, 
84, 232, 233, 234, 235, 86, 236, 237, 238, 239, 233, 240, 241, 242, 243, 36, 245, 246, 247, 255, 
},
},
//2.5

};











#endif //#if ENABLE_GAMMA == ON
