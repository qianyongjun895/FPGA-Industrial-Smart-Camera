/**
  * @file  [MonoAreaGlobal.h]
  * @brief  黑白面积对外接口函数
  * @author  <Terry>
  * @date  <2017/6/20>
  * @version  <v1.0>
  * @note
  *
  */
#ifndef _MONO_AREA_GLOBAL_H_
#define _MONO_AREA_GLOBAL_H_
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */
#include "BaseStruct.h"
#include "TaskGlobal.h"

typedef enum {
	ERROR_TYPE_ID = 0,
	MONO_AREA_OK_NG_ID,
    MONO_AREA,
    MONO_AREA_END
} Mono_Area_Result;

typedef struct {
    int detect_ok_ng_flag;	/* 检测OK\NG标志 */
    unsigned int area;		/* 面积值 */
} MONO_AREA_RESULT;

#define CHECK_BLACK_AREA		0x0
#define CHECK_WHITE_AREA		0x1
typedef struct {
	unsigned int check_type;		/* 面积检测类型 */
    THRESHOLD_INT area_threshold;	/* 面积大小的有效范围 */
} MONO_AREA_INPUT_PARAM;

typedef struct {
    OUTPUT_COMMON_PARAM	common_param;	/* common parameter */
} MONO_AREA_OUTPUT_PARAM;

typedef struct {
    /* 模板设置时得出的中间变量 */
    PRIVATE_COMMON_PARAM private_common;		/* 私有数据的公共结构体 */
    MONO_AREA_RESULT model_area_rst;	/* 模板设置的时候结果 */
} MONO_AREA_PRIVATE_PARAM;

typedef struct {
    TASK_STEP_HEADER *pStepHeader;
    MONO_AREA_INPUT_PARAM *pMonoAreaInputParam;
    MONO_AREA_OUTPUT_PARAM *pMonoAreaOutputParam;
    MONO_AREA_PRIVATE_PARAM *pMonoAreaPrivateParam;
}TASK_MONO_AREA_CHECK;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif

