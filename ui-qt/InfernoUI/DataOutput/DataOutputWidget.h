#ifndef DATAOUTPUTWIDGET_H
#define DATAOUTPUTWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include "ExternalCommWidget.h"
#include "IOSetWidget.h"
#include "DataInputWidget.h"
namespace Ui {
class DataOutputWidget;
}

class DataOutputWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DataOutputWidget(QWidget *parent = 0);
    ~DataOutputWidget();

    void DeleteWidgetInLayout();
private slots:
    void SetButtonStyle(QPushButton *pre, QPushButton *current);

    void on_IOpushButton_clicked();

    void on_ExternalpushButton_clicked();

    void on_InsidepushButton_clicked();

    void on_PushButton_Data_Input_clicked();

    void on_PushButton_HeartBeat_clicked();

private:
    Ui::DataOutputWidget *ui;
    IOSetWidget *IOWidget;
    ExternalCommWidget *CommWidget;
    DataInputWidget *InputDataWidget;
    QPushButton *m_btn_pre;
    QGridLayout *ComViewLayout;
};

#endif // DATAOUTPUTWIDGET_H
