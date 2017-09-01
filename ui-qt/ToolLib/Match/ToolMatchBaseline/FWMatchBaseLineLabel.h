/**
  * @file  [FWMatchBaseLineLabel.h]
  * @brief  FWMatchBaseLineLabel
  * @author  <dgq>
  * @date  <2017/5/24>
  * @version  <1.0>
  * @note 基准线OSD
  * detailed  description
  */
#ifndef FWMATCHBASELINELABEL_H
#define FWMATCHBASELINELABEL_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>

#define BASE_LINE_NUM_MAX    20

class FWMatchBaseLineLabel : public QLabel
{
    Q_OBJECT
public:
    FWMatchBaseLineLabel(QWidget *parent = 0);


    void SetBaseLineNum(int num);
    void SetBaseLinePoint1(QPoint point1);
    void SetBaseLinePoint2(QPoint point2);
    void SetSampleLines(int *x1, int *y1, int *x2, int *y2, int inum);
    void SetBaseLinePoints(QPoint *point1, QPoint *point2, int num);
    QVector<QLine> GetBaseLines();
    void MoveUp(int value);
    void MoveDown(int value);
    void MoveLeft(int value);
    void MoveRight(int value);
    void SetBaseLineCurrentIndex(int index);
    void SetBaseLineCurrentPoint(int index);
    void SetPenColor(void *pen_color);
private:

    QPoint m_point1;
    QPoint m_point2;
    QPoint m_points1[20];
    QPoint m_points2[20];

    int m_select;
    int m_current_point;
    QPoint m_press_point;
    //取祥成功后的点
    int m_x1[20];
    int m_y1[20];
    int m_x2[20];
    int m_y2[20];
    int m_line_num;
    int m_sample_line_num;
    int m_current_index;
    void *m_pen_color;
    int m_dx[20];
signals:
    void Point1ChangeSignal(QPoint point1,int index );
    void Point2ChangeSignal(QPoint point2,int index );
protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
};

#endif // FWMATCHBASELINELABEL_H
