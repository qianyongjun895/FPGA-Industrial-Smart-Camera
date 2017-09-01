#include "SerialPortWidget.h"
#include "ui_SerialPortWidget.h"
#include "ProtocolManageGlobal.h"
#include "UartGlobal.h"
#include <QMessageBox>
#include <QDebug>
#include "ModbusGlobal.h"
#include "ProtocolInitGlobal.h"
SerialPortWidget::SerialPortWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SerialPortWidget)
{
    ui->setupUi(this);
    Ini_Flag = 0;
    ui->txtMacthionAddr->installEventFilter(this);
    ui->txtMacthionAddr->setText("1");
}

SerialPortWidget::~SerialPortWidget()
{
    if(m_keyBoard_Lib.isLoaded())
    {
        m_keyBoard_Lib.unload();
    }
    delete ui;
}


void SerialPortWidget::IniData()
{
    Ini_Flag = 1;
    Uart_Baud.insert(9600, 0);
    Uart_Baud.insert(19200, 1);
    Uart_Baud.insert(38400, 2);
    Uart_Baud.insert(57600, 3);
    Uart_Baud.insert(115200, 4);

    Data_Bit.insert(6, 0);
    Data_Bit.insert(7, 1);
    Data_Bit.insert(8, 2);

    ui->comboBoxWorkKind->addItem(tr("从机"));
    ui->comboBoxWorkKind->addItem(tr("主机"));

    ui->comboBoxComPort->addItem(tr("COM1"));

    ui->comboBoxBaudrate->addItem(tr("9600"));
    ui->comboBoxBaudrate->addItem(tr("19200"));
    ui->comboBoxBaudrate->addItem(tr("38400"));
    ui->comboBoxBaudrate->addItem(tr("57600"));
    ui->comboBoxBaudrate->addItem(tr("115200"));

    ui->comboBoxDataBit->addItem(tr("6"));
    ui->comboBoxDataBit->addItem(tr("7"));
    ui->comboBoxDataBit->addItem(tr("8"));

    ui->comboBoxParity->addItem(tr("无校验"));
    ui->comboBoxParity->addItem(tr("偶校验"));
    ui->comboBoxParity->addItem(tr("奇校验"));

    ui->comboBoxStopBit->addItem(tr("1"));
    ui->comboBoxStopBit->addItem(tr("2"));

    ui->txtRecv->installEventFilter(this);
    ui->txtSend->installEventFilter(this);
    int dev_addr = 1;
    if(Protocol_Type == MODBUS_PROTOCOL){
        ui->comboBoxWorkKind->setCurrentIndex(modbus_slave_or_host_get());
        dev_addr = modbus_device_dddress_get();
    }
    ui->txtMacthionAddr->setText(QString::number(dev_addr));
    UART_CONFIG uart_param;
    uart_config_get(&uart_param);

    ui->comboBoxBaudrate->setCurrentIndex(Uart_Baud.value(uart_param.baudrate));
    ui->comboBoxDataBit->setCurrentIndex(Data_Bit.value(uart_param.databit));
    ui->comboBoxParity->setCurrentIndex(uart_param.verifytype);
    ui->comboBoxStopBit->setCurrentIndex(uart_param.stopbit);
    PROTOCOL_SELECT protocol_status;
    protocol_select_get(&protocol_status);
    if(protocol_status.protocol_status == 0)
    {
        WidgetEnable(true);
        ui->btnOpen->setText("打开");
    }
    else
    {
        WidgetEnable(false);
        ui->btnOpen->setText("关闭");
    }

    LoadKeyBoardLib();
    Ini_Flag = 0;
}

void SerialPortWidget::LoadKeyBoardLib()
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

void SerialPortWidget::NumKeyBoardDlg(QObject *watched, QEvent *event, int Min_value, int Max_value)
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

bool SerialPortWidget::eventFilter(QObject *watched, QEvent *event)
{
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

void SerialPortWidget::WidgetEnable(bool enable_flag)
{
    EnableFlag = enable_flag;

    ui->comboBoxComPort->setEnabled(enable_flag);
    ui->comboBoxBaudrate->setEnabled(enable_flag);
    ui->comboBoxDataBit->setEnabled(enable_flag);
    ui->comboBoxParity->setEnabled(enable_flag);
    ui->comboBoxStopBit->setEnabled(enable_flag);

    if(Protocol_Type == MODBUS_PROTOCOL)
    {
        ui->txtMacthionAddr->setEnabled(enable_flag);
        ui->comboBoxWorkKind->setEnabled(enable_flag);
    }
    else
    {
        ui->txtMacthionAddr->setEnabled(false);
        ui->comboBoxWorkKind->setEnabled(false);
    }

    ui->txtRecv->setEnabled(!enable_flag);
    ui->btnRecv->setEnabled(!enable_flag);
    ui->txtSend->setEnabled(!enable_flag);
    ui->btnSend->setEnabled(!enable_flag);
}

int SerialPortWidget::SetUartParam()
{
    UART_CONFIG uart_param;
    uart_param.uartport = UART_PORT_COM1;
    uart_param.baudrate = Uart_Baud.key(ui->comboBoxBaudrate->currentIndex());
    uart_param.databit = Data_Bit.key(ui->comboBoxDataBit->currentIndex());
    uart_param.verifytype = ui->comboBoxParity->currentIndex();
    uart_param.stopbit = ui->comboBoxStopBit->currentIndex();
    uart_config_set(&uart_param);

    if(Protocol_Type == MODBUS_PROTOCOL)
    {
        modbus_slave_or_host_set(ui->comboBoxWorkKind->currentIndex());
        modbus_device_dddress_set(ui->txtMacthionAddr->text().toInt());
    }
    ///<开启协议
    int ret = protocol_open(COMM_UART_TYPE, Protocol_Type);
    return ret;
}

void SerialPortWidget::SaveUartParam(int open_Flag)
{
    COMM_UART_CONFIG comm_uart_param;
    memset(&comm_uart_param, 0, sizeof(COMM_UART_CONFIG));

    QByteArray ba = ui->comboBoxWorkKind->currentText().toUtf8();
    char* work = ba.data();
    memcpy(comm_uart_param.work_mode, work, strlen(work));

    comm_uart_param.dev_addr = ui->txtMacthionAddr->text().toInt();

    comm_uart_param.baudrate = Uart_Baud.key(ui->comboBoxBaudrate->currentIndex());
    comm_uart_param.databit = Data_Bit.key(ui->comboBoxDataBit->currentIndex());

    ba = ui->comboBoxParity->currentText().toUtf8();
    char* Parity = ba.data();
    memcpy(comm_uart_param.verifytype, Parity, strlen(Parity));
    comm_uart_param.stopbit = ui->comboBoxStopBit->currentIndex();

    Protocol_Param_Change(Protocol_Type, open_Flag, COMM_UART_TYPE, &comm_uart_param);
}

void SerialPortWidget::on_btnOpen_clicked()
{
    int ret = 0;
    if(ui->btnOpen->text() == tr("打开"))
    {
        ret = SetUartParam();
        if(ret == 1)
        {
            WidgetEnable(false);
            SaveUartParam(1);
            ui->btnOpen->setText(tr("关闭"));
        }
        else
        {
            QMessageBox::about(NULL, tr("提示"), tr("打开协议失败"));
        }
    }
    else if(ui->btnOpen->text() == tr("关闭"))
    {
        ret = protocol_close(Protocol_Type);
        if(ret == 1)
        {
            WidgetEnable(true);
            SaveUartParam(0);
            ui->btnOpen->setText(tr("打开"));
        }
        else
        {
            QMessageBox::about(NULL, tr("提示"), tr("关闭协议失败"));
        }
    }
}

void SerialPortWidget::on_comboBoxWorkKind_currentIndexChanged(int index)
{
    if(Ini_Flag == 0)
    {
        if(Protocol_Type == MODBUS_PROTOCOL)
        {
            modbus_slave_or_host_set(index);
            modbus_clean_data_list();
        }
    }
}
