#include "FWPolygonCenterLabel.h"
#include "BasicDefine.h"

FWPolygonCenterLabel::FWPolygonCenterLabel(QWidget *parent) : QLabel(parent)
{
    i_learn_result = 0;
    m_Line1 = QLine(0,0,0,0);
    m_Line2 = QLine(0,0,0,0);
    m_Line3 = QLine(0,0,0,0);
    m_Line4 = QLine(0,0,0,0);
    m_pen_color = NULL;
}
void FWPolygonCenterLabel::SetLine1(QLine line)
{
    m_Line1 = line;
    update();
}

void FWPolygonCenterLabel::SetLine2(QLine line)
{
    m_Line2 = line;
    update();
}

void FWPolygonCenterLabel::SetLine3(QLine line)
{
    m_Line3 = line;
    update();
}

void FWPolygonCenterLabel::SetLine4(QLine line)
{
    m_Line4 = line;
    update();
}

void FWPolygonCenterLabel::SetSet_Parameter_To_RamPoint(QPoint point)
{
    m_center_point = point;
    i_learn_result = 1;
    update();
}


void FWPolygonCenterLabel::paintEvent(QPaintEvent *e)
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

    painter.drawLine(m_Line1);
    painter.drawLine(m_Line2);
    painter.drawLine(m_Line3);
    painter.drawLine(m_Line4);
    if(i_learn_result)//取样成功后需要画的osd
    {
        if(pencolor !=NULL)
        {
            pen.setColor(pencolor->m_vt_color[pencolor->task_osd.task_osd_select_color]);
            pen.setWidth(pencolor->task_osd.task_osd_select_width);
            painter.setPen(pen);
        }
        painter.drawLine(m_center_point.x()-10,m_center_point.y(),m_center_point.x()+10,m_center_point.y());
        painter.drawLine(m_center_point.x(),m_center_point.y()-10,m_center_point.x(),m_center_point.y()+10);
    }
    i_learn_result = 1;
}
void FWPolygonCenterLabel::SetPenColor(void *pen_color)
{
    this->m_pen_color = pen_color;
}
