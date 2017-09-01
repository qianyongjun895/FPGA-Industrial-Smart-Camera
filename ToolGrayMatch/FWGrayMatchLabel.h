#ifndef FWGRAYMATCHLABEL_H
#define FWGRAYMATCHLABEL_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>

class FWGrayMatchLabel :public QLabel
{
public:
    FWGrayMatchLabel(QWidget *parent = 0);
    ~FWGrayMatchLabel();
    void SetOsdPoint(QPoint point);
    void SetPen(QPen *pen);
    void SetRect(QRectF rect,QString str="");
protected:
    QPoint m_point;
    void *m_pen_color;
    bool flagOrNot;
    bool bSelect;
    int m_start_x;
    int m_end_x;
    int m_start_y;
    int m_end_y;
    void *m_pen;
    QRectF m_Rect;
    QString m_str_id;
    QRectF m_RectPoint[2];
    QPointF m_press_point;
    int curt_Area;
    int scalePoint;
    void updateMovePointRect();

protected:
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
    void paintEvent(QPaintEvent *ev);

};

#endif // FWGRAYMATCHLABEL_H
