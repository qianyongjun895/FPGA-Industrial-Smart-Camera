#ifndef GLOBALPARAMETER_H
#define GLOBALPARAMETER_H
#include <QVector>
#include <QHash>
#include <QString>
#include "BusinessData/InterfaceLib/LibTaskFun.h"
#include "BusinessData/InterfaceLib/LibInitCamera.h"
class GlobalParameter
{
public:
    GlobalParameter();
    static int g_login;
    static int g_user_mode; // 0：普通用户模式 1:开发者模式
    static QVector<QString>m_vt_tool_type_info;//任务分类说明
    static QVector<QVector<QString> >m_vt_tool_Lib_path; //任务lib路径
    static QVector<QVector<QString> >m_vt_tool_Lib_icon; //任务图标路径
    static QVector<QVector<int> >m_vt_task_id;//任务id
    static QVector<QVector<QString> >m_vt_tool_detail_info; //任务详细说明
    static QVector<QVector<QString> >m_vt_tool_detail_name; //任务详细名称
    static QVector<QVector<QString> >m_vt_tool_fun_detail_name;//任务中需要用的dll用来初始数据

    static QVector<QVector<int> >m_vt_preModule_NUM;
    static QVector<QVector<int> >m_vt_preModule_Flag;
    static QVector<QVector<int> >m_vt_Link_Module_flag;

    static QVector<QString>m_vt_className;//工具集合名称(如定位)
    static QVector<QString>m_vt_classIcon;//工具集合图标()
    static QVector<QString>m_vt_classInfo;//工具集合说明
    static QHash<int,QString>m_ID_LibName_hash;
    static QHash<int,QString>m_tool_name_hash;
    static QHash<int,QString>m_tool_Icon_hash;
    static QHash<int,QString>m_tool_FunLib_hash;

    static QHash<int,int>m_pre_num;
    static QHash<int,QVector<int> >m_pre_value;
    static QHash<int,int>m_link_flag;
    static QHash<int,int>m_template_flag;
    static QHash<int,QString>m_tool_detail_info;
    static QHash<int,int>m_area_select_state;
    static LibTaskFun g_libTaskFun;
    static LibInitCamera g_lib_zynq;
};

#endif // GLOBALPARAMETER_H
