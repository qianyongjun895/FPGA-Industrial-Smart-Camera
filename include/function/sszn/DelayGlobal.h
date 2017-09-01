/**
  * @file  [DelayGlobal.h]
  * @brief  包含其他任务相关头文件
  * @author  <Terry>
  * @date  <2017/5/20>
  * @version  <v1.0>
  * @note
  *
  */
#ifndef __DELAY_GLOBAL_H__
#define __DELAY_GLOBAL_H__
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include "BaseStruct.h"
#include "TaskGlobal.h"

typedef enum {
    ERROR_TYPE_ID = 0,
	DELAY_MS_ID,
    DELAY_END
} Delay_Result;

typedef struct {
    float total_ms;
}DELAY_RESULT;

typedef struct {
    unsigned int minutes;       //分
    unsigned int seconds;       //秒
    unsigned int ms;            //毫秒
    unsigned int us;            //微秒
} DELAY_INPUT_PARAM;

typedef struct {
    OUTPUT_COMMON_PARAM	common_param;	/* common parameter */
} DELAY_OUTPUT_PARAM;

typedef struct {
    PRIVATE_COMMON_PARAM private_common;	/* 私有数据的公共结构体 */
} DELAY_PRIVATE_PARAM;

typedef struct {
    TASK_STEP_HEADER *pStepHeader;
    DELAY_INPUT_PARAM *pDelayInputParam;
    DELAY_OUTPUT_PARAM *pDelayOutputParam;
    DELAY_PRIVATE_PARAM *pDelayPrivateParam;
}TASK_DELAY;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __TASKMANAGE_H__ */
