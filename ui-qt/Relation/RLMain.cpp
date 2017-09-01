#include <QDebug>
#include "RLMain.h"
#include "ui_RLMain.h"
#include <QMessageBox>
#include "CommonDataSelect/CommonDataSelectDialog.h"
#include "PublicLinkData.h"
#include "stdio.h"

RLMain::RLMain(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RLMain)
{
    ui->setupUi(this);
    ui->groupBox_4->setEnabled(false);
    m_keyBoard.LoadKeyBoardLib();
    ui->radioButton_X_Null->setChecked(true);
    ui->radioButton_Y_Null->setChecked(true);
    ui->radioButton_A_Null->setChecked(true);
    ui->lineEdit_Angle->installEventFilter(this);
    ui->lineEdit_X->installEventFilter(this);
    ui->lineEdit_Y->installEventFilter(this);
    m_i_CurrentStep = 2;
}

RLMain::~RLMain()
{
    ui->lineEdit_Angle->removeEventFilter(this);
    ui->lineEdit_X->removeEventFilter(this);
    ui->lineEdit_Y->removeEventFilter(this);
    delete ui;
}
void RLMain::SetCurrentStepIndex(int index)
{
    m_i_CurrentStep = index;
    InitTaskEdit();
}

void RLMain::SelectDataSlot(int v)
{
    CommonDataSelectDialog *dlg = new CommonDataSelectDialog();
    dlg->InitTaskList(v,m_i_CurrentStep);
    int ret = dlg->exec();
    if(ret == QDialog::Accepted)
    {
        QString list = dlg->GetDataList();
        if(0 == v)
        {
            m_X_Ref = list;
            ui->lineEdit_X->setText(list);
        }
        if(1 == v)
        {
            m_Y_Ref = list;
            ui->lineEdit_Y->setText(list);
        }
        if(2 == v)
        {
            m_A_Ref = list;
            ui->lineEdit_Angle->setText(list);
        }
    }
    else
    {
        if(0 == v && ui->lineEdit_X->text().isEmpty())
            ui->radioButton_X_Null->setChecked(true);
        if(1 == v && ui->lineEdit_Y->text().isEmpty())
            ui->radioButton_Y_Null->setChecked(true);
        if(2 == v && ui->lineEdit_Angle->text().isEmpty())
            ui->radioButton_A_Null->setChecked(true);
    }
    if(dlg !=NULL)
     {
         delete dlg;
         dlg = NULL;
     }

}



void RLMain::on_RelateLocationCheckBox_clicked()
{
    if(!ui->RelateLocationCheckBox->isChecked())
        ui->groupBox_4->setEnabled(false);
    else
        ui->groupBox_4->setEnabled(true);
}

void RLMain::InitTaskEdit()
{
    //初始化关联定位控件显示
    int ret = PublicLinkData::GetPublicLinkInstance()->PublicLinkDataInit(m_i_CurrentStep);
    if(ret == -1)
    {
        QMessageBox::warning(NULL, tr("Warning"), tr("初始化关联定位数据失败！"), QMessageBox::Yes);
        return;
    }
    //关联定位不使能
    if(PublicLinkData::GetPublicLinkInstance()->GetLinkDataEnableFlag() == 0)
    {
        ui->RelateLocationCheckBox->setChecked(false);
        ui->groupBox_4->setEnabled(false);
    }
    //关联定位使能
    else
    {
        ui->RelateLocationCheckBox->setChecked(true);
        ui->groupBox_4->setEnabled(true);
        int type;
        int task_index;
        int result_index;
        QString task_str;
        QString result_str;
        // X数据
        type = PublicLinkData::GetPublicLinkInstance()->GetLinkDataType(0);

        //ui->comboBox_X->setCurrentIndex(type);
        if(type == COMPASS_MANUAL)
        {
            ui->radioButton_X_Manual->setChecked(true);
            m_X_Manual = QString::number(PublicLinkData::GetPublicLinkInstance()->GetLinkDataValue(0));
            ui->lineEdit_X->setText(m_X_Manual);
        }
        else if(type == COMPASS_REF_VALUE)
        {
            task_index = PublicLinkData::GetPublicLinkInstance()->GetLinkDataStep(0);
            if(task_index == 0)
            {
                //ui->comboBox_X->setCurrentIndex(0);
                ui->radioButton_X_Null->setChecked(true);
                return;
            }
            ui->radioButton_X_Link->setChecked(true);
            result_index = PublicLinkData::GetPublicLinkInstance()->GetLinkDataResult(0);
            task_str = PublicLinkData::GetPublicLinkInstance()->GetLinkDataPointTaskStr(task_index);
            QStringList list = PublicLinkData::GetPublicLinkInstance()->GetLinkDataXResultStr(task_index);
            if(list.count()>result_index)
                result_str = list[result_index];
            m_X_Ref = QString::number(task_index)+"."+task_str + ";"+QString::number(result_index+1)+"."+result_str;
            ui->lineEdit_X->setText(m_X_Ref);
        }
        else
        {
            ui->radioButton_X_Null->setChecked(true);
        }
        // Y数据
        type = PublicLinkData::GetPublicLinkInstance()->GetLinkDataType(1);
//        ui->comboBox_Y->setCurrentIndex(type);
        if(type == COMPASS_MANUAL)
        {
            ui->radioButton_Y_Manual->setChecked(true);
            m_Y_Manual = QString::number(PublicLinkData::GetPublicLinkInstance()->GetLinkDataValue(1));
            ui->lineEdit_Y->setText(m_Y_Manual);
        }
        else if(type == COMPASS_REF_VALUE)
        {
            task_index = PublicLinkData::GetPublicLinkInstance()->GetLinkDataStep(1);
            if(task_index == 0)
            {
//                ui->comboBox_Y->setCurrentIndex(0);
                ui->radioButton_Y_Null->setChecked(true);
                return;
            }
            ui->radioButton_Y_Link->setChecked(true);
            result_index = PublicLinkData::GetPublicLinkInstance()->GetLinkDataResult(1);
            task_str = PublicLinkData::GetPublicLinkInstance()->GetLinkDataPointTaskStr(task_index);
            QStringList list = PublicLinkData::GetPublicLinkInstance()->GetLinkDataYResultStr(task_index);
            if(list.count()>result_index)
                result_str = list[result_index];
            m_Y_Ref = QString::number(task_index)+"."+task_str + ";"+QString::number(result_index+1)+"."+result_str;
            ui->lineEdit_Y->setText(m_Y_Ref);
        }
        else
        {
            ui->radioButton_Y_Null->setChecked(true);
        }
        //角度数据
        type = PublicLinkData::GetPublicLinkInstance()->GetLinkDataType(2);
//        ui->comboBox_Angle->setCurrentIndex(PublicLinkData::GetPublicLinkInstance()->GetLinkDataType(2));

        if(type == COMPASS_MANUAL)
        {
            ui->radioButton_A_Manual->setChecked(true);
            m_A_Manual = QString::number(PublicLinkData::GetPublicLinkInstance()->GetLinkDataValue(2));
            ui->lineEdit_Angle->setText(m_A_Manual);
        }
        else if(type == COMPASS_REF_VALUE)
        {
            task_index = PublicLinkData::GetPublicLinkInstance()->GetLinkDataStep(2);
            if(task_index == 0)
            {
//                ui->comboBox_Angle->setCurrentIndex(0);
                ui->radioButton_A_Null->setChecked(true);
                return;
            }
            ui->radioButton_A_Link->setChecked(true);
            result_index = PublicLinkData::GetPublicLinkInstance()->GetLinkDataResult(2);
            task_str = PublicLinkData::GetPublicLinkInstance()->GetLinkDataAngleString(task_index);
            QStringList list = PublicLinkData::GetPublicLinkInstance()->GetLinkDataAngleStr(task_index);
            if(list.count()>result_index)
                result_str = list[result_index];
            m_A_Ref = QString::number(task_index)+"."+task_str + ";"+QString::number(result_index+1)+"."+result_str;
            ui->lineEdit_Angle->setText(m_A_Ref);
        }
        else
        {
            ui->radioButton_A_Null->setChecked(true);
        }

    }
}


int RLMain::SetRelateLocationData()
{
    if(ui->RelateLocationCheckBox->isChecked())
    {
        PublicLinkData::GetPublicLinkInstance()->SetLinkDataEnableFlag(1);
        bool ok = true;
        double data_input;
        //设置X
        if(ui->radioButton_X_Null->isChecked())
        {

            PublicLinkData::GetPublicLinkInstance()->SetLinkDataType(0,COMPASS_NULL);
        }
        else if(ui->radioButton_X_Manual->isChecked())
        {
            PublicLinkData::GetPublicLinkInstance()->SetLinkDataType(0,COMPASS_MANUAL);
            data_input = ui->lineEdit_X->text().toDouble();
            if(ok)
                PublicLinkData::GetPublicLinkInstance()->GetLinkDataValue(0,data_input);
            else
            {
                QMessageBox::warning(NULL, tr("Warning"), tr("请输入正确的X坐标值!"), QMessageBox::Yes);
                return -1;
            }
        }
        else if(ui->radioButton_X_Link->isChecked())
        {
            PublicLinkData::GetPublicLinkInstance()->SetLinkDataType(0,COMPASS_REF_VALUE);
            QStringList list = ui->lineEdit_X->text().split(";");
            if(list.count() == 2)
            {
                int task_index = list[0].split(".")[0].toInt();
                int result_index = list[1].split(".")[0].toInt();
                PublicLinkData::GetPublicLinkInstance()->SetLinkDataStep(0,task_index);
                PublicLinkData::GetPublicLinkInstance()->SetLinkDataResult(0,result_index);
            }
        }

        //设置Y
        if(ui->radioButton_Y_Null->isChecked())
        {
            PublicLinkData::GetPublicLinkInstance()->SetLinkDataType(1,COMPASS_NULL);
        }
        else if(ui->radioButton_Y_Manual->isChecked())
        {
            PublicLinkData::GetPublicLinkInstance()->SetLinkDataType(1,COMPASS_MANUAL);
            data_input = ui->lineEdit_Y->text().toDouble();
            if(ok)
                PublicLinkData::GetPublicLinkInstance()->GetLinkDataValue(1,data_input);
            else
            {
                QMessageBox::warning(NULL, tr("Warning"), tr("请输入正确的Y坐标值!"), QMessageBox::Yes);
                return -1;
            }
        }
        else if(ui->radioButton_Y_Link->isChecked())
        {
            PublicLinkData::GetPublicLinkInstance()->SetLinkDataType(1,COMPASS_REF_VALUE);
            QStringList list = ui->lineEdit_Y->text().split(";");
            if(list.count() == 2)
            {
                int task_index = list[0].split(".")[0].toInt();
                int result_index = list[1].split(".")[0].toInt();
                PublicLinkData::GetPublicLinkInstance()->SetLinkDataStep(1,task_index);
                PublicLinkData::GetPublicLinkInstance()->SetLinkDataResult(1,result_index);
            }
        }

        //设置角度
        if(ui->radioButton_A_Null->isChecked())
        {
            PublicLinkData::GetPublicLinkInstance()->SetLinkDataType(2,COMPASS_NULL);
        }
        else if(ui->radioButton_A_Manual->isChecked())
        {
            PublicLinkData::GetPublicLinkInstance()->SetLinkDataType(2,COMPASS_MANUAL);
            data_input = ui->lineEdit_Angle->text().toDouble();
            if(ok)
                PublicLinkData::GetPublicLinkInstance()->GetLinkDataValue(2,data_input);
            else
            {
                QMessageBox::warning(NULL, tr("Waring"), tr("请输入正确的角度值!"), QMessageBox::Yes);
                return -1;
            }
        }

        else if(ui->radioButton_A_Link->isChecked())
        {
            PublicLinkData::GetPublicLinkInstance()->SetLinkDataType(2,COMPASS_REF_VALUE);
            QStringList list = ui->lineEdit_Angle->text().split(";");
            if(list.count() == 2)
            {
                int task_index = list[0].split(".")[0].toInt();
                int result_index = list[1].split(".")[0].toInt();
                PublicLinkData::GetPublicLinkInstance()->SetLinkDataStep(2,task_index);
                PublicLinkData::GetPublicLinkInstance()->SetLinkDataResult(2,result_index);
            }
        }
    }
    else
    {
        PublicLinkData::GetPublicLinkInstance()->SetLinkDataEnableFlag(0);
    }
    int ret = PublicLinkData::GetPublicLinkInstance()->PublicLinkDataHandleFinish();
    if(ret == -1)
    {
        QMessageBox::warning(NULL, tr("Warning"), tr("设置数据失败！"), QMessageBox::Yes);
        return -1;
    }
    return 0;
}

void RLMain::on_radioButton_X_Null_clicked()
{
    ui->lineEdit_X->clear();
}

void RLMain::on_radioButton_X_Manual_clicked()
{
    ui->lineEdit_X->clear();
    ui->lineEdit_X->setText(m_X_Manual);
}

void RLMain::on_radioButton_X_Link_clicked()
{
    ui->lineEdit_X->clear();
    ui->lineEdit_X->setText(m_X_Ref);
}

void RLMain::on_radioButton_Y_Null_clicked()
{
    ui->lineEdit_Y->clear();
}

void RLMain::on_radioButton_Y_Manual_clicked()
{
    ui->lineEdit_Y->clear();
    ui->lineEdit_Y->setText(m_Y_Manual);
}

void RLMain::on_radioButton_Y_Link_clicked()
{
    ui->lineEdit_Y->clear();
    ui->lineEdit_Y->setText(m_Y_Ref);
}

void RLMain::on_radioButton_A_Null_clicked()
{
    ui->lineEdit_Angle->clear();
}

void RLMain::on_radioButton_A_Manual_clicked()
{
    ui->lineEdit_Angle->clear();
    ui->lineEdit_Angle->setText(m_A_Ref);
}

void RLMain::on_radioButton_A_Link_clicked()
{
    ui->lineEdit_Angle->clear();
    ui->lineEdit_Angle->setText(m_A_Ref);
}

bool RLMain::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui->lineEdit_X)         //首先判断控件(这里指 lineEdit1)
    {
         if (event->type()==QEvent::MouseButtonPress)     //然后再判断控件的具体事件 (这里指点击事件)
         {
             if(ui->radioButton_X_Null->isChecked())
             {
                 return QWidget::eventFilter(watched, event);
             }
             else if(ui->radioButton_X_Manual->isChecked())
             {

                 int ret = m_keyBoard.GetNumDlg()->exec();

                 if(ret == QDialog::Accepted)
                 {
                     m_X_Manual =  m_keyBoard.GetNum();
                     if(m_X_Manual.toInt() > 640 || m_X_Manual.toInt() < 0)
                     {
                         QMessageBox::information(this,tr("提示"),tr("请输入0到640之间的数"));
                         return QWidget::eventFilter(watched, event);
                     }
                     ui->lineEdit_X->setText(m_X_Manual);
                 }
             }
             else
             {
                 SelectDataSlot(PublicLinkData::SELECT_X_DATA);
             }
         }
    }
    if (watched == ui->lineEdit_Y)         //首先判断控件(这里指 lineEdit1)
    {
         if (event->type()==QEvent::MouseButtonPress)     //然后再判断控件的具体事件 (这里指点击事件)
         {
             if(ui->radioButton_Y_Null->isChecked())
             {
                 return QWidget::eventFilter(watched, event);
             }
             else if(ui->radioButton_Y_Manual->isChecked())
             {
                 int ret = m_keyBoard.GetNumDlg()->exec();
                 if(ret == QDialog::Accepted)
                 {
                     m_Y_Manual = m_keyBoard.GetNum();
                     if(m_Y_Manual.toInt() > 480 || m_Y_Manual.toInt() < 0)
                     {
                         QMessageBox::information(this,tr("提示"),tr("请输入0到480之间的数"));
                         return QWidget::eventFilter(watched, event);
                     }
                     ui->lineEdit_Y->setText(m_Y_Manual);
                 }
             }
             else
             {
                 SelectDataSlot(PublicLinkData::SELECT_Y_DATA);
             }
         }
    }
    if (watched == ui->lineEdit_Angle)         //首先判断控件(这里指 lineEdit1)
    {
         if (event->type()==QEvent::MouseButtonPress)     //然后再判断控件的具体事件 (这里指点击事件)
         {
             if(ui->radioButton_A_Null->isChecked())
             {
                 return QWidget::eventFilter(watched, event);
             }
             else if(ui->radioButton_A_Manual->isChecked())
             {
                 int ret = m_keyBoard.GetNumDlg()->exec();
                 if(ret == QDialog::Accepted)
                 {
                     m_A_Manual = m_keyBoard.GetNum();
                     ui->lineEdit_Angle->setText(m_A_Manual);
                 }
             }
             else
             {
                 SelectDataSlot(PublicLinkData::SELECT_ANGLE_DATA);
             }
         }
    }
    return QWidget::eventFilter(watched, event);
}
