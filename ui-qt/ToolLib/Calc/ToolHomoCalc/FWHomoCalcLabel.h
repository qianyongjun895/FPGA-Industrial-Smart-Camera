#ifndef FWHOMOCALCLABEL_H
#define FWHOMOCALCLABEL_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>

class FWHomoCalcLabel : public QLabel
{
public:
    explicit FWHomoCalcLabel(QWidget *parent = 0);
    void SetPoint(QPoint point);
    void SetPenColor(void *pen_color);
protected:
    void paintEvent(QPaintEvent *e);
private:
    QPoint m_point;
    void *m_pen_color;
};

#endif // FWHOMOCALCLABEL_H
