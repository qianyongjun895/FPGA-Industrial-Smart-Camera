#include "ScaleImageLabel.h"
#include <QDebug>

ScaleImageLabel::ScaleImageLabel(QWidget *parent) : QLabel(parent)
{
    m_num = 2;
    m_select = 0;
    m_current_index = 0;
    m_point[0].rx() = 270;
    m_point[0].ry() = 240;
    m_point[1].rx() = 370;
    m_point[1].ry() = 240;
}

ScaleImageLabel::~ScaleImageLabel()
{

}

void ScaleImageLabel::SetCurrentPointIndex(int index)
{
    m_current_index = index;
    update();
}

void ScaleImageLabel::KeyMoveUp(int value)
{
    int x,y;
    x = m_point[m_current_index].x();
    y = m_point[m_current_index].y()-value;
    if(y < 0)
    {
        return;
    }
    m_point[m_current_index].setX(x);
    m_point[m_current_index].setY(y);
    update();
    CurrentPointChangeSignal(m_current_index,m_point[m_current_index]);
}

void ScaleImageLabel::KeyMoveDown(int value)
{
    int x,y;
    x = m_point[m_current_index].x();
    y = m_point[m_current_index].y()+value;
    if(y > 480)
    {
        return;
    }
    m_point[m_current_index].setX(x);
    m_point[m_current_index].setY(y);
    update();
    CurrentPointChangeSignal(m_current_index,m_point[m_current_index]);
}

void ScaleImageLabel::KeyMoveLeft(int value)
{
    int x,y;
    x = m_point[m_current_index].x()-value;
    y = m_point[m_current_index].y();
    if(x < 0)
    {
        return;
    }
    m_point[m_current_index].setX(x);
    m_point[m_current_index].setY(y);
    update();
    CurrentPointChangeSignal(m_current_index,m_point[m_current_index]);
}

void ScaleImageLabel::KeyMoveRight(int value)
{
    int x,y;
    x = m_point[m_current_index].x()+value;
    y = m_point[m_current_index].y();
    if(x > 640)
    {
        return;
    }
    m_point[m_current_index].setX(x);
    m_point[m_current_index].setY(y);
    update();
    CurrentPointChangeSignal(m_current_index,m_point[m_current_index]);
}

void ScaleImageLabel::GetPointByIndex(int index, QPoint &point)
{
    point = m_point[index];
}

void ScaleImageLabel::paintEvent(QPaintEvent *e)
{
    QLabel::paintEvent(e);
    QPainter painter(this);
    QPen pen;
    pen.setColor(Qt::red);
    pen.setWidth(2);
    painter.setPen(pen);

    for(int i=0;i<m_num;i++)
    {
        painter.drawEllipse(m_point[i],10,10);
        painter.drawLine(m_point[i].x()+20,m_point[i].y(),m_point[i].x()-20,m_point[i].y());
        painter.drawLine(m_point[i].x(),m_point[i].y()+20,m_point[i].x(),m_point[i].y()-20);
        painter.drawText(QPoint(m_point[i].x(),m_point[i].y()-20),QString::number(i+1));
    }
    painter.drawLine(m_point[0], m_point[1]);

    pen.setColor(Qt::blue);
    pen.setWidth(2);
    painter.setPen(pen);
    painter.drawEllipse(m_point[m_current_index],10,10);
    painter.drawLine(m_point[m_current_index].x()+20, \
                     m_point[m_current_index].y(), \
                     m_point[m_current_index].x()-20, \
                     m_point[m_current_index].y());
    painter.drawLine(m_point[m_current_index].x(), \
                     m_point[m_current_index].y()+20, \
                     m_point[m_current_index].x(), \
                     m_point[m_current_index].y()-20);
    painter.drawText(QPoint(m_point[m_current_index].x(), m_point[m_current_index].y()-20), \
                     QString::number(m_current_index+1));

}

void ScaleImageLabel::mousePressEvent(QMouseEvent *ev)
{
    m_select = 0;
    int x =ev->pos().x();
    int y = ev->pos().y();
    int i =0;
    for (i = 0; i< m_num; i++)
    {
        if(((x-m_point[i].x())*(x-m_point[i].x())+(y-m_point[i].y())*(y-m_point[i].y())) <= 20*20)
        {
            m_select = 1;
            m_current_index = i;
            CurrentPointChangeSignal(m_current_index,m_point[m_current_index]);
            break;
        }
    }
    m_press_point = ev->pos();
    update();
}

void ScaleImageLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    if(m_select != 0)
    {
        CurrentPointChangeSignal(m_current_index,m_point[m_current_index]);
        m_select = 0;
    }
}

void ScaleImageLabel::mouseMoveEvent(QMouseEvent *ev)
{
    QPoint pos = ev->pos();

    int disX = pos.x() - m_press_point.x();
    int disY = pos.y() - m_press_point.y();
    int ix = 0;
    int iy = 0;

    if(m_select ==1)
    {
        ix = m_point[m_current_index].x() + disX;
        iy = m_point[m_current_index].y() + disY;
        if(ix >= 0 && ix <= 640 && iy>=0 && iy<=480)
        {
            m_point[m_current_index].setX(m_point[m_current_index].x() + disX);
            m_point[m_current_index].setY(m_point[m_current_index].y() + disY);
            CurrentPointChangeSignal(m_current_index,m_point[m_current_index]);
        }
    }
    m_press_point = ev->pos();
    update();
}

