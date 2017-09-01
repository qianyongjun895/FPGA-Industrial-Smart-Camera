/**
  * @file  [DataStatGlobal.h]
  * @brief 数据统计对外接口函数
  * @author  <Terry>
  * @date  <2017/5/11>
  * @version  <v1.0>
  * @note
  *
  */
#ifndef _DATA_STAT_GLOBAL_H_
#define _DATA_STAT_GLOBAL_H_
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */
#include "BaseStruct.h"
#include "TaskGlobal.h"

typedef enum {
    ERROR_TYPE_ID = 0,
	DS_LAST_VALUE,
    DS_MIN_VALUE,
    DS_MAX_VALUE,
    DS_MEAN_VALUE,
    DS_SUM_VALUE,
    DS_SUCCESS_RATIO,
    DS_TOTAL_CNT,
    DS_SUCCESS_CNT,
    DS_INVALID_CNT,
    DS_FAIL_CNT,
    DS_ENUM_END
} Data_Stst_Result;

typedef struct {
	float last_value;	/* 最后获取到的值 */
	float min_value;	/* 统计到的最小值 */
	float max_value;	/* 统计到的最大值 */
	float mean_value;	/* 统计到的平均值，mean_value = sum_value/(stst_success_cnt+stst_invalid_cnt)  */
	double sum_value;	/* 所有数据累加和 */
	float success_ratio;/* 成品率, success_ratio = stst_success_cnt/stst_total_cnt */
	unsigned int stst_total_cnt;	/* 统计次数, stst_total_cnt = stst_success_cnt+stst_invalid_cnt+stst_fail_cnt*/
	unsigned int stst_success_cnt;	/* 成功次数 */
	unsigned int stst_invalid_cnt;	/* 数据超出有效范围的次数 */
	unsigned int stst_fail_cnt;		/* 索引数据所在步骤运行失败了，此值增加 */
}DATASTST_RST;

typedef struct {
	float valid_range_check;	/* 有效范围检查标志位，1：检查，0：不检查 */
	float low_threshold;		/* 有效值下限 */
	float high_threshold;		/* 有效值上限 */
} DATASTST_INPUT_PARAM;

typedef struct {
	OUTPUT_COMMON_PARAM	common_param;	/* common parameter */
} DATASTST_OUTPUT_PARAM;

typedef struct {
	PRIVATE_COMMON_PARAM private_common;	/* 私有数据的公共结构体 */
	DATASTST_RST ds_rst;	/* 计算时用的，最终值会写入output指定的memory,清零时要清除 */
} DATASTST_PRIVATE_PARAM;

typedef struct {
	TASK_STEP_HEADER *pStepHeader;
	DATASTST_INPUT_PARAM *pDataStstInputParam;
	DATASTST_OUTPUT_PARAM *pDataStstOutputParam;
	DATASTST_PRIVATE_PARAM *pDataStstPrivateParam;
}TASK_DATASTST;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif
