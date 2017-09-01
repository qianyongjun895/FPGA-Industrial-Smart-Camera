#ifndef CALIBRATIONPARAMREFERENCE_H
#define CALIBRATIONPARAMREFERENCE_H

#include <QWidget>
#include <stdbool.h>

namespace Ui {
class CalibrationParamReference;
}

class CalibrationParamReference : public QWidget
{
    Q_OBJECT

public:
    explicit CalibrationParamReference(QWidget *parent = 0);
    ~CalibrationParamReference();

    int m_step_index; // 当前步骤索引
    int m_param_index; // 多点标定参数索引
    int m_scale_param_index; // 刻度校准参数索引
    float m_scale_value; // 刻度校准比例系数

    void SetParamData(QString &stepName, int curStepIndex);
    void UpdateParamReference(int paramIndex);
    void UpdateScaleParamRef(int paramIndex, float curFloat);

private slots:
    void on_btnChangeParam_clicked();

    void on_btnScaleChangeParam_clicked();

private:
    Ui::CalibrationParamReference *ui;
};

#endif // CALIBRATIONPARAMREFERENCE_H
