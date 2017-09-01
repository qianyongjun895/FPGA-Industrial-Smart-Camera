#ifndef OSDSTYLE_H
#define OSDSTYLE_H

#include <QObject>
#include <QVector>
//#include "UIBasicDefine.h"
#include "BasicDefine.h"

class OSDStyle : public QObject
{
    Q_OBJECT
public:

    explicit OSDStyle(QObject *parent = 0);
    static  void iniColorPen();
    static void InitOSDConfig(int step);
    static void InitPenStyle();
    static QVector<unsigned char>vt_task_enable;
    static PEN_COLOR pen_color;
    static PEN_STYLE_RUN pen_style;
    static void *GetPenColor();
    static void *GetPenStyleAddr();

signals:

public slots:
};

#endif // OSDSTYLE_H
