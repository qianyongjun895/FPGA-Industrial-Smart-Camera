#include "CondJumpListItem.h"
#include "ui_CondJumpListItem.h"

CondJumpListItem::CondJumpListItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CondJumpListItem)
{
    ui->setupUi(this);
}

CondJumpListItem::~CondJumpListItem()
{
    delete ui;
}

/**
 * @brief CondJumpListItem::SetJumpSetpName
 * @param strName
 * @author dgq
 * @note 设置跳转步骤名字
 */
void CondJumpListItem::SetJumpSetpName(QString strName)
{
    ui->labelJumpStepName->setText(strName);
}

/**
 * @brief CondJumpListItem::SetCheckboxState
 * @param bflag
 * @author dgq
 * @note 设置取反标志
 */
void CondJumpListItem::SetCheckboxState(bool bflag)
{
    ui->checkBoxOr->setChecked(bflag);
}

/**
 * @brief CondJumpListItem::GetJumpSetpName
 * @return
 * @author dgq
 * @note 获取跳转步骤名称
 */
QString CondJumpListItem::GetJumpSetpName()
{
    return ui->labelJumpStepName->text();
}

/**
 * @brief CondJumpListItem::GetCheckboxState
 * @return
 * @author dgq
 * @note 获取取反标志
 */
bool CondJumpListItem::GetCheckboxState()
{

    if(ui->checkBoxOr->isChecked())
    {
        return true;
    }else
    {

        return false;
    }
}
