/**
  * @file  [PointsLineGlobal.h]
  * @brief  两点线段对外接口函数
  * @author  <Terry>
  * @date  <2017/5/11>
  * @version  <v1.0>
  * @note
  *
  */
#ifndef _POINTS_LINE_GLOBAL_H_
#define _POINTS_LINE_GLOBAL_H_
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */
#include "BaseStruct.h"
#include "TaskGlobal.h"

#define PPL_POINT1_SELECT 0
#define PPL_POINT2_SELECT 1

typedef enum {
	ERROR_TYPE_ID = 0,
    P2PL_THETA_ID,
    P2PL_DEGREE_ID,
    P2PL_ROTATE_DEG_ID,
    P2PL_COS_ID,
    P2PL_SIN_ID,
    P2PL_POINT_X_ID,
    P2PL_POINT_Y_ID,
    P2PL_PHY_POINT_X_ID,
    P2PL_PHY_POINT_Y_ID,
    P2PL_END
} P2P_Line_Result;

typedef struct {
    LineParameter p2p_line_rst;
}P2PL_RESULT;

typedef struct {
} P2PL_INPUT_PARAM;

typedef struct {
    OUTPUT_COMMON_PARAM	common_param;	/* common parameter */
} P2PL_OUTPUT_PARAM;

typedef struct {
    PRIVATE_COMMON_PARAM private_common;    /* 私有数据的公共结构体 */
    P2PL_RESULT p2p_line;                   /* 中分线取模板时的结果 */
} P2PL_PRIVATE_PARAM;

typedef struct {
    TASK_STEP_HEADER *pStepHeader;
    P2PL_INPUT_PARAM *pP2PLineInputParam;
    P2PL_OUTPUT_PARAM *pP2PLineOutputParam;
    P2PL_PRIVATE_PARAM *pP2PLinePrivateParam;
}TASK_P2P_LINE;
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif
