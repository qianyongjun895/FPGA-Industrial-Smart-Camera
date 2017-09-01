#include "ContrastStrengthenAdjustLabel.h"
#include <qdebug.h>

ContrastStrengthenAdjustLabel::ContrastStrengthenAdjustLabel(QWidget *parent) : QLabel(parent)
{
    m_y1 = 10;
    m_y2 = 160;
    m_point1.setX(114);
    m_point1.setY(290);
    m_point2.setX(224);
    m_point2.setY(240);
    m_img_smooth = 0;
    m_smooth_mode = 0;
    m_current_ad = 0;
    m_list_adjust_line =1;
}
void ContrastStrengthenAdjustLabel::UpAdjustLine(KEYKIND kind, int value)
{
    if(kind == UPLINE)
    {
        if(this->m_y1 > 0)
            this->m_y1 -= value;
        if(this->m_y1 < 0)
            this->m_y1 = 0;
        update();
        signaleValue(1);

    }else if(kind == DOWNLIN)
    {
        if(this->m_y2 > this->m_y1+DISTANCE)
            this->m_y2 -=value;
        update();
        signaleValue(1);
    }
}
void ContrastStrengthenAdjustLabel::DownAdjustmentLine(KEYKIND kind, int value)
{
    if(kind == UPLINE)
    {
        if(this->m_y2 > this->m_y1+DISTANCE)
            this->m_y1 +=value;
        update();
        signaleValue(1);

    }else if(kind == DOWNLIN)
    {
        if(this->m_y2 < 480)
            this->m_y2 +=value;

        if(this->m_y2 > 480)
            this->m_y2 = 480;

        update();
        signaleValue(1);
    }
}
void ContrastStrengthenAdjustLabel::paintEvent(QPaintEvent *e)
{

    QLabel::paintEvent(e);
    QPainter painter(this);
    QPen pen;
    pen.setColor(Qt::red);
    pen.setWidth(1);
    painter.setPen(pen);
    if(m_img_smooth == 0)
    {
        if(m_list_adjust_line ==1)
        {
        painter.drawLine(0,m_y1,640,m_y1);
        painter.drawLine(0,m_y2,640,m_y2);

        painter.drawLine(640,m_y1,630,m_y1-15);
        painter.drawLine(620,m_y1,630,m_y1-15);
        painter.drawLine(640,m_y1,630,m_y1+15);
        painter.drawLine(620,m_y1,630,m_y1+15);

        painter.drawLine(640,m_y2,630,m_y2-15);
        painter.drawLine(620,m_y2,630,m_y2-15);
        painter.drawLine(640,m_y2,630,m_y2+15);
        painter.drawLine(620,m_y2,630,m_y2+15);
        }
    }
    //绘图像均衡参数
    if(m_img_smooth == 1)
    {
        //坐标
        painter.drawLine(ORIGINX,ORIGINY,ORIGINX+512,ORIGINY);
        painter.drawLine(ORIGINX+507,ORIGINY-5,ORIGINX+512,ORIGINY);
        painter.drawLine(ORIGINX+507,ORIGINY+5,ORIGINX+512,ORIGINY);
        painter.drawLine(ORIGINX,ORIGINY,ORIGINX,ORIGINY-255);
        painter.drawLine(ORIGINX-5,ORIGINY-250,ORIGINX,ORIGINY-255);
        painter.drawLine(ORIGINX+5,ORIGINY-250,ORIGINX,ORIGINY-255);
        painter.drawText(ORIGINX+512,ORIGINY+20,"255");
        painter.drawText(ORIGINX-25,ORIGINY-255,"255");
        painter.drawText(ORIGINX-5,ORIGINY+15,"0");
        //刻度

        painter.drawLine(120,ORIGINY,120,ORIGINY-5);
        painter.drawLine(176,ORIGINY,176,ORIGINY-5);
        painter.drawLine(232,ORIGINY,232,ORIGINY-5);
        painter.drawLine(288,ORIGINY,288,ORIGINY-5);
        painter.drawLine(344,ORIGINY,344,ORIGINY-5);
        painter.drawLine(ORIGINY,ORIGINY,ORIGINY,ORIGINY-5);
        painter.drawLine(456,ORIGINY,456,ORIGINY-5);
        painter.drawLine(512,ORIGINY,512,ORIGINY-5);
        painter.drawText(110,ORIGINY+20,"28");
        painter.drawText(166,ORIGINY+20,"56");
        painter.drawText(222,ORIGINY+20,"84");
        painter.drawText(278,ORIGINY+20,"112");
        painter.drawText(334,ORIGINY+20,"140");
        painter.drawText(390,ORIGINY+20,"168");
        painter.drawText(446,ORIGINY+20,"196");
        painter.drawText(502,ORIGINY+20,"224");

        painter.drawLine(64,ORIGINY-51,69,ORIGINY-51);
        painter.drawLine(64,ORIGINY-102,69,ORIGINY-102);
        painter.drawLine(64,ORIGINY-153,69,ORIGINY-153);
        painter.drawLine(64,ORIGINY-204,69,ORIGINY-204);
        painter.drawText(35,ORIGINY+5-51,"51");
        painter.drawText(35,ORIGINY+5-102,"102");
        painter.drawText(35,ORIGINY+5-153,"153");
        painter.drawText(35,ORIGINY+5-204,"204");

        int i = 0;

        if(m_smooth_mode > 20)
        {
            for(i = 0; i < m_smooth_mode-1;i++)
            {
                painter.drawLine(m_Points[i].x(),m_Points[i].y(),m_Points[i+1].x(),m_Points[i+1].y());
            }

            painter.drawLine(m_Points[iSelectKind-3].x(),m_Points[iSelectKind-3].y()-10,m_Points[iSelectKind-3].x(),m_Points[iSelectKind-3].y()+10);
            painter.drawLine(m_Points[iSelectKind-3].x()-5,m_Points[iSelectKind-3].y()+6,m_Points[iSelectKind-3].x(),m_Points[iSelectKind-3].y()+10);
            painter.drawLine(m_Points[iSelectKind-3].x()+5,m_Points[iSelectKind-3].y()+6,m_Points[iSelectKind-3].x(),m_Points[iSelectKind-3].y()+10);
            painter.drawLine(m_Points[iSelectKind-3].x()-5,m_Points[iSelectKind-3].y()-6,m_Points[iSelectKind-3].x(),m_Points[iSelectKind-3].y()-10);
            painter.drawLine(m_Points[iSelectKind-3].x()+5,m_Points[iSelectKind-3].y()-6,m_Points[iSelectKind-3].x(),m_Points[iSelectKind-3].y()-10);

        }else
        {
            for(i = 0; i < m_smooth_mode;i++)
            {

                if(i > 0){
                    painter.drawLine(m_Points[i].x(),m_Points[i].y(),m_Points[i-1].x(),m_Points[i-1].y());
                }
                painter.drawLine(m_Points[i].x()-10,m_Points[i].y(),m_Points[i].x()+10,m_Points[i].y());
                painter.drawLine(m_Points[i].x(),m_Points[i].y()-10,m_Points[i].x(),m_Points[i].y()+10);
                painter.drawEllipse(m_Points[i],10,10);
                if(m_Points[i].y()-20 > 0)
                    painter.drawText(m_Points[i].x()-10,m_Points[i].y()-20,QString::number(i+1));
                else
                    painter.drawText(m_Points[i].x()-10,m_Points[i].y()+20,QString::number(i+1));
                // painter.drawText(m_Points[i].x()+10,m_Points[i].y()-20,QString::number(i+1));

                if(iSelectKind-3 == i)
                {
                    if(m_Points[i].y()-40 > 0)
                    {
                        painter.drawText(m_Points[i].x()-40,m_Points[i].y()-40,
                                         "("+QString::number((m_Points[i].x()-64)/2)+","+QString::number(ORIGINY-m_Points[i].y())+")");
                    }else
                    {
                        painter.drawText(m_Points[i].x()-40,m_Points[i].y()+40,
                                         "("+QString::number((m_Points[i].x()-64)/2)+","+QString::number(ORIGINY-m_Points[i].y())+")");
                    }

                }
            }
            painter.drawLine(64,ORIGINY,m_Points[0].x(),m_Points[0].y());
            painter.drawLine(64+512,ORIGINY-255,m_Points.last().x(),m_Points.last().y());
        }

        /*if(m_current_ad == -10)
        {
            QRect rect(m_point_start,m_point_end);
            painter.drawRect(rect);
        }*/
    }
}
void ContrastStrengthenAdjustLabel::mousePressEvent(QMouseEvent *ev)
{
    int x = ev->pos().x();
    int y = ev->pos().y();
    iSelectKind = 0;
    if(m_list_adjust_line ==1)
    {
    if(y > this->m_y1-20 && y < this->m_y1 + 20)
        iSelectKind = 1;
    else if(y > this->m_y2 - 20 && y<this->m_y2 + 20)
        iSelectKind = 2;
    }
    m_current_ad = 0;
    int count = 0;
    count = m_Points.count();
    for(int i = 0;i < count;i++)
    {
        if((x-m_Points[i].x())*(x-m_Points[i].x())+(y-m_Points[i].y())*(y-m_Points[i].y())< 20*20)
        {
            iSelectKind = 3+i;
            PointChangeSignal(i,m_Points[i]);
        }
    }

    /*if(m_img_smooth == 1)
    {
        if(iSelectKind <3)
        {
            m_current_ad = -10;
            m_point_start = ev->pos();
            m_point_end = ev->pos();
            update();
        }
    }*/

    if(iSelectKind !=0)
    {
        update();
        return;
    }

}
void ContrastStrengthenAdjustLabel::mouseMoveEvent(QMouseEvent *ev)
{
    int x = ev->pos().x();
    int y = ev->pos().y();

    if(iSelectKind == 1)
    {
        if(y < 0)
        {
            this->m_y1 = 0;

        }else if(y>= this->m_y2-DISTANCE)
        {
            this->m_y1 = m_y2-DISTANCE;
        }else
        {
            if(y %2 !=0)
                this->m_y1 = y-1;
            else
                this->m_y1 = y;
        }
        signaleValue(0);
        update();

    }else if(iSelectKind ==2)
    {
        if(y <= this->m_y1+DISTANCE)
            this->m_y2 = this->m_y1+DISTANCE;
        else if(y > 480)
            this->m_y2 = 480;
        else
        {
            if(y%2 !=0)
                this->m_y2 = y+1;
            else
                this->m_y2 = y;
        }
        signaleValue(0);
        update();
    }/*else if(iSelectKind ==3) //图像均衡点1
    {
        if(x>=64 && x<m_point2.x() && y>=145 && y<=400)
        {
            m_point1.setX(x);
            m_point1.setY(y);
            update();
        }
    }else if(iSelectKind ==4) //图像均衡点2
    {
        if(x>=64 && x<=576 && y>=145 && y<=400 && x > m_point1.x())
        {
            m_point2.setX(x);
            m_point2.setY(y);
            update();
        }
    }*/
    if(m_smooth_mode < 20)
    {
        if(iSelectKind >=3)
        {
            int count = 0;
            count = m_Points.count();
            for(int i = 0;i < count;i++)
            {
                if(iSelectKind -3 == i)
                {

                    if(i == 0)
                    {
                        if(x>=64 && x<m_Points[1].x() && y>=ORIGINY-255 && y<=ORIGINY)
                        {
                            m_Points[i].setX(x);
                            m_Points[i].setY(y);
                            update();
                        }
                    }else if( i == count-1)
                    {
                        if(x<=575 && y>=ORIGINY-255 && y<=ORIGINY && x > m_Points[i-1].x())
                        {
                            m_Points[i].setX(x);
                            m_Points[i].setY(y);
                            update();
                        }
                    }else
                    {
                        if(x>=m_Points[i-1].x() && x <= m_Points[i+1].x() && y>=ORIGINY-255 && y<=ORIGINY)
                        {
                            m_Points[i].setX(x);
                            m_Points[i].setY(y);
                            update();
                        }
                    }
                    PointChangeSignal(i,m_Points[i]);
                }
            }

        }
    }

    /*if(m_current_ad == -10)
    {
        m_point_end = ev->pos();
        update();
    }*/

}
void ContrastStrengthenAdjustLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    if(iSelectKind == 1 || iSelectKind == 2)
        signaleValue(1);
    if(iSelectKind >= 3)
    {
        sendDataSignal();
    }

    /*if(m_current_ad == -10)
    {
        PointChangeSignal(-10,m_point_start);
    }*/
    QLabel::mouseReleaseEvent(ev);
}
void ContrastStrengthenAdjustLabel::SetLine(int y1,int y2)
{
    m_y1 = y1;
    m_y2 = y2;
    update();
}
int ContrastStrengthenAdjustLabel::GetLineHeigth()
{
    return this->m_y2 - this->m_y1;
}
void ContrastStrengthenAdjustLabel::SetImagSmothEnable(int flag)
{
    this->m_img_smooth = flag;
}
QPoint ContrastStrengthenAdjustLabel::GetPoint1()
{
    int x = m_point1.x()- 64;
    int y = ORIGINY-m_point1.y();
    QPoint retPoint;
    retPoint.setX(x);
    retPoint.setY(y);
    return retPoint;
}
QPoint ContrastStrengthenAdjustLabel::GetPoint2()
{
    int x = m_point2.x()- 64;
    int y = ORIGINY-m_point2.y();
    QPoint retPoint;
    retPoint.setX(x);
    retPoint.setY(y);
    return retPoint;
}
void ContrastStrengthenAdjustLabel::SetPoint1(int x,int  y)
{
    int ix = 64 +x;
    int iy = ORIGINY-y;
    m_point1.setX(ix);
    m_point1.setY(iy);
    update();
}
void ContrastStrengthenAdjustLabel::SetPoint2(int x, int y)
{
    int ix = 64 +x;
    int iy = ORIGINY-y;
    m_point2.setX(ix);
    m_point2.setY(iy);
    update();
}


