/**
  * @file  [ImagepreprocessDlg.h]
  * @brief  ImagepreprocessDlg
  * @author  <szj>
  * @date  <2017/05/08>
  * @version  <1.0>
  * @note
  * detailed  description
  */
#ifndef IMAGEPREPROCESSDLG_H
#define IMAGEPREPROCESSDLG_H

#include <QDialog>
#include <QListWidget>
#include "PreBasicHead.h"
#include "AcceCommon.h"
namespace Ui {
class ImagepreprocessDlg;
}
/**
  * @class  <ImagepreprocessDlg>  [ImagepreprocessDlg.h]  [ImagepreprocessDlg]
  * @brief  图像预处理模块
  * @author  <szj>
  * @note
  * detailed  description
  */
class ImagepreprocessDlg : public QDialog
{
    Q_OBJECT

public:

    int m_task_id;
    int m_step;
    int m_listX;
    int m_listY;
    void *m_pre_ptr;
    explicit ImagepreprocessDlg(QWidget *parent = 0);
    ~ImagepreprocessDlg();
    /**
     * @brief IniDefalutPattern
     * @author szj
     * @date 2017/05/08
     * @note 初始化预处理模块模式数据
     */
    void IniDefalutPattern();
    /**
     * @brief IniDefalutPattern
     * @author szj
     * @date 2017/05/08
     * @note 初始化预处理模块数据
     */
    void IniData();
private slots:

    void OperateSlots(int iOperate, int itaskKind, int value, int current);

    void on_btnOk_clicked();

    void on_btnQuit_clicked();

    void on_listWidgetPattern_clicked(const QModelIndex &index);

    void on_listWidget_clicked(const QModelIndex &index);

private:
    Ui::ImagepreprocessDlg *ui;
    int m_image_out_src;
    PRE_MODEL_CFG m_cfg;
    QMap<int,STRUCT_FUN_PTR>m_fun_ptr;
    /**
     * @brief InitFunPtr
     * @author szj
     * @date 2017/05/08
     * @note 初始化函数指针
     */
    void InitFunPtr();
    /**
     * @brief ClearList
     * @param pListWidget 列表控件
     * @author szj
     * @date 2017/05/08
     * @note 清空列表
     */
    void ClearList(QListWidget *pListWidget);
    /**
     * @brief AddItemData
     * @param strName 列表名称
     * @param index 预处理模块ID
     * @param bCheck 是否使能
     * @author szj
     * @date 2017/05/08
     * @note 增加列表数据
     */
    void AddItemData(QString strName, int index, int bCheck, int current);
    /**
     * @brief DefalutOne
     * @author szj
     * @date 2017/05/08
     * @note 模式一
     */
    void DefalutOne();
    /**
     * @brief DefalutTwo
     * @author szj
     * @date 2017/05/08
     * @note 模式二
     */
    void DefalutTwo();
    /**
     * @brief DefalutThree
     * @author szj
     * @date 2017/05/08
     * @note 模式三
     */
    void DefalutThree();
    /**
     * @brief GetImageOutPut
     * @return 返回最后一个图像输出源
     * @author szj
     * @date 2017/05/08
     * @note 配置预处理模块输入源
     */
    int GetImageOutPut();
    void ListInformation(QString strInfo);
    QString GetInfoByTaskID(int taskId);
};

#endif // IMAGEPREPROCESSDLG_H
