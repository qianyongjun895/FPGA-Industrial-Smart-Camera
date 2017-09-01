/**
  * @file  [ResolveRunData.h]
  * @brief  ResolveRunData
  * @author  <dgq>
  * @date  <2017/7/13>
  * @version  <1.0>
  * @note 长宽测量的运行数据处理
  * detailed  description
  */
#ifndef RESOLVERUNDATA_H
#define RESOLVERUNDATA_H

#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QLabel>
#include <QVector>
#include "../../BasicDefine.h"
#include "MapGlobal.h"

class ResolveRunData
{
public:
    explicit ResolveRunData();
    ~ResolveRunData();
    void Paint(QPainter *paint,int step,void *penStyle,int paintAreaSelect);
    QVector<STRU_KEY_VALUE> GetHead(int step);
    QVector<STRU_KEY_VALUE> GetContent(int step, int index, int *count);

private:
    int m_ok_cnt;
    int m_ng_cnt;
    int m_excute_flag;
    int m_ok_ng_flag;
    void GetPreData(QPainter *paint, int iStep, int iSwitch);
    void GetRoiData(QPainter *paint, SELECT_AREA_PARAM del_model);
    void DrawPolygon(QPainter *paint, OCTAGON_CFG_PARA points);
    void DrawRing(QPainter *paint, CIRCULAR ring);
};

#endif // RESOLVERUNDATA_H
