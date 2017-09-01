#include "FWL2LCrossPointLabel.h"

FWL2LCrossPointLabel::FWL2LCrossPointLabel(QWidget *parent) : QLabel(parent)
{
    i_learn_result = 0;
    m_Line1 = QLine(0,0,0,0);
    m_Line2 = QLine(0,0,0,0);
}
/**
 * @brief FWL2LCrossPointLabel::SetLine1
 * @param line
 * @author dgq
 * @note 设置直线一的值并更新osd显示
 */
void FWL2LCrossPointLabel::SetLine1(QLine line)
{
    m_Line1 = line;
    update();
}

/**
 * @brief FWL2LCrossPointLabel::SetLine2
 * @param line
 * @author dgq
 * @note 设置直线二的值并更新osd显示
 */
void FWL2LCrossPointLabel::SetLine2(QLine line)
{
    m_Line2 = line;
    update();
}
/**
 * @brief FWL2LCrossPointLabel::SetSet_Parameter_To_RamPoint
 * @param point
 * @author dgq
 * @note 设置取样成功后的交点的值并更新osd显示
 */
void FWL2LCrossPointLabel::SetSet_Parameter_To_RamPoint(QPoint point)
{
    i_learn_result = 1;
    m_point = point;
    update();
}

/**
 * @brief FWL2LCrossPointLabel::paintEvent
 * @param e
 * @author dgq
 * @note OSD显示
 */
void FWL2LCrossPointLabel::paintEvent(QPaintEvent *e)
{
    QLabel::paintEvent(e);
    QPainter painter(this);
    QPen pen;
    pen.setColor(Qt::red);
    pen.setWidth(2);
    painter.setPen(pen);
    painter.drawLine(m_Line1);
    painter.drawLine(m_Line2);
    if(i_learn_result)//取样成功后需要画的osd
    {
        pen.setColor(Qt::green);
        pen.setWidth(2);
        painter.setPen(pen);
        painter.drawLine(m_point.x()-10,m_point.y(),m_point.x()+10,m_point.y());
        painter.drawLine(m_point.x(),m_point.y()-10,m_point.x(),m_point.y()+10);
    }
    i_learn_result = 0;
}
