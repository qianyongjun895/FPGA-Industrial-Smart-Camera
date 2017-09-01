#include "FWAreaSelect.h"
#include <stdio.h>
//#include <UIBasicDefine.h>
#include "BasicDefine.h"
FWAreaSelect::FWAreaSelect(QWidget *parent) : QLabel(parent)
{
    //QRect rect;
    //rect.setTopLeft(QPoint(100,100));
    //rect.setBottomRight(QPoint(400,400));
    this->m_end_x = 640;
    this->m_start_x = 0;
    this->m_start_y = 0;
    this->m_end_y = 480;
    m_pen = NULL;
}
void FWAreaSelect::SetPen(void *pen)
{
   this->m_pen = pen;
   update();
}
void FWAreaSelect::paintEvent(QPaintEvent *e)
{
    QLabel::paintEvent(e);
    QPainter painter(this);
    QPen pen;
    pen.setColor(Qt::red);
    pen.setWidth(2);
    painter.setPen(pen);

    int i;
    for(i = 0; i< m_vt_RingTool.count();i++)
    {
        m_vt_RingTool[i].paint_Event(&painter);
    }
    for(i = 0; i< m_vt_PolygonTool.count();i++)
    {
        m_vt_PolygonTool[i].paint_Event(&painter);
    }
    for(i = 0; i< m_vt_rectTool.count();i++)
    {
        m_vt_rectTool[i].paint_Event(&painter);
    }
    PEN_COLOR *pencolor = (PEN_COLOR*)m_pen;

    if(pencolor != NULL)
    {
        pen.setColor(pencolor->m_vt_color[pencolor->task_osd.task_osd_ImageBorder_color]);
        pen.setWidth(pencolor->task_osd.task_osd_ImageBorder_width);

    }else
    {
        pen.setColor(Qt::red);
        pen.setWidth(1);
    }

    pen.setStyle(Qt::DashDotLine);
    painter.setPen(pen);
    painter.drawLine(0,m_start_y,640,m_start_y);
    painter.drawLine(0,m_end_y,640,m_end_y);
    painter.drawLine(m_start_x,0,m_start_x,480);
    painter.drawLine(m_end_x,0,m_end_x,480);

}
void FWAreaSelect::mousePressEvent(QMouseEvent *ev)
{
    if(this->m_toolKind == RINGTOOL)
    {
        if(this->m_index < this->m_vt_RingTool.count() && this->m_index>=0)
        {
            m_vt_RingTool[m_index].mouse_PressEvent(ev);
        }

    }else if(this->m_toolKind == POLYGONTOOL)
    {
        if(this->m_index < this->m_vt_PolygonTool.count() && this->m_index>=0)
        {

            m_vt_PolygonTool[m_index].mouse_PressEvent(ev);
        }
    }else if(this->m_toolKind == RECTTOOL)
    {
        if(this->m_index < this->m_vt_rectTool.count() && this->m_index>=0)
        {

            m_vt_rectTool[m_index].mouse_PressEvent(ev);
        }
    }
}
void FWAreaSelect::mouseMoveEvent(QMouseEvent *ev)
{
    if(this->m_toolKind == RINGTOOL)
    {
        if(this->m_index < this->m_vt_RingTool.count() && this->m_index>=0)
        {
            m_vt_RingTool[m_index].mouse_MoveEvent(ev);
            signalsValueChange(RINGTOOL);
        }

    }else if(this->m_toolKind == POLYGONTOOL)
    {
        if(this->m_index < this->m_vt_PolygonTool.count() && this->m_index>=0)
        {
            m_vt_PolygonTool[m_index].mouse_MoveEvent(ev);
            signalsValueChange(POLYGONTOOL);
        }
    }
    else if(this->m_toolKind == RECTTOOL)
    {
        if(this->m_index < this->m_vt_rectTool.count() && this->m_index>=0)
        {

            m_vt_rectTool[m_index].mouse_MoveEvent(ev);
            signalsValueChange(RECTTOOL);
        }
    }

    update();
}
void FWAreaSelect::mouseReleaseEvent(QMouseEvent *ev)
{
    if(this->m_toolKind == RINGTOOL)
    {
        if(this->m_index < this->m_vt_RingTool.count() && this->m_index>=0)
        {
            m_vt_RingTool[m_index].mouse_ReleaseEvent(ev);
        }

    }else if(this->m_toolKind == POLYGONTOOL)
    {
        if(this->m_index < this->m_vt_PolygonTool.count() && this->m_index>=0)
        {
            m_vt_PolygonTool[m_index].mouse_ReleaseEvent(ev);
        }
    }else if(this->m_toolKind == RECTTOOL)
    {
        if(this->m_index < this->m_vt_rectTool.count() && this->m_index>=0)
        {

            m_vt_rectTool[m_index].mouse_ReleaseEvent(ev);
        }
    }
}
void FWAreaSelect::AddTool(TOOL_KIND toolKind)
{
    m_toolKind = toolKind;
    switch (toolKind) {
    case RINGTOOL:
        AddRingTool();
        break;
    case POLYGONTOOL:
        AddPolygonTool();
        break;
    case RECTTOOL:
        AddRectTool();
        break;
    case CIRCLETOOL:
        break;
    default:
        break;
    }
    update();
}
void FWAreaSelect::IniPolygonPoint(int index,int ipointNum,int x, int y,int flag)
{

    int count =m_vt_PolygonTool.count();
    m_vt_PolygonTool[count-1].m_current_point_num = ipointNum;
    m_vt_PolygonTool[count-1].IniPoint(index,x,y);
    m_vt_PolygonTool[count-1].flagOrNot = flag;
    update();
}
void FWAreaSelect::IniRectPoint(int x1,int y1,int x2 ,int y2,int flag)
{
    int count = m_vt_rectTool.count();
    QRectF rect;
    rect.setTopLeft(QPointF(x1,y1));
    rect.setBottomRight(QPointF(x2,y2));
    m_vt_rectTool[count-1].SetRect(rect);
    m_vt_rectTool[count-1].flagOrNot = flag;
    update();
}
void FWAreaSelect::DeleteTool(TOOL_KIND toolKind,int index)
{
    switch (toolKind) {
    case RINGTOOL:
        this->m_vt_RingTool.removeAt(index);
        break;
    case POLYGONTOOL:
        this->m_vt_PolygonTool.removeAt(index);
        break;
    case RECTTOOL:
        this->m_vt_rectTool.removeAt(index);
        break;
    default:
        break;
    }
}
void FWAreaSelect::AddPolygonTool()
{
    PolygonTool polygonTool;
    polygonTool.m_start_x = m_start_x;
    polygonTool.m_end_x =m_end_x;
    polygonTool.m_start_y = m_start_y;
    polygonTool.m_end_y = m_end_y;
    polygonTool.m_pen = m_pen;
    m_vt_PolygonTool.append(polygonTool);
    this->m_index = m_vt_PolygonTool.count()-1;
}
void FWAreaSelect::AddRingTool()
{
    RingTool ringTool;
    ringTool.m_start_x = m_start_x;
    ringTool.m_end_x =m_end_x;
    ringTool.m_start_y = m_start_y;
    ringTool.m_end_y = m_end_y;
    ringTool.m_pen = m_pen;
    m_vt_RingTool.append(ringTool);
    this->m_index = m_vt_RingTool.count() - 1;
}
void FWAreaSelect::AddRectTool()
{
    RectTool rectTool;
    QRectF rectf;
    rectTool.m_start_x = m_start_x;
    rectTool.m_end_x =m_end_x;
    rectTool.m_start_y = m_start_y;
    rectTool.m_end_y = m_end_y;
    rectTool.m_pen = m_pen;
    rectf.setTopLeft(QPointF(100,100));
    rectf.setBottomRight(QPointF(200,200));
    rectTool.SetRect(rectf);
    m_vt_rectTool.append(rectTool);
    this->m_index = m_vt_rectTool.count() -1;

}
void FWAreaSelect::SelectTool(TOOL_KIND toolKind,int index)
{
    this->m_toolKind = toolKind;
    this->m_index = index;
    SetSelectFlag();
    update();

}
void FWAreaSelect::SetSelectFlag()
{
    int count = 0;
    int i;
    count = m_vt_PolygonTool.count();
    for(i =0; i<count;i++)
    {
        m_vt_PolygonTool[i].bSelect = false;
    }
    count = m_vt_RingTool.count();

    for(i = 0; i<count;i++)
    {
        m_vt_RingTool[i].bSelect = false;
    }

    count = m_vt_rectTool.count();

    for(i = 0; i<count;i++)
    {
        m_vt_rectTool[i].bSelect = false;
    }

    if(m_toolKind == RINGTOOL)
    {
        m_vt_RingTool[m_index].bSelect = true;
    }
    else if(m_toolKind == POLYGONTOOL)
    {
        m_vt_PolygonTool[m_index].bSelect = true;

    }else if(m_toolKind == RECTTOOL)
    {
        m_vt_rectTool[m_index].bSelect = true;
    }
}

void FWAreaSelect::AddPolygonPoint()
{
    if(this->m_index < this->m_vt_PolygonTool.count() && this->m_index>=0)
    {
        m_vt_PolygonTool[m_index].AddPoint();
        update();
    }
}
void FWAreaSelect::SubPolygonPoint()
{
    if(this->m_index < this->m_vt_PolygonTool.count() && this->m_index>=0)
    {
        m_vt_PolygonTool[m_index].Subpoint();
        update();
    }
}

int FWAreaSelect::GetPolygonPointNum()
{
    int ret =0;
    if(this->m_index < this->m_vt_PolygonTool.count() && this->m_index>=0)
    {
        ret =m_vt_PolygonTool[m_index].m_current_point_num;
    }
    return ret;
}
QPoint FWAreaSelect::GetPolyGonPoint(int i)
{
    QPoint point;
    if(this->m_index < this->m_vt_PolygonTool.count() && this->m_index>=0)
    {
        point =m_vt_PolygonTool[m_index].m_point[i];
    }
    return point;
}
void FWAreaSelect::UpPolygonAdjust(int index)
{
    if(this->m_index < this->m_vt_PolygonTool.count() && this->m_index>=0)
    {
        m_vt_PolygonTool[m_index].UpAdjust(index);
        update();
        signalsValueChange(POLYGONTOOL);
    }
}
void FWAreaSelect::DownPolygonAdjust(int index)
{
    if(this->m_index < this->m_vt_PolygonTool.count() && this->m_index>=0)
    {
        m_vt_PolygonTool[m_index].DownAdjust(index);
        update();
        signalsValueChange(POLYGONTOOL);
    }
}
void FWAreaSelect::LeftPolygonAdjust(int index)
{
    if(this->m_index < this->m_vt_PolygonTool.count() && this->m_index>=0)
    {
        m_vt_PolygonTool[m_index].LeftAdjust(index);
        update();
        signalsValueChange(POLYGONTOOL);
    }
}
void FWAreaSelect::RightPolygonAdjust(int index)
{
    if(this->m_index < this->m_vt_PolygonTool.count() && this->m_index>=0)
    {
        m_vt_PolygonTool[m_index].RightAdjust(index);
        update();
        signalsValueChange(POLYGONTOOL);
    }
}
//设置圆环外半径
void FWAreaSelect::SetRingROut(int r)
{

    if(this->m_index < this->m_vt_RingTool.count() && this->m_index>=0)
    {
        m_vt_RingTool[m_index].SetROut(r);
        update();
    }

}
//设置圆环内半径
void FWAreaSelect::SetRingRIn(int r)
{
    if(this->m_index < this->m_vt_RingTool.count() && this->m_index>=0)
    {
        m_vt_RingTool[m_index].SetRIn(r);
        update();
    }
}
//设置圆环中心点
void FWAreaSelect::SetRingCenter(int x,int y)
{
    if(this->m_index < this->m_vt_RingTool.count() && this->m_index>=0)
    {
        m_vt_RingTool[m_index].SetCenter(x,y);
        update();
    }
}
int FWAreaSelect::GetRingROut()
{
    int r = 0;
    if(this->m_index < this->m_vt_RingTool.count() && this->m_index>=0)
    {
        r = m_vt_RingTool[m_index].GetROut();

    }
    return r;
}
int FWAreaSelect::GetRingRIn()
{
    int r = 0;
    if(this->m_index < this->m_vt_RingTool.count() && this->m_index>=0)
    {
        r = m_vt_RingTool[m_index].GetRIn();

    }
    return r;
}
QPoint FWAreaSelect::GetRingCenter()
{
    QPoint point = QPoint(0,0);

    if(this->m_index < this->m_vt_RingTool.count() && this->m_index>=0)
    {
        point = m_vt_RingTool[m_index].GetCenter();

    }
    return point;
}
bool FWAreaSelect::GetRingOrNot()
{
    bool bflag = false;
    if(this->m_index < this->m_vt_RingTool.count() && this->m_index>=0)
    {
        bflag = m_vt_RingTool[m_index].flagOrNot;
    }
    return bflag;
}
bool FWAreaSelect::GetPolygonOrNot()
{
    bool bflag = false;
    if(this->m_index < this->m_vt_PolygonTool.count() && this->m_index>=0)
    {
        bflag = m_vt_PolygonTool[m_index].flagOrNot;
    }
    return bflag;
}
void FWAreaSelect::SetRingOrNot(bool flag)
{
    if(this->m_index < this->m_vt_RingTool.count() && this->m_index>=0)
    {
        m_vt_RingTool[m_index].flagOrNot = flag;
        update();
    }
}
void FWAreaSelect::SetPolygonOrNot(bool flag)
{
    if(this->m_index < this->m_vt_PolygonTool.count() && this->m_index>=0)
    {
        m_vt_PolygonTool[m_index].flagOrNot = flag;
        update();
    }
}
bool FWAreaSelect::GetRectOrNot()
{
    bool bflag = false;
    if(this->m_index < this->m_vt_rectTool.count() && this->m_index>=0)
    {
        bflag = m_vt_rectTool[m_index].flagOrNot;
    }
    return bflag;
}
void FWAreaSelect::SetRectOrNot(bool flag)
{
    if(this->m_index < this->m_vt_rectTool.count() && this->m_index>=0)
    {
        m_vt_rectTool[m_index].flagOrNot = flag;
        update();
    }
}
QPoint FWAreaSelect::GetRectPoint(int i)
{
    QPoint RetPoint = QPoint(0,0);
    QPointF pointf = QPointF(0.0,0.0);

    if(i ==0)
    {
        if(this->m_index < this->m_vt_rectTool.count() && this->m_index>=0)
        {
            pointf = m_vt_rectTool[m_index].GetRect().topLeft();
        }
    }else if(i ==1)
    {
        if(this->m_index < this->m_vt_rectTool.count() && this->m_index>=0)
        {
            pointf = m_vt_rectTool[m_index].GetRect().topRight();
        }
    }else if(i ==2)
    {
        if(this->m_index < this->m_vt_rectTool.count() && this->m_index>=0)
        {
            pointf = m_vt_rectTool[m_index].GetRect().bottomRight();
        }
    }else if(i ==3)
    {
        if(this->m_index < this->m_vt_rectTool.count() && this->m_index>=0)
        {
            pointf = m_vt_rectTool[m_index].GetRect().bottomLeft();
        }
    }
    RetPoint.setX(pointf.x());
    RetPoint.setY(pointf.y());
    return RetPoint;
}
void FWAreaSelect::UpRectAdjust(int kind,int value)
{
    if(this->m_index < this->m_vt_rectTool.count() && this->m_index>=0)
    {
        m_vt_rectTool[m_index].UpAdjust(kind,value);
        update();
        signalsValueChange(RECTTOOL);
    }
}
void FWAreaSelect::DownRectAdjust(int kind,int value)
{
    if(this->m_index < this->m_vt_rectTool.count() && this->m_index>=0)
    {
        m_vt_rectTool[m_index].DownAdjust(kind,value);
        update();
        signalsValueChange(RECTTOOL);
    }
}
void FWAreaSelect::LeftRectAdjust(int kind,int value)
{
    if(this->m_index < this->m_vt_rectTool.count() && this->m_index>=0)
    {
        m_vt_rectTool[m_index].LeftAdjust(kind,value);
        update();
        signalsValueChange(RECTTOOL);
    }
}
void FWAreaSelect::RightRectAdjust(int kind,int value)
{
    if(this->m_index < this->m_vt_rectTool.count() && this->m_index>=0)
    {
        m_vt_rectTool[m_index].RightAdjust(kind,value);
        update();
        signalsValueChange(RECTTOOL);
    }
}
void FWAreaSelect::SetLimit(int startx,int endx,int starty,int endy)
{
    m_start_x = startx;
    m_end_x = endx;
    m_start_y = starty;
    m_end_y = endy;
}
