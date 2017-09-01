#ifndef P2PDISTANCEWIDGET_H
#define P2PDISTANCEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLibrary>
#include <QLineEdit>
#include <QTimer>

/*下门限*/
#define THRESHOLD_LOW   0
/*上门限*/
#define THRESHOLD_HIGH  1
namespace Ui {
class P2PDistanceWidget;
}

typedef QDialog* (*Fun_GetNumkeyBoardDlg)();
typedef void (*Fun_SetRangeInput)(QString max, QString min, int flag);
typedef QString (*Fun_GetRangeNum)();
typedef QDialog* (*Fun_GetLearnDialog)();
typedef void* (*Fun_SetResultString)(QString str);

class P2PDistanceWidget : public QWidget
{
    Q_OBJECT

public:
    explicit P2PDistanceWidget(QWidget *parent = 0);
    ~P2PDistanceWidget();
    QPoint Get_Image_Pos();
    int Set_Parameter_To_Ram();
    void Init_Input_Ptr(void *ptr,int i_step_index,int new_flag,void *pen_color);
    void Get_Result_From_Ram();
protected:
    bool eventFilter(QObject *watched, QEvent *event);
private slots:
    void Point1TaskChangeSlot(int index);
    void Point2TaskChangeSlot(int index);
    void Point1ResultChangeSlot(int index);
    void Point2ResultChangeSlot(int index);
    void on_radioButton_pix_clicked();
    void on_radioButton_phy_clicked();
    void on_btnCalculation_clicked();
    void CalcTimerSlot();

private:
    Ui::P2PDistanceWidget *ui;
    QLabel *m_label;
    void *pInputPara;
    int m_step_index;//当前步骤索引
    int m_i_load_first;
    int pix_phy_flag;
    QLibrary m_keyBoard_Lib;
    QLibrary m_Learn_Lib;
    QTimer *CalcTimer;

    void InitData(int i_step_index);
    QString InitPointCombobox(int TaskIndex, int id);
    void GetPointRefPara(int ref_step, int ref_result, QPoint *point);
    void LoadKeyBoardLib();
    int SetRangetoLib();
    void InitRangeData();
    void LoadLearnLib();
    void RangeInputPro(QLineEdit *pEditMax, QLineEdit *pEditMin, QString calc_value, int flag);
};

#endif // P2PDISTANCEWIDGET_H
