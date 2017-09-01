#ifndef FWMIDDLELINELABEL_H
#define FWMIDDLELINELABEL_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>

class FWMiddleLineLabel : public QLabel
{
public:
    FWMiddleLineLabel(QWidget *parent = 0);
    void SetLine1(QLine line);
    void SetLine2(QLine line);
    void SetLineSamp(QLine line);
    void SetPenColor(void *pen_color);
protected:
    void paintEvent(QPaintEvent *e);
private:
    QLine m_Line1;
    QLine m_Line2;
    QLine m_samplint_line;

    int i_learn_result;
    void *m_pen_color;
};

#endif // FWMIDDLELINELABEL_H
