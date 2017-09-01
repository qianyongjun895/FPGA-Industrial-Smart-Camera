#ifndef PROTOCOLMANAGEGLOBAL_H
#define PROTOCOLMANAGEGLOBAL_H

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#define SEND_DATA_LEN_MAX 1024
#define RECV_DATA_LEN_MAX 1024

#define DATA_SEND_OVER	0 ///< 发送完毕
#define DATA_SENDING	1 ///< 未发送
#define DATA_EXEC_POST_STEP    0     ///< 步骤之后执行
#define DATA_EXEC_PRE_STEP     1     ///< 步骤之前执行

#define PROTOCOL_INACTIVE 0 ///< 协议未启动
#define PROTOCOL_ACTIVE 1 ///< 协议已启动

/** @brief 通信方式 */
typedef enum{
    COMM_UART_TYPE = 0, ///< 0 串口通信
    COMM_TCP_TYPE, ///< 1 tcp通信
    COMM_UDP_TYPE, ///< 2 udp通信
    COMM_WAY_MAX
}COMM_TYPE;

/** @brief 协议类型 */ 
typedef enum{
    USER_DEFINED_PROTOCOL = 0, ///< 0 自定义协议
    MODBUS_PROTOCOL, ///< 1 Modbus协议
    MITSUBSHI_FX_PROTOCOL, ///< 2 三菱FX
    HANS_ROBOT_PROTOCOL,
    PROTOCOL_MAX = 5 ///< 32
}PROTOCOL_TYPE;

/** @brief 协议选择 */
typedef struct{
    int comm_type; ///< 通信方式
    int protocol_type; ///< 协议类型
    int protocol_status; ///< 协议状态, 0:未启动，1：已启动
}PROTOCOL_SELECT;


/**
 * @brief ProtocolOpen
 * @param comm_way
 * @param protocol_type
 * @return  0:失败 1:成功
 * @author pml
 * @date 2017/5/12
 * @note 打开协议
 */
int protocol_open(int comm_way, int protocol_type);

/**
 * @brief ProtocolClose
 * @param protocol_type
 * @return  0:失败 1:成功
 * @author pml
 * @date 2017/5/12
 * @note 关闭协议
 */
int protocol_close(int protocol_type);

/**
 * @brief protocol_select_get
 * @param p
 * @return  0:失败 1:成功
 * @author pml
 * @date 2017/5/12
 * @note 获取协议的选择、通信方式、协议状态
 */
int protocol_select_get(PROTOCOL_SELECT *p);


/**
 * @brief protocol_test_recv
 * @param pStr
 * @return
 * @author pml
 * @date 2017/5/12
 * @note 测试接收
 */
int protocol_test_recv(char *pStr);

/**
 * @brief protocol_test_send
 * @param pStr
 * @return
 * @author pml
 * @date 2017/5/12
 * @note 测试发送
 */
int protocol_test_send(char *pStr);

 /**
  * @brief local_ip_get
  * @param pIP
  * @return 0:失败，1：成功
  * @author pml
  * @date 2017/5/12
  * @note 获取本地ip
  */
 int local_ip_get(char *pIP);


/**
 * @brief Communication_Round_Over_Check
 * @author pml
 * @date 2017/5/12
 * @note 数据发送完毕检查
 */
void Communication_Round_Over_Check(void);

/**
 * @brief Communication_Work_Before_Step_Run
 * @param crt_step
 * @author pml
 * @date 2017/5/12
 * @note 该步执行前通讯协议该做的工作
 */
void Communication_Work_Before_Step_Run(unsigned int crt_step);


/**
 * @brief Communication_Work_After_Step_Run
 * @param crt_step
 * @author pml
 * @date 2017/5/12
 * @note 该步执行后通讯协议该做的工作
 */
void Communication_Work_After_Step_Run(unsigned int crt_step);


/**
 * @brief Communication_Work_After_OneRound
 * @author pml
 * @date 2017/5/12
 * @note 完成一轮后通讯协议该做的工作
 */
void Communication_Work_After_OneRound(void);

/**
 * @brief task_step_add_update_comm_data_list
 * @param add_step
 * @return 0:失败 1:成功
 * @author pml
 * @date 2017/5/12
 * @note 添加任务，更新通信数据列表
 */
int task_step_add_update_comm_data_list(unsigned int add_step);

/**
 * @brief task_step_del_update_comm_data_list
 * @param del_step
 * @return 0:失败 1:成功
 * @author pml
 * @date 2017/5/12
 * @note 删除任务，更新通信数据列表
 */
int task_step_del_update_comm_data_list(unsigned int del_step);

/**
 * @brief task_clean_update_comm_data_list
 * @return 0:失败 1:成功
 * @author pml
 * @date 2017/5/12
 * @note 清空任务，更新通信数据列表
 */
int task_clean_update_comm_data_list(void);

/**
 * @brief comm_data_list_save_to_file
 * @return 0:失败 1:成功
 * @author pml
 * @date 2017/5/12
 * @note 数据列表保存到文件
 */
int comm_data_list_save_to_file(void);

/**
 * @brief comm_data_list_load_from_file
 * @return 0:失败 1:成功
 * @author pml
 * @date 2017/5/12
 * @note 从文件里加载数据列表
 */
int comm_data_list_load_from_file(void);


int protocol_non_block_open(int comm_way, int protocol_type);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif // PROTOCOLMANAGEGLOBAL_H
