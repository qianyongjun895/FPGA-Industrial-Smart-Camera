/**
  * @file  [taskParamCreateGlobal.h]
  * @brief 任务参数的创建
  * @author  <th>
  * @date  <2017/6/1>
  * @version  <v1.0>
  * @note
  *
  */

#ifndef __TASK_PARAM_CREATE_GLOBAL_H
#define __TASK_PARAM_CREATE_GLOBAL_H


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/**
 * @brief 创建任务参数
 * @param task_type:任务类型;
 *        Param_Name:保存的参数名
 * @return -1:创建失败; 0:该任务的参数无法创建; 1:创建成功;
 * @author <th>
 * @note
 */
extern int Create_Task_Param(int task_type, char *Param_Name);

/**
 * @brief 设置任务参数的数据
 * @param Param_String:参数名的字符串;
 *        Task_Param:参数的数据;
 *        Data_Type:参数的类型
 * @return -1:设置失败; 0:设置成功;
 * @author <th>
 * @note
 */
extern int Set_Task_Param(char *Param_String, void *Task_Param, int Data_Type);

/**
 * @brief 任务参数设置完成后的文件保存
 * @param void
 * @return -1:保存失败; 0:保存成功
 * @author <th>
 * @note
 */
extern int Set_Task_Param_Finish(void);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif
