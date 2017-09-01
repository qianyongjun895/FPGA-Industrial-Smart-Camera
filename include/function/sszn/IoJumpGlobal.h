/**
  * @file  [IoJumpGlobal.h]
  * @brief
  * @author  <Terry>
  * @date  <2017/5/20>
  * @version  <v1.0>
  * @note
  *
  */
#ifndef __IO_JUMP_GLOBAL_H__
#define __IO_JUMP_GLOBAL_H__
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include "BaseStruct.h"
#include "TaskGlobal.h"
typedef enum {
    ERROR_TYPE_ID = 0,
	IO_JUMP_INDEX,
    IO_JUMP_TARGET_STEP_ID,
    IO_JUMP_END
} IO_Jump_Result;

typedef struct {
    unsigned int io_index;	/* 收到io信号编号 */
    unsigned int jump_step;	/* 跳转步骤的step_index */
}IO_JUMP_RESULT;

typedef struct{
    unsigned int io_enable_bitmask; // 0x0:all disable 0x01:IO1 enable 0x02:IO2 enable 0x03:IO1 and IO2 enable
    unsigned int io1_trigger_mode; // 1:Rise edge 2:Fall edge 3:High level 4:Low level
    unsigned int io2_trigger_mode; // 1:Rise edge 2:Fall edge 3:High level 4:Low level
    unsigned int io1_step_index; // the step want to jump to;
    unsigned int io2_step_index; // the step want to jump to;
}IO_JUMP_INPUT_PARAM;

typedef struct{
    OUTPUT_COMMON_PARAM	common_param;	/* common parameter */
}IO_JUMP_OUTPUT_PARAM;

typedef struct{
    PRIVATE_COMMON_PARAM private_common;	/* 私有数据的公共结构体 */
}IO_JUMP_PRIVATE_PARAM;

typedef struct {
    TASK_STEP_HEADER *pStepHeader;
    IO_JUMP_INPUT_PARAM *pIOJumpInputParam;
    IO_JUMP_OUTPUT_PARAM *pIOJumpOutputParam;
    IO_JUMP_PRIVATE_PARAM *pIOJumpPrivateParam;
} TASK_IO_JUMP;
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __TASKMANAGE_H__ */
