#ifndef P2PLINEWIDGET_H
#define P2PLINEWIDGET_H

#include <QWidget>
#include <QLabel>
#include "PointsLineGlobal.h"

namespace Ui {
class P2PLineWidget;
}

class P2PLineWidget : public QWidget
{
    Q_OBJECT

public:
    explicit P2PLineWidget(QWidget *parent = 0);
    ~P2PLineWidget();
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
    Ui::P2PLineWidget *ui;
    QLabel *m_label;
    void *pInputPara;
    int m_step_index;//当前步骤索引
    void InitData(int i_step_index);
    int m_i_load_first;
    QString InitPointCombobox(int TaskIndex, int id);
    void GetRefPara(int ref_step, int ref_result, QPoint *point);
};

#endif // P2PLINEWIDGET_H
