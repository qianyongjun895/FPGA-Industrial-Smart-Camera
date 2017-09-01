#ifndef USERDEFINEDGLOBAL_H
#define USERDEFINEDGLOBAL_H

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include "BaseStruct.h"

#define USER_DEFINE_DATA_LIST_NUM_MAX       100     ///< 最大数据流个数

#define DATA_SOURCE_TYPE_LINK_STEP          0       ///< 引用步骤
#define DATA_SOURCE_TYPE_MANUAL_INPUT       1       ///< 手动输入
#define DATA_SOURCE_TYPE_G_DATA             2       ///< G_DATA        

#define USER_DEFINE_TEXT_SIZE               20      ///< 文本的最大长度
#define USER_LABEL_DATA_SIZE                32      ///< 标签最大长度

#define USER_lINK_DATA_SIZE                 30      ///< 最大关联数据个数

#define	DECIMAL_DIGITS_MIN 				    0		///< 没有小数部分
#define	DECIMAL_DIGITS_MAX				    6		///< 保留小数位最大位数

#define SEPARATOR_DISABLE                   0       ///< 分隔符不使能
#define SEPARATOR_ENABLE                    1       ///< 分隔符使能
#define SEPARATOR_TYPE_STANDARD             0       ///< 分隔符标准类型
#define SEPARATOR_TYPE_OTHER                1       ///< 分隔符其他类型
#define SEPARATOR_COMMA                     0x2C    ///< 逗号
#define SEPARATOR_SPACE                     0x20    ///< 空格
#define SEPARATOR_COLON                     0x3A    ///< 冒号
#define SEPARATOR_SLASH                     0x2F    ///< 斜杠
#define SEPARATOR_VERTICAL_BAR              0x7C    ///< 竖杠
#define SEPARATOR_UNDERLINE                 0x2F    ///< 下划线
#define SEPARATOR_SEMICOLON                 0x3B    ///< 分号

#define SPECIAL_END_CHARACTER_NONE          0       ///< 结束符 无
#define SPECIAL_END_CHARACTER_CR            1       ///< 结束符 CR
#define SPECIAL_END_CHARACTER_LF            2       ///< 结束符 LF
#define SPECIAL_END_CHARACTER_CR_LF         3       ///< 结束符 CR+LF

#define CRC_VERIFY_NONE                     0       ///< 无校验
#define CRC_VERIFY_CRC16_MODBUS             1       ///< CRC16/modbus校验
#define CRC_VERIFY_CRC32                    2       ///< CRC32校验
#define CRC_VERIFY_CRC32_MEPG2              3       ///< crc32/mepg2校验

#define LABEL_DISABLE                       0       ///< 标签使能
#define LABEL_ENABLE                        1       ///< 标签使能

#define SEND_NOW_DISABLE                    256     ///< 立即发送不使能，将发送的关联步骤置为256, 使能则置为所关联的步骤索引

#define FILL_DISABLE                        0       ///< 数据填充不使能
#define FILL_ENABLE                         1       ///< 数据填充使能
#define FILL_WIDTH_MIN                      1       ///< 数据填充最小宽度
#define FILL_WIDTH_MAX                      30      ///< 数据填充最大宽度
#define FILL_TYPE_LEADING_SPACE			    1		///< 数据填充方式:前导空格
#define FILL_TYPE_TRAILING_SPACE			2		///< 数据填充方式:尾随空格
#define FILL_TYPE_LEADING_ZERO			    3		///< 数据填充方式:前导零                  


/**
 * @brief user_defined_init
 * @return 0：失败，1：成功
 * @author pml
 * @date 2017/6/9
 * @note 自定义协议初始化
 */
int user_defined_init(void);

/**
 * @brief user_defined_data_cnt_set
 * @author pml
 * @date 2017/5/12
 * @note 设置数据流个数
 */
void user_defined_data_cnt_set(unsigned int data_cnt);

/**
 * @brief user_defined_data_cnt_get
 * @return 数据流个数
 * @author pml
 * @date 2017/5/12
 * @note 获取数据流个数
 */
unsigned int user_defined_data_cnt_get(void);

/**
 * @brief user_defined_start_text_set
 * @param pStr
 * @return
 * @author pml
 * @date 2017/5/12
 * @note 设置自定义协议通信开头文本
 */
int user_defined_start_text_set(char *pStr);

/**
 * @brief user_defined_start_text_get
 * @param pStr
 * @return
 * @author pml
 * @date 2017/5/12
 * @note 获取自定义协议通信开头文本
 */
int user_defined_start_text_get(char *pStr);

/**
 * @brief UserDefinedEndCharacterSet
 * @param pStr
 * @return
 * @author pml
 * @date 2017/5/12
 * @note 设置自定义协议通信结束文本
 */
int user_defined_end_text_set(char *pStr);

/**
 * @brief user_defined_end_text_get
 * @param pStr
 * @return
 * @author pml
 * @date 2017/5/12
 * @note 获取自定义协议通信结束文本
 */
int user_defined_end_text_get(char *pStr);

/**
 * @brief user_defined_separator_enable_set
 * @param flag
 * @author pml
 * @date 2017/5/12
 * @note 设置自定义协议通信分隔符使能标志（0：不使能，1：使能）
 */
void user_defined_separator_enable_set(char flag);

/**
 * @brief user_defined_separator_enable_get
 * @return 分隔符使能标志
 * @author pml
 * @date 2017/5/12
 * @note 获取自定义协议通信分隔符使能标志（0：不使能，1：使能）
 */
char user_defined_separator_enable_get(void);

/**
 * @brief user_defined_separator_type_set
 * @param type
 * @author pml
 * @date 2017/5/12
 * @note 设置自定义协议通信分隔符类型（0表示标准分隔符  1表示其他分隔符）
 */
void user_defined_separator_type_set(char type);

/**
 * @brief user_defined_separator_type_get
 * @return 分隔符类型
 * @author pml
 * @date 2017/5/12
 * @note 获取自定义协议通信分隔符类型（0表示标准分隔符  1表示其他分隔符）
 */
char user_defined_separator_type_get(void);

/**
 * @brief user_defined_separator_character_set
 * @param c
 * @author pml
 * @date 2017/5/12
 * @note 设置自定义协议通信分隔符
 */
void user_defined_separator_character_set(char c);

/**
 * @brief user_defined_separator_character_get
 * @return 分隔符
 * @author pml
 * @date 2017/5/12
 * @note 获取自定义协议通信分隔符
 */
char user_defined_separator_character_get(void);

/**
 * @brief user_defined_special_end_character_set
 * @param 结束符
 * @author pml
 * @date 2017/5/12
 * @note 设置特殊结束符
 */
void user_defined_special_end_character_set(char c);

/**
 * @brief user_defined_special_end_character_get
 * @return 结束符
 * @author pml
 * @date 2017/5/12
 * @note 获取特殊结束符
 */
char user_defined_special_end_character_get(void);
/**
 * @brief user_defined_CRC_verify_set
 * @param crc_verify
 * @return
 * @author pml
 * @date 2017/5/12
 * @note 设置自定义协议通信校验类型
 */
void user_defined_CRC_verify_set(char crc_verify);

/**
 * @brief user_defined_CRC_verify_get
 * @return crc 校验类型
 * @author pml
 * @date 2017/5/12
 * @note 获取自定义协议通信校验类型
 */
char user_defined_CRC_verify_get(void);

/**
 * @brief user_defined_send_step_set
 * @param list_index
 * @param send_step
 * @author pml
 * @date 2017/5/12
 * @note 设置数据流发送步骤，即在执行该步骤时发送
 */
void user_defined_send_step_set(unsigned int list_index, unsigned int send_step);

/**
 * @brief user_defined_send_step_get
 * @param list_index
 * @return 数据流发送步骤
 * @author pml
 * @date 2017/5/12
 * @note 获取数据流发送步骤
 */
unsigned int user_defined_send_step_get(unsigned int list_index);

/**
 * @brief user_defined_source_item_cnt_set
 * @param list_index
 * @param link_cnt
 * @author pml
 * @date 2017/5/12
 * @note 设置自定义协议数据流关联数据的个数
 */
void user_defined_source_item_cnt_set(unsigned int list_index, unsigned int source_item_cnt);

/**
 * @brief user_defined_source_item_cnt_get
 * @param list_index
 * @return 关联数据的个数
 * @author pml
 * @date 2017/5/12
 * @note 获取自定义协议数据流关联数据的个数
 */
unsigned int user_defined_source_item_cnt_get(unsigned int list_index);

/**
 * @brief user_defined_data_source_type_set
 * @param list_index
 * @param data_index
 * @param type
 * @return
 * @author pml
 * @date 2017/5/12
 * @note 设置数据源类型
 */
unsigned  int user_defined_data_source_type_set(unsigned int list_index, unsigned int data_index, unsigned int type);

/**
 * @brief user_defined_data_source_type_get
 * @param list_index
 * @param data_index
 * @return
 * @author pml
 * @date 2017/5/12
 * @note 获取数据源类型
 */
unsigned  int user_defined_data_source_type_get(unsigned int list_index, unsigned int data_index);

/**
 * @brief user_defined_link_step_info_set
 * @param list_index
 * @param link_index
 * @param step_index
 * @author pml
 * @date 2017/5/12
 * @note 设置自定义协议数据流关联步骤的参数
 */
void user_defined_link_step_info_set(unsigned int list_index, unsigned int data_index, unsigned int step_index, unsigned int result_index);

/**
 * @brief user_defined_link_step_info_get
 * @param list_index
 * @param link_index
 * @param pStepIndex
 * @param pResultIndex
 * @return 关联数据的步骤
 * @author pml
 * @date 2017/5/12
 * @note 获取自定义协议数据流关联步骤的参数
 */
void user_defined_link_step_info_get(unsigned int list_index, unsigned int data_index, unsigned int *pStepIndex, unsigned int *pResultIndex);

/**
 * @brief user_defined_manual_input_value_set
 * @param list_index
 * @param data_index
 * @param value
 * @author pml
 * @date 2017/5/12
 * @note 设置手动输入的数值
 */
void user_defined_manual_input_value_set(unsigned int list_index, unsigned int data_index, float value);

/**
 * @brief user_defined_manual_input_value_get
 * @param list_index
 * @param data_index
 * @param pValue
 * @author pml
 * @date 2017/5/12
 * @note 获取手动输入的数值
 */
void user_defined_manual_input_value_get(unsigned int list_index, unsigned int data_index, float *pValue);

/**
 * @brief user_defined_g_data_info_set
 * @param list_index
 * @param data_index
 * @param g_data_type
 * @param g_data_addr
 * @author pml
 * @date 2017/5/12
 * @note 设置G_DATA的参数
 */
void user_defined_g_data_info_set(unsigned int list_index, unsigned int data_index, unsigned int g_data_type, unsigned int g_data_addr);

/**
 * @brief user_defined_g_data_info_get
 * @param list_index
 * @param data_index
 * @param pGDataType
 * @param pGDataAddr
 * @author pml
 * @date 2017/5/12
 * @note 获取G_DATA的参数
 */
void user_defined_g_data_info_get(unsigned int list_index, unsigned int data_index, unsigned int *pGDataType, unsigned int *pGDataAddr);


/**
 * @brief user_defined_label_enable_set
 * @param list_index
 * @param label_enable
 * @author pml
 * @date 2017/5/12
 * @note 设置自定义协议数据流数据标签使能标志(0：不使能，1：使能)
 */
void user_defined_label_enable_set(unsigned int list_index, unsigned int label_enable);

/**
 * @brief user_defined_label_enable_get
 * @param list_index
 * @return
 * @author pml
 * @date 2017/5/12
 * @note 获取自定义协议数据流数据标签使能标志(0：不使能，1：使能)
 */
unsigned int user_defined_label_enable_get(unsigned int list_index);

/**
 * @brief user_defined_label_str_set
 * @param list_index
 * @param pStr
 * @author pml
 * @date 2017/5/12
 * @note 设置自定义协议数据流数据标签
 */
void user_defined_label_str_set(unsigned int list_index, char *pStr);

/**
 * @brief user_defined_label_str_get
 * @param list_index
 * @param pStr
 * @author pml
 * @date 2017/5/12
 * @note 获取自定义协议数据流数据标签
 */
void user_defined_label_str_get(unsigned int list_index, char *pStr);

/**
 * @brief user_defined_data_type_set
 * @param list_index
 * @param data_type
 * @return
 * @author pml
 * @date 2017/5/12
 * @note 设置自定义协议数据流数据类型
 */
void user_defined_data_type_set(unsigned int list_index, unsigned int data_index, unsigned int data_type);

/**
 * @brief user_defined_data_type_get
 * @param list_index
 * @return 数据类型
 * @author pml
 * @date 2017/5/12
 * @note 获取自定义协议数据流数据类型
 */
unsigned int user_defined_data_type_get(unsigned int list_index, unsigned int data_index);

/**
 * @brief user_defined_data_decimal_set
 * @param list_index
 * @param decimal
 * @author pml
 * @date 2017/5/12
 * @note 设置自定义协议数据流数据小数点位数
 */
void user_defined_data_decimal_set(unsigned int list_index, unsigned int data_index, unsigned int decimal);

/**
 * @brief user_defined_data_decimal_get
 * @param list_index
 * @return 数据小数点位数
 * @author pml
 * @date 2017/5/12
 * @note 获取自定义协议数据流数据小数点位数
 */
unsigned int user_defined_data_decimal_get(unsigned int list_index, unsigned int data_index);


/**
 * @brief user_defined_fixed_width_enable_set
 * @param list_index
 * @param fixed_width_enable
 * @author pml
 * @date 2017/5/12
 * @note 设置自定义协议数据流数据固定宽度使能标志(0：不使能，1：使能)
 */
void user_defined_fixed_width_enable_set(unsigned int list_index, unsigned int fixed_width_enable);

/**
 * @brief user_defined_fixed_width_enable_get
 * @param list_index
 * @return 数据固定宽度使能
 * @author pml
 * @date 2017/5/12
 * @note 获取自定义协议数据流数据固定宽度使能标志(0：不使能，1：使能)
 */
unsigned int user_defined_fixed_width_enable_get(unsigned int list_index);

/**
 * @brief user_defined_fixed_width_set
 * @param list_index
 * @param fixed_width
 * @author pml
 * @date 2017/5/12
 * @note 设置自定义协议数据流数据固定宽度
 */
void user_defined_fixed_width_set(unsigned int list_index, unsigned int fixed_width);

/**
 * @brief user_defined_fixed_width_get
 * @param list_index
 * @return 数据固定宽度
 * @author pml
 * @date 2017/5/12
 * @note 获取自定义协议数据的流数据固定宽度
 */
unsigned int user_defined_fixed_width_get(unsigned int list_index);

/**
 * @brief user_defined_fill_type_set
 * @param list_index
 * @param fill_type
 * @author pml
 * @date 2017/5/12
 * @note 设置自定义协议数据流的数据填充方式
 */
void user_defined_fill_type_set(unsigned int list_index, unsigned int fill_type);

/**
 * @brief user_defined_fill_type_get
 * @param list_index
 * @return 数据填充方式
 * @author pml
 * @date 2017/5/12
 * @note 获取自定义协议数据流数据填充方式
 */
unsigned int user_defined_fill_type_get(unsigned int list_index);

/**
 * @brief user_defined_data_list_move_up
 * @param list_index
 * @return  0:失败，1：成功
 * @author pml
 * @date 2017/5/12
 * @note user_defined数据流上移
 */
int user_defined_data_list_move_up(unsigned int list_index);

/**
 * @brief user_defined_data_list_move_down
 * @param list_index
 * @return 0:失败，1：成功
 * @author pml
 * @date 2017/5/12
 * @note user_defined数据流下移
 */
int user_defined_data_list_move_down(unsigned int list_index);

/**
 * @brief user_defined_data_list_del
 * @param list_index
 * @return
 * @author pml
 * @date 2017/5/12
 * @note user_defined删除数据流
 */
int user_defined_data_list_del(unsigned int list_index);


/**
 * @brief user_defined_recv_data_get
 * @param recv_data
 * @param max_len（最大为1024）
 * @return
 * @author pml
 * @date 2017/5/12
 * @note 获取接受到的数据
 */
 int user_defined_recv_data_get(char *pRecvData, int max_len);

/**
 * @brief user_defined_recv_data_set
 * @param list_index
 * @return 0:失败，大于0：成功
 * @author pml
 * @date 2017/5/12
 * @note 自定义协议发送数据
 */
int user_defined_data_stream_send(unsigned int list_index);



int user_defined_recv_data_analysis(char *pStr, int str_len, 
RST_VALUE_STRUCT *pParam, char data_cnt, char data_type, char separator, 
char end_char);



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif // USERDEFINEDGLOBAL_H