void ContrastStrengthenAdjustLabel::SetPoints(QVector<QPoint> Points,int num)
{
    m_smooth_mode = num;
    m_Points = Points;
    update();
}


void ContrastStrengthenAdjustLabel::SetPointsChange(QVector<QPoint> Points,int num)
{
    m_smooth_mode = num;
    int i = 0;
    m_Points.clear();
    for(i = 0; i < num; i++)
    {
        QPoint point;
        point.setX(ORIGINX+2*(Points[i].x()));
        point.setY(ORIGINY-(Points[i].y()));
        m_Points.append(point);
    }
    if(m_smooth_mode >16)
        iSelectKind = 3;
    update();
}

QVector<QPoint> ContrastStrengthenAdjustLabel::GetPoints()
{
    //return m_Points;
    QVector<QPoint> Points;
    for(int i = 0; i < m_smooth_mode; i++)
    {
        QPoint point;
        point.setX((m_Points[i].x()-64)/2);
        point.setY(ORIGINY-(m_Points[i].y()));
        Points.append(point);
    }
    return Points;
}


void ContrastStrengthenAdjustLabel::MoveUp()
{
    if(iSelectKind >= 3 && iSelectKind-3 < m_Points.count())
    {
        if(m_Points[iSelectKind-3].y() > ORIGINY-255 &&m_Points[iSelectKind-3].y() <= ORIGINY)
        {
            //        m_Points[iSelectKind-3].setX(m_Points[iSelectKind-3].x());
            m_Points[iSelectKind-3].setY(m_Points[iSelectKind-3].y()-1);
            update();
            sendDataSignal();
            PointChangeSignal(iSelectKind-3,m_Points[iSelectKind-3]);
        }
    }
}

