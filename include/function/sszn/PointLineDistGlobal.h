/**
  * @file  [PointLineDistGlobal.h]
  * @brief  点到直线距离对外接口函数
  * @author  <Terry>
  * @date  <2017/5/11>
  * @version  <v1.0>
  * @note
  *
  */
#ifndef _POINT_LINE_DIST_GLOBAL_H_
#define _POINT_LINE_DIST_GLOBAL_H_
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */
#include "BaseStruct.h"
#include "TaskGlobal.h"

#define PLD_POINT_SELECT 0
#define PLD_LINE_SELECT 1

typedef enum {
	ERROR_TYPE_ID = 0,
    PLD_POINT_LINE_DIST_ID,
    PHY_PLD_POINT_LINE_DIST_ID,
    PLD_STROKE_POINT_X_ID,
    PLD_STROKE_POINT_Y_ID,
    PLD_ENUM_END
} Point2Line_Result;

typedef struct {
    double  distance;       /* 点到线的像素距离 */
    double  phy_distance;   /* 点到线的物理距离 */
    POINT_F stroke_point;   /* 点到线的垂点 */
}P2L_DIST_RESULT;

typedef struct {
    unsigned int pix_phy_flag;      /* 0：像素值， 1：物理值 */
    THRESHOLD_FLOAT valid_range;    /* 有效范围数据 */
} P2L_DIST_INPUT_PARAM;

typedef struct {
    OUTPUT_COMMON_PARAM	common_param;	/* common parameter */
} P2L_DIST_OUTPUT_PARAM;

typedef struct {
    PRIVATE_COMMON_PARAM private_common;	/* 私有数据的公共结构体 */
    P2L_DIST_RESULT	model_p2l_dist_result;	/* 设模板时候的结果 */
} P2L_DIST_PRIVATE_PARAM;

typedef struct {
    TASK_STEP_HEADER *pStepHeader;
    P2L_DIST_INPUT_PARAM *pP2LDistInputParam;
    P2L_DIST_OUTPUT_PARAM *pP2LDistOutputParam;
    P2L_DIST_PRIVATE_PARAM *pP2LDistPrivateParam;
}TASK_P2L_DIST_CALC;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif
