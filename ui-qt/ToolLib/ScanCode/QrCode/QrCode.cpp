#include "QrCode.h"
#include "ToolQrCode.h"
#include <QDebug>
#include "ResolveRunData.h"
#include <QMap>
QMap<int ,ResolveRunData*> g_map;
ToolQrCode *pWidget = NULL;
QrCode::QrCode()
{
}

QWidget *GetWidget()
{
    pWidget = new ToolQrCode();
    return  pWidget;
}
void ReleaseWidget(QWidget *PWidget)
{
    if(PWidget !=NULL)
    {
        delete PWidget;
        PWidget = NULL;
    }
}

void Paint(QPainter *paint,int step,void *penStyle,int paintAreaSelect)
{
}

void Init_Input_Ptr(void *pInpuPara,int i_step_index ,int new_flag,void *pen_color)
{
    pWidget->Init_Input_Ptr(pInpuPara,i_step_index,new_flag,pen_color);
}
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
    return resolveRunData->GetHead(step);
}

QVector<STRU_KEY_VALUE> GetContent(int step,int index,int *count)
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
    return resolveRunData->GetContent(step,index,count);
}

int Set_Parameter_To_Ram()
{
    return pWidget->Set_Parameter_To_Ram();
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
QPoint Get_Image_Pos()
{
   QPoint point(-1024,-768);
    if(pWidget !=NULL)
    {
        point= pWidget->Get_Image_Pos();
    }
    return point;
}
