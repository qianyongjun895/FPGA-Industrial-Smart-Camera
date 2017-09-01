#include "FWL2LAngleLabel.h"
#include "BasicDefine.h"

FWL2LAngleLabel::FWL2LAngleLabel(QWidget *parent) : QLabel(parent)
{
    i_learn_result = 0;
    m_Line1 = QLine(0,0,0,0);
    m_Line2 = QLine(0,0,0,0);
    m_pen_color = NULL;
}

/**
 * @brief FWL2LAngleLabel::SetLine1
 * @param line
 * @author dgq
 * @note 设置直线1的值
 */
void FWL2LAngleLabel::SetLine1(QLine line)
{
    m_Line1 = line;
    update();
}

void FWL2LAngleLabel::SetArcData(OSD_ARC data)
{
    i_learn_result = 1;
    m_arc = data;
    update();
}
/**
 * @brief FWL2LAngleLabel::SetLine2
 * @param line
 * @author dgq
 * @note 设置直线2的值
 */
void FWL2LAngleLabel::SetLine2(QLine line)
{
    m_Line2 = line;
    update();
}

/**
 * @brief FWL2LAngleLabel::SetSet_Parameter_To_RamFlag
 * @param flag
 * @author dgq
 * @note 设置取样成功后的中分线值
 */
void FWL2LAngleLabel::SetSet_Parameter_To_RamFlag(int flag)
{
    i_learn_result = flag;
    update();
}

/**
 * @brief FWL2LAngleLabel::paintEvent
 * @param e
 * @author dgq
 * @note paint事件
 */
void FWL2LAngleLabel::paintEvent(QPaintEvent *e)
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
            painter.setPen(pen);
        }
        QRect rect;
        rect.setTopLeft(QPoint(m_arc.x - m_arc.r,m_arc.y - m_arc.r));
        rect.setBottomRight(QPoint(m_arc.x + m_arc.r,m_arc.y + m_arc.r));
        painter.drawArc(rect,m_arc.angStart*16,m_arc.angEnd*16);
    }
    i_learn_result = 0;
}
void FWL2LAngleLabel::SetPenColor(void *pen_color)
{
    this->m_pen_color = pen_color;
}

