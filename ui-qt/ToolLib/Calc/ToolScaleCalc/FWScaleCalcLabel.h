#ifndef FWSCALECALCLABEL_H
#define FWSCALECALCLABEL_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>

class FWScaleCalcLabel : public QLabel
{
public:
    explicit FWScaleCalcLabel(QWidget *parent = 0);
    void SetPoint(QPoint point);
protected:
    void paintEvent(QPaintEvent *e);
private:
    QPoint m_point;
};

#endif // FWSCALECALCLABEL_H
