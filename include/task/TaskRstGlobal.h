/**
  * @file  [TaskRstGlobal.h]
  * @brief  任务结果对外接口
  * @author  <Terry>
  * @date  <2017/5/15>
  * @version  <v1.0>
  * @note
  */

#ifndef _TASK_RST_GLOBAL_H_
#define _TASK_RST_GLOBAL_H_
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */
#include "BaseStruct.h"

/**
 * @brief 初始化个任务结果指针数组为NULL
 * @param
 * @return
 * @author <Terry>
 * @note
 */
void TaskRstMemAddrSizeInit(void *pRstVirAddr, unsigned int size);

/**
 * @brief 运行时执行结果内存重新划分
 * @param
 * @return
 * @author <Terry>
 * @note
 *  考虑到每次运行之前都有可能修改任务列表，导致结果内存的划分发生变化，
 *  因此每次运行任务前通过本函数进行结果内存的重新划分。
 */
int TaskRunRstMemInit(void);

/**
 * @brief 返回指定步对应的结果内存指针
 * @param
 * @return step_index步对应的结果内存指针
 * @author <Terry>
 * @note
 */
RST_VALUE_STRUCT * TaskStepResultMemGet(unsigned int step_index);

/**
 * @brief 返回指定步对应的结果内存指针,仅供脚本使用
 * @param
 * @return step_index步对应的结果内存指针
 * @author <Terry>
 * @note
 */
RST_VALUE_STRUCT * TaskStepResultMemGetForScript(unsigned int step_index);

/**
 * @brief 清除指定步骤的结果
 * @param step_index: 步骤索引
 * @return
 * @author <Terry>
 * @note
 */
void Task_Step_Result_Output_Mem_Clear(unsigned int step_index);

/**
 * @brief 清除指定步骤的结果，用于跳转命令清除中间步骤结果数据
 * @param step_index: 起始步骤索引
 *        step_end: 结束枚举索引
 * @return
 * @author <Terry>
 * @note
 */
void Task_Steps_Result_Output_Mem_Clear(unsigned int step_start, unsigned int step_end);

/**
 * @brief 测量功能获取其他步骤的线
 * @param step_index: 引用参数步骤号
 * @param result_index: 引用数据的开始枚举值
 * @param pRstValue: 结果保存指针
 * @return 0: 成功，others: 失败
 * @author <Terry>
 * @note
 */
int Task_Step_Rst_Get(unsigned int step_index, unsigned int result_index, unsigned int model_flag, RST_VALUE_STRUCT *pRstValue);

/**
 * @brief 测量功能获取其他步骤的线
 * @param ref_step: 引用参数步骤号
 * @param result_index: 引用数据的开始枚举值
 * @param pLineResult: 线结果保存指针
 * @param model_flag: 取样状态标志位，0: 运行状态，1: 取样状态
 * @return 0: 成功，others: 失败
 * @author <Terry>
 * @note
 */
int measure_ref_line_result_get(int ref_step, int result_index, void *pLineResult, unsigned int model_flag);

/**
 * @brief 测量功能获取其他步骤的点位置
 * @param ref_step: 引用参数步骤号
 * @param point_ref_index: 引用数据的开始枚举值
 * @param pPoint: 位置保存指针
 * @param model_flag: 取样状态标志位，0: 运行状态，1: 取样状态
 * @return 0: 成功，others: 失败
 * @author <Terry>
 * @note
 */
int measure_ref_point_result_get(unsigned int ref_step, unsigned int point_ref_index, POINT_F *pPoint, unsigned int model_flag);

/**
 * @brief 获取多结果任务步骤中的结果数
 * @param ref_step: 引用参数步骤号
 * @param model_flag: 取样状态标志位，0: 运行状态，1: 取样状态
 * @param pNum: 数量保存指针
 * @return 0: 成功，others: 失败
 * @author <Terry>
 * @note
 */
int TaskMultiRstNumGet(unsigned int ref_step, unsigned int model_flag, unsigned int *pNum);

/**
 * @brief 获取指定步骤的结果数量
 * @param step_index: 步骤索引
 *        pRstNum: 结果个数指针
 * @return 0：成功，others：失败
 * @author <Terry>
 * @note
 */
