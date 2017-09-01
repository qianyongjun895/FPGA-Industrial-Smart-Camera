/**
  * @file  [TaskRegGlobal.h]
  * @brief  任务注册对外接口函数
  * @author  <Terry>
  * @date  <2017/5/11>
  * @version  <v1.0>
  * @note
  * 任务相关函数注册
  * 每个实际的功能会被封装成单独的库文件，UI进程启动的时候会根据function.xml中的配置信息
  * 初始化gTaskCBSets，通过调用库文件中的初始化函数注册TASK_CB_FUNC指针。
  * 每个功能函数中必须包含一个xxx_cb_reg回调函数，其中xxx在xml中指定的库名字。
  * 比如圆定位功能，在xml里面name指定值为circle，在库里面需要对应的一个circle_cb_reg函数，
  * 该函数返回其对应的TASK_CB_FUNC结构体指针。
  * 主程序加载库的时候通过dlsym函数调用circle_cb_reg函数，获取其TASK_CB_FUNC指针，并调用
  * TaskCbReg进行完成注册。
  * 后续任何任务的操作就是通过gTaskCBSets中注册的函数进行。
  */

#ifndef _TASK_REG_GLOBAL_H_
#define _TASK_REG_GLOBAL_H_
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#define TASK_ID_MAX             2048        ///< 最大任务ID数
#define TASK_USER_DEF_ID_START  1024        ///< 用户自定ID号起始值

/**
 * @brief 获得输出结果大小回调函数的类型定义
 * @author <Terry>
 * @return 输出结果大小
 * @note
 * 请在具体的功能模块中实现函数的定义，并进行注册
 */
typedef unsigned int (*OutputSizefunc)(void);

/**
 * @brief 输出内存初始化回调函数的类型定义
 * @author <Terry>
 * @param[in] step_index 步骤索引
 * @return
 * @note
 * 请在具体的功能模块中实现函数的定义，并进行注册
 */
typedef void (*OutputMemTypeInitfunc)(unsigned int step_index);

/**
 * @brief 结果数量获取回调函数的类型定义
 * @author <Terry>
 * @param[in] step_index 步骤索引
 * @param[in] model_set_flag 模板设置标志
 * @param[out] pValue 结果数量
 * @return  0:成功 其它:失败
 * @note
 * 请在具体的功能模块中实现函数的定义，并进行注册
 */
typedef int (*TaskResultCountGetFunc)(unsigned int step_index, unsigned int model_set_flag, unsigned int *pValue);

/**
 * @brief 取样/确定 回调函数的类型定义
 * @author <Terry>
 * @param[in] pTaskStructCommon 任务结构指针
 * @return  0:成功 其它:失败
 * @note
 * 请在具体的功能模块中实现函数的定义，并进行注册
 */
typedef int (*TaskSetfunc)(void *pTaskStructCommon);

/**
 * @brief 步骤运行回调函数的类型定义
 * @author <Terry>
 * @param[in] pTaskStructCommon 任务结构指针
 * @return  0:成功 其它:失败
 * @note
 * 请在具体的功能模块中实现函数的定义，并进行注册
 */
typedef int (*TaskRunfunc)(void *pTaskStructCommon);

/**
 * @brief 模板数据写入输出内存回调函数的类型定义
 * @author <Terry>
 * @param[in] step_index 步骤索引
 * @return  0:成功 其它:失败
 * @note
 * 请在具体的功能模块中实现函数的定义，并进行注册
 */
typedef int (*ModelRstToOutputMem)(unsigned int step_index);

/**
 * @brief 任务列表添加步骤时，更新步骤专有引用信息回调函数的类型定义
 * @author <AutumnX>
 * @param[in] step_index 步骤索引
 * @param[in] addStepIndex 模板设置标志
 * @return  0:成功 其它:失败
 * @note
 * 请在具体的功能模块中实现函数的定义，并进行注册
 */
