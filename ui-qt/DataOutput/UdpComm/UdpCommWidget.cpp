#include "UdpCommWidget.h"
#include "ui_UdpCommWidget.h"
#include "UdpGlobal.h"
#include "ProtocolManageGlobal.h"
#include <QMessageBox>
#include <QDebug>
#include "ProtocolInitGlobal.h"
UdpCommWidget::UdpCommWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UdpCommWidget)
{
    ui->setupUi(this);
    IniData();
}


UdpCommWidget::~UdpCommWidget()
{
    if(m_keyBoard_Lib.isLoaded())
    {
        m_keyBoard_Lib.unload();
    }
    ui->lineEdit_Remote_IP1->removeEventFilter(this);
    ui->lineEdit_Remote_IP2->removeEventFilter(this);
    ui->lineEdit_Remote_IP3->removeEventFilter(this);
    ui->lineEdit_Remote_IP4->removeEventFilter(this);
    ui->lineEdit_Remote_Port->removeEventFilter(this);
    ui->lineEdit_Local_Port->removeEventFilter(this);
    delete ui;
}


void UdpCommWidget::IniData()
{
    ui->lineEdit_Remote_IP1->installEventFilter(this);
    ui->lineEdit_Remote_IP2->installEventFilter(this);
    ui->lineEdit_Remote_IP3->installEventFilter(this);
    ui->lineEdit_Remote_IP4->installEventFilter(this);
    ui->lineEdit_Remote_Port->installEventFilter(this);
    ui->lineEdit_Local_Port->installEventFilter(this);
    ui->txtRecv->installEventFilter(this);
    ui->txtSend->installEventFilter(this);

    UDP_CONFIG udp_param;
    udp_config_get(&udp_param);

    char port_str[5];
    memset(port_str, 0, 5);
    sprintf(port_str, "%d", udp_param.local_port);
    QString Port_String = QString::fromLatin1(port_str);
    if(udp_param.local_port < 0 || udp_param.local_port > 65535)
    {
        ui->lineEdit_Local_Port->setText("8080");
    }
    else
    {
        ui->lineEdit_Local_Port->setText(Port_String);
    }

    QString ip_String = QString::fromLatin1(udp_param.ip);
    QStringList strIpList= ip_String.split(".");
    if(strIpList.count() == 4)
    {
        ui->lineEdit_Remote_IP1->setText(strIpList.at(0));
        ui->lineEdit_Remote_IP2->setText(strIpList.at(1));
        ui->lineEdit_Remote_IP3->setText(strIpList.at(2));
        ui->lineEdit_Remote_IP4->setText(strIpList.at(3));
    }
    else
    {
        ui->lineEdit_Remote_IP1->setText("192");
        ui->lineEdit_Remote_IP2->setText("168");
        ui->lineEdit_Remote_IP3->setText("0");
        ui->lineEdit_Remote_IP4->setText("1");
    }


    memset(port_str, 0, 5);
    sprintf(port_str, "%d", udp_param.server_port);
    Port_String = QString::fromLatin1(port_str);
    if(udp_param.server_port < 0 || udp_param.server_port > 65535)
    {
        ui->lineEdit_Remote_Port->setText("8080");
    }
    else
    {
        ui->lineEdit_Remote_Port->setText(Port_String);
    }

    PROTOCOL_SELECT protocol_status;
    protocol_select_get(&protocol_status);
    if(protocol_status.protocol_status == 0)
    {
        WidgetEnable(true);
        ui->StartpushButton->setText(tr("启动"));
    }
    else
    {
        WidgetEnable(false);
        ui->StartpushButton->setText(tr("停止"));
    }

    LoadKeyBoardLib();
}

void UdpCommWidget::LoadKeyBoardLib()
{
    m_keyBoard_Lib.setFileName("libFrmInputKeyBoard.so");
    if(m_keyBoard_Lib.load())
    {
        printf("libFrmInputKeyBoard.so OK\n");
    }
    else
    {
        qDebug()<<"load libFrmInputKeyBoard.so fail"<<m_keyBoard_Lib.errorString();
    }
}

void UdpCommWidget::WidgetEnable(bool enable_flag)
{
    EnableFlag = enable_flag;

    ui->lineEdit_Local_IP1->setEnabled(enable_flag);
    ui->lineEdit_Local_IP2->setEnabled(enable_flag);
    ui->lineEdit_Local_IP3->setEnabled(enable_flag);
    ui->lineEdit_Local_IP4->setEnabled(enable_flag);
    ui->lineEdit_Local_Port->setEnabled(enable_flag);

    ui->lineEdit_Remote_IP1->setEnabled(enable_flag);
    ui->lineEdit_Remote_IP2->setEnabled(enable_flag);
    ui->lineEdit_Remote_IP3->setEnabled(enable_flag);
    ui->lineEdit_Remote_IP4->setEnabled(enable_flag);
    ui->lineEdit_Remote_Port->setEnabled(enable_flag);

    ui->txtRecv->setEnabled(!enable_flag);
    ui->btnRecv->setEnabled(!enable_flag);
    ui->txtSend->setEnabled(!enable_flag);
    ui->btnSend->setEnabled(!enable_flag);
}

int UdpCommWidget::SetUdpParam()
{
    UDP_CONFIG udp_param;

    udp_param.local_port = ui->lineEdit_Local_Port->text().toInt();
    udp_param.server_port = ui->lineEdit_Remote_Port->text().toInt();

    QString ip_String = ui->lineEdit_Remote_IP1->text()+"."+ui->lineEdit_Remote_IP2->text()+ \
            "."+ui->lineEdit_Remote_IP3->text()+"."+ui->lineEdit_Remote_IP4->text();
    QByteArray ba = ip_String.toUtf8();
    char* ip = ba.data();
    memset(udp_param.ip, 0, 16);
    memcpy(udp_param.ip, ip, strlen(ip));
    udp_config_set(&udp_param);

    ///<开启协议
    int ret = protocol_open(COMM_UDP_TYPE, Protocol_Type);
    return ret;
}

