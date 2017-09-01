/**
  * @file  [AreaCenterGlobal.h]
  * @brief  对象面积对外接口函数
  * @author  <Terry>
  * @date  <2017/5/11>
  * @version  <v1.0>
  * @note
  *
  */
#ifndef _AREA_CENTER_GLOBAL_H_
#define _AREA_CENTER_GLOBAL_H_
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */
#include "BaseStruct.h"
#include "TaskGlobal.h"

typedef enum {
	ERROR_TYPE_ID = 0,
    AREA_CENTER_OK_NG_ID,
    AREA_CENTER_X_ID,
    AREA_CENTER_Y_ID,
    AREA_CENTER_X_PHY_ID,
    AREA_CENTER_Y_PHY_ID,
    AREA_COUNT,
    AREA_CENTER_END
} Area_Center_Result;

typedef struct {
    int detect_ok_ng_flag;	/* 检测OK\NG标志 */
    POINT_F area_center_pixel;	/* 面积重心像素坐标 */
    POINT_F area_center_phy;	/* 面积重心物理坐标 */
    unsigned int area;		/* 面积值 */
} AREA_CENTER_RESULT;


typedef struct {
    THRESHOLD_INT x_threshold;	/* X有效范围 */
    THRESHOLD_INT y_threshold;	/* Y有效范围 */
    THRESHOLD_INT area_threshold;	/* 面积大小的有效范围 */
} AREA_CENTER_INPUT_PARAM;

typedef struct {
    OUTPUT_COMMON_PARAM	common_param;	/* common parameter */
} AREA_CENTER_OUTPUT_PARAM;

typedef struct {
    /* 模板设置时得出的中间变量 */
    PRIVATE_COMMON_PARAM private_common;		/* 私有数据的公共结构体 */
    AREA_CENTER_RESULT model_area_center_rst;	/* 模板设置的时候结果 */
} AREA_CENTER_PRIVATE_PARAM;

typedef struct {
    TASK_STEP_HEADER *pStepHeader;
    AREA_CENTER_INPUT_PARAM *pAreaCenterInputParam;
    AREA_CENTER_OUTPUT_PARAM *pAreaCenterOutputParam;
    AREA_CENTER_PRIVATE_PARAM *pAreaCenterPrivateParam;
}TASK_AREA_CENTER_CHECK;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif
