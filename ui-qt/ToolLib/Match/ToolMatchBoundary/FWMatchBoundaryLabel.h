/**
  * @file  [FWMatchBoundaryLabel.h]
  * @brief  FWMatchBoundaryLabel
  * @author  <dgq>
  * @date  <2017/5/23>
  * @version  <1.0>
  * @note 边沿定位OSD
  * detailed  description
  */
#ifndef FWMATCHBOUNDARYLABEL_H
#define FWMATCHBOUNDARYLABEL_H


#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>

#define STARTX     0
#define ENDX       640
#define STARTY     0
#define ENDY       480
#define  RESPONSERANGERECTEDIT 20
#define DIRX        0
#define DIRY        1
#define TOPLEFT     0
#define BOTTOMRIGHT 1

class FWMatchBoundaryLabel : public QLabel
{
    Q_OBJECT
public:
    typedef enum
    {
        SELECTNONE = 0,
        SELECTRECTOUTTOP,
        SELECTRECTOUTBOTTOM,
        SELECTRECTXTOP,
        SELECTRECTXBOTTOM,
        SELECTRECTYTOP,
        SELECTRECTYBOTTOM,
    }SELECTRECT;

    explicit FWMatchBoundaryLabel(QWidget *parent = 0);
    ~FWMatchBoundaryLabel();


    void SetListRectY(int iFlag);
    void SetRectEditOut(QRect data);
    void SetRectEditY(QRect data);
    void SetRectEditX(QRect data);
    void SetRectXDirect(int iDirect);
    void SetRectYDirect(int iDirect);
    QRect GetRectEditY();
    QRect GetRectEditX();
    QRect GetRectEditOut();
    void MoveUp(int value);
    void MoveDown(int value);
    void MoveLeft(int value);
    void MoveRight(int value);
protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
private:

    int iSelectKind;
    int m_list_RectY;
    QRect m_rectEditOut;
    QRect m_rectEditX;
    QRect m_rectEditY;

    int m_rectEditX_Direct; //0 x 1,y;
    int m_rectEditY_Direct;
    int m_list_edit_osd;
    int m_key_value;
    void OSDLimit();
    int IsInEditRect(int x, int y, QRect *rect);
    void MoveFunPro(QRect *rect, int Point, int value, int dir);
signals:
    void signalPointsChange(QPoint point,int type);
};

#endif // FWMATCHBOUNDARYLABEL_H
