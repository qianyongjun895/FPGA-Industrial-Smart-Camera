#include <QDebug>
#include "CalcDataSelectDialog.h"
#include "ui_CalcDataSelectDialog.h"
#include "CalcuatorData.h"
#include <QMessageBox>
#include "ProtocolManageGlobal.h"

CalcDataSelectDialog::CalcDataSelectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CalcDataSelectDialog)
{
    ui->setupUi(this);
    LoadKeyBoardLib();
    m_Mul_index = 0;
    m_MaxAddress = 65535;
    if(m_data_source == SELECT_TASK_DATA || m_data_source == SELECT_CALC_DATA)
        ui->Okbtn->setEnabled(false);
    else
        ui->Okbtn->setEnabled(true);
    ui->lineEdit_manualInput->installEventFilter(this);
    ui->lineEdit_MbsAddr->installEventFilter(this);
    ui->lineEdit_StartAddr->installEventFilter(this);
    ui->lineEdit_Data_Input_Addr->installEventFilter(this);
    //connect(ui->listWidget_Data_list,&QListWidget::doubleClicked,this,&CalcDataSelectDialog::on_Okbtn_clicked);
    connect(ui->listWidget_Result,&QListWidget::doubleClicked,this,&CalcDataSelectDialog::on_Okbtn_clicked);
}

CalcDataSelectDialog::~CalcDataSelectDialog()
{
    ui->lineEdit_MbsAddr->removeEventFilter(this);
    ui->lineEdit_StartAddr->removeEventFilter(this);
    ui->lineEdit_manualInput->removeEventFilter(this);
    ui->lineEdit_Data_Input_Addr->removeEventFilter(this);
    delete ui;
}

void CalcDataSelectDialog::InitDataSelect(int source,int calc_cnt, int currentstep)
{
    //p_CalcData = p_CalcuatorData;
    i_currentStep = currentstep;
    m_data_source = source;
    ui->stackedWidget->setCurrentIndex(source);
    m_calc_item_cnt = calc_cnt;
    ui->stackedWidget->setCurrentIndex(source);
    switch (m_data_source) {
    case SELECT_INPUT_DATA:
        ui->radioButton_manual->setChecked(true);
        break;
    case SELECT_TASK_DATA:
        ui->radioButton_Ref->setChecked(true);
        break;
    case SELECT_MODBUS_DATA:
        ui->radioButton_Mbs->setChecked(true);
        break;
    case SELECT_CALC_DATA:
        ui->radioButton_Calc->setChecked(true);
        break;
    case SELECT_DATA_INPUT:
        ui->radioButton_Input->setChecked(true);
        break;
    default:
        break;
    }

}


void CalcDataSelectDialog::on_Okbtn_clicked()
{
    if(ui->stackedWidget->currentIndex() == SELECT_INPUT_DATA)
    {
        QString str = ui->lineEdit_manualInput->text();
        bool bOk;
        float fdata = str.toFloat(&bOk);

        if(!bOk)
        {
            QMessageBox::about(NULL,"提示","请输入浮点型数据!");
            return;
        }

        m_input_str = "I"+ui->lineEdit_manualInput->text();
    }
    if(ui->stackedWidget->currentIndex() == SELECT_TASK_DATA)
    {
        if(ui->listWidget_TaskList->count() > 0)
        {
            if(m_Mul_index == 0)
            {
                m_task_index = ui->listWidget_TaskList->currentRow()+1;
                m_result_index = ui->listWidget_Data_list->currentRow();
                m_task_str = "$"+ui->listWidget_TaskList->currentItem()->text().append(";")\
                        .append(ui->listWidget_Data_list->currentItem()->text());
            }
            else
            {
                m_task_index = ui->listWidget_TaskList->currentRow()+1;
                m_result_index = ui->listWidget_Data_list->currentRow();
                if(ui->listWidget_MulData->count() == 0)
                {
                    m_task_str = "$"+ui->listWidget_TaskList->currentItem()->text().append(";")\
                            .append(ui->listWidget_Data_list->currentItem()->text());
                }
                else
                {
                    m_Mul_data_index = ui->listWidget_MulData->currentRow();
                    m_task_str = "$"+ui->listWidget_TaskList->currentItem()->text().append(";")\
                            .append(ui->listWidget_Data_list->currentItem()->text())+";"+\
                            ui->listWidget_MulData->currentItem()->text();
                }
            }
        }
    }
    if(ui->stackedWidget->currentIndex() == SELECT_MODBUS_DATA)
    {
        if(ui->radioButton_HoldReg->isChecked())
            m_reg_type = 0;
        else
            m_reg_type = 1;
        m_data_type = ui->comboBox_DataType->currentIndex();
        m_address = ui->lineEdit_MbsAddr->text().toInt();
    }
    if(ui->stackedWidget->currentIndex() == SELECT_CALC_DATA)
    {
        if(ui->listWidget_CalcItem->count() > 0)
        {
            m_calc_item_index = ui->listWidget_CalcItem->currentRow();
            m_calc_result_index = ui->listWidget_Result->currentRow()+1;
            m_calc_str = "P"+ui->listWidget_CalcItem->currentItem()->text().append(";").append(ui->listWidget_Result->currentItem()->text());
        }
    }
    if(ui->stackedWidget->currentIndex() == SELECT_PLC_DATA)
    {
        m_plc_data_type = ui->comboBox_PLCDataType->currentIndex();
        m_plc_address = ui->lineEdit_StartAddr->text().toInt();
    }
    if(ui->stackedWidget->currentIndex() == SELECT_DATA_INPUT)
    {
        if(ui->lineEdit_Data_Input_Addr->text().toInt() == 0){
            QMessageBox::about(NULL,"提示","请输入大于0的int型数据!");
            return;
        }
        Data_Input_Addr = ui->lineEdit_Data_Input_Addr->text().toInt();

        if(ui->radioButton_manual->isChecked())
            Data_Input_Type = 0;
        else
            Data_Input_Type = 1;
        printf("Data_Input_Addr == %d  Data_Input_Type = %d\n",Data_Input_Addr,Data_Input_Type);
    }
    m_data_source = ui->stackedWidget->currentIndex();
    QDialog::accept();
}

void CalcDataSelectDialog::on_Cancelbtn_clicked()
{
    QDialog::reject();
}

void CalcDataSelectDialog::on_radioButton_HoldReg_toggled(bool checked)
{
    m_reg_type = 0;
}

void CalcDataSelectDialog::on_radioButton_InputReg_clicked()
{
    m_reg_type = 1;
}

void CalcDataSelectDialog::on_comboBox_DataType_activated(int index)
{
    m_data_type = ui->comboBox_DataType->currentIndex();
    if(index == 3 || index == 7)
    {
        m_MaxAddress = 65533;
    }
    else
        m_MaxAddress = 65535;
}


void CalcDataSelectDialog::on_comboBox_PLCDataType_activated(int index)
{
    m_plc_data_type = ui->comboBox_PLCDataType->currentIndex();
    if(index == 2)
    {
        m_MaxAddress = 65533;
    }
    else
        m_MaxAddress = 65535;
}

void CalcDataSelectDialog::on_listWidget_TaskList_currentTextChanged(const QString &currentText)
{
    CalcuatorData m_CalcuatorData;
    QStringList strdata;

    int m_task_index = currentText.split(".")[0].toInt();
    int i_mul_flag = m_CalcuatorData.GetTaskTypeFlag(m_task_index);//判断是否是多结果任务
    ui->Okbtn->setEnabled(false);
    ui->listWidget_Data_list->clear();
    ui->listWidget_MulData->clear();
    if(i_mul_flag != 0)//如果是多结果任务
    {
        m_Mul_index = 1;
        QStringList mul_result = m_CalcuatorData.GetTaskResultString(m_task_index);
        for(unsigned int i = 0;i < m_CalcuatorData.GetTaskMuchResultCount(m_task_index);i++)
        {
            ui->listWidget_Data_list->addItem(QString::number(i+1)+"."+mul_result[i]);
        }
    }else//不是多结果任务
    {
        m_Mul_index = 0;
        strdata = m_CalcuatorData.GetSendDataStringList(m_task_index,-1);
        for(int i = 0; i < strdata.count(); i++)
        {
            ui->listWidget_Data_list->addItem(QString::number(i+1)+"."+strdata[i]);
        }
    }
}

void CalcDataSelectDialog::on_listWidget_CalcItem_currentTextChanged(const QString &currentText)
{
    ui->listWidget_Result->clear();
    ui->listWidget_Result->addItem("1.结果1");
    ui->listWidget_Result->setCurrentRow(0);
//    ui->Okbtn->setEnabled(false);
}

void CalcDataSelectDialog::on_listWidget_Result_itemClicked(QListWidgetItem *item)
{
    ui->Okbtn->setEnabled(true);
}

void CalcDataSelectDialog::on_listWidget_Data_list_itemClicked(QListWidgetItem *item)
{
    CalcuatorData m_CalcuatorData;
    ui->listWidget_MulData->clear();
    if(m_Mul_index == 1)
    {
        int i_task_index = ui->listWidget_TaskList->currentItem()->text().split(".")[0].toInt();
        QStringList Mul_data = m_CalcuatorData.GetSendDataStringList(i_task_index,ui->listWidget_Data_list->currentRow());
        for(int i = 0; i < Mul_data.count(); i++)
        {
            ui->listWidget_MulData->addItem(QString::number(i+1)+"."+Mul_data[i]);
        }
        if(ui->listWidget_MulData->count() > 0){
            ui->listWidget_MulData->setCurrentRow(0);
        }
        ui->Okbtn->setEnabled(true);
//        if(ui->listWidget_MulData->count() == 0)
//        {
//            ui->Okbtn->setEnabled(true);
//        }else
//        {
//            ui->Okbtn->setEnabled(false);
//        }
    }
    else
    {
        ui->Okbtn->setEnabled(true);
    }


}


bool CalcDataSelectDialog::eventFilter(QObject *watched, QEvent *event)
{
//    if(((QLineEdit *)watched)->isReadOnly() || !((QLineEdit *)watched)->isEnabled())
//    {
//        return QWidget::eventFilter(watched, event);
//    }
/*
    if (watched == ui->lineEdit_manualInput)         //首先判断控件(这里指 lineEdit1)
    {
         if (event->type()==QEvent::MouseButtonPress)     //然后再判断控件的具体事件 (这里指点击事件)
         {
             KeyboardDlg *dlg = new KeyboardDlg();
             dlg->SetInputString(ui->lineEdit_manualInput->text());
             int ret = dlg->exec();
             if(ret == QDialog::Accepted)
             {
                 ui->lineEdit_manualInput->setText(dlg->GetInputString());
             }
             delete dlg;
         }
    }
    return QWidget::eventFilter(watched, event);
    */
    QList<QLineEdit *> lineEdit = this->findChildren<QLineEdit *>();
    foreach (QLineEdit * L, lineEdit) {
        if (L->objectName() == watched->objectName() && L->isEnabled()) {
            if (event->type()==QEvent::MouseButtonPress){
//                NumKeyBoard dlg;
//                dlg.SetOldNum(((QLineEdit *)watched)->text());
//                int ret = dlg.exec();
//                if(ret == QDialog::Accepted)
//                {
//                    QString strAddr = dlg.GetNum();
//                    if(watched == ui->lineEdit_MbsAddr || watched == ui->lineEdit_StartAddr)
//                    {
//                        int addr = strAddr.toInt();
//                        if(addr > m_MaxAddress)
//                            strAddr = QString::number(m_MaxAddress);
//                    }
//                    ((QLineEdit *)watched)->setText(strAddr);
//                }

                    NumKeyBoardDlg(watched, event);

            }
        }
    }
    return QWidget::eventFilter(watched, event);
}

void CalcDataSelectDialog::LoadKeyBoardLib()
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

void CalcDataSelectDialog::NumKeyBoardDlg(QObject *watched, QEvent *event)
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
                if(watched == ui->lineEdit_MbsAddr || watched == ui->lineEdit_StartAddr || watched == ui->lineEdit_Data_Input_Addr){
                    if(num.toInt() > m_MaxAddress){
                        num = QString::number(m_MaxAddress);
                    }
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


void CalcDataSelectDialog::on_listWidget_MulData_itemClicked(QListWidgetItem *item)
{
    ui->Okbtn->setEnabled(true);
}


void CalcDataSelectDialog::on_radioButton_manual_clicked()
{
    m_data_source = SELECT_INPUT_DATA;
    ui->stackedWidget->setCurrentIndex(0);
    ui->lineEdit_manualInput->setText(m_input_str);
}

void CalcDataSelectDialog::on_radioButton_Ref_clicked()
{
    m_data_source = SELECT_TASK_DATA;
    CalcuatorData m_CalcuatorData;
    ui->stackedWidget->setCurrentIndex(1);
    ui->listWidget_TaskList->clear();
    QString Task_Str;
    for(int i = 0; i < i_currentStep-1;i++)
    {
        Task_Str = m_CalcuatorData.GetTaskListString(i+1);
        if(!Task_Str.isEmpty())
        {
            ui->listWidget_TaskList->addItem(Task_Str);
        }
    }
    ui->listWidget_TaskList->setCurrentRow(0);
}

void CalcDataSelectDialog::on_radioButton_Mbs_clicked()
{
    m_data_source = SELECT_MODBUS_DATA;
    ui->stackedWidget->setCurrentIndex(2);
    PROTOCOL_SELECT protocol;
    protocol_select_get(&protocol);
    if(protocol.protocol_type == MODBUS_PROTOCOL && protocol.protocol_status == PROTOCOL_ACTIVE){
        ui->radioButton_HoldReg->setChecked(true);
        ui->comboBox_DataType->setCurrentIndex(0);
        ui->lineEdit_MbsAddr->setText("1");
        ui->Okbtn->setEnabled(true);
    }else{
        ui->radioButton_HoldReg->setEnabled(false);
        ui->radioButton_InputReg->setEnabled(false);
        ui->comboBox_DataType->setEnabled(false);
        ui->lineEdit_MbsAddr->setEnabled(false);
        ui->Okbtn->setEnabled(false);
    }

}

void CalcDataSelectDialog::on_radioButton_Calc_clicked()
{
    m_data_source = SELECT_CALC_DATA;
    ui->Okbtn->setEnabled(true);
    ui->stackedWidget->setCurrentIndex(3);
    ui->listWidget_CalcItem->clear();
    ui->listWidget_Result->clear();
    if(m_calc_item_cnt > 0)
    {
        for(int i = 0; i < m_calc_item_cnt; i++)
        {
            ui->listWidget_CalcItem->addItem(QString::number(i+1).append(".").append("算式").append(QString::number(i+1)));
        }
        ui->listWidget_Result->addItem("1.结果1");
        ui->listWidget_CalcItem->setCurrentRow(0);
        ui->listWidget_Result->setCurrentRow(0);
    }
}

void CalcDataSelectDialog::on_radioButton_Input_clicked()
{
    m_data_source = SELECT_DATA_INPUT;
    ui->stackedWidget->setCurrentIndex(5);
    ui->radioButton_ManualSet->setChecked(true);
    ui->lineEdit_Data_Input_Addr->setText("1");
    m_MaxAddress = 128;
    ui->Okbtn->setEnabled(true);
}

