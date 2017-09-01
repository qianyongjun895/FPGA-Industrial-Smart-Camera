#ifndef RESOLVERUNDATA_H
#define RESOLVERUNDATA_H

#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QLabel>
#include <QVector>
#include "../../BasicDefine.h"
#include "LineFlawGlobal.h"

class ResolveRunData
{
public:
    explicit ResolveRunData();
    ~ResolveRunData();
    void Paint(QPainter *paint,int step,void *penStyle,int paintAreaSelect);
    QVector<STRU_KEY_VALUE> GetHead(int step);
    QVector<STRU_KEY_VALUE> GetContent(int step, int index, int *count);

private:
    int m_flaw_total_area;  ///< 直线缺陷总面积
    int m_flaw_cnt;         ///< 缺陷个数
    int m_ok_ng_flag;       ///< ok/ng标志
    QLine m_line;           ///< 关联直线
    int m_ok_cnt;
    int m_ng_cnt;
    int m_excute_flag;

    QVector<QPoint> Flaw_Pix_Center;
    QVector<QPoint> Real_Pix_Center;
    QVector<unsigned int> Flaw_Length;
    QVector<float> Flaw_Area;
    QVector<float> Flaw_Level;

    void GetPreData(QPainter *paint, int iStep, int iSwitch);
    void GetRoiData(QPainter *paint, SELECT_AREA_PARAM del_model);
    void DrawPolygon(QPainter *paint, OCTAGON_CFG_PARA points);
    void DrawRing(QPainter *paint, CIRCULAR ring);
};

#endif // RESOLVERUNDATA_H
