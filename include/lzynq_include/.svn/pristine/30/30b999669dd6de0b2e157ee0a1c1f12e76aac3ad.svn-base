#ifndef __CMOS_9M021C_H__
#define __CMOS_9M021C_H__


#include "cmos_common.h"

#define CMOS_9M021C_I2C_DEV_ADDR     0x00000020

#define EXPOSURE_INIT_9M021C        12000



#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


/**
 * @brief Cmos_9M021C_Init
 * @param pixel_config
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 全局曝光(彩色)初始化函数
 */
extern int Cmos_9M021C_Init(unsigned int pixel_config);

/**
 * @brief Cmos_9M021C_Set_Exposure
 * @param texp
 * @author Vincent
 * @date 2017/5/12
 * @note 全局曝光(彩色)相机曝光设置函数
 */
extern void Cmos_9M021C_Set_Exposure(unsigned int texp);

/**
 * @brief Cmos_9M021C_Set_Gain
 * @param num
 * @author Vincent
 * @date 2017/5/12
 * @note 全局曝光(彩色)相机增益设置函数
 */
extern void Cmos_9M021C_Set_Gain(unsigned int num);

/**
 * @brief Init_9M021C_130w
 * @author Vincent
 * @date 2017/5/12
 * @note 130W全局曝光(彩色)初始化函数
 */
extern void Init_9M021C_130w(void);

/**
 * @brief Init_9M021C_30w
 * @author Vincent
 * @date 2017/5/12
 * @note 30W全局曝光(彩色)初始化函数
 */
extern void Init_9M021C_30w(void);

/**
 * @brief Cmos_9M021C_30w_Y_Clip_Set
 * @param start_y
 * @param height
 * @author Vincent
 * @date 2017/5/12
 * @note 设置30W全局曝光(彩色)CMOS采集图像Y方向的裁剪参数
 */
extern void Cmos_9M021C_30w_Y_Clip_Set(u16 start_y, u16 height);

/**
 * @brief Cmos_9M021C_130w_Y_Clip_Set
 * @param start_y
 * @param height
 * @author Vincent
 * @date 2017/5/12
 * @note 设置130W全局曝光(彩色)CMOS采集图像Y方向的裁剪参数
 */
extern void Cmos_9M021C_130w_Y_Clip_Set(u16 start_y, u16 height);

/**
 * @brief Cmos_9m021c_30W_Para_Init
 * @param pCmosCfg
 * @author Vincent
 * @date 2017/5/12
 * @note 彩色相机30W像素CMOS相关参数初始化
 */
extern void Cmos_9m021c_30W_Para_Init(CMOS_CFG *pCmosCfg);

/**
 * @brief Cmos_9m021c_130W_Para_Init
 * @param pCmosCfg
 * @author Vincent
 * @date 2017/5/12
 * @note 彩色相机130W像素CMOS相关参数初始化
 */
extern void Cmos_9m021c_130W_Para_Init(CMOS_CFG *pCmosCfg);

//extern void Cmos_9M021C_Gain_Change(unsigned int num);
//extern void Cmos_9M021C_Exposure_Change(unsigned int num);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __CMOS_9M021C_H__ */
