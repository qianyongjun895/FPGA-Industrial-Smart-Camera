#ifndef FWP2POFFSETLABEL_H
#define FWP2POFFSETLABEL_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>

class FWP2POffsetLabel : public QLabel
{
public:
    FWP2POffsetLabel(QWidget *parent = 0);
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

#endif // FWP2POFFSETLABEL_H
