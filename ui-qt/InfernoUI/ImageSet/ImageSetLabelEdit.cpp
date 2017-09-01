#include "ImageSetLabelEdit.h"


ImageSetLabelEdit::ImageSetLabelEdit(QWidget *parent) : QLabel(parent)
{
    m_y1 = 10;
    m_y2 = 160;
    m_list_adjust_line =1;
}
void ImageSetLabelEdit::UpAdjustLine(KEYKIND kind, int value)
{
    if(kind == UPLINE)
    {
        if(this->m_y1 > 0)
            this->m_y1 -= value;
        if(this->m_y1 < 0)
            this->m_y1 = 0;
        update();
        signaleValue(1);

    }else if(kind == DOWNLIN)
    {
        if(this->m_y2 > this->m_y1+DISTANCE)
            this->m_y2 -=value;
        update();
        signaleValue(1);
    }
}
void ImageSetLabelEdit::DownAdjustmentLine(KEYKIND kind, int value)
{
    if(kind == UPLINE)
    {
        if(this->m_y2 > this->m_y1+DISTANCE)
            this->m_y1 +=value;
        update();
        signaleValue(1);

    }else if(kind == DOWNLIN)
    {
        if(this->m_y2 < 480)
            this->m_y2 +=value;

        if(this->m_y2 > 480)
            this->m_y2 = 480;

        update();
        signaleValue(1);
    }
}
void ImageSetLabelEdit::paintEvent(QPaintEvent *e)
{
    QLabel::paintEvent(e);
    QPainter painter(this);
    QPen pen;
    pen.setColor(Qt::red);
    pen.setWidth(1);
    painter.setPen(pen);

    if(m_list_adjust_line ==1)
    {
        painter.drawLine(0,m_y1,640,m_y1);
        painter.drawLine(0,m_y2,640,m_y2);

        painter.drawLine(640,m_y1,630,m_y1-15);
        painter.drawLine(620,m_y1,630,m_y1-15);
        painter.drawLine(640,m_y1,630,m_y1+15);
        painter.drawLine(620,m_y1,630,m_y1+15);

        painter.drawLine(640,m_y2,630,m_y2-15);
        painter.drawLine(620,m_y2,630,m_y2-15);
        painter.drawLine(640,m_y2,630,m_y2+15);
        painter.drawLine(620,m_y2,630,m_y2+15);
    }

}
void ImageSetLabelEdit::mousePressEvent(QMouseEvent *ev)
{
    int x = ev->pos().x();
    int y = ev->pos().y();
    iSelectKind = 0;

    if(m_list_adjust_line ==1)
    {
        if(y > this->m_y1-20 && y < this->m_y1 + 20)
            iSelectKind = 1;
        else if(y > this->m_y2 - 20 && y<this->m_y2 + 20)
            iSelectKind = 2;
    }

    if(iSelectKind !=0)
    {
        update();
        return;
    }

}
void ImageSetLabelEdit::mouseMoveEvent(QMouseEvent *ev)
{
    int x = ev->pos().x();
    int y = ev->pos().y();

    if(iSelectKind == 1)
    {
        if(y < 0)
        {
            this->m_y1 = 0;

        }else if(y>= this->m_y2-DISTANCE)
        {
            this->m_y1 = m_y2-DISTANCE;
        }else
        {
            if(y %2 !=0)
                this->m_y1 = y-1;
            else
                this->m_y1 = y;
        }
        signaleValue(0);
        update();

    }else if(iSelectKind ==2)
    {
        if(y <= this->m_y1+DISTANCE)
            this->m_y2 = this->m_y1+DISTANCE;
        else if(y > 480)
            this->m_y2 = 480;
        else
        {
            if(y%2 !=0)
                this->m_y2 = y+1;
            else
                this->m_y2 = y;
        }
        signaleValue(0);
        update();
    }

}
void ImageSetLabelEdit::mouseReleaseEvent(QMouseEvent *ev)
{
    if(iSelectKind == 1 || iSelectKind == 2)
        signaleValue(1);

    QLabel::mouseReleaseEvent(ev);
}
void ImageSetLabelEdit::SetLine(int y1,int y2)
{
    m_y1 = y1;
    m_y2 = y2;
    update();
}
int ImageSetLabelEdit::GetLineHeigth()
{
    return this->m_y2 - this->m_y1;
}
void ImageSetLabelEdit::SetListAdjustLine(int flag)
{
    m_list_adjust_line = flag;
    update();
}
