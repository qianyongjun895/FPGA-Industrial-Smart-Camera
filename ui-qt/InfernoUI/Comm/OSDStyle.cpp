#include "OSDStyle.h"

PEN_COLOR OSDStyle::pen_color;
QVector<unsigned char> OSDStyle::vt_task_enable;
PEN_STYLE_RUN OSDStyle::pen_style;
OSDStyle::OSDStyle(QObject *parent) : QObject(parent)
{

}
void OSDStyle::iniColorPen()
{

    if(pen_color.m_vt_color.count() == 0)
    {
        QColor colorRed(255,0,0);       //红
        QColor colorOrange(255,125,0);  //橙
        QColor colorYellow(255,255,0);  //黄
        QColor colorGreen(0,255,0);     //绿
        QColor colorBlue(0,0,255);      //蓝
        QColor colorCyan(0,255,255);    //靛
        QColor colorPurple(255,0,255);  //紫
        QColor colorWhilte(255,255,255); //白
        QColor colorBlack(0,0,0);       //黑
        QColor colorGray(192,192,192);  //灰

        pen_color.m_vt_color.append(colorRed);
        pen_color.m_vt_color.append(colorOrange);
        pen_color.m_vt_color.append(colorYellow);
        pen_color.m_vt_color.append(colorGreen);
        pen_color.m_vt_color.append(colorBlue);
        pen_color.m_vt_color.append(colorCyan);
        pen_color.m_vt_color.append(colorPurple);
        pen_color.m_vt_color.append(colorWhilte);
        pen_color.m_vt_color.append(colorBlack);
        pen_color.m_vt_color.append(colorGray);
    }
}
void OSDStyle::InitOSDConfig(int step)
{
    iniColorPen();
    //获取图像边界OSD颜色
    pen_color.task_osd.task_osd_ImageBorder_color = COLOR_RED_TYPE;
    //获取图像边界OSD粗细
    pen_color.task_osd.task_osd_ImageBorder_width= 1;
    //获取参数编辑界面OSD颜色
    pen_color.task_osd.task_osd_edit_color = COLOR_BLUE_TYPE;
    //获取参数编辑界面OSD粗细
    pen_color.task_osd.task_osd_edit_width = 1;
    //获取选中OSD颜色
    pen_color.task_osd.task_osd_select_color = COLOR_GREEN_TYPE;
    //获取选中OSD粗细
    pen_color.task_osd.task_osd_select_width = 1;
    //获取计算/取样OSD颜色
    pen_color.task_osd.task_osd_Calc_color = COLOR_GREEN_TYPE;
    //获取计算/取样OSD粗细
    pen_color.task_osd.task_osd_Calc__width = 1;
    //获取边沿点OSD颜色
    pen_color.task_osd.task_osd_edgePoint_color = COLOR_RED_TYPE;
    //获取边沿点OSD粗细
    pen_color.task_osd.task_osd_edgePoint_width = 1;
    //获取区域筛选OSD颜色
    pen_color.task_osd.task_osd_AreaSelect_color = COLOR_BLUE_TYPE;
    //获取区域筛选OSD粗细
    pen_color.task_osd.task_osd_AreaSelect_width = 1;

    pen_color.run_osd.runNGWidth = 1;
    pen_color.run_osd.runNG_color = COLOR_RED_TYPE;

    pen_color.run_osd.runOKWidth = 1;
    pen_color.run_osd.runOK_color = COLOR_GREEN_TYPE;
}
void *OSDStyle::GetPenColor()
{
    PEN_COLOR *pen = &pen_color;
    return (void *)pen;
}
void *OSDStyle::GetPenStyleAddr()
{
    PEN_STYLE_RUN *pen = &pen_style;
    return (void *)pen;
}
void OSDStyle::InitPenStyle()
{
    pen_style.pen_ok_solidLine.setColor(pen_color.m_vt_color[pen_color.run_osd.runOK_color]);
    pen_style.pen_ok_solidLine.setWidth(pen_color.run_osd.runOKWidth);
    pen_style.pen_ok_solidLine.setStyle(Qt::SolidLine);

    pen_style.pen_ok_dashLine.setColor(pen_color.m_vt_color[pen_color.run_osd.runOK_color]);
    pen_style.pen_ok_dashLine.setWidth(pen_color.run_osd.runOKWidth);
    pen_style.pen_ok_dashLine.setStyle(Qt::DashLine);

    pen_style.pen_ng_solidLine.setColor(pen_color.m_vt_color[pen_color.run_osd.runNG_color]);
    pen_style.pen_ng_solidLine.setWidth(pen_color.run_osd.runNGWidth);
    pen_style.pen_ng_solidLine.setStyle(Qt::SolidLine);

    pen_style.pen_ng_dashLine.setColor(pen_color.m_vt_color[pen_color.run_osd.runNG_color]);
    pen_style.pen_ng_dashLine.setWidth(pen_color.run_osd.runNGWidth);
    pen_style.pen_ng_dashLine.setStyle(Qt::DashLine);
}
