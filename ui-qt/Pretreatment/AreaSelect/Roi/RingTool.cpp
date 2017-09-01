#include "RingTool.h"
//#include "UIBasicDefine.h"
#include "BasicDefine.h"

RingTool::RingTool()
{
    m_start_x = 0;
    m_end_x = 640;
    m_start_y = 0;
    m_end_y = 480;
    m_pen = NULL;
    this->m_r_out = 60;
    this->m_r_in = 40;
    this->m_center.setX(300);
    this->m_center.setY(300);
    m_b_move = false;
    flagOrNot = false;
    bSelect = false;

}
void RingTool::mouse_PressEvent(QMouseEvent *e)
{
    int x = e->pos().x();
    int y = e->pos().y();

    m_b_move = false;

    int dis = abs(x-m_center.x())*abs(x-m_center.x())+ abs(y-m_center.y())*abs(y-m_center.y());

    if(dis  < m_r_out*m_r_out)
    {
        m_b_move = true;
    }else
    {
        m_b_move = false;
    }
    m_press_point = e->pos();

}
void RingTool::mouse_MoveEvent(QMouseEvent *e)
{
    QPoint pos = e->pos();

    int disX = pos.x() - m_press_point.x();
    int disY = pos.y() - m_press_point.y();
    if(m_b_move)
    {
        if(m_center.x() + disX > this->m_end_x || m_center.x() + disX < this->m_start_x || m_center.y() + disY > this->m_end_y || m_center.y() + disY< this->m_start_y)
            return;
        m_center.setX(m_center.x() + disX);
        m_center.setY(m_center.y() + disY);
    }
    m_press_point = e->pos();

}
void RingTool::mouse_ReleaseEvent(QMouseEvent *e)
{
    m_b_move = false;
}
void RingTool::SetPen(QPen *pen,void *pdata)
{
    PEN_COLOR *pen_color = (PEN_COLOR *)m_pen;
    if(flagOrNot)
    {

         pen->setColor(Qt::red);
         pen->setWidth(1);

    }
    else
    {
        if(pen_color != NULL)
        {
            pen->setColor(pen_color->m_vt_color[pen_color->task_osd.task_osd_AreaSelect_color]);
            pen->setWidth(pen_color->task_osd.task_osd_AreaSelect_width);
        }else
        {
            pen->setColor(Qt::green);
            pen->setWidth(1);
        }
    }
}
void RingTool::paint_Event(QPainter *e)
{
    PEN_COLOR *pen_color = (PEN_COLOR *)m_pen;
    if(pen_color == NULL)
        return;
    QPen pen;
    SetPen(&pen,m_pen);
    e->setPen(pen);
    e->drawEllipse(m_center,m_r_out,m_r_out);
    e->drawEllipse(m_center,m_r_in,m_r_in);

    if(bSelect)
    {
        pen.setColor(pen_color->m_vt_color[pen_color->task_osd.task_osd_select_color]);
        pen.setWidth(pen_color->task_osd.task_osd_select_width);
        e->setPen(pen);
        e->drawLine(m_center.x()-5,m_center.y(),m_center.x()+5,m_center.y());
        e->drawLine(m_center.x(),m_center.y()-5,m_center.x(),m_center.y()+5);
    }
}
void RingTool::SetCenter(int x,int y)
{
    if(x>=this->m_start_x && x<=this->m_end_x && y>=this->m_start_y && y<=this->m_end_y)
    {
        this->m_center.setX(x);
        this->m_center.setY(y);
    }else
    {
        this->m_center.setX((m_start_x+m_end_x)/2);
        this->m_center.setY((m_start_y+m_end_y)/2);
    }
}
void RingTool::SetROut(int r)
{
    this->m_r_out = r;
}
void RingTool::SetRIn(int r)
{
    this->m_r_in = r;
}
