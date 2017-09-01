#include "FWGrayMatchLabel.h"
#include <QPen>
#include <QDebug>
#include <stdio.h>
#include "BasicDefine.h"
#define MINRECT 8

FWGrayMatchLabel::FWGrayMatchLabel(QWidget *parent) :QLabel(parent)
{
    m_pen = NULL;
   // curt_Area =101;
   // m_str_id= "";
    flagOrNot = false;
    bSelect = false;
    m_start_x = 0;
    m_end_x  = 640;
    m_start_y = 0;
    m_end_y = 480;
}

FWGrayMatchLabel::~FWGrayMatchLabel()
{

}

void FWGrayMatchLabel::SetOsdPoint(QPoint point)
{
    m_point = point;
    update();
}

//ROI绘制
void FWGrayMatchLabel::paintEvent(QPaintEvent *ev)
{
    QLabel::paintEvent(ev);
     QPainter painter(this);
    QPen pen;
    PEN_COLOR * pencolor = (PEN_COLOR*)m_pen;
    if(pencolor !=NULL)
    {
        pen.setColor(pencolor->m_vt_color[pencolor->task_osd.task_osd_edit_color]);
        pen.setWidth(pencolor->task_osd.task_osd_edit_width);
        painter.setPen(pen);
    }
    painter.setPen(pen);
    updateMovePointRect();
    painter.drawRect(m_Rect);
    if(bSelect)
    {
        QRectF Rect0 = QRectF(QPointF(m_Rect.topLeft().x()-8, m_Rect.topLeft().y()-8),
                                QPointF(m_Rect.topLeft().x()+8, m_Rect.topLeft().y()+8));
        QRectF Rect1 = QRectF(QPointF(m_Rect.bottomRight().x()-8, m_Rect.bottomRight().y()-8),
                                QPointF(m_Rect.bottomRight().x()+8, m_Rect.bottomRight().y()+8));

        painter.drawRect(Rect0);
        painter.drawText(Rect0,QString::number(1));
        painter.drawRect(Rect1);
        painter.drawText(Rect1,QString::number(2));
    }
}

/**
 * @brief FWMatchBaseLineLabel::mousePressEvent
 * @param ev
 * @author dgq
 * @note 鼠标按下事件的响应函数
 */
void FWGrayMatchLabel::mousePressEvent(QMouseEvent *ev)
{
    QPointF pos = ev->pos();
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

/**
 * @brief FWMatchBaseLineLabel::mouseMoveEvent
 * @param ev
 * @author dgq
 * @note 鼠标移动事件响应函数
 */
void FWGrayMatchLabel::mouseMoveEvent(QMouseEvent *ev)
{
    QPointF pos = ev->pos();

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

/**
 * @brief FWMatchBaseLineLabel::mouseReleaseEvent
 * @param ev
 * @author dgq
 * @note 鼠标释放事件响应函数
 */
void FWGrayMatchLabel::mouseReleaseEvent(QMouseEvent *ev)
{
     scalePoint = 101;
}

void FWGrayMatchLabel::SetPen(QPen *pen)
{
    m_pen = pen;
    update();
}

void FWGrayMatchLabel::SetRect(QRectF rect,QString str)
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

void FWGrayMatchLabel::updateMovePointRect()
{
    m_RectPoint[0] = QRectF(QPointF(m_Rect.topLeft().x()-20, m_Rect.topLeft().y()-20),
                            QPointF(m_Rect.topLeft().x()+20, m_Rect.topLeft().y()+20));
    m_RectPoint[1] = QRectF(QPointF(m_Rect.bottomRight().x()-20, m_Rect.bottomRight().y()-20),
                            QPointF(m_Rect.bottomRight().x()+20, m_Rect.bottomRight().y()+20));
}
