/**
  * @file  [TaskHeaderGlobal.h]
  * @brief  定义任务头的结构体及相关操作函数
  * @author  <Terry>
  * @date  <2017/5/15>
  * @version  <v1.0>
  * @note
  *
  */
#ifndef __TASK_HEADER_GLOBAL_H__
#define __TASK_HEADER_GLOBAL_H__
#include "sszn_basic.h"
#include "BaseStruct.h"

#define JUDGEMEBT_NG 0  ///< 判定失败
#define JUDGEMEBT_OK 1  ///< 判定成功
/* 综合判定是否参与宏定义 */
#define NONPARTICIPATION_SYNTHETIC_JUDGMENT     0	///< 不参与综合判定
#define PARTICIPATION_SYNTHETIC_JUDGMENT	1	///< 参与综合判定

/* 综合判定IO输出掩码 */
#define SYNC_JUDGE_IO_ROUND_OK_MASK			0x1
#define SYNC_JUDGE_IO_ROUND_NG_MASK			0x2
#define SYNC_JUDGE_IO_ROUND_OVER_MASK		0x4

/* 单步NG复位宏定义 */
#define NG_NOT_RESET    0   ///< NG不复位
#define NG_RESET        1   ///< NG复位

/* 脚本执行状态宏定义 */
#define SCRIPT_EXECING			0x1 ///< 脚本执行中
#define SCRIPT_EXEC_OVER		0x2 ///< 脚本执行结束

#define SCRIPT_RST_MAX			16 ///< 脚本步骤产生的最大结果数

/* 模板相关宏定义 */


/**
  * @struct <STEP_IO_OUTPUT_INFO>
  * @brief  每个步骤的IO输出信息
  * @note   本步骤OK或NG时IO输出口选择 0:无输出 1:IO1 2:IO2 4:IO3 8:IO4
  */
typedef struct {
    unsigned int ok_io_index; ///< 步骤OK时,IO输出索引
    unsigned int ng_io_index; ///< 步骤NG时,IO输出索引
} STEP_IO_OUTPUT_INFO;

/**
  * @struct <TASK_HEADER>
  * @brief  任务头结构体
  * @note
  * 整个任务的共有信息和描述信息
  */
typedef struct {
    unsigned int task_step_cnt;                 ///< 任务步骤总数
    unsigned int round_cost_time;               ///< 执行时间,单位毫秒
    unsigned int synth_judge_result;            ///< 综合判定结果
    unsigned int synth_judge_io_status;         ///< 0:两个都不使能 1:使能OK IO  2:使能NG IO 4:使能完成IO
    unsigned int task_round_over_io_index;      ///< 一轮结束时IO输出口选择  1:IO1 2:IO2 4:IO3 8:IO4
    unsigned int synth_judge_ng_reset;          ///< 综合判定失败跳回第一步，0：不使能（不跳回，继续向下走），1：使能（跳回第一步）
    unsigned int ng_reset_flag;                 ///< 该步骤不参与综合判定时,1:NG时复位，0:不复位
    STEP_IO_OUTPUT_INFO synth_judge_io_output;	///< 抓图完成后的IO输出
    unsigned int round_over_flag;               ///< 启动的时候主线程清零，运行线程执行完一轮后置1
    unsigned int script_exec_status;            ///< 脚本执行状态
} TASK_HEADER;

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


/**
 * @brief   任务头指针初始化
 * @param   taskVirtualAddr 任务起始地址
 * @return
 * @author  <AutumnX>
 * @note
 */
void TaskHeadPointerInit(unsigned int taskVirtualAddr);

/**
 * @brief   获取任务头指针
 * @return  任务头指针 如果返回的是NULL，表示获取失败
 * @author  <AutumnX>
 * @note    注意对返回值作非空判断
 */
TASK_HEADER * GetTaskHeadPointer(void);

/**
 * @brief   清空任务头的数据
 * @return  0:成功 其它:失败
 * @author  <AutumnX>
 */
int ClearTaskHead(void);

/**
 * @brief   获取任务步骤总数
 * @return  任务步骤总数
 * @author  <AutumnX>
 */
unsigned int GetTaskStepCount(void);

/**
 * @brief   任务步骤数加1
 * @return  0:成功 其它:失败
 * @author  <AutumnX>
 */
int TaskStepCountInc(void);

/**
 * @brief   任务步骤数减1
 * @return  0:成功 其它:失败
 * @author  <AutumnX>
 */
int TaskStepCountDec(void);

/**
 * @brief   检查步骤数是否达到了最大值
 * @param
 * @return  0:未达到 1:达到
 * @author  <AutumnX>
 * @note
 */
int WetherOverMaxStepCount(void);

/**
 * @brief   获取任务执行时间
 * @return  任务执行时间
 * @author  <AutumnX>
 */
