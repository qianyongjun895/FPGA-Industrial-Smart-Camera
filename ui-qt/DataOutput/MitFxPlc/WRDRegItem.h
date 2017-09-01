#ifndef WRDREGITEM_H
#define WRDREGITEM_H

#include <QWidget>
#include <QLibrary>
#include "MitFxPlcGlobal.h"
#include "WRDRegSelectDataDialog.h"

namespace Ui {
class WRDRegItem;
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
class WRDRegItem : public QWidget
{
    Q_OBJECT

public:
    explicit WRDRegItem(QWidget *parent = 0);
    ~WRDRegItem();

    void SetNumber(int index);
    void SetRegAddr(int addr);
    void SetCurrentIndex(int index);
    void SetModbusMode(int mode);
    void SetToolType(int tool);
    void SetDataType(int Data_type, int Data_Length);
    void LoadKeyBoardLib();
    void NumKeyBoardDlg(QObject *watched, QEvent *event, int Min_value, int Max_value);

    void SetQuoteString(unsigned short task_index, unsigned short result_index);
    void SetDataSource(PLC_WRITE_D_REG *Data, int flag);
protected:
    bool eventFilter(QObject *watched, QEvent *event);

private slots:
    void on_pushButton_DataSelect_clicked();

    void on_radioButton_Input_clicked();

    void on_radioButton_Quote_clicked();

    void on_lineEdit_Input_textChanged(const QString &arg1);
private:
    Ui::WRDRegItem *ui;
    QLibrary m_keyBoard_Lib;
    QDialog *Numkey;
    int Data_cnt;
    int Data_Type;
    int Current_index;
    int slave_or_host;
    int tool_type;
    PLC_WRITE_D_REG *WR_D_Reg;
    QStringList Select_Data_List;
    Input_Data input_data;
    void GetInputData();
    void GetQuoteData();
    void SetInputValue(unsigned short *value);
};

#endif // WRDREGITEM_H
