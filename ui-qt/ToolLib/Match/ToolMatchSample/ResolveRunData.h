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
#include "tool_testGlobal.h"

class ResolveRunData
{

public:
    explicit ResolveRunData();
    ~ResolveRunData();

    void Paint(QPainter *paint,int step,void *penStyle,int paintAreaSelect);
    QVector<STRU_KEY_VALUE> GetHead(int step);
    QVector<STRU_KEY_VALUE> GetContent(int step, int index, int *count);
    void SetInputPtr(void *ptr);
private:
    BASE_LINE_OUTPUT_PARAM *pRunPara;
    int m_line_index;
    int m_line_cnt;
    int m_pix_x;
    int m_pix_y;
    TOOLTEST_INPUT_PARAM *pInputPara;
};

#endif // RESOLVERUNDATA_H
