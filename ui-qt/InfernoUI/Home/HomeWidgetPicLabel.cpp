#include "HomeWidgetPicLabel.h"
#include <QPen>
#include <stdio.h>
#include <math.h>
#include <qdebug.h>
#include "Comm/OSDStyle.h"
#include "Comm/GlobalParameter.h"
#include "BusinessData/InterfaceLib/UIToolLibFun.h"

HomeWidgetPicLabel::HomeWidgetPicLabel(QWidget *parent) : QLabel(parent)
{
    m_paint = 0;
    count =0;
}
HomeWidgetPicLabel::~HomeWidgetPicLabel()
{

}
void HomeWidgetPicLabel::paintEvent(QPaintEvent *e)
{
    QLabel::paintEvent(e);
    QPainter painterPic(this);
    if(m_paint == 1)
    {
        //painterPic.drawPixmap(0, 0, m_pix);
        int iCount = m_vt_lib.count();
        OSDStyle::InitPenStyle();
        for (int i = 0; i<iCount;i++)
        {
            if(OSDStyle::vt_task_enable[i] == 1)
            {
                int state = GlobalParameter::m_area_select_state.value(i+1);
                UIToolLibFun * libFun = (UIToolLibFun * )m_vt_lib[i];
                libFun->Paint(&painterPic,i+1,OSDStyle::GetPenStyleAddr(),state);
            }
        }
        //count++;
        //painterPic.drawText(320,240,QString::number(count));

    }else
    {
        painterPic.drawPoint(-3,-3);
    }
}
void HomeWidgetPicLabel::mousePressEvent(QMouseEvent *ev)
{
    QLabel::mousePressEvent(ev);
}
void HomeWidgetPicLabel::mouseMoveEvent(QMouseEvent *ev)
{
    QLabel::mouseMoveEvent(ev);
}
void HomeWidgetPicLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    QLabel::mouseReleaseEvent(ev);
}

void HomeWidgetPicLabel::Update()
{
    repaint();
}
void HomeWidgetPicLabel::SetPixMap(QPixmap pix)
{
    m_paint = 1;
    this->m_pix = pix;
    repaint();
}
void HomeWidgetPicLabel::ListOSD()
{
    m_paint = 1;
    repaint();
}
void HomeWidgetPicLabel::ClearOSD()
{
    m_paint = 0;
    count = 0;
    repaint();
}
void HomeWidgetPicLabel::SetLibVt(QVector<BaseLibInterface *>vt)
{
    this->m_vt_lib = vt;
}
