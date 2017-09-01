#ifndef HOMOCALCWIDGET_H
#define HOMOCALCWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QLibrary>
#include "HomoCalcGlobal.h"

/*获取小键盘Dialog指针的函数指针*/
typedef QDialog* (*Fun_GetNumkeyBoardDlg)();
/*获取普通数字输入值的函数指针*/
typedef QString (*Fun_GetNumString)();

namespace Ui {
class HomoCalcWidget;
}

class HomoCalcWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HomoCalcWidget(QWidget *parent = 0);
    ~HomoCalcWidget();
    QPoint Get_Image_Pos();
    int Set_Parameter_To_Ram();
    void Init_Input_Ptr(void *ptr,int i_step_index,int new_flag,void *pen_color);
    void Get_Result_From_Ram();

protected:
    /**
     * @brief eventFilter
     * @param watched 监听对象
     * @param event 监听事件
     * @return
     * @author dgq
     * @note 事件过滤器，用来模拟行文本编辑框点击事件
     */
    bool eventFilter(QObject *watched, QEvent *event);
private slots:
    void PointTaskChangeSlot(int index);
    void PointResultChangeSlot(int index);
    void AngleTaskChangeSlot(int index);
    void AngleResultChangeSlot(int index);

    void on_checkBox_OffsetCacl_clicked();

private:
    Ui::HomoCalcWidget *ui;
    QLabel *m_label;
    HOMO_CALC_INPUT_PARAM *pInputPara;
    int m_step_index;//当前步骤索引
    int m_i_load_first;
    QLibrary m_keyBoard_Lib;


    QString InitPointCombobox(int TaskIndex, int id);
    void InitData(int i_step_index);
    void GetRefPara(int ref_step, int ref_result, QPoint *point);
    void NumInputPro(QLineEdit *txtInput);
    void LoadKeyBoardLib();
    QString InitAngleCombobox(int TaskIndex, int id);
    QStringList GetResultString(int task_index, int link_type_index);
};

#endif // HOMOCALCWIDGET_H
