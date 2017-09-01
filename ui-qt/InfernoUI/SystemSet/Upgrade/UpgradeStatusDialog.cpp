#include "UpgradeStatusDialog.h"
#include "ui_UpgradeStatusDialog.h"
#include <QFile>
#include <QString>
#include <QTextStream>

typedef enum {
    UPDATE_SUCCESS=0,
    UPDATE_FAIL,
    UPDATING,
    GET_FILE,
    GET_FILE_FAIL,
    GET_FILE_SUCCESS,
    TAR_FILE_ERR,
    UPDATE_STATUS_END
} UPDATE_STATUS;

UpgradeStatusDialog::UpgradeStatusDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UpgradeStatusDialog)
{
    ui->setupUi(this);
    ui->btnOK->hide();
    prgBarValue = 0;
    ui->progressBar->setRange(0,100);
    ui->progressBar->setValue(prgBarValue);
    updateTimer = new QTimer;
    connect(updateTimer, &QTimer::timeout, this, &UpgradeStatusDialog::updateTimerSlot);
    updateTimer->start(1000);
}

UpgradeStatusDialog::~UpgradeStatusDialog()
{
    if (updateTimer != NULL)
    {
        delete updateTimer;
        updateTimer = NULL;
    }
    delete ui;
}

void UpgradeStatusDialog::updateTimerSlot()
{
    QString updateStatus;
    QFile file("/mnt/emmc3/softwareUpdate/updateStatus");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    if (file.isOpen())
    {

        ++ prgBarValue;
        if (prgBarValue > 100)
        {
            prgBarValue = 100;
        }

        QTextStream in(&file);
        updateStatus = in.readAll();
        int status = updateStatus.toInt();
        switch (status) {
        case UPDATE_SUCCESS:
            prgBarValue = 100;
            updateTimer->stop();
            ui->labelUpdate->setText(tr("升级成功,掉电重启后生效!"));
            ui->progressBar->setValue(prgBarValue);
            ui->btnOK->show();
            break;
        case UPDATE_FAIL:
            prgBarValue = 100;
            updateTimer->stop();
            ui->labelUpdate->setText(tr("升级失败!"));
            ui->progressBar->setValue(prgBarValue);
            ui->btnOK->show();
            break;
        case UPDATING:
            ui->labelUpdate->setText(tr("升级中……"));
            ui->progressBar->setValue(prgBarValue);
            break;
        case GET_FILE:
            ui->labelUpdate->setText(tr("下载升级文件……"));
            ui->progressBar->setValue(prgBarValue);
            break;
        case GET_FILE_FAIL:
            prgBarValue = 100;
            updateTimer->stop();
            ui->labelUpdate->setText(tr("获取升级文件失败!"));
            ui->progressBar->setValue(prgBarValue);
            ui->btnOK->show();
            break;
        case GET_FILE_SUCCESS:
            ui->labelUpdate->setText(tr("获取升级文件成功，开始更新系统文件……"));
            ui->progressBar->setValue(prgBarValue);
            break;
        case TAR_FILE_ERR:
            prgBarValue = 100;
            updateTimer->stop();
            ui->labelUpdate->setText(tr("升级文件解析失败!"));
            ui->progressBar->setValue(prgBarValue);
            ui->btnOK->show();
            break;
        default:
            break;
        }
        file.close();
    }
}

void UpgradeStatusDialog::on_btnOK_clicked()
{
    this->close();
}
