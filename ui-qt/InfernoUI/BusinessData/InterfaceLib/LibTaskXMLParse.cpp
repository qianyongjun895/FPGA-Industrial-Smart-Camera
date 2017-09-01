#include <qdebug.h>
#include "LibTaskXMLParse.h"
#include <QMessageBox>
#include "Comm/GlobalParameter.h"
#include "cmos_common.h"
LibTaskXMLParse::LibTaskXMLParse()
{

}
LibTaskXMLParse::~LibTaskXMLParse()
{
    /*if(m_lib.isLoaded())
        m_lib.unload();*/
}
/*int LibTaskXMLParse::IniLib(QString strName)
{
    this->m_strLib = strName;
    m_lib.setFileName(m_strLib);

    if(m_lib.load())
    {
        return 1;
    }else
    {
        QMessageBox::information(NULL,"提示","加载图像工作DLL("+m_strLib+")失败!");
        return 0;
    }
}*/
int LibTaskXMLParse::lib_UI_Data_Init()
{
    int ret = 0;
    typedef int (*Fun_UI_Data_Init)(); //定义函数指针，以备调用
    Fun_UI_Data_Init xmlIni=(Fun_UI_Data_Init)m_lib.resolve("UI_Data_Init");
    if (xmlIni)
    {
         ret =xmlIni();
         if(ret ==0)
              return 1;
         else
             return 0;

    }else
    {
        QMessageBox::information(NULL,"提示","获取libtaskparse.so中UI_Data_Init函数名失败!");
    }
    return ret;
}
int LibTaskXMLParse::Get_Task_Classify_Num()
{
    int ret = 0;
    typedef int (*Fun_Get_Task_Classify_Num)(); //定义函数指针，以备调用
    Fun_Get_Task_Classify_Num fun=(Fun_Get_Task_Classify_Num)m_lib.resolve("Get_Task_Classify_Num");
    if (fun)
    {
         ret =fun();

    }else
    {
        QMessageBox::information(NULL,"提示","获取libtaskparse.so中Get_Task_Classify_Num函数名失败!");
        ret = 0;
    }
    return ret;
}
 QString LibTaskXMLParse::Get_Classify_Name(int index)
 {
     QString strRet = "";
     char className[32];
     memset(className,0,sizeof(className));

     typedef void (*Fun_Get_Classify_Name)(int , char*); //定义函数指针，以备调用
     Fun_Get_Classify_Name fun=(Fun_Get_Classify_Name)m_lib.resolve("Get_Classify_Name");
     if (fun)
     {
         fun(index,className);
         if(className != NULL)
         {
             strRet = QString::fromUtf8(className);
         }

     }else
     {
         QMessageBox::information(NULL,"提示","获取libtaskparse.so中Get_Classify_Name函数名失败!");
         strRet = "";
     }
     return strRet;
 }
QString LibTaskXMLParse::Get_Classify_Icon_Path(int index)
{
    QString strRet = "";
    char classPic[100];
    memset(classPic,0,sizeof(classPic));

    typedef void (*Fun_Get_Classify_Icon_Path)(int , char*); //定义函数指针，以备调用
    Fun_Get_Classify_Icon_Path fun=(Fun_Get_Classify_Icon_Path)m_lib.resolve("Get_Classify_Icon_Path");
    if (fun)
    {
        fun(index,classPic);
        if(classPic != NULL)
        {
            strRet = QString::fromUtf8(classPic);
        }

    }else
    {
        QMessageBox::information(NULL,"提示","获取libtaskparse.so中Get_Classify_Icon_Path函数名失败!");
        strRet = "";
    }
    return strRet;
}
int LibTaskXMLParse::Get_Classify_Task_Num(int index)
{
    int ret = 0;
    typedef int (*Fun_Get_Classify_Task_Num)(int); //定义函数指针，以备调用
    Fun_Get_Classify_Task_Num fun=(Fun_Get_Classify_Task_Num)m_lib.resolve("Get_Classify_Task_Num");
    if (fun)
    {
         ret =fun(index);

    }else
    {
        QMessageBox::information(NULL,"提示","获取libtaskparse.so中Get_Classify_Task_Num函数名失败!");
        ret = 0;
    }
    return ret;
}
int LibTaskXMLParse::Get_Classify_Task_ID(int class_index, int task_Index)
{
    int ret = 0;
    typedef int (*Fun_Get_Classify_Task_ID)(int,int); //定义函数指针，以备调用
    Fun_Get_Classify_Task_ID fun=(Fun_Get_Classify_Task_ID)m_lib.resolve("Get_Classify_Task_ID");
    if (fun)
    {
         ret =fun(class_index,task_Index);

    }else
    {
        QMessageBox::information(NULL,"提示","获取libtaskparse.so中Get_Classify_Task_ID函数名失败!");
        ret = 0;
    }
    return ret;
}
QString LibTaskXMLParse::Get_Classify_Task_Name(int class_index, int task_Index)
{
    QString strRet = "";
    char className[32];
    memset(className,0,sizeof(className));

    typedef void (*Fun_Get_Classify_Task_Name)(int ,int, char*); //定义函数指针，以备调用
    Fun_Get_Classify_Task_Name fun=(Fun_Get_Classify_Task_Name)m_lib.resolve("Get_Classify_Task_Name");
    if (fun)
    {
        fun(class_index,task_Index,className);
        if(className != NULL)
        {
            strRet = QString::fromUtf8(className);
        }

    }else
    {
        QMessageBox::information(NULL,"提示","获取libtaskparse.so中Get_Classify_Task_Name函数名失败!");
        strRet = "";
    }
    return strRet;
}
QString LibTaskXMLParse::Get_UI_Library_Name(int class_index, int task_Index)
{
    QString strRet = "";
    char className[100];
    memset(className,0,sizeof(className));

    typedef void (*Fun_Get_UI_Library_Name)(int ,int, char*); //定义函数指针，以备调用
    Fun_Get_UI_Library_Name fun=(Fun_Get_UI_Library_Name)m_lib.resolve("Get_UI_Library_Name");
    if (fun)
    {
        fun(class_index,task_Index,className);
        if(className != NULL)
        {
            strRet = QString::fromUtf8(className);
        }

    }else
    {
        QMessageBox::information(NULL,"提示","获取libtaskparse.so中Get_UI_Library_Name函数名失败!");
        strRet = "";
    }
    return strRet;
}

