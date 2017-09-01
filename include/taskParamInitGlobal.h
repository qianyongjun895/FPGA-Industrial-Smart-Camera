/**
  * @file  [taskParamInitGlobal.h]
  * @brief  任务参数初始化
  * @author  <th>
  * @date  <2017/5/31>
  * @version  <v1.0>
  * @note
  *
  */

#ifndef __TASK_PARAM_INIT_GLOBAL_H
#define __TASK_PARAM_INIT_GLOBAL_H


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


/**
 * @brief 初始化任务数据,查找对应的文档指针和节点指针
 * @param task_type:任务类型;
 * @return 1:获取成功; 0:未找到符合条件的任务参数; -1:失败;
 * @author <th>
 * @note
 */
extern int Init_Task_File(int task_type);

/**
 * @brief 获取任务参数数据
 * @param Task_Param:任务参数指针;
 * @return -1:获取失败; 0:该数据是最后一个数据; 1:可继续获取参数数据;
 * @author <th>
 * @note 调用该函数赋值必须对应xml文件中的数据顺序
 */
extern int Init_Task_Data(void* Task_Param);

/**
 * @brief 获取任务参数完成后释放内存的操作
 * @param void
 * @return void
 * @author <th>
 * @note
 */
extern void Task_Finish(void);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif
