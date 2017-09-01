
#include "LabelMain.h"
#include <qdebug.h>
#include <QPen>
#include "AcceCommon.h"
#include "SideExtract.h"
#include <stdio.h>
#include "sszn_basic.h"
//#include "UIBasicDefine.h"
#include "BasicDefine.h"

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#define LINEWIDTH 30

LabelMain::LabelMain(QWidget *parent) : QLabel(parent)
{
    m_start_x = 0;
    m_start_y = 0;
    m_end_x = 640;
    m_end_y = 480;
    m_edge_ptr = NULL;
    m_skeletonMatch_ptr = NULL;
    m_scaleMode =2;
    m_pen_color = NULL;
}

void LabelMain::mousePressEvent(QMouseEvent *e)
{
    QLabel::mousePressEvent(e);
}

void LabelMain::mouseMoveEvent(QMouseEvent *e)
{
    QLabel::mouseMoveEvent(e);
}

void  LabelMain::mouseReleaseEvent(QMouseEvent *e)
{
    QLabel::mouseReleaseEvent(e);
}

void LabelMain::paintEvent(QPaintEvent *e)
{
    QLabel::paintEvent(e);
    QPainter painter(this);
    PEN_COLOR *pen_color = (PEN_COLOR*)m_pen_color;
    if(m_pen_color ==NULL)
        return;
    QPen pen;
    pen.setColor(pen_color->m_vt_color[pen_color->task_osd.task_osd_edgePoint_color]);
    pen.setWidth(pen_color->task_osd.task_osd_edgePoint_width);
    painter.setPen(pen);

    int count = m_vt.count();

    for(int i= 0;i < count;i++)
    {
        switch(m_vt[i])
        {
        case ACCE_EDGE_EXTRACT_MODLE_ID:
            paintEdgePoint(&painter);
            break;
        case ACCE_SKE_MATCH_MODLE_ID:
            paintSkeletonMatch(&painter);
            break;
        default:
            break;
        }
    }

    pen.setColor(pen_color->m_vt_color[pen_color->task_osd.task_osd_ImageBorder_color]);
    pen.setWidth(pen_color->task_osd.task_osd_ImageBorder_width);
    pen.setStyle(Qt::DashDotLine);
    painter.setPen(pen);
    painter.drawLine(0,m_start_y,640,m_start_y);
    painter.drawLine(0,m_end_y,640,m_end_y);
    painter.drawLine(m_start_x,0,m_start_x,480);
    painter.drawLine(m_end_x,0,m_end_x,480);
}
void LabelMain::paintEdgePoint(QPainter *painter)
{
    if(m_edge_ptr !=NULL)
    {
        FPGA_EDGE_CALC_POINT *edgetPtr = ((FPGA_EDGE_CALC_POINT*)m_edge_ptr);
        int x;
        int y;
        int num = 0;
        int j = 0;
        num = GET_SIDE_SEL_POINT_NUM();

        for(int i= 0; i<num;i++)
        {
            x = edgetPtr[i].x/m_scaleMode;
            y = edgetPtr[i].y/m_scaleMode;
            painter->drawPoint(x,y);
        }
        /*if(GetDebugFlag() & 0x800)
        {
            if (j) {
                printf("\n");
            }
        }*/
    }
}

void LabelMain::paintSkeletonMatch(QPainter *painter)
{
    if(m_edge_ptr !=NULL)
    {
        FPGA_EDGE_CALC_POINT *skeletonMatchPtr = ((FPGA_EDGE_CALC_POINT*)m_skeletonMatch_ptr);
        int x;
        int y;
        int num = 0;

        for(int i= 0; i<num;i++)
        {
            x = skeletonMatchPtr[i].x/m_scaleMode;
            y = skeletonMatchPtr[i].y/m_scaleMode;
            painter->drawPoint(x,y);

        }
    }
}
void LabelMain::Set_startX(int x)
{
    this->m_start_x = x;
    update();
}
void LabelMain::Set_endX(int x)
{
    this->m_end_x = x;
    update();
}
void LabelMain::Set_startY(int y)
{
    this->m_start_y = y;
    update();
}
void LabelMain::Set_endY(int y)
{
    this->m_end_y = y;
}
void LabelMain::paintPointSlot(QVector<int>vt)
{
    m_vt = vt;
    update();
}
void LabelMain::SetEdgePtr(void *ptr)
{
    this->m_edge_ptr = ptr;
}
void LabelMain::SetSkeletonMatchPtr(void *ptr)
{
    this->m_skeletonMatch_ptr = ptr;
}
void LabelMain::SetHWCVga2Sub(int mode)
{
    m_scaleMode = mode;
}
void LabelMain::SetPenColor(void *pen)
{
    this->m_pen_color = pen;
    update();
}
