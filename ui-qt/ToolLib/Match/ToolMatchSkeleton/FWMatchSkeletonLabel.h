/**
  * @file  [FWMatchSkeletonLabel.h]
  * @brief  brief
  * @author  <dgq>
  * @date  <2017/5/25>
  * @version  <1.0>
  * @note 轮廓匹配OSD
  * detailed  description
  */
#ifndef FWMATCHSKELETONLABEL_H
#define FWMATCHSKELETONLABEL_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>

#define STARTX     1
#define ENDX       639
#define STARTY     1
#define ENDY       479
#define  RESPONSERANGERECTEDIT 20

class FWMatchSkeletonLabel : public QLabel
{
    Q_OBJECT
public:
    FWMatchSkeletonLabel(QWidget *parent = 0);
    void ShowOsd(int iFlag);
    QRect GetTrainRect();
    void SetTrainRect(QRect rect);
    QRect GetSearchRect();
    void SetSearchRect(QRect rect);
    void MoveUp(int value);
    void MoveRight(int value);
    void MoveLeft(int value);
    void MoveDown(int value);

    void SetRectPoint(int index);
    void SetPenColor(void *pen_color);
protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
private:

    int iSelectKind;//1搜索框左上点，2搜索框右下点，3学习框左上点，4学习框右下点
    int iSelectPoint;
    QRect m_rectEditOut;
    QRect m_rectEditIn;
    int m_list_eidt_osd;
    int IsInEditRect(int x, int y, QRect *rect);
    void JudgmentRectBoundary();

    void *m_pen_color;

signals:
    void signalPointsChange(QPoint data,int type);
};

#endif // FWMATCHSKELETONLABEL_H
