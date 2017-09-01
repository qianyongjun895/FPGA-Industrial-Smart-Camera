/**
  * @file  [WorkOverGlobal.h]
  * @brief  包含其他任务相关头文件
  * @author  <Terry>
  * @date  <2017/5/20>
  * @version  <v1.0>
  * @note
  *
  */
#ifndef __WORK_OVER_GLOBAL_H__
#define __WORK_OVER_GLOBAL_H__
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include "BaseStruct.h"
#include "TaskGlobal.h"

typedef struct {

} TASK_WORKOVER_INPUT_PARAM;

typedef struct {
    OUTPUT_COMMON_PARAM	common_param;	/* common parameter */
} TASK_WORKOVER_OUTPUT_PARAM;

typedef struct {
    PRIVATE_COMMON_PARAM private_common;	/* 私有数据的公共结构体 */
} TASK_WORKOVER_PRIVATE_PARAM;

typedef struct {
    TASK_STEP_HEADER *pStepHeader;
    TASK_WORKOVER_INPUT_PARAM *pTaskWorkOverInputParam;
    TASK_WORKOVER_OUTPUT_PARAM *pTaskWorkOverOutputParam;
    TASK_WORKOVER_PRIVATE_PARAM *pTaskWorkOverPrivateParam;
}TASK_WORKOVER;
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __TASKMANAGE_H__ */
