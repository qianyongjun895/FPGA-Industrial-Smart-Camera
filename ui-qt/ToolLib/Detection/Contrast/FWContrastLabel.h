#ifndef FWCONTRASTLABEL_H
#define FWCONTRASTLABEL_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>

class FWContrastLabel : public QLabel
{
public:
    FWContrastLabel(QWidget *parent = 0);
protected:
    void paintEvent(QPaintEvent *e);
private:
    int i_learn_result;
};


#endif // FWCONTRASTLABEL_H
