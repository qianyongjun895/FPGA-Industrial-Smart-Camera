#include "InsideComm.h"
#include "ui_InsideComm.h"
#include <QComboBox>
#include <QDialog>
#include <QMessageBox>
#include <QDebug>
#include <QDialog>
#include <QListWidgetItem>
#include "ProtocolManageGlobal.h"
InsideComm::InsideComm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InsideComm)
{
    ui->setupUi(this);
    LoadKeyBoardLib();
    list_cnt = 0;
    ui->comboBox_Mode->addItem("服务端");
    ui->comboBox_Mode->addItem("客户端");
    QList<QLineEdit*> line_list = this->findChildren<QLineEdit*>();
    foreach (QLineEdit *L, line_list) {
        L->installEventFilter(this);
    }
    IniData();
}

InsideComm::~InsideComm()
{
    QList<QLineEdit*> line_list = this->findChildren<QLineEdit*>();
    foreach (QLineEdit *L, line_list) {
        L->removeEventFilter(this);
    }
    if(m_keyBoard_Lib.isLoaded())
    {
        m_keyBoard_Lib.unload();
    }
    delete ui;
}

bool InsideComm::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->lineEdit_IP_1 || watched == ui->lineEdit_IP_2 ||\
            watched == ui->lineEdit_IP_3 || watched == ui->lineEdit_IP_4){
        if(event->type() == QEvent::MouseButtonPress){
            if(((QLineEdit *)watched)->isEnabled()){
                NumKeyBoardDlg(watched, event, 0, 255);
            }
        }
    }
    if(watched == ui->lineEdit_Port_number){
        if(event->type() == QEvent::MouseButtonPress){
            if(((QLineEdit *)watched)->isEnabled()){
                NumKeyBoardDlg(watched, event, 0, 65535);
            }
        }
    }
    if(watched == ui->lineEdit_dev_Addr){
        if(event->type() == QEvent::MouseButtonPress){
            if(((QLineEdit *)watched)->isEnabled()){
                NumKeyBoardDlg(watched, event, 1, 247);
            }
        }
    }
    return QWidget::eventFilter(watched, event);
}

void InsideComm::LoadKeyBoardLib()
{
    m_keyBoard_Lib.setFileName("libFrmInputKeyBoard.so");
    if(m_keyBoard_Lib.isLoaded())
    {
        return;
    }
    if(m_keyBoard_Lib.load())
    {
        qDebug()<<"libFrmInputKeyBoard.so OK";
    }
    else
    {
        qDebug()<<"load libFrmInputKeyBoard.so fail"<<m_keyBoard_Lib.errorString();
    }
}

void InsideComm::NumKeyBoardDlg(QObject *watched, QEvent *event, int Min_value, int Max_value)
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
        Numkey = NULL;
    }
    else
    {
        qDebug()<<"get GetDialog func fail:"<<m_keyBoard_Lib.errorString();
    }
}



void InsideComm::on_comboBox_Mode_currentIndexChanged(int index)
{
    if(index == 0){
        ui->pushButton_connect->setText("启动");
        char ip_addr[16];
        int ret = local_ip_get(ip_addr);
        if(ret == 1){
            QString ip = QString::fromUtf8(ip_addr);
            QStringList ip_list = ip.split(".");
            ui->lineEdit_IP_1->setText(ip_list.at(0));
            ui->lineEdit_IP_2->setText(ip_list.at(1));
            ui->lineEdit_IP_3->setText(ip_list.at(2));
            ui->lineEdit_IP_4->setText(ip_list.at(3));
        }
        ui->label_IP->setText("本地IP地址:");
        ui->label_Port->setText("本地端口号:");
    }else{
        ui->pushButton_connect->setText("连接");
        ui->label_IP->setText("服务器IP地址:");
        ui->label_Port->setText("服务器端口号:");
    }
}

