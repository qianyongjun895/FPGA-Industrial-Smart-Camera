#ifndef CALIBRATIONPARAMSELECT_H
#define CALIBRATIONPARAMSELECT_H

#include <QDialog>

namespace Ui {
class CalibrationParamSelect;
}

class CalibrationParamSelect : public QDialog
{
    Q_OBJECT

public:
    explicit CalibrationParamSelect(QWidget *parent = 0);
    ~CalibrationParamSelect();

    int m_cur_param_index;
    int m_scale_param_index;
    float m_scale_value[128];

    void MpdParamListInit();
    void ScaleParamListInit();

private slots:
    void on_btnCancel_clicked();

    void on_listWidget_currentRowChanged(int currentRow);

    void on_btnOk_clicked();

private:
    Ui::CalibrationParamSelect *ui;
};

#endif // CALIBRATIONPARAMSELECT_H
