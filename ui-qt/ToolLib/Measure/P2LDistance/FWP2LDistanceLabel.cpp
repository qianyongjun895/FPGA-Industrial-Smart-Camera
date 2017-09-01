#include "FWP2LDistanceLabel.h"
#include "BasicDefine.h"
FWP2LDistanceLabel::FWP2LDistanceLabel(QWidget *parent) : QLabel(parent)
{
    i_learn_result = 0;
    m_point = QPoint(-20,-20);
    m_line = QLine(0,0,0,0);
    m_pen_color = NULL;
}

/**
 * @brief FWP2LDistanceLabel::SetPoint
 * @param point 点1坐标
 * @author dgq
 * @note 设置点一的坐标
 */
void FWP2LDistanceLabel::SetPoint(QPoint point)
{
    m_point = point;
    update();
}


/**
 * @brief FWP2LDistanceLabel::SetVPoint
 * @param point 点1坐标
 * @author dgq
 * @note 设置垂点的坐标
 */
void FWP2LDistanceLabel::SetVPoint(QPoint point)
{
    i_learn_result = 1;
    m_Vpoint = point;
    update();
}

/**
 * @brief FWP2LDistanceLabel::SetLine
 * @param line 直线
 * @author dgq
 * @note 设置直线的坐标
 */
void FWP2LDistanceLabel::SetLine(QLine line)
{
    m_line = line;
    update();
}

/**
 * @brief FWP2LDistanceLabel::paintEvent
 * @param e
 * @author dgq
 * @note 两点距离的osd绘制函数
 */
void FWP2LDistanceLabel::paintEvent(QPaintEvent *e)
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

    painter.drawLine(m_line);
    if(i_learn_result)
    {
        if(pencolor !=NULL)
        {
            pen.setColor(pencolor->m_vt_color[pencolor->task_osd.task_osd_select_color]);
            pen.setWidth(pencolor->task_osd.task_osd_select_width);
            pen.setStyle(Qt::DashLine);
            painter.setPen(pen);
        }
        painter.drawLine(m_point,m_Vpoint);
    }
    i_learn_result = 0;
}
void FWP2LDistanceLabel::SetPenColor(void *pen_color)
{
    this->m_pen_color = pen_color;
}
