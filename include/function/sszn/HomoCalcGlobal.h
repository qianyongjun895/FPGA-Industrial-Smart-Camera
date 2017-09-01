/**
  * @file  [HomoCalcGlobal.h]
  * @brief  机械手专用的像素转物理坐标工具
  * @author  <Terry>
  * @date  <2017/08/01>
  * @version  <v1.0>
  * @note
  *
  */
#ifndef _HOMO_CALC_GLOBAL_H_
#define _HOMO_CALC_GLOBAL_H_
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */
#include "BaseStruct.h"
#include "TaskGlobal.h"

#define HOMO_INDEX_COMMON			0	/* 使用公共模块里面指定的homograph参数 */
#define HOMO_INDEX_REF_GRST			1	/* 使用GRst里面Dynamic数据作为homograph参数索引 */
#define HOMO_ERR_PADDING_DISABLE	0	/* 不使用默认错误数据做结果 */
#define HOMO_ERR_PADDING_ENABLE		1	/* 使用默认错误数据做结果 */
#define HOMO_OFFSET_CALC_DISABLE	0	/* 关闭相对原点的偏移量计算 */
#define HOMO_OFFSET_CALC_ENABLE		1	/* 使能相对原点的偏移量计算 */
typedef enum {
	ERROR_TYPE_ID = 0,
	HOMO_CALC_PIX_X,
    HOMO_CALC_PIX_Y,
    HOMO_CALC_PHY_X,
    HOMO_CALC_PHY_Y,
    HOMO_OFFSET_X,
    HOMO_OFFSET_Y,
    HOMO_ROT_DEGREE,
    HOMO_ROT_THETA,
    HOMO_CALC_END
} Homo_Calc_Result;

typedef struct {
	POINT_F pos_pix;
	POINT_F pos_phy;
	float x_offset;
	float y_offset;
	float rot_theta;
	float rot_degree;
} HOMO_CALC_RESULT;

typedef struct {
    unsigned int homo_index_mode;	/* homograph参数的模式 */
	unsigned int homo_dynamic_index;/* 动态homo参数索引 */
    unsigned int error_pad_enable;	/* 使能错误时用默认标志数据作为结果 */
	unsigned int offset_calc_enable;/* 使能偏移计算 */	
    POINT_F pos_pix_def;			/* 默认的像素坐标 */
    POINT_F pos_phy_def;			/* 默认的物理坐标 */
} HOMO_CALC_INPUT_PARAM;

typedef struct {
    OUTPUT_COMMON_PARAM	common_param;	/* common parameter */
} HOMO_CALC_OUTPUT_PARAM;

typedef struct {
    /* 模板设置时得出的中间变量 */
    PRIVATE_COMMON_PARAM private_common;	/* 私有数据的公共结构体 */
    HOMO_CALC_RESULT model_rst;		/* 模板设置的时候结果 */
} HOMO_CALC_PRIVATE_PARAM;

typedef struct {
    TASK_STEP_HEADER *pStepHeader;
    HOMO_CALC_INPUT_PARAM *pHomoCalcInputParam;
    HOMO_CALC_OUTPUT_PARAM *pHomoCalcOutputParam;
    HOMO_CALC_PRIVATE_PARAM *pHomoCalcPrivateParam;
}TASK_HOMO_CALC;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif

