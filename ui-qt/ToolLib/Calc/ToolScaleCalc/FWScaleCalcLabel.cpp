#include "FWScaleCalcLabel.h"

FWScaleCalcLabel::FWScaleCalcLabel(QWidget *parent) : QLabel(parent)
{

}

void FWScaleCalcLabel::SetPoint(QPoint point)
{
    m_point = point;
    update();
}

void FWScaleCalcLabel::paintEvent(QPaintEvent *e)
{
//    QLabel::paintEvent(e);
//    QPainter painter(this);
//    QPen pen;
//    pen.setColor(Qt::red);
//    pen.setWidth(2);
//    painter.setPen(pen);
//    painter.drawEllipse(m_point,10,10);
//    painter.drawLine(m_point.x()+20,m_point.y(),m_point.x()-20,m_point.y());
//    painter.drawLine(m_point.x(),m_point.y()+20,m_point.x(),m_point.y()-20);
//    painter.drawText(QPoint(m_point.x(),m_point.y()-20),QString::number(1));
}
