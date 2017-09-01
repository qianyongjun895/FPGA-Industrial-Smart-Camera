#include "MultipointDemarcateImageLabel.h"

MultipointDemarcateImageLabel::MultipointDemarcateImageLabel(QWidget *parent) :QLabel(parent)
{
    m_points.append(QPoint(160, 120));
    m_points.append(QPoint(480, 120));
    m_points.append(QPoint(160, 360));
    m_points.append(QPoint(480, 360));
    cur_point_index = 0;
    cur_ccc_index = 0;
    point_selected = 0;
    point_move_flag = false;
    draw_line_flag = false;
    m_paint_content = 0;
}


MultipointDemarcateImageLabel::~MultipointDemarcateImageLabel()
{

}


void MultipointDemarcateImageLabel::show(QPen &pen, QPainter &painter)
{
    QPen penBak;
    pen.setWidth(1);
    pen.setColor(Qt::green);
    painter.setPen(pen);
    int set_pen_flag = 0;

    for (int i = 0; i < m_points.count(); ++ i)
    {
        if (cur_point_index == i)
        {
            set_pen_flag = 1;
            penBak = pen;
            pen.setColor(Qt::red);
            painter.setPen(pen);
        }

        DrawDemarcatePoint(painter,m_points[i],i);

        if (draw_line_flag)
        {
            DrawBaseLine(painter,m_base_line);
            draw_line_flag = false;
        }

        if (set_pen_flag == 1)
        {
            pen = penBak;
            painter.setPen(pen);
            set_pen_flag = 0;
        }
    }

    SendCurPoint(m_points[cur_point_index]);
}

void MultipointDemarcateImageLabel::DrawDemarcatePoint(QPainter &painter, QPoint &drawPoint, int &pIndex)
{
    int line_width = 15;
    int radius = 10;

    painter.drawEllipse(drawPoint, radius , radius);
    painter.drawLine(drawPoint.rx()-line_width,drawPoint.ry(),drawPoint.rx()+line_width,drawPoint.ry());
    painter.drawLine(drawPoint.rx(),drawPoint.ry()-line_width,drawPoint.rx(),drawPoint.ry()+line_width);
    painter.drawText(drawPoint.rx()+line_width+5,drawPoint.ry()+5,QString::number(pIndex+1));
}

void MultipointDemarcateImageLabel::DrawBaseLine(QPainter &painter, QLine &rLine)
{
    painter.drawLine(rLine);
}

void MultipointDemarcateImageLabel::ShowPointsAxisR(QPen &pen, QPainter &painter)
{
    QPen penBak;
    pen.setWidth(1);
    pen.setColor(Qt::green);
    painter.setPen(pen);
    int set_pen_flag = 0;

    for (int i = 0; i < m_ccc_points.count(); ++ i)
    {
        if (cur_ccc_index == i)
        {
            set_pen_flag = 1;
            penBak = pen;
            pen.setColor(Qt::red);
            painter.setPen(pen);
        }

        DrawDemarcatePoint(painter,m_ccc_points[i],i);

        if (set_pen_flag == 1)
        {
            pen = penBak;
            painter.setPen(pen);
            set_pen_flag = 0;
        }
    }
}


void MultipointDemarcateImageLabel::paintEvent(QPaintEvent *e)
{
    QLabel::paintEvent(e);
    QPainter painter(this);

    QPen pen;
    painter.setRenderHint(QPainter::Antialiasing);

    if (m_paint_content == 0)
    {
        show(pen, painter);
    }
    else if (m_paint_content == 1)
    {
        ShowPointsAxisR(pen, painter);
    }
}

void MultipointDemarcateImageLabel::mousePressEvent(QMouseEvent *ev)
{
    if (!point_move_flag)
    {
        return ;
    }
    int x = ev->pos().x();
    int y = ev->pos().y();
    for (int i = 0; i < m_points.count(); ++ i)
    {
        if(((x-m_points[i].rx())*(x-m_points[i].rx())+(y-m_points[i].ry())*(y-m_points[i].ry())) <= 20*20)
        {
            cur_point_index = i;
            CurPointIndexChanged(i+1);
            point_selected = 1;
            update();
            break;
        }
    }

    m_press_point = ev->pos();
}

void MultipointDemarcateImageLabel::mouseMoveEvent(QMouseEvent *ev)
{
    if (!point_move_flag)
    {
        return ;
    }
    QPoint pos = ev->pos();

    if (point_selected == 1)
    {
        int disX = pos.x() - m_press_point.x();
        int disY = pos.y() - m_press_point.y();
        int ix,iy;

        ix = m_points[cur_point_index].x() + disX;
        iy = m_points[cur_point_index].y() + disY;

        if(ix >= 0 && ix <= 640 && iy >= 0 && iy <= 480)
        {
            m_points[cur_point_index].setX(m_points[cur_point_index].x() + disX);
            m_points[cur_point_index].setY(m_points[cur_point_index].y() + disY);
            update();
        }
    }

    m_press_point = ev->pos();
}

void MultipointDemarcateImageLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    if (!point_move_flag)
    {
        return ;
    }
    if (point_selected == 1)
    {
        point_selected = 0;
        UpdateCoordinateTable();
    }
}

void MultipointDemarcateImageLabel::PrevPonitSelected()
{
    if (cur_point_index > 0)
    {
        -- cur_point_index;
        update();
    }
}

void MultipointDemarcateImageLabel::NextPointSelected()
{
    if (cur_point_index < m_points.count() - 1)
    {
        ++ cur_point_index;
        update();
    }
}

void MultipointDemarcateImageLabel::AddPoint()
{
    int pCnt = m_points.count();
    if (pCnt >= 9)
    {
        return ;
    }

    m_points.append(QPoint(320,240));
    pCnt = m_points.count();
    if (pCnt > 0)
    {
        cur_point_index = pCnt - 1;
    }
    UpdateCoordinateTable();
    update();
}

void MultipointDemarcateImageLabel::AddPoint(int x, int y)
{
    int pCnt = m_points.count();
    if (pCnt >= 9)
    {
        return ;
    }

    m_points.append(QPoint(x,y));
    pCnt = m_points.count();
    if (pCnt > 0)
    {
        cur_point_index = pCnt - 1;
    }
    UpdateCoordinateTable();
    update();
}

void MultipointDemarcateImageLabel::AddPointAxisR(int x, int y)
{
    int pCnt = m_ccc_points.count();
    if (pCnt >= 3)
    {
        return ;
    }

    m_ccc_points.append(QPoint(x,y));
    pCnt = m_ccc_points.count();
    if (pCnt > 0)
    {
        cur_ccc_index = pCnt - 1;
    }
    update();
}

void MultipointDemarcateImageLabel::DelPoint()
{
    int pCnt = m_points.count();
    if (pCnt <= 4)
    {
        return ;
    }

    m_points.pop_back();
    pCnt = m_points.count();
    if (pCnt > 0)
    {
        cur_point_index = pCnt - 1;
    }
    UpdateCoordinateTable();
    update();
}

void MultipointDemarcateImageLabel::DeleteLastOnePoint()
{
    int pCnt = m_points.count();
    if (pCnt <= 0)
    {
        return ;
    }

    m_points.pop_back();
    pCnt = m_points.count();
    if (pCnt > 0)
    {
        cur_point_index = pCnt - 1;
    }
    UpdateCoordinateTable();
    update();
}

void MultipointDemarcateImageLabel::DeleteLastOnePointAxisR()
{
    int pCnt = m_ccc_points.count();
    if (pCnt <= 0)
    {
        return ;
    }

    m_ccc_points.pop_back();
    pCnt = m_ccc_points.count();
    if (pCnt > 0)
    {
        cur_ccc_index = pCnt - 1;
    }
    update();
}

void MultipointDemarcateImageLabel::ClearAllPoints()
{
    m_points.clear();
    UpdateCoordinateTable();
    update();
}

void MultipointDemarcateImageLabel::ClearAllPointsAxisR()
{
    m_ccc_points.clear();
    update();
}

int MultipointDemarcateImageLabel::GetPointNum()
{
    return m_points.count();
}

int MultipointDemarcateImageLabel::GetCurPointIndex()
{
    return cur_point_index + 1;
}

int MultipointDemarcateImageLabel::GetCurPointIndexAxisR()
{
    return cur_ccc_index + 1;
}

void MultipointDemarcateImageLabel::CurPointMoveUp(int value)
{
    m_points[cur_point_index].ry() -= value;

    if (m_points[cur_point_index].ry() < 0)
    {
        m_points[cur_point_index].ry() = 0;
    }

    update();
}

void MultipointDemarcateImageLabel::CurPointMoveDown(int value)
{
    m_points[cur_point_index].ry() += value;

    if (m_points[cur_point_index].ry() > 480)
    {
        m_points[cur_point_index].ry() = 480;
    }

    update();
}

void MultipointDemarcateImageLabel::CurPointMoveLeft(int value)
{
    m_points[cur_point_index].rx() -= value;

    if (m_points[cur_point_index].rx() < 0)
    {
        m_points[cur_point_index].rx() = 0;
    }

    update();
}

void MultipointDemarcateImageLabel::CurPointMoveRight(int value)
{
    m_points[cur_point_index].rx() += value;

    if (m_points[cur_point_index].rx() > 640)
    {
        m_points[cur_point_index].rx() = 640;
    }

    update();
}

void MultipointDemarcateImageLabel::SetPointMoveFlag(bool flag)
{
    point_move_flag = flag;
}

void MultipointDemarcateImageLabel::SetBaseLine(QLine qLine)
{
    m_base_line = qLine;
    draw_line_flag = true;

    update();
}

void MultipointDemarcateImageLabel::SetOsdPaintContent(unsigned int content)
{
    m_paint_content = content;
    update();
}

