/**
  * @file  [ProtocolInitGlobal.h]
  * @brief  协议数据的解析
  * @author  <th>
  * @date  <2017/6/21>
  * @version  <v1.0>
  * @note
  *
  */
#ifndef PROTOCOLINITGLOBAL_H
#define PROTOCOLINITGLOBAL_H


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


typedef struct{
    char work_mode[32];
    int dev_addr;
    int port;
    char ip[16];
}COMM_TCP_CONFIG;

typedef struct{
    char Server_ip[16];
    int Server_port;
    char local_ip[16];
    int local_port;
}COMM_UDP_CONFIG;

typedef struct {
    char work_mode[32];
    int dev_addr;
    unsigned int uartport;    	/* 端口  */
    unsigned int baudrate;      /* 波特率  */
    unsigned int databit;   	/* 数据位  */
    char verifytype[32];    /* 奇偶校验  */
    unsigned int stopbit;   	/* 停止位  */
}COMM_UART_CONFIG;

/**
 * @brief   解析协议的数据
 * @param   void
 * @return -1:失败; 0:成功
 * @author <th>
 * @note
 */
extern int Parse_Protocol_Data();

/**
 * @brief 获取协议名,可一直调用直到返回-1为止
 * @param protocol_index:协议的数组下标,从0开始; ProtocolName[100]:返回的协议名
 * @return -1:获取结束; 0:获取成功
 * @author <th>
 * @note
 */
extern int Get_Protocol_Name(unsigned int protocol_index, char* ProtocolName);

/**
 * @brief 获取协议的状态
 * @param protocol_index:协议的数组下标,从0开始;
 * @return -1:获取失败; 0:未打开; 1:已打开;
 * @author <th>
 * @note
 */
extern int Get_Protocol_Status(unsigned int protocol_index);

/**
 * @brief 获取协议类型,可一直调用直到返回-1为止
 * @param protocol_index:协议的数组下标,从0开始;
 * @return -1:获取结束; 其他:协议类型
 * @author <th>
 * @note
 */
extern int Get_Protocol_Type(unsigned int protocol_index);

/**
 * @brief 获取协议启用的通讯模式
 * @param protocol_index:协议的数组下标,从0开始; CommMode[100]:返回的通讯模式的字符
 * @return -1:获取结束; 0:获取成功
 * @author <th>
 * @note
 */
extern int Get_Protocol_Comm_Mode(unsigned int protocol_index, char* CommMode);

/**
 * @brief 获取协议可选择的通讯模式的字符
 * @param protocol_index:协议的数组下标,从0开始; comm_mode_index:通讯模式的数组下标,从0开始; Comm_Mode_Name[100]:返回的通讯模式的字符
 * @return -1:获取结束; 0:获取成功
 * @author <th>
 * @note
 */
extern int Get_Protocol_CommMode_Name(unsigned int protocol_index, unsigned int comm_mode_index, char* Comm_Mode_Name);

/**
 * @brief 获取协议的UI库的路径
 * @param protocol_index:协议的数组下标,从0开始; Lib_Path[100]:返回的UI库的路径
 * @return -1:获取结束; 0:获取成功
 * @author <th>
 * @note
 */
extern int Get_Protocol_Lib_Path(unsigned int protocol_index, char* Lib_Path);

/**
 * @brief 获取通讯模式名,可一直调用直到返回-1为止
 * @param Comm_Mode_index:通讯模式的数组下标,从0开始; Comm_Mode_Name[100]:返回的通讯模式名
 * @return -1:获取结束; 0:获取成功
 * @author <th>
 * @note
 */
extern int Get_Comm_Mode_Name(unsigned int Comm_Mode_index, char* Comm_Mode_Name);

/**
 * @brief 获取通讯模式的类型
 * @param Comm_Mode_index:通讯模式的数组下标,从0开始;
 * @return -1:获取结束; 其他:通讯模式类型
 * @author <th>
 * @note
 */
extern int Get_Comm_Mode_Type(unsigned int Comm_Mode_index);

/**
 * @brief 获取通讯模式的UI库的路径
 * @param Comm_Mode_index:通讯模式的数组下标,从0开始;Comm_Mode_Lib_Path[100]:返回的UI库的路径
 * @return -1:获取结束; 0:获取成功
 * @author <th>
 * @note
 */
extern int Get_Comm_Mode_Lib_Path(unsigned int Comm_Mode_index, char* Comm_Mode_Lib_Path);

/**
 * @brief 获取串口参数
 * @param  uart_cfg:返回的串口参数
 * @return void
 * @author <th>
 * @note
 */
extern void Get_Uart_Config(COMM_UART_CONFIG* uart_cfg);

/**
 * @brief 获取TCP参数
 * @param  tcp_cfg:返回的TCP参数
 * @return void
 * @author <th>
 * @note
 */
extern void Get_Tcp_Config(COMM_TCP_CONFIG* tcp_cfg);

/**
 * @brief 获取UDP参数
 * @param  udp_cfg:返回的UDP参数
 * @return void
 * @author <th>
 * @note
 */
extern void Get_Udp_Config(COMM_UDP_CONFIG* udp_cfg);

/**
 * @brief 协议参数变化时写入xml文件的函数
 * @param protocol_type:协议类型;
 *        protocol_status:协议的状态, 0:关闭 1:打开;
 *        Comm_Mode_type:通讯模式的类型;
 *        data:写入的数据,如COMM_UART_CONFIG结构体;
 * @return
 * @author <th>
 * @note
 */
extern int Protocol_Param_Change(unsigned int protocol_type, unsigned int protocol_status, unsigned int Comm_Mode_type, void *data);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif // PROTOCOLINITGLOBAL_H
