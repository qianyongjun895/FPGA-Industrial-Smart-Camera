/**
  * @file  [FWMatchBasePointLabel]
  * @brief  FWMatchBasePointLabel
  * @author  <dhq>
  * @date  <2017/5/24>
  * @version  <1.0>
  * @note  基准点OSD
  * detailed  description
  */
#ifndef FWMATCHBASEPOINTLABEL_H
#define FWMATCHBASEPOINTLABEL_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>

#define BASE_POINT_NUM_MAX    20

class FWMatchBasePointLabel : public QLabel
{
    Q_OBJECT
public:
    explicit FWMatchBasePointLabel(QWidget *parent = 0);
    ~FWMatchBasePointLabel();


    QVector<QPoint> GetBasePointData();
    void SetBasePointData(QVector<QPoint> data);
    int GetBasePointNum();
    void SetBasePointNum(int num);
    int GetBasePointCurrentIndex();
    void SetBasePointCurrentIndex(int index);
    void KeyMoveUp(int value);
    void KeyMoveDown(int value);
    void KeyMoveLeft(int value);
    void KeyMoveRight(int value);
    void SetPenColor(void *pen_color);
protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
private:
    QPoint m_press_point;
    QPoint m_point[20];
    int m_num;
    int m_select;
    int m_current_index;
    void *m_pen_color;
signals:
    void CurrentPointChangeSignal(int index,QPoint Point);
};

#endif // FWMATCHBASEPOINTLABEL_H
