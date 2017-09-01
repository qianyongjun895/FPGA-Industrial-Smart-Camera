#ifndef FWL2LCROSSPOINTLABEL_H
#define FWL2LCROSSPOINTLABEL_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>

class FWL2LCrossPointLabel : public QLabel
{
public:
    FWL2LCrossPointLabel(QWidget *parent = 0);
    void SetLine1(QLine line);
    void SetLine2(QLine line);
    void SetSet_Parameter_To_RamPoint(QPoint point);
protected:
    void paintEvent(QPaintEvent *e);
private:
    QLine m_Line1;
    QLine m_Line2;
    QPoint m_point;
    int i_learn_result;
};

#endif // FWL2LCROSSPOINTLABEL_H
