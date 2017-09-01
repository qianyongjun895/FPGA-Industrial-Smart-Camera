/**
  * @file  [threshold.h]
  * @brief 门限设置\检查函数
  * @author  <Terry>
  * @date  <2017/06/03>
  * @version  <v1.0>
  * @note
  *
  */

#ifndef THRESHOLD_H
#define THRESHOLD_H

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/* 门限结构体及宏定义 */
#define TH_DISABLE  0
#define TH_ENABLE   1
typedef struct {
    int low_enable;
    int high_enable;
    int low_threshold;
    int high_threshold;
}THRESHOLD_INT;

typedef struct {
    int low_enable;
    int high_enable;
    float low_threshold;
    float high_threshold;
}THRESHOLD_FLOAT;

/**
 * @brief 检查整形数是否在有效范围
 * @param
 * @return 0：成功，others：失败
 * @author <Terry>
 * @note
 */
int ThresholdIntCheck(THRESHOLD_INT *pThreshold, int iValue);

/**
 * @brief 整形门限设置低门限
 * @param
 * @return 0：成功，others：失败
 * @author <Terry>
 * @note
 */
int ThresholdIntLowEnableAndSet(THRESHOLD_INT *pThreshold, int iValue);

/**
 * @brief 整形门限关闭低门限
 * @param
 * @return 0：成功，others：失败
 * @author <Terry>
 * @note
 */
int ThresholdIntLowDisable(THRESHOLD_INT *pThreshold);

/**
 * @brief 整形门限设置高门限
 * @param
 * @return 0：成功，others：失败
 * @author <Terry>
 * @note
 */
int ThresholdIntHighEnableAndSet(THRESHOLD_INT *pThreshold, int iValue);

/**
 * @brief 整形门限关闭高门限
 * @param
 * @return 0：成功，others：失败
 * @author <Terry>
 * @note
 */
int ThresholdIntHighDisable(THRESHOLD_INT *pThreshold);

/**
 * @brief 检查浮点数是否在有效范围
 * @param
 * @return 0：成功，others：失败
 * @author <Terry>
 * @note
 */
int ThresholdFloatCheck(THRESHOLD_FLOAT *pThreshold, float fValue);

/**
 * @brief 浮点型门限设置低门限
 * @param
 * @return 0：成功，others：失败
 * @author <Terry>
 * @note
 */
int ThresholdFloatLowEnableAndSet(THRESHOLD_FLOAT *pThreshold, float fValue);

/**
 * @brief 浮点型门限关闭低门限
 * @param
 * @return 0：成功，others：失败
 * @author <Terry>
 * @note
 */
int ThresholdFloatLowDisable(THRESHOLD_FLOAT *pThreshold);

/**
 * @brief 浮点型门限设置高门限
 * @param
 * @return 0：成功，others：失败
 * @author <Terry>
 * @note
 */
int ThresholdFloatHighEnableAndSet(THRESHOLD_FLOAT *pThreshold, float fValue);

/**
 * @brief 浮点型门限关闭高门限
 * @param
 * @return 0：成功，others：失败
 * @author <Terry>
 * @note
 */
int ThresholdFloatHighDisable(THRESHOLD_FLOAT *pThreshold);
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif // THRESHOLD_H
