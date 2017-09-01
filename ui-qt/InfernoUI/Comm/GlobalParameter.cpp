#include "GlobalParameter.h"

int GlobalParameter::g_login = 0;
int GlobalParameter::g_user_mode = 0;
QVector<QString>GlobalParameter::m_vt_tool_type_info;//任务分类说明
QVector<QVector<QString> >GlobalParameter::m_vt_tool_Lib_path; //任务lib路径
QVector<QVector<QString> >GlobalParameter::m_vt_tool_Lib_icon; //任务图标路径
QVector<QVector<int> >GlobalParameter::m_vt_task_id;//任务id
QVector<QVector<QString> >GlobalParameter::m_vt_tool_detail_info; //任务详细说明
QVector<QVector<QString> >GlobalParameter::m_vt_tool_detail_name; //任务详细名称
QVector<QVector<QString> >GlobalParameter::m_vt_tool_fun_detail_name;//任务中需要用的dll用来初始数据
QHash<int,int>GlobalParameter::m_pre_num;
QHash<int,QVector<int> >GlobalParameter::m_pre_value;
QHash<int,int>GlobalParameter::m_link_flag;
QHash<int,int>GlobalParameter::m_template_flag;
QHash<int,QString>GlobalParameter::m_tool_detail_info;

QVector<QString>GlobalParameter::m_vt_className;//工具集合名称(如定位)
QVector<QString>GlobalParameter::m_vt_classIcon;//工具集合图标()
QVector<QString>GlobalParameter::m_vt_classInfo;//工具集合说明
QHash<int,QString>GlobalParameter::m_ID_LibName_hash;
QHash<int,QString>GlobalParameter::m_tool_name_hash;
QHash<int,QString>GlobalParameter::m_tool_Icon_hash;
QHash<int,QString>GlobalParameter::m_tool_FunLib_hash;
LibTaskFun GlobalParameter::g_libTaskFun;
LibInitCamera GlobalParameter::g_lib_zynq;
QHash<int,int>GlobalParameter::m_area_select_state;


GlobalParameter::GlobalParameter()
{

}
