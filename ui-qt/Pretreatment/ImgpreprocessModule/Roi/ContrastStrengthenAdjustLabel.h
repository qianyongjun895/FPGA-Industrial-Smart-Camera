#ifndef CONTRASTSTRENGTHENADJUSTLABEL_H
#define CONTRASTSTRENGTHENADJUSTLABEL_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>
#define DISTANCE 120

#define ORIGINX 64
#define ORIGINY 400  //400-255

class ContrastStrengthenAdjustLabel : public QLabel
{
    Q_OBJECT
public:

    typedef enum{
        UPLINE = 0,
        DOWNLIN,
        NONE
    }KEYKIND;

    explicit ContrastStrengthenAdjustLabel(QWidget *parent = 0);

    void SetLine(int y1,int y2);
    int GetStartY(){return m_y1;}
    int GetEndY(){return m_y2;}
    int GetLineHeigth();
    void UpAdjustLine(KEYKIND kind,int value =2);
    void DownAdjustmentLine(KEYKIND kind,int value =2);
    void SetImagSmothEnable(int flag);
    QPoint GetPoint1();
    QPoint GetPoint2();
    void SetPoint1(int x, int y);
    void SetPoint2(int x, int y);
    void SetPoints(QVector<QPoint> Points, int num);
    void SetPointsChange(QVector<QPoint> Points, int num);
    QVector<QPoint> GetPoints();
    void MoveUp();
    void MoveDown();
    void MoveLeft();
    void MoveRight();
    void SetPointFocus(int index);
    QRect GetRect();
    int GetCurrentIndexAd();
    void SetCurrentIndexAd(int value);
    QPoint GetCurrentPoint();
    void SetCurrentPoint(int y);
    void SetListAdjustLine(int flag);
signals:
    void signaleValue(int kind);
    void sendDataSignal();
    void PointChangeSignal(int num,QPoint point);
public slots:

protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);

private:
    int iSelectKind;
    int m_y1;
    int m_y2;
    QPoint m_point1;
    QPoint m_point2;
    QPoint m_point[16];
    int m_img_smooth;
    QVector<QPoint> m_Points;
    int m_smooth_mode;
    QPoint m_point_start;
    QPoint m_point_end;
    int m_current_ad;
    int m_list_adjust_line;

};

#endif // IMAGESETLABELEDIT_H
