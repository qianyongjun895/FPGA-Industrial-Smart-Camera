/**
  * @file  [FWWHMeasureLabel.h]
  * @brief  FWWHMeasureLabel
  * @author  <dgq>
  * @date  <2017/7/13>
  * @version  <1.0>
  * @note 长宽测量的编辑OSD文件
  * detailed  description
  */
#ifndef FWWHMEASURELABEL_H
#define FWWHMEASURELABEL_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>

class FWWHMeasureLabel : public QLabel
{
    Q_OBJECT
public:
    explicit FWWHMeasureLabel(QWidget *parent = 0);
    ~FWWHMeasureLabel();
    void SetOSDData(QLine ref_line);
    void MoveRight(int value);
    void MoveLeft(int value);
    void MoveDown(int value);
    void MoveUp(int value);
    void SetXDirLine(int line_x);
    void SetYDirLine(int line_y);
    void SetXCurveLines(QVector<QPoint> points);
    void SetYCurveLines(QVector<QPoint> points);
    void SetPenColor(void *pen_color);
protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
private:
    QLine m_ref_line;//引用的直线
//    int i_learn_result;//取样结果标志1 成功 0 失败
    QLine m_x_line;
    QLine m_y_line;
    QRect m_rect;
    int m_select;
    QPoint m_press_point;
    QVector<QPoint> m_Xpoints;
    QVector<QPoint> m_Ypoints;
    int IsInEditRect(int x, int y, QRect *rect);
    void *m_pen_color;

signals:
    void LinePosChangeSignal(int x,int y);
};

#endif // FWWHMEASURELABEL_H
