#ifndef COMMONDATASELECTDIALOG_H
#define COMMONDATASELECTDIALOG_H

#include <QDialog>
#include "QListWidgetItem"

namespace Ui {
class CommonDataSelectDialog;
}

class CommonDataSelectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CommonDataSelectDialog(QWidget *parent = 0);
    ~CommonDataSelectDialog();

    QString GetDataList(){return m_data_list;}

    void InitTaskList(int type,int current_index);

private slots:
    void on_btnOk_clicked();

    void on_btnCancel_clicked();

    void on_listWidget_TaskList_currentTextChanged(const QString &currentText);

    void on_listWidget_DataList_itemClicked(QListWidgetItem *item);

private:
    Ui::CommonDataSelectDialog *ui;
    //PublicLinkData *p_PublicLinkData;
    QString m_task;
    QString m_data_list;
    int data_type;

};

#endif // COMMONDATASELECTDIALOGDIALOG_H
