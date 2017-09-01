#ifndef GRAYMATCHWIDGET_H
#define GRAYMATCHWIDGET_H

#include <QWidget>
#include <QWidget>
#include <QLabel>
#include <QLibrary>
#include <QTimer>
#include "TaskGlobal.h"
#include "PixelConvert.h"
#include "qlineedit.h"
#include "GreayMatchGlobal.h"

typedef QDialog* (*Fun_GetNumkeyBoardDlg)();
typedef void (*Fun_SetRangeInput)(QString max, QString min, int flag);
typedef QString (*Fun_GetRangeNum)();

typedef QDialog* (*Fun_GetLearnDialog)();
typedef void* (*Fun_SetResultString)(QString str);

namespace Ui {
class GrayMatchWidget;
}

class GrayMatchWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GrayMatchWidget(QWidget *parent = 0);
    ~GrayMatchWidget();
    QPoint Get_Image_Pos();
    int Set_Parameter_To_Ram();
    void InitData();
    void Init_Input_Ptr(void *ptr,int i_step_index,int new_flag,void *pen_color);

private:
    Ui::GrayMatchWidget *ui;
    QLabel *m_label;
    QLibrary m_keyBoard_Lib;
    QLibrary m_Learn_Lib;
    QTimer *CalcTimer;
    GREAY_MATCH_INPUT_PARAM *pInputPara;
    int m_step_index; // 当前步骤索引
    int m_i_load_first;//

    void LoadLearnLib();
    void LoadKeyBoardLib();
    void GetDataFromLib();
    void GrayMatchMinInputPro();
    void GrayMatchMaxInputPro();

protected:
    bool eventFilter(QObject *watched, QEvent *event);

private slots:
    void CalcTimerSlot();
    void on_horizontalSlider11_valueChanged(int value);
};

#endif // GRAYMATCHWIDGET_H
