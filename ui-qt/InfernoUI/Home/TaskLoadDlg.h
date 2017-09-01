#ifndef TASKLOADSAVE_H
#define TASKLOADSAVE_H

#include <QDialog>
#include <QTimer>

namespace Ui {
class TaskLoadDlg;
}

class TaskLoadDlg: public QDialog
{
    Q_OBJECT

public:
    explicit TaskLoadDlg(QWidget *parent = 0);
    ~TaskLoadDlg();
    QString GetFileName(){return m_fileName;}
private slots:
    void on_btnQuit_clicked();

    void GetTaskFileList();
    void on_btnOpen_clicked();

    void TaskLoadTimerSlot();
    void on_btnDel_clicked();

    void on_radioButtonUDisk_clicked();

    void on_radioButtonDefaultPath_clicked();

private:
    Ui::TaskLoadDlg *ui;

    void IniTabaleHead();
    void AddDataToTable(QString strTaskName,QString strCreator,QString strDate,QString strTaskInfo);
    void DelTableData();
    QTimer *LoadTaskTimer;
    QString m_fileName;
    QString m_task_path;
};

#endif // TASKLOADSAVE_H
