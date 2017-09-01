/**
  * @file  []
  * @brief
  * @author  <pml>
  * @date  <2017/5/11>
  * @version  <v1.0>
  * @note
  *
  */
#ifndef _UDPGLOBAL_H
#define _UDPGLOBAL_H

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/** @brief udp参数配置 */
typedef struct{
    char ip[16]; ///< 远程设备ip
    int server_port; ///< 远程端口
    int local_port; ///< 本地端口
}UDP_CONFIG;

/**
 * @brief udp_config_set
 * @param udp
 * @author pml
 * @date 2017/5/12
 * @note set udp config
 */
void udp_config_set(UDP_CONFIG *udp);

/**
 * @brief udp_config_get
 * @param udp
 * @author pml
 * @date 2017/5/12
 * @note get udp config
 */
void udp_config_get(UDP_CONFIG *udp);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif
