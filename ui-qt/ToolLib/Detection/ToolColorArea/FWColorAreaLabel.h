#ifndef FWCOLORAREALABEL_H
#define FWCOLORAREALABEL_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>

class FWColorAreaLabel : public QLabel
{
public:
    explicit FWColorAreaLabel(QWidget *parent = 0);
    ~FWColorAreaLabel();
    void SetOsdPoint(QPoint point);
    void SetPenColor(void *pen_color);
protected:
    void paintEvent(QPaintEvent *e);
    QPoint m_point;

    void *m_pen_color;


};

#endif // FWCOLORAREALABEL_H
