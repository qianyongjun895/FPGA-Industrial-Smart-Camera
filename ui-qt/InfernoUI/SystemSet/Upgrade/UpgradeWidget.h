#ifndef UPGRADEWIDGET_H
#define UPGRADEWIDGET_H

#include <QWidget>
#include "BusinessData/InterfaceLib/KeyBoardLib.h"
namespace Ui {
class UpgradeWidget;
}

class UpgradeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UpgradeWidget(QWidget *parent = 0);
    ~UpgradeWidget();

protected:
    bool eventFilter(QObject *watched, QEvent *event);

private slots:
    void on_btnUpdate_clicked();

    void on_radioButtonUDisk_clicked();

    void on_radioButtonServer_clicked();

private:
    Ui::UpgradeWidget *ui;
    KeyBoardLib m_KeyBoardLib;
};

#endif // UPGRADEWIDGET_H
