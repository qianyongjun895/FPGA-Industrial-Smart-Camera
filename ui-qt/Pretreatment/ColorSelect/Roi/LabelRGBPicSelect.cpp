#include "LabelRGBPicSelect.h"
#include <QDebug>
LabelRGBPicSelect::LabelRGBPicSelect(QWidget *parent): QLabel(parent)
{
    m_x_start = 0;
    m_y_start = 0;
    m_x_end = 0;
    m_y_end = 0;
}
void LabelRGBPicSelect::mousePressEvent(QMouseEvent *e)
{
    m_x_start = e->pos().x();
    m_y_start = e->pos().y();

}
void LabelRGBPicSelect::mouseMoveEvent(QMouseEvent *e)
{
    m_x_end = e->pos().x();
    m_y_end = e->pos().y();
    update();

}
void  LabelRGBPicSelect::mouseReleaseEvent(QMouseEvent *e)
{
    m_x_end = e->pos().x();
    m_y_end = e->pos().y();
    int xTemp; int yTemp;
    xTemp = m_x_start;
    yTemp = m_y_start;
    if(m_x_start > m_x_end)
    {
        m_x_start = m_x_end;
        m_x_end = xTemp;
    }
    if(m_y_start > m_y_end)
    {
        m_y_start = m_y_end;
        m_y_end = yTemp;
    }
    if(m_x_start == m_x_end)
    {
        m_x_end = m_x_start+2;
    }
    if(m_y_start == m_y_end)
    {
        m_y_end = m_y_start+2;
    }
    QRect rect(QPoint(m_x_start,m_y_start),QPoint(m_x_end,m_y_end));
    m_rect = rect;
    SignalsRect();
    update();
}
void LabelRGBPicSelect::paintEvent(QPaintEvent *e)
{
    QLabel::paintEvent(e);
    QPainter painter(this);
    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(2);
    painter.setPen(pen);
    QRect rect(QPoint(m_x_start,m_y_start),QPoint(m_x_end,m_y_end));
    painter.drawRect(rect);
    m_rect = rect;


}
