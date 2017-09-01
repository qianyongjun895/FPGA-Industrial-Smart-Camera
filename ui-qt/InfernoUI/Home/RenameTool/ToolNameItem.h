#ifndef TOOLNAMEITEM_H
#define TOOLNAMEITEM_H

#include <QWidget>

namespace Ui {
class ToolNameItem;
}

class ToolNameItem : public QWidget
{
    Q_OBJECT

public:
    explicit ToolNameItem(QWidget *parent = 0);
    ~ToolNameItem();
    void SetName(QString strName,QString strReName);
    void SetReName(QString strReName);
    QString GetName();
    QString GetRename();
private:
    Ui::ToolNameItem *ui;
};

#endif // TOOLNAMEITEM_H
