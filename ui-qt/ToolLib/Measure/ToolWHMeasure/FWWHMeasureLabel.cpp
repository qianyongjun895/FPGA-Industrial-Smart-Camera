#include "QDebug"
#include "FWWHMeasureLabel.h"
#include "BasicDefine.h"

FWWHMeasureLabel::FWWHMeasureLabel(QWidget *parent) : QLabel(parent)
{
    m_x_line = QLine(50,0,50,480);
    m_y_line = QLine(0,50,640,50);
    m_rect = QRect(QPoint(200,200),QPoint(400,300));
    m_pen_color = NULL;
}

FWWHMeasureLabel::~FWWHMeasureLabel()
{

}

void FWWHMeasureLabel::SetOSDData(QLine ref_line)
{
    m_ref_line = ref_line;
    update();
}

void FWWHMeasureLabel::paintEvent(QPaintEvent *e)
{
    QLabel::paintEvent(e);
    QPainter painter(this);
    PEN_COLOR * pencolor = (PEN_COLOR*)m_pen_color;
    QPen pen;
    if(pencolor !=NULL)
    {
        pen.setColor(pencolor->m_vt_color[pencolor->task_osd.task_osd_select_color]);
        pen.setWidth(pencolor->task_osd.task_osd_select_width);
        painter.setPen(pen);
    }
    painter.drawLine(m_ref_line);

    if(pencolor !=NULL)
    {
        pen.setColor(pencolor->m_vt_color[pencolor->task_osd.task_osd_edit_color]);
        pen.setWidth(pencolor->task_osd.task_osd_edit_width);
        pen.setStyle(Qt::DashLine);
        painter.setPen(pen);
    }

    painter.drawLine(m_x_line);
    painter.drawLine(m_y_line);
    if(pencolor !=NULL)
    {
        pen.setColor(pencolor->m_vt_color[pencolor->task_osd.task_osd_select_color]);
        pen.setWidth(pencolor->task_osd.task_osd_select_width);
        pen.setStyle(Qt::SolidLine);
        painter.setPen(pen);
    }

    painter.setPen(pen);
    for(int i = 0 ; i < m_Xpoints.count()-2;i++)
    {
        painter.drawLine(m_Xpoints[i],m_Xpoints[i+1]);
    }
    for(int i = 0 ; i < m_Ypoints.count()-2;i++)
    {
        painter.drawLine(m_Ypoints[i],m_Ypoints[i+1]);
    }
//    painter.drawRect(m_rect);
//    painter.drawRect(m_rect.topLeft().x()-5,m_rect.topLeft().y()-5,10,10);
//    painter.drawRect(m_rect.bottomRight().x()-5,m_rect.bottomRight().y()-5,10,10);

}


void FWWHMeasureLabel::mousePressEvent(QMouseEvent *ev)
{
    m_select = 0;
    int x =ev->pos().x();
    int y = ev->pos().y();
    if(x > m_x_line.x1()-20 && x < m_x_line.x1()+20)
    {
        m_select = 1;
    }

    if(m_select == 0)
    {
        if(y > m_y_line.y1()-20 && y < m_y_line.y1()+20)
        {
            m_select = 2;
        }
    }

//    if(m_select == 0)
//    {
//        if(IsInEditRect(x,y,&m_rect)== 1)
//        {

//            m_select =3;
//        }else if(IsInEditRect(x,y,&m_rect)== 2)
//        {
//            m_select =4;
//        }
//    }
    m_press_point = ev->pos();
    LinePosChangeSignal(m_x_line.x1(),m_y_line.y1());
    update();
}

/**
 * @brief FWWHMeasureLabel::IsInEditRect
 * @param x 点击位置的X坐标
 * @param y 点击位置的Y坐标
 * @param rect 点中的搜索框
 * @return 选中的点
 * @author dgq
 * @note 判断鼠标按下位置的位置是搜索框的左上顶点还是右下顶点
 */
int FWWHMeasureLabel::IsInEditRect(int x,int y,QRect *rect)
{
    int  ret = 0;

    if(x > rect->topLeft().x()-20 && x < rect->topLeft().x()+20 &&
            y > rect->topLeft().y()-20 && y < rect->topLeft().y()+20)
    {
        ret =1;

    }else if(x > rect->bottomRight().x()-20 && x < rect->bottomRight().x()+20 &&
             y >  rect->bottomRight().y()-20 && y < rect->bottomRight().y()+20)
    {
        ret =2;

    }else
    {
        ret = 0;
    }
    return ret;
}

