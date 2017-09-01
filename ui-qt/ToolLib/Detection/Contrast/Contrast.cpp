#include "Contrast.h"
#include "ResolveRunData.h"
#include "ContrastWidget.h"
#include <QMap>

QMap<int ,ResulveRunData*> g_map;
ContrastWidget *pWidget = NULL;

Contrast::Contrast()
{
}


/**
 * @brief GetWidget
 * @return QWidget指针
 * @author dgq
 * note 获取工具界面对象指针
 */
QWidget *GetWidget()
{
    pWidget = new ContrastWidget();
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
    QMap<int, ResulveRunData*>::const_iterator i;
    for (i = g_map.constBegin(); i != g_map.constEnd(); ++i) {
        ResulveRunData *runData = i.value();
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
//    resolveRunData.Paint(paint,step,penStyle,paintAreaSelect);
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
 * @return
 * @author dgq
 * @note 获取任务通用输出数据
 */
QVector<STRU_KEY_VALUE> GetHead(int step)
{
    ResulveRunData *resolveRunData = NULL;
    if(g_map.contains(step))
    {
       resolveRunData =  g_map.value(step);
    }else
    {
        resolveRunData = new ResulveRunData ;
        g_map.insert(step,resolveRunData);
    }

    return resolveRunData->GetHead(step);
}

/**
 * @brief GetContent
 * @param step
 * @return
 * @author dgq
 * @note 获取本步特有参数
 */
QVector<STRU_KEY_VALUE> GetContent(int step, int index, int *count)
{
    ResulveRunData *resolveRunData = NULL;
    if(g_map.contains(step))
    {
       resolveRunData =  g_map.value(step);
    }else
    {
        resolveRunData = new ResulveRunData ;
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
