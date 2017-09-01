/**
  * @file  [TaskStepGlobal.h]
  * @brief  定义任务步骤的结构体及相关操作函数
  * @author  <Terry>
  * @date  <2017/5/15>
  * @version  <v1.0>
  * @note
  *
  */
#ifndef __TASK_STEP_GLOBAL_H__
#define __TASK_STEP_GLOBAL_H__

#include "TaskHeaderGlobal.h"

/** @brief  IO输出模式配置文件路径 */
#define IO_OUTPUT_MODE_CONFIG_FILE_PATH "task/tmp/config/IOOutputMode.cfg"

/** @brief  任务步骤相关宏定义 */
#define TS_SIZE				0x2000  ///< 单个步骤占用8KB内存
#define TS_MAX_NUM			0x100   ///< 最大步骤数量
#define TS_HEADER_SIZE		2048    ///< 任务头结构体大小上限
#define TS_INPUT_SIZE		2560    ///< 输入参数结构体大小上限
#define TS_OUTPUT_SIZE		512     ///< 输出参数结构体大小上限
#define TS_PRIVATE_SIZE		3072    ///< 私有参数结构体大小上限
#define TS_HEADER_OFFSET	0       ///< 任务头偏移量
#define TS_INPUT_OFFSET		(TS_HEADER_SIZE)    ///< 输入参数偏移量
#define TS_OUTPUT_OFFSET	(TS_HEADER_SIZE+TS_INPUT_SIZE)  ///< 输出参数偏移量
#define TS_PRIVATE_OFFSET	(TS_HEADER_SIZE+TS_INPUT_SIZE+TS_OUTPUT_SIZE)   ///< 私有参数偏移量

/** @brief  位图掩码数组大小 */
#define BITMAP_ARRAY_SIZE       8
/** @brief  引用步骤最大个数 */
#define COMBOBOX_COUNT 5
/** @brief  命令触发的最大命令长度 */
#define USER_TRIGGER_DATA_SIZE  16
/** @brief  步骤参数无效 */
#define PARAM_VALID_FLAG_NG 0
/** @brief  步骤参数有效 */
#define PARAM_VALID_FLAG_OK 1
/** @brief  步骤别名数组长度 */
#define STEP_ALIAS_SIZE 40

/* 步骤取样结果数据有效标志 */
#define MODULE_RST_INVALID	0 ///< 模板结果无效
#define MODULE_RST_VALID	1 ///< 模板结果有效

/**
  * @struct <LINK_INFO>
  * @brief  引用其它步骤的信息的结构体
  */
typedef struct {
    unsigned short step_index; ///< 引用步骤的索引
    unsigned short result_index; ///< 引用步骤的结果索引
    unsigned int bitmask; ///< 引用步骤结果具体项索引
} LINK_INFO;

/**
  * @struct <STEP_LINK_INFO>
  * @brief  本步骤关联其它步骤的相关信息的
  */
typedef struct {
    unsigned int link_count; ///< 本步引用步骤的总数
    LINK_INFO link_info[COMBOBOX_COUNT]; ///< 详细引用信息
} STEP_LINK_INFO;

/**
  * @struct  <COMPASS_INFO>
  * @brief  关联定位的结构体
  */
typedef struct {
    unsigned int compass_type;	  ///< 关联设置类型 0:无 1:手动输入 2:引用
    unsigned int compass_step;	  ///< 关联步骤
    unsigned int ref_value_index; ///< 从ref_value取值索引
    double     compass_ori_value; ///< 取样时的数据
    double     compass_run_value; ///< 运行时的数据
} COMPASS_INFO;

/**
  * @struct <STEP_IO_INPUT_INFO>
  * @brief  IO触发结构体
  */
typedef struct {
    unsigned short input_pin_index; ///< 触发管脚的index
    unsigned short input_type; ///< IO输入类型
} STEP_IO_INPUT_INFO;

/**
  * @struct <STEP_COMMAND_INPUT_INFO>
  * @brief  命令触发结构体
  */
typedef struct {
    char trigger_data[USER_TRIGGER_DATA_SIZE]; ///< 触发命令
    unsigned short addr;                         ///<数据保存地址1~1024
	char data_cnt;                             ///<数据个数
	char data_type;                            ///<数据类型
	char separator;                            ///<分隔符
	char end_char;                             ///<结束符
	char pad[2];
} STEP_COMMAND_INPUT_INFO;

/**
  * @struct <STEP_CONDITION_INPUT_INFO>
  * @brief  条件触发
  */
