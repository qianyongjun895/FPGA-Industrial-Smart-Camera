#ifndef SPOTFLAWWIDGET_H
#define SPOTFLAWWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QLibrary>
#include <QTimer>
#include "TaskStepGlobal.h"
#include "TaskRstGlobal.h"
#include "PixelConvert.h"
#include "SpotFlawGlobal.h"

typedef QDialog* (*Fun_GetNumkeyBoardDlg)();
typedef void (*Fun_SetRangeInput)(QString max, QString min, int flag);
typedef QString (*Fun_GetRangeNum)();

typedef QDialog* (*Fun_GetLearnDialog)();
typedef void* (*Fun_SetResultString)(QString str);

#define THRESHOLD_LOW   0
#define THRESHOLD_HIGH  1

namespace Ui {
class SpotFlawWidget;
}

class SpotFlawWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SpotFlawWidget(QWidget *parent = 0);
    ~SpotFlawWidget();
    QPoint Get_Image_Pos();
    int Set_Parameter_To_Ram();
    void Init_Input_Ptr(void *ptr,int i_step_index,int new_flag,void *pen_color);

protected:
    bool eventFilter(QObject *watched, QEvent *event);

private slots:
    void on_btnPrePage_clicked();
    void on_btnNextPage_clicked();
    void on_btnAutoCalc_clicked();

    void CalcTimerSlot();
private:
    Ui::SpotFlawWidget *ui;
    QLabel *m_label;
    SPOT_FLAW_INPUT_PARAM *pInputPara;
    int m_step_index;//当前步骤索引
    int m_i_load_first;//
    QLibrary m_keyBoard_Lib;
    QLibrary m_Learn_Lib;
    QTimer *CalcTimer;

    void InitData();
    void LoadKeyBoardLib();
    void RangeInputPro(QLineEdit *max, QLineEdit *min, QString calc_value, int flag);
    void SetDataToLib();
    void GetDataFromLib();
    void LoadLearnLib();
};

#endif // SPOTFLAWWIDGET_H
