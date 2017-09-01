#include <QDebug>
#include "FWLineFlawLabel.h"
#include "math.h"
#include "BasicDefine.h"

FWLineFlawLabel::FWLineFlawLabel(QWidget *parent) : QLabel(parent)
{
    m_pen_color = NULL;
}

FWLineFlawLabel::~FWLineFlawLabel()
{

}


/**
 * @brief FWLineFlawLabel::SetOSDData
 * @param data
 * @author Vincent
 * @note 设置blob取样/计算后的参数
 */
void FWLineFlawLabel::SetOSDData(QVector<QPoint> data)
{
    i_learn_result = 1;
    m_data = data;
    update();
}

/**
 * @brief FWLineFlawLabel::SetLine
 * @param line
 * @author dgq
 * @note 设置直线的值并更新OSD显示
 */
void FWLineFlawLabel::SetLine(QLine line)
{
    m_line = line;
    update();
}



/**
 * @brief FWLineFlawLabel::paintEvent
 * @param e
 * @author Vincent
 * @date 2017/6/27
 * @note OSD绘制函数
 */
void FWLineFlawLabel::paintEvent(QPaintEvent *e)
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

    painter.drawLine(m_line);

    if(i_learn_result)
    {
        if(pencolor !=NULL)
        {
            pen.setColor(pencolor->m_vt_color[pencolor->task_osd.task_osd_Calc_color]);
            pen.setWidth(pencolor->task_osd.task_osd_Calc__width);
            painter.setPen(pen);
        }
        int count = m_data.count();
        for(int i = 0; i<count;i++)
        {
            painter.drawLine(m_data[i].x()-5,m_data[i].y(),m_data[i].x()+5,m_data[i].y());
            painter.drawLine(m_data[i].x(),m_data[i].y()-5,m_data[i].x(),m_data[i].y()+5);
        }
    }
    i_learn_result = 0;
}
void FWLineFlawLabel::SetPenColor(void *pen_color)
{
    this->m_pen_color = pen_color;
}
