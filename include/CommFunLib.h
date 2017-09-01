#ifndef COMMFUNLIB_H
#define COMMFUNLIB_H
#include <QtCore/qglobal.h>
#include <QPainter>
#include <qdebug.h>
#include <QThread>
#include <qmath.h>
#include <QTime>
#include <QLine>
#include <QListWidget>
#include "AreaSelect.h"

#if defined(COMMFUNLIB_LIBRARY)
#  define COMMFUNLIBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define COMMFUNLIBSHARED_EXPORT Q_DECL_IMPORT
#endif

class COMMFUNLIBSHARED_EXPORT CommFunLib
{

public:
    CommFunLib();
};
void GetRoiData(QPainter *paint,SELECT_AREA_PARAM del_model);
void DrawPolygon(QPainter *paint, OCTAGON_CFG_PARA points);
void DrawRing(QPainter *paint, CIRCULAR ring);
int Line_Paint_Base_On_KB_SubPixel(float k_f, float b_f, QLine *pOsd_line);
extern "C" Q_DECL_EXPORT void GetPreData(QPainter *paint, int iStep,int iSwitch);
extern "C" Q_DECL_EXPORT void DrawArrow(QPainter *painter,QPoint lastPoint,QPoint endPoint,float iArrowLen);
extern "C" Q_DECL_EXPORT int Line_Osd_Init(LineParameter *pLinePara, QLine *pOsdLine);
extern "C" Q_DECL_EXPORT void ClearListWidget(QListWidget *pListWidget);
#endif // COMMFUNLIB_H
