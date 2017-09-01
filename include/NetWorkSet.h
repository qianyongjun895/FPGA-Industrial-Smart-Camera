#ifndef NETWORKSET_H
#define NETWORKSET_H

#define NET_WORK_CFG_PATH "/mnt/emmc2/config/Network.cfg"

typedef enum {
    CONNECT_ERR = 0,
    CONNECT_OK,
    CONNECT_FAIL,
    CONNECTING
} NETWORK_CONNECT_STATUS;

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/**
 * @brief 获取相机IP
 * @param
 * @return 相机IP
 * @author <AutumnX>
 * @note
 */
char* GetLocalIp(void);

/**
 * @brief 获取相机MAC地址
 * @param
 * @return 相机MAC地址
 * @author <AutumnX>
 * @note
 */
char* GetLocalMacAddr(void);

/**
 * @brief 获取相机子网掩码
 * @param
 * @return 相机子网掩码
 * @author <AutumnX>
 * @note
 */
char* GetLocalNetMask(void);

/**
 * @brief 设置相机IP
 * @param ipaddr 相机IP
 * @return 0:成功 <0:失败
 * @author <AutumnX>
 * @note
 */
int SetLocalIp(char *ipaddr);

/**
 * @brief 设置相机子网掩码
 * @param netMask 相机子网掩码
 * @return 0:成功 <0:失败
 * @author <AutumnX>
 * @note
 */
int SetLocalNetMask(char *netMask);

/**
 * @brief 设置相机网关
 * @param szGateWay 相机网关
 * @return 0:成功 <0:失败
 * @author <AutumnX>
 * @note
 */
int SetLocalGateWay(char *szGateWay);

/**
 * @brief 设置相机自动获取网络
 * @param
 * @return 0:成功 <0:失败
 * @author <AutumnX>
 * @note
 */
int SetNetWayAuto(void);

/**
 * @brief 手动设置相机网络(IP,子网掩码,网关)
 * @param ipaddr 相机IP
 * @param mask 相机子网掩码
 * @param gateway 相机网关
 * @return 0:成功 <0:失败
 * @author <AutumnX>
 * @note
 */
int SetNetWayManual(char *Ipaddr, char *mask, char *gateway);

/**
 * @brief 获取相机网络状态
 * @param
 * @return 0:错误 1:已连接 2:已断开 3:连接中
 * @author <AutumnX>
 * @note
 */
int GetNetworkStatus(void);

/**
 * @brief 获取相机网络连接方式
 * @param
 * @return 0:手动 1:自动
 * @author <AutumnX>
 * @note
 */
int GetNetWay(void);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif

