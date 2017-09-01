#ifndef UDPCOMMWIDGET_H
#define UDPCOMMWIDGET_H

#include <QWidget>
#include <QLibrary>
#include <QDialog>

namespace Ui {
class UdpCommWidget;
}

typedef QDialog* (*Fun_GetkeyBoardDlg)();
typedef QString (*Fun_GetInputString)();

typedef QDialog* (*Fun_GetNumkeyBoardDlg)();
typedef QString (*Fun_GetNumString)();
typedef void (*Fun_SetNumString)(QString NumString);

class UdpCommWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UdpCommWidget(QWidget *parent = 0);
    ~UdpCommWidget();

    int Protocol_Type;
    bool EnableFlag;

    void IniData();
    int SetUdpParam();
    void NumKeyBoardDlg(QObject *watched, QEvent *event, int Min_value, int Max_value);
protected:
    bool eventFilter(QObject *watched, QEvent *event);
private slots:
    void on_StartpushButton_clicked();

private:
    Ui::UdpCommWidget *ui;
    QLibrary m_keyBoard_Lib;
    QDialog *m_dlg;
    QDialog *Numkey;
    void WidgetEnable(bool enable_flag);
    void LoadKeyBoardLib();
    void SaveUdpParam(int open_Flag);
};

#endif // UDPCOMMWIDGET_H
