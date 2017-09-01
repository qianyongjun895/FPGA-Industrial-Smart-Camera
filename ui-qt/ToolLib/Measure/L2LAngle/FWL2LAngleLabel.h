/**
  * @file  [FWL2LAngleLabel.h]
  * @brief  FWL2LAngleLabel
  * @author  <dgq>
  * @date  <2017/6/6>
  * @version  <1.0>
  * @note 两线夹角的osd
  * detailed  description
  */
#ifndef FWL2LANGLELABEL_H
#define FWL2LANGLELABEL_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>
#include "TaskStepGlobal.h"

class FWL2LAngleLabel : public QLabel
{
public:
    FWL2LAngleLabel(QWidget *parent = 0);

    void SetLine1(QLine line);
    void SetLine2(QLine line);
    void SetSet_Parameter_To_RamFlag(int flag);
    void SetArcData(OSD_ARC data);
    void SetPenColor(void *pen_color);
protected:
    void paintEvent(QPaintEvent *e);
private:
    QLine m_Line1;
    QLine m_Line2;

    int i_learn_result;
    OSD_ARC m_arc;
    void *m_pen_color;
};

#endif // FWL2LANGLELABEL_H
