#include "UserDefinedDataItem.h"
#include "ui_UserDefinedDataItem.h"
#include "UserDefineSelectDialog.h"
#include <QDebug>
UserDefinedDataItem::UserDefinedDataItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserDefinedDataItem)
{
    ui->setupUi(this);
    m_include_Label_flag = 0;///<包括标签
    m_link_step = 0;///<关联步骤
    m_width_flag = 0;///<固定宽度
    m_data_width = 0;///<字段宽度
    m_fill = 0;///填充
}

UserDefinedDataItem::~UserDefinedDataItem()
{
    delete ui;
}



void UserDefinedDataItem::SetLabelString(QString str)
{
    m_Label_string = str;
    ui->DataLabel->setText(str);
}

void UserDefinedDataItem::SetTaskString(QString str)
{
    ui->TaskName_label->setText(str);
}


void UserDefinedDataItem::on_detail_pushButton_clicked()
{
    UserDefineSelectDialog *UserDefineDlg = new UserDefineSelectDialog;
    UserDefineDlg->SetDataListIndex(List_index);
    UserDefineDlg->EditModeInit();
    int ret = UserDefineDlg->exec();
    if(ret == QDialog::Accepted)
    {
        select_data = UserDefineDlg->GetSelectData();
        ui->TaskName_label->setText(select_data);
    }
    delete UserDefineDlg;
    UserDefineDlg = NULL;
}