void InsideComm::on_pushButton_connect_clicked()
{
    if(ui->pushButton_connect->text() == "连接" || ui->pushButton_connect->text() == "启动"){
        QString ip_1 = ui->lineEdit_IP_1->text();
        QString ip_2 = ui->lineEdit_IP_2->text();
        QString ip_3 = ui->lineEdit_IP_3->text();
        QString ip_4 = ui->lineEdit_IP_4->text();
        QString dev_addr = ui->lineEdit_dev_Addr->text();
        QString port_number = ui->lineEdit_Port_number->text();
        TCP_CONFIG tcp__config;
        memset(&tcp__config, 0, sizeof(TCP_CONFIG));
        QString ip_String = ip_1+"."+ip_2+"."+ip_3+"."+ip_4;
        QByteArray ba = ip_String.toUtf8();
        char *ip = ba.data();
        memcpy(tcp__config.ip, ip, strlen(ip));
        tcp__config.net_type = ui->comboBox_Mode->currentIndex();
        tcp__config.port = port_number.toInt();
        intercom_tcp_config_set(&tcp__config);

        intercom_modbus_slave_or_host_set(ui->comboBox_Mode->currentIndex());
        intercom_modbus_device_address_set(dev_addr.toUInt());
        int ret = protocol_open(COMM_TCP_TYPE, PROTOCOL_MAX);
        if(ret == 1){
            if(ui->comboBox_Mode->currentIndex() == 0){
                ui->pushButton_connect->setText("停止");
            }else{
                ui->pushButton_connect->setText("断开");
            }
            ui->comboBox_Mode->setEnabled(false);
            ui->lineEdit_dev_Addr->setEnabled(false);
            ui->lineEdit_IP_1->setEnabled(false);
            ui->lineEdit_IP_2->setEnabled(false);
            ui->lineEdit_IP_3->setEnabled(false);
            ui->lineEdit_IP_4->setEnabled(false);
            ui->lineEdit_Port_number->setEnabled(false);
        }else{
            QMessageBox::about(NULL, "提示", "打开协议失败");
        }
    }else{
        int ret = protocol_close(PROTOCOL_MAX);
        if(ret == 1){
            if(ui->comboBox_Mode->currentIndex() == 0){
                ui->pushButton_connect->setText("启动");
            }else{
                ui->pushButton_connect->setText("连接");
            }
            ui->comboBox_Mode->setEnabled(true);
            ui->lineEdit_dev_Addr->setEnabled(true);
            ui->lineEdit_IP_1->setEnabled(true);
            ui->lineEdit_IP_2->setEnabled(true);
            ui->lineEdit_IP_3->setEnabled(true);
            ui->lineEdit_IP_4->setEnabled(true);
            ui->lineEdit_Port_number->setEnabled(true);
        }else{
            QMessageBox::about(NULL, "提示", "关闭协议失败");
        }
    }
}




void InsideComm::IniData()
{
    intercom_modbus_init();
    TCP_CONFIG tcp_config;
    intercom_tcp_config_get(&tcp_config);
    ui->comboBox_Mode->setCurrentIndex(tcp_config.net_type);
    ui->lineEdit_dev_Addr->setText(QString::number(intercom_modbus_device_address_get()));
    QString ip = QString::fromUtf8(tcp_config.ip);
    QStringList ip_list = ip.split(".");
    ui->lineEdit_IP_1->setText(ip_list.at(0));
    ui->lineEdit_IP_2->setText(ip_list.at(1));
    ui->lineEdit_IP_3->setText(ip_list.at(2));
    ui->lineEdit_IP_4->setText(ip_list.at(3));
    ui->lineEdit_Port_number->setText(QString::number(tcp_config.port));
    int status = intercom_modbus_status_get();
    if(status == 1){
        if(ui->comboBox_Mode->currentIndex() == 0){
            ui->pushButton_connect->setText("停止");
        }else{
            ui->pushButton_connect->setText("断开");
        }
        ui->comboBox_Mode->setEnabled(false);
        ui->lineEdit_dev_Addr->setEnabled(false);
        ui->lineEdit_IP_1->setEnabled(false);
        ui->lineEdit_IP_2->setEnabled(false);
        ui->lineEdit_IP_3->setEnabled(false);
        ui->lineEdit_IP_4->setEnabled(false);
        ui->lineEdit_Port_number->setEnabled(false);
    }else{
        if(ui->comboBox_Mode->currentIndex() == 0){
            ui->pushButton_connect->setText("启动");
        }else{
            ui->pushButton_connect->setText("连接");
        }
        ui->comboBox_Mode->setEnabled(true);
        ui->lineEdit_dev_Addr->setEnabled(true);
        ui->lineEdit_IP_1->setEnabled(true);
        ui->lineEdit_IP_2->setEnabled(true);
        ui->lineEdit_IP_3->setEnabled(true);
        ui->lineEdit_IP_4->setEnabled(true);
        ui->lineEdit_Port_number->setEnabled(true);
    }
}

void InsideComm::IniSlaveOrHost()
{
    slave_or_host = intercom_modbus_slave_or_host_get();
    if(slave_or_host == MODBUS_SLAVE_TYPE){
        ui->comboBoxModbusTool->clear();
        ui->comboBoxModbusTool->addItem("读线圈");
        ui->comboBoxModbusTool->addItem("写线圈");
        ui->comboBoxModbusTool->addItem("写离散量");
        ui->comboBoxModbusTool->addItem("读保持寄存器");
        ui->comboBoxModbusTool->addItem("写保持寄存器");
        ui->comboBoxModbusTool->addItem("写输入寄存器");
    } else {
        ui->comboBoxModbusTool->clear();
        ui->comboBoxModbusTool->addItem("读线圈");
        ui->comboBoxModbusTool->addItem("写线圈");
        ui->comboBoxModbusTool->addItem("读离散量");
        ui->comboBoxModbusTool->addItem("读保持寄存器");
        ui->comboBoxModbusTool->addItem("写保持寄存器");
        ui->comboBoxModbusTool->addItem("读输入寄存器");
    }
    ui->listWidgetData->clear();
    list_cnt = intercom_modbus_data_list_cnt_get();
    for(int i = 0; i < list_cnt; i++){
        int tool_type = intercom_modbus_list_data_type_get(i);
        AddListWidgetItem(ui->comboBoxModbusTool->itemText(tool_type), i, slave_or_host, tool_type);
    }
}


void InsideComm::AddCommandItemData(IntercomModbusDataListItem *pListWidgeModbusItem)
{
    pListWidgeModbusItem->setAttribute(Qt::WA_DeleteOnClose);
    int size =ui->listWidgetData->count();
    QListWidgetItem* mItem = new QListWidgetItem(ui->listWidgetData);
    ui->listWidgetData->setItemWidget(mItem,(QWidget*)pListWidgeModbusItem);
    ui->listWidgetData->item(size)->setSizeHint(QSize(240,40));
    ui->listWidgetData->setCurrentRow(size);
}

void InsideComm::AddListWidgetItem(QString String, int Current_index, int Host_Or_Slave, int Tool_type)
{
    IntercomModbusDataListItem *Data_List = new IntercomModbusDataListItem;
    Data_List->SetLabelText(String);
    Data_List->SetModbusMode(Host_Or_Slave);
    Data_List->SetCurrentIndex(Current_index);
    Data_List->SetToolType(Tool_type);
    AddCommandItemData(Data_List);
}

void InsideComm::AddSlaveReadCoil()
{
    int current_index = ui->listWidgetData->count();
    IntercomRDSingleCoilDialog *SlaveReadCoil_dlg = new IntercomRDSingleCoilDialog;
    SlaveReadCoil_dlg->SetDataListIndex(current_index);
    SlaveReadCoil_dlg->SetModbusMode(MODBUS_SLAVE_TYPE);
    SlaveReadCoil_dlg->SetToolType(SLAVE_RD_COILS);
    SlaveReadCoil_dlg->IniSingleCoilData();
    int ret = SlaveReadCoil_dlg->exec();
    if(ret == QDialog::Accepted){
        QString lable_string = ui->comboBoxModbusTool->itemText(SLAVE_RD_COILS);
        AddListWidgetItem(lable_string, current_index, MODBUS_SLAVE_TYPE, SLAVE_RD_COILS);
    }
    delete SlaveReadCoil_dlg;
}

