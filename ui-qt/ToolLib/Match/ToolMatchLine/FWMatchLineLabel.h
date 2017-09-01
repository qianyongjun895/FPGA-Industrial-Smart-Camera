#ifndef IMAGESETLABELEDIT_H
#define IMAGESETLABELEDIT_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>

#define DISTANCE 120
#define ORIGINX 64
#define ORIGINY 255  //400-255

class FWMatchLineLabel : public QLabel
{
    Q_OBJECT
public:
    typedef struct {
        float x_f;
        float y_f;
    }POINT_FLOAT_UI;

    explicit FWMatchLineLabel(QWidget *parent = 0);
    void SetPoint1(QPoint point1);
    void SetPoint2(QPoint point2);

    void SetPoints(QPoint *point1,QPoint *point2,int num);

    QPoint GetPoint1(){return m_point1;}
    QPoint GetPoint2(){return m_point2;}

    QPoint *GetPoints1(){return m_points1;}
    QPoint *GetPoints2(){return m_points2;}
    int GetLineNum(){return m_line_num;}
    int GetLineCurrence(){return m_current_index;}
    void SetLineCurrence(int index);
    double GetAngel(int x1, int y1, int x2, int y2);
    double GetCurrentAngel();
    void SetSampleLine(int x1,int y1,int x2,int y2);
    void SetSampleLines(int *x1,int *y1,int *x2,int *y2,int inum);
    void SetLineNum(int num,int add=0);
    void SetScanDirs(int *dirs,int num);
    void SetCurrentDir(int dir,int index);
    void SetPenColor(void *pen_color);
signals:
    void Point1ChangeSignal(QPoint point1,int kind );
    void Point2ChangeSignal(QPoint point2,int kind );
public slots:

protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);

private:
    QPoint m_point1;
    QPoint m_point2;
    QPoint m_points1[20];
    QPoint m_points2[20];

    int m_select;
    QPoint m_press_point;
    //取祥成功后的点
    int m_x1[20];
    int m_y1[20];
    int m_x2[20];
    int m_y2[20];
    int m_line_num;
    int m_sample_line_num;
    int m_current_index;
    POINT_FLOAT_UI point1[20];
    POINT_FLOAT_UI point2[20];
    POINT_FLOAT_UI point3[20];
    POINT_FLOAT_UI point4[20];

    POINT_FLOAT_UI dir_point1;
    POINT_FLOAT_UI dir_point2;
    int m_dx[20];

    void Coordinate_Rotate_Calc(POINT_FLOAT_UI *OutPoint, POINT_FLOAT_UI *ref_point, POINT_FLOAT_UI *ref_delt, float sin_a, float cos_a);
    void CalcRangePoints(QPainter *p);
    void DrawArrow(QPainter *painter, QPointF lastPoint, QPointF endPoint, float iArrowLen);

    void *m_pen_color;


};

#endif // IMAGESETLABELEDIT_H
