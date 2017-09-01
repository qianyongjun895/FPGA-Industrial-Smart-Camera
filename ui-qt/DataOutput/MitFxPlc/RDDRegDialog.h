#ifndef RDDREGDIALOG_H
#define RDDREGDIALOG_H

#include <QDialog>
#include <QLibrary>
#include "MitFxPlcGlobal.h"
#include <QHash>
namespace Ui {
class RDDRegDialog;
}
typedef QDialog* (*Fun_GetNumkeyBoardDlg)();
typedef QString (*Fun_GetNumString)();
class RDDRegDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RDDRegDialog(QWidget *parent = 0);
    ~RDDRegDialog();
    void LoadKeyBoardLib();
    void NumKeyBoardDlg(QObject *watched, QEvent *event, int Min_value, int Max_value);

    void SetToolType(int tool);
    void SetCurrentIndex(int index);
    void IniRDDRegData();
    void GetRDDRegData();
protected slots:
    bool eventFilter(QObject *watched, QEvent *event);
private slots:
    void on_btn_Finish_clicked();

    void on_btn_Cancel_clicked();

private:
    Ui::RDDRegDialog *ui;
    QLibrary m_keyBoard_Lib;
    QDialog *Numkey;
    QHash<QString, int>Data_type;
    PLC_READ_D_REG RD_D_Reg;
    int Current_index;
    int tool_type;
};

#endif // RDDREGDIALOG_H
