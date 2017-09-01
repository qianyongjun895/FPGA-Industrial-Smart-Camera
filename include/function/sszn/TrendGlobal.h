/**
  * @file  [TrendGlobal.h]
  * @brief 数据趋势对外接口函数
  * @author  <Terry>
  * @date  <2017/7/7>
  * @version  <v1.0>
  * @note
  *
  */
#ifndef _TREND_GLOBAL_H_
#define _TREND_GLOBAL_H_
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */
#include "BaseStruct.h"
#include "TaskGlobal.h"

#define TREND_ITEM_SIZE			4		/* 趋势任务每次保存的数据占4个字节，用float类型保存 */
#define TREND_ITEM_NUM_DEF		1000	/* 每个buffer中默认保存过去1000个数据点，后续可以改成可配置的 */
#define TREND_BUFFER_SIZE_DEF	4096	/* 每个buffer默认的大小 */
#define TREND_BUFFER_NUM		2		/* buffer的个数 */

typedef enum {
	ERROR_TYPE_ID = 0,
	TD_BUF_CRT,
	TD_BUF_OFFSET,
	TD_BUF1_FULL_FLAG,
	TD_BUF2_FULL_FLAG,
	TD_ENUM_END
}Trend_Result;

typedef struct {
	unsigned int buf_crt;			/* 当前buffer索引 */
	unsigned int buf_offset;		/* 当前buffer的偏移量 */
	unsigned int buf_full_flag[2];/* buffer写满标志，CPU1负责置1,表示数据写满,CPU0保存完数据后清零 */
}TREND_RST;

typedef struct {
	unsigned int error_insert_flag;	/* 索引数据步骤发生错误时，是否用error_data填充数据点，1：使用，0：不使用 */
	float error_data;	/* 索引数据发生错误时填充的值 */
	unsigned int points_per_buf;	/* 单个buffer中记录的点数 */
} TREND_INPUT_PARAM;

typedef struct {
	OUTPUT_COMMON_PARAM	common_param;	/* common parameter */
} TREND_OUTPUT_PARAM;

typedef struct {
	PRIVATE_COMMON_PARAM private_common;	/* 私有数据的公共结构体 */
	TREND_RST trend_rst;
} TREND_PRIVATE_PARAM;

typedef struct {
	TASK_STEP_HEADER *pStepHeader;
	TREND_INPUT_PARAM *pTrendInputParam;
	TREND_OUTPUT_PARAM *pTrendOutputParam;
	TREND_PRIVATE_PARAM *pTrendPrivateParam;
}TASK_TREND;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif

