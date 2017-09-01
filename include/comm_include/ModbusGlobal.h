#ifndef MODBUSGLOBAL_H
#define MODBUSGLOBAL_H
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

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



/** @brief Modbus 引用步骤数据 */
typedef struct{
    unsigned short reg_address; ///< 寄存器地址
    unsigned short step_index; ///< 步骤索引
    unsigned short result_index; ///< 结果索引
}MB_RESULT_REFERENCE;


/** @brief 主站读从站线圈 */
typedef struct {
    unsigned int address; 		///< 线圈开始号，有效范围1-65536 
    unsigned int length; 		///< 读取的长度，有效范围1-2000，CPU0根据length是否大于1选用不同的指令 
    unsigned char expecte_value[MODBUS_MAX_READ_BITS];	 ///< 本步期待值，output中的coil_value值等于expecte_value时本步结束
} MBH_RD_COILS;

/** @brief 主站写从站线圈 */
typedef struct {
    unsigned int address;			///< 线圈开始号，有效范围1-65536 
    unsigned int length;			///< 读取的长度，有效范围1-1968
    unsigned char coil_value[MODBUS_MAX_WRITE_BITS]; ///< 线圈写的值 ,CPU0将数据写到对端
} MBH_WR_COILS;

/** @brief 主站读从站离散量 */
typedef struct {
    unsigned int address;			///< 离散量开始号，有效范围1-65536 
    unsigned int length;			///< 读取的长度，有效范围1-2000 
    unsigned char expecte_value[MODBUS_DISCRETE_RW_MAX]; ///< 本步期待值，output中的discrete_value值等于expecte_value时本步结束
} MBH_RD_DISCRETE;

/** @brief 主站读从站的保持寄存器 */
typedef struct {
    unsigned int address;			///< 保持寄存器开始号，有效范围1-65536 
    unsigned int length;			///< 读取长度 ，有效范围1-125
    unsigned int data_type;			///< 数据解析类型 
} MBH_RD_HOLD_REG;
/** @brief 主站写从站的保持寄存器 */
typedef struct {
    unsigned int address;			///< 保持寄存器开始号，有效范围1-65536 
    unsigned int length;			///< 写入长度 ，有效范围1-123
    unsigned int data_type; ///< 数据类型 
    unsigned int link_cnt;          ///< 数据引用个数 
    MB_RESULT_REFERENCE link_info[MODBUS_MAX_WRITE_REGISTERS];  ///< 结果引用结构体 
    unsigned char data_source[MODBUS_MAX_WRITE_REGISTERS];	///< 数据来源，0:手动输入 1:结果引用
    unsigned short hold_reg_value[MODBUS_MAX_WRITE_REGISTERS];	///< 保持寄存器写入，最多一次123个，占用246个字节

} MBH_WR_HOLD_REG;

/** @brief主站读从站的输入寄存器 */
typedef struct {
    unsigned int address;			///< 保持寄存器开始号，有效范围1-65536 
    unsigned int length;			///< 读取长度 ，有效范围1-125
    unsigned int data_type;			///< 数据解析类型 
} MBH_RD_INPUT_REG;

/** @brief从站读本地线圈 */
typedef struct {
    unsigned int address;			///< 线圈开始号，有效范围1-65536 
    unsigned int action_after_rd;	///< 读取后的动作 
    unsigned int trigger_value;		///< 0:读到指定线圈为0时本步完成，1：读到指定线圈为1时本步完成
} MBS_RD_SINGLE_COIL;

/** @brief从站写本地线圈 */
typedef struct {
    unsigned int address;			///< 线圈开始号，有效范围1-65536 
    unsigned int length;			///< 读取长度 ，有效范围1-2000
    unsigned char coil_value[MODBUS_MAX_READ_BITS];	///< 线圈写入，最多一次2000个，占用2000个字节 
} MBS_WR_COIL;

/** @brief从站写本地离散量 */
typedef struct {
    unsigned int address;			///< 离散量开始号，有效范围1-65536 
    unsigned int length;			///< 读取长度 ，有效范围1-2000
    unsigned char discrete_value[MODBUS_DISCRETE_RW_MAX];	///< 离散量写入，最多一次2000个，占用250个字节 
} MBS_WR_DISCRETE;

/** @brief从站读本地保持寄存器 */
typedef struct {
    unsigned int address;			///< 保持寄存器开始号，有效范围1-65536 
    unsigned int length;			///< 读取长度 ，有效范围1-125
    unsigned int data_type;			///< 数据解析类型 
    unsigned short hold_reg_value[HOLD_REG_RW_MAX];	///< 保持寄存器读取，最多一次125个，占用250个字节 
} MBS_RD_HOLD_REG;

/** @brief从站写本地本地保持寄存器 */
typedef struct {
    unsigned int address;			///< 保持寄存器开始号，有效范围1-65536 
    unsigned int length;			///< 写入长度 ，有效范围1-125
    unsigned int data_type;         ///< 数据类型 
    unsigned int link_cnt;          ///< 数据引用个数 
    MB_RESULT_REFERENCE link_info[HOLD_REG_RW_MAX];  ///< 结果引用结构体 
    unsigned char data_source[HOLD_REG_RW_MAX];	///< 数据来源，0:手动输入 1:结果引用 
    unsigned short hold_reg_value[HOLD_REG_RW_MAX];	///< 保持寄存器写入，最多一次125个，占用250个字节 
} MBS_WR_HOLD_REG;

/** @brief从站写本地输入寄存器 */
typedef struct {
    unsigned int address;			///< 输入寄存器开始号，有效范围1-65536 
    unsigned int length;			///< 写入长度 ，有效范围1-125
    unsigned int data_type;   ///< 数据类型 
    unsigned int link_cnt;          ///< 数据引用个数 
    MB_RESULT_REFERENCE link_info[HOLD_REG_RW_MAX];  ///< 结果引用结构体 
    unsigned char data_source[INPUT_REG_RW_MAX];	///< 数据来源，0:手动输入 1:结果引用 
    unsigned short input_reg_value[INPUT_REG_RW_MAX];	///< 输入寄存器写入，最多一次125个，占用250个字节 

} MBS_WR_INPUT_REG;

/**
 * @brief modbus_init
 * @return 0：失败，1：成功
 * @author pml
 * @date 2017/5/12
 * @note modbus协议初始化
 */
int modbus_init(void);

/**
 * @brief modbus_data_addr_map
 * @return 0：失败，1：成功
 * @author pml
 * @date 2017/5/12
 * @note modbus协议映射地址初始化
 */
int modbus_data_addr_map(void);


/**
 * @brief modbus_slave_or_host_set
 * @param slave_or_host
 * @author pml
 * @date 2017/5/12
 * @note 设置modbus主从站
 */
void modbus_slave_or_host_set(unsigned int slave_or_host);

/**
 * @brief ModbusSlaveOrHostGet
 * @return
 * @author pml
 * @date 2017/5/12
 * @note 获取modbus主从站
 */
unsigned int modbus_slave_or_host_get(void);

/**
 * @brief modbus_device_dddress_set
 * @param device_addr
 * @author pml
 * @date 2017/5/12
 * @note 设置modbus设备地址
 */
void modbus_device_dddress_set(unsigned int device_addr);

/**
 * @brief modbus_device_dddress_get
 * @return
 * @author pml
 * @date 2017/5/12
 * @note 获取modbus设备地址
 */
unsigned int modbus_device_dddress_get(void);
/**
 * @brief modbus_data_list_cnt_set
 * @param list_cnt
 * @author pml
 * @date 2017/5/12
 * @note 设置modbus数据流个数
 */
void modbus_data_list_cnt_set(unsigned int list_cnt);

/**
 * @brief modbus_data_list_cnt_get
 * @return 数据流的个数
 * @author pml
 * @date 2017/5/12
 * @note 获取modbus数据个数
 */
unsigned int modbus_data_list_cnt_get(void);

/**
 * @brief modbus_list_data_type_set
 * @param listIndex
 * @param data_type
 * @return
 * @author pml
 * @date 2017/5/12
 * @note 设置Modbus数据流数据类型
 */
void modbus_list_data_type_set(unsigned int listIndex, unsigned int data_type);

