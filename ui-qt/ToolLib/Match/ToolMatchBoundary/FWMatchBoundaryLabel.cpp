#include "FWMatchBoundaryLabel.h"
#include <QDebug>
FWMatchBoundaryLabel::FWMatchBoundaryLabel(QWidget *parent) : QLabel(parent)
{
    m_rectEditOut = QRect(QPoint(150,150),QPoint(500,350));
    m_rectEditX = QRect(QPoint(80,220),QPoint(300,280));
    m_rectEditY = QRect(QPoint(200,80),QPoint(400,200));

    iSelectKind = SELECTNONE;
    m_list_RectY = 0;
    m_list_edit_osd =1;
    m_rectEditY_Direct = 0;
    m_rectEditY_Direct = 0;
}

FWMatchBoundaryLabel::~FWMatchBoundaryLabel()
{

}

/**
 * @brief FWMatchBoundaryLabel::SetListRectY
 * @param iFlag ROI区域是能标志 0：不使能，1：使能
 * @author dgq
 * @note  设置ROI区域搜索框的使能状态
 */
void FWMatchBoundaryLabel::SetListRectY(int iFlag)
{
    m_list_RectY = iFlag;
    update();
}

/**
 * @brief FWMatchBoundaryLabel::OSDLimit
 * @author dgq
 * @note OSD边界限制
 */
void FWMatchBoundaryLabel::OSDLimit()
{
    if(m_rectEditOut.topLeft().x() < STARTX)
        m_rectEditOut.topLeft().setX(STARTX);
    if(m_rectEditOut.bottomRight().x() > ENDX)
        m_rectEditOut.bottomRight().setX(ENDX);
    if(m_rectEditOut.topLeft().y() < STARTY)
        m_rectEditOut.topLeft().setY(STARTY);
    if(m_rectEditOut.bottomRight().y() > ENDY)
        m_rectEditOut.bottomRight().setY(ENDY);

    if(m_rectEditX.topLeft().x() < STARTX)
        m_rectEditX.topLeft().setX(STARTX);
    if(m_rectEditX.bottomRight().x() > ENDX)
        m_rectEditOut.bottomRight().setX(ENDX);
    if(m_rectEditX.topLeft().y() < STARTY)
        m_rectEditX.topLeft().setY(STARTY);
    if(m_rectEditX.bottomRight().y() > ENDY)
        m_rectEditX.bottomRight().setY(ENDY);

    if(m_rectEditY.topLeft().x() < STARTX)
        m_rectEditY.topLeft().setX(STARTX);
    if(m_rectEditY.bottomRight().x() > ENDX)
        m_rectEditY.bottomRight().setX(ENDX);
    if(m_rectEditY.topLeft().y() < STARTY)
        m_rectEditY.topLeft().setY(STARTY);
    if(m_rectEditY.bottomRight().y() > ENDY)
        m_rectEditY.bottomRight().setY(ENDY);
}

/**
 * @brief FWMatchBoundaryLabel::SetRectEditX
 * @param data 边沿搜索框的矩形参数
 * @author dgq
 * @note 设置边沿搜索框参数
 */
void FWMatchBoundaryLabel::SetRectEditX(QRect data)
{
    m_rectEditX = data;
    update();
}

/**
 * @brief FWMatchBoundaryLabel::SetRectEditY
 * @param data Roi搜索框的矩形参数
 * @author dgq
 * @note 设置Roi搜索框参数
 */
void FWMatchBoundaryLabel::SetRectEditY(QRect data)
{
    m_rectEditY = data;
    update();
}

/**
 * @brief FWMatchBoundaryLabel::SetRectEditOut
 * @param data 目标搜索框的矩形参数
 * @author dgq
 * @note 设置目标搜索框参数
 */
void FWMatchBoundaryLabel::SetRectEditOut(QRect data)
{
    m_rectEditOut = data;
    update();
}

/**
 * @brief FWMatchBoundaryLabel::paintEvent
 * @param e
 * @author dgq
 * @note 边沿搜索工具的OSD绘制函数
 */
void FWMatchBoundaryLabel::paintEvent(QPaintEvent *e)
{
    int ix = 0;
    int iy =0;
    QLabel::paintEvent(e);
    QPainter painter(this);
    QPen pen;
    pen.setColor(Qt::red);
    pen.setWidth(2);
    painter.setPen(pen);
    if(iSelectKind ==SELECTRECTOUTTOP || iSelectKind ==SELECTRECTOUTBOTTOM)
    {
        pen.setColor(Qt::blue);
        pen.setWidth(2);
        painter.setPen(pen);

    }else
    {
        pen.setColor(Qt::red);
        pen.setWidth(1);
        painter.setPen(pen);
    }
    painter.drawRect(m_rectEditOut);
    painter.drawRect(m_rectEditOut.topLeft().x()-5,m_rectEditOut.topLeft().y()-5,10,10);
    painter.drawRect(m_rectEditOut.bottomRight().x()-5,m_rectEditOut.bottomRight().y()-5,10,10);

    if(iSelectKind ==SELECTRECTXTOP || iSelectKind ==SELECTRECTXBOTTOM)
    {
        pen.setColor(Qt::blue);
        pen.setWidth(2);
        painter.setPen(pen);

    }else
    {
        pen.setColor(Qt::red);
        pen.setWidth(1);
        painter.setPen(pen);
    }
    painter.drawRect(m_rectEditX);
    painter.drawRect(m_rectEditX.topLeft().x()-5,m_rectEditX.topLeft().y()-5,10,10);
    painter.drawRect(m_rectEditX.bottomRight().x()-5,m_rectEditX.bottomRight().y()-5,10,10);
    if(m_rectEditX_Direct == 0) //x方向
    {
        ix = (m_rectEditX.topLeft().x() + m_rectEditX.bottomRight().x())/2;
        iy =  m_rectEditX.topLeft().y();
        painter.drawLine(ix-10,iy-10,ix,iy);
        painter.drawLine(ix-10,iy+10,ix,iy);

    }else
    {
        ix = m_rectEditX.topLeft().x();
        iy =(m_rectEditX.topLeft().y()+m_rectEditX.bottomRight().y())/2;
        painter.drawLine(ix -10,iy-10,ix,iy);
        painter.drawLine(ix +10,iy-10,ix,iy);
    }

    if(1 == m_list_RectY)
    {
        if(iSelectKind ==SELECTRECTYTOP || iSelectKind ==SELECTRECTYBOTTOM)
        {
            pen.setColor(Qt::blue);
            pen.setWidth(2);
            painter.setPen(pen);
        }else
        {
            pen.setColor(Qt::red);
            pen.setWidth(1);
            painter.setPen(pen);
        }
        painter.drawRect(m_rectEditY);
        painter.drawRect(m_rectEditY.topLeft().x()-5,m_rectEditY.topLeft().y()-5,10,10);
        painter.drawRect(m_rectEditY.bottomRight().x()-5,m_rectEditY.bottomRight().y()-5,10,10);
        if(m_rectEditY_Direct == 0) //x方向
        {
            ix = (m_rectEditY.topLeft().x() + m_rectEditY.bottomRight().x())/2;
            iy =  m_rectEditY.topLeft().y();
            painter.drawLine(ix -10,iy-10,ix,iy);
            painter.drawLine(ix -10,iy+10,ix,iy);

        }else
        {
            ix = m_rectEditY.topLeft().x();
            iy =(m_rectEditY.topLeft().y()+m_rectEditY.bottomRight().y())/2;
            painter.drawLine(ix -10,iy-10,ix,iy);
            painter.drawLine(ix +10,iy-10,ix,iy);
        }
    }
}

/**
 * @brief FWMatchBoundaryLabel::IsInEditRect
 * @param x 点击位置的X坐标
 * @param y 点击位置的Y坐标
 * @param rect 点中的搜索框
 * @return 选中的点
 * @author dgq
 * @note 判断鼠标按下位置的位置是搜索框的左上顶点还是右下顶点
 */
int FWMatchBoundaryLabel::IsInEditRect(int x,int y,QRect *rect)
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
 * @brief FWMatchBoundaryLabel::mousePress
 * @param ev
 * @author dgq
 * @note 鼠标按下事件响应函数
 */
void FWMatchBoundaryLabel::mousePressEvent(QMouseEvent *ev)
{
    int x = ev->pos().x();
    int y = ev->pos().y();

    iSelectKind = SELECTNONE;

    if(IsInEditRect(x,y,&m_rectEditOut)== 1)
    {
        iSelectKind =SELECTRECTOUTTOP;
        signalPointsChange(m_rectEditOut.topLeft(),SELECTRECTOUTTOP);
    }else if(IsInEditRect(x,y,&m_rectEditOut)== 2)
    {
        iSelectKind =SELECTRECTOUTBOTTOM;
        signalPointsChange(m_rectEditOut.bottomRight(),SELECTRECTOUTBOTTOM);
    }

    if(iSelectKind !=SELECTNONE)
    {
        update();
        return;
    }

    if(IsInEditRect(x,y,&m_rectEditX)== 1)
    {
        iSelectKind =SELECTRECTXTOP;
        signalPointsChange(m_rectEditX.topLeft(),SELECTRECTXTOP);
    }else if(IsInEditRect(x,y,&m_rectEditX)== 2)
    {
        iSelectKind =SELECTRECTXBOTTOM;
        signalPointsChange(m_rectEditX.bottomRight(),SELECTRECTXBOTTOM);
    }

    if(iSelectKind !=SELECTNONE)
    {
        update();
        return;
    }
    if(IsInEditRect(x,y,&m_rectEditY)== 1)
    {
        iSelectKind =SELECTRECTYTOP;
        signalPointsChange(m_rectEditY.topLeft(),SELECTRECTOUTBOTTOM);
    }else if(IsInEditRect(x,y,&m_rectEditY)== 2)
    {
        iSelectKind =SELECTRECTYBOTTOM;
        signalPointsChange(m_rectEditY.bottomRight(),SELECTRECTOUTBOTTOM);
    }
    update();
}

/**
 * @brief FWBoundaryMatchLabel::mouseMove
 * @param ev
 * @author dgq
 * @note 鼠标移动事件响应函数
 */
void FWMatchBoundaryLabel::mouseMoveEvent(QMouseEvent *ev)
{
    int x = ev->pos().x();
    int y = ev->pos().y();
    if(iSelectKind == SELECTRECTOUTTOP)
    {
        if(m_rectEditOut.bottomRight().x()-x < 100 || m_rectEditOut.bottomRight().y() -y<100)
            return;
        if(y < STARTY  || x < STARTX)
            return;
        m_rectEditOut.setTopLeft(QPoint(ev->pos()));
        update();
        signalPointsChange(m_rectEditOut.topLeft(),SELECTRECTOUTTOP);
    }else if(iSelectKind == SELECTRECTOUTBOTTOM)
    {
        if(x - m_rectEditOut.topLeft().x() < 100 || y-m_rectEditOut.topLeft().y() <100)
            return;
        if(x > ENDX || y > ENDY)
            return;
        m_rectEditOut.setBottomRight(QPoint(ev->pos()));
        update();
        signalPointsChange(m_rectEditOut.bottomRight(),SELECTRECTOUTBOTTOM);
    }else if(iSelectKind ==SELECTRECTXTOP)
    {
        if(m_rectEditX.bottomRight().x()-x < 100 || m_rectEditX.bottomRight().y() -y<100)
            return;
        if(y < STARTY  || x < STARTX)
            return;
        m_rectEditX.setTopLeft(QPoint(ev->pos()));
        update();
        signalPointsChange(m_rectEditX.topLeft(),SELECTRECTXTOP);
    }else if(iSelectKind == SELECTRECTXBOTTOM)
    {
        if(x - m_rectEditX.topLeft().x() < 60 || y-m_rectEditX.topLeft().y() <60)
            return;
        if(x > ENDX || y > ENDY)
            return;
        m_rectEditX.setBottomRight(QPoint(ev->pos()));
        update();
        signalPointsChange(m_rectEditX.bottomRight(),SELECTRECTXBOTTOM);
    }else if(iSelectKind ==SELECTRECTYTOP)
    {
        if(m_rectEditY.bottomRight().x()-x < 60 || m_rectEditY.bottomRight().y() -y<60)
            return;
        if(y < STARTY  || x < STARTX)
            return;
        m_rectEditY.setTopLeft(QPoint(ev->pos()));
        update();
        signalPointsChange(m_rectEditY.topLeft(),SELECTRECTYTOP);
    }else if(iSelectKind == SELECTRECTYBOTTOM)
    {
        if(x - m_rectEditY.topLeft().x() < 60 || y-m_rectEditY.topLeft().y() <60)
            return;
        if(x > ENDX || y > ENDY)
            return;
        m_rectEditY.setBottomRight(QPoint(ev->pos()));
        update();
        signalPointsChange(m_rectEditY.bottomRight(),SELECTRECTYBOTTOM);
    }
}
/**
 * @brief FWMatchBoundaryLabel::mouseRelease
 * @param ev
 * @author dgq
 * @note 鼠标释放事件响应函数
 */
void FWMatchBoundaryLabel::mouseReleaseEvent(QMouseEvent *ev)
{

}

/**
 * @brief FWMatchBoundaryLabel::SetRectXDirect
 * @param iDirect 0：x方向 1：y方向;
 * @author dgq
 * @note 设置边沿搜索方向
 */
void FWMatchBoundaryLabel::SetRectXDirect(int iDirect)
{
    m_rectEditX_Direct = iDirect; //0 x 1,y;
    update();

}

/**
 * @brief FWMatchBoundaryLabel::SetRectYDirect
 * @param iDirect 0：x方向 1：y方向;
 * @author dgq
 * @note 设置ROI搜索方向
 */
void FWMatchBoundaryLabel::SetRectYDirect(int iDirect)
{
    m_rectEditY_Direct = iDirect;
    update();
}

/**
 * @brief FWMatchBoundaryLabel::GetRectEditOut
 * @return 返回目标搜索框参数
 * @author dgq
 * @note 获取搜索框的位置参数
 */
QRect FWMatchBoundaryLabel::GetRectEditOut()
{
    return m_rectEditOut;
}

/**
 * @brief FWMatchBoundaryLabel::GetRectEditX
 * @return 返回边沿搜索框参数
 * @author dgq
 * @note 获取边沿搜索框的位置参数
 */
QRect FWMatchBoundaryLabel::GetRectEditX()
{
    return m_rectEditY;
}

/**
 * @brief FWMatchBoundaryLabel::GetRectEditY
 * @return 返回ROI搜索框参数
 * @author dgq
 * @note 获取Roi搜索框的位置参数
 */
QRect FWMatchBoundaryLabel::GetRectEditY()
{
    return m_rectEditY;
}

void FWMatchBoundaryLabel::MoveUp(int value)
{
    switch (iSelectKind) {
    case SELECTRECTOUTTOP:
        MoveFunPro(&m_rectEditOut,TOPLEFT,-value,DIRY);
        break;
    case SELECTRECTOUTBOTTOM:
        MoveFunPro(&m_rectEditOut,BOTTOMRIGHT,-value,DIRY);
        break;
    case SELECTRECTXTOP:
        MoveFunPro(&m_rectEditX,TOPLEFT,-value,DIRY);
        break;
    case SELECTRECTXBOTTOM:
        MoveFunPro(&m_rectEditX,BOTTOMRIGHT,-value,DIRY);
        break;
    case SELECTRECTYTOP:
        MoveFunPro(&m_rectEditY,TOPLEFT,-value,DIRY);
        break;
    case SELECTRECTYBOTTOM:
        MoveFunPro(&m_rectEditY,BOTTOMRIGHT,-value,DIRY);
        break;
    default:
        break;
    }
}
void FWMatchBoundaryLabel::MoveDown(int value)
{
    switch (iSelectKind) {
    case SELECTRECTOUTTOP:
        MoveFunPro(&m_rectEditOut,TOPLEFT,value,DIRY);
        break;
    case SELECTRECTOUTBOTTOM:
        MoveFunPro(&m_rectEditOut,BOTTOMRIGHT,value,DIRY);
        break;
    case SELECTRECTXTOP:
        MoveFunPro(&m_rectEditX,TOPLEFT,value,DIRY);
        break;
    case SELECTRECTXBOTTOM:
        MoveFunPro(&m_rectEditX,BOTTOMRIGHT,value,DIRY);
        break;
    case SELECTRECTYTOP:
        MoveFunPro(&m_rectEditY,TOPLEFT,value,DIRY);
        break;
    case SELECTRECTYBOTTOM:
        MoveFunPro(&m_rectEditY,BOTTOMRIGHT,value,DIRY);
        break;
    default:
        break;
    }
}
void FWMatchBoundaryLabel::MoveLeft(int value)
{
    switch (iSelectKind) {
    case SELECTRECTOUTTOP:
        MoveFunPro(&m_rectEditOut,TOPLEFT,-value,DIRX);
        break;
    case SELECTRECTOUTBOTTOM:
        MoveFunPro(&m_rectEditOut,BOTTOMRIGHT,-value,DIRX);
        break;
    case SELECTRECTXTOP:
        MoveFunPro(&m_rectEditX,TOPLEFT,-value,DIRX);
        break;
    case SELECTRECTXBOTTOM:
        MoveFunPro(&m_rectEditX,BOTTOMRIGHT,-value,DIRX);
        break;
    case SELECTRECTYTOP:
        MoveFunPro(&m_rectEditY,TOPLEFT,-value,DIRX);
        break;
    case SELECTRECTYBOTTOM:
        MoveFunPro(&m_rectEditY,BOTTOMRIGHT,-value,DIRX);
        break;
    default:
        break;
    }
}
void FWMatchBoundaryLabel::MoveRight(int value)
{
    switch (iSelectKind) {
    case SELECTRECTOUTTOP:
        MoveFunPro(&m_rectEditOut,TOPLEFT,value,DIRX);
        break;
    case SELECTRECTOUTBOTTOM:
        MoveFunPro(&m_rectEditOut,BOTTOMRIGHT,value,DIRX);
        break;
    case SELECTRECTXTOP:
        MoveFunPro(&m_rectEditX,TOPLEFT,value,DIRX);
        break;
    case SELECTRECTXBOTTOM:
        MoveFunPro(&m_rectEditX,BOTTOMRIGHT,value,DIRX);
        break;
    case SELECTRECTYTOP:
        MoveFunPro(&m_rectEditY,TOPLEFT,value,DIRX);
        break;
    case SELECTRECTYBOTTOM:
        MoveFunPro(&m_rectEditY,BOTTOMRIGHT,value,DIRX);
        break;
    default:
        break;
    }
}

/**
 * @brief FWMatchBoundaryLabel::MoveFunPro
 * @param rect 当前编辑的矩形框
 * @param Point 当前矩形框的点 0:左上点, 1:y右下点
 * @param value 移动的像素值
 * @param dir 移动的方向 0:x轴方向, 1:y轴方向
 */
void FWMatchBoundaryLabel::MoveFunPro(QRect *rect,int point,int value,int dir)
{
    if(dir == 0)//X方向左右移动
    {
        if(point == 0)//左上点
        {
            if(rect->topLeft().x()+value < STARTX || rect->topLeft().x()+value > rect->bottomRight().x() - 40)
            {
                return;
            }
            rect->setTopLeft(QPoint(rect->topLeft().x()+value,rect->topLeft().y()));
            update();
            signalPointsChange(rect->topLeft(),iSelectKind);
        }else//右下点
        {
            if(rect->bottomRight().x()+value < rect->topLeft().x() || rect->bottomRight().x()+value > ENDX)
            {
                return;
            }
            rect->setBottomRight(QPoint(rect->bottomRight().x()+value,rect->bottomRight().y()));
            update();
            signalPointsChange(rect->bottomRight(),iSelectKind);
        }
    }else//Y方向上下移动
    {
        if(point == 0)//左上点
        {
            if(rect->topLeft().y()+value < STARTY || rect->topLeft().y()+value > rect->bottomRight().y() - 40)
            {
                return;
            }
            rect->setTopLeft(QPoint(rect->topLeft().x(),rect->topLeft().y()+value));
            update();
            signalPointsChange(rect->topLeft(),iSelectKind);
        }else//右下点
        {
            if(rect->bottomRight().y()+value < rect->topLeft().y()+40 || rect->bottomRight().y()+value > ENDY)
            {
                return;
            }
            rect->setBottomRight(QPoint(rect->bottomRight().x(),rect->bottomRight().y()+value));
            update();
            signalPointsChange(rect->bottomRight(),iSelectKind);
        }
    }
}
