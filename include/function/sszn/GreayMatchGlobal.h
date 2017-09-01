/**
  * @file  [GreayMatchGlobal.h]
  * @brief  灰度匹配对外接口函数
  * @author  <Terry>
  * @date  <2017/6/20>
  * @version  <v1.0>
  * @note
  *
  */
#ifndef _GREAY_MATCH_GLOBAL_H_
#define _GREAY_MATCH_GLOBAL_H_
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */
#include "BaseStruct.h"
#include "TaskGlobal.h"

typedef enum {
	ERROR_TYPE_ID = 0,
	GREAY_MATCH_OK_NG_ID,
    GREAY_MATCH_SCORE,
    GREAY_MATCH_END
} Greay_Match_Result;

typedef struct {
    int detect_ok_ng_flag;	/* 检测OK\NG标志 */
    unsigned int Score;		/* 匹配分数 */
	int Angle;
	int Model_Pat_X;
	int Model_Pat_Y;
} GREAY_MATCH_RESULT;

//#define CHECK_BLACK_AREA		0x0
//#define CHECK_WHITE_AREA		0x1
typedef struct {
    int  Differential_threshold;	/* 匹配阈值 */
	THRESHOLD_INT In_Put_ROI; //匹配区域ROI
	int *Score;		/* 匹配分数 */
	void *Mod_Image_Ptr;
	int Max_Score;
	int Min_Score;
} GREAY_MATCH_INPUT_PARAM;

typedef struct {
    OUTPUT_COMMON_PARAM	common_param;	/* common parameter *//*公有输出参数*/
} GREAY_MATCH_OUTPUT_PARAM;

typedef struct {
    /* 模板设置时得出的中间变量 */
    PRIVATE_COMMON_PARAM private_common;		/* 私有数据的公共结构体 */
    GREAY_MATCH_RESULT model_area_rst;	/* 模板设置的时候结果 */
} GREAY_MATCH_PRIVATE_PARAM;

typedef struct {
    TASK_STEP_HEADER *pStepHeader;
    GREAY_MATCH_INPUT_PARAM *pGreayMatchInputParam;
    GREAY_MATCH_OUTPUT_PARAM *pGreayMatchOutputParam;
    GREAY_MATCH_PRIVATE_PARAM *pGreayMatchPrivateParam;  /*私有输出参数变量*/
}TASK_GREAY_MATCH_CHECK;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif

