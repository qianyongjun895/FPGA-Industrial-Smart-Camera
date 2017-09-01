#ifndef P2POFFSETWIDGET_H
#define P2POFFSETWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QLibrary>

namespace Ui {
class P2POffsetWidget;
}

typedef QDialog* (*Fun_GetNumkeyBoardDlg)();
typedef void (*Fun_SetRangeInput)(QString max, QString min, int flag);
typedef QString (*Fun_GetRangeNum)();
typedef QDialog* (*Fun_GetLearnDialog)();
typedef void* (*Fun_SetResultString)(QString str);

class P2POffsetWidget : public QWidget
{
    Q_OBJECT

public:
    explicit P2POffsetWidget(QWidget *parent = 0);
    ~P2POffsetWidget();
    QPoint Get_Image_Pos();
    int Set_Parameter_To_Ram();
    void Init_Input_Ptr(void *ptr,int i_step_index,int new_flag,void *pen_color);
private slots:
    void Point1TaskChangeSlot(int index);
    void Point2TaskChangeSlot(int index);
    void Point1ResultChangeSlot(int index);
    void Point2ResultChangeSlot(int index);
    void on_btnCalculation_clicked();

    void on_radioButton_phy_clicked();
    void on_radioButton_pix_clicked();
    void CalcTimerSlot();
private:
    Ui::P2POffsetWidget *ui;
    QLabel *m_label;
    void *pInputPara;
    int m_step_index;//当前步骤索引
    int m_i_load_first;
    QLibrary m_keyBoard_Lib;
    int pix_phy_flag;
    QLibrary m_Learn_Lib;
    QTimer *CalcTimer;

    void InitData(int i_step_index);
    QString InitPointCombobox(int TaskIndex, int id);
    void LoadKeyBoardLib();
    int SetYRangetoLib();
    int SetXRangetoLib();
    void InitRangeData();
    void GetRefPara(int ref_step, int ref_result, QPoint *point);
    void LoadLearnLib();
    void GetDataFromLib();
protected:
    bool eventFilter(QObject *watched, QEvent *event);
};

#endif // P2POFFSETWIDGET_H
