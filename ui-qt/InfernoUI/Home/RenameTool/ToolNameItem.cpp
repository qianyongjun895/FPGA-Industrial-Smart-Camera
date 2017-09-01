#include "ToolNameItem.h"
#include "ui_ToolNameItem.h"

ToolNameItem::ToolNameItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ToolNameItem)
{
    ui->setupUi(this);
}

ToolNameItem::~ToolNameItem()
{
    delete ui;
}
void ToolNameItem::SetName(QString strName,QString strReName)
{
    ui->labelName->setText(strName);
    ui->labelRename->setText(strReName);
}
void ToolNameItem::SetReName(QString strReName)
{
    ui->labelRename->setText(strReName);
}
QString ToolNameItem::GetName()
{
    QString strRet;
    int index = ui->labelName->text().indexOf('.');
    if(index > 0)
        strRet = ui->labelName->text().right(ui->labelName->text().length()-index-1);
    else
        strRet = ui->labelName->text();
    return strRet;
}
QString ToolNameItem::GetRename()
{
    QString strRet;
    int index = ui->labelRename->text().indexOf('.');
    if(index > 0)
        strRet = ui->labelRename->text().right(ui->labelRename->text().length()-index-1);
    else
        strRet = ui->labelRename->text();
    return strRet;
}
