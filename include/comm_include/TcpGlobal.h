/**
  * @file  [Tcp.h]
  * @brief  TCP接口函数
  * @author  <pml>
  * @date  <2017/5/15>
  * @version  <v1.0>
  * @note
  *
  */
#ifndef _TCPGLOBAL_H_
#define _TCPGLOBAL_H_
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#define TCP_SERVER 0 ///< 服务器
#define TCP_CLIENT 1 ///< 客户端


/** @brief tcp参数配置 */
typedef struct{
    int net_type; ///< 0:server, 1:client
    int port; ///< The network port number
    char ip[16]; ///< The network ip
}TCP_CONFIG;

/**
 * @brief tcp_config_set
 * @param tcp
 * @author pml
 * @date 2017/5/12
 * @note set tcp config
 */
void tcp_config_set(TCP_CONFIG *tcp);
/**
 * @brief tcp_config_get
 * @param tcp
 * @author pml
 * @date 2017/5/12
 * @note get tcp config
 */
void tcp_config_get(TCP_CONFIG *tcp);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif
