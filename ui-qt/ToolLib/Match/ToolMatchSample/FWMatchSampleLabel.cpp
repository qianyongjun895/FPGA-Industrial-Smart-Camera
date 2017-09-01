#include "FWMatchSampleLabel.h"
#include <QDebug>
#include "BasicDefine.h"
FWMatchSampleLabel::FWMatchSampleLabel(QWidget *parent) : QLabel(parent)
{
    this->m_pen_color = NULL;
}

/**
 * @brief FWMatchBaseLineLabel::paintEvent
 * @param e
 * @author dgq
 * @note 基准线绘制OSD
 */
void FWMatchSampleLabel::paintEvent(QPaintEvent *e)
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

}

/**
 * @brief FWMatchBaseLineLabel::mousePressEvent
 * @param ev
 * @author dgq
 * @note 鼠标按下事件的响应函数
 */
void FWMatchSampleLabel::mousePressEvent(QMouseEvent *ev)
{

    QLabel::mousePressEvent(ev);
}

/**
 * @brief FWMatchBaseLineLabel::mouseMoveEvent
 * @param ev
 * @author dgq
 * @note 鼠标移动事件响应函数
 */
void FWMatchSampleLabel::mouseMoveEvent(QMouseEvent *ev)
{
    QLabel::mouseMoveEvent(ev);
}

/**
 * @brief FWMatchBaseLineLabel::mouseReleaseEvent
 * @param ev
 * @author dgq
 * @note 鼠标释放事件响应函数
 */
void FWMatchSampleLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    QLabel::mouseReleaseEvent(ev);
}
void FWMatchSampleLabel::SetPenColor(void *pen_color)
{
    this->m_pen_color = pen_color;
}




