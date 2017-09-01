#include <QDebug>
#include "FWMatchSkeletonLabel.h"
#include "BasicDefine.h"
FWMatchSkeletonLabel::FWMatchSkeletonLabel(QWidget *parent) : QLabel(parent)
{
    m_rectEditOut = QRect(QPoint(30,30),QPoint(610,450));
    m_rectEditIn = QRect(QPoint(200,200),QPoint(400,300));
    iSelectKind = 0;
    m_list_eidt_osd = 1;
    m_pen_color = NULL;
}
void FWMatchSkeletonLabel::SetPenColor(void *pen_color)
{
    this->m_pen_color = pen_color;
}
/**
 * @brief FWMatchSkeletonLabel::ShowOsd
 * @param iFlag OSD是否显示标志
 * @author dgq
 * @note 设置OSD显示标志位
 */
void FWMatchSkeletonLabel::ShowOsd(int iFlag)
{
    this->m_list_eidt_osd = iFlag;
}

/**
 * @brief FWMatchSkeletonLabel::paintEvent
 * @param e
 * @author dgq
 * @note 轮廓匹配的OSD绘制
 */
void FWMatchSkeletonLabel::paintEvent(QPaintEvent *e)
{
    QLabel::paintEvent(e);
    QPainter painter(this);
    QPen pen;
    PEN_COLOR * pencolor = (PEN_COLOR*)m_pen_color;
    if(m_list_eidt_osd == 1)
    {
        if(iSelectKind ==1 || iSelectKind==2)
        {
            if(pencolor !=NULL)
            {
                pen.setColor(pencolor->m_vt_color[pencolor->task_osd.task_osd_select_color]);
                pen.setWidth(pencolor->task_osd.task_osd_select_width);
                painter.setPen(pen);
            }

        }else
        {

            if(pencolor !=NULL)
            {
                pen.setColor(pencolor->m_vt_color[pencolor->task_osd.task_osd_edit_color]);
                pen.setWidth(pencolor->task_osd.task_osd_edit_width);
                painter.setPen(pen);
            }
        }
        painter.setPen(pen);
        painter.drawRect(m_rectEditOut);
        painter.drawRect(m_rectEditOut.topLeft().x()-5,m_rectEditOut.topLeft().y()-5,10,10);
        painter.drawRect(m_rectEditOut.bottomRight().x()-5,m_rectEditOut.bottomRight().y()-5,10,10);

        if(iSelectKind ==3 || iSelectKind==4)
        {
            if(pencolor !=NULL)
            {
                pen.setColor(pencolor->m_vt_color[pencolor->task_osd.task_osd_select_color]);
                pen.setWidth(pencolor->task_osd.task_osd_select_width);
                painter.setPen(pen);
            }

        }else
        {
            if(pencolor !=NULL)
            {
                pen.setColor(pencolor->m_vt_color[pencolor->task_osd.task_osd_edit_color]);
                pen.setWidth(pencolor->task_osd.task_osd_edit_width);
                painter.setPen(pen);
            }
        }
        painter.setPen(pen);
        painter.drawRect(m_rectEditIn);
        painter.drawRect(m_rectEditIn.topLeft().x()-5,m_rectEditIn.topLeft().y()-5,10,10);
        painter.drawRect(m_rectEditIn.bottomRight().x()-5,m_rectEditIn.bottomRight().y()-5,10,10);
    }
}

/**
 * @brief FWMatchSkeletonLabel::mousePressEvent
 * @param ev
 * @author dgq
 * @note 鼠标按下事件响应函数
 */
void FWMatchSkeletonLabel::mousePressEvent(QMouseEvent *ev)
{
    int x = ev->pos().x();
    int y = ev->pos().y();

    iSelectKind = 0;

    if(IsInEditRect(x,y,&m_rectEditOut)== 1)
    {
        iSelectKind =1;
    }else if(IsInEditRect(x,y,&m_rectEditOut)== 2)
    {
        iSelectKind =2;
    }

    if(iSelectKind !=0)
    {
        update();
        return;
    }
    if(IsInEditRect(x,y,&m_rectEditIn)== 1)
    {

        iSelectKind =3;
    }else if(IsInEditRect(x,y,&m_rectEditIn)== 2)
    {
        iSelectKind =4;
    }
    update();
}

/**
 * @brief FWMatchSkeletonLabel::mouseMoveEvent
 * @param ev
 * @author dgq
 * @note 鼠标移动响应函数
 */
void FWMatchSkeletonLabel::mouseMoveEvent(QMouseEvent *ev)
{
    int x = ev->pos().x();
    int y = ev->pos().y();

    if(iSelectKind == 1)
    {
        /*if(m_rectEditOut.m_rect_x1_right_bottom-x < 100 || m_rectEditOut.m_rect_y1_right_bottom -y<100)
            return;*/

        if(x > m_rectEditIn.topLeft().x() -20 || y > m_rectEditIn.topLeft().y()-20)
            return;
        m_rectEditOut.setTopLeft(ev->pos());
        JudgmentRectBoundary();

        //SignalUpdataXY();
        iSelectPoint = 1;
        signalPointsChange(m_rectEditOut.topLeft(),1);

    }else if(iSelectKind ==2)
    {
        /*if(x -m_rectEditOut.m_rect_x1_Left_top< 100 || y-m_rectEditOut.m_rect_y1_Left_top<100)
            return;*/
        if(x < m_rectEditIn.bottomRight().x() + 20  || y < m_rectEditIn.bottomRight().y() + 20)
            return;
        m_rectEditOut.setBottomRight(ev->pos());
        JudgmentRectBoundary();

        //SignalUpdataXY();
        iSelectPoint = 2;
        signalPointsChange(m_rectEditOut.bottomRight(),2);

    }else if(iSelectKind ==3)
    {
        if(m_rectEditIn.bottomRight().x() - x < 60 || m_rectEditIn.bottomRight().y() -y < 60)
            return;
        if(x-20 < m_rectEditOut.topLeft().x() || y-20 < m_rectEditOut.topLeft().y())
            return;
        m_rectEditIn.setTopLeft(ev->pos());
        JudgmentRectBoundary();

        //SignalUpdataXY();
        iSelectPoint = 3;
        signalPointsChange(m_rectEditIn.topLeft(),3);

    }else if(iSelectKind == 4)
    {
        if(x- m_rectEditIn.topLeft().x() < 60 ||y-m_rectEditIn.topLeft().y() <60)
            return;
        if(x+20 > m_rectEditOut.bottomRight().x() || y+20 > m_rectEditOut.bottomRight().y())
            return;
        m_rectEditIn.setBottomRight(ev->pos());
        JudgmentRectBoundary();

        //SignalUpdataXY();
        iSelectPoint = 4;
        signalPointsChange(m_rectEditIn.bottomRight(),4);
    }
    if(iSelectKind !=0)
    {
        return;
    }

}

/**
 * @brief FWMatchSkeletonLabel::mouseReleaseEvent
 * @param ev
 * @author dgq
 * @note 鼠标释放事件响应函数
 */
void FWMatchSkeletonLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    //QLabel::mouseReleaseEvent(ev);
}

/**
 * @brief FWMatchSkeletonLabel::IsInEditRect
 * @param x 点击位置的X坐标
 * @param y 点击位置的Y坐标
 * @param rect 点中的搜索框
 * @return 选中的点
 * @author dgq
 * @note 判断鼠标按下位置的位置是搜索框的左上顶点还是右下顶点
 */
int FWMatchSkeletonLabel::IsInEditRect(int x,int y,QRect *rect)
{
    int  ret = 0;

    if(x > rect->topLeft().x()-RESPONSERANGERECTEDIT && x < rect->topLeft().x()+RESPONSERANGERECTEDIT &&
            y > rect->topLeft().y()-RESPONSERANGERECTEDIT && y < rect->topLeft().y()+RESPONSERANGERECTEDIT)
    {
        ret =1;

    }else if(x > rect->bottomRight().x()-RESPONSERANGERECTEDIT && x < rect->bottomRight().x()+RESPONSERANGERECTEDIT &&
             y >  rect->bottomRight().y()-RESPONSERANGERECTEDIT && y < rect->bottomRight().y()+RESPONSERANGERECTEDIT)
    {
        ret =2;

    }else
    {
        ret = 0;
    }
    return ret;
}

/**
 * @brief FWMatchSkeletonLabel::JudgmentRectBoundary
 * @author dgq
 * @note 矩形框的边界位置限制判断
 */
void FWMatchSkeletonLabel::JudgmentRectBoundary()
{
    if(m_rectEditIn.topLeft().x() < m_rectEditOut.topLeft().x()+20 )
    {
        m_rectEditIn.setTopLeft(QPoint(m_rectEditOut.topLeft().x()+20,m_rectEditIn.topLeft().y()));
    }else if(m_rectEditIn.topLeft().x() > m_rectEditOut.bottomRight().x()-20)
    {
        m_rectEditIn.setTopLeft(QPoint(m_rectEditOut.bottomRight().x()-20,m_rectEditIn.topLeft().y()));
    }else if(m_rectEditIn.bottomRight().x() > m_rectEditOut.bottomRight().x()-20)
    {
        m_rectEditIn.setBottomRight(QPoint(m_rectEditOut.bottomRight().x()-20,m_rectEditIn.bottomRight().y()));
    }
    else if(m_rectEditIn.bottomRight().x() < m_rectEditOut.topLeft().x()+20)
    {
        m_rectEditIn.setBottomRight(QPoint(m_rectEditOut.bottomRight().x()+20,m_rectEditIn.bottomRight().y()));
    }

    if(m_rectEditIn.topLeft().y() < m_rectEditOut.topLeft().y()+20 )
    {
        m_rectEditIn.setTopLeft(QPoint(m_rectEditIn.topLeft().x(),m_rectEditOut.topLeft().y()+20));

    }else if(m_rectEditIn.topLeft().y() > m_rectEditOut.bottomRight().y()-20)
    {
        m_rectEditIn.setTopLeft(QPoint(m_rectEditIn.topLeft().x(),m_rectEditOut.topLeft().y()-20));

    }else if(m_rectEditIn.bottomRight().y() > m_rectEditOut.bottomRight().y()-20)
    {
        m_rectEditIn.setBottomRight(QPoint(m_rectEditIn.bottomRight().x(),m_rectEditOut.bottomRight().y()-20));
    }
    else if(m_rectEditIn.bottomRight().y() < m_rectEditOut.topLeft().y()+20)
    {
        m_rectEditIn.setBottomRight(QPoint(m_rectEditIn.bottomRight().x(),m_rectEditOut.bottomRight().y()+20));
    }

    if(m_rectEditOut.topLeft().x() < STARTX)
    {
        m_rectEditOut.setTopLeft(QPoint(STARTX,m_rectEditOut.topLeft().y()));

    }else if(m_rectEditOut.topLeft().x() > ENDX)
    {
        m_rectEditOut.setTopLeft(QPoint(ENDX,m_rectEditOut.topLeft().y()));
    }else if(m_rectEditOut.bottomRight().x() < STARTX)
    {
        m_rectEditOut.setBottomRight(QPoint(STARTX,m_rectEditOut.bottomRight().y()));

    }else if(m_rectEditOut.bottomRight().x() > ENDX)
    {
        m_rectEditOut.setBottomRight(QPoint(ENDX,m_rectEditOut.bottomRight().y()));
    }

    if(m_rectEditOut.topLeft().y() < STARTY)
    {
        qDebug()<<"m_rectEditOut.topLeft().y() = "<<m_rectEditOut.topLeft().y();
        m_rectEditOut.setTopLeft(QPoint(m_rectEditOut.topLeft().x(),STARTY));

    }else if(m_rectEditOut.topLeft().y() > ENDY)
    {
        m_rectEditOut.setTopLeft(QPoint(m_rectEditOut.topLeft().x(),ENDY));
    }else if(m_rectEditOut.bottomRight().y() < STARTY)
    {
        m_rectEditOut.setBottomRight(QPoint(m_rectEditOut.bottomRight().x(),STARTY));

    }else if(m_rectEditOut.bottomRight().y() > ENDY)
    {
        m_rectEditOut.setBottomRight(QPoint(m_rectEditOut.bottomRight().x(),ENDY));
    }
    update();
}

/**
 * @brief FWMatchSkeletonLabel::SetSearchRect
 * @param rect 搜索框
 * @author dgq
 * @note 设置搜索框
 */
void FWMatchSkeletonLabel::SetSearchRect(QRect rect)
{
    m_rectEditOut = rect;
    update();
}

