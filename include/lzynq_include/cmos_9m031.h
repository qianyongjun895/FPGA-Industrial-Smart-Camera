/******************************************************************************

                  版权所有 (C), 2015, SSZN

 ******************************************************************************
  文 件 名   : cmos_9m031.h
  版 本 号   : 初稿
  作    者   : Vincent
  生成日期   : 2016年1月29日
  最近修改   :
  功能描述   : cmos_9m031.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2016年1月29日
    作    者   : Vincent
    修改内容   : 创建文件

******************************************************************************/
#ifndef __CMOS_9M031_H__
#define __CMOS_9M031_H__
/*----------------------------------------------*
 * 包含头文件                                   *
 *----------------------------------------------*/
#include "cmos_common.h"
/*----------------------------------------------*
 * 宏定义                                       *
 *----------------------------------------------*/
#define CMOS_9M031_I2C_DEV_ADDR     0x00000020
#define EXPOSURE_INIT_9M031         12000
/*----------------------------------------------*
 * 外部变量说明                                  *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 全局变量                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 常量定义                                     *
 *----------------------------------------------*/



#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/**
 * @brief Cmos_9m031_Init
 * @param pixel_config
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 黑白全局曝光CMOS初始化函数
 */
extern int Cmos_9m031_Init(unsigned int pixel_config);

/**
 * @brief Cmos_9M031_Set_Exposure
 * @param texp
 * @author Vincent
 * @date 2017/5/12
 * @note 全局曝光相机曝光设置函数
 */
extern void Cmos_9M031_Set_Exposure(unsigned int texp);

/**
 * @brief Cmos_9M031_Set_Gain
 * @param num
 * @author Vincent
 * @date 2017/5/12
 * @note 全局曝光相机增益设置函数
 */
extern void Cmos_9M031_Set_Gain(unsigned int num);

/**
 * @brief Cmos_9m031_30W_Para_Init
 * @param pCmosCfg
 * @author Vincent
 * @date 2017/5/12
 * @note 黑白全局相机30W像素CMOS相关参数初始化
 */
extern void Cmos_9m031_30W_Para_Init(CMOS_CFG *pCmosCfg);

/**
 * @brief Cmos_9m031_130W_Para_Init
 * @param pCmosCfg
 * @author Vincent
 * @date 2017/5/12
 * @note 黑白全局相机130W像素CMOS相关参数初始化
 */
extern void Cmos_9m031_130W_Para_Init(CMOS_CFG *pCmosCfg);

/**
 * @brief Cmos_9M031_Filp_Mode_Set
 * @param flip_mode
 * @author Vincent
 * @date 2017/5/12
 * @note 设置黑白全局CMOS图像翻转模式
 */
void Cmos_9M031_Filp_Mode_Set(unsigned int flip_mode);

/**
 * @brief Cmos_9M031_130w_Y_Clip_Set
 * @param startY
 * @param height
 * @author Vincent
 * @date 2017/5/12
 * @note 设置黑白全局130W像素CMOS采集图像Y方向的裁剪参数
 */
void Cmos_9M031_130w_Y_Clip_Set(unsigned short startY, unsigned short height);

/**
 * @brief Cmos_9M031_30w_Y_Clip_Set
 * @param startY
 * @param height
 * @author Vincent
 * @date 2017/5/12
 * @note 设置黑白全局30W像素CMOS采集图像Y方向的裁剪参数
 */
void Cmos_9M031_30w_Y_Clip_Set(unsigned short startY, unsigned short height);

/**
 * @brief Cmos_9M031_130W
 * @author Vincent
 * @date 2017/5/12
 * @note 130W黑白全局曝光初始化函数
 */
void Cmos_9M031_130W(void);

/**
 * @brief Cmos_9M031_30W
 * @author Vincent
 * @date 2017/5/12
 * @note 30W黑白全局曝光初始化函数
 */
void Cmos_9M031_30W(void);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __CMOS_9M031_H__ */
