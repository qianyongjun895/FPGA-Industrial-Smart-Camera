#ifndef RUNOSDSTYLEITEM_H
#define RUNOSDSTYLEITEM_H

#include <QWidget>

namespace Ui {
class RunOsdStyleItem;
}

class RunOsdStyleItem : public QWidget
{
    Q_OBJECT

public:
    explicit RunOsdStyleItem(QWidget *parent = 0);
    ~RunOsdStyleItem();

    QString GetTaskStep();
    void SetTaskName(QString strName,int value);

private slots:
    void on_checkBoxTaskName_clicked();
    void on_checkBoxListOK_clicked();

    void on_checkBoxListNG_clicked();

signals:
    void ChangeItemCheck(int value,QString strStept);

private:
    Ui::RunOsdStyleItem *ui;
    int IsHasPreModule();
    int GetROIState();

};

#endif // RUNOSDSTYLEITEM_H