void InsideComm::AddSlaveWriteCoil()
{
    int current_index = ui->listWidgetData->count();
    IntercomWRMultiCoilDialog *SlaveWriteCoil_dlg = new IntercomWRMultiCoilDialog;
    SlaveWriteCoil_dlg->SetDataListIndex(current_index);
    SlaveWriteCoil_dlg->SetModbusMode(MODBUS_SLAVE_TYPE);
    SlaveWriteCoil_dlg->SetToolType(SLAVE_WR_COILS);
    SlaveWriteCoil_dlg->IniMultiCoilData();
    int ret = SlaveWriteCoil_dlg->exec();
    if(ret == QDialog::Accepted){
        QString lable_string = ui->comboBoxModbusTool->itemText(SLAVE_WR_COILS);
        AddListWidgetItem(lable_string, current_index, MODBUS_SLAVE_TYPE, SLAVE_WR_COILS);
    }
    delete SlaveWriteCoil_dlg;
}

void InsideComm::AddSlaveWriteDiscrete()
{
    int current_index = ui->listWidgetData->count();
    IntercomWRMultiCoilDialog *SlaveWriteDiscrete_dlg = new IntercomWRMultiCoilDialog;
    SlaveWriteDiscrete_dlg->SetDataListIndex(current_index);
    SlaveWriteDiscrete_dlg->SetModbusMode(MODBUS_SLAVE_TYPE);
    SlaveWriteDiscrete_dlg->SetToolType(SLAVE_WR_DISCRETE);
    SlaveWriteDiscrete_dlg->IniMultiCoilData();
    int ret = SlaveWriteDiscrete_dlg->exec();
    if(ret == QDialog::Accepted){
        QString lable_string = ui->comboBoxModbusTool->itemText(SLAVE_WR_DISCRETE);
        AddListWidgetItem(lable_string, current_index, MODBUS_SLAVE_TYPE, SLAVE_WR_DISCRETE);
    }
    delete SlaveWriteDiscrete_dlg;
}

void InsideComm::AddSlaveReadHoldReg()
{
    int current_index = ui->listWidgetData->count();
    IntercomReadRegDialog *SlaveReadHoldReg_dlg = new IntercomReadRegDialog;
    SlaveReadHoldReg_dlg->SetDataListIndex(current_index);
    SlaveReadHoldReg_dlg->SetModbusMode(MODBUS_SLAVE_TYPE);
    SlaveReadHoldReg_dlg->SetToolType(SLAVE_RD_HOLD_REG);
    SlaveReadHoldReg_dlg->IniRegData();
    int ret = SlaveReadHoldReg_dlg->exec();
    if(ret == QDialog::Accepted){
        QString lable_string = ui->comboBoxModbusTool->itemText(SLAVE_RD_HOLD_REG);
        AddListWidgetItem(lable_string, current_index, MODBUS_SLAVE_TYPE, SLAVE_RD_HOLD_REG);
    }
    delete SlaveReadHoldReg_dlg;
}

void InsideComm::AddSlaveWriteHoldReg()
{
    int current_index = ui->listWidgetData->count();
    IntercomMultiRegDialog *SlaveWriteHoldReg_dlg = new IntercomMultiRegDialog;
    SlaveWriteHoldReg_dlg->SetDlgType(0);
    SlaveWriteHoldReg_dlg->SetDataListIndex(current_index);
    SlaveWriteHoldReg_dlg->SetModbusMode(MODBUS_SLAVE_TYPE);
    SlaveWriteHoldReg_dlg->SetToolType(SLAVE_WR_HOLD_REG);
    SlaveWriteHoldReg_dlg->IniRegData();
    int ret = SlaveWriteHoldReg_dlg->exec();
    if(ret == QDialog::Accepted){
        QString lable_string = ui->comboBoxModbusTool->itemText(SLAVE_WR_HOLD_REG);
        AddListWidgetItem(lable_string, current_index, MODBUS_SLAVE_TYPE, SLAVE_WR_HOLD_REG);
    }
    delete SlaveWriteHoldReg_dlg;
}

