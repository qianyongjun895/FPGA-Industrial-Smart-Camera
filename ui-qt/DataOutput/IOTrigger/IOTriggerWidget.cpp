#include "IOTriggerWidget.h"
#include "ui_IOTriggerWidget.h"
#include <QMessageBox>
#include <QDebug>
#include <stdio.h>
#include "TaskHeaderGlobal.h"
#include "TaskStepGlobal.h"
#include "xmlInitGlobal.h"
#include "LinkDataGlobal.h"
#include "IOInitGlobal.h"
IOTriggerWidget::IOTriggerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IOTriggerWidget)
{
    ui->setupUi(this);

    LoadKeyBoardLib();

    QStringList IO_CbBItems_String;

    IO_CbBItems_String.append(tr("上升沿"));
    IO_CbBItems_String.append(tr("下降沿"));
    IO_CbBItems_String.append(tr("高电平"));
    IO_CbBItems_String.append(tr("低电平"));

    Trigger_Type_Hash.insert(tr("收到上升沿信号"), RISE_EDGE_TRIGGER);
    Trigger_Type_Hash.insert(tr("收到下降沿信号"), FALL_EDGE_TRIGGER);
    Trigger_Type_Hash.insert(tr("收到高电平信号"), HIGH_LEVEL_TRIGGER);
    Trigger_Type_Hash.insert(tr("收到低电平信号"), LOW_LEVEL_TRIGGER);

    ui->IO1TriggerTypeCbB->addItems(IO_CbBItems_String);
    ui->IO2TriggerTypeCbB->addItems(IO_CbBItems_String);

    ui->IO1DelayMsEdit->installEventFilter(this);
    ui->IO1SmoothingEdit->installEventFilter(this);

    ui->IO2DelayMsEdit->installEventFilter(this);
    ui->IO2SmoothingEdit->installEventFilter(this);

    memset(&IO_triggerParam, 0, sizeof(IO_TRIGGER_CONFIG));
    IO_Trigger_Config_Get(&IO_triggerParam);
    GetIOTriggerParam();

    connect(&IO1_test_time, &QTimer::timeout, this, &IOTriggerWidget::IO1_Trigger_Test_Slot);
    connect(&IO2_test_time, &QTimer::timeout, this, &IOTriggerWidget::IO2_Trigger_Test_Slot);
}

IOTriggerWidget::~IOTriggerWidget()
{

    disconnect(&IO1_test_time, &QTimer::timeout, this, &IOTriggerWidget::IO1_Trigger_Test_Slot);
    disconnect(&IO2_test_time, &QTimer::timeout, this, &IOTriggerWidget::IO2_Trigger_Test_Slot);

    ui->IO1DelayMsEdit->removeEventFilter(this);
    ui->IO1SmoothingEdit->removeEventFilter(this);

    ui->IO2DelayMsEdit->removeEventFilter(this);
    ui->IO2SmoothingEdit->removeEventFilter(this);
    if(m_keyBoard_Lib.isLoaded())
    {
        m_keyBoard_Lib.unload();
    }
    delete ui;
}

void IOTriggerWidget::GetIOTriggerParam()
{
    ui->IO1DelayMsEdit->setText(QString::number(IO_triggerParam.IO1_delay, 'f', 3));
    ui->IO1SmoothingEdit->setText(QString::number(IO_triggerParam.IO1_jitters_timer, 'f', 3));

    ui->IO2DelayMsEdit->setText(QString::number(IO_triggerParam.IO2_delay, 'f', 3));
    ui->IO2SmoothingEdit->setText(QString::number(IO_triggerParam.IO2_jitters_timer, 'f', 3));
}

void IOTriggerWidget::SetIOTriggerParam()
{
    if(ui->IO1DelayMsEdit->text() != "")
        IO_triggerParam.IO1_delay = ui->IO1DelayMsEdit->text().toFloat();
    if(ui->IO1SmoothingEdit->text() != "")
        IO_triggerParam.IO1_jitters_timer = ui->IO1SmoothingEdit->text().toFloat();

    if(ui->IO2DelayMsEdit->text() != "")
        IO_triggerParam.IO2_delay = ui->IO2DelayMsEdit->text().toFloat();
    if(ui->IO2SmoothingEdit->text() != "")
        IO_triggerParam.IO2_jitters_timer = ui->IO2SmoothingEdit->text().toFloat();

    Set_IO_Trigger_Param(0, IO_triggerParam.IO1_delay, IO_triggerParam.IO1_jitters_timer);
    Set_IO_Trigger_Param(1, IO_triggerParam.IO2_delay, IO_triggerParam.IO2_jitters_timer);
    IO_Config_Save();
    IO_Trigger_Config_Set(&IO_triggerParam);
}

