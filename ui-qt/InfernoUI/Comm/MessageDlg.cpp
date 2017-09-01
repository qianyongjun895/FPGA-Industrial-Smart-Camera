#include "MessageDlg.h"
#include "ui_MessageDlg.h"

MessageDlg::MessageDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MessageDlg)
{
    ui->setupUi(this);
}

MessageDlg::~MessageDlg()
{
    delete ui;
}

void MessageDlg::on_btnOk_clicked()
{
    QDialog::accept();
}
void MessageDlg::SetMessage(QString strMess)
{
    ui->labelInfo->setText(strMess);
}
