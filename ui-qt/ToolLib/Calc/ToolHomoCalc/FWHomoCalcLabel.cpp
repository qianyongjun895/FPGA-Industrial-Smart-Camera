#include "FWHomoCalcLabel.h"
#include "BasicDefine.h"
FWHomoCalcLabel::FWHomoCalcLabel(QWidget *parent) : QLabel(parent)
{
    m_pen_color = NULL;
}

void FWHomoCalcLabel::SetPoint(QPoint point)
{
    m_point = point;
    update();
}

void FWHomoCalcLabel::paintEvent(QPaintEvent *e)
{
    QLabel::paintEvent(e);
    QPainter painter(this);
    QPen pen;
    PEN_COLOR * pencolor = (PEN_COLOR*)m_pen_color;
    if(pencolor !=NULL)
    {
        pen.setColor(pencolor->m_vt_color[pencolor->task_osd.task_osd_edit_color]);
        pen.setWidth(pencolor->task_osd.task_osd_edit_width);
        painter.setPen(pen);
    }
    painter.drawEllipse(m_point,10,10);
    painter.drawLine(m_point.x()+20,m_point.y(),m_point.x()-20,m_point.y());
    painter.drawLine(m_point.x(),m_point.y()+20,m_point.x(),m_point.y()-20);
    painter.drawText(QPoint(m_point.x(),m_point.y()-20),QString::number(1));
}
void FWHomoCalcLabel::SetPenColor(void *pen_color)
{
    this->m_pen_color = pen_color;
}
