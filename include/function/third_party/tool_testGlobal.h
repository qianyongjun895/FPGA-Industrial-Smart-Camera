/**
  * @file  [tool_testGlobal.h]
  * @brief  示例工具的结构体定义
  * @author  <Terry>
  * @date  <2017/5/11>
  * @version  <v1.0>
  * @note
  *
  */
#ifndef _TOOL_TEST_GLOBAL_H_
#define _TOOL_TEST_GLOBAL_H_
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */
#include "BaseStruct.h"
#include "TaskGlobal.h"

typedef enum {
    TOOL_TEST_RST1,
    TOOL_TEST_RST2,
    TOOL_TEST_POINT_PIX_X,
    TOOL_TEST_POINT_PIX_Y,
    TOOL_TEST_POINT_PHY_X,
    TOOL_TEST_POINT_PHY_Y,
    TOOL_TEST_ENUM_END
} Tool_Test_Result;

typedef struct {
	int param1;				/* 参数1 */
	int param2;				/* 参数2 */
} TOOLTEST_INPUT_PARAM;

typedef struct {
	int rst1;
	float rst2;
	POINT_F	point_pix;
	POINT_F point_phy;
} TOOLTEST_RESULT;

typedef struct {
    OUTPUT_COMMON_PARAM	common_param;	/* common parameter */
} TOOLTEST_OUTPUT_PARAM;

typedef struct {
    PRIVATE_COMMON_PARAM private_common;	/* 私有数据的公共结构体 */
    TOOLTEST_RESULT model_testtool_rst;		/* 设置模板结果 */
} TOOLTEST_PRIVATE_PARAM;

typedef struct {
    TASK_STEP_HEADER *pStepHeader;
    TOOLTEST_INPUT_PARAM *pToolTestInputParam;
    TOOLTEST_OUTPUT_PARAM *pToolTestOutputParam;
    TOOLTEST_PRIVATE_PARAM *pToolTestPrivateParam;
}TASK_TOOL_TEST;
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif


