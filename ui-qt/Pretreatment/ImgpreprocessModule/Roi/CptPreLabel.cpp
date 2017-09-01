#include "CptPreLabel.h"
#include <qdebug.h>
//#include "UIBasicDefine.h"
#include "BasicDefine.h"
CptPreLabel::CptPreLabel(QWidget *parent) : QLabel(parent)
{
    m_rect_x1_Left_top = 30;
    m_rect_y1_Left_top = 30;
    m_rect_x1_right_bottom = 610;
    m_rect_y1_right_bottom = 450;
    m_i_startY = 0;
    m_i_endY = 480;
    m_is_Skeleton = 0;
    m_i_cpt = 0;
    m_pen = NULL;
}

void CptPreLabel::paintEvent(QPaintEvent *e)
{
    QLabel::paintEvent(e);
    QPainter painter(this);
    PEN_COLOR *pen_clor = (PEN_COLOR *)m_pen;
    QPen pen;
    if(m_i_cpt == 0)
    {
        if(pen_clor != NULL)
        {
            pen.setColor(pen_clor->m_vt_color[pen_clor->task_osd.task_osd_edit_color]);
            pen.setWidth(pen_clor->task_osd.task_osd_edit_width);
        }else
        {
            pen.setColor(Qt::red);
            pen.setWidth(1);

        }
        painter.setPen(pen);
        int w;
        int h;
        w = m_rect_x1_right_bottom - m_rect_x1_Left_top;
        h = m_rect_y1_right_bottom - m_rect_y1_Left_top;

        painter.drawRect(m_rect_x1_Left_top,m_rect_y1_Left_top,w,h);
        painter.drawRect(m_rect_x1_Left_top-5,m_rect_y1_Left_top-5,10,10);
        painter.drawRect(m_rect_x1_right_bottom-5,m_rect_y1_right_bottom-5,10,10);
    }
    QPen penTemp;
    if(pen_clor != NULL)
    {
        penTemp.setColor(pen_clor->m_vt_color[pen_clor->task_osd.task_osd_ImageBorder_color]);
        penTemp.setWidth(pen_clor->task_osd.task_osd_ImageBorder_width);
    }else
    {
        penTemp.setColor(Qt::red);
        penTemp.setWidth(1);

    }
    penTemp.setStyle(Qt::DashDotLine);
    painter.setPen(penTemp);
    painter.drawLine(0,m_i_startY,640,m_i_startY);
    painter.drawLine(0,m_i_endY,640,m_i_endY);

}
void CptPreLabel::mousePressEvent(QMouseEvent *ev)
{
    int x = ev->pos().x();
    int y = ev->pos().y();

    iSelectKind = 0;

    if(m_i_cpt == 0)
    {
        if(m_is_Skeleton == 1)
            return;
        if(IsInEditRect(x,y)== 1)
        {
            iSelectKind =1;
        }else if(IsInEditRect(x,y)== 2)
        {
            iSelectKind =2;
        }

    }
    if(iSelectKind !=0)
    {
        update();
        return;
    }
}
void CptPreLabel::mouseMoveEvent(QMouseEvent *ev)
{
    int x = ev->pos().x();
    int y = ev->pos().y();


    if(m_is_Skeleton == 1)
        return;
    if(iSelectKind == 1)
    {
        if(x+20 > m_rect_x1_right_bottom \
                || y+10>m_rect_y1_right_bottom)
            return;

        m_rect_x1_Left_top = x;
        m_rect_y1_Left_top = y;
        JudgmentRectBoundary();
        update();
        SingalUpdateXY();

    }else if(iSelectKind ==2)
    {
        if(m_rect_x1_Left_top+20 > x \
                || m_rect_y1_Left_top+10>y)
            return;

        m_rect_x1_right_bottom = x;
        m_rect_y1_right_bottom = y;
        JudgmentRectBoundary();
        update();
        SingalUpdateXY();
    }

    if(iSelectKind !=0)
    {
        return;
    }
}
void CptPreLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    QLabel::mouseReleaseEvent(ev);
}
void CptPreLabel::JudgmentRectBoundary()
{

    if(m_rect_x1_Left_top < 0)
    {
        m_rect_x1_Left_top  =0;

    }else if(m_rect_x1_Left_top > this->width())
    {
        m_rect_x1_Left_top  =this->width();
    }else if(m_rect_x1_right_bottom < 0)
    {
        m_rect_x1_right_bottom  =0;

    }else if(m_rect_x1_right_bottom > this->width())
    {
        m_rect_x1_right_bottom  =this->width();
    }
    if(m_rect_y1_Left_top < m_i_startY)
    {
        m_rect_y1_Left_top  =m_i_startY;

    }else if(m_rect_y1_Left_top > m_i_endY)
    {
        m_rect_y1_Left_top  =m_i_endY;

    }else if(m_rect_y1_right_bottom < m_i_startY)
    {
        m_rect_y1_right_bottom  =m_i_startY;

    }else if(m_rect_y1_right_bottom > m_i_endY)
    {
        m_rect_y1_right_bottom  = m_i_endY;
    }
}
int CptPreLabel::GetALeftTopX()
{
    return this->m_rect_x1_Left_top;
}
int CptPreLabel::GetALeftTopY()
{
    return this->m_rect_y1_Left_top;
}
int CptPreLabel::GetABottomRightX()
{
    return this->m_rect_x1_right_bottom;
}
int CptPreLabel::GetABottomRightY()
{
    return this->m_rect_y1_right_bottom;
}

int CptPreLabel::GetARectWidth()
{
    int width = m_rect_x1_right_bottom - m_rect_x1_Left_top;
    return width;
}
int CptPreLabel::GetARectHeight()
{
    int height = m_rect_y1_right_bottom - m_rect_y1_Left_top;
    return height;
}
void CptPreLabel::SetARect(int iLeftTopX,int iLeftTopY,int iBottomRightX,int iBottomRightY)
{
    m_rect_x1_Left_top = iLeftTopX;
    m_rect_y1_Left_top = iLeftTopY;
    m_rect_x1_right_bottom =  iBottomRightX;
    m_rect_y1_right_bottom = iBottomRightY;
    update();
}
void CptPreLabel::SetCptFlag(int iFlag)
{
    this->m_i_cpt = iFlag;
    update();
}

void CptPreLabel::UpAdjustment(POINTKIND kind, int value)
{
    if(kind == LeftTop)
    {
        if(m_rect_y1_Left_top-value >= m_i_startY)
        {
            m_rect_y1_Left_top = m_rect_y1_Left_top-value;
            SingalUpdateXY();
            update();
        }
    }else if(kind == RightBottom)
    {
        if(m_rect_y1_right_bottom-value > m_rect_y1_Left_top+30)
        {
            m_rect_y1_right_bottom  = m_rect_y1_right_bottom -value;
            SingalUpdateXY();
            update();
        }
    }
}
void CptPreLabel::DownAdjustment(POINTKIND kind, int value)
{
    if(kind == LeftTop)
    {
        if(m_rect_y1_right_bottom +value >= m_rect_y1_Left_top+30)
        {
            m_rect_y1_Left_top = m_rect_y1_Left_top + value;
            SingalUpdateXY();
            update();
        }

    }else if(kind == RightBottom)
    {
        if(m_rect_y1_right_bottom + value < m_i_endY)
        {
            m_rect_y1_right_bottom  = m_rect_y1_right_bottom +value;
            SingalUpdateXY();
            update();
        }
    }
}
void CptPreLabel::LeftAdjustment(POINTKIND kind, int value)
{
    if(kind == LeftTop)
    {
        if(m_rect_x1_Left_top - value >= 0)
        {
            m_rect_x1_Left_top  = m_rect_x1_Left_top -value;
            SingalUpdateXY();
            update();
        }

    }else if(kind == RightBottom)
    {
        if(m_rect_x1_right_bottom-value >= m_rect_x1_Left_top+30)
        {
            m_rect_x1_right_bottom = m_rect_x1_right_bottom -value;
            SingalUpdateXY();
            update();
        }
    }
}
void CptPreLabel::RightAdjustment(POINTKIND kind, int value)
{
    if(kind == LeftTop)
    {
        if(m_rect_x1_Left_top +30+value <= m_rect_x1_right_bottom)
        {
            m_rect_x1_Left_top +=value;
            SingalUpdateXY();
            update();
        }

    }else if(kind == RightBottom)
    {
        if(m_rect_x1_right_bottom + value  <= 640)
        {
            m_rect_x1_right_bottom +=value;
            SingalUpdateXY();
            update();
        }
    }
}
void CptPreLabel::UpdateTwoLineY(int startY,int endY)
{
    m_i_startY = startY;
    m_i_endY = endY;
    update();
}
int CptPreLabel::IsInEditRect(int x,int y)
{
    int ret = 0;

    if(x>m_rect_x1_Left_top-RESPONSERANGERECTEDIT && x < m_rect_x1_Left_top+RESPONSERANGERECTEDIT && y>m_rect_y1_Left_top-RESPONSERANGERECTEDIT && y<m_rect_y1_Left_top+RESPONSERANGERECTEDIT)
    {
        ret =1;

    }else if(x>m_rect_x1_right_bottom-RESPONSERANGERECTEDIT && x < m_rect_x1_right_bottom+RESPONSERANGERECTEDIT && y>m_rect_y1_right_bottom-RESPONSERANGERECTEDIT && y<m_rect_y1_right_bottom+RESPONSERANGERECTEDIT)
    {
        ret =2;

    }else
    {
        ret = 0;
    }
    return ret;
}
void CptPreLabel::SetPen(void *pen)
{
    this->m_pen = pen;
    update();
}
