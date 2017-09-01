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
#include "MiddleLineGlobal.h"

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
    QLine m_line;
    QLine line1;
    QLine line2;
    LineParameter m_line_para;
    int m_ok_cnt;
    int m_ng_cnt;
    int m_excute_flag;

    void GetMesureOsdData(int i_step);
    int Line_Paint_Base_On_KB_SubPixel(float k_f, float b_f, QLine *pOsd_line);
    int Line_Osd_Init(LineParameter *pLinePara, QLine *pOsdLine);
};
#endif // RESOLVERUNDATA_H
