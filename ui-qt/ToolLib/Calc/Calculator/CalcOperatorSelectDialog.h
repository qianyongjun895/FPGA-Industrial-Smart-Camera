#ifndef CALCOPERATORSELECTDIALOG_H
#define CALCOPERATORSELECTDIALOG_H

#include <QDialog>
#include <QListWidgetItem>
namespace Ui {
class CalcOperatorSelectDialog;
}

class CalcOperatorSelectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CalcOperatorSelectDialog(QWidget *parent = 0);
    ~CalcOperatorSelectDialog();
    void SetDataByOperator(int Op_type_index, int Op_index);
    void AddOperatorItem(QString strTemp,QListWidget *plistWidgetOperatorSelect);

    void InitOperatorInfo(QStringList info);
    int m_use_data_count;
    QString strInfo;
    QString  m_str_operator_type;

private slots:


    void on_btnOk_clicked();

    void on_btnQuit_clicked();


    void on_listWidgetOperatorTypeSelect_itemClicked(QListWidgetItem *item);

    void on_listWidgetOperatorSelect_itemClicked(QListWidgetItem *item);

private:
    QStringList str_operator_info;
    Ui::CalcOperatorSelectDialog *ui;


};

#endif // CALCOPERATORSELECTDIALOG_H