/**
 * @brief FWMatchSkeletonLabel::GetSearchRect
 * @return 搜索框
 * @author dgq
 * @note 返回搜索框参数
 */
QRect FWMatchSkeletonLabel::GetSearchRect()
{
    return m_rectEditOut;
}

/**
 * @brief FWMatchSkeletonLabel::SetTrainRect
 * @param rect 学习框
 * @author dgq
 * @note 设置学习框
 */
void FWMatchSkeletonLabel::SetTrainRect(QRect rect)
{
    m_rectEditIn = rect;
    update();
}

/**
 * @brief FWMatchSkeletonLabel::GetTrainRect
 * @return 学习框
 * @author dgq
 * @note 返回学习框参数
 */
QRect FWMatchSkeletonLabel::GetTrainRect()
{
    return m_rectEditIn;
}

/**
 * @brief FWMatchSkeletonLabel::MoveUp
 * @author dgq
 * @note 向上移动一个像素
 */
void FWMatchSkeletonLabel::MoveUp(int value)
{
    if(iSelectKind == 1)
    {
        if(m_rectEditOut.topLeft().y() > STARTY + value)
            m_rectEditOut.setTopLeft(QPoint(m_rectEditOut.topLeft().x(),m_rectEditOut.topLeft().y()-value));
        else
            m_rectEditOut.setTopLeft(QPoint(m_rectEditOut.topLeft().x(),1));
        signalPointsChange(m_rectEditOut.topLeft(),iSelectKind);
    }else if(iSelectKind == 2)
    {
        if(m_rectEditOut.bottomRight().y() > m_rectEditIn.bottomRight().y()+20)
            m_rectEditOut.setBottomRight(QPoint(m_rectEditOut.bottomRight().x(),m_rectEditOut.bottomRight().y()-value));
        signalPointsChange(m_rectEditOut.bottomRight(),iSelectKind);
    }else if(iSelectKind == 3)
    {
        if(m_rectEditIn.topLeft().y() > m_rectEditOut.topLeft().y()+20)
            m_rectEditIn.setTopLeft(QPoint(m_rectEditIn.topLeft().x(),m_rectEditIn.topLeft().y()- value));
        signalPointsChange(m_rectEditIn.topLeft(),iSelectKind);
    }else if(iSelectKind == 4)
    {
        if(m_rectEditIn.bottomRight().y() > m_rectEditIn.topLeft().y()+60)
            m_rectEditIn.setBottomRight(QPoint(m_rectEditIn.bottomRight().x(),m_rectEditIn.bottomRight().y()-value));
        signalPointsChange(m_rectEditIn.bottomRight(),iSelectKind);
    }
//    JudgmentRectBoundary();
    update();
}

/**
 * @brief FWMatchSkeletonLabel::MoveDown
 * @author dgq
 * @note 向下移动一个像素
 */
void FWMatchSkeletonLabel::MoveDown(int value)
{
    if(iSelectKind == 1)
    {
        if(m_rectEditOut.topLeft().y() < m_rectEditIn.topLeft().y()-20)
            m_rectEditOut.setTopLeft(QPoint(m_rectEditOut.topLeft().x(),m_rectEditOut.topLeft().y()+value));
        signalPointsChange(m_rectEditOut.topLeft(),iSelectKind);

    }else if(iSelectKind == 2)
    {
        if(m_rectEditOut.bottomRight().y() < ENDY-value)
            m_rectEditOut.setBottomRight(QPoint(m_rectEditOut.bottomRight().x(),m_rectEditOut.bottomRight().y()+value));
        else
            m_rectEditOut.setBottomRight(QPoint(m_rectEditOut.bottomRight().x(),479));
        signalPointsChange(m_rectEditOut.bottomRight(),iSelectKind);
    }else if(iSelectKind == 3)
    {
        if(m_rectEditIn.topLeft().y() < m_rectEditIn.bottomRight().y()-60)
            m_rectEditIn.setTopLeft(QPoint(m_rectEditIn.topLeft().x(),m_rectEditIn.topLeft().y()+value));
        signalPointsChange(m_rectEditIn.topLeft(),iSelectKind);
    }else if(iSelectKind == 4)
    {
        if(m_rectEditIn.bottomRight().y() < m_rectEditOut.bottomRight().y()-20)
            m_rectEditIn.setBottomRight(QPoint(m_rectEditIn.bottomRight().x(),m_rectEditIn.bottomRight().y()+value));
        signalPointsChange(m_rectEditIn.bottomRight(),iSelectKind);
    }
//    JudgmentRectBoundary();
    update();
}

