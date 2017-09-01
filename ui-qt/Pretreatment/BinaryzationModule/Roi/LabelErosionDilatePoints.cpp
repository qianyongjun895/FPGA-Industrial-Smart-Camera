#include "LabelErosionDilatePoints.h"
#include <math.h>
#include <QDebug>

QRect m_rect[13*13];
unsigned char m_buf[13*13];
QRect m_rect_col[13];
QRect m_rect_row[13];
unsigned char m_buf_row[13];
unsigned char m_buf_col[13];

LabelErosionDilatePoints::LabelErosionDilatePoints(QWidget *parent) : QLabel(parent)
{
    this->m_num = 3*3;
    IniRectPoints(m_num);
    m_type = 0;
}
void LabelErosionDilatePoints::GetbufFlag(char *buf)
{
    memcpy(buf,m_buf,m_num);
}
void LabelErosionDilatePoints::IniRectPoints(int inum)
{
    this->m_num = inum;
    int max = sqrt(inum);
    int i,j;
    int k = 0;
    for(i=0; i<max;i++)
    {
        for(j=0;j<max;j++)
        {
            QRect rect(STARTX+j*RECTWIDTH,STARTY +i*RECTHEIGHT,RECTWIDTH,RECTHEIGHT);
            m_rect[k]= rect;
            m_buf[k]=1;
            k++;
        }
    }

    for(i=0;i<max;i++)
    {
        QRect rectRow(STARTX+max*RECTWIDTH+5,STARTY +i*RECTHEIGHT,RECTWIDTH,RECTHEIGHT);
        m_rect_row[i]= rectRow;

        QRect rectcol(STARTX+i*RECTWIDTH,STARTY +max*RECTHEIGHT+5,RECTWIDTH,RECTHEIGHT);
        m_rect_col[i]= rectcol;

        m_buf_row[i] = 1;
        m_buf_col[i] = 1;
    }
    update();
}

