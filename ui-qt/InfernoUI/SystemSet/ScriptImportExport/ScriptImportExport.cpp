#include "ScriptImportExport.h"
#include "ui_ScriptImportExport.h"
#include "QFileDialog"
#include "stdio.h"
#include <QMessageBox>
#include "Comm/ControlStyle.h"
#include "TaskGlobal.h"
#include <QDebug>

#define SHELL_SCRIPT_PATH "/mnt/emmc4/Script/PrivateShell"
#define LUA_SCRIPT_PATH "/mnt/emmc4/Script/Lua"
#define PY2_SCRIPT_PATH "/mnt/emmc4/Script/Python2"
#define PY3_SCRIPT_PATH "/mnt/emmc4/Script/Python3"

ScriptImportExport::ScriptImportExport(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScriptImportExport)
{
    ui->setupUi(this);
    m_btn_pre = NULL;
    ControlStyle::SetTabBar(ui->tabWidget);
    ui->tabWidget->setCurrentIndex(0);
    on_btnShell_clicked();
    ui->lineEdit_ExportIP->installEventFilter(this);
    ui->lineEdit_ImportIP->installEventFilter(this);
    updateTimer = new QTimer;
    m_UpdateProgressBarDlg = new UpdateProgressBarDlg(this);
    connect(updateTimer, &QTimer::timeout, this, &ScriptImportExport::UpdateTimerSlot);
}

ScriptImportExport::~ScriptImportExport()
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

