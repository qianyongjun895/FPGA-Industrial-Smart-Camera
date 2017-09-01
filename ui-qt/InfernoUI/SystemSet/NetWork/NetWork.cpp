#include "NetWork.h"
#include "ui_NetWork.h"
#include <QMessageBox>
#include <QDebug>

#include "NetWorkSet.h"

NetWork::NetWork(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NetWork)
{
    ui->setupUi(this);
    PanelInit();
    CheckNetTimer = new QTimer;
    QList<QLineEdit *> lineEdit = this->findChildren<QLineEdit *>();
    foreach (QLineEdit * L, lineEdit) {
        L->installEventFilter(this);
        }
    connect(CheckNetTimer,&QTimer::timeout,this,&NetWork::CheckerNetTimerSlot);
    CheckNetTimer->start(1000);
}

NetWork::~NetWork()
{
    CheckNetTimer->stop();
    if (CheckNetTimer != NULL)
    {
        delete CheckNetTimer;
        CheckNetTimer = NULL;
    }
    QList<QLineEdit *> lineEdit = this->findChildren<QLineEdit *>();
    foreach (QLineEdit * L, lineEdit) {
        L->removeEventFilter(this);
        }
    delete ui;
}

bool NetWork::eventFilter(QObject *watched, QEvent *event)
{
    QList<QLineEdit *> lineEdit = this->findChildren<QLineEdit *>();
    foreach (QLineEdit * L, lineEdit)
    {
        if (L->objectName() == watched->objectName() && L->isEnabled() && !L->isReadOnly())
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
    }
    return QWidget::eventFilter(watched, event);
}

void NetWork::on_btnOK_clicked()
{
    int ret = 0;
    if(ui->radioButton_AutoIp->isChecked())
    {
        int ret = SetNetWayAuto();
        if(ret < 0)
        {
            QMessageBox::about(this,tr("Warning"),tr("设置失败!"));
        }

        return ;
    }

    if(ui->lineEdit_IP->text().isEmpty())
    {
        QMessageBox::about(this,tr("Warning"),tr("IP为空!"));
        return;
    }

    if(ui->lineEdit_Mask->text().isEmpty())
    {
        QMessageBox::about(this,tr("Warning"),tr("子网掩码为空!"));
        return;
    }

    if(ui->lineEdit_Gateway->text().isEmpty())
    {
        QMessageBox::about(this,tr("Warning"),tr("网关为空!"));
        return;
    }


    char *pIP = NULL, *pNetMask = NULL, *pGateWay = NULL;

    QString strIP = ui->lineEdit_IP->text(); //QString转char *
    QByteArray ba = strIP.toLatin1();
    pIP = ba.data();

    QString strNetMask = ui->lineEdit_Mask->text();
    QByteArray bb = strNetMask.toLatin1();
    pNetMask = bb.data();

    QString strGateWay = ui->lineEdit_Gateway->text();
    QByteArray bc = strGateWay.toLatin1();
    pGateWay = bc.data();

//    qDebug() << "Set: IP = " << pIP << " net mask = " << pNetMask << " gate way = " << pGateWay;

    ret = SetNetWayManual(pIP, pNetMask, pGateWay);
    if(ret < 0)
    {
        QMessageBox::about(this,tr("Warning"),tr("设置失败!"));
    }
}

void NetWork::PanelInit()
{
    int netWay = 0;
    char *pMac = NULL, *pIP = NULL, *pNetMask = NULL;

    netWay = GetNetWay();
    if (netWay == 1)
    {
        on_radioButton_AutoIp_clicked();
    }
    else
    {
        on_radioButton_InputIP_clicked();
        pNetMask = GetLocalNetMask();
        pIP = GetLocalIp();
//        qDebug() << "init:" << pIP;
        ui->lineEdit_IP->setText(pIP);
        ui->lineEdit_Mask->setText(pNetMask);
    }

    pMac = GetLocalMacAddr();
    ui->label_MacAddr->setText(pMac);
}

void NetWork::on_radioButton_AutoIp_clicked()
{
    ui->groupBox->setEnabled(false);
    ui->radioButton_AutoIp->setChecked(true);
    ui->lineEdit_IP->setReadOnly(true);
    ui->lineEdit_Mask->setReadOnly(true);
    ui->lineEdit_Gateway->setReadOnly(true);
}

void NetWork::on_radioButton_InputIP_clicked()
{
    ui->groupBox->setEnabled(true);
    ui->radioButton_InputIP->setChecked(true);
    ui->lineEdit_IP->setReadOnly(false);
    ui->lineEdit_Mask->setReadOnly(false);
    ui->lineEdit_Gateway->setReadOnly(false);
}

void NetWork::CheckerNetTimerSlot()
{
    int netStatus = GetNetworkStatus();
    char *pIP = NULL, *pNetMask = NULL;

    if(netStatus == 0)
    {
        ui->label_Status->setText(tr("错误"));
        ui->label_Mask->setText("");
        ui->label_IP->setText("");
    }
    else if(netStatus == 1)
    {
        ui->label_Status->setText(tr("已连接"));
        pIP = GetLocalIp();
////        qDebug() << "clock:" << pIP;
        pNetMask = GetLocalNetMask();
        ui->label_IP->setText(pIP);
        ui->label_Mask->setText(pNetMask);
    }
    else if(netStatus == 2)
    {
        ui->label_Status->setText(tr("已断开"));
        ui->label_IP->setText("");
        ui->label_Mask->setText("");
    }
    else if(netStatus == 3)
    {
        ui->label_Status->setText(tr("连接中…"));
        ui->label_IP->setText("");
        ui->label_Mask->setText("");
    }
}
