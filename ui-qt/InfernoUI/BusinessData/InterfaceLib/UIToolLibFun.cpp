#include <QDebug>
#include "UIToolLibFun.h"
#include <QMessageBox>
#include "TaskGlobal.h"
UIToolLibFun::UIToolLibFun()
{
    m_pWidget = NULL;
}
UIToolLibFun::~UIToolLibFun()
{
    if(m_pWidget !=NULL)
    {
        delete m_pWidget;
        m_pWidget = NULL;
    }
    ReleaseMap();
    qDebug()<<"UIToolLibFun::~UIToolLibFun()";
}
/*int UIToolLibFun::IniLib(QString strName)
{
    this->m_strLib = strName;
    m_lib.setFileName(m_strLib);
    if (m_lib.load())
    {
        return 1;
    }else
    {
        QMessageBox::information(NULL,"提示","加载图像工作DLL("+m_strLib+")失败!");
        return 0;
    }
}*/
QWidget* UIToolLibFun::GetToolWidget()
{
    typedef QWidget* (*Fun_GetToolWidget)(); //定义函数指针，以备调用
    //m_lib.setFileName(m_strLib);

    //if (m_lib.load())
    {
        Fun_GetToolWidget fun=(Fun_GetToolWidget)m_lib.resolve("GetWidget");
        if (fun)
        {
            m_pWidget=fun();
        }else
        {
            QMessageBox::information(NULL,"提示","获取"+m_strLib+"中GetWidget函数名失败!");
            m_pWidget = NULL;
        }
        //mylib.unload();
    }
    /*else
   {
       QMessageBox::information(NULL,"提示","加载图像工作DLL("+m_strLib+")失败!");
       m_pWidget = NULL;
   }*/
   return m_pWidget;
}
void UIToolLibFun::Set_fun_lib_path(QString strPath)
{
    typedef void (*Fun_Set_fun_lib_path)(QString); //定义函数指针，以备调用

    Fun_Set_fun_lib_path fun=(Fun_Set_fun_lib_path)m_lib.resolve("Set_fun_lib_path");
    if (fun)
    {
        fun(strPath);
    }else
    {
        QMessageBox::information(NULL,"提示","获取"+m_strLib+"中Set_fun_lib_path函数名失败!");
    }
}
void UIToolLibFun::Paint(QPainter *paint, int step, void *PenStly, int paintAreaSelect)
{
    typedef void (*Fun_Paint)(QPainter *,int,void *,int); //定义函数指针，以备调用

    Fun_Paint fun=(Fun_Paint)m_lib.resolve("Paint");
    if (fun)
    {
        fun(paint,step,PenStly,paintAreaSelect);
    }else
    {
        QMessageBox::information(NULL,"提示","获取"+m_strLib+"中Paint函数名失败!");
    }

}


QVector<STRU_KEY_VALUE> UIToolLibFun::GetHead(int step)
{
    QVector<STRU_KEY_VALUE> vt;
    typedef QVector<STRU_KEY_VALUE> (*Fun_GetHead)(int ); //定义函数指针，以备调用

    Fun_GetHead fun=(Fun_GetHead)m_lib.resolve("GetHead");
    if (fun)
    {
         vt = fun(step);
         return vt;
    }else
    {
        QMessageBox::information(NULL,"提示","获取"+m_strLib+"中GetHead函数名失败!");
    }

}

QVector<STRU_KEY_VALUE> UIToolLibFun::GetContent(int step,int index,int *count)
{
    QVector<STRU_KEY_VALUE> vt;
    typedef QVector<STRU_KEY_VALUE> (*Fun_GetContent)(int,int ,int *); //定义函数指针，以备调用

    Fun_GetContent fun=(Fun_GetContent)m_lib.resolve("GetContent");
    if (fun)
    {
        vt = fun(step,index,count);

    }else
    {
        QMessageBox::information(NULL,"提示","获取"+m_strLib+"中GetContent函数名失败!");
    }
    return vt;

}


int UIToolLibFun::SetResultIndex(int index)
{
    typedef int (*Fun_SetResultIndex)(int ); //定义函数指针，以备调用

    Fun_SetResultIndex fun=(Fun_SetResultIndex)m_lib.resolve("SetResultIndex");
    if (fun)
    {
        int i_cnt = fun(index);
        return i_cnt;
    }else
    {
        QMessageBox::information(NULL,"提示","获取"+m_strLib+"中SetResultIndex函数名失败!");
        return 1;
    }

}

void UIToolLibFun::Init_Input_Ptr(void *pInpuPara,int i_step_index,int new_flag,void *pen_color)
{
    typedef void (*Fun_Init_Input_Ptr)(void *,int,int,void *); //定义函数指针，以备调用

    Fun_Init_Input_Ptr fun=(Fun_Init_Input_Ptr)m_lib.resolve("Init_Input_Ptr");
    if (fun)
    {
        fun(pInpuPara,i_step_index,new_flag,pen_color);
    }else
    {
        QMessageBox::information(NULL,"提示","获取"+m_strLib+"中Init_Input_Ptr函数名失败!");
    }
}


void UIToolLibFun::Get_Result_From_Ram()
{
    typedef void (*Fun_Get_Result_From_Ram)(); //定义函数指针，以备调用

    Fun_Get_Result_From_Ram fun=(Fun_Get_Result_From_Ram)m_lib.resolve("Get_Result_From_Ram");
    if (fun)
    {
        fun();
    }else
    {
//        QMessageBox::information(NULL,"提示","获取"+m_strLib+"中Get_Result_From_Ram函数名失败!");
    }
}

int UIToolLibFun::Set_Parameter_To_Ram()
{
    typedef int (*Fun_Set_Parameter_To_Ram)(); //定义函数指针，以备调用
    int rst;
    Fun_Set_Parameter_To_Ram fun=(Fun_Set_Parameter_To_Ram)m_lib.resolve("Set_Parameter_To_Ram");
    if (fun)
    {
        rst = fun();
    }else
    {
        QMessageBox::information(NULL,"提示","获取"+m_strLib+"中Set_Parameter_To_Ram函数名失败!");
    }
    return rst;
}
QPoint UIToolLibFun::Get_Image_Pos()
{
    QPoint temp(10,10);
    typedef QPoint (*Fun_Get_Image_Pos)(); //定义函数指针，以备调用

    Fun_Get_Image_Pos fun=(Fun_Get_Image_Pos)m_lib.resolve("Get_Image_Pos");
    if (fun)
    {
        temp = fun();
    }else
    {
        QMessageBox::information(NULL,"提示","获取"+m_strLib+"中Get_Image_Pos函数名失败!");
    }
    return temp;
}
void UIToolLibFun::ReleaseMap()
{

    typedef QPoint (*Fun_ReleaseBuf)(); //定义函数指针，以备调用

    Fun_ReleaseBuf fun=(Fun_ReleaseBuf)m_lib.resolve("ReleaseQMap");
    if (fun)
    {
         fun();
    }else
    {
        QMessageBox::information(NULL,"提示","获取"+m_strLib+"中ReleaseQMap函数名失败!");
    }
}


