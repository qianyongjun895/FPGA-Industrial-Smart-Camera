/**
  * @file  [UIBasicDefine.h]
  * @brief
  * @author  <szj>
  * @date  <2017/05/09>
  * @version  <1.0>
  * @note
  * detailed  description
  */
#ifndef UIBASICDEFINE_H
#define UIBASICDEFINE_H

#define VGA_WIDTH 640
#define VGA_HEIGHT 480
#include <QPoint>
#include <QString>
#include <QColor>
#include <QVector>
#include <QPen>

#define LIST_NG_ROI  1
#define LIST_OK_ROI  2
#define LIST_NG_OK_ROI 3
#define HIDE_NG_OK_ROI 4

typedef struct
{
    int r;
    QPoint center;
}STRU_CIRCLE;

typedef struct
{
    QString strName; //结果名称
    QString strValue; //结果值
}STRU_KEY_VALUE;

typedef enum
{
    COLOR_RED_TYPE = 0,      /* 红 */
    COLOR_ORANGE_TYPE,       /* 橙 */
    COLOR_YELLOW_TYPE,       /* 黄 */
    COLOR_GREEN_TYPE,        /* 绿 */
    COLOR_BLUE_TYPE,         /* 蓝 */
    COLOR_CYAN_TYPE,         /* 靛 */
    COLOR_PURPLE_TYPE,       /* 紫 */
    COLOR_WHILTE_TYPE,       /* 白 */
    COLOR_BLACK_TYPE,        /* 黑 */
    COLOR_GRAY_TYPE,         /* 灰 */
}COLOR_SELECT;

typedef struct
{
    COLOR_SELECT runOK_color;
    int runOKWidth;
    COLOR_SELECT runNG_color;
    int runNGWidth;
}RUN_OSD_PARA;

typedef struct
{
    COLOR_SELECT task_osd_edit_color;
    int task_osd_edit_width;

    COLOR_SELECT task_osd_select_color;
    int task_osd_select_width;

    COLOR_SELECT task_osd_Calc_color;
    int task_osd_Calc__width;

    COLOR_SELECT task_osd_edgePoint_color;
    int task_osd_edgePoint_width;

    COLOR_SELECT task_osd_AreaSelect_color;
    int task_osd_AreaSelect_width;

    COLOR_SELECT task_osd_ImageBorder_color;
    int task_osd_ImageBorder_width;
}TASK_OSD_PARA;

typedef struct
{
    RUN_OSD_PARA run_osd;
    TASK_OSD_PARA task_osd;
    QVector<QColor>m_vt_color;
}PEN_COLOR;

typedef struct
{
    QPen pen_ok_solidLine;
    QPen pen_ok_dashLine;
    QPen pen_ng_solidLine;
    QPen pen_ng_dashLine;

}PEN_STYLE_RUN;
#endif // UIBASICDEFINE_H
