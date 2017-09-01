/**
  * @file  [LineFlawGlobal.h]
  * @brief  直线缺陷对外接口函数
  * @author  <Terry>
  * @date  <2017/5/11>
  * @version  <v1.0>
  * @note
  *
  */
#ifndef _LINE_FLAW_GLOBAL_H_
#define _LINE_FLAW_GLOBAL_H_
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
#define LINE_FLAW_NUM_MAX		100
#define PARA_NUM_FOR_SINGLE_FLAW	5
/* 缺陷检测方向 */
#define CHECK_DIR_X_POSI		0x0
#define CHECK_DIR_X_NEGA		0x1
#define CHECK_DIR_Y_POSI		0x2
#define CHECK_DIR_Y_NEGA		0x3

/* 缺陷类型 */
#define POSITIVE_FLAW			0x0
#define NEGATIVE_FLAW			0x1
#define POSI_NEGATIVE_FLAW		0x2
typedef struct {
    POINT_F pos;
    double dist;
} FLAW_POINT_INFO;

typedef struct {
    POINT_F flaw_pos;			/* 缺陷位置 */
    unsigned int flaw_length;           /* 缺陷长度 */
    double flaw_level;			/* 缺陷强度 */
    double flaw_weight;			/* 缺陷量 */
} FLAW_INFO;

typedef enum {
	ERROR_TYPE_ID = 0,
	LINE_FLAW_OK_NG_ID,
    LINE_FLAW_AREA_ID,			/* 缺陷总面积 */
    LINE_FLAW_NUM_ID,			/* 缺陷个数 */
    LINE_FLAW0_LENGTH_ID,		/* 缺陷0的长度 */
    LINE_FLAW0_AREA_ID,			/* 缺陷0的面积 */
    LINE_FLAW0_LEVEL_ID,		/* 缺陷0的强度 */
    LINE_FLAW0_PIXEL_X_ID,		/* 缺陷0的像素坐标X */
    LINE_FLAW0_PIXEL_Y_ID,		/* 缺陷0的像素坐标Y */
    LINE_FLAW_END = 504
} Line_Flaw_Result;

typedef struct {
    unsigned int flaw_length;           /* 缺陷段数 */
    float flaw_area;                    /* 缺陷面积 */
    float flaw_level;                   /* 缺陷等级（最大缺陷点距离） */
    POINT_F flaw_pos_pixel;		/* 缺陷位置（像素值） */
}LINE_FLAW_INFO;

typedef struct {
    int detect_ok_ng_flag;			/* 检测OK\NG标志 */
    unsigned int flaw_area_sum;			/* 测量出的面积 */
    unsigned int flaw_cnt;			/* 缺陷数 */
    LINE_FLAW_INFO flaw_info[LINE_FLAW_NUM_MAX];/* 缺陷信息数组 */
} LINE_FLAW_RESULT;

typedef struct {
    unsigned int flaw_check_dir;	/* 0:X+, 1:X-, 2:Y+, 3:Y-*/
    unsigned int flaw_check_type;	/* 0:正缺陷（XY增加方向），1：负缺陷（XY减少方向），2：双方向 */
    unsigned int flaw_num_max;		/* 最大检测个数，不超过200 */
    /* 单个缺陷的判断参数 */
    float flaw_level_low_th;		/* 缺陷强度门限，边沿点缺陷距离门限值（像素数）*/
    unsigned int flaw_length_low_th;	/* 缺陷段长（连续缺陷像素）门限 */
    float flaw_area_low_th;		/* 却限量，缺陷面积门限 */
    /* 最终判断门限参数 */
    THRESHOLD_FLOAT flaw_level_threshold;	/* 缺陷强度门限 */
    THRESHOLD_INT flaw_length_total_threshold;	/* 总长度门限 */
    THRESHOLD_FLOAT flaw_area_total_threshold;	/* 总缺陷量门限 */
    THRESHOLD_INT flaw_count_threshold;		/* 缺陷数量门限 */
} LINE_FLAW_INPUT_PARAM;

typedef struct {
    OUTPUT_COMMON_PARAM	common_param;	/* common parameter */
} LINE_FLAW_OUTPUT_PARAM;

typedef struct {
    PRIVATE_COMMON_PARAM private_common;	/* 私有数据的公共结构体 */
    LINE_FLAW_RESULT model_line_flaw_rst;	/* 模板的对象面积 */
} LINE_FLAW_PRIVATE_PARAM;

typedef struct {
    TASK_STEP_HEADER *pStepHeader;
    LINE_FLAW_INPUT_PARAM *pLineFlawInputParam;
    LINE_FLAW_OUTPUT_PARAM *pLineFlawOutputParam;
    LINE_FLAW_PRIVATE_PARAM *pLineFlawPrivateParam;
}TASK_LINE_FLAW_CHECK;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif
