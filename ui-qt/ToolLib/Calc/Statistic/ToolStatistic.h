#ifndef TOOLSTATISTIC_H
#define TOOLSTATISTIC_H

#include <QWidget>
#include <QLibrary>
#include <QHash>
#include "DataStatGlobal.h"
namespace Ui {
class ToolStatistic;
}
typedef QDialog* (*Fun_GetNumkeyBoardDlg)();
typedef QString (*Fun_GetNumString)();
class ToolStatistic : public QWidget
{
    Q_OBJECT

public:
    explicit ToolStatistic(QWidget *parent = 0);
    ~ToolStatistic();

    int Set_Parameter_To_Ram();
    void Init_Input_Ptr(void *ptr,int i_step_index,int new_flag,void *pen_color);
protected:
    bool eventFilter(QObject *watched, QEvent *event);

private slots:
    void on_listWidget_Task_currentRowChanged(int currentRow);
    void on_listWidget_Result_currentRowChanged(int currentRow);

    void on_checkBox_ValidValue_clicked();

private:
    Ui::ToolStatistic *ui;
    int Current_Step;
    int Select_Finish_Flag;
    DATASTST_INPUT_PARAM* pInputPara;
    QLibrary m_keyBoard_Lib;
    QDialog *Numkey;
    QHash<int,int>Task_List_Hash;
    void InitTaskListItem();
    void LoadKeyBoardLib();
    void NumKeyBoardDlg(QObject *watched, QEvent *event, int Min_value, int Max_value);
};

#endif // TOOLSTATISTIC_H
