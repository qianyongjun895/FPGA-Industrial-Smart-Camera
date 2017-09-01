#ifndef SERIALPORTWIDGET_H
#define SERIALPORTWIDGET_H

#include <QWidget>
#include <QHash>
#include <QLibrary>
#include <QDialog>
#include <QString>
#include "UartGlobal.h"
namespace Ui {
class SerialPortWidget;
}

typedef QDialog* (*Fun_GetkeyBoardDlg)();
typedef QString (*Fun_GetInputString)();


typedef QDialog* (*Fun_GetNumkeyBoardDlg)();
typedef QString (*Fun_GetNumString)();

class SerialPortWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SerialPortWidget(QWidget *parent = 0);
    ~SerialPortWidget();

    int Protocol_Type;
    bool EnableFlag;

    void IniData();
    void NumKeyBoardDlg(QObject *watched, QEvent *event, int Min_value, int Max_value);
protected:
    bool eventFilter(QObject *watched, QEvent *event);
private slots:
    void on_btnOpen_clicked();

    void on_comboBoxWorkKind_currentIndexChanged(int index);

private:
    Ui::SerialPortWidget *ui;
    int Ini_Flag;
    QLibrary m_keyBoard_Lib;
    QDialog *m_dlg;
    QDialog *Numkey;
    QHash<int, int> Uart_Baud;
    QHash<int, int> Data_Bit;

    void LoadKeyBoardLib();
    void WidgetEnable(bool enable_flag);
    int SetUartParam();
    void SaveUartParam(int open_Flag);
};

#endif // SERIALPORTWIDGET_H
