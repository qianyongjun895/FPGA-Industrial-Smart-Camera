#include "FWSpotFlawLabel.h"
#include "BasicDefine.h"

FWSpotFlawLabel::FWSpotFlawLabel(QWidget *parent) : QLabel(parent)
{
    m_pen_color = NULL;
}

FWSpotFlawLabel::~FWSpotFlawLabel()
{

}

void FWSpotFlawLabel::SetFlawsCenterPoint(QVector<QPoint > points)
{
    m_Points = points;
    update();
}

void FWSpotFlawLabel::paintEvent(QPaintEvent *e)
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
    for(int i = 0; i < m_Points.count(); i++)
    {
        painter.drawText(m_Points[i].x(),m_Points[i].y()-20,QString::number(i+1));
        painter.drawLine(m_Points[i].x()-5,m_Points[i].y(),m_Points[i].x()+5,m_Points[i].y());
        painter.drawLine(m_Points[i].x(),m_Points[i].y()-5,m_Points[i].x(),m_Points[i].y()+5);
    }
}
void FWSpotFlawLabel::SetPenColor(void *pen_color)
{
    this->m_pen_color = pen_color;
}