void FWMatchSkeletonLabel::SetRectPoint(int index)
{
    iSelectKind = index;
    update();
}

/**
 * @brief FWMatchSkeletonLabel::MoveLeft
 * @author dgq
 * @note 向左移动一个像素
 */
void FWMatchSkeletonLabel::MoveLeft(int value)
{
    if(iSelectKind == 1)
    {
        if(m_rectEditOut.topLeft().x() > STARTX+value)
            m_rectEditOut.setTopLeft(QPoint(m_rectEditOut.topLeft().x()-value,m_rectEditOut.topLeft().y()));
        else
            m_rectEditOut.setTopLeft(QPoint(1,m_rectEditOut.topLeft().y()));
        signalPointsChange(m_rectEditOut.topLeft(),iSelectKind);

    }else if(iSelectKind == 2)
    {
        if(m_rectEditOut.bottomRight().x() > m_rectEditIn.bottomRight().x()+20)
            m_rectEditOut.setBottomRight(QPoint(m_rectEditOut.bottomRight().x()-value,m_rectEditOut.bottomRight().y()));
        signalPointsChange(m_rectEditOut.bottomRight(),iSelectKind);
    }else if(iSelectKind == 3)
    {
        if(m_rectEditIn.topLeft().x()>m_rectEditOut.topLeft().x()+20)
            m_rectEditIn.setTopLeft(QPoint(m_rectEditIn.topLeft().x()-value,m_rectEditIn.topLeft().y()));
        signalPointsChange(m_rectEditIn.topLeft(),iSelectKind);
    }else if(iSelectKind == 4)
    {
        if(m_rectEditIn.bottomRight().x() > m_rectEditIn.topLeft().x()+60)
            m_rectEditIn.setBottomRight(QPoint(m_rectEditIn.bottomRight().x()-value,m_rectEditIn.bottomRight().y()));
        signalPointsChange(m_rectEditIn.bottomRight(),iSelectKind);
    }
//    JudgmentRectBoundary();
    update();
}

/**
 * @brief FWMatchSkeletonLabel::MoveRight
 * @author dgq
 * @note 向右移动一个像素
 */
void FWMatchSkeletonLabel::MoveRight(int value)
{
    if(iSelectKind == 1)
    {
        if(m_rectEditOut.topLeft().x() < m_rectEditIn.topLeft().x()-20)
            m_rectEditOut.setTopLeft(QPoint(m_rectEditOut.topLeft().x()+value,m_rectEditOut.topLeft().y()));
        signalPointsChange(m_rectEditOut.topLeft(),iSelectKind);

    }else if(iSelectKind == 2)
    {
        if(m_rectEditOut.bottomRight().x() < ENDX-value)
            m_rectEditOut.setBottomRight(QPoint(m_rectEditOut.bottomRight().x()+value,m_rectEditOut.bottomRight().y()));
        else
            m_rectEditOut.setBottomRight(QPoint(639,m_rectEditOut.bottomRight().y()));
        signalPointsChange(m_rectEditOut.bottomRight(),iSelectKind);
    }else if(iSelectKind == 3)
    {
        if(m_rectEditIn.topLeft().x() < m_rectEditIn.bottomRight().x() -60)
            m_rectEditIn.setTopLeft(QPoint(m_rectEditIn.topLeft().x()+value,m_rectEditIn.topLeft().y()));
        signalPointsChange(m_rectEditIn.topLeft(),iSelectKind);
    }else if(iSelectKind == 4)
    {
        if(m_rectEditIn.bottomRight().x() < m_rectEditOut.bottomRight().x() -20)
            m_rectEditIn.setBottomRight(QPoint(m_rectEditIn.bottomRight().x()+value,m_rectEditIn.bottomRight().y()));
        signalPointsChange(m_rectEditIn.bottomRight(),iSelectKind);
    }
//    JudgmentRectBoundary();
    update();
}
