#ifndef CRUNDATATHREAD_H
#define CRUNDATATHREAD_H

#include <QObject>
#include <QTimer>
//#include "Comm/UIBasicDefine.h"
#include "BasicDefine.h"
#include <QVector>
#include <QThread>
#include <QPixmap>
//#include <stdbool.h>

#include "BusinessData/InterfaceLib/UIToolLibFun.h"

#define RUNOK 1
#define RUNNG 2
#define NORUN 0

class CRunDataThread : public QThread
{
    Q_OBJECT
public:
    ~CRunDataThread();
    void StartSingleRun(int step_cnt, int time = 30);
    void StopSingleRun();
    void StartStepEditRun(int step_cnt, int time = 30);
    void StopStepEditRun();
    void StopThreadRun();
    void SetSetpCnt(int step_cnt);
    static CRunDataThread* Instance();
    void ChangeStepData();
    void DeleteVtLib();
    QVector<BaseLibInterface *>m_vt_lib;
    int m_current_index;//任务列表焦点所在任务的索引号
    int m_result_index;//多结果任务的结果索引号
    int m_Simulat;
    int GetRoundTime(){return  m_iRoundCostTime;}
    int GetJudgeResult(){return m_JudgeResult;}
    QVector<int>GetRunState(){return m_vt_run_state;}
    QPixmap m_pix;
    static int m_thread_time;
private:
    explicit CRunDataThread(QObject *parent = 0);
    void run();
signals:
    void SignalsRunData(QStringList info,int cnt);
    void SignalsSingleExcute(QVector<STRU_KEY_VALUE> vtHead,QVector<STRU_KEY_VALUE> vtBody,int cnt,QVector<QVector<STRU_KEY_VALUE> >vt);
    void OsdUpdateSignal(QPixmap pix);
    void OsdUpdateStepEdit(QPixmap pix);
    void SignalsOver();
public slots:
    void SlotSingleRun();
    void SlotStepEditRun();
private:
    QStringList SetRunInfo(QVector<STRU_KEY_VALUE> vt_head, QVector<STRU_KEY_VALUE> vt_body);
    QTimer *m_timer;
    int m_times;
    static CRunDataThread* m_runData;
    int m_step_cnt;//任务总数
    volatile bool m_b_thread;
    int m_iRoundCostTime;
    int m_JudgeResult;
    QVector<int>m_vt_run_state;
    QVector<STRU_KEY_VALUE>m_vt_ok_ng_num;
    void DealThreadData();
    void DealSingleStepData();
    void InitPixMap();
    void JudgeRunState(QVector<STRU_KEY_VALUE> vt_head, int i);
    int JudeSimulatRunOver();

};

#endif // CRUNDATATHREAD_H
