
#include "LabelGrayHistogram.h"
#include <qdebug.h>
#include <QPen>

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#define LINEWIDTH 30

LabelGrayHistogram::LabelGrayHistogram(QWidget *parent) : QLabel(parent)
{
    m_max =100;
    m_mode = -1;
    for(int i=0; i<2560;i++)
    {
        m_grade[i] = 0;
    }
}

void LabelGrayHistogram::mousePressEvent(QMouseEvent *e)
{
    QLabel::mousePressEvent(e);
}

void LabelGrayHistogram::mouseMoveEvent(QMouseEvent *e)
{
    QLabel::mouseMoveEvent(e);
}

void  LabelGrayHistogram::mouseReleaseEvent(QMouseEvent *e)
{
    QLabel::mouseReleaseEvent(e);
}
void LabelGrayHistogram::PaintGray(QPainter *painter)
{
    painter->drawLine(100,400,610,400);//x轴
    painter->drawLine(600,390,610,400);
    painter->drawLine(600,410,610,400);
    painter->drawLine(100,400,100,100);//y轴
    painter->drawLine(90,110,100,100);
    painter->drawLine(110,110,100,100);
    painter->drawText(90,420,"0");
    painter->drawText(610,420,"255");

    int i = 0;
    for(i= 1; i< 15;i++)
    {
        painter->drawLine(100+i*34,400,100+i*34,395);
        painter->drawText(100+i*34-5,420,QString::number(15+16*(i-1)));
    }

    int iGrade = this->m_max/10;
    //painter->drawText(60,100+5,QString::number(m_max));
    //painter->drawText(100,100,QString::number(m_max));
    for(i = 1;i<10;i++)
    {
       painter->drawLine(100,100+i*30,105,100+i*30);
       //painter->drawText(60,100+i*30+5,QString::number(m_max-iGrade*i));
       /*QString strTemp = QString::number(10-i);
       strTemp +="/10";
       painter->drawText(60,100+i*30+5,strTemp);*/
    }

    float fScale = 0.0;
    fScale = 300.0/m_max*1.0;
    int iMax = m_grade[0];
    int iIndex = 0;
    for(i = 0; i<255;i++)
    {
        if(m_grade[i] > iMax)
        {
            iMax = m_grade[i];
            iIndex = i;
        }
        painter->drawLine(100+i*2,400-m_grade[i]*fScale,100+i*2+1,400-m_grade[i+1]*fScale);
    }
    painter->drawText(100+iIndex*2,400-m_grade[iIndex]*fScale,QString::number(m_max));
}
void LabelGrayHistogram::PaintByColoum(QPainter *painter)
{
    painter->drawLine(0,400,640,400);//x轴
    painter->drawLine(630,390,640,400);
    painter->drawLine(630,410,640,400);
    painter->drawLine(0,400,0,100);//y轴
    painter->drawLine(-10,110,0,100);
    painter->drawLine(10,110,0,100);
    painter->drawText(3,420,"0");
    painter->drawText(610,420,"640");

    int i = 0;
    for(i= 1; i< 15;i++)
    {
        painter->drawLine(i*42,400,i*42,395);
        painter->drawText(i*42-8,420,QString::number(42+42*(i-1)));
    }

    int iGrade = this->m_max/10;
    //painter->drawText(0,100+5,QString::number(m_max));
    //painter->drawText(0,100,QString::number(m_max));

    for(i = 1;i<10;i++)
    {
       painter->drawLine(0,100+i*30,5,100+i*30);
       //painter->drawText(5,100+i*30+10,QString::number(m_max-iGrade*i));
       /*QString strTemp = QString::number(10-i);
       strTemp +="/10";
       painter->drawText(5,100+i*30+5,strTemp);*/
    }

    float fScale = 0.0;
    fScale = 300.0/m_max*1.0;
    int iMax = m_grade[0];
    int iIndex = 0;

    for(i = 0; i<639;i++)
    {
        if(m_times == 4)
            painter->drawLine(i,400-m_grade[i*4]*fScale,i+1,400-m_grade[i*4+4]*fScale);
        else if(m_times  == 2)
            painter->drawLine(i,400-m_grade[i*2]*fScale,i+1,400-m_grade[i*2+2]*fScale);
        else if(m_times  == 1)
            painter->drawLine(i,400-m_grade[i]*fScale,i+1,400-m_grade[i+1]*fScale);
        if(m_grade[i*m_times] > iMax)
        {
            iMax = m_grade[i*m_times];
            iIndex = i;
        }
    }
    painter->drawText(iIndex,400-m_grade[iIndex*m_times]*fScale,QString::number(m_max));
}
void LabelGrayHistogram::PaintByRow(QPainter *painter)
{
    painter->drawLine(100,400,580,400);//x轴
    painter->drawLine(570,390,580,400);
    painter->drawLine(570,410,580,400);
    painter->drawLine(100,400,100,100);//y轴
    painter->drawLine(90,110,100,100);
    painter->drawLine(110,110,100,100);
    painter->drawText(90,420,"0");
    painter->drawText(580,420,"480");

    int i = 0;
    for(i= 1; i< 15;i++)
    {
        painter->drawLine(100+i*32,400,100+i*32,395);
        painter->drawText(100+i*32-5,420,QString::number(32+32*(i-1)));
    }

    int iGrade = this->m_max/10;
    //painter->drawText(60,100+5,QString::number(m_max));
    //painter->drawText(100,100,QString::number(m_max));

    for(i = 1;i<10;i++)
    {
       painter->drawLine(100,100+i*30,105,100+i*30);
       //painter->drawText(60,100+i*30+5,QString::number(m_max-iGrade*i));
       /*QString strTemp = QString::number(10-i);
       strTemp += "/10";
       painter->drawText(60,100+i*30+5,strTemp);*/
    }

    float fScale = 0.0;
    fScale = 300.0/m_max*1.0;
    int iMax = m_grade[0];
    int iIndex = 0;
    for(i = 0; i<479;i++)
    {
        if(m_times == 1)
            painter->drawLine(100+i,400-m_grade[i]*fScale,100+i+1,400-m_grade[i+1]*fScale);
        else if(m_times == 2)
            painter->drawLine(100+i,400-m_grade[i*2]*fScale,100+i+1,400-m_grade[i*2+2]*fScale);
        else if(m_times == 4)
            painter->drawLine(100+i,400-m_grade[i*4]*fScale,100+i+1,400-m_grade[i*4+4]*fScale);
        if(m_grade[i*m_times] > iMax)
        {
            iMax = m_grade[i*m_times];
            iIndex = i;
        }
    }
    painter->drawText(100+iIndex,400-m_grade[iIndex*m_times]*fScale,QString::number(m_max));
}
void LabelGrayHistogram::paintEvent(QPaintEvent *e)
{
    QLabel::paintEvent(e);
    QPainter painter(this);

    QPen pen;
    pen.setColor(Qt::red);
    pen.setWidth(1);
    painter.setPen(pen);
    if(m_mode == 0)
    {
        PaintGray(&painter);
    }else if(m_mode == 1) //列
    {
        PaintByColoum(&painter);

    }else if(m_mode == 2) //行
    {
        PaintByRow(&painter);
    }

}
void LabelGrayHistogram::SetGrade(unsigned int *gradeArr, int size, int mode,int times)
{
    this->m_size = size;
    this->m_mode = mode;
    m_times = times;
    m_max = gradeArr[0];

    for(int i = 0;i<size;i++)
    {
        this->m_grade[i] = gradeArr[i];

        if(gradeArr[i] > m_max)
        {
            m_max = gradeArr[i];
        }
    }
    update();
}
