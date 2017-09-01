#ifndef FWLINEFLAWLABEL_H
#define FWLINEFLAWLABEL_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>


class FWLineFlawLabel : public QLabel
{
    Q_OBJECT
public:
    explicit FWLineFlawLabel(QWidget *parent = 0);
    ~FWLineFlawLabel();
    void SetOSDData(QVector<QPoint> data);
    void SetLine(QLine line);
    void SetPenColor(void *pen_color);
protected:
    void paintEvent(QPaintEvent *e);

private:
    QVector<QPoint>  m_data;
    QLine m_line;
    int i_learn_result;//取样结果标志 1成功， 0失败
    void *m_pen_color;
};

#endif // FWLINEFLAWLABEL_H
