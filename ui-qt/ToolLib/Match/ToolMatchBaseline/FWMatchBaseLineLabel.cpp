#include "FWMatchBaseLineLabel.h"
#include <QDebug>
#include <BasicDefine.h>

FWMatchBaseLineLabel::FWMatchBaseLineLabel(QWidget *parent) : QLabel(parent)
{
    m_point1.setX(100);
    m_point1.setY(100);
    m_point2.setX(200);
    m_point2.setY(200);
    m_select = 0;
    m_line_num =1;
    m_current_point = 1;
    m_sample_line_num = 0;
    m_current_index = 0;
    for(int i = 0;i<20;i++)
    {
        m_x1[i] = -10;
        m_y1[i] = -10;
        m_x2[i] = -10;
        m_y2[i] = -10;
        m_points1[i].setX(320);
        m_points1[i].setY(10);
        m_points2[i].setX(320);
        m_points2[i].setY(470);
   }
    m_pen_color = NULL;

}

/**
 * @brief FWMatchBaseLineLabel::SetBaseLineNum
 * @param num 基准线数量
 * @author dgq
 * @note 设置基准线的数量
 */
void FWMatchBaseLineLabel::SetBaseLineNum(int num)
{
    this->m_line_num = num;
    this->m_current_index = num-1;
    update();
    emit Point1ChangeSignal(m_points1[m_current_index],m_current_index);
    emit Point2ChangeSignal(m_points2[m_current_index],m_current_index);

}

/**
 * @brief FWMatchBaseLineLabel::SetBaseLineCurrentIndex
 * @param index 当前基准线索引
 * @author dgq
 * @note 设置当前基准线索引
 */
void FWMatchBaseLineLabel::SetBaseLineCurrentIndex(int index)
{
    this->m_current_index = index;
    update();
    emit Point1ChangeSignal(m_points1[m_current_index],m_current_index);
    emit Point2ChangeSignal(m_points2[m_current_index],m_current_index);

}

/**
 * @brief FWMatchBaseLineLabel::SetBaseLineCurrentPoint
 * @param index 当前基准线编辑点的索引
 * @author dgq
 * @note 设置当前基准线编辑点的索引
 */
void FWMatchBaseLineLabel::SetBaseLineCurrentPoint(int index)
{
    this->m_current_point = index;
    update();
    if(index == 1)
        emit Point1ChangeSignal(m_points1[m_current_index],m_current_index);
    else
        emit Point2ChangeSignal(m_points2[m_current_index],m_current_index);
}

/**
 * @brief FWMatchBaseLineLabel::SetBaseLinePoint1
 * @param point1 基准线点a
 * @author dgq
 * @note 设置基准线点a
 */
void FWMatchBaseLineLabel::SetBaseLinePoint1(QPoint point1)
{
    //m_point1 = point1;
    m_points1[m_current_index] = point1;

}

/**
 * @brief FWMatchBaseLineLabel::SetBaseLinePoint2
 * @param point2 基准线点b
 * @author dgq
 * @note 设置基准线点b
 */
void FWMatchBaseLineLabel::SetBaseLinePoint2(QPoint point2)
{
    //m_point2 = point2;
    m_points2[m_current_index] = point2;

}

/**
 * @brief FWMatchBaseLineLabel::paintEvent
 * @param e
 * @author dgq
 * @note 基准线绘制OSD
 */
void FWMatchBaseLineLabel::paintEvent(QPaintEvent *e)
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
        pen.setColor(pencolor->m_vt_color[pencolor->task_osd.task_osd_edit_color]);
        pen.setWidth(pencolor->task_osd.task_osd_edit_width);
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

}

/**
 * @brief FWMatchBaseLineLabel::mousePressEvent
 * @param ev
 * @author dgq
 * @note 鼠标按下事件的响应函数
 */
void FWMatchBaseLineLabel::mousePressEvent(QMouseEvent *ev)
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
            m_current_point = 1;
            m_current_index = i;
            emit Point1ChangeSignal(m_points1[i],m_current_index);
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
                m_current_point = 2;
                emit Point2ChangeSignal(m_points2[i],m_current_index);
                break;
            }
        }
    }
    m_press_point = ev->pos();
    update();

}

/**
 * @brief FWMatchBaseLineLabel::mouseMoveEvent
 * @param ev
 * @author dgq
 * @note 鼠标移动事件响应函数
 */
void FWMatchBaseLineLabel::mouseMoveEvent(QMouseEvent *ev)
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
            emit Point1ChangeSignal(m_points1[m_current_index],m_current_index);
        }
    }else if(m_select ==2)
    {
        ix = m_points2[m_current_index].x() + disX;
        iy = m_points2[m_current_index].y() + disY;

        if(ix >= 0 && ix <= 640 && iy>=0 && iy<=480)
        {
            m_points2[m_current_index].setX(m_points2[m_current_index].x() + disX);
            m_points2[m_current_index].setY(m_points2[m_current_index].y() + disY);
            emit Point2ChangeSignal(m_points2[m_current_index],m_current_index);
        }
    }
    m_press_point = ev->pos();
    update();
}