typedef struct {
    unsigned int logic_and_or;                          ///< 0表示逻辑与，1表示逻辑或
    unsigned int logic_step_mask[BITMAP_ARRAY_SIZE];    ///< 参与逻辑运算的步骤mask
    unsigned int logic_step_reverse[BITMAP_ARRAY_SIZE]; ///< 参与逻辑运算的结果是否取反，0不取反，1取反
} STEP_CONDITION_INPUT_INFO;

/**
  * @union <STEP_TRIG_UNION>
  * @brief  触发信息联合体
  */
typedef union {
    STEP_IO_INPUT_INFO  io_trig_info; ///< IO 触发信息
    STEP_COMMAND_INPUT_INFO  command_trig_info; ///< 命令触发信息
    STEP_CONDITION_INPUT_INFO  condition_trig_info; ///< 条件跳转信息
} STEP_TRIG_UNION;

/** @brief 触发方式 */
typedef enum {
    NONE_TRIGGER_TYPE = 0,  ///< 0 无触发
    IO_TRIGGER_TYPE, 		///< 1 IO 触发
    CMD_TRIGGER_TYPE, 		///< 2 命令触发
    CON_TRIGGER_TYPE        ///< 3 条件触发
} TRIGGER_TYPE;

/**
  * @struct <STEP_TRIG_INFO>
  * @brief  步骤触发信息结构体
  */
typedef struct {
    unsigned int trig_type;    ///< 0:无触发， 1: 表示IO触发，2:表示命令触发，3表示条件触发
    unsigned int trig_flag;    ///< 0:触发失败  1:触发成功
    STEP_TRIG_UNION  trig_info; ///< 步骤触发信息
} STEP_TRIG_INFO;

/**
  * @struct <MODEL_INFO>
  * @brief  模板信息结构体
  */
typedef struct {
    unsigned int model_flag; ///< 0:无模板 1:有模板
    unsigned int model_size; ///< 模板大小
    unsigned int model_addr;        ///< 模板保存地址（虚地址）
} MODEL_INFO;

/**
  * @struct <TASK_STEP_HEADER>
  * @brief  步骤头结构体
  */
typedef struct {
    unsigned int step_type_id; 		///< 该step 的ID
    unsigned int step_index; 		///< step index
    unsigned int synth_judge_flag;	///< 综合判定标志,1:参与综合判定，0:不参与综合判定
    unsigned char param_valid_flag; ///< 用于在运行之前对必要参数是否配置的检查
    unsigned char step_exec_flag;	///< 用于判断该步骤的可运行状态，1:表示不可执行，0:表示永远执行
    unsigned char homo_index;		///< homography参数数组的索引
    unsigned char scale_cali_index; ///< 刻度校准参数数组的索引
    unsigned int send_data_flag;	///< 发送数据标志 0:没有数据发送 1:本步骤执行后有数据需要发送
    unsigned int execute_count;		///< 单步任务执行次数
    unsigned int compass_enable;	///< 使能compass，0:disable，1:enable
    COMPASS_INFO compass_info[3];	///< 关联定位步骤
    STEP_TRIG_INFO step_trig_info;	///< 本步等待触发信号类型定义
    STEP_IO_OUTPUT_INFO step_io_output_info; ///< 本步I/O输出的配置信息
    STEP_LINK_INFO step_link; 		///< 本步关联其它步骤的信息
    OSD_CONFIG osd_config;			///< osd配置
    MODEL_INFO model_info;			///< 模板信息
    char step_alias[STEP_ALIAS_SIZE]; 	///< 步骤别名
    unsigned int cmos_para_index;
} TASK_STEP_HEADER;

/**
  * @struct <OUTPUT_COMMON_PARAM>
  * @brief 步骤运行结果的共有数据结构
  */
typedef struct {
    unsigned int err_type_id;         ///< 在状态显示的时候使用
    unsigned int OK_count;            ///< 用来计成功的次数
    unsigned int NG_count;            ///< 用来计失败的次数
    double step_cost_time;            ///< 用来计算本步执行时间，单位毫秒(ms)
    double total_ok_cost_time;	      ///< OK情况下执行总时间
    double total_ng_cost_time;	      ///< NG情况下执行总时间
} OUTPUT_COMMON_PARAM;

/**
  * @struct <PRIVATE_COMMON_PARAM>
  * @brief  私有数据通用结构体
  */
typedef struct {
    unsigned int model_rst_valid_flag;	///< 模板结果是否有效
} PRIVATE_COMMON_PARAM;

/**
  * @struct <TASK_STRUCT_COMMON>
  * @brief 步骤分区参数入口地址
  */
