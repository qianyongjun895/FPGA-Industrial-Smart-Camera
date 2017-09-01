#include "LicenseInfo.h"
#include "ui_LicenseInfo.h"
#include "sszn_basic.h"
#include <cstdio>
#include <QMessageBox>

LicenseInfo::LicenseInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LicenseInfo)
{
    ui->setupUi(this);
    LincenseInfoInit();

    ui->stackedWidget->setCurrentIndex(1);
}

LicenseInfo::~LicenseInfo()
{
    delete ui;
}

void LicenseInfo::LincenseInfoInit()
{
    unsigned int regStatus = GetLicenseStatus();
    if (regStatus == 0)
    {
        ui->status->setText("未注册");
    }
    else if (regStatus == 1)
    {
        ui->status->setText("临时注册");

        unsigned expireDate = GetExpireDate();
        QString s_edate = QString::number(expireDate);
        s_edate.insert(4, "/");
        s_edate.insert(7, "/");
        ui->date->setText(s_edate);

        unsigned int remainDays = GetRemainDays();
        ui->days->setText(QString::number(remainDays));
    }
    else if (regStatus == 2)
    {
        ui->status->setText("永久注册");
    }

    unsigned int serialNumHigh, serialNumLow;
    unsigned int responseCodeHigh, responseCodeLow;

    GetSerialNumber(&serialNumHigh, &serialNumLow);
    GetResponseCode(&responseCodeHigh, &responseCodeLow);

    char buf[20] = {0};
    const char *pStr = buf;
    sprintf(buf, "%08X", serialNumHigh);
    QString tmpStrH(pStr);
    tmpStrH.insert(4," ");
    tmpStrH.insert(9," ");
    sprintf(buf, "%08X", serialNumLow);
    QString tmpStrL(pStr);
    tmpStrL.insert(4," ");
    ui->serial_num->setText(tmpStrH+tmpStrL);

    sprintf(buf, "%08X", responseCodeHigh);
    QString tmpStrH2(pStr);
    tmpStrH2.insert(4," ");
    tmpStrH2.insert(9," ");
    sprintf(buf, "%08X", responseCodeLow);
    QString tmpStrL2(pStr);
    tmpStrL2.insert(4," ");
    ui->response_code->setText(tmpStrH2+tmpStrL2);
}

void LicenseInfo::on_btnRegister_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void LicenseInfo::on_register_code_selectionChanged()
{
    QDialog *dlg = m_KeyBoardLib.GetKeyBoardDialog();
    m_KeyBoardLib.SetInputString(ui->register_code->text());
    int ret = dlg->exec();
    if(ret == QDialog::Accepted)
    {
        ui->register_code->setText(m_KeyBoardLib.GetInputString());
    }
}

void LicenseInfo::on_OK_clicked()
{
    if(ui->register_code->text().isEmpty())
    {
        QMessageBox::about(NULL,tr("presentation"),tr("请输入注册码"));
        return;
    }

    QString str = ui->register_code->text(); //QString转char *
    QByteArray ba = str.toLatin1();
    char *mm = ba.data();
    int ret = isLicenseRight(mm);
    if(ret == 0)
    {
        QMessageBox::about(NULL,tr("presentation"),tr("注册码错误，请重新输入！"));
        return;
    }

    ui->register_code->setText("");

    if(ret == 1)
    {
        ui->status->setText(tr("临时注册"));
    }
    else if(ret == 2)
    {
        ui->status->setText(tr("永久注册"));
    }

    emit LicensePass();

    LincenseInfoInit();
    ui->stackedWidget->setCurrentIndex(1);
}

void LicenseInfo::on_Cancel_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}
