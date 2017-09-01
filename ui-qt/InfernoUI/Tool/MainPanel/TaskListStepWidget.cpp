#include "TaskListStepWidget.h"
#include "ui_TaskListStepWidget.h"

TaskListStepWidget::TaskListStepWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TaskListStepWidget)
{
    ui->setupUi(this);
}

TaskListStepWidget::~TaskListStepWidget()
{
    delete ui;
}

void TaskListStepWidget::SetStepIcon(QString iconPath)
{
    QPixmap pix = QPixmap(iconPath);
//    ui->stepIconLabel->setStyleSheet("QLabel{background-image: url(:/res/on.png);"
//                                     "background-position:center left;"
//                                     "background-repeat: no-repeat}");
    ui->stepIconLabel->setPixmap(pix);
}

void TaskListStepWidget::SetStepStatus(QString color)
{
    ui->statusLabel->setStyleSheet(color); //("background-color:green");
}

void TaskListStepWidget::SetStepName(QString name)
{
    ui->stepNameLabel->setText(name);
}

QString TaskListStepWidget::GetStepName()
{
    return ui->stepNameLabel->text();
}