void LabelErosionDilatePoints::iniRect(unsigned short *buf)
{
    int max = sqrt(m_num);
    int i,j;
    int num;

    for(i=0;i<max;i++)
    {
        for(j=0;j<max;j++)
        {
            num = (buf[i]>>j)&1;
            m_buf[i*max+j]=num;
        }
    }
    SelectRowColIsAll();
    update();
}
void LabelErosionDilatePoints::ClearDefaultPara()
{
    m_type = 0;
    update();
}
void LabelErosionDilatePoints::DefaultDiamondPara()
{
    IniRectPoints(m_num);
    m_type = 2;
    int max = sqrt(m_num);

    if(max == 3)
    {
        m_buf[0]=0;
        m_buf[2]=0;
        m_buf[2*max]=0;
        m_buf[2*max+2]=0;
    }
    else if(max == 5)
    {
        m_buf[0]=0;
        m_buf[1]=0;
        m_buf[3]=0;
        m_buf[4]=0;
        m_buf[1*max]=0;
        m_buf[1*max+4]=0;
        m_buf[3*max]=0;
        m_buf[3*max+4]=0;
        m_buf[4*max]=0;
        m_buf[4*max+1]=0;
        m_buf[4*max+3]=0;
        m_buf[4*max+4]=0;

    }else if(max == 7)
    {
        m_buf[0]=0;
        m_buf[1]=0;
        m_buf[2]=0;
        m_buf[4]=0;
        m_buf[5]=0;
        m_buf[6]=0;
        m_buf[1*max]=0;
        m_buf[1*max + 1]=0;
        m_buf[1*max+5]=0;
        m_buf[1*max + 6]=0;
        m_buf[2*max]=0;
        m_buf[2*max + 6]=0;
        m_buf[4*max]=0;
        m_buf[4*max + 6]=0;
        m_buf[5*max]=0;
        m_buf[5*max + 1]=0;
        m_buf[5*max+5]=0;
        m_buf[5*max + 6]=0;
        m_buf[6*max]=0;
        m_buf[6*max + 1]=0;
        m_buf[6*max + 2]=0;
        m_buf[6*max + 4]=0;
        m_buf[6*max+5]=0;
        m_buf[6*max + 6]=0;

    }else if(max == 9)
    {
        m_buf[0]=0;
        m_buf[1]=0;
        m_buf[2]=0;
        m_buf[3]=0;
        m_buf[5]=0;
        m_buf[6]=0;
        m_buf[7]=0;
        m_buf[8]=0;
        m_buf[1*max]=0;
        m_buf[1*max+1]=0;
        m_buf[1*max+2]=0;
        m_buf[1*max+6]=0;
        m_buf[1*max+7]=0;
        m_buf[1*max+8]=0;
        m_buf[2*max]=0;
        m_buf[2*max+1]=0;
        m_buf[2*max+7]=0;
        m_buf[2*max+8]=0;
        m_buf[3*max]=0;
        m_buf[3*max+8]=0;
        m_buf[5*max]=0;
        m_buf[5*max+8]=0;
        m_buf[6*max]=0;
        m_buf[6*max+1]=0;
        m_buf[6*max+7]=0;
        m_buf[6*max+8]=0;
        m_buf[7*max]=0;
        m_buf[7*max+1]=0;
        m_buf[7*max+2]=0;
        m_buf[7*max+6]=0;
        m_buf[7*max+7]=0;
        m_buf[7*max+8]=0;
        m_buf[8*max]=0;
        m_buf[8*max+1]=0;
        m_buf[8*max+2]=0;
        m_buf[8*max+3]=0;
        m_buf[8*max+5]=0;
        m_buf[8*max+6]=0;
        m_buf[8*max+7]=0;
        m_buf[8*max+8]=0;

    }else if(max == 11)
    {
        m_buf[0]=0;
        m_buf[1]=0;
        m_buf[2]=0;
        m_buf[3]=0;
        m_buf[4]=0;
        m_buf[6]=0;
        m_buf[7]=0;
        m_buf[8]=0;
        m_buf[9]=0;
        m_buf[10]=0;
        m_buf[1*max]=0;
        m_buf[1*max+1]=0;
        m_buf[1*max+2]=0;
        m_buf[1*max+3]=0;
        m_buf[1*max+7]=0;
        m_buf[1*max+8]=0;
        m_buf[1*max+9]=0;
        m_buf[1*max+10]=0;
        m_buf[2*max]=0;
        m_buf[2*max+1]=0;
        m_buf[2*max+2]=0;
        m_buf[2*max+8]=0;
        m_buf[2*max+9]=0;
        m_buf[2*max+10]=0;
        m_buf[3*max]=0;
        m_buf[3*max+1]=0;
        m_buf[3*max+9]=0;
        m_buf[3*max+10]=0;
        m_buf[4*max]=0;
        m_buf[4*max+10]=0;
        m_buf[6*max]=0;
        m_buf[6*max+10]=0;
        m_buf[7*max]=0;
        m_buf[7*max+1]=0;
        m_buf[7*max+9]=0;
        m_buf[7*max+10]=0;
        m_buf[8*max]=0;
        m_buf[8*max+1]=0;
        m_buf[8*max+2]=0;
        m_buf[8*max+8]=0;
        m_buf[8*max+9]=0;
        m_buf[8*max+10]=0;
        m_buf[9*max]=0;
        m_buf[9*max+1]=0;
        m_buf[9*max+2]=0;
        m_buf[9*max+3]=0;
        m_buf[9*max+7]=0;
        m_buf[9*max+8]=0;
        m_buf[9*max+9]=0;
        m_buf[9*max+10]=0;
        m_buf[10*max+0]=0;
        m_buf[10*max+1]=0;
        m_buf[10*max+2]=0;
        m_buf[10*max+3]=0;
        m_buf[10*max+4]=0;
        m_buf[10*max+6]=0;
        m_buf[10*max+7]=0;
        m_buf[10*max+8]=0;
        m_buf[10*max+9]=0;
        m_buf[10*max+10]=0;

    }else if(max == 13)
    {
        m_buf[0]=0;
        m_buf[1]=0;
        m_buf[2]=0;
        m_buf[3]=0;
        m_buf[4]=0;
        m_buf[5]=0;
        m_buf[7]=0;
        m_buf[8]=0;
        m_buf[9]=0;
        m_buf[10]=0;
        m_buf[11]=0;
        m_buf[12]=0;
        m_buf[1*max]=0;
        m_buf[1*max+1]=0;
        m_buf[1*max+2]=0;
        m_buf[1*max+3]=0;
        m_buf[1*max+4]=0;
        m_buf[1*max+8]=0;
        m_buf[1*max+9]=0;
        m_buf[1*max+10]=0;
        m_buf[1*max+11]=0;
        m_buf[1*max+12]=0;

        m_buf[2*max]=0;
        m_buf[2*max+1]=0;
        m_buf[2*max+2]=0;
        m_buf[2*max+3]=0;
        m_buf[2*max+9]=0;
        m_buf[2*max+10]=0;
        m_buf[2*max+11]=0;
        m_buf[2*max+12]=0;

        m_buf[3*max]=0;
        m_buf[3*max+1]=0;
        m_buf[3*max+2]=0;
        m_buf[3*max+10]=0;
        m_buf[3*max+11]=0;
        m_buf[3*max+12]=0;

        m_buf[4*max]=0;
        m_buf[4*max+1]=0;
        m_buf[4*max+11]=0;
        m_buf[4*max+12]=0;

        m_buf[5*max]=0;
        m_buf[5*max+12]=0;

        m_buf[7*max]=0;
        m_buf[7*max+12]=0;

        m_buf[8*max]=0;
        m_buf[8*max+1]=0;
        m_buf[8*max+11]=0;
        m_buf[8*max+12]=0;

        m_buf[9*max]=0;
        m_buf[9*max+1]=0;
        m_buf[9*max+2]=0;
        m_buf[9*max+10]=0;
        m_buf[9*max+11]=0;
        m_buf[9*max+12]=0;

        m_buf[10*max]=0;
        m_buf[10*max+1]=0;
        m_buf[10*max+2]=0;
        m_buf[10*max+3]=0;
        m_buf[10*max+9]=0;
        m_buf[10*max+10]=0;
        m_buf[10*max+11]=0;
        m_buf[10*max+12]=0;

        m_buf[11*max]=0;
        m_buf[11*max+1]=0;
        m_buf[11*max+2]=0;
        m_buf[11*max+3]=0;
        m_buf[11*max+4]=0;
        m_buf[11*max+8]=0;
        m_buf[11*max+9]=0;
        m_buf[11*max+10]=0;
        m_buf[11*max+11]=0;
        m_buf[11*max+12]=0;

        m_buf[12*max+0]=0;
        m_buf[12*max+1]=0;
        m_buf[12*max+2]=0;
        m_buf[12*max+3]=0;
        m_buf[12*max+4]=0;
        m_buf[12*max+5]=0;
        m_buf[12*max+7]=0;
        m_buf[12*max+8]=0;
        m_buf[12*max+9]=0;
        m_buf[12*max+10]=0;
        m_buf[12*max+11]=0;
        m_buf[12*max+12]=0;

    }
    SelectRowColIsAll();
    update();
}
void LabelErosionDilatePoints::DefaultCirclePara()
{
    IniRectPoints(m_num);
    m_type = 1;
    int max = sqrt(m_num);

    if(max == 5)
    {
        m_buf[0]=0;
        m_buf[4]=0;
        m_buf[4*max]=0;
        m_buf[4*max+4]=0;

    }else if(max == 7)
    {
        m_buf[0]=0;
        m_buf[6]=0;
        m_buf[6*max]=0;
        m_buf[6*max+6]=0;

    }else if(max == 9)
    {
        m_buf[0]=0;
        m_buf[1]=0;
        m_buf[max-1]=0;
        m_buf[max-2]=0;
        m_buf[1*max]=0;
        m_buf[1*max+8]=0;
        m_buf[7*max]=0;
        m_buf[7*max+8]=0;
        m_buf[8*max]=0;
        m_buf[8*max+1]=0;
        m_buf[8*max+7]=0;
        m_buf[8*max+8]=0;

    }else if(max == 11)
    {
        m_buf[0]=0;
        m_buf[1]=0;
        m_buf[2]=0;
        m_buf[max-1]=0;
        m_buf[max-2]=0;
        m_buf[max-3]=0;

        m_buf[1*max]=0;
        m_buf[1*max+10]=0;
        m_buf[2*max]=0;
        m_buf[2*max+10]=0;

        m_buf[8*max]=0;
        m_buf[8*max+10]=0;
        m_buf[9*max]=0;
        m_buf[9*max+10]=0;
        m_buf[10*max]=0;
        m_buf[10*max+1]=0;
        m_buf[10*max+2]=0;

        m_buf[10*max+10]=0;
        m_buf[10*max+9]=0;
        m_buf[10*max+8]=0;

    }else if(max == 13)
    {
        m_buf[0]=0;
        m_buf[1]=0;
        m_buf[2]=0;
        m_buf[3]=0;
        m_buf[max-1]=0;
        m_buf[max-2]=0;
        m_buf[max-3]=0;
        m_buf[max-4]=0;
        m_buf[1*max]=0;
        m_buf[1*max+1]=0;
        m_buf[1*max+12]=0;
        m_buf[1*max+11]=0;
        m_buf[2*max]=0;
        m_buf[2*max+12]=0;
        m_buf[3*max]=0;
        m_buf[3*max+12]=0;
        m_buf[9*max]=0;
        m_buf[9*max+12]=0;
        m_buf[10*max]=0;
        m_buf[10*max+12]=0;
        m_buf[11*max]=0;
        m_buf[11*max+1]=0;
        m_buf[11*max+12]=0;
        m_buf[11*max+11]=0;

        m_buf[12*max+0]=0;
        m_buf[12*max+1]=0;
        m_buf[12*max+2]=0;
        m_buf[12*max+3]=0;

        m_buf[12*max+12]=0;
        m_buf[12*max+11]=0;
        m_buf[12*max+10]=0;
        m_buf[12*max+9]=0;

    }
    SelectRowColIsAll();
    update();
}
void LabelErosionDilatePoints::SelectRowColIsAll()
{
    int max = sqrt(m_num);
    int i,j;
    bool bflag = false;

    //判断行全选
    for(i=0;i<max;i++)
    {
        bflag = false;
        m_buf_row[i] = 1;

        for(j=0;j<max;j++)
        {
            if((int)m_buf[i*max+j]==0)
            {
                bflag = true;
                break;
            }
        }

        if(bflag)
        {
            m_buf_row[i] = 0;
        }
    }
    //判断全列是否选上
    for(i=0;i<max;i++)
    {
        bflag = false;
        m_buf_col[i] = 1;

        for(j=0;j<max;j++)
        {
            if((int)m_buf[j*max+i]==0)
            {
                bflag = true;
                break;
            }
        }

        if(bflag)
        {
            m_buf_col[i] = 0;
        }
    }
}
void LabelErosionDilatePoints::SelectAll()
{
    int max = sqrt(m_num);
    int i;
    for(i=0;i<m_num;i++)
    {
        m_buf[i] = 1;
    }
    for(i=0;i<max;i++)
    {
        m_buf_col[i] = 1;
        m_buf_row[i] = 1;
    }
    update();
}

