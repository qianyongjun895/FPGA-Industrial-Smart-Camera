#ifndef FWL2LDISTANCELABEL_H
#define FWL2LDISTANCELABEL_H


#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>

class FWL2LDistanceLabel : public QLabel
{
public:
    FWL2LDistanceLabel(QWidget *parent = 0);
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

#endif // FWL2LDISTANCELABEL_H
