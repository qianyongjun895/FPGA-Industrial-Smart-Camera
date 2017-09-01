#include "FWL2LDistanceLabel.h"
#include "BasicDefine.h"
FWL2LDistanceLabel::FWL2LDistanceLabel(QWidget *parent) : QLabel(parent)
{
    i_learn_result = 0;
    m_Line1 = QLine(0,0,0,0);
    m_Line2 = QLine(0,0,0,0);
    m_samplint_line = QLine(0,0,0,0);
    m_pen_color = NULL;
}

/**
 * @brief FWL2LDistanceLabel::SetLine1
 * @param line
 * @author dgq
 * @note 设置直线一的值并更新OSD显示
 */
void FWL2LDistanceLabel::SetLine1(QLine line)
{
    m_Line1 = line;
    update();
}


/**
 * @brief FWL2LDistanceLabel::SetLine2
 * @param line
 * @author dgq
 * @note 设置直线一的值并更新OSD显示
 */
void FWL2LDistanceLabel::SetLine2(QLine line)
{
    m_Line2 = line;
    update();
}


/**
 * @brief FWL2LDistanceLabel::SetLineSamp
 * @param line
 * @author dgq
 * @note 设置取样成功后的直线的值并更新OSD显示
 */
void FWL2LDistanceLabel::SetLineSamp(QLine line)
{
    i_learn_result = 1;
    m_samplint_line = line;
    update();
}

/**
 * @brief FWL2LDistanceLabel::paintEvent
 * @param e
 * @author dgq
 * @note OSD显示
 */
void FWL2LDistanceLabel::paintEvent(QPaintEvent *e)
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

    painter.drawLine(m_Line1);
    painter.drawLine(m_Line2);
    if(i_learn_result)//取样成功后需要画的osd
    {
        if(pencolor !=NULL)
        {
            pen.setColor(pencolor->m_vt_color[pencolor->task_osd.task_osd_Calc_color]);
            pen.setWidth(pencolor->task_osd.task_osd_Calc__width);
            pen.setStyle(Qt::DashLine);
            painter.setPen(pen);
        }
        painter.drawLine(m_samplint_line);
    }
    i_learn_result = 0;
}
void FWL2LDistanceLabel::SetPenColor(void *pen_color)
{
    this->m_pen_color = pen_color;
}
