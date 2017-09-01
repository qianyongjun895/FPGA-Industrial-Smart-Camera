/**
  * @file  [ControlStyle.h]
  * @brief
  * @author  <szj>
  * @date  <2017/05/09>
  * @version  <1.0>
  * @note
  * detailed  description
  */
#ifndef CONTROLSTYLE_H
#define CONTROLSTYLE_H

#include <QObject>
#include <QTabWidget>
#include <QPushButton>
#include <QToolButton>
/**
  * @class  <ControlStyle>  [ControlStyle.h]  [ControlStyle]
  * @brief  控件样式表
  * @author  <szj>
  * @note
  * detailed  description
  */
class ControlStyle
{
public:
    ControlStyle();
    /**
     * @brief SetTabBar Qtabwidget样式
     * @param tabWidget Qtabwidget控件
     * @return 空
     * @author szj
     * @date 2017/05/09
     * @note 设置Qtabwidget样式
     */
    static void SetTabBar(QTabWidget *tabWidget);
    /**
     * @brief SetTabBar QPushButton样式
     * @param  QPushButton之前控件
     * @param  QPushButton当前控件
     * @return 空
     * @author szj
     * @date 2017/05/09
     * @note 设置QPushButton样式
     */
    static void SetButtonStyle(QPushButton *pre, QPushButton *current);
    /**
     * @brief SetTabBar QPushButton样式
     * @param  QPushButton之前控件
     * @param  QPushButton当前控件
     * @param  strStyle 样式字任串
     * @return 空
     * @author szj
     * @date 2017/05/09
     * @note 设置QPushButton样式
     */
    static void SetButtonStyle(QPushButton *pre, QPushButton *current,QString strStyle);
    /**
     * @brief SetTabBar QToolButton样式
     * @param  QToolButton之前控件
     * @param  QToolButton当前控件
     * @return 空
     * @author szj
     * @date 2017/05/09
     * @note 设置QToolButton样式
     */
    static void SetToolButtonStyle(QToolButton *pre, QToolButton *current);
    /**
     * @brief SetToolButtonStyle
     * @param pre QToolButton之前控件
     * @param current QToolButton当前控件
     * @param strStyle 样式字任串
     * @return 空
     * @author szj
     * @date 2017/05/09
     * @note 设置QToolButton样式
     */
    static void SetToolButtonStyle(QToolButton *pre, QToolButton *current,QString strStyle);
};

#endif // CONTROLSTYLE_H
