#include <QDebug>
#include "SyntheticJudgment.h"
#include "ui_SyntheticJudgment.h"
#include "QMessageBox"
#include "TaskHeaderGlobal.h"
#include "TaskStepGlobal.h"

SyntheticJudgment::SyntheticJudgment(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SyntheticJudgment)
{
    ui->setupUi(this);
    //dataModel = DataModel::GetInstance();


    ui->groupBox->setVisible(false);
    ui->groupBox_2->setVisible(false);
    ui->groupBox_Finish->setVisible(false);
    ui->checkBox_NGReset->setChecked(true);
    ui->radioButton_Finish1->setVisible(false);
    ui->radioButton_NG1->setVisible(false);
    ui->radioButton_OK1->setVisible(false);

    ui->tableWidget_TaskList->setSelectionMode(QAbstractItemView::NoSelection);
    ui->tableWidget_TaskList->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

SyntheticJudgment::~SyntheticJudgment()
{
    delete ui;
}

/**
 * @brief SyntheticJudgment::on_btnOK_clicked
 * @note 确定按钮响应函数
 */
void SyntheticJudgment::on_btnOK_clicked()
{
    int i = 0;
    int ok_flag;
    int ng_flag;
    int finish_flag;
    for(i = 0; i < ui->tableWidget_TaskList->rowCount(); i++)
    {
        QCheckBox *checkBox = static_cast<QCheckBox *>(ui->tableWidget_TaskList->cellWidget(i, 0));
        if(checkBox->isChecked())
        {
            Task_Step_Synthetic_Judge_Flag_Set(i+1,1);
        }else
        {
            Task_Step_Synthetic_Judge_Flag_Set(i+1,0);
        }
    }
    if(ui->checkBox_OKEnable->isChecked())
    {
        ok_flag = 1;
        if(ui->radioButton_OKIO1->isChecked())
            SetSyntheticJudgementOkIo(1);
        else if(ui->radioButton_OKIO2->isChecked())
            SetSyntheticJudgementOkIo(2);
        else if(ui->radioButton_OKIO3->isChecked())
            SetSyntheticJudgementOkIo(4);
        else if(ui->radioButton_OKIO4->isChecked())
            SetSyntheticJudgementOkIo(8);
    }
    else
    {
        ok_flag = 0;
        SetSyntheticJudgementOkIo(0);
    }
    if(ui->checkBox_NGEnable->isChecked())
    {
        ng_flag = 2;
        if(ui->radioButton_NGIO1->isChecked())
            SetSyntheticJudgementNgIo(1);
        else if(ui->radioButton_NGIO2->isChecked())
            SetSyntheticJudgementNgIo(2);
        else if(ui->radioButton_NGIO3->isChecked())
            SetSyntheticJudgementNgIo(4);
        else if(ui->radioButton_NGIO4->isChecked())
            SetSyntheticJudgementNgIo(8);
    }
    else
    {
        ng_flag = 0;
        SetSyntheticJudgementNgIo(0);
    }

    if(ui->checkBox_FinishEnable->isChecked())
    {
        finish_flag = 4;
        if(ui->radioButton_FinishIO1->isChecked())
            SetTaskRoundOverIoIndex(1);
        else if(ui->radioButton_FinishIO2->isChecked())
            SetTaskRoundOverIoIndex(2);
        else if(ui->radioButton_FinishIO3->isChecked())
            SetTaskRoundOverIoIndex(4);
        else if(ui->radioButton_FinishIO4->isChecked())
            SetTaskRoundOverIoIndex(8);
    }
    else
    {
        finish_flag = 0;
        SetTaskRoundOverIoIndex(0);
    }
    SetSyntheticJudgementIoStatus(ok_flag|ng_flag|finish_flag);
    if(ui->checkBox_ColligateNGReset->isChecked())
    {
        SetSynthJudgeNgResetFlag(1);
    }
    else
    {
        SetSynthJudgeNgResetFlag(0);
    }

    if(ui->checkBox_NGReset->isChecked())
    {
        SetNgResetFlag(1);
    }
    else
    {
        SetNgResetFlag(0);
    }

    QDialog::accept();

//    m_SynJudgData->SynJudgFinish();
//    m_p_object->TaskEditEnd();
    //    this->close();
}

void SyntheticJudgment::InitList(QStringList task_list)
{
    TaskList = task_list;
    AddItemToTableTaskList(TaskList.count());
    //获取任务数
    unsigned int count = GetTaskStepCount();
    for(unsigned int i = 0; i < count; i++)
    {
        unsigned int flag;
        Task_Step_Synthetic_Judge_Flag_Get(i+1,&flag);
        if(flag)
        {
            QCheckBox *checkBox = static_cast<QCheckBox *>(ui->tableWidget_TaskList->cellWidget(i, 0));
            checkBox->setChecked(true);
        }
    }

    //获取OK时的IO输出（0:无输出 1:IO1 2:IO2 4:IO3 8:IO4）
    unsigned int ok = GetSyntheticJudgementOkIo();
    if(ok != 0){
        ui->checkBox_OKEnable->setChecked(true);
        ui->groupBox->setVisible(true);
        if(ok == 1){
            ui->radioButton_OKIO1->setChecked(true);
        }else if(ok == 2){
            ui->radioButton_OKIO2->setChecked(true);
        }else if(ok == 4){
            ui->radioButton_OKIO3->setChecked(true);
        }else{
            ui->radioButton_OKIO4->setChecked(true);
        }
    }else{
        ui->checkBox_OKEnable->setChecked(false);
        ui->groupBox->setVisible(false);
    }
    //获取NG时的IO输出（0:无输出 1:IO1 2:IO2 4:IO3 8:IO4）
    unsigned int ng = GetSyntheticJudgementNgIo();
    if(ng != 0){
        ui->groupBox_2->setVisible(true);
        ui->checkBox_NGEnable->setChecked(true);
        if(ng == 1){
            ui->radioButton_NGIO1->setChecked(true);
        }else if(ng == 2){
            ui->radioButton_NGIO2->setChecked(true);
        }else if(ng == 4){
            ui->radioButton_NGIO3->setChecked(true);
        }else{
            ui->radioButton_NGIO4->setChecked(true);
        }
    }else{
        ui->checkBox_NGEnable->setChecked(false);
        ui->groupBox_2->setVisible(false);
    }

    unsigned int finish = GetTaskRoundOverIoIndex();
    if(finish != 0){
        ui->groupBox_Finish->setVisible(true);
        ui->checkBox_FinishEnable->setChecked(true);
        if(finish == 1){
            ui->radioButton_FinishIO1->setChecked(true);
        }else if(finish == 2){
            ui->radioButton_FinishIO2->setChecked(true);
        }else if(finish == 4){
            ui->radioButton_FinishIO3->setChecked(true);
        }else{
            ui->radioButton_FinishIO4->setChecked(true);
        }
    }else{
        ui->checkBox_FinishEnable->setChecked(false);
        ui->groupBox_Finish->setVisible(false);
    }

    int flag = GetSynthJudgeNgResetFlag();
    if(flag == 1)
        ui->checkBox_ColligateNGReset->setChecked(true);
    else
        ui->checkBox_ColligateNGReset->setChecked(false);

    flag = GetNgResetFlag();
    if(flag == 1)
        ui->checkBox_NGReset->setChecked(true);
    else
        ui->checkBox_NGReset->setChecked(false);

}

/**
 * @brief SyntheticJudgment::AddItemToTableTaskList
 * @param Rows
 * @note 列表添加项
 */
void SyntheticJudgment::AddItemToTableTaskList(int Rows)
{
    //iValid_points = Rows;
    ui->tableWidget_TaskList->setRowCount(Rows);
    ui->tableWidget_TaskList->setColumnCount(2);
    QStringList header;
    header<<" "<<tr("任务");   //表头
    ui->tableWidget_TaskList->setHorizontalHeaderLabels(header);
    ui->tableWidget_TaskList->setColumnWidth(0,50);
    ui->tableWidget_TaskList->setColumnWidth(1,380);
    ui->tableWidget_TaskList->verticalHeader()->setVisible(false);
    int i = 0;
    for(i = 0; i < ui->tableWidget_TaskList->rowCount(); i++)
    {
        QCheckBox *checkbox = new QCheckBox();
        checkbox->setText(tr("    "));
        //checkbox->setLayoutDirection(Qt::RightToLeft);
        checkbox->setStyleSheet("margin-left:20px");
        ui->tableWidget_TaskList->setCellWidget(i,0,checkbox);
        ui->tableWidget_TaskList->setItem(i, 1, new QTableWidgetItem(TaskList.at(i)));
    }
}

/**
 * @brief SyntheticJudgment::on_checkBox_SelectAll_clicked
 * @param checked
 * @note 全选按钮响应函数
 */
void SyntheticJudgment::on_checkBox_SelectAll_clicked(bool checked)
{
    for(int i = 0; i < ui->tableWidget_TaskList->rowCount(); i++)
    {
        QCheckBox *checkBox = static_cast<QCheckBox *>(ui->tableWidget_TaskList->cellWidget(i, 0));
        checkBox->setChecked(checked);
    }

    if(ui->checkBox_SelectAll->isChecked())
    {
        for(int i = 0; i < ui->tableWidget_TaskList->rowCount(); i++)
        {
            QCheckBox *checkBox = static_cast<QCheckBox *>(ui->tableWidget_TaskList->cellWidget(i, 0));
            checkBox->setChecked(checked);
        }
        ui->checkBox_SelectAll->setText(tr("全不选"));
    }else
    {
        for(int i = 0; i < ui->tableWidget_TaskList->rowCount(); i++)
        {
            QCheckBox *checkBox = static_cast<QCheckBox *>(ui->tableWidget_TaskList->cellWidget(i, 0));
            checkBox->setChecked(checked);
        }
        ui->checkBox_SelectAll->setText(tr("全选"));
    }
}

/**
 * @brief SyntheticJudgment::on_checkBox_OKEnable_toggled
 * @param checked
 * @note OG IO使能响应函数
 */
void SyntheticJudgment::on_checkBox_OKEnable_toggled(bool checked)
{
    ui->groupBox->setVisible(checked);
    ui->radioButton_OKIO1->setChecked(false);
    ui->radioButton_OKIO2->setChecked(false);
    ui->radioButton_OKIO3->setChecked(false);
    ui->radioButton_OKIO4->setChecked(false);
    if(!checked)
        ui->radioButton_OK1->setChecked(true);
    else
    {
        if(!ui->radioButton_NGIO1->isChecked() && !ui->radioButton_FinishIO1->isChecked())
        {
            ui->radioButton_OKIO1->setChecked(true);
            return;
        }
        if(!ui->radioButton_NGIO2->isChecked() && !ui->radioButton_FinishIO2->isChecked())
        {
            ui->radioButton_OKIO2->setChecked(true);
            return;
        }
        if(!ui->radioButton_NGIO3->isChecked() && !ui->radioButton_FinishIO1->isChecked())
        {
            ui->radioButton_OKIO3->setChecked(true);
            return;
        }
        if(!ui->radioButton_NGIO4->isChecked() && !ui->radioButton_FinishIO4->isChecked())
        {
            ui->radioButton_OKIO4->setChecked(true);
            return;
        }
    }
}

/**
 * @brief SyntheticJudgment::on_checkBox_NGEnable_toggled
 * @param checked
 * @note NG IO使能响应函数
 */
void SyntheticJudgment::on_checkBox_NGEnable_toggled(bool checked)
{
    ui->groupBox_2->setVisible(checked);
    ui->radioButton_NGIO1->setChecked(false);
    ui->radioButton_NGIO2->setChecked(false);
    ui->radioButton_NGIO3->setChecked(false);
    ui->radioButton_NGIO4->setChecked(false);
    if(!checked)
        ui->radioButton_NG1->setChecked(true);
    else
    {
        if(!ui->radioButton_OKIO1->isChecked() && !ui->radioButton_FinishIO1->isChecked())
        {
            ui->radioButton_NGIO1->setChecked(true);
            return;
        }
        if(!ui->radioButton_OKIO2->isChecked() && !ui->radioButton_FinishIO2->isChecked())
        {
            ui->radioButton_NGIO2->setChecked(true);
            return;
        }
        if(!ui->radioButton_OKIO3->isChecked() && !ui->radioButton_FinishIO3->isChecked())
        {
            ui->radioButton_NGIO3->setChecked(true);
            return;
        }
        if(!ui->radioButton_OKIO4->isChecked() && !ui->radioButton_FinishIO4->isChecked())
        {
            ui->radioButton_NGIO4->setChecked(true);
            return;
        }
    }

}
/**
 * @brief SyntheticJudgment::on_radioButton_OKIO1_toggled
 * @param checked
 * @note OK IO1单选按钮响应函数
 */
void SyntheticJudgment::on_radioButton_OKIO1_clicked(bool checked)
{
    if(ui->radioButton_NGIO1->isChecked() || ui->radioButton_FinishIO1->isChecked())
    {
        QMessageBox::about(this,tr("提示"),tr("该IO口已经被占用,请选择其他IO口"));
        ui->radioButton_OKIO1->setChecked(false);
        ui->radioButton_OK1->setChecked(true);
        return;
    }
}

/**
 * @brief SyntheticJudgment::on_radioButton_OKIO2_toggled
 * @param checked
 * @note OK IO2单选按钮响应函数
 */
void SyntheticJudgment::on_radioButton_OKIO2_clicked(bool checked)
{
    if(ui->radioButton_NGIO2->isChecked() || ui->radioButton_FinishIO2->isChecked())
    {
        QMessageBox::about(this,tr("提示"),tr("该IO口已经被占用,请选择其他IO口"));
        ui->radioButton_OKIO2->setChecked(false);
        ui->radioButton_OK1->setChecked(true);
        return;
    }
}

/**
 * @brief SyntheticJudgment::on_radioButton_OKIO3_toggled
 * @param checked
 * @note OK IO3单选按钮响应函数
 */
void SyntheticJudgment::on_radioButton_OKIO3_clicked(bool checked)
{
    if(ui->radioButton_NGIO3->isChecked() || ui->radioButton_FinishIO3->isChecked())
    {
        QMessageBox::about(this,tr("提示"),tr("该IO口已经被占用,请选择其他IO口"));
        ui->radioButton_OKIO3->setChecked(false);
        ui->radioButton_OK1->setChecked(true);
        return;
    }
}

/**
 * @brief SyntheticJudgment::on_radioButton_OKIO4_toggled
 * @param checked
 * @note OK IO4单选按钮响应函数
 */
void SyntheticJudgment::on_radioButton_OKIO4_clicked(bool checked)
{
    if(ui->radioButton_NGIO4->isChecked() || ui->radioButton_FinishIO4->isChecked())
    {
        QMessageBox::about(this,tr("提示"),tr("该IO口已经被占用,请选择其他IO口"));
        ui->radioButton_OKIO4->setChecked(false);
        ui->radioButton_OK1->setChecked(true);
        return;
    }
}

/**
 * @brief SyntheticJudgment::on_radioButton_NGIO1_toggled
 * @param checked
 * @note NG IO1单选按钮响应函数
 */
void SyntheticJudgment::on_radioButton_NGIO1_clicked(bool checked)
{
    if(ui->radioButton_OKIO1->isChecked() || ui->radioButton_FinishIO1->isChecked())
    {
        QMessageBox::about(this,tr("提示"),tr("该IO口已经被占用,请选择其他IO口"));
        ui->radioButton_NGIO1->setChecked(false);
        ui->radioButton_NG1->setChecked(true);
        return;
    }
}

/**
 * @brief SyntheticJudgment::on_radioButton_NGIO2_toggled
 * @param checked
 * @note NG IO2单选按钮响应函数
 */
void SyntheticJudgment::on_radioButton_NGIO2_clicked(bool checked)
{
    if(ui->radioButton_OKIO2->isChecked() || ui->radioButton_FinishIO2->isChecked())
    {
        QMessageBox::about(this,tr("提示"),tr("该IO口已经被占用,请选择其他IO口"));
        ui->radioButton_NGIO2->setChecked(false);
        ui->radioButton_NG1->setChecked(true);
        return;
    }
}

/**
 * @brief SyntheticJudgment::on_radioButton_NGIO3_toggled
 * @param checked
 * @note NG IO3单选按钮响应函数
 */
void SyntheticJudgment::on_radioButton_NGIO3_clicked(bool checked)
{
    if(ui->radioButton_OKIO3->isChecked() || ui->radioButton_FinishIO3->isChecked())
    {
        QMessageBox::about(this,tr("提示"),tr("该IO口已经被占用,请选择其他IO口"));
        ui->radioButton_NGIO3->setChecked(false);
        ui->radioButton_NG1->setChecked(true);
        return;
    }
}

/**
 * @brief SyntheticJudgment::on_radioButton_NGIO4_toggled
 * @param checked
 * @note NG IO4单选按钮响应函数
 */
void SyntheticJudgment::on_radioButton_NGIO4_clicked(bool checked)
{
    if(ui->radioButton_OKIO4->isChecked() || ui->radioButton_FinishIO4->isChecked())
    {
        QMessageBox::about(this,tr("提示"),tr("该IO口已经被占用,请选择其他IO口"));
        ui->radioButton_NGIO4->setChecked(false);
        ui->radioButton_NG1->setChecked(true);
        return;
    }
}

void SyntheticJudgment::on_checkBox_FinishEnable_toggled(bool checked)
{
    ui->groupBox_Finish->setVisible(checked);
    ui->radioButton_FinishIO1->setChecked(false);
    ui->radioButton_FinishIO2->setChecked(false);
    ui->radioButton_FinishIO3->setChecked(false);
    ui->radioButton_FinishIO4->setChecked(false);

    if(!checked)
        ui->radioButton_Finish1->setChecked(true);
    else
    {
        if(!ui->radioButton_NGIO1->isChecked() && !ui->radioButton_OKIO1->isChecked())
        {
            ui->radioButton_FinishIO1->setChecked(true);
            return;
        }
        if(!ui->radioButton_NGIO2->isChecked() && !ui->radioButton_OKIO2->isChecked())
        {
            ui->radioButton_FinishIO2->setChecked(true);
            return;
        }
        if(!ui->radioButton_NGIO3->isChecked() && !ui->radioButton_OKIO3->isChecked())
        {
            ui->radioButton_FinishIO3->setChecked(true);
            return;
        }
        if(!ui->radioButton_NGIO4->isChecked() && !ui->radioButton_OKIO4->isChecked())
        {
            ui->radioButton_FinishIO4->setChecked(true);
            return;
        }
    }

}

void SyntheticJudgment::on_radioButton_FinishIO1_clicked(bool checked)
{
    if(ui->radioButton_OKIO1->isChecked() || ui->radioButton_NGIO1->isChecked())
    {
        QMessageBox::about(this,tr("提示"),tr("该IO口已经被占用,请选择其他IO口"));
        ui->radioButton_FinishIO1->setChecked(false);
        ui->radioButton_Finish1->setChecked(true);
        return;
    }

}

void SyntheticJudgment::on_radioButton_FinishIO2_clicked(bool checked)
{
    if(ui->radioButton_OKIO2->isChecked() || ui->radioButton_NGIO2->isChecked())
    {
        QMessageBox::about(this,tr("提示"),tr("该IO口已经被占用,请选择其他IO口"));
        ui->radioButton_FinishIO2->setChecked(false);
        ui->radioButton_Finish1->setChecked(true);
        return;
    }
}

void SyntheticJudgment::on_radioButton_FinishIO3_clicked(bool checked)
{
    if(ui->radioButton_OKIO3->isChecked() || ui->radioButton_NGIO3->isChecked())
    {
        QMessageBox::about(this,tr("提示"),tr("该IO口已经被占用,请选择其他IO口"));
        ui->radioButton_FinishIO3->setChecked(false);
        ui->radioButton_Finish1->setChecked(true);
        return;
    }
}

void SyntheticJudgment::on_radioButton_FinishIO4_clicked(bool checked)
{
    if(ui->radioButton_OKIO4->isChecked() || ui->radioButton_NGIO4->isChecked())
    {
        QMessageBox::about(this,tr("提示"),tr("该IO口已经被占用,请选择其他IO口"));
        ui->radioButton_FinishIO4->setChecked(false);
        ui->radioButton_Finish1->setChecked(true);
        return;
    }
}

void SyntheticJudgment::on_btnQuit_clicked()
{
    QDialog::reject();
}

void SyntheticJudgment::on_tableWidget_TaskList_cellClicked(int row, int column)
{

    QCheckBox *checkBox = static_cast<QCheckBox *>(ui->tableWidget_TaskList->cellWidget(row, 0));
    if(checkBox->isChecked())
    {
        checkBox->setChecked(false);
        ui->checkBox_SelectAll->setChecked(false);
        ui->checkBox_SelectAll->setText(tr("全选"));

    }
    else
    {
        checkBox->setChecked(true);

        int cnt= 0;
        for(int i = 0; i < ui->tableWidget_TaskList->rowCount(); i++)
        {
            QCheckBox *checkBox = static_cast<QCheckBox *>(ui->tableWidget_TaskList->cellWidget(i, 0));
            if(checkBox->isChecked())
                cnt++;
        }
        if(cnt == ui->tableWidget_TaskList->rowCount())
        {
            ui->checkBox_SelectAll->setChecked(true);
            ui->checkBox_SelectAll->setText(tr("全不选"));
        }
    }
}
