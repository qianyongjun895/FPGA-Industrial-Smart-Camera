#ifndef LEARNONEROUNDDIALOG_H
#define LEARNONEROUNDDIALOG_H

#include <QDialog>
#include <QTimer>

namespace Ui {
class LearnOneRoundDialog;
}

class LearnOneRoundDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LearnOneRoundDialog(QWidget *parent = 0);
    ~LearnOneRoundDialog();

    void InitUISlot(QStringList task_list);
private slots:
    void on_btnQuite_clicked();

    void UpdataDataSlot();
private:
    Ui::LearnOneRoundDialog *ui;
    QTimer UpdataDataTimer;
};

#endif // LEARNONEROUNDDIALOG_H
