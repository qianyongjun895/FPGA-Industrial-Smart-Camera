/**
  * @file  [MeanBrightnessGlobal.h]
  * @brief  平均亮度对外接口函数
  * @author  <Terry>
  * @date  <2017/5/11>
  * @version  <v1.0>
  * @note
  *
  */
#ifndef _MEAN_BRIGHTNESS_GLOBAL_H_
#define _MEAN_BRIGHTNESS_GLOBAL_H_
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */
#include "BaseStruct.h"
#include "TaskGlobal.h"

typedef enum {
	ERROR_TYPE_ID = 0,
    MEAN_BRIGHTNESS_OK_NG_ID,
    MEAN_BRIGHTNESS_ID,
    MEAN_BRIGHTNESS_PIXEL_CNT_ID,
    MEAN_BRIGHTNESS_END
} MeanBrightness_Result;

typedef struct {
    int detect_ok_ng_flag;		/* 检测OK\NG标志 */
    unsigned int mean_brightness;	/* 测量出的平均亮度 */
    unsigned int total_area_num;	/* 参与计算的像素数 */
}MEANBRI_RESULT;

typedef struct {
    THRESHOLD_INT valid_brightness_range;	/* 有效的亮度范围 */
} MEANBRI_INPUT_PARAM;

typedef struct {
    OUTPUT_COMMON_PARAM	common_param;	/* common parameter */
} MEANBRI_OUTPUT_PARAM;

typedef struct {
    PRIVATE_COMMON_PARAM private_common;	/* 私有数据的公共结构体 */
    MEANBRI_RESULT model_meanbri_rst;		/* 模板设置的时候结果 */
} MEANBRI_PRIVATE_PARAM;

typedef struct {
    TASK_STEP_HEADER *pStepHeader;
    MEANBRI_INPUT_PARAM *pMeanBInputParam;
    MEANBRI_OUTPUT_PARAM *pMeanBOutputParam;
    MEANBRI_PRIVATE_PARAM *pMeanBPrivateParam;
}TASK_MEAN_BRIGHTNESS;
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif
