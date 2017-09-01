#ifndef HANSROBOTHWIDGET_H
#define HANSROBOTHWIDGET_H

#include <QWidget>

namespace Ui {
class HansRobothWidget;
}

class HansRobothWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HansRobothWidget(QWidget *parent = 0);
    ~HansRobothWidget();

private:
    Ui::HansRobothWidget *ui;
};

#endif // HANSROBOTHWIDGET_H
