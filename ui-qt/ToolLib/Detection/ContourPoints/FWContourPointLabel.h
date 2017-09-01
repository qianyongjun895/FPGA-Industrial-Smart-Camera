#ifndef FWCONTOURPOINTLABEL_H
#define FWCONTOURPOINTLABEL_H

#include <QWidget>
#include <QLabel>
class FWContourPointLabel : public QLabel
{
    Q_OBJECT
public:
    explicit FWContourPointLabel(QWidget *parent = 0);
    ~FWContourPointLabel();
signals:

public slots:
};

#endif // FWCONTOURPOINTLABEL_H
