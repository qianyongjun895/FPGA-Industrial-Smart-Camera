#include "TaskLoadDlg.h"
#include "ui_TaskLoadDlg.h"
#include "QFileDialog"
#include "QTableWidgetItem"
#include "stdio.h"
#include <QMessageBox>
#include "Comm/FileView.h"
#include "TaskGlobal.h"
#include <QFile>
#include <QTextStream>
#include <qdebug.h>

TaskLoadDlg::TaskLoadDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TaskLoadDlg)
{
    ui->setupUi(this);
    m_task_path = "/mnt/emmc2/task/save";
    this->setWindowTitle(tr("打开任务"));
    ui->btnQuit->setFocus();
    LoadTaskTimer = new QTimer;
    ui->progressBar->setVisible(false);
    IniTabaleHead();
    GetTaskFileList();
    m_fileName = "";
    connect(LoadTaskTimer,&QTimer::timeout,this,&TaskLoadDlg::TaskLoadTimerSlot);

    ui->radioButtonDefaultPath->setChecked(true);

}

TaskLoadDlg::~TaskLoadDlg()
{
    delete ui;
}

//初始表格列
void TaskLoadDlg::IniTabaleHead()
{
    ui->tableWidgetData->setRowCount(0);
    ui->tableWidgetData->setColumnCount(4);
    QStringList horizontalHeader;
    horizontalHeader<<QObject::tr("任务名称")<<QObject::tr("创建者")<<QObject::tr("日期")<<QObject::tr("任务摘要");
    QStringList verticalHeader;
    //verticalHeader<<QObject::tr("line")<<QObject::tr("circle")<<QObject::tr("baseline");
    ui->tableWidgetData->setColumnWidth(0,100);
    ui->tableWidgetData->setColumnWidth(1,120);
    ui->tableWidgetData->setColumnWidth(2,150);
    ui->tableWidgetData->setColumnWidth(3,370);

    ui->tableWidgetData->setHorizontalHeaderLabels(horizontalHeader);
    ui->tableWidgetData->setVerticalHeaderLabels(verticalHeader);

    ui->tableWidgetData->setSelectionBehavior ( QAbstractItemView::SelectRows); //设置选择行为，以行为单位
    ui->tableWidgetData->setSelectionMode ( QAbstractItemView::SingleSelection); //设置选择模式，选择单行
    ui->tableWidgetData->setEditTriggers(QAbstractItemView::NoEditTriggers);
}
void TaskLoadDlg::AddDataToTable(QString strTaskName,QString strCreator,QString strDate,QString strTaskInfo)
{
    int icount = ui->tableWidgetData->rowCount();
    ui->tableWidgetData->setRowCount(icount + 1);//总行数增加1

    ui->tableWidgetData->setItem(icount, 0, new QTableWidgetItem(strTaskName));
    ui->tableWidgetData->setItem(icount , 1, new QTableWidgetItem(strCreator));
    ui->tableWidgetData->setItem(icount , 2, new QTableWidgetItem(strDate));
    ui->tableWidgetData->setItem(icount , 3, new QTableWidgetItem(strTaskInfo));
    ui->tableWidgetData->setItemSelected(ui->tableWidgetData->item(icount+1,1),true);
}
//删除
void TaskLoadDlg::DelTableData()
{
    int iIndex = ui->tableWidgetData->currentRow();
    //QString strType = ui->tableWidgetData->item(iIndex,0)->text();
    if(iIndex >= 0)
    {
        QMessageBox::StandardButton rb = \
                QMessageBox::warning(NULL, \
                                     tr("Warning"), \
                                     tr("确定删除这个任务文件?"), \
                                     QMessageBox::Yes | QMessageBox::No, \
                                     QMessageBox::No);
        if(rb == QMessageBox::Yes)
        {
            ui->tableWidgetData->removeRow(iIndex);
        }
    }
    else
    {
        QMessageBox::about(NULL,tr("information"),tr("请选择一个任务文件"));
    }
}

void TaskLoadDlg::on_btnQuit_clicked()
{
    m_fileName = "";
    QDialog::reject();
}



