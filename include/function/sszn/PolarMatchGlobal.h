/**
  * @file  [PolarMatchGlobal.h]
  * @brief  圆展开对外接口函数
  * @author  <Terry>
  * @date  <2017/5/11>
  * @version  <v1.0>
  * @note
  *
  */
#ifndef _POLAR_MATCH_GLOBAL_H_
#define _POLAR_MATCH_GLOBAL_H_
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */
#include "BaseStruct.h"
#include "TaskGlobal.h"

typedef enum {
	ERROR_TYPE_ID = 0,
    POLAR_MATCH_CENTER_X_ID,
    POLAR_MATCH_CENTER_Y_ID,
    POLAR_MATCH_RST_START_DEGREE,
    POLAR_MATCH_RST_END_DEGREE,
    POLAR_MATCH_DEGREE_ID,
    POLAR_MATCH_THETA_ID,
    POLAR_MATCH_SCORE_ID,
    POLAR_MATCH_END
} Polar_Match_Result;

typedef struct {
    POINT_F polar_center;	/* 极坐标展开的中心点 */
    float result_window_start;	/* 结果窗口起始角度 */
    float result_window_end;	/* 结果窗口结束角度 */
    float degree;	/* 与设置模板时采样窗口的夹角，顺时针正角度 */
    float theta;	/* 与设置模板时采样窗口的旋转角度，逆时针负角度 */
    unsigned int score;	/* 匹配后的得分 */
}POLAR_MATCH_RESULT;

typedef struct {
    unsigned int inner_radius;		/* 内径长度 */
    unsigned int outer_radius;		/* 外径长度 */
    unsigned int score_threshold;	/* 判决门限，范围0-100 */
    float sample_window_start;		/* 采样窗口起始角度 */
    float sample_window_end;		/* 采样窗口结束角度 */
    float search_window_start;		/* 搜索窗口起始角度 */
    float search_window_end;		/* 搜索窗口结束角度 */
    unsigned int search_all_window_flag;	/* 360度搜索, 1:360度搜索，0:按照search_window_start\end搜索 */
} POLAR_MATCH_INPUT_PARAM;

typedef struct {
    OUTPUT_COMMON_PARAM	common_param;	/* common parameter */
} POLAR_MATCH_OUTPUT_PARAM;

typedef struct {
    PRIVATE_COMMON_PARAM private_common;	/* 私有数据的公共结构体 */
    POLAR_MATCH_RESULT model_polar_match_rst;	/* 模板设置时的结果 */
    /* 模板设置时得出的中间变量 */
    unsigned int polar_model_length;	/* 模板的长度，根据输入参数中的precision和采样窗口宽度计算 */
    unsigned int polar_model_height;	/* 模板的高度，根据输入参数中的内外半径计算 */
    unsigned int polar_model_data_size;	/* 模板数据总的大小，等于以上两个参数的乘积 */
    unsigned int polar_model_data_save_addr;
    unsigned int search_window_width;	/* 搜索窗口的宽度 */
    unsigned int expand_line_length;	/* 搜索窗口展开后的长度， expand_line_length = search_window_width/sin_cos_lut_step */
    unsigned int expand_data_size;	/* 搜索窗口展开后数据量, expand_data_size = expand_line_length*polar_model_height + polar_model_data_size */
} POLAR_MATCH_PRIVATE_PARAM;

typedef struct {
    TASK_STEP_HEADER *pStepHeader;
    POLAR_MATCH_INPUT_PARAM *pPolarMatchInputParam;
    POLAR_MATCH_OUTPUT_PARAM *pPolarMatchOutputParam;
    POLAR_MATCH_PRIVATE_PARAM *pPolarMatchPrivateParam;
} TASK_POLAR_MATCH;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif
