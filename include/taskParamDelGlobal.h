/**
  * @file  [taskParamDelGlobal.h]
  * @brief 任务参数的删除
  * @author  <th>
  * @date  <2017/6/2>
  * @version  <v1.0>
  * @note
  *
  */

#ifndef __TASK_PARAM_DEL_GLOBAL_H
#define __TASK_PARAM_DEL_GLOBAL_H


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/**
 * @brief 删除任务参数
 * @param task_type:任务类型;
 *        Param_Name:删除的参数名
 * @return -1:删除失败; 0:该任务的参数无法删除; 1:删除成功;
 * @author <th>
 * @note
 */
extern int Del_Task_Param(int task_type, char *Param_Name);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif
