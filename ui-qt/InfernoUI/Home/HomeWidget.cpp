#include <QDebug>
#include "HomeWidget.h"
#include "ui_HomeWidget.h"
#include <QDir>
#include "Comm/ControlStyle.h"
#include "BusinessData/RunData/CRunDataThread.h"
#include "BusinessData/InterfaceLib/LibTaskXMLParse.h"
#include "Comm/GlobalParameter.h"
#include "Comm/FileIniControl.h"
#include "TaskManageGlobal.h"
#include "RunOsdStyle/RunOsdStyleDlg.h"
#include <QMessageBox>
#include "../Global/UtilitiesFun.h"
#include "RegisterImageDlg.h"
#include "sszn_basic.h"
//#include "TaskSaveDlg.h"
#include "TaskLoadDlg.h"
#include "ToolEnable/ToolEnableDialog.h"
#include "SimulationTool/SimulationSelsetDog.h"
#include "SimulationTool/ImageManagemnet.h"
#include "RunStatistics/RunStatistics.h"
#include "TendencyGraph/TendencyGraph.h"
#include "System.h"
#include "TaskExecGlobal.h"
#include "SyntheticJudgment/SyntheticJudgment.h"
#include "image_include/ImageSimulationGlobal.h"
#include "BusinessData/InterfaceLib/BaseImageData.h"
#include "cmos_common.h"
#include "System.h"
#include "image_include/TaskRunImageSaveGlobal.h"


HomeWidget::HomeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomeWidget)
{
    ui->setupUi(this);
    m_RenameToolWidget = NULL;
    m_TaskSaveDlg = NULL;
    if(GlobalParameter::g_login == 1)
    {
        SetBtnEnable(1);
    }
    else
    {
        SetBtnEnable(0);
    }
    m_listOsd_timer = new QTimer;
    connect(m_listOsd_timer,&QTimer::timeout,this,&HomeWidget::ListOsdTimeOut);
    m_update_state = new QTimer();
    connect(m_update_state,&QTimer::timeout,this,&HomeWidget::UpdateStateTimeOut);
    ControlStyle::SetTabBar(ui->tabWidgetResult);
    ControlStyle::SetTabBar(ui->tabWidgetRun);
    ui->tabWidgetResult->setCurrentIndex(0);
    ui->tabWidgetRun->setCurrentIndex(0);
    ui->intervalLineEdit->installEventFilter(this);
    IniTaskListWiget();
    ui->stackedWidget->setCurrentIndex(0);
    UtilitiesFun::Instance()->ListVGA(ui->labelPic->x(),ui->labelPic->y());
    UtilitiesFun::Instance()->SetCPT(CPT_CMOS_PIC);
    GetIp();
    GetTaskSimulateMode();
    InitIconTask();
    InitUtilityToolIcon();
    AddOkNgPicSave();
    //InitSimulationDir();
    InitCurTaskName();
    QString isRun = FileIniControl::ReadSettings("./Config/UIIcon.ini","Inferno","AutoRun");

    if(isRun.toInt() == 1)
    {
        ui->checkBox_Startrun->setChecked(true);
//        run_clicked();
    }else
    {
        ui->checkBox_Startrun->setChecked(false);
    }
    m_update_state->start(1000);
}

void HomeWidget::InitUtilityToolIcon()
{
    QString path;
    QDir dir;
    path = dir.currentPath() + "/image/ToolMainIcon/";

    QPixmap pixIcon(path+"Trend_64_64.png");
    ui->btnCheck->setIcon(QIcon(pixIcon.scaled(QSize(48,48))));

    pixIcon.load(path+"Statistics_64_64.png");
    ui->btnRunCount->setIcon(QIcon(pixIcon.scaled(QSize(48,48))));

    pixIcon.load(path+"ToolEnable_64_64.png");
    ui->btnToolEnable->setIcon(QIcon(pixIcon.scaled(QSize(48,48))));
    pixIcon.load(path+"Rename_64_64.png");
    ui->btnToolRename->setIcon(QIcon(pixIcon.scaled(QSize(48,48))));
    pixIcon.load(path+"SyntheticJudgment.png");
    ui->btnJudge->setIcon(QIcon(pixIcon.scaled(QSize(48,48))));
    pixIcon.load(path+"osd_size_color.png");
    ui->btnToolOsdEdit->setIcon(QIcon(pixIcon.scaled(QSize(48,48))));

}

