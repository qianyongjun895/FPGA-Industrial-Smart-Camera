#ifndef FWPOLYGONCENTERLABEL_H
#define FWPOLYGONCENTERLABEL_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>

class FWPolygonCenterLabel : public QLabel
{
public:
    FWPolygonCenterLabel(QWidget *parent = 0);
    void SetLine1(QLine line);
    void SetLine2(QLine line);
    void SetLine3(QLine line);
    void SetLine4(QLine line);
    void SetSet_Parameter_To_RamPoint(QPoint point);
    void SetPenColor(void *pen_color);
protected:
    void paintEvent(QPaintEvent *e);
private:
    QLine m_Line1;
    QLine m_Line2;
    QLine m_Line3;
    QLine m_Line4;
    QPoint m_center_point;
    void *m_pen_color;
    int i_learn_result;
};

#endif // FWPOLYGONCENTERLABEL_H
