/**
  * @file  [GrayStatGlobal.h]
  * @brief  彩色面积对外接口函数
  * @author  <Terry>
  * @date  <2017/6/20>
  * @version  <v1.0>
  * @note
  *
  */
#ifndef _GRAY_STAT_GLOBAL_H_
#define _GRAY_STAT_GLOBAL_H_
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */
#include "BaseStruct.h"
#include "TaskGlobal.h"

typedef enum {
    ERROR_TYPE_ID = 0,
	GRAY_STAT_OK_NG_ID,
    GRAY_STAT_NUM,
    GRAY_STAT_END
} Gray_Stat_Result;

typedef struct {
    int detect_ok_ng_flag;	/* 检测OK\NG标志 */
    unsigned int pixel_num;	/* 有效像素数值 */
} GRAY_STAT_RESULT;

typedef struct {
    THRESHOLD_INT pixel_num_threshold;	/* 像素数量的有效范围 */
} GRAY_STAT_INPUT_PARAM;

typedef struct {
    OUTPUT_COMMON_PARAM	common_param;	/* common parameter */
} GRAY_STAT_OUTPUT_PARAM;

typedef struct {
    /* 模板设置时得出的中间变量 */
    PRIVATE_COMMON_PARAM private_common;	/* 私有数据的公共结构体 */
    GRAY_STAT_RESULT model_stat_rst;		/* 模板设置的时候结果 */
} GRAY_STAT_PRIVATE_PARAM;

typedef struct {
    TASK_STEP_HEADER *pStepHeader;
    GRAY_STAT_INPUT_PARAM *pGrayStatInputParam;
    GRAY_STAT_OUTPUT_PARAM *pGrayStatOutputParam;
    GRAY_STAT_PRIVATE_PARAM *pGrayStatPrivateParam;
}TASK_GRAY_STAT_CHECK;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif


