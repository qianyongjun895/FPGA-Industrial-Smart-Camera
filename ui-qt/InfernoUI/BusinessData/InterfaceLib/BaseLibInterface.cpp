#include "BaseLibInterface.h"
#include <QMessageBox>
#include <qdebug.h>

BaseLibInterface::BaseLibInterface()
{

}
BaseLibInterface::~BaseLibInterface()
{
    if(m_lib.isLoaded())
        m_lib.unload();
}
int BaseLibInterface::IniLib(QString strName)
{
    this->m_strLib = strName;
    m_lib.setFileName(m_strLib);

    if(m_lib.load())
    {
        return 1;
    }else
    {
        QMessageBox::information(NULL,"提示","加载DLL("+m_strLib+")失败!");
        qDebug()<<"BaseLibInterface::IniLib error=="<<m_lib.errorString();
        return 0;
    }
}
