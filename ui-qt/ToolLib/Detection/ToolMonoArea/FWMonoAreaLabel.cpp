#include "FWMonoAreaLabel.h"
#include "BasicDefine.h"
FWMonoAreaLabel::FWMonoAreaLabel(QWidget *parent) : QLabel(parent)
{
    m_point = QPoint(-10,-10);
    m_pen_color = NULL;
}

FWMonoAreaLabel::~FWMonoAreaLabel()
{

}

void FWMonoAreaLabel::SetOsdPoint(QPoint point)
{
    m_point = point;
    update();
}

void FWMonoAreaLabel::paintEvent(QPaintEvent *e)
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
    painter.setPen(pen);
    painter.drawLine(m_point.x()-10,m_point.y(),m_point.x()+10,m_point.y());
    painter.drawLine(m_point.x(),m_point.y()-10,m_point.x(),m_point.y()+10);
}
void FWMonoAreaLabel::SetPenColor(void *pen_color)
{
    this->m_pen_color = pen_color;
}
