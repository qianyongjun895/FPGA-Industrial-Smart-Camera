#ifndef DELAYWIDGET_H
#define DELAYWIDGET_H

#include <QWidget>
#include <QLibrary>
#include "DelayGlobal.h"
#include "TaskStepGlobal.h"
#include "LinkDataGlobal.h"

namespace Ui {
class DelayWidget;
}

typedef QDialog* (*Fun_GetNumkeyBoardDlg)();
typedef QString (*Fun_GetNumString)();
typedef void (*Fun_SetNumString)(QString NumString);
class DelayWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DelayWidget(QWidget *parent = 0);
    ~DelayWidget();
    void Init_Input_Ptr(void *ptr,int i_step_index,int new_flag,void *pen_color);
    int Set_Parameter_To_Ram();
    QPoint Get_Image_Pos();
protected:
    bool eventFilter(QObject *watched, QEvent *event);
private:
    Ui::DelayWidget *ui;
    void *pInputPara;
    int m_step_index;//当前步骤索引
    void InitData(int i_step_index);
    int m_i_load_first;//
    QLibrary m_keyBoard_Lib;
    void LoadKeyBoardLib();
};

#endif // DELAYWIDGET_H
