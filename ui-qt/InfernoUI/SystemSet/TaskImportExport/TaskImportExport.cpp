#include <QDebug>
#include "TaskImportExport.h"
#include "ui_TaskImportExport.h"
#include "QFileDialog"
#include "stdio.h"
#include <QMessageBox>
#include "Comm/ControlStyle.h"
#include "TaskGlobal.h"

#define TASK_SAVE_PATH "/mnt/emmc2/task/save"

TaskImportExport::TaskImportExport(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TaskImportExport)
{
    ui->setupUi(this);
    ControlStyle::SetTabBar(ui->tabWidget);
    ui->tabWidget->setCurrentIndex(0);
    GetTaskFileList(ui->listWidget_TaskFileName,TASK_SAVE_PATH);
    GetTaskFileList(ui->listWidget_TaskFileName_U,TASK_SAVE_PATH);
    GetTaskFileList(ui->listWidget_TaskFileName_Camera,TASK_SAVE_PATH);
    ui->lineEdit_ExportIP->installEventFilter(this);
    ui->lineEdit_ImportIP->installEventFilter(this);
    updateTimer = new QTimer;
    m_UpdateProgressBarDlg = new UpdateProgressBarDlg(this);
    connect(updateTimer, &QTimer::timeout, this, &TaskImportExport::UpdateTimerSlot);
}

TaskImportExport::~TaskImportExport()
{
    ui->lineEdit_ExportIP->removeEventFilter(this);
    ui->lineEdit_ImportIP->removeEventFilter(this);
    if(m_UpdateProgressBarDlg != NULL)
    {
        delete m_UpdateProgressBarDlg;
        m_UpdateProgressBarDlg = NULL;
    }
    if (updateTimer != NULL)
    {
        delete updateTimer;
        updateTimer = NULL;
    }
    delete ui;
}


void TaskImportExport::GetTaskFileList(QListWidget *pList,QString strPath)
{
    pList->clear();
    m_task_creater.clear();
    m_task_date.clear();
    m_task_info.clear();
    QDir dir(strPath);
    foreach(QFileInfo mfi, dir.entryInfoList())
    {
        if(mfi.isFile())
        {
            if(0 == (mfi.suffix().compare("txt")))
            {
//                UI_DRV_PRINTF(EDIT_DEBUG,"mfi.baseName().toUtf8().data() = %s\n",mfi.baseName().toLocal8Bit().data());
                QFile file(strPath+"/"+mfi.fileName());
                if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                }
                int i = 0;
                pList->addItem(QString::fromUtf8(mfi.baseName().toLocal8Bit().data()));
//                qDebug()<<"curFileName:"<<QString::fromUtf8(mfi.baseName().toLocal8Bit().data());
                int loopFlag = 0;
                QString taskInfo;
                while(!file.atEnd())
                {
                    QByteArray line = file.readLine();
                    QString str = QString::fromUtf8(line);
                    i++;
                    if(i == 1)
                        m_task_creater.append(str);
                    else if(i == 2)
                        m_task_date.append(str);
                    else
                    {
                        taskInfo += str; // 描述信息可能有多行
                        loopFlag = 1; // 表示有描述信息
                    }
                }

                if (loopFlag == 1)
                {
                    m_task_info.append(taskInfo);
                }
            }
        }
    }
}

void TaskImportExport::on_listWidget_TaskFileName_currentRowChanged(int currentRow)
{
    ui->txt_Name->clear();
    ui->txtAuthor->clear();
    ui->txt_Date->clear();
    ui->textBrowser_TaskInfo->clear();
    ui->txt_Name->setText(ui->listWidget_TaskFileName->currentItem()->text());
    if(currentRow < m_task_creater.count())
        ui->txtAuthor->setText(m_task_creater[currentRow]);
    if(currentRow < m_task_date.count())
        ui->txt_Date->setText(m_task_date[currentRow]);
    if(currentRow < m_task_info.count())
        ui->textBrowser_TaskInfo->setText(m_task_info[currentRow]);
}


bool TaskImportExport::eventFilter(QObject *watched, QEvent *event)
{
//    if(((QLineEdit *)watched)->isReadOnly() || !((QLineEdit *)watched)->isEnabled())
//    {
//        return QWidget::eventFilter(watched, event);
//    }
    if (watched == ui->lineEdit_ExportIP || watched == ui->lineEdit_ImportIP)
    {
         if (event->type()==QEvent::MouseButtonPress)
         {
             QDialog *dlg = m_KeyBoardLib.GetNumKeyBoardDialog();
             m_KeyBoardLib.SetOldNum(((QLineEdit *)watched)->text());
             m_KeyBoardLib.InputIp();
             int ret = dlg->exec();
             if(ret == QDialog::Accepted)
             {
                 ((QLineEdit *)watched)->setText(m_KeyBoardLib.GetNum());
             }

         }
    }
    return QWidget::eventFilter(watched, event);
}

void TaskImportExport::on_btnExport_clicked()
{
    QString fileName = ui->txt_Name->text();
    QString IP_str = ui->lineEdit_ExportIP->text();
    if(IP_str.length() < 11)
    {
        QMessageBox::about(this,tr("提示"),tr("请输入电脑IP地址！"));
        return;
    }
    if(fileName.isEmpty())
    {
        QMessageBox::about(this,tr("提示"),tr("请选择要导出的任务文件！"));
        return;
    }

    // 导出文件
    QByteArray ba = fileName.toLatin1();
    char *name = ba.data();
    QByteArray bb = IP_str.toLatin1();
    char *serverIP = bb.data();

    m_UpdateProgressBarDlg->taskPortSetProgress(0);
    updateTimer->start(10);
    m_UpdateProgressBarDlg->show();
    int ret = TaskFileUpload(name, serverIP);
    if(ret != 0)
    {
        m_UpdateProgressBarDlg->taskPortSetProgress(-1);
//        QMessageBox::information(this,tr("提示"),tr("导出失败！"));
    }
    else
    {
        m_UpdateProgressBarDlg->taskPortSetProgress(1);
    }
    updateTimer->stop();
}

/**
 * @brief TaskImportExport::UpdateTimerSlot
 * @note 软件更新的定时器响应函数
 */
void TaskImportExport::UpdateTimerSlot()
{
    static int times = 0;
    if(times >= 150)
    {
        times = 0;
        m_UpdateProgressBarDlg->taskPortSetProgress(0);
    }
    times++;
}

bool TaskImportExport::isLegal(QString text)
{
    if(text.isEmpty())
    {
        return true;
    }

    // 正则表达式判断特殊字符
    QString pattern("[\\\\/:*?\"<>\\.\\s]");
//    QString pattern("[`~!@#$^&*()=|{}':;',\\[\\].<>/?~！@#￥……&*（）——|{}【】‘；：”“'。，、？]");
    QRegExp rx(pattern);
    int match = text.indexOf(rx);
//    qDebug()<<"match:"<<match;
    if(match >= 0)
    {
        return true;
    }

    return false;
}

void TaskImportExport::on_btnImport_clicked()
{
    QString fileName = ui->lineEdit_ImportName->text();
    QString IP_str = ui->lineEdit_ImportIP->text();
    if(IP_str.length() < 11)
    {
        QMessageBox::about(this,tr("提示"),tr("请输入电脑IP地址！"));
        return;
    }
    if(fileName.isEmpty())
    {
        QMessageBox::about(this,tr("提示"),tr("请输入任务文件名！"));
        return;
    }
    if(fileName.contains(QRegExp("[\\x4e00-\\x9fa5]+")))
    {
        // 存在中文
        QMessageBox::about(NULL,tr("提示"),tr("任务名字含有中文字符，请重新输入!"));
        return;
    }
    if (isLegal(fileName))
    {
        QMessageBox::about(NULL,tr("提示"),tr("任务名字含有非法字符，请重新输入!"));
        return;
    }
    if(strlen(fileName.toUtf8().data()) >= 20)
    {
        QMessageBox::about(this,tr("提示"),tr("任务文件名称过长！"));
        return;
    }
    for(int i = 0; i < ui->listWidget_TaskFileName->count();i++)
    {
        if(fileName == ui->listWidget_TaskFileName->item(i)->text())
        {
            QMessageBox::StandardButton rb = \
                    QMessageBox::warning(NULL, \
                                         tr("提示"), \
                                         tr("相机中存在同名任务，确定覆盖相机中的同名任务？"), \
                                         QMessageBox::Yes | QMessageBox::No, \
                                         QMessageBox::No);

            if(rb == QMessageBox::No)
            {
                return ;
            }
        }
    }

    // 导入任务
    QByteArray ba = fileName.toLatin1();
    char *name = ba.data();
    QByteArray bb = IP_str.toLatin1();
    char *serverIP = bb.data();

    m_UpdateProgressBarDlg->taskPortSetProgress(0);
    updateTimer->start(10);
    m_UpdateProgressBarDlg->show();
    int ret = TaskFileDownload(name, serverIP);
    if(ret != 0)
    {
        m_UpdateProgressBarDlg->taskPortSetProgress(-1);
//        QMessageBox::information(this,tr("提示"),tr("导入失败！"));
    }
    else
    {
        m_UpdateProgressBarDlg->taskPortSetProgress(1);
        GetTaskFileList(ui->listWidget_TaskFileName,TASK_SAVE_PATH); // 更新文件列表和信息
    }
    updateTimer->stop();
}
//u盘导出
void TaskImportExport::on_listWidget_TaskFileName_U_clicked(const QModelIndex &index)
{
    int currentRow = index.row();
    ui->txt_Name_U->clear();
    ui->txtAuthor_U->clear();
    ui->txt_Date_U->clear();
    ui->textBrowser_TaskInfo_U->clear();
    ui->txt_Name_U->setText(ui->listWidget_TaskFileName_U->currentItem()->text());
    if(currentRow < m_task_creater.count())
        ui->txtAuthor_U->setText(m_task_creater[currentRow]);
    if(currentRow < m_task_date.count())
        ui->txt_Date_U->setText(m_task_date[currentRow]);
    if(currentRow < m_task_info.count())
        ui->textBrowser_TaskInfo_U->setText(m_task_info[currentRow]);
}
//导入
void TaskImportExport::on_btn_U_Import_clicked()
{

}