typedef struct {
    TASK_STEP_HEADER *pStepHeader;  ///< 步骤头
    void *pInputParam;  ///< 输入参数
    void *pOutputParam;  ///< 输出参数
    void *pPrivateParam;  ///< 私有参数
} TASK_STRUCT_COMMON;

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/**
 * @brief 任务步骤的头、输入参数、输出参数、私有参数指针初始化
 * @param task_base_addr: 任务头映射的虚地址
 * @return
 * @author <Terry>
 * @note
 */
void TaskParamPointerInit(unsigned int task_base_addr);

/**
 * @brief 任务步骤头指针获取
 * @param step_index：步骤号
 * @return
 * @author <Terry>
 * @note
 */
TASK_STEP_HEADER * Task_Step_Head_Get(unsigned int step_index);

/**
 * @brief 任务输入参数指针获取
 * @param step_index：步骤号
 * @return
 * @author <Terry>
 * @note
 */
void * Task_Step_Input_Para_Get(unsigned int step_index);

/**
 * @brief 任务输出参数指针获取
 * @param step_index：步骤号
 * @return
 * @author <Terry>
 * @note
 */
void * Task_Step_Output_Para_Get(unsigned int step_index);
/**
 * @brief 任务私有参数指针获取
 * @param step_index：步骤号
 * @return
 * @author <Terry>
 * @note
 */
void * Task_Step_Private_Para_Get(unsigned int step_index);

/**
 * @brief 获取任务步骤的类型ID
 * @param step_index：步骤号
 * @param pTypeID：任务类型指针
 * @return 0:成功，其它：失败
 * @author <Terry>
 * @note
 */
int Task_Step_Type_ID_Get(unsigned int step_index, unsigned int *pTypeID);

/**
 * @brief 设置任务步骤的类型ID
 * @param step_index：步骤号
 * @param pTypeID：任务类型指针
 * @return 0:成功，其它：失败
 * @author <Terry>
 * @note
 */
int Task_Step_Type_ID_Set(unsigned int step_index, unsigned int TypeID);

/**
 * @brief 获取任务步骤的参与综合判定标志位
 * @param step_index：步骤号
 * @param pSyntheticJudgeFlag：综合判定标志位指针
 * @return 0:成功，其它：失败
 * @author <Terry>
 * @note
 */
int Task_Step_Synthetic_Judge_Flag_Get(unsigned int step_index, unsigned int *pSyntheticJudgeFlag);

/**
 * @brief 设置任务步骤的参与综合判定标志位
 * @param step_index：步骤号
 * @param SyntheticJudgeFlag：综合判定标志位
 * @return 0:成功，其它：失败
 * @author <Terry>
 * @note
 */
int Task_Step_Synthetic_Judge_Flag_Set(unsigned int step_index, unsigned int SyntheticJudgeFlag);

/**
 * @brief 获取任务步骤的参数有效标志位
 * @param step_index：步骤号
 * @param pParamValidFlag：参数有效标志位指针
 * @return 0:成功，其它：失败
 * @author <Terry>
 * @note
 */
int Task_Step_Param_Valid_Flag_Get(unsigned int step_index, unsigned int *pParamValidFlag);
/**
 * @brief 设置任务步骤的参数有效标志位
 * @param step_index：步骤号
 * @param ParamValidFlag：参数标志位
 * @return 0:成功，其它：失败
 * @author <Terry>
 * @note
 */
int Task_Step_Param_Valid_Flag_Set(unsigned int step_index, unsigned int ParamValidFlag);

/**
 * @brief 获取任务步骤的执行使能标志位
 * @param step_index：步骤号
 * @param pExecEnFlag：任务执行使能标志位指针
 * @return 0:成功，其它：失败
 * @author <Terry>
 * @note
 */
int Task_Step_Exec_En_Flag_Get(unsigned int step_index, unsigned int *pExecEnFlag);
/**
 * @brief 设置任务步骤的参数有效标志位
 * @param step_index：步骤号
 * @param ExecEnFlag：任务执行使能标志位
 * @return 0:成功，其它：失败
 * @author <Terry>
 * @note
 */
int Task_Step_Exec_En_Flag_Set(unsigned int step_index, unsigned int ExecEnFlag);

/**
 * @brief 获取任务步骤的Homography参数索引
 * @param step_index：步骤号
 * @param pHomoParamIndex：Homography参数索引指针
 * @return 0:成功，其它：失败
 * @author <Terry>
 * @note
 */
