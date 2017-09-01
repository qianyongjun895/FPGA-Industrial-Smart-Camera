#ifndef CMDTRIGGERITEM_H
#define CMDTRIGGERITEM_H

#include <QWidget>
#include <QLibrary>
namespace Ui {
class CmdTriggerItem;
}
typedef QDialog* (*Fun_GetkeyBoardDlg)();
typedef QString (*Fun_GetInputString)();
typedef void (*Fun_SetInputString)(QString str);

class CmdTriggerItem : public QWidget
{
    Q_OBJECT

public:
    explicit CmdTriggerItem(QWidget *parent = 0);
    ~CmdTriggerItem();

    void SetTaskName(QString TaskName);
protected:
    bool eventFilter(QObject *watched, QEvent *event);
private slots:
    void on_checkBox_Task_clicked();

    void on_comboBoxDataType_currentIndexChanged(int index);



private:
    Ui::CmdTriggerItem *ui;
    QLibrary m_keyBoard_Lib;
    QDialog *m_dlg;
    void *m_data_ptr;
    int Ini_Flag;
    void LoadKeyBoardLib();
    void KeyBoardDlg(QObject *watched, QEvent *event, int dlg_x, int dlg_y, int String_Len);
    void SetCmdTriggerParam();
    QString GetStrDataType(int index);
    int GetDataTypeIndex(QString strName);
};

#endif // CMDTRIGGERITEM_H
