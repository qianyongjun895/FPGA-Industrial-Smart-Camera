#ifndef TOUCHSCREENCALIBRATE_H
#define TOUCHSCREENCALIBRATE_H

#include <QWidget>

namespace Ui {
class TouchScreenCalibrate;
}

class TouchScreenCalibrate : public QWidget
{
    Q_OBJECT

public:
    explicit TouchScreenCalibrate(QWidget *parent = 0);
    ~TouchScreenCalibrate();

private slots:
    void on_btnScreenCalibrate_clicked();

private:
    Ui::TouchScreenCalibrate *ui;
};

#endif // TOUCHSCREENCALIBRATE_H
