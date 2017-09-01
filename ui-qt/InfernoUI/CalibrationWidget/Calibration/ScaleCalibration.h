#ifndef SCALECALIBRATION_H
#define SCALECALIBRATION_H

#include <QWidget>
#include <QDialog>
#include <QKeyEvent>
#include <stdbool.h>
#include "ScaleImageLabel.h"
#include "BusinessData/InterfaceLib/KeyBoardLib.h"

namespace Ui {
class ScaleCalibration;
}

class ScaleCalibration : public QDialog
{
    Q_OBJECT

public:
    explicit ScaleCalibration(QWidget *parent = 0);
    ~ScaleCalibration();

    QString GetRatio();
    void SetRatio(QString ratio);
    void SetParamIndex(int paramIndex);

protected:
    bool eventFilter(QObject *watched, QEvent *event);

private slots:
    void CurPointChangedSlot(int curIndex,QPoint Point);

    void on_btnQuit_clicked();

    void on_radioButtonP1_clicked();

    void on_radioButtonP2_clicked();

    void on_btnMoveUp_clicked();

    void on_btnMoveDown_clicked();

    void on_btnMoveLeft_clicked();

    void on_btnMoveRight_clicked();

    void on_btnOk_clicked();

private:
    Ui::ScaleCalibration *ui;
    ScaleImageLabel *m_image_label;
    int m_auto_repeat_count; // 长按计数
    int m_self_inc; // 长按自增长值
    int param_index; // 参数索引 0:表示新参数
    int m_edit_ratio_flag; // 如果是点击编辑按钮进入编辑界面，则置2，用来保持像素比与进来时的值一样
    QString m_Ratio;//像素比参数
    QPoint m_press_point;
    QPoint m_point[2];

    void SeleIncValuePro();
    void PanelInit();
    KeyBoardLib m_keyBoardLib;

};

#endif // SCALECALIBRATION_H
