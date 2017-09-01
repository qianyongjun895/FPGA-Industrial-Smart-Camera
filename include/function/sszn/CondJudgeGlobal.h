/**
  * @file  [CondJudgeGlobal.h]
  * @brief
  * @author  <Terry>
  * @date  <2017/5/20>
  * @version  <v1.0>
  * @note
  *
  */
#ifndef __COND_JUDGE_GLOBAL_H__
#define __COND_JUDGE_GLOBAL_H__
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include "BaseStruct.h"
#include "TaskGlobal.h"

#define COND_JUDGE_AND	0
#define COND_JUDGE_OR	1
#define CONDITION_JUDGE_DATA_SIZE 100

typedef enum {
    ERROR_TYPE_ID = 0,
    COND_JUDGE_RST_ID,
    COND_JUDGE_END
} Cond_Judge_Result;

typedef struct {
    int judge_rst;
}COND_JUDGE_RESULT;

typedef union{
    int inum;
    unsigned int unum;
    float fnum;
    double dnum;
}DATA_UNION;

typedef struct {
    unsigned short task_index;//任务索引
    unsigned short data_type;//数据类型,如：int型,宏定义参照自定义协议数据类型;
    unsigned int result_index;//结果索引,从0开始;
    DATA_UNION max;//上限;
    DATA_UNION min;//下限;
}JUDGE_DATA_STRU;

typedef struct{
}COND_JUDGE_INPUT_PARAM;

typedef struct{
    OUTPUT_COMMON_PARAM	common_param;	/* common parameter */
}COND_JUDGE_OUTPUT_PARAM;

typedef struct{
    PRIVATE_COMMON_PARAM private_common;	/* 私有数据的公共结构体 */
    unsigned int data_number; //条件判断数据总数
    unsigned int logic_type;//数据的逻辑;0:与; 1:或;
    JUDGE_DATA_STRU data[CONDITION_JUDGE_DATA_SIZE];//条件判断数据(上限100)
}COND_JUDGE_PRIVATE_PARAM;

typedef struct {
    TASK_STEP_HEADER *pStepHeader;
    COND_JUDGE_INPUT_PARAM *pCondJudgeInputParam;
    COND_JUDGE_OUTPUT_PARAM *pCondJudgeOutputParam;
    COND_JUDGE_PRIVATE_PARAM *pCondJudgePrivateParam;
} TASK_COND_JUDGE;
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __TASKMANAGE_H__ */
