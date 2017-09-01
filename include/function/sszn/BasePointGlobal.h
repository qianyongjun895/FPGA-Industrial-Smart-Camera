/**
  * @file  [BasePointGlobal.h]
  * @brief  基准点对外接口函数
  * @author  <Terry>
  * @date  <2017/5/11>
  * @version  <v1.0>
  * @note
  *
  */
#ifndef _BASE_POINT_GLOBAL_H_
#define _BASE_POINT_GLOBAL_H_
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */
#include "BaseStruct.h"
#include "TaskGlobal.h"
#define BP_POINT_NUM_MAX			20
#define PARA_NUM_FOR_SINGLE_POINT	4
typedef enum {
	ERROR_TYPE_ID = 0,
    BASE_POINT_NUM,
    BASE_POINT0_X_ID,
    BASE_POINT0_Y_ID,
    BASE_POINT0_PHY_X_ID,
    BASE_POINT0_PHY_Y_ID,
    BASE_POINT_END = 82
} Base_Point_Result;

typedef struct {
    unsigned int point_num;					/* 点个数 */
    POINT_F pixel_point[BP_POINT_NUM_MAX];	/* 像素坐标 */
    POINT_F phy_point[BP_POINT_NUM_MAX];	/* 物理坐标 */
}BASE_POINT_RESULT;

typedef struct {
    unsigned int base_point_num;			/* 基准点个数 */
    POINT_I base_points[BP_POINT_NUM_MAX];	/* 基准点位置信息 */
} BASEPOINT_INPUT_PARAM;

typedef struct {
    OUTPUT_COMMON_PARAM	common_param;		/* common parameter */
} BASEPOINT_OUTPUT_PARAM;

typedef struct {
    PRIVATE_COMMON_PARAM private_common;	/* 私有数据的公共结构体 */
    BASE_POINT_RESULT model_base_point_result;
} BASEPOINT_PRIVATE_PARAM;

typedef struct {
    TASK_STEP_HEADER 		*pStepHeader;
    BASEPOINT_INPUT_PARAM 	*pBPInputParam;
    BASEPOINT_OUTPUT_PARAM 	*pBPOutputParam;
    BASEPOINT_PRIVATE_PARAM *pBPPrivateParam;
}TASK_BASE_POINT;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif
