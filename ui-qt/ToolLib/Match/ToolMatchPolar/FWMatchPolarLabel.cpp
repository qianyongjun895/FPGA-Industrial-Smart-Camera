#include "FWMatchPolarLabel.h"
#include "BasicDefine.h"
#define SIN67_5 0.923879
#define COS67_5 0.382683
#define MAXR 240
FWMatchPolarLabel::FWMatchPolarLabel(QWidget *parent) : QLabel(parent)
{
    radius = 30;
    center = QPoint(0,0);
    angle[0] = M_PI/6;
    angle[1] = M_PI/3;
    angle[2] = 0;
    angle[3] = M_PI/2;
    Global = 1;
    radiusMax = 100;
    radiusMin =40;
    m_center.setX(-300);
    m_center.setY(-300);
}

void FWMatchPolarLabel::setRadius(int r)
{
    this->radius = r;
    update();
}

void FWMatchPolarLabel::setRadiusMin(int r)
{
    radiusMin = r;
    signalRadiuChange(radiusMin,1);//内圆
    update();

}

void FWMatchPolarLabel::setRadiusMax(int r)
{
    radiusMax = r;
    signalRadiuChange(radiusMax,2);//外圆
    update();
}

void FWMatchPolarLabel::AddRadiuMin(int value)
{
    if(radiusMin < radiusMax -20)
        radiusMin += value;
    update();
    signalRadiuChange(radiusMin,1);
}
void FWMatchPolarLabel::SubRadiuMin(int value)
{
    if(radiusMin > 20 + value)
        radiusMin -= value;
    update();
    signalRadiuChange(radiusMin,1);
}
void FWMatchPolarLabel::AddRadiuMax(int value)
{
    if(radiusMax < 240 - value )
    {
        radiusMax += value;
    }
    update();
    signalRadiuChange(radiusMax,2);
}
void FWMatchPolarLabel::SubRadiuMax(int value)
{
    if(radiusMax > radiusMin + 20)
        radiusMax -= value;
    update();
    signalRadiuChange(radiusMax,2);
}

void FWMatchPolarLabel::setSearchMode(int b)
{
    this->Global = b;
    update();
}

int FWMatchPolarLabel::getRadius()
{
    return this->radius;
}

int FWMatchPolarLabel::getRadiusMin()
{
    return this->radiusMin;
}

int FWMatchPolarLabel::getRadiusMax()
{
    return this->radiusMax;
}

float FWMatchPolarLabel::getLearnStartAngle()
{
    return this->angle[0]*180/M_PI;
}

float FWMatchPolarLabel::getLearnEndAngle()
{
    return this->angle[1]*180/M_PI;
}

float FWMatchPolarLabel::getSearchStartAngle()
{
    return this->angle[2]*180/M_PI;
}

float FWMatchPolarLabel::getSearchEndAngle()
{
    return this->angle[3]*180/M_PI;
}

void FWMatchPolarLabel::setLearnStartAngle(float a)
{
    selectRect = 1;
    angle[0] = a*M_PI/180;
    signalPointsChange(angle[selectRect-1],selectRect);//
    update();
}

void FWMatchPolarLabel::setLearnEndAngle(float a)
{
    selectRect = 2;
    angle[1] = a*M_PI/180;
    signalPointsChange(angle[selectRect-1],selectRect);//
    update();
}

void FWMatchPolarLabel::setSearchStartAngle(float a)
{
    selectRect = 3;
    angle[2] = a*M_PI/180;
    signalPointsChange(angle[selectRect-1],selectRect);//
    update();
}

void FWMatchPolarLabel::setSearchEndAngle(float a)
{
    selectRect = 4;
    angle[3] = a*M_PI/180;
    signalPointsChange(angle[selectRect-1],selectRect);//
    update();
}
FWMatchPolarLabel::~FWMatchPolarLabel()
{

}
void FWMatchPolarLabel::paintEvent(QPaintEvent *e)
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
    painter.drawEllipse(m_center,radiusMax,radiusMax);
    painter.drawEllipse(m_center,radiusMin,radiusMin);

    PointA1 = QPoint((radiusMax+15)*cos(angle[0])+m_center.x(),(radiusMax+15)*sin(angle[0])+m_center.y());
    PointA2 = QPoint((radiusMax+15)*cos(angle[1])+m_center.x(),(radiusMax+15)*sin(angle[1])+m_center.y());
    PointB1 = QPoint((radiusMax+15)*cos(angle[2])+m_center.x(),(radiusMax+15)*sin(angle[2])+m_center.y());
    PointB2 = QPoint((radiusMax+15)*cos(angle[3])+m_center.x(),(radiusMax+15)*sin(angle[3])+m_center.y());

    ClickRect[0] = QRectF(PointA1-ClickArea,PointA1+ClickArea);
    ClickRect[1] = QRectF(PointA2-ClickArea,PointA2+ClickArea);
    ClickRect[2] = QRectF(PointB1-ClickArea,PointB1+ClickArea);
    ClickRect[3] = QRectF(PointB2-ClickArea,PointB2+ClickArea);
    center = m_center;
    //采样范围起始线
    painter.drawLine(center,PointA1);
    painter.drawRect(ClickRect[0]);
    painter.drawText((PointA1.x()+m_center.x())/2,(PointA1.y()+m_center.y())/2, QString::number(angle[0]*180/M_PI)+"°");
    if(PointA1.x() > m_center.x())
        painter.drawText(PointA1+ClickArea,"A1");
    else
        painter.drawText(PointA1-ClickArea,"A1");
    if(PointA2.x() > m_center.x())
        painter.drawText(PointA2+ClickArea,"A2");
    else
        painter.drawText(PointA2-ClickArea,"A2");

    //采样范围终止线
    painter.drawLine(center,PointA2);
    painter.drawRect(ClickRect[1]);
    painter.drawText((PointA2.x()+m_center.x())/2,(PointA2.y()+m_center.y())/2, QString::number(angle[1]*180/M_PI)+"°");
    //搜索范围起始线
    if(Global !=1)
    {
        pen.setColor(Qt::blue);
        pen.setWidth(2);
        painter.setPen(pen);

        if(PointB1.x() > m_center.x())
            painter.drawText(PointB1+ClickArea,"B1");
        else
            painter.drawText(PointB1-ClickArea,"B1");
        if(PointB2.x() > m_center.x())
            painter.drawText(PointB2+ClickArea,"B2");
        else
            painter.drawText(PointB2-ClickArea,"B2");
        pen.setStyle(Qt::DashLine);
        painter.setPen(pen);

        painter.drawLine(center,PointB1);
        painter.drawRect(ClickRect[2]);
        painter.drawText((PointB1.x()+m_center.x())/2,(PointB1.y()+m_center.y())/2, QString::number(angle[2]*180/M_PI)+"°");

        //搜索范围终止线
        painter.drawLine(center,PointB2);
        painter.drawRect(ClickRect[3]);
        painter.drawText((PointB2.x()+m_center.x())/2,(PointB2.y()+m_center.y())/2, QString::number(angle[3]*180/M_PI)+"°");
        //画圆弧
        int spanAngle;
        int startAngle;
        if(angle[2]*180/M_PI > angle[3]*180/M_PI)
        {
            startAngle = (360-angle[3]*180/M_PI) * 16;
            spanAngle = (360-angle[2]*180/M_PI+angle[3]*180/M_PI) * 16;
        }
        else
        {
            startAngle = (360-angle[3]*180/M_PI) * 16;
            spanAngle = (angle[3]*180/M_PI-angle[2]*180/M_PI) * 16;
        }
        //painter.drawArc(QRectF(-radiusMax - 3, -radiusMax - 3,radiusMax*2 + 8, radiusMax*2 + 8),startAngle,spanAngle);
        painter.drawArc(m_center.x()-radiusMax - 4,m_center.y()-radiusMax - 4,2*radiusMax+8,2*radiusMax+8,startAngle,spanAngle);
    }

}

void FWMatchPolarLabel::mousePressEvent(QMouseEvent *ev)
{
    QPointF pos = ev->pos();
    selectRect = -1;
    for (int i = 0; i < 4; i++){
        //QRectF rect = ClickRect[i];
        QRectF rect;
        rect.setTopLeft(QPointF(ClickRect[i].topLeft().x()-15,ClickRect[i].topLeft().y()-15));
        rect.setBottomRight(QPointF(ClickRect[i].bottomRight().x()+15,ClickRect[i].bottomRight().y()+15));
        if (rect.contains(pos))
        {
            selectRect = i+1;
            return;
        }
    }
    update();
}

void FWMatchPolarLabel::mouseMoveEvent(QMouseEvent *ev)
{
    QPointF disTemp = ev->pos();
    QPointF dis;
    dis.setX(disTemp.x()-m_center.x());
    dis.setY(disTemp.y()-m_center.y());
    if(dis.x() >= 0 && dis.y() < 0)
        angle[selectRect-1] = atan(dis.y()/dis.x())+2*M_PI;
    else if((dis.x() < 0 && dis.y() <= 0)||(dis.x() < 0 && dis.y() >= 0))
        angle[selectRect-1] = atan(dis.y()/dis.x())+M_PI;
    else
        angle[selectRect-1] = atan(dis.y()/dis.x());
    signalPointsChange(angle[selectRect-1],selectRect);//
    update();
}

void FWMatchPolarLabel::setCenterPoint(QPoint centerPoint)
{
    m_center.setX(centerPoint.x());
    m_center.setY(centerPoint.y());
}
void FWMatchPolarLabel::SetPenColor(void *pen_color)
{
    this->m_pen_color = pen_color;
}
