/**
  * @file  [PolygonTool.h]
  * @brief  PolygonTool
  * @author  <szj>
  * @date  <2017/05/08>
  * @version  <1.0>
  * @note
  * detailed  description
  */
#ifndef POLYGONTOOL_H
#define POLYGONTOOL_H


#include <QObject>
#include <QPoint>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>

/**
  * @class  <PolygonTool>  [PolygonTool.h]  [PolygonTool]
  * @brief  多边形OSD工具
  * @author  <szj>
  * @note
  * detailed  description
  */
class PolygonTool
{
public:

    bool flagOrNot;
    bool bSelect;
    int m_current_point_num;
    int m_selectType;
    QPoint m_point[8];
    QRect m_rect_point[8];
    int m_start_x;
    int m_end_x;
    int m_start_y;
    int m_end_y;
    void *m_pen;
    PolygonTool();
    /**
     * @brief AddPoint
     * @author szj
     * @date 2017/05/08
     * @note 增加多边形点
     */
    void AddPoint();
    /**
     * @brief Subpoint
     * @param name 任务名称
     * @author szj
     * @date 2017/05/08
     * @note 减少多边形点
     */
    void Subpoint();
    /**
     * @brief IniPoint
     * @param index 多边形点集合位置
     * @param x 多边点x坐标
     * @param y 多边点y坐标
     * @author szj
     * @date 2017/05/08
     * @note 初始化多边形点位置
     */
    void IniPoint(int index,int x, int y);
    /**
     * @brief UpAdjust
     * @param index 多边形点集合位置
     * @author szj
     * @date 2017/05/08
     * @note 多边形点上移
     */
    void UpAdjust(int index);
    /**
     * @brief DownAdjust
     * @param index 多边形点集合位置
     * @author szj
     * @date 2017/05/08
     * @note 多边形点下移
     */
    void DownAdjust(int index);
    /**
     * @brief LeftAdjust
     * @param index 多边形点集合位置
     * @author szj
     * @date 2017/05/08
     * @note 多边形点左移
     */
    void LeftAdjust(int index);
    /**
     * @brief RightAdjust
     * @param index 多边形点集合位置
     * @author szj
     * @date 2017/05/08
     * @note 多边形点右移
     */
    void RightAdjust(int index);

public:
    void mouse_PressEvent(QMouseEvent *e);
    void mouse_MoveEvent(QMouseEvent *e);
    void mouse_ReleaseEvent(QMouseEvent *e);
    void paint_Event(QPainter *e);
private:
    QRect m_move_rect;
    QPoint startPoint;

    void FindMoveRect();
    void SetPen(QPen *pen, void *pdata);
};

#endif // POLYGONTOOL_H
