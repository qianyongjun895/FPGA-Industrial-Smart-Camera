#include "ResolveRunData.h"
#include <qdebug.h>
#include <QThread>
ResolveRunData::ResolveRunData()
{

}
ResolveRunData::~ResolveRunData()
{

}

void ResolveRunData::Paint(QPainter *paint,int step,void *penStyle,int paintAreaSelect)
{
    QPen pen;
    pen.setColor(Qt::red);
    paint->setPen(pen);
    paint->drawLine(100,100,640,480);
}

QVector<STRU_KEY_VALUE> ResolveRunData::GetHead(int step)
{
    QVector<STRU_KEY_VALUE> vt;
    //Todo...
    return vt;
}


QVector<STRU_KEY_VALUE> ResolveRunData::GetContent(int step, int index, int *count)
{
    QVector<STRU_KEY_VALUE> vt;
    return vt;
}
