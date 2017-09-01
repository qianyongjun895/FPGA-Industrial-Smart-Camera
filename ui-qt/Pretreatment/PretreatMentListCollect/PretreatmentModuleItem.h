/**
  * @file  [PretreatmentModuleItem.h]
  * @brief  PretreatmentModuleItem
  * @author  <szj>
  * @date  <2017/05/08>
  * @version  <1.0>
  * @note
  * detailed  description
  */

#ifndef PRETREATMENTMODULEITEMB_H
#define PRETREATMENTMODULEITEMB_H

#include <QWidget>
#define PREENABLE 1
#define PREDETAIL 2
namespace Ui {
class PretreatmentModuleItem;
}
/**
  * @class  <PretreatmentModuleItem>  [PretreatmentModuleItem.h]  [PretreatmentModuleItem]
  * @brief  预处理cpt模块
  * @author  <szj>
  * @note
  * detailed  description
  */

class PretreatmentModuleItem : public QWidget
{
    Q_OBJECT

public:
    explicit PretreatmentModuleItem(QWidget *parent = 0);
    ~PretreatmentModuleItem();
    int m_taskKind;
    int m_current_row;
    /**
     * @brief SetInfoName
     * @author szj
     * @date 2017/05/08
     * @note 设置列表名称
     */
    void SetInfoName(QString strName);
    /**
     * @brief GetInfoName
     * @author szj
     * @date 2017/05/08
     * @note 获取列表名称
     */
    QString GetInfoName();
    /**
     * @brief GetCheckedValue
     * @author szj
     * @date 2017/05/08
     * @note 获取列表框中checkbox状态
     */
    int GetCheckedValue();
    /**
     * @brief SetCheckdevalue
     * @param bflag  1.选中 0未选中
     * @author szj
     * @date 2017/05/08
     * @note 设置列表框中checkbox状态
     */
    void SetCheckdevalue(int bflag);
    /**
     * @brief SetControlEnable
     * @param 1使能 0未使能
     * @author szj
     * @date 2017/05/08
     * @note 设置控件使能
     */
    void SetControlEnable(int bflag);
    /**
     * @brief IniData
     * @author szj
     * @date 2017/05/08
     * @note cpt模块初始化数据
     */
    int GetCheckBoxEnable();

private slots:
    void on_btnDetail_clicked();

    void on_checkBox_clicked();
signals:
    //1,使能，2，详细界面
    void SignalOperate(int iOperate,int itaskKind,int value,int current);
private:
    Ui::PretreatmentModuleItem *ui;
};

#endif // PRETREATMENTMODULEITEMB_H
