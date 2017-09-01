#ifndef ADDTOOLFILES_H
#define ADDTOOLFILES_H

#include <QWidget>
#include <QTimer>
#include "../UpdateProgressBarDlg.h"
#include "BusinessData/InterfaceLib/KeyBoardLib.h"

namespace Ui {
class AddToolFiles;
}

class AddToolFiles : public QWidget
{
    Q_OBJECT

public:
    explicit AddToolFiles(QWidget *parent = 0);
    ~AddToolFiles();

protected:
    bool eventFilter(QObject *watched, QEvent *event);

private slots:
    void on_btnImport_clicked();

    void UpdateTimerSlot();

private:
    Ui::AddToolFiles *ui;
    KeyBoardLib m_KeyBoardLib;
    QTimer *updateTimer;
    UpdateProgressBarDlg *m_UpdateProgressBarDlg;
};

#endif // ADDTOOLFILES_H
