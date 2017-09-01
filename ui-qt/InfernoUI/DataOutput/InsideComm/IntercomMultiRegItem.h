#ifndef MULTIREGITEM_H
#define MULTIREGITEM_H

#include <QWidget>
#include <QLibrary>
#include "ModbusGlobal.h"
namespace Ui {
class IntercomMultiRegItem;
}

typedef QDialog* (*Fun_GetNumkeyBoardDlg)();
typedef QString (*Fun_GetNumString)();

typedef union {
    unsigned short bit_u16[4];
    int bit_i32[2];
    unsigned int bit_u32[2];
    float bit_f32[2];
    long bit_l32[2];
    double bit_d64;
}Input_Data;

class IntercomMultiRegItem : public QWidget
{
    Q_OBJECT

public:
    explicit IntercomMultiRegItem(QWidget *parent = 0);
    ~IntercomMultiRegItem();

    void SetNumber(int index);
    void SetRegAddr(int addr);
    void SetCurrentIndex(int index);
    void SetModbusMode(int mode);
    void SetToolType(int tool);
    void SetDataType(int Data_type, int Data_Length);
    void SetDataSource(MBS_WR_HOLD_REG *Data, int flag);
    void LoadKeyBoardLib();
    void NumKeyBoardDlg(QObject *watched, QEvent *event, int Min_value, int Max_value);

    void SetQuoteString(unsigned short task_index, unsigned short result_index);
    void SetDataSource(MBS_WR_INPUT_REG *Data, int flag);
    void SetDataSource(MBH_WR_HOLD_REG *Data, int flag);
protected:
    bool eventFilter(QObject *watched, QEvent *event);

private slots:
    void on_pushButton_DataSelect_clicked();

    void on_radioButton_Input_clicked();

    void on_radioButton_Quote_clicked();

    void on_lineEdit_Input_textChanged(const QString &arg1);

private:
    Ui::IntercomMultiRegItem *ui;
    QLibrary m_keyBoard_Lib;
    QDialog *Numkey;
    int Data_cnt;
    int Data_Type;
    int Current_index;
    int slave_or_host;
    int tool_type;
    QStringList Select_Data_List;
    Input_Data input_data;
    MBS_WR_HOLD_REG* S_WR_Hold_Reg_Data;
    MBS_WR_INPUT_REG* S_WR_Input_Reg_Data;

    MBH_WR_HOLD_REG* H_WR_Hold_Reg_Data;
    void GetInputData();
    void GetQuoteData();
    void SetInputValue(unsigned short *value);
};

#endif // MULTIREGITEM_H
