#ifndef UPGRADESTATUSDIALOG_H
#define UPGRADESTATUSDIALOG_H

#include <QDialog>
#include <QTimer>

namespace Ui {
class UpgradeStatusDialog;
}

class UpgradeStatusDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UpgradeStatusDialog(QWidget *parent = 0);
    ~UpgradeStatusDialog();

private slots:
    void updateTimerSlot();

    void on_btnOK_clicked();

private:
    Ui::UpgradeStatusDialog *ui;
    QTimer *updateTimer;
    int prgBarValue;
};

#endif // UPGRADESTATUSDIALOG_H