void ContrastStrengthenAdjustLabel::MoveDown()
{

    if(iSelectKind >= 3 && iSelectKind-3 < m_Points.count())
    {
        if(m_Points[iSelectKind-3].y() >= ORIGINY-255 &&m_Points[iSelectKind-3].y() < ORIGINY)
        {
            //        m_Points[iSelectKind-3].setX(m_Points[iSelectKind-3].x());
            m_Points[iSelectKind-3].setY(m_Points[iSelectKind-3].y()+1);
            update();
            sendDataSignal();
            PointChangeSignal(iSelectKind-3,m_Points[iSelectKind-3]);
        }
    }
}

void ContrastStrengthenAdjustLabel::MoveLeft()
{
    int count = m_Points.count();
    int index = iSelectKind-3;
    if(index >= 0 && index < count)
    {
        if(index == 0)
        {
            if(m_Points[0].x() > 64)
            {
                m_Points[index].setX(m_Points[index].x()-1);
                update();
            }
        }else if( index == count-1)
        {
            if(m_Points[index].x() > m_Points[index-1].x())
            {
                m_Points[index].setX(m_Points[index].x()-1);
                update();
            }
        }else
        {
            if(m_Points[index].x() > m_Points[index-1].x())
            {
                m_Points[index].setX(m_Points[index].x()-1);
                update();
            }
        }
        sendDataSignal();
        PointChangeSignal(index,m_Points[index]);
    }
}

