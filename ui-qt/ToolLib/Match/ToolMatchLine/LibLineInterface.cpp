#include "LibLineInterface.h"
#include <QMessageBox>
#include <qdebug.h>
LibLineInterface::LibLineInterface()
{

}
LibLineInterface::~LibLineInterface()
{
    if(m_lib.isLoaded())
        m_lib.unload();
}
int LibLineInterface::IniLib(QString strName)
{
    this->m_strLib = strName;
    m_lib.setFileName(m_strLib);
    qDebug()<<"strName==="<<strName;
    if(m_lib.load())
    {
        return 1;
    }else
    {
        QMessageBox::information(NULL,"提示","加载图像工作DLL("+m_strLib+")失败!");
        return 0;
    }
}
int LibLineInterface::LibLineInterface::Circle_Input_Center_X_Y_Set(unsigned int step_index, unsigned int x, unsigned int y)
{
    int ret = 0;
    typedef int (*Fun_Circle_Input_Center_X_Y_Set)(unsigned int,unsigned int,unsigned int); //定义函数指针，以备调用
    Fun_Circle_Input_Center_X_Y_Set fun=(Fun_Circle_Input_Center_X_Y_Set)m_lib.resolve("Circle_Input_Center_X_Y_Set");
    if (fun)
    {
         ret =fun(step_index,x,y);
         if(ret == 0)
             ret =1;
    }else
    {
        QMessageBox::information(NULL,"提示","获取libcircle.so中Get_Task_Classify_Num函数名失败!");
        ret = 0;
    }
    return ret;
}
