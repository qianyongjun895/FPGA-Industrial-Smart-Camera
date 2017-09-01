#include "FWMatchLineLabel.h"
#include <math.h>
#include <stdio.h>
#include <QDebug>
#include "BasicDefine.h"

FWMatchLineLabel::FWMatchLineLabel(QWidget *parent) : QLabel(parent)
{
    m_point1.setX(320);
    m_point1.setY(100);
    m_point2.setX(320);
    m_point2.setY(300);
    m_select = 0;
    m_line_num =1;
    m_sample_line_num = 0;
    m_current_index = 0;
    for(int i = 0;i<20;i++)
    {
        m_x1[i] = -10;
        m_y1[i] = -10;
        m_x2[i] = -10;
        m_y2[i] = -10;
        m_points1[i].setX(320);
        m_points1[i].setY(100);
        m_points2[i].setX(320);
        m_points2[i].setY(300);
        m_dx[i] = 39;
    }
    m_pen_color = NULL;
}
void FWMatchLineLabel::SetPenColor(void *pen_color)
{
    this->m_pen_color = pen_color;
}
void FWMatchLineLabel::SetLineNum(int num, int add)
{
    this->m_line_num = num;
    this->m_current_index = num-1;
    if(add == 1)
    {
        m_point1.setX(320);
        m_point1.setY(100);
        m_point2.setX(320);
        m_point2.setY(300);

        m_points1[m_current_index].setX(320);
        m_points1[m_current_index].setY(100);
        m_points2[m_current_index].setX(320);
        m_points2[m_current_index].setY(300);
        m_dx[m_current_index] = 39;

    }
    emit Point1ChangeSignal(m_points1[m_current_index],1);
    emit Point2ChangeSignal(m_points2[m_current_index],1);
    update();

}
void FWMatchLineLabel::SetPoint1(QPoint point1)
{
    //m_point1 = point1;
    m_points1[m_current_index] = point1;
    update();
    emit Point1ChangeSignal(m_points1[m_current_index],0);
}
void FWMatchLineLabel::SetPoint2(QPoint point2)
{
    //m_point2 = point2;
    m_points2[m_current_index] = point2;
    update();
    emit Point2ChangeSignal(m_points2[m_current_index],0);

}
void FWMatchLineLabel::SetCurrentDir(int dir,int index)
{
    this->m_dx[index] = dir;
    update();
}
void FWMatchLineLabel::paintEvent(QPaintEvent *e)
{
    QLabel::paintEvent(e);
    QPainter painter(this);
    QPen pen;
    PEN_COLOR * pencolor = (PEN_COLOR*)m_pen_color;
    if(pencolor !=NULL)
    {
        pen.setColor(pencolor->m_vt_color[pencolor->task_osd.task_osd_edit_color]);
        pen.setWidth(pencolor->task_osd.task_osd_edit_width);
        painter.setPen(pen);
    }

    int i =0;

    for(i = 0;i<m_line_num;i++)
    {
        painter.drawEllipse(m_points1[i],10,10);
        painter.drawEllipse(m_points2[i],10,10);
        painter.drawText(QPoint(m_points1[i].x(),m_points1[i].y()-20),"a");
        painter.drawText(QPoint(m_points2[i].x(),m_points2[i].y()-20),"b");

        painter.drawText(QPoint((m_points1[i].x()+m_points2[i].x())/2,(m_points1[i].y()+m_points2[i].y())/2),QString::number(i+1));

        painter.drawLine(m_points1[i].x()-10,m_points1[i].y(),m_points1[i].x()+10,m_points1[i].y());
        painter.drawLine(m_points1[i].x(),m_points1[i].y()-10,m_points1[i].x(),m_points1[i].y()+10);
        painter.drawLine(m_points2[i].x()-10,m_points2[i].y(),m_points2[i].x()+10,m_points2[i].y());
        painter.drawLine(m_points2[i].x(),m_points2[i].y()-10,m_points2[i].x(),m_points2[i].y()+10);
        painter.drawLine(m_points1[i].x(),m_points1[i].y(),m_points2[i].x(),m_points2[i].y());
    }
    if(pencolor !=NULL)
    {
        pen.setColor(pencolor->m_vt_color[pencolor->task_osd.task_osd_select_color]);
        pen.setWidth(pencolor->task_osd.task_osd_select_width);
        painter.setPen(pen);
    }
    painter.drawEllipse(m_points1[m_current_index],10,10);
    painter.drawEllipse(m_points2[m_current_index],10,10);
    painter.drawText(QPoint(m_points1[m_current_index].x(),m_points1[m_current_index].y()-20),"a");
    painter.drawText(QPoint(m_points2[m_current_index].x(),m_points2[m_current_index].y()-20),"b");
    painter.drawLine(m_points1[m_current_index].x()-10,m_points1[m_current_index].y(),m_points1[m_current_index].x()+10,m_points1[m_current_index].y());
    painter.drawLine(m_points1[m_current_index].x(),m_points1[m_current_index].y()-10,m_points1[m_current_index].x(),m_points1[m_current_index].y()+10);
    painter.drawLine(m_points2[m_current_index].x()-10,m_points2[m_current_index].y(),m_points2[m_current_index].x()+10,m_points2[m_current_index].y());
    painter.drawLine(m_points2[m_current_index].x(),m_points2[m_current_index].y()-10,m_points2[m_current_index].x(),m_points2[m_current_index].y()+10);
    painter.drawLine(m_points1[m_current_index].x(),m_points1[m_current_index].y(),m_points2[m_current_index].x(),m_points2[m_current_index].y());
    painter.drawText(QPoint((m_points1[m_current_index].x()+m_points2[m_current_index].x())/2,(m_points1[m_current_index].y()+m_points2[m_current_index].y())/2),QString::number(m_current_index+1));

    if(pencolor !=NULL)
    {
        pen.setColor(pencolor->m_vt_color[pencolor->task_osd.task_osd_Calc_color]);
        pen.setWidth(pencolor->task_osd.task_osd_Calc__width);
        painter.setPen(pen);
    }

    for(i =0; i<m_sample_line_num;i++)
    {
        painter.drawLine(m_x1[i],m_y1[i],m_x2[i],m_y2[i]);
    }
    CalcRangePoints(&painter);

}
void FWMatchLineLabel::mousePressEvent(QMouseEvent *ev)
{
    m_select = 0;
    int x =ev->pos().x();
    int y = ev->pos().y();
    int i =0;
    for (i = 0; i< m_line_num; i++)
    {
        if(((x-m_points1[i].x())*(x-m_points1[i].x())+(y-m_points1[i].y())*(y-m_points1[i].y())) <= 20*20)
        {
            m_select = 1;
            m_current_index = i;
            emit Point1ChangeSignal(m_points1[i],1);
            break;
        }
    }

    if(m_select == 0)
    {
        for (i = 0;i<m_line_num;i++)
        {
            if(((x-m_points2[i].x())*(x-m_points2[i].x())+(y-m_points2[i].y())*(y-m_points2[i].y())) <= 20*20)
            {
                m_current_index = i;
                m_select = 2;
                emit Point2ChangeSignal(m_points2[i],1);
                break;
            }
        }
    }
    m_press_point = ev->pos();
}
void FWMatchLineLabel::mouseMoveEvent(QMouseEvent *ev)
{
    QPoint pos = ev->pos();

    int disX = pos.x() - m_press_point.x();
    int disY = pos.y() - m_press_point.y();
    int ix,iy;

    if(m_select ==1)
    {
        ix = m_points1[m_current_index].x() + disX;
        iy = m_points1[m_current_index].y() + disY;
        if(ix >= 0 && ix <= 640 && iy>=0 && iy<=480)
        {
            m_points1[m_current_index].setX(m_points1[m_current_index].x() + disX);
            m_points1[m_current_index].setY(m_points1[m_current_index].y() + disY);
            emit Point1ChangeSignal(m_points1[m_current_index],0);
        }
    }else if(m_select ==2)
    {
        ix = m_points2[m_current_index].x() + disX;
        iy = m_points2[m_current_index].y() + disY;

        if(ix >= 0 && ix <= 640 && iy>=0 && iy<=480)
        {
            m_points2[m_current_index].setX(m_points2[m_current_index].x() + disX);
            m_points2[m_current_index].setY(m_points2[m_current_index].y() + disY);
            emit Point2ChangeSignal(m_points2[m_current_index],0);
        }
    }
    m_press_point = ev->pos();
    update();
}
void FWMatchLineLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    if(m_select != 0)
    {
        emit Point1ChangeSignal(m_points1[m_current_index],2);
        emit Point2ChangeSignal(m_points2[m_current_index],2);
        m_select = 0;
    }
}
double FWMatchLineLabel::GetAngel(int x1, int y1, int x2, int y2 )
{
    double xDis;
    double yDis;

    if ((pow(x1, 2) + pow(y1, 2)) \
            > (pow(x2, 2) + pow(y2, 2)))
    {
        xDis = x2-x1;
        yDis = y2-y1;

    }else
    {
        xDis = x1-x2;
        yDis = y1-y2;
    }

    double ret = atan2(yDis,xDis);
    return ret;
}
double FWMatchLineLabel::GetCurrentAngel()
{
    double xDis ;
    double yDis;

    if ((pow(m_points1[m_current_index].x(), 2) + pow(m_points1[m_current_index].y(), 2)) \
            > (pow(m_points2[m_current_index].x(), 2) + pow(m_points2[m_current_index].y(), 2)))
    {
        xDis = m_points2[m_current_index].x() - m_points1[m_current_index].x();
        yDis = m_points2[m_current_index].y() - m_points1[m_current_index].y();
    }else
    {
        xDis = m_points1[m_current_index].x() - m_points2[m_current_index].x();
        yDis = m_points1[m_current_index].y() - m_points2[m_current_index].y();
    }
    double ret = atan2(yDis,xDis);
    return ret;
}


void FWMatchLineLabel::SetSampleLine(int x1,int y1,int x2,int y2)
{

}
void FWMatchLineLabel::SetSampleLines(int *x1, int *y1, int *x2, int *y2, int inum)
{
    m_sample_line_num = inum;

    for (int i=0; i< inum;i++)
    {
        this->m_x1[i] = x1[i];
        this->m_x2[i] = x2[i];
        this->m_y1[i] = y1[i];
        this->m_y2[i] = y2[i];
    }
    update();
}
void FWMatchLineLabel::SetPoints(QPoint *point1,QPoint *point2,int num)
{
    this->m_line_num = num;

    for(int i= 0; i< num ;i++)
    {
        this->m_points1[i] = point1[i];
        this->m_points2[i] = point2[i];
    }
    update();
}

inline void FWMatchLineLabel::Coordinate_Rotate_Calc(POINT_FLOAT_UI *OutPoint, POINT_FLOAT_UI *ref_point, POINT_FLOAT_UI *ref_delt, float sin_a, float cos_a)
{
    OutPoint->x_f = (cos_a*ref_delt->x_f - sin_a*ref_delt->y_f + (ref_point->x_f));
    OutPoint->y_f = (sin_a*ref_delt->x_f + cos_a*ref_delt->y_f + (ref_point->y_f));
}

void FWMatchLineLabel::CalcRangePoints(QPainter *p)
{
    QPoint middlePoint;
    middlePoint.setX((m_points1[m_current_index].x()+m_points2[m_current_index].x())/2);
    middlePoint.setY((m_points1[m_current_index].y()+m_points2[m_current_index].y())/2);
    float dis = (m_points1[m_current_index].x()-m_points2[m_current_index].x())*(m_points1[m_current_index].x()-m_points2[m_current_index].x()) +
            (m_points1[m_current_index].y()-m_points2[m_current_index].y())*(m_points1[m_current_index].y()-m_points2[m_current_index].y());
    float dy = sqrt(dis);
    float dx = m_dx[m_current_index];
    float cos_x;
    float sin_x;
    sin_x = (m_points1[m_current_index].y()-m_points2[m_current_index].y())/dy;
    cos_x = (m_points1[m_current_index].x()-m_points2[m_current_index].x())/dy;



    POINT_FLOAT_UI point_center;
    point_center.x_f = (m_points1[m_current_index].x()+m_points2[m_current_index].x())/2;
    point_center.y_f = (m_points1[m_current_index].y()+m_points2[m_current_index].y())/2;
    POINT_FLOAT_UI point_dis;
    point_dis.y_f = -dx;
    point_dis.x_f = dy/2;
    Coordinate_Rotate_Calc(&point1[m_current_index],&point_center,&point_dis,sin_x,cos_x);
    point_dis.y_f = dx;
    point_dis.x_f = -dy/2;
    Coordinate_Rotate_Calc(&point2[m_current_index],&point_center,&point_dis,sin_x,cos_x);
    point_dis.y_f = dx;
    point_dis.x_f = dy/2;
    Coordinate_Rotate_Calc(&point3[m_current_index],&point_center,&point_dis,sin_x,cos_x);
    point_dis.y_f = -dx;
    point_dis.x_f = -dy/2;
    Coordinate_Rotate_Calc(&point4[m_current_index],&point_center,&point_dis,sin_x,cos_x);


    point_dis.y_f = -40;
    point_dis.x_f = -0;
    Coordinate_Rotate_Calc(&dir_point1,&point_center,&point_dis,sin_x,cos_x);
    point_dis.y_f = 40;
    point_dis.x_f = 0;
    Coordinate_Rotate_Calc(&dir_point2,&point_center,&point_dis,sin_x,cos_x);
    p->drawLine(QPointF(point_center.x_f,point_center.y_f)
                ,QPointF(dir_point2.x_f,dir_point2.y_f));
    DrawArrow(p,QPointF(point_center.x_f,point_center.y_f),QPointF(dir_point2.x_f,dir_point2.y_f),15);

    p->drawLine(QPointF(point1[m_current_index].x_f,point1[m_current_index].y_f),
                QPointF(point4[m_current_index].x_f,point4[m_current_index].y_f));
    p->drawLine(QPointF(point4[m_current_index].x_f,point4[m_current_index].y_f),
                QPointF(point2[m_current_index].x_f,point2[m_current_index].y_f));
    p->drawLine(QPointF(point2[m_current_index].x_f,point2[m_current_index].y_f),
                QPointF(point3[m_current_index].x_f,point3[m_current_index].y_f));
    p->drawLine(QPointF(point1[m_current_index].x_f,point1[m_current_index].y_f),
                QPointF(point3[m_current_index].x_f,point3[m_current_index].y_f));

}

