#ifndef INTERCOMMODBUSGLOBAL_H
#define INTERCOMMODBUSGLOBAL_H
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include "TcpGlobal.h"

#define MODBUS_SLAVE_TYPE 0 ///< 从站
#define MODBUS_HOST_TYPE 1 ///< 主站

/** @brief modbus的数据流最大个数 */
#define MB_DATA_LIST_NUM_MAX          100

#define MODBUS_MAX_READ_BITS              2000 ///< 单次读线圈的最大个数
#define MODBUS_MAX_WRITE_BITS             1968 ///< 单次写线圈的最大个数
#define MODBUS_DISCRETE_RW_MAX 2000 ///< 单次读写离散量的最大个数
#define HOLD_REG_RW_MAX 125 ///<单次读写保持寄存器的最大个数
#define INPUT_REG_RW_MAX 125 ///<单次读写输入寄存器的最大个数
#define MODBUS_MAX_READ_REGISTERS          125 ///<单次读输入寄存器的最大个数
#define MODBUS_MAX_WRITE_REGISTERS         123 ///<单次写输入寄存器的最大个数
#define MODBUS_MAX_RW_WRITE_REGISTERS      121 ///<单次读写输入寄存器的最大个数


/** @brief 线圈功能定义
 ** @brief 线圈编号界面上从1开始计数 */
/** @brief 前256个线圈是用来表示每个步骤的运行成功失败结果，OK为0， NG为1 */
#define MODBUS_COIL_ZERO_TRIGGER		0		///<  线圈值为0触发，线圈值为1停止
#define MODBUS_COIL_ONE_TRIGGER			1		///<  线圈值为1触发，线圈值为0停止
#define MODBUS_COIL_NO_OPT_AFTER_RD		0		///<  读线圈后无操作
#define MODBUS_COIL_CLEAR_AFTER_RD		1		///<  读线圈后清零
#define MODBUS_COIL_INVERT_AFTER_RD		2		///<  读线圈后取反


#define MODBUS_EXEC_POST_STEP    0     ///< 步骤之后执行
#define MODBUS_EXEC_PRE_STEP     1     ///< 步骤之前执行

#define HOST_RD_COILS       0 ///< 主站的数据流类型 读线圈
#define HOST_WR_COILS       1 ///< 主站的数据流类型 写线圈
#define HOST_RD_DISCRETE    2 ///< 主站的数据流类型 读离散量
#define HOST_RD_HOLD_REG    3 ///< 主站的数据流类型 读保持寄存器
#define HOST_WR_HOLD_REG    4 ///< 主站的数据流类型 写保持寄存器
#define HOST_RD_INPUT_REG   5 ///< 主站的数据流类型 读输入寄存器

#define SLAVE_RD_COILS		0 ///< 从站的数据流类型 读线圈
#define SLAVE_WR_COILS		1 ///< 从站的数据流类型 写线圈
#define SLAVE_WR_DISCRETE	2 ///< 从站的数据流类型 写离散量
#define SLAVE_RD_HOLD_REG	3 ///< 从站的数据流类型 读保持寄存器
#define SLAVE_WR_HOLD_REG	4 ///< 从站的数据流类型 写保持寄存器
#define SLAVE_WR_INPUT_REG	5 ///< 从站的数据流类型 写输入寄存器

#ifndef MODBUS_REG_TYPE_HOLD
#define MODBUS_REG_TYPE_HOLD 0 ///<保持寄存器
#endif
#ifndef MODBUS_REG_TYPE_INPUT
#define MODBUS_REG_TYPE_INPUT 1 ///<输入寄存器
#endif

/**
 * @brief modbus_init
 * @return 0：失败，1：成功
 * @author pml
 * @date 2017/5/12
 * @note 多机互联modbus协议初始化
 */

int intercom_modbus_init(void);

/**
 * @brief intercom_modbus_status_get
 * @return 0：未启动，1：启动
 * @author pml
 * @date 2017/5/12
 * @note 多机互联modbus协议启动状态
 */

int intercom_modbus_status_get(void);


/**
 * @brief intercom_tcp_config_set
 * @param tcp
 * @author pml
 * @date 2017/5/12
 * @note 设置多机互联tcp配置
 */
void intercom_tcp_config_set(TCP_CONFIG *tcp);

/**
 * @brief intercom_tcp_config_get
 * @param tcp
 * @author pml
 * @date 2017/5/12
 * @note 获取多机互联tcp配置
 */
void intercom_tcp_config_get(TCP_CONFIG *tcp);

/**
 * @brief intercom_modbus_slave_or_host_set
 * @param slave_or_host
 * @author pml
 * @date 2017/5/12
 * @note 设置多机互联modbus主从站
 */
void intercom_modbus_slave_or_host_set(unsigned int slave_or_host);

/**
 * @brief ModbusSlaveOrHostGet
 * @return
 * @author pml
 * @date 2017/5/12
 * @note 获取多机互联modbus主从站
 */
unsigned int intercom_modbus_slave_or_host_get(void);

/**
 * @brief intercom_modbus_device_address_set
 * @param device_addr
 * @author pml
 * @date 2017/5/12
 * @note 设置多机互联modbus设备地址
 */
void intercom_modbus_device_address_set(unsigned int device_addr);

/**
 * @brief modbus_device_dddress_get
 * @return
 * @author pml
 * @date 2017/5/12
 * @note 获取多机互联modbus设备地址
 */