QString LibTaskXMLParse::Get_Task_Icon_Path(int class_index, int task_Index)
{
    QString strRet = "";
    char className[100];
    memset(className,0,sizeof(className));

    typedef void (*Fun_Get_Task_Icon_Path)(int ,int, char*); //定义函数指针，以备调用
    Fun_Get_Task_Icon_Path fun=(Fun_Get_Task_Icon_Path)m_lib.resolve("Get_Task_Icon_Path");
    if (fun)
    {
        fun(class_index,task_Index,className);
        if(className != NULL)
        {
            strRet = QString::fromUtf8(className);
        }

    }else
    {
        QMessageBox::information(NULL,"提示","获取libtaskparse.so中Get_Task_Icon_Path函数名失败!");
        strRet = "";
    }
    return strRet;
}
QString LibTaskXMLParse::Get_Function_Library_Name(int class_index, int task_Index)
{
    QString strRet = "";
    char className[100];
    memset(className,0,sizeof(className));

    typedef void (*Fun_Get_Function_Library_Name)(int ,int, char*); //定义函数指针，以备调用
    Fun_Get_Function_Library_Name fun=(Fun_Get_Function_Library_Name)m_lib.resolve("Get_Function_Library_Name");
    if (fun)
    {
        fun(class_index,task_Index,className);
        if(className != NULL)
        {
            strRet = QString::fromUtf8(className);
        }

    }else
    {
        QMessageBox::information(NULL,"提示","获取libtaskparse.so中Get_Function_Library_Name函数名失败!");
        strRet = "";
    }
    return strRet;
}
//黑白相机标志
int LibTaskXMLParse::Get_Black_Camera_Task_Load_Flag(int class_index, int task_Index)
{
    int ret = 0;
    typedef int (*Fun_Get_Task_Load_Flag)(int,int); //定义函数指针，以备调用
    Fun_Get_Task_Load_Flag fun=(Fun_Get_Task_Load_Flag)m_lib.resolve("Get_Black_Camera_Task_Load_Flag");
    if (fun)
    {
         ret =fun(class_index,task_Index);

    }else
    {
        QMessageBox::information(NULL,"提示","获取libtaskparse.so中Get_Classify_Task_ID函数名失败!");
        ret = 0;
    }
    return ret;
}
//采色相机标志
int LibTaskXMLParse::Get_Color_Camera_Task_Load_Flag(int class_index, int task_Index)
{
    int ret = 0;
    typedef int (*Fun_Get_Task_Load_Flag)(int,int); //定义函数指针，以备调用
    Fun_Get_Task_Load_Flag fun=(Fun_Get_Task_Load_Flag)m_lib.resolve("Get_Color_Camera_Task_Load_Flag");
    if (fun)
    {
         ret =fun(class_index,task_Index);

    }else
    {
        QMessageBox::information(NULL,"提示","获取libtaskparse.so中Get_Color_Camera_Task_Load_Flag函数名失败!");
        ret = 0;
    }
    return ret;
}
//获取任务的加速器模块数量
int LibTaskXMLParse::Get_Task_Acce_Common_Module_Num(int class_index, int task_Index)
{
    int ret = 0;
    typedef int (*Fun_Get_Module_Num)(int,int); //定义函数指针，以备调用
    Fun_Get_Module_Num fun=(Fun_Get_Module_Num)m_lib.resolve("Get_Task_Acce_Common_Module_Num");
    if (fun)
    {
        ret =fun(class_index,task_Index);

    }else
    {
        QMessageBox::information(NULL,"提示","获取libtaskparse.so中Get_Classify_Task_ID函数名失败!");
        ret = 0;
    }
    return ret;
}
//加速模块标志
int LibTaskXMLParse::Get_Task_Acce_Common_Module_Flag(int class_index, int task_Index, int Module_Index)
{
    int ret = 0;
    typedef int (*Fun_Get_Module_Flag)(int ,int, int);//定义函数指针，以备调用
    Fun_Get_Module_Flag fun=(Fun_Get_Module_Flag)m_lib.resolve("Get_Task_Acce_Common_Module_Flag");
    if (fun)
    {
        ret = fun(class_index,task_Index,Module_Index);

    }else
    {
        QMessageBox::information(NULL,"提示","获取libtaskparse.so中Get_Task_Acce_Common_Module_Flag函数名失败!");
    }
    return ret;
}
//关联定位模块
int LibTaskXMLParse::Get_Task_Link_Module_Load_Flag(int class_index, int task_Index)
{
    int ret = 0;
    typedef int (*Fun_Get_Classify_Task_ID)(int,int); //定义函数指针，以备调用
    Fun_Get_Classify_Task_ID fun=(Fun_Get_Classify_Task_ID)m_lib.resolve("Get_Task_Link_Module_Load_Flag");
    if (fun)
    {
         ret =fun(class_index,task_Index);

    }else
    {
        QMessageBox::information(NULL,"提示","获取libtaskparse.so中Get_Classify_Task_ID函数名失败!");
        ret = 0;
    }
    return ret;
}
int LibTaskXMLParse::Get_Task_Template_Flag(int class_index, int task_Index)
{
    int ret = 0;
    typedef int (*Fun_Get_Task_Template_Flag)(int,int); //定义函数指针，以备调用
    Fun_Get_Task_Template_Flag fun=(Fun_Get_Task_Template_Flag)m_lib.resolve("Get_Task_Template_Flag");
    if (fun)
    {
         ret =fun(class_index,task_Index);

    }else
    {
        QMessageBox::information(NULL,"提示","获取libtaskparse.so中Get_Task_Template_Flag函数名失败!");
        ret = 0;
    }
    return ret;
}

