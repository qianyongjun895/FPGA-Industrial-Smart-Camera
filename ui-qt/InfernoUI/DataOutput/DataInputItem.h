#ifndef DATAINPUTITEM_H
#define DATAINPUTITEM_H

#include <QWidget>
#include <QHash>
#include "BaseStruct.h"
#include <QLibrary>
namespace Ui {
class DataInputItem;
}
typedef QDialog* (*Fun_GetNumkeyBoardDlg)();
typedef QString (*Fun_GetNumString)();
class DataInputItem : public QWidget
{
    Q_OBJECT
public:
    explicit DataInputItem(QWidget *parent = 0);
    ~DataInputItem();
    void ShowInputDataID(int Id);
    void ShowInputDataEnable(int flag);
    void ShowInputDataValue(unsigned int type, RESULTvalue value);
    void ShowDynamicInputDataEnable(int flag);
    void ShowDynamicInputDataValue(unsigned int type, RESULTvalue value);

    void SetInputData();
protected:
    bool eventFilter(QObject *watched, QEvent *event);
private slots:
    void on_radioButton_Enable_clicked();

private:
    Ui::DataInputItem *ui;
    int Type_flag;
    QHash<int,int> Data_type;
    QLibrary m_keyBoard_Lib;
    QDialog *Numkey;
    void LoadKeyBoardLib();
    void NumKeyBoardDlg(QObject *watched, QEvent *event);
};

#endif // DATAINPUTITEM_H
