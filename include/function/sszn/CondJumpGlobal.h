/**
  * @file  [CondJumpGlobal.h]
  * @brief
  * @author  <Terry>
  * @date  <2017/5/20>
  * @version  <v1.0>
  * @note
  *
  */
#ifndef __COND_JUMP_GLOBAL_H__
#define __COND_JUMP_GLOBAL_H__
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include "BaseStruct.h"
#include "TaskGlobal.h"
#define COND_AND_OP		0
#define COND_OR_OP		1
typedef enum {
    ERROR_TYPE_ID = 0,
	COND_RST_ID,
    COND_JUMP_STEP,
    COND_JUMP_END
} Cond_Jump_Result;

typedef struct {
    int compare_rst;
    unsigned int jump_step;
}COND_JUMP_RESULT;

typedef struct{
    unsigned int ok_jump_index;	// OK 跳转步骤索引
    unsigned int ng_jump_index;	// NG 跳转步骤索引
    unsigned int ok_io;	// OK IO 输出
    unsigned int ng_io;	// NG IO 输出
    unsigned int and_or;   // 1:全或  0:全与
    unsigned int link_step_bitmap[8];	//关联步骤BITMAP
    unsigned int link_step_negation[8];	//关联步骤取反标志
} CONDITION_JUMP_INPUT_PARAM;

typedef struct{
    OUTPUT_COMMON_PARAM	common_param;	/* common parameter */
}CONDITION_JUMP_OUTPUT_PARAM;

typedef struct{
    PRIVATE_COMMON_PARAM private_common;	/* 私有数据的公共结构体 */
}CONDITION_JUMP_PRIVATE_PARAM;

typedef struct {
    TASK_STEP_HEADER *pStepHeader;
    CONDITION_JUMP_INPUT_PARAM *pCondJumpInputParam;
    CONDITION_JUMP_OUTPUT_PARAM *pCondJumpOutputParam;
    CONDITION_JUMP_PRIVATE_PARAM *pCondJumpPrivateParam;
} TASK_COND_JUMP;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __TASKMANAGE_H__ */