void ContrastStrengthenAdjustLabel::MoveRight()
{
    int count = m_Points.count();
    int index = iSelectKind-3;
    if(index >= 0 && index < count)
    {
        if(index == 0)
        {
            if(m_Points[0].x() < m_Points[1].x())
            {
                m_Points[index].setX(m_Points[index].x()+1);
                update();
            }
        }else if( index == count-1)
        {
            if(m_Points[index].x() < 575)
            {
                m_Points[index].setX(m_Points[index].x()+1);
                update();
            }
        }else
        {
            if(m_Points[index].x() < m_Points[index+1].x())
            {
                m_Points[index].setX(m_Points[index].x()+1);
                update();
            }
        }
        sendDataSignal();
        PointChangeSignal(index,m_Points[index]);
    }
}


void ContrastStrengthenAdjustLabel::SetPointFocus(int index)
{
    iSelectKind = index + 3;
    update();
}
QRect ContrastStrengthenAdjustLabel::GetRect()
{
    int x1 = m_point_start.x();
    int y1 = m_point_start.y();
    int x2 = m_point_end.x();
    int y2= m_point_end.y();

    int xTemp; int yTemp;
    xTemp = x1;
    yTemp = y1;

    if(x1> x2)
    {
        x1 = x2;
        x2= xTemp;
    }

    if(y1> y2)
    {
        y1 = y2;
        y2 = yTemp;
    }

    if(x1== x2)
    {
        x2= x1+2;
    }

    if(y1 == y2)
    {
        y2 = y1+2;
    }
    QRect rect(QPoint(x1,y1),QPoint(x2,y2));
    return rect;
}
int ContrastStrengthenAdjustLabel::GetCurrentIndexAd()
{
    return this->iSelectKind-2;
}
void ContrastStrengthenAdjustLabel::SetCurrentIndexAd(int value)
{
    this->iSelectKind = value+2;
    update();
}
QPoint ContrastStrengthenAdjustLabel::GetCurrentPoint()
{
    QPoint point;
    point.setX((m_Points[iSelectKind-3].x()-64)/2);
    point.setY(ORIGINY-(m_Points[iSelectKind-3].y()));
    return point;
}
void ContrastStrengthenAdjustLabel::SetCurrentPoint(int y)
{
    m_Points[iSelectKind-3].setY(ORIGINY-y);
    update();
}
void ContrastStrengthenAdjustLabel::SetListAdjustLine(int flag)
{
    m_list_adjust_line = flag;
    update();
}
