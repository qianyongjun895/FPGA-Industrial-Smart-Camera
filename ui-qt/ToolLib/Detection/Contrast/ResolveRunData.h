#ifndef RESOLVERUNDATA_H
#define RESOLVERUNDATA_H
#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QLabel>
#include <QVector>
#include "../../BasicDefine.h"
#include "TaskStepGlobal.h"
#include "TaskRstGlobal.h"
#include "ContrastGlobal.h"

class ResulveRunData
{
public:
    explicit ResulveRunData();
    ~ResulveRunData();
    void Paint(QPainter *paint,int step,void *penStyle,int paintAreaSelect);
    QVector<STRU_KEY_VALUE> GetHead(int step);
    QVector<STRU_KEY_VALUE> GetContent(int step, int index, int *count);
    QPixmap GetPixMap();

private:
    CONTRAST_RESULT m_contrast_result;
    int m_ok_ng_flag;//ok\ng标志
    int m_ok_cnt;
    int m_ng_cnt;
    int m_excute_flag;

    void GetPreData(QPainter *paint, int iStep, int iSwitch);
    void GetRoiData(QPainter *paint, SELECT_AREA_PARAM del_model);
    void DrawPolygon(QPainter *paint, OCTAGON_CFG_PARA points);
    void DrawRing(QPainter *paint, CIRCULAR ring);
};

#endif // RESOLVERUNDATA_H
