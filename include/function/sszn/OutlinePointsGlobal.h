/**
  * @file  [BlobGlobal.h]
  * @brief  blob对外接口函数
  * @author  <Terry>
  * @date  <2017/5/11>
  * @version  <v1.0>
  * @note
  *
  */
#ifndef _OUTLINE_POINTS_GLOBAL_H_
#define _OUTLINE_POINTS_GLOBAL_H_
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */
#include "BaseStruct.h"
#include "TaskGlobal.h"

typedef enum {
	ERROR_TYPE_ID = 0,
    OLPXNUM_OK_NG_ID,
    OLPXNUM_ID,
    OLPXNUM_END
} OutlinePixelNum_Result;

typedef struct {
    THRESHOLD_INT valid_pixel_num_range;	/* 有效边沿点范围 */
} OLPXNUM_INPUT_PARAM;

typedef struct {
    int detect_ok_ng_flag;				/* 检测OK\NG标志 */
    unsigned int outline_pixel_num;		/* 测量出的轮廓点数 */
}OLPXNUM_RESULT;

typedef struct {
    OUTPUT_COMMON_PARAM	common_param;	/* common parameter */
} OLPXNUM_OUTPUT_PARAM;

typedef struct {
    /* CPU1 模板设置时得出的中间变量 */
    PRIVATE_COMMON_PARAM private_common;	/* 私有数据的公共结构体 */
    OLPXNUM_RESULT model_olpxnum_rst;		/* 设置模板的结果 */
} OLPXNUM_PRIVATE_PARAM;

typedef struct {
    TASK_STEP_HEADER *pStepHeader;
    OLPXNUM_INPUT_PARAM *pOLPXInputParam;
    OLPXNUM_OUTPUT_PARAM *pOLPXOutputParam;
    OLPXNUM_PRIVATE_PARAM *pOLPXPrivateParam;
}TASK_OUTLINE_POINT_NUM;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif
