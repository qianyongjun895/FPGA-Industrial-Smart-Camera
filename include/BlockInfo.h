/**
  * @file  [BlockInfo.h]
  * @brief  关联关系及数据引用的管理
  * @author  <Terry>
  * @date  <2017/06/03>
  * @version  <v1.0>
  * @note
  *
  */

#ifndef BLOCKINFO_H
#define BLOCKINFO_H

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


#define IO_SIGINAL_BLOCK	0x1
#define CMD_BLOCK		0x2
#define DELAY_BLOCK		0x3
#define TASK_STOP_BLOCK		0x4
#define COND_TRIGGER		0x5
#define SAVE_PIC_BLOCK          0x6

typedef struct {
    int CurrentStep;	/* 当前步数 */
    int BlockReason;	/* 阻塞原因 */
} RUN_BLOCK_INFO;

/**
 * @brief 清理阻塞信息
 * @param
 * @return
 * @author <Terry>
 * @note
 */
void BlockInfoClear(void);

/**
 * @brief 获取阻塞的步骤号
 * @param
 * @return
 * @author <Terry>
 * @note
 */
unsigned int BlockStepIndexGet(void);

/**
 * @brief 获取阻塞的原因
 * @param
 * @return
 * @author <Terry>
 * @note
 */
unsigned int BlockReasonGet(void);

/**
 * @brief 设置阻塞的步骤号、阻塞源：IO触发信号
 * @param step_index:步骤号
 * @return
 * @author <Terry>
 * @note
 */
void BlockInfoIoSet(unsigned int step_index);

/**
 * @brief 设置阻塞的步骤号、阻塞源：命令触发信号
 * @param step_index:步骤号
 * @return
 * @author <Terry>
 * @note
 */
void BlockInfoCmdSet(unsigned int step_index);

/**
 * @brief 设置阻塞的步骤号、阻塞源：延时等待
 * @param step_index:步骤号
 * @return
 * @author <Terry>
 * @note
 */
void BlockInfoDelaySet(unsigned int step_index);

/**
 * @brief 设置阻塞的步骤号、阻塞源：任务停止中
 * @param step_index:步骤号
 * @return
 * @author <Terry>
 * @note
 */
void BlockInfoStopSet(unsigned int step_index);

/**
 * @brief 设置阻塞的步骤号、阻塞源：条件触发
 * @param step_index:步骤号
 * @return
 * @author <Terry>
 * @note
 */
void BlockInfoCondSet(unsigned int step_index);

/**
 * @brief 设置阻塞的步骤号、阻塞源：图像保存
 * @param step_index:步骤号
 * @return
 * @author <Terry>
 * @note
 */
void BlockInfoSavePicSet(unsigned int step_index);
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif // BLOCKINFO_H
