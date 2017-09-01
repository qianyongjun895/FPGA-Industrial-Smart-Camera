#ifndef RESOLVERUNDATA_H
#define RESOLVERUNDATA_H


#include <QVector>
#include "../../BasicDefine.h"

class ResolveRunData
{
public:
    ResolveRunData();
    QVector<STRU_KEY_VALUE> GetHead(int step);
    QVector<STRU_KEY_VALUE> GetContent(int step, int index, int *count);
private:
    QVector<QString> Code_Type;
};

#endif // RESOLVERUNDATA_H
