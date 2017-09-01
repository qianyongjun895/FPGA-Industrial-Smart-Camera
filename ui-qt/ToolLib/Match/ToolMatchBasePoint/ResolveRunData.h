#ifndef RESOLVERUNDATA_H
#define RESOLVERUNDATA_H

#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QLabel>
#include <QVector>
#include "../../BasicDefine.h"
#include "BasePointGlobal.h"
#include "TaskStepGlobal.h"
#include "TaskRstGlobal.h"
class ResolveRunData
{

public:
    explicit ResolveRunData();
    ~ResolveRunData();
    void Paint(QPainter *paint,int step,void *penStyle,int paintAreaSelect);
    QVector<STRU_KEY_VALUE> GetHead(int step);
    QVector<STRU_KEY_VALUE> GetContent(int step, int index, int *count);
private:
    void *pRunPara;
    int m_Point_cnt;//基准点总数
    QPointF m_BasePointPix[20];
    QPointF m_BasePointPhy[20];
    QPointF m_BasePointReal[20];

};

#endif // RESOLVERUNDATA_H