void InsideComm::AddSlaveWriteInputReg()
{
    int current_index = ui->listWidgetData->count();
    IntercomMultiRegDialog *SlaveWriteInputReg_dlg = new IntercomMultiRegDialog;
    SlaveWriteInputReg_dlg->SetDlgType(0);
    SlaveWriteInputReg_dlg->SetDataListIndex(current_index);
    SlaveWriteInputReg_dlg->SetModbusMode(MODBUS_SLAVE_TYPE);
    SlaveWriteInputReg_dlg->SetToolType(SLAVE_WR_INPUT_REG);
    SlaveWriteInputReg_dlg->IniRegData();
    int ret = SlaveWriteInputReg_dlg->exec();
    if(ret == QDialog::Accepted){
        QString lable_string = ui->comboBoxModbusTool->itemText(SLAVE_WR_INPUT_REG);
        AddListWidgetItem(lable_string, current_index, MODBUS_SLAVE_TYPE, SLAVE_WR_INPUT_REG);
    }
    delete SlaveWriteInputReg_dlg;
}

void InsideComm::AddHostReadCoil()
{
    int current_index = ui->listWidgetData->count();
    IntercomWRMultiCoilDialog *HostReadCoil_dlg = new IntercomWRMultiCoilDialog;
    HostReadCoil_dlg->SetDataListIndex(current_index);
    HostReadCoil_dlg->SetModbusMode(MODBUS_HOST_TYPE);
    HostReadCoil_dlg->SetToolType(HOST_RD_COILS);
    HostReadCoil_dlg->IniMultiCoilData();
    int ret = HostReadCoil_dlg->exec();
    if(ret == QDialog::Accepted){
        QString lable_string = ui->comboBoxModbusTool->itemText(HOST_RD_COILS);
        AddListWidgetItem(lable_string, current_index, MODBUS_HOST_TYPE, HOST_RD_COILS);
    }
    delete HostReadCoil_dlg;
}

void InsideComm::AddHostWriteCoil()
{
    int current_index = ui->listWidgetData->count();
    IntercomWRMultiCoilDialog *HostWriteCoil_dlg = new IntercomWRMultiCoilDialog;
    HostWriteCoil_dlg->SetDataListIndex(current_index);
    HostWriteCoil_dlg->SetModbusMode(MODBUS_HOST_TYPE);
    HostWriteCoil_dlg->SetToolType(HOST_WR_COILS);
    HostWriteCoil_dlg->IniMultiCoilData();
    int ret = HostWriteCoil_dlg->exec();
    if(ret == QDialog::Accepted){
        QString lable_string = ui->comboBoxModbusTool->itemText(HOST_WR_COILS);
        AddListWidgetItem(lable_string, current_index, MODBUS_HOST_TYPE, HOST_WR_COILS);
    }
    delete HostWriteCoil_dlg;
}

void InsideComm::AddHostReadDiscrete()
{
    int current_index = ui->listWidgetData->count();
    IntercomWRMultiCoilDialog *HostReadDiscrete_dlg = new IntercomWRMultiCoilDialog;
    HostReadDiscrete_dlg->SetDataListIndex(current_index);
    HostReadDiscrete_dlg->SetModbusMode(MODBUS_HOST_TYPE);
    HostReadDiscrete_dlg->SetToolType(HOST_RD_DISCRETE);
    HostReadDiscrete_dlg->IniMultiCoilData();
    int ret = HostReadDiscrete_dlg->exec();
    if(ret == QDialog::Accepted){
        QString lable_string = ui->comboBoxModbusTool->itemText(HOST_RD_DISCRETE);
        AddListWidgetItem(lable_string, current_index, MODBUS_HOST_TYPE, HOST_RD_DISCRETE);
    }
    delete HostReadDiscrete_dlg;
}

void InsideComm::AddHostReadHoldReg()
{
    int current_index = ui->listWidgetData->count();
    IntercomReadRegDialog *HostReadHoldReg_dlg = new IntercomReadRegDialog;
    HostReadHoldReg_dlg->SetDataListIndex(current_index);
    HostReadHoldReg_dlg->SetModbusMode(MODBUS_HOST_TYPE);
    HostReadHoldReg_dlg->SetToolType(HOST_RD_HOLD_REG);
    HostReadHoldReg_dlg->IniRegData();
    int ret = HostReadHoldReg_dlg->exec();
    if(ret == QDialog::Accepted){
        QString lable_string = ui->comboBoxModbusTool->itemText(HOST_RD_HOLD_REG);
        AddListWidgetItem(lable_string, current_index, MODBUS_HOST_TYPE, HOST_RD_HOLD_REG);
    }
    delete HostReadHoldReg_dlg;
}

