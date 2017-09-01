#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <QLibrary>
#include <QDialog>
#include <stdbool.h>

typedef QDialog* (*Fun_GetNumkeyBoardDlg)();
typedef QString (*Fun_GetNumString)();
typedef void (*FunInputMode)(bool bflag);
class KeyBoard
{
public:


    KeyBoard();
    ~KeyBoard();
    void LoadKeyBoardLib();
    QDialog* GetNumDlg();
    void SetNaturalNumberInputMode(bool bflag);
    QString GetNum();
private:
    QLibrary m_keyBoard_Lib;
    QDialog* m_Numkey;
};

#endif // KEYBOARD_H
