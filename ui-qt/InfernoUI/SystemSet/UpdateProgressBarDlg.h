#ifndef UPDATEPROGRESSBARDLG_H
#define UPDATEPROGRESSBARDLG_H

#include <QDialog>

namespace Ui {
class UpdateProgressBarDlg;
}

class UpdateProgressBarDlg : public QDialog
{
    Q_OBJECT

public:
    explicit UpdateProgressBarDlg(QWidget *parent = 0);
    ~UpdateProgressBarDlg();

    void SetProgress(int process);
    void taskPortSetProgress(int process);
private slots:
    void on_btnOk_clicked();

private:
    Ui::UpdateProgressBarDlg *ui;
};

#endif // UPDATEPROGRESSBARDLG_H
