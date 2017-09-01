/**
  * @file  [MapGlobal.h]
  * @brief  映射测量对外接口函数
  * @author  <Vincent>
  * @date  <2017/7/13>
  * @version  <v1.0>
  * @note
  *
  */
#ifndef _MAP_GLOBAL_H_
#define _MAP_GLOBAL_H_
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */
#include "BaseStruct.h"
#include "TaskGlobal.h"


typedef enum {
	ERROR_TYPE_ID = 0,
    MAP_PIXEL_WIDTH_ID,
    MAP_PIXEL_HEIGHT_ID,
    MAP_PHY_WIDTH_ID,
    MAP_PHY_HEIGHT_ID,
    MAP_END
} Map_Result;


typedef struct {
    unsigned int width_pixel;				///< 筛选出的宽度值(像素)
    unsigned int height_pixel;				///< 筛选出的高度值(像素)
    double width_phy;						///< 筛选出的宽度值(物理)
    double height_phy;						///< 筛选出的高度值(物理)
} MapParameter;



typedef struct {
    unsigned int x_stat_threshold;			///< X方向上映射后的统计门限值
	unsigned int y_stat_threshold;			///< y方向上映射后的统计门限值
    unsigned int pix_phy_flag;              ///< 0：像素值， 1：物理值
    THRESHOLD_FLOAT width_threshold;        ///< 宽度门限 */
    THRESHOLD_FLOAT heigh_threshold;        ///< 高度门限 */
} MAP_INPUT_PARAM;

typedef struct {
    OUTPUT_COMMON_PARAM	common_param;		///< common parameter
} MAP_OUTPUT_PARAM;

typedef struct {
    PRIVATE_COMMON_PARAM private_common;	///< 私有数据的公共结构体
    MapParameter model_map_rst;             ///< 取样时的结果记录
} MAP_PRIVATE_PARAM;

typedef struct {
    TASK_STEP_HEADER *pStepHeader;
    MAP_INPUT_PARAM *pMapInputParam;
    MAP_OUTPUT_PARAM *pMapOutputParam;
    MAP_PRIVATE_PARAM *pMapPrivateParam;
}TASK_MAP;


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif
