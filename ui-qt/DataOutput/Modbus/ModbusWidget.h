#ifndef MODBUSWIDGET_H
#define MODBUSWIDGET_H

#include <QWidget>
#include <QLibrary>
#include <QDialog>
#include <QHash>

#include "ModbusDataListItem.h"
namespace Ui {
class ModbusWidget;
}

typedef QDialog* (*Fun_GetNumkeyBoardDlg)();
typedef QString (*Fun_GetNumString)();

class ModbusWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ModbusWidget(QWidget *parent = 0);
    ~ModbusWidget();

    void LoadKeyBoardLib();
    void NumKeyBoardDlg(QObject *watched, QEvent *event, int Min_value, int Max_value);
    void SetModbusData();
    void AddCommandItemData(ModbusDataListItem *pListWidgeModbusItem);

    void AddSlaveReadCoil();
    void AddSlaveWriteCoil();
    void AddSlaveWriteDiscrete();
    void AddSlaveReadHoldReg();
    void AddSlaveWriteHoldReg();
    void AddSlaveWriteInputReg();

    void AddHostWriteCoil();
    void AddHostReadCoil();
    void AddHostReadDiscrete();
    void AddHostReadHoldReg();
    void AddHostWriteHoldReg();
    void AddHostReadInputReg();

    void IniSlaveOrHost();

    void IniData();
    void AddListWidgetItem(QString String, int Current_index, int Host_Or_Slave, int Tool_type);
private slots:

    void on_btnAdd_clicked();

    void on_btnDelete_clicked();

    void on_btnUp_clicked();

    void on_btnDown_clicked();

private:
    Ui::ModbusWidget *ui;
    QLibrary m_keyBoard_Lib;
    QDialog *Numkey;
    int slave_or_host;
    int list_cnt;
};

#endif // MODBUSWIDGET_H