int Task_Step_Homo_Param_Index_Get(unsigned int step_index, unsigned int *pHomoParamIndex);

/**
 * @brief 设置任务步骤的Homography参数索引
 * @param step_index：步骤号
 * @param HomoParamIndex：Homography参数索引
 * @return 0:成功，其它：失败
 * @author <Terry>
 * @note
 */
int Task_Step_Homo_Param_Index_Set(unsigned int step_index, unsigned int HomoParamIndex);

/**
 * @brief 获取任务步骤的Homography参数索引
 * @param step_index：步骤号
 * @param pScaleCalcParamIndex：比例系数索引指针
 * @return 0:成功，其它：失败
 * @author <Terry>
 * @note
 */
int Task_Step_Scale_Cali_Param_Index_Get(unsigned int step_index, unsigned int *pScaleCalcParamIndex);

/**
 * @brief 设置任务步骤的Homography参数索引
 * @param step_index：步骤号
 * @param ScaleCalcParamIndex：比例系数索引
 * @return 0:成功，其它：失败
 * @author <Terry>
 * @note
 */
int Task_Step_Scale_Cali_Param_Index_Set(unsigned int step_index, unsigned int ScaleCalcParamIndex);

/**
 * @brief 获取任务步骤的发送数据标志位
 * @param step_index：步骤号
 * @param pSendDataFlag：发送数据标志位指针
 * @return 0:成功，其它：失败
 * @author <Terry>
 * @note
 */
int Task_Step_Send_Data_Flag_Get(unsigned int step_index, unsigned int *pSendDataFlag);

/**
 * @brief 设置任务步骤的发送数据标志位
 * @param step_index：步骤号
 * @param SendDataFlag：发送数据标志位
 * @return 0:成功，其它：失败
 * @author <Terry>
 * @note
 */
int Task_Step_Send_Data_Flag_Set(unsigned int step_index, unsigned int SendDataFlag);

/**
 * @brief 获取任务步骤循环执行次数
 * @param step_index：步骤号
 * @param pExecCount：步骤循环执行次数指针
 * @return 0:成功，其它：失败
 * @author <Terry>
 * @note
 */
int Task_Step_Send_Data_Flag_Get(unsigned int step_index, unsigned int *pExecCount);

/**
 * @brief 设置任务步骤循环执行次数
 * @param step_index：步骤号
 * @param ExecCount：步骤循环执行次数
 * @return 0:成功，其它：失败
 * @author <Terry>
 * @note
 */
int Task_Step_Send_Data_Flag_Set(unsigned int step_index, unsigned int ExecCount);

/**
 * @brief 获取任务步骤关联定位使能标志位
 * @param step_index：步骤号
 * @param pCompassEnFlag：关联定位使能标志位指针
 * @return 0:成功，其它：失败
 * @author <Terry>
 * @note
 */
int Task_Step_Compass_En_Flag_Get(unsigned int step_index, unsigned int *pCompassEnFlag);

/**
 * @brief 设置任务步骤关联定位使能标志位
 * @param step_index：步骤号
 * @param CompassEnFlag：关联定位使能标志位
 * @return 0:成功，其它：失败
 * @author <Terry>
 * @note
 */
int Task_Step_Compass_En_Flag_Set(unsigned int step_index, unsigned int CompassEnFlag);

/**
 * @brief 添加任务步骤时，更新任务各步骤索引
 * @param stepIndex：要更新的步骤号
 * @param addStepIndex：添加步骤的位置索引
 * @return 0:成功，其它：失败
 * @author <AutumnX>
 * @note
 */
int TaskAddStepUpdateStepIndex(unsigned int stepIndex, unsigned int addStepIndex);

/**
 * @brief 删除任务步骤时，更新任务各步骤索引
 * @param stepIndex：要更新的步骤号
 * @param delStepIndex：删除步骤的索引
 * @return 0:成功，其它：失败
 * @author <AutumnX>
 * @note
 */
int TaskDeleteStepUpdateStepIndex(unsigned int stepIndex, unsigned int delStepIndex);

/**
 * @brief 添加任务步骤时，更新任务各步骤关联定位信息
 * @param stepIndex：要更新的步骤号
 * @param addStepIndex：添加步骤的位置索引
 * @return 0:成功，其它：失败
 * @author <AutumnX>
 * @note
 */
int TaskAddStepUpdateStepCompassInfo(unsigned int stepIndex, unsigned int addStepIndex);

