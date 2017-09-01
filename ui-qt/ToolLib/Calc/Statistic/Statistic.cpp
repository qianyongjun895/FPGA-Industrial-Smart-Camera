#include "Statistic.h"
#include "ToolStatistic.h"
#include "ResolveRunData.h"
#include <QMap>
QMap<int ,ResolveRunData*> g_map;
ToolStatistic* pWidget = NULL;
Statistic::Statistic()
{
}

/**
 * @brief GetWidget
 * @return QWidget指针
 * @author th
 * note 获取工具界面对象指针
 */
QWidget* GetWidget()
{
    pWidget = new ToolStatistic();
    return  pWidget;
}

/**
 * @brief ReleaseWidget
 * @param pWidget
 * @author th
 * @note 释放工具界面对象指针
 */
void ReleaseWidget(QWidget *pWidget)
{
    if(pWidget !=NULL)
    {
        delete pWidget;
        pWidget = NULL;
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

/**
 * @brief Paint
 * @param paint
 * @param step
 * @author th
 * @note 编辑画osd
 */
void Paint(QPainter *paint,int step,void *penStyle,int paintAreaSelect)
{
}


void Init_Input_Ptr(void *ptr,int i_step_index,int new_flag,void *pen_color)
{
    pWidget->Init_Input_Ptr(ptr,i_step_index,new_flag,pen_color);
}


int Set_Parameter_To_Ram()
{
    return pWidget->Set_Parameter_To_Ram();
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
    return resolveRunData->GetContent(step, index,count);
}

QPoint Get_Image_Pos()
{
     QPoint point(10,10);
//    if(pWidget !=NULL)
//    {
//        point= pWidget->Get_Image_Pos();
//    }
    return point;
}
