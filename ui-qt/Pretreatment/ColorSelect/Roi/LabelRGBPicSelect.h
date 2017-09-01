#ifndef LABELRGBPICSELECT_H
#define LABELRGBPICSELECT_H

#include <QObject>
#include <QLabel>
#include <QMouseEvent>
#include <QPainter>


class LabelRGBPicSelect: public QLabel
{
    Q_OBJECT
public:
    LabelRGBPicSelect(QWidget *parent = 0);
    QRect GetRect(){return m_rect;}

signals:
    void SignalsRect();
public slots:

protected:
    virtual void mousePressEvent(QMouseEvent *e);
    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual  void  mouseReleaseEvent(QMouseEvent *e);
    virtual void paintEvent(QPaintEvent *e);
private:
    int m_x_start,m_y_start;
    int m_x_end,m_y_end;
    QRect m_rect;
};

#endif // LABELRGBPICSELECT_H