void LabelErosionDilatePoints::SelectNoAll()
{
    int max = sqrt(m_num);
    int i;
    for(i=0;i<m_num;i++)
    {
        m_buf[i] = 0;
    }
    for(i=0;i<max;i++)
    {
        m_buf_col[i] = 0;
        m_buf_row[i] = 0;
    }
    update();
}
void LabelErosionDilatePoints::paintEvent(QPaintEvent *e)
{
    QLabel::paintEvent(e);
    QPainter painter(this);

    QPen pen;
    pen.setColor(Qt::green);
    pen.setWidth(1);
    //pen.setStyle(Qt::DashDotLine);
    painter.setPen(pen);

    int i;
    for(i=0; i< this->m_num;i++)
    {
        painter.drawRect(m_rect[i]);
        if(m_buf[i] == 1)
        {
            painter.drawText(m_rect[i].topLeft().x()+20,m_rect[i].topLeft().y()+30,"1");
        }else
        {
            painter.drawText(m_rect[i].topLeft().x()+20,m_rect[i].topLeft().y()+30,"0");
        }

    }

    int max = sqrt(m_num);
    for(i =0;i<max;i++)
    {
        painter.drawRect(m_rect_row[i]);
        painter.drawRect(m_rect_col[i]);

        if((int)m_buf_col[i]==1)
        {
            painter.drawLine(m_rect_col[i].topLeft(),m_rect_col[i].bottomRight());
            painter.drawLine(m_rect_col[i].topRight(),m_rect_col[i].bottomLeft());
        }

        if((int)m_buf_row[i] == 1)
        {
            painter.drawLine(m_rect_row[i].topLeft(),m_rect_row[i].bottomRight());
            painter.drawLine(m_rect_row[i].topRight(),m_rect_row[i].bottomLeft());
        }
    }

    for(i = 0;i<max;i++)
    {
        painter.drawText(m_rect[i].topLeft().x()+20,m_rect[i].topLeft().y()-5,QString::number(i));
        painter.drawText(m_rect[i*max].topLeft().x()-20,m_rect[i*max].topLeft().y()+30,QString::number(i));
    }
    pen.setColor(Qt::red);
    pen.setWidth(1);
    painter.setPen(pen);

    if(m_buf[m_num/2] == 1)
    {
        painter.drawText(m_rect[m_num/2].topLeft().x()+20,m_rect[m_num/2].topLeft().y()+30,"1");
    }else
    {
        painter.drawText(m_rect[m_num/2].topLeft().x()+20,m_rect[m_num/2].topLeft().y()+30,"0");
    }
    painter.drawText(m_rect[max/2].topLeft().x()+20,m_rect[max/2].topLeft().y()-5,QString::number(max/2));
    painter.drawText(m_rect[max/2*max].topLeft().x()-20,m_rect[max/2*max].topLeft().y()+30,QString::number(max/2));

    if(m_type == 1)
    {
        pen.setStyle(Qt::DashDotLine);
        painter.setPen(pen);
        painter.drawEllipse(STARTX,STARTY,max*RECTHEIGHT,max*RECTHEIGHT);//画圆

    }else if(m_type ==2)
    {
        //凌形
        pen.setStyle(Qt::DashDotLine);
        painter.setPen(pen);
        painter.drawLine(STARTX+max*RECTHEIGHT/2,STARTY,STARTX,STARTY+max*RECTHEIGHT/2);
        painter.drawLine(STARTX,STARTY+max*RECTHEIGHT/2,STARTX+max*RECTHEIGHT/2,STARTY+max*RECTHEIGHT);
        painter.drawLine(STARTX+max*RECTHEIGHT/2,STARTY+max*RECTHEIGHT,STARTX+max*RECTHEIGHT,STARTY+max*RECTHEIGHT/2);
        painter.drawLine(STARTX+max*RECTHEIGHT,STARTY+max*RECTHEIGHT/2,STARTX+max*RECTHEIGHT/2,STARTY);
    }
}
void LabelErosionDilatePoints::mousePressEvent(QMouseEvent *ev)
{
    int x = ev->pos().x();
    int y = ev->pos().y();
    int i = 0;

    for(i = 0; i<m_num;i++)
    {
        if(m_rect[i].contains(x,y))
        {
            if((int)m_buf[i]==1)
            {
                m_buf[i] =0;
            }else
            {
                m_buf[i] =1;
            }
        }
    }

    int max = sqrt(m_num);
    int j;
    for(i = 0; i<max;i++)
    {
        if(m_rect_col[i].contains(x,y))
        {
            if((int)m_buf_col[i]==1)
            {
                m_buf_col[i] =0;

                for(j=0;j<max;j++)
                {
                    m_buf[i+j*max] = 0;
                }

            }else
            {
                m_buf_col[i] =1;

                for(j=0;j<max;j++)
                {
                    m_buf[i+j*max] = 1;
                }
            }
        }
        if(m_rect_row[i].contains(x,y))
        {
            if((int)m_buf_row[i]==1)
            {
                m_buf_row[i] =0;
                for(j=0;j<max;j++)
                {
                    m_buf[j+i*max] = 0;
                }
            }else
            {
                m_buf_row[i] =1;

                for(j=0;j<max;j++)
                {
                    m_buf[j+i*max] = 1;
                }
            }
        }
    }
    /*bool bflag = false;
    for(i = 0;i<m_num;i++)
    {
        if((int)m_buf[i]==1)
        {
            bflag = true;
            break;
        }
    }
    if(!bflag)
    {
        for(i=0;i<max;i++)
        {
             m_buf_col[i] =0;
             m_buf_row[i] = 0;
        }
    }*/
    SelectRowColIsAll();
    update();
    QLabel::mousePressEvent(ev);
}
void LabelErosionDilatePoints::mouseMoveEvent(QMouseEvent *ev)
{
    QLabel::mouseMoveEvent(ev);
}
void LabelErosionDilatePoints::mouseReleaseEvent(QMouseEvent *ev)
{
    QLabel::mouseReleaseEvent(ev);
}
