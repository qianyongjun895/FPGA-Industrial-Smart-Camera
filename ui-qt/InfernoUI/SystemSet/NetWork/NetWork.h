#ifndef NETWORK_H
#define NETWORK_H

#include <QWidget>
#include <QTimer>
#include "BusinessData/InterfaceLib/KeyBoardLib.h"
namespace Ui {
class NetWork;
}

class NetWork : public QWidget
{
    Q_OBJECT

public:
    explicit NetWork(QWidget *parent = 0);
    ~NetWork();

protected:
    bool eventFilter(QObject *watched, QEvent *event);

private slots:
    void on_btnOK_clicked();

    void on_radioButton_AutoIp_clicked();

    void on_radioButton_InputIP_clicked();

    void CheckerNetTimerSlot();

private:
    Ui::NetWork *ui;
    QTimer *CheckNetTimer;
    KeyBoardLib m_KeyBoardLib;
    void PanelInit(void);
};

#endif // NETWORK_H
