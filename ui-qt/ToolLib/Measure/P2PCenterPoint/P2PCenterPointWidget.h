#ifndef P2PCENTERPOINTWIDGET_H
#define P2PCENTERPOINTWIDGET_H

#include <QWidget>
#include <QLabel>
#include "MiddlePointGlobal.h"

namespace Ui {
class P2PCenterPointWidget;
}

class P2PCenterPointWidget : public QWidget
{
    Q_OBJECT

public:
    explicit P2PCenterPointWidget(QWidget *parent = 0);
    ~P2PCenterPointWidget();
    QPoint Get_Image_Pos();
    int Set_Parameter_To_Ram();
    void Init_Input_Ptr(void *ptr,int i_step_index,int new_flag,void *pen_color);
    void Get_Result_From_Ram();
private slots:
    void Point1TaskChangeSlot(int index);
    void Point2TaskChangeSlot(int index);
    void Point1ResultChangeSlot(int index);
    void Point2ResultChangeSlot(int index);

private:
    Ui::P2PCenterPointWidget *ui;
    QLabel *m_label;
    void *pInputPara;
    int m_step_index;//当前步骤索引
    void InitData(int i_step_index);
    int m_i_load_first;
    QString InitPointCombobox(int TaskIndex, int id);
    void GetRefPara(int ref_step, int ref_result, QPoint *point);
};

#endif // P2PCENTERPOINTWIDGET_H
