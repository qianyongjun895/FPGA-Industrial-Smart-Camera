/**
  * @file  [MiddleLineGlobal.h]
  * @brief  两线中线对外接口函数
  * @author  <Terry>
  * @date  <2017/5/11>
  * @version  <v1.0>
  * @note
  *
  */
#ifndef _MIDDLE_LINE_GLOBAL_H_
#define _MIDDLE_LINE_GLOBAL_H_
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */
#include "BaseStruct.h"
#include "TaskGlobal.h"

#define LLML_LINE1_SELECT 0
#define LLML_LINE2_SELECT 1

#define ACUTE_MIDDLE 	0	//锐角中分线
#define OBTUSE_MIDDLE	1	//钝角中分线

typedef enum {
	ERROR_TYPE_ID = 0,
    LLML_THETA_ID,
    LLML_DEGREE_ID,
    LLML_ROTATE_DEG_ID,
    LLML_COS_ID,
    LLML_SIN_ID,
    LLML_POINT_X_ID,
    LLML_POINT_Y_ID,
    LLML_PHY_POINT_X_ID,
    LLML_PHY_POINT_Y_ID,
    LLML_END
} L2L_Middle_Result;

typedef struct {
    LineParameter middle_line_rst;
}LLML_RESULT;

typedef struct {
    unsigned int middle_type;	/* 选择求的是钝角还是锐角的中分线 */
} LLML_INPUT_PARAM;

typedef struct {
    OUTPUT_COMMON_PARAM	common_param;       /* common parameter */
    LineParameter line_result;              /* 计算出来的中分线参数 */
} LLML_OUTPUT_PARAM;

typedef struct {
    PRIVATE_COMMON_PARAM private_common;    /* 私有数据的公共结构体 */
    LLML_RESULT l2l_middle_line_rst;        /* 中分线取模板时的结果 */
} LLML_PRIVATE_PARAM;

typedef struct {
    TASK_STEP_HEADER *pStepHeader;
    LLML_INPUT_PARAM *pLlmlInputParam;
    LLML_OUTPUT_PARAM *pLlmlOutputParam;
    LLML_PRIVATE_PARAM *pLlmlPrivateParam;
}TASK_L2L_MIDDLE_CALC;
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif
