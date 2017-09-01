#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "BusinessData/InterfaceLib/KeyBoardLib.h"
namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

private slots:
    void on_btnLogin_clicked();

    void on_btnQuit_clicked();

    void on_checkBox_PswVisible_clicked();

protected:
    bool eventFilter(QObject *watched, QEvent *event);

private:
    Ui::LoginDialog *ui;
    KeyBoardLib m_KeyBoardLib;
};

#endif // LOGINDIALOG_H
