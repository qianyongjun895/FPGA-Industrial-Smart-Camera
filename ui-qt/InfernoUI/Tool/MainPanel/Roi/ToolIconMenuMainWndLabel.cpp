#include "ToolIconMenuMainWndLabel.h"
#include <QPen>
#include <stdio.h>
#include <math.h>
#include <qdebug.h>
ToolIconMenuMainWndLabel::ToolIconMenuMainWndLabel(QWidget *parent) : QLabel(parent)
{
    m_paint = 0;
}
ToolIconMenuMainWndLabel::~ToolIconMenuMainWndLabel()
{

}
void ToolIconMenuMainWndLabel::paintEvent(QPaintEvent *e)
{
    QLabel::paintEvent(e);
    QPainter painterPic(this);

    if(m_paint == 1)
    {
        painterPic.drawPixmap(0, 0, m_pix);

    }else
    {
        painterPic.drawPoint(-3,-3);
    }
}
void ToolIconMenuMainWndLabel::mousePressEvent(QMouseEvent *ev)
{
    QLabel::mousePressEvent(ev);
}
void ToolIconMenuMainWndLabel::mouseMoveEvent(QMouseEvent *ev)
{
    QLabel::mouseMoveEvent(ev);
}
void ToolIconMenuMainWndLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    QLabel::mouseReleaseEvent(ev);
}

void ToolIconMenuMainWndLabel::Update()
{
    repaint();
}
void ToolIconMenuMainWndLabel::SetPixMap(QPixmap pix)
{
    m_paint = 1;
    this->m_pix = pix;
    repaint();
}
void ToolIconMenuMainWndLabel::ClearOSD()
{
    m_paint = 0;
    repaint();
}
