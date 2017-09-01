#ifndef CMPJUMPWIDGET_H
#define CMPJUMPWIDGET_H

#include <QWidget>
#include <QLibrary>
#include "SelectDataDialog.h"
#include "CmpJumpGlobal.h"
#include "TaskStepGlobal.h"
#include "LinkDataGlobal.h"

namespace Ui {
class CmpJumpWidget;
}


typedef QDialog* (*Fun_GetNumkeyBoardDlg)();
typedef QString (*Fun_GetNumString)();
typedef void (*Fun_SetNumString)(QString NumString);

class CmpJumpWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CmpJumpWidget(QWidget *parent = 0);
    ~CmpJumpWidget();

    void Init_Input_Ptr(void *ptr,int i_step_index,int new_flag,void *pen_color);
    int Set_Parameter_To_Ram();

private slots:
    void on_radioButtonInput_clicked();

    void on_radioButtonQuote_clicked();

    void on_btnSelectA_clicked();

    void on_btnSelectB_clicked();

protected:
    bool eventFilter(QObject *watched, QEvent *event);
private:
    Ui::CmpJumpWidget *ui;
    CMP_JUMP_INPUT_PARAM *pInputPara;
    int m_step_index;//当前步骤索引
    int m_i_load_first;//
    QLibrary m_keyBoard_Lib;

    void InitData(int i_step_index);
    void LoadKeyBoardLib();
    QString SetQuoteString(unsigned short task_index, unsigned short result_index);
    void GetQuoteDataIndex(int *task_index, int *result_index, QString info);

    unsigned int dataComFrom;
};

#endif // CMPJUMPWIDGET_H
