#ifndef COMMANDJUMPWIDGET_H
#define COMMANDJUMPWIDGET_H

#include <QWidget>
#include <QLabel>
#include "CommandJumpSetDialog.h"
#include "CmdJumpGlobal.h"

namespace Ui {
class CommandJumpWidget;
}

class CommandJumpWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CommandJumpWidget(QWidget *parent = 0);
    ~CommandJumpWidget();

    void Init_Input_Ptr(void *ptr,int i_step_index,int new_flag,void *pen_color);
    int Set_Parameter_To_Ram();
private slots:
    void on_btnAdd_clicked();

    void on_btnDelete_clicked();
    void on_btn_Edit_clicked();
private:
    Ui::CommandJumpWidget *ui;
    void *pInputPara;
    int m_step_index;//当前步骤索引
    void InitData(int i_step_index);
    int m_i_load_first;//
    QString GetStrDataType(int index);
    int GetDataTypeIndex(QString strName);
    void InitTableData(QString strJumpCmdValue,  \
                       QString strJumpStepValue, \
                       QString strAddr, \
                       QString strNum, \
                       QString  strDataType, \
                       QString strSPlit, \
                       QString strEnd);
};

#endif // COMMANDJUMPWIDGET_H
