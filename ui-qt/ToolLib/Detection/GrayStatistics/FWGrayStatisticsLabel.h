#ifndef FWGRAYSTATISTICSLABEL_H
#define FWGRAYSTATISTICSLABEL_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>

class FWGrayStatisticsLabel : public QLabel
{
public:
    explicit FWGrayStatisticsLabel(QWidget *parent = 0);
    ~FWGrayStatisticsLabel();

};

#endif // FWGRAYSTATISTICSLABEL_H
