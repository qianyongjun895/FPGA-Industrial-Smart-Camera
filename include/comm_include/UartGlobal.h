/**
  * @file  [UartGlobal.h]
  * @brief  串口接口函数
  * @author  <pml>
  * @date  <2017/5/15>
  * @version  <v1.0>
  * @note
  *
  */
#ifndef _UARTGLOBAL_H_
#define _UARTGLOBAL_H_

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/** @brief 波特率 */
typedef enum {
    UART_BAUD_9600 = 9600, ///< 波特率9600
    UART_BAUD_19200 = 19200, ///< 波特率19200
    UART_BAUD_38400 = 38400, ///< 波特率38400
    UART_BAUD_57600 = 57600, ///< 波特率57600
    UART_BAUD_115200 = 115200, ///< 波特率115200
    UART_BAUD_MAX
} Uart_Baud;

/** @brief 数据位 */
typedef enum {
    UART_DATA_BITS_6 = 6, ///< 6位数据位
    UART_DATA_BITS_7 = 7, ///< 7位数据位
    UART_DATA_BITS_8 = 8, ///< 8位数据位
    UART_DATA_BITS_MAX
} Uart_Data_Bits;

/** @brief 停止位 */
typedef enum {
    UART_STOP_BITS_1 = 0, ///< 1位停止位
    UART_STOP_BITS_2, ///< 2位停止位
    UART_STOP_BITS_MAX
} Uart_Stop_Bits;

/** @brief 核验位 */
typedef enum {
    UART_PARITY_BITS_NONE = 0, ///< 无校验
    UART_PARITY_BITS_EVEN,  ///< 偶校验
    UART_PARITY_BITS_ODD,  ///< 奇校验
    UART_PARITY_BITS_MAX
} Uart_Parity_Bits;

/** @brief 端口号，目前只用到1 */
typedef enum {
    UART_PORT_COM1 = 0, ///< 端口1
    UART_PORT_COM2, ///< 端口2
    UART_PORT_COM3, ///< 端口3
    UART_PORT_MAX
} Uart_Port_Number;

/** @brief 串口参数配置  */
typedef struct  {
    unsigned int uartport;    	///< 端口
    unsigned int baudrate;      ///< 波特率
    unsigned int databit;   	///< 数据位
    unsigned int verifytype;    ///< 奇偶校验
    unsigned int stopbit;   	///< 停止位
}UART_CONFIG;

/**
 * @brief uart_config_set
 * @param uart
 * @return
 * @author pml
 * @date 2017/5/12
 * @note set serial port config
 */
void uart_config_set(UART_CONFIG *uart);

/**
 * @brief uart_config_get
 * @param uart
 * @return
 * @author pml
 * @date 2017/5/12
 * @note get serial port config
 */
void uart_config_get(UART_CONFIG *uart);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif
