#ifndef IOTRIGGERWIDGET_H
#define IOTRIGGERWIDGET_H

#include <QWidget>
#include <QLibrary>
#include <QTimer>
#include <QHash>
#include "ListWidgetIOTriggerItem.h"
#include "../../../include/lzynq_include/io.h"
namespace Ui {
class IOTriggerWidget;
}
typedef QDialog* (*Fun_GetNumkeyBoardDlg)();
typedef QString (*Fun_GetNumString)();

class IOTriggerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit IOTriggerWidget(QWidget *parent = 0);
    ~IOTriggerWidget();

protected:
    bool eventFilter(QObject *watched, QEvent *event);
private slots:
    void on_tabWidget_currentChanged(int index);

    void on_IO1TestButton_clicked();

    void on_IO2TestButton_clicked();

    void IO1_Trigger_Test_Slot();
    void IO2_Trigger_Test_Slot();

private:
    Ui::IOTriggerWidget *ui;
    QLibrary m_keyBoard_Lib;
    QDialog *Numkey;
    IO_TRIGGER_CONFIG IO_triggerParam;
    QTimer IO1_test_time;
    QTimer IO2_test_time;
    int Test_Flag;
    QHash<QString, int> Trigger_Type_Hash;
    void LoadKeyBoardLib();
    void NumKeyBoardDlg(QObject *watched, QEvent *event, int Min_value, int Max_value);

    void AddTaskListItem(ListWidgetIOTriggerItem *item);
    void ClearListWidget();
    void SetIOTriggerParam();
    void GetIOTriggerParam();
};

#endif // IOTRIGGERWIDGET_H
