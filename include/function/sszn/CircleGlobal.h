/**
  * @file  [CircleGlobal.h]
  * @brief  圆形定位任务对外接口及数据结构
  * @author  <Terry>
  * @date  <2017/5/11>
  * @version  <v1.0>
  * @note
  *
  */
#ifndef _CIRCLE_GLOBAL_H_
#define _CIRCLE_GLOBAL_H_
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */
#include "BaseStruct.h"
#include "TaskGlobal.h"
typedef enum {
	ERROR_TYPE_ID = 0,
    CIRCLE_OK_NG_ID,    ///< 圆形定位成功失败标志
    CIRCLE_PIXEL_X_ID,      ///< 圆心点X像素坐标
    CIRCLE_PIXEL_Y_ID,      ///< 圆心点Y像素坐标
    CIRCLE_PIXEL_RADIUS_ID, ///< 圆半径像素长度
    CIRCLE_PHY_X_ID,        ///< 圆心点X物理坐标
    CIRCLE_PHY_Y_ID,        ///< 圆形点Y物理坐标
    CIRCLE_PHY_RADIUS_ID,   ///< 圆半径物理长度
    CIRCLE_END
} Circle_Result;


typedef struct {
    double pixel_x;
    double pixel_y;
    double pixel_radius;
    double phy_x;
    double phy_y;
    double phy_radius;
}CircleParameter;

/* 本结构体接收来自外部的配置参数,
 * CPU0在用户点击取样后初始化该结构体 */
typedef struct {
    POINT_I center_input;           /* 640*480 */
    unsigned int radius_input;      /* OSD pixel */
    unsigned int color_tran_dir;    /* 0:w2b, 1:b2w */
} CIRCLE_INPUT_PARAM;

/* 本结构体保存对外的输出参数，
 * CPU1在计算完成后初始化该结构体 */
typedef struct {
    OUTPUT_COMMON_PARAM	common_param;	/* common parameter */
} CIRCLE_OUTPUT_PARAM;

/* 本结构体为圆形定位的私有结构体 */
typedef struct {
    PRIVATE_COMMON_PARAM private_common;	/* 私有数据的公共结构体 */
    CircleParameter model_circle_rst;	/* 取模板时的结果记录 */
} CIRCLE_PRIVATE_PARAM;

typedef struct {
    TASK_STEP_HEADER *pStepHeader;
    CIRCLE_INPUT_PARAM *pCircleInputParam;
    CIRCLE_OUTPUT_PARAM *pCircleOutputParam;
    CIRCLE_PRIVATE_PARAM *pCirclePrivateParam;
}TASK_CIRCLE;
/**
 * @brief 获取圆形定位功能的TASK_CB_FUNC结构体
 * @param
 * @return 圆形定位回调函数结构体指针
 * @author <Terry>
 * @note
 */
TASK_CB_FUNC * Circle_CallBack_Reg(void);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif
