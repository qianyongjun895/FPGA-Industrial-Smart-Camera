#ifndef MITFXPLCGLOBAL_H
#define MITFXPLCGLOBAL_H

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#define M_REG_READ 0  ///< 三菱Fx协议数据流的类型 读M寄存器
#define M_REG_WRITE 1 ///< 三菱Fx协议数据流的类型 写M寄存器
#define D_REG_READ 2 ///< 三菱Fx协议数据流的类型 读D寄存器
#define D_REG_WRITE 3 ///<三菱Fx协议 数据流的类型 写D寄存器

#define M_REG_MAX_READ_CNT     256  ///< 单次读M寄存器的最大个数
#define M_REG_MAX_WRITE_CNT    160 ///< 单次写M寄存器的最大个数
#define D_REG_MAX_READ_NUM     64 ///< 单次读D寄存器的最大个数
#define D_REG_MAX_WRITE_NUM    64 ///< 单次写D寄存器的最大个数
#define PLC_DATA_LIST_NUM_MAX  100 ///< 数据流的最大个数

#define MIT_FX_FORMAT_NONE      0     ///< 数据结束格式，无 
#define MIT_FX_FORMAT_CR_LF     1     ///< 数据结束格式，CR+LF 

/** @brief PLC配置 */
typedef struct {
    unsigned int plc_type;	///< 三菱PLC型号众多，此值预留后续分辨对端连接设备类型使用 
    unsigned int station_id;	///< PLC站号(两位十六进制，范围:0x00～0x0F)
    unsigned int pc_id;			///< PC号(两位十六进制)
    unsigned int format;		///< 格式  0:无CR,LF; 1:有CR,LF
    unsigned int message_wait;	///< 报文等待时间(一位十六进制，范围:0x0~0xF)
}MIT_PLC_CFG;


/** @brief 读M寄存器 */
typedef struct {
    unsigned int reg_start;		///< 读取的寄存器起始编号 
    unsigned int reg_num;		///< 读取的寄存器个数，有效范围1-256，CPU0根据length是否大于1选用不同的指令 
    unsigned char expecte_value[M_REG_MAX_READ_CNT];		///< 本步期待值，output中的reg_value值等于expecte_value时本步结束
} PLC_READ_M_REG;

/** @brief 写M寄存器 */
typedef struct {
    unsigned int reg_start;		///< 写入的寄存器起始编号 
    unsigned int reg_num;			///< 读取的寄存器个数，有效范围1-256，CPU0根据length是否大于1选用不同的指令 
    unsigned char reg_value[M_REG_MAX_WRITE_CNT];		///< 寄存器值写入
} PLC_WRITE_M_REG;

/** @brief 读D寄存器 */
typedef struct {
    unsigned int reg_start;		///< 读取的D寄存器起始编号 
    unsigned int reg_num;		///< 读取的寄存器数量，有效范围1-64
    unsigned int data_type;		///< 写入的数据类型 
} PLC_READ_D_REG;

/** @brief  MITSUBISHI FX-3 Serial PLC 数据引用 */
typedef struct{
    unsigned short reg_index;	  ///< 起始寄存器的索引号
    unsigned short step_index;        ///< 步骤索引
    unsigned short result_index;      ///< 结果索引
}FX_RESULT_REF;

/** @brief  写D寄存器 */
typedef struct {
    unsigned int reg_start;		///< 写入的D寄存器起始编号 
    unsigned int reg_num;		///< 写入长度 ，有效范围1-64
    unsigned int data_type;		///< 写入的数据类型 
    unsigned int link_cnt;          ///< 数据引用个数 
    FX_RESULT_REF link_info[D_REG_MAX_WRITE_NUM];  ///< 结果引用结构体 
    unsigned char data_source[D_REG_MAX_WRITE_NUM];	///< 数据来源，0:手动输入 1:结果引用 
    unsigned short reg_value[D_REG_MAX_WRITE_NUM];	///< 保持寄存器写入，最多一次64个，占用128个字节 
} PLC_WRITE_D_REG;

/**
 * @brief mit_fx_plc_init
 * @return 0：失败，1：成功
 * @author pml
 * @date 2017/6/9
 * @note 三菱fx协议初始化
 */
int mit_fx_plc_init(void);

/**
 * @brief mit_fx_plc_cfg_set
 * @param pCfg
 * @author pml
 * @date 2017/5/12
 * @note 设置三菱fx协议配置
 */
void mit_fx_plc_cfg_set(MIT_PLC_CFG *pCfg);

/**
 * @brief mit_fx_plc_cfg_get
 * @param pCfg
 * @author pml
 * @date 2017/5/12
 * @note 获取三菱fx协议配置
 */
void mit_fx_plc_cfg_get(MIT_PLC_CFG *pCfg);

/**
 * @brief mit_fx_plc_type_set
 * @param plc_type
 * @author pml
 * @date 2017/5/12
 * @note  设置plc类型
 */
void mit_fx_plc_type_set(unsigned int plc_type);

/**
 * @brief mit_fx_plc_type_get
 * @return
 * @author pml
 * @date 2017/5/12
 * @note  获取plc类型
 */
unsigned int mit_fx_plc_type_get(void);
/**
 * @brief mit_fx_plc_station_id_set
 * @param station_id(范围:0x00～0x0F)
 * @author pml
 * @date 2017/5/12
 * @note  设置plc站号
 */
void mit_fx_plc_station_id_set(unsigned int station_id);

/**
 * @brief mit_fx_plc_station_id_get
 * @return
 * @author pml
 * @date 2017/5/12
 * @note 获取plc号
 */
unsigned int mit_fx_plc_station_id_get(void);

/**
 * @brief mit_fx_plc_pc_id_set
 * @param pc_id(两位十六进制)
 * @return
 * @author pml
 * @date 2017/5/12
 * @note  设置pc号
 */
void mit_fx_plc_pc_id_set(unsigned int pc_id);

/**
 * @brief mit_fx_plc_pc_id_get
 * @return
 * @author pml
 * @date 2017/5/12
 * @note 获取pc号
 */
unsigned int mit_fx_plc_pc_id_get(void);

/**
 * @brief mit_fx_plc_format_set
 * @param format(0:无CR,LF; 1:有CR,LF)
 * @author pml
 * @date 2017/5/12
 * @note  设置三菱Fx协议数据结束格式
 */
void mit_fx_plc_format_set(unsigned int format);

/**
 * @brief mit_fx_plc_format_get
 * @return 0:无CR,LF; 1:有CR,LF
 * @author pml
 * @date 2017/5/12
 * @note 获取三菱Fx协议数据结束格式
 */
unsigned int mit_fx_plc_format_get(void);

/**
 * @brief mit_fx_plc_message_wait_set
 * @param format(范围:0x0~0xF)
 * @author pml
 * @date 2017/5/12
 * @note  设置三菱Fx协议报文等待时间
 */
void mit_fx_plc_message_wait_set(unsigned int message_wait);

/**
 * @brief mit_fx_plc_message_wait_get
 * @return
 * @author pml
 * @date 2017/5/12
 * @note 获取三菱Fx协议报文等待时间
 */
unsigned int mit_fx_plc_message_wait_get(void);
/**
 * @brief mit_fx_plc_list_data_cnt_set
 * @param count
 * @author pml
 * @date 2017/5/12
 * @note 设置三菱Fx协议数据流个数
 */
void mit_fx_plc_list_data_cnt_set(unsigned int count);

/**
 * @brief mit_fx_plc_list_data_cnt_get
 * @return
 * @author pml
 * @date 2017/5/12
 * @note 获取三菱Fx协议数据流个数
 */
unsigned int mit_fx_plc_list_data_cnt_get(void);

/**
 * @brief mit_fx_plc_list_data_type_set
 * @param listIndex
 * @param data_type
 * @author pml
 * @date 2017/5/12
 * @note 设置三菱Fx协议数据流数据类型
 */
void mit_fx_plc_list_data_type_set(unsigned int listIndex, unsigned int data_type);

/**
 * @brief mit_fx_plc_list_data_type_get
 * @param listIndex
 * @return
 * @author pml
 * @date 2017/5/12
 * @note 获取三菱Fx协议数据流数据类型
 */
unsigned int mit_fx_plc_list_data_type_get(unsigned int listIndex);


/**
 * @brief mit_fx_plc_list_exec_step_set
 * @param listIndex
 * @param step
 * @author pml
 * @date 2017/5/12
 * @note 设置三菱Fx协议数据流发送步骤，即发送步骤执行时发送
 */
void mit_fx_plc_list_exec_step_set(unsigned int listIndex, unsigned int step);

/**
 * @brief mit_fx_plc_list_exec_step_get
 * @param listIndex
 * @return
 * @author pml
 * @date 2017/5/12
 * @note 获取三菱Fx协议数据流发送步骤
 */
unsigned int mit_fx_plc_list_exec_step_get(unsigned int listIndex);

/**
 * @brief mit_fx_plc_list_pre_post_exec_step_set
 * @param listIndex
 * @param flag
 * @author pml
 * @date 2017/5/12
 * @note 设置三菱Fx协议数据流在发送步骤执行之前（1）或之后（0）发送的标志
 */
void mit_fx_plc_list_pre_post_exec_step_set(unsigned int listIndex, unsigned int flag);

/**
 * @brief mit_fx_plc_list_pre_post_exec_step_get
 * @param listIndex
 * @return
 * @author pml
 * @date 2017/5/12
 * @note 获取三菱Fx协议数据流在发送步骤执行之前（1）或之后（0）发送的标志
 */
unsigned int mit_fx_plc_list_pre_post_exec_step_get(unsigned int listIndex);

/**
 * @brief mit_fx_plc_list_op_over_step_set
 * @param listIndex
 * @param flag
 * @author pml
 * @date 2017/5/12
 * @note 设置三菱Fx协议数据流发送完成标志（1：未发送，0：发送完毕）
 */
void mit_fx_plc_list_op_over_step_set(unsigned int listIndex, unsigned int flag);

/**
 * @brief mit_fx_plc_list_op_over_step_get
 * @param listIndex
 * @return
 * @author pml
 * @date 2017/5/12
 * @note 获取三菱Fx协议数据流发送完成标志（1：未发送，0：发送完毕）
 */
unsigned int mit_fx_plc_list_op_over_step_get(unsigned int listIndex);

/**
 * @brief mit_fx_plc_data_list_set
 * @param listIndex
 * @param pDataList
 * @param dataType
 * @author pml
 * @date 2017/5/12
 * @note 设置三菱Fx协议数据流参数
 */
void mit_fx_plc_data_list_set(unsigned int listIndex, void *pDataList, unsigned int dataType);

/**
 * @brief mit_fx_plc_data_list_get
 * @param listIndex
 * @param pDataList
 * @author pml
 * @date 2017/5/12
 * @note 获取三菱Fx协议数据流参数
 */
void mit_fx_plc_data_list_get(unsigned int listIndex, void *pDataList);

/**
 * @brief mit_fx_plc_data_list_move_up
 * @param list_index
 * @return 0:失败，1：成功
 * @author pml
 * @date 2017/5/12
 * @note 三菱fx协议数据流上移
 */
int mit_fx_plc_data_list_move_up(unsigned int list_index);

/**
 * @brief mit_fx_plc_data_list_move_down
 * @param list_index
 * @return 0:失败，1：成功
 * @author pml
 * @date 2017/5/12
 * @note 三菱fx协议数据流下移
 */
int mit_fx_plc_data_list_move_down(unsigned int list_index);

/**
 * @brief mit_fx_plc_clean_data_list
 * @return 0:失败，1：成功
 * @author pml
 * @date 2017/5/12
 * @note 清空三菱fx协议数据流
 */
int mit_fx_plc_clean_data_list(void);

/**
 * @brief mit_fx_plc_del_data_list
 * @param list_index
 * @return 0:失败，1：成功
 * @author pml
 * @date 2017/5/12
 * @note 删除三菱fx协议数据流
 */
int mit_fx_plc_del_data_list(unsigned int list_index);

/**
 * @brief mit_fx_plc_d_reg_data_get
 * @param addr
 * @return
 * @author pml
 * @date 2017/5/12
 * @note 获取三菱FX数据寄存器的起始地址
 */
unsigned short *mit_fx_plc_d_reg_data_get(unsigned int addr);



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif // MITFXPLCGLOBAL_H
