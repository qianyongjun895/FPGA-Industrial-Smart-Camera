#include <QDebug>
#include "FWMatchBlobLabel.h"
#include "math.h"
#include "BasicDefine.h"

FWMatchBlobLabel::FWMatchBlobLabel(QWidget *parent) : QLabel(parent)
{
//    m_data = NULL;
    m_pen_color = NULL;
}

FWMatchBlobLabel::~FWMatchBlobLabel()
{

}

/**
 * @brief FWMatchBlobLabel::SetOSDData
 * @param data
 * @author dgq
 * @note 设置blob取样/计算后的参数
 */
void FWMatchBlobLabel::SetOSDData(BLOB_OSD_EDIT *data)
{
    m_data.m_angle = data->m_angle;
    m_data.m_blob_heigth = data->m_blob_heigth;
    m_data.m_blob_width = data->m_blob_width;
    m_data.m_vt_point = data->m_vt_point;
    update();
}

/**
 * @brief FWMatchBlobLabel::paintEvent
 * @param e
 * @author dgq
 * @date 2017/5/23
 * @note OSD绘制函数
 */
void FWMatchBlobLabel::paintEvent(QPaintEvent *e)
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

    int count = m_data.m_vt_point.count();
    float fLen =20.0;
    for(int i = 0; i<count;i++)
    {
        if(m_data.m_blob_heigth[i] > 40.0)
        {
          fLen = m_data.m_blob_heigth[i]*0.5;

        }
        else
          fLen = 20.0;
        QPoint lastPoint;
        if(m_data.m_vt_point[i].x() >= 0 && m_data.m_vt_point[i].x() <= 640 &&m_data.m_vt_point[i].y() >= 0 && m_data.m_vt_point[i].y() <= 480)
        {
            lastPoint.setX(m_data.m_vt_point[i].x());
            lastPoint.setY(m_data.m_vt_point[i].y());
            int x = (int)(m_data.m_vt_point[i].x() + fLen*cos(m_data.m_angle[i]));
            int y = (int)(m_data.m_vt_point[i].y() + fLen*sin(m_data.m_angle[i]));
            QPoint endPoint;
            endPoint.setX(x);
            endPoint.setY(y);
            DrawArrow(&painter,lastPoint,endPoint,10.0);
            painter.drawText(lastPoint,QString::number(i+1));
        }
    }
}

/**
 * @brief FWMatchBlobLabel::DrawArrow
 * @param painter
 * @param lastPoint 起点
 * @param endPoint 终点
 * @param iArrowLen 箭头的两条线长度
 * @author dgq
 * @date 2017/5/23
 * @note 画箭头
 */
void FWMatchBlobLabel::DrawArrow(QPainter *painter,QPoint lastPoint,QPoint endPoint,float iArrowLen)
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
void FWMatchBlobLabel::SetPenColor(void *pen_color)
{
    this->m_pen_color = pen_color;
}
