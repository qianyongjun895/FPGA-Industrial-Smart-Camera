#include "FWMatchCircleLabel.h"
#include <qdebug.h>
#include "BasicDefine.h"

FWMatchCircleLabel::FWMatchCircleLabel(QWidget *parent) : QLabel(parent)
{
    m_r = 100;
    m_center.setX(320);
    m_center.setY(240);
    m_sample_center.setX(-10);
    m_sample_center.setY(-10);
    m_sample_r = 0;
    m_pen_color = NULL;
}
FWMatchCircleLabel::~FWMatchCircleLabel()
{

}

void FWMatchCircleLabel::paintEvent(QPaintEvent *e)
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
    painter.drawEllipse(m_center,m_r,m_r);
    painter.drawEllipse(m_sample_center,m_sample_r,m_sample_r);

}
void FWMatchCircleLabel::SetSample(QPoint point,int r)
{
    this->m_sample_center = point;
    this->m_sample_r = r;
    update();
}
void FWMatchCircleLabel::mousePressEvent(QMouseEvent *ev)
{
    m_sample_center.setX(-10);
    m_sample_center.setY(-10);
    m_sample_r = 0;

    int x = ev->pos().x();
    int y = ev->pos().y();

    m_b_move = false;

    int dis = abs(x-m_center.x())*abs(x-m_center.x())+ abs(y-m_center.y())*abs(y-m_center.y());

    if(dis  < m_r*m_r)
    {
        m_b_move = true;
    }else
    {
        m_b_move = false;
    }
    m_press_point = ev->pos();
}
void FWMatchCircleLabel::mouseMoveEvent(QMouseEvent *ev)
{
    QPoint pos = ev->pos();

    int disX = pos.x() - m_press_point.x();
    int disY = pos.y() - m_press_point.y();
    if(m_b_move)
    {
        int ix = 0;
        int iy = 0;
        ix = m_center.x() + disX;
        iy = m_center.y() + disY;

        if(ix>0 && ix<640 && iy>0 && iy<480)
        {
            m_center.setX(m_center.x() + disX);
            m_center.setY(m_center.y() + disY);
        }
        update();
        signalsCenter();
    }
    m_press_point = ev->pos();
}
void FWMatchCircleLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    m_b_move = false;
}
QPoint FWMatchCircleLabel::GetCenter()
{
    return m_center;
}
void FWMatchCircleLabel::SetCenter(QPoint center)
{
    m_center = center;
    update();
}
void FWMatchCircleLabel::SetR(int r)
{
    this->m_r = r;
    update();
}

void FWMatchCircleLabel::KeyMoveUp(int value)
{
    int x = m_center.x();
    int y = m_center.y();

    if(y-value >=0)
    {
        m_center.setX(x);
        m_center.setY(y-value);
    }
    update();

}
void FWMatchCircleLabel::KeyMoveDown(int value)
{
    int x = m_center.x();
    int y = m_center.y();
    if(y + value <=480)
    {
        m_center.setX(x);
        m_center.setY(y+value);
    }
    update();

}
void FWMatchCircleLabel::KeyMoveLeft(int value)
{
    int x = m_center.x();
    int y = m_center.y();
    if(x-value >=0)
    {
        m_center.setX(x-value);
        m_center.setY(y);
    }
    update();

}
void FWMatchCircleLabel::KeyMoveRight(int value)
{
    int x = m_center.x();
    int y = m_center.y();
    if(x+value <=480)
    {
        m_center.setX(x+value);
        m_center.setY(y);
    }
    update();
}
void FWMatchCircleLabel::SetPenColor(void *pen_color)
{
    this->m_pen_color = pen_color;
}