void UdpCommWidget::SaveUdpParam(int open_Flag)
{
    COMM_UDP_CONFIG comm_udp_param;
    memset(&comm_udp_param, 0, sizeof(COMM_UDP_CONFIG));

    comm_udp_param.local_port = ui->lineEdit_Local_Port->text().toInt();
    comm_udp_param.Server_port = ui->lineEdit_Remote_Port->text().toInt();

    QString ip_String = ui->lineEdit_Remote_IP1->text()+"."+ui->lineEdit_Remote_IP2->text()+ \
            "."+ui->lineEdit_Remote_IP3->text()+"."+ui->lineEdit_Remote_IP4->text();
    QByteArray ba = ip_String.toUtf8();
    char* ip = ba.data();
    memcpy(comm_udp_param.Server_ip, ip, strlen(ip));

    ip_String = ui->lineEdit_Local_IP1->text()+"."+ui->lineEdit_Local_IP2->text()+ \
                "."+ui->lineEdit_Local_IP3->text()+"."+ui->lineEdit_Local_IP4->text();
    ba = ip_String.toUtf8();
    ip = ba.data();
    memcpy(comm_udp_param.local_ip, ip, strlen(ip));

    Protocol_Param_Change(Protocol_Type, open_Flag, COMM_UDP_TYPE, &comm_udp_param);
}

void UdpCommWidget::on_StartpushButton_clicked()
{
    int ret = 0;
    if(ui->StartpushButton->text() == tr("启动"))
    {
        ret = SetUdpParam();
        if(ret == 1)
        {
            WidgetEnable(false);
            SaveUdpParam(1);
            ui->StartpushButton->setText(tr("停止"));
        }
        else
        {
            QMessageBox::about(NULL, tr("提示"), tr("启动协议失败"));
        }
    }
    else if(ui->StartpushButton->text() == tr("停止"))
    {
        ret = protocol_close(Protocol_Type);
        if(ret == 1)
        {
            WidgetEnable(true);
            SaveUdpParam(0);
            ui->StartpushButton->setText(tr("启动"));
        }
        else
        {
            QMessageBox::about(NULL, tr("提示"), tr("停止协议失败"));
        }
    }
}

void UdpCommWidget::NumKeyBoardDlg(QObject *watched, QEvent *event, int Min_value, int Max_value)
{
    Fun_GetNumkeyBoardDlg GetNumKeyBoardDlg = (Fun_GetNumkeyBoardDlg)m_keyBoard_Lib.resolve("GetNumKeyBoardDialog");
    if(GetNumKeyBoardDlg)
    {
        Numkey = GetNumKeyBoardDlg();
        int ret = Numkey->exec();
        if(ret == QDialog::Accepted)
        {
            Fun_GetNumString GetNumString = (Fun_GetNumString)m_keyBoard_Lib.resolve("GetNum");
            if(GetNumString)
            {
                QString num = GetNumString();
                if(num.toInt() > Max_value || num.toInt() < Min_value)
                {
                    QMessageBox::about(NULL, tr("提示"), tr("该值无效,请输入")+QString::number(Min_value)+tr("~")+QString::number(Max_value)+tr("之间的值"));
                    return;
                }
                ((QLineEdit *)watched)->setText(num);
            }
        }
        delete Numkey;
    }
    else
    {
        qDebug()<<"get GetDialog func fail:"<<m_keyBoard_Lib.errorString();
    }
}

bool UdpCommWidget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->lineEdit_Local_IP1 || watched == ui->lineEdit_Remote_IP1)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            if(((QLineEdit *)watched)->isEnabled())
            {
                NumKeyBoardDlg(watched, event, 0, 223);
            }
        }
    }
    if(watched == ui->lineEdit_Local_IP2 || watched == ui->lineEdit_Local_IP3 || watched == ui->lineEdit_Local_IP4 || \
            watched == ui->lineEdit_Remote_IP2 || watched == ui->lineEdit_Remote_IP3 || watched == ui->lineEdit_Remote_IP4)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            if(((QLineEdit *)watched)->isEnabled())
            {
                NumKeyBoardDlg(watched, event, 0, 255);
            }
        }
    }
    if(watched == ui->lineEdit_Local_Port || watched == ui->lineEdit_Remote_Port)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            if(((QLineEdit *)watched)->isEnabled())
            {
                NumKeyBoardDlg(watched, event, 0, 65535);
            }
        }
    }
    if(watched == ui->txtRecv || watched == ui->txtSend)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            if(((QLineEdit *)watched)->isEnabled())
            {
                Fun_GetkeyBoardDlg GetKeyBoardDlg = (Fun_GetkeyBoardDlg)m_keyBoard_Lib.resolve("GetKeyBoardDialog");
                Fun_GetInputString GetInputString = (Fun_GetInputString)m_keyBoard_Lib.resolve("GetInputString");
                if(GetKeyBoardDlg)
                {
                    m_dlg = GetKeyBoardDlg();
                    m_dlg->move(0, 150);
                    int ret = m_dlg->exec();
                    if(ret == QDialog::Accepted)
                    {
                        if(GetInputString)
                            ((QLineEdit *)watched)->setText(GetInputString());
                    }
                    delete m_dlg;
                }
                else
                {
                    qDebug()<<"get GetDialog func fail:"<<m_keyBoard_Lib.errorString();
                }
            }
        }
    }
    return QWidget::eventFilter(watched, event);
}
