#include "MatchineLabel.h"
#include <QPen>
#include <stdio.h>
#include <math.h>
#include <qdebug.h>
#define R 60

MatchineLabel::MatchineLabel(QWidget *parent) : QLabel(parent)
{
    m_y1 = 240;
    m_x1 = 320;
    kind = 0;
}
MatchineLabel::~MatchineLabel()
{

}
void MatchineLabel::paintEvent(QPaintEvent *e)
{
    QLabel::paintEvent(e);
    QPainter painterPic(this);
    QPen pen;
    pen.setColor(Qt::red);
    pen.setWidth(1);
    painterPic.setPen(pen);
    painterPic.drawLine(320-R,240,320+R,240);
    painterPic.drawLine(320,240-R,320,240+R);
    painterPic.drawEllipse(QPointF(320,240),R,R);
    painterPic.drawLine(0,m_y1,640,m_y1);
    painterPic.drawLine(m_x1,0,m_x1,480);

    painterPic.drawLine(640,m_y1,630,m_y1-15);
    painterPic.drawLine(620,m_y1,630,m_y1-15);
    painterPic.drawLine(640,m_y1,630,m_y1+15);
    painterPic.drawLine(620,m_y1,630,m_y1+15);

    painterPic.drawLine(m_x1,0,m_x1-15,10);
    painterPic.drawLine(m_x1-15,10,m_x1,20);
    painterPic.drawLine(m_x1,0,m_x1+15,10);
    painterPic.drawLine(m_x1+15,10,m_x1,20);

}
void MatchineLabel::mousePressEvent(QMouseEvent *ev)
{
    int x = ev->pos().x();
    int y = ev->pos().y();
    kind = 0;

    if(y> this->m_y1 -30 && y<this->m_y1 +30)
        kind =2;
    else if(x > this->m_x1-30 && x <this->m_x1 +30)
        kind =1;
    if(kind !=0)
        update();


    QLabel::mousePressEvent(ev);
}
void MatchineLabel::mouseMoveEvent(QMouseEvent *ev)
{
    int x = ev->pos().x();
    int y = ev->pos().y();
    if(kind == 1) //x
    {
        if(x <0)
            this->m_x1 = 0;
        else if(x > 640)
            this->m_x1 = 640;
        else
            this->m_x1 = x;
        update();

    }else if(kind == 2) //y
    {
        if(y < 0)
            this->m_y1 = 0;
        else if(y > 480)
            this->m_y1 = 480;
        else
            this->m_y1 = y;
        update();
    }

    QLabel::mouseMoveEvent(ev);
}
void MatchineLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    QLabel::mouseReleaseEvent(ev);
}
