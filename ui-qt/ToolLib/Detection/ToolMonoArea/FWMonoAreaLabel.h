#ifndef FWMONOAREALABEL_H
#define FWMONOAREALABEL_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>

class FWMonoAreaLabel : public QLabel
{
public:
    FWMonoAreaLabel(QWidget *parent = 0);
    ~FWMonoAreaLabel();
    void SetOsdPoint(QPoint point);
    void SetPenColor(void *pen_color);
protected:
    void paintEvent(QPaintEvent *e);
    QPoint m_point;
    void *m_pen_color;
};

#endif // FWMONOAREALABEL_H
