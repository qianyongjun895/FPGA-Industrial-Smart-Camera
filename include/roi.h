/*
 * roi.h
 *
 *  Created on: 2015-11-18
 *      Author: terry
 */

#ifndef ROI_H_
#define ROI_H_
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#ifndef roiHighColor
#define roiHighColor 0xff
#endif
#ifndef uchar
#define uchar unsigned char
#endif
#ifndef bool
#define bool int
#endif
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define CONNECTIVITY4	4
#define CONNECTIVITY8	8
#define CONNECTIVITY_DEF_NUM	CONNECTIVITY4
#define EROSION_ROUND_DFT_NUM 	1
#define EROSION_ROUND_NO_CONNECT_NUM 	2
#define EROSION_MIN_NUM	6
#define EROSION_MAX_NUM	8
#define MAX_AREA_NUM 2000
#define MIN_HITS					8//2
#define DISTANCE_ANTI_OVERLAY		3
#define ANGLE_DIFF_ANTI_OVERLAY		384
#define RANGE_CALC_AVG_DIR			4
#define RANGE_SQR_INV_CALC_AVG_DIR	0.111111111111111111111
#define NUM_PRECISE_ITERATION		5
#define NUM_MAX_CANDIDATE			4096
#define NUM_MAX_CANDIDATES_CALC_AVG 32

#define _ROI_ANGLE_1     128
#define _ROI_ANGLE_5     640	//(_ROI_ANGLE_1*5)
#define _ROI_ANGLE_10    1280	//(_ROI_ANGLE_1*10)
#define _ROI_ANGLE_15    1920	//(_ROI_ANGLE_1*15)
#define _ROI_ANGLE_30    3840	//(_ROI_ANGLE_1*30)
#define _ROI_ANGLE_45    5760	//(_ROI_ANGLE_1*45)
#define _ROI_ANGLE_90    11520	//(_ROI_ANGLE_1*90)
#define _ROI_ANGLE_180   23040	//(_ROI_ANGLE_1*180)
#define _ROI_ANGLE_270   34560	//(_ROI_ANGLE_1*270)
#define _ROI_ANGLE_360   46080	//(_ROI_ANGLE_1*360)
#define _ROI_ANGLE_630	 80640	//(_ROI_ANGLE_1*630)
#define _ROI_ANGLE_720   92160	//(_ROI_ANGLE_1*720)
#define _ROI_MAX_GEO_IMAGE_SIZE					256
#define _ROI_NUM_SEEDS							16
#define _ROI_NUM_SEED_FEATURES					16
#define _ROI_MAX_FULL_FEATURE_RELATIONSHIPS		16384
#define _ROI_MAX_CANDIDATES_CALC_AVG			512
#define _ROI_MAX_CANDIDATES_SCORING				32

#define CONVERT_SKELETON_DEGREE2THETA(degree) (((float)degree/128)*0.0174533)
#define CONVERT_SKELETON_THETA2DEGREE(theta) (((float)theta/0.0174533)*128)
#define _ROI_SATURATION_TABLE_START_INDEX_ 1024
#define __ROI_SATURATION_TABLE__ \
{ \
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, \
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, \
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, \
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, \
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, \
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, \
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, \
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, \
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, \
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, \
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, \
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, \
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, \
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, \
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, \
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, \
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, \
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, \
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, \
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, \
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, \
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, \
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, \
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, \
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, \
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, \
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, \
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, \
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, \
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, \
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, \
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, \
    0,   1,   2,   3,   4,   5,   6,   7,   8,   9,   10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31, \
    32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,  48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,  63, \
    64,  65,  66,  67,  68,  69,  70,  71,  72,  73,  74,  75,  76,  77,  78,  79,  80,  81,  82,  83,  84,  85,  86,  87,  88,  89,  90,  91,  92,  93,  94,  95, \
    96,  97,  98,  99,  100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, \
    128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, \
    160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, \
    192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, \
    224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 254, \
    254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, \
    254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, \
    254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, \
    254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, \
    254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, \
    254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, \
    254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, \
    254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, \
    254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, \
    254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, \
    254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, \
    254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, \
    254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, \
    254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, \
    254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, \
    254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, \
    254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, \
    254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, \
    254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, \
    254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, \
    254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, \
    254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, \
    254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, \
    254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, \
    254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, \
    254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, \
    254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, \
    254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, \
    254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, \
    254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, \
    254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, \
    254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, \
    254 \
}

typedef struct
{
	unsigned char table[256];
	unsigned int low_threshold;
	unsigned int high_threshold;
	unsigned int valid_flag;
}IMG_STRETCH_LUT;

typedef struct
{
	unsigned short xxx;
	unsigned short yyy;
} roiPoint_s;

typedef struct {
	unsigned int minX;
	unsigned int maxX;
	unsigned int minY;
	unsigned int maxY;
}COMP_RANGE;

typedef struct
{
	int totalPoints;
	int minX;
	int maxX;
	int minY;
	int maxY;
	int width;
	int height;
	int orthocenterX;
	int orthocenterY;
	int boundary_flag;
	roiPoint_s * points;
} roiConnectedComponent;

typedef struct
{
	double m00, m10, m01, m20, m11, m02, m30, m21, m12, m03;
	double mu20, mu11, mu02, mu30, mu21, mu12, mu03;
	double inv_sqrt_m00;
	double centerX, centerY;
} roiMoments;

typedef struct
{
    double hu1, hu2, hu3, hu4, hu5, hu6, hu7; /* Hu invariants */
}HuMoments;

typedef struct
{
	int fullWidth;
	int fullHeight;
	int minX;
	int maxX;
	int minY;
	int maxY;
	int width;
	int height;
} roiROI;

typedef struct
{
	int xxx;
	int yyy;
} roiPoint;

typedef struct
{
	int point5X;
	int point5Y;
	int direction;
	double score;
	int hasBeenPairedPoint;
} Point5;

typedef struct
{
	int iii;
	double ddd;
} roiIntDecimal;

typedef struct
{
	double theta;
	double cos;
	double sin;
	double xxx;
	double yyy;
} roiLineParameter;

typedef struct {
	short x;
	short y;
	int theta;
} FPGA_CALC_POINT;

typedef struct {
	float distance;
	int deviationAngle;
	int directionDifference;
	int polarity;
} roiGeoRelationship;

typedef struct
{
	double xxx;
	double yyy;
} roiPointDecimal;

typedef struct {
	float distance;
	int deviationAngle;
	uchar scalar;
} roiGeoRelationshipGrayscale;

typedef struct {
	double seedX;
	double seedY;
	int seedDirection;
	int indexPairedPoint;
	roiGeoRelationship pairedRelationship;
	int multiShotAngleStep;
	roiGeoRelationship originRelationship;
} roiGeoSeed;

typedef struct {
	double originX;
	double originY;
	int originDirection;
	roiGeoSeed seeds[_ROI_NUM_SEEDS];
	int numSearchFeatureRelationships;
	int numPreciseFeatureRelationships;
	int numFullFeatureRelationships;
	roiGeoRelationship fullFeatureRelationships[_ROI_MAX_FULL_FEATURE_RELATIONSHIPS];
	int primaryDirection;
	int preciseRange;
	int numPolarityPrimaryDirections;
	int numPolaritySecondaryDirections;
} roiGeoPattern;

typedef struct {
	int numCandidates;
	int numOptimizations;
	double score;
	double matchX;
	double matchY;
	int matchDirection;
	const roiGeoPattern * pattern;
} roiGeoMatch;

typedef struct
{
	double xSubPix;
	double ySubPix;
	int direction;
	double score;
} FeaturePoint;

typedef struct
{
	int x;
	int y;
	uchar scalar;
	short edgeValue;
} FeaturePointGrayscale;

typedef struct {
	double x;
	double y;
} GeoFeaturePoint;

