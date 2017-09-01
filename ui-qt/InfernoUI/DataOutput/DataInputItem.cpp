#include "DataInputItem.h"
#include "ui_DataInputItem.h"
#include "TaskRstGlobal.h"
#include "RstData.h"
#include <QDebug>
#include <QMessageBox>
#include <QLineEdit>
#include <QComboBox>
#include <QRadioButton>
DataInputItem::DataInputItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataInputItem)
{
    ui->setupUi(this);
    LoadKeyBoardLib();
    Type_flag = 0;
    ui->comboBox_Data_type->addItem(tr("int"));
    ui->comboBox_Data_type->addItem(tr("unsigned int"));
    ui->comboBox_Data_type->addItem(tr("float"));
    ui->comboBox_Data_type->addItem(tr("double"));

    Data_type.insert(DATA_SINT, 0);
    Data_type.insert(DATA_UINT, 1);
    Data_type.insert(DATA_FLT, 2);
    Data_type.insert(DATA_DBL, 3);

    ui->lineEdit_Value->setEnabled(false);
    ui->comboBox_Data_type->setEnabled(false);
    ui->lineEdit_Value->installEventFilter(this);
}

DataInputItem::~DataInputItem()
{
    ui->lineEdit_Value->removeEventFilter(this);
    delete ui;
}

void DataInputItem::ShowInputDataID(int Id)
{
    ui->lineEdit_ID->setText(QString::number(Id));
}

void DataInputItem::ShowInputDataEnable(int flag)
{
    Type_flag = 0;
    if(flag == 1){
        ui->lineEdit_Value->setEnabled(true);
        ui->comboBox_Data_type->setEnabled(true);
        ui->radioButton_Enable->setChecked(true);
    }else{
        ui->radioButton_Enable->setChecked(false);
    }
}

void DataInputItem::ShowDynamicInputDataEnable(int flag)
{
    Type_flag = 1;
    ui->lineEdit_Value->removeEventFilter(this);
    ui->radioButton_Enable->setCheckable(true);
    if(flag == 1){
        ui->lineEdit_Value->setEnabled(true);
        ui->comboBox_Data_type->setEnabled(true);
        ui->radioButton_Enable->setChecked(true);
    }else{
        ui->radioButton_Enable->setChecked(false);
        ui->radioButton_Enable->setCheckable(false);
    }
}

void DataInputItem::ShowInputDataValue(unsigned int type, RESULTvalue value)
{
    int index = Data_type.value(type);
    ui->comboBox_Data_type->setCurrentIndex(index);
    if(type == DATA_SINT){
        ui->lineEdit_Value->setText(QString::number(value.I32_Value));
    }else if(type == DATA_UINT){
        ui->lineEdit_Value->setText(QString::number(value.U32_Value));
    }else if(type == DATA_FLT){
        ui->lineEdit_Value->setText(QString::number(value.F32_Value, 'g', 6));
    }else if(type == DATA_DBL){
        ui->lineEdit_Value->setText(QString::number(value.D64_Value, 'g', 6));
    }
}

void DataInputItem::ShowDynamicInputDataValue(unsigned int type, RESULTvalue value)
{
    int index = Data_type.value(type);
    ui->comboBox_Data_type->setCurrentIndex(index);
    QString com_str = ui->comboBox_Data_type->currentText();
    ui->comboBox_Data_type->clear();
    ui->comboBox_Data_type->addItem(com_str);
    if(type == DATA_SINT){
        ui->lineEdit_Value->setText(QString::number(value.I32_Value));
    }else if(type == DATA_UINT){
        ui->lineEdit_Value->setText(QString::number(value.U32_Value));
    }else if(type == DATA_FLT){
        ui->lineEdit_Value->setText(QString::number(value.F32_Value, 'g', 6));
    }else if(type == DATA_DBL){
        ui->lineEdit_Value->setText(QString::number(value.D64_Value, 'g', 6));
    }
}

void DataInputItem::SetInputData()
{
    RST_VALUE_STRUCT value;
    if(!ui->radioButton_Enable->isChecked()){
        value.resultflag = TASK_RESULT_INVALID_FLAG;
        G_Data_Set(G_DATA_MANUAL, ui->lineEdit_ID->text().toInt() - 1, &value);
        return;
    }
    int index = Data_type.key(ui->comboBox_Data_type->currentIndex());
    value.resulttype = index;
    if(index == DATA_SINT){
        SINT_RST_VALUE_SET(&value, 0, ui->lineEdit_Value->text().toInt());
    }else if(index == DATA_UINT){
        UINT_RST_VALUE_SET(&value, 0, ui->lineEdit_Value->text().toUInt());
    }else if(index == DATA_FLT){
        FLT_RST_VALUE_SET(&value, 0, ui->lineEdit_Value->text().toFloat());
    }else if(index == DATA_DBL){
        DBL_RST_VALUE_SET(&value, 0, ui->lineEdit_Value->text().toDouble());
    }
    G_Data_Set(G_DATA_MANUAL, ui->lineEdit_ID->text().toInt() - 1, &value);
}

bool DataInputItem::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->lineEdit_Value){
        if(event->type() == QEvent::MouseButtonPress)
        if(((QLineEdit *)watched)->isEnabled()){
            NumKeyBoardDlg(watched, event);
        }
    }
    return QWidget::eventFilter(watched, event);
}

void DataInputItem::LoadKeyBoardLib()
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

void DataInputItem::NumKeyBoardDlg(QObject *watched, QEvent *event)
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



void DataInputItem::on_radioButton_Enable_clicked()
{
    if(Type_flag == 1){
        ui->radioButton_Enable->setChecked(true);
        return;
    }
    if(ui->radioButton_Enable->isChecked()){
        ui->lineEdit_Value->setEnabled(true);
        ui->comboBox_Data_type->setEnabled(true);
    }else{
        ui->lineEdit_Value->setEnabled(false);
        ui->comboBox_Data_type->setEnabled(false);
    }
}
