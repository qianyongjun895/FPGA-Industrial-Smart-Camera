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
#include "DelayGlobal.h"

class ResolveRunData
{
public:
    ResolveRunData();
    void Paint(QPainter *paint,int step,void *penStyle,int paintAreaSelect);
    QVector<STRU_KEY_VALUE> GetHead(int step);
    QVector<STRU_KEY_VALUE> GetContent(int step,int index,int *count);

private:
    void *pRunPara;
};

#endif // RESOLVERUNDATA_H