extern short _roiGeoLookupDirectionTable[_ROI_MAX_GEO_IMAGE_SIZE*2][_ROI_MAX_GEO_IMAGE_SIZE*2];
extern double _roiGeoLookupCircleOffsetXTable[_ROI_ANGLE_360];
extern double _roiGeoLookupCircleOffsetYTable[_ROI_ANGLE_360];
extern double _roiGeoScaleThetaToAngle;
inline roiROI _roiCreate(const int _fullWidth, const int _fullHeigth, int _minX, int _maxX, int _minY, int _maxY);
inline roiROI _roiCreateWholeImage(const int fullWidth, const int fullHeight);
inline int roiRound(const double value);
inline void roiCopy(const unsigned char * src, unsigned char * dst, const roiROI * roi);
inline void roiErode(const uchar * srcBuffer, uchar * destBuffer, const roiROI * roi, const int minCount, const int maxCount);
inline void roiSmooth(const unsigned char * srcBuffer, unsigned char * destBuffer, const roiROI * roi);
inline void roiSharpen(const unsigned char * srcBuffer, unsigned char * destBuffer, const roiROI * roi);
inline void roiEdgeTransform(const unsigned char * src, short * dst16, const roiROI * roi);
inline void roiSet(unsigned char * buffer, const unsigned char value, const roiROI * roi);
inline void roiEdgeMaxima2(const uchar * src, uchar * dst, roiPoint_s *edgePoint, int *pedgePointNum, short * edge16, const roiROI * roi, const int threshold);
inline void roiEdgeMaxima2DilateSimple(const uchar * src, uchar * dst, uchar *dilatedst, GeoFeaturePoint *edgePoint, int *pEdgePointPos, int *pedgePointNum, short * edge16, const roiROI * roi, const int threshold);
inline void roiEdgeMaxima2DilateSimpleCalcDirection(const uchar * src, uchar * dst, uchar *dilatedst, int *directions, roiPoint_s *edgePoint, int *pedgePointNum, short * edge16, const roiROI * roi, const int threshold);
void roiDilateSimple(const uchar * src, uchar * dst, const roiROI * roi);
int roiEdgeXY2SubPixelXY(const short * edge16, const int _x, const int _y, const int width, const int height, double * outX, double * outY);
int roiToFeaturePointsExt(
		const uchar * mask,
		const short * edge16,
		const int * directions,
		const roiROI * roi,
		const FeaturePoint * existingFeaturePoints,
		const int numExistingFeaturePoints,
		FeaturePoint * outFeaturePoints
		);
inline roiLineParameter roiFitLine2(const roiPointDecimal * points, const int numPoints);
inline roiLineParameter roiFitLine2Iterated(
		const roiPointDecimal * points,
		const int numPoints,
		const int numAccept,
		int numFitIterations,
		void * workBuffer
		);
inline int roiFindConnectedComponents(
		const uchar * data,
		const roiROI * roi,
		uchar * workBuffer,
		roiPoint_s * points,
		roiConnectedComponent * comps,
		const int connectivity4or8,
		int filterMinTotalPoints,
		const int maxConnectedComponents
		);
inline int roiFilterConnectedComponentsByFunction(
		roiConnectedComponent * connectedComponents,
		const int numConnectedComponents,
		int (*func)(roiConnectedComponent*, const void*, const void*, const void*, const void*),
		const void * param0,
		const void * param1,
		const void * param2,
		const void * param3
		);
