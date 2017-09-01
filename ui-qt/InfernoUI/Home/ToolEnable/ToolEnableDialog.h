#ifndef TOOLENABLEDIALOG_H
#define TOOLENABLEDIALOG_H

#include <QDialog>
#include "TaskHeaderGlobal.h"
#include "TaskStepGlobal.h"
#include "LinkDataGlobal.h"
#include <QListWidgetItem>

namespace Ui {
class ToolEnableDialog;
}

class ToolEnableDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ToolEnableDialog(QWidget *parent = 0);
    ~ToolEnableDialog();
    void InitList(QStringList task_list);

private slots:
    void on_okButton_clicked();

    void on_cancelButton_clicked();

    void on_checkBox_SelectAll_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);

private:
    Ui::ToolEnableDialog *ui;
};

#endif // TOOLENABLEDIALOG_H
