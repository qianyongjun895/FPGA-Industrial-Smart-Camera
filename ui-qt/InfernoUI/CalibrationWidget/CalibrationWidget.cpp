#include "CalibrationWidget.h"
#include "ui_CalibrationWidget.h"
#include <QMessageBox>
#include <cstring>
#include <QDebug>
#include <QDialog>
#include "Calibration/ScaleCalibration.h"
#include "../Global/UtilitiesFun.h"
#include "Demarcate/MultipointsDemarcate.h"
#include "Comm/ControlStyle.h"
#include "CalibrationParamReference.h"
#include "ScaleRatio.h"
#include "Comm/GlobalParameter.h"
#include "task/TaskGlobal.h"
#include "Comm/CommonRowInput/CommonRowInput.h"
#include <cstdio>
#include "comm_include/HansRobotGlobal.h"
#include "comm_include/CommunicateBase.h"
#include <stdio.h>
#include <stdlib.h>
#include <QLineEdit>
#include "UserDefinedGlobal.h"
#include "ProtocolManageGlobal.h"
#include <QListWidget>
CalibrationWidget::CalibrationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CalibrationWidget)
{
    ui->setupUi(this);
    ui->labelPic->setVisible(false);
    ui->txtID->installEventFilter(this);
    ui->txtAngleStep->installEventFilter(this);
    ui->txtSpaceStep->installEventFilter(this);
    ui->txtID->setText("0");
    ui->txtAngleStep->setText("2.0");
    ui->txtSpaceStep->setText("2.0");
    m_timer = new QTimer;
    connect(m_timer,SIGNAL(timeout()),this,SLOT(TimeOutFun()));
    rowInput = new CommonRowInput;
    m_robot_id = 0;

    ControlStyle::SetTabBar(ui->tabWidget);
    ui->listWidgetParamType->setCurrentRow(0);

    // 从文件加载刻度校准参数到内存中
    ScaleRatioInfoLoadFromFile();
    MultipointDemarcateParamListInit();
    ParamReferencePanelInit();
    CommonRowInput *p = NULL;
    p = static_cast<CommonRowInput *>(rowInput);
    connect(p, &CommonRowInput::SendInputText, this, &CalibrationWidget::RecieveRenameText);
    InitEthernet();
    ui->tabWidget->setCurrentIndex(0);
    ui->stackedWidget->setCurrentIndex(0);
    IniUserDefList();
}

CalibrationWidget::~CalibrationWidget()
{
    ui->txtID->removeEventFilter(this);
    ui->txtAngleStep->removeEventFilter(this);
    ui->txtSpaceStep->removeEventFilter(this);

    ui->lineEdit_IP1->removeEventFilter(this);
    ui->lineEdit_IP2->removeEventFilter(this);
    ui->lineEdit_IP3->removeEventFilter(this);
    ui->lineEdit_IP4->removeEventFilter(this);
    ui->lineEdit_Port->removeEventFilter(this);
    if (rowInput != NULL)
    {
        delete rowInput;
        rowInput = NULL;
    }

    if(m_timer != NULL)
    {
        delete m_timer;
        m_timer = NULL;
    }
    if(Recv_time != NULL){
        delete Recv_time;
        Recv_time = NULL;
    }
    delete ui;
}

void CalibrationWidget::IniUserDefList()
{
    Recv_count = 0;
    Recv_time = new QTimer;
    connect(Recv_time, &QTimer::timeout, this, &CalibrationWidget::ShowRecvData);
    PROTOCOL_SELECT status;
    protocol_select_get(&status);
    if(status.protocol_type == USER_DEFINED_PROTOCOL && status.protocol_status == PROTOCOL_ACTIVE){
        unsigned int count = user_defined_data_cnt_get();
        for(int i = 0; i < count; i++){
            if(user_defined_send_step_get(i) == 0){
                int list_count = ui->listWidget_User_Def_List->count();
                QLabel *label = new QLabel;
                QString str = "";
                if(user_defined_label_enable_get(i) == 1){
                    char label[USER_LABEL_DATA_SIZE];
                    user_defined_label_str_get(i, label);
                    str = "(";
                    str += QString::fromUtf8(label);
                    str += ")";
                }
                label->setText(QString::number(list_count+1)+str);
                QFont font;
                font.setPixelSize(20);
                label->setFont(font);
                QListWidgetItem *Item = new QListWidgetItem(ui->listWidget_User_Def_List);
                ui->listWidget_User_Def_List->setItemWidget(Item, (QWidget*)label);
                ui->listWidget_User_Def_List->item(list_count)->setSizeHint(QSize(200,31));
                User_List_index.insertMulti(list_count, i);
            }
        }
        if(ui->listWidget_User_Def_List->count() == 0){
            ui->pushButton_Manual_send->setEnabled(false);
        }else{
            ui->listWidget_User_Def_List->setCurrentRow(0);
        }
    }else{
        ui->pushButton_Manual_send->setEnabled(false);
    }
}

void CalibrationWidget::SetRobotID(int id)
{
    m_robot_id = id;
}

int CalibrationWidget::GetRobotID()
{
    return m_robot_id;
}

