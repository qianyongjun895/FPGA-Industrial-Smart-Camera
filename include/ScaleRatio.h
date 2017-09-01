#ifndef __SCALECALIBRATION_H__
#define __SCALECALIBRATION_H__

#include "BaseStruct.h"

#ifndef EPSINON
#define EPSINON 0.000001
#endif

#define SCALE_RATIO_PARAM_MAX 128

typedef struct {
    unsigned int count;
    double ratio[SCALE_RATIO_PARAM_MAX];
} SCALE_RATIO;

typedef struct {
    POINT_I vga_point[2];
    double phy_dist;
} SCALE_RATIO_INPUT;

typedef struct {
    double ratio;
} SCALE_RATIO_OUTPUT;

typedef struct {
    unsigned int unuse;
} SCALE_RATIO_PRIVATE;

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/**
 * @brief 获取两点的亚像素距离
 * @param subPixDist 指针参数，接收亚像素距离
 * @return
 * @author <AutumnX>
 * @note
 */
void GetSubPixDist(double* subPixDist);

/**
 * @brief 计算像素比
 * @param
 * @return
 * @author <AutumnX>
 * @note 计算结果保存于 SCALE_CALIBRATE_OUTPUT 的 ratio 中
 */
void CalcScaleRatio(void);

/**
 * @brief 获取像素比
 * @param scaleRatio 指针参数，接收像素比
 * @return
 * @author <AutumnX>
 * @note 本接口会调用 CalcScaleRatio(),所以不必调用本接口前再调用计算像素比的函数
 */
void GetScaleRatio(double* scaleRatio);

/**
 * @brief 保存像素比
 * @param index 像素比索引 范围[0,127]
 * @param ratio 像素比
 * @return
 * @author <AutumnX>
 * @note 调用此函数会分别保存像素比到内存和文件中
 */
void SaveScaleRatio(unsigned int index, double ratio);

/**
 * @brief 获取像素比
 * @param index 要获取的像素比索引 范围[0,127]
 * @return 像素比
 * @author <AutumnX>
 * @note
 */
double GetScaleRatioByIndex(unsigned int index);

/**
 * @brief 获取像素比
 * @param index 要获取的像素比索引 范围[0,127]
 * @param ratio 指针参数，用于接收像素比
 * @return
 * @author <AutumnX>
 * @note
 */
void GetScaleRatioByIndex2(unsigned int index, double* ratio);

/**
 * @brief Pixel_Physics_Convert
 * @param scale_cali_index 刻度校准参数索引
 * @param pixel_len 像素长度值
 * @param phy_len 实际长度值
 * @author Terry
 * @date 2017/5/12
 * @note 像素长度通过刻度校准后的比例参数转换为实际长度
 */
void Pixel_Physics_Convert(unsigned int scale_cali_index, double pixel_len, double *phy_len);

/**
 * @brief 获取像素比参数信息指针
 * @param
 * @return 返回像素比参数信息指针
 * @author <AutumnX>
 * @note
 */
SCALE_RATIO* GetScaleRatioInfo(void);

/**
 * @brief 像素比参数套数加1
 * @param
 * @return
 * @author <AutumnX>
 * @note
 */
void ScaleRatioParamCountInc(void);

/**
 * @brief 像素比参数套数减1
 * @param
 * @return
 * @author <AutumnX>
 * @note
 */
void ScaleRatioParamCountDec(void);

/**
 * @brief 获取像素比参数套数
 * @param
 * @return 像素比参数套数
 * @author <AutumnX>
 * @note
 */
unsigned int GetScaleRatioParamCount(void);

/**
 * @brief 保存像素比参数到文件里
 * @param
 * @return
 * @author <AutumnX>
 * @note
 */
int ScaleRatioInfoSaveToFile(void);

/**
 * @brief 从文件里载入像素比参数套数
 * @param
 * @return
 * @author <AutumnX>
 * @note
 */
int ScaleRatioInfoLoadFromFile(void);

/**
 * @brief 设置 VGA 点坐标
 * @param index 点索引 范围[0,1]
 * @param x 点的 x 坐标
 * @param y 点的 y 坐标
 * @return
 * @author <AutumnX>
 * @note
 */
void SetScaleRatioVgaPoint(unsigned int index, int x, int y);

/**
 * @brief 设置物理距离
 * @param phyDist 物理距离
 * @return
 * @author <AutumnX>
 * @note
 */
void SetScaleRatioPhyDist(double phyDist);

/**
 * @brief 删除像素比参数
 * @param index 要删除的像素比参数索引 范围[0,127]
 * @return
 * @author <AutumnX>
 * @note
 */
void DeleteScaleRatioParam(unsigned int index);

/************************* 以下函数独立于以上所有函数，不参与已设定的16套像素比参数的处理 ***************************/

/**
 * @brief 获取两点的亚像素距离
 * @param x0,y0,x1,y1 VGA点坐标
 * @param subPixelDist 指针参数，接收亚像素距离
 * @return 0:成功 其它：失败
 * @author <AutumnX>
 * @note
 * 输入两个VGA点坐标，可获得两点的亚像素距离
 */
int Get_Subpixel_Distance(int x0, int y0, int x1, int y1, double *subPixelDist);

/**
 * @brief 获取像素比
 * @param x0,y0,x1,y1 VGA点坐标
 * @param phyDist 物理距离
 * @param ratio 指针参数，接收像素比
 * @return 0:成功 其它：失败
 * @author <AutumnX>
 * @note
 * 输入两个VGA点坐标，并输入物理距离，可获得一个像素比参数
 */
int Get_Scale_Ratio(int x0, int y0, int x1, int y1, double phyDist, double *ratio);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __SCALECALIBRATION_H__ */
