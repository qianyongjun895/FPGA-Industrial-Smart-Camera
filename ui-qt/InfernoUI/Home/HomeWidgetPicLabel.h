#ifndef HOMEWIDGETPICLABEL_H
#define HOMEWIDGETPICLABEL_H

#include <QObject>
#include <QLabel>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QImage>
#include <QPainter>
#include "BusinessData/InterfaceLib/BaseLibInterface.h"


class HomeWidgetPicLabel : public QLabel
{
    Q_OBJECT
public:

    explicit HomeWidgetPicLabel(QWidget *parent = 0);
    ~HomeWidgetPicLabel();
    void Update();
    void SetPixMap(QPixmap pix);
    void ClearOSD();
    void SetLibVt(QVector<BaseLibInterface *>vt);
    void ListOSD();
signals:

public slots:
protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
private:
    int m_paint;
    QPixmap m_pix;
    QVector<BaseLibInterface *>m_vt_lib;
    int count;

};

#endif // HOMEWIDGETPICLABEL_H
