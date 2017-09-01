/**
  * @file  [BaseLineGlobal.h]
  * @brief  基准线对外接口函数
  * @author  <Terry>
  * @date  <2017/5/11>
  * @version  <v1.0>
  * @note
  *
  */
#ifndef _BASE_LINE_GLOBAL_H_
#define _BASE_LINE_GLOBAL_H_
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */
#include "BaseStruct.h"
#include "TaskGlobal.h"
#include "LineGlobal.h"
typedef struct {
    POINT_I line_points[2];
}BASE_LINE_INFO;
typedef struct{
    unsigned int base_line_num;
    BASE_LINE_INFO base_line_info[MULTI_LINE_NUM_MAX];
}BASE_LINE_INPUT_PARAM;

typedef struct {
    OUTPUT_COMMON_PARAM	common_param;	/* common parameter */
}BASE_LINE_OUTPUT_PARAM;

typedef struct {
    PRIVATE_COMMON_PARAM private_common;						/* 私有数据的公共结构体 */
    LineParameter model_base_line_result[MULTI_LINE_NUM_MAX];	/* save the center point and the cos(theta) and sin(theta) value */
}BASE_LINE_PRIVATE_PARAM;

typedef struct {
    TASK_STEP_HEADER *pStepHeader;
    BASE_LINE_INPUT_PARAM *pBLInputParam;
    BASE_LINE_OUTPUT_PARAM *pBLOutputParam;
    BASE_LINE_PRIVATE_PARAM *pBLPrivateParam;
}TASK_BASE_LINE;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif
