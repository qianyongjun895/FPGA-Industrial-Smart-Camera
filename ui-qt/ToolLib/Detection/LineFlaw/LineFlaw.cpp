#include "LineFlaw.h"
#include "LineFlawWidget.h"
#include "ResolveRunData.h"
#include <QMap>
QMap<int ,ResolveRunData*> g_map;
LineFlaw::LineFlaw()
{
}
LineFlawWidget *pWidget = NULL;
/**
 * @brief GetWidget
 * @return QWidget指针
 * @author dgq
 * note 获取工具界面对象指针
 */
QWidget *GetWidget()
{
    pWidget = new LineFlawWidget();
    return  pWidget;
}

/**
 * @brief ReleaseWidget
 * @param PWidget
 * @author dgq
 * @note 释放工具界面对象指针
 */
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
/**
 * @brief Paint
 * @param paint
 * @param step
 * @author dgq
 * @note 编辑画osd
 */
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
 * @note 取样
 */
extern "C" Q_DECL_EXPORT int Set_Parameter_To_Ram()
{
    return pWidget->Set_Parameter_To_Ram();
}

/**
 * @brief GetHead
 * @param step
 * @return
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
 * @note 获取本步骤特有输出数据
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

/**
 * @brief Get_Result_From_Ram
 * @author dgq
 * @note 从内存中获取取样、计算的结果数据更新界面显示
 */
extern "C" Q_DECL_EXPORT void Get_Result_From_Ram()
{
    pWidget->Get_Result_From_Ram();
}

