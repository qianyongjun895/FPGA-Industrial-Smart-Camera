#include "FrmInputKeyBoard.h"
#include "KeyboardDlg.h"
#include "NumKeyBoard.h"
KeyboardDlg* dlg = NULL;
NumKeyBoard* Numdlg = NULL;
FrmInputKeyBoard::FrmInputKeyBoard()
{
}


QDialog* GetKeyBoardDialog()
{
    dlg = new KeyboardDlg;
    return dlg;
}

QString GetInputString()
{
    if(dlg != NULL)
        return dlg->GetInputString();
    else
        return "";
}

void SetInputString(QString str)
{
    if(dlg !=NULL)
        dlg->SetInputString(str);
}
void SetInputObj(QObject *w)
{
    if(dlg !=NULL)
        dlg->SetInputObj(w);
}
void PassWordInput()
{
    if(dlg !=NULL)
        dlg->PassWordInput();
}

QDialog* GetNumKeyBoardDialog()
{
    Numdlg = new NumKeyBoard;
    return Numdlg;
}

QString GetNum()
{
    if(Numdlg !=NULL)
        return Numdlg->GetNum();
    else
        return "";
}
void SetNaturalNumberInputMode(bool b_value)
{
    if(Numdlg !=NULL)
        Numdlg->SetNaturalNumberInputMode(b_value);
}
void SetNum(QString str_Num)
{
    if(Numdlg !=NULL)
        Numdlg->SetNum(str_Num);
}

void SetRangeEnvBtn()
{
    if(Numdlg !=NULL)
        Numdlg->ShowbtnRangeEn();
}

void SetRangeInput(QString max,QString min,int flag)
{
    if(Numdlg !=NULL)
    {
        Numdlg->RangeInput(max,min,flag);
        Numdlg->ShowbtnRangeEn();
    }
}

QString GetRangeNum()
{
    return Numdlg->GetRangeNum();
}
void SetOldNum(QString str_Num)
{
    return Numdlg->SetOldNum(str_Num);
}
void InputIp()
{
    return Numdlg->InputIp();
}

