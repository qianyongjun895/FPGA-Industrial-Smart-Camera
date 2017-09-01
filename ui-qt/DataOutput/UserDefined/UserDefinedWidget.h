#ifndef USERDEFINEDWIDGET_H
#define USERDEFINEDWIDGET_H

#include <QWidget>
#include <QLibrary>
#include <QString>
#include <QHash>
#include <QListWidgetItem>
#include "CmdTriggerItem.h"

namespace Ui {
class UserDefinedWidget;
}

typedef QDialog* (*Fun_GetkeyBoardDlg)();
typedef QString (*Fun_GetInputString)();
typedef void (*Fun_SetInputString)(QString str);

typedef QDialog* (*Fun_GetNumkeyBoardDlg)();
typedef QString (*Fun_GetNumString)();

class UserDefinedWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UserDefinedWidget(QWidget *parent = 0);
    ~UserDefinedWidget();

    void NumKeyBoardDlg(QObject *watched, QEvent *event, int Min_value, int Max_value);
    void KeyBoardDlg(QObject *watched, QEvent *event, int dlg_x, int dlg_y, QString str, int String_Len);
    void IniData();
    void SetUserDefinedData();
protected:
    bool eventFilter(QObject *watched, QEvent *event);
private slots:
    void on_btnAdd_clicked();

    void on_txtLable_textChanged(const QString &arg1);


    void on_listWidgetData_currentRowChanged(int currentRow);

    void on_lineEditFieldWidth_textChanged(const QString &arg1);

    void on_comboBoxFill_currentIndexChanged(int index);


    void on_comboBoxTask_currentIndexChanged(int index);

    void on_checkBoxFixWidth_clicked();

    void on_checkBox_Now_send_clicked();

    void on_checkBoxIncludeLabel_clicked();

    void on_checkBoxSplit_clicked();

    void on_btnDown_clicked();
    void on_btnUp_clicked();
    void on_btnDelete_clicked();

    void on_radioButtonStandard_clicked();

    void on_radioButtonOther_clicked();

    void on_comboBoxStandard_currentIndexChanged(int index);

    void on_txtOther_textChanged(const QString &arg1);

    void on_tabWidget_currentChanged(int index);

    void on_txtEndString_textChanged(const QString &arg1);

    void on_txtStartString_textChanged(const QString &arg1);

    void on_checkBox_manual_send_clicked();

private:
    Ui::UserDefinedWidget *ui;
    QVector<QStringList> DataVector;

    int list_cnt;
    int Change_Flag;
    QHash<QString, int> End_Symbol;
    QHash<QString, int> Standard;
    QHash<QString, int> Data_type;
    QHash<QString, int> Data_Fill;

    QLibrary m_keyBoard_Lib;
    QDialog *m_dlg;
    QDialog *Numkey;
    void LoadKeyBoardLib();
    void ListOutPutdata();
    QString FillOutPutdata(QString str, QString strNumber);
    void AddCmdTriggerItem(CmdTriggerItem *item);
    void SetTaskData(unsigned int list_index, unsigned int data_index, QStringList list_string, QString task_string);
    void SetGData(unsigned int list_index, unsigned int data_index, unsigned int type, unsigned int addr);
    void SetManualData(unsigned int list_index, unsigned int data_index, float data);
    QStringList InitTaskData(unsigned int List_index, unsigned int Data_index);
    QStringList InitGData(unsigned int List_index, unsigned int Data_index);
    QStringList InitManualData(unsigned int List_index, unsigned int Data_index);
};

#endif // USERDEFINEDWIDGET_H