bool IOTriggerWidget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->IO1DelayMsEdit || watched == ui->IO1SmoothingEdit || \
            watched == ui->IO2DelayMsEdit || watched == ui->IO2SmoothingEdit)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            NumKeyBoardDlg(watched, event, 0, 0);
            SetIOTriggerParam();
        }
    }
    return QWidget::eventFilter(watched, event);
}

void IOTriggerWidget::LoadKeyBoardLib()
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

void IOTriggerWidget::NumKeyBoardDlg(QObject *watched, QEvent *event, int Min_value, int Max_value)
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
                if(!(Max_value == 0 && Min_value == 0))
                {
                    if(num.toInt() > Max_value || num.toInt() < Min_value)
                    {
                        QMessageBox::about(NULL, tr("提示"), tr("该值无效,请输入")+QString::number(Min_value)+tr("~")+QString::number(Max_value)+tr("之间的值"));
                        return;
                    }
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

void IOTriggerWidget::ClearListWidget()
{
    int size = ui->TaskTriggerSetListWidget->count();
    for(int i = size; i >= 0 ; i--)
    {
        QListWidgetItem *item = ui->TaskTriggerSetListWidget->takeItem(i);
        delete item;
    }
}

void IOTriggerWidget::AddTaskListItem(ListWidgetIOTriggerItem* item)
{
    item->setAttribute(Qt::WA_DeleteOnClose);
    int size = ui->TaskTriggerSetListWidget->count();
    QListWidgetItem* list_item = new QListWidgetItem(ui->TaskTriggerSetListWidget);
    ui->TaskTriggerSetListWidget->setItemWidget(list_item, (QWidget*)item);
    ui->TaskTriggerSetListWidget->item(size)->setSizeHint(QSize(240,45));
    ui->TaskTriggerSetListWidget->setCurrentRow(0);
}

void IOTriggerWidget::on_tabWidget_currentChanged(int index)
{
    if(index == 1)
    {
        ClearListWidget();
        char taskName[40];
        for(unsigned int i = 0; i < GetTaskStepCount(); i ++)
        {
            memset(taskName, 0, 40);
            int ret = Get_Task_Name(i+1, taskName);
            if(ret != -1)
            {
                ListWidgetIOTriggerItem *item = new ListWidgetIOTriggerItem;
                item->SetTaskName(QString::number(i+1) +"."+ QString::fromUtf8(taskName));
                AddTaskListItem(item);
            }
        }
    }
}

void IOTriggerWidget::on_IO1TestButton_clicked()
{
    Test_Flag = 0;
    IO_Tigger_Test_Init(ui->IO1TriggerTypeCbB->currentIndex()+1);
    IO1_test_time.start(100);
}

void IOTriggerWidget::on_IO2TestButton_clicked()
{
    Test_Flag = 0;
    IO_Tigger_Test_Init(ui->IO2TriggerTypeCbB->currentIndex()+1);
    IO2_test_time.start(100);
}

void IOTriggerWidget::IO1_Trigger_Test_Slot()
{
    if(Test_Flag < 50){
        int ret = IO_Trigger_Test(INPUT_PIN0_MASK);
        if(ret == 0){
            Test_Flag++;
        }else{
            if(Trigger_Type_Hash.key(ret) != NULL)
                ui->IO1TestResultLabel->setText(Trigger_Type_Hash.key(ret));
            IO1_test_time.stop();
        }
    }else{
        IO1_test_time.stop();
        ui->IO1TestResultLabel->setText(tr("IO触发超时"));
    }
}

void IOTriggerWidget::IO2_Trigger_Test_Slot()
{
    if(Test_Flag < 50){
        int ret = IO_Trigger_Test(INPUT_PIN1_MASK);
        if(ret == 0){
            Test_Flag++;
        }else{
            if(Trigger_Type_Hash.key(ret) != NULL)
                ui->IO2TestResultLabel->setText(Trigger_Type_Hash.key(ret));
            IO2_test_time.stop();
        }
    }else{
        IO2_test_time.stop();
        ui->IO2TestResultLabel->setText(tr("IO触发超时"));
    }
}
