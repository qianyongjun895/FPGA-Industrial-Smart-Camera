#ifndef FRMINPUTKEYBOARD_H
#define FRMINPUTKEYBOARD_H

#include "frminputkeyboard_global.h"
#include <QDialog>
#include <stdbool.h>

class FRMINPUTKEYBOARDSHARED_EXPORT FrmInputKeyBoard
{

public:
    FrmInputKeyBoard();
};
extern "C" Q_DECL_EXPORT QDialog* GetKeyBoardDialog();
extern "C" Q_DECL_EXPORT QString GetInputString();
extern "C" Q_DECL_EXPORT void SetInputString(QString str);

extern "C" Q_DECL_EXPORT QDialog* GetNumKeyBoardDialog();
extern "C" QString GetNum();
extern "C" void SetNum(QString str_Num);
extern "C" void SetRangeEnvBtn();
extern "C" void SetRangeInput(QString max, QString min, int flag);//

extern "C" QString GetRangeNum();
extern "C" Q_DECL_EXPORT void SetNaturalNumberInputMode(bool b_value);
extern "C" Q_DECL_EXPORT void SetOldNum(QString str_Num);
extern "C" Q_DECL_EXPORT void InputIp();
extern "C" Q_DECL_EXPORT void SetInputObj(QObject *w);
extern "C" Q_DECL_EXPORT void PassWordInput();

#endif // FRMINPUTKEYBOARD_H
