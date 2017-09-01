#ifndef IOSETWIDGET_H
#define IOSETWIDGET_H

#include <QWidget>
#include <QLibrary>
#include <QGridLayout>
namespace Ui {
class IOSetWidget;
}
typedef QWidget* (*Fun_GetToolWidget)();
class IOSetWidget : public QWidget
{
    Q_OBJECT

public:
    explicit IOSetWidget(QWidget *parent = 0);
    ~IOSetWidget();

private slots:
    void on_tabWidget_currentChanged(int index);

private:
    Ui::IOSetWidget *ui;
    QLibrary IO_Output_Lib;
    QWidget* IO_Output_Widget;
    QLibrary IO_Trigger_Lib;
    QWidget* IO_Trigger_Widget;
    void LoadIOOutputWidget();
    void LoadIOTriggerWidget();
    QGridLayout *IOOutputLayout;
    QGridLayout *IOTriggetLayout;
};

#endif // IOSETWIDGET_H
