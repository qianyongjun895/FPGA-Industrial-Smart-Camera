#include "UpgradeWidget.h"
#include "ui_UpgradeWidget.h"
#include <cstdlib>
#include <QMessageBox>
#include "UpgradeStatusDialog.h"

UpgradeWidget::UpgradeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UpgradeWidget)
{
    ui->setupUi(this);
    qApp->installEventFilter(this);
    ui->radioButtonServer->setChecked(true);
}

UpgradeWidget::~UpgradeWidget()
{
    qApp->removeEventFilter(this);
    delete ui;
}

bool UpgradeWidget::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui->lineEdit_ServerIp)
    {
         if (event->type()==QEvent::MouseButtonPress)
         {
             QDialog *dlg = m_KeyBoardLib.GetNumKeyBoardDialog();
             m_KeyBoardLib.SetOldNum(((QLineEdit *)watched)->text());
             m_KeyBoardLib.InputIp();
             int ret = dlg->exec();
             if(ret == QDialog::Accepted)
             {
                 ((QLineEdit *)watched)->setText(m_KeyBoardLib.GetNum());
             }

         }
    }

    return QWidget::eventFilter(watched, event);
}

void UpgradeWidget::on_btnUpdate_clicked()
{
    if (ui->lineEdit_ServerIp->text().isEmpty())
    {
        QMessageBox::about(NULL, "about", tr("IP不能为空!"));
        return ;
    }
    QMessageBox::StandardButton rb = QMessageBox::question(NULL, \
                                                           "Update", \
                                                           "确定进行升级?", \
                                                           QMessageBox::Yes | QMessageBox::No, \
                                                           QMessageBox::No);
    if(rb == QMessageBox::No)
    {
          return ;
    }

    if (ui->checkBox_Del->isChecked())
    {
        system("/mnt/emmc4/Script/Shell/DeleteAllTaskFiles.sh");
    }

    if (ui->checkBox_CLeanBinFiles->isChecked())
    {
        system("echo yes > /mnt/emmc3/softwareUpdate/cleanBinFilesFlag");
    }
    else
    {
        system("echo no > /mnt/emmc3/softwareUpdate/cleanBinFilesFlag");
    }

    QString cmdStr("/mnt/emmc4/Script/Shell/upgrade.sh ");
    cmdStr += ui->lineEdit_ServerIp->text() + " &";
    QByteArray ba = cmdStr.toLatin1();
    char *cmd = ba.data();
    system(cmd);
    UpgradeStatusDialog iDlg;
    iDlg.exec();
}

void UpgradeWidget::on_radioButtonUDisk_clicked()
{
    ui->labelTitleServerIP->setEnabled(false);
    ui->lineEdit_ServerIp->setEnabled(false);

}

void UpgradeWidget::on_radioButtonServer_clicked()
{
    ui->labelTitleServerIP->setEnabled(true);
    ui->lineEdit_ServerIp->setEnabled(true);
}
