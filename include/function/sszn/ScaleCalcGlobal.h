/**
  * @file  [HomoCalcGlobal.h]
  * @brief  机械手专用的像素转物理坐标工具
  * @author  <Terry>
  * @date  <2017/08/01>
  * @version  <v1.0>
  * @note
  *
  */
#ifndef _SCALE_CALC_GLOBAL_H_
#define _SCALE_CALC_GLOBAL_H_
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */
#include "BaseStruct.h"
#include "TaskGlobal.h"

#define SCALE_INDEX_COMMON			0	/* 使用公共模块里面指定的homograph参数 */
#define SCALE_INDEX_REF_PRE_STEP	1	/* 使用前面步骤计算出来的结果来作为索引号 */
#define SCALE_ERR_PADDING_DISABLE	0	/* 不使用默认错误数据做结果 */
#define SCALE_ERR_PADDING_ENABLE	1	/* 使用默认错误数据做结果 */
typedef enum {
	ERROR_TYPE_ID = 0,
    SCALE_CALC_PIX_LEN,
    SCALE_CALC_PHY_LEN,
    SCALE_CALC_END
} Scale_Calc_Result;

typedef struct {
	float pix_len;
	float phy_len;
} SCALE_CALC_RESULT;

typedef struct {
    unsigned int scale_index_mode;		/* scale参数的模式 */
	unsigned int scale_dynamic_index;	/* 动态scale参数索引 */
	unsigned int error_pad_enable;		/* 使能错误时用默认标志数据作为结果 */
	float len_pix_def;			/* 默认的像素长度 */
	float len_phy_def;			/* 默认的物理长度 */
} SCALE_CALC_INPUT_PARAM;

typedef struct {
    OUTPUT_COMMON_PARAM	common_param;	/* common parameter */
} SCALE_CALC_OUTPUT_PARAM;

typedef struct {
    /* 模板设置时得出的中间变量 */
    PRIVATE_COMMON_PARAM private_common;	/* 私有数据的公共结构体 */
    SCALE_CALC_RESULT model_rst;			/* 模板设置的时候结果 */
} SCALE_CALC_PRIVATE_PARAM;

typedef struct {
    TASK_STEP_HEADER *pStepHeader;
    SCALE_CALC_INPUT_PARAM *pScaleCalcInputParam;
    SCALE_CALC_OUTPUT_PARAM *pScaleCalcOutputParam;
    SCALE_CALC_PRIVATE_PARAM *pScaleCalcPrivateParam;
}TASK_SCALE_CALC;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif

