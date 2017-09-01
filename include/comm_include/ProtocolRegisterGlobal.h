#ifndef PROTOCOLREGISTERGLOBAL_H
#define PROTOCOLREGISTERGLOBAL_H
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#define DATA_LENGTH_MAX 1024 ///<数据最大长度
#define DATA_REF_CNT_MAX 30  //<数据引用最大个数

/** @brief 数据流格式处理函数 */
typedef int (*data_stream_format_handle_func)(unsigned int data_stream_index);
/** @brief 数据流发送前的处理函数 */
typedef int (*data_stream_send_handle_func)(unsigned int data_stream_index);
/** @brief 数据接收后的处理函数 */
typedef int (*data_recv_handle_func)(char *recv_data, int recv_len);


/**
 * @brief protocol_register_init
 * @param protocol_type
 * @return
 * @author pml
 * @date 2017/5/12
 * @note 协议注册初始化
 */
int protocol_register_init(int protocol_type);

/**
 * @brief data_stream_format_func_set
 * @param fpFunc
 * @return
 * @author pml
 * @date 2017/5/12
 * @note 数据流格式处理函数
 */
int data_stream_format_func_set(data_stream_format_handle_func fpFunc);

/**
 * @brief data_stream_send_handle_func_set
 * @param fpFunc
 * @return
 * @author pml
 * @date 2017/5/12
 * @note 数据发送前的处理函数
 */
int data_stream_send_handle_func_set(data_stream_send_handle_func fpFunc);

/**
 * @brief data_recv_handle_func_set
 * @param fpFunc
 * @return
 * @author pml
 * @date 2017/5/12
 * @note 数据接收后的处理函数
 */
int data_recv_handle_func_set(data_recv_handle_func fpFunc);

/**
 * @brief send_data_set
 * @param data
 * @param send_len
 * @return
 * @author pml
 * @date 2017/5/12
 * @note 设置发送数据，数据长度最大为DATA_LENGTH_MAX
 */
int send_data_set(char *data, int send_len);



/**
 * @brief data_stream_send_step_set
 * @param count
 * @author pml
 * @date 2017/5/12
 * @note 设置数据流个数
 */
void data_stream_cnt_set(unsigned int count);

/**
 * @brief data_stream_cnt_get
 * @param data_list_index：数据流的索引
 * @return 数据流个数
 * @author pml
 * @date 2017/5/12
 * @note 获取数据流个数
 */
unsigned int data_stream_cnt_get(void);


/**
 * @brief data_stream_send_step_set
 * @param data_list_index：数据流的索引
 * @param step：所执行的步骤
 * @author pml
 * @date 2017/5/12
 * @note 设置数据流发送步骤，即运行到该步骤发送
 */
void data_stream_send_step_set(unsigned int data_stream_index, unsigned int step);

/**
 * @brief data_stream_send_step_get
 * @param data_list_index：数据流的索引
 * @return 发送步骤
 * @author pml
 * @date 2017/5/12
 * @note 获取数据流发送步骤
 */
unsigned int data_stream_send_step_get(unsigned int data_stream_index);

/**
 * @brief data_stream_send_step_pre_post_exec_set
 * @param data_list_index：数据流的索引
 * @param pre_post_exec（0：所执行的步骤之后执行，1：所执行的步骤之前执行）
 * @author pml
 * @date 2017/5/12
 * @note 设置数据流在发送步骤执行之前（1）或之后（0）发送的标志
 */
void data_stream_send_step_pre_post_exec_set(unsigned int data_stream_index, unsigned int pre_post_exec);

/**
 * @brief data_stream_send_step_pre_post_exec_get
 * @param data_stream_index
 * @return
 * @author pml
 * @date 2017/5/12
 * @note 获取数据流在发送步骤执行之前（1）或之后（0）发送的标志
 */
unsigned int data_stream_send_step_pre_post_exec_get(unsigned int data_stream_index);

/**
 * @brief data_stream_send_step_op_over_set
 * @param data_stream_index
 * @param op_over
 * @author pml
 * @date 2017/5/12
 * @note 设置数据流发送完毕标志
 */
void data_stream_send_step_op_over_set(unsigned int data_stream_index, unsigned int op_over);

/**
 * @brief data_stream_send_step_op_over_get
 * @param data_stream_index
 * @return
 * @author pml
 * @date 2017/5/12
 * @note 获取数据流发送完毕标志
 */
unsigned int data_stream_send_step_op_over_get(unsigned int data_stream_index);

/**
 * @brief data_stream_ref_link_cnt_set
 * @param data_stream_index
 * @param link_cnt
 * @author pml
 * @date 2017/5/12
 * @note 设置数据流引用数据个数
 */
void data_stream_ref_link_cnt_set(unsigned int data_stream_index, unsigned int link_cnt);

/**
 * @brief data_stream_ref_link_cnt_get
 * @param data_stream_index
 * @return
 * @author pml
 * @date 2017/5/12
 * @note 获取数据流引用数据个数
 */
unsigned int data_stream_ref_link_cnt_get(unsigned int data_stream_index);

/**
 * @brief data_stream_ref_link_step_set
 * @param data_stream_index
 * @param link_index
 * @param link_step
 * @author pml
 * @date 2017/5/12
 * @note 设置数据流的引用步骤
 */
void data_stream_ref_link_step_set(unsigned int data_stream_index, unsigned int link_index, unsigned int link_step);

/**
 * @brief data_stream_ref_link_step_get
 * @param data_stream_index
 * @param link_index
 * @return
 * @author pml
 * @date 2017/5/12
 * @note 获取数据流的引用步骤
 */
unsigned int data_stream_ref_link_step_get(unsigned int data_stream_index, unsigned int link_index);

/**
 * @brief data_stream_ref_result_index_set
 * @param data_stream_index
 * @param link_index
 * @param result_index
 * @author pml
 * @date 2017/5/12
 * @note 设置数据流的关联引用结果索引
 */
void data_stream_ref_result_index_set(unsigned int data_stream_index, unsigned int link_index, unsigned int result_index);

/**
 * @brief data_stream_ref_result_index_get
 * @param data_stream_index
 * @param link_index
 * @return
 * @author pml
 * @date 2017/5/12
 * @note 获取数据流的引用步骤结果索引
 */
unsigned int data_stream_ref_result_index_get(unsigned int data_stream_index, unsigned int link_index);



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif // PROTOCOLREGISTERGLOBAL_H
