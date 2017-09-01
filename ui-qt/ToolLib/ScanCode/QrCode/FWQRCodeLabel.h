#ifndef FWQRCODELABEL_H
#define FWQRCODELABEL_H

#include <QLabel>
#include <QObject>
#include <QWidget>

class FWQRCodeLabel : public QLabel
{
    Q_OBJECT
public:
    explicit FWQRCodeLabel(QWidget *parent = 0);
    void SetPenColor(void *pen_color);

private:
    void *m_pen_color;
};

#endif // FWQRCODELABEL_H