/**
 * @brief 删除任务步骤时，更新任务各步骤关联定位信息
 * @param stepIndex：要更新的步骤号
 * @param delStepIndex：删除步骤的位置索引
 * @return 0:成功，其它：失败
 * @author <AutumnX>
 * @note
 */
int TaskDeleteStepUpdateStepCompassInfo(unsigned int stepIndex, unsigned int delStepIndex);

/**
 * @brief 添加任务步骤时，更新任务各步骤引用别的步骤的信息
 * @param stepIndex：要更新的步骤号
 * @param addStepIndex：添加步骤的位置索引
 * @return 0:成功，其它：失败
 * @author <AutumnX>
 * @note
 */
int TaskAddStepUpdateStepLinkInfo(unsigned int stepIndex, unsigned int addStepIndex);

/**
 * @brief 删除任务步骤时，更新任务各步骤引用别的步骤的信息
 * @param stepIndex：要更新的步骤号
 * @param delStepIndex：删除步骤的位置索引
 * @return 0:成功，其它：失败
 * @author <AutumnX>
 * @note
 */
int TaskDeleteStepUpdateStepLinkInfo(unsigned int stepIndex, unsigned int delStepIndex);

/**
 * @brief 检测checkStepIndex步是否被stepIndex步引用
 * @param stepIndex：被检查的步骤索引
 * @param checkStepIndex：是否被引用的步骤索引
 * @return 0:否，1：是
 * @author <AutumnX>
 * @note
 * 如果不是通过 STEP_LINK_INFO 来引用的步骤，需要另外实现检查的处理函数
 */
int WhetherBeUsedByStepLinkInfo(unsigned int stepIndex, unsigned int checkStepIndex);

/**
 * @brief 以int型数据获取指定步骤的指定结果
 * @param step_index: 步骤索引
 * @param result_index: 结果索引
 * @return 0: 成功，Other: 失败
 * @author <Terry>
 * @note
 */
int Task_Step_Result_Get_As_Int(unsigned int step_index, unsigned int result_index, int *pRetValue);

/**
 * @brief 以unsigned int型数据获取指定步骤的指定结果
 * @param step_index: 步骤索引
 * @param result_index: 结果索引
 * @return 0: 成功，Other: 失败
 * @author <Terry>
 * @note
 */
int Task_Step_Result_Get_As_Uint(unsigned int step_index, unsigned int result_index, unsigned int *pRetValue);

/**
 * @brief 以float型数据获取指定步骤的指定结果
 * @param step_index: 步骤索引
 * @param result_index: 结果索引
 * @return 0: 成功，Other: 失败
 * @author <Terry>
 * @note
 */
int Task_Step_Result_Get_As_Float(unsigned int step_index, unsigned int result_index, float *pRetValue);

/**
 * @brief 以double型数据获取指定步骤的指定结果
 * @param step_index: 步骤索引
 * @param result_index: 结果索引
 * @return 0: 成功，Other: 失败
 * @author <Terry>
 * @note
 */
int Task_Step_Result_Get_As_Double(unsigned int step_index, unsigned int result_index, double *pRetValue);

/**
 * @brief 增加任务成功次数
 * @param index：步骤号
 * @return
 * @author <Terry>
 * @note
 */
void Task_Step_Success_Count_Increase(unsigned int index);

/**
 * @brief 增加任务失败次数
 * @param index：步骤号
 * @return
 * @author <Terry>
 * @note
 */
void Task_Step_Fail_Count_Increase(unsigned int index);

/**
 * @brief 获取任务成功次数
 * @param index：步骤号
 * @return
 * @author <Terry>
 * @note
 */
unsigned int Task_Step_Success_Count_Get(unsigned int index);

/**
 * @brief 获取任务失败次数
 * @param index：步骤号
 * @return
 * @author <Terry>
 * @note
 */
unsigned int Task_Step_Fail_Count_Get(unsigned int index);

/**
 * @brief 设置任务步骤执行时间
 * @param index：步骤号
 * @param time_cost: 执行时间（ms）
 * @return
 * @author <Terry>
 * @note
 */
unsigned int Task_Step_Cost_Time_Set(unsigned int index, struct timespec *pRoundStart);

/**
 * @brief 获取任务步骤执行时间
 * @param index：步骤号
 * @return
 * @author <Terry>
 * @note
 */
double Task_Step_Cost_Time_Get(unsigned int index);
/**
 * @brief 设置步骤私有的CMOS参数ID
 * @param step_index：步骤号
 * @return
 * @author <Terry>
 * @note
 */
int Task_Step_Cmos_Param_Index_Set(unsigned int step_index, unsigned int cmos_param_index);
	
