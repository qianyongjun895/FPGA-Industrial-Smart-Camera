#ifndef SYNTHETICJUDGMENT_H
#define SYNTHETICJUDGMENT_H

#include <QDialog>
#include <QCloseEvent>
#include <stdbool.h>



namespace Ui {
class SyntheticJudgment;
}

class SyntheticJudgment : public QDialog
{
    Q_OBJECT

public:
    explicit SyntheticJudgment(QWidget *parent = 0);
    ~SyntheticJudgment();
   // SSTaskEditBase *m_p_object;

    void InitList(QStringList task_list);
private slots:

    void AddItemToTableTaskList(int Rows);
    void on_checkBox_SelectAll_clicked(bool checked);

    void on_checkBox_OKEnable_toggled(bool checked);

    void on_checkBox_NGEnable_toggled(bool checked);

    void on_radioButton_OKIO1_clicked(bool checked);

    void on_radioButton_OKIO2_clicked(bool checked);

    void on_radioButton_OKIO3_clicked(bool checked);
    void on_radioButton_OKIO4_clicked(bool checked);
    void on_radioButton_NGIO1_clicked(bool checked);

    void on_radioButton_NGIO2_clicked(bool checked);

    void on_radioButton_NGIO3_clicked(bool checked);
    void on_radioButton_NGIO4_clicked(bool checked);
    void on_checkBox_FinishEnable_toggled(bool checked);

    void on_radioButton_FinishIO1_clicked(bool checked);

    void on_radioButton_FinishIO2_clicked(bool checked);

    void on_radioButton_FinishIO3_clicked(bool checked);

    void on_radioButton_FinishIO4_clicked(bool checked);

    void on_btnOK_clicked();

    void on_btnQuit_clicked();

    void on_tableWidget_TaskList_cellClicked(int row, int column);

private:
    Ui::SyntheticJudgment *ui;
    //DataModel *dataModel;

    QStringList TaskList;
};

#endif // SYNTHETICJUDGMENT_H