int Task_Step_Result_Num_Get(unsigned int step_index, unsigned int *pRstNum);

/**
 * @brief 设置错误类型结果数据
 * @param step_index: 步骤号
 *        error_type: 错误码
 * @return
 * @author <Terry>
 * @note
 */
void Task_Error_Type_Id_Value_Set(unsigned int step_index, int error_type);

/**
 * @brief 检查结果索引是否有效
 * @param step_index: 步骤索引
 *        result_index: 结果索引
 * @return 0：成功，others：失败
 * @author <Terry>
 * @note
 */
int Task_Step_Result_Index_Valid_Check(unsigned int step_index, unsigned int result_index);

/**
 * @brief 保存无符号整形数到指定步骤的指定偏移位置
 * @param step_index: 步骤索引
 *        result_index: 结果偏移
 *		  value：待保存结果
 * @return 0：成功，others：失败
 * @author <Terry>
 * @note
 */
int Task_Step_Unsigned_Result_Set(unsigned int step_index, unsigned int result_index, unsigned int value);

/*
 * @brief 保存有符号整形数到指定步骤的指定偏移位置
 * @param step_index: 步骤索引
 *        result_index: 结果偏移
 *		  value：待保存结果
 * @return 0：成功，others：失败
 * @author <Terry>
 * @note
 */
int Task_Step_Signed_Result_Set(unsigned int step_index, unsigned int result_index, int value);

/*
 * @brief 保存浮点数到指定步骤的指定偏移位置
 * @param step_index: 步骤索引
 *        result_index: 结果偏移
 *		  value：待保存结果
 * @return 0：成功，others：失败
 * @author <Terry>
 * @note
 */
int Task_Step_Float_Result_Set(unsigned int step_index, unsigned int result_index, float value);

/*
 * @brief 保存双精度浮点数到指定步骤的指定偏移位置
 * @param step_index: 步骤索引
 *        result_index: 结果偏移
 *		  value：待保存结果
 * @return 0：成功，others：失败
 * @author <Terry>
 * @note
 */
int Task_Step_Double_Result_Set(unsigned int step_index, unsigned int result_index, double value);

/* 以下函数为GData相关的处理函数 */
/**
 * @brief 初始化GData的全局指针
 * @param
 * @return
 * @author <Terry>
 * @note
 */
void TaskGDataAddrSizeInit(void *pGDataVirAddr, unsigned int size);

#define G_RST_DATA_ARRAY_SIZE	1024	///全局数组的大小
#define G_DATA_MANUAL			0		///手动配置的全局结果数组
#define G_DATA_DYNAMIC			1		///动态配置的全局结果数组
#define G_DATA_FILE_PATH 		"task/tmp/G_Result/Gdata.bin"
#define G_DATA_DIR_PATH			"task/tmp/G_Result"
/**
 * @brief 全局数据初始化，UI启动的时候调用该函数
 * @param
 * @return 0:成功，other:失败
 * @author <Terry>
 * @note
 */
int G_Rst_Data_Init(void);

/**
 * @brief 设置指定类型的数据
 * @param type：数据类型
 		  index：索引号
 		  pRstValue：输入参数指针
 * @return 0：成功，other：失败
 * @author <Terry>
 * @note
 */
int G_Data_Set(unsigned int type, unsigned int index, RST_VALUE_STRUCT *pRstValue);

/**
 * @brief 获取指定类型指定位置的数据
 * @param type：数据类型
 		  index：索引号
 		  pRstValue：指向结果保存的指针
 * @return 0：成功，other：失败
 * @author <Terry>
 * @note
 */
int G_Data_Get(unsigned int type, unsigned int index, RST_VALUE_STRUCT *pRstValue);

/**
 * @brief 保存手动配置的数据
 * @param 
 * @return 0：成功，other：失败
 * @author <Terry>
 * @note
 */
int G_Data_Save(void);

/**
 * @brief 重新加载任务全局数据，切换任务的时候用
 * @param 
 * @return 0：成功，other：失败
 * @author <Terry>
 * @note
 */
int G_Data_ReLoad(void);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif
