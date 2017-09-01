#ifndef HEARTBEATGLOBAL_H
#define HEARTBEATGLOBAL_H
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#define HEART_BEAT_DATA_SIZE 32
#define HEART_BEAT_PASSIVE_TYPE 0 ///<0:被动类型
#define HEART_BEAT_ACTIVE_TYPE 1 ///<1：主动类型

typedef struct{
    int heart_beat_flag; ///<0：关闭，1：启动
    int heart_beat_type; ///<0：被动类型，1：主动类型
    int pulse_time; ///<脉搏时间，单位为ms
    char recv_str[HEART_BEAT_DATA_SIZE]; ///<接收的字符串
    char send_str[HEART_BEAT_DATA_SIZE]; ///<发送的字符串
}HEART_BEAT_STRUCT;

/**
 * @brief heart_beat_config_set
 * @param pHeartBeatCfg
 * @author Vincent
 * @date 2017/5/12
 * @note 设置心跳监控的参数
 */
void heart_beat_config_set(HEART_BEAT_STRUCT *pHeartBeatCfg);

/**
 * @brief heart_beat_config_get
 * @param pHeartBeatCfg
 * @author Vincent
 * @date 2017/5/12
 * @note 获取心跳监控的参数
 */
void heart_beat_config_get(HEART_BEAT_STRUCT *pHeartBeatCfg);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif // HEARTBEATGLOBAL_H
