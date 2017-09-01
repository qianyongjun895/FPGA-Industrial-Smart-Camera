#ifndef WRMREGDIALOG_H
#define WRMREGDIALOG_H

#include <QDialog>
#include <QLibrary>
#include "WRMRegItem.h"
#include "MitFxPlcGlobal.h"
namespace Ui {
class WRMRegDialog;
}
typedef QDialog* (*Fun_GetNumkeyBoardDlg)();
typedef QString (*Fun_GetNumString)();
class WRMRegDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WRMRegDialog(QWidget *parent = 0);
    ~WRMRegDialog();

    void SetToolType(int tool);
    void SetCurrentIndex(int index);
    void IniWRMRegData();
    void GetWRMRegData();

protected slots:
    bool eventFilter(QObject *watched, QEvent *event);
private slots:
    void on_lineEdit_StartAddr_textChanged(const QString &arg1);

    void on_lineEdit_Length_textChanged(const QString &arg1);

    void on_btnPrePage_clicked();

    void on_btnNextPage_clicked();

    void on_btnOk_clicked();

    void on_btnquit_clicked();

private:
    Ui::WRMRegDialog *ui;
    QLibrary m_keyBoard_Lib;
    QDialog *Numkey;
    int Current_index;
    int tool_type;
    int Page_cnt;
    int current_page;
    int show_type;///<0:添加; 1:详细

    PLC_READ_M_REG RD_M_Reg;
    PLC_WRITE_M_REG WR_M_Reg;

    void IniData();
    void WRMRegSetChange();
    void WRMRegCofingChanged(int number, int reg_addr, int data_cnts);
    void AddWRRegItem(WRMRegItem *item);
    void CalcPageData();
    void LoadKeyBoardLib();
    void NumKeyBoardDlg(QObject *watched, QEvent *event, int Min_value, int Max_value);
};

#endif // WRMREGDIALOG_H