/**
 * @brief 获取步骤私有的CMOS参数ID
 * @param step_index：步骤号
 * @return
 * @author <Terry>
 * @note
 */
int Task_Step_Cmos_Param_Index_Get(unsigned int step_index);

/**
 * @brief 获取任务步骤OK执行时间
 * @param index：步骤号
 * @return
 * @author <Terry>
 * @note
 */
double Task_Step_Total_Ok_Cost_Time_Get(unsigned int index);

/**
 * @brief 获取任务步骤NG执行时间
 * @param index：步骤号
 * @return
 * @author <Terry>
 * @note
 */
double Task_Step_Total_Ng_Cost_Time_Get(unsigned int index);

/**
 * @brief 获取任务步骤OUTPUT_COMMON_PARAM指针
 * @param index：步骤号
 * @return
 * @author <Terry>
 * @note
 */
OUTPUT_COMMON_PARAM * Task_Step_Output_Common_Para_Get(unsigned int index);
/**
 * @brief 添加任务步骤时，更新任务各步骤索引
 * @param stepIndex：要更新的步骤号
 * @param addStepIndex：添加步骤的位置索引
 * @return 0:成功，其它：失败
 * @author <AutumnX>
 * @note
 */
int TaskAddStepUpdateStepIndex(unsigned int stepIndex, unsigned int addStepIndex);

/**
 * @brief 删除任务步骤时，更新任务各步骤索引
 * @param stepIndex：要更新的步骤号
 * @param delStepIndex：删除步骤的索引
 * @return 0:成功，其它：失败
 * @author <AutumnX>
 * @note
 */
int TaskDeleteStepUpdateStepIndex(unsigned int stepIndex, unsigned int delStepIndex);

/**
 * @brief 添加任务步骤时，更新任务各步骤引用别的步骤的信息
 * @param stepIndex：要更新的步骤号
 * @param addStepIndex：添加步骤的位置索引
 * @return 0:成功，其它：失败
 * @author <AutumnX>
 * @note
 */
int TaskAddStepUpdateStepLinkInfo(unsigned int stepIndex, unsigned int addStepIndex);

/**
 * @brief 删除任务步骤时，更新任务各步骤引用别的步骤的信息
 * @param stepIndex：要更新的步骤号
 * @param delStepIndex：删除步骤的位置索引
 * @return 0:成功，其它：失败
 * @author <AutumnX>
 * @note
 */
int TaskDeleteStepUpdateStepLinkInfo(unsigned int stepIndex, unsigned int delStepIndex);

/**
 * @brief 获取指定步骤的错误码
 * @param index：步骤号
 * @return
 * @author <Terry>
 * @note
 */
unsigned int GetStepErrorTypeIdByIndex(unsigned int index);

/**
 * @brief 设置指定步骤的错误码
 * @param index：步骤号
 * @param error_type_id: 错误码
 * @return
 * @author <Terry>
 * @note
 */
void Task_Error_TypeID_Set_ByIndex(unsigned int index, unsigned int error_type_id);

/**
 * @brief 获取指定步骤类型ID
 * @param index：步骤号
 * @return
 * @author <Terry>
 * @note
 */
unsigned int Task_Step_TypeID_Get_By_Index(unsigned int index);

/**
 * @brief 任务步骤号有效性检查
 * @param step_index：步骤号
 * @return
 * @author <Terry>
 * @note
 */
int Task_Step_Index_Valid_Check(unsigned int step_index);

/**
 * @brief 任务步骤号有效性检查
 * @param pParamStruct 步骤分区入口地址变量
 * @param pParam 步骤头指针
 * @return
 * @author <Terry>
 * @note
 */
void Task_Struct_Common_Init(TASK_STRUCT_COMMON *pParamStruct, void *pParam);

/**
 * @brief 指定任务的取样结果数据是否有效
 * @param step_index：步骤号
 * @return 0:成功，other：失败
 * @author <Terry>
 * @note
 */
int Task_Step_Model_Result_Valid_Flag_Check(unsigned int step_index);

/**
 * @brief 取样结果数据置为有效
 * @param step_index：步骤号
 * @return
 * @author <Terry>
 * @note
 */
void Task_Step_Model_Result_Valid_Flag_Set(unsigned int step_index);

/**
 * @brief 取样结果数据置为无效
 * @param step_index：步骤号
 * @return
 * @author <Terry>
 * @note
 */
