#ifndef RDSINGLECOILDIALOG_H
#define RDSINGLECOILDIALOG_H

#include <QDialog>
#include <QLibrary>
namespace Ui {
class IntercomRDSingleCoilDialog;
}

typedef QDialog* (*Fun_GetNumkeyBoardDlg)();
typedef QString (*Fun_GetNumString)();

class IntercomRDSingleCoilDialog : public QDialog
{
    Q_OBJECT

public:
    explicit IntercomRDSingleCoilDialog(QWidget *parent = 0);
    ~IntercomRDSingleCoilDialog();
    void LoadKeyBoardLib();
    void NumKeyBoardDlg(QObject *watched, QEvent *event, int Min_value, int Max_value);

    void SetDataListIndex(unsigned int List_Index);
    void GetSingleCoilData();
    void IniSingleCoilData();
    void SetModbusMode(int mode);
    void SetToolType(int tool);
    void IniData();
protected:
    bool eventFilter(QObject *watched, QEvent *event);
private slots:
    void on_btn_Finished_clicked();

    void on_btn_Cancel_clicked();

private:
    Ui::IntercomRDSingleCoilDialog *ui;
    QLibrary m_keyBoard_Lib;
    QDialog *Numkey;
    unsigned int Data_List_Index;
    int slave_or_host;
    int tool_type;
};

#endif // RDSINGLECOILDIALOG_H