HomeWidget::~HomeWidget()
{
    disconnect(this,0,0,0);
    if(m_listOsd_timer != NULL)
    {
        delete m_listOsd_timer;
        m_listOsd_timer = NULL;
    }
    if(m_RenameToolWidget != NULL)
    {
        delete m_RenameToolWidget ;
        m_RenameToolWidget = NULL;
    }
    if(m_TaskSaveDlg !=NULL)
    {
        delete m_TaskSaveDlg;
        m_TaskSaveDlg = NULL;
    }
    if(m_update_state != NULL)
    {
        delete m_update_state;
        m_update_state = NULL;
    }
    ui->intervalLineEdit->removeEventFilter(this);
    CRunDataThread *run = CRunDataThread::Instance();
    run->DeleteVtLib();
    disconnect(this,0,0,0);
    delete ui;
}
void HomeWidget::UpdateStateTimeOut()
{
    GetIp();
}
void HomeWidget::AddOkNgPicSave()
{
    QString strOkPicSave = FileIniControl::ReadSettings("./Config/UIIcon.ini","Inferno","okPicSave");
    QString strNgPicSave = FileIniControl::ReadSettings("./Config/UIIcon.ini","Inferno","ngPicSave");
    QImage ppmOK(strOkPicSave);
    ui->label_ImageSave->setPixmap(QPixmap::fromImage(ppmOK));
    QImage ppmNG(strNgPicSave);
    ui->label_NGImageSave->setPixmap(QPixmap::fromImage(ppmNG));

    ui->LabelOKNGSaveInfo->setVisible(false);
    unsigned int iok =ok_pic_save_flag_get();
    if(iok == 1)
    {
        ui->label_ImageSave->setVisible(true);
        ui->checkBoxSaveImageOK->setChecked(true);
        ui->LabelOKNGSaveInfo->setVisible(true);

    }else
    {
        ui->label_ImageSave->setVisible(false);
        ui->checkBoxSaveImageOK->setChecked(false);
    }

    unsigned int iNg = ng_pic_save_flag_get();
    if(iNg == 1)
    {
        ui->label_NGImageSave->setVisible(true);
        ui->checkBoxSaveImage->setChecked(true);
        ui->LabelOKNGSaveInfo->setVisible(true);

    }else
    {
        ui->label_NGImageSave->setVisible(false);
        ui->checkBoxSaveImage->setChecked(false);
    }
}
void HomeWidget::InitIconTask()
{

    QString strNoExcute = FileIniControl::ReadSettings("./Config/UIIcon.ini","Inferno","noExecute");
    QString strOk = FileIniControl::ReadSettings("./Config/UIIcon.ini","Inferno","ok");
    QString strNg = FileIniControl::ReadSettings("./Config/UIIcon.ini","Inferno","ng");

    m_icon_ok = QIcon(QPixmap(strOk).scaled(QSize(32,32)));
    m_icon_ng = QIcon(QPixmap(strNg).scaled(QSize(32,32)));
    m_icon_noexcuse = QIcon(QPixmap(strNoExcute).scaled(QSize(32,32)));
}
void HomeWidget::GetIp()
{
    //0:错误 1:已连接 2:已断开 3:连接中
    int ret = GetNetworkStatus();

    char *pIP = NULL;
    switch (ret) {
    case 0:
        ui->labelIP->setText("网络错误");
        break;
    case 1:
        pIP = GetLocalIp();
        if(pIP !=NULL)
            ui->labelIP->setText(pIP);
        break;
    case 2:
        ui->labelIP->setText("网络已断开");
        break;
    case 3:
        ui->labelIP->setText("网络连接中");
        break;
    default:
        break;
    }
}
void HomeWidget::GetTaskSimulateMode()
{
   unsigned int taskState = TaskSimulateModeGet();
   if(taskState == 1)
   {
       ui->checkBox_SimuSwitch->setChecked(true);
       SetSimuControl(1);
       InitSimulationDir();
       ui->groupBox_2->setEnabled(false);
   }else
   {
       ui->checkBox_SimuSwitch->setChecked(false);
       SetSimuControl(0);
       ui->groupBox_2->setEnabled(true);
   }
}
void HomeWidget::IniTaskListWiget()
{

    QVector<int> vt = GlobalParameter::g_libTaskFun.Get_taskID();
    QString strPicName = FileIniControl::ReadSettings("./Config/UIIcon.ini","Inferno","noExecute");
    CRunDataThread *run = CRunDataThread::Instance();
    connect(run,&CRunDataThread::SignalsRunData,this,&HomeWidget::ShowRunDataSlot,Qt::QueuedConnection);
    connect(run,&CRunDataThread::SignalsOver,this,&HomeWidget::SlotOver,Qt::QueuedConnection);
    run->DeleteVtLib();
    char buf[64];

    GlobalParameter::m_area_select_state.clear();
    //connect(run,&CRunDataThread::OsdUpdateSignal,this,&HomeWidget::OsdUpdteSlot,Qt::BlockingQueuedConnection);
    for(int i =0; i<vt.count();i++)
    {
        int taskId = vt[i];
        QString strTaskDetailName = GlobalParameter::m_tool_name_hash.value(taskId);
        memset(buf,0,sizeof(buf));
        int ret = Task_Step_Alias_Get(i+1,64,buf);
        if (ret ==0)
        {
            strTaskDetailName = QString::fromUtf8(buf);
        }

        QString strName = QString::number(i+1);
        strName +=".";
        strName +=strTaskDetailName;
        QListWidgetItem *item = new QListWidgetItem(QIcon(QPixmap(strPicName).scaled(QSize(40,40))),strName);
        ui->listWidget->addItem(item);

        /*BaseLibInterface *toolibfun = new UIToolLibFun;
        QString strLibName = GlobalParameter::m_ID_LibName_hash.value(taskId);
        toolibfun->IniLib(strLibName);
        run->m_vt_lib.append(toolibfun);*/
        int value = 1;

        GlobalParameter::m_area_select_state.insert(i+1,value);

        /*ACCE_MODEL *m_pre_ptr = (ACCE_MODEL*)GetStepAcceModelPointer(i+1);

        for(int k = 0; k < m_pre_ptr->accelerator_num; k++)
        {
            if(m_pre_ptr->accelerator[k] == ACCE_AREA_SELECT_MODEL_ID)
            {
                value = 1;
                GlobalParameter::m_area_select_state.insert(i+1,value);
                break;
            }
        }*/
    }

    //ui->labelPic->SetLibVt(CRunDataThread::Instance()->m_vt_lib);

    if(ui->listWidget->count() > 0)
    {
        ui->listWidget->setCurrentRow(0);
    }
    RunOsdStyleDlg dlg;
    dlg.InitVt(ui->listWidget);
}
void HomeWidget::SlotOver()
{
    btnStop_clicked();
}
void HomeWidget::BeginRunTask()
{
    btnRun_clicked();
}
int HomeWidget::CheckParamInvalid()
{
    unsigned int i_step_total = ui->listWidget->count();
    if(i_step_total == 0)
    {
        SET_SYSTEM_USER_STATUS(0);
        return 0;
    }

    unsigned int i_ng_step_index[256];
    unsigned int i_ng_step_cnt = GetStepParamInvalidInfo(i_ng_step_index,i_step_total);

    if(i_ng_step_cnt != 0)
    {
        QString str_step_info = tr("步骤");
        if(i_ng_step_cnt <= i_step_total)
        {
            unsigned int i = 0;
            for(i = 0; i < i_ng_step_cnt; i++)
            {
                str_step_info.append(QString::number(i_ng_step_index[i])+",");
            }
        }
        QString str_message = str_step_info.left(str_step_info.length()-1)+tr("参数不完整!");
        QMessageBox::about(NULL,tr("提示"),str_message);
        SET_SYSTEM_USER_STATUS(0);
        return 0;
    }
    return 1;
}

void HomeWidget::run_clicked()
{
    SetRoundOverFlag(0);
    //运行前步骤参数检查
    if(CheckParamInvalid()==0)
    {
        SET_SYSTEM_USER_STATUS(0);
        return;
    }

    int ret = TaskRunStartProc();

    if(ret != 0)
    {
        SET_SYSTEM_USER_STATUS(0);
        QMessageBox::about(NULL,tr(""),tr("开始运行失败!"));
        return;
    }
    AddRunLib();
    TaskRunSignal(true);
    SetBtnEnable(0);
    //CRunDataThread::Instance()->StartRun(ui->listWidget->count());
    CRunDataThread::Instance()->SetSetpCnt(ui->listWidget->count());
    //CRunDataThread::Instance()->start(QThread::HighestPriority);
    CRunDataThread::Instance()->m_Simulat = 0;
    CRunDataThread::Instance()->start(QThread::NormalPriority);
    ui->stackedWidget->setCurrentIndex(1);
    m_listOsd_timer->start(1);
    task_run_image_save();
}
void HomeWidget::btnRun_clicked()
{
    if(ui->listWidget->count() == 0)
        return;
    SET_SYSTEM_USER_STATUS(1);
    run_clicked();
}
//注册
void HomeWidget::on_btnRecord_clicked()
{
    RegisterImageDlg registerImageDlg;
    registerImageDlg.exec();
    UtilitiesFun::Instance()->ListVGA(ui->labelPic->x(),ui->labelPic->y());
    //设置图像动态
}

void HomeWidget::btnStop_clicked()
{
    int ret = TaskRunStopProc();

    if(ret != 0)
    {
        QMessageBox::about(NULL,tr(""),tr("停止运行失败!"));
        return;
    }
    //CRunDataThread::Instance()->StopRun();

    m_listOsd_timer->stop();
    CRunDataThread::Instance()->StopThreadRun();
    QThread::msleep(200);
    ui->stackedWidget->setCurrentIndex(0);
    ui->labelPic->ClearOSD();
    TaskRunSignal(false);
    SetBtnEnable(1);
    UtilitiesFun::Instance()->SetCPT(CPT_CMOS_PIC);
    SET_SYSTEM_USER_STATUS(0);
    SetRoundOverFlag(0);
    RemoveRunLib();
}

void HomeWidget::SetBtnEnable(int flag)
{
    if(GlobalParameter::g_login == 1)
    {
        ui->groupBox->setEnabled(flag);
        ui->groupBox_2->setEnabled(flag);
        ui->btnCheck->setEnabled(flag);
        ui->btnRunCount->setEnabled(flag);
        ui->btnToolEnable->setEnabled(flag);
        ui->btnRecord->setEnabled(flag);
        ui->btnSaveTask->setEnabled(flag);
        ui->btnOpenTask->setEnabled(flag);
        ui->btnJudge->setEnabled(flag);
        ui->btnToolRename->setEnabled(flag);
        if(ui->checkBox_SimuSwitch->isChecked())
            ui->groupBox_2->setEnabled(false);
    }
    else
    {
        ui->groupBox->setEnabled(false);
        ui->groupBox_2->setEnabled(false);
        ui->btnCheck->setEnabled(false);
        ui->btnRunCount->setEnabled(false);
        ui->btnToolEnable->setEnabled(false);
        ui->btnRecord->setEnabled(false);
        ui->btnSaveTask->setEnabled(false);
        ui->btnOpenTask->setEnabled(false);
        ui->btnJudge->setEnabled(false);
    }
}

void HomeWidget::ShowRunDataSlot(QStringList info,int cnt)
{
    ui->LabelRunResult->setText(tr("任务名称:")+ui->listWidget->currentItem()->text()+"\r\n"+info[0].split("\n")[1]);
    ui->LabelResultLeft->setText(info[1]);
    ui->LabelResultRight->setText(info[2]);
    m_results_cnt = cnt;
    ui->txtPointNum->setText(QString::number(m_results_cnt));

    QVector<int> vtRunState = CRunDataThread::Instance()->GetRunState();
    int icount = vtRunState.count();
    for(int i = 0; i<icount;i++)
    {
        SetItemTextColor(i,vtRunState[i]);
    }
    int times = CRunDataThread::Instance()->GetRoundTime();
    ui->labelTime->setText(QString::number(times)+"ms");
    int iJudgeResult =  CRunDataThread::Instance()->GetJudgeResult();
    QPalette pa;
    if(iJudgeResult == 1)
    {
        pa.setColor(QPalette::WindowText,Qt::green);
        ui->labelOKNG->setPalette(pa);
        ui->labelOKNG->setText("OK");
    }else
    {
        pa.setColor(QPalette::WindowText,Qt::red);
        ui->labelOKNG->setPalette(pa);
        ui->labelOKNG->setText("NG");
    }

}
void HomeWidget::OsdUpdteSlot(QPixmap pix)
{
    ui->labelPic->SetPixMap(pix);
    QVector<int> vtRunState = CRunDataThread::Instance()->GetRunState();
    int icount = vtRunState.count();
    for(int i = 0; i<icount;i++)
    {
        SetItemTextColor(i,vtRunState[i]);
    }

}
void HomeWidget::SetItemTextColor(int index,int flag)
{
    QListWidgetItem *item = ui->listWidget->item(index);
    if(flag == RUNOK)
        item->setIcon(m_icon_ok);
    else if(flag == RUNNG)
        item->setIcon(m_icon_ng);
    else if(flag ==NORUN)
        item->setIcon(m_icon_noexcuse);

}
void HomeWidget::on_listWidget_currentRowChanged(int currentRow)
{
    CRunDataThread *run = CRunDataThread::Instance();
    run->m_current_index = currentRow+1;
    this->m_results_index = 1;
    run->m_result_index = m_results_index;
    ui->txtCurrentPoint->setText("1");
}

void HomeWidget::on_btnMatchLineUp_clicked()
{
    if(m_results_index > 1)
    {
        m_results_index--;
        CRunDataThread *run = CRunDataThread::Instance();
        run->m_result_index = m_results_index;
        ui->txtCurrentPoint->setText(QString::number(m_results_index));
    }
}

void HomeWidget::on_btnMatchLineDown_clicked()
{
    if(m_results_index < m_results_cnt)
    {
        m_results_index++;
        CRunDataThread *run = CRunDataThread::Instance();
        run->m_result_index = m_results_index;
        ui->txtCurrentPoint->setText(QString::number(m_results_index));
    }
}
void HomeWidget::SlotModifyTaskName(int bexit,QString strName)
{
    if(bexit == 1)
    {
        ui->labelTaskName->setText(strName);
        disconnect(m_TaskSaveDlg,&TaskSaveDlg::signalTaskName,this,&HomeWidget::SlotModifyTaskName);
        if(m_TaskSaveDlg != NULL)
        {
            delete m_TaskSaveDlg;
            m_TaskSaveDlg = NULL;
        }

    }else
    {
        ui->labelTaskName->setText(strName);
    }
}
void HomeWidget::on_btnSaveTask_clicked()
{
    m_TaskSaveDlg = new TaskSaveDlg();
    connect(m_TaskSaveDlg,&TaskSaveDlg::signalTaskName,this,&HomeWidget::SlotModifyTaskName);
    m_TaskSaveDlg->show();
}

void HomeWidget::on_btnOpenTask_clicked()
{
    TaskLoadDlg dlg;
    dlg.exec();
    ui->listWidget->clear();
    IniTaskListWiget();
    InitImageSetData();
    QString strName = dlg.GetFileName();

    if(strName != "")
        ui->labelTaskName->setText(strName);
}

/**
 * @brief HomeWidget::on_btnToolEnable_clicked
 * @note 工具使能
 */
void HomeWidget::on_btnToolEnable_clicked()
{
    QStringList task_list;
    task_list.clear();
    for(int i = 0 ; i < ui->listWidget->count(); i++)
    {
        task_list.append(ui->listWidget->item(i)->text());
    }
    ToolEnableDialog dlg;
    dlg.InitList(task_list);
    dlg.exec();

}


/**
 * @brief HomeWidget::on_btnToolEnable_clicked
 * @note 运行统计
 */
void HomeWidget::on_btnRunCount_clicked()
{
    QStringList task_list;
    task_list.clear();
    for(int i = 0 ; i < ui->listWidget->count(); i++)
    {
        task_list.append(ui->listWidget->item(i)->text());
    }
    RunStatistics dlg;
    dlg.InitTable(task_list);
    dlg.exec();
}


/**
 * @brief HomeWidget::on_btnToolEnable_clicked
 * @note 工具趋势图查看
 */
void HomeWidget::on_btnCheck_clicked()
{
    TendencyGraph dlg;
    dlg.exec();
}
//开启仿真模式
void HomeWidget::on_checkBox_SimuSwitch_clicked()
{
    if(ui->checkBox_SimuSwitch->isChecked())
    {
        ui->groupBox_2->setEnabled(false);
        SetSimuControl(1);
        TaskSimulateModeSet();
        InitSimulationDir();
    }else
    {
        SetSimuControl(0);
        TaskSimulateModeClear();
        ui->groupBox_2->setEnabled(true);
    }
}
void HomeWidget::SetSimuControl(int iEnable)
{
    ui->btnImageRun->setEnabled(iEnable);
    ui->btnFirst->setEnabled(iEnable);
    ui->btnPrev->setEnabled(iEnable);
    ui->btnNext->setEnabled(iEnable);
    ui->btnLast->setEnabled(iEnable);
    ui->btnImageSelect->setEnabled(iEnable);
    ui->intervalLineEdit->setEnabled(iEnable);

}
bool HomeWidget::eventFilter(QObject *watched, QEvent *event)
{
    if ((ui->intervalLineEdit->objectName() == watched->objectName()) \
            && ui->intervalLineEdit->isEnabled())
    {
        if (event->type()== QEvent::MouseButtonPress)
        {
            QDialog *dlg = m_keyBoardLib.GetNumKeyBoardDialog();
            m_keyBoardLib.SetNaturalNumberInputMode(true);
            m_keyBoardLib.SetOldNum(((QLineEdit *)watched)->text());
            int ret = dlg->exec();
            if(ret == QDialog::Accepted)
            {
                ((QLineEdit *)watched)->setText(m_keyBoardLib.GetNum());
                //m_SimulatData->SetImageSimulatTime(dlg.GetNum().toUInt());
                TaskSimulateGapTimeSet(m_keyBoardLib.GetNum().toUInt());
            }
        }
    }

    return QWidget::eventFilter(watched, event);
}
void HomeWidget::ListOsdTimeOut()
{
    ui->labelPic->ListOSD();
    //ui->labelPic->SetPixMap(CRunDataThread::Instance()->m_pix);
}

void HomeWidget::on_checkBoxSaveImage_clicked()
{
    if(ui->checkBoxSaveImage->isChecked())
    {
        ui->label_NGImageSave->setVisible(true);
        ng_pic_save_flag_set(1);
        ui->LabelOKNGSaveInfo->setVisible(true);

    }else
    {
        ui->label_NGImageSave->setVisible(false);
        ng_pic_save_flag_set(0);
        if(ui->checkBoxSaveImageOK->isChecked())
        {
            ui->LabelOKNGSaveInfo->setVisible(true);
        }else
        {
            ui->LabelOKNGSaveInfo->setVisible(false);
        }
    }
}

void HomeWidget::on_checkBoxSaveImageOK_clicked()
{
    if(ui->checkBoxSaveImageOK->isChecked())
    {
        ui->label_ImageSave->setVisible(true);
        ok_pic_save_flag_set(1);
        ui->LabelOKNGSaveInfo->setVisible(true);
    }else
    {
        ui->label_ImageSave->setVisible(false);
        ok_pic_save_flag_set(0);
        if(ui->checkBoxSaveImage->isChecked())
        {
            ui->LabelOKNGSaveInfo->setVisible(true);
        }else
        {
            ui->LabelOKNGSaveInfo->setVisible(false);
        }
    }
}

void HomeWidget::on_btnJudge_clicked()
{

    QStringList task_list;
    task_list.clear();
    for(int i = 0 ; i < ui->listWidget->count(); i++)
    {
        task_list.append(ui->listWidget->item(i)->text());
    }
    SyntheticJudgment dlg;
    dlg.InitList(task_list);
    dlg.exec();
}

void HomeWidget::on_btnImageRun_clicked()
{
    SET_SYSTEM_USER_STATUS(2);
    run_clicked();
    CRunDataThread::Instance()->m_Simulat = 1;
    simulation_run_load_pic(SIMULATION_RUN_ONE_ROUND);
}

void HomeWidget::on_btnFirst_clicked()
{
    SET_SYSTEM_USER_STATUS(2);
    run_clicked();
    CRunDataThread::Instance()->m_Simulat = 1;
    simulation_run_load_pic(SIMULATION_RUN_FIRST_PIC);
}

void HomeWidget::on_btnPrev_clicked()
{
    SET_SYSTEM_USER_STATUS(2);
    run_clicked();
    CRunDataThread::Instance()->m_Simulat = 1;
    simulation_run_load_pic(SIMULATION_RUN_PRE_PIC);
}

void HomeWidget::on_btnNext_clicked()
{
    SET_SYSTEM_USER_STATUS(2);
    run_clicked();
    CRunDataThread::Instance()->m_Simulat = 1;
    simulation_run_load_pic(SIMULATION_RUN_NEXT_PIC);
}

void HomeWidget::on_btnLast_clicked()
{
    SET_SYSTEM_USER_STATUS(2);
    run_clicked();
    CRunDataThread::Instance()->m_Simulat = 1;
    simulation_run_load_pic(SIMULATION_RUN_LAST_PIC);
}
//选择图像路径
void HomeWidget::on_btnImageSelect_clicked()
{
    SimulationSelsetDog dlg;
    dlg.SetSimulatDir(ui->label_Path->text());
    int ret = dlg.exec();
    if(ret == QDialog::Accepted)
    {
        QString dir = dlg.GetSimulatDir();
        //m_SimulatData->SelectCatalog(dir);
        ui->label_Path->setText(dir);
        BaseImageData baseImageData;
        baseImageData.SimulationRunInit(dir);
    }
}
void HomeWidget::InitSimulationDir()
{
    BaseImageData baseImageData;
    QString strName = baseImageData.GetSimulationDir();
    ui->label_Path->setText(strName);
    int iTime = TaskSimulateGapTimeGet();
    ui->intervalLineEdit->setText(QString::number(iTime));

}
void HomeWidget::InitImageSetData()
{
    int iMsExposure;
    int iUsExposure;
    int value;
    int iStartY;
    int iEndY;
    int iHeight =0;
    int m_rotate_type;
    int iGain;
    unsigned int iR;
    unsigned  int iB;
    QString strTaskPath = "/mnt/emmc2/task/tmp/ImageSet.ini";
    QFile file(strTaskPath);

    if(!file.exists())
    {
        strTaskPath = "./Config/UIIcon.ini";
        QString strPath = "/mnt/emmc2/task/tmp/ImageSet.ini";

        iMsExposure = FileIniControl::ReadSettings(strTaskPath,"imageSet","mExplosion").toInt();
        iUsExposure = FileIniControl::ReadSettings(strTaskPath,"imageSet","uExplosion").toInt();
        iStartY = FileIniControl::ReadSettings(strTaskPath,"imageSet","startY").toInt();
        iEndY =FileIniControl::ReadSettings(strTaskPath,"imageSet","endY").toInt();
        m_rotate_type = (unsigned char)FileIniControl::ReadSettings(strTaskPath,"imageSet","ImageRollovers").toInt();
        iGain = FileIniControl::ReadSettings(strTaskPath,"imageSet","gain").toInt();
        iR = FileIniControl::ReadSettings(strTaskPath,"imageSet","R").toInt();
        iB = FileIniControl::ReadSettings(strTaskPath,"imageSet","B").toInt();

        FileIniControl::WriteSettings(strPath,"imageSet","mExplosion",QString::number(iMsExposure));
        FileIniControl::WriteSettings(strPath,"imageSet","uExplosion",QString::number(iUsExposure));
        FileIniControl::WriteSettings(strPath,"imageSet","gain",QString::number(iGain));
        FileIniControl::WriteSettings(strPath,"imageSet","startY",QString::number(iStartY));
        FileIniControl::WriteSettings(strPath,"imageSet","endY",QString::number(iEndY));
        FileIniControl::WriteSettings(strPath,"imageSet","R",QString::number(iR));
        FileIniControl::WriteSettings(strPath,"imageSet","B",QString::number(iB));
        FileIniControl::WriteSettings(strPath,"imageSet","ImageRollovers",QString::number(m_rotate_type));
    }else
    {
        iMsExposure = FileIniControl::ReadSettings(strTaskPath,"imageSet","mExplosion").toInt();
        iUsExposure = FileIniControl::ReadSettings(strTaskPath,"imageSet","uExplosion").toInt();
        iStartY = FileIniControl::ReadSettings(strTaskPath,"imageSet","startY").toInt();
        iEndY =FileIniControl::ReadSettings(strTaskPath,"imageSet","endY").toInt();
        m_rotate_type = (unsigned char)FileIniControl::ReadSettings(strTaskPath,"imageSet","ImageRollovers").toInt();
        iGain = FileIniControl::ReadSettings(strTaskPath,"imageSet","gain").toInt();
        iR = FileIniControl::ReadSettings(strTaskPath,"imageSet","R").toInt();
        iB = FileIniControl::ReadSettings(strTaskPath,"imageSet","B").toInt();
    }

    value = iMsExposure*1000+iUsExposure;
    GlobalParameter::g_lib_zynq.Set_Exposure(value);
    UtilitiesFun::Instance()->SetCmosLimit(iStartY,iEndY);

    iHeight =0;
    iHeight = iEndY - iStartY;

    if(m_rotate_type == 0)
    {
        Set_HWC_CMOS_Flip(IMAGE_NORMAL);
        UtilitiesFun::Instance()->Set_rotate_type(m_rotate_type);
        UtilitiesFun::Instance()->SetCPTCmosStartYAndHeight(iStartY, iHeight, m_rotate_type);
    }
    else if(m_rotate_type == 1)
    {
        Set_HWC_CMOS_Flip(IMAGE_LEFT_RIGHT_INVERT);
        UtilitiesFun::Instance()->Set_rotate_type(m_rotate_type);
        UtilitiesFun::Instance()->SetCPTCmosStartYAndHeight(iStartY, iHeight, m_rotate_type);
    }
    else if(m_rotate_type == 2)
    {
        Set_HWC_CMOS_Flip(IMAGE_UP_DOWN_INVERT);
        UtilitiesFun::Instance()->Set_rotate_type(m_rotate_type);
        UtilitiesFun::Instance()->SetCPTCmosStartYAndHeight(480-iEndY, iHeight, m_rotate_type);
    }
    else if(m_rotate_type == 3)
    {
        Set_HWC_CMOS_Flip(IMAGE_TWO_DIR_INVERT);
        UtilitiesFun::Instance()->Set_rotate_type(m_rotate_type);
        UtilitiesFun::Instance()->SetCPTCmosStartYAndHeight(480-iEndY, iHeight, m_rotate_type);
    }
    GlobalParameter::g_lib_zynq.Set_Gain(iGain);
    White_Balance_Param_Set(MANUAL_WHITE_BALANCE,&iR,&iB);

}

void HomeWidget::InitCurTaskName()
{
    QString taskName;
    QFile file("/mnt/emmc2/task/tmp/curTaskName.bin");
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream txtInput(&file);
        taskName = txtInput.readAll();
        ui->labelTaskName->setText(taskName);
        file.close();
    }
    else
    {
        ui->labelTaskName->setText(tr("新建任务"));
    }
}

void HomeWidget::on_btnSaveImage_clicked()
{
    ui->btnSaveImage->setEnabled(false);
    QString str;
    int ret =0;
    BaseImageData baseImagedata;
    ret = baseImagedata.SaveImage(ui->labelPathSaveImg->text());
    QPalette pa;
    if(ret == 1)
    {
        str = tr("保存图片成功");
        pa.setColor(QPalette::WindowText,Qt::green);

    }else
    {
        str = tr("保存图片失败");
        pa.setColor(QPalette::WindowText,Qt::red);
    }
    ui->LabelSaveImageInfo->setPalette(pa);
    ui->LabelSaveImageInfo->setText(str);
    ui->btnSaveImage->setEnabled(true);
}

void HomeWidget::on_btnSelectImageSavePath_clicked()
{
    SimulationSelsetDog dlg;
    dlg.SetSimulatDir(ui->label_Path->text());
    int ret = dlg.exec();
    if(ret == QDialog::Accepted)
    {
        QString dir = dlg.GetSimulatDir();
        ui->labelPathSaveImg->setText(dir);
    }
}

void HomeWidget::on_btnViewImage_clicked()
{
    ImageManagemnet dlg;
    dlg.InitData();
    dlg.exec();
    UtilitiesFun::Instance()->SetCPT(CPT_CMOS_PIC);
}

void HomeWidget::on_tabWidgetResult_tabBarClicked(int index)
{
    if(index == 4)
       ui->LabelSaveImageInfo->setText("");
}

void HomeWidget::SlotRename(int index,QString strName)
{
    if(index >=0)
    {
        QListWidgetItem *item = ui->listWidget->item(index);
        item->setText(strName);
    }else
    {

        disconnect(m_RenameToolWidget,&RenameToolWidget::SignalsExit,this,&HomeWidget::SlotRename);

        if(m_RenameToolWidget != NULL)
        {
            delete m_RenameToolWidget;
            m_RenameToolWidget = NULL;
        }
    }


}
void HomeWidget::on_btnToolRename_clicked()
{
    QVector<int> vt = GlobalParameter::g_libTaskFun.Get_taskID();

    m_RenameToolWidget = new RenameToolWidget;
    connect(m_RenameToolWidget,&RenameToolWidget::SignalsExit,this,&HomeWidget::SlotRename);
    m_RenameToolWidget->SetTaskId(vt);
    m_RenameToolWidget->show();

}

void HomeWidget::on_btnRun_pressed()
{
    m_start = QTime::currentTime();
}

void HomeWidget::on_btnRun_released()
{
    m_end = QTime::currentTime();
    if(m_start.msecsTo(m_end) > 20)
        btnRun_clicked();
}
void HomeWidget::on_btnStop_pressed()
{
    m_start = QTime::currentTime();
}

void HomeWidget::on_btnStop_released()
{
    m_end = QTime::currentTime();
    if(m_start.msecsTo(m_end) > 20)
        btnStop_clicked();
}
void HomeWidget::on_checkBox_Startrun_clicked()
{
    if(ui->checkBox_Startrun->isChecked())
    {
        FileIniControl::WriteSettings("./Config/UIIcon.ini","Inferno","AutoRun","1");

    }else
    {
        FileIniControl::WriteSettings("./Config/UIIcon.ini","Inferno","AutoRun","0");
    }
    system("sync");
}



void HomeWidget::on_btnToolOsdEdit_clicked()
{
    RunOsdStyleDlg dlg;
    dlg.InitVtEnable(ui->listWidget);
    dlg.SetLable(ui->labelPic);
    CRunDataThread::m_thread_time = 50;

    if(m_listOsd_timer->isActive())
    {
        m_listOsd_timer->stop();
        m_listOsd_timer->start(30);
    }

    dlg.exec();
    CRunDataThread::m_thread_time = 15;

    if(m_listOsd_timer->isActive())
    {
        m_listOsd_timer->stop();
        m_listOsd_timer->start(1);
    }
}
void HomeWidget::AddRunLib()
{
    QVector<int> vt = GlobalParameter::g_libTaskFun.Get_taskID();
    CRunDataThread *run = CRunDataThread::Instance();
    connect(run,&CRunDataThread::SignalsRunData,this,&HomeWidget::ShowRunDataSlot,Qt::QueuedConnection);
    connect(run,&CRunDataThread::SignalsOver,this,&HomeWidget::SlotOver,Qt::QueuedConnection);
    run->DeleteVtLib();

    for(int i =0; i<vt.count();i++)
    {
        int taskId = vt[i];
        BaseLibInterface *toolibfun = new UIToolLibFun;
        QString strLibName = GlobalParameter::m_ID_LibName_hash.value(taskId);
        toolibfun->IniLib(strLibName);
        run->m_vt_lib.append(toolibfun);
    }
    ui->labelPic->SetLibVt(CRunDataThread::Instance()->m_vt_lib);
}
void HomeWidget::RemoveRunLib()
{

    CRunDataThread *run = CRunDataThread::Instance();
    disconnect(run,&CRunDataThread::SignalsRunData,this,&HomeWidget::ShowRunDataSlot);
    disconnect(run,&CRunDataThread::SignalsOver,this,&HomeWidget::SlotOver);
    run->DeleteVtLib();

}
