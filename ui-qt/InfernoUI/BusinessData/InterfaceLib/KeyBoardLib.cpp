#include "KeyBoardLib.h"
#include <QMessageBox>
KeyBoardLib::KeyBoardLib()
{
    m_dlg = NULL;
    m_Num_dlg = NULL;
    this->IniLib("libFrmInputKeyBoard.so");
}
KeyBoardLib::~KeyBoardLib()
{
    if(m_dlg !=NULL)
    {
        delete m_dlg;
        m_dlg = NULL;
    }
    if(m_Num_dlg !=NULL)
    {
        delete m_Num_dlg;
        m_Num_dlg = NULL;
    }
}
QDialog* KeyBoardLib::GetKeyBoardDialog()
{
    typedef QDialog* (*Fun_GetkeyBoardDlg)();

    Fun_GetkeyBoardDlg fun=(Fun_GetkeyBoardDlg)m_lib.resolve("GetKeyBoardDialog");
    if (fun)
    {
        m_dlg=fun();
    }else
    {
        QMessageBox::information(NULL,"提示","获取"+m_strLib+"中GetKeyBoardDialog函数名失败!");
        m_dlg = NULL;
    }

    return m_dlg;
}
QString KeyBoardLib::GetInputString()
{
   QString strRet;
   typedef QString (*Fun_GetInputString)();
   Fun_GetInputString fun=(Fun_GetInputString)m_lib.resolve("GetInputString");

   if (fun)
   {
       strRet=fun();
   }else
   {
       QMessageBox::information(NULL,"提示","获取"+m_strLib+"中GetInputString函数名失败!");
       strRet = "";
   }
    return strRet;
}
void KeyBoardLib::SetInputString(QString str)
{
    typedef void (*Fun_SetInputString)(QString);

    Fun_SetInputString fun=(Fun_SetInputString)m_lib.resolve("SetInputString");

    if (fun)
    {
        fun(str);
    }else
    {
        QMessageBox::information(NULL,"提示","获取"+m_strLib+"中SetInputString函数名失败!");

    }
}
QDialog* KeyBoardLib::GetNumKeyBoardDialog()
{
    typedef QDialog* (*Fun_GetNumKeyBoardDialog)();

    Fun_GetNumKeyBoardDialog fun=(Fun_GetNumKeyBoardDialog)m_lib.resolve("GetNumKeyBoardDialog");
    if (fun)
    {
        m_Num_dlg=fun();
    }else
    {
        QMessageBox::information(NULL,"提示","获取"+m_strLib+"中GetNumKeyBoardDialog函数名失败!");
        m_Num_dlg = NULL;
    }
    return m_Num_dlg;
}
QString KeyBoardLib::GetNum()
{
    QString strRet = "";
    typedef QString (*Fun_GetNum)();

    Fun_GetNum fun=(Fun_GetNum)m_lib.resolve("GetNum");
    if (fun)
    {
        strRet=fun();
    }else
    {
        QMessageBox::information(NULL,"提示","获取"+m_strLib+"中GetNum函数名失败!");
        strRet = "";
    }
    return strRet;
}
void KeyBoardLib::SetNum(QString str_Num)
{

    typedef void  (*Fun_SetNum)(QString);

    Fun_SetNum fun=(Fun_SetNum)m_lib.resolve("SetNum");
    if (fun)
    {
       fun(str_Num);
    }else
    {
        QMessageBox::information(NULL,"提示","获取"+m_strLib+"中SetNum函数名失败!");
    }
}
void KeyBoardLib::SetRangeEnvBtn()
{
    typedef void  (*Fun_SetRangeEnvBtn)();

    Fun_SetRangeEnvBtn fun=(Fun_SetRangeEnvBtn)m_lib.resolve("SetRangeEnvBtn");
    if (fun)
    {
       fun();
    }else
    {
        QMessageBox::information(NULL,"提示","获取"+m_strLib+"中SetRangeEnvBtn函数名失败!");
    }
}
void KeyBoardLib::SetRangeInput(QString max, QString min, int flag)
{
    typedef void  (*Fun_SetRangeInput)(QString,QString,int);

    Fun_SetRangeInput fun=(Fun_SetRangeInput)m_lib.resolve("SetRangeInput");
    if (fun)
    {
       fun(max,min,flag);

    }else
    {
        QMessageBox::information(NULL,"提示","获取"+m_strLib+"中SetRangeInput函数名失败!");
    }
}
QString KeyBoardLib::GetRangeNum()
{
    QString strRet = "";
    typedef QString  (*Fun_GetRangeNum)();

    Fun_GetRangeNum fun=(Fun_GetRangeNum)m_lib.resolve("GetRangeNum");
    if (fun)
    {
       strRet = fun();
    }else
    {
        QMessageBox::information(NULL,"提示","获取"+m_strLib+"中SetRangeEnvBtn函数名失败!");
        strRet = "";
    }
    return strRet;
}
void KeyBoardLib::SetNaturalNumberInputMode(bool b_value)
{
    typedef void  (*Fun_SetNaturalNumberInputMode)(bool);

    Fun_SetNaturalNumberInputMode fun=(Fun_SetNaturalNumberInputMode)m_lib.resolve("SetNaturalNumberInputMode");
    if (fun)
    {
       fun(b_value);
    }else
    {
        QMessageBox::information(NULL,"提示","获取"+m_strLib+"中SetNaturalNumberInputMode函数名失败!");
    }
}
void KeyBoardLib::SetOldNum(QString str_Num)
{
    typedef void  (*Fun_SetOldNum)(QString);

    Fun_SetOldNum fun=(Fun_SetOldNum)m_lib.resolve("SetOldNum");
    if (fun)
    {
       fun(str_Num);
    }else
    {
        QMessageBox::information(NULL,"提示","获取"+m_strLib+"中SetOldNum函数名失败!");
    }
}
void KeyBoardLib::InputIp()
{
    typedef void  (*Fun_InputIp)();

    Fun_InputIp fun=(Fun_InputIp)m_lib.resolve("InputIp");
    if (fun)
    {
       fun();
    }else
    {
        QMessageBox::information(NULL,"提示","获取"+m_strLib+"中InputIp函数名失败!");
    }
}
void KeyBoardLib::SetInputObj(QObject *w)
{
    typedef void  (*Fun_SetInputObj)(QObject *);

    Fun_SetInputObj fun=(Fun_SetInputObj)m_lib.resolve("SetInputObj");
    if (fun)
    {
       fun(w);
    }else
    {
        QMessageBox::information(NULL,"提示","获取"+m_strLib+"中SetInputObj函数名失败!");
    }
}
void KeyBoardLib::PassWordInput()
{
    typedef void  (*Fun_PassWordInput)();

    Fun_PassWordInput fun=(Fun_PassWordInput)m_lib.resolve("PassWordInput");
    if (fun)
    {
       fun();
    }else
    {
        QMessageBox::information(NULL,"提示","获取"+m_strLib+"中PassWordInput函数名失败!");
    }
}
