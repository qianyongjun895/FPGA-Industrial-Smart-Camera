#include "RectTool.h"
#include <QPen>
#include <QDebug>
#include <stdio.h>
//#include "UIBasicDefine.h"
#include "BasicDefine.h"
#define MINRECT 8
RectTool::RectTool()
{
    m_pen = NULL;
    curt_Area =101;
    m_str_id= "";
    flagOrNot = false;
    bSelect = false;
    m_start_x = 0;
    m_end_x  = 640;
    m_start_y = 0;
    m_end_y = 480;

}
void RectTool::mouse_PressEvent(QMouseEvent *e)
{
    QPointF pos = e->pos();
    m_press_point = pos;
    scalePoint = 0;
    if(m_RectPoint[0].contains(pos))
    {
        curt_Area = 1;
        scalePoint = 1;

    }
    else if(m_RectPoint[1].contains(pos))
    {
        curt_Area = 1;
        scalePoint = 2;

    }
    else if(m_Rect.contains(pos)) //平移
    {
        curt_Area = 1;
        scalePoint = 3;

    }
    else
    {
        scalePoint = 101;
        //setMousePos(UNSIDE_AREA);
    }

}
bool RectTool::bSelectFun()
{
    bool bFlag = false;
    if(scalePoint == 101)
        bFlag = false;
    else
        bFlag = true;
    return bFlag;
}
void RectTool::mouse_MoveEvent(QMouseEvent *e)
{

    QPointF pos = e->pos();

    int disX = pos.x() - m_press_point.x();
    int disY = pos.y() - m_press_point.y();

    if(scalePoint == 1)
    {
        if(pos.x()< m_start_x || pos.y()< m_start_y)
            return;
        m_Rect.setTopLeft(pos);

        if(m_Rect.left()+MINRECT > m_Rect.right())
            m_Rect.setLeft(m_Rect.right() - MINRECT);
        if(m_Rect.top()+MINRECT > m_Rect.bottom())
            m_Rect.setTop(m_Rect.bottom() - MINRECT);
    }
    else if(scalePoint == 2)
    {
        if(pos.x() > m_end_x || pos.y()> m_end_y)
            return;
        m_Rect.setBottomRight(pos);
        if(m_Rect.left()+MINRECT > m_Rect.right())
            m_Rect.setRight(m_Rect.left() + MINRECT);
        if(m_Rect.top() +MINRECT > m_Rect.bottom())
            m_Rect.setBottom(m_Rect.top() + MINRECT);
    }else if(scalePoint == 3)//平移
    {
        if(m_Rect.bottomRight().x() > m_end_x )
        {
            SetRect(QRectF(QPointF(m_Rect.topLeft().x()-5,m_Rect.topLeft().y()),\
                           QPointF(m_Rect.bottomRight().x()-5,m_Rect.bottomRight().y())),this->m_str_id);
            return;
        }
        if(m_Rect.topLeft().x() < m_start_x )
        {
            SetRect(QRectF(QPointF(m_Rect.topLeft().x()+5,m_Rect.topLeft().y()+disY),\
                           QPointF(m_Rect.bottomRight().x()+5,m_Rect.bottomRight().y()+disY)),this->m_str_id);
            return;
        }
        if( m_Rect.bottomRight().y() > m_end_y)
        {
            SetRect(QRectF(QPointF(m_Rect.topLeft().x(),m_Rect.topLeft().y()-5),\
                           QPointF(m_Rect.bottomRight().x(),m_Rect.bottomRight().y()-5)),this->m_str_id);
            return;
        }
        if(m_Rect.topLeft().y() < m_start_y)
        {
            SetRect(QRectF(QPointF(m_Rect.topLeft().x(),m_Rect.topLeft().y()+5),\
                           QPointF(m_Rect.bottomRight().x(),m_Rect.bottomRight().y()+5)),this->m_str_id);
            return;
        }
        SetRect(QRectF(QPointF(m_Rect.topLeft().x()+disX,m_Rect.topLeft().y()+disY),\
                       QPointF(m_Rect.bottomRight().x()+disX,m_Rect.bottomRight().y()+disY)),this->m_str_id);
        m_press_point = pos;
    }
}
void RectTool::mouse_ReleaseEvent(QMouseEvent *e)
{
    scalePoint = 101;
}
void RectTool::SetPen(QPen *pen,void *pdata)
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
void RectTool::paint_Event(QPainter *painter)
{
    PEN_COLOR *pen_color = (PEN_COLOR *)m_pen;
    if(pen_color == NULL)
        return;
    QPen drawPen;
    SetPen(&drawPen,m_pen);
    painter->setPen(drawPen);
    updateMovePointRect();
    painter->drawRect(m_Rect);

    if(bSelect)
    {
        drawPen.setColor(pen_color->m_vt_color[pen_color->task_osd.task_osd_select_color]);
        drawPen.setWidth(pen_color->task_osd.task_osd_select_width);
        painter->setPen(drawPen);

        QRectF Rect0 = QRectF(QPointF(m_Rect.topLeft().x()-8, m_Rect.topLeft().y()-8),
                                QPointF(m_Rect.topLeft().x()+8, m_Rect.topLeft().y()+8));
        QRectF Rect1 = QRectF(QPointF(m_Rect.bottomRight().x()-8, m_Rect.bottomRight().y()-8),
                                QPointF(m_Rect.bottomRight().x()+8, m_Rect.bottomRight().y()+8));

        painter->drawRect(Rect0);
        painter->drawText(Rect0,QString::number(1));
        painter->drawRect(Rect1);
        painter->drawText(Rect1,QString::number(2));
    }
}
void RectTool::SetRect(QRectF rect,QString str)
{
    int xtop = rect.topLeft().x();
    int ytop = rect.topLeft().y();
    int xRb = rect.bottomRight().x();
    int yRb = rect.bottomRight().y();
    if(xtop < this->m_start_x)
        xtop = m_start_x;
    if(ytop < this->m_start_y)
        ytop = m_start_y;
    if(xRb >this->m_end_x)
        xRb = m_end_x;
    if(yRb > this->m_end_y)
        yRb = this->m_end_y;
    this->m_Rect.setTopLeft(QPoint(xtop,ytop));
    this->m_Rect.setBottomRight(QPoint(xRb,yRb));
    //this->m_Rect = rect;
    this->m_str_id = str;

}
void RectTool::updateMovePointRect()
{
    m_RectPoint[0] = QRectF(QPointF(m_Rect.topLeft().x()-20, m_Rect.topLeft().y()-20),
                            QPointF(m_Rect.topLeft().x()+20, m_Rect.topLeft().y()+20));
    m_RectPoint[1] = QRectF(QPointF(m_Rect.bottomRight().x()-20, m_Rect.bottomRight().y()-20),
                            QPointF(m_Rect.bottomRight().x()+20, m_Rect.bottomRight().y()+20));
}
void RectTool::UpAdjust(int kind, int value )
{
    scalePoint = kind;
    int yTop,yBottom;
    int xTop = m_Rect.topLeft().x();
    int xBottom = m_Rect.bottomRight().x();
    yTop = m_Rect.topLeft().y();
    yBottom= m_Rect.bottomRight().y();

    if(kind ==1) //左上顶点
    {
        if(yTop-value < m_start_y)
            return;
        else
        {
            m_Rect.setTopLeft(QPoint(xTop,yTop-value));
            m_Rect.setBottomRight(QPoint(xBottom,yBottom));
        }

    }else if(kind ==2)
    {
        if(yBottom-value < yTop)
            return;
        else
        {
            m_Rect.setTopLeft(QPoint(xTop,yTop));
            m_Rect.setBottomRight(QPoint(xBottom,yBottom-value));
        }
    }else if(kind ==3)
    {
        if(yTop-value < m_start_y)
            return;
        else
        {
            m_Rect.setTopLeft(QPoint(xTop,yTop-value));
            m_Rect.setBottomRight(QPoint(xBottom,yBottom-value));
        }
    }
}
void RectTool::DownAdjust(int kind,int value)
{
    scalePoint = kind;
    int yTop,yBottom;
    int xTop = m_Rect.topLeft().x();
    int xBottom = m_Rect.bottomRight().x();
    yTop = m_Rect.topLeft().y();
    yBottom= m_Rect.bottomRight().y();

    if(kind ==1) //左上顶点
    {
        if(yTop+value > yBottom)
            return;
        else
        {
            m_Rect.setTopLeft(QPoint(xTop,yTop+value));
            m_Rect.setBottomRight(QPoint(xBottom,yBottom));
        }

    }else if(kind == 2)
    {
        if(yBottom+value >m_end_y)
            return;
        else
        {
            m_Rect.setTopLeft(QPoint(xTop,yTop));
            m_Rect.setBottomRight(QPoint(xBottom,yBottom+value));
        }
    }
    else
    {

        if(yBottom+value >m_end_y)
            return;
        else
        {
            m_Rect.setTopLeft(QPoint(xTop,yTop+value));
            m_Rect.setBottomRight(QPoint(xBottom,yBottom+value));
        }
    }
}
void RectTool::LeftAdjust(int kind,int value)
{
    scalePoint = kind;
    int yTop,yBottom;
    int xTop = m_Rect.topLeft().x();
    int xBottom = m_Rect.bottomRight().x();
    yTop = m_Rect.topLeft().y();
    yBottom= m_Rect.bottomRight().y();
    if(kind ==1) //左上顶点
    {
        if(xTop - value < m_start_x)
            return;
        else
        {
            m_Rect.setTopLeft(QPoint(xTop-value,yTop));
            m_Rect.setBottomRight(QPoint(xBottom,yBottom));
        }

    }else if(kind == 2)
    {
        if(xBottom - value < xTop)
            return;
        else
        {
            m_Rect.setTopLeft(QPoint(xTop,yTop));
            m_Rect.setBottomRight(QPoint(xBottom-value,yBottom));
        }
    }else
    {
        if(xTop - value < m_start_x)
            return;
        else
        {
            m_Rect.setTopLeft(QPoint(xTop-value,yTop));
            m_Rect.setBottomRight(QPoint(xBottom-value,yBottom));
        }
    }
}
void RectTool::RightAdjust(int kind, int value)
{
    scalePoint = kind;
    int yTop,yBottom;
    int xTop = m_Rect.topLeft().x();
    int xBottom = m_Rect.bottomRight().x();
    yTop = m_Rect.topLeft().y();
    yBottom= m_Rect.bottomRight().y();

    if(kind ==1) //左上顶点
    {
        if(xTop + value > xBottom)
            return;
        else
        {
            m_Rect.setTopLeft(QPoint(xTop+value,yTop));
            m_Rect.setBottomRight(QPoint(xBottom,yBottom));
        }

    }else if(kind == 2)
    {
        if(xBottom + value > m_end_x)
            return;
        else
        {
            m_Rect.setTopLeft(QPoint(xTop,yTop));
            m_Rect.setBottomRight(QPoint(xBottom+value,yBottom));
        }
    }else
    {
        if(xBottom + value > m_end_x)
            return;
        else
        {
            m_Rect.setTopLeft(QPoint(xTop+value,yTop));
            m_Rect.setBottomRight(QPoint(xBottom+value,yBottom));
        }
    }
}
