#include "ToolGrayMatch.h"
#include "GreayMatchRunData.h"
#include "GrayMatchWidget.h"
#include <QMap>
QMap<int ,GreayMatchRunData*> g_map;

ToolGrayMatch::ToolGrayMatch()
{

}
//获取界面的指针对象
GrayMatchWidget *pWidget = NULL;
QWidget *GetWidget()
{
    pWidget = new GrayMatchWidget();
    return  pWidget;
}

//释放界面的指针对象
void ReleaseWidget(QWidget *PWidget)
{
    if(PWidget !=NULL)
    {
        delete PWidget;
        PWidget = NULL;
    }
}

//释放Map对象里面的内存
void ReleaseQMap()
{
    QMap<int, GreayMatchRunData*>::const_iterator i;
    for (i = g_map.constBegin(); i != g_map.constEnd(); ++i) {
        GreayMatchRunData *runData = i.value();
        if(runData != NULL)
        {
            delete runData;
            runData = NULL;
        }
    }
    g_map.clear();
}

//显示的指针结构体赋值函数
void Paint(QPainter *paint,int step,void *penStyle,int paintAreaSelect)
{
    GreayMatchRunData *resolveRunData = NULL;
    if(g_map.contains(step))
    {
       resolveRunData =  g_map.value(step);
    }else
    {
        resolveRunData = new GreayMatchRunData ;
        g_map.insert(step,resolveRunData);
    }
    resolveRunData->Paint(paint,step,penStyle,paintAreaSelect);
}

//初始化输入参数的指针
extern "C" Q_DECL_EXPORT void Init_Input_Ptr(void *pInpuPara,int i_step_index ,int new_flag,void *pen_color)
{
    pWidget->Init_Input_Ptr(pInpuPara,i_step_index,new_flag,pen_color);
}

//将参数设置到内存里面
extern "C" Q_DECL_EXPORT int Set_Parameter_To_Ram()
{
    return pWidget->Set_Parameter_To_Ram();
}

//获取通用的输出数据
QVector<STRU_KEY_VALUE> GetHead(int step)
{
    GreayMatchRunData *resolveRunData = NULL;
    if(g_map.contains(step))
    {
       resolveRunData =  g_map.value(step);
    }else
    {
        resolveRunData = new GreayMatchRunData ;
        g_map.insert(step,resolveRunData);
    }
    return resolveRunData->GetHead(step);
}

//获取本过程的输出数据
QVector<STRU_KEY_VALUE> GetContent(int step, int index, int *count)
{
    GreayMatchRunData *resolveRunData = NULL;
    if(g_map.contains(step))
    {
       resolveRunData =  g_map.value(step);
    }else
    {
        resolveRunData = new GreayMatchRunData ;
        g_map.insert(step,resolveRunData);
    }
    return resolveRunData->GetContent(step, index, count);
}

//获取图像显示区域的位置
QPoint Get_Image_Pos()
{
    QPoint point(-1024,-768);
    if(pWidget !=NULL)
    {
        point= pWidget->Get_Image_Pos();
    }
    return point;
}
