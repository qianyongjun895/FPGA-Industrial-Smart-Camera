#ifndef RUNSTATISTICS_H
#define RUNSTATISTICS_H


#include <QDialog>
#include "TaskStepGlobal.h"

namespace Ui {
class RunStatistics;
}

class RunStatistics : public QDialog
{
    Q_OBJECT

public:
    explicit RunStatistics(QWidget *parent = 0);
    ~RunStatistics();

    void InitTable(QStringList task_list);
private slots:
    void on_btnClear_clicked();

    void on_btnQuite_clicked();

private:
    Ui::RunStatistics *ui;
};

#endif // RUNSTATISTICS_H
