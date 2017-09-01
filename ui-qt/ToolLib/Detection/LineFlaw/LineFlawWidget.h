#ifndef LINEFLAWWIDGET_H
#define LINEFLAWWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLibrary>
#include <QLineEdit>
#include <QTimer>
#include "TaskStepGlobal.h"
#include "TaskRstGlobal.h"
#include "PixelConvert.h"
#include "LineFlawGlobal.h"

typedef QDialog* (*Fun_GetNumkeyBoardDlg)();
typedef void (*Fun_SetRangeInput)(QString max, QString min, int flag);
typedef QString (*Fun_GetRangeNum)();
typedef QString (*Fun_GetNumString)();

typedef QDialog* (*Fun_GetLearnDialog)();
typedef void* (*Fun_SetResultString)(QString str);

#define THRESHOLD_LOW   0
#define THRESHOLD_HIGH  1

#define VGA_WIDTH 640
#define VGA_HEIGHT 480

namespace Ui {
class LineFlawWidget;
}

class LineFlawWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LineFlawWidget(QWidget *parent = 0);
    ~LineFlawWidget();
    QPoint Get_Image_Pos();
    int Set_Parameter_To_Ram();
    void Init_Input_Ptr(void *ptr,int i_step_index,int new_flag,void *pen_color);

    void Get_Result_From_Ram();
private slots:
    void on_btnCalculation_clicked();
    void on_btnNextPage_clicked();
    void on_btnPrePage_clicked();
    void on_comboBoxLineStep_activated(int index);
    void on_comboBoxLineIndex_activated(int index);
    void CalcTimerSlot();

protected:
    bool eventFilter(QObject *watched, QEvent *event);

private:
    Ui::LineFlawWidget *ui;
    QLabel *m_label;
    int m_step_index;//当前步骤索引
    LINE_FLAW_INPUT_PARAM *pInputPara;
    int m_i_load_first;
    QLibrary m_keyBoard_Lib;
    QLibrary m_Learn_Lib;
    QTimer *CalcTimer;

    void InitData();
    void LoadKeyBoardLib();
    void ParamInputPro(int iMin, int iMax, QLineEdit *pEdit);
    void ThresholdInputPro(QLineEdit *pEditMax,QLineEdit *pEditMin,int flag);
    void SetDataToLib();
    void RegisterEventFilter();
    void UnRegisterEventFilter();
    void SetTableData();
    void CleaTable();
    int Line_Paint_Base_On_KB_SubPixel(float k_f, float b_f, QLine *pOsd_line);
    int Line_Osd_Init(LineParameter *pLinePara, QLine *pOsdLine);
    QString InitLineCombobox(int TaskIndex, int id);
    void InitComboBox(int i_step_index);
    void LoadLearnLib();
};

#endif // LINEFLAWWIDGET_H
