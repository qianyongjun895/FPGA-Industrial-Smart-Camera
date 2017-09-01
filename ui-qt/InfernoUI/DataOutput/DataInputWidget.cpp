#include "DataInputWidget.h"
#include "ui_DataInputWidget.h"
#include <QListWidgetItem>
#include "DataInputItem.h"
#include "TaskRstGlobal.h"
#include "BaseStruct.h"
#include <QDebug>
#include <QMessageBox>
DataInputWidget::DataInputWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataInputWidget)
{
    ui->setupUi(this);
    LoadKeyBoardLib();
    page_index = 1;
    dynamic_page_index = 1;
    ShowItemData();
    ShowDynamicItemData();
    ui->lineEdit_Page->installEventFilter(this);
    ui->lineEdit_Page_dynamic->installEventFilter(this);

    QString tabBarStyle = "QTabBar::tab {min-width:80px;color: rgb(0,0,0);border: 1px solid;border-top-left-radius: 10px;border-top-right-radius: 10px;padding:5px;}\
    QTabBar::tab:!selected {margin-top: 5px;background: rgb(230, 230, 230);} \
    QTabBar::tab:selected {color: rgb(0,0,0);background: rgb(249,220, 117);}";
    ui->tabWidget->setStyleSheet(tabBarStyle);
}

DataInputWidget::~DataInputWidget()
{
    ui->lineEdit_Page->removeEventFilter(this);
    ui->lineEdit_Page_dynamic->removeEventFilter(this);
    SetItemData();
    G_Data_Save();
    delete ui;
}

bool DataInputWidget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->lineEdit_Page || watched == ui->lineEdit_Page_dynamic){
        if(event->type() == QEvent::MouseButtonPress){
            if(((QLineEdit *)watched)->isEnabled()){
                NumKeyBoardDlg(watched, event, 1, 128);
            }
        }
    }
    return QWidget::eventFilter(watched, event);
}

void DataInputWidget::SetItemData()
{
    for(int i = 0; i < 8; i++){
        QListWidgetItem *widgetItem = ui->listWidget->item(i);
        QWidget *ItemData = ui->listWidget->itemWidget(widgetItem);
        ((DataInputItem*)ItemData)->SetInputData();
    }
}

void DataInputWidget::LoadKeyBoardLib()
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

void DataInputWidget::NumKeyBoardDlg(QObject *watched, QEvent *event, int Min_value, int Max_value)
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

void DataInputWidget::ShowItemData()
{
    ui->label_Current_index->setText(QString::number(page_index));
    ui->listWidget->clear();
    for(int i = 0; i < 8; i++){
        int index = i+(page_index-1)*8;
        RST_VALUE_STRUCT value;
        DataInputItem* Input_Item = new DataInputItem;
        int ret = G_Data_Get(G_DATA_MANUAL, index, &value);
        Input_Item->ShowInputDataEnable(0);
        if(value.resultflag == TASK_RESULT_VALID_FLAG && ret == 0){
            Input_Item->ShowInputDataEnable(1);
            Input_Item->ShowInputDataValue(value.resulttype, value.value);
        }
        Input_Item->ShowInputDataID(index + 1);
        QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
        ui->listWidget->setItemWidget(item, (QWidget*)Input_Item);
        ui->listWidget->item(i)->setSizeHint(QSize(240,50));
    }
}

void DataInputWidget::ShowDynamicItemData()
{
    ui->label_Current_index_dynamic->setText(QString::number(dynamic_page_index));
    ui->listWidget_dynamic->clear();
    for(int i = 0; i < 8; i++){
        int index = i+(dynamic_page_index-1)*8;
        RST_VALUE_STRUCT value;
        DataInputItem* Input_Item = new DataInputItem;
        int ret = G_Data_Get(G_DATA_DYNAMIC, index, &value);
        Input_Item->ShowDynamicInputDataEnable(0);
        if(value.resultflag == TASK_RESULT_VALID_FLAG && ret == 0){
            Input_Item->ShowDynamicInputDataEnable(1);
            Input_Item->ShowDynamicInputDataValue(value.resulttype, value.value);
        }
        Input_Item->ShowInputDataID(index + 1);
        QListWidgetItem *item = new QListWidgetItem(ui->listWidget_dynamic);
        ui->listWidget_dynamic->setItemWidget(item, (QWidget*)Input_Item);
        ui->listWidget_dynamic->item(i)->setSizeHint(QSize(240,50));
    }
}

void DataInputWidget::on_pushButton_Down_clicked()
{
    if(page_index == 1){
        return;
    }
    SetItemData();
    page_index--;
    ShowItemData();
}

void DataInputWidget::on_pushButton_Up_clicked()
{
    if(page_index == 128){
        return;
    }
    SetItemData();
    page_index++;
    ShowItemData();
}

void DataInputWidget::on_pushButton_GO_clicked()
{
    if(!ui->lineEdit_Page->text().isEmpty()){
        int index = ui->lineEdit_Page->text().toInt();
        SetItemData();
        page_index = index;
        ShowItemData();
    }
}

void DataInputWidget::on_tabWidget_currentChanged(int index)
{

}

void DataInputWidget::on_pushButton_Down_dynamic_clicked()
{
    if(dynamic_page_index == 1){
        return;
    }
    dynamic_page_index--;
    ShowDynamicItemData();
}

void DataInputWidget::on_pushButton_Up_dynamic_clicked()
{
    if(dynamic_page_index == 128){
        return;
    }
    dynamic_page_index++;
    ShowDynamicItemData();
}

void DataInputWidget::on_pushButton_GO_dynamic_clicked()
{
    if(!ui->lineEdit_Page_dynamic->text().isEmpty()){
        int index = ui->lineEdit_Page_dynamic->text().toInt();
        dynamic_page_index = index;
        ShowDynamicItemData();
    }
}
