#ifndef COMMANDJUMPSETDIALOG_H
#define COMMANDJUMPSETDIALOG_H

#include <QDialog>
#include "TaskHeaderGlobal.h"
#include "TaskStepGlobal.h"
#include "LinkDataGlobal.h"
#include <QLibrary>
#include <QHash>
namespace Ui {
class CommandJumpSetDialog;
}


typedef QDialog* (*Fun_GetkeyBoardDlg)();
typedef QString (*Fun_GetInputString)();
typedef void (*Fun_SetInputString)(QString str);

class CommandJumpSetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CommandJumpSetDialog(int currentIndex, QWidget *parent = 0);
    ~CommandJumpSetDialog();
    //获取跳转步骤名称
   QString GetJumpStepValue(){return m_str_Jump_Step;}
   //获取触发命令值
   QString GetJumpCmdValue(){return m_str_cmd_jump;}
   //编辑初始控件数据
   void IniEditData(QString str_cmd_jump, QString str_Jump_Step);

   int m_i_data_type;
   QString str_End_Symbol;
   QString str_Num;
   QString str_SaveAdr;
   QString str_Split;

protected:
    bool eventFilter(QObject *watched, QEvent *event);
private slots:
    //确定退出
    void on_btnOk_clicked();
    //取消退出
    void on_btnQuit_clicked();
private:
    Ui::CommandJumpSetDialog *ui;
    QString m_str_cmd_jump;
    QString m_str_Jump_Step;
    int i_currentIndex;
    QHash<QString, int> Data_type;
    QLibrary m_keyBoard_Lib;
    void LoadKeyBoardLib();
    void TaskGetStepName();
};

#endif // COMMANDJUMPSETDIALOG_H
