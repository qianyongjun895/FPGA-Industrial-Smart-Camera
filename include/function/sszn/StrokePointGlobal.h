/**
  * @file  [StrokePointGlobal.h]
  * @brief  点到线垂点对外接口函数
  * @author  <Terry>
  * @date  <2017/5/11>
  * @version  <v1.0>
  * @note
  *
  */
#ifndef _STROKE_POINT_GLOBAL_H_
#define _STROKE_POINT_GLOBAL_H_
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */
#include "BaseStruct.h"
#include "TaskGlobal.h"

#define P2LS_POINT_SELECT   0
#define P2LS_LINE_SELECT    1

typedef enum {
	ERROR_TYPE_ID = 0,
    P2LINE_STROKE_POINT_X_ID,
    P2LINE_STROKE_POINT_Y_ID,
    P2LINE_STROKE_POINT_X_PHY_ID,
    P2LINE_STROKE_POINT_Y_PHY_ID,
    P2LINE_STROKE_POINT_END
} P2LS_Result;

typedef struct {
    POINT_F stroke_pixel;   /* 垂点像素值 */
    POINT_F stroke_phy;     /* 垂点物理值 */
} P2LS_RESULT;

typedef struct {
} P2LS_INPUT_PARAM;

typedef struct {
    OUTPUT_COMMON_PARAM	common_param;	/* common parameter */
} P2LS_OUTPUT_PARAM;

typedef struct {
    PRIVATE_COMMON_PARAM private_common;    /* 私有数据的公共结构体 */
    P2LS_RESULT	model_p2l_stroke_result;    /* 设模板时候的结果 */
} P2LS_PRIVATE_PARAM;

typedef struct {
    TASK_STEP_HEADER *pStepHeader;
    P2LS_INPUT_PARAM *pP2LSInputParam;
    P2LS_OUTPUT_PARAM *pP2LSOutputParam;
    P2LS_PRIVATE_PARAM *pP2LSPrivateParam;
}TASK_P2LS;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif
