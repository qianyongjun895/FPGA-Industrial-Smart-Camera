#ifndef INSIDECOMM_H
#define INSIDECOMM_H

#include <QWidget>
#include <QLibrary>
#include "IntercomModbusDataListItem.h"
#include "IntercomModbusSelectDataDialog.h"
#include "IntercomMultiCoilItem.h"
#include "IntercomMultiRegDialog.h"
#include "IntercomMultiRegItem.h"
#include "IntercomRDSingleCoilDialog.h"
#include "IntercomReadRegDialog.h"
//#include "ModbusGlobal.h"
#include "IntercomWRMultiCoilDialog.h"
#include "IntercomModbusGlobal.h"
namespace Ui {
class InsideComm;
}
typedef QDialog* (*Fun_GetNumkeyBoardDlg)();
typedef QString (*Fun_GetNumString)();
class InsideComm : public QWidget
{
    Q_OBJECT

public:
    explicit InsideComm(QWidget *parent = 0);
    ~InsideComm();

protected:
    bool eventFilter(QObject *watched, QEvent *event);


private slots:
    void on_comboBox_Mode_currentIndexChanged(int index);

    void on_pushButton_connect_clicked();
    void on_btnAdd_clicked();
    void on_btnDelete_clicked();
    void on_btnUp_clicked();
    void on_btnDown_clicked();
    void on_tabWidget_currentChanged(int index);

private:
    Ui::InsideComm *ui;
    QLibrary m_keyBoard_Lib;
    QDialog *Numkey;
    int slave_or_host;
    int list_cnt;
    void LoadKeyBoardLib();
    void NumKeyBoardDlg(QObject *watched, QEvent *event, int Min_value, int Max_value);
    void IniData();
    void IniSlaveOrHost();
    void AddCommandItemData(IntercomModbusDataListItem *pListWidgeModbusItem);
    void AddListWidgetItem(QString String, int Current_index, int Host_Or_Slave, int Tool_type);
    void AddSlaveReadCoil();
    void AddSlaveWriteCoil();
    void AddSlaveWriteDiscrete();
    void AddSlaveReadHoldReg();
    void AddSlaveWriteHoldReg();
    void AddSlaveWriteInputReg();
    void AddHostReadCoil();
    void AddHostWriteCoil();
    void AddHostReadDiscrete();
    void AddHostReadHoldReg();
    void AddHostWriteHoldReg();
    void AddHostReadInputReg();
};

#endif // INSIDECOMM_H
