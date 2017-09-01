/**
  * @file  [taskParamChangeGlobal.h]
  * @brief 任务参数的修改
  * @author  <th>
  * @date  <2017/6/2>
  * @version  <v1.0>
  * @note
  *
  */

#ifndef __TASK_PARAM_CHANGE_GLOBAL_H
#define __TASK_PARAM_CHANGE_GLOBAL_H


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/**
 * @brief 更改任务引用的参数
 * @param task_type:任务类型;
 *        Param_Name:引用的参数名
 * @return -1:引用失败; 0:该任务的参数无法引用; 1:引用成功;
 * @author <th>
 * @note
 */
extern int Change_Task_Param(int task_type, char *Param_Name);

/**
 * @brief 初始化任务参数
 * @param task_type:任务类型
 * @return -1:失败; 0:该任务的参数无法初始化; 1:成功;
 * @author <th>
 * @note
 */
extern int Init_Task_ParamData(int task_type);

/**
 * @brief 获取任务参数套数,该函数在InitTaskParamData之后调用
 * @param void
 * @return 任务参数套数
 * @author <th>
 * @note
 */
extern int Get_Task_Param_Num();

/**
 * @brief 获取任务参数名
 * @param Param_index:参数索引(从0开始),小于任务参数套数
 *        Param_Name:任务参数名
 * @return -1:失败; 0:未找到索引对应的参数; 1:成功;
 * @author <th>
 * @note
 */
extern int Get_Task_Param_Name(int Param_index, char *Param_Name);

/**
 * @brief 获取任务参数名完成后释放内存的操作
 * @param void
 * @return void
 * @author <th>
 * @note
 */
extern void Get_Task_Param_Name_Finish(void);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif
