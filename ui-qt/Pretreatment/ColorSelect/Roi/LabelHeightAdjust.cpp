
#include "LabelHeightAdjust.h"
#include "QDebug"
#include <QPen>

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#define LINEWIDTH 30

LabelHeightAdjust::LabelHeightAdjust(QWidget *parent) : QLabel(parent)
{
    this->m_r = 255;
    this->m_g = 255;
    this->m_b = 255;
    m_x1 = 0;
    m_y1 =30;
    m_x2 = 0;
    m_y2 = 100;

    df_line1 = 0;
    df_line2 = 0;

    lineKind = 0;
    m_fun = NULL;
    m_heigth = height();

    showtextEnable = true;
    m_b_edit_paint = true;
}

void LabelHeightAdjust::mousePressEvent(QMouseEvent *e)
{
    if (!m_b_edit_paint)
        return;

    startTime = QTime::currentTime();

    lineKind = 0;
    int x = e->x();
    int y= e->y();
    int iwidth = this->width()-30-2;
    int iTemp = 40;
    QRect rectOne(30,m_y1-20,iwidth,iTemp);
    QRect rectTwo(30,m_y2-20,iwidth,iTemp);

    if(rectOne.contains(x,y))
    {
         lineKind =1;
    }else if(rectTwo.contains(x,y))
    {
         lineKind =2;
    }
}

void LabelHeightAdjust::mouseMoveEvent(QMouseEvent *e)
{
    if (!m_b_edit_paint)
        return;
    if(lineKind == 1)
    {
        if (e->y() >= 10 && e->y()<= 138)
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
        if (e->y() >= 10 && e->y() <= 138)
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
    }
    stopTime = QTime::currentTime();
    int elapsed = startTime.msecsTo(stopTime);
    if(elapsed>1000)
    {
        startTime = stopTime;
        SignalI(this->m_y2-10,this->m_y1-10);
    }
}

void  LabelHeightAdjust::mouseReleaseEvent(QMouseEvent *e)
{
    if (!m_b_edit_paint)
        return;

    if (lineKind == 0)
    {
        return;
    }

    if (lineKind == 1)
    {
        if (e->y() >= 10 && e->y()<= 138)
        {
            if(e->y() < this->m_y2)
            this->m_y1 = e->y();
        }
    }
    else if (lineKind == 2)
    {
        if (e->y() >= 10 && e->y() <= 138)
        {
            if(e->y() > this->m_y1)
            this->m_y2 = e->y();
        }
    }
    SignalI(this->m_y2-10,this->m_y1-10);

    //LineMovedSignal();
    /*
    if (m_fun != NULL)
    {
        m_fun(this->m_y1, this->m_y2, this->m_p_this);
    }
    */
}

void LabelHeightAdjust::paintEvent(QPaintEvent *e)
{
    QLabel::paintEvent(e);
    QPainter painter(this);

    QLinearGradient linearGradient(0,10,0,128);
    linearGradient.setColorAt(0,QColor((int)m_r,(int)m_g,(int)m_b,128));
    linearGradient.setColorAt(1,Qt::black);
    painter.setBrush(linearGradient);
    painter.drawRect(0,10,LINEWIDTH,128);

    QPen pen;
    pen.setColor(Qt::green);
    pen.setWidth(1);
    painter.setPen(pen);

    painter.drawLine(0,this->m_y1,LINEWIDTH,this->m_y1);
    painter.drawLine(0,this->m_y2,LINEWIDTH,this->m_y2);

    painter.drawLine(LINEWIDTH,this->m_y1,this->width()-2,this->m_y1-15);
    painter.drawLine(LINEWIDTH,this->m_y1,this->width()-2,this->m_y1+15);
    painter.drawLine(this->width()-2,this->m_y1-15,this->width()-2,this->m_y1+15);

    painter.drawLine(LINEWIDTH,this->m_y2,this->width()-2,this->m_y2-15);
    painter.drawLine(LINEWIDTH,this->m_y2,this->width()-2,this->m_y2+15);
    painter.drawLine(this->width()-2,this->m_y2-15,this->width()-2,this->m_y2+15);


    pen.setColor(Qt::white);
    painter.setPen(pen);

    int count = m_vt_i_pic.count();
    for(int i= 0; i< count; i++)
    {
        painter.drawPoint(15,m_vt_i_pic[i]);
        painter.drawPoint(16,m_vt_i_pic[i]);
        painter.drawPoint(17,m_vt_i_pic[i]);
        painter.drawPoint(18,m_vt_i_pic[i]);
        painter.drawPoint(19,m_vt_i_pic[i]);
    }




    /*if (showtextEnable)
    {
        if (m_y1 > m_y2)
        {
            painter.drawText(10, m_y1 - 2, QString::number(df_line1));
            painter.drawText(10, m_y2 - 2, QString::number(df_line2));
        }
        else
        {
            painter.drawText(10, m_y1 - 2, QString::number(df_line2));
            painter.drawText(10, m_y2 - 2, QString::number(df_line1));
        }
    }*/

}
void LabelHeightAdjust::SetRGB(int r,int g,int b)
{
    this->m_r = r;
    this->m_g = g;
    this->m_b = b;
    update();
}
void LabelHeightAdjust::SetLowHighYValue(int yLow,int yHight)
{
    this->m_y1 = yLow;
    this->m_y2 = yHight;
    update();
}

void LabelHeightAdjust::SetSize(int iwidth,int iheigth)
{
    this->m_heigth = iheigth;
    this->m_width = iwidth;
    this->m_y2 = iheigth - 100;
}
void LabelHeightAdjust::Up()
{
    if(lineKind == 1)
    {
        if (this->m_y1>0 && this->m_y1 < this->height())
        {
            this->m_y1--;
            update();
        }

    }
    else if (lineKind == 2)
    {
        if (this->m_y2>0 && this->m_y2 < this->height())
        {
            this->m_y2--;
            update();
        }
    }
    else
        return;

    LineMovedSignal();
}
void LabelHeightAdjust::Down()
{
    if(lineKind == 1)
    {
        if (this->m_y2>0 && this->m_y2 < this->height())
        {
            this->m_y1++;
            update();
        }

    }else if(lineKind == 2)
    {
        if (this->m_y2>0 && this->m_y2 < this->height())
        {
            this->m_y2++;
            update();
        }
    }
    else
        return;

    LineMovedSignal();
}

void LabelHeightAdjust::setCallBack(void(*fun)(int, int, void*), void *pthis)
{

    m_fun = fun;
    m_p_this = pthis;

}

void LabelHeightAdjust::setLineVaule(double v1, double v2)
{
    df_line1 = v1;
    df_line2 = v2;
    update();
}
void LabelHeightAdjust::SetEditPaint(bool bflag)
{
    m_b_edit_paint = bflag;
}
void LabelHeightAdjust::SetVtPic(QVector<int>vtPic)
{
    m_vt_i_pic = vtPic;
    update();
}
