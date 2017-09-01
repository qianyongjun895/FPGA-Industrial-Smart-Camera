#ifndef USERDEFINESELECTDIALOG_H
#define USERDEFINESELECTDIALOG_H

#include <QDialog>
#include <QStringList>
#include <QVector>
#include <QLibrary>
#include <QHash>
namespace Ui {
class UserDefineSelectDialog;
}
typedef QDialog* (*Fun_GetNumkeyBoardDlg)();
typedef QString (*Fun_GetNumString)();
class UserDefineSelectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UserDefineSelectDialog(QWidget *parent = 0);
    ~UserDefineSelectDialog();
    void SetDataListIndex(int index){List_Index = index;}

    void InitTaskListTableWidget(int index, QString taskName);
    void InitTaskResultListTableWidget(int index, QString taskResult);
    void InitTaskDataListTableWidget(int index, QString taskResult);
    void InitSelectDataListTableWidget(QString strTask, QString strResult, QString strData);

    QString GetSelectData(){return Select_Data;}
    void SetSelectData(QString Data){Select_Data = Data;}

    void EditModeInit();
    void IniData();
private slots:
    void on_pushButton_OK_clicked();

    void on_tableWidget_task_cellClicked(int row, int column);

    void on_tableWidget_detail_cellClicked(int row, int column);

    void on_tableWidget_data_cellClicked(int row, int column);

    void on_pushButton_ADD_clicked();

    void on_pushButton_del_clicked();

    void on_pushButton_Down_clicked();

    void on_pushButton_Up_clicked();

    void on_pushButton_quit_clicked();

    void on_radioButt_data_link_clicked();

    void on_radioButton_G_data_clicked();

    void on_radioButton_Manual_clicked();
    void on_comboBox_Data_type_currentIndexChanged(const QString &arg1);

    void on_lineEdit_decimals_textChanged(const QString &arg1);

    void on_tableWidget_FA_itemSelectionChanged();

protected:
    bool eventFilter(QObject *watched, QEvent *event);
private:
    Ui::UserDefineSelectDialog *ui;
    QString Select_Data;
    unsigned int current_Data_index;
    unsigned int task_type;
    unsigned int multi_flag;
    int task_pre_index;
    int detail_pre_index;
    int Edit_Flag;
    int List_Index;
    QLibrary m_keyBoard_Lib;
    QDialog *Numkey;
    QHash<int,QString>Data_Type;
    void LoadKeyBoardLib();
    void NumKeyBoardDlg(QObject *watched, QEvent *event);
    void InitGDataDataListTableWidget(QString type, QString Id);
    void InitManualDataListTableWidget(QString data);
    void DownListData();
    void UpListData();
    void SetManualData(unsigned int list_index, unsigned int data_index, float data);
    void SetGData(unsigned int list_index, unsigned int data_index, unsigned int type, unsigned int addr);
    void SetTaskData(unsigned int list_index, unsigned int data_index, QStringList list_string, QString task_string);
    QStringList InitManualData(unsigned int List_index, unsigned int Data_index);
    QStringList InitGData(unsigned int List_index, unsigned int Data_index);
    QStringList InitTaskData(unsigned int List_index, unsigned int Data_index);
};

#endif // USERDEFINESELECTDIALOG_H
