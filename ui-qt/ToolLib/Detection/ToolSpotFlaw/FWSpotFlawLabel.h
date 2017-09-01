#ifndef FWSPOTFLAWLABEL_H
#define FWSPOTFLAWLABEL_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>

class FWSpotFlawLabel : public QLabel
{
public:
    FWSpotFlawLabel(QWidget *parent = 0);
    ~FWSpotFlawLabel();
    void SetFlawsCenterPoint(QVector<QPoint> points);
    void SetPenColor(void *pen_color);
protected:
    void paintEvent(QPaintEvent *e);
private:
    QVector<QPoint> m_Points;
    void *m_pen_color;

};

#endif // FWSPOTFLAWLABEL_H
