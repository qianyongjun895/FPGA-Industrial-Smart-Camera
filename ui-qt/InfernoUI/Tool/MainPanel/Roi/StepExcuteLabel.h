#ifndef STEPEXCUTELABEL_H
#define STEPEXCUTELABEL_H
#include <QObject>
#include <QLabel>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QImage>
#include <QPainter>
//#include "Comm/UIBasicDefine.h"
#include "BasicDefine.h"

class StepExcuteLabel : public QLabel
{
    Q_OBJECT
public:

    explicit StepExcuteLabel(QWidget *parent = 0);
    ~StepExcuteLabel();
    void ClearOSD();
    void SetSingleData(QVector<STRU_KEY_VALUE>vtHead,QVector<STRU_KEY_VALUE>vtBody);
    void SetCurrentIndex(int index);
signals:

public slots:
protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
private:

    QVector<STRU_KEY_VALUE> m_vtHead;
    QVector<STRU_KEY_VALUE> m_vtBody;
    int m_index;

};

#endif // HOMEWIDGETPICLABEL_H
