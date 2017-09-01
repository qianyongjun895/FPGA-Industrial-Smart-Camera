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

class ImageSetLabelEdit : public QLabel
{
    Q_OBJECT
public:

    typedef enum{
        UPLINE = 0,
        DOWNLIN,
        NONE
    }KEYKIND;

    explicit ImageSetLabelEdit(QWidget *parent = 0);

    void SetLine(int y1,int y2);
    int GetStartY(){return m_y1;}
    int GetEndY(){return m_y2;}
    int GetLineHeigth();
    void UpAdjustLine(KEYKIND kind,int value =2);
    void DownAdjustmentLine(KEYKIND kind,int value =2);
    void SetListAdjustLine(int flag);
signals:
    void signaleValue(int kind);
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
    int m_list_adjust_line;

};

#endif // IMAGESETLABELEDIT_H
