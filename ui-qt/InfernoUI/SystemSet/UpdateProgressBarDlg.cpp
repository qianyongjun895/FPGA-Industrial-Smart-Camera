#include "UpdateProgressBarDlg.h"
#include "ui_UpdateProgressBarDlg.h"

UpdateProgressBarDlg::UpdateProgressBarDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UpdateProgressBarDlg)
{
    ui->setupUi(this);
    ui->btnOk->setVisible(false);
}

UpdateProgressBarDlg::~UpdateProgressBarDlg()
{
    delete ui;
}
void UpdateProgressBarDlg::SetProgress(int process)
{
    if(process == 0 && ui->progressBar->value() < 99)
    {
        ui->label_Updating->setText(tr("正在升级，请勿掉电!"));
        ui->progressBar->setValue(ui->progressBar->value()+1);
    }else if(process == 1)
    {
        ui->label_Updating->setText(tr("升级成功，请掉电重启相机!"));
        ui->progressBar->setValue(100);
    }else
    {
        ui->label_Updating->setText(tr("升级失败!"));
        ui->btnOk->setVisible(true);
        ui->progressBar->setValue(100);
    }

}

void UpdateProgressBarDlg::on_btnOk_clicked()
{
    QDialog::accept();
}

void UpdateProgressBarDlg::taskPortSetProgress(int process)
{
    if(process == 0 && ui->progressBar->value() < 99)
    {
        ui->label_Updating->setText(tr("正在传输文件!"));
        ui->progressBar->setValue(ui->progressBar->value()+1);
    }else if(process == 1)
    {
        ui->label_Updating->setText(tr("文件传输成功!"));
        ui->btnOk->setVisible(true);
        ui->progressBar->setValue(100);
    }else
    {
        ui->label_Updating->setText(tr("文件传输失败!"));
        ui->btnOk->setVisible(true);
        ui->progressBar->setValue(100);
    }

}
