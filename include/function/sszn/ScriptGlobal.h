/**
  * @file  [ScriptGlobal.h]
  * @brief  脚本功能
  * @author  <Terry>
  * @date  <2017/5/11>
  * @version  <v1.0>
  * @note
  *
  */
#ifndef _SCRIPT_GLOBAL_H_
#define _SCRIPT_GLOBAL_H_
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */
#include "BaseStruct.h"
#include "TaskGlobal.h"
#define SCRIPT_FILE_NAME_MAX	64
#define SCRIPT_TYPE_PY2			0x1
#define SCRIPT_TYPE_PY3			0x2
#define SCRIPT_TYPE_LUA			0x3
#define PY2_ROOT_DIR	"/mnt/emmc4/Script/Python2/"
#define PY3_ROOT_DIR	"/mnt/emmc4/Script/Python3/"
#define LUA_ROOT_DIR	"/mnt/emmc4/Script/Lua/"
typedef enum {
	ERROR_TYPE_ID = 0,
	SCRIPT_RST_NUM,
    SCRIPT_RST1,
    SCRIPT_END = 18
} Script_Result;

typedef struct {
    unsigned int script_type;
    char script_file_name[SCRIPT_FILE_NAME_MAX];
} SCRIPT_INPUT_PARAM;

typedef struct {
    OUTPUT_COMMON_PARAM	common_param;	/* common parameter */
} SCRIPT_OUTPUT_PARAM;

typedef struct {
    PRIVATE_COMMON_PARAM private_common;	/* 私有数据的公共结构体 */
} SCRIPT_PRIVATE_PARAM;

typedef struct {
    TASK_STEP_HEADER *pStepHeader;
    SCRIPT_INPUT_PARAM *pScriptInputParam;
    SCRIPT_OUTPUT_PARAM *pScriptOutputParam;
    SCRIPT_PRIVATE_PARAM *pScriptPrivateParam;
}TASK_SCRIPT;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif

