#include <QDir>
#include "ToolMainTypeDialog.h"
#include "ui_ToolMainTypeDialog.h"
#include <QMessageBox>
#include "Comm/ControlStyle.h"
#include "Comm/FileIniControl.h"
#include "Comm/FileIniControl.h"
#include "Comm/GlobalParameter.h"
#include <qdebug.h>
ToolMainTypeDialog::ToolMainTypeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ToolMainTypeDialog)
{
    ui->setupUi(this);
    InitTask();
}

ToolMainTypeDialog::~ToolMainTypeDialog()
{
    delete ui;
}
void ToolMainTypeDialog::InitTask()
{
    int count = GlobalParameter::m_vt_className.count();
    int i = 0;

    for(i=0; i<count;i++)
    {
        QString strClassName = GlobalParameter::m_vt_className[i];
        QString strClassIcon = GlobalParameter::m_vt_classIcon[i];
        ToolTypeInit(strClassName,strClassIcon);
    }
    if(count > 0)
    {
        ui->listWidgetType->setCurrentRow(0);
        ui->mainTipsTextBrowser->clear();
        ui->mainTipsTextBrowser->append(GlobalParameter::m_vt_classInfo[0]);
        //GlobalParameter::m_tool_detail_info
        ToolDetailListItem(0);

        if(ui->listWidgetDetail->count() > 0)
        {
            ui->listWidgetDetail->setCurrentRow(0);
            ListDetailInfo();
        }
    }


}
void ToolMainTypeDialog::on_addToolBtn_clicked()
{
    int row = ui->listWidgetDetail->currentRow();
    if (row >= 0)
    {
        int iClassRow = ui->listWidgetType->currentRow();
        m_tool_id = GlobalParameter::m_vt_task_id[iClassRow].at(row);
        m_lib_path = GlobalParameter::m_vt_tool_Lib_path[iClassRow].at(row);
        m_icon_path = GlobalParameter::m_vt_tool_Lib_icon[iClassRow].at(row);
        m_task_name = GlobalParameter::m_vt_tool_detail_name[iClassRow].at(row);
        m_fun_lib_path = GlobalParameter::m_vt_tool_fun_detail_name[iClassRow].at(row);
    }else
    {
        QMessageBox::about(NULL, tr("警告"), tr("请选择要添加的步骤!"));
        return ;
    }

    m_btn_operation = 2;
    QDialog::accept();

}
void ToolMainTypeDialog::ListDetailInfo()
{
    int row = ui->listWidgetDetail->currentRow();
    if (row >= 0)
    {
        int iClassRow = ui->listWidgetType->currentRow();
        m_tool_id = GlobalParameter::m_vt_task_id[iClassRow].at(row);
        QString strInfo = GlobalParameter::m_tool_detail_info.value(m_tool_id);
        ui->detailTipsTextBrowser->clear();
        ui->detailTipsTextBrowser->append(strInfo);
    }



}
void ToolMainTypeDialog::on_insertToolBtn_clicked()
{
    int row = ui->listWidgetDetail->currentRow();
    if (row >= 0)
    {
        int iClassRow = ui->listWidgetType->currentRow();
        m_tool_id = GlobalParameter::m_vt_task_id[iClassRow].at(row);
        m_lib_path = GlobalParameter::m_vt_tool_Lib_path[iClassRow].at(row);
        m_icon_path = GlobalParameter::m_vt_tool_Lib_icon[iClassRow].at(row);
        m_task_name = GlobalParameter::m_vt_tool_detail_name[iClassRow].at(row);
        m_fun_lib_path = GlobalParameter::m_vt_tool_fun_detail_name[iClassRow].at(row);
    }else
    {
        QMessageBox::about(NULL, tr("警告"), tr("请选择要添加的步骤!"));
        return ;
    }
    m_btn_operation = 1;
    QDialog::accept();
}

void ToolMainTypeDialog::on_cancelBtn_clicked()
{
    m_btn_operation = 0;
    QDialog::reject();

}
int ToolMainTypeDialog::GetTaskId()
{
    return m_tool_id;
}
void ToolMainTypeDialog::ToolTypeInit(QString strName,QString strPic)
{
    int width =110;
    int hegith = 120;
    ui->listWidgetType->setSpacing(5);
    ui->listWidgetType->setViewMode(QListView::IconMode);
    ui->listWidgetType->setIconSize(QSize(80,80));  //100,80
    ui->listWidgetType->setMovement(QListView::Static);
    int count = ui->listWidgetType->count();
    QPixmap pixIcon(strPic);
    ui->listWidgetType->addItem(new QListWidgetItem(QIcon(pixIcon.scaled(QSize(80,80))),strName));
    ui->listWidgetType->item(count)->setSizeHint(QSize(width,hegith));
}

void ToolMainTypeDialog::ToolDetailInit(QString strName,QString strPic)
{
    //m_vt_task_id.clear();
    int width =115;
    int hegith = 90;
    ui->listWidgetDetail->setSpacing(5);
    ui->listWidgetDetail->setViewMode(QListView::IconMode);
    ui->listWidgetDetail->setIconSize(QSize(100,50));
    ui->listWidgetDetail->setMovement(QListView::Static);
    int count = ui->listWidgetDetail->count();
    QPixmap pixIcon(strPic);
    ui->listWidgetDetail->addItem(new QListWidgetItem(QIcon(pixIcon.scaled(QSize(100,50))),strName));
    ui->listWidgetDetail->item(count)->setSizeHint(QSize(width,hegith));

}
void ToolMainTypeDialog::ToolDetailListItem(int iSelect)
{
    QString strTaskDetailName;
    QString strIocn;
    int count = GlobalParameter::m_vt_tool_detail_name[iSelect].count();
    for(int i = 0; i<count;i++)
    {
        strTaskDetailName = GlobalParameter::m_vt_tool_detail_name[iSelect].at(i);
        strIocn = GlobalParameter::m_vt_tool_Lib_icon[iSelect].at(i);
        ToolDetailInit(strTaskDetailName,strIocn);
    }
    ui->listWidgetDetail->setCurrentRow(0);
}
void ToolMainTypeDialog::on_listWidgetType_clicked(const QModelIndex &index)
{
    int iSelect  = index.row();

    if(iSelect >= 0)
    {
        ui->mainTipsTextBrowser->clear();
        ui->mainTipsTextBrowser->append(GlobalParameter::m_vt_classInfo[iSelect]);
        ui->listWidgetDetail->clear();
        ToolDetailListItem(iSelect);
        ListDetailInfo();
    }
}

void ToolMainTypeDialog::on_listWidgetDetail_clicked(const QModelIndex &index)
{
    int row = index.row();

    if(row >=0)
    {
        ListDetailInfo();
    }
}
