#ifndef TOOLICONMENUMAINWNDLABEL_H
#define TOOLICONMENUMAINWNDLABEL_H

#include <QObject>
#include <QLabel>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QImage>
#include <QPainter>



class ToolIconMenuMainWndLabel : public QLabel
{
    Q_OBJECT
public:

    explicit ToolIconMenuMainWndLabel(QWidget *parent = 0);
    ~ToolIconMenuMainWndLabel();
    void Update();
    void SetPixMap(QPixmap pix);
    void ClearOSD();
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
