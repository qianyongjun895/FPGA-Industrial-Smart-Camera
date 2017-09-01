/**
  * @file  [ParallelLinesDistGlobal.h]
  * @brief  两线距离对外接口函数
  * @author  <Terry>
  * @date  <2017/5/11>
  * @version  <v1.0>
  * @note
  *
  */
#ifndef _PARALLEL_LINES_DIST_GLOBAL_H_
#define _PARALLEL_LINES_DIST_GLOBAL_H_
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */
#include "BaseStruct.h"
#include "TaskGlobal.h"
#define L2LD_THETA_DELTA_MAX	(M_PI/180)
#define L2LD_DEGREE_DELTA_MAX	1.0
#define LLD_LINE1_SELECT        0
#define LLD_LINE2_SELECT        1

typedef enum {
	ERROR_TYPE_ID = 0,
    LLD_POINT1_X_ID,
    LLD_POINT1_Y_ID,
    LLD_POINT2_X_ID,
    LLD_POINT2_Y_ID,
    LLD_LINE_LINE_DIST_ID,
    PHY_LLD_LINE_LINE_DIST_ID,
    LLD_ENUM_END
} Line2Line_Dist_Result;

typedef struct {
    POINT_F point1;             /* 线1上的点 */
    POINT_F point2;             /* 线1到线2的垂点 */
    double  distance;           /* 两条线的像素距离 */
    double  phy_distance;       /* 两条线的物理距离 */
}L2L_DIST_RESULT;

typedef struct {
    unsigned int pix_phy_flag;		/* 0：像素值， 1：物理值 */
    THRESHOLD_FLOAT valid_range;	/* 有效范围数据 */
} L2L_DIST_INPUT_PARAM;

typedef struct {
    OUTPUT_COMMON_PARAM	common_param;	/* common parameter */
} L2L_DIST_OUTPUT_PARAM;

typedef struct {
    PRIVATE_COMMON_PARAM private_common;	/* 私有数据的公共结构体 */
    L2L_DIST_RESULT model_l2l_distance_result;
} L2L_DIST_PRIVATE_PARAM;

typedef struct {
    TASK_STEP_HEADER *pStepHeader;
    L2L_DIST_INPUT_PARAM *pL2LDistInputParam;
    L2L_DIST_OUTPUT_PARAM *pL2LDistOutputParam;
    L2L_DIST_PRIVATE_PARAM *pL2LDistPrivateParam;
}TASK_L2L_DIST_CALC;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif
