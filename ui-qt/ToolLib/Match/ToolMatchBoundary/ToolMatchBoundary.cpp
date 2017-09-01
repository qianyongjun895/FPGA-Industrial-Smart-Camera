#include "ToolMatchBoundary.h"
#include "ResolveRunData.h"
#include <QMap>
QMap<int ,ResolveRunData*> g_map;
BoundaryWidget *pWidget = NULL;

ToolMatchBoundary::ToolMatchBoundary()
{
}

QWidget *GetWidget()
{
    pWidget = new BoundaryWidget();
    return  pWidget;
}

void ReleaseWidget(QWidget *PWidget)
{
    if(PWidget != NULL)
    {
        delete PWidget;
        PWidget = NULL;
    }
}
void ReleaseQMap()
{
    QMap<int, ResolveRunData*>::const_iterator i;
    for (i = g_map.constBegin(); i != g_map.constEnd(); ++i) {
        ResolveRunData *runData = i.value();
        if(runData != NULL)
        {
            delete runData;
            runData = NULL;
        }
    }
    g_map.clear();
}
void Paint(QPainter *paint,int step,void *penStyle,int paintAreaSelect)
{
    ResolveRunData *resolveRunData = NULL;
    if(g_map.contains(step))
    {
       resolveRunData =  g_map.value(step);
    }else
    {
        resolveRunData = new ResolveRunData ;
        g_map.insert(step,resolveRunData);
    }
//    resolveRunData.Paint(paint,step,penStyle,paintAreaSelect);
}
/*
QVector<STRU_KEY_VALUE> GetHead(int step)
{
    ResolveRunData *resolveRunData = NULL;
    if(g_map.contains(step))
    {
       resolveRunData =  g_map.value(step);
    }else
    {
        resolveRunData = new ResolveRunData ;
        g_map.insert(step,resolveRunData);
    }
//    return resolveRunData.GetHead(step);
}
QVector<STRU_KEY_VALUE> GetContent(int step, int index, int *count)
{
    ResolveRunData *resolveRunData = NULL;
    if(g_map.contains(step))
    {
       resolveRunData =  g_map.value(step);
    }else
    {
        resolveRunData = new ResolveRunData ;
        g_map.insert(step,resolveRunData);
    }
//    return resolveRunData.GetContent(step,index, count);
}*/
QPoint Get_Image_Pos()
{
     QPoint point(-1024,-768);
    if(pWidget !=NULL)
    {
        point= pWidget->Get_Image_Pos();
    }
    return point;
}
