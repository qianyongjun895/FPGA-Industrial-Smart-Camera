#include "CRunDataThread.h"
#include <qdebug.h>
#include <QPainter>
#include <QTime>
#include "Comm/OSDStyle.h"
#include "TaskStepGlobal.h"
#include "BlockInfo.h"
#include "TaskHeaderGlobal.h"
#include "image_include/ImageSimulationGlobal.h"

CRunDataThread* CRunDataThread::m_runData = NULL;
int CRunDataThread::m_thread_time = 15;
CRunDataThread::CRunDataThread(QObject *parent) : QThread(parent)
{
    m_Simulat = 0;
    m_timer = new QTimer;
    m_current_index = 1;
    m_result_index = 1;
}
CRunDataThread* CRunDataThread::Instance()
{
    if(m_runData == NULL)
    {
        m_runData = new CRunDataThread;
    }
    return m_runData;
}
CRunDataThread::~CRunDataThread()
{
    if(m_runData !=NULL)
    {
        delete m_runData;
        m_runData = NULL;
    }
    if(m_timer != NULL)
    {
        delete m_timer;
        m_timer = NULL;
    }
}
void CRunDataThread::SetSetpCnt(int step_cnt)
{
    this->m_step_cnt = step_cnt;
}
void CRunDataThread::StartSingleRun(int step_cnt, int time )
{
    m_step_cnt = step_cnt;
    if(!m_timer->isActive())
    {
        m_times = 0;
        connect(m_timer,SIGNAL(timeout()),this,SLOT(SlotSingleRun()));
        m_timer->start(time);
    }
}
void CRunDataThread::StopSingleRun()
{
    if(m_timer->isActive())
    {
        m_timer->stop();
        disconnect(m_timer,SIGNAL(timeout()),this,SLOT(SlotSingleRun()));
    }
}
void CRunDataThread::StartStepEditRun(int step_cnt, int time)
{
    m_step_cnt = step_cnt;
    if(!m_timer->isActive())
    {
        m_times = 0;
        connect(m_timer,SIGNAL(timeout()),this,SLOT(SlotStepEditRun()));
        m_timer->start(time);
    }
}
void CRunDataThread::StopStepEditRun()
{
    if(m_timer->isActive())
    {
        m_timer->stop();
        disconnect(m_timer,SIGNAL(timeout()),this,SLOT(SlotStepEditRun()));
    }
}
int CRunDataThread::JudeSimulatRunOver()
{
    if(m_Simulat == 1)
    {
        unsigned int ret = simulation_pic_load_over_get();

        if(ret == 0)
        {
           m_b_thread= false;
           SignalsOver();
        }
    }
}
void CRunDataThread::run()
{
    int count = m_vt_lib.count();
    m_vt_run_state.clear();
    m_vt_ok_ng_num.clear();
    for(int i=0;i<count;i++)
    {
        m_vt_run_state.append(NORUN);
        STRU_KEY_VALUE stru_value;
        stru_value.strName = "";
        stru_value.strValue = "";
        m_vt_ok_ng_num.append(stru_value);
    }

    m_b_thread = true;
    while(m_b_thread)
    {
        DealThreadData();
        QThread::msleep(CRunDataThread::m_thread_time);
        JudeSimulatRunOver();
    }
}
void CRunDataThread::StopThreadRun()
{
    this->m_b_thread = false;
}
void CRunDataThread::DealThreadData()
{
    int flag =GetRuondOverFlag();
    if(flag == 1)
    {
       m_iRoundCostTime = GetTaskRoundCostTime();
       m_JudgeResult= GetSynthJudgeResult();
        int i_block_reason = BlockReasonGet();
        switch (i_block_reason) {
        case IO_SIGINAL_BLOCK:
            break;
        case CMD_BLOCK:
            break;
        case DELAY_BLOCK:

            break;
        case TASK_STOP_BLOCK:
            m_b_thread= false;
            break;
        case COND_TRIGGER:

            break;
        case SAVE_PIC_BLOCK:
            break;
        default:
            break;
        }
        QVector<STRU_KEY_VALUE> vt_head_value;
        QVector<STRU_KEY_VALUE> vt_body_value;
        int StepCnt=1;
        int cnt = 1;
        for(int  i=0 ;i<m_step_cnt;i++)
        {
            UIToolLibFun * libFun = (UIToolLibFun * )m_vt_lib[i];
            QVector<STRU_KEY_VALUE> vt_head = libFun->GetHead(i+1);
            QVector<STRU_KEY_VALUE> vt_body = libFun->GetContent(i+1,m_result_index,&StepCnt);
            //libFun->Paint(&paint,i+1);
            JudgeRunState(vt_head,i);
            if(m_current_index == i+1)
            {
                vt_head_value = vt_head;
                vt_body_value = vt_body;
                cnt = StepCnt;
            }
        }
        SignalsRunData(SetRunInfo(vt_head_value,vt_body_value),cnt);
        SetRoundOverFlag(0);
    }
}
void CRunDataThread::JudgeRunState(QVector<STRU_KEY_VALUE> vt_head,int i)
{
    if(vt_head.count() >=5 )
    {
        if(m_vt_ok_ng_num[i].strName == vt_head[2].strValue  \
           && m_vt_ok_ng_num[i].strValue == vt_head[3].strValue)
        {
            m_vt_run_state[i] = NORUN;
        }else
        {
            if(m_vt_ok_ng_num[i].strName != vt_head[2].strValue)
            {
                m_vt_run_state[i] = RUNOK;
                m_vt_ok_ng_num[i].strName = vt_head[2].strValue;
                m_vt_ok_ng_num[i].strValue = vt_head[3].strValue;
            }else
            {
                m_vt_run_state[i] = RUNNG;
                m_vt_ok_ng_num[i].strName = vt_head[2].strValue;
                m_vt_ok_ng_num[i].strValue = vt_head[3].strValue;
            }
        }

    }else
    {
        m_vt_run_state[i] = NORUN;
    }
}
void CRunDataThread::ChangeStepData()
{
    QPixmap pix(640,480);
    pix.fill(Qt::transparent);
    QPainter paint(&pix);
    int cnt = 1;

    QVector<QVector<STRU_KEY_VALUE> >vt;
    QVector<STRU_KEY_VALUE>vt_head_value;
    QVector<STRU_KEY_VALUE>vt_body_value;
    int stepCount = 1;
    for(int  i=0 ;i<m_step_cnt;i++)
    {
        UIToolLibFun * libFun = (UIToolLibFun * )m_vt_lib[i];
        QVector<STRU_KEY_VALUE> vt_head = libFun->GetHead(i+1);
        QVector<STRU_KEY_VALUE> vt_body = libFun->GetContent(i+1,m_result_index,&cnt);
        vt.append(vt_head);

        if(m_current_index == i+1)
        {
            libFun->Paint(&paint,i+1,OSDStyle::GetPenStyleAddr());
            vt_head_value = vt_head;
            vt_body_value = vt_body;
            stepCount = cnt;
        }
    }
    SignalsSingleExcute(vt_head_value,vt_body_value,stepCount,vt);
    OsdUpdateSignal(pix);
}
void CRunDataThread::DealSingleStepData()
{
    int flag =GetRuondOverFlag();
    m_times++;
    if(m_times >10)
    {
        QPixmap pix(640,480);
        pix.fill(Qt::transparent);
        StopSingleRun();
        SetRoundOverFlag(0);
        OsdUpdateSignal(pix);
    }
    if(flag == 1)
    {
        m_iRoundCostTime = GetTaskRoundCostTime();
        m_JudgeResult= GetSynthJudgeResult();
        ChangeStepData();
        StopSingleRun();
        SetRoundOverFlag(0);
    }
}
void CRunDataThread::SlotSingleRun()
{
    DealSingleStepData();
}
void CRunDataThread::SlotStepEditRun()
{
    QPixmap pix(640,480);
    pix.fill(Qt::transparent);
    int flag =GetRuondOverFlag();
    m_times++;
    if(m_times >10)
    {
        StopStepEditRun();
        SetRoundOverFlag(0);
        OsdUpdateStepEdit(pix);
    }
    if(flag == 1)
    {
        QPainter paint(&pix);
        int cnt = 1;
        for(int  i=0 ;i<m_step_cnt;i++)
        {
            UIToolLibFun * libFun = (UIToolLibFun * )m_vt_lib[i];
            libFun->GetHead(i+1);
            libFun->GetContent(i+1,m_result_index,&cnt);
            if(m_current_index == i+1)
            {
                libFun->Paint(&paint,i+1,OSDStyle::GetPenStyleAddr());
            }
        }
        StopStepEditRun();
        SetRoundOverFlag(0);
        OsdUpdateStepEdit(pix);
    }
}
void CRunDataThread::DeleteVtLib()
{
    int count = m_vt_lib.count();
    int i= 0;
    for(i = 0; i<count;i++)
    {
        int row =  m_vt_lib.count() -1 ;
        delete (UIToolLibFun*)m_vt_lib[row];
        m_vt_lib[row] = NULL;
        m_vt_lib.erase(m_vt_lib.begin()+row);
    }
}

QStringList CRunDataThread::SetRunInfo(QVector<STRU_KEY_VALUE> vt_head,QVector<STRU_KEY_VALUE> vt_body)
{
    QStringList DataList;
    QString HeadInfo = "";
    QString LeftInfo = "";
    QString RightInfo = "";
    int i = 0;
    for(i = 0; i < vt_head.count();i++)
    {
        if(i < 2)
        {
            HeadInfo += vt_head[i].strName;
            HeadInfo += vt_head[i].strValue;
        }else
        {
            HeadInfo += "  "+vt_head[i].strName;
            HeadInfo += vt_head[i].strValue;
        }
    }
    DataList.append(HeadInfo);
    for(i = 0; i < vt_body.count();i++)
    {
        if(i%2 == 0)
        {
            LeftInfo += vt_body[i].strName;
            LeftInfo += vt_body[i].strValue+"\r\n";
        }else
        {
            RightInfo += vt_body[i].strName;
            RightInfo += vt_body[i].strValue+"\r\n";
        }
    }
    DataList.append(LeftInfo);
    DataList.append(RightInfo);
    return DataList;
}
