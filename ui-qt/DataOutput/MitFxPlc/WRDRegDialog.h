#ifndef WRDREGDIALOG_H
#define WRDREGDIALOG_H

#include <QDialog>
#include <QLibrary>
#include <QHash>
#include "MitFxPlcGlobal.h"
#include "WRDRegItem.h"
namespace Ui {
class WRDRegDialog;
}
typedef QDialog* (*Fun_GetNumkeyBoardDlg)();
typedef QString (*Fun_GetNumString)();
class WRDRegDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WRDRegDialog(QWidget *parent = 0);
    ~WRDRegDialog();
    void IniData();

    void IniRegData();
    void GetRegData();
    void SetDlgType(int type){Dlg_Type = type;}
    void SetDataListIndex(int List_Index);
    void LoadKeyBoardLib();
    void NumKeyBoardDlg(QObject *watched, QEvent *event, int Min_value, int Max_value);


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
    Ui::WRDRegDialog *ui;
    QLibrary m_keyBoard_Lib;
    QDialog *Numkey;
    int Dlg_Type;///<0:添加;1:查看
    int Ini_Flag;
    unsigned int Data_List_Index;
    PLC_WRITE_D_REG WR_D_Reg;

    int Page_cnt;
    int current_page;
    void AddMultiRegItem(WRDRegItem *item);
    void RegCofingChanged(int number, int coil_addr, int data_cnts);
    void CalcPageData();
    void RegSetChanged();
};

#endif // WRDREGDIALOG_H
