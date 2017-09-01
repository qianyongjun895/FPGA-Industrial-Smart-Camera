#ifndef FWP2PLINELABEL_H
#define FWP2PLINELABEL_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>

class FWP2PLineLabel : public QLabel
{
public:
    FWP2PLineLabel(QWidget *parent = 0);
    void SetPoint1(QPoint point);
    void SetPoint2(QPoint point);
    void SetSet_Parameter_To_RamFlag(int flag);
    void SetPenColor(void *pen_color);
protected:
    void paintEvent(QPaintEvent *e);
private:
    QPoint m_point1;
    QPoint m_point2;
    void *m_pen_color;

    int i_learn_result;
};

#endif // FWP2PLINELABEL_H
