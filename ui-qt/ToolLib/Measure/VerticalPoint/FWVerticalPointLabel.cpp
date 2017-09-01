#include "FWVerticalPointLabel.h"

FWVerticalPointLabel::FWVerticalPointLabel(QWidget *parent) : QLabel(parent)
{
    i_learn_result = 0;
    m_point = QPoint(-20,-20);
    m_line = QLine(0,0,0,0);
}

/**
 * @brief FWVerticalPointLabel::SetPoint
 * @param point 点1坐标
 * @author dgq
 * @note 设置点一的坐标
 */
void FWVerticalPointLabel::SetPoint(QPoint point)
{
    m_point = point;
    update();
}

/**
 * @brief FWVerticalPointLabel::SetLine
 * @param point 点2坐标
 * @author dgq
 * @note 设置点二的坐标
 */
void FWVerticalPointLabel::SetLine(QLine line)
{
    m_line = line;
    update();
}

void FWVerticalPointLabel::SetSet_Parameter_To_RamPoint(QPoint point)
{
    i_learn_result = 1;
    m_Vpoint = point;
    update();
}

/**
 * @brief FWVerticalPointLabel::paintEvent
 * @param e
 * @author dgq
 * @note 两点距离的osd绘制函数
 */
void FWVerticalPointLabel::paintEvent(QPaintEvent *e)
{
    QLabel::paintEvent(e);
    QPainter painter(this);
    QPen pen;
    pen.setColor(Qt::red);
    pen.setWidth(2);
    painter.setPen(pen);

    painter.drawEllipse(m_point,10,10);
    painter.drawLine(m_point.x()+20,m_point.y(),m_point.x()-20,m_point.y());
    painter.drawLine(m_point.x(),m_point.y()+20,m_point.x(),m_point.y()-20);
    painter.drawText(QPoint(m_point.x(),m_point.y()-20),QString::number(1));

    painter.drawLine(m_line);
    if(i_learn_result)
    {
        pen.setColor(Qt::green);
        pen.setStyle(Qt::DashLine);
        pen.setWidth(2);
        painter.setPen(pen);
        painter.drawLine(m_point,m_Vpoint);
        painter.drawLine(m_Vpoint.x()-10,m_Vpoint.y(),m_Vpoint.x()+10,m_Vpoint.y());
        painter.drawLine(m_Vpoint.x(),m_Vpoint.y()-10,m_Vpoint.x(),m_Vpoint.y()+10);
    }
    i_learn_result = 0;
}

