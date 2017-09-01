/**
  * @file  [FWMatchBaseLineLabel.h]
  * @brief  FWMatchBaseLineLabel
  * @author  <dgq>
  * @date  <2017/5/24>
  * @version  <1.0>
  * @note 基准线OSD
  * detailed  description
  */
#ifndef FWMATCHSAMPLELABEL_H
#define FWMATCHSAMPLELABEL_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>

#define BASE_LINE_NUM_MAX    20

class FWMatchSampleLabel : public QLabel
{
    Q_OBJECT
public:
    FWMatchSampleLabel(QWidget *parent = 0);
    void SetPenColor(void *pen_color);

private:

signals:

protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);

    void *m_pen_color ;

};

#endif // FWMATCHBASELINELABEL_H
