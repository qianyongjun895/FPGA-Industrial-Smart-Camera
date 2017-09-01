#ifndef ETHERNETPORTWIDGET_H
#define ETHERNETPORTWIDGET_H

#include <QWidget>
#include <QLibrary>
#include <QDialog>
#include "TcpGlobal.h"
namespace Ui {
class EthernetPortWidget;
}

typedef QDialog* (*Fun_GetkeyBoardDlg)();
typedef QString (*Fun_GetInputString)();

typedef QDialog* (*Fun_GetNumkeyBoardDlg)();
typedef QString (*Fun_GetNumString)();
typedef void (*Fun_SetNumString)(QString NumString);

class EthernetPortWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EthernetPortWidget(QWidget *parent = 0);
    ~EthernetPortWidget();

    int Protocol_Type;
    bool EnableFlag;

    int SetEthernetParam();
    void IniData();
    void NumKeyBoardDlg(QObject *watched, QEvent *event, int Min_value, int Max_value);
protected:
    bool eventFilter(QObject *watched, QEvent *event);


private slots:

    void on_StartpushButton_clicked();

    void on_btnSend_clicked();

    void on_EthernetPortcbB_currentIndexChanged(int index);

private:
    Ui::EthernetPortWidget *ui;
    int Ini_Flag;

    TCP_CONFIG tcp_param;
    QLibrary m_keyBoard_Lib;
    QDialog *m_dlg;
    QDialog *Numkey;
    void WidgetEnable(bool flag);
    void LoadKeyBoardLib();
    void SaveTcpParam(int open_Flag);
};

#endif // ETHERNETPORTWIDGET_H
