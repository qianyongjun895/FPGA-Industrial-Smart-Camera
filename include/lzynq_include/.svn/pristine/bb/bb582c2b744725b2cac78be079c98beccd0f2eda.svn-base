/******************************************************************************

                  版权所有 (C), 2015, SSZN

 ******************************************************************************
  文 件 名   : cmos_9p031.h
  版 本 号   : 初稿
  作    者   : Vincent
  生成日期   : 2016年1月29日
  最近修改   :
  功能描述   : cmos_9p031.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2016年1月29日
    作    者   : Vincent
    修改内容   : 创建文件

******************************************************************************/
#ifndef CMOS_9P031_H_
#define CMOS_9P031_H_

/*----------------------------------------------*
 * 包含头文件                                   *
 *----------------------------------------------*/
#include "cmos_common.h"
/*----------------------------------------------*
 * 宏定义                                       *
 *----------------------------------------------*/
#define CMOS_9P031_I2C_DEVICE_ADDR	0x90
#define EXPOSURE_INIT_9P031         30000
/*----------------------------------------------*
 * 外部变量说明                                 *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 全局变量                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 常量定义                                     *
 *----------------------------------------------*/



/**
 * @brief Cmos_9p031_Init
 * @param pixel_config
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 卷帘曝光CMOS初始化函数
 */
int Cmos_9p031_Init(unsigned int pixel_config);

/**
 * @brief Cmos_9P031_Capture_Break
 * @author Vincent
 * @date 2017/5/12
 * @note 卷帘曝光采图中断函数
 */
void Cmos_9P031_Capture_Break(void);

/**
 * @brief Cmos_9P031_Set_Gain
 * @param cmos_gain
 * @author Vincent
 * @date 2017/5/12
 * @note 卷帘曝光相机增益配置函数
 */
void Cmos_9P031_Set_Gain(unsigned int cmos_gain);

/**
 * @brief Cmos_9P031_Set_Exposure
 * @param texp
 * @author Vincent
 * @date 2017/5/12
 * @note 卷帘曝光相机曝光配置函数
 */
void Cmos_9P031_Set_Exposure(unsigned int cmos_exposure);

/**
 * @brief Cmos_9P031_30w_Y_Clip_Set
 * @param start_y
 * @param height
 * @author Vincent
 * @date 2017/5/12
 * @note 设置卷帘曝光30W像素CMOS采集图像Y方向的裁剪参数
 */
void Cmos_9P031_30w_Y_Clip_Set(unsigned short start_y, unsigned short height);

/**
 * @brief Cmos_9P031_130w_Y_Clip_Set
 * @param start_y
 * @param height
 * @author Vincent
 * @date 2017/5/12
 * @note 设置卷帘曝光130W像素CMOS采集图像Y方向的裁剪参数
 */
void Cmos_9P031_130w_Y_Clip_Set(unsigned short start_y, unsigned short height);

/**
 * @brief Cmos_9P031_500w_Y_Clip_Set
 * @param start_y
 * @param height
 * @author Vincent
 * @date 2017/5/12
 * @note 设置卷帘曝光500W像素CMOS采集图像Y方向的裁剪参数
 */
void Cmos_9P031_500w_Y_Clip_Set(unsigned short start_y, unsigned short height);

/**
 * @brief Cmos_9P031_30W_Para_Init
 * @param pCmosCfg
 * @author Vincent
 * @date 2017/5/12
 * @note 卷帘曝光30W像素CMOS相关配置参数初始化
 */
void Cmos_9P031_30W_Para_Init(CMOS_CFG *pCmosCfg);

/**
 * @brief Cmos_9P031_130W_Para_Init
 * @param pCmosCfg
 * @author Vincent
 * @date 2017/5/12
 * @note 卷帘曝光130W像素CMOS相关配置参数初始化
 */
void Cmos_9P031_130W_Para_Init(CMOS_CFG *pCmosCfg);

/**
 * @brief Cmos_9P031_500W_Para_Init
 * @param pCmosCfg
 * @author Vincent
 * @date 2017/5/12
 * @note 卷帘曝光500W像素CMOS相关配置参数初始化
 */
void Cmos_9P031_500W_Para_Init(CMOS_CFG *pCmosCfg);

#endif /* CMOS_9P031_H_ */
