/**
  * @file  [PolygonCenterGlobal.h]
  * @brief  多边形中心对外接口函数
  * @author  <Terry>
  * @date  <2017/5/11>
  * @version  <v1.0>
  * @note
  *
  */
#ifndef _POLYGON_CENTER_GLOBAL_H_
#define _POLYGON_CENTER_GLOBAL_H_
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */
#include "BaseStruct.h"
#include "TaskGlobal.h"
#define PYGC_LINE_MIN	3
#define PYGC_LINE_MAX	4

typedef enum {
	ERROR_TYPE_ID = 0,
    PYG_CENTER_POINT_X_ID,
    PYG_CENTER_POINT_Y_ID,
    PYG_CENTER_POINT_PHY_X_ID,
    PYG_CENTER_POINT_PHY_Y_ID,
    PYG_CENTER_END
} PYG_Center_Result;

typedef struct {
    POINT_F	center_pixel;	/* 中间点像素值 */
    POINT_F	center_phy;	/* 中间点物理值 */
}PYG_CENTER_RESULT;

typedef struct {
    unsigned int line_num; 		/* 用户配置的边的条数 */
} PYG_CENTER_INPUT_PARAM;

typedef struct {
    OUTPUT_COMMON_PARAM	common_param;	/* common parameter */
} PYG_CENTER_OUTPUT_PARAM;

typedef struct {
    PRIVATE_COMMON_PARAM private_common;	/* 私有数据的公共结构体 */
    PYG_CENTER_RESULT pyg_center_model_rst;	/* 多边形中心点模板时的结果 */
} PYG_CENTER_PRIVATE_PARAM;

typedef struct {
    TASK_STEP_HEADER *pStepHeader;
    PYG_CENTER_INPUT_PARAM *pPygCInputParam;
    PYG_CENTER_OUTPUT_PARAM *pPygCOutputParam;
    PYG_CENTER_PRIVATE_PARAM *pPygCPrivateParam;
}TASK_PYG_CENTER;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif
