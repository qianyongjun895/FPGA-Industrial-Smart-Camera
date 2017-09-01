/**
  * @file  [LibTaskXMLParse.h]
  * @brief
  * @author  <szj>
  * @date  <2017/05/15>
  * @version  <1.0>
  * @note
  * detailed  description
  */
#ifndef LIBTASKXMLPARSE_H
#define LIBTASKXMLPARSE_H
//#include <QLibrary>
#include "BaseLibInterface.h"
#include <QVector>
#include <QHash>
/**
  * @class  <LibTaskXMLParse>  [LibTaskXMLParse.h]  [LibTaskXMLParse]
  * @brief  工具dll访问类
  * @author  <szj>
  * @note
  * detailed  description
  */
class LibTaskXMLParse :public BaseLibInterface
{
public:
    LibTaskXMLParse();
    ~LibTaskXMLParse();
    /**
     * @brief IniLib
     * @param strName 控件lib路径
     * @return 返回1 成功 0失败
     * @author szj
     * @date 2017/05/08
     * @note 初始化lib
     */
    //int IniLib(QString strName);
    /**
     * @brief lib_UI_Data_Init
     * @return 1返回成功，0返回失败
     * @author szj
     * @date 2017/05/17
     * @note 初始化xml
     */
    int lib_UI_Data_Init();
    /**
     * @brief Get_Task_Classify_Num
     * @return 1返回成功，0返回失败
     * @author szj
     * @date 2017/05/17
     * @note 获取任务类数量
     */
    int Get_Task_Classify_Num();
    /**
     * @brief Get_Classify_Name
     * @param index 数组下标
     * @return 返回任务汇总名称
     * @author szj
     * @date 2017/05/17
     * @note 获取任务类名称
     */
    QString  Get_Classify_Name(int index);
    /**
     * @brief Get_Classify_Icon_Path
     * @param index
     * @return 返回任务汇总图标路径
     * @author szj
     * @date 2017/05/17
     * @note 获取任务汇总图标路径
     */
    QString Get_Classify_Icon_Path(int index);
    /**
     * @brief 获取任务类的任务数量
     * @param index:数组下标,小于任务类数量;
     * @return -1:数组下标即index越界; 其他:任务类的任务数量
     * @author <szj>
     * @date 2017/05/17
     * @note
     */
    int Get_Classify_Task_Num(int index);

    /**
     * @brief 获取任务功能对应的任务ID
     * @param class_index:数组下标,小于任务类数量; task_Index:数组下标,小于任务类的任务数量
     * @return -1:数组下标即index越界; 其他:任务ID
     * @author <szj>
     * @date 2017/05/17
     * @note
     */
    int Get_Classify_Task_ID(int class_index, int task_Index);

    /**
     * @brief 获取任务名字符串
     * @param index:数组下标,小于任务类数量;task_Index:数组下标,小于任务类的任务数量;
     * @return
     * @author <szj>
     * @date 2017/05/17
     * @note 如果taskName为NULL,表示数组下标即index越界。
     */
    QString Get_Classify_Task_Name(int class_index, int task_Index);

    /**
     * @brief 获取任务对应的ui库的路径
     * @param index:数组下标,小于任务类数量;task_Index:数组下标,小于任务类的任务数量;
     * @return
     * @author <th>
     * @date 2017/05/17
     * @note 如果LibraryName为NULL,表示数组下标即index越界。
     */
    QString Get_UI_Library_Name(int class_index, int task_Index);

    /**
     * @brief 获取任务对应的Icon路径
     * @param index:数组下标,小于任务类数量;task_Index:数组下标,小于任务类的任务数量;
     * @return
     * @author <th>
     * @date 2017/05/17
     * @note 如果IconPath为NULL,表示数组下标即index越界。
     */
    QString Get_Task_Icon_Path(int class_index, int task_Index);
    /**
     * @brief 获取任务对应的Fun库的路径
     * @param index:数组下标,小于任务类数量;task_Index:数组下标,小于任务类的任务数量;
     * @return
     * @author <th>
     * @date 2017/05/17
     * @note 如果IconPath为NULL,表示数组下标即index越界。
     */
     QString Get_Function_Library_Name(int class_index, int task_Index);
    /**
     * @brief LibTaskXMLParse::IniTaskXML
     * @param strPath
     * @return
     * @author <th>
     * @date 2017/05/20
     * @note 解析xml里的图标，任务名，taskID，调用lib名
     */
    void InitTaskXML(QString strPath);
    QString FindUILibName(int key);
    QString FindToolName(int key);

    int Get_Black_Camera_Task_Load_Flag(int class_index, int task_Index);
    int Get_Color_Camera_Task_Load_Flag(int class_index, int task_Index);
    /**
     * @brief 获取任务的加速器模块数量
     * @param class_index:数组下标,小于任务类数量; task_Index:数组下标,小于任务类的任务数量
     * @return -1: 参数越界, 获取失败; 其他：任务的加速器模块数量
     * @author <th>
     * @note
     */
    int Get_Task_Acce_Common_Module_Num(int class_index, int task_Index);

    /**
     * @brief 获取任务的加速器模块标志
     * @param class_index:数组下标,小于任务类数量; task_Index:数组下标,小于任务类的任务数量; Module_Index:加速器数组下标,小于任务的加速器模块数量
     * @return -1: 参数越界, 获取失败; 其他：加速器模块标志
     * @author <th>
     * @note
     */
    int Get_Task_Acce_Common_Module_Flag(int class_index, int task_Index, int Module_Index);

    //关联定位模块
    int Get_Task_Link_Module_Load_Flag(int class_index, int task_Index);
    int Get_Task_Template_Flag(int class_index, int task_Index);

    /**
     * @brief 获取任务说明
     * @param class_index:数组下标,小于任务类数量; task_Index:数组下标,小于任务类的任务数量; explain[1024]:任务说明
     * @return -1: 参数越界, 获取失败; 1：获取成功
     * @author <th>
     * @note
     */
    QString Get_Task_Explain(int class_index, int task_Index);

    /**
     * @brief 获取任务类的说明
     * @param index:数组下标,小于任务类数量;explain[512]:任务类的说明
     * @return -1: 参数越界, 获取失败; 1：获取成功
     * @author <th>
     * @note
     */
    QString Get_Classify_Explain(int index);

public:
     /*QVector<QString>m_vt_tool_type_info;//任务分类说明
     QVector<QVector<QString> >m_vt_tool_Lib_path; //任务lib路径
     QVector<QVector<QString> >m_vt_tool_Lib_icon; //任务图标路径
     QVector<QVector<int> >m_vt_task_id;//任务id
     QVector<QVector<QString> >m_vt_tool_detail_info; //任务详细说明
     QVector<QVector<QString> >m_vt_tool_detail_name; //任务详细名称
     QVector<QVector<QString> >m_vt_tool_fun_detail_name;//任务中需要用的dll用来初始数据
     QVector<QString>m_vt_className;//工具集合名称(如定位)
     QVector<QString>m_vt_classIcon;//工具集合图标()
     QHash<int,QString>m_ID_LibName_hash;
     QHash<int,QString>m_tool_name_hash;*/
private:
    //QString m_strLib;
    //QLibrary m_lib;
};

#endif // LIBTASKXMLPARSE_H
