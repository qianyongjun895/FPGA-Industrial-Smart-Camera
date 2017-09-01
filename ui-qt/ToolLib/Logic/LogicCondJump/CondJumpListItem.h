#ifndef CONDJUMPLISTITEM_H
#define CONDJUMPLISTITEM_H

#include <QWidget>

namespace Ui {
class CondJumpListItem;
}

class CondJumpListItem : public QWidget
{
    Q_OBJECT

public:
    explicit CondJumpListItem(QWidget *parent = 0);
    ~CondJumpListItem();
    void SetJumpSetpName(QString strName);
    void SetCheckboxState(bool bflag);
    QString GetJumpSetpName();
    bool GetCheckboxState();

private:
    Ui::CondJumpListItem *ui;
};

#endif // CONDJUMPLISTITEM_H
