#ifndef WRMULTICOILDIALOG_H
#define WRMULTICOILDIALOG_H

#include <QDialog>
#include <QLibrary>
#include "MultiCoilItem.h"
#include "ModbusGlobal.h"
namespace Ui {
class WRMultiCoilDialog;
}

typedef QDialog* (*Fun_GetNumkeyBoardDlg)();
typedef QString (*Fun_GetNumString)();

class WRMultiCoilDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WRMultiCoilDialog(QWidget *parent = 0);
    ~WRMultiCoilDialog();

    void IniData();
    void SetDataListIndex(int List_Index);
    void LoadKeyBoardLib();
    void NumKeyBoardDlg(QObject *watched, QEvent *event, int Min_value, int Max_value);


    void CoilCofingChanged(int number, int coil_addr, int data_cnts);
    void AddMultiColiItem(MultiCoilItem *CoilItem);
    void IniMultiCoilData();
    void CalcPageData();
    void CoilSetChanged();
    void GetMultiCoilData();
    void SetModbusMode(int mode);
    void SetToolType(int tool);
protected:
    bool eventFilter(QObject *watched, QEvent *event);
private slots:

    void on_lineEdit_StartAddr_textChanged(const QString &arg1);

    void on_lineEdit_Length_textChanged(const QString &arg1);

    void on_btnPrePage_clicked();

    void on_btnNextPage_clicked();

    void on_btnOk_clicked();

    void on_btnquit_clicked();

private:
    Ui::WRMultiCoilDialog *ui;
    QLibrary m_keyBoard_Lib;
    QDialog *Numkey;
    int Ini_Flag;
    unsigned int Data_List_Index;
    int slave_or_host;
    int tool_type;
    int Page_cnt;
    int current_page;
    MBS_WR_COIL WR_Coil_Data;
    MBS_WR_DISCRETE WR_Discrete_Data;

    MBH_RD_COILS H_RD_Coil_Data;
    MBH_WR_COILS H_WR_Coil_Data;
    MBH_RD_DISCRETE H_RD_Discrete_Data;
    void IniSlaveWriteCoilData();
    void IniSlaveWriteDiscreteData();
    void IniHostReadCoilData();
    void IniHostWriteCoilData();
    void IniHostReadDiscreteData();
};

#endif // WRMULTICOILDIALOG_H
