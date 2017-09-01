#ifndef SCRIPTWIDGET_H
#define SCRIPTWIDGET_H

#include <QWidget>
#include <QListWidgetItem>
#include "ScriptGlobal.h"

namespace Ui {
class ScriptWidget;
}

class ScriptWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ScriptWidget(QWidget *parent = 0);
    ~ScriptWidget();
    int Set_Parameter_To_Ram();
    void Init_Input_Ptr(void *ptr,int i_step_index,int new_flag,void *pen_color);
    void Get_Result_From_Ram();

private slots:
    void on_comboBox_currentIndexChanged(int index);

    void on_tabWidget_tabBarClicked(int index);

    void on_listWidget_itemClicked(QListWidgetItem *item);

private:
    Ui::ScriptWidget *ui;
    SCRIPT_INPUT_PARAM *pInputpara;
    void LoadPython2Script();
    void LoadPython3Script();
    void LoadLuaScript();
};

#endif // SCRIPTWIDGET_H
