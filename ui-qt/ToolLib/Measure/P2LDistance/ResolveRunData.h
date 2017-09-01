/**
  * @file  [ResolveRunData.h]
  * @brief  ResolveRunData
  * @author  <dgq>
  * @date  <2017/6/5>
  * @version  <1.0>
  * @note  获取点线距离的运行数据
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
#include "PixelConvert.h"
#include "TaskStepGlobal.h"
#include "TaskRstGlobal.h"
#include "PointLineDistGlobal.h"

class ResolveRunData
{
public:
    explicit ResolveRunData();
    ~ResolveRunData();

    /**
     * @brief Paint
     * @param paint QPainter指针
     * @param step步骤号
     * @author dgq
     * @note 运行时画OSD，运行时需要画OSD的工具需要实现的接口
     */
    void Paint(QPainter *paint,int step,void *penStyle,int paintAreaSelect);

    /**
     * @brief GetHead
     * @param step 步骤号
     * @return 运行时的通用输出数据
     * @author dgq
     * @note 运行时获取通用输出数据的接口，按照固定格式将数据填入QVector中
     */
    QVector<STRU_KEY_VALUE> GetHead(int step);

    /**
     * @brief GetContent
     * @param step 步骤号
     * @return 运行时本步骤特有的输出数据
     * @author dgq
     * @note 运行时获取本步骤特有的输出数据，按照固定格式将数据填入QVector中
     */
    QVector<STRU_KEY_VALUE> GetContent(int step, int index, int *count);

private:
    QLine m_line; //表示点线距离的线段
    QLine m_ref_line;
    int m_ok_cnt;
    int m_ng_cnt;
    int m_excute_flag;

    /**
     * @brief GetMesureOsdData
     * @param i_step
     * @author dgq
     * @note 获取运行时的OSD数据
     */
    void GetMesureOsdData(int i_step);
    int Line_Osd_Init(LineParameter *pLinePara, QLine *pOsdLine);
    int Line_Paint_Base_On_KB_SubPixel(float k_f, float b_f, QLine *pOsd_line);
};

#endif // RESOLVERUNDATA_H
