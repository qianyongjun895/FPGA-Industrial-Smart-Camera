#ifndef TASKSAVEDLG_H
#define TASKSAVEDLG_H

#include <QDialog>
#include <QTimer>
#include <stdbool.h>
#include "BusinessData/InterfaceLib/KeyBoardLib.h"
namespace Ui {
class TaskSaveDlg;
}

class TaskSaveDlg : public QDialog
{
    Q_OBJECT

public:
    explicit TaskSaveDlg(QWidget *parent = 0);
    ~TaskSaveDlg();

    bool isLegal(QString text);

private slots:
    void on_btnSave_clicked();

    void on_btnDel_clicked();

    void on_btnQuit_clicked();

    void TaskSaveTimerSlot();
    void GetTaskFileList();
    void on_radioButtonDefaultPath_clicked();

    void on_radioButtonUDisk_clicked();

signals:
    void signalTaskName(int bexit, QString strName);
private:
    Ui::TaskSaveDlg *ui;
    QString m_SaveTime;
    QTimer *TaskSaveTimer;
    KeyBoardLib m_KeyBoardLib;
    QString m_file_path;
    void IniTabaleHead();
    void AddDataToTable(QString strTaskName,QString strCreator,QString strDate,QString strTaskInfo);
    void DelTableData();
    bool SaveCurTaskFile(QString taskName, QString description);
    void SaveTaskFileFinished();
    bool SameFileNameCheck(QString fileName);

};

#endif // TASKSAVEDLG_H