void FWWHMeasureLabel::mouseMoveEvent(QMouseEvent *ev)
{
    QPoint pos = ev->pos();

    int disX = pos.x() - m_press_point.x();
    int disY = pos.y() - m_press_point.y();
    int ix,iy;

    if(m_select ==1)
    {
        ix = m_x_line.x1() + disX;
        if(ix >= 0 && ix <= 640)
        {
            m_x_line.setLine(ix,0,ix,480);
        }
    }else if(m_select ==2)
    {
        iy = m_y_line.y1() + disY;
        if(iy >= 0 && iy <= 480)
        {
            m_y_line.setLine(0,iy,640,iy);
        }
    }
//    else if(m_select == 3)
//    {
////        if(x <= 0 || y > m_rect.topLeft().y()-20)
////            return;
//        m_rect.setTopLeft(ev->pos());
//    }else if(m_select == 4)
//    {
////        if(x < m_rect.bottomRight().x() + 20  || y < m_rect.bottomRight().y() + 20)
////            return;
//        m_rect.setBottomRight(ev->pos());
//    }
    m_press_point = ev->pos();
    LinePosChangeSignal(m_x_line.x1(),m_y_line.y1());
    update();
}

void FWWHMeasureLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    if(m_select != 0)
    {
        LinePosChangeSignal(m_x_line.x1(),m_y_line.y1());
        m_select = 0;
    }
}
/**
 * @brief FWWHMeasureLabel::MoveUp
 * @author dgq
 * @note 向上移动一个像素
 */
void FWWHMeasureLabel::MoveUp(int value)
{
    if(m_y_line.y1() > value)
        m_y_line.setLine(0,m_y_line.y1()-value,640,m_y_line.y2()-value);
    LinePosChangeSignal(m_x_line.x1(),m_y_line.y1());
    update();
}


/**
 * @brief FWWHMeasureLabel::MoveDown
 * @author dgq
 * @note 向下移动一个像素
 */
void FWWHMeasureLabel::MoveDown(int value)
{

    if(m_y_line.y1() < 480-value)
        m_y_line.setLine(0,m_y_line.y1()+value,640,m_y_line.y2()+value);
    LinePosChangeSignal(m_x_line.x1(),m_y_line.y1());
    update();
}

/**
 * @brief FWWHMeasureLabel::MoveLeft
 * @author dgq
 * @note 向左移动一个像素
 */
void FWWHMeasureLabel::MoveLeft(int value)
{
    if(m_x_line.x1() > value )
        m_x_line.setLine(m_x_line.x1()-value,0,m_x_line.x2()-value,640);
    LinePosChangeSignal(m_x_line.x1(),m_y_line.y1());
    update();
}

/**
 * @brief FWWHMeasureLabel::MoveRight
 * @author dgq
 * @note 向右移动一个像素
 */
void FWWHMeasureLabel::MoveRight(int value)
{
    if(m_x_line.x1() < 640-value)
        m_x_line.setLine(m_x_line.x1()+value,0,m_x_line.x2()+value,640);
    LinePosChangeSignal(m_x_line.x1(),m_y_line.y1());
    update();
}

void FWWHMeasureLabel::SetXDirLine(int line_x)
{
    m_x_line.setLine(line_x,0,line_x,480);
    LinePosChangeSignal(m_x_line.x1(),m_y_line.y1());
    update();
}
void FWWHMeasureLabel::SetYDirLine(int line_y)
{
    m_y_line.setLine(0,line_y,640,line_y);
    LinePosChangeSignal(m_x_line.x1(),m_y_line.y1());
    update();
}

void FWWHMeasureLabel::SetXCurveLines(QVector<QPoint> points)
{
    m_Xpoints = points;
    update();
}
void FWWHMeasureLabel::SetYCurveLines(QVector<QPoint> points)
{
    m_Ypoints = points;
    update();
}
void FWWHMeasureLabel::SetPenColor(void *pen_color)
{
    this->m_pen_color = pen_color;
}
