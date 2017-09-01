/**
  * @file  [PointOffsetGlobal.h]
  * @brief  偏移量对外接口函数
  * @author  <Terry>
  * @date  <2017/5/11>
  * @version  <v1.0>
  * @note
  *
  */
#ifndef _POINT_OFFSET_GLOBAL_H_
#define _POINT_OFFSET_GLOBAL_H_
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */
#include "BaseStruct.h"
#include "TaskGlobal.h"

#define OFFSET_POINT1_SELECT 0
#define OFFSET_POINT2_SELECT 1

typedef enum {
	ERROR_TYPE_ID = 0,
    OFFSET_POINT1_X_ID,
    OFFSET_POINT1_Y_ID,
    OFFSET_POINT2_X_ID,
    OFFSET_POINT2_Y_ID,
    OFFSET_PIXEL_X_ID,
    OFFSET_PIXEL_Y_ID,
    OFFSET_PHY_X_ID,
    OFFSET_PHY_Y_ID,
    OFFSET_OUTPUT_RESULT,
    OFFSET_ENUM_END
} Offset_Point_Result;

typedef struct {
    POINT_F point1;             /* 选择点1 */
    POINT_F point2;             /* 选择点2 */
    POINT_F point_offset;       /* 计算像素结果 ,这里的x,y分别指的是长度，不是一个点的坐标*/
    POINT_F phy_point_offset;   /* 计算物理结果 ，这里的x,y分别指的是长度，不是一个点的坐标*/
    int offset_valid_flag;	/* 有效范围检测结果 */
} OFFSET_RESULT;

typedef struct {
    unsigned int pix_phy_flag;		/* 0：像素值， 1：物理值 */
    THRESHOLD_FLOAT valid_range_x;	/* x方向有效范围数据 */
    THRESHOLD_FLOAT valid_range_y;	/* Y方向有效范围数据 */
} OFFSET_POINT_INPUT_PARAM;

typedef struct {
    OUTPUT_COMMON_PARAM	common_param;	/* common parameter */
} OFFSET_POINT_OUTPUT_PARAM;

typedef struct {
    PRIVATE_COMMON_PARAM private_common;	/* 私有数据的公共结构体 */
    OFFSET_RESULT model_offset_result;
} OFFSET_POINT_PRIVATE_PARAM;

typedef struct {
    TASK_STEP_HEADER *pStepHeader;
    OFFSET_POINT_INPUT_PARAM *pOffsetPointInputParam;
    OFFSET_POINT_OUTPUT_PARAM *pOffsetPointOutputParam;
    OFFSET_POINT_PRIVATE_PARAM *pOffsetPointPrivateParam;
}TASK_OFFSET_POINT_CALC;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif
