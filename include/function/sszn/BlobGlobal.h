/**
  * @file  [BlobGlobal.h]
  * @brief  blob对外接口函数
  * @author  <Terry>
  * @date  <2017/5/11>
  * @version  <v1.0>
  * @note
  *
  */
#ifndef _BLOB_GLOBAL_H_
#define _BLOB_GLOBAL_H_
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */
#include "BaseStruct.h"
#include "TaskGlobal.h"

#define PARA_NUM_FOR_SINGLE_BLOB	12
#define MULTI_BLOB_NUM_MAX		60
#define BLOB_NO_SORT				0x0		/* 不排序 */
#define BLOB_X_ASCEND_SORT			0x1		/* 按X坐标升序排列 */
#define BLOB_X_DESCEND_SORT			0x2		/* 按X坐标降序排列 */
#define BLOB_Y_ASCEND_SORT			0x3		/* 按Y坐标升序排列 */
#define BLOB_Y_DESCEND_SORT			0x4		/* 按Y坐标降序排列 */
#define BLOB_UDLR_SORT				0x5		/* 从上到下，从左往右排序 */
#define BLOB_LRUD_SORT				0x6		/* 从左往右，从上到下排序 */
#define BLOB_AREA_SIZE_ASCEND_SORT	0x7		/* 按面积升序排列 */
#define BLOB_AREA_SIZE_DESCEND_SORT	0x8		/* 按面积降序排序 */


typedef enum {
	ERROR_TYPE_ID = 0,
	BLOB_OK_NG_ID,
    BLOB_NUM,
    BLOB0_PIXEL_CENTER_X_ID,
    BLOB0_PIXEL_CENTER_Y_ID,
    BLOB0_PHY_CENTER_X_ID,
    BLOB0_PHY_CENTER_Y_ID,
    BLOB0_AREA_ID,
    BLOB0_THETA_ID,
    BLOB0_DEGREE_ID,
    BLOB0_ROTATE_THETA_ID,
    BLOB0_ROTATE_DEGREE_ID,
    BLOB0_RATIO_ID,
    BLOB0_WIDTH_ID,
    BLOB0_HEIGHT_ID,
    BLOB_ENUM_END=722
} BlobDetector_Result;

typedef struct {
    unsigned int boundary_flag;			/* 边界是否有效标志位，暂时不使用 */
    unsigned int sort_type;			/* 连通域排序方法 */
    unsigned int blob_num_max;			/* 最多检测个数 */
    unsigned int degree_lock;			/* 角度锁定在0-180度，0：不锁定，1：锁定 */
    THRESHOLD_INT single_link_area;			/* 单个连通域面积筛选的门限 */
    THRESHOLD_FLOAT single_link_ratio;          /* 单个连通域 长宽比筛选的门限*/
    THRESHOLD_FLOAT single_link_roundness;	/* 单个连通域的圆度门限， */
    THRESHOLD_INT total_link_num;			/* 有效blob数量，本步成功失败判决门限 */
    THRESHOLD_INT total_link_area;			/* 有效blob的面积总数，本步成功失败判决门限 */
} BLOB_INPUT_PARAM;

typedef struct {
    unsigned int cur_area;
    float theta;
    float degree;
    float rotate_theta;
    float rotate_degree;
    POINT_F blob_center_pixel;
    POINT_F blob_center_phy;
    float blobRatio;
    float blobWidth;
    float blobHeight;
} BLOB_MATCH_RESULT;

typedef struct {
    OUTPUT_COMMON_PARAM	common_param;	/* common parameter */
} BLOB_OUTPUT_PARAM;

typedef struct {
    PRIVATE_COMMON_PARAM private_common;	/* 私有数据的公共结构体 */
    unsigned int model_blob_num;			/* 设置模板时blob个数 */
    BLOB_MATCH_RESULT blob_model_rst[MULTI_BLOB_NUM_MAX]; /* 保存取模板时的结果 */
} BLOB_PRIVATE_PARAM;

typedef struct {
    TASK_STEP_HEADER *pStepHeader;
    BLOB_INPUT_PARAM *pBlobInputParam;
    BLOB_OUTPUT_PARAM *pBlobOutputParam;
    BLOB_PRIVATE_PARAM *pBlobPrivateParam;
}TASK_BLOB_CHECK;
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif
