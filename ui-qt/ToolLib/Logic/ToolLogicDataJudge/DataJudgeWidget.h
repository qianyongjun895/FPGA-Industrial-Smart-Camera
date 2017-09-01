#ifndef DATAJUDGEWIDGET_H
#define DATAJUDGEWIDGET_H

#include <QWidget>
#include <QLibrary>
#include "SelectDataDialog.h"
#include "TaskStepGlobal.h"
#include "LinkDataGlobal.h"
#include "CondJudgeGlobal.h"

namespace Ui {
class DataJudgeWidget;
}

class DataJudgeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DataJudgeWidget(QWidget *parent = 0);
    ~DataJudgeWidget();
    void Init_Input_Ptr(void *ptr,int i_step_index,int new_flag,void *pen_color);
    int Set_Parameter_To_Ram();
private slots:
    void on_btnAdd_clicked();

    void on_btnEdit_clicked();

    void on_btnDell_clicked();

private:
    Ui::DataJudgeWidget *ui;
    void *pInputPara;
    int m_step_index;//当前步骤索引
    void InitData(int i_step_index);
    int m_i_load_first;//
    bool JudgeDataIntable(QString strName);
    void AddTableData(QString StrName, QString strUpLimit, QString strDownLimit, QString strDatakind);
    void Initable();
    void GetQuoteDataIndex(int *task_index, int *result_index, QString info);
    void SetLimitData(int index, QString strUpLimit, QString strDwonLimit, int iDataType);
    QString GetQuoteString(unsigned short task_index, unsigned short result_index);
};

#endif // DATAJUDGEWIDGET_H
