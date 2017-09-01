/**
  * @file  [TaskExecGlobal.h]
  * @brief  任务执行模块
  * @author  <Terry>
  * @date  <2017/5/17>
  * @version  <v1.0>
  * @note
  *
  */
#ifndef __TASK_EXEC_H__
#define __TASK_EXEC_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/**
 * @brief 设置任务运行状态为运行
 * @param
 * @return
 * @author <Terry>
 * @note
 */
void TaskStartSet(void);

/**
 * @brief 设置任务运行状态为停止中
 * @param
 * @return
 * @author <Terry>
 * @note
 */
void TaskStopingSet(void);

/**
 * @brief 设置任务运行状态为完全停止
 * @param
 * @return
 * @author <Terry>
 * @note
 */
void TaskStopSet(void);

/**
 * @brief 返回当前任务状态
 * @param
 * @return
 * @author <Terry>
 * @note
 */
unsigned int TaskStatusGet(void);

/**
 * @brief 任务是否处于运行状态检测
 * @param
 * @return 0:非运行状态，1：运行状态
 * @author <Terry>
 * @note
 */
int TaskStatusRunningCheck(void);

/**
 * @brief 设置仿真状态
 * @param
 * @return
 * @author <Terry>
 * @note
 */
void TaskSimulateModeSet(void);

/**
 * @brief 清除仿真状态
 * @param
 * @return
 * @author <Terry>
 * @note
 */
void TaskSimulateModeClear(void);

/**
 * @brief 获取仿真状态
 * @param
 * @return
 * @author <Terry>
 * @note
 */
unsigned int TaskSimulateModeGet(void);
/**
 * @brief 单步任务执行
 * @param step_index：任务索引号
 * @return 0：成功，others：失败状态值
 * @author <Terry>
 * @note
 */
int TaskStepExec(unsigned int step_index);

/**
 * @brief 设置仿真加载图像状态
 * @param
 * @return
 * @author <Terry>
 * @note
 */
void TaskSimulateLoadPicFlagSet(void);

/**
 * @brief 获取仿真加载图像状态
 * @param
 * @return
 * @author <Terry>
 * @note
 */
unsigned int TaskSimulateLoadPicFlagGet(void);

/**
 * @brief 清除仿真加载图像状态
 * @param
 * @return
 * @author <Terry>
 * @note
 */
void TaskSimulateLoadPicFlagClear(void);

/**
 * @brief 设置仿真两轮之间间隔时间
 * @param gap_ms:间隔时间，单位ms
 * @return
 * @author <Terry>
 * @note
 */
void TaskSimulateGapTimeSet(unsigned int gap_ms);
/**
 * @brief 获取仿真两轮之间间隔时间
 * @param
 * @return
 * @author <Terry>
 * @note
 */
unsigned int TaskSimulateGapTimeGet(void);
/**
 * @brief ok_pic_save_flag_set
 * @param flag 0：不保存，1：保存
 * @author pml
 * @date 2017/7/27
 * @note 设置运行保存OK图片的标志
 */
void ok_pic_save_flag_set(unsigned int flag);

/**
 * @brief ng_pic_save_flag_set
 * @param flag 0：不保存，1：保存
 * @author pml
 * @date 2017/7/27
 * @note 设置运行保存NG图片的标志
 */
void ng_pic_save_flag_set(unsigned int flag);

/**
 * @brief ok_pic_save_flag_get
 * @return 0：不保存，1：保存
 * @author pml
 * @date 2017/7/27
 * @note 获取运行保存OK图片的标志
 */
unsigned int ok_pic_save_flag_get(void);

/**
 * @brief ng_pic_save_flag_get
 * @return 0：不保存，1：保存
 * @author pml
 * @date 2017/5/12
 * @note 获取运行保存NG图片的标志
 */
unsigned int ng_pic_save_flag_get(void);


/**
 * @brief 设置全局变量g_step_index
 * @param step_next: 下一步的步骤号
 * @return
 * @author <Terry>
 * @note
 */
void TaskGlobalStepIndexSet(unsigned int step_next);

/**
 * @brief 全体任务执行
 * @param
 * @return
 * @author <Terry>
 * @note
 */
void TaskExec(void);

/**
 * @brief 全体任务执行N轮
 * @param total_round:执行的轮数
 * @return
 * @author <Terry>
 * @note
 */
void TaskExecNRound(unsigned int total_round);

/**
 * @brief 仿真全体任务执行
 * @param
 * @return
 * @author <Terry>
 * @note
 */
void TaskExecSimulate(void);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __TASK_EXEC_H__ */
