#include "AddToolFiles.h"
#include "ui_AddToolFiles.h"
#include <QMessageBox>
#include "TaskGlobal.h"

AddToolFiles::AddToolFiles(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddToolFiles)
{
    ui->setupUi(this);
    qApp->installEventFilter(this);
    updateTimer = new QTimer;
    m_UpdateProgressBarDlg = new UpdateProgressBarDlg(this);
    connect(updateTimer, &QTimer::timeout, this, &AddToolFiles::UpdateTimerSlot);
}

AddToolFiles::~AddToolFiles()
{
    qApp->removeEventFilter(this);
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

void AddToolFiles::on_btnImport_clicked()
{
    if (ui->lineEdit_ServerIp->text().isEmpty())
    {
        QMessageBox::about(NULL, "about", tr("IP不能为空!"));
        return ;
    }
//    QMessageBox::StandardButton rb = QMessageBox::question(NULL, \
//                                                           "Update", \
//                                                           "确定进行升级?", \
//                                                           QMessageBox::Yes | QMessageBox::No, \
//                                                           QMessageBox::No);
//    if(rb == QMessageBox::No)
//    {
//          return ;
//    }
    QString cmdStr = ui->lineEdit_ServerIp->text();
    QByteArray ba = cmdStr.toLatin1();
    char *serverIP = ba.data();

    m_UpdateProgressBarDlg->taskPortSetProgress(0);
    updateTimer->start(10);
    m_UpdateProgressBarDlg->show();
    int ret = ToolFileDownload(serverIP);
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

void AddToolFiles::UpdateTimerSlot()
{
    static int times = 0;
    if(times >= 150)
    {
        times = 0;
        m_UpdateProgressBarDlg->taskPortSetProgress(0);
    }
    times++;
}

bool AddToolFiles::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui->lineEdit_ServerIp)
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
