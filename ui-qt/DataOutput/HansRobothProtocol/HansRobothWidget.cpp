#include "HansRobothWidget.h"
#include "ui_HansRobothWidget.h"

HansRobothWidget::HansRobothWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HansRobothWidget)
{
    ui->setupUi(this);
}

HansRobothWidget::~HansRobothWidget()
{
    delete ui;
}
