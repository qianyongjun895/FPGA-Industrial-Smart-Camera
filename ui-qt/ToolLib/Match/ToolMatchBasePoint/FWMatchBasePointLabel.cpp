#include "FWMatchBasePointLabel.h"
#include "BasicDefine.h"
FWMatchBasePointLabel::FWMatchBasePointLabel(QWidget *parent) : QLabel(parent)
{
    m_num = 1;
    m_select = 0;
    m_current_index = 0;
    for(int i = 0; i < BASE_POINT_NUM_MAX;i++)
    {
        m_point[i].setX(320);
        m_point[i].setY(240);
    }
    m_pen_color = NULL;
}

FWMatchBasePointLabel::~FWMatchBasePointLabel()
{

}
void FWMatchBasePointLabel::SetPenColor(void *pen_color)
{
    this->m_pen_color = pen_color;
}
/**
 * @brief FWMatchBasePointLabel::paintEvent
 * @param e
 * @author dgq
 * @note 基准点OSD绘制函数
 */
void FWMatchBasePointLabel::paintEvent(QPaintEvent *e)
{
    QLabel::paintEvent(e);
    QPainter painter(this);
    QPen pen;
    /*pen.setColor(Qt::red);
    pen.setWidth(2);
    painter.setPen(pen);*/
    PEN_COLOR * pencolor = (PEN_COLOR*)m_pen_color;
    if(pencolor !=NULL)
    {
        pen.setColor(pencolor->m_vt_color[pencolor->task_osd.task_osd_edit_color]);
        pen.setWidth(pencolor->task_osd.task_osd_edit_width);
        painter.setPen(pen);
    }
    for(int i=0;i<m_num;i++)
    {
        painter.drawEllipse(m_point[i],10,10);
        painter.drawLine(m_point[i].x()+20,m_point[i].y(),m_point[i].x()-20,m_point[i].y());
        painter.drawLine(m_point[i].x(),m_point[i].y()+20,m_point[i].x(),m_point[i].y()-20);
        painter.drawText(QPoint(m_point[i].x(),m_point[i].y()-20),QString::number(i+1));
    }
    if(pencolor !=NULL)
    {
        pen.setColor(pencolor->m_vt_color[pencolor->task_osd.task_osd_select_color]);
        pen.setWidth(pencolor->task_osd.task_osd_select_width);
        painter.setPen(pen);
    }

    painter.drawEllipse(m_point[m_current_index],10,10);
    painter.drawLine(m_point[m_current_index].x()+20,m_point[m_current_index].y(),m_point[m_current_index].x()-20,m_point[m_current_index].y());
    painter.drawLine(m_point[m_current_index].x(),m_point[m_current_index].y()+20,m_point[m_current_index].x(),m_point[m_current_index].y()-20);
    painter.drawText(QPoint(m_point[m_current_index].x(),m_point[m_current_index].y()-20),QString::number(m_current_index+1));

}

/**
 * @brief FWMatchBasePointLabel::mousePressEvent
 * @param ev
 * @author dgq
 * @note 鼠标点击按下事件
 */
void FWMatchBasePointLabel::mousePressEvent(QMouseEvent *ev)
{
    m_select = 0;
    int x =ev->pos().x();
    int y = ev->pos().y();
    int i =0;
    for (i = 0; i< m_num; i++)
    {
        if(((x-m_point[i].x())*(x-m_point[i].x())+(y-m_point[i].y())*(y-m_point[i].y())) <= 20*20)
        {
            m_select = 1;
            m_current_index = i;
            CurrentPointChangeSignal(m_current_index,m_point[m_current_index]);
            break;
        }
    }
    m_press_point = ev->pos();
    update();
}

/**
 * @brief FWMatchBasePointLabel::mouseReleaseEvent
 * @param ev
 * @author dgq
 * @note 鼠标点击释放事件
 */
void FWMatchBasePointLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    if(m_select != 0)
    {
        CurrentPointChangeSignal(m_current_index,m_point[m_current_index]);
        m_select = 0;
    }
}

/**
 * @brief FWMatchBasePointLabel::mouseMoveEvent
 * @param ev
 * @author dgq
 * @note 鼠标点击移动事件
 */
void FWMatchBasePointLabel::mouseMoveEvent(QMouseEvent *ev)
{
    QPoint pos = ev->pos();

    int disX = pos.x() - m_press_point.x();
    int disY = pos.y() - m_press_point.y();
    int ix = 0;
    int iy = 0;

    if(m_select ==1)
    {
        ix = m_point[m_current_index].x() + disX;
        iy = m_point[m_current_index].y() + disY;
        if(ix >= 0 && ix <= 640 && iy>=0 && iy<=480)
        {
            m_point[m_current_index].setX(m_point[m_current_index].x() + disX);
            m_point[m_current_index].setY(m_point[m_current_index].y() + disY);
            //todo点移动或者当前点切换时将当前点的数据传给界面控件显示出来
            CurrentPointChangeSignal(m_current_index,m_point[m_current_index]);
            //            SINGLEPOINT singlPoint;
            //            singlPoint.icurrent = m_current_index;
            //            singlPoint.iSelectPoint = m_select;
            //            singlPoint.point1 = m_point[m_current_index];
            //            singlPoint.point2 = m_point[m_current_index];
            //            signalPointsChange(&singlPoint,SIGNALMOVEPOINT1);

        }
    }
    m_press_point = ev->pos();
    update();
}

/**
 * @brief FWMatchBasePointLabel::SetBasePointData
 * @param data 基准点参数
 * @author dgq
 * @note 设置基准点的数量以及坐标参数
 */
void FWMatchBasePointLabel::SetBasePointData(QVector<QPoint> data)
{
    int inum = data.count();
    if(inum > BASE_POINT_NUM_MAX)
        inum = BASE_POINT_NUM_MAX;
    this->m_num =inum;
    for (int i = 0; i < m_num;i++)
    {
        m_point[i] = data[i];
    }
    update();
    CurrentPointChangeSignal(0,m_point[0]);
}

/**
 * @brief FWMatchBasePointLabel::GetBasePointData
 * @return 基准点参数
 * @author dgq
 * @note 返回基准点的参数
 */
QVector<QPoint> FWMatchBasePointLabel::GetBasePointData()
{
    QVector<QPoint> vt_Points;
    for(int i = 0; i < m_num; i++)
    {
        vt_Points.append(m_point[i]);
    }
    return vt_Points;
}

/**
 * @brief FWMatchBasePointLabel::SetBasePointNum
 * @param num 基准点数量
 * @author dgq
 * @note 设置基准点的个数
 */
void FWMatchBasePointLabel::SetBasePointNum(int num)
{
    m_num = num;
    if(m_current_index > num - 1)
        m_current_index = num -1;
    CurrentPointChangeSignal(m_current_index,m_point[m_current_index]);
    update();
}

/**
 * @brief FWMatchBasePointLabel::GetBasePointNum
 * @return 基准点数量
 * @author dgq
 * @note 返回基准点数量
 */
int FWMatchBasePointLabel::GetBasePointNum()
{
    return m_num;
}

/**
 * @brief FWMatchBasePointLabel::SetBasePointCurrentIndex
 * @param index 当前基准点的索引号
 * @author dgq
 * @note 设置当前基准点的索引号
 */
void FWMatchBasePointLabel::SetBasePointCurrentIndex(int index)
{
    m_current_index = index;
    CurrentPointChangeSignal(m_current_index,m_point[m_current_index]);
    update();
}

/**
 * @brief FWMatchBasePointLabel::GetBasePointCurrentIndex
 * @return 获取当前基准点的索引号
 * @author dgq
 * @note 返回当前基准点的索引号
 */
int FWMatchBasePointLabel::GetBasePointCurrentIndex()
{
    return m_current_index;
}

/**
 * @brief FWMatchBasePointLabel::KeyMoveUp
 * @param value 移动的像素单位
 * @author dgq
 * @note 向上移动value个像素单位
 */
void FWMatchBasePointLabel::KeyMoveUp(int value)
{
    int x,y;
    x = m_point[m_current_index].x();
    y = m_point[m_current_index].y()-value;
    if(y < 0)
    {
        return;
    }
    m_point[m_current_index].setX(x);
    m_point[m_current_index].setY(y);
    update();
    CurrentPointChangeSignal(m_current_index,m_point[m_current_index]);
}

/**
 * @brief FWMatchBasePointLabel::KeyMoveDown
 * @param value 移动的像素单位
 * @author dgq
 * @note 向下移动value个像素单位
 */
void FWMatchBasePointLabel::KeyMoveDown(int value)
{
    int x,y;
    x = m_point[m_current_index].x();
    y = m_point[m_current_index].y()+value;
    if(y > 480)
    {
        return;
    }
    m_point[m_current_index].setX(x);
    m_point[m_current_index].setY(y);
    update();
    CurrentPointChangeSignal(m_current_index,m_point[m_current_index]);
}

/**
 * @brief FWMatchBasePointLabel::KeyMoveLeft
 * @param value 移动的像素单位
 * @author dgq
 * @note 向左移动value个像素单位
 */
void FWMatchBasePointLabel::KeyMoveLeft(int value)
{
    int x,y;
    x = m_point[m_current_index].x()-value;
    y = m_point[m_current_index].y();
    if(x < 0)
    {
        return;
    }
    m_point[m_current_index].setX(x);
    m_point[m_current_index].setY(y);
    update();
    CurrentPointChangeSignal(m_current_index,m_point[m_current_index]);
}

/**
 * @brief FWMatchBasePointLabel::KeyMoveRight
 * @param value 移动的像素单位
 * @author dgq
 * @note 向右移动value个像素单位
 */
void FWMatchBasePointLabel::KeyMoveRight(int value)
{
    int x,y;
    x = m_point[m_current_index].x()+value;
    y = m_point[m_current_index].y();
    if(x > 640)
    {
        return;
    }
    m_point[m_current_index].setX(x);
    m_point[m_current_index].setY(y);
    update();
    CurrentPointChangeSignal(m_current_index,m_point[m_current_index]);
}
