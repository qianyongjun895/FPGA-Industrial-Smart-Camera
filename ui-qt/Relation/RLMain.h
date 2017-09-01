#ifndef RLMAIN_H
#define RLMAIN_H

#include <QWidget>
#include <stdbool.h>
#include <KeyBoard.h>
#define COMPASS_NULL		0        /*不参与计算 */
#define COMPASS_MANUAL		1       /* 手动输入 */
#define COMPASS_REF_VALUE	2       /* 参考坐标 */

namespace Ui {
class RLMain;
}

class RLMain : public QWidget
{
    Q_OBJECT

public:
    explicit RLMain(QWidget *parent = 0);
    ~RLMain();
    void SetCurrentStepIndex(int index);

    int SetRelateLocationData();

private slots:

    void SelectDataSlot(int v);

    void on_RelateLocationCheckBox_clicked();

    void InitTaskEdit();

    void on_radioButton_X_Null_clicked();

    void on_radioButton_X_Manual_clicked();

    void on_radioButton_X_Link_clicked();

    void on_radioButton_Y_Null_clicked();

    void on_radioButton_Y_Manual_clicked();

    void on_radioButton_Y_Link_clicked();

    void on_radioButton_A_Null_clicked();

    void on_radioButton_A_Manual_clicked();

    void on_radioButton_A_Link_clicked();

protected:
    bool eventFilter(QObject *watched, QEvent *event);
private:
    Ui::RLMain *ui;
    int m_i_CurrentStep;

    int m_X;
    int m_Y;
    int m_Angle;

    QString m_X_Manual;
    QString m_X_Ref;
    QString m_Y_Manual;
    QString m_Y_Ref;
    QString m_A_Manual;
    QString m_A_Ref;
    KeyBoard m_keyBoard;
};

#endif // RLMAIN_H
