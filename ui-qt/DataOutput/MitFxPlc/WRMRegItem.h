#ifndef WRMREGITEM_H
#define WRMREGITEM_H

#include <QWidget>
#include "MitFxPlcGlobal.h"
namespace Ui {
class WRMRegItem;
}

class WRMRegItem : public QWidget
{
    Q_OBJECT

public:
    explicit WRMRegItem(QWidget *parent = 0);
    ~WRMRegItem();

    void SetNumber(int num);
    void SetMRegAddr(int addr);
    void SetToolType(int tool);
    void SetDataSource(PLC_READ_M_REG *reg);
    void SetDataSource(PLC_WRITE_M_REG *reg);
private slots:
    void on_radioButton_no_clicked();

    void on_radioButton_off_clicked();

private:
    Ui::WRMRegItem *ui;
    int tool_type;
    PLC_READ_M_REG* RD_M_Reg;
    PLC_WRITE_M_REG* WR_M_Reg;
};

#endif // WRMREGITEM_H
