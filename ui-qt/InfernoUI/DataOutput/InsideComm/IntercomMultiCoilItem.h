#ifndef MULTICOILITEM_H
#define MULTICOILITEM_H

#include <QWidget>
#include "ModbusGlobal.h"
namespace Ui {
class IntercomMultiCoilItem;
}

class IntercomMultiCoilItem : public QWidget
{
    Q_OBJECT

public:
    explicit IntercomMultiCoilItem(QWidget *parent = 0);
    ~IntercomMultiCoilItem();

    void SetNumber(int index);
    void setCoilAddr(int addr);
    void SetDataSource(MBS_WR_COIL *Data);
    void SetCurrentIndex(int index);
    void SetModbusMode(int mode);
    void SetToolType(int tool);
    void SetDataSource(MBS_WR_DISCRETE *Data);
    void SetDataSource(MBH_RD_COILS *Data);
    void SetDataSource(MBH_WR_COILS *Data);
    void SetDataSource(MBH_RD_DISCRETE *Data);
private slots:
    void on_radioButton_OFF_clicked();

    void on_radioButton_ON_clicked();

private:
    Ui::IntercomMultiCoilItem *ui;
    int Current_index;
    int slave_or_host;
    int tool_type;
    MBS_WR_COIL* WR_Coil_Data;
    MBS_WR_DISCRETE* WR_Discrete_Data;
    MBH_RD_COILS* H_RD_Coil_Data;
    MBH_WR_COILS* H_WR_Coil_Data;
    MBH_RD_DISCRETE* H_RD_Discrete_Data;
};

#endif // MULTICOILITEM_H
