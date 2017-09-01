/**
  * @file  [BlobCountGlobal.h]
  * @brief  blob计数对外接口函数
  * @author  <Terry>
  * @date  <2017/5/11>
  * @version  <v1.0>
  * @note
  *
  */
#ifndef _BLOB_COUNT_GLOBAL_H_
#define _BLOB_COUNT_GLOBAL_H_
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */
#include "BaseStruct.h"
#include "TaskGlobal.h"

typedef enum {
	ERROR_TYPE_ID = 0,
    BLOB_COUNT_OK_NG_ID,
    BLOB_NUM,
    BLOB_COUNT_ENUM_END
} BlobCount_Result;

typedef struct {
    THRESHOLD_INT single_area;		/* 单个连通域面积筛选的门限 */
    THRESHOLD_INT total_num;		/* 有效blob数量，本步成功失败判决门限 */
} BLOBCOUNT_INPUT_PARAM;

typedef struct {
    int detect_ok_ng_flag;	/* 检测OK\NG标志 */
    unsigned int blob_num;
} BLOBCOUNT_RESULT;

typedef struct {
    OUTPUT_COMMON_PARAM	common_param;	/* common parameter */
} BLOBCOUNT_OUTPUT_PARAM;

typedef struct {
    PRIVATE_COMMON_PARAM private_common;	/* 私有数据的公共结构体 */
    unsigned int model_blob_num;			/* 设置模板时blob个数 */
} BLOBCOUNT_PRIVATE_PARAM;

typedef struct {
    TASK_STEP_HEADER *pStepHeader;
    BLOBCOUNT_INPUT_PARAM *pBlobCountInputParam;
    BLOBCOUNT_OUTPUT_PARAM *pBlobCountOutputParam;
    BLOBCOUNT_PRIVATE_PARAM *pBlobCountPrivateParam;
}TASK_BLOB_COUNT;
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif

