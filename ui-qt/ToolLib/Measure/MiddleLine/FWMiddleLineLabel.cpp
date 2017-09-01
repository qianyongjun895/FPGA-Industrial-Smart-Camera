#include "FWMiddleLineLabel.h"
#include "BasicDefine.h"
FWMiddleLineLabel::FWMiddleLineLabel(QWidget *parent) : QLabel(parent)
{
    i_learn_result = 0;
    m_Line1 = QLine(0,0,0,0);
    m_Line2 = QLine(0,0,0,0);
    m_samplint_line = QLine(0,0,0,0);
    m_pen_color = NULL;
}

void FWMiddleLineLabel::SetLine1(QLine line)
{
    m_Line1 = line;
    update();
}

void FWMiddleLineLabel::SetLine2(QLine line)
{
    m_Line2 = line;
    update();
}

void FWMiddleLineLabel::SetLineSamp(QLine line)
{
    i_learn_result = 1;
    m_samplint_line = line;
    update();
}


void FWMiddleLineLabel::paintEvent(QPaintEvent *e)
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
    painter.drawLine(m_Line1);
    painter.drawLine(m_Line2);
    if(i_learn_result)//取样成功后需要画的osd
    {
        if(pencolor !=NULL)
        {
            pen.setColor(pencolor->m_vt_color[pencolor->task_osd.task_osd_select_color]);
            pen.setWidth(pencolor->task_osd.task_osd_select_width);
            painter.setPen(pen);
        }
        painter.drawLine(m_samplint_line);
    }
    i_learn_result = 0;
}
void FWMiddleLineLabel::SetPenColor(void *pen_color)
{
    this->m_pen_color = pen_color;
}
