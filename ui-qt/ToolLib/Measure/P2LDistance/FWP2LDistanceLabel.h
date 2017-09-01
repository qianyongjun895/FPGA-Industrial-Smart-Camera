/**
  * @file  [FWP2LDistanceLabel.h]
  * @brief  FWP2LDistanceLabel
  * @author  <Vincent>
  * @date  <2017/6/5>
  * @version  <1.0>
  * @note 点到线距离的osd
  * detailed  description
  */
#ifndef FWP2LDISTANCELABEL_H
#define FWP2LDISTANCELABEL_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>

class FWP2LDistanceLabel : public QLabel
{
    Q_OBJECT
public:
    FWP2LDistanceLabel(QWidget *parent = 0);

    void SetPenColor(void *pen_color);

    /**
     * @brief SetPoint
     * @param point
     * @author dgq
     * @note 编辑时设置点的位置
     */
    void SetPoint(QPoint point);

    /**
     * @brief SetLine
     * @param line
     * @author dgq
     * @note 编辑时设置线的位置
     */
    void SetLine(QLine line);

    /**
     * @brief SetVPoint
     * @param point
     * @author dgq
     * @note 计算、取样成功后设置垂点的位置，画出点到直线的距离虚线
     */
    void SetVPoint(QPoint point);
protected:
    /**
     * @brief paintEvent
     * @param e
     * @author dgq
     * @note 绘图事件
     */
    void paintEvent(QPaintEvent *e);
private:
    QPoint m_point; //引用其他步骤的点
    QPoint m_Vpoint; //计算、取样成功后得到的垂点
    QLine m_line; //引用其他步骤的线
    int i_learn_result; //计算、取样成功标志 1:计算或取样成功状态，0:没有计算或取样的状态

    void *m_pen_color ;

};


#endif // FWP2LDISTANCELABEL_H