void compRangeCenterCalc(roiPoint_s *centerPoint, roiConnectedComponent * comps, COMP_RANGE *comp_range);
inline void roiCalcMomentsSingleConnectedComponent(const roiConnectedComponent * comp, roiMoments *pOutMoments);
inline double roiCalcMomentsAspectRatio(const roiMoments * moments, const double momentsAngle);
inline double roiCalcMomentsAngle(const roiMoments * moments);
inline void roiCalcMomentsAspectLength(const roiMoments * moments, const double momentsAngle, double *height, double *width);
inline void roiCalcConnectedComponentCenter(const roiConnectedComponent * comp, roiPointDecimal *pCenter);
inline void roiCalcMaxMinPointComponent(const roiConnectedComponent * comp, roiPointDecimal centerPoint, double theta, roiPoint_s *point_max_dist, roiPoint_s *point_min_dist);
inline void roiFindMaxDistPointComponent(const roiConnectedComponent * comp, roiPointDecimal centerPoint, double theta, roiPoint_s *point_max_dist);
inline void roiCalcConnectedComponentAngleCenterLengthWidth(const roiConnectedComponent * comp, double * outAngle, double * outCenterX, double * outCenterY, double * outLength, double * outWidth);
inline int roiCalcPointAtLineLeftRightSide(double pointX, double pointY, double lineX0, double lineY0, double lineX1, double lineY1);
inline int roiCalcLeftMoreThanRight(const roiConnectedComponent * comp, roiPointDecimal centerPoint, double theta);
inline int roiSum(const unsigned char * srcBuffer, const roiROI * roi);
inline void roiMultiplyS(const unsigned char * src, unsigned char * dst, double num, int isSaturationNeeded, const roiROI * roi);
inline void roiThreshold16(const short * src, unsigned char * dst, const int threshold, const roiROI * roi, const int reverse, const int isAbs);
inline double roiGetXYInterpolatedScalar(const uchar * data, const int width, const double xxx, const double yyy);
int ImageStretchByHistogram(roiROI *roi, unsigned char *srcData, unsigned char *dstData);
int ImageStretchByLUT(roiROI *roi, unsigned char *srcData, unsigned char *dstData);
int ImageStretchLutCreate(unsigned char low_threshold, unsigned char high_threshold);
inline void _roiInitLookupTables(void);
inline int calcDirectionDifference180(int direction0, int direction1);
inline int calcDirectionDifference90(int direction0, int direction1);
inline int _roiCalcPointDirection(const uchar * src, int width, int pos);
inline void roiCalcMaskDirections(const uchar * src, uchar * mask, int * directions, const roiROI * roi);
inline void roiCalcMaskStabilities(uchar * src, roiROI * roi, uchar * mask, int * directions, int * stabilities, int numBlursForStability, int angleThresholdStability);
inline void roiCalcMaskLinearities(uchar * src, uchar * mask, int * directions, int * linearities, roiROI * roi, int rangeForLinearity, int angleThresholdLinearity);
inline void _roiCalcGeoRelationship(double activePointX, double activePointY, int activePointDirection, double referencePointX, double referencePointY, int referencePointDirection, const int polarity, roiGeoRelationship * geoRelationship);
inline void _roiCalcRelativePointXYDirection(const GeoFeaturePoint *pfeaturePoint, int direction, const roiGeoRelationship * relationship, GeoFeaturePoint *pOutPos, int * outDirection);
inline int _roiCalcRelativePointDirectionDifference(GeoFeaturePoint *pfeaturePoint, int direction, roiGeoRelationship * relationship, roiROI * searchROI, uchar * mask, int * directions, int defaultDirectionDifference);
inline double calcPointScore(int contrast, int stability, int linearity, int isBoundary);
inline int roiToPoints5(uchar * mask, roiROI * roi, Point5 * outPoints5, double originX, double originY, int * directions, short * edge16, int * stabilities, int * linearities);
inline int _comparePoints5ByScore(const void * _v0, const void * _v1);
inline int findSeedPairedPoint(Point5 * featurePoints5, int numFeaturePoints, int indexSeed, Point5 * seed);
void roiTopEdge(const uchar * srcBuffer, uchar * destBuffer, const roiROI * roi, const int clearDstFirst, const int continuousPaint);
void roiBottomEdge(const uchar * srcBuffer, uchar * destBuffer, const roiROI * roi, const int clearDstFirst, const int continuousPaint);
void roiLeftEdge(const uchar * srcBuffer, uchar * destBuffer, const roiROI * roi, const int clearDstFirst, const int continuousPaint);
void roiRightEdge(const uchar * srcBuffer, uchar * destBuffer, const roiROI * roi, const int clearDstFirst, const int continuousPaint);
void roiFilterMaskBoundaries(uchar * mask, short * edge16, const int * directions, const roiROI * roi, uchar * workBuffer);
inline void roiPlotMask(uchar * data, const uchar * mask, const int width, const int height, const uchar scalar);
void roiThreshold(const uchar * src, uchar * dst, const int threshold, const roiROI * roi, const bool reverse);
int _compareFeaturePointsGrayscale(const void * _v0, const void * _v1);
int _compareFeaturePointByScore(const void * _v0, const void * _v1);
int _compareGeoMatchByScore(const void * _m0, const void * _m1);
double roiCalcPointDistanceSquare(const double xx0, const double yy0, const double xx1, const double yy1);
void roiLineParameterCheckCos(roiLineParameter * lineParam);
void roiFilterMaskUniquities(const uchar * src, uchar * mask, short * edge16, const int * directions, const roiROI * roi, uchar * workBuffer, const double rangeRatioForUniquity, const int angleThresholdForUniquity);
void _roiCalcGeoRelationshipGrayscale(double activePointX, double activePointY, uchar activePointScalar, double referencePointX, double referencePointY, int referencePointDirection, roiGeoRelationshipGrayscale * geoRelationshipGrayscale);
void mergeFeaturePoints(
		const FeaturePoint * featurePoints0,
		const int numFeaturePoints0,
		const FeaturePoint * featurePoints1,
		const int numFeaturePoints1,
		FeaturePoint * outFeaturePointsMerged,
		const int numFeaturePointsMerged
		);