typedef int (*TaskAddStepUpdateLinkInfoFunc)(unsigned int stepIndex, unsigned int addStepIndex);

/**
 * @brief 任务列表删除步骤时，更新步骤专有引用信息回调函数的类型定义
 * @author <AutumnX>
 * @param[in] step_index 步骤索引
 * @param[in] delStepIndex 模板设置标志
 * @return  0:成功 其它:失败
 * @note
 * 请在具体的功能模块中实现函数的定义，并进行注册
 */
typedef int (*TaskDeleteStepUpdateLinkInfoFunc)(unsigned int stepIndex, unsigned int delStepIndex);

/**
 * @brief 检查某步骤是否被本步骤专有引用信息回调函数的类型定义
 * @author <AutumnX>
 * @param[in] step_index 步骤索引
 * @param[in] checkStepIndex 模板设置标志
 * @return  0:成功 其它:失败
 * @note
 * 请在具体的功能模块中实现函数的定义，并进行注册
 */
typedef int (*WhetherBeUsedByThisStepFunc)(unsigned int stepIndex, unsigned int checkStepIndex);

/**
 * @brief 工具库私有资源初始化函数接口
 * @author <Terry>
 * @param
 * @return  0:成功 其它:失败
 * @note
 * 请在具体的功能模块中实现函数的定义，并进行注册
 */
typedef int (*TaskInitFunc)(void);

/**
 * @brief 工具库私有资源注销函数接口
 * @author <Terry>
 * @param
 * @return  0:成功 其它:失败
 * @note
 * 请在具体的功能模块中实现函数的定义，并进行注册
 */
typedef int (*TaskDeInitFunc)(void);


/** @struct <TASK_CB_FUNC>
 *  @brief 任务回调函数结构体
 *  @note
 */
typedef struct {
    OutputSizefunc fpOutputSize;    				///< 输出结果的大小
    OutputMemTypeInitfunc fpOutputMemTypeInit;  	///< 输出内存的初始化
    ModelRstToOutputMem fpModelRstToOutputMem;  	///< 模板数据转化成正常结果数据
    TaskSetfunc fpSetFunc;  						///< 任务设置模板的接口
    TaskRunfunc fpRunFunc;  						///< 任务运行的接口
    TaskResultCountGetFunc fpRstCountFunc;  		///< 任务结果数量的获取接口
    TaskAddStepUpdateLinkInfoFunc fpTaskAddUpdateStepLinkInfo; 			///< 任务添加步骤更新步骤专有引用信息
    TaskDeleteStepUpdateLinkInfoFunc fpTaskDeleteUpdateStepLinkInfo; 	///< 任务删除步骤更新步骤专有引用信息
    WhetherBeUsedByThisStepFunc fpWhetherBeUsedByThisStep; 				///< 检查某步是否被专有引用信息引用
    TaskInitFunc fpTaskInit;						///< 工具库私有资源初始化接口
	TaskDeInitFunc fpTaskDeInit;					///< 工具库私有资源注销函数接口
} TASK_CB_FUNC;

/** 任务回调函数结构体指针数组 */
extern TASK_CB_FUNC *gTaskCBSets[TASK_ID_MAX];

/**
 * @brief 功能相关函数注册数组初始化
 * @param
 * @return
 * @author <Terry>
 * @note
 */
void TaskCbArrayInit(void);

/**
 * @brief 功能函数注册
 * @param
 * @return
 * @author <Terry>
 * @note
 */
int TaskCbReg(unsigned int task_id, TASK_CB_FUNC *pTaskCbPointer);

/**
 * @brief 功能函数注销
 * @param
 * @return
 * @author <Terry>
 * @note
 */
int TaskCbUnReg(unsigned int task_id);

/**
 * @brief 获取指定功能ID的回调函数指针
 * @param
 * @return
 * @author <Terry>
 * @note
 */
TASK_CB_FUNC *TaskCbPointerGet(unsigned int task_id);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif
