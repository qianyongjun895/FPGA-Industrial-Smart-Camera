#ifndef LISTWIDGETIOOUTPUTITEM_H
#define LISTWIDGETIOOUTPUTITEM_H

#include <QWidget>
namespace Ui {
class ListWidgetIOOutputItem;
}

class ListWidgetIOOutputItem : public QWidget
{
    Q_OBJECT

public:
    explicit ListWidgetIOOutputItem(QWidget *parent = 0);
    ~ListWidgetIOOutputItem();

    void SetLabelText(QString str);
    void SetIOModel(int flag){Model_Flag = flag;}
protected slots:
    bool eventFilter(QObject *watched, QEvent *event);
private:
    Ui::ListWidgetIOOutputItem *ui;
    int Model_Flag;///<0:基础; 1:高级
    int OK_IO_Port;
    int NG_IO_Port;
};

#endif // LISTWIDGETIOOUTPUTITEM_H
