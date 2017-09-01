#ifndef RESOLVERUNDATA_H
#define RESOLVERUNDATA_H

#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QLabel>
#include <QVector>
#include "../../BasicDefine.h"
#include "SkeletonMatchGlobal.h"
class ResolveRunData
{
public:
    explicit ResolveRunData();
    ~ResolveRunData();
    void Paint(QPainter *paint,int step,void *penStyle,int paintAreaSelect);
    QVector<STRU_KEY_VALUE> GetHead(int step);
    QVector<STRU_KEY_VALUE> GetContent(int step, int index, int *count);

    void SetInputPtr(int step);
private slots:
    void Coordinate_Rotate_Calc(POINT_F *OutPoint, POINT_F *ref_point, POINT_F *ref_delt, float sin_a, float cos_a);
private:
    int m_ok_ng_flag;//ok\ng标志
    QPoint pix_center_point;
    QPoint phy_center_point;
    float m_width;
    float m_height;
    double m_theta;
    int m_ok_cnt;
    int m_ng_cnt;
    int m_excute_flag;

    void GetPreData(QPainter *paint, int iStep, int iSwitch);
    void GetRoiData(QPainter *paint, SELECT_AREA_PARAM del_model);
    void DrawPolygon(QPainter *paint, OCTAGON_CFG_PARA points);
    void DrawRing(QPainter *paint, CIRCULAR ring);
};

#endif // RESOLVERUNDATA_H
