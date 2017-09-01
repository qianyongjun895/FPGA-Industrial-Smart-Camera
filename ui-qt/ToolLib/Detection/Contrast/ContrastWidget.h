#ifndef CONTRASTWIDGET_H
#define CONTRASTWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLibrary>
#include <QTimer>
#include <QComboBox>
#include "TaskStepGlobal.h"
#include "TaskRstGlobal.h"
#include "ContrastGlobal.h"


typedef QDialog* (*Fun_GetNumkeyBoardDlg)();
typedef QString (*Fun_GetNumString)();
typedef void (*ShowRangeEn)();

typedef QDialog* (*Fun_GetLearnDialog)();
typedef void* (*Fun_SetResultString)(QString str);

namespace Ui {
class ContrastWidget;
}

class ContrastWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ContrastWidget(QWidget *parent = 0);
    ~ContrastWidget();
    int Set_Parameter_To_Ram();
    void Init_Input_Ptr(void *ptr,int i_step_index,int new_flag,void *pen_color);

    QPoint Get_Image_Pos();
protected:
    bool eventFilter(QObject *watched, QEvent *event);

private slots:
    void on_ContrastCalc_clicked();
    void CalcTimerSlot();

private:
    Ui::ContrastWidget *ui;
    QLabel *m_label;
    int m_index;
    CONTRAST_INPUT_PARAM *pInputPara;
    int m_step_index;
    QLibrary m_keyBoard_Lib;
    QDialog *Numkey;
    QLibrary m_Learn_Lib;
    QTimer *CalcTimer;

    void InitData();
    int SetParamtoRam();
    void LoadKeyBoardLib();
    void NumKeyBoardDlg(QObject *watched, QEvent *event, int Min_value, int Max_value);
    void LoadLearnLib();
};

#endif // CONTRASTWIDGET_H
