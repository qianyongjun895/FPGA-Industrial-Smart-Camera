#ifndef RESOLVERUNDATA_H
#define RESOLVERUNDATA_H

#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QLabel>
#include <QVector>
#include "../../BasicDefine.h"
#include "BaseLineGlobal.h"
#include "TaskStepGlobal.h"
#include "TaskRstGlobal.h"

#define VGA_WIDTH 640
#define VGA_HEIGHT 480

class ResolveRunData
{

public:
    explicit ResolveRunData();
    ~ResolveRunData();
    void Paint(QPainter *paint, int step, void *penStyle, int paintAreaSelect);
    QVector<STRU_KEY_VALUE> GetHead(int step);
    QVector<STRU_KEY_VALUE> GetContent(int step, int index, int *count);

private:
    void *pRunPara;
    int m_line_cnt;//基准点总数
    LineParameter m_line_para[20];

    QLine m_line[20];

    int Line_Paint_Base_On_KB_SubPixel(float k_f, float b_f, QLine *pOsd_line);
    int Line_Osd_Init(LineParameter *pLinePara, QLine *pOsdLine);
};

#endif // RESOLVERUNDATA_H