int roiToFeaturePointsGrayscale(
		const uchar * edgeExt,
		const uchar * src,
		const short * edge16,
		const roiROI * roi,
		FeaturePointGrayscale * outFeaturePointsGrayscale
		);
void roiRansacFindBestLine(
		const uchar * src,
		const uchar * edge,
		const short * edge16,
		const roiROI * roi,
		roiLineParameter * outLineParam0,
		const int numTriesWildcard,
		const int numTriesCount,
		const int minDistance,
		uchar * plotBuffer
		);
int roiToFeaturePoints(
		const uchar * mask,
		const uchar * edgeBoundaries,
		const roiROI * roi,
		FeaturePoint * outFeaturePoints,
		int * directions,
		short * edge16,
		int * stabilities,
		int * linearities,
		const int baseDirection
		);
double _roiCalcRelativePointDirectionDifferenceScore(
		const GeoFeaturePoint *pFeaturePoint,
		const int direction,
		const roiGeoRelationship * relationship,
		const roiROI * searchROI,
		const uchar * edgeLow,
		const int * directions,
		const double angleThresholdOffsetX
		);
void roiErode3_cross(
        const uchar * srcBuffer,
        uchar * destBuffer,
        const roiROI * roi,
        const int minCount,
        const int maxCount,
        const int minRisingEdges,
        const int maxRisingEdges
        );
void roiFindConnectedComponentsAndPlot(
        const uchar * src,
        uchar * dst,
        const roiROI * roi,
        uchar * workBuffer,
        roiPoint_s * points,
        const int connectivity4or8,
        int filterMinTotalPoints_0MaxOnly,
        const int maxConnectedComponents
        );
inline int _roiCompareIntDecimalByDecimal(const void * pd0, const void * pd1);
double roiCalcLinePointDistance2(const roiLineParameter * lineParam, const double xxx, const double yyy);
int _calcAvgDirection(const uchar * src, const int * directions, const int width, const int height, const int x, const int y, const int pos, const int range, int * outAvgDirection);
int _calcAvgDirectionQuick(const uchar * src, const int direction0, const int width, const int height, const int maxX, const int maxY, GeoFeaturePoint *pFeaturePoint, int * outAvgDirection);
void _calcCandidatesAvg(roiGeoMatch * candidate0, roiGeoMatch * candidates, const int numCandidates, roiGeoMatch * outAvg);
int _calcPrecisePosition(const uchar * src, const roiGeoPattern * pattern, const roiROI * roi, const uchar * edgeLow, const short * edge16, const int * directions, const int angleThreshold, const int numIterations, roiGeoMatch * outMatch);
void calcMatchScoreByEdge(const uchar * src, const roiROI * roi, const roiGeoPattern * pattern, const uchar * edgeLow, const int * directions, roiGeoMatch * outMatch);
uchar roiCalcThresholdByScarcity(const unsigned int histogramCalculated[256], const int numTotalPoints, const unsigned int numScarce, const int reverse);
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif /* ROI_H_ */
