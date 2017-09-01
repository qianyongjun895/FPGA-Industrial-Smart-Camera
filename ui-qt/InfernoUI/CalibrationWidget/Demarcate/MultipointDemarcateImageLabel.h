#ifndef MULTIPOINTDEMARCATEIMAGELABEL_H
#define MULTIPOINTDEMARCATEIMAGELABEL_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>

class MultipointDemarcateImageLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MultipointDemarcateImageLabel(QWidget *parent = 0);
    ~MultipointDemarcateImageLabel();


protected:
    virtual void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);

signals:
    void SendCurPoint(QPoint &curPoint);
    void CurPointIndexChanged(int curIndex); // 索引从1开始
    void UpdateCoordinateTable();

public:
    QVector<QPoint> m_points;
    int cur_point_index; // 当前点索引 从0开始
    int cur_ccc_index; // 当前R轴三个圆周点索引 从0开始
    QLine m_base_line; // AGV 校准时的基准线
    QVector<QPoint> m_ccc_points; // 用于计算R轴中心的三个点

    void PrevPonitSelected();
    void NextPointSelected();
    void AddPoint();
    void AddPoint(int x, int y);
    void AddPointAxisR(int x, int y);
    void DelPoint();
    void DeleteLastOnePoint();
    void DeleteLastOnePointAxisR();
    void ClearAllPoints();
    void ClearAllPointsAxisR();
    int GetPointNum();
    int GetCurPointIndex(); // 返回点索引 从1开始
    int GetCurPointIndexAxisR(); // 返回点索引 从1开始
    void CurPointMoveUp(int value);
    void CurPointMoveDown(int value);
    void CurPointMoveLeft(int value);
    void CurPointMoveRight(int value);
    void SetPointMoveFlag(bool flag);
    void SetBaseLine(QLine qLine);
    void SetOsdPaintContent(unsigned int content);

private:
    QPoint m_press_point;
    int point_selected; // 0：没选中，1:选中 表示当前是否有点被选中，用于点击屏幕时，进行点坐标调整
    bool point_move_flag; // false:不能拖动调整屏幕上的点 true:可以调整屏幕上的点
    bool draw_line_flag;
    unsigned int m_paint_content; // OSD 显示内容

    void show(QPen&, QPainter&);
    void DrawDemarcatePoint(QPainter&, QPoint&, int &pIndex);
    void DrawBaseLine(QPainter&, QLine&);
    void ShowPointsAxisR(QPen&, QPainter&);
};

#endif // MULTIPOINTDEMARCATEIMAGELABEL_H