void Task_Step_Model_Result_Valid_Flag_Clear(unsigned int step_index);
/**
 * @brief 指定任务的关联步骤信息检查
 * @param pStepHeader:步骤头指针
 * @param step_num:关联步骤数
 * @param model_flag:取样状态标志位
 * @return 0:成功，other：失败
 * @author <Terry>
 * @note
 */
int Task_Step_Link_Step_Check(TASK_STEP_HEADER *pStepHeader, unsigned int step_num, unsigned int model_flag);

/**
 * @brief 设置步骤执行OK时IO输出bitmask
 * @param step_index:步骤索引
 * @param ok_io_index:OK时IO输出mask
 * @return 0:成功，other：失败
 * @author <Terry>
 * @note
 */
int Task_Step_OK_IO_Output_Index_Set(unsigned int step_index, unsigned int ok_io_index);

/**
 * @brief 设置步骤执行NG时IO输出bitmask
 * @param step_index:步骤索引
 * @param ng_io_index:NG时IO输出mask
 * @return 0:成功，other：失败
 * @author <Terry>
 * @note
 */
int Task_Step_NG_IO_Output_Index_Set(unsigned int step_index, unsigned int ng_io_index);

/**
 * @brief 获取步骤执行OK时IO输出bitmask
 * @param step_index:步骤索引
 * @param ng_io_index:NG时IO输出mask
 * @return TASK_STEP_INDEX_INVALID：失败
 * @author <Terry>
 * @note
 */
int Task_Step_OK_IO_Output_Index_Get(unsigned int step_index);

/**
 * @brief 获取步骤执行NG时IO输出bitmask
 * @param step_index:步骤索引
 * @param ng_io_index:NG时IO输出mask
 * @return TASK_STEP_INDEX_INVALID：失败
 * @author <Terry>
 * @note
 */
int Task_Step_NG_IO_Output_Index_Get(unsigned int step_index);

/**
 * @brief 步骤执行结束按照配置输出IO
 * @param step_index:步骤索引
 * @param ng_io_index:NG时IO输出mask
 * @return TASK_STEP_INDEX_INVALID：失败
 * @author <Terry>
 * @note
 */
void Task_Step_IO_Output(unsigned int step_index, unsigned int ok_ng_flag);

/**
 * @brief Task_IO_OutPut_Mode_Get
 * @param mode 0:普通模式，1：高级模式
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 获取io输出模式
 */
int Task_IO_OutPut_Mode_Get(unsigned int *mode);

/**
 * @brief Task_IO_OutPut_Mode_Set
 * @param mode 0:普通模式，1：高级模式
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 设置io输出模式
 */
int Task_IO_OutPut_Mode_Set(unsigned int mode);


/**
 * @brief Task_Step_Trigger_Type_Set
 * @param step_index
 * @param trig_type
 * @return 0:成功，其它：失败
 * @author pml
 * @date 2017/6/20
 * @note 设置步骤的触发类型
 */
int Task_Step_Trigger_Type_Set(unsigned int step_index, unsigned int trig_type);

/**
 * @brief Task_Step_Trigger_Type_Get
 * @param step_index
 * @param pTrigType
 * @return 0:成功，其它：失败
 * @author pml
 * @date 2017/6/20
 * @note 获取步骤触发类型
 */
int Task_Step_Trigger_Type_Get(unsigned int step_index, unsigned int *pTrigType);


/**
 * @brief Task_Step_Trigger_Cmd_Set
 * @param step_index
 * @param pCmd
 * @return 0:成功，其他：失败
 * @author pml
 * @date 2017/6/20
 * @note 设置命令触发参数
 */
int Task_Step_Trigger_Cmd_Set(unsigned int step_index, char *pCmd);

/**
 * @brief Task_Step_Trigger_Cmd_Get
 * @param step_index
 * @param pCmd
 * @return 0:成功，其它：失败
 * @author pml
 * @date 2017/6/20
 * @note 获取命令触发的参数
 */
int Task_Step_Trigger_Cmd_Get(unsigned int step_index, char *pCmd);

/**
 * @brief Task_Step_Trigger_Cmd_Get
 * @param step_index
 * @return 命令触发的指针
 * @author pml
 * @date 2017/6/20
 * @note 获取命令触发的参数
 */
void *Task_Step_Trigger_Cmd_Pointer_Get(unsigned int step_index);

/**
 * @brief Task_Step_Trigger_IO_Set
 * @param step_index
 * @param input_pin_index
 * @param input_type
 * @return 0:成功，其他：失败
 * @author pml
 * @date 2017/6/20
 * @note 设置io触发参数
 */
int Task_Step_Trigger_IO_Set(unsigned int step_index, unsigned short input_pin_index, unsigned short input_type);

