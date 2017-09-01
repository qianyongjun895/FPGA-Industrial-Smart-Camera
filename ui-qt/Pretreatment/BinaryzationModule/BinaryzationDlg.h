/**
  * @file  [BinaryzationDlg.h]
  * @brief  BinaryzationDlg
  * @author  <szj>
  * @date  <2017/05/08>
  * @version  <1.0>
  * @note
  * detailed  description
  */
#ifndef BINARYZATIONDLG_H
#define BINARYZATIONDLG_H

#include <QDialog>
#include <QListWidget>
#include "PreBasicHead.h"
#include "AcceCommon.h"

namespace Ui {
class BinaryzationDlg;
}
/**
  * @class  <BinaryzationDlg>  [BinaryzationDlg.h]  [BinaryzationDlg]
  * @brief  二值化预处理模块
  * @author  <szj>
  * @note
  * detailed  description
  */
class BinaryzationDlg : public QDialog
{
    Q_OBJECT

public:
    explicit BinaryzationDlg(QWidget *parent = 0);
    ~BinaryzationDlg();
    /**
     * @brief IniData
     * @author szj
     * @date 2017/05/08
     * @note 二值预处理模块数据初始化
     */
    void IniData();
   int m_task_id;
   int m_step;
   void *m_pre_ptr;
   int m_listX;
   int m_listY;
private slots:
    void OperateSlots(int iOperate, int itaskKind, int value, int current);

    void on_btnOk_clicked();

    void on_btnQuit_clicked();

private:
    Ui::BinaryzationDlg *ui;
    int m_image_out_src;
    QMap<int,STRUCT_FUN_PTR>m_fun_ptr;
    BW_PROCESS_MODEL_CFG m_bw_cfg;
    /**
     * @brief InitFunPtr
     * @author szj
     * @date 2017/05/08
     * @note 初始化函数指针
     */
    void InitFunPtr();
    /**
     * @brief ClearList
     * @param pListWidget 数据列表控件
     * @author szj
     * @date 2017/05/08
     * @note 清空数据列表控件中的数据
     */
    void ClearList(QListWidget *pListWidget);
    /**
     * @brief AddItemData
     * @param strName 预处理模块名称
     * @param index  预处理模块id
     * @param bCheck 预处理模块使能
     * @author szj
     * @date 2017/05/08
     * @note 将预处理模块加到数据列表中
     */
    void AddItemData(QString strName,int index,int bCheck,int current);
    /**
     * @brief GetImageOutPut
     * @author szj
     * @date 2017/05/08
     * @note 配置预处理模块输入源
     */
    int GetImageOutPut();
};

#endif // BINARYZATIONDLG_H