unsigned int GetTaskRoundCostTime(void);

/**
 * @brief   设置任务执行时间
 * @return  任务执行时间
 * @author  <AutumnX>
 */
void SetTaskRoundCostTime(struct timespec *pRoundStart, double trigger_cost);

/**
 * @brief   设置脚本执行状态
 * @return
 * @author  <Terry>
 */
void SetScriptExecStatus(unsigned int status);

/**
 * @brief   设置脚本执行结束状态
 * @return
 * @author  <Terry>
 */
void SetScriptExecOver(void);

/**
 * @brief   获取脚本执行状态
 * @return
 * @author  <Terry>
 */
unsigned int GetScriptExecStatus(void);

/**
 * @brief   设置综合判断失败
 * @return
 * @author  <Terry>
 */
void SetSynthJudgeFail(void);

/**
 * @brief   设置综合判断成功
 * @return
 * @author  <Terry>
 */
void SetSyntheticJudgementSuccess(void);

/**
 * @brief   获取综合判定结果
 * @return  综合判定结果
 * @author  <AutumnX>
 */
unsigned int GetSynthJudgeResult(void);

/**
 * @brief   获取综合判定IO状态
 * @return  综合判定IO状态
 * @author  <AutumnX>
 */
unsigned int GetSyntheticJudgementIoStatus(void);

/**
 * @brief   设置综合判定IO状态
 * @return  0:成功 其它:失败
 * @author  <AutumnX>
 * @note    0:两个都不使能 1:使能OK IO  2:使能NG IO 4:使能完成IO
 */
int SetSyntheticJudgementIoStatus(unsigned int status);

/**
 * @brief   获取综合判定 OK IO
 * @return  综合判定 OK IO
 * @author  <AutumnX>
 */
unsigned int GetSyntheticJudgementOkIo(void);

/**
 * @brief   设置综合判定 OK IO
 * @return  0:成功 其它:失败
 * @author  <AutumnX>
 */
int SetSyntheticJudgementOkIo(unsigned int ioIndex);

/**
 * @brief   获取综合判定 NG IO
 * @return  综合判定 NG IO
 * @author  <AutumnX>
 */
unsigned int GetSyntheticJudgementNgIo(void);

/**
 * @brief   设置综合判定 NG IO
 * @return  0:成功 其它:失败
 * @author  <AutumnX>
 */
int SetSyntheticJudgementNgIo(unsigned int ioIndex);

/**
 * @brief   获取综合判定失败跳回第一步的使能状态
 * @return  综合判定失败跳回第一步的使能状态
 * @author  <AutumnX>
 * @note    0：不使能（不跳回，继续向下走），1：使能（跳回第一步）
 */
unsigned int GetSynthJudgeNgResetFlag(void);

/**
 * @brief   设置综合判定失败跳回第一步的使能状态
 * @return  0:成功 其它:失败
 * @author  <AutumnX>
 * @note    0：不使能（不跳回，继续向下走），1：使能（跳回第一步）
 */
int SetSynthJudgeNgResetFlag(unsigned int enStatus);

/**
 * @brief   获取一轮结束时选择的IO输出口
 * @return  0:成功 其它:失败
 * @author  <AutumnX>
 * @note    1:IO1 2:IO2 4:IO3 8:IO4
 */
unsigned int GetTaskRoundOverIoIndex(void);

/**
 * @brief   设置一轮结束时IO输出口选择
 * @return  0:成功 其它:失败
 * @author  <AutumnX>
 * @note    1:IO1 2:IO2 4:IO3 8:IO4
 */
int SetTaskRoundOverIoIndex(unsigned int ioIndex);

/**
 * @brief   一轮结束时IO输出
 * @return
 * @author  <Terry>
 * @note
 */
void RoundOverIoOutput(void);

/**
 * @brief   获取综合判定NG复位标志
 * @return  综合判定NG复位标志
 * @author  <AutumnX>
 * @note    综合判定NG时 1:复位 0:不复位
 */
unsigned int GetNgResetFlag(void);

/**
 * @brief   设置综合判定NG复位标志
 * @return  0:成功 其它:失败
 * @author  <AutumnX>
 * @note    1:复位 0:不复位
 */
int SetNgResetFlag(unsigned int flag);

/**
 * @brief 设置执行一轮完成的标志
 * @param
 * @return
 * @author <Terry>
 * @note
 */
void SetRoundOverFlag(unsigned int flag);

/**
 * @brief 获取执行一轮完成的标志
 * @param
 * @return
 * @author <Terry>
 * @note
 */
unsigned int GetRuondOverFlag(void);

/**
 * @brief   结束时综合判定输出
 * @return
 * @author  <Terry>
 * @note
 */
void Task_Synth_Judge_Result_Output(void);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __TASKMANAGE_H__ */
