#include "StepExcuteLabel.h"
#include <QPen>
#include <stdio.h>
#include <math.h>
#include <qdebug.h>
StepExcuteLabel::StepExcuteLabel(QWidget *parent) : QLabel(parent)
{
    m_index = 1;
}
StepExcuteLabel::~StepExcuteLabel()
{

}
void StepExcuteLabel::paintEvent(QPaintEvent *e)
{
    QLabel::paintEvent(e);
    QPainter painterPic(this);
    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(1);
    painterPic.setPen(pen);

    int iWidth = this->width();
    int iHeight = this->height();
    int iColoum = 25;

    painterPic.drawLine(0,0,iWidth,0);
    painterPic.drawLine(iWidth-2,0,iWidth-1,iHeight-2);
    painterPic.drawLine(iWidth-2,iHeight-2,0,iHeight-2);
    painterPic.drawLine(0,iHeight,0,0);
    //common
    for(int i = 1;i<=3;i++)
    {
        painterPic.drawLine(0,i*iColoum,iWidth,i*iColoum);

    }
    //painterPic.drawText(10,iColoum-10,"错误码:");
    painterPic.drawText(10,1*iColoum-5,"OK计数:");
    painterPic.drawText(10,2*iColoum-5,"NG计数:");
    painterPic.drawText(10,3*iColoum-5,"总计数:");
    painterPic.drawLine(iWidth/2,0,iWidth/2,3*iColoum);

    if(m_vtHead.count() >=5)
    {
        painterPic.drawText(iWidth/2+10,1*iColoum-5,m_vtHead[2].strValue);
        painterPic.drawText(iWidth/2+10,2*iColoum-5,m_vtHead[3].strValue);
        int total = m_vtHead[2].strValue.toInt()+m_vtHead[3].strValue.toInt();
        painterPic.drawText(iWidth/2+10,3*iColoum-5,QString::number(total));
    }

    if(m_vtBody.count() > 0)
    {
        painterPic.drawLine(0,4*iColoum,iWidth,4*iColoum);
        QString strNo;
        strNo = "NO.";
        strNo += QString::number(m_index);
        painterPic.drawText(10,4*iColoum-5,strNo);

        int count = m_vtBody.count();
        int i=0;
        int j = 0;
        int len =0;
        for(j =0; j<count;j++)
        {
            if(m_vtBody[j].strName == " ")
                continue;
            if(QLabel::fontMetrics().width(m_vtBody[j].strName) > len)
                len = QLabel::fontMetrics().width(m_vtBody[j].strName);
        }
        for(j =0; j<count;j++)
        {
            if(m_vtBody[j].strName == " ")
                continue;

            painterPic.drawLine(0,(5+i)*iColoum,iWidth,(5+i)*iColoum);
            painterPic.drawText(5,(5+i)*iColoum-5,m_vtBody[j].strName);
            //painterPic.drawText(2*iWidth/3+10,(5+i)*iColoum-10,m_vtBody[j].strValue);
            painterPic.drawText(len+15,(5+i)*iColoum-5,m_vtBody[j].strValue);
            i++;
        }
        //painterPic.drawLine(2*iWidth/3,4*iColoum,2*iWidth/3,(4+i)*iColoum);
        painterPic.drawLine(len+10,4*iColoum,len+10,(4+i)*iColoum);

    }
}

void StepExcuteLabel::mousePressEvent(QMouseEvent *ev)
{
    QLabel::mousePressEvent(ev);
}
void StepExcuteLabel::mouseMoveEvent(QMouseEvent *ev)
{
    QLabel::mouseMoveEvent(ev);
}
void StepExcuteLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    QLabel::mouseReleaseEvent(ev);
}
void StepExcuteLabel::ClearOSD()
{
    m_vtHead.clear();
    m_vtBody.clear();
    repaint();
}
void StepExcuteLabel::SetSingleData(QVector<STRU_KEY_VALUE>vtHead,QVector<STRU_KEY_VALUE>vtBody)
{
    this->m_vtHead = vtHead;
    this->m_vtBody = vtBody;
    repaint();
}
void StepExcuteLabel::SetCurrentIndex(int index)
{
    this->m_index = index;
}
