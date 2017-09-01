/**
  * @file  [CmdJumpGlobal.h]
  * @brief  命令跳转任务结构体定义
  * @author  <Terry>
  * @date  <2017/5/20>
  * @version  <v1.0>
  * @note
  *
  */
#ifndef __CMD_JUMP_GLOBAL_H__
#define __CMD_JUMP_GLOBAL_H__
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include "BaseStruct.h"
#include "TaskGlobal.h"

#define COMMAND_JUMP_SIZE   50
#define TRIGGER_STR_LEN     16

typedef enum {
	ERROR_TYPE_ID = 0,
    CMD_JUMP_CMD_INDEX,
    CMD_JUMP_TARGET_STEP_ID,
    CMD_JUMP_END
} Cmd_Jump_Result;

typedef struct {
    unsigned int cmd_index;	/* 收到命令的编号 */
    unsigned int jump_step;	/* 跳转步骤的step_index */
}CMD_JUMP_RESULT;

typedef struct TriggerCmdInfo {
    char Trigger_data[TRIGGER_STR_LEN];	///<触发命令
    unsigned short step_index;          ///<要跳转到的步骤
    unsigned short addr;                ///<数据保存地址1~1024
	char data_cnt;                      ///<数据个数
	char data_type;                     ///<数据类型
	char separator;                     ///<分隔符
	char end_char;                      ///<结束符
} TRIGGER_CMD_INFO;

typedef struct{
    unsigned int cmd_count;		//命令总数
    unsigned int target_step;           //收到匹配命令后跳转的步骤
}CMD_JUMP_INPUT_PARAM;

typedef struct{
    OUTPUT_COMMON_PARAM	common_param;	/* common parameter */
}CMD_JUMP_OUTPUT_PARAM;

typedef struct{
    PRIVATE_COMMON_PARAM private_common;	/* 私有数据的公共结构体 */
    TRIGGER_CMD_INFO Trigger[COMMAND_JUMP_SIZE];/* 触发命令结构数组 */
}CMD_JUMP_PRIVATE_PARAM;

typedef struct {
    TASK_STEP_HEADER *pStepHeader;
    CMD_JUMP_INPUT_PARAM *pCmdJumpInputParam;
    CMD_JUMP_OUTPUT_PARAM *pCmdJumpOutputParam;
    CMD_JUMP_PRIVATE_PARAM *pCmdJumpPrivateParam;
} TASK_CMD_JUMP;

#define CMD_JUMP_HEADER     pCmdJump->pStepHeader
#define CMD_JUMP_IN_PARA    pCmdJump->pCmdJumpInputParam
#define CMD_JUMP_OUT_PARA   pCmdJump->pCmdJumpOutputParam
#define CMD_JUMP_PTE_PARA   pCmdJump->pCmdJumpPrivateParam
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __TASKMANAGE_H__ */
