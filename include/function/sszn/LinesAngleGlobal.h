/**
  * @file  [LinesAngleGlobal.h]
  * @brief  两线夹角对外接口函数
  * @author  <Terry>
  * @date  <2017/5/11>
  * @version  <v1.0>
  * @note
  *
  */
#ifndef _LINES_ANGLE_GLOBAL_H_
#define _LINES_ANGLE_GLOBAL_H_
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */
#include "BaseStruct.h"
#include "TaskGlobal.h"

#define ACUTE_ANGLE 0   //锐角
#define OBTUSE_ANGLE 1  //钝角
#define LLA_LINE1_SELECT 0
#define LLA_LINE2_SELECT 1

typedef enum {
	ERROR_TYPE_ID = 0,
    LLA_LINE_LINE_ANGLE_ID,
    LLA_CROSS_POINT_X_ID,
    LLA_CROSS_POINT_Y_ID,
    LLA_ENUM_END
} Line2Line_Angle_Result;

typedef struct {
    double  angle;		/* 两条线的夹角 */
    POINT_F cross_point;	/* 交点 */
}L2L_ANGLE_RESULT;

typedef struct {
    unsigned int angle_type;	/* 用于区分钝角和锐角 */
    THRESHOLD_FLOAT valid_range;	/* 有效范围数据 */
} L2L_ANGLE_INPUT_PARAM;

typedef struct {
    OUTPUT_COMMON_PARAM	common_param;	/* common parameter */
} L2L_ANGLE_OUTPUT_PARAM;

typedef struct {
    PRIVATE_COMMON_PARAM private_common;	/* 私有数据的公共结构体 */
    L2L_ANGLE_RESULT model_l2l_angle_result;	/* 设模板时线与线角度的参数 */
} L2L_ANGLE_PRIVATE_PARAM;

typedef struct {
    TASK_STEP_HEADER *pStepHeader;
    L2L_ANGLE_INPUT_PARAM *pL2LAngleInputParam;
    L2L_ANGLE_OUTPUT_PARAM *pL2LAngleOutputParam;
    L2L_ANGLE_PRIVATE_PARAM *pL2LAnglePrivateParam;
}TASK_L2L_ANGLE_CALC;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif
