#include <qdebug.h>
#include "KeyBoard.h"

KeyBoard::KeyBoard()
{
    m_Numkey = NULL;
}
KeyBoard::~KeyBoard()
{
    if(m_Numkey !=NULL)
    {
        delete m_Numkey;
        m_Numkey = NULL;
    }

    if(m_keyBoard_Lib.isLoaded())
    {
        m_keyBoard_Lib.unload();
    }
}
void KeyBoard::LoadKeyBoardLib()
{
    if(m_keyBoard_Lib.isLoaded())
    {
        return;
    }
    m_keyBoard_Lib.setFileName("libFrmInputKeyBoard.so");
    if(m_keyBoard_Lib.load())
    {
        qDebug()<<"libFrmInputKeyBoard.so OK";
    }
    else
    {
        qDebug()<<"load libFrmInputKeyBoard.so fail"<<m_keyBoard_Lib.errorString();
    }
}
QDialog* KeyBoard::GetNumDlg()
{
    if(m_Numkey == NULL)
    {
        Fun_GetNumkeyBoardDlg GetNumKeyBoardDlg = (Fun_GetNumkeyBoardDlg)m_keyBoard_Lib.resolve("GetNumKeyBoardDialog");
        if(GetNumKeyBoardDlg)
        {
            m_Numkey = GetNumKeyBoardDlg();
        }
    }
    return m_Numkey;
}
void KeyBoard::SetNaturalNumberInputMode(bool bflag)
{
    if(m_Numkey !=NULL)
    {
        FunInputMode inputMode = (FunInputMode)m_keyBoard_Lib.resolve("SetNaturalNumberInputMode");
        if(inputMode)
        {
            inputMode(bflag);
        }
    }
}
QString KeyBoard::GetNum()
{
    QString str="";

    if(m_Numkey !=NULL)
    {
        Fun_GetNumString GetNumString = (Fun_GetNumString)m_keyBoard_Lib.resolve("GetNum");
        if(GetNumString)
        {
            str = GetNumString();
        }
    }

    return str;
}
