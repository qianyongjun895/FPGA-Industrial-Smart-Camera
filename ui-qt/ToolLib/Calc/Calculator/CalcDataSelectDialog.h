#ifndef CALCDATASELECTDIALOG_H
#define CALCDATASELECTDIALOG_H

#include <QDialog>
#include "QListWidgetItem"
#include <stdbool.h>
#include <QLibrary>

namespace Ui {
class CalcDataSelectDialog;
}
typedef QDialog* (*Fun_GetNumkeyBoardDlg)();
typedef QString (*Fun_GetNumString)();
class CalcDataSelectDialog : public QDialog
{
    Q_OBJECT
public:
    enum{
        SELECT_INPUT_DATA = 0,
        SELECT_TASK_DATA,
        SELECT_MODBUS_DATA,
        SELECT_CALC_DATA,
        SELECT_PLC_DATA,
        SELECT_DATA_INPUT,
    };

public:
    explicit CalcDataSelectDialog(QWidget *parent = 0);
    ~CalcDataSelectDialog();

    void InitDataSelect(int source, int calc_cnt, int currentstep);


    int m_Mul_index; //0普通任务，1多结果任务
    int m_task_index;//数据引用任务索引
    int m_result_index;// 数据引用结果索引
    int m_Mul_data_index; //多结果任务的数据索引

    int m_reg_type;//Modbus寄存器类型
    int m_data_type;// Modbus数据类型
    int m_address;//Modbus 起始地址

    int m_calc_item_index;//计算项索引
    int m_calc_result_index;//计算项结果索引（现在都为1）

    int m_plc_data_type;//plc数据类型
    int m_plc_address;//plc起始地址

    unsigned Data_Input_Type;//数据输入的类型
    int Data_Input_Addr;//数据输入的地址


    QString m_task_str;
    QString m_calc_str;
    QString m_input_str;
    int m_data_source;
    int m_calc_item_cnt;


private slots:
    void on_Okbtn_clicked();

    void on_Cancelbtn_clicked();

    void on_radioButton_HoldReg_toggled(bool checked);

    void on_radioButton_InputReg_clicked();

    void on_comboBox_DataType_activated(int index);

    void on_listWidget_TaskList_currentTextChanged(const QString &currentText);

    void on_listWidget_CalcItem_currentTextChanged(const QString &currentText);

    void on_listWidget_Result_itemClicked(QListWidgetItem *item);

    void on_listWidget_Data_list_itemClicked(QListWidgetItem *item);

    void on_listWidget_MulData_itemClicked(QListWidgetItem *item);

    void on_comboBox_PLCDataType_activated(int index);

    void on_radioButton_manual_clicked();

    void on_radioButton_Ref_clicked();

    void on_radioButton_Mbs_clicked();

    void on_radioButton_Calc_clicked();

    void on_radioButton_Input_clicked();

private:
    Ui::CalcDataSelectDialog *ui;
    //CalcuatorData *p_CalcData;
    int i_currentStep;
    QLibrary m_keyBoard_Lib;
    QDialog *Numkey;

    int m_MaxAddress;//根据数据类型设置的最大起始地址
protected:
    bool eventFilter(QObject *obj, QEvent *event);
    void LoadKeyBoardLib();
    void NumKeyBoardDlg(QObject *watched, QEvent *event);
};

#endif // CALCDATASELECTDIALOG_H
