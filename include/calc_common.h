/*
 * calc_common.h
 *
 *  Created on: 2016-1-13
 *      Author: terry
 */

#ifndef CALC_COMMON_H_
#define CALC_COMMON_H_
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */
#include "BaseStruct.h"

#define POWER2_30	1073741824
#define POWER2_32	4294967296
int i_max(int a,int b);
int i_min(int a, int b);
float f_max(float a, float b);
float f_min(float a, float b);

/**
 * @brief CHECK_BIT_1_OR_0
 * @param data
 * @param index
 * @return
 * @author Terry
 * @date 2017/5/12
 * @note 检查unsigned int型的数据对应的bit位为0还是为1
 */
unsigned int CHECK_BIT_1_OR_0(unsigned int data, unsigned int index);

/**
 * @brief First_0_Bit_Search
 * @param data
 * @return
 * @author Terry
 * @date 2017/5/12
 * @note 查找第一个为0的bit位，返回对应偏移
 */
int First_0_Bit_Search(unsigned int data);

/**
 * @brief First_1_Bit_Search
 * @param data
 * @return
 * @author Terry
 * @date 2017/5/12
 * @note 查找第一个为1的bit位，返回对应偏移
 */
int First_1_Bit_Search(unsigned int data);

unsigned int Get_Fisrt_Bit_Set(unsigned int data);

/**
 * @brief Points_Distance_Float
 * @param pfpoint1 点1坐标的指针
 * @param pfpoint2 点2坐标的指针
 * @param pDistance 存放计算结果的指针
 * @author Terry
 * @date 2017/5/12
 * @note 计算两点间的距离（float型）
 */
void Points_Distance_Float(POINT_F *pfpoint1, POINT_F *pfpoint2, double *pDistance);

/**
 * @brief degree_Adjust_To_180
 * @param degree_ori 原角度
 * @param pDegreeAdj 转换后的角度
 * @author Terry
 * @date 2017/5/12
 * @note 把角度转换为+/-180范围内的角度
 */
void degree_Adjust_To_180(double degree_ori, double *pDegreeAdj);

/**
 * @brief Theta_to_Degree
 * @param theta 弧度值
 * @param pDegree 转换后的角度值
 * @author Terry
 * @date 2017/5/12
 * @note 将弧度转换为角度
 */
void Theta_to_Degree(double theta, double *pDegree);

/**
 * @brief Points_Degree_Float
 * @param pfpoint1 点1指针
 * @param pfpoint2 点2指针
 * @param pDegree 计算后的角度
 * @author Terry
 * @date 2017/5/12
 * @note  计算两点形成线段的角度是以 点1 为旋转中心，点2与点1构成线段与水平方向的夹角
 * 本函数返回的为角度值
 */
void Points_Degree_Float(POINT_F *pfpoint1, POINT_F *pfpoint2, double *pDegree);

/**
 * @brief Points_Theta_Float
 * @param pfcenter
 * @param pfpoint
 * @param pTheta
 * @author Vincent
 * @date 2017/5/12
 * @note 计算两点形成线段的角度是以 点1 为旋转中心，点2与点1构成线段与水平方向的弧度
 * 本函数返回的为弧度值
 */
void Points_Theta_Float(POINT_F *pfcenter, POINT_F *pfpoint, double *pTheta);

/**
 * @brief uchar_sort
 * @param a
 * @param left
 * @param right
 * @author Terry
 * @date 2017/5/12
 * @note 排序算法
 */
void uchar_sort(unsigned char *a, int left, int right);

/**
 * @brief bool_point_inside_check
 * @param SelectRange 矩形框参数
 * @param check_point 判断的点坐标
 * @return 1：点在框内 0：点不在框内
 * @author Terry
 * @date 2017/5/12
 * @note 判断点坐标是否在矩形框内部
 */
int bool_point_inside_check(OSD_POLYGON *SelectRange, POINT_I *check_point);

/**
 * @brief rotate_range_extend
 * @param OriRange 旋转矩形
 * @param ExtRange 外切矩形
 * @param theta 旋转矩形框弧度
 * @author Terry
 * @date 2017/5/12
 * @note 获取旋转矩形的外切矩形
 */
void rotate_range_extend(OSD_POLYGON *OriRange, OSD_POLYGON *ExtRange, float theta);

/**
 * @brief Rotate_Para_Calc
 * @param pCenterPoint 中心点
 * @param pRotatePoints 旋转点数组指针
 * @param point_num 旋转点个数
 * @param pRotataPara 旋转参数
 * @author Terry
 * @date 2017/5/12
 * @note 计算point_num个旋转点与中心点之间的距离和角度关系
 */
void Rotate_Para_Calc(POINT_F *pCenterPoint, POINT_F *pRotatePoints, unsigned int point_num, ROTATE_PARA *pRotataPara);

/**
 * @brief Rotate_Points_Calc
 * @param pCenterPoint 旋转中心点
 * @param pRotatePoints 旋转点数组指针
 * @param point_num 点个数
 * @param pRotataPara 旋转参数
 * @param rotate_theta 旋转角度(弧度值)
 * @author Terry
 * @date 2017/5/12
 * @note 点绕旋转中心旋转后的坐标计算
 */
void Rotate_Points_Calc(POINT_F *pCenterPoint, POINT_F *pRotatePoints, unsigned int point_num, ROTATE_PARA *pRotataPara, double rotate_theta);

/**
 * @brief Calc_Distance_Point2Line
 * @param pPoint 点坐标
 * @param pPointOnLine 直线上点坐标
 * @param line_theta 直线弧度值
 * @param pDistance 计算结果(距离)
 * @author Vincent
 * @date 2017/5/12
 * @note 计算点到线距离
 */
void Calc_Distance_Point2Line(POINT_F *pPoint, POINT_F *pPointOnLine, double line_theta, double *pDistance);

/**
 * @brief Calc_Cross_Point_2Lines
 * @param pPointOnLine1 直线1上的点坐标
 * @param pPointOnLine2 直线2上的点坐标
 * @param theta1 直线1的弧度值
 * @param theta2 直线2的弧度值
 * @param pCrossPoint 计算出的两线交点坐标
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 计算两线交点
 */
int Calc_Cross_Point_2Lines(POINT_F *pPointOnLine1, POINT_F *pPointOnLine2, double theta1, double theta2, POINT_F *pCrossPoint);

/**
 * @brief Coordinate_Rotate_Calc
 * @param pt1 点1指针
 * @param pt2 点2指针
 * @param pt2 点3指针
 * @param pR 半径指针
 * @param pCenter 圆心指针
 * @author Terry
 * @date 2017/8/9
 * @note 根据三个不在一条线上的点确定一个圆
 */
int Calc_Circle_By_3Points(POINT_F *pt1, POINT_F *pt2, POINT_F *pt3, float *pR, POINT_F *pCenter);

/**
 * @brief Coordinate_Rotate_Calc
 * @param OutPoint 旋转后的点坐标
 * @param ref_point 被旋转点坐标
 * @param ref_delt 旋转中心点
 * @param sin_a 旋转角度sin值
 * @param cos_a 旋转角度cos值
 * @author Vincent
 * @date 2017/5/12
 * @note 旋转坐标计算
 */
void Coordinate_Rotate_Calc(POINT_F *OutPoint, POINT_F *ref_point, POINT_F *ref_delt, float sin_a, float cos_a);

/**
 * @brief Point_Rotate_Calc
 * @param pPoint_Dst 旋转结果点的指针
 * @param pPoint_Org 被旋转点的指针
 * @param pRefPoint 新的旋转中心点指针
 * @param pRefOldPoint 旧的旋转中心点指针
 * @param sin_a 旋转角度的sin值
 * @param cos_a 旋转角度的cos值
 * @author Terry
 * @date 2017/5/12
 * @note 旋转点（int型）坐标计算
 * 输出结果是亚像素单位的，输入也是亚像素，其余的参考点都是亚像素单位
 */
void Point_Rotate_Calc(POINT_I *pPoint_Dst, POINT_I *pPoint_Org, POINT_F *pRefPoint, POINT_F *pRefOldPoint, float sin_a, float cos_a);

/**
 * @brief Point_Float_Rotate_Calc
 * @param pPoint_Dst 旋转结果点的指针
 * @param pPoint_Org 被旋转点的指针
 * @param pRefPoint 新的旋转中心点指针
 * @param pRefOldPoint 旧的旋转中心点指针
 * @param sin_a 旋转角度的sin值
 * @param cos_a 旋转角度的cos值
 * @author Terry
 * @date 2017/5/12
 * @note 旋转点（float型）坐标计算
 */
void Point_Float_Rotate_Calc(POINT_F *pPoint_Dst, POINT_F *pPoint_Org, POINT_F *pRefPoint, POINT_F *pRefOldPoint, float sin_a, float cos_a);

/**
 * @brief SinCos_Lut_Init
 * @author <Terry>
 * @note Initial Sin\Cos lookup table
 */
void SinCos_Lut_Init(void);

/**
 * @brief Sin_Lut_Search
 * @param degree:0.0-360.0
 * @return
 * @author <Terry>
 * @note Search Sin lookup table by degree
 */
void Sin_Lut_Search(float degree, float *pSinValue);

/**
 * @brief Sin_Lut_Search_Quick
 * @param degree:0-3600
 * @return
 * @author <Terry>
 * @note Search Sin lookup table by degree
 */
void Sin_Lut_Search_Quick(     int degree, float *pSinValue);

/**
 * @brief Cos_Lut_Search
 * @param degree:0.0-360.0
 * @return
 * @author <Terry>
 * @note Search Cos lookup table by degree
 */
void Cos_Lut_Search(float degree, float *pCosValue);

/**
 * @brief Cos_Lut_Search_Quick
 * @param degree:0-3600
 * @return
 * @author <Terry>
 * @note Search Cos lookup table by degree
 */
void Cos_Lut_Search_Quick(int degree, float *pCosValue);

/**
 * @brief ComparePointIByXdescend
 * @param _v0：点1指针
 * @param _v1：点2指针
 * @return 1: x0 < x1; -1: x0 > x1
 * @author <Terry>
 * @note Compare 2 POINT_I by X
 */
int ComparePointIByXdescend(const void * _v0, const void * _v1);

/**
 * @brief ComparePointIByXascend
 * @param _v0：点1指针
 * @param _v1：点2指针
 * @return 1: x0 > x1; -1: x0 < x1
 * @author <Terry>
 * @note Compare 2 POINT_I by X
 */
int ComparePointIByXascend(const void * _v0, const void * _v1);

/**
 * @brief ComparePointIByYdescend
 * @param _v0：点1指针
 * @param _v1：点2指针
 * @return 1: y0 < y1; -1: y0 > y1
 * @author <Terry>
 * @note Compare 2 POINT_I by Y
 */
int ComparePointIByYdescend(const void * _v0, const void * _v1);

/**
 * @brief ComparePointIByYascend
 * @param _v0：点1指针
 * @param _v1：点2指针
 * @return 1: y0 > y1; -1: y0 < y1
 * @author <Terry>
 * @note Compare 2 POINT_I by Y
 */
int ComparePointIByYascend(const void * _v0, const void * _v1);

/**
 * @brief ComparePointFByXdescend
 * @param _v0：点1指针
 * @param _v1：点2指针
 * @return 1: x0 < x1; -1: x0 > x1
 * @author <Terry>
 * @note Compare 2 POINT_F by X
 */
int ComparePointFByXdescend(const void * _v0, const void * _v1);

/**
 * @brief ComparePointsByXascend
 * @param _v0：点1指针
 * @param _v1：点2指针
 * @return 1: x0 > x1; -1: x0 < x1
 * @author <Terry>
 * @note Compare 2 POINT_F by X
 */
int ComparePointsByXascend(const void * _v0, const void * _v1);

/**
 * @brief ComparePointsByYdescend
 * @param _v0：点1指针
 * @param _v1：点2指针
 * @return 1: y0 < y1; -1: y0 > y1
 * @author <Terry>
 * @note Compare 2 POINT_F by Y
 */
int ComparePointsByYdescend(const void * _v0, const void * _v1);

/**
 * @brief ComparePointsByYascend
 * @param _v0：点1指针
 * @param _v1：点2指针
 * @return 1: y0 > y1; -1: y0 < y1
 * @author <Terry>
 * @note Compare 2 POINT_F by Y
 */
int ComparePointsByYascend(const void * _v0, const void * _v1);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif
