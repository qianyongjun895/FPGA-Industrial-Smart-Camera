#ifndef FWBLOBSCOUNTLABEL_H
#define FWBLOBSCOUNTLABEL_H

#include <QObject>
#include <QWidget>
#include <QLabel>
class FWBlobsCountLabel : public QLabel
{
    Q_OBJECT
public:
    explicit FWBlobsCountLabel(QWidget *parent = 0);
    ~FWBlobsCountLabel();

public slots:
};

#endif // FWBLOBSCOUNTLABEL_H
