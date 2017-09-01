#ifndef REGISTERIMAGEDLG_H
#define REGISTERIMAGEDLG_H

#include <QDialog>
#include "BusinessData/InterfaceLib/KeyBoardLib.h"
namespace Ui {
class RegisterImageDlg;
}

class RegisterImageDlg : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterImageDlg(QWidget *parent = 0);
    ~RegisterImageDlg();

private slots:
    void on_btnRegister_clicked();

    void on_btnDel_clicked();

    void on_btnQuit_clicked();



    void on_btnClear_clicked();

    void on_radioButtonSmall_clicked();

    void on_radioButtonBig_clicked();

protected:
    bool eventFilter(QObject *watched, QEvent *event);

private:
    Ui::RegisterImageDlg *ui;
    QString m_str_pic_path;
    void AddItemData(QString strName);
    int FindNameInTable(QString strName);
    void IniImageNameList();
    KeyBoardLib m_keyBoardLib;
};

#endif // REGISTERIMAGEDLG_H
