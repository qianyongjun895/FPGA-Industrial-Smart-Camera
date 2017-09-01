#include "PretreatmentLibFun.h"
#include <QMessageBox>
#include <qdebug.h>

PretreatmentLibFun::PretreatmentLibFun()
{
    m_pWidget = NULL;
}
PretreatmentLibFun::~PretreatmentLibFun()
{
    if(m_pWidget !=NULL)
    {
        delete m_pWidget;
        m_pWidget = NULL;
    }
}
QWidget *PretreatmentLibFun::GetPreWidget()
{
    typedef QWidget* (*Fun_GetToolWidget)(); //定义函数指针，以备调用
    Fun_GetToolWidget fun=(Fun_GetToolWidget)m_lib.resolve("GetWidget");
    if (fun)
    {
        m_pWidget=fun();
    }else
    {
        QMessageBox::information(NULL,"提示","获取"+m_strLib+"中GetWidget函数名失败!");
        m_pWidget = NULL;
    }
    return m_pWidget;
}
void PretreatmentLibFun::Set_id_step(int iTask,int iStep,int x,int y,int edit,QVector<int> vt)
{
    typedef QWidget* (*Fun_SetIdAndStep)(int,int,int ,int,int,QVector<int>); //定义函数指针，以备调用
    Fun_SetIdAndStep fun=(Fun_SetIdAndStep)m_lib.resolve("SetIdAndStep");
    if (fun)
    {
        fun(iTask,iStep,x,y,edit,vt);
    }else
    {
        QMessageBox::information(NULL,"提示","获取"+m_strLib+"中SetIdAndStep函数名失败!");
    }
}
void PretreatmentLibFun::ConfigAllPreModule()
{
    typedef void (*Fun_PreModuleConfigAll)(); //定义函数指针，以备调用
    Fun_PreModuleConfigAll fun=(Fun_PreModuleConfigAll)m_lib.resolve("PreModuleConfigAll");
    if (fun)
    {
        fun();
    }else
    {
        QMessageBox::information(NULL,"提示","获取"+m_strLib+"中PreModuleConfigAll函数名失败!");

    }
}
void PretreatmentLibFun::PreAllPreModuleDisable()
{
    typedef void (*Fun_PreAllModuleDisable)(); //定义函数指针，以备调用
    Fun_PreAllModuleDisable fun=(Fun_PreAllModuleDisable)m_lib.resolve("PreAllModuleDisable");
    if (fun)
    {
        fun();
    }else
    {
        QMessageBox::information(NULL,"提示","获取"+m_strLib+"中PreAllModuleDisable函数名失败!");

    }
}
void PretreatmentLibFun::ListCptVga()
{
    typedef void (*Fun_ListCptVga)(); //定义函数指针，以备调用
    Fun_ListCptVga fun=(Fun_ListCptVga)m_lib.resolve("ListCptVga");

    if (fun)
    {
        fun();
    }else
    {
        QMessageBox::information(NULL,"提示","获取"+m_strLib+"中ListCptVga函数名失败!");
    }
}
void PretreatmentLibFun::GetImageOutPut()
{
    typedef void (*Fun_GetImageOutPut)(); //定义函数指针，以备调用
    Fun_GetImageOutPut fun=(Fun_GetImageOutPut)m_lib.resolve("GetImageOutPut");

    if (fun)
    {
        fun();
    }else
    {
        QMessageBox::information(NULL,"提示","获取"+m_strLib+"中GetImageOutPut函数名失败!");
    }
}
void PretreatmentLibFun::StepAcceleratorModuleEnable()
{
    typedef void (*Fun_ModuleEnable)(); //定义函数指针，以备调用
    Fun_ModuleEnable fun=(Fun_ModuleEnable)m_lib.resolve("StepAcceleratorModuleEnable");

    if (fun)
    {
        fun();
    }else
    {
        QMessageBox::information(NULL,"提示","获取"+m_strLib+"中StepAcceleratorModuleEnable函数名失败!");
    }
}
void PretreatmentLibFun::SetTaskNameVt(QVector<QString>vt)
{
    typedef void (*Fun_SetTaskNameVt)(QVector<QString>); //定义函数指针，以备调用
    Fun_SetTaskNameVt fun=(Fun_SetTaskNameVt)m_lib.resolve("SetTaskListName");

    if (fun)
    {
        fun(vt);

    }else
    {
        QMessageBox::information(NULL,"提示","获取"+m_strLib+"中SetTaskListName函数名失败!");
    }

}
void PretreatmentLibFun::SetColor(void *pen_color)
{
    typedef void (*Fun_SetColor)(void *); //定义函数指针，以备调用
    Fun_SetColor fun=(Fun_SetColor)m_lib.resolve("SetColor");

    if (fun)
    {
        fun(pen_color);

    }else
    {
        QMessageBox::information(NULL,"提示","获取"+m_strLib+"中SetColor函数名失败!");
    }
}
