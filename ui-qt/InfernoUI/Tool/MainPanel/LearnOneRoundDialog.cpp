#include "LearnOneRoundDialog.h"
#include "ui_LearnOneRoundDialog.h"
#include "stdbool.h"
#include "QMessageBox"
#include "TaskStepGlobal.h"
#include "TaskManageGlobal.h"

LearnOneRoundDialog::LearnOneRoundDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LearnOneRoundDialog)
{
    ui->setupUi(this);
    connect(&UpdataDataTimer,&QTimer::timeout,this,&LearnOneRoundDialog::UpdataDataSlot);
    ui->btnQuite->setEnabled(false);
    UpdataDataTimer.start(10);
}

LearnOneRoundDialog::~LearnOneRoundDialog()
{
    delete ui;
}

void LearnOneRoundDialog::on_btnQuite_clicked()
{
    QDialog::accept();
}

void LearnOneRoundDialog::InitUISlot(QStringList task_list)
{
    int i = 0;
    ui->tableWidget->setRowCount(task_list.count());
    for(i = 0; i < ui->tableWidget->rowCount();i++)
    {
        ui->tableWidget->setItem(i,0, new QTableWidgetItem(task_list[i]));
    }
}


void LearnOneRoundDialog::UpdataDataSlot()
{
    for(int i = 0; i < ui->tableWidget->rowCount();i++)
    {
        int ret = TaskStepLearnProc(i+1);

        if(ret == 0)
        {
            Task_Step_Model_Result_Valid_Flag_Set(i+1);
            ui->tableWidget->setItem(i,1,new QTableWidgetItem("OK"));
        }
        else
        {
            ui->tableWidget->setItem(i,1,new QTableWidgetItem(QString::number(ret,16)));
        }
    }
    ui->btnQuite->setEnabled(true);
    UpdataDataTimer.stop();
}

