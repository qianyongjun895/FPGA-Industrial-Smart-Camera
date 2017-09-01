/**
  * @file  [ResolveRunData.h]
  * @brief  ResolveRunData
  * @author  <dgq>
  * @date  <2017/5/23>
  * @version  <1.0>
  * @note  获取Blob运行数据
  * detailed  description
  */
#ifndef RESOLVERUNDATA_H
#define RESOLVERUNDATA_H

#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QLabel>
#include <QVector>
#include "BasicDefine.h"
#include "BlobGlobal.h"


class ResolveRunData
{
public:
    explicit ResolveRunData();
    ~ResolveRunData();

    /**
     * @brief Paint
     * @param paint QPainter指针
     * @param step步骤号
     * @author dgq
     * @note 运行时画OSD，运行时需要画OSD的工具需要实现的接口
     */
    void Paint(QPainter *paint,int step,void *penStyle,int paintAreaSelect);

    /**
     * @brief GetHead
     * @param step 步骤号
     * @return 运行时的通用输出数据
     * @author dgq
     * @note 运行时获取通用输出数据的接口，按照固定格式将数据填入QVector中
     */
    QVector<STRU_KEY_VALUE> GetHead(int step);

    /**
     * @brief GetContent
     * @param step 步骤号
     * @return 运行时本步骤特有的输出数据
     * @author dgq
     * @note 运行时获取本步骤特有的输出数据，按照固定格式将数据填入QVector中
     */
    QVector<STRU_KEY_VALUE> GetContent(int step, int index, int *count);

    int ClearOsdData();

private:
    int m_Point_cnt;//blob总数
    int m_ok_ng_flag;//ok\ng标志
    QVector<QPoint> Blob_Pix_Center;
    QVector<QPoint> Blob_Real_Center;
    QVector<QPoint> Blob_Phy_Center;
    QVector<unsigned int> Blob_Area;
    QVector<float> Blob_Theta;
    QVector<float> Blob_Angle;
    QVector<float> Blob_Rotate_Theta;
    QVector<float> Blob_Rotate_Angle;
    QVector<float> Blob_Ratio;
    QVector<float> Blob_Width;
    QVector<float> Blob_Height;
    int m_ok_cnt;
    int m_ng_cnt;
    int m_excute_flag;

    /**
     * @brief DrawArrow
     * @param painter QPainter指针
     * @param lastPoint 箭头的起点
     * @param endPoint 箭头的终点
     * @param iArrowLen 箭头长度
     * @author szj
     * @note 画blob长轴方向的箭头
     */
    void DrawArrow(QPainter *painter, QPoint lastPoint, QPoint endPoint, float iArrowLen);


    void GetPreData(QPainter *paint, int iStep, int iSwitch);
    void GetRoiData(QPainter *paint, SELECT_AREA_PARAM del_model);
    void DrawPolygon(QPainter *paint, OCTAGON_CFG_PARA points);
    void DrawRing(QPainter *paint, CIRCULAR ring);
};

#endif // RESOLVERUNDATA_H
