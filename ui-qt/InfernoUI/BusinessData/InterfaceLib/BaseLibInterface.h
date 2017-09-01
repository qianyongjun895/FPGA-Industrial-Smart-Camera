#ifndef BASELIBINTERFACE_H
#define BASELIBINTERFACE_H
#include <QString>
#include <QLibrary>

class BaseLibInterface
{
public:
    BaseLibInterface();
    ~BaseLibInterface();
    /**
     * @brief IniLib
     * @param strName 控件lib路径
     * @return 返回1 成功 0失败
     * @author szj
     * @date 2017/05/18
     * @note 初始化lib
     */
    int IniLib(QString strName);
public:
    QString m_strLib;
    QLibrary m_lib;

};

#endif // BASELIBINTERFACE_H