/**
 * @brief FWMatchBaseLineLabel::mouseReleaseEvent
 * @param ev
 * @author dgq
 * @note 鼠标释放事件响应函数
 */
void FWMatchBaseLineLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    if(m_select != 0)
    {
//        emit Point1ChangeSignal(m_points1[m_current_index],m_current_index);
//        emit Point2ChangeSignal(m_points2[m_current_index],m_current_index);
        m_select = 0;
    }
}

/**
 * @brief FWMatchBaseLineLabel::SetSampleLines
 * @param x1 基准线点a的x坐标
 * @param y1 基准线点a的Y坐标
 * @param x2 基准线点b的x坐标
 * @param y2 基准线点b的y坐标
 * @param inum 基准线数量
 * @author dgq
 * @note 取样成功后设置取样后的基准线数据
 */
void FWMatchBaseLineLabel::SetSampleLines(int *x1, int *y1, int *x2, int *y2, int inum)
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

/**
 * @brief FWMatchBaseLineLabel::SetBaseLinePoints
 * @param point1 基准线的点a
 * @param point2 基准线的点b
 * @param num 基准线的数量
 * @author dgq
 * @note 初始化设置基准线的参数
 */
void FWMatchBaseLineLabel::SetBaseLinePoints(QPoint *point1,QPoint *point2,int num)
{
    this->m_line_num = num;

    for(int i= 0; i< num ;i++)
    {
        this->m_points1[i] = point1[i];
        this->m_points2[i] = point2[i];
    }
    update();
    Point1ChangeSignal(m_points1[0],0);
    Point2ChangeSignal(m_points2[0],0);
}

/**
 * @brief FWMatchBaseLineLabel::GetBaseLines
 * @return 基准线(数量，坐标)
 * @author dgq
 * @note 返回基准线参数
 */
QVector<QLine> FWMatchBaseLineLabel::GetBaseLines()
{
    QVector<QLine> data;
    for(int i = 0; i < m_line_num;i++)
    {
        data.append(QLine(m_points1[i],m_points2[i]));
    }
    return data;
}

/**
 * @brief FWMatchBaseLineLabel::MoveUp
 * @author dgq
 * @note 向上移动一个像素
 */
void FWMatchBaseLineLabel::MoveUp(int value)
{
    if(m_current_point == 1)
    {
        if(m_points1[m_current_index].y() > value)
            m_points1[m_current_index].setY(m_points1[m_current_index].y()-value);
        emit Point1ChangeSignal(m_points1[m_current_index],m_current_index);
    }else if(m_current_point == 2)
        {
            if(m_points2[m_current_index].y() > value)
                m_points2[m_current_index].setY(m_points2[m_current_index].y()-value);
            emit Point2ChangeSignal(m_points2[m_current_index],m_current_index);
        }
    update();
}

/**
 * @brief FWMatchBaseLineLabel::MoveDown
 * @author dgq
 * @note 向下移动一个像素
 */
void FWMatchBaseLineLabel::MoveDown(int value)
{
    if(m_current_point == 1)
    {
        if(m_points1[m_current_index].y() < 480-value)
            m_points1[m_current_index].setY(m_points1[m_current_index].y()+ value);
        emit Point1ChangeSignal(m_points1[m_current_index],m_current_index);
    }else if(m_current_point == 2)
        {
            if(m_points2[m_current_index].y() < 480-value)
                m_points2[m_current_index].setY(m_points2[m_current_index].y()+value);
            emit Point2ChangeSignal(m_points2[m_current_index],m_current_index);
        }
    update();
}

/**
 * @brief FWMatchBaseLineLabel::MoveLeft
 * @author dgq
 * @note 向左移动一个像素
 */
void FWMatchBaseLineLabel::MoveLeft(int value)
{
    if(m_current_point == 1)
    {
        if(m_points1[m_current_index].x() > value )
            m_points1[m_current_index].setX(m_points1[m_current_index].x()-value);
        emit Point1ChangeSignal(m_points1[m_current_index],m_current_index);
    }else if(m_current_point == 2)
        {
            if(m_points2[m_current_index].x() > value)
                m_points2[m_current_index].setX(m_points2[m_current_index].x()-value);
            emit Point2ChangeSignal(m_points2[m_current_index],m_current_index);
        }

    update();
}

/**
 * @brief FWMatchBaseLineLabel::MoveRight
 * @author dgq
 * @note 向右移动一个像素
 */
void FWMatchBaseLineLabel::MoveRight(int value)
{
    if(m_current_point == 1)
    {
        if(m_points1[m_current_index].x() < 640-value )
            m_points1[m_current_index].setX(m_points1[m_current_index].x()+value);
        emit Point1ChangeSignal(m_points1[m_current_index],m_current_index);
    }else if(m_current_point == 2)
        {
            if(m_points2[m_current_index].x() < 640-value)
                m_points2[m_current_index].setX(m_points2[m_current_index].x()+value);
            emit Point2ChangeSignal(m_points2[m_current_index],m_current_index);
        }
    update();
}
void FWMatchBaseLineLabel::SetPenColor(void *pen_color)
{
    this->m_pen_color = pen_color;
}
