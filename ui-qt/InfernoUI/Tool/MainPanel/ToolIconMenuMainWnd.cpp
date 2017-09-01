#include "ToolIconMenuMainWnd.h"
#include "ui_ToolIconMenuMainWnd.h"
#include "ToolMainTypeDialog.h"
//#include "TaskMainToolEditDlg.h"
#include "TaskListStepWidget.h"
#include "BusinessData/RunData/CRunDataThread.h"
#include "BusinessData/InterfaceLib/BaseImageData.h"
#include <qdebug.h>
#include <QMessageBox>
#include <QScrollBar>
#include "Comm/FileIniControl.h"
#include "Comm/GlobalParameter.h"
#include "../Global/UtilitiesFun.h"
#include "TaskGlobal.h"
#include "LearnOneRoundDialog.h"
#include <QThread>
ToolIconMenuMainWnd::ToolIconMenuMainWnd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ToolIconMenuMainWnd)
{
    ui->setupUi(this);
    m_TaskMainToolEditDlg = NULL;
    m_execute = 0;
    ui->taskListWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    InitTaskList();

    //UtilitiesFun::Instance()->SetCPT(CPT_DDR_PIC);
    //UtilitiesFun::Instance()->ListVGA(ui->labelPic->x(),ui->labelPic->y());

    m_i_add = 0;
    CRunDataThread *run = CRunDataThread::Instance();
    //connect(run,&CRunDataThread::SignalsSingleExcute,this,&ToolIconMenuMainWnd::SingleExcuteSlot,Qt::BlockingQueuedConnection);
    //connect(run,&CRunDataThread::OsdUpdateSignal,this,&ToolIconMenuMainWnd::OsdUpdteSlot,Qt::BlockingQueuedConnection);
    connect(run,&CRunDataThread::SignalsSingleExcute,this,&ToolIconMenuMainWnd::SingleExcuteSlot);
    connect(run,&CRunDataThread::OsdUpdateSignal,this,&ToolIconMenuMainWnd::OsdUpdteSlot);
    //m_TaskMainToolEditDlg = new TaskMainToolEditDlg;
    //connect(m_TaskMainToolEditDlg,&TaskMainToolEditDlg::SignalExit,this,&ToolIconMenuMainWnd::ExitSlot);
    LoadToolBasicImage();
}

ToolIconMenuMainWnd::~ToolIconMenuMainWnd()
{
     CRunDataThread *run = CRunDataThread::Instance();
    run->DeleteVtLib();
    disconnect(this,0,0,0);
    if(m_TaskMainToolEditDlg !=NULL)
    {
        delete m_TaskMainToolEditDlg;
        m_TaskMainToolEditDlg = NULL;
    }
    delete ui;
}
QVector<QString> ToolIconMenuMainWnd::GetTaskNameVt()
{
    QVector<int> vt = GlobalParameter::g_libTaskFun.Get_taskID();
    QVector<QString>vt_name;
    QString strName = "";
    char buf[64];

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

        strName = QString::number(i+1);
        strName +=".";
        strName +=strTaskDetailName;
        vt_name.append(strName);
    }
    return vt_name;
}
void ToolIconMenuMainWnd::InitTaskList()
{
    char buf[64];
    QVector<int> vt = GlobalParameter::g_libTaskFun.Get_taskID();
    for(int i =0; i<vt.count();i++)
    {
        int taskId = vt[i];
        QString strTaskLib = GlobalParameter::m_ID_LibName_hash.value(taskId);
        QString strTaskDetailName = GlobalParameter::m_tool_name_hash.value(taskId);
        memset(buf,0,sizeof(buf));
        int ret = Task_Step_Alias_Get(i+1,64,buf);
        if (ret ==0)
        {
            strTaskDetailName = QString::fromUtf8(buf);
        }

        QString strIocn = GlobalParameter::m_tool_Icon_hash.value(taskId);
        QString strFunLib = GlobalParameter::m_tool_FunLib_hash.value(taskId,strFunLib);
        QString strName = QString::number(i+1);
        strName +=".";
        strName +=strTaskDetailName;
        AddStepItem(taskId,strName,strTaskLib,strIocn,strFunLib);
    }
}
void ToolIconMenuMainWnd::on_toolViewBtn_clicked()
{
    int count = ui->taskListWidget->count();
    if(count == 0)
    {
        SetNgResetFlag(1);
        SetSynthJudgeNgResetFlag(1);

    }
    ToolMainTypeDialog dlg;
    dlg.exec();
    m_i_add = 1;

    m_template_flag = GlobalParameter::m_template_flag.value(dlg.GetTaskId());
    if (dlg.m_btn_operation == 1)
    {
        m_execute =0;
        CRunDataThread::Instance()->DeleteVtLib();
        // 插入步骤
        if (count == 0)
        {
            m_current_index = 0;
        }else
        {
            m_current_index = ui->taskListWidget->currentRow();
        }

        if(GlobalParameter::g_libTaskFun.TaskList_AddStep_Proc(m_current_index + 1, dlg.GetTaskId(),m_template_flag)==0)
        {
            ui->taskListWidget->clear();

            QString m_taskNameOrigin = GlobalParameter::m_tool_name_hash.value(dlg.GetTaskId());
            const char *buf = m_taskNameOrigin.toUtf8().data();
            Task_Step_Alias_Set(m_current_index + 1, buf);

            InitTaskList();
            ui->taskListWidget->setCurrentRow(m_current_index);

            on_stepEditBtn_clicked();
        }
    }
    else if (dlg.m_btn_operation == 2)
    {
        m_execute =0;
        CRunDataThread::Instance()->DeleteVtLib();
        // 追加步骤
        AddStepToTaskListWidget(count + 1, dlg.GetTaskId(),dlg.m_task_name,dlg.m_lib_path,dlg.m_icon_path,dlg.m_fun_lib_path);
        on_stepEditBtn_clicked();
    }
    m_i_add = 0;
}
void ToolIconMenuMainWnd::on_stepEditBtn_clicked()
{
    int row = ui->taskListWidget->currentRow();
    if(row >=0)
    {
        QListWidgetItem* mItem = ui->taskListWidget->item(row);
        QWidget *qWidget = ui->taskListWidget->itemWidget(mItem);
        int taskId = ((TaskListStepWidget*)qWidget)->m_step_type;
        QString libPath = ((TaskListStepWidget*)qWidget)->m_lib_path;
        QString libFunPath = ((TaskListStepWidget*)qWidget)->m_fun_lib_path;
        QString taskName = ((TaskListStepWidget*)qWidget)->GetStepName();
        //TaskMainToolEditDlg dlg;
        //m_TaskMainToolEditDlg = new TaskMainToolEditDlg;
        m_TaskMainToolEditDlg = new TaskMainToolEditDlg;
        connect(m_TaskMainToolEditDlg,&TaskMainToolEditDlg::SignalExit,this,&ToolIconMenuMainWnd::ExitSlot);
        m_current_index = ui->taskListWidget->currentRow();
        m_TaskMainToolEditDlg->m_task_step = this->m_current_index+1;
        m_TaskMainToolEditDlg->m_task_id = taskId;
        m_TaskMainToolEditDlg->m_lib_path = libPath;
        m_TaskMainToolEditDlg->m_fun_lib_path = libFunPath;
        int index = taskName.indexOf(".");
        QString strName = taskName.right(taskName.length()-index-1);
        m_TaskMainToolEditDlg->m_taskName = strName;
        m_TaskMainToolEditDlg->m_i_add = this->m_i_add;
        QVector<QString> vtName = GetTaskNameVt();
        m_TaskMainToolEditDlg->vt_name = vtName;
        int  ret = m_TaskMainToolEditDlg->IniData();
        if(ret == 0)
        {
            return;
        }
        m_TaskMainToolEditDlg->show();
        //dlg.exec();
        /*UtilitiesFun::Instance()->ListVGA(ui->labelPic->x(),ui->labelPic->y());
        UtilitiesFun::Instance()->SetCPT(CPT_DDR_PIC);*/
    }
}

void ToolIconMenuMainWnd::ExitSlot()
{

    UtilitiesFun::Instance()->ListVGA(ui->labelPic->x(),ui->labelPic->y());
    UtilitiesFun::Instance()->SetCPT(CPT_DDR_PIC);
    int row = ui->taskListWidget->currentRow();

    QString strName;
    char buf[64];
    if(row >=0)
    {
        QListWidgetItem* mItem = ui->taskListWidget->item(row);
        QWidget *qWidget = ui->taskListWidget->itemWidget(mItem);

        memset(buf,0,sizeof(buf));
        int ret = Task_Step_Alias_Get(row+1,sizeof(buf),buf);

        if (ret ==0)
        {
            strName = QString::fromUtf8(buf);
            ((TaskListStepWidget*)qWidget)->SetStepName(QString::number(row+1)+"."+strName);

        }


    }
    if(m_TaskMainToolEditDlg !=NULL)
    {
        disconnect(m_TaskMainToolEditDlg,&TaskMainToolEditDlg::SignalExit,this,&ToolIconMenuMainWnd::ExitSlot);
        delete m_TaskMainToolEditDlg;
        m_TaskMainToolEditDlg = NULL;
    }

}
void ToolIconMenuMainWnd::AddStepToTaskListWidget(int stepIndex,
                                                  int stepType,
                                                  QString strName,
                                                  QString strPath,
                                                  QString strIcon,
                                                  QString libFunPaht)
{
    if(GlobalParameter::g_libTaskFun.TaskList_AddStep_Proc(stepIndex,stepType,m_template_flag)==0)
    {
        QString strTaskName = QString::number(stepIndex);
        strTaskName +=".";
        strTaskName +=strName;
        AddStepItem(stepType,strTaskName,strPath,strIcon,libFunPaht);
    }
}
void ToolIconMenuMainWnd::AddStepItem(int stepType,
                                      QString strName,
                                      QString strPath,
                                      QString strIcon,
                                      QString libFunPaht)
{
    int count = ui->taskListWidget->count();
    TaskListStepWidget *newItem = new TaskListStepWidget;
    newItem->SetStepIcon(strIcon);
    newItem->SetStepStatus("background-color:gray");
    newItem->SetStepName(strName);
    newItem->m_lib_path = strPath;
    newItem->m_step_type = stepType;
    newItem->m_fun_lib_path = libFunPaht;
    QListWidgetItem* mItem = new QListWidgetItem(ui->taskListWidget);
    ui->taskListWidget->setItemWidget(mItem,(QWidget*)newItem);
    ui->taskListWidget->item(count)->setSizeHint(QSize(140,110));
    ui->taskListWidget->setCurrentRow(ui->taskListWidget->count()-1);
}

void ToolIconMenuMainWnd::on_taskListWidget_clicked(const QModelIndex &index)
{
    if(m_execute ==1)
    {
        ui->txtCurrentPoint->setText("1");
        int results_index = ui->txtCurrentPoint->text().toInt();
        CRunDataThread *run = CRunDataThread::Instance();
        run->m_result_index = results_index;
        int currentRow = ui->taskListWidget->currentRow();

        if(currentRow <0)
            currentRow = 0;
        ui->labelExcuteData->SetCurrentIndex(results_index);
        TaskListStepWidget *tmpItem = static_cast<TaskListStepWidget *>(ui->taskListWidget->itemWidget(ui->taskListWidget->item(currentRow)));
        QString strName = tmpItem->GetStepName();
        ui->stepNameLabel->setText(strName);
        run->m_current_index = currentRow+1;
        run->ChangeStepData();
    }/*else
    {
        StepExcecute();
    }*/
    LoadToolBasicImage();
}
//删除
void ToolIconMenuMainWnd::on_stepDeleteBtn_clicked()
{
    int selectedIndex = 0;
    int index = ui->taskListWidget->currentRow();
    int cnt = ui->taskListWidget->count();

    if (index < 0)
    {
        QMessageBox::about(NULL, tr("警告"), tr("请选择要删除的步骤!"));
        return ;
    }
    QMessageBox::StandardButton rb = QMessageBox::warning(NULL, tr("警告"), tr("确定删除第%1步?").arg(index+1), QMessageBox::Yes | QMessageBox::No,  QMessageBox::No);
    if(rb == QMessageBox::Yes)
    {
        if(GlobalParameter::g_libTaskFun.TaskList_DelStep_Proc(index+1)<0)
        {
            QMessageBox::warning(NULL, tr("警告"), tr("删除失败!"), QMessageBox::Ok,  QMessageBox::Ok);
            return;
        }
        m_execute =0;
        if (index == 0)
        { // 删除的是首项
            if (cnt > 1)
            {
                m_current_index = 0;
                selectedIndex = m_current_index + 1;
            }

        }
        else if (index == (cnt - 1))
        { // 删除的是末项
            if (cnt > 1)
            {
                m_current_index = cnt - 2;
                selectedIndex = m_current_index + 1;
            }
        }
        else
        { // 删除的是中间项
            m_current_index = index;
            selectedIndex = m_current_index + 1;
        }
        ui->taskListWidget->takeItem(index);
        //重新设置步骤名
        for(int i= 0; i<ui->taskListWidget->count();i++)
        {
            QListWidgetItem* mItem = ui->taskListWidget->item(i);
            QWidget *qWidget = ui->taskListWidget->itemWidget(mItem);
            QString taskName = ((TaskListStepWidget*)qWidget)->GetStepName();
            int i_index = taskName.indexOf(".");
            QString strName = taskName.right(taskName.length()-i_index-1);
            QString strStepName = QString::number(i+1);
            strStepName +=".";
            strStepName +=strName;
            ((TaskListStepWidget*)qWidget)->SetStepName(strStepName);
        }
    }
}
//清空
void ToolIconMenuMainWnd::on_clearTaskBtn_clicked()
{
    int cnt = ui->taskListWidget->count();
    if (cnt == 0)
        return ;

    QMessageBox::StandardButton rb = QMessageBox::warning(NULL, tr("警告"),tr("清空所有步骤?"), QMessageBox::Yes | QMessageBox::No,  QMessageBox::No);
    if(rb == QMessageBox::Yes)
    {
        int ret = GlobalParameter::g_libTaskFun.TaskClear_Proc();
        if(ret < 0)
        {
            QMessageBox::warning(NULL, tr("警告"), tr("清空任务失败!"), QMessageBox::Ok,  QMessageBox::Ok);
            return;
        }
        ui->taskListWidget->clear();
    }
}
//向前翻页
void ToolIconMenuMainWnd::on_btnPrevPage_clicked()
{
    int curPos = ui->taskListWidget->horizontalScrollBar()->value();
    int movPos = curPos - 5;
    if (movPos < 0)
    {
        movPos = 0;
    }
    ui->taskListWidget->horizontalScrollBar()->setSliderPosition(movPos);
    LoadToolBasicImage();
}
//向后翻页
void ToolIconMenuMainWnd::on_btnNextPage_clicked()
{
    int curPos = ui->taskListWidget->horizontalScrollBar()->value();
    int movPos = curPos + 5;
    int maxPos = ui->taskListWidget->horizontalScrollBar()->maximum();
    if (movPos > maxPos)
    {
        movPos = maxPos;
    }
    ui->taskListWidget->horizontalScrollBar()->setSliderPosition(movPos);
    LoadToolBasicImage();
}
int ToolIconMenuMainWnd::CheckTaskParamInvalidInfo()
{
    //运行前步骤参数检查
    unsigned int i_step_total = ui->taskListWidget->count();
    if(i_step_total == 0)
    {
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
        return 0;
    }
    return 1;
}
void ToolIconMenuMainWnd::StepExcecute()
{
    SetRoundOverFlag(0);
    SetControlEnable(0);
    int ret = CheckTaskParamInvalidInfo();
    if(ret == 1)
    {
        m_execute = 1;
        TaskExecNRound(1);
        InitStepExcuteLib();
        int currentRow = ui->taskListWidget->currentRow();

        if(currentRow <0)
            currentRow = 0;
        CRunDataThread::Instance()->m_current_index = currentRow+1;
        CRunDataThread::Instance()->m_result_index = ui->txtCurrentPoint->text().toInt();
        CRunDataThread::Instance()->SetSetpCnt(ui->taskListWidget->count());
        CRunDataThread::Instance()->StartSingleRun(ui->taskListWidget->count());
    }else
    {
        TaskRunSignal(0);
    }
    SetControlEnable(1);
}
void ToolIconMenuMainWnd::OsdUpdteSlot(QPixmap pix)
{
    TaskRunSignal(0);
    ui->labelPic->SetPixMap(pix);
}
void ToolIconMenuMainWnd::SingleExcuteSlot(QVector<STRU_KEY_VALUE> vtHead,QVector<STRU_KEY_VALUE> vtBody,int cnt,QVector<QVector<STRU_KEY_VALUE> >vt)
{
    ui->labelExcuteData->SetSingleData(vtHead,vtBody);
    int index = ui->txtCurrentPoint->text().toInt()-1;
    int iJudgeResult =  CRunDataThread::Instance()->GetJudgeResult();
    int iRoundTime = CRunDataThread::Instance()->GetRoundTime();
    if(iJudgeResult == 1)
    {
        SetStatusLabelOK();
    }else
    {
        SetStatusLabelNG();
    }
    ui->oneRoundTimeLabel->setText(QString::number(iRoundTime)+"ms");

    if(vtHead.count() >=5)
    {
        ui->stepExecuteTimeLabel->setText(vtHead[4].strValue);
        ui->txtPointNum->setText(QString::number(cnt));
    }
    int headCount = vt.count();

    for(int i = 0;i<headCount;i++)
    {
        QVector<STRU_KEY_VALUE> vt_temp = vt[i];

        if(vt_temp.count() >= 5)
        {
            if(vt_temp[1].strValue == "OK")
            {
                UpdateListItemsStatus(i,1);

            }else
            {                
                UpdateListItemsStatus(i,0);
            }
        }
    }

}
void ToolIconMenuMainWnd::InitStepExcuteLib()
{
    QVector<int> vt = GlobalParameter::g_libTaskFun.Get_taskID();
    CRunDataThread *run = CRunDataThread::Instance();
    run->DeleteVtLib();

    for(int i =0; i<vt.count();i++)
    {
        int taskId = vt[i];
        BaseLibInterface *toolibfun = new UIToolLibFun;
        QString strLibName = GlobalParameter::m_ID_LibName_hash.value(taskId);
        toolibfun->IniLib(strLibName);
        run->m_vt_lib.append(toolibfun);
    }
}
void ToolIconMenuMainWnd::SetStatusLabelOK()
{
    ui->stepStatusLabel->setText(tr("OK"));
    ui->stepStatusLabel->setStyleSheet("background-color:rgb(0, 255, 0);");
}

void ToolIconMenuMainWnd::SetStatusLabelNG()
{
    ui->stepStatusLabel->setText(tr("NG"));
    ui->stepStatusLabel->setStyleSheet("background-color:rgb(255, 0, 0);");
}

void ToolIconMenuMainWnd::SetStatusLabelNone()
{
    ui->stepStatusLabel->setText(tr("--"));
    ui->stepStatusLabel->setStyleSheet("background-color:rgb(144, 144, 144);");
}

void ToolIconMenuMainWnd::SetExecuteTimeLabel(double exeTime)
{
    QString exeStr;
    //    qDebug() << "1 exeTime is " << exeTime << endl;
    ui->stepExecuteTimeLabel->setText(exeStr.number((exeTime / 1000), 'g', 6) + tr(" ms"));
}

void ToolIconMenuMainWnd::StepExecuteTimeLabelInit()
{
    ui->stepExecuteTimeLabel->setText(tr("----.-- ms"));
}

void ToolIconMenuMainWnd::SetOneRoundTimeLabel(double exeTime)
{
    QString exeStr;
    //    qDebug() << "2 exeTime is " << exeTime << endl;
    ui->oneRoundTimeLabel->setText(exeStr.number((exeTime), 'g', 6) + tr(" ms"));
}

void ToolIconMenuMainWnd::OneRoundTimeLabelInit()
{
    ui->oneRoundTimeLabel->setText(tr("----.-- ms"));
}
void ToolIconMenuMainWnd::UpdateListItemsStatus(int index, int ok)
{
    int count = ui->taskListWidget->count();
    if(count  > index)
    {
        TaskListStepWidget *tmpItem = static_cast<TaskListStepWidget *>(ui->taskListWidget->itemWidget(ui->taskListWidget->item(index)));
        if (tmpItem != NULL)
        {
            if (ok ==1) //执行成功
            {
                tmpItem->SetStepStatus("background-color:rgb(0, 255, 0);");
            }
            else
            {
                tmpItem->SetStepStatus("background-color:rgb(255, 0, 0);");
            }
        }
    }
}

void ToolIconMenuMainWnd::on_btnDataPre_clicked()
{
    int results_index = ui->txtCurrentPoint->text().toInt();
    if(results_index > 1)
    {
        results_index--;
        CRunDataThread *run = CRunDataThread::Instance();
        run->m_result_index = results_index;
        ui->txtCurrentPoint->setText(QString::number(results_index));
        int currentRow = ui->taskListWidget->currentRow();

        if(currentRow <0)
            currentRow = 0;
        run->m_current_index = currentRow+1;
        ui->labelExcuteData->SetCurrentIndex(results_index);
        if(m_execute ==1)
            run->ChangeStepData();
    }
}

void ToolIconMenuMainWnd::on_btnDataNext_clicked()
{
    int results_index = ui->txtCurrentPoint->text().toInt();
    int results_cnt = ui->txtPointNum->text().toInt();
    if(results_index < results_cnt)
    {
        results_index++;
        CRunDataThread *run = CRunDataThread::Instance();
        run->m_result_index = results_index;
        ui->txtCurrentPoint->setText(QString::number(results_index));

        int currentRow = ui->taskListWidget->currentRow();

        if(currentRow <0)
            currentRow = 0;
        run->m_current_index = currentRow+1;
        ui->labelExcuteData->SetCurrentIndex(results_index);
        if(m_execute ==1)
            run->ChangeStepData();
    }
}
void ToolIconMenuMainWnd::SetControlEnable(int flag)
{
    ui->btnNextPage->setEnabled(flag);
    ui->btnPrevPage->setEnabled(flag);
    ui->btnDataNext->setEnabled(flag);
    ui->btnDataPre->setEnabled(flag);
    ui->toolViewBtn->setEnabled(flag);
    ui->stepEditBtn->setEnabled(flag);
    ui->stepEditBtn->setEnabled(flag);
    ui->stepDeleteBtn->setEnabled(flag);
    ui->clearTaskBtn->setEnabled(flag);
    ui->LearnOneRound->setEnabled(flag);
}

void ToolIconMenuMainWnd::on_LearnOneRound_clicked()
{
    QStringList task_list;
    for(int i = 0; i < ui->taskListWidget->count(); i++)
    {
        TaskListStepWidget *tmpItem = static_cast<TaskListStepWidget *>(ui->taskListWidget->itemWidget(ui->taskListWidget->item(i)));
        QString strName = tmpItem->GetStepName();
        task_list.append(strName);
    }
    LearnOneRoundDialog dlg;
    dlg.InitUISlot(task_list);
    dlg.exec();
}
void ToolIconMenuMainWnd::LoadToolBasicImage()
{
    BaseImageData baseImageData;
    QString strName;
    int row = ui->taskListWidget->currentRow();
    if(row >= 0)
    {
        UtilitiesFun::Instance()->SetCPT(CPT_DDR_PIC);
        UtilitiesFun::Instance()->ListVGA(ui->labelPic->x(),ui->labelPic->y());
        QThread::usleep(500);
        strName = baseImageData.GetStepMsFileNameValue(row +1);
        baseImageData.LoadBaseImage(strName);

    }else
    {
        UtilitiesFun::Instance()->SetCPT(CPT_DDR_PIC);
        UtilitiesFun::Instance()->ListVGA(ui->labelPic->x(),ui->labelPic->y());
        baseImageData.LoadBaseImage("\0");
        /*
        UtilitiesFun::Instance()->SetCPT(CPT_DDR_PIC);
        UtilitiesFun::Instance()->ListVGA(ui->labelPic->x(),UtilitiesFun::Instance()->GetCmosStartY()+ui->labelPic->y());*/
    }

}