void InsideComm::AddHostWriteHoldReg()
{
    int current_index = ui->listWidgetData->count();
    IntercomMultiRegDialog *HostWriteHoldReg_dlg = new IntercomMultiRegDialog;
    HostWriteHoldReg_dlg->SetDlgType(0);
    HostWriteHoldReg_dlg->SetDataListIndex(current_index);
    HostWriteHoldReg_dlg->SetModbusMode(MODBUS_HOST_TYPE);
    HostWriteHoldReg_dlg->SetToolType(HOST_WR_HOLD_REG);
    HostWriteHoldReg_dlg->IniRegData();
    int ret = HostWriteHoldReg_dlg->exec();
    if(ret == QDialog::Accepted){
        QString lable_string = ui->comboBoxModbusTool->itemText(HOST_WR_HOLD_REG);
        AddListWidgetItem(lable_string, current_index, MODBUS_HOST_TYPE, HOST_WR_HOLD_REG);
    }
    delete HostWriteHoldReg_dlg;
}

void InsideComm::AddHostReadInputReg()
{
    int current_index = ui->listWidgetData->count();
    IntercomReadRegDialog *HostReadInputReg_dlg = new IntercomReadRegDialog;
    HostReadInputReg_dlg->SetDataListIndex(current_index);
    HostReadInputReg_dlg->SetModbusMode(MODBUS_HOST_TYPE);
    HostReadInputReg_dlg->SetToolType(HOST_RD_INPUT_REG);
    HostReadInputReg_dlg->IniRegData();
    int ret = HostReadInputReg_dlg->exec();
    if(ret == QDialog::Accepted){
        QString lable_string = ui->comboBoxModbusTool->itemText(HOST_RD_INPUT_REG);
        AddListWidgetItem(lable_string, current_index, MODBUS_HOST_TYPE, HOST_RD_INPUT_REG);
    }
    delete HostReadInputReg_dlg;
}

void InsideComm::on_btnAdd_clicked()
{
    if(ui->listWidgetData->count() >= MB_DATA_LIST_NUM_MAX){
        QMessageBox::StandardButton rb = QMessageBox::warning(NULL, tr("警告"), tr("数据流达到最大限制100条,不能再添加"), QMessageBox::Yes);
        return;
    }
    int size =ui->listWidgetData->count();
    list_cnt = size + 1;
    intercom_modbus_data_list_cnt_set(list_cnt);
    if(slave_or_host == MODBUS_SLAVE_TYPE){
        if(ui->comboBoxModbusTool->currentIndex() == SLAVE_RD_COILS){
            AddSlaveReadCoil();
        }else if(ui->comboBoxModbusTool->currentIndex() == SLAVE_WR_COILS){
            AddSlaveWriteCoil();
        }else if(ui->comboBoxModbusTool->currentIndex() == SLAVE_WR_DISCRETE){
            AddSlaveWriteDiscrete();
        }else if(ui->comboBoxModbusTool->currentIndex() == SLAVE_RD_HOLD_REG){
            AddSlaveReadHoldReg();
        }else if(ui->comboBoxModbusTool->currentIndex() == SLAVE_WR_HOLD_REG){
            AddSlaveWriteHoldReg();
        }else if(ui->comboBoxModbusTool->currentIndex() == SLAVE_WR_INPUT_REG){
            AddSlaveWriteInputReg();
        }
    }
    if(slave_or_host == MODBUS_HOST_TYPE){
        if(ui->comboBoxModbusTool->currentIndex() == HOST_RD_COILS){
            AddHostReadCoil();
        }else if(ui->comboBoxModbusTool->currentIndex() == HOST_WR_COILS){
            AddHostWriteCoil();
        }else if(ui->comboBoxModbusTool->currentIndex() == HOST_RD_DISCRETE){
            AddHostReadDiscrete();
        }else if(ui->comboBoxModbusTool->currentIndex() == HOST_RD_HOLD_REG){
            AddHostReadHoldReg();
        }else if(ui->comboBoxModbusTool->currentIndex() == HOST_WR_HOLD_REG){
            AddHostWriteHoldReg();
        }else if(ui->comboBoxModbusTool->currentIndex() == HOST_RD_INPUT_REG){
            AddHostReadInputReg();
        }
    }
}

void InsideComm::on_btnDelete_clicked()
{
    int row = ui->listWidgetData->currentRow();
    if(row >= 0){
        intercom_modbus_del_data_list(row);
        list_cnt--;
        intercom_modbus_data_list_cnt_set(list_cnt);
        QListWidgetItem *List_Item =  ui->listWidgetData->takeItem(row);
        delete List_Item;
    }
}

void InsideComm::on_btnUp_clicked()
{
    int row = ui->listWidgetData->currentRow();
    if(row > 0){
        intercom_modbus_data_list_move_up(row);

        QListWidgetItem *List_Item = ui->listWidgetData->item(row);
        QWidget *m_Widget = ui->listWidgetData->itemWidget(List_Item);

        QListWidgetItem *Pre_List_Item = ui->listWidgetData->item(row - 1);
        QWidget *Pre_Widget = ui->listWidgetData->itemWidget(Pre_List_Item);
        QString Pre_String = ((IntercomModbusDataListItem*)Pre_Widget)->GetLabelText();
        int Pre_Mode = ((IntercomModbusDataListItem*)Pre_Widget)->GetModbusMode();
        int Pre_Tool = ((IntercomModbusDataListItem*)Pre_Widget)->GetToolType();

        ((IntercomModbusDataListItem*)Pre_Widget)->SetLabelText(((IntercomModbusDataListItem*)m_Widget)->GetLabelText());
        ((IntercomModbusDataListItem*)Pre_Widget)->SetModbusMode(((IntercomModbusDataListItem*)m_Widget)->GetModbusMode());
        ((IntercomModbusDataListItem*)Pre_Widget)->SetToolType(((IntercomModbusDataListItem*)m_Widget)->GetToolType());

        ((IntercomModbusDataListItem*)m_Widget)->SetLabelText(Pre_String);
        ((IntercomModbusDataListItem*)m_Widget)->SetModbusMode(Pre_Mode);
        ((IntercomModbusDataListItem*)m_Widget)->SetToolType(Pre_Tool);

        ui->listWidgetData->setCurrentRow(row-1);
    }
}

void InsideComm::on_btnDown_clicked()
{
    int row = ui->listWidgetData->currentRow();
    if(row >= 0 && row < ui->listWidgetData->count() - 1){
        intercom_modbus_data_list_move_down(row);

        QListWidgetItem *List_Item = ui->listWidgetData->item(row);
        QWidget *m_Widget = ui->listWidgetData->itemWidget(List_Item);

        QListWidgetItem *Pre_List_Item = ui->listWidgetData->item(row + 1);
        QWidget *Pre_Widget = ui->listWidgetData->itemWidget(Pre_List_Item);
        QString Pre_String = ((IntercomModbusDataListItem*)Pre_Widget)->GetLabelText();
        int Pre_Mode = ((IntercomModbusDataListItem*)Pre_Widget)->GetModbusMode();
        int Pre_Tool = ((IntercomModbusDataListItem*)Pre_Widget)->GetToolType();

        ((IntercomModbusDataListItem*)Pre_Widget)->SetLabelText(((IntercomModbusDataListItem*)m_Widget)->GetLabelText());
        ((IntercomModbusDataListItem*)Pre_Widget)->SetModbusMode(((IntercomModbusDataListItem*)m_Widget)->GetModbusMode());
        ((IntercomModbusDataListItem*)Pre_Widget)->SetToolType(((IntercomModbusDataListItem*)m_Widget)->GetToolType());

        ((IntercomModbusDataListItem*)m_Widget)->SetLabelText(Pre_String);
        ((IntercomModbusDataListItem*)m_Widget)->SetModbusMode(Pre_Mode);
        ((IntercomModbusDataListItem*)m_Widget)->SetToolType(Pre_Tool);

        ui->listWidgetData->setCurrentRow(row+1);
    }
}

void InsideComm::on_tabWidget_currentChanged(int index)
{
    if(index == 1){
        IniSlaveOrHost();
    }
}
