#ifndef FWMEANBRIGHTNESSLABEL_H
#define FWMEANBRIGHTNESSLABEL_H

#include <QWidget>
#include <QLabel>
class FWMeanBrightnessLabel : public QLabel
{
    Q_OBJECT
public:
    explicit FWMeanBrightnessLabel(QWidget *parent = 0);
    ~FWMeanBrightnessLabel();
    void SetPenColor(void *pen_color);
signals:

public slots:

private:
   void *m_pen_color;

};

#endif // FWMEANBRIGHTNESSLABEL_H