unsigned int intercom_modbus_device_address_get(void);

/**
 * @brief modbus_data_list_cnt_set
 * @param list_cnt
 * @author pml
 * @date 2017/5/12
 * @note 设置多机互联modbus数据流的个数
 */
void intercom_modbus_data_list_cnt_set(unsigned int list_cnt);

/**
 * @brief intercom_modbus_data_list_cnt_get
 * @return 数据流的个数
 * @author pml
 * @date 2017/5/12
 * @note 获取多机互联modbus数据流个数
 */
unsigned int intercom_modbus_data_list_cnt_get(void);


/**
 * @brief intercom_modbus_list_data_type_set
 * @param listIndex
 * @param data_type
 * @return
 * @author pml
 * @date 2017/5/12
 * @note 设置多机互联Modbus数据流的数据类型
 */
void intercom_modbus_list_data_type_set(unsigned int listIndex, unsigned int data_type);

/**
 * @brief intercom_modbus_list_data_type_get
 * @param listIndex
 * @return
 * @author pml
 * @date 2017/5/12
 * @note 获取多机互联Modbus数据流的数据类型
 */
unsigned int intercom_modbus_list_data_type_get(unsigned int listIndex);


/**
 * @brief intercom_modbus_list_exec_step_set
 * @param listIndex
 * @param step
 * @return
 * @author pml
 * @date 2017/5/12
 * @note 设置多机互联Modbus数据流发送的关联步骤
 */
int intercom_modbus_list_exec_step_set(unsigned int listIndex, unsigned int step);

/**
 * @brief intercom_modbus_list_exec_step_get
 * @param listIndex
 * @return
 * @author pml
 * @date 2017/5/12
 * @note 获取多机互联Modbus数据流发送的关联步骤
 */
unsigned int intercom_modbus_list_exec_step_get(unsigned int listIndex);

/**
 * @brief modbus_list_pre_post_exec_step_set
 * @param listIndex
 * @param flag
 * @return
 * @author pml
 * @date 2017/5/12
 * @note 设置多机互联Modbus数据流在执行关联步骤之前发送的标志
 */
int intercom_modbus_list_pre_post_exec_step_set(unsigned int listIndex, unsigned int flag);

/**
 * @brief intercom_modbus_list_pre_post_exec_step_get
 * @param listIndex
 * @return
 * @author pml
 * @date 2017/5/12
 * @note 获取多机互联Modbus数据流在执行关联步骤之前发送的标志
 */
unsigned int intercom_modbus_list_pre_post_exec_step_get(unsigned int listIndex);

/**
 * @brief intercom_modbus_list_op_over_step_set
 * @param listIndex
 * @param flag
 * @return
 * @author pml
 * @date 2017/5/12
 * @note 设置多机互联Modbus数据流发送完成的标志（1：未发送，0：发送完毕）
 */
int intercom_modbus_list_op_over_step_set(unsigned int listIndex, unsigned int flag);

/**
 * @brief intercom_modbus_list_op_over_step_get
 * @param listIndex
 * @return 1：未发送，0：发送完毕
 * @author pml
 * @date 2017/5/12
 * @note 获取多机互联Modbus数据流发送完成的标志
 */
unsigned int intercom_modbus_list_op_over_step_get(unsigned int listIndex);

/**
 * @brief intercom_modbus_data_list_set
 * @param slave_or_host
 * @param list_index
 * @param p_data_ist
 * @param data_type
 * @return
 * @author pml
 * @date 2017/5/12
 * @note 设置多机互联modbus数据流列表
 */
int intercom_modbus_data_list_set(unsigned int slave_or_host, unsigned int list_index, void *p_data_ist, unsigned int data_type);

/**
 * @brief intercom_modbus_data_list_get
 * @param list_index
 * @param p_data_ist
 * @return
 * @author pml
 * @date 2017/5/12
 * @note 获取多机互联modbus数据流列表
 */
int intercom_modbus_data_list_get(unsigned int list_index, void *p_data_ist);

/**
 * @brief intercom_modbus_hold_input_reg_data_get
 * @param reg_type
 * @param addr
 * @return
 * @author pml
 * @date 2017/5/12
 * @note 获取多机互联modbus寄存器数据起始地址
 */
unsigned short *intercom_modbus_hold_input_reg_data_get(unsigned int reg_type, unsigned int addr);

/**
 * @brief intercom_modbus_del_data_list
 * @param list_index
 * @return
 * @author pml
 * @date 2017/5/12
 * @note 多机互联modbus删除数据流
 */
int intercom_modbus_del_data_list(unsigned int list_index);


/**
 * @brief intercom_modbus_clean_data_list
 * @return 0：失败，1：成功
 * @author pml
 * @date 2017/5/12
 * @note 清空多机互联Modbus数据列表
 */
int intercom_modbus_clean_data_list(void);

/**
 * @brief modbus_data_list_move_up
 * @param list_index
 * @return  0:失败，1：成功
 * @author pml
 * @date 2017/5/12
 * @note 多机互联modbus数据流上移
 */
int intercom_modbus_data_list_move_up(unsigned int list_index);

/**
 * @brief modbus_data_list_move_down
 * @param list_index
 * @return 0:失败，1：成功
 * @author pml
 * @date 2017/5/12
 * @note 多机互联modbus数据流下移
 */
int intercom_modbus_data_list_move_down(unsigned int list_index);



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif // INTERCOMMODBUSGLOBAL_H
