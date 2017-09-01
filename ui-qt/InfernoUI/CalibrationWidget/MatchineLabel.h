#ifndef MATCHINELABEL_H
#define MATCHINELABEL_H

#include <QObject>
#include <QLabel>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>



class MatchineLabel : public QLabel
{
    Q_OBJECT
public:

    explicit MatchineLabel(QWidget *parent = 0);
    ~MatchineLabel();

signals:

public slots:
protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);

private:
    int m_y1;
    int m_x1;
    int kind;
};

#endif // HOMEWIDGETPICLABEL_H
