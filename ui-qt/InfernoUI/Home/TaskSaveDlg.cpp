#include "TaskSaveDlg.h"
#include "ui_TaskSaveDlg.h"
#include <sys/stat.h>
#include "stdio.h"
#include <QDateTime>
#include <QMessageBox>
#include <QFileDialog>
#include "TaskGlobal.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QByteArray>
#include "Comm/FileView.h"
TaskSaveDlg::TaskSaveDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TaskSaveDlg)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("保存任务"));
    m_file_path = "/mnt/emmc2/task/save";
    TaskSaveTimer = new QTimer;
    ui->progressBar->setVisible(false);
    IniTabaleHead();
    GetTaskFileList();

    connect(TaskSaveTimer,&QTimer::timeout,this,&TaskSaveDlg::TaskSaveTimerSlot);
    ui->radioButtonDefaultPath->setChecked(true);
}

TaskSaveDlg::~TaskSaveDlg()
{
    delete ui;
}

//初始表格列
void TaskSaveDlg::IniTabaleHead()
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
    ui->tableWidgetData->setColumnWidth(3,360);

    ui->tableWidgetData->setHorizontalHeaderLabels(horizontalHeader);
    ui->tableWidgetData->setVerticalHeaderLabels(verticalHeader);

    ui->tableWidgetData->setSelectionBehavior ( QAbstractItemView::SelectRows); //设置选择行为，以行为单位
    ui->tableWidgetData->setSelectionMode ( QAbstractItemView::SingleSelection); //设置选择模式，选择单行
    ui->tableWidgetData->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void TaskSaveDlg::AddDataToTable(QString strTaskName,QString strCreator,QString strDate,QString strTaskInfo)
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
void TaskSaveDlg::DelTableData()
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
        QMessageBox::about(NULL,tr("presentation"),tr("请选中需要删除的任务!"));
    }
}

bool TaskSaveDlg::SaveCurTaskFile(QString taskName, QString description)
{
    QByteArray ba = taskName.toLatin1();
    char *name = ba.data();
    QByteArray bb = description.toUtf8();
//    char *desc = bb.data();
//    qDebug()<<"name:"<<name<<endl<<"desc:"<<desc;
    //int ret = TaskFileSave(name);
    qDebug()<<"1111";
    int ret = TaskFileSaveToPath(m_file_path.toLatin1().data(), name);
    qDebug()<<"2222";
    if (ret != 0)
    {
        QMessageBox::about(NULL, tr("about"), tr("保存文件失败!"));
        return false;
    }

    QString fileName;
    fileName += m_file_path+"/"+taskName+".txt";
    QFile file(fileName);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QMessageBox::about(NULL, tr("about"), tr("打开文件失败!"));
        return false;
    }
    QTextStream out(&file);
    out.seek(0);
    out.setCodec("utf-8");
    out << bb;
    file.close();
    SystemCmd("sync");

    return true;
}

void TaskSaveDlg::on_btnSave_clicked()
{
    QString fileName;
    QString description;
    fileName = ui->lineEdit_TaskName->text();
    if(fileName.isEmpty())
    {
        QMessageBox::about(NULL,tr("Presentation"),tr("请输入任务名称!"));
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
        QMessageBox::about(NULL,tr("提示"),tr("任务名字过长，请重新输入!"));
        return;
    }
    if(ui->radioButtonUDisk->isChecked())
    {
        FileView fileDlg;
        int ret = fileDlg.exec();
        if(ret == QDialog::Accepted)
        {
            //m_file_path = "/mnt/emmc2/task/save";
            m_file_path = fileDlg.GetFolderPath();
            if(m_file_path !="")
            {
                 GetTaskFileList();
            }
        }else
        {
            m_file_path = "";
            QMessageBox::about(NULL,tr("提示"),tr("请选择任务保存的路径!"));
            return;
        }

    }

    if (SameFileNameCheck(fileName))
    {
        QMessageBox::about(NULL,tr("提示"),tr("名字已存在!"));
        return;
    }

    if(strlen(ui->lineEdit_AuthorName->text().toUtf8().data()) >= 20)
    {
        QMessageBox::about(NULL,tr("提示"),tr("作者名字过长，请重新输入!"));
        return;
    }
    description += ui->lineEdit_AuthorName->text()+"\n";

    if(strlen(ui->textEdit_TaskInfo->toPlainText().toUtf8().data()) >= 100)
    {
        QMessageBox::about(NULL,tr("提示"),tr("描述信息过长，请重新输入!"));
        return;
    }

    QDateTime time = QDateTime::currentDateTime(); // 获取系统现在的时间
    QString strTime = time.toString("yyyy-MM-dd hh:mm:ss ddd"); // 设置显示格式
    description += strTime+"\n";
    description += ui->textEdit_TaskInfo->toPlainText();

    ui->progressBar->setVisible(true);
    ui->progressBar->setValue(0);
    TaskSaveTimer->start(10);
    bool saveRst = SaveCurTaskFile(fileName, description);
    TaskSaveTimer->stop();
    ui->progressBar->setValue(100);
    if(saveRst)
    {       
        SaveTaskFileFinished();
        QMessageBox::about(NULL,tr("Presentation"),tr("保存成功"));
        ui->progressBar->setVisible(false);
        this->close();
        signalTaskName(1,fileName);
    }
    //ui->progressBar->setVisible(false);
}

void TaskSaveDlg::GetTaskFileList()
{
    QDir dir(m_file_path);
    foreach(QFileInfo mfi, dir.entryInfoList())
    {
        if(mfi.isFile())
        {
            if(0==(mfi.suffix().compare("txt")))
            {
                ui->tableWidgetData->setRowCount(ui->tableWidgetData->rowCount()+1);
//                UI_DRV_PRINTF(EDIT_DEBUG,"mfi.baseName().toUtf8().data() = %s\n",mfi.baseName().toLocal8Bit().data());
                ui->tableWidgetData->setItem(ui->tableWidgetData->rowCount()-1, 0, new QTableWidgetItem(QString::fromUtf8(mfi.baseName().toLocal8Bit().data())));
//                ui->tableWidgetData->setItem(ui->tableWidgetData->rowCount()-1, 0, new QTableWidgetItem(mfi.baseName()));

                QFile file(m_file_path+"/"+mfi.fileName());
                if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                }
                int i = 0;
                QTextStream in(&file);
                in.setCodec("utf-8");
                while(!in.atEnd())
                {
                    QString str = in.readLine();
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


void TaskSaveDlg::TaskSaveTimerSlot()
{
    ui->progressBar->setVisible(true);
    static int times = 0;
    if(times >= 100)
    {
        times = 0;
        if(ui->progressBar->value() < 99)
            ui->progressBar->setValue(ui->progressBar->value()+1);

    }
    times++;
}

void TaskSaveDlg::SaveTaskFileFinished()
{
    ui->tableWidgetData->clear();
    ui->tableWidgetData->setRowCount(0);
    GetTaskFileList();
}

bool TaskSaveDlg::SameFileNameCheck(QString fileName)
{
    QDir dir(m_file_path);
    foreach(QFileInfo mfi, dir.entryInfoList())
    {
        if(mfi.isFile())
        {
            if(0 == (mfi.suffix().compare("txt")))
            {
//                QFile file("/mnt/emmc2/task/save/"+mfi.fileName());
//                if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
//                }
                if(fileName == QString::fromUtf8(mfi.baseName().toLocal8Bit().data()))
                {
                    return true;
                }
            }
        }
    }
    return false;
}


void TaskSaveDlg::on_btnDel_clicked()
{
    DelTableData();
}

void TaskSaveDlg::on_btnQuit_clicked()
{
    QDialog::reject();
}

bool TaskSaveDlg::isLegal(QString text)
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

//默认
void TaskSaveDlg::on_radioButtonDefaultPath_clicked()
{
    int count = ui->tableWidgetData->rowCount();
    for(int i = 0; i< count;i++)
    {
        ui->tableWidgetData->removeRow(0);

    }
    m_file_path = "/mnt/emmc2/task/save";
     GetTaskFileList();
}
//u盘目录
void TaskSaveDlg::on_radioButtonUDisk_clicked()
{
    int count = ui->tableWidgetData->rowCount();
    for(int i = 0; i< count;i++)
    {
        ui->tableWidgetData->removeRow(0);

    }
}
