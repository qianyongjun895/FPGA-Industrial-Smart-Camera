#ifndef RESOLVERUNDATA_H
#define RESOLVERUNDATA_H

#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QLabel>
#include <QVector>
#include "../../BasicDefine.h"
#include "PixelConvert.h"
#include "TaskStepGlobal.h"
#include "TaskRstGlobal.h"
#include "MiddlePointGlobal.h"

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
    QPoint m_mid_point;
    LineParameter m_line_para;
    int m_ok_cnt;
    int m_ng_cnt;
    int m_excute_flag;

    void GetMesureOsdData(int i_step);
};

#endif // RESOLVERUNDATA_H
