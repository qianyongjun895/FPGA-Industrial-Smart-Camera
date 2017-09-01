#ifndef CONTRASTSTRENGTHENGRAYLABEL_H
#define CONTRASTSTRENGTHENGRAYLABEL_H

#include <QLabel>
#include <QPainter>
#include <QPoint>
#include <QMouseEvent>

class ContrastStrengthenGrayLabel: public QLabel
{
	Q_OBJECT
public:

    explicit ContrastStrengthenGrayLabel(QWidget *parent = 0);
     ~ContrastStrengthenGrayLabel();
    void ValueChangeSlot(float Min, float Max, QVector<float> Value);
    void SetRange(int istart, int iend);
    void SetPlayMode(bool point);
    void ClearPoints();
    void SetYMax(float iy);
    void SetYmin(float iy);
    void BalanceValueChangeSlot(int Min, int Max, QVector<int> Value);
    void SetBalance(int flag);
protected:

    virtual void paintEvent(QPaintEvent *e);

private:

    QVector<QPointF> rePoints;  //实际绘画坐标点
	void show(QPen&, QPainter&);
    //TrendPoins *p_TrendPoins;
    QPointF mMaxPoint;
    QPointF mMinPoint;
    float min;
    float max;
    int start;
    int end;
    float m_yMin;
    float m_yMax;
    bool Point;
    int m_i_balance;
    void wheelEvent(QWheelEvent *event);
signals:
    void paintSignal(int start, int end);
private slots:
};

#endif // MYLABEL_H
