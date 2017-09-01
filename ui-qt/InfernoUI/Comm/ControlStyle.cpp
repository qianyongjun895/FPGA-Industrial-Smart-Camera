#include "ControlStyle.h"

ControlStyle::ControlStyle()
{

}
void ControlStyle::SetTabBar(QTabWidget *tabWidget)
{
    QString tabBarStyle = "QTabBar::tab {min-width:80px;color: rgb(0,0,0);border: 1px solid;border-top-left-radius: 10px;border-top-right-radius: 10px;padding:5px;}\
    QTabBar::tab:!selected {margin-top: 5px;background: rgb(230, 230, 230);} \
    QTabBar::tab:selected {color: rgb(0,0,0);background: rgb(249,220, 117);}";
    tabWidget->setStyleSheet(tabBarStyle);
}
void ControlStyle::SetButtonStyle(QPushButton *pre, QPushButton *current)
{
    /*if(pre != NULL)
        pre->setStyleSheet("background-color: rgb(238, 238, 238);");

    if(current != NULL)
        current->setStyleSheet("background-color: rgb(174, 220, 255);");*/
    if(pre != NULL)
    {
        pre->setStyleSheet("background-color: rgb(77, 77, 77);");
    }
    if(current != NULL)
    {
        current->setStyleSheet("background-color: rgb(249, 220, 117);");
    }
}
void ControlStyle::SetButtonStyle(QPushButton *pre, QPushButton *current,QString strStyle)
{
    if(pre != NULL)
    {
        pre->setStyleSheet(strStyle);
    }
    if(current != NULL)
    {
        current->setStyleSheet(strStyle);
    }
}
void ControlStyle::SetToolButtonStyle(QToolButton *pre, QToolButton *current)
{
    /*if(pre != NULL)
        pre->setStyleSheet("background-color: rgb(238, 238, 238);");

    if(current != NULL)
        current->setStyleSheet("background-color: rgb(174, 220, 255);");*/
    if(pre != NULL)
    {
        pre->setStyleSheet("background-color: rgb(150, 150, 150);");
    }
    if(current != NULL)
    {
        current->setStyleSheet("background-color: rgb(249, 220, 117);");
    }
}
void ControlStyle::SetToolButtonStyle(QToolButton *pre, QToolButton *current,QString strStyle)
{
    if(pre != NULL)
    {
        pre->setStyleSheet(strStyle);
    }
    if(current != NULL)
    {
        current->setStyleSheet(strStyle);
    }
}
