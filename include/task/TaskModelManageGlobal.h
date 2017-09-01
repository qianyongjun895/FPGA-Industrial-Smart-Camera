#ifndef TASKMODELMANAGEGLOBAL_H
#define TASKMODELMANAGEGLOBAL_H

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/**
 * @brief   任务模板数据初始化
 * @param
 * @return
 * @author  <AutumnX>
 * @note
 */
void TaskModelDataInit(void);

/**
 * @brief 获取步骤模板内存指针
 * @param stepIndex 步骤索引
 * @param modelSize 模板大小
 * @param pModelVirtualAddr 模板保存指针
 * @return 0:成功 TASK_MODEL_MEM_FREE_SIZE_NOT_ENOUGH:模板剩余空间不足 TASK_MODEL_MEM_UNUSED_SIZE_NOT_ENOUGH:模板剩余空间足够，但需要重新整理内存
 * @author <AutumnX>
 * @note
 */
int GetTaskStepModelAddr(unsigned int stepIndex, unsigned int modeSize, unsigned int *pModelVirtualAddr);

/**
 * @brief 保存步骤模板
 * @param stepIndex 步骤索引
 * @return 0:成功 其它:失败
 * @author <AutumnX>
 * @note
 */
int SaveStepModelToFile(unsigned int stepIndex);

/**
 * @brief 任务列表有步骤添加或删除时，更新模板文件夹名称
 * @param stepIndex 添加或删除的步骤索引
 * @param oper 1:添加步骤 -1:删除步骤
 * @return 0:成功 其它:失败
 * @author <AutumnX>
 * @note
 */
int UpdateStepModelDirectoryNameProc(unsigned int stepIndex, int oper);

/**
 * @brief 重新载入模板文件，把模板空闲空间整理出来
 * @param
 * @return
 * @author <AutumnX>
 * @note
 */
void ReloadModeFiles(void);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif // TASKMODELMANAGEGLOBAL_H
