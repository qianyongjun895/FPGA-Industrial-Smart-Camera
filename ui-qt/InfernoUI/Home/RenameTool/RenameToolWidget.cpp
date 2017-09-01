#include "RenameToolWidget.h"
#include "ui_RenameToolWidget.h"
#include "TaskGlobal.h"
#include "Comm/GlobalParameter.h"
#include "ToolNameItem.h"

RenameToolWidget::RenameToolWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RenameToolWidget)
{
    ui->setupUi(this);
    ui->txtToolRename->setText("");
}

RenameToolWidget::~RenameToolWidget()
{
    delete ui;
}

void RenameToolWidget::on_btnQuit_clicked()
{
    this->close();
    SignalsExit(-10,"");
}

void RenameToolWidget::on_btnModifyName_clicked()
{
    int row = ui->listWidgetName->currentRow();
    if(row >=0)
    {
        if(ui->txtToolRename->text() == "")
        {
            SetInfor("别名不能为空",0);
            return;
        }

        if(isLegal(ui->txtToolRename->text()))
        {
            SetInfor("别名中含有非法字符",0);
            return;
        }
        if(ui->txtToolRename->text().length() > 16)
        {
            SetInfor("最多支持8个汉字或16字母",0);
            return;
        }
        QString str = ui->txtToolRename->text();
        const char *buf = str.toUtf8().data();
        int ret =Task_Step_Alias_Set(row+1, buf);
        if(ret == 0)
        {
            QListWidgetItem *item =  ui->listWidgetName->item(row);
            QWidget *qWidget = ui->listWidgetName->itemWidget(item);
            QString strTemp = QString::number(row+1);
            strTemp += str;
            ((ToolNameItem*)qWidget)->SetReName(strTemp);
             SetInfor("重命名成功",1);
             SignalsExit(row,strTemp);

        }else
        {
            SetInfor("重命名失败",0);
        }
    }else
    {
        SetInfor("请先选择需要重置工具",0);
    }

}

void RenameToolWidget::on_btnReset_clicked()
{
    int row = ui->listWidgetName->currentRow();
    if(row >=0)
    {
        const char *buf = m_strName.toUtf8().data();
        int ret =Task_Step_Alias_Set(row+1, buf);
        if(ret == 0)
        {
            SetInfor("工具名重置成功",1);
            QListWidgetItem *item =  ui->listWidgetName->item(row);
            QWidget *qWidget = ui->listWidgetName->itemWidget(item);
            QString strTemp = QString::number(row+1);
            strTemp += m_strName;
            ((ToolNameItem*)qWidget)->SetReName(strTemp);
            SignalsExit(row,strTemp);
        }else
        {
            SetInfor("工具名重置失败",0);
        }
    }else
    {
        SetInfor("请先选择需要重置工具",0);
    }

}
void RenameToolWidget::AddItemData(QString strName,QString strReName)
{
    ToolNameItem *p_ToolNameItem = new ToolNameItem;
    p_ToolNameItem->setAttribute(Qt::WA_DeleteOnClose);
    p_ToolNameItem->SetName(strName,strReName);
    int size =ui->listWidgetName->count();
    QListWidgetItem* mItem = new QListWidgetItem(ui->listWidgetName);
    ui->listWidgetName->setItemWidget(mItem,(QWidget*)p_ToolNameItem);
    ui->listWidgetName->item(size)->setSizeHint(QSize(685,50));
    ui->listWidgetName->setCurrentRow(size);

}
void RenameToolWidget::SetTaskId(QVector<int> vt)
{
    this->m_vt_task_id = vt;

    char buf[64];

    for(int i =0; i<vt.count();i++)
    {
        int taskId = vt[i];
        QString strTaskDetailName = GlobalParameter::m_tool_name_hash.value(taskId);
        memset(buf,0,sizeof(buf));
        QString strRename;
        int ret = Task_Step_Alias_Get(i+1,64,buf);
        if (ret ==0)
        {
            strRename  = QString::fromUtf8(buf);
        }else
        {
            strRename = strRename;
        }

        QString strName = QString::number(i+1);
        strName +=".";
        strName +=strTaskDetailName;

        QString strNameModify = QString::number(i+1);
        strNameModify +=".";
        strNameModify +=strRename;
        AddItemData(strName,strNameModify);
    }
}
bool RenameToolWidget::isLegal(QString text)
{
    if(text.isEmpty())
    {
        return true;
    }

    // 正则表达式判断特殊字符
    //QString pattern("[\\\\/:*?\"<>\\.\\s]");
    QString pattern("[`~!@#$^&*()=|{}':;',\\[\\].<>/?~！@#￥……&*（）——|{}【】‘；：”“'。，、？]");
    QRegExp rx(pattern);
    int match = text.indexOf(rx);
//    qDebug()<<"match:"<<match;
    if(match >= 0)
    {
        return true;
    }

    return false;
}

void RenameToolWidget::SetInfor(QString str,int flag)
{
    QPalette pa;

    if(flag == 1)
    {
        pa.setColor(QPalette::WindowText,Qt::darkGreen);
        ui->labelInfor->setPalette(pa);

    }else
    {
        pa.setColor(QPalette::WindowText,Qt::red);
        ui->labelInfor->setPalette(pa);

    }
   ui->labelInfor->setText(str);
}

void RenameToolWidget::on_listWidgetName_clicked(const QModelIndex &index)
{
    int row = index.row();

    if(row >= 0)
    {
        QListWidgetItem *item =  ui->listWidgetName->item(row);
        QWidget *qWidget = ui->listWidgetName->itemWidget(item);
        m_strName= ((ToolNameItem*)qWidget)->GetName();
        QString strRename = ((ToolNameItem*)qWidget)->GetRename();
        int iIndex = strRename.indexOf('.');
        if(iIndex > 0)
            strRename = strRename.right(strRename.length()-iIndex-1);
        ui->txtToolRename->setText(strRename);
    }
}
