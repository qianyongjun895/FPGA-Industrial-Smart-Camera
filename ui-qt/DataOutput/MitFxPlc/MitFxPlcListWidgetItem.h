#ifndef MITFXPLCLISTWIDGETITEM_H
#define MITFXPLCLISTWIDGETITEM_H

#include <QWidget>

namespace Ui {
class MitFxPlcListWidgetItem;
}

class MitFxPlcListWidgetItem : public QWidget
{
    Q_OBJECT

public:
    explicit MitFxPlcListWidgetItem(QWidget *parent = 0);
    ~MitFxPlcListWidgetItem();

    void SetLableText(QString text);
    QString GetLabelText();
    void SetCurrentIndex(int index);
    void SetToolType(int type);
    int GetToolType(){return tool_type;}
private slots:
    void on_pushButton_clicked();

private:
    Ui::MitFxPlcListWidgetItem *ui;
    int Current_index;
    int tool_type;
};

#endif // MITFXPLCLISTWIDGETITEM_H
