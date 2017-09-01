/**
  * @file  [PixelConvert.h]
  * @brief 像素、亚像素、ROI转换
  * @author  <Terry>
  * @date  <2017/06/03>
  * @version  <v1.0>
  * @note
  *
  */

#ifndef PIXEL_CONVERT_H
#define PIXEL_CONVERT_H

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */
#include "BaseStruct.h"

/* 数据转换类型 */
#define CVT_VGA2SUB     0x01    ///VGA转亚像素
#define CVT_SUB2VGA     0x02    ///亚像素转VGA
#define CVT_VGA2REAL    0x03    ///VGA转实际像素
#define CVT_REAL2VGA    0x04    ///实际像素转VGA
#define CVT_REAL2SUB    0x05    ///实际像素转亚像素
#define CVT_SUB2REAL    0x06    ///亚像素转实际像素
#define CVT_PIX_MASK    0xff

/* 数据类型 */
#define CVT_I2I         0x1000  ///src:整形数 dst:整形数
#define CVT_I2F         0x2000  ///src:整形数 dst:浮点数
#define CVT_F2F         0x3000  ///src:浮点数 dst:浮点数
#define CVT_F2I         0x4000  ///src:浮点数 dst:整形数
#define CVT_D2D			0x5000	///src:double dst:double
#define CVT_D2I			0x6000  ///src:double dst:整形数
#define CVT_D2F			0x7000  ///src:double dst:浮点数
#define CVT_F2D			0x8000  ///src:浮点数 dst:double
#define CVT_I2D			0x9000  ///src:整形数 dst:double
#define CVT_DATA_MASK   0xff00

/* 指针类型 */
#define CVT_POINT           0x100000    ///src,dst为POINT_X结构体指针
#define CVT_DATA            0x200000    ///src,dst为普通数据指针
#define CVT_POINTER_MASK    0xff0000

/**
 * @brief 通用的转换接口
 * @param pSrc:源数据指针
 * @param pDst:目标数据指针
 * @param cvt_flag:转换参数组合标志
 * @return
 * @author <Terry>
 * @note
 */
int PixelCvt(void *pSrc, void *pDst, unsigned int cvt_flag);

/**
 * @brief 多数据通用的转换接口
 * @param pSrc:源数据指针
 * @param pDst:目标数据指针
 * @param num:待转换数据个数
 * @param cvt_flag:转换参数组合标志
 * @return
 * @author <Terry>
 * @note
 */
int PixelCvtMulti(void *pSrc, void *pDst, unsigned int num, unsigned int cvt_flag);
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif // PIXEL_CONVERT_H
