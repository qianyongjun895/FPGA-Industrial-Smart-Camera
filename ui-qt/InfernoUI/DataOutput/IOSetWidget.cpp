#include "IOSetWidget.h"
#include "ui_IOSetWidget.h"
#include <QMessageBox>
#include <QDebug>
#include <stdio.h>
IOSetWidget::IOSetWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IOSetWidget)
{
    ui->setupUi(this);
    IOOutputLayout = new QGridLayout;
    IOTriggetLayout = new QGridLayout;

    IO_Output_Lib.setFileName("./UILib/libIOOutput.so");
    if(IO_Output_Lib.load())
    {
        LoadIOOutputWidget();
    }
    else
    {
        qDebug()<<"Load ./UILib/libIOOutput.so ERR "<<IO_Output_Lib.errorString();
    }
    IOOutputLayout->setContentsMargins(0,0,0,0);
    IOOutputLayout->addWidget(IO_Output_Widget, 0, 0);
    ui->widget_IOOutput->setLayout(IOOutputLayout);

    IO_Trigger_Lib.setFileName("./UILib/libIOTrigger.so");
    if(IO_Trigger_Lib.load())
    {
        LoadIOTriggerWidget();
    }
    else
    {
        qDebug()<<"Load ./UILib/libIOTrigger.so ERR "<<IO_Trigger_Lib.errorString();
    }
    IOTriggetLayout->setContentsMargins(0,0,0,0);
    IOTriggetLayout->addWidget(IO_Trigger_Widget, 0, 0);
    ui->Widget_IOTrigger->setLayout(IOTriggetLayout);

    QString tabBarStyle = "QTabBar::tab {min-width:80px;color: rgb(0,0,0);border: 1px solid;border-top-left-radius: 10px;border-top-right-radius: 10px;padding:5px;}\
    QTabBar::tab:!selected {margin-top: 5px;background: rgb(230, 230, 230);} \
    QTabBar::tab:selected {color: rgb(0,0,0);background: rgb(249,220, 117);}";
    ui->tabWidget->setStyleSheet(tabBarStyle);
}

IOSetWidget::~IOSetWidget()
{
    delete ui;
}

void IOSetWidget::LoadIOOutputWidget()
{
    Fun_GetToolWidget GetIOOutputWidget = (Fun_GetToolWidget)IO_Output_Lib.resolve("GetWidget");
    if(GetIOOutputWidget)
    {
        IO_Output_Widget = GetIOOutputWidget();
    }
    else
    {
        IO_Output_Widget = NULL;
        QMessageBox::information(NULL,"提示","获取GetWidget函数名失败!");
    }
}

void IOSetWidget::LoadIOTriggerWidget()
{
    Fun_GetToolWidget GetIOOutputWidget = (Fun_GetToolWidget)IO_Trigger_Lib.resolve("GetWidget");
    if(GetIOOutputWidget)
    {
        IO_Trigger_Widget = GetIOOutputWidget();

    }
    else
    {
        IO_Trigger_Widget = NULL;
        QMessageBox::information(NULL,"提示","获取GetWidget函数名失败!");
    }
}

void IOSetWidget::on_tabWidget_currentChanged(int index)
{
//    if(index == 0)
//    {
//        if(IO_Output_Lib.isLoaded())
//        {
//            LoadIOOutputWidget();
//        }
//        else
//        {
//            IO_Output_Lib.setFileName("./UILib/libIOOutput.so");
//            if(IO_Output_Lib.load())
//            {
//                LoadIOOutputWidget();
//            }
//            else
//            {
//                qDebug()<<"Load ./UILib/libIOOutput.so ERR "<<IO_Output_Lib.errorString();
//            }
//        }
//    }
//    else
//    {
//        if(IO_Trigger_Lib.isLoaded())
//        {
//            LoadIOTriggerWidget();
//        }
//        else
//        {
//            IO_Trigger_Lib.setFileName("./UILib/libIOTrigger.so");
//            if(IO_Trigger_Lib.load())
//            {
//                LoadIOTriggerWidget();
//            }
//            else
//            {
//                qDebug()<<"Load ./UILib/libIOTrigger.so ERR "<<IO_Trigger_Lib.errorString();
//            }
//        }
//    }
}
