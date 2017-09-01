#ifndef FWP2PCENTERPOINTLABEL_H
#define FWP2PCENTERPOINTLABEL_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>


class FWP2PCenterPointLabel : public QLabel
{
public:
    FWP2PCenterPointLabel(QWidget *parent = 0);
    void SetPoint1(QPoint point);
    void SetPoint2(QPoint point);
    void SetSet_Parameter_To_RamPoint(QPoint point);
    void SetPenColor(void *pen_color);
protected:
    void paintEvent(QPaintEvent *e);
private:
    QPoint m_point1;
    QPoint m_point2;
    QPoint m_mid_point;
    void *m_pen_color ;
    int i_learn_result;
};

#endif // FWP2PCENTERPOINTLABEL_H
