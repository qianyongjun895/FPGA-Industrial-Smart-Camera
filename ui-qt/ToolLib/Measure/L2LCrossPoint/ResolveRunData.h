#ifndef RESOLVERUNDATA_H
#define RESOLVERUNDATA_H

#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QLabel>
#include <QVector>
#include "../../BasicDefine.h"
#include "TaskStepGlobal.h"
#include "TaskRstGlobal.h"
#include "LinesCrossPointGlobal.h"

class ResolveRunData
{
public:
    explicit ResolveRunData();

    ~ResolveRunData();
    void Paint(QPainter *paint,int step,void *penStyle,int paintAreaSelect);
    QVector<STRU_KEY_VALUE> GetHead(int step);
    QVector<STRU_KEY_VALUE> GetContent(int step, int index,int *count);
private:
    QPoint m_point;
    QLine line1;
    QLine line2;
    int m_ok_cnt;
    int m_ng_cnt;
    int m_excute_flag;

    void GetMesureOsdData(int i_step);
    int Line_Osd_Init(LineParameter *pLinePara, QLine *pOsdLine);
    int Line_Paint_Base_On_KB_SubPixel(float k_f, float b_f, QLine *pOsd_line);
};

#endif // RESOLVERUNDATA_H