/**
 * @brief Task_Step_Trigger_IO_Get
 * @param step_index
 * @param pInputPinIndex
 * @param pInputType
 * @return 0:成功，其它：失败
 * @author pml
 * @date 2017/6/20
 * @note 获取IO触发参数
 */
int Task_Step_Trigger_IO_Get(unsigned int step_index, unsigned short *pInputPinIndex, unsigned short *pInputType);


/**
 * @brief 添加任务步骤时，更新任务各步骤引用别的步骤的信息
 * @param stepIndex: 要更新的步骤号
 * @param pCost: 等待触发信号时间变量指针
 * @return 0:成功，其它：失败
 * @author <AutumnX>
 * @note
 */
int Task_Step_Trigger_Check(unsigned int step_index, double *pCost);

/**
 * @brief 同时检查两个IO的触发状态是否满足
 * @param pin_mask: 0:无触发，1：输入IO1触发，2：输入IO2触发，3：输入IO1\2触发
 * @param trigger_mode1：IO1的触发模式
 * @param trigger_mode2：IO2的触发模式
 * @return 0：无触发退出，1：IO1触发退出，2：IO2触发退出，
 * @author <Terry>
 * @note
 */
int Dul_IO_Condition_Check(unsigned int pin_mask, unsigned int trigger_mode1, unsigned int trigger_mode2);

/**
 * @brief 删除刻度校准参数时，更新任务各步骤刻度校准引用信息
 * @param delParamIndex：删除的参数索引
 * @return 0:成功，其它：失败
 * @author <AutumnX>
 * @note
 */
int DeleteScaleRatioParamUpdateStepLinkInfo(unsigned int delParamIndex);

/**
 * @brief 删除homo参数时，更新任务各步骤homo引用信息
 * @param delParamIndex：删除的参数索引
 * @return 0:成功，其它：失败
 * @author <AutumnX>
 * @note
 */
int DeleteHomoParamUpdateStepLinkInfo(unsigned int delParamIndex);

/**
 * @brief 获取模板标志
 * @param step_index:步骤索引
 * @param p_model_flag:模板标志接收指针
 * @return 0:成功，other：失败
 * @author <AutumnX>
 * @note
 */
int Task_Step_Model_Flag_Get(unsigned int step_index, unsigned int *p_model_flag);

/**
 * @brief 设置模板标志
 * @param step_index:步骤索引
 * @param model_flag:模板标志
 * @return 0:成功，other：失败
 * @author <AutumnX>
 * @note
 */
int Task_Step_Model_Flag_Set(unsigned int step_index, unsigned int model_flag);

/**
 * @brief 获取模板大小
 * @param step_index:步骤索引
 * @param p_model_size:模板大小接收指针
 * @return 0:成功，other：失败
 * @author <AutumnX>
 * @note
 */
int Task_Step_Model_Size_Get(unsigned int step_index, unsigned int *p_model_size);

/**
 * @brief 设置模板大小
 * @param step_index:步骤索引
 * @param model_size:模板大小
 * @return 0:成功，other：失败
 * @author <AutumnX>
 * @note
 */
int Task_Step_Model_Size_Set(unsigned int step_index, unsigned int model_size);

/**
 * @brief 获取模板地址
 * @param step_index:步骤索引
 * @param p_model_addr:模板地址接收指针
 * @return 0:成功，other：失败
 * @author <AutumnX>
 * @note
 */
int Task_Step_Model_Addr_Get(unsigned int step_index, unsigned int *p_model_addr);

/**
 * @brief 设置模板地址
 * @param step_index:步骤索引
 * @param model_addr:模板地址
 * @return 0:成功，other：失败
 * @author <AutumnX>
 * @note
 */
int Task_Step_Model_Addr_Set(unsigned int step_index, unsigned int model_addr);

/**
 * @brief Task_Step_Alias_Get
 * @param step_index:步骤索引
 * @param buf_len:接收缓存区的大小，要 >= STEP_ALIAS_SIZE
 * @param buf:接收缓存区指针
 * @return 0:成功，other:失败
 * @note 获取步骤别名
 */

int Task_Step_Alias_Get(unsigned int step_index, unsigned int buf_len, char buf[]);

/**
 * @brief Task_Step_Alias_Set
 * @param step_index:步骤索引
 * @param step_alias:步骤别名
 * @return 0:成功，other:失败
 * @note 设置步骤别名
 */
int Task_Step_Alias_Set(unsigned int step_index, const char* step_alias);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __TASKMANAGE_H__ */
