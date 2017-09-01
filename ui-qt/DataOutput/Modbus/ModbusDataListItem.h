#ifndef MODBUSDATALISTITEM_H
#define MODBUSDATALISTITEM_H

#include <QWidget>

namespace Ui {
class ModbusDataListItem;
}

class ModbusDataListItem : public QWidget
{
    Q_OBJECT

public:
    explicit ModbusDataListItem(QWidget *parent = 0);
    ~ModbusDataListItem();

    void SetLabelText(QString test);
    void SetToolType(int type);
    void SetModbusMode(int mode);
    void SetCurrentIndex(int index);
    QString GetLabelText();
    int GetModbusMode();
    int GetToolType();
private slots:
    void on_btnDetail_clicked();

private:
    Ui::ModbusDataListItem *ui;
    int current_index;
    int slave_or_host;
    int tool_type;
};

#endif // MODBUSDATALISTITEM_H