void TaskLoadDlg::GetTaskFileList()
{
    //    m_TaskInfoData->InitTaskInfo();
    QDir dir(m_task_path);

    foreach(QFileInfo mfi ,dir.entryInfoList())
    {
        if(mfi.isFile())
        {
            if(0==(mfi.suffix().compare("txt")))
            {
                ui->tableWidgetData->setRowCount(ui->tableWidgetData->rowCount()+1);
                ui->tableWidgetData->setItem(ui->tableWidgetData->rowCount()-1, 0, new QTableWidgetItem(QString::fromUtf8(mfi.baseName().toLocal8Bit().data())));
                QFile file(m_task_path+"/"+mfi.fileName());
                if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                }
                int i = 0;
                while(!file.atEnd()) {
                    QByteArray line = file.readLine();
                    QString str(line);
                    i++;
                    if(i == 1)
                        ui->tableWidgetData->setItem(ui->tableWidgetData->rowCount()-1, 1, new QTableWidgetItem(str));
                    else if(i == 2)
                        ui->tableWidgetData->setItem(ui->tableWidgetData->rowCount()-1, 2, new QTableWidgetItem(str));
                    else
                        ui->tableWidgetData->setItem(ui->tableWidgetData->rowCount()-1, 3, new QTableWidgetItem(str));
                }
            }
        }
    }
}

void TaskLoadDlg::on_btnOpen_clicked()
{
    printf("on_btnOpen_clicked\n");
    if(ui->tableWidgetData->rowCount() == 0 || ui->tableWidgetData->currentRow() < 0)
    {
        return;
    }

    QString fileName = ui->tableWidgetData->item(ui->tableWidgetData->currentRow(),0)->text();
    QString strfilePath = m_task_path+"/"+fileName;
    QByteArray ba = strfilePath.toLatin1();

    ui->progressBar->setVisible(true);
    ui->progressBar->setValue(0);
    LoadTaskTimer->start(10);
    char *name = ba.data();
    //int ret = TaskFileLoad(name); // m_TaskFileHandleData->LoadTaskData(ui->tableWidgetData->item(ui->tableWidgetData->currentRow(),0)->text());
    int ret = TaskFileLoadFromPath(name);
    LoadTaskTimer->stop();
    ui->progressBar->setValue(100);
    if(ret != 0)
    {
        QMessageBox::about(NULL,tr("Presentation"),tr("打开任务失败!"));
    }
    else
    {
        m_fileName = fileName;
        // 保存为当前任务名称
        QFile file("/mnt/emmc2/task/tmp/curTaskName.bin");
        if(file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream txtOutput(&file);
            txtOutput << fileName;
            file.close();
        }
        system("sync");
        QMessageBox::about(NULL,tr("Presentation"),tr("打开任务成功!"));
        ui->progressBar->setVisible(false);
        G_Data_ReLoad();
        M_Cmos_Param_ReLoad();
        this->close();
    }
    ui->progressBar->setVisible(false);
}

void TaskLoadDlg::TaskLoadTimerSlot()
{
    ui->progressBar->setVisible(true);
    static int times = 0;
    if(times >= 20)
    {
        times = 0;
        if(ui->progressBar->value() < 99)
            ui->progressBar->setValue(ui->progressBar->value()+1);
    }
    times++;
}

void TaskLoadDlg::on_btnDel_clicked()
{
    int iIndex = ui->tableWidgetData->currentRow();
    //QString strType = ui->tableWidgetData->item(iIndex,0)->text();
    if(iIndex >= 0)
    {
        QMessageBox::StandardButton rb = \
                QMessageBox::warning(NULL, \
                                     tr("Warning"), \
                                     tr("确定删除这个任务文件?"), \
                                     QMessageBox::Yes | QMessageBox::No, \
                                     QMessageBox::No);
        if(rb == QMessageBox::Yes)
        {
            QString fileName = ui->tableWidgetData->item(iIndex,0)->text();
            QByteArray ba = fileName.toLatin1();
            char *name = ba.data();
            int ret = TaskFileDelete(name); // m_TaskFileHandleData->DeleteCameraTaskFile(ui->tableWidgetData->item(iIndex,0)->text());
            if(ret != 0)
            {
                QMessageBox::about(NULL,tr("Presentation"),tr("删除失败!"));
                return;
            }
            ui->tableWidgetData->removeRow(iIndex);
        }
    }else
    {
        QMessageBox::about(NULL,tr("presentation"),tr("请选择要删除的文件!"));
    }
}

void TaskLoadDlg::on_radioButtonUDisk_clicked()
{

    FileView fileDlg;
    int ret = fileDlg.exec();

    int count = ui->tableWidgetData->rowCount();
    for(int i = 0; i< count;i++)
    {
        ui->tableWidgetData->removeRow(0);

    }
    if(ret == QDialog::Accepted)
    {
        m_task_path = fileDlg.GetFolderPath();
        if(m_task_path != "")
            GetTaskFileList();
    }
    //m_task_path = "./";
    //GetTaskFileList();
}

void TaskLoadDlg::on_radioButtonDefaultPath_clicked()
{
    int count = ui->tableWidgetData->rowCount();
    for(int i = 0; i< count;i++)
    {
        ui->tableWidgetData->removeRow(0);
    }

    m_task_path = "/mnt/emmc2/task/save";
    GetTaskFileList();
}
