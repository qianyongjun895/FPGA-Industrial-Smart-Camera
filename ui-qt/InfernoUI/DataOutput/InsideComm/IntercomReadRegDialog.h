#ifndef READREGDIALOG_H
#define READREGDIALOG_H

#include <QDialog>
#include <QLibrary>
#include "ModbusGlobal.h"
#include <QHash>
#include "IntercomModbusGlobal.h"
namespace Ui {
class IntercomReadRegDialog;
}

typedef QDialog* (*Fun_GetNumkeyBoardDlg)();
typedef QString (*Fun_GetNumString)();

class IntercomReadRegDialog : public QDialog
{
    Q_OBJECT

public:
    explicit IntercomReadRegDialog(QWidget *parent = 0);
    ~IntercomReadRegDialog();

    void IniRegData();
    void GetRegData();

    void SetDataListIndex(int List_Index);
    void LoadKeyBoardLib();
    void NumKeyBoardDlg(QObject *watched, QEvent *event, int Min_value, int Max_value);

    void SetModbusMode(int mode);
    void SetToolType(int tool);
    void IniData();
protected:
    bool eventFilter(QObject *watched, QEvent *event);

private slots:
    void on_btn_Finish_clicked();

    void on_btn_Cancel_clicked();

private:
    Ui::IntercomReadRegDialog *ui;
    QHash<QString, int>Data_type;
    QLibrary m_keyBoard_Lib;
    QDialog *Numkey;
    unsigned int Data_List_Index;
    int slave_or_host;
    int tool_type;
    MBS_RD_HOLD_REG S_RD_Hold_Reg_Data;
    MBH_RD_HOLD_REG H_RD_Hold_Reg_Data;
    MBH_RD_INPUT_REG H_RD_Input_Reg_Data;
};

#endif // READREGDIALOG_H
