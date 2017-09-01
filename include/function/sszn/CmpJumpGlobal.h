/**
  * @file  [CmpJumpGlobal.h]
  * @brief
  * @author  <Terry>
  * @date  <2017/5/20>
  * @version  <v1.0>
  * @note
  *
  */
#ifndef __CMP_JUMP_GLOBAL_H__
#define __CMP_JUMP_GLOBAL_H__
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include "BaseStruct.h"
#include "TaskGlobal.h"

#define COMPARE_EQUAL               1
#define COMPARE_GREATER             2
#define COMPARE_GREATER_EQUAL       3
#define COMPARE_LESS                4
#define COMPARE_LESS_EQUAL          5

typedef enum {
	ERROR_TYPE_ID = 0,
    CMP_RST_ID,
    CMP_JUMP_STEP,
    CMP_JUMP_END
} Cmp_Jump_Result;

typedef struct {
    int compare_rst;
    unsigned int jump_step;
}CMP_JUMP_RESULT;

typedef struct{
    unsigned int cmp_way;   /*判断的选项(1:==; 2:>; 3:>=; 4:<; 5:<=) */
    double cmp_data;        /*比较数据，当表达式B不引用步骤结果时，表达式A与此数据比较*/
    unsigned int ok_jump_step; /*ok时跳转的任务索引,当索引为0时，说明不进行跳转*/
    unsigned int ng_jump_step; /*ng时跳转的任务索引,当索引为0时，说明不进行跳转*/
}CMP_JUMP_INPUT_PARAM;

typedef struct{
    OUTPUT_COMMON_PARAM	common_param;	/* common parameter */
}CMP_JUMP_OUTPUT_PARAM;

typedef struct{
    PRIVATE_COMMON_PARAM private_common;/* 私有数据的公共结构体 */
}CMP_JUMP_PRIVATE_PARAM;

typedef struct {
    TASK_STEP_HEADER *pStepHeader;
    CMP_JUMP_INPUT_PARAM *pCmpJumpInputParam;
    CMP_JUMP_OUTPUT_PARAM *pCmpJumpOutputParam;
    CMP_JUMP_PRIVATE_PARAM *pCmpJumpPrivateParam;
} TASK_CMP_JUMP;
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __TASKMANAGE_H__ */
