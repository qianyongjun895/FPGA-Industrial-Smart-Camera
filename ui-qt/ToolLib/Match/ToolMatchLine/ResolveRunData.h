#ifndef RESOLVERUNDATA_H
#define RESOLVERUNDATA_H

#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QLabel>
#include <QVector>
#include "../../BasicDefine.h"
#include "LineGlobal.h"
#include "TaskStepGlobal.h"
#include "TaskRstGlobal.h"
#include "../BaseStruct.h"
#define VGA_WIDTH 640
#define VGA_HEIGHT 480

class ResolveRunData
{
public:
    explicit ResolveRunData();
    ~ResolveRunData();
    void Paint(QPainter *paint,int step,void *penStyle,int paintAreaSelect);
    QVector<STRU_KEY_VALUE> GetHead(int step);
    QVector<STRU_KEY_VALUE> GetContent(int step, int index, int *count);

private:
    LINE_OUTPUT_PARAM *pRunPara;
    int m_line_cnt;
    int m_ok_ng_flag;       ///< ok/ng标志
    LineParameter m_line_para[20];
    QLine m_line[20];
    int m_ok_cnt;
    int m_ng_cnt;
    int m_excute_flag;

    int Line_Paint_Base_On_KB_SubPixel(float k_f, float b_f, QLine *pOsd_line);
    int Line_Osd_Init(LineParameter *pLinePara, QLine *pOsdLine);

    void GetPreData(QPainter *paint, int iStep, int iSwitch);
    void GetRoiData(QPainter *paint, SELECT_AREA_PARAM del_model);
    void DrawPolygon(QPainter *paint, OCTAGON_CFG_PARA points);
    void DrawRing(QPainter *paint, CIRCULAR ring);
};

#endif // RESOLVERUNDATA_H
