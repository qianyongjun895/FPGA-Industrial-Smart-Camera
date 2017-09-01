#include "StepEditExcuteLabel.h"
#include <QPen>
#include <stdio.h>
#include <math.h>
#include <qdebug.h>

StepEditExcuteLabel::StepEditExcuteLabel(QWidget *parent) : QLabel(parent)
{
    m_paint = 0;
}
StepEditExcuteLabel::~StepEditExcuteLabel()
{

}
void StepEditExcuteLabel::paintEvent(QPaintEvent *e)
{
    QLabel::paintEvent(e);
    QPainter painterPic(this);

    if(m_paint == 1)
    {
        qDebug()<<"m_paint===1";
        painterPic.drawPixmap(0, 0, m_pix);

    }else
    {
        painterPic.drawPoint(-3,-3);
    }
}
void StepEditExcuteLabel::mousePressEvent(QMouseEvent *ev)
{
    QLabel::mousePressEvent(ev);
}
void StepEditExcuteLabel::mouseMoveEvent(QMouseEvent *ev)
{
    QLabel::mouseMoveEvent(ev);
}
void StepEditExcuteLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    QLabel::mouseReleaseEvent(ev);
}

void StepEditExcuteLabel::Update()
{
    repaint();
}
void StepEditExcuteLabel::SetPixMap(QPixmap pix)
{
    qDebug()<<"SetPixMap";
    m_paint = 1;
    this->m_pix = pix;
    repaint();
}
void StepEditExcuteLabel::ListOSD()
{
    m_paint = 1;
    repaint();
}
void StepEditExcuteLabel::ClearOSD()
{
    m_paint = 0;
    repaint();
}
