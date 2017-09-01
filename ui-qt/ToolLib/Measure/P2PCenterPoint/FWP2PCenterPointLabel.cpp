#include "FWP2PCenterPointLabel.h"
#include "BasicDefine.h"
FWP2PCenterPointLabel::FWP2PCenterPointLabel(QWidget *parent) : QLabel(parent)
{
    i_learn_result = 0;
    m_point1 = QPoint(-20,-20);
    m_point2 = QPoint(-20,-20);
    m_pen_color = NULL;
}
/**
 * @brief FWP2PCenterPointLabel::SetPoint1
 * @param point 点1坐标
 * @author dgq
 * @note 设置点一的坐标
 */
void FWP2PCenterPointLabel::SetPoint1(QPoint point)
{
    m_point1 = point;
    update();
}

/**
 * @brief FWP2PCenterPointLabel::SetPoint2
 * @param point 点2坐标
 * @author dgq
 * @note 设置点二的坐标
 */
void FWP2PCenterPointLabel::SetPoint2(QPoint point)
{
    m_point2 = point;
    update();
}

void FWP2PCenterPointLabel::SetSet_Parameter_To_RamPoint(QPoint point)
{
    i_learn_result = 1;
    m_mid_point = point;
    update();
}

/**
 * @brief FWP2PCenterPointLabel::paintEvent
 * @param e
 * @author dgq
 * @note 两点距离的osd绘制函数
 */
void FWP2PCenterPointLabel::paintEvent(QPaintEvent *e)
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

    painter.drawEllipse(m_point1,10,10);
    painter.drawLine(m_point1.x()+20,m_point1.y(),m_point1.x()-20,m_point1.y());
    painter.drawLine(m_point1.x(),m_point1.y()+20,m_point1.x(),m_point1.y()-20);
    painter.drawText(QPoint(m_point1.x(),m_point1.y()-20),QString::number(1));

    painter.drawEllipse(m_point2,10,10);
    painter.drawLine(m_point2.x()+20,m_point2.y(),m_point2.x()-20,m_point2.y());
    painter.drawLine(m_point2.x(),m_point2.y()+20,m_point2.x(),m_point2.y()-20);
    painter.drawText(QPoint(m_point2.x(),m_point2.y()-20),QString::number(2));
    if(i_learn_result)
    {
        if(pencolor !=NULL)
        {
            pen.setColor(pencolor->m_vt_color[pencolor->task_osd.task_osd_select_color]);
            pen.setWidth(pencolor->task_osd.task_osd_select_width);
            pen.setStyle(Qt::DashLine);
            painter.setPen(pen);
        }

        painter.drawLine(m_point1,m_point2);
        painter.drawLine(m_mid_point.x()-10,m_mid_point.y()-10,m_mid_point.x()+10,m_mid_point.y()+10);
        painter.drawLine(m_mid_point.x()-10,m_mid_point.y()+10,m_mid_point.x()+10,m_mid_point.y()-10);
    }
    i_learn_result = 0;
}
void FWP2PCenterPointLabel::SetPenColor(void *pen_color)
{
    this->m_pen_color = pen_color;
}
