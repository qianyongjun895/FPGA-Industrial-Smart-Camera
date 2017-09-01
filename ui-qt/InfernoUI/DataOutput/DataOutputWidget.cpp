#include "DataOutputWidget.h"
#include "ui_DataOutputWidget.h"
#include "stdio.h"
#include <QDebug>
#include "InsideComm/InsideComm.h"
#include "HeartBeatWidget.h"

DataOutputWidget::DataOutputWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataOutputWidget)
{
    ui->setupUi(this);

    m_btn_pre = ui->ExternalpushButton;
    ComViewLayout = new QGridLayout;
    on_IOpushButton_clicked();
}

DataOutputWidget::~DataOutputWidget()
{
    delete ui;
}

void DataOutputWidget::DeleteWidgetInLayout()
{

    for(int i=0; i<ComViewLayout->count(); ++i)
    {
        QWidget* widget = ComViewLayout->itemAt(i)->widget();
        ComViewLayout->removeWidget(widget);
        widget->setParent(0);
        if(widget !=NULL)
        {
            delete widget;
            widget = NULL;
        }
    }
}

void DataOutputWidget::SetButtonStyle(QPushButton *pre, QPushButton *current)
{
    if(pre != NULL)
    {
        pre->setStyleSheet("background-color: rgb(255, 255, 255);");
    }
    if(current != NULL)
    {
        current->setStyleSheet("background-color: rgb(249, 220, 117);");
    }
}

void DataOutputWidget::on_IOpushButton_clicked()
{
    if(m_btn_pre->objectName() == ui->IOpushButton->objectName()){
        return;
    }
    DeleteWidgetInLayout();
    SetButtonStyle(m_btn_pre, ui->IOpushButton);
    m_btn_pre = ui->IOpushButton;
    IOWidget = new IOSetWidget;
    ComViewLayout->setContentsMargins(0,0,0,0);
    ComViewLayout->addWidget(IOWidget, 0, 0);
    ui->Commwidget->setLayout(ComViewLayout);
}

void DataOutputWidget::on_ExternalpushButton_clicked()
{
    if(m_btn_pre->objectName() == ui->ExternalpushButton->objectName()){
        return;
    }
    DeleteWidgetInLayout();
    SetButtonStyle(m_btn_pre, ui->ExternalpushButton);
    m_btn_pre = ui->ExternalpushButton;
    CommWidget = new ExternalCommWidget;
    ComViewLayout->setContentsMargins(0,0,0,0);
    ComViewLayout->addWidget(CommWidget, 0, 0);
    ui->Commwidget->setLayout(ComViewLayout);
}

void DataOutputWidget::on_InsidepushButton_clicked()
{
    if(m_btn_pre->objectName() == ui->InsidepushButton->objectName()){
        return;
    }
    DeleteWidgetInLayout();
    SetButtonStyle(m_btn_pre, ui->InsidepushButton);
    m_btn_pre = ui->InsidepushButton;
    InsideComm *Inside = new InsideComm;
    ComViewLayout->setContentsMargins(0,0,0,0);
    ComViewLayout->addWidget(Inside, 0, 0);
    ui->Commwidget->setLayout(ComViewLayout);
}



void DataOutputWidget::on_PushButton_Data_Input_clicked()
{
    if(m_btn_pre->objectName() == ui->PushButton_Data_Input->objectName()){
        return;
    }
    DeleteWidgetInLayout();
    SetButtonStyle(m_btn_pre, ui->PushButton_Data_Input);
    m_btn_pre = ui->PushButton_Data_Input;
    InputDataWidget = new DataInputWidget;
    ComViewLayout->setContentsMargins(0,0,0,0);
    ComViewLayout->addWidget(InputDataWidget, 0, 0);
    ui->Commwidget->setLayout(ComViewLayout);
}

void DataOutputWidget::on_PushButton_HeartBeat_clicked()
{
    if(m_btn_pre->objectName() == ui->PushButton_HeartBeat->objectName()){
        return;
    }
    DeleteWidgetInLayout();
    SetButtonStyle(m_btn_pre, ui->PushButton_HeartBeat);
    m_btn_pre = ui->PushButton_HeartBeat;
    HeartBeatWidget* widget = new HeartBeatWidget;
    ComViewLayout->setContentsMargins(0,0,0,0);
    ComViewLayout->addWidget(widget, 0, 0);
    ui->Commwidget->setLayout(ComViewLayout);
}