void FWMatchLineLabel::DrawArrow(QPainter *painter,QPointF lastPoint,QPointF endPoint,float iArrowLen)
{
    float x1 = lastPoint.x();         //lastPoint 起点
    float y1 = lastPoint.y();
    float x2 = endPoint.x();           //endPoint 终点
    float y2 = endPoint.y();
    if(((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1))>640*480)
    {
        return;
    }
    //float iArrowLen = 10.0;                   //箭头的那长度
    float a = 0.5;                       //箭头与线段角度
    float x3 = x2 - iArrowLen * cos(atan2((y2 - y1) , (x2 - x1)) - a);
    float y3 = y2 - iArrowLen * sin(atan2((y2 - y1) , (x2 - x1)) - a);
    float x4 = x2 - iArrowLen * sin(atan2((x2 - x1) , (y2 - y1)) - a);
    float y4 = y2 - iArrowLen * cos(atan2((x2 - x1) , (y2 - y1)) - a);
    painter->drawLine(x2,y2,x3,y3);
    painter->drawLine(x2,y2,x4,y4);
    painter->drawLine(lastPoint,endPoint);
}
void FWMatchLineLabel::SetScanDirs(int *dirs,int num)
{
    for(int i=0; i<num;i++)
    {
        m_dx[i] = dirs[i];
    }

    update();
}
void FWMatchLineLabel::SetLineCurrence(int index)
{

    this->m_current_index = index;
    update();
    emit Point1ChangeSignal(m_points1[index],1);
    emit Point1ChangeSignal(m_points2[index],1);
}
