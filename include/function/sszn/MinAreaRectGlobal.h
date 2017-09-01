
#ifndef __MIN_AREA_RECT_GLOBAL_H_
#define __MIN_AREA_RECT_GLOBAL_H_


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */
#include "BaseStruct.h"
#include "TaskGlobal.h"

#define MAX_SIDE_POINT_NUM      65535

typedef enum {
	ERROR_TYPE_ID = 0,
	MIN_AREA_RECT_OK_NG_ID,
    MIN_AREA_RECT_CENTER_X_ID,
    MIN_AREA_RECT_CENTER_Y_ID,
    MIN_AREA_RECT_THETA_ID,
    MIN_AREA_RECT_DEGREE_ID,
    MIN_AREA_RECT_ROTATE_THETA_ID,
    MIN_AREA_RECT_ROTATE_DEGREE_ID,
    MIN_AREA_RECT_HALF_WIDTH_ID,
    MIN_AREA_RECT_HALF_HIGH_ID,
   	MIN_AREA_RECT_POINT_1_X_ID,
   	MIN_AREA_RECT_POINT_1_Y_ID,
   	MIN_AREA_RECT_POINT_2_X_ID,
	MIN_AREA_RECT_POINT_2_Y_ID,
	MIN_AREA_RECT_POINT_3_X_ID,
   	MIN_AREA_RECT_POINT_3_Y_ID,
   	MIN_AREA_RECT_POINT_4_X_ID,
	MIN_AREA_RECT_POINT_4_Y_ID,
    MIN_AREA_RECT_END
} PPMP_Result;

typedef struct {
	unsigned int ok_Ng_falg;
    POINT_F centre_point;
    float theta;
    float degree;
	float rotate_theta;
	float rotate_degree;
	float Half_Width;
	float Half_high;
	POINT_F point1;
	POINT_F point2;
	POINT_F point3;
	POINT_F point4;
}MAR_RESULT;

typedef struct {
	int pixel_rate;
	int rect_shape;
	int compress_flag;
} MAR_INPUT_PARAM;

typedef struct {
    OUTPUT_COMMON_PARAM	common_param;	/* common parameter */
} MAR_OUTPUT_PARAM;

typedef struct {
   MAR_RESULT  model_pmar_result; 
} MAR_PRIVATE_PARAM;

typedef struct {
    TASK_STEP_HEADER *pStepHeader;
    MAR_INPUT_PARAM *pMARInputParam;
    MAR_OUTPUT_PARAM *pMAROutputParam;
    MAR_PRIVATE_PARAM *pMARPrivateParam;
}TASK_MINAREARECT;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif

