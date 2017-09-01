#ifndef UTILITIESFUN_H
#define UTILITIESFUN_H

#include <QObject>
#include <QPushButton>
#include <QTime>
#include <QTimer>
#include <QVector>
#include <QPushButton>
#define CPT_CMOS_PIC 0
#define CPT_DDR_PIC  1

class UtilitiesFun : public QObject
{
    Q_OBJECT
public:
    ~UtilitiesFun();

    static UtilitiesFun * Instance();
    void StartTimer(int time =100);
    void ListVGA(int x,int y,int edited_status = 0xffffffff);
    void StopTimer();
    void SetCPT(int flag,int x=0,int y=0,int w=640,int h=480);
    void Set_rotate_type(int type);
    void SetStartX(int x);
    void SetStartY(int y);
    void SetEndX(int x);
    void SetEndY(int y);
    void SetCptType(int type);
    void SetCmosLimit(int starty,int endy);
    int GetStartX(){return m_startx;}
    int GetEndX(){return m_endx;}
    int GetStartY(){return m_starty;}
    int GetEndY(){return m_endy;}
    int GetCmosStartY(){return m_cmos_starty;}
    int GetCmosEndY(){return m_coms_endy;}
    int GetRotateType(){return m_rotate_type;}

    void SetCPTCmosStartYAndHeight(int startx,int hegith,int type);
    QTimer *timerUpData;
public slots:
    void timeOutSlot();
private:
    explicit UtilitiesFun(QObject *parent = 0);
signals:
    void signalValue(int value);
private:

    int m_iPresstimes;
    int m_current;
    static UtilitiesFun *m_UtilitiesFun;
    int m_startx;
    int m_starty;
    int m_endx;
    int m_endy;
    int m_cmos_starty;
    int m_coms_endy;
    int m_rotate_type;
    int m_cpt_type;

};

#endif // UTILITIESFUN_H
