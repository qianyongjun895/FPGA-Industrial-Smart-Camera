/**
  * @file  [NumKeyBoard.h]
  * @brief
  * @author  <szj>
  * @date  <2017/05/09>
  * @version  <1.0>
  * @note
  * detailed  description
  */
#ifndef NUMKEYBOARD_H
#define NUMKEYBOARD_H

#include <QDialog>
#include <stdbool.h>

namespace Ui {
class NumKeyBoard;
}
/**
  * @class  <NumKeyBoard>  [NumKeyBoard.h]  [NumKeyBoard]
  * @brief  数字键盘
  * @author  <szj>
  * @note
  * detailed  description
  */
class NumKeyBoard : public QDialog
{
    Q_OBJECT

public:
    explicit NumKeyBoard(QWidget *parent = 0);
    ~NumKeyBoard();
    /**
     * @brief GetNum
     * @return 返回输入数字
     * @author szj
     * @date 2017/05/08
     * @note 获取输入数字
     */
    QString GetNum();
    /**
     * @brief SetNum
     * @param str_Num 键盘上初始化数字
     * @return 返回空
     * @author szj
     * @date 2017/05/08
     * @note 初始化键盘数字
     */
    void SetNum(QString str_Num);
    /**
     * @brief SetOldNum
     * @param str_Num 键盘上初始化数字
     * @return 返回空
     * @author szj
     * @date 2017/05/08
     * @note 初始化键盘数字
     */
    void SetOldNum(QString str_Num);
    /**
     * @brief InputIp
     * @return 返回空
     * @author dgq
     * @date 2017/05/08
     * @note 设置数字键盘为ip格式
     */
    void InputIp();
    /**
     * @brief ShowbtnRangeEn
     * @author dgq
     * @return 返回空
     * @date 2017/05/08
     * @note 清空按扭的显示
     */
    void ShowbtnRangeEn();
    /**
     * @brief RangeInput
     * @param max 上限最大值
     * @param min 下限最小值
     * @param flag 1上限 0下限
     * @return 返回空
     * @author dgq
     * @date 2017/05/08
     * @note 设置上下限
     */
    void RangeInput(QString max, QString min, int flag);
    /**
     * @brief GetRangeNum
     * @return 返回数据门限范围
     * @author dgq
     */
    QString GetRangeNum();
    void SetNaturalNumberInputMode(bool b_value);
private slots:
    void on_btn1_clicked();

    void on_btn2_clicked();

    void on_btn3_clicked();

    void on_btn4_clicked();

    void on_btn5_clicked();

    void on_btn6_clicked();

    void on_btn7_clicked();

    void on_btn8_clicked();

    void on_btn9_clicked();

    void on_btnSpot_clicked();

    void on_btn0_clicked();

    void on_btnNegative_clicked();

    void on_btnClear_clicked();

    void on_btnBack_clicked();

    void on_btnOk_clicked();

    void on_btnQuit_clicked();



    void on_btnRangeEn_clicked();

    void on_txtNum_selectionChanged();

private:
    Ui::NumKeyBoard *ui;
    QString strNum;
    bool b_IP;
    QString strCmp;
    int m_flag; //1上限，0下限
    QString m_StrSelect;
    void SelectTextReplace(QPushButton *object);
};

#endif // NUMKEYBOARD_H
