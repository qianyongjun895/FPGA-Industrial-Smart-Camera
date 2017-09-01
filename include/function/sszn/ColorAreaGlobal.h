/**
  * @file  [ColorAreaGlobal.h]
  * @brief  彩色面积对外接口函数
  * @author  <Terry>
  * @date  <2017/6/20>
  * @version  <v1.0>
  * @note
  *
  */
#ifndef _COLOR_AREA_GLOBAL_H_
#define _COLOR_AREA_GLOBAL_H_
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */
#include "BaseStruct.h"
#include "TaskGlobal.h"

typedef enum {
	ERROR_TYPE_ID = 0,
    COLOR_AREA_OK_NG_ID,
    COLOR_AREA,
    COLOR_AREA_END
} Color_Area_Result;

typedef struct {
    int detect_ok_ng_flag;	/* 检测OK\NG标志 */
    unsigned int area;		/* 面积值 */
} COLOR_AREA_RESULT;

typedef struct {
    THRESHOLD_INT area_threshold;	/* 面积大小的有效范围 */
} COLOR_AREA_INPUT_PARAM;

typedef struct {
    OUTPUT_COMMON_PARAM	common_param;	/* common parameter */
} COLOR_AREA_OUTPUT_PARAM;

typedef struct {
    /* 模板设置时得出的中间变量 */
    PRIVATE_COMMON_PARAM private_common;		/* 私有数据的公共结构体 */
    COLOR_AREA_RESULT model_area_rst;	/* 模板设置的时候结果 */
} COLOR_AREA_PRIVATE_PARAM;

typedef struct {
    TASK_STEP_HEADER *pStepHeader;
    COLOR_AREA_INPUT_PARAM *pColorAreaInputParam;
    COLOR_AREA_OUTPUT_PARAM *pColorAreaOutputParam;
    COLOR_AREA_PRIVATE_PARAM *pColorAreaPrivateParam;
}TASK_COLOR_AREA_CHECK;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif

