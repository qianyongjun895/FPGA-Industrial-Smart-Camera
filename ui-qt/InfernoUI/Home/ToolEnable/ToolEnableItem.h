#ifndef TOOLENABLEITEM_H
#define TOOLENABLEITEM_H

#include <QWidget>

namespace Ui {
class ToolEnableItem;
}

class ToolEnableItem : public QWidget
{
    Q_OBJECT

public:
    explicit ToolEnableItem(QWidget *parent = 0);
    ~ToolEnableItem();

    void SetEnaFlag(bool flag);
    void SetTaskName(QString name);
    char GetEnaFlag();
private:
    Ui::ToolEnableItem *ui;
};

#endif // TOOLENABLEITEM_H
