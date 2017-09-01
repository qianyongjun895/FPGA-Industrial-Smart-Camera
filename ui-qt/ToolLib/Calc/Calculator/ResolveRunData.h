#ifndef RESOLVERUNDATA_H
#define RESOLVERUNDATA_H

#include <QObject>
#include <QVector>
#include "../../BasicDefine.h"
class ResolveRunData
{
public:
    ResolveRunData();
    QVector<STRU_KEY_VALUE> GetContent(int step, int index, int *count);
    QVector<STRU_KEY_VALUE> GetHead(int step);
};

#endif // RESOLVERUNDATA_H
