#include "PolygonTool.h"
#include <QDebug>
//#include "UIBasicDefine.h"
#include "BasicDefine.h"
#define ADJUSTRECTVALUE 8
PolygonTool::PolygonTool()
{
    m_pen = NULL;
    m_start_x = 0;
    m_end_x = 640;
    m_start_y = 0;
    m_end_y = 480;

    m_point[0].setX(300);
    m_point[0].setY(200);

    m_point[1].setX(300);
    m_point[1].setY(300);

    m_point[2].setX(400);
    m_point[2].setY(300);

    int xLeft = m_point[0].x()-ADJUSTRECTVALUE;
    int yLeft= m_point[0].y()-ADJUSTRECTVALUE;

    int xRight = m_point[0].x()+ADJUSTRECTVALUE;
    int yRight = m_point[0].y()+ADJUSTRECTVALUE;

    m_rect_point[0] = QRect(QPoint(xLeft,yLeft),QPoint(xRight,yRight));


    xLeft = m_point[1].x()-ADJUSTRECTVALUE;
    yLeft= m_point[1].y()-ADJUSTRECTVALUE;

    xRight = m_point[1].x()+ADJUSTRECTVALUE;
    yRight = m_point[1].y()+ADJUSTRECTVALUE;

    m_rect_point[1] = QRect(QPoint(xLeft,yLeft),QPoint(xRight,yRight));


    xLeft = m_point[2].x()-ADJUSTRECTVALUE;
    yLeft= m_point[2].y()-ADJUSTRECTVALUE;

    xRight = m_point[2].x()+ADJUSTRECTVALUE;
    yRight = m_point[2].y()+ADJUSTRECTVALUE;

    m_rect_point[2] = QRect(QPoint(xLeft,yLeft),QPoint(xRight,yRight));


    m_current_point_num = 3;
    m_selectType = -1;
    flagOrNot = false;
    bSelect = false;

}
void PolygonTool::mouse_PressEvent(QMouseEvent *e)
{

    int x = e->pos().x();
    int y = e->pos().y();
    startPoint = e->pos();
    m_selectType = -1;

    for(int i = 0; i< this->m_current_point_num;i++)
    {
        /*if(this->m_rect_point[i].contains(x,y))
        {
            m_selectType = i;
            break;
        }*/

        int xLeft = m_point[i].x()-20;
        int yLeft= m_point[i].y()-20;

        int xRight = m_point[i].x()+20;
        int yRight = m_point[i].y()+20;

        QRect m_rect_point_Temp = QRect(QPoint(xLeft,yLeft),QPoint(xRight,yRight));
        if(m_rect_point_Temp.contains(x,y))
        {
            m_selectType = i;
            break;
        }

    }
    /*if(m_selectType == -1)
    {
        FindMoveRect();

        if(m_move_rect.contains(x,y))
            m_selectType = 8;
    }*/



}
void PolygonTool::mouse_MoveEvent(QMouseEvent *e)
{
    int x = e->pos().x();
    int y = e->pos().y();

    if(m_selectType>=0 && m_selectType <=7)
    {
        if(x>m_end_x || x<m_start_x || y<m_start_y || y>m_end_y )
            return;

        m_point[m_selectType].setX(x);
        m_point[m_selectType].setY(y);
        int xLeft = m_point[m_selectType].x()-ADJUSTRECTVALUE;
        int yLeft= m_point[m_selectType].y()-ADJUSTRECTVALUE;

        int xRight = m_point[m_selectType].x()+ADJUSTRECTVALUE;
        int yRight = m_point[m_selectType].y()+ADJUSTRECTVALUE;

        m_rect_point[m_selectType] = QRect(QPoint(xLeft,yLeft),QPoint(xRight,yRight));

    }else if(m_selectType == 8) //移动
    {
        int dx = e->pos().x()-startPoint.x();
        int dy = e->pos().y()-startPoint.y();
        startPoint = e->pos();
        int currentX;
        int currentY;

        for(int i = 0; i< this->m_current_point_num;i++)
        {
            currentX = this->m_point[i].x()+dx;
            currentY = this->m_point[i].y()+dy;
            this->m_point[i].setX(currentX);
            this->m_point[i].setY(currentY);


            int xLeft = m_point[i].x()-ADJUSTRECTVALUE;
            int yLeft= m_point[i].y()-ADJUSTRECTVALUE;

            int xRight = m_point[i].x()+ADJUSTRECTVALUE;
            int yRight = m_point[i].y()+ADJUSTRECTVALUE;
            m_rect_point[i] = QRect(QPoint(xLeft,yLeft),QPoint(xRight,yRight));
        }
    }

}
void PolygonTool::mouse_ReleaseEvent(QMouseEvent *e)
{
    m_selectType = -1;
}
void PolygonTool::SetPen(QPen *pen,void *pdata)
{
    PEN_COLOR *pen_color = (PEN_COLOR *)m_pen;
    if(flagOrNot)
    {

         pen->setColor(Qt::red);
         pen->setWidth(1);

    }
    else
    {
        if(pen_color != NULL)
        {
            pen->setColor(pen_color->m_vt_color[pen_color->task_osd.task_osd_AreaSelect_color]);
            pen->setWidth(pen_color->task_osd.task_osd_AreaSelect_width);
        }else
        {
            pen->setColor(Qt::green);
            pen->setWidth(1);
        }
    }
}
void PolygonTool::paint_Event(QPainter *e)
{
    PEN_COLOR *pen_color = (PEN_COLOR *)m_pen;
    if(pen_color == NULL)
        return;
    QPen pen;
    SetPen(&pen,m_pen);
    e->setPen(pen);

    for(int i = 0; i< m_current_point_num-1;i++)
    {
        SetPen(&pen,m_pen);
        e->setPen(pen);
        e->drawLine(m_point[i],m_point[i+1]);

        if(bSelect)
        {
            pen.setColor(pen_color->m_vt_color[pen_color->task_osd.task_osd_select_color]);
            pen.setWidth(pen_color->task_osd.task_osd_select_width);
            e->setPen(pen);
            e->drawRect(this->m_rect_point[i]);
            e->drawText(m_rect_point[i],QString::number(i+1));
        }
    }

    SetPen(&pen,m_pen);
    e->setPen(pen);
    e->drawLine(m_point[m_current_point_num-1],m_point[0]);

    if(bSelect)
    {
        pen.setColor(pen_color->m_vt_color[pen_color->task_osd.task_osd_select_color]);
        pen.setWidth(pen_color->task_osd.task_osd_select_width);
        e->setPen(pen);
        e->drawRect(this->m_rect_point[m_current_point_num-1]);
        e->drawText(m_rect_point[m_current_point_num-1],QString::number(m_current_point_num));
    }

}
void PolygonTool::AddPoint()
{
    if(this->m_current_point_num < 8)
    {
        this->m_current_point_num++;
        this->m_point[m_current_point_num-1].setX((this->m_start_x+this->m_end_y)/2);
        this->m_point[m_current_point_num-1].setY((this->m_start_y+this->m_end_y)/2);

        int xLeft = m_point[m_current_point_num-1].x()-ADJUSTRECTVALUE;
        int yLeft= m_point[m_current_point_num-1].y()-ADJUSTRECTVALUE;

        int xRight = m_point[m_current_point_num-1].x()+ADJUSTRECTVALUE;
        int yRight = m_point[m_current_point_num-1].y()+ADJUSTRECTVALUE;

        m_rect_point[m_current_point_num-1] = QRect(QPoint(xLeft,yLeft),QPoint(xRight,yRight));

    }
}
void PolygonTool::Subpoint()
{
    if(this->m_current_point_num > 3)
    {
        this->m_current_point_num--;

    }

}
void PolygonTool::FindMoveRect()
{
    int xMin = this->m_end_x ;
    int yMin  = this->m_end_y;
    int xMax = this->m_start_x;
    int yMax = this->m_start_y;
    int xcurrent;
    int ycurrent;

    for(int i = 0; i< this->m_current_point_num;i++)
    {
        xcurrent = this->m_point[i].x();
        ycurrent = this->m_point[i].y();

        if(xMin >= xcurrent)
            xMin = xcurrent;
        if(yMin >= ycurrent)
            yMin = ycurrent;
        if(xMax <= xcurrent)
            xMax = xcurrent;

        if(yMax <= ycurrent)
            yMax = ycurrent;
    }

    m_move_rect.setTopLeft(QPoint(xMin,yMin));
    m_move_rect.setBottomRight(QPoint(xMax,yMax));

}
void PolygonTool::UpAdjust(int index)
{
    int y =  m_point[index].y()-1;

     if(y >= this->m_start_y)
    {
        m_point[index].setY(y);
        int xLeft = m_point[index].x()-ADJUSTRECTVALUE;
        int yLeft= m_point[index].y()-ADJUSTRECTVALUE;

        int xRight = m_point[index].x()+ADJUSTRECTVALUE;
        int yRight = m_point[index].y()+ADJUSTRECTVALUE;

        m_rect_point[index] = QRect(QPoint(xLeft,yLeft),QPoint(xRight,yRight));
    }
}
void PolygonTool::DownAdjust(int index)
{
    int y =  m_point[index].y() + 1;

    if(y <= this->m_end_y)
    {
        m_point[index].setY(y);
        int xLeft = m_point[index].x()-ADJUSTRECTVALUE;
        int yLeft= m_point[index].y()-ADJUSTRECTVALUE;

        int xRight = m_point[index].x()+ADJUSTRECTVALUE;
        int yRight = m_point[index].y()+ADJUSTRECTVALUE;

        m_rect_point[index] = QRect(QPoint(xLeft,yLeft),QPoint(xRight,yRight));
    }
}
void PolygonTool::LeftAdjust(int index)
{
    int x =  m_point[index].x()-1;
    if(x >= m_start_x)
    {
        m_point[index].setX(x);
        //m_point[index].setY(y);
        int xLeft = m_point[index].x()-ADJUSTRECTVALUE;
        int yLeft= m_point[index].y()-ADJUSTRECTVALUE;

        int xRight = m_point[index].x()+ADJUSTRECTVALUE;
        int yRight = m_point[index].y()+ADJUSTRECTVALUE;

        m_rect_point[index] = QRect(QPoint(xLeft,yLeft),QPoint(xRight,yRight));
    }
}
void PolygonTool::RightAdjust(int index)
{
    int x =  m_point[index].x()+1;

    if(x<=m_end_x)
    {
        m_point[index].setX(x);
        //m_point[index].setY(y);
        int xLeft = m_point[index].x()-ADJUSTRECTVALUE;
        int yLeft= m_point[index].y()-ADJUSTRECTVALUE;

        int xRight = m_point[index].x()+ADJUSTRECTVALUE;
        int yRight = m_point[index].y()+ADJUSTRECTVALUE;

        m_rect_point[index] = QRect(QPoint(xLeft,yLeft),QPoint(xRight,yRight));
    }
}
void PolygonTool::IniPoint(int index,int x, int y)
{
    int dixX = (m_end_x-m_start_x)/6;
     if(x>m_end_x || x<m_start_x || y<m_start_y || y>m_end_y )
     {
         if(index == 0)
         {
             this->m_point[index].setX(m_start_x);
             this->m_point[index].setY(m_start_y);
         }else if(index == 1)
         {
             this->m_point[index].setX(m_start_x);
             this->m_point[index].setY(m_end_y);

         }else if(index == 2)
         {
             this->m_point[index].setX(m_start_x+dixX);
             this->m_point[index].setY(m_end_y);
         }else if(index == 3)
         {
             this->m_point[index].setX(m_start_x+2*dixX);
             this->m_point[index].setY(m_end_y);
         }else if(index == 4)
         {
             this->m_point[index].setX(m_start_x+dixX*3);
             this->m_point[index].setY(m_end_y);
         }else if(index == 5)
         {
             this->m_point[index].setX(m_start_x+dixX*4);
             this->m_point[index].setY(m_end_y);
         }else if(index == 6)
         {
             this->m_point[index].setX(m_start_x+dixX*5);
             this->m_point[index].setY(m_end_y);
         }else if(index == 7)
         {
             this->m_point[index].setX(m_start_x+dixX*6);
             this->m_point[index].setY(m_end_y);
         }



     }else
     {
         this->m_point[index].setX(x);
         this->m_point[index].setY(y);
     }


   int xLeft = m_point[index].x()-ADJUSTRECTVALUE;
   int yLeft= m_point[index].y()-ADJUSTRECTVALUE;

   int xRight = m_point[index].x()+ADJUSTRECTVALUE;
   int yRight = m_point[index].y()+ADJUSTRECTVALUE;

   m_rect_point[index] = QRect(QPoint(xLeft,yLeft),QPoint(xRight,yRight));
}
