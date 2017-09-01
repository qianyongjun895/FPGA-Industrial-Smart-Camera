/**
  * @file  [TaskCompassGlobal.h]
  * @brief 关联定位
  * @author  <Terry>
  * @date  <2017/5/20>
  * @version  <v1.0>
  * @note
  *
  */
#ifndef __TASK_COMPASS_GLOBAL_H__
#define __TASK_COMPASS_GLOBAL_H__
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */
#include "TaskHeaderGlobal.h"
#include "BaseStruct.h"
#include "AcceCommon.h"


/**
  * @struct  <COMPASS_DATA>
  * @brief  关联定位数据结构
  * @note
  */
typedef struct {
    double compass_x; ///< 关联定位 x 坐标值
    double compass_y; ///< 关联定位 y 坐标值
    double compass_theta; ///< 关联定位旋转角度
}COMPASS_DATA;

/**
  * @struct  <COMPASS_RUN_DATA>
  * @brief  关联定位数据结构
  * @note
  */
typedef struct {
    COMPASS_DATA ori_data; ///< 参考步骤原始数据
    COMPASS_DATA run_data; ///< 参考步骤运行数据
    /* 直接在本结构体中包含参考点信息，以免每个功能中单独写重复代码 */
    POINT_F ref_model_point; ///< 取模板时参考点的位置
    POINT_F ref_point;	///< 运行时参考点的位置
    double rt_theta; ///< 运行时参考的旋转角度
}COMPASS_RUN_DATA;

/**  @brief  关联定位x坐标的步骤索引  */
#define COMPASS_POINT_X_STEP_INDEX		0
/**  @brief  关联定位y坐标的步骤索引  */
#define COMPASS_POINT_Y_STEP_INDEX		1
/**  @brief  关联定位旋转角度的步骤索引  */
#define COMPASS_DEGREE_STEP_INDEX		2
/* 关联设置类型设置宏定义 */
/**  @brief  关联定位类型为空，即不使能关联定位  */
#define COMPASS_NULL		0
/**  @brief  关联定位类型为手动设置  */
#define COMPASS_MANUAL		1
/**  @brief  关联定位类型为引用其它步骤数据  */
#define COMPASS_REF_VALUE	2


/**
 * @brief 添加任务步骤时，更新任务各步骤关联定位信息
 * @param stepIndex：要更新的步骤号
 * @param addStepIndex：添加步骤的位置索引
 * @return 0:成功，其它：失败
 * @author <AutumnX>
 * @note
 */
int TaskAddStepUpdateStepCompassInfo(unsigned int stepIndex, unsigned int addStepIndex);

/**
 * @brief 删除任务步骤时，更新任务各步骤关联定位信息
 * @param stepIndex：要更新的步骤号
 * @param delStepIndex：删除步骤的位置索引
 * @return 0:成功，其它：失败
 * @author <AutumnX>
 * @note
 */
int TaskDeleteStepUpdateStepCompassInfo(unsigned int stepIndex, unsigned int delStepIndex);

/**
 * @brief 检测checkStepIndex步是否被stepIndex步用作关联定位
 * @param stepIndex：被检查的步骤索引
 * @param checkStepIndex：是否被引用的步骤索引
 * @return 0:否，1：是
 * @author <AutumnX>
 * @note
 */
int WhetherBeUsedByCompass(unsigned int stepIndex, unsigned int checkStepIndex);

/**
 * @brief 对指定步骤的区域筛选范围进行旋转操作
 * @param stepIndex：步骤索引
 * @param pSelectCfgOri：原始筛选范围
 * @param pSelectCfgRot：旋转后筛选范围
 * @return 0:成功，others：不成功
 * @author <Terry>
 * @note
 */
int Task_Select_Area_Rotate_Calc(int step_index, SELECT_MODEL_CFG *pSelectCfgOri, SELECT_MODEL_CFG *pSelectCfgRot);

/**
 * @brief 对指定步骤的CPT DDR范围进行平移操作
 * @param stepIndex：步骤索引
 * @param pSelectCfgOri：原始ROI范围
 * @param pSelectCfgRot：移动后ROI范围
 * @return 0:成功，others：不成功
 * @author <Terry>
 * @note
 */
int Task_Cpt_Ddr_Roi_Calc(int step_index, CPT_ROI_PARAM *pCptRoiOri, CPT_ROI_PARAM *pCptRoiRot);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __TASKMANAGE_H__ */
