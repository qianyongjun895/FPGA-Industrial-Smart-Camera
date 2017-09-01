#ifndef LISTWIDGETIOTRIGGERITEM_H
#define LISTWIDGETIOTRIGGERITEM_H

#include <QWidget>

namespace Ui {
class ListWidgetIOTriggerItem;
}

class ListWidgetIOTriggerItem : public QWidget
{
    Q_OBJECT

public:
    explicit ListWidgetIOTriggerItem(QWidget *parent = 0);
    ~ListWidgetIOTriggerItem();
    void SetTaskName(QString str);

private slots:
    void on_TaskNameCheckBox_clicked();

    void on_IOTriggerWayCbB_currentIndexChanged(int index);

    void on_IOTriggerPortCbB_currentIndexChanged(int index);

private:
    Ui::ListWidgetIOTriggerItem *ui;
    int Ini_Flag;
    void SetTaskIOTriggerParam();
};

#endif // LISTWIDGETIOTRIGGERITEM_H
