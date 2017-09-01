#ifndef SCALECALCWIDGET_H
#define SCALECALCWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QLibrary>
#include "ScaleCalcGlobal.h"

/*获取小键盘Dialog指针的函数指针*/
typedef QDialog* (*Fun_GetNumkeyBoardDlg)();
/*获取普通数字输入值的函数指针*/
typedef QString (*Fun_GetNumString)();

namespace Ui {
class ScaleCalcWidget;
}

class ScaleCalcWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ScaleCalcWidget(QWidget *parent = 0);
    ~ScaleCalcWidget();
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
    void on_radioButton_Comm_Scale_clicked();

    void on_radioButton_Ref_Result_clicked();

    void PointTaskChangeSlot(int index);
    void PointResultChangeSlot(int index);

private:
    Ui::ScaleCalcWidget *ui;
    QLabel *m_label;
    SCALE_CALC_INPUT_PARAM *pInputPara;
    int m_step_index;//当前步骤索引
    int m_i_load_first;
    QLibrary m_keyBoard_Lib;


    QString InitPointCombobox(int TaskIndex, int id);
    void InitData(int i_step_index);
    void GetRefPara(int ref_step, int ref_result, QPoint *point);
    void BlobNumInputPro(QLineEdit *txtInput);
    void LoadKeyBoardLib();
};

#endif // SCALECALCWIDGET_H
