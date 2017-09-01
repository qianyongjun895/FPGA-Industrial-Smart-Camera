/**
  * @file  [FWP2PDistanceLabel.h]
  * @brief  FWP2PDistanceLabel
  * @author  <dgq>
  * @date  <2017/6/5>
  * @version  <1.0>
  * @note 两点距离的osd
  * detailed  description
  */
#ifndef FWP2PDISTANCELABEL_H
#define FWP2PDISTANCELABEL_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>

class FWP2PDistanceLabel : public QLabel
{
    Q_OBJECT
public:
    FWP2PDistanceLabel(QWidget *parent = 0);
    void SetPoint1(QPoint point);
    void SetPoint2(QPoint point);
    void SetSet_Parameter_To_RamFlag(int flag);
    void SetPenColor(void *pen_color);
protected:
    void paintEvent(QPaintEvent *e);
private:
    QPoint m_point1;
    QPoint m_point2;

    int i_learn_result;
    void *m_pen_color;

};

#endif // FWP2PDISTANCELABEL_H
