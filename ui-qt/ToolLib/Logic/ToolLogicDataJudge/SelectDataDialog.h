#ifndef MODBUSSELECTDATADIALOG_H
#define MODBUSSELECTDATADIALOG_H

#include <QDialog>
#include <QLibrary>
#include <QStringList>
#include "LinkDataGlobal.h"

//数据类型
#define DATA_SINT		    0
#define SINT_INVERT		    1
#define DATA_UINT		    2
#define UINT_INVERT		    3
#define DATA_FLT			4
#define FLT_INVERT	        5
#define DATA_LONG		    6
#define LONG_INVERT	        7
#define DATA_DBL			8
#define DATA_DBL_INVERT	    9

namespace Ui {
class SelectDataDialog;
}

typedef QDialog* (*Fun_GetNumkeyBoardDlg)();
typedef QString (*Fun_GetNumString)();
typedef void (*Fun_SetNumString)(QString NumString);

class SelectDataDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SelectDataDialog(int currentIndex, QWidget *parent = 0);
    ~SelectDataDialog();

    void IniData(int currentIndex);
    void InitTaskListTableWidget(int index, QString taskName);
    void InitTaskResultListTableWidget(int index, QString taskResult);
    void InitTaskDataListTableWidget(int index, QString taskResult);

    QString GetSelectDataList(){return Select_Data_List;}
    QString GetUpLimit();
    QString GetDownLimit();
    int GetDataType(){return m_data_type;}
    void DetailInitData(QString datalist, QString uplimit, QString downlimit, QString datatype);
protected:
    bool eventFilter(QObject *watched, QEvent *event);
private slots:
    void on_tableWidget_task_cellClicked(int row, int column);

    void on_tableWidget_detail_cellClicked(int row, int column);
    void on_tableWidget_data_cellClicked(int row, int column);
    void on_pushButton_OK_clicked();

    void on_pushButton_Cancel_clicked();

private:
    Ui::SelectDataDialog *ui;
    QString Select_Data_List;
    unsigned int task_type;
    unsigned int multi_flag;
    int task_pre_index;
    int detail_pre_index;
    int m_data_type;//数据类型
    int m_step_index;
    void GetDataInfo();
    QLibrary m_keyBoard_Lib;
    void LoadKeyBoardLib();
    void SetLineEditLimit();
    void RangeJudge();
};

#endif // MODBUSSELECTDATADIALOG_H
