#ifndef LABELEROSIONDILATEPOINTS
#define LABELEROSIONDILATEPOINTS

#include <QObject>
#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>

#define RECTWIDTH 50
#define RECTHEIGHT 50
#define STARTX 30
#define STARTY 30
class LabelErosionDilatePoints : public QLabel
{
    Q_OBJECT
public:
    explicit LabelErosionDilatePoints(QWidget *parent = 0);
    void IniRectPoints(int inum);
    void SelectAll();
    void SelectNoAll();
    void GetbufFlag(char *buf);
    void iniRect(unsigned short *buf);
    void DefaultCirclePara();
    void DefaultDiamondPara();
    void ClearDefaultPara();
signals:

public slots:

protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
private:
    int m_num;
    int m_type;
    void SelectRowColIsAll();


};

#endif // LABEPAINT_H
