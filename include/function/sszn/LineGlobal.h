/**
  * @file  [LineGlobal.h]
  * @brief  直线定位对外接口函数
  * @author  <Terry>
  * @date  <2017/5/11>
  * @version  <v1.0>
  * @note
  *
  */
#ifndef _LINE_GLOBAL_H_
#define _LINE_GLOBAL_H_
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */
#include "BaseStruct.h"
#include "TaskGlobal.h"

#define PARA_NUM_FOR_SINGLE_LINE	10
#define LINE_PIXEL_SELECT_ROUND		40
#define LINE_PIXEL_SELECT_ROUND_MAX	39
#define MAX_SIDE_SELECT_PIXEL_NUM	65535
#define MULTI_LINE_NUM_MAX		20
#define LINE_FIT_POINTS_MIN		20
#define MULTI_LINE_NUM_MAX		20
#define LINE_FIT_POINTS_MIN		20
typedef enum {
	ERROR_TYPE_ID = 0,
    LINE_NUM,
    LINE0_OK_NG_ID,
    LINE0_THETA_ID,
    LINE0_DEGREE_ID,
    LINE0_ROTATE_DEG_ID,
    LINE0_COS_ID,
    LINE0_SIN_ID,
    LINE0_PIXEL_X_ID,
    LINE0_PIXEL_Y_ID,
    LINE0_PHY_X_ID,
    LINE0_PHY_Y_ID,
    LINE_END = 202
} Line_Result;

typedef struct {
    POINT_I anchor[2];                    /* 设置时的锚点 */
    float anchor_theta;			/* 两个锚点计算出来的theta值，以点1为原点，点2到点1的角度 */
    unsigned char sensitivity;		/* 筛选边沿点时门限计算参数 */
    unsigned char scan_dir;		/* 检测方向：0:正方向，1:负方向 */
    unsigned char color_tran_dir;	/* 边沿方向：0:暗到明，1:明到暗 */
    unsigned char angle_filter_th;	/* 角度判断的门限 */
    unsigned int search_range;          /* 直线搜索宽度  */
}LINE_SET_PARA;

typedef struct {
    unsigned int line_num;				/* 直线条数 */
    LINE_SET_PARA line_paras[MULTI_LINE_NUM_MAX];	/* 各自直线的配置参数 */
} LINE_INPUT_PARAM;

typedef struct {
    OUTPUT_COMMON_PARAM	common_param;	/* common parameter */
} LINE_OUTPUT_PARAM;

typedef struct {
    PRIVATE_COMMON_PARAM private_common;						/* 私有数据的公共结构体 */
    unsigned char model_line_valid_flag[MULTI_LINE_NUM_MAX];	/* 设模板时每条线结果是否有效标志， 0：无效，1：有效 */
    unsigned int model_line_pixel_num[MULTI_LINE_NUM_MAX];	/* 模板设置时每条线的筛选结果 */
    LineParameter model_line_rst[MULTI_LINE_NUM_MAX];		/* 模板设置的时候结果 */
} LINE_PRIVATE_PARAM;

typedef struct {
    TASK_STEP_HEADER *pStepHeader;
    LINE_INPUT_PARAM *pLineInputParam;
    LINE_OUTPUT_PARAM *pLineOutputParam;
    LINE_PRIVATE_PARAM *pLinePrivateParam;
}TASK_LINE;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif
