#include "LabelHSIPicAdjust.h"
#include <QDir>

LabelHSIPicAdjust::LabelHSIPicAdjust(QWidget *parent) : QLabel(parent)
{
    QString path;
    QDir dir;
    path=dir.currentPath()+"/image/Buttons/";
    //QString strName = path+"color.jpg";
    QString strName = path+"color.bmp";

    m_image.load(strName);
    m_y1 = 30;
    m_y2 = 100;
    m_x1 = 50;
    m_x2 = 80;
    lineKind = 0;
}
void LabelHSIPicAdjust::mousePressEvent(QMouseEvent *e)
{
    startTime = QTime::currentTime();
    lineKind = 0;
    int x = e->x();
    int y= e->y();
    int iwidth = 30;
    int iTemp = 40;
    QRect rectOne(this->width()-30,m_y1-20,iwidth,iTemp);
    QRect rectTwo(this->width()-30,m_y2-20,iwidth,iTemp);
    QRect rectThree(this->m_x1-20,this->height()-30,iwidth,iTemp);
    QRect rectFour(this->m_x2-20,this->height()-30,iwidth,iTemp);

    if(rectOne.contains(x,y))
    {
        lineKind =1;
    }else if(rectTwo.contains(x,y))
    {
        lineKind =2;
    }else if(rectThree.contains(x,y))
    {
        lineKind =3;
    }else if(rectFour.contains(x,y))
    {
        lineKind =4;
    }

}
void LabelHSIPicAdjust::mouseMoveEvent(QMouseEvent *e)
{
    if(lineKind == 1)
    {
        if(e->y()>=10 && e->y()<=110)
        {
            if(e->y() < this->m_y2)
                this->m_y1 = e->y();
            else
            {
                this->m_y1 = e->y();
                this->m_y2 = e->y()+1;
            }
            update();
        }

    }else if(lineKind == 2)
    {
        if(e->y()>=10 && e->y()<=110)
        {
            if(e->y()>this->m_y1)
                this->m_y2 = e->y();
            else
            {
                this->m_y2 = e->y();
                this->m_y1 = e->y()-1;
            }
            update();
        }

    }else if(lineKind == 3)
    {
        if(e->x()>=10 && e->x()<=190)
        {
            /*if(e->x() < this->m_x2)
                this->m_x1 = e->x();
            else
            {
                this->m_x1 = e->x();
                this->m_x2 = e->x()+1;
            }*/
            this->m_x1 = e->x();
            update();
        }

    }else if(lineKind == 4)
    {
        if(e->x()>=10 && e->x()<=190)
        {
            /*if(e->x()> this->m_x1)
                this->m_x2 = e->x();
            else
            {
                this->m_x2 = e->x();
                this->m_x1 = e->x()-1;
            }*/
            this->m_x2 = e->x();
            update();
        }

     }
    stopTime = QTime::currentTime();
    int elapsed = startTime.msecsTo(stopTime);
    if(elapsed>1000)
    {
        startTime = stopTime;
        SignalHS(m_x2-10,m_x1-10,m_y2-10,m_y1-10);
    }

}
void LabelHSIPicAdjust::mouseReleaseEvent(QMouseEvent *e)
{
    if (lineKind == 0)
    {
        return;
    }

    if(lineKind == 1)
    {
        if(e->y()>=10 && e->y()<=110)
        {
            if(e->y() < this->m_y2)
                this->m_y1 = e->y();
            update();
        }


    }else if(lineKind == 2)
    {
        if(e->y()>=10 && e->y()<=110)
        {
            if(e->y() > this->m_y1)
                this->m_y2 = e->y();
            update();
        }


    }else if(lineKind == 3)
    {
        if(e->x()>=10 && e->x()<=190)
        {
            //if(e->x() < this->m_x2)
              //  this->m_x1 = e->x();
            update();
        }

    }else if(lineKind == 4)
    {
        if(e->x()>=10 && e->x()<=190)
        {
            //if(e->x()>this->m_x1)
              //  this->m_x2 = e->x();
            update();
        }
    }
    SignalHS(m_x2-10,m_x1-10,m_y2-10,m_y1-10);

}
void LabelHSIPicAdjust::paintEvent(QPaintEvent *e)
{
    QLabel::paintEvent(e);
    QPainter painter(this);
    painter.drawImage(10,10,m_image.scaled(180,100));
    QPen pen;
    pen.setColor(Qt::white);
    pen.setWidth(1);
    painter.setPen(pen);

    painter.drawLine(10,this->m_y1,this->width()-30,this->m_y1);
    painter.drawLine(10,this->m_y2,this->width()-30,this->m_y2);

    painter.drawLine(this->m_x1,10,this->m_x1,this->height()-30);
    painter.drawLine(this->m_x2,10,this->m_x2,this->height()-30);

    pen.setColor(Qt::black);
    pen.setWidth(2);
    painter.setPen(pen);
    if(m_x2 >= m_x1)
    {
        painter.drawLine(m_x1,m_y1,m_x2,m_y1);
        painter.drawLine(m_x2,m_y1,m_x2,m_y2);
        painter.drawLine(m_x2,m_y2,m_x1,m_y2);
        painter.drawLine(m_x1,m_y2,m_x1,m_y1);

    }else
    {
        painter.drawLine(m_x2,m_y1,m_x2,m_y2);
        painter.drawLine(m_x1,m_y2,m_x1,m_y1);

        painter.drawLine(10,m_y1,m_x2,m_y1);
        painter.drawLine(10,m_y2,m_x2,m_y2);

        painter.drawLine(m_x1,m_y1,190,m_y1);
        painter.drawLine(m_x1,m_y2,190,m_y2);

    }

    pen.setColor(Qt::green);
    pen.setWidth(1);
    painter.setPen(pen);

    painter.drawLine(this->width()-30,this->m_y1,this->width()-2,this->m_y1-15);
    painter.drawLine(this->width()-30,this->m_y1,this->width()-2,this->m_y1+15);
    painter.drawLine(this->width()-2,this->m_y1-15,this->width()-2,this->m_y1+15);

    painter.drawLine(this->width()-30,this->m_y2,this->width()-2,this->m_y2-15);
    painter.drawLine(this->width()-30,this->m_y2,this->width()-2,this->m_y2+15);
    painter.drawLine(this->width()-2,this->m_y2-15,this->width()-2,this->m_y2+15);

    painter.drawLine(this->m_x1,this->height()-30,this->m_x1-15,this->height()-2);
    painter.drawLine(this->m_x1,this->height()-30,this->m_x1+15,this->height()-2);
    painter.drawLine(this->m_x1-15,this->height()-2,this->m_x1+15,this->height()-2);

    painter.drawLine(this->m_x2,this->height()-30,this->m_x2-15,this->height()-2);
    painter.drawLine(this->m_x2,this->height()-30,this->m_x2+15,this->height()-2);
    painter.drawLine(this->m_x2-15,this->height()-2,this->m_x2+15,this->height()-2);

    for (int i=0; i< m_vt_h.count();i++)
    {
        pen.setColor(Qt::gray);
        pen.setWidth(1);
        painter.setPen(pen);
        QPoint pointTemp(m_vt_h[i],m_vt_s[i]);
        painter.drawPoint(pointTemp);
    }
}
void LabelHSIPicAdjust::SetHS(int hMax,int sMax,int hMin,int sMin)
{
    m_y1 = sMin;
    m_y2 = sMax;
    m_x1 = hMin;
    m_x2 = hMax;

    if(this->m_y1 >110)
        this->m_y1= 110;
    if(m_y2 >110)
        m_y2 = 110;
    if(this->m_x1 >190)
        this->m_x2= 190;
    if(m_x2 >190)
        m_x2 = 190;
    if(this->m_y1 <10)
        this->m_y1= 10;
    if(m_y2 <10)
        m_y2 = 10;
    if(this->m_x1 < 10)
        this->m_x2= 10;
    if(m_x2 <10)
        m_x2 = 10;

    update();

}
void LabelHSIPicAdjust::SetHSs(QVector<int>vtH,QVector<int>vtS)
{
    m_vt_h = vtH;
    m_vt_s = vtS;
    update();
}
