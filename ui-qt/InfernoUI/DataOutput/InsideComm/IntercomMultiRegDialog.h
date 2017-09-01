#ifndef MULTIREGDIALOG_H
#define MULTIREGDIALOG_H

#include <QDialog>
#include <QLibrary>
//#include "ModbusGlobal.h"
#include <QHash>
#include "IntercomMultiRegItem.h"
#include "IntercomModbusGlobal.h"
namespace Ui {
class IntercomMultiRegDialog;
}

typedef QDialog* (*Fun_GetNumkeyBoardDlg)();
typedef QString (*Fun_GetNumString)();


class IntercomMultiRegDialog : public QDialog
{
    Q_OBJECT

public:
    explicit IntercomMultiRegDialog(QWidget *parent = 0);
    ~IntercomMultiRegDialog();

    void IniData();

    void IniRegData();
    void GetRegData();
    void SetDlgType(int type){Dlg_Type = type;}
    void SetDataListIndex(int List_Index);
    void LoadKeyBoardLib();
    void NumKeyBoardDlg(QObject *watched, QEvent *event, int Min_value, int Max_value);
    void SetModbusMode(int mode);
    void SetToolType(int tool);


protected:
    bool eventFilter(QObject *watched, QEvent *event);

private slots:
    void on_pushButton_pre_clicked();

    void on_pushButton_next_clicked();

    void on_lineEdit_StartAddr_textChanged(const QString &arg1);

    void on_lineEdit_Length_textChanged(const QString &arg1);

    void on_comboBox_DataType_currentIndexChanged(int index);

    void on_btn_Finish_clicked();

    void on_btn_Quit_clicked();

private:
    Ui::IntercomMultiRegDialog *ui;
    QLibrary m_keyBoard_Lib;
    QDialog *Numkey;
    int Dlg_Type;///<0:添加;1:查看
    int Ini_Flag;
    unsigned int Data_List_Index;
    int slave_or_host;
    int tool_type;

    int Page_cnt;
    int current_page;
    MBS_WR_HOLD_REG S_WR_Hold_Reg_Data;
    MBS_WR_INPUT_REG S_WR_Input_Reg_Data;

    MBH_WR_HOLD_REG H_WR_Hold_Reg_Data;

    void AddMultiRegItem(IntercomMultiRegItem *item);
    void RegCofingChanged(int number, int coil_addr, int data_cnts);
    void CalcPageData();
    void RegSetChanged();
};

#endif // MULTIREGDIALOG_H
