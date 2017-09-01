/**
  * @file  [SpotFlawGlobal.h]
  * @brief  斑点缺陷对外接口函数
  * @author  <Terry>
  * @date  <2017/5/11>
  * @version  <v1.0>
  * @note
  *
  */
#ifndef _SPOT_FLAW_GLOBAL_H_
#define _SPOT_FLAW_GLOBAL_H_
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */
#include "BaseStruct.h"
#include "TaskGlobal.h"
#define FLAW_X_ASCEND_SORT 		0x1
#define FLAW_X_DESCEND_SORT		0x2
#define FLAW_Y_ASCEND_SORT		0x3
#define FLAW_Y_DESCEND_SORT		0x4
#define FLAW_AREA_ASCEND_SORT           0x5
#define FLAW_AREA_DESCEND_SORT          0x6
#define SPOT_FLAW_NUM_MAX               100
#define PARA_NUM_FOR_SINGLE_SPOT_FLAW	3

typedef enum {
	ERROR_TYPE_ID = 0,
    SPOT_FLAW_OK_NG_ID,
    SPOT_FLAW_AREA_SUM_ID,		/* 缺陷总面积 */
    SPOT_FLAW_NUM_ID,			/* 缺陷个数 */
    SPOT_FLAW0_AREA_ID,			/* 缺陷0的面积 */
    SPOT_FLAW0_PIXEL_X_ID,		/* 缺陷0的像素坐标X */
    SPOT_FLAW0_PIXEL_Y_ID,		/* 缺陷0的像素坐标Y */
    SPOT_FLAW_END = 304
} Spot_Flaw_Result;

typedef struct {
    POINT_I pos;
    unsigned int area;
} SPOT_FLAW_INFO;

typedef struct {
    int detect_ok_ng_flag;                          /* 检测OK\NG标志 */
    unsigned int flaw_area_sum;                     /* 测量出的面积 */
    unsigned int flaw_cnt;                          /* 缺陷数 */
    SPOT_FLAW_INFO flaw_info[SPOT_FLAW_NUM_MAX];    /* 缺陷信息数组 */
} SPOT_FLAW_RESULT;

typedef struct {
    OSD_RECT search_area;			/* 检测时的搜索范围 */
    unsigned int sort_type;			/* 排序方式 */
    /* 单个缺陷的判断参数 */
    THRESHOLD_INT single_flaw_area_threshold;	/* 单缺陷面积门限 */
    /* 最终判断门限参数 */
    THRESHOLD_INT flaw_area_sum_threshold;		/* 缺陷强度门限 */
    THRESHOLD_INT flaw_count_threshold;		/* 缺陷数量门限 */
} SPOT_FLAW_INPUT_PARAM;

typedef struct {
    OUTPUT_COMMON_PARAM	common_param;	/* common parameter */
} SPOT_FLAW_OUTPUT_PARAM;

typedef struct {
    PRIVATE_COMMON_PARAM private_common;	/* 私有数据的公共结构体 */
    SPOT_FLAW_RESULT model_spot_flaw_rst;	/* 模板的对象面积 */
} SPOT_FLAW_PRIVATE_PARAM;

typedef struct {
    TASK_STEP_HEADER *pStepHeader;
    SPOT_FLAW_INPUT_PARAM *pSpotFlawInputParam;
    SPOT_FLAW_OUTPUT_PARAM *pSpotFlawOutputParam;
    SPOT_FLAW_PRIVATE_PARAM *pSpotFlawPrivateParam;
}TASK_SPOT_FLAW_CHECK;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif
