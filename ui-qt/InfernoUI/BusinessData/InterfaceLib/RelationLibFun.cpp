#include "RelationLibFun.h"
#include <QMessageBox>
RelationLibFun::RelationLibFun()
{
    m_pWidget = NULL;
}
RelationLibFun::~RelationLibFun()
{
    if(m_pWidget !=NULL)
    {
        delete m_pWidget;
        m_pWidget = NULL;
    }
}
QWidget *RelationLibFun::GetRLWidget()
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

int RelationLibFun::IniRLData(int task_Index)
{
    int ret = 0;
    typedef int (*Fun_InitData)(int index); //定义函数指针，以备调用
    Fun_InitData fun=(Fun_InitData)m_lib.resolve("IniLinkData");
    if (fun)
    {
        ret = fun(task_Index);
    }else
    {
        QMessageBox::information(NULL,"提示","获取"+m_strLib+"中IniLinkData函数名失败!");
        ret = -1;
    }
    return ret;
}

int RelationLibFun::SetRLData()
{
    int ret = 0;
    typedef int (*Fun_SetRLData)(); //定义函数指针，以备调用
    Fun_SetRLData fun=(Fun_SetRLData)m_lib.resolve("SetLinkData");
    if (fun)
    {
        ret = fun();
    }else
    {
        QMessageBox::information(NULL,"提示","获取"+m_strLib+"中SetLinkData函数名失败!");
        ret = -1;
    }
    return ret;
}
