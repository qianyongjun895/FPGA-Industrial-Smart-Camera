/**
  * @file  [MiddlePointGlobal.h]
  * @brief  两点中点对外接口函数
  * @author  <Terry>
  * @date  <2017/5/11>
  * @version  <v1.0>
  * @note
  *
  */
#ifndef _MIDDLE_POINT_GLOBAL_H_
#define _MIDDLE_POINT_GLOBAL_H_
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */
#include "BaseStruct.h"
#include "TaskGlobal.h"

#define PPMP_POINT1_SELECT 0
#define PPMP_POINT2_SELECT 1

typedef enum {
	ERROR_TYPE_ID = 0,
    PPMP_POINT_M_X_ID,
    PPMP_POINT_M_Y_ID,
    PPMP_POINT_M_X_PHY_ID,
    PPMP_POINT_M_Y_PHY_ID,
    PPMP_END
} PPMP_Result;

typedef struct {
    POINT_F point_pixel;
    POINT_F point_phy;
}PPMP_RESULT;

typedef struct {
} PPMP_INPUT_PARAM;

typedef struct {
    OUTPUT_COMMON_PARAM	common_param;	/* common parameter */
} PPMP_OUTPUT_PARAM;

typedef struct {
    PRIVATE_COMMON_PARAM private_common;    /* 私有数据的公共结构体 */
    PPMP_RESULT  model_ppmp_result;         /* 设模板时线与线交点的参数 */
} PPMP_PRIVATE_PARAM;

typedef struct {
    TASK_STEP_HEADER *pStepHeader;
    PPMP_INPUT_PARAM *pPPMPInputParam;
    PPMP_OUTPUT_PARAM *pPPMPOutputParam;
    PPMP_PRIVATE_PARAM *pPPMPPrivateParam;
}TASK_PPMP;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif
