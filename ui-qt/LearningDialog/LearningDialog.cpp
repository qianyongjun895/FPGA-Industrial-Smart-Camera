#include "LearningDialog.h"
#include "Learning.h"


LearningDialog::LearningDialog()
{
}
Learning *pDialog = NULL;

/**
 * @brief GetDialog
 * @return
 * @author dgq
 * @note 获取进度条弹窗的界面对象指针
 */
QDialog *GetDialog()
{
    pDialog = new Learning();
    return pDialog;
}

/**
 * @brief ReleaseDialog
 * @param pDlg
 * @author dgq
 * @note 释放进度条弹窗的界面对象指针
 */
void ReleaseDialog(QDialog *pDlg)
{
    if(pDlg != NULL)
    {
        delete pDlg;
        pDlg = NULL;
    }
}


/**
 * @brief SetResultString
 * @param code_string
 * @author dgq
 * @note 设置取样结果信息（成功、失败、错误码等）
 */
void SetResultString(QString code_string)
{
    pDialog->SetResultString(code_string);
}

