/**
  * @file  [LinesCrossPointGlobal.h]
  * @brief  两线交点对外接口函数
  * @author  <Terry>
  * @date  <2017/5/11>
  * @version  <v1.0>
  * @note
  *
  */
#ifndef _LINES_CROSS_POINT_GLOBAL_H_
#define _LINES_CROSS_POINT_GLOBAL_H_
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */
#include "BaseStruct.h"
#include "TaskGlobal.h"

#define LLCP_LINE1_SELECT 0
#define LLCP_LINE2_SELECT 1

typedef enum {
	ERROR_TYPE_ID = 0,
    LLCP_CROSS_POINT_X_ID,
    LLCP_CROSS_POINT_Y_ID,
    LLCP_PHY_CROSS_POINT_X_ID,
    LLCP_PHY_CROSS_POINT_Y_ID,
    LLCP_ENUM_END
} Line2Line_Cross_Point_Result;

typedef struct {
    POINT_F point_pixel;
    POINT_F point_phy;
}L2L_CROSS_POINT_RESULT;

typedef struct {
} L2L_CROSS_POINT_INPUT_PARAM;

typedef struct {
    OUTPUT_COMMON_PARAM	common_param;	/* common parameter */
} L2L_CROSS_POINT_OUTPUT_PARAM;

typedef struct {
    PRIVATE_COMMON_PARAM private_common;		/* 私有数据的公共结构体 */
    L2L_CROSS_POINT_RESULT model_l2l_corss_point_result;/* 设模板时线与线交点的参数 */
} L2L_CROSS_POINT_PRIVATE_PARAM;

typedef struct {
    TASK_STEP_HEADER *pStepHeader;
    L2L_CROSS_POINT_INPUT_PARAM *pLLCPInputParam;
    L2L_CROSS_POINT_OUTPUT_PARAM *pLLCPOutputParam;
    L2L_CROSS_POINT_PRIVATE_PARAM *pLLCPPrivateParam;
}TASK_L2L_CROSS_POINT_CALC;
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif
