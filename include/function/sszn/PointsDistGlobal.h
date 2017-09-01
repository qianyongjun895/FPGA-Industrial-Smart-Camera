/**
  * @file  [PointsDistGlobal.h]
  * @brief  两点距离对外接口函数
  * @author  <Terry>
  * @date  <2017/5/11>
  * @version  <v1.0>
  * @note
  *
  */
#ifndef _POINTS_DIST_GLOBAL_H_
#define _POINTS_DIST_GLOBAL_H_
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */
#include "BaseStruct.h"
#include "TaskGlobal.h"
#define PPD_POINT1_SELECT 0
#define PPD_POINT2_SELECT 1

typedef enum {
	ERROR_TYPE_ID = 0,
    PP_POINT_POINT_DIST_ID,
    PHY_PP_POINT_POINT_DIST_ID,
    PP_ENUM_END
} Point2Point_Result;

typedef struct {
    double distance;			/* 点到点的像素距离 */
    double phy_distance;		/* 点到点的物理距离 */
}P2P_DIST_RESULT;

typedef struct {
    unsigned int pix_phy_flag;		/* 0：像素值， 1：物理值 */
    THRESHOLD_FLOAT valid_range;	/* 有效范围数据 */
} P2P_DIST_INPUT_PARAM;

typedef struct {
    OUTPUT_COMMON_PARAM	common_param;	/* common parameter */
} P2P_DIST_OUTPUT_PARAM;

typedef struct {
    PRIVATE_COMMON_PARAM private_common;	/* 私有数据的公共结构体 */
    P2P_DIST_RESULT model_p2p_dist_result;
} P2P_DIST_PRIVATE_PARAM;

typedef struct {
    TASK_STEP_HEADER *pStepHeader;
    P2P_DIST_INPUT_PARAM *pP2PDistInputParam;
    P2P_DIST_OUTPUT_PARAM *pP2PDistOutputParam;
    P2P_DIST_PRIVATE_PARAM *pP2PDistPrivateParam;
}TASK_P2P_DIST_CALC;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif
