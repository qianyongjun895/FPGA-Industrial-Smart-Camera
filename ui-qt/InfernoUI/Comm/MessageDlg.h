#ifndef MESSAGEDLG_H
#define MESSAGEDLG_H

#include <QDialog>

namespace Ui {
class MessageDlg;
}

class MessageDlg : public QDialog
{
    Q_OBJECT

public:
    explicit MessageDlg(QWidget *parent = 0);
    ~MessageDlg();
    void SetMessage(QString strMess);
private slots:
    void on_btnOk_clicked();

private:
    Ui::MessageDlg *ui;
};

#endif // MESSAGEDLG_H
