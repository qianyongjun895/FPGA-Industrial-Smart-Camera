/**
  * @file  [LibInitFun.h]
  * @brief
  * @author  <szj>
  * @date  <2017/05/09>
  * @version  <1.0>
  * @note
  * detailed  description
  */
#ifndef LIBINITFUN_H
#define LIBINITFUN_H
#include "BaseLibInterface.h"

/**
  * @class  <LibInitFun>  [LibInitFun.h]  [LibInitFun]
  * @brief  相机初始化dll接口
  * @author  <szj>
  * @note
  * detailed  description
  */
class LibInitCamera :public BaseLibInterface
{
public:
    LibInitCamera();
    /**
     * @brief IniCamera
     * @author szj
     * @date 2017/05/08
     * @note 初始化相机参数
     */
    int IniCamera();
    /* 曝光 */
    void Set_Exposure(int value);
    /* 增益 */
    void Set_Gain(int value);

    /**
     * @brief Set_CMOS_Capture_Y_Clip
     * @param start_y
     * @param height
     * @return
     * @author Vincent
     * @date 2017/5/12
     * @note 调用相机图像Y方向裁剪函数
     */
     int Set_CMOS_Capture_Y_Clip(unsigned int start_y, unsigned int height);


    /**
     * @brief Get_Exposure_Init
     * @return
     * @author Vincent
     * @date 2017/5/19
     * @note 获取曝光初始值
     */
     unsigned int Get_Exposure_Init();

    /**
     * @brief Get_Exposure_Max
     * @return
     * @author Vincent
     * @date 2017/5/19
     * @note 获取曝光最大值
     */
     unsigned int Get_Exposure_Max();

    /**
     * @brief Get_Exposure_Min
     * @return
     * @author Vincent
     * @date 2017/5/19
     * @note 获取exposure_min
     */
     unsigned int Get_Exposure_Min();

};

#endif // LIBINITFUN_H
