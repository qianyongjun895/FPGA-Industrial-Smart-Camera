/**
  * @file  [TaskInitGlobal.h]
  * @brief  任务初始化
  * @author  <Terry>
  * @date  <2017/5/17>
  * @version  <v1.0>
  * @note
  *
  */
#ifndef __TASK_INIT_GLOBAL_H__
#define __TASK_INIT_GLOBAL_H__
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/**
* @brief 任务相关地址初始化
* @param task_phy_addr: 任务物理地址
* @param task_size: 任务空间大小
* @param rst_phy_addr: 结果物理地址
* @param rst_size: 结果空间大小
* @param model_phy_addr: 模板物理地址
* @param model_size: 模板空间大小
* @return 0: 成功，other: 失败
* @author <Terry>
* @note
*/
int TaskAddrInit_Simple(unsigned int task_phy_addr, unsigned int task_size,
			  unsigned int rst_phy_addr, unsigned int rst_size,
			  unsigned int model_phy_addr, unsigned int model_size,
			  unsigned int acce_phy_addr, unsigned int acce_size,
			  unsigned int gdata_phy_addr, unsigned int gdata_size);

/**
* @brief 任务初始化
* @param
* @return 0: 成功，other: 失败
* @author <AutumnX>
* @note
*/
int TaskInitialization(void);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __TASKMANAGE_H__ */
