/**
  * @file  [FWVerticalPointLabel.h]
  * @brief  FWVerticalPointLabel
  * @author  <Vincent>
  * @date  <2017/6/5>
  * @version  <1.0>
  * @note 垂点的osd
  * detailed  description
  */
#ifndef FWVERTICALPOINTLABEL_H
#define FWVERTICALPOINTLABEL_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>

class FWVerticalPointLabel : public QLabel
{
public:
    FWVerticalPointLabel(QWidget *parent = 0);
    void SetPoint(QPoint point);
    void SetLine(QLine line);
    void SetSet_Parameter_To_RamPoint(QPoint point);
protected:
    void paintEvent(QPaintEvent *e);
private:
    QPoint m_point;
    QLine m_line;
    QPoint m_Vpoint;

    int i_learn_result;
};

#endif // FWVERTICALPOINTLABEL_H
