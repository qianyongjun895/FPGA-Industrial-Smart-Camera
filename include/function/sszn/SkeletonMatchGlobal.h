/**
  * @file  [SkeletonMatchGlobal.h]
  * @brief  轮廓匹配对外接口函数
  * @author  <Terry>
  * @date  <2017/5/11>
  * @version  <v1.0>
  * @note
  *
  */
#ifndef _SKELETON_MATCH_GLOBAL_H_
#define _SKELETON_MATCH_GLOBAL_H_
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */
#include "BaseStruct.h"
#include "TaskGlobal.h"
#include "roi.h"
#define MAX_BLIND_ZONE_NUM 16
typedef enum {
	ERROR_TYPE_ID = 0,
    S_CENTER_POINT_X_ID,
    S_CENTER_POINT_Y_ID,
    S_PHY_CENTER_POINT_X_ID,
    S_PHY_CENTER_POINT_Y_ID,
    S_ROTATE_ANGLE_ID,
    S_ROTATA_THETA_ID,
    S_MARK_ANGLE_ID,
    S_SCORE_ID,
    S_OK_NG_ID,
    S_ENUM_END
} Skeleton_Result;

typedef struct {
    POINT_F match_point;		/* 匹配到目标的中心点坐标 */
    POINT_F phy_match_point;	/* 匹配到目标的中心点坐标 */
    double theta;	/* 旋转后的弧度，-π到π */
    double degree;	/* 旋转后的角度，-180°到180°*/
    double score;	/* 每个的匹配打分成绩 */
}SKELETON_MATCH_RESULT;


typedef struct {
    POINT_F train_roi_point[2];		/* 训练区域左上角和右下角坐标 */
    POINT_F search_roi_point[2];	/* 搜索区域左上角和右下角坐标 */
	unsigned int score_threshold;	/* 分数门限 */
    unsigned int sensitivity;		/* 对比灵敏度 */
    unsigned int scopeRotation;		/* 旋转范围 ，取正负值*/
    unsigned int calc_type;			/* 计算方式  0:普通 1:快速 */
} SKELETON_INPUT_PARAM;

typedef struct {
    OUTPUT_COMMON_PARAM	common_param;	/* common parameter */
} SKELETON_OUTPUT_PARAM;

typedef struct {
    /* 模板设置时得出的中间变量 */
    PRIVATE_COMMON_PARAM private_common;        /* 私有数据的公共结构体 */
    unsigned int PatternTableSaveBaseAddr;      /* base address for pattern and 3 tables */
    int originDirection;                /* degree, if precise match flag = 0, originDirection always 0, other wise the originDirection come from line */
    double originX;			/* if precise match flag = 0, the originX\Y is the center of trainROI, other wise the value come from 2-line cross point or circle center */
    double originY;			/*亚像素*/
    double ske_originX;                 /* model of skeleton center point , 缩放后的点*/
    double ske_originY;                 /* model of skeleton */
    roiROI	trainROI;
    roiROI 	searchROI;
    roiGeoMatch outMatch;
    SKELETON_MATCH_RESULT model_skeleton_result;
} SKELETON_PRIVATE_PARAM;

typedef struct {
    TASK_STEP_HEADER *pStepHeader;
    SKELETON_INPUT_PARAM *pSkeletonInputParam;
    SKELETON_OUTPUT_PARAM *pSkeletonOutputParam;
    SKELETON_PRIVATE_PARAM *pSkeletonPrivateParam;
}TASK_SKELETON;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif
