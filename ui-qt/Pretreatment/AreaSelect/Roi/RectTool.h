/**
  * @file  [RectTool.h]
  * @brief  RectTool
  * @author  <szj>
  * @date  <2017/05/08>
  * @version  <1.0>
  * @note
  * detailed  description
  */

#ifndef RECTTOOL_H
#define RECTTOOL_H

#include <QObject>
#include <QPoint>
#include <QLine>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QRectF>
/**
  * @class  <RectTool>  [RectTool.h]  [RectTool]
  * @brief  矩形osd工具
  * @author  <szj>
  * @note
  * detailed  description
  */
class RectTool
{
public:
    bool flagOrNot;
    bool bSelect;
    int m_start_x;
    int m_end_x;
    int m_start_y;
    int m_end_y;
    void *m_pen;
    RectTool();

    /**
     * @brief SetRect
     * @param rect 矩形osd参数
     * @param str  矩形osd标识ID
     * @author szj
     * @date 2017/05/08
     * @note 设置当前矩形osd
     */
    void SetRect(QRectF rect,QString str="");
    /**
     * @brief GetRect
     * @return 返回当前矩形osd
     * @author szj
     * @date 2017/05/08
     * @note 获取当前矩形osd
     */
    QRectF GetRect(){return m_Rect;}
    /**
     * @brief bSelectFun
     * @return 返回当前矩形osd是否选中
     * @author szj
     * @date 2017/05/08
     * @note 获取当前矩形osd是否选中
     */
    bool bSelectFun();
    /**
     * @brief UpAdjust
     * @param kind 1左上顶点，其他右下点
     * @param value 移动步进
     * @author szj
     * @date 2017/05/08
     * @note 矩形坐标点上移
     */
    void UpAdjust(int kind,int value =1);
    /**
     * @brief DownAdjust
     * @param kind 1左上顶点，其他右下点
     * @param value 移动步进
     * @author szj
     * @date 2017/05/08
     * @note 矩形坐标点下移
     */
    void DownAdjust(int kind,int value=1);
    /**
     * @brief LeftAdjust
     * @param kind 1左上顶点，其他右下点
     * @param value 移动步进
     * @author szj
     * @date 2017/05/08
     * @note 矩形坐标点左移
     */
    void LeftAdjust(int kind,int value=1);
    /**
     * @brief RightAdjust
     * @param kind 1左上顶点，其他右下点
     * @param value 移动步进
     * @author szj
     * @date 2017/05/08
     * @note 矩形坐标点右移
     */
    void RightAdjust(int kind,int value=1);

public:
    void mouse_PressEvent(QMouseEvent *e);
    void mouse_MoveEvent(QMouseEvent *e);
    void mouse_ReleaseEvent(QMouseEvent *e);
    void paint_Event(QPainter *painter);

private:
    QRectF m_Rect;
    QString m_str_id;
    QRectF m_RectPoint[2];
    QPointF m_press_point;
    int curt_Area;
    int scalePoint;
    void updateMovePointRect();
    void SetPen(QPen *pen,void *pdata);
};

#endif
