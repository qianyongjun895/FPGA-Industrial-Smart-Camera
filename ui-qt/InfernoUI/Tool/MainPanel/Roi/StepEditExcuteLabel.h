#ifndef STEPEDITEXCUTELABEL_H
#define STEPEDITEXCUTELABEL_H
#include <QObject>
#include <QLabel>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QImage>
#include <QPainter>

class StepEditExcuteLabel : public QLabel
{
    Q_OBJECT
public:

    explicit StepEditExcuteLabel(QWidget *parent = 0);
    ~StepEditExcuteLabel();
    void Update();
    void SetPixMap(QPixmap pix);
    void ClearOSD();
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
};

#endif // HOMEWIDGETPICLABEL_H
