#ifndef KEYBOARDLIB_H
#define KEYBOARDLIB_H
#include <QWidget>
#include <QDialog>
#include "BaseLibInterface.h"


typedef QString (*Fun_GetInputString)();

class KeyBoardLib :public BaseLibInterface
{
public:
    KeyBoardLib();
    ~KeyBoardLib();
    QDialog* GetKeyBoardDialog();
    QString GetInputString();
    void SetInputString(QString str);
    QDialog* GetNumKeyBoardDialog();
    QString GetNum();
    void SetNum(QString str_Num);
    void SetRangeEnvBtn();
    void SetRangeInput(QString max, QString min, int flag);//
    QString GetRangeNum();
    void SetNaturalNumberInputMode(bool b_value);
    void SetOldNum(QString str_Num);
    void InputIp();
    void SetInputObj(QObject *w);
    void PassWordInput();
private:
    QDialog *m_dlg;
    QDialog *m_Num_dlg;
};

#endif // KEYBOARDLIB_H
