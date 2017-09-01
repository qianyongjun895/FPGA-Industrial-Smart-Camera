#ifndef RINGTOOL_H
#define RINGTOOL_H

#include <QObject>
#include <QPoint>
#include <QMouseEvent>
/**
  * @file  [RingTool.h]
  * @brief  RingTool
  * @author  <szj>
  * @date  <2017/05/08>
  * @version  <1.0>
  * @note
  * detailed  description
  */

#include <QPaintEvent>
#include <QPainter>
/**
  * @class  <RingTool>  [RingTool.h]  [RingTool]
  * @brief  圆环工具
  * @author  <szj>
  * @note
  * detailed  description
  */
class RingTool
{
public:

    RingTool();
    bool flagOrNot;
    bool bSelect;

    int m_start_x;
    int m_end_x;
    int m_start_y;
    int m_end_y;
    void *m_pen;
    /**
     * @brief SetROut
     * @param r 外圆环半径
     * @author szj
     * @date 2017/05/08
     * @note 设置外圆环半径
     */
    void SetROut(int r);
    /**
     * @brief SetStepIcon
     * @param r 内圆环半径
     * @author szj
     * @date 2017/05/08
     * @note 设置内圆环半径
     */
    void SetRIn(int r);
    /**
     * @brief SetStepIcon
     * @param x 圆环中心点x坐标
     * @param y 圆环中心点y坐标
     * @author szj
     * @date 2017/05/08
     * @note 设置圆环中心点坐标
     */
    void SetCenter(int x,int y);
    /**
     * @brief GetROut
     * @return 返回外圆环半径
     * @author szj
     * @date 2017/05/08
     * @note 获取外圆环半径
     */
    int GetROut(){return m_r_out;}
    /**
     * @brief SetStepIcon
     * @return 返回内圆环半径
     * @author szj
     * @date 2017/05/08
     * @note 获取内圆环半径
     */
    int GetRIn(){return m_r_in;}
    /**
     * @brief SetStepIcon
     * @return 返回圆环中心点坐标
     * @author szj
     * @date 2017/05/08
     * @note 获取圆环中心点坐标
     */
    QPoint GetCenter(){return m_center;}
public:
    void mouse_PressEvent(QMouseEvent *e);
    void mouse_MoveEvent(QMouseEvent *e);
    void mouse_ReleaseEvent(QMouseEvent *e);
    void paint_Event(QPainter *e);
private:
    int m_b_move;
    int m_r_in;
    int m_r_out;
    QPoint m_press_point;
    QPoint m_center;
    void SetPen(QPen *pen,void *pdata);

};

#endif // RINGTOOL_H
