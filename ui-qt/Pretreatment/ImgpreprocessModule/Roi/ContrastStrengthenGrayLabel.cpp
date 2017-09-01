#include "ContrastStrengthenGrayLabel.h"
#include <QPaintEvent>
#include <QtMath>
#include <QMessageBox>
#include <stdio.h>

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

const QPointF ClickArea(5, 5);
ContrastStrengthenGrayLabel::ContrastStrengthenGrayLabel(QWidget *parent) :QLabel(parent)
{
    mMinPoint.setX(700);
    mMinPoint.setY(300);
    mMaxPoint.setX(700);
    mMaxPoint.setY(150);
    min = 0;
    max = 0;
    start = 0;
    end = 1;
    Point = false;
    m_i_balance = 0;
}


ContrastStrengthenGrayLabel::~ContrastStrengthenGrayLabel()
{

}

void ContrastStrengthenGrayLabel::show(QPen &pen, QPainter &painter)
{
    pen.setColor(Qt::red);
    painter.setPen(pen);
    painter.drawLine(0,0,0,300);
    painter.drawLine(0,300,600,300);
    int i = 0;
    for(i = 0; i < 7; i++)
    {
        painter.drawLine(100*(i+1),295,100*(i+1),300);
    }
    painter.drawLine(0,5,5,5);
    int iHeigth = this->height();
    int ihDis = (iHeigth-10)/2;
    painter.drawLine(0,5+ihDis,5,5+ihDis);
    painter.drawLine(0,5+ihDis*2,5,5+ihDis*2);

    if(!Point)
    {
        pen.setWidth(1);
        pen.setColor(Qt::red);
        painter.setPen(pen);
        //painter.scale(1,2);
        for(i = 0; i < (rePoints.count()-1); i++)
        {
            painter.drawLine(rePoints[i],rePoints[i+1]);
        }
    }
    else
    {
        pen.setWidth(3);
        pen.setColor(Qt::red);
        painter.setPen(pen);
        for(i = 0; i < (rePoints.count()-1); i++)
        {
            painter.drawPoint(rePoints[i]);
        }
    }
    pen.setWidth(1);
    pen.setColor(Qt::green);
    painter.setPen(pen);

    float y1;
    float y2;

    if(m_i_balance != 1)
    {
        if(m_yMax<0)
        {
            y1 = (m_yMax-min)*290.0/((max-min)*1.0);
        }
        else
        {
            y1 = 295.0-(m_yMax-min)*290.0/((max-min)*1.0);
        }

        if(m_yMin < 0){
            y2 = (m_yMin-min)*290.0/((max-min)*1.0);
        }
        else
        {
            y2 = 295.0-(m_yMin-min)*290.0/((max-min)*1.0);
        }
        painter.drawLine(QPointF(0,y1),QPointF(this->width(),y1));
        painter.drawLine(QPointF(0,y2),QPointF(this->width(),y2));
    }
}


void ContrastStrengthenGrayLabel::paintEvent(QPaintEvent *e)
{
    QLabel::paintEvent(e);
    QPainter painter(this);
    QPen pen;
    if(m_i_balance == 1)
    {
        pen.setColor(Qt::red);
        painter.setPen(pen);

        int dis = this->width()/16;
        int iheight = this->height();
        int y = iheight -5;
        for(int i = 1;i<16;i++)
        {
            painter.drawLine(i*dis,y,i*dis,iheight);
        }
    }


    painter.setRenderHint(QPainter::Antialiasing);
    show(pen, painter);
}
void ContrastStrengthenGrayLabel::ClearPoints()
{
    rePoints.clear();
    mMinPoint.setX(700);
    mMinPoint.setY(300);
    mMaxPoint.setX(700);
    mMaxPoint.setY(150);
    min = 0;
    max = 0;
    start = 0;
    end = 1;
    update();
}

void ContrastStrengthenGrayLabel::SetYMax(float iy)
{

    this->m_yMax = iy;
    update();
}

void ContrastStrengthenGrayLabel::SetYmin(float iy)
{
    this->m_yMin = iy;
    update();
}

void ContrastStrengthenGrayLabel::ValueChangeSlot(float Min,float Max,QVector<float> Value)
{
    min = Min;
    max = Max;
    mMaxPoint.setX(0);
    mMaxPoint.setY(149);
    mMinPoint.setX(0);
    rePoints.clear();

    int iheight = this->height();
    int ydis1 = iheight-10;
    int yDis2 = iheight-5;

    if(Max != 0)
    {
        if(Max<0)
            mMinPoint.setY((ydis1*Min)/Max);
        else
            mMinPoint.setY(yDis2-(ydis1*Min)/Max);
        int i = 0;
        QPointF Point;
        for(i = 0; i < Value.count(); i++)
        {
            Point.setX(((this->width()*i)/(Value.count()-1)));
            if(Value[i] < 0){
                Point.setY((ydis1*(Value[i]-Min))/(Max-Min));
            }
            else
            {
                Point.setY(yDis2-(ydis1*(Value[i]-Min))/(Max-Min));
            }
            rePoints.append(Point);
        }
        for(i = 0; i < Value.count(); i++)
        {
            if(Value[i] == min)
                mMinPoint.setX(i);
            if(Value[i] == max)
                mMaxPoint.setX(i);
            break;
        }
    }
    update();
}

void ContrastStrengthenGrayLabel::BalanceValueChangeSlot(int Min,int Max,QVector<int> Value)
{
    min = Min;
    max = Max;
    mMaxPoint.setX(0);
    mMaxPoint.setY(110);
    mMinPoint.setX(0);
    rePoints.clear();
    int iheight = this->height();
    int ydis1 = iheight-10;
    int yDis2 = iheight-5;
    if(Max != 0 && Max != Min)
    {
        if(Max<0)
            mMinPoint.setY((ydis1*Min)/Max);
        else
            mMinPoint.setY(yDis2-(ydis1*Min)/Max);
        int i = 0;
        QPointF Point;
        for(i = 0; i < Value.count(); i++)
        {
            Point.setX((this->width()*i)/(Value.count()-1));
            if(Value[i] < 0){
                Point.setY(ydis1*(Value[i]-Min)/(Max-Min));
            }
            else
            {
                Point.setY(yDis2-(ydis1*(Value[i]-Min))/(Max-Min));
            }
            //printf("Point[%d] = (%d , %d)\r\n",i,Point.x(),Point.y());
            rePoints.append(Point);
        }
        for(i = 0; i < Value.count(); i++)
        {
            if(Value[i] == min)
                mMinPoint.setX(i);
            if(Value[i] == max)
                mMaxPoint.setX(i);
            break;
        }
    }
    update();
}

void ContrastStrengthenGrayLabel::SetRange(int istart, int iend)
{
    start = istart;
    end = iend;
}

void ContrastStrengthenGrayLabel::SetPlayMode(bool point)
{
    Point = point;
    update();
}


void ContrastStrengthenGrayLabel::wheelEvent(QWheelEvent *event)
{
    int sub;
    if((end-start)>200 )
        sub = 5;
    else
        sub = 1;
    if(event->delta() < 0)
    {

        if(end > event->pos().x()*(end-start)/600 - 1)
            end = end+sub;
        if(start < event->pos().x()*(end-start)/600 - 1)
            start = start-sub;
        if(start < 1)
            start = 1;
        if(end == start && start != 0 )
        {
            end = end+1;
            start = start-1;
        }
    }
    else
    {
        if(end > event->pos().x()*(end-start)/600)
            end = end-sub;
        if(start < event->pos().x()*(end-start)/600 && start < 2000)
            start = start+sub;
        if(end == start && start != 0 )
        {
            end = end+1;
            start = start-1;
        }
    }
    emit paintSignal(start, end);
}
void ContrastStrengthenGrayLabel::SetBalance(int flag)
{
    m_i_balance = flag;
    update();
}

