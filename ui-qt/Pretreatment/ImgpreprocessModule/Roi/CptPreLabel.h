#ifndef CPTPRELABEL_H
#define CPTPRELABEL_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>
#define  RESPONSERANGERECTEDIT 20

class CptPreLabel : public QLabel
{

    Q_OBJECT
public:

    typedef enum{
        LeftTop = 0,
        RightBottom,
        UPLINE,
        DOWNLIN,
        NONE
    }POINTKIND;

    explicit CptPreLabel(QWidget *parent = 0);

    int GetALeftTopX();
    int GetALeftTopY();
    int GetARectWidth();
    int GetARectHeight();
    int GetABottomRightX();
    int GetABottomRightY();
    void SetARect(int iLeftTopX,int iLeftTopY,int iBottomRightX,int iBottomRightY);
    void SetCptFlag(int iFlag);
    void UpdateTwoLineY(int startY,int endY);
    void UpAdjustment(POINTKIND kind,int value =1);
    void DownAdjustment(POINTKIND kind,int value =1);
    void LeftAdjustment(POINTKIND kind,int value =1);
    void RightAdjustment(POINTKIND kind,int value =1 );
    void SetSkeletonFlag(int value){m_is_Skeleton = value;}
    void SetPen(void *pen);
signals:
    void SingalUpdateXY();
public slots:

protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);

private :
     int iSelectKind;
     int m_is_Skeleton; 
     int m_i_startY;
     int m_i_endY;
     int m_rect_x1_Left_top;
     int m_rect_y1_Left_top;
     int m_rect_x1_right_bottom;
     int m_rect_y1_right_bottom;
     int m_i_cpt;
     void *m_pen;

     void JudgmentRectBoundary();
     /**
      * @brief IsInEditRect
      * @param x
      * @param y
      * @return 0未选中 1 选中矩形左上角点，2选中矩形右下角点
      */
     int IsInEditRect(int x,int y);

};

#endif // CPTPRELABEL_H
