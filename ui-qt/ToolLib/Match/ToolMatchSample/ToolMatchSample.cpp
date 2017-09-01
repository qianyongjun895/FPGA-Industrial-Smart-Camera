#include "ToolMatchSample.h"
#include "SampleWidget.h"
#include "ResolveRunData.h"
#include <QMap>
QMap<int ,ResolveRunData*> g_map;
SampleWidget *pWidget = NULL;


ToolMatchSample::ToolMatchSample()
{
}
QWidget *GetWidget()
{
    pWidget = new SampleWidget();
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
    resolveRunData->Paint(paint,step,penStyle,paintAreaSelect);
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
    return resolveRunData->GetContent(step, index, count);
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
void Init_Input_Ptr(void *pInpuPara,int i_step_index ,int new_flag,void *pen_color)
{
    if(pWidget !=NULL)
    {
        pWidget->Init_Input_Ptr(pInpuPara,i_step_index,new_flag,pen_color);
    }
    ResolveRunData *resolveRunData = NULL;
    if(g_map.contains(i_step_index))
    {
       resolveRunData =  g_map.value(i_step_index);
    }else
    {
        resolveRunData = new ResolveRunData ;
        g_map.insert(i_step_index,resolveRunData);
    }
    resolveRunData->SetInputPtr(pInpuPara);
}
int Set_Parameter_To_Ram()
{
    if(pWidget !=NULL)
    {
        return pWidget->Set_Parameter_To_Ram();
    }
}
extern "C" Q_DECL_EXPORT void Get_Result_From_Ram()
{
    pWidget->Get_Result_From_Ram();
}

