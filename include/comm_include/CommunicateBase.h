#ifndef COMMUNICATEBASE_H
#define COMMUNICATEBASE_H
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>

#ifndef DATA_SINT
#define DATA_SINT           0
#endif
#ifndef DATA_SINT_INV
#define DATA_SINT_INV       1
#endif
#ifndef DATA_UINT
#define DATA_UINT           2
#endif
#ifndef DATA_UINT_INV
#define DATA_UINT_INV       3
#endif
#ifndef DATA_FLT
#define DATA_FLT            4
#endif
#ifndef DATA_FLT_INV
#define DATA_FLT_INV        5
#endif
#ifndef DATA_LONG
#define DATA_LONG           6
#endif
#ifndef DATA_LONG_INV
#define DATA_LONG_INV       7
#endif
#ifndef DATA_DBL
#define DATA_DBL            8
#endif
#ifndef DATA_DBL_INV
#define DATA_DBL_INV        9
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

typedef struct _comm_t COMM_T;
typedef struct _backend_t BACKEND_T;

/** @brief 通信的回调函数 */
struct _backend_t{
    int (*send) (COMM_T *pComm, const char *sendData, int sendLen); ///< 发送函数
    int (*recv) (COMM_T *pComm, char *recvData, int recvLen); ///< 接收函数
    int (*connect) (COMM_T *pComm); ///< 连接函数
    int (*close) (COMM_T *pComm); ///< 关闭函数
    int (*free) (COMM_T *pComm); ///< 释放资源函数
};

/** @brief 数据通信 */
struct _comm_t{
    int fd; ///< 套接字或文件描述符
    int host_or_slave; ///< 主从关系 0：从机，1：主机
    void *backend_data; ///< 参数
    BACKEND_T *backend; ///< 通信的回调函数
};

extern int g_SendDataFlag;
#define send_data_flag_get(flag) {\
									*flag = g_SendDataFlag;\
								}
#define send_data_flag_set() if(g_SendDataFlag == 0){\
								g_SendDataFlag=1;\
							}
#define send_data_flag_clear() if(g_SendDataFlag == 1){\
									g_SendDataFlag=0;\
								}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif // COMMUNICATEBASE_H
