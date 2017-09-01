/**
  * @file  [InfernoUI.h]
  * @brief
  * @author  <szj>
  * @date  <2017/05/08>
  * @version  <1.0>
  * @note
  * detailed  description
  */
#ifndef INFERNOUI_H
#define INFERNOUI_H

#include <QMainWindow>
#include <QToolButton>
#include <QGridLayout>
namespace Ui {
class InfernoUI;
}
/**
  * @class  <InfernoUI>  [InfernoUI.h]  [InfernoUI]
  * @brief  程序主界面
  * @author  <szj>
  * @note
  * detailed  description
  */
class InfernoUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit InfernoUI(QWidget *parent = 0);
    ~InfernoUI();

private slots:

    void on_btnHome_clicked();

    void on_btnImage_clicked();

    void on_btnTool_clicked();

    void on_btnDataOut_clicked();

    void on_btnCalibrat_clicked();

    void on_btnSysSet_clicked();
    void on_btnAdmin_clicked();

    void on_btnRun_clicked();

    void on_btnRunStep_clicked();

    void ControlSetEnable(bool flag);
signals:
    void TaskRunSignal();
private:
    Ui::InfernoUI *ui;
    QToolButton *m_btn_pre;
    QGridLayout *MainViewLayout;
    QWidget *m_frm;

    int m_admin;
    /**
     * @brief IniNavigationButtonStyle
     * @param btn
     * @param strKey
     * @author szj
     * @date 2017/05/08
     * @note 初始化导航栏按扭背景
     */
    void IniNavigationButtonStyle(QToolButton *btn,QString strKey);
    /**
     * @brief AddQWidget
     * @param qWidget
     * @author szj
     * @date 2017/05/08
     * @note 将widget加载到主框架中
     */
    void AddQWidget(QWidget *qWidget);
    /**
     * @brief DeleteWidgetInLayout
     * @author szj
     * @date 2017/05/08
     * @note 将删除主框架中widget
     */
    void DeleteWidgetInLayout();
    /**
     * @brief IniNavigation
     * @author szj
     * @date 2017/05/08
     * @note 初始化主界面导航栏
     */
    void IniNavigation();
    /**
     * @brief IniMainWidget
     * @author szj
     * @date 2017/05/08
     * @note 初始化主界面
     */
    void IniMainWidget();
    void SetBtnEnable(int bflag, int runflag=0);
};

#endif // INFERNOUI_H
