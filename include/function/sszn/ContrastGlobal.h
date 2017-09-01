/**
  * @file  [ContrastGlobal.h]
  * @brief  对比度对外接口函数
  * @author  <Terry>
  * @date  <2017/5/11>
  * @version  <v1.0>
  * @note
  *
  */
#ifndef _CONTRAST_GLOBAL_H_
#define _CONTRAST_GLOBAL_H_
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */
#include "BaseStruct.h"
#include "TaskGlobal.h"

typedef enum {
    ERROR_TYPE_ID = 0,
	CONTRAST_OK_NG_ID,
    CONTRAST_ID,
    CONTRAST_END
} Contrast_Result;

typedef struct {
    int detect_ok_ng_flag;		/* 检测OK\NG标志 */
    unsigned int contrast;		/* 测量出的对比度 */
}CONTRAST_RESULT;

typedef struct {
    THRESHOLD_INT valid_contrast_range;	/* 有效对比度范围，1-100 */
} CONTRAST_INPUT_PARAM;

typedef struct {
    OUTPUT_COMMON_PARAM	common_param;	/* common parameter */
} CONTRAST_OUTPUT_PARAM;

typedef struct {
    /* 模板设置时得出的中间变量 */
    PRIVATE_COMMON_PARAM private_common;		/* 私有数据的公共结构体 */
    CONTRAST_RESULT model_contrast_rst;			/* 模板设置的时候结果 */
} CONTRAST_PRIVATE_PARAM;

typedef struct {
    TASK_STEP_HEADER *pStepHeader;
    CONTRAST_INPUT_PARAM *pConInputParam;
    CONTRAST_OUTPUT_PARAM *pConOutputParam;
    CONTRAST_PRIVATE_PARAM *pConPrivateParam;
}TASK_CONTRAST_CHECK;
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif
