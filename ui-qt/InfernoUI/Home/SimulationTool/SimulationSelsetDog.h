#ifndef SIMULATIONSELSETDOG_H
#define SIMULATIONSELSETDOG_H

#include <QDialog>

namespace Ui {
class SimulationSelsetDog;
}

class SimulationSelsetDog : public QDialog
{
    Q_OBJECT

public:
    explicit SimulationSelsetDog(QWidget *parent = 0);
    ~SimulationSelsetDog();
    void SetSimulatDir(QString str);
    QString GetSimulatDir();
private slots:
    void on_btnSelectOk_clicked();

private:
    Ui::SimulationSelsetDog *ui;
    QString m_dir;
};

#endif // SIMULATIONSELSETDOG_H