bool CalibrationWidget::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui->txtAngleStep)         //首先判断控件(这里指 lineEdit1)
    {
        if (event->type()==QEvent::MouseButtonPress)     //然后再判断控件的具体事件 (这里指点击事件)
        {
            QDialog *dlg = m_keyBoardLib.GetNumKeyBoardDialog();
            //m_keyBoardLib.SetNum(ui->txtImageName->text());
            int ret = dlg->exec();
            if(ret == QDialog::Accepted)
            {
                ui->txtAngleStep->setText(m_keyBoardLib.GetNum());
            }
        }
    }
    if (watched == ui->txtSpaceStep)         //首先判断控件(这里指 lineEdit1)
    {
        if (event->type()==QEvent::MouseButtonPress)     //然后再判断控件的具体事件 (这里指点击事件)
        {
            QDialog *dlg = m_keyBoardLib.GetNumKeyBoardDialog();
            //m_keyBoardLib.SetNum(ui->txtImageName->text());
            int ret = dlg->exec();
            if(ret == QDialog::Accepted)
            {
                ui->txtSpaceStep->setText(m_keyBoardLib.GetNum());
            }
        }
    }
    if (watched == ui->txtID)         //首先判断控件(这里指 lineEdit1)
    {
        if (event->type()==QEvent::MouseButtonPress)     //然后再判断控件的具体事件 (这里指点击事件)
        {
            QDialog *dlg = m_keyBoardLib.GetNumKeyBoardDialog();
            //m_keyBoardLib.SetNum(ui->txtImageName->text());
            int ret = dlg->exec();
            if(ret == QDialog::Accepted)
            {
                ui->txtID->setText(m_keyBoardLib.GetNum());
            }
        }
    }

    if (watched == ui->lineEdit_Port && ((QLineEdit*)watched)->isEnabled())         //首先判断控件(这里指 lineEdit1)
    {
        if (event->type()==QEvent::MouseButtonPress)     //然后再判断控件的具体事件 (这里指点击事件)
        {
            QDialog *dlg = m_keyBoardLib.GetNumKeyBoardDialog();
            //m_keyBoardLib.SetNum(ui->txtImageName->text());
            int ret = dlg->exec();
            if(ret == QDialog::Accepted)
            {
                ui->lineEdit_Port->setText(m_keyBoardLib.GetNum());
            }
        }
    }
    if (watched == ui->lineEdit_IP1 && ((QLineEdit*)watched)->isEnabled())         //首先判断控件(这里指 lineEdit1)
    {
        if (event->type()==QEvent::MouseButtonPress)     //然后再判断控件的具体事件 (这里指点击事件)
        {
            QDialog *dlg = m_keyBoardLib.GetNumKeyBoardDialog();
            //m_keyBoardLib.SetNum(ui->txtImageName->text());
            int ret = dlg->exec();
            if(ret == QDialog::Accepted)
            {
                ui->lineEdit_IP1->setText(m_keyBoardLib.GetNum());
            }
        }
    }
    if (watched == ui->lineEdit_IP2 && ((QLineEdit*)watched)->isEnabled())         //首先判断控件(这里指 lineEdit1)
    {
        if (event->type()==QEvent::MouseButtonPress)     //然后再判断控件的具体事件 (这里指点击事件)
        {
            QDialog *dlg = m_keyBoardLib.GetNumKeyBoardDialog();
            //m_keyBoardLib.SetNum(ui->txtImageName->text());
            int ret = dlg->exec();
            if(ret == QDialog::Accepted)
            {
                ui->lineEdit_IP2->setText(m_keyBoardLib.GetNum());
            }
        }
    }
    if (watched == ui->lineEdit_IP3 && ((QLineEdit*)watched)->isEnabled())         //首先判断控件(这里指 lineEdit1)
    {
        if (event->type()==QEvent::MouseButtonPress)     //然后再判断控件的具体事件 (这里指点击事件)
        {
            QDialog *dlg = m_keyBoardLib.GetNumKeyBoardDialog();
            //m_keyBoardLib.SetNum(ui->txtImageName->text());
            int ret = dlg->exec();
            if(ret == QDialog::Accepted)
            {
                ui->lineEdit_IP3->setText(m_keyBoardLib.GetNum());
            }
        }
    }
    if (watched == ui->lineEdit_IP4 && ((QLineEdit*)watched)->isEnabled())         //首先判断控件(这里指 lineEdit1)
    {
        if (event->type()==QEvent::MouseButtonPress)     //然后再判断控件的具体事件 (这里指点击事件)
        {
            QDialog *dlg = m_keyBoardLib.GetNumKeyBoardDialog();
            //m_keyBoardLib.SetNum(ui->txtImageName->text());
            int ret = dlg->exec();
            if(ret == QDialog::Accepted)
            {
                ui->lineEdit_IP4->setText(m_keyBoardLib.GetNum());
            }
        }
    }


    return QWidget::eventFilter(watched, event);
}

void CalibrationWidget::on_btnNew_clicked()
{
    int curRow = ui->listWidgetParamType->currentRow();
    int paramCount = ui->listWidgetParamList->count();

    if (curRow == 0)
    {
        if (paramCount >= HOMO_CONFIG_MAX)
        {
            QMessageBox::about(NULL, tr("提示"), tr("参数已满!"));
            return;
        }
        MultipointsDemarcate mpdDlg;
        mpdDlg.SetParamIndex(paramCount);
        mpdDlg.SetCurRobotID(m_robot_id);
        mpdDlg.exec();
        MultipointDemarcateParamListInit();
    }
    else if (curRow == 1)
    {
        if (paramCount >= SCALE_RATIO_PARAM_MAX)
        {
            QMessageBox::about(NULL, tr("提示"), tr("参数已满!"));
            return;
        }
        ScaleCalibration scaleDlg;
        scaleDlg.SetParamIndex(paramCount);
        int ret = scaleDlg.exec();
        if (ret == QDialog::Accepted)
        {
            int index = ui->listWidgetParamList->count();
            ui->listWidgetParamList->addItem(tr("参数")+QString::number(index+1)+"("+scaleDlg.GetRatio()+")");
            if (index >= 0)
            {
                ui->listWidgetParamList->setCurrentRow(index);
            }
            ScaleRatioParamCountInc();
            ScaleRatioInfoSaveToFile();
            ScaleCalibrationParamListInit();
        }
    }
}

void CalibrationWidget::MultipointDemarcateParamListInit()
{
    unsigned int param_num = 0, i = 0;
    char* name = NULL;
    QString nameString;

    // 获取参数个数
    param_num = GetHomoParamCount();

    if (param_num > HOMO_CONFIG_MAX)
    {
        QMessageBox::about(NULL, tr("提示"), tr("获取参数个数失败!"));
        return ;
    }

    ui->listWidgetParamList->clear();
    for (i = 0; i < param_num; ++ i)
    {
        name = GetHomoParamName(i);
        nameString = QString::fromUtf8(name);
        ui->listWidgetParamList->addItem(QString::number(i+1)+"."+nameString);
    }

    if (param_num > 0)
    {
        ui->listWidgetParamList->setCurrentRow(param_num - 1);
    }
}

void CalibrationWidget::ScaleCalibrationParamListInit()
{
    unsigned int param_num = 0, i = 0;
    // 获取参数个数

    param_num = GetScaleRatioParamCount();
    ui->listWidgetParamList->clear();
    if (param_num > SCALE_RATIO_PARAM_MAX)
    {
        QMessageBox::about(NULL, tr("提示"), tr("获取参数个数失败!"));
        return ;
    }

    double scaleRatio;
    for (i = 0; i < param_num; ++ i)
    {
        scaleRatio = GetScaleRatioByIndex(i);
        ui->listWidgetParamList->addItem(tr("参数")+QString::number(i+1)\
                                         +"("+QString::number(scaleRatio)+")");
    }

    if (param_num > 0)
    {
        ui->listWidgetParamList->setCurrentRow(param_num - 1);
    }
}

void CalibrationWidget::ParamReferencePanelInit()
{
    unsigned int demarcateRefIndex;
    unsigned int scaleRefIndex;
    // 获取任务步骤类型ID
    QVector<int> vt = GlobalParameter::g_libTaskFun.Get_taskID();

    if(vt.count() > 0)
    {
        for(int i = 0; i < vt.count(); ++ i)
        {
            int taskId = vt[i];
            QString strTaskDetailName = GlobalParameter::m_tool_name_hash.value(taskId);
            QString strName = QString::number(i+1);
            strName +=".";
            strName +=strTaskDetailName;

            CalibrationParamReference *newItem = new CalibrationParamReference;
            Task_Step_Homo_Param_Index_Get(i+1, &demarcateRefIndex);
            newItem->SetParamData(strName, i+1);
            newItem->UpdateParamReference(demarcateRefIndex);

            Task_Step_Scale_Cali_Param_Index_Get(i+1, &scaleRefIndex);
            if ((scaleRefIndex > 0) && (scaleRefIndex < 17))
            {
                float ratio = GetScaleRatioByIndex(scaleRefIndex - 1);
                newItem->UpdateScaleParamRef(scaleRefIndex, ratio);
            }
            else
            {
                newItem->UpdateScaleParamRef(0, 0.0);
            }
            QListWidgetItem *tmpItem = new QListWidgetItem;
            QSize tmpSize(380, 35);
            tmpItem->setSizeHint(tmpSize);
            ui->listWidgetParamReference->addItem(tmpItem);
            ui->listWidgetParamReference->setItemWidget(tmpItem, (QWidget *)newItem);
        }
    }
}

void CalibrationWidget::on_btnEdit_clicked()
{
    int typeRow = ui->listWidgetParamType->currentRow();
    int paramRow = ui->listWidgetParamList->currentRow();

    if (typeRow == 0)
    {
        if (paramRow >= 0)
        {
            MultipointsDemarcate dlg;
            dlg.SetCurRobotID(m_robot_id);
            dlg.ParamDataInit(paramRow);
            dlg.exec();
        }
    }
    else if (typeRow == 1)
    {
        if (paramRow >= 0)
        {
            QString strParam = ui->listWidgetParamList->item(paramRow)->text().split("(")[1];

            ScaleCalibration scaleDlg;
            scaleDlg.SetParamIndex(paramRow);
            scaleDlg.SetRatio(strParam.left(strParam.length()-1));
            int ret = scaleDlg.exec();
            if(ret == QDialog::Accepted)
            {
                if (ret == QDialog::Accepted)
                {
                    int index = ui->listWidgetParamList->count();
                    ui->listWidgetParamList->item(paramRow)->setText(tr("参数")+QString::number(index+1)+"("+scaleDlg.GetRatio()+")");
                    ScaleRatioInfoSaveToFile();
                    ScaleCalibrationParamListInit();
                    ParamReferencePanelUpdate();
                }
            }
        }
    }
}

void CalibrationWidget::on_btnDelete_clicked()
{
    int typeRow = ui->listWidgetParamType->currentRow();
    int paramRow = ui->listWidgetParamList->currentRow();

    if (paramRow >= 0)
    {
        QMessageBox::StandardButton rb = \
                QMessageBox::warning(NULL, \
                                     tr("提示"), \
                                     tr("确定删除"), \
                                     QMessageBox::Yes | QMessageBox::No, \
                                     QMessageBox::No);

        if(rb == QMessageBox::No)
        {
            return ;
        }
    }

    if (typeRow == 0)
    {
        if (paramRow >= 0)
        {
            HomoParamDeleteProc(paramRow);
            DeleteHomoParamUpdateStepLinkInfo(paramRow+1);
            MultipointDemarcateParamListInit();
        }
    }
    else if(typeRow == 1)
    {
        ui->listWidgetParamList->takeItem(ui->listWidgetParamList->currentRow());
        DeleteScaleRatioParam(paramRow);
        DeleteScaleRatioParamUpdateStepLinkInfo(paramRow+1);
        //        qDebug() << "Delete param index: " << paramRow;
        ScaleCalibrationParamListInit();
    }
    ParamReferencePanelUpdate();
}

void CalibrationWidget::ParamReferencePanelUpdate()
{
    ui->listWidgetParamReference->clear();
    ParamReferencePanelInit();
}

void CalibrationWidget::on_listWidgetParamType_currentRowChanged(int currentRow)
{
    if (currentRow == 0)
    {
        ui->btnRename->show();
        MultipointDemarcateParamListInit();
    }
    else if (currentRow == 1)
    {
        ui->btnRename->hide();
        ScaleCalibrationParamListInit();
    }

    // 保存机器人ID
    QString robotIdString = ui->txtID->text();
    m_robot_id = robotIdString.toInt();
}

void CalibrationWidget::on_tabWidget_tabBarClicked(int index)
{
    if (index == 0)
    {
        ui->labelPic->setVisible(false);
    }
    else if (index == 1)
    {
        ui->labelPic->setVisible(false);
    }else if(index == 2)
    {
        ui->labelPic->setVisible(true);
        UtilitiesFun::Instance()->ListVGA(ui->labelPic->x(),ui->labelPic->y());
        UtilitiesFun::Instance()->SetCPT(CPT_CMOS_PIC);
    }
}

void CalibrationWidget::on_btnXSub_pressed()
{
    m_kind =1;
    m_AxisID = 0;
    m_Derection = 0;
    m_start = QTime::currentTime();
    m_timer->start(10);
}

void CalibrationWidget::on_btnXSub_released()
{
    m_timer->stop();
    m_end = QTime::currentTime();

    if(ui->checkBoxSpace->isChecked())
    {
        OnMoveRelL();
    }else
    {
        if(IsTimeOut() == 1)
        {
            on_btnStop_clicked();
        }else
        {
            OnShortJogL();
        }
    }
    OnReadPcsActualPos();
}

void CalibrationWidget::on_btnYSub_pressed()
{
    m_kind =1;
    m_AxisID = 1;
    m_Derection = 0;
    m_start = QTime::currentTime();
    if(!ui->checkBoxSpace->isChecked())
        m_timer->start(10);
}

void CalibrationWidget::on_btnYSub_released()
{
    m_timer->stop();
    m_end = QTime::currentTime();

    if(ui->checkBoxSpace->isChecked())
    {
        OnMoveRelL();
    }else
    {
        if(IsTimeOut() == 1)
        {
            on_btnStop_clicked();
        }else
        {
            OnShortJogL();
        }
    }
    OnReadPcsActualPos();
}

void CalibrationWidget::on_btnZSub_pressed()
{
    m_kind =1;
    m_AxisID = 2;
    m_Derection = 0;
    m_start = QTime::currentTime();
    if(!ui->checkBoxSpace->isChecked())
        m_timer->start(10);
}

void CalibrationWidget::on_btnZSub_released()
{
    m_timer->stop();
    m_end = QTime::currentTime();
    if(ui->checkBoxSpace->isChecked())
    {
        OnMoveRelL();
    }else
    {
        if(IsTimeOut() == 1)
        {
            on_btnStop_clicked();
        }else
        {
            OnShortJogL();
        }
    }
    OnReadPcsActualPos();
}

void CalibrationWidget::on_btnASub_pressed()
{
    m_kind =1;
    m_AxisID = 3;
    m_Derection = 0;
    m_start = QTime::currentTime();
    if(!ui->checkBoxSpace->isChecked())
        m_timer->start(10);
}

void CalibrationWidget::on_btnASub_released()
{
    m_timer->stop();
    m_end = QTime::currentTime();
    if(ui->checkBoxSpace->isChecked())
    {
        OnMoveRelL();
    }else
    {
        if(IsTimeOut() == 1)
        {
            on_btnStop_clicked();
        }else
        {
            OnShortJogL();
        }
    }
    OnReadPcsActualPos();
}

void CalibrationWidget::on_btnBSub_pressed()
{
    m_kind =1;
    m_AxisID = 4;
    m_Derection = 0;
    m_start = QTime::currentTime();
    if(!ui->checkBoxSpace->isChecked())
        m_timer->start(10);
}

void CalibrationWidget::on_btnBSub_released()
{
    m_timer->stop();
    m_end = QTime::currentTime();
    if(ui->checkBoxSpace->isChecked())
    {
        OnMoveRelL();
    }else
    {
        if(IsTimeOut() == 1)
        {
            on_btnStop_clicked();
        }else
        {
            OnShortJogL();
        }
    }
    OnReadPcsActualPos();
}

void CalibrationWidget::on_btnCSub_pressed()
{
    m_kind =1;
    m_AxisID = 5;
    m_Derection = 0;
    m_start = QTime::currentTime();
    if(!ui->checkBoxSpace->isChecked())
        m_timer->start(10);
}

void CalibrationWidget::on_btnCSub_released()
{
    m_timer->stop();
    m_end = QTime::currentTime();
    if(ui->checkBoxSpace->isChecked())
    {
        OnMoveRelL();
    }else
    {
        if(IsTimeOut() == 1)
        {
            on_btnStop_clicked();
        }else
        {
            OnShortJogL();
        }
    }
    OnReadPcsActualPos();
}

void CalibrationWidget::on_btnXAdd_pressed()
{
    m_kind =1;
    m_AxisID = 0;
    m_Derection = 1;
    m_start = QTime::currentTime();
    if(!ui->checkBoxSpace->isChecked())
        m_timer->start(10);
}

void CalibrationWidget::on_btnXAdd_released()
{
    m_timer->stop();
    m_end = QTime::currentTime();
    if(ui->checkBoxSpace->isChecked())
    {
        OnMoveRelL();
    }else
    {
        if(IsTimeOut() == 1)
        {
            on_btnStop_clicked();
        }else
        {
            OnShortJogL();
        }
    }
    OnReadPcsActualPos();
}
void CalibrationWidget::on_btnYAdd_pressed()
{
    m_kind =1;
    m_AxisID = 1;
    m_Derection = 1;
    m_start = QTime::currentTime();
    if(!ui->checkBoxSpace->isChecked())
        m_timer->start(10);
}

void CalibrationWidget::on_btnYAdd_released()
{
    m_timer->stop();
    m_end = QTime::currentTime();
    if(ui->checkBoxSpace->isChecked())
    {
        OnMoveRelL();
    }else
    {
        if(IsTimeOut() == 1)
        {
            on_btnStop_clicked();
        }else
        {
            OnShortJogL();
        }
    }
    OnReadPcsActualPos();
}
void CalibrationWidget::on_btnZAdd_pressed()
{
    m_kind =1;
    m_AxisID = 2;
    m_Derection = 1;
    m_start = QTime::currentTime();
    if(!ui->checkBoxSpace->isChecked())
        m_timer->start(10);
}

void CalibrationWidget::on_btnZAdd_released()
{
    m_timer->stop();
    m_end = QTime::currentTime();
    if(ui->checkBoxSpace->isChecked())
    {
        OnMoveRelL();
    }else
    {
        if(IsTimeOut() == 1)
        {
            on_btnStop_clicked();
        }else
        {
            OnShortJogL();
        }
    }
    OnReadPcsActualPos();
}
void CalibrationWidget::on_btnAAdd_pressed()
{
    m_kind =1;
    m_AxisID = 3;
    m_Derection = 1;
    m_start = QTime::currentTime();
    if(!ui->checkBoxSpace->isChecked())
        m_timer->start(10);
}

void CalibrationWidget::on_btnAAdd_released()
{
    m_timer->stop();
    m_end = QTime::currentTime();
    if(ui->checkBoxSpace->isChecked())
    {
        OnMoveRelL();
    }else
    {
        if(IsTimeOut() == 1)
        {
            on_btnStop_clicked();
        }else
        {
            OnShortJogL();
        }
    }
    OnReadPcsActualPos();
}
void CalibrationWidget::on_btnBAdd_pressed()
{
    m_kind =1;
    m_AxisID = 4;
    m_Derection = 1;
    m_start = QTime::currentTime();
    if(!ui->checkBoxSpace->isChecked())
        m_timer->start(10);
}

void CalibrationWidget::on_btnBAdd_released()
{
    m_timer->stop();
    m_end = QTime::currentTime();
    if(ui->checkBoxSpace->isChecked())
    {
        OnMoveRelL();
    }else
    {
        if(IsTimeOut() == 1)
        {
            on_btnStop_clicked();
        }else
        {
            OnShortJogL();
        }
    }
    OnReadPcsActualPos();
}
void CalibrationWidget::on_btnCAdd_pressed()
{
    m_kind =1;
    m_AxisID = 5;
    m_Derection = 1;
    m_start = QTime::currentTime();
    m_timer->start(10);
}

void CalibrationWidget::on_btnCAdd_released()
{
    m_timer->stop();
    m_end = QTime::currentTime();
    if(ui->checkBoxSpace->isChecked())
    {
        OnMoveRelL();
    }else
    {
        if(IsTimeOut() == 1)
        {
            on_btnStop_clicked();
        }else
        {
            OnShortJogL();
        }
    }
    OnReadPcsActualPos();
}
int CalibrationWidget::IsTimeOut()
{
    int ret =0;
    int time = m_start.msecsTo(m_end);
    if(time >=200)
    {
        ret = 1;
    }else
    {
        ret =0;
    }
    return ret;
}

void CalibrationWidget::on_btnRename_clicked()
{
    int paramRow = ui->listWidgetParamList->currentRow();
    char* paramName = NULL;

    if (paramRow >= 0)
    {
        CommonRowInput *p = NULL;
        p = static_cast<CommonRowInput *>(rowInput);
        paramName = GetHomoParamName(paramRow);
        p->SetInputText(QString::fromUtf8(paramName));
        p->show();
    }
}

void CalibrationWidget::RecieveRenameText(QString text)
{
    QString nameString = text;
    QByteArray ba = nameString.toUtf8();
    char* name = ba.data();
    printf("name:%s\n", name);
    int typeRow = ui->listWidgetParamType->currentRow();
    int paramRow = ui->listWidgetParamList->currentRow();

    if (typeRow == 0)
    {
        // 多点标定
        if (paramRow >= 0)
        {
            SetHomoParamName(paramRow, name);
            nameString = QString::number(paramRow + 1) + "." + text;
            ui->listWidgetParamList->item(paramRow)->setText(nameString);
            ParamReferencePanelUpdate();
        }
    }
    else if (typeRow == 1)
    {
        // 刻度校准
        if (paramRow >= 0)
        {
            // TODO(目前的方式比较好，不建议做改动)
        }
    }
}
//上电
void CalibrationWidget::on_btnElectrify_clicked()
{
    int ret = Hans_Rbt_Communicate_Data_Splice(Electrify, 0, NULL);
    if(ret ==1)
    {
        ui->labelInfo->setText("上电成功");
    }else
    {
        ui->labelInfo->setText("上电失败");
    }

}
//断电
void CalibrationWidget::on_btnBlackOut_clicked()
{
    int ret =Hans_Rbt_Communicate_Data_Splice(BlackOut, 0, NULL);
    if(ret ==1)
    {
        ui->labelInfo->setText("断电成功");
    }else
    {
        ui->labelInfo->setText("断电失败");
    }
}
//使能
void CalibrationWidget::on_bntGrpPowerOn_clicked()
{   //DATA_DBL_INV
    HANS_RBT_PARAM para;
    para.data_type = DATA_SINT;
    para.param.inum = ui->txtID->text().toInt();
    int ret = Hans_Rbt_Communicate_Data_Splice(GrpPowerOn, 1, &para);
    if(ret ==1)
    {
        ui->labelInfo->setText("使能成功");
    }else
    {
        ui->labelInfo->setText("使能失败");
    }
    OnReadAcsActualPos();
    OnReadPcsActualPos();
}
//不使能
void CalibrationWidget::on_bntGrpPowerOff_clicked()
{
    HANS_RBT_PARAM para;
    para.data_type = DATA_SINT;
    para.param.inum = ui->txtID->text().toInt();
    int ret = Hans_Rbt_Communicate_Data_Splice(GrpPowerOff, 1, &para);
    if(ret ==1)
    {
        ui->labelInfo->setText("不使能成功");
    }else
    {
        ui->labelInfo->setText("不使能失败");
    }
}
//复位
void CalibrationWidget::on_btnReset_clicked()
{
    HANS_RBT_PARAM para;
    para.data_type = DATA_SINT;
    para.param.inum = ui->txtID->text().toInt();
    int ret = Hans_Rbt_Communicate_Data_Splice(GrpReset, 1, &para);
    if(ret ==1)
    {
        ui->labelInfo->setText("复位成功");
    }else
    {
        ui->labelInfo->setText("复位失败");
    }

}
//急停
void CalibrationWidget::on_btnStop_clicked()
{
    HANS_RBT_PARAM para;
    para.data_type = DATA_SINT;
    para.param.inum = ui->txtID->text().toInt();
    int ret = Hans_Rbt_Communicate_Data_Splice(GrpStop, 1, &para);
    if(ret ==1)
    {
        ui->labelInfo->setText("急停成功");
    }else
    {
        ui->labelInfo->setText("急停失败");
    }
}

void CalibrationWidget::on_btnJ1Sub_pressed()
{
    m_kind =2;
    m_AxisID = 0;
    m_Derection = 0;
    m_start = QTime::currentTime();

    if(!ui->checkBoxAngle->isChecked())
        m_timer->start(10);

}

void CalibrationWidget::on_btnJ1Sub_released()
{
    m_timer->stop();
    m_end = QTime::currentTime();

    if(ui->checkBoxAngle->isChecked())
    {
        OnMoveRelJ();
    }else
    {
        if(IsTimeOut() == 1)
        {
            on_btnStop_clicked();
        }else
        {
            OnShortJogJ();
        }
    }
    OnReadAcsActualPos();

}
void CalibrationWidget::on_btnJ2Sub_pressed()
{
    m_kind =2;
    m_AxisID = 1;
    m_Derection = 0;
    m_start = QTime::currentTime();
    if(!ui->checkBoxAngle->isChecked())
        m_timer->start(10);
}

void CalibrationWidget::on_btnJ2Sub_released()
{
    m_timer->stop();
    m_end = QTime::currentTime();

    if(ui->checkBoxAngle->isChecked())
    {
        OnMoveRelJ();
    }else
    {
        if(IsTimeOut() == 1)
        {
            on_btnStop_clicked();
        }else
        {
            OnShortJogJ();
        }
    }
    OnReadAcsActualPos();
}
void CalibrationWidget::on_btnJ3Sub_pressed()
{
    m_kind =2;
    m_AxisID = 2;
    m_Derection = 0;
    m_start = QTime::currentTime();
    if(!ui->checkBoxAngle->isChecked())
        m_timer->start(10);
}

void CalibrationWidget::on_btnJ3Sub_released()
{
    m_timer->stop();
    m_end = QTime::currentTime();

    if(ui->checkBoxAngle->isChecked())
    {
        OnMoveRelJ();
    }else
    {
        if(IsTimeOut() == 1)
        {
            on_btnStop_clicked();
        }else
        {
            OnShortJogJ();
        }
    }
    OnReadAcsActualPos();
}
void CalibrationWidget::on_btnJ4Sub_pressed()
{
    m_kind =2;
    m_AxisID = 3;
    m_Derection = 0;
    m_start = QTime::currentTime();
    if(!ui->checkBoxAngle->isChecked())
        m_timer->start(10);
}

void CalibrationWidget::on_btnJ4Sub_released()
{
    m_timer->stop();
    m_end = QTime::currentTime();

    if(ui->checkBoxAngle->isChecked())
    {
        OnMoveRelJ();
    }else
    {
        if(IsTimeOut() == 1)
        {
            on_btnStop_clicked();
        }else
        {
            OnShortJogJ();
        }
    }
    OnReadAcsActualPos();
}
void CalibrationWidget::on_btnJ5Sub_pressed()
{
    m_kind =2;
    m_AxisID = 4;
    m_Derection = 0;
    m_start = QTime::currentTime();
    if(!ui->checkBoxAngle->isChecked())
        m_timer->start(10);
}

void CalibrationWidget::on_btnJ5Sub_released()
{
    m_timer->stop();
    m_end = QTime::currentTime();

    if(ui->checkBoxAngle->isChecked())
    {
        OnMoveRelJ();
    }else
    {
        if(IsTimeOut() == 1)
        {
            on_btnStop_clicked();
        }else
        {
            OnShortJogJ();
        }
    }
    OnReadAcsActualPos();
}
void CalibrationWidget::on_btnJ6Sub_pressed()
{
    m_kind =2;
    m_AxisID = 5;
    m_Derection = 0;
    m_start = QTime::currentTime();
    if(!ui->checkBoxAngle->isChecked())
        m_timer->start(10);
}

void CalibrationWidget::on_btnJ6Sub_released()
{
    m_timer->stop();
    m_end = QTime::currentTime();

    if(ui->checkBoxAngle->isChecked())
    {
        OnMoveRelJ();
    }else
    {
        if(IsTimeOut() == 1)
        {
            on_btnStop_clicked();
        }else
        {
            OnShortJogJ();
        }
    }
    OnReadAcsActualPos();
}

void CalibrationWidget::on_btnJ1Add_pressed()
{
    m_kind =2;
    m_AxisID = 0;
    m_Derection = 1;
    m_start = QTime::currentTime();
    if(!ui->checkBoxAngle->isChecked())
        m_timer->start(10);
}
void CalibrationWidget::on_btnJ1Add_released()
{
    m_timer->stop();
    m_end = QTime::currentTime();

    if(ui->checkBoxAngle->isChecked())
    {
        OnMoveRelJ();
    }else
    {
        if(IsTimeOut() == 1)
        {
            on_btnStop_clicked();
        }else
        {
            OnShortJogJ();
        }
    }
    OnReadAcsActualPos();
}
void CalibrationWidget::on_btnJ2Add_pressed()
{
    m_kind =2;
    m_AxisID = 1;
    m_Derection = 1;
    m_start = QTime::currentTime();
    if(!ui->checkBoxAngle->isChecked())
        m_timer->start(10);
}
void CalibrationWidget::on_btnJ2Add_released()
{
    m_timer->stop();
    m_end = QTime::currentTime();

    if(ui->checkBoxAngle->isChecked())
    {
        OnMoveRelJ();
    }else
    {
        if(IsTimeOut() == 1)
        {
            on_btnStop_clicked();
        }else
        {
            OnShortJogJ();
        }
    }
    OnReadAcsActualPos();
}
void CalibrationWidget::on_btnJ3Add_pressed()
{
    m_kind =2;
    m_AxisID = 2;
    m_Derection = 1;
    m_start = QTime::currentTime();
    if(!ui->checkBoxAngle->isChecked())
        m_timer->start(10);
}
void CalibrationWidget::on_btnJ3Add_released()
{
    m_timer->stop();
    m_end = QTime::currentTime();

    if(ui->checkBoxAngle->isChecked())
    {
        OnMoveRelJ();
    }else
    {
        if(IsTimeOut() == 1)
        {
            on_btnStop_clicked();
        }else
        {
            OnShortJogJ();
        }
    }
    OnReadAcsActualPos();
}
void CalibrationWidget::on_btnJ4Add_pressed()
{
    m_kind =2;
    m_AxisID = 3;
    m_Derection = 1;
    m_start = QTime::currentTime();
    if(!ui->checkBoxAngle->isChecked())
        m_timer->start(10);
}
void CalibrationWidget::on_btnJ4Add_released()
{
    m_timer->stop();
    m_end = QTime::currentTime();

    if(ui->checkBoxAngle->isChecked())
    {
        OnMoveRelJ();
    }else
    {
        if(IsTimeOut() == 1)
        {
            on_btnStop_clicked();
        }else
        {
            OnShortJogJ();
        }
    }
    OnReadAcsActualPos();
}
void CalibrationWidget::on_btnJ5Add_pressed()
{
    m_kind =2;
    m_AxisID = 4;
    m_Derection = 1;
    m_start = QTime::currentTime();
    if(!ui->checkBoxAngle->isChecked())
        m_timer->start(10);
}
void CalibrationWidget::on_btnJ5Add_released()
{
    m_timer->start(10);
    m_end = QTime::currentTime();

    if(ui->checkBoxAngle->isChecked())
    {
        OnMoveRelJ();
    }else
    {
        if(IsTimeOut() == 1)
        {
            on_btnStop_clicked();
        }else
        {
            OnShortJogJ();
        }
    }
    OnReadAcsActualPos();
}
void CalibrationWidget::on_btnJ6Add_pressed()
{
    m_kind =2;
    m_AxisID = 5;
    m_Derection = 1;
    m_start = QTime::currentTime();
    if(!ui->checkBoxAngle->isChecked())
        m_timer->start(10);
}
void CalibrationWidget::on_btnJ6Add_released()
{
    m_timer->stop();

    m_end = QTime::currentTime();

    if(ui->checkBoxAngle->isChecked())
    {
        OnMoveRelJ();
    }else
    {
        if(IsTimeOut() == 1)
        {
            on_btnStop_clicked();
        }else
        {
            OnShortJogJ();
        }
    }
    OnReadAcsActualPos();
}
void CalibrationWidget::OnShortJogL()
{
    HANS_RBT_PARAM para[3];
    para[0].data_type = DATA_SINT;
    para[0].param.inum = ui->txtID->text().toInt();
    para[1].data_type = DATA_SINT;
    para[1].param.inum = m_AxisID;
    para[2].data_type = DATA_SINT;
    para[2].param.inum = m_Derection;
    int ret = Hans_Rbt_Communicate_Data_Splice(ShortJogL, 3, para);
    if(ret ==1)
    {
        ui->labelInfo->setText("ShortJogL成功");
    }else
    {
        ui->labelInfo->setText("ShortJogL失败");
    }

}
void CalibrationWidget::OnLongJogL()
{
    HANS_RBT_PARAM para[3];
    para[0].data_type = DATA_SINT;
    para[0].param.inum = ui->txtID->text().toInt();
    para[1].data_type = DATA_SINT;
    para[1].param.inum = m_AxisID;
    para[2].data_type = DATA_SINT;
    para[2].param.inum = m_Derection;
    int ret = Hans_Rbt_Communicate_Data_Splice(LongJogL, 3, para);
    if(ret ==1)
    {
        ui->labelInfo->setText("LongJogL成功");
    }else
    {
        ui->labelInfo->setText("LongJogL失败");
    }
}
void CalibrationWidget::OnShortJogJ() //角度
{
    HANS_RBT_PARAM para[3];
    para[0].data_type = DATA_SINT;
    para[0].param.inum = ui->txtID->text().toInt();
    para[1].data_type = DATA_SINT;
    para[1].param.inum = m_AxisID;
    para[2].data_type = DATA_SINT;
    para[2].param.inum = m_Derection;
    int ret = Hans_Rbt_Communicate_Data_Splice(ShortJogJ, 3, para);
    if(ret ==1)
    {
        ui->labelInfo->setText("ShortJogJ成功");
    }else
    {
        ui->labelInfo->setText("ShortJogJ失败");
    }
}
void CalibrationWidget::OnLongJogJ()
{
    HANS_RBT_PARAM para[3];
    para[0].data_type = DATA_SINT;
    para[0].param.inum = ui->txtID->text().toInt();
    para[1].data_type = DATA_SINT;
    para[1].param.inum = m_AxisID;
    para[2].data_type = DATA_SINT;
    para[2].param.inum = m_Derection;
    int ret = Hans_Rbt_Communicate_Data_Splice(LongJogJ, 3, para);
    if(ret ==1)
    {
        ui->labelInfo->setText("LongJogJ成功");
    }else
    {
        ui->labelInfo->setText("LongJogJ失败");
    }
}
void CalibrationWidget::OnMoveRelL()
{
    HANS_RBT_PARAM para[4];
    para[0].data_type = DATA_SINT;
    para[0].param.inum = ui->txtID->text().toInt();
    para[1].data_type = DATA_SINT;
    para[1].param.inum = m_AxisID;
    para[2].data_type = DATA_SINT;
    para[2].param.inum = m_Derection;
    para[3].data_type = DATA_DBL;
    para[3].param.dnum = ui->txtSpaceStep->text().toDouble();
    int ret = Hans_Rbt_Communicate_Data_Splice(MoveRelL, 4, para);
    if(ret ==1)
    {
        ui->labelInfo->setText("MoveRelL成功");
    }else
    {
        ui->labelInfo->setText("MoveRelL失败");
    }
}
void CalibrationWidget::OnMoveRelJ()
{
    HANS_RBT_PARAM para[4];
    para[0].data_type = DATA_SINT;
    para[0].param.inum = ui->txtID->text().toInt();
    para[1].data_type = DATA_SINT;
    para[1].param.inum = m_AxisID;
    para[2].data_type = DATA_SINT;
    para[2].param.inum = m_Derection;
    para[3].data_type = DATA_DBL;
    para[3].param.dnum = ui->txtSpaceStep->text().toDouble();
    int ret = Hans_Rbt_Communicate_Data_Splice(MoveRelJ, 4, para);
    if(ret ==1)
    {
        ui->labelInfo->setText("MoveRelJ成功");
    }else
    {
        ui->labelInfo->setText("MoveRelJ失败");
    }
}
void CalibrationWidget::OnReadAcsActualPos()
{
    WaitRobotMotionFinish(ui->txtID->text().toInt());
    HANS_RBT_PARAM para;
    para.data_type = DATA_SINT;
    para.param.inum = ui->txtID->text().toInt();
    int ret = Hans_Rbt_Communicate_Data_Splice(ReadAcsActualPos, 1, &para);
    if(ret ==1)
    {
        ui->labelInfo->setText("ReadPcsActualPos成功");

        HANS_RBT_PARAM ret_para[6];
        memset(ret_para,0,sizeof(ret_para));
        hans_robot_recv_data_get(ret_para, 6);

        ui->txtJ1->setText(QString::number(ret_para[0].param.dnum,'f',3));
        ui->txtJ2->setText(QString::number(ret_para[1].param.dnum,'f',3));
        ui->txtJ3->setText(QString::number(ret_para[2].param.dnum,'f',3));
        ui->txtJ4->setText(QString::number(ret_para[3].param.dnum,'f',3));
        ui->txtJ5->setText(QString::number(ret_para[4].param.dnum,'f',3));
        ui->txtJ6->setText(QString::number(ret_para[5].param.dnum,'f',3));


    }else
    {
        ui->labelInfo->setText("ReadPcsActualPos失败");
    }


}
void CalibrationWidget::OnReadPcsActualPos()
{
    WaitRobotMotionFinish(ui->txtID->text().toInt());
    HANS_RBT_PARAM para;
    para.data_type = DATA_SINT;
    para.param.inum = ui->txtID->text().toInt();
    int ret =Hans_Rbt_Communicate_Data_Splice(ReadPcsActualPos, 1, &para);

    if(ret ==1)
    {
        ui->labelInfo->setText("ReadPcsActualPos成功");
        HANS_RBT_PARAM ret_para[6];
        memset(ret_para,0,sizeof(ret_para));
        hans_robot_recv_data_get(ret_para, 6);
        ui->txtX->setText(QString::number(ret_para[0].param.dnum,'f',3));
        ui->txtY->setText(QString::number(ret_para[1].param.dnum,'f',3));
        ui->txtZ->setText(QString::number(ret_para[2].param.dnum,'f',3));
        ui->txtA->setText(QString::number(ret_para[3].param.dnum,'f',3));
        ui->txtB->setText(QString::number(ret_para[4].param.dnum,'f',3));
        ui->txtC->setText(QString::number(ret_para[5].param.dnum,'f',3));

    }else
    {
        ui->labelInfo->setText("ReadPcsActualPos失败");
    }
}
void CalibrationWidget::TimeOutFun()
{
    m_end = QTime::currentTime();

    if(IsTimeOut() == 1)
    {
        if(m_kind ==1)
        {
            OnLongJogL();
        }else if(m_kind ==2)
        {
            OnLongJogJ();
        }
        m_timer->stop();
    }

}
void CalibrationWidget::InitEthernet()
{
    ui->lineEdit_IP1->installEventFilter(this);
    ui->lineEdit_IP2->installEventFilter(this);
    ui->lineEdit_IP3->installEventFilter(this);
    ui->lineEdit_IP4->installEventFilter(this);
    ui->lineEdit_Port->installEventFilter(this);
    ui->EthernetPortcbB->addItem(tr("服务端"));
    ui->EthernetPortcbB->addItem(tr("客户端"));
    TCP_CONFIG tcp_param;
    hans_robot_tcp_config_get(&tcp_param);
    ui->EthernetPortcbB->setCurrentIndex(tcp_param.net_type);
    QString ip_String = QString::fromLatin1(tcp_param.ip);
    QStringList strIpList= ip_String.split(".");
    if(strIpList.count() == 4)
    {
        ui->lineEdit_IP1->setText(strIpList.at(0));
        ui->lineEdit_IP2->setText(strIpList.at(1));
        ui->lineEdit_IP3->setText(strIpList.at(2));
        ui->lineEdit_IP4->setText(strIpList.at(3));
    }
    else
    {
        ui->lineEdit_IP1->setText("192");
        ui->lineEdit_IP2->setText("168");
        ui->lineEdit_IP3->setText("0");
        ui->lineEdit_IP4->setText("1");
    }
    char port_str[5];
    memset(port_str, 0, 5);
    sprintf(port_str, "%d", tcp_param.port);
    QString Port_String = QString::fromLatin1(port_str);
    if(tcp_param.port < 0 || tcp_param.port > 65535)
    {
        ui->lineEdit_Port->setText("8080");
    }
    else
    {
        ui->lineEdit_Port->setText(Port_String);
    }
    int iStatus = hans_robot_protocol_status_get();
    if(ui->EthernetPortcbB->currentIndex() == 0)
    {
        ui->IP_Label->setText(tr("本地IP地址"));
        ui->Port_Label->setText(tr("本地端口号"));

        if(iStatus == 0)
        {
            ui->StartpushButton->setText(tr("启动"));
            SetGroupBoxEnable(0);
        }
        else
        {
            ui->StartpushButton->setText(tr("停止"));
            SetGroupBoxEnable(1);
        }
    }
    else
    {
        ui->IP_Label->setText(tr("服务器IP地址"));
        ui->Port_Label->setText(tr("服务器端口号"));
        if(iStatus== 0)
        {
            ui->StartpushButton->setText(tr("连接"));
            SetGroupBoxEnable(0);
        }
        else
        {
            ui->StartpushButton->setText(tr("断开"));
            SetGroupBoxEnable(1);
        }

    }

}
int CalibrationWidget::SetEthernetParam()
{
    ///<设置网口模式
    TCP_CONFIG tcp_param;
    tcp_param.net_type = ui->EthernetPortcbB->currentIndex();
    ///<设置IP
    QString ip_String = ui->lineEdit_IP1->text()+"."+ui->lineEdit_IP2->text()+ \
            "."+ui->lineEdit_IP3->text()+"."+ui->lineEdit_IP4->text();
    QByteArray ba = ip_String.toUtf8();
    char* ip = ba.data();
    memset(tcp_param.ip, 0, 16);
    memcpy(tcp_param.ip, ip, strlen(ip));
    ///<设置端口号
    tcp_param.port = ui->lineEdit_Port->text().toInt();

    hans_robot_tcp_config_set(&tcp_param);

    ///<开启协议
    int ret = hans_robot_homo_comm_open(1);

    return ret;
}

void CalibrationWidget::on_StartpushButton_clicked()
{

        if(ui->StartpushButton->text() == "连接")
        {
            if(SetEthernetParam() == 1)
            {
                ui->StartpushButton->setText(tr("断开"));
                SetGroupBoxEnable(1);
            }
        }else if(ui->StartpushButton->text() == "断开")
        {
            if(hans_robot_homo_comm_close(1)== 1)
            {
                ui->StartpushButton->setText(tr("连接"));
                SetGroupBoxEnable(0);
            }
        }else if(ui->StartpushButton->text() == "启动")
        {
            if(SetEthernetParam() == 1)
            {
                ui->StartpushButton->setText(tr("停止"));
                SetGroupBoxEnable(1);
            }
        }else if(ui->StartpushButton->text() == "停止")
        {
            if(hans_robot_homo_comm_close(1)== 1)
            {
                ui->StartpushButton->setText(tr("启动"));
                SetGroupBoxEnable(0);
            }
        }


}
void CalibrationWidget::SetGroupBoxEnable(int blag)
{
    ui->EthernetPortcbB->setEnabled(!blag);
    ui->lineEdit_IP1->setEnabled(!blag);
    ui->lineEdit_IP2->setEnabled(!blag);
    ui->lineEdit_IP3->setEnabled(!blag);
    ui->lineEdit_IP4->setEnabled(!blag);
    ui->lineEdit_Port->setEnabled(!blag);

    ui->btnPre->setEnabled(blag);
    ui->btnNext->setEnabled(blag);
    ui->groupBox_1->setEnabled(blag);
    ui->groupBox_2->setEnabled(blag);
    ui->groupBox_3->setEnabled(blag);
}

void CalibrationWidget::on_btnNext_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void CalibrationWidget::on_btnPre_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void CalibrationWidget::on_pushButton_Manual_send_clicked()
{
    ui->labelInfo->setText("");
    int index = ui->listWidget_User_Def_List->currentRow();
    if(index >= 0){
        int list_index = User_List_index.value(index);
        int ret = user_defined_data_stream_send(list_index);
        if(ret > 0){
            Recv_time->start(10);
        }else{
            QMessageBox::about(NULL, "提示", "发送失败");
        }
    }
}


void CalibrationWidget::ShowRecvData()
{
    char data[1024];
    Recv_count++;
    int ret = user_defined_recv_data_get(data, 1024);
    if(ret > 0){
        ui->labelInfo->setText(QString::fromUtf8(data));
        Recv_time->stop();
        Recv_count = 0;
    }else{
        if(Recv_count > 500){
            Recv_time->stop();
            Recv_count = 0;
        }
    }
}
