#include "EthernetPortWidget.h"
#include "ui_EthernetPortWidget.h"
#include <QMessageBox>
#include <stdio.h>
#include <stdlib.h>
#include <QDebug>
#include "ProtocolManageGlobal.h"
#include "ModbusGlobal.h"
#include "TcpGlobal.h"
#include "ProtocolInitGlobal.h"

EthernetPortWidget::EthernetPortWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EthernetPortWidget)
{
    ui->setupUi(this);
    Ini_Flag = 0;
}


EthernetPortWidget::~EthernetPortWidget()
{
    if(m_keyBoard_Lib.isLoaded())
    {
        m_keyBoard_Lib.unload();
    }
    ui->lineEdit_IP1->removeEventFilter(this);
    ui->lineEdit_IP2->removeEventFilter(this);
    ui->lineEdit_IP3->removeEventFilter(this);
    ui->lineEdit_IP4->removeEventFilter(this);
    ui->lineEdit_Port->removeEventFilter(this);
    ui->txtRecv->removeEventFilter(this);
    ui->txtSend->removeEventFilter(this);
    ui->txtMacthionAddr->removeEventFilter(this);
    delete ui;
}


void EthernetPortWidget::IniData()
{
    Ini_Flag = 1;
    ui->lineEdit_IP1->installEventFilter(this);
    ui->lineEdit_IP2->installEventFilter(this);
    ui->lineEdit_IP3->installEventFilter(this);
    ui->lineEdit_IP4->installEventFilter(this);
    ui->lineEdit_Port->installEventFilter(this);
    ui->txtRecv->installEventFilter(this);
    ui->txtSend->installEventFilter(this);
    ui->txtMacthionAddr->installEventFilter(this);
    int dev_addr = 1;
    if(Protocol_Type == MODBUS_PROTOCOL)
    {
        dev_addr = modbus_device_dddress_get();
    }
    ui->txtMacthionAddr->setText(QString::number(dev_addr));

    tcp_config_get(&tcp_param);

    if(tcp_param.net_type < 0 || tcp_param.net_type > 1)
        tcp_param.net_type = 0;
    ui->EthernetPortcbB->addItem(tr("服务端"));
    ui->EthernetPortcbB->addItem(tr("客户端"));
    ui->EthernetPortcbB->setCurrentIndex(tcp_param.net_type);

    QString ip_String = QString::fromLatin1(tcp_param.ip);
    QStringList strIpList= ip_String.split(".");
    if(strIpList.count() == 4)
    {
        ui->lineEdit_IP1->setText(strIpList.at(0));
        ui->lineEdit_IP2->setText(strIpList.at(1));
        ui->lineEdit_IP3->setText(strIpList.at(2));
        ui->lineEdit_IP4->setText(strIpList.at(3));
    }
    else
    {
        ui->lineEdit_IP1->setText("192");
        ui->lineEdit_IP2->setText("168");
        ui->lineEdit_IP3->setText("0");
        ui->lineEdit_IP4->setText("1");
    }

    char port_str[5];
    memset(port_str, 0, 5);
    sprintf(port_str, "%d", tcp_param.port);
    QString Port_String = QString::fromLatin1(port_str);
    if(tcp_param.port < 0 || tcp_param.port > 65535)
    {
        ui->lineEdit_Port->setText("8080");
    }
    else
    {
        ui->lineEdit_Port->setText(Port_String);
    }
    PROTOCOL_SELECT protocol_status;
    protocol_select_get(&protocol_status);
    if(ui->EthernetPortcbB->currentIndex() == 0)
    {
        ui->IP_Label->setText(tr("本地IP地址"));
        ui->Port_Label->setText(tr("本地端口号"));
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
    }
    else
    {
        ui->IP_Label->setText(tr("服务器IP地址"));
        ui->Port_Label->setText(tr("服务器端口号"));
        if(protocol_status.protocol_status == 0)
        {
            WidgetEnable(true);
            ui->StartpushButton->setText(tr("连接"));
        }
        else
        {
            WidgetEnable(false);
            ui->StartpushButton->setText(tr("断开"));
        }
    }
    LoadKeyBoardLib();
    Ini_Flag = 0;
}

void EthernetPortWidget::LoadKeyBoardLib()
{
    m_keyBoard_Lib.setFileName("libFrmInputKeyBoard.so");
    if(m_keyBoard_Lib.isLoaded())
    {
        return;
    }
    if(m_keyBoard_Lib.load())
    {
        printf("libFrmInputKeyBoard.so OK\n");
    }
    else
    {
        qDebug()<<"load libFrmInputKeyBoard.so fail"<<m_keyBoard_Lib.errorString();
    }
}

void EthernetPortWidget::WidgetEnable(bool enable_flag)
{
    EnableFlag = enable_flag;

    ui->EthernetPortcbB->setEnabled(enable_flag);
    ui->lineEdit_IP1->setEnabled(enable_flag);
    ui->lineEdit_IP2->setEnabled(enable_flag);
    ui->lineEdit_IP3->setEnabled(enable_flag);
    ui->lineEdit_IP4->setEnabled(enable_flag);
    ui->lineEdit_Port->setEnabled(enable_flag);

    if(Protocol_Type == MODBUS_PROTOCOL)
    {
        ui->txtMacthionAddr->setEnabled(enable_flag);
    }
    else
    {
        ui->txtMacthionAddr->setEnabled(false);
    }

    ui->txtRecv->setEnabled(!enable_flag);
    ui->btnRecv->setEnabled(!enable_flag);
    ui->txtSend->setEnabled(!enable_flag);
    ui->btnSend->setEnabled(!enable_flag);
}

void EthernetPortWidget::NumKeyBoardDlg(QObject *watched, QEvent *event, int Min_value, int Max_value)
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

bool EthernetPortWidget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->lineEdit_IP1)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            if(((QLineEdit *)watched)->isEnabled())
            {
                NumKeyBoardDlg(watched, event, 0, 223);
            }
        }
    }
    if(watched == ui->lineEdit_IP2 || watched == ui->lineEdit_IP3 || watched == ui->lineEdit_IP4)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            if(((QLineEdit *)watched)->isEnabled())
            {
                NumKeyBoardDlg(watched, event, 0, 255);
            }
        }
    }
    if(watched == ui->lineEdit_Port)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            if(((QLineEdit *)watched)->isEnabled())
            {
                NumKeyBoardDlg(watched, event, 0, 65535);
            }
        }
    }
    if(watched == ui->txtMacthionAddr)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            if(((QLineEdit *)watched)->isEnabled())
            {
                NumKeyBoardDlg(watched, event, 1, 247);
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

int EthernetPortWidget::SetEthernetParam()
{
    ///<设置网口模式
    tcp_param.net_type = ui->EthernetPortcbB->currentIndex();
    if(Protocol_Type == MODBUS_PROTOCOL)
    {
        modbus_device_dddress_set(ui->txtMacthionAddr->text().toInt());
    }
    ///<设置IP
    QString ip_String = ui->lineEdit_IP1->text()+"."+ui->lineEdit_IP2->text()+ \
            "."+ui->lineEdit_IP3->text()+"."+ui->lineEdit_IP4->text();
    QByteArray ba = ip_String.toUtf8();
    char* ip = ba.data();
    memset(tcp_param.ip, 0, 16);
    memcpy(tcp_param.ip, ip, strlen(ip));
    ///<设置端口号
    tcp_param.port = ui->lineEdit_Port->text().toInt();

    tcp_config_set(&tcp_param);

    ///<开启协议
    int ret = protocol_open(COMM_TCP_TYPE, Protocol_Type);
    return ret;
}

void EthernetPortWidget::SaveTcpParam(int open_Flag)
{
    COMM_TCP_CONFIG comm_tcp_param;
    memset(&comm_tcp_param, 0, sizeof(COMM_TCP_CONFIG));

    QByteArray ba = ui->EthernetPortcbB->currentText().toUtf8();
    char* work = ba.data();
    memcpy(comm_tcp_param.work_mode, work, strlen(work));

    comm_tcp_param.dev_addr = ui->txtMacthionAddr->text().toInt();

    comm_tcp_param.port = ui->lineEdit_Port->text().toInt();

    QString ip_String = ui->lineEdit_IP1->text()+"."+ui->lineEdit_IP2->text()+ \
            "."+ui->lineEdit_IP3->text()+"."+ui->lineEdit_IP4->text();
    ba = ip_String.toUtf8();
    char* ip = ba.data();
    memcpy(comm_tcp_param.ip, ip, strlen(ip));

    Protocol_Param_Change(Protocol_Type, open_Flag, COMM_TCP_TYPE, &comm_tcp_param);
}

void EthernetPortWidget::on_StartpushButton_clicked()
{
    if(ui->StartpushButton->text() == tr("启动"))
    {
        ///< 设置网口参数
        int ret = SetEthernetParam();
        if(ret == 1)
        {
            WidgetEnable(false);
            SaveTcpParam(1);
            ui->StartpushButton->setText(tr("停止"));
        }
        else
        {
            QMessageBox::about(NULL, tr("提示"), tr("启动协议失败"));
        }
        return;
    }

    if(ui->StartpushButton->text() == tr("连接"))
    {
        ///< 设置网口参数
        int ret = SetEthernetParam();
        if(ret == 1)
        {
            WidgetEnable(false);
            SaveTcpParam(1);
            ui->StartpushButton->setText(tr("断开"));
        }
        else
        {
            QMessageBox::about(NULL, tr("提示"), tr("启动协议失败"));
        }
        return;
    }

    if(ui->StartpushButton->text() == tr("停止"))
    {
        ///< 停止服务器
        int ret = protocol_close(Protocol_Type);
        if(ret == 1)
        {
            WidgetEnable(true);
            SaveTcpParam(0);
            ui->StartpushButton->setText(tr("启动"));
        }
        else
        {
            QMessageBox::about(NULL, tr("提示"), tr("关闭协议失败"));
        }
        return;
    }

    if(ui->StartpushButton->text() == tr("断开"))
    {
        ///< 断开连接
        int ret = protocol_close(Protocol_Type);
        if(ret == 1)
        {
            WidgetEnable(true);
            SaveTcpParam(0);
            ui->StartpushButton->setText(tr("连接"));
        }
        else
        {
            QMessageBox::about(NULL, tr("提示"), tr("关闭协议失败"));
        }
        return;
    }
}

void EthernetPortWidget::on_btnSend_clicked()
{
    //    TCP_CONFIG tcp_param;
    //    tcp_config_get(&tcp_param);
}

void EthernetPortWidget::on_EthernetPortcbB_currentIndexChanged(int index)
{
    if(Ini_Flag == 0)
    {
        if(Protocol_Type == MODBUS_PROTOCOL)
        {
            modbus_clean_data_list();
        }

        if(ui->EthernetPortcbB->currentIndex() == 0)
        {
            char ip_addr[16];
            int ret = local_ip_get(ip_addr);
            if(ret == 1){
                QString ip = QString::fromUtf8(ip_addr);
                QStringList ip_list = ip.split(".");
                ui->lineEdit_IP1->setText(ip_list.at(0));
                ui->lineEdit_IP2->setText(ip_list.at(1));
                ui->lineEdit_IP3->setText(ip_list.at(2));
                ui->lineEdit_IP4->setText(ip_list.at(3));
            }
            ui->StartpushButton->setText("启动");
            ui->IP_Label->setText(tr("本地IP地址"));
            ui->Port_Label->setText(tr("本地端口号"));
        }
        else if(ui->EthernetPortcbB->currentIndex() == 1)
        {
            ui->StartpushButton->setText("连接");
            ui->IP_Label->setText(tr("服务器IP地址"));
            ui->Port_Label->setText(tr("服务器端口号"));
        }
    }
}

