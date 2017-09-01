#ifndef TASKIMPORTEXPORT_H
#define TASKIMPORTEXPORT_H

#include <QWidget>
#include <QTimer>
#include <QListWidget>
#include "../UpdateProgressBarDlg.h"
#include "BusinessData/InterfaceLib/KeyBoardLib.h"
namespace Ui {
class TaskImportExport;
}

class TaskImportExport : public QWidget
{
    Q_OBJECT

public:
    explicit TaskImportExport(QWidget *parent = 0);
    ~TaskImportExport();

protected:
    bool eventFilter(QObject *watched, QEvent *event);

private slots:
    void GetTaskFileList(QListWidget *pList, QString strPath);
    void on_listWidget_TaskFileName_currentRowChanged(int currentRow);

    void on_btnExport_clicked();

    void on_btnImport_clicked();

    void UpdateTimerSlot();

    void on_listWidget_TaskFileName_U_clicked(const QModelIndex &index);

    void on_btn_U_Import_clicked();

private:
    Ui::TaskImportExport *ui;
    QVector<QString> m_task_creater;
    QVector<QString> m_task_date;
    QVector<QString> m_task_info;
    KeyBoardLib m_KeyBoardLib;
    QTimer *updateTimer;
    UpdateProgressBarDlg *m_UpdateProgressBarDlg;

    bool isLegal(QString text);
};

#endif // TASKIMPORTEXPORT_H
