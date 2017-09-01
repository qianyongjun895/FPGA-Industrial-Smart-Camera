#ifndef ADMINWIDGET_H
#define ADMINWIDGET_H

#include <QWidget>
#include "BusinessData/InterfaceLib/KeyBoardLib.h"
namespace Ui {
class AdminWidget;
}

class AdminWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AdminWidget(QWidget *parent = 0);
    ~AdminWidget();

protected:
    bool eventFilter(QObject *watched, QEvent *event);

private slots:
    void on_btnModify_clicked();

    void on_checkBox_clicked();

private:
    Ui::AdminWidget *ui;
    KeyBoardLib m_KeyBoardLib;
};

#endif // ADMINWIDGET_H
