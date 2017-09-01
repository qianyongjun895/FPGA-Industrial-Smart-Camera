/******************************************************************************

                  版权所有 (C), 2015, SSZN

 ******************************************************************************
  文 件 名   : cmos_common.h
  版 本 号   : 初稿
  作    者   : Vincent
  生成日期   : 2016年1月29日
  最近修改   :
  功能描述   : cmos_common.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2016年1月29日
    作    者   : Vincent
    修改内容   : 创建文件

******************************************************************************/
#ifndef CMOS_COMMON_H_
#define CMOS_COMMON_H_
/*----------------------------------------------*
 * 包含头文件                                   *
 *----------------------------------------------*/
#include "BaseStruct.h"
#include "define.h"
/*----------------------------------------------*
 * 宏定义                                       *
 *----------------------------------------------*/
/* Following sensor macro define the type of CMOS type */
#define CMOS_9M021C		1
#define CMOS_9M031		2
#define CMOS_9P031		3
#define CMOS_TYPE_MAX	3	/* any new type add before max, increase this MACRO */


/*
 * Bit Information for FPGA CMOS configuration
[0]: 1= 7.5w像素
[1]: 1= 30w像素
[2]: 1= 130w像素
[3]: 1= 200w像素
[4]: 1= 500w像素
[16]: 0=Global Shutter, 1=Rolling Shutter
*/
#define FPGA_CMOS_SPEC_ADDR		0x10fc
#define MASK_PIXEL_7P5W			0x1
#define MASK_PIXEL_30W			0x2
#define MASK_PIXEL_130W			0x4
#define MASK_PIXEL_200W			0x8
#define MASK_PIXEL_500W			0x10
#define MASK_SHUTTER_MOD		0x10000

#define MULTIPLE_ROLLING_30W    16.04
#define MULTIPLE_ROLLING_130W   22.71
#define MULTIPLE_ROLLING_500W   36.04
#define MULTIPLE_GLOBAL_30W     19.7
#define MULTIPLE_GLOBAL_130W    21.3
#define CMOS_9m021c_30W         19.7
#define CMOS_9m021c_130W        21.3

#define R0x3012_30W_MAX         0x1f7
#define R0x3014_30W_MAX         0x2a8
#define R0x3012_130W_MAX        0x3e3
#define R0x3014_130W_MAX        0x38c

/* 彩色黑白相机宏定义 */
#define CAMERA_MONO             0x0
#define CAMERA_COLOR            0x1

/* 曝光模式 */
#define ROLLING_SHUTTER			0x0
#define GLOBAL_SHUTTER			0x1

/* 图像翻转宏定义 */
#define IMAGE_NORMAL            0x0
#define IMAGE_UP_DOWN_INVERT    0x1
#define IMAGE_LEFT_RIGHT_INVERT 0x2
#define IMAGE_TWO_DIR_INVERT    0x3

/* 实际图像与VGA图像大小比例 */
#define VGA2REAL_FACTOR_30W         1
#define VGA2REAL_FACTOR_130W        2
#define VGA2REAL_FACTOR_500W        4

/*----------------------------------------------*
 * 外部变量说明                                 *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 全局变量                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 常量定义                                     *
 *----------------------------------------------*/
typedef int (*cmos_config_func)(unsigned int);
typedef void (*cmos_capture_break)(void);
typedef void (*cmos_set_gain)(unsigned int);
typedef void (*cmos_set_exposure)(unsigned int);
typedef void (*Cmos_Capture_Y_Clip)(unsigned short, unsigned short);
typedef void (*cmos_image_flip)(unsigned int);

typedef struct {
    unsigned int sensor_type;               ///<  CMOS型号 1:MT9M031I12STC(彩色全局)，2:MT9M031I12STM(黑白全局)，3:MT9P031(黑白卷帘)，4:SN5000A(高速黑白全局)
    unsigned int shutter_mode;              ///<  曝光方式 1表示全局快门，0表示卷帘快门
    unsigned int color_type;                ///<  色彩模式 1表示彩色相机，0表示黑白相机
    unsigned int pixel_size;                ///<  像素大小 0x02表示30W像素，0x04表示130W像素，0x10表示500W像素
    unsigned int fpga_type;                 ///<  FPGA版本信息 例:0x17020510表示版本号为2017年02月05日10点(24小时制)
    unsigned int pixel_width;               ///<  像素宽度
    unsigned int pixel_height;              ///<  像素高度
    unsigned int vga2real_factor;           ///<  VGA图像与实际像素比
    unsigned int vga2sub_factor;            ///<  VGA图像与亚像素比
    unsigned int real2sub_factor;           ///<  实际像素与亚像素比
    float exposure_multiple;                ///<  曝光倍数
    unsigned int exposure_init;             ///<  曝光初始值
    unsigned int exposure_min;              ///<  曝光最小值
    unsigned int exposure_max;              ///<  曝光最大值
    unsigned int global_high_max;           ///<  全局曝光高位最大值
    unsigned int global_low_max;            ///<  全局曝光低位最大值
    cmos_config_func fpCmosConfigFunc;      ///<  CMOS初始化函数
    cmos_capture_break fpCmosCaptureBreak;  ///<  采图中断函数
    cmos_set_gain fpCmosSetGain;            ///<  相机增益设置函数
    cmos_set_exposure fpCmosSetExposure;    ///<  相机曝光设置函数
    cmos_image_flip fpCmosImageFlip;        ///<  相机图像翻转函数
    Cmos_Capture_Y_Clip fpCmosCaptureYClip; ///<  相机图像裁剪函数
}CMOS_CFG;
extern CMOS_CFG gCmosCfg;
extern CMOS_CFG *pgCmosCfg;

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief Cmos_Sensor_Type_Get
 * @return 1:MT9M031I12STC(彩色全局)，2:MT9M031I12STM(黑白全局)，3:MT9P031(黑白卷帘)，4:SN5000A(高速黑白全局)，
 * @author Vincent
 * @date 2017/5/12
 * @note Sensor类型获取函数
 */
unsigned int Cmos_Sensor_Type_Get(void);

/**
 * @brief Cmos_Pixel_Config_Type_Get
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 获取相机像素型号
 */
unsigned int Cmos_Pixel_Config_Type_Get(void);

/**
 * @brief Cmos_Sensor_Color_Type_Get
 * @return 1表示彩色相机，0表示黑白相机
 * @author Vincent
 * @date 2017/5/12
 * @note Sensor颜色类型获取函数
 */
unsigned int Cmos_Sensor_Color_Type_Get(void);

/**
 * @brief Cmos_Config_Init
 * @return 0: 成功 -1: 失败
 * @author Vincent
 * @date 2017/5/12
 * @note CMOS配置参数初始化
 */
int Cmos_Config_Init(void);

/**
 * @brief Set_HWC_CMOS_Config_Init
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 调用CMOS初始化函数
 */
DLLSHARED_EXPORT int Set_HWC_CMOS_Config_Init(void);

/**
 * @brief Set_HWC_CMOS_Capture_Break
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 调用CMOS采图中断函数
 */
DLLSHARED_EXPORT int Set_HWC_CMOS_Capture_Break(void);

/**
 * @brief Set_HWC_CMOS_Gain
 * @param cmos_gain
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 调用设置CMOS增益的函数
 */
DLLSHARED_EXPORT int Set_HWC_CMOS_Gain(unsigned int cmos_gain);

/**
 * @brief Set_HWC_CMOS_Exposure
 * @param exposure
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 调用设置CMOS曝光的函数
 */
DLLSHARED_EXPORT int Set_HWC_CMOS_Exposure(unsigned int exposure);

/**
 * @brief Get_HWC_Sensor_Type
 * @return 1:MT9M031I12STC(彩色全局)，2:MT9M031I12STM(黑白全局)，3:MT9P031(黑白卷帘)，4:SN5000A(高速黑白全局)，
 * @author Vincent
 * @date 2017/5/12
 * @note Sensor类型获取函数
 */
DLLSHARED_EXPORT unsigned int Get_HWC_Sensor_Type(void);

/**
 * @brief Get_HWC_Fpga_Type
 * @return 例:0x17020510表示版本号为2017年02月05日10点(24小时制)
 * @author Vincent
 * @date 2017/5/12
 * @note FPGA类型获取函数
 */
DLLSHARED_EXPORT unsigned int Get_HWC_Fpga_Type(void);

/**
 * @brief Get_HWC_Pixel_Size
 * @return 0x02表示30W像素，0x04表示130W像素，0x10表示500W像素
 * @author Vincent
 * @date 2017/5/12
 * @note 获取相机Sensor像素型号
 */
DLLSHARED_EXPORT unsigned int Get_HWC_Pixel_Size(void);

/**
 * @brief Get_HWC_Color_Type
 * @return 1表示彩色相机，0表示黑白相机
 * @author Vincent
 * @date 2017/5/12
 * @note Sensor颜色类型获取函数
 */
DLLSHARED_EXPORT unsigned int Get_HWC_Color_Type(void);

/**
 * @brief Get_HWC_Shutter_Mode
 * @return 1表示全局快门，0表示卷帘快门
 * @author Vincent
 * @date 2017/5/12
 * @note 获取相机Sensor类型: 卷帘/全局
 */
DLLSHARED_EXPORT unsigned int Get_HWC_Shutter_Mode(void);

/**
 * @brief Get_HWC_Pixel_Width
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 获取相机图像像素宽度
 */
DLLSHARED_EXPORT unsigned int Get_HWC_Pixel_Width(void);

/**
 * @brief Get_HWC_Pixel_Height
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 获取相机图像像素高度
 */
DLLSHARED_EXPORT unsigned int Get_HWC_Pixel_Height(void);

/**
 * @brief Get_HWC_Vga2Real_Factor
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 获取VGA图像与实际像素比
 */
DLLSHARED_EXPORT unsigned int Get_HWC_Vga2Real_Factor(void);

/**
 * @brief Get_HWC_Vga2Sub_Factor
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 获取VGA图像与亚像素比
 */
DLLSHARED_EXPORT unsigned int Get_HWC_Vga2Sub_Factor(void);

/**
 * @brief Get_HWC_Real2Sub_Factor
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 获取实际像素与亚像素比
 */
DLLSHARED_EXPORT unsigned int Get_HWC_Real2Sub_Factor(void);

/**
 * @brief Set_HWC_CMOS_Capture_Y_Clip
 * @param start_y
 * @param height
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 调用相机图像Y方向裁剪函数
 */
DLLSHARED_EXPORT int Set_HWC_CMOS_Capture_Y_Clip(unsigned int start_y, unsigned int height);


/**
 * @brief Set_HWC_CMOS_Flip
 * @param flip_mode
 * @return
 * @author Vincent
 * @date 2017/6/27
 * @note 调用相机图像翻转函数
 */
DLLSHARED_EXPORT int Set_HWC_CMOS_Flip(unsigned int flip_mode);


/**
 * @brief Get_HWC_Exposure_Init
 * @return
 * @author Vincent
 * @date 2017/5/19
 * @note 获取曝光初始值
 */
DLLSHARED_EXPORT unsigned int Get_HWC_Exposure_Init(void);

/**
 * @brief Get_HWC_Exposure_Max
 * @return
 * @author Vincent
 * @date 2017/5/19
 * @note 获取曝光最大值
 */
DLLSHARED_EXPORT unsigned int Get_HWC_Exposure_Max(void);

/**
 * @brief Get_HWC_Exposure_Min
 * @return
 * @author Vincent
 * @date 2017/5/19
 * @note 获取exposure_min
 */
DLLSHARED_EXPORT unsigned int Get_HWC_Exposure_Min(void);

/**
 * @brief Get_HWC_Exposure_Multiple
 * @return
 * @author Vincent
 * @date 2017/5/19
 * @note 获取曝光倍数
 */
DLLSHARED_EXPORT float Get_HWC_Exposure_Multiple(void);

/**
 * @brief Get_HWC_Global_High_Max
 * @return
 * @author Vincent
 * @date 2017/5/19
 * @note 获取全局曝光高位最大值
 */
DLLSHARED_EXPORT unsigned int Get_HWC_Global_High_Max(void);

/**
 * @brief Get_HWC_Global_Low_Max
 * @return
 * @author Vincent
 * @date 2017/5/19
 * @note 获取全局曝光低位最大值
 */
DLLSHARED_EXPORT unsigned int Get_HWC_Global_Low_Max(void);


#ifdef __cplusplus
}
#endif
#endif /* CMOS_COMMON_H_ */

