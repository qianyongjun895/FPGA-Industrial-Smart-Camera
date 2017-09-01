#include "ToolMatchBaseline.h"
#include "BaseLineWidget.h"
#include "ResolveRunData.h"
#include <qdebug.h>
#include <QMap>

QMap<int ,ResolveRunData*> g_map;
BaseLineWidget *pWidget = NULL;
ToolMatchBaseline::ToolMatchBaseline()
{
    qDebug()<<"ToolMatchBaseline::ToolMatchBaseline()";
}

/**
 * @brief GetWidget
 * @return
 * @author dgq
 * @note 获取界面对象指针
 */
QWidget *GetWidget()
{
    pWidget = new BaseLineWidget();
    return  pWidget;
}


/**
 * @brief ReleaseWidget
 * @param PWidget
 * @author dgq
 * @note 释放界面对象
 */
void ReleaseWidget(QWidget *PWidget)
{
    if(pWidget !=NULL)
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


/**
 * @brief Paint
 * @param paint
 * @param step
 * @author dgq
 * @note OSD显示
 */
void Paint(QPainter *paint, int step, void *penStyle, int paintAreaSelect)
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


/**
 * @brief Init_Input_Ptr
 * @param ptr input结构体指针
 * @param i_step_index 当前步骤号
 * @param new_flag 新加步骤标志：1新加，0编辑
 * @author dgq
 * @note 初始化设置Input结构体指针
 */
extern "C" Q_DECL_EXPORT void Init_Input_Ptr(void *pInpuPara,int i_step_index ,int new_flag,void *pen_color)
{
    pWidget->Init_Input_Ptr(pInpuPara,i_step_index,new_flag,pen_color);
}


/**
 * @brief Set_Parameter_To_Ram
 * @author dgq
 * @note 将界面的配置参数写入内存
 */
extern "C" Q_DECL_EXPORT int Set_Parameter_To_Ram()
{
    return pWidget->Set_Parameter_To_Ram();
}


/**
 * @brief GetHead
 * @param step
 * @return 通用输出详细信息
 * @author dgq
 * @note 获取任务通用输出数据
 */
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


/**
 * @brief GetContent
 * @param step
 * @return
 * @author dgq
 * @note 获取本步特有输出数据
 */
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
    return resolveRunData->GetContent(step,index,count);
}
/**
 * @brief Get_Image_Pos
 * @return
 * @author dgq
 * @note 获取图像显示区域的位置
 */
QPoint Get_Image_Pos()
{
    QPoint point(-1024,-768);
    if(pWidget !=NULL)
    {
        point= pWidget->Get_Image_Pos();
    }
    return point;
}