/**
 * @brief modbus_list_data_type_get
 * @param listIndex
 * @return
 * @author pml
 * @date 2017/5/12
 * @note 获取Modbus数据流数据类型
 */
unsigned int modbus_list_data_type_get(unsigned int listIndex);


/**
 * @brief modbus_list_exec_step_set
 * @param listIndex
 * @param step
 * @return
 * @author pml
 * @date 2017/5/12
 * @note 设置Modbus数据流发送步骤,即在执行该步骤时发送
 */
int modbus_list_exec_step_set(unsigned int listIndex, unsigned int step);

/**
 * @brief modbus_list_exec_step_get
 * @param listIndex
 * @return
 * @author pml
 * @date 2017/5/12
 * @note 获取Modbus数据流发送步骤
 */
unsigned int modbus_list_exec_step_get(unsigned int listIndex);

/**
 * @brief modbus_list_pre_post_exec_step_set
 * @param listIndex
 * @param flag
 * @return
 * @author pml
 * @date 2017/5/12
 * @note 设置Modbus数据流在发送步骤执行之前（1）或之后（0）发送的标志
 */
int modbus_list_pre_post_exec_step_set(unsigned int listIndex, unsigned int flag);

/**
 * @brief modbus_list_pre_post_exec_step_get
 * @param listIndex
 * @return
 * @author pml
 * @date 2017/5/12
 * @note 获取Modbus数据流在发送步骤执行之前（1）或之后（0）发送的标志
 */
unsigned int modbus_list_pre_post_exec_step_get(unsigned int listIndex);

/**
 * @brief modbus_list_op_over_step_set
 * @param listIndex
 * @param flag
 * @return
 * @author pml
 * @date 2017/5/12
 * @note 设置Modbus数据流发送完成标志（1：未发送，0：发送完毕）
 */
int modbus_list_op_over_step_set(unsigned int listIndex, unsigned int flag);

/**
 * @brief modbus_list_op_over_step_get
 * @param listIndex
 * @return 1：未发送，0：发送完毕
 * @author pml
 * @date 2017/5/12
 * @note 获取Modbus数据流发送完成标志
 */
unsigned int modbus_list_op_over_step_get(unsigned int listIndex);
/**
 * @brief modbus_data_list_set
 * @param slave_or_host
 * @param list_index
 * @param p_data_ist
 * @param data_type
 * @return
 * @author pml
 * @date 2017/5/12
 * @note 设置modbus数据流列表
 */
int modbus_data_list_set(unsigned int slave_or_host, unsigned int list_index, void *p_data_ist, unsigned int data_type);


/**
 * @brief modbus_data_list_get
 * @param list_index
 * @param p_data_ist
 * @return
 * @author pml
 * @date 2017/5/12
 * @note 获取modbus数据流列表
 */
int modbus_data_list_get(unsigned int list_index, void *p_data_ist);

/**
 * @brief modbus_del_data_list
 * @param list_index
 * @return
 * @author pml
 * @date 2017/5/12
 * @note modbus删除数据流
 */
int modbus_del_data_list(unsigned int list_index);
/**
 * @brief modbus_clean_data_list
 * @return 0：失败，1：成功
 * @author pml
 * @date 2017/5/12
 * @note 清空Modbus数据列表
 */
int modbus_clean_data_list(void);
/**
 * @brief modbus_data_list_move_up
 * @param list_index
 * @return 0：失败，1：成功
 * @author pml
 * @date 2017/5/12
 * @note modbus数据流上移
 */
int modbus_data_list_move_up(unsigned int list_index);

/**
 * @brief modbus_data_list_move_down
 * @param list_index
 * @return 0：失败，1：成功
 * @author pml
 * @date 2017/5/12
 * @note modbus数据流下移
 */
int modbus_data_list_move_down(unsigned int list_index);

/**
 * @brief modbus_hold_input_reg_data_get
 * @param reg_type
 * @param addr
 * @return
 * @author pml
 * @date 2017/5/12
 * @note 获取modbus寄存器数据起始地址
 */
unsigned short *modbus_hold_input_reg_data_get(unsigned int reg_type, unsigned int addr);



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif // MODBUSGLOBAL_H
