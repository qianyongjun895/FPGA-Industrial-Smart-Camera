#ifndef SCALEIMAGELABEL_H
#define SCALEIMAGELABEL_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>

class ScaleImageLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ScaleImageLabel(QWidget *parent = 0);
    ~ScaleImageLabel();

    void SetCurrentPointIndex(int index);
    void KeyMoveUp(int value);
    void KeyMoveDown(int value);
    void KeyMoveLeft(int value);
    void KeyMoveRight(int value);
    void GetPointByIndex(int index, QPoint &point);

protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);

private:
    QPoint m_press_point;
    QPoint m_point[2];
    int m_num;
    int m_select;
    int m_current_index;

signals:
    void CurrentPointChangeSignal(int index,QPoint Point);
};

#endif // SCALEIMAGELABEL_H