/**
 * @brief 获取任务说明
 * @param class_index:数组下标,小于任务类数量; task_Index:数组下标,小于任务类的任务数量; explain[1024]:任务说明
 * @return -1: 参数越界, 获取失败; 1：获取成功
 * @author <th>
 * @note
 */
QString LibTaskXMLParse::Get_Task_Explain(int class_index, int task_Index)
{
    QString strRet = "";
    char buf[1024];
    memset(buf,'\0',sizeof(buf));
    int ret = 0;
    typedef int (*Fun_Get_Task_Explain)(int,int,char *);
    Fun_Get_Task_Explain fun=(Fun_Get_Task_Explain)m_lib.resolve("Get_Task_Explain");
    if (fun)
    {
         ret =fun(class_index,task_Index,buf);
         if(ret ==1)
         {
             strRet = QString::fromUtf8(buf);
         }
    }else
    {
        QMessageBox::information(NULL,"提示","获取libtaskparse.so中Get_Task_Explain函数名失败!");
        strRet ="";
    }
    return strRet;
}

/**
 * @brief 获取任务类的说明
 * @param index:数组下标,小于任务类数量;explain[512]:任务类的说明
 * @return -1: 参数越界, 获取失败; 1：获取成功
 * @author <th>
 * @note
 */
QString LibTaskXMLParse::Get_Classify_Explain(int index)
{
    QString strRet = "";
    char buf[512];
    memset(buf,'\0',sizeof(buf));
    int ret = 0;
    typedef int (*Fun_Get_Classify_Explain)(int,char *); //定义函数指针，以备调用
    Fun_Get_Classify_Explain fun=(Fun_Get_Classify_Explain)m_lib.resolve("Get_Classify_Explain");
    if (fun)
    {
         ret =fun(index,buf);
         if(ret == 1)
         {
             strRet = QString::fromUtf8(buf);
         }
    }else
    {
        QMessageBox::information(NULL,"提示","获取libtaskparse.so中Get_Classify_Explain函数名失败!");
        strRet = "";
    }
    return strRet;
}

void LibTaskXMLParse::InitTaskXML(QString strPath)
{
    int ret = 0;
    int i= 0;
    int j = 0;
    int cameraType = 1;
    cameraType = Get_HWC_Color_Type();
    //ret = IniLib("./lib/sszn/libtaskparse.so");
    ret = IniLib(strPath);
    if(ret == 1)
    {
        ret = lib_UI_Data_Init();
        if(ret ==1)
        {

             int num = Get_Task_Classify_Num();

             if(num > 0)
             {

                 for(i = 0;i<num;i++)
                 {

                    QString strInfo = Get_Classify_Explain(i);
                    QString strClassName = Get_Classify_Name(i);
                    QString strClassIcon = Get_Classify_Icon_Path(i);
                    //ToolTypeInit(strClassName,strClassIcon);
                    GlobalParameter::m_vt_className.append(strClassName);
                    GlobalParameter::m_vt_classIcon.append(strClassIcon);
                    GlobalParameter::m_vt_classInfo.append(strInfo);

                    int taskDetailNum = Get_Classify_Task_Num(i);

                    if(taskDetailNum > 0)
                    {

                        QVector<int>vt_taskid;
                        QVector<QString>vt_taskDetail;
                        QVector<QString>vt_task_lib;
                        QVector<QString>vt_task_icon;
                        QVector<QString>vt_fun_lib;

                        int flag;
                        for(j= 0;j<taskDetailNum;j++)
                        {

                            if(cameraType ==1) //彩色
                            {
                                flag = Get_Color_Camera_Task_Load_Flag(i, j);
                            }else
                            {
                                flag = Get_Black_Camera_Task_Load_Flag(i,j);
                            }

                            if(flag == 0)
                                continue;

                            int taskId = Get_Classify_Task_ID(i,j);
                            vt_taskid.append(taskId);
                            QString strTaskDetailName = Get_Classify_Task_Name(i,j);
                            vt_taskDetail.append(strTaskDetailName);
                            QString strTask = Get_UI_Library_Name(i,j);
                            vt_task_lib.append(strTask);
                            QString strIocn = Get_Task_Icon_Path(i,j);
                            vt_task_icon.append(strIocn);
                            //ToolDetailInit(strTaskDetailName,strIocn);
                            QString strFunLib = Get_Function_Library_Name(i,j);
                            vt_fun_lib.append(strFunLib);
                            int moduleNum = Get_Task_Acce_Common_Module_Num(i,j);
                            QVector<int>vt_pre_flag;
                            for(int k =0; k< moduleNum;k++)
                            {
                                int moduleFlag = Get_Task_Acce_Common_Module_Flag(i,j,k);
                                vt_pre_flag.append(moduleFlag);
                            }

                            int linkFlag = Get_Task_Link_Module_Load_Flag(i,j);
                            int iTemplateFlag = Get_Task_Template_Flag(i,j);
                            QString strDetailInfo = Get_Task_Explain(i,j);
                            GlobalParameter::m_ID_LibName_hash.insert(taskId,strTask);
                            GlobalParameter::m_tool_name_hash.insert(taskId,strTaskDetailName);
                            GlobalParameter::m_tool_Icon_hash.insert(taskId,strIocn);
                            GlobalParameter::m_tool_FunLib_hash.insert(taskId,strFunLib);
                            GlobalParameter::m_pre_num.insert(taskId,moduleNum);
                            GlobalParameter::m_pre_value.insert(taskId,vt_pre_flag);
                            GlobalParameter::m_link_flag.insert(taskId,linkFlag);
                            GlobalParameter::m_template_flag.insert(taskId,iTemplateFlag);
                            GlobalParameter::m_tool_detail_info.insert(taskId,strDetailInfo);

                        }

                        GlobalParameter::m_vt_task_id.append(vt_taskid);
                        GlobalParameter::m_vt_tool_detail_name.append(vt_taskDetail);
                        GlobalParameter::m_vt_tool_Lib_icon.append(vt_task_icon);
                        GlobalParameter::m_vt_tool_Lib_path.append(vt_task_lib);
                        GlobalParameter::m_vt_tool_fun_detail_name.append(vt_fun_lib);
                    }

                 }

             }

        }

    }
}

QString LibTaskXMLParse::FindUILibName(int key)
{
    return GlobalParameter::m_ID_LibName_hash.value(key);
}
QString LibTaskXMLParse::FindToolName(int key)
{
    return GlobalParameter::m_tool_name_hash.value(key);
}



