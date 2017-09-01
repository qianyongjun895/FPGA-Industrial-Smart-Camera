#include "TaskMainToolEditDlg.h"
#include "ui_TaskMainToolEditDlg.h"
#include <QDebug>
#include <QMessageBox>
#include "Comm/ControlStyle.h"
#include "Comm/FileIniControl.h"
#include "Comm/MessageDlg.h"
#include "BusinessData/InterfaceLib/LibTaskFun.h"
#include "BusinessData/RunData/CRunDataThread.h"
#include "OSDColorSetDlg.h"
#include "TaskManageGlobal.h"
#include "TaskStepGlobal.h"
#include "Comm/GlobalParameter.h"
#include "CommPara/CommPara.h"
//#include "System.h"
#include "../Global/UtilitiesFun.h"
#include "BusinessData/InterfaceLib/BaseImageData.h"
#include "BasicImageSelect.h"
#include "TaskStepGlobal.h"
#include "AcceCommon.h"


TaskMainToolEditDlg::TaskMainToolEditDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TaskMainToolEditDlg)
{
    ui->setupUi(this);
    LoadLearnLib();
    m_need__ReloadModeFiles = 0;
    memset(input_bak, 0, sizeof(input_bak));
    memset(&task_step_header_bak, 0, sizeof(task_step_header_bak));
    MainViewLayout = NULL; //参数
    m_pWidget = NULL; //参数界面
    MainViewLayout_pre = NULL; //预处理
    m_pWidget_pre = NULL; //预处理界面
    MainViewLayout_RL = NULL; //关联定位
    m_pWidget_RL = NULL; //关联定位界面
    MainViewLayout_comm = NULL; //公共
    m_pWidget_comm = NULL; //公共
    ControlStyle::SetTabBar(ui->tabWidget);
    ui->tabWidget->setCurrentIndex(0);
    ui->txtPicName->installEventFilter(this);
    m_i_add = 0;
    CalcTimer = new QTimer;
    connect(CalcTimer, &QTimer::timeout, this, &TaskMainToolEditDlg::LearnTimerSlot);
    ui->labelExecPic->setVisible(false);
    m_vt_tab_index.append(0);
    m_vt_tab_index.append(1);
    m_vt_tab_index.append(2);
    m_vt_tab_index.append(3);
    connect(CRunDataThread::Instance(),&CRunDataThread::OsdUpdateStepEdit,this,&TaskMainToolEditDlg::OsdUpdteSlot);
}

TaskMainToolEditDlg::~TaskMainToolEditDlg()
{
    /*if(m_pWidget == NULL) //参数界面
    {
        delete m_pWidget;
        m_pWidget = NULL;
    }*/
    //m_ToolLibFun.ReleaseBuf();
    if(MainViewLayout == NULL)
    {
        delete MainViewLayout;
        MainViewLayout = NULL;
    }
    if(m_pWidget_pre == NULL)
    {
        delete m_pWidget_pre;
        m_pWidget_pre = NULL;
    }
    if(MainViewLayout_pre == NULL)
    {
        delete MainViewLayout_pre;
        MainViewLayout_pre = NULL;
    }
    if(m_pWidget_RL == NULL)
    {
        delete m_pWidget_RL;
        m_pWidget_RL = NULL;
    }
    if(MainViewLayout_RL == NULL)
    {
        delete MainViewLayout_RL;
        MainViewLayout_RL = NULL;
    }

    if(m_pWidget_comm == NULL)
    {
        delete m_pWidget_comm;
        m_pWidget_comm = NULL;
    }
    if(MainViewLayout_comm == NULL)
    {
        delete MainViewLayout_comm;
        MainViewLayout_comm = NULL;
    }
    ui->txtPicName->removeEventFilter(this);
    delete CalcTimer;
    delete ui;
}
void TaskMainToolEditDlg::SetListVga(int x,int y)
{
    /*SYSTEM_MODEL_CFG cfg = {0};
    System_Model_Param_Init(&cfg);
    cfg.start_x = x;
    cfg.start_y = y;
    System_Model_Param_Set(&cfg);*/
}
int TaskMainToolEditDlg::IniData()
{
    QString strName = QString::number(m_task_step);
    strName+=".";
    strName+=m_taskName;
    ui->labelTaskName->setText(strName);
    ui->tabWidget->setTabText(0,m_taskName);

    OSDColorSetDlg dlg;

    dlg.SetStep(m_task_step);

    if(m_i_add == 1)
    {
        dlg.InitLibColor();

    }else
    {
        dlg.GetDataFromLib();
    }
    AddCommWidget();

    int ret = AddParaWidget();//获取工具参数主界面

    bool bRemovePre = false;
    bool bRemoveRL = false;
    if(GlobalParameter::m_pre_num.value(this->m_task_id)> 0)
    {
        AddPreWidget();//获取预处理主界面;
    }
    else
    {
        bRemovePre = true;
    }

    if(GlobalParameter::m_link_flag.value(this->m_task_id) == 1)
    {
        AddRLWidget();//获取关联定位主界面
    }
    else
    {
        bRemoveRL = true;
    }
    if(bRemovePre)
    {
        ui->tabWidget->removeTab(1);
        m_vt_tab_index.takeAt(1);
    }
    if(bRemoveRL)
    {
        if(bRemovePre)
        {
            ui->tabWidget->removeTab(1);
            m_vt_tab_index.takeAt(1);
        }
        else
        {
            ui->tabWidget->removeTab(2);
            m_vt_tab_index.takeAt(2);
        }
    }

    //AddCommWidget();

    strName = "";
    BaseImageData baseImageData;
    m_strNameList = baseImageData.GetBaseImageDirAllName();

    if(m_i_add == 1)
    {
        for(int i= m_task_step-1;i>=1;i--)
        {
            strName = baseImageData.GetStepMsFileNameValue(i);
            if(strName !="")
                break;
        }
    }else
    {
        strName = baseImageData.GetStepMsFileNameValue(m_task_step);
    }
    ui->txtPicName->setText(strName);
    IniImageList(strName);

    if(m_pWidget_pre != NULL)
    {
        m_preLibFun.ListCptVga();
    }
    ui->tabWidget->setCurrentIndex(0);

    return ret;
}
int TaskMainToolEditDlg::AddParaWidget()
{
    LibTaskFun libFun;
    void *fun = libFun.Get_Task_Step_Input_Para(m_task_step);
    TASK_STEP_HEADER *pStepHeader = Task_Step_Head_Get(m_task_step);
    m_ToolLibFun.IniLib(m_lib_path);
    m_pWidget = m_ToolLibFun.GetToolWidget();
    OSDColorSetDlg dlg;
    m_ToolLibFun.Init_Input_Ptr(fun,m_task_step,m_i_add,dlg.GetPenColorDrr());
    memcpy(input_bak, fun, 2560);
    memcpy(&task_step_header_bak, pStepHeader, sizeof(TASK_STEP_HEADER));
    if(m_pWidget == NULL)
    {
        return 0;
    }
    MainViewLayout= new QGridLayout();
    MainViewLayout->setContentsMargins(0, 0, 0, 0);
    if(m_pWidget !=NULL)
        MainViewLayout->addWidget(m_pWidget, 0, 0);
    ui->widgetTool->setLayout(MainViewLayout);
    ui->stackedWidget->setCurrentIndex(0);
    QPoint temp = m_ToolLibFun.Get_Image_Pos();
    m_para_x = temp.x() + ui->stackedWidget->x();
    m_para_y = temp.y() + ui->stackedWidget->y();
    //SetListVga(m_para_X,m_para_y);
    if(m_para_x >= 0 && m_para_y>=0)
    {
        UtilitiesFun::Instance()->ListVGA(m_para_x,m_para_y);
        UtilitiesFun::Instance()->SetCPT(CPT_DDR_PIC);
    }
    return 1;
}
void TaskMainToolEditDlg::AddPreWidget()
{
    QString strlibPath = FileIniControl::ReadSettings("./Config/UIIcon.ini","libPath","Pretreatment");
    m_preLibFun.IniLib(strlibPath);
    m_pWidget_pre = m_preLibFun.GetPreWidget();
    MainViewLayout_pre= new QGridLayout();
    MainViewLayout_pre->setContentsMargins(0, 0, 0, 0);
    if(m_pWidget_pre !=NULL)
    {
        MainViewLayout_pre->addWidget(m_pWidget_pre, 0, 0);
    }

    ui->widgetPre->setLayout(MainViewLayout_pre);

    QVector<int> vt_pre;
    if(m_i_add == 1)
    {
        vt_pre = GlobalParameter::m_pre_value.value(this->m_task_id);
        m_preLibFun.Set_id_step(m_task_id,m_task_step,ui->stackedWidget->x(),ui->stackedWidget->y(),0,vt_pre);
    }
    else
    {
        m_preLibFun.Set_id_step(m_task_id,m_task_step,ui->stackedWidget->x(),ui->stackedWidget->y(),1,vt_pre);
    }
    OSDColorSetDlg dlg;
    m_preLibFun.SetColor(dlg.GetPenColorDrr());
    m_preLibFun.SetTaskNameVt(vt_name);
    m_preLibFun.StepAcceleratorModuleEnable();
    AcceleratorModuleParamsBackup(m_task_step);
}
void TaskMainToolEditDlg::AddCommWidget()
{
    m_pWidget_comm = new CommPara;
    ((CommPara *)m_pWidget_comm)->task_index = m_task_step;
    QString strTaskDetailName = GlobalParameter::m_tool_name_hash.value(m_task_id);
    ((CommPara *)m_pWidget_comm)->m_taskNameOrigin = strTaskDetailName;

    if(m_i_add == 1)
    {

        ((CommPara *)m_pWidget_comm)->m_strName = m_taskName;
        ((CommPara *)m_pWidget_comm)->SetTaskName();

    }else
    {
        char buf[64];
        Task_Step_Alias_Get(m_task_step, sizeof(buf),buf);
        QString strName = QString::fromUtf8(buf);
        ((CommPara *)m_pWidget_comm)->m_strName = strName;
    }
    ((CommPara *)m_pWidget_comm)->InitData();
    MainViewLayout_comm= new QGridLayout();
    MainViewLayout_comm->setContentsMargins(0, 0, 0, 0);
    if(m_pWidget_comm !=NULL)
        MainViewLayout_comm->addWidget(m_pWidget_comm, 0, 0);
    else
        qDebug()<<"MainViewLayout_RL===NULL";
    ui->widgetComm->setLayout(MainViewLayout_comm);
}
void TaskMainToolEditDlg::AddRLWidget()
{
    QString strlibPath = FileIniControl::ReadSettings("./Config/UIIcon.ini","libPath","Relation");
    qDebug()<<"strlibpa==="<<strlibPath;
    m_RLFun.IniLib(strlibPath);
    m_pWidget_RL = m_RLFun.GetRLWidget();
    m_RLFun.IniRLData(m_task_step);
    MainViewLayout_RL= new QGridLayout();
    MainViewLayout_RL->setContentsMargins(0, 0, 0, 0);
    if(m_pWidget_RL !=NULL)
        MainViewLayout_RL->addWidget(m_pWidget_RL, 0, 0);
    else
        qDebug()<<"MainViewLayout_RL===NULL";
    ui->widgetRL->setLayout(MainViewLayout_RL);
}
void TaskMainToolEditDlg::on_btnOK_clicked()
{

    BaseImageData baseImageData;
    baseImageData.LoadBaseImage(ui->txtPicName->text());
    baseImageData.SetStepMsFileNameValue(this->m_task_step,ui->txtPicName->text());

    if(GlobalParameter::m_link_flag.value(this->m_task_id) == 1)
    {
        QString strlibPath = FileIniControl::ReadSettings("./Config/UIIcon.ini","libPath","Relation");
        m_RLFun.IniLib(strlibPath);
        m_RLFun.SetRLData();
    }
//    TaskRunRstMemInit();
    int ret = m_ToolLibFun.Set_Parameter_To_Ram();
    if(ret != 1)
    {
        QMessageBox::about(this,tr("提示"),tr("参数有误，请仔细检查并修改无误后重试"));
        return;
    }
    Fun_GetLearnDialog GetDialog = (Fun_GetLearnDialog)m_Learn_Lib.resolve("GetDialog");
    QDialog *dlg = GetDialog();
    CalcTimer->start(10);
    dlg->exec();
    if(m_learn_result == 1)
    {
        QDialog::accept();
        SignalExit();
    }
    if(m_need__ReloadModeFiles ==1)
    {
       //模板剩余空间足够，但需要重新整理内存
        ;

    }
}

void TaskMainToolEditDlg::on_tabWidget_tabBarClicked(int index)
{
    //ui->stackedWidget->setCurrentIndex(index);

    if(GlobalParameter::m_link_flag.value(this->m_task_id) == 1)
    {
        QString strlibPath = FileIniControl::ReadSettings("./Config/UIIcon.ini","libPath","Relation");
        m_RLFun.IniLib(strlibPath);
        m_RLFun.SetRLData();
    }
    switch (index) {
    case 0:
        if(m_pWidget_pre != NULL)
        {
            m_preLibFun.ListCptVga();
        }
        ui->stackedWidget->setCurrentIndex(this->m_vt_tab_index.at(0));
        break;
    case 1:
        if(m_pWidget_pre != NULL)
        {
            m_preLibFun.GetImageOutPut();
        }
        ui->stackedWidget->setCurrentIndex(this->m_vt_tab_index.at(1));
        break;
    case 2:
        if(m_pWidget_pre != NULL)
        {
            m_preLibFun.ListCptVga();
        }
        ui->stackedWidget->setCurrentIndex(this->m_vt_tab_index.at(2));
        break;
    case 3:
         ui->stackedWidget->setCurrentIndex(this->m_vt_tab_index.at(3));
        break;
    default:
        break;
    }
}

void TaskMainToolEditDlg::on_btnQuit_clicked()
{
    QMessageBox::StandardButton rb = QMessageBox::warning(NULL, tr("提示"), tr("取样未完成，确定退出?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    if(rb == QMessageBox::No)
    {
        return;
    }

    LibTaskFun libFun;
    TASK_STEP_HEADER *pStepHeader = Task_Step_Head_Get(m_task_step);
    void *fun = libFun.Get_Task_Step_Input_Para(m_task_step);
    memcpy(fun, input_bak, 2560);
    memcpy(pStepHeader, &task_step_header_bak, sizeof(TASK_STEP_HEADER));
    if(m_pWidget_pre != NULL)
    {
        m_preLibFun.PreAllPreModuleDisable();
        AcceleratorModuleParamsRecover(m_task_step);
    }
    QDialog::accept();
    SignalExit();
}
bool TaskMainToolEditDlg::eventFilter(QObject *watched, QEvent *event)
{
    if(!((QLineEdit*)watched)->isEnabled() || ((QLineEdit*)watched)->isReadOnly())
        return QWidget::eventFilter(watched, event);
    if (watched == ui->txtPicName)         //首先判断控件(这里指 lineEdit1)
    {
        if (event->type()==QEvent::MouseButtonPress)
        {
            SelectImg();
            ui->comboBoxSelectImage->setCurrentIndex(1);
             UtilitiesFun::Instance()->ListVGA(m_para_x,m_para_y);
        }
    }
    return QWidget::eventFilter(watched, event);
}
void TaskMainToolEditDlg::SelectImg()
{
    BaseImageData baseImageData;
    BasicImageSelect *dlg = new BasicImageSelect();
    dlg->move(700,30);
    int ret = dlg->exec();
    if(ret == QDialog::Accepted)
    {
        ui->txtPicName->setText(dlg->m_pic_name);
        baseImageData.LoadBaseImage(dlg->m_pic_name);
        int count = m_strNameList.count();

        for(int i = 0; i<count;i++)
        {
            if(dlg->m_pic_name == m_strNameList[i])
                m_current = i;
        }
    }else
    {
        baseImageData.LoadBaseImage(ui->txtPicName->text());
    }
    delete dlg;
}
void TaskMainToolEditDlg::on_btnPrev_clicked()
{
    if(m_current < 0)
        return;
    if(m_current > 0)
    {
        m_current--;
        int count = m_strNameList.count();
        if(m_current < count)
        {
            QString strName = m_strNameList[m_current];
            ui->txtPicName->setText(strName);
            BaseImageData baseImageData;
            baseImageData.LoadBaseImage(strName);
            ui->comboBoxSelectImage->setCurrentIndex(1);
        }
    }
}

void TaskMainToolEditDlg::on_btnNext_clicked()
{
    int count = m_strNameList.count();

    if(m_current < count-1)
    {
        m_current++;
        QString strName = m_strNameList[m_current];
        ui->txtPicName->setText(strName);
        BaseImageData baseImageData;
        baseImageData.LoadBaseImage(strName);
        ui->comboBoxSelectImage->setCurrentIndex(1);
    }
}
void TaskMainToolEditDlg::IniImageList(QString strName)
{
    m_current = -1;
    int count = m_strNameList.count();

    for(int i = 0; i<count;i++)
    {
        if(strName == m_strNameList[i])
            m_current = i;
    }
    BaseImageData baseImageData;
    if(m_current == -1)
    {
        if(count > 0)
        {
            strName = m_strNameList[0];
            ui->txtPicName->setText(strName);
            baseImageData.SetStepMsFileNameValue(this->m_task_step,strName);
        }
    }
    baseImageData.LoadBaseImage(strName);
}

void TaskMainToolEditDlg::LearnTimerSlot()
{

    Fun_SetResultString SetResultString = (Fun_SetResultString)m_Learn_Lib.resolve("SetResultString");
    QString info = tr("正在取样，请稍等");
    SetResultString(info);
    int ret = TaskStepLearnProc(m_task_step);
    if(ret == 0)
    {
        Task_Step_Model_Result_Valid_Flag_Set(m_task_step);
        if(m_pWidget_pre != NULL)
        {
            m_preLibFun.PreAllPreModuleDisable();
        }
        m_ToolLibFun.Get_Result_From_Ram();
        m_learn_result = 1;
        info = tr("取样成功!");
    }else
    {
        m_learn_result = 0;
        info = tr("取样失败!")+tr("错误码:")+QString::number(ret,16);
        if(GlobalParameter::m_template_flag.value(this->m_task_id)==1)
        {
            if(ret == TASK_MODEL_MEM_UNUSED_SIZE_NOT_ENOUGH)
            {
                m_need__ReloadModeFiles = 1;
            }
        }

    }
    SetResultString(info);
    CalcTimer->stop();
}

void TaskMainToolEditDlg::LoadLearnLib()
{
    m_Learn_Lib.setFileName("libLearningDialog.so");
    if(m_Learn_Lib.isLoaded())
    {
        qDebug()<<"load libLearningDialog.so isLoaded";
        return;
    }
    if(m_Learn_Lib.load())
    {
        printf("libLearningDialog.so OK\n");
    }
    else
    {
        qDebug()<<"load libLearningDialog.so fail"<<m_Learn_Lib.errorString();
    }
}
//执行
void TaskMainToolEditDlg::on_btnExcute_clicked()
{
    StepExcecute();
    ui->labelExecPic->setVisible(true);
    ui->labelExecPic->move(m_para_x,m_para_y);
    ui->labelExecPic->setWindowFlags(Qt::WindowStaysOnTopHint);
    MessageDlg dlgWarn;
    dlgWarn.move(100,540);
    dlgWarn.exec();
    ui->labelExecPic->setVisible(false);
}
int TaskMainToolEditDlg::CheckTaskParamInvalidInfo()
{
    //运行前步骤参数检查
    //unsigned int i_step_total = ui->taskListWidget->count();
    unsigned int i_step_total = m_task_step;
    if(i_step_total == 0)
    {
        return 0;
    }
    unsigned int i_ng_step_index[256];
    unsigned int i_ng_step_cnt = GetStepParamInvalidInfo(i_ng_step_index,i_step_total);

    if(i_ng_step_cnt != 0)
    {
        bool bflag = false;
        QString str_step_info = tr("步骤");
        if(i_ng_step_cnt <= i_step_total)
        {
            unsigned int i = 0;
            for(i = 0; i < i_ng_step_cnt; i++)
            {
                if(i_ng_step_index[i] <= m_task_step)
                {
                    bflag = true;
                    str_step_info.append(QString::number(i_ng_step_index[i])+",");
                }
            }
        }
        if(bflag)
        {
            QString str_message = str_step_info.left(str_step_info.length()-1)+tr("参数不完整!");
            QMessageBox::about(NULL,tr("提示"),str_message);
            return 0;
        }else
        {
            return 1;
        }
    }
    return 1;
}
void TaskMainToolEditDlg::StepExcecute()
{
    SetRoundOverFlag(0);
    int ret = CheckTaskParamInvalidInfo();
    if(ret == 1)
    {
        qDebug()<<"m_task_step==="<<m_task_step;
        //TaskExecNRound(1);
        TaskStepExec(m_task_step);
        InitStepExcuteLib();
        CRunDataThread::Instance()->m_current_index = m_task_step;
        CRunDataThread::Instance()->m_result_index = 1;
        CRunDataThread::Instance()->SetSetpCnt(m_task_step);
        CRunDataThread::Instance()->StartStepEditRun(m_task_step);
    }
}
void TaskMainToolEditDlg::OsdUpdteSlot(QPixmap pix)
{
    ui->labelExecPic->SetPixMap(pix);
}
void TaskMainToolEditDlg::InitStepExcuteLib()
{
    QVector<int> vt = GlobalParameter::g_libTaskFun.Get_taskID();
    CRunDataThread *run = CRunDataThread::Instance();
    run->DeleteVtLib();

    for(int i =0; i<m_task_step;i++)
    {
        int taskId = vt[i];
        BaseLibInterface *toolibfun = new UIToolLibFun;
        QString strLibName = GlobalParameter::m_ID_LibName_hash.value(taskId);
        toolibfun->IniLib(strLibName);
        run->m_vt_lib.append(toolibfun);
    }
}

void TaskMainToolEditDlg::on_btnOSDSet_clicked()
{
    OSDColorSetDlg dlg;
    dlg.SetStep(m_task_step);
    //dlg.SetLabel(ui->labelPic);
    dlg.move(660,60);
    dlg.SetWidget(this->m_pWidget);
    dlg.exec();
    if(m_pWidget_pre != NULL)
    {
        m_preLibFun.SetColor(dlg.GetPenColorDrr());
    }
    this->m_pWidget->hide();
    this->m_pWidget->show();
}
