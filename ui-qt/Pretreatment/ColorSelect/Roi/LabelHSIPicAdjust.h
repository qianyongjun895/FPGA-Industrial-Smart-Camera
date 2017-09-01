#ifndef LABELHSIPICADJUST_H
#define LABELHSIPICADJUST_H

#include <QObject>
#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include <QVector>
#include <QTime>

class LabelHSIPicAdjust : public QLabel
{
    Q_OBJECT
public:
    explicit LabelHSIPicAdjust(QWidget *parent = 0);
    void SetHS(int hMax,int sMax,int hMin,int sMin);
    void SetHSs(QVector<int>vtH,QVector<int>vtS);
    int m_y1;
    int m_y2;
    int m_x1;
    int m_x2;
signals:
    void SignalHS(int hMax,int hMin,int sMax,int sMin);
public slots:

protected:
    virtual void mousePressEvent(QMouseEvent *e);
    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual  void  mouseReleaseEvent(QMouseEvent *e);
    virtual void paintEvent(QPaintEvent *e);
private:
    QImage m_image;
    int lineKind;

    QVector<int> m_vt_h;
    QVector<int> m_vt_s;

    QTime startTime;
    QTime stopTime;
};

#endif // LABELHSIPICADJUST_H