bool ScriptImportExport::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui->lineEdit_ExportIP || watched == ui->lineEdit_ImportIP)
    {
         if (event->type()==QEvent::MouseButtonPress)
         {
             QDialog * dlg = m_KeyBoardLib.GetNumKeyBoardDialog();
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

void ScriptImportExport::GetShellScriptFilesList(QListWidget *list,QString path)
{
    list->clear();
    //ui->listScriptFiles->clear();
    QDir dir(path);
    foreach(QFileInfo mfi, dir.entryInfoList())
    {
        if(mfi.isFile())
        {
            if(0 == (mfi.suffix().compare("sh")))
            {
//                ui->listScriptFiles->addItem(QString::fromUtf8(mfi.baseName().toLocal8Bit().data()));
                  list->addItem(QString::fromUtf8(mfi.fileName().toLocal8Bit().data()));
//                qDebug()<<"curFileName:"<<QString::fromUtf8(mfi.baseName().toLocal8Bit().data());
            }
        }
    }
}

void ScriptImportExport::GetLuaScriptFilesList(QListWidget *list,QString path)
{
    list->clear();
    //ui->listScriptFiles->clear();
    QDir dir(path);
    foreach(QFileInfo mfi, dir.entryInfoList())
    {
        if(mfi.isFile())
        {
            if(0 == (mfi.suffix().compare("lua")))
            {
                list->addItem(QString::fromUtf8(mfi.fileName().toLocal8Bit().data()));
//                qDebug()<<"curFileName:"<<QString::fromUtf8(mfi.baseName().toLocal8Bit().data());
            }
        }
    }
}

void ScriptImportExport::GetPython2ScriptFilesList(QListWidget *list,QString path)
{
    list->clear();
    //ui->listScriptFiles->clear();
    QDir dir(path);
    foreach(QFileInfo mfi, dir.entryInfoList())
    {
        if(mfi.isFile())
        {
            if(0 == (mfi.suffix().compare("py")))
            {
                ui->listScriptFiles->addItem(QString::fromUtf8(mfi.fileName().toLocal8Bit().data()));
//                qDebug()<<"curFileName:"<<QString::fromUtf8(mfi.baseName().toLocal8Bit().data());
            }
        }
    }
}

void ScriptImportExport::GetPython3ScriptFilesList(QListWidget *list,QString path)
{
    list->clear();
    //ui->listScriptFiles->clear();
    QDir dir(path);
    foreach(QFileInfo mfi, dir.entryInfoList())
    {
        if(mfi.isFile())
        {
            if(0 == (mfi.suffix().compare("py")))
            {
                ui->listScriptFiles->addItem(QString::fromUtf8(mfi.fileName().toLocal8Bit().data()));
//                qDebug()<<"curFileName:"<<QString::fromUtf8(mfi.baseName().toLocal8Bit().data());
            }
        }
    }
}

void ScriptImportExport::SetButtonStyle(QPushButton *pre, QPushButton *current)
{
    if(pre != NULL)
    {
        pre->setStyleSheet("background-color: rgb(255, 255, 255);");
    }

    if(current != NULL)
    {
        current->setStyleSheet("background-color: rgb(249, 220, 117);");
    }
}

bool ScriptImportExport::isLegal(QString text)
{
    if(text.isEmpty())
    {
        return true;
    }

    // 正则表达式判断特殊字符
    QString pattern("[\\\\/:*?\"<>\\s]");
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

void ScriptImportExport::on_btnShell_clicked()
{
    m_script_type = SHELL_SCRIPT;
    SetButtonStyle(m_btn_pre, ui->btnShell);
    m_btn_pre = ui->btnShell;
    GetShellScriptFilesList(ui->listScriptFiles,SHELL_SCRIPT_PATH);
}

void ScriptImportExport::on_btnLua_clicked()
{
    m_script_type = LUA_SCRIPT;
    SetButtonStyle(m_btn_pre, ui->btnLua);
    m_btn_pre = ui->btnLua;
    GetLuaScriptFilesList(ui->listScriptFiles,LUA_SCRIPT_PATH);
}

void ScriptImportExport::on_btnPython2_clicked()
{
    m_script_type = PYTHON2_SCRIPT;
    SetButtonStyle(m_btn_pre, ui->btnPython2);
    m_btn_pre = ui->btnPython2;
    GetPython2ScriptFilesList(ui->listScriptFiles,PY2_SCRIPT_PATH);
}

void ScriptImportExport::on_btnPython3_clicked()
{
    m_script_type = PYTHON3_SCRIPT;
    SetButtonStyle(m_btn_pre, ui->btnPython3);
    m_btn_pre = ui->btnPython3;

    GetPython3ScriptFilesList(ui->listScriptFiles,PY3_SCRIPT_PATH);
}

void ScriptImportExport::on_radioButtonShell_clicked()
{
    m_script_type = SHELL_SCRIPT;
}

void ScriptImportExport::on_radioButtonLua_clicked()
{
    m_script_type = LUA_SCRIPT;
}

void ScriptImportExport::on_radioButtonPython2_clicked()
{
    m_script_type = PYTHON2_SCRIPT;
}

void ScriptImportExport::on_radioButtonPython3_clicked()
{
    m_script_type = PYTHON3_SCRIPT;
}

void ScriptImportExport::on_btnExport_clicked()
{
    QString IP_str = ui->lineEdit_ExportIP->text();
    QString fileName;
    fileName.clear();
    if (ui->listScriptFiles->count() > 0)
    {
        qDebug() << "count = " << ui->listScriptFiles->count();
        if (ui->listScriptFiles->currentItem())
            fileName = ui->listScriptFiles->currentItem()->text();
        qDebug() << "file name: " << fileName;
    }
    if(IP_str.length() < 11)
    {
        QMessageBox::about(this,tr("提示"),tr("请输入电脑IP地址！"));
        return;
    }
    if(fileName.isEmpty())
    {
        QMessageBox::about(this,tr("提示"),tr("请选择要导出的文件！"));
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
    int ret = ScriptFileUpload(m_script_type, name, serverIP);
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

void ScriptImportExport::on_btnImport_clicked()
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
        QMessageBox::about(this,tr("提示"),tr("请输入文件名！"));
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
        QMessageBox::about(this,tr("提示"),tr("文件名称过长！"));
        return;
    }

    bool scriptTypeErr = false;
    QString fileSuffix = fileName.right(3);
//    qDebug() << "fileSuffix: " << fileSuffix;
    if (fileSuffix == ".sh")
    {
//        qDebug()<<"sh script";
        if (! ui->radioButtonShell->isChecked())
        {
            scriptTypeErr = true;
        }
    }
    else if (fileSuffix == ".py")
    {
//        qDebug()<<"py script";
        if (! (ui->radioButtonPython2->isChecked() || ui->radioButtonPython3->isChecked()))
        {
            scriptTypeErr = true;
        }
    }
    else
    {
        QString luaScript = fileName.right(4);
        if (luaScript == ".lua")
        {
    //        qDebug()<<"lua script";
            if (! ui->radioButtonLua->isChecked())
            {
                scriptTypeErr = true;
            }
        }
        else
        {
            QMessageBox::about(this,tr("提示"),tr("不支持的脚本类型！"));
            return;
        }
    }

    if (! (ui->radioButtonShell->isChecked() \
          || ui->radioButtonLua->isChecked() \
          || ui->radioButtonPython2->isChecked() \
          || ui->radioButtonPython3->isChecked()))
    {
        QMessageBox::about(this,tr("提示"),tr("请选择脚本类型！"));
        return;
    }
    else
    {
        if (scriptTypeErr)
        {
            QMessageBox::about(this,tr("提示"),tr("脚本类型选择错误！"));
            return;
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
    int ret = ScriptFileDownload(m_script_type, name, serverIP);
    if(ret != 0)
    {
        m_UpdateProgressBarDlg->taskPortSetProgress(-1);
//        QMessageBox::information(this,tr("提示"),tr("导入失败！"));
    }
    else
    {
        m_UpdateProgressBarDlg->taskPortSetProgress(1);
    }
    updateTimer->stop();
}

void ScriptImportExport::UpdateTimerSlot()
{
    static int times = 0;
    if(times >= 150)
    {
        times = 0;
        m_UpdateProgressBarDlg->taskPortSetProgress(0);
    }
    times++;
}
//beging u盘导出
void ScriptImportExport::on_btnShell_U_clicked()
{
    m_script_type = SHELL_SCRIPT;
    SetButtonStyle(m_btn_pre, ui->btnShell_U);
    m_btn_pre = ui->btnShell_U;
    GetShellScriptFilesList(ui->listScriptFiles_U,SHELL_SCRIPT_PATH);
}

void ScriptImportExport::on_btnLua_U_clicked()
{
    m_script_type = LUA_SCRIPT;
    SetButtonStyle(m_btn_pre, ui->btnLua_U);
    m_btn_pre = ui->btnLua_U;
    GetShellScriptFilesList(ui->listScriptFiles_U,LUA_SCRIPT_PATH);
}

void ScriptImportExport::on_btnPython2_U_clicked()
{
    m_script_type = PYTHON2_SCRIPT;
    SetButtonStyle(m_btn_pre, ui->btnPython2_U);
    m_btn_pre = ui->btnPython2_U;
    GetShellScriptFilesList(ui->listScriptFiles_U,PY2_SCRIPT_PATH);
}

void ScriptImportExport::on_btnPython3_U_clicked()
{
    m_script_type = PYTHON3_SCRIPT;
    SetButtonStyle(m_btn_pre, ui->btnPython3_U);
    m_btn_pre = ui->btnPython3_U;
    GetShellScriptFilesList(ui->listScriptFiles_U,PY3_SCRIPT_PATH);
}

void ScriptImportExport::on_btnExport_U_clicked()
{
    QString fileName;
    fileName.clear();
    if (ui->listScriptFiles_U->count() > 0)
    {
        qDebug() << "count = " << ui->listScriptFiles_U->count();
        if (ui->listScriptFiles_U->currentItem())
            fileName = ui->listScriptFiles_U->currentItem()->text();
        qDebug() << "file name: " << fileName;
    }

    if(fileName.isEmpty())
    {
        QMessageBox::about(this,tr("提示"),tr("请选择要导出的文件！"));
        return;
    }
}
//end u盘导出

//beginu盘导入
void ScriptImportExport::on_btnShell_u_import_clicked()
{
    m_script_type = SHELL_SCRIPT;
    SetButtonStyle(m_btn_pre, ui->btnShell_u_import);
    m_btn_pre = ui->btnShell_u_import;
    GetShellScriptFilesList(ui->listScriptFiles_u_import,SHELL_SCRIPT_PATH);
}

void ScriptImportExport::on_btnLua_u_import_clicked()
{
    m_script_type = LUA_SCRIPT;
    SetButtonStyle(m_btn_pre, ui->btnLua_u_import);
    m_btn_pre = ui->btnLua_u_import;
    GetShellScriptFilesList(ui->listScriptFiles_u_import,LUA_SCRIPT_PATH);
}

void ScriptImportExport::on_btnPython2_u_import_clicked()
{
    m_script_type = PYTHON2_SCRIPT;
    SetButtonStyle(m_btn_pre, ui->btnPython2_u_import);
    m_btn_pre = ui->btnPython2_u_import;
    GetShellScriptFilesList(ui->listScriptFiles_u_import,PY2_SCRIPT_PATH);
}

void ScriptImportExport::on_btnPython3_u_import_clicked()
{
    m_script_type = PYTHON3_SCRIPT;
    SetButtonStyle(m_btn_pre, ui->btnPython3_u_import);
    m_btn_pre = ui->btnPython3_u_import;
    GetShellScriptFilesList(ui->listScriptFiles_u_import,PY3_SCRIPT_PATH);
}

void ScriptImportExport::on_btnImport_u_import_clicked()
{
    QString fileName;
    fileName.clear();
    if (ui->listScriptFiles_U->count() > 0)
    {
        qDebug() << "count = " << ui->listScriptFiles_u_import->count();
        if (ui->listScriptFiles_u_import->currentItem())
            fileName = ui->listScriptFiles_u_import->currentItem()->text();
        qDebug() << "file name: " << fileName;
    }

    if(fileName.isEmpty())
    {
        QMessageBox::about(this,tr("提示"),tr("请选择要导出的文件！"));
        return;
    }
}
