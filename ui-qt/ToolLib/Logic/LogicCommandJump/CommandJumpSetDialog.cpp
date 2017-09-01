#include <QDebug>
#include "CommandJumpSetDialog.h"
#include "ui_CommandJumpSetDialog.h"
#include "QMessageBox"

CommandJumpSetDialog::CommandJumpSetDialog(int currentIndex,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CommandJumpSetDialog)
{
    ui->setupUi(this);
    LoadKeyBoardLib();
    i_currentIndex = currentIndex;
    //ui->txtTriggerCmd->setText("$jumpto1#");
    ui->txtTriggerCmd->setText("jumpto1");
    ui->txtTriggerCmd->installEventFilter(this);
    ui->txtEndSymbol->installEventFilter(this);
    ui->txtNum->installEventFilter(this);
    ui->txtSaveAdr->installEventFilter(this);
    ui->txtSplit->installEventFilter(this);

    ui->comboBoxDataType->addItem(tr("整型"));
    ui->comboBoxDataType->addItem(tr("无符号整型"));
    ui->comboBoxDataType->addItem(tr("浮点型"));
    ui->comboBoxDataType->addItem(tr("双精度型"));
    Data_type.insert(tr("整型"), DATA_SINT);
    Data_type.insert(tr("无符号整型"), DATA_UINT);
    Data_type.insert(tr("浮点型"), DATA_FLT);
    Data_type.insert(tr("双精度型"), DATA_DBL);
    ui->txtNum->setText("0");
    ui->txtSaveAdr->setText("1");
    TaskGetStepName();


}
CommandJumpSetDialog::~CommandJumpSetDialog()
{
    ui->txtTriggerCmd->removeEventFilter(this);
    ui->txtEndSymbol->removeEventFilter(this);
    ui->txtNum->removeEventFilter(this);
    ui->txtSaveAdr->removeEventFilter(this);
    ui->txtSplit->removeEventFilter(this);
    delete ui;
}
void CommandJumpSetDialog::TaskGetStepName()
{
    int i_task_cnt = GetTaskStepCount();
    int currentIndex = i_currentIndex;
    for(int i = 0;i < i_task_cnt;i++)
    {
        if(i == currentIndex-1)
        {
            continue;
        }
        char taskName[40];
        unsigned int task_type;
        int ret = Task_Step_Type_ID_Get(i+1,&task_type);
        if(ret == 0)
        {
            memset(taskName, 0, 40);
            int ret = Get_Task_Name(i+1, taskName);
            if(ret != -1)
            {
                if(i > i_currentIndex - 1)
                {
                    ui->comboBoxJumpCmdStep->addItem(QString::number(i+1) +"."+ QString::fromUtf8(taskName));
                }
            }
        }

    }
}
/**
 * @brief CommandJumpSetDialog::on_btnOk_clicked
 * @author dgq
 * @note 确认按钮响应函数
 */
void CommandJumpSetDialog::on_btnOk_clicked()
{
    m_str_cmd_jump =  ui->txtTriggerCmd->text();
    m_str_Jump_Step =  ui->comboBoxJumpCmdStep->itemText(ui->comboBoxJumpCmdStep->currentIndex());

    if(m_str_cmd_jump.count() > 10)
    {
        QMessageBox::warning(NULL, tr("警告"), tr("命令长度不能超过10个字符"), QMessageBox::Ok,  QMessageBox::Ok);
        return;
    }

    /*if(m_str_cmd_jump.left(1) != "$")
    {
        QMessageBox::warning(NULL, tr("警告"), tr("命令起始字符必须为$"), QMessageBox::Ok,  QMessageBox::Ok);
        return;
    }
    if(m_str_cmd_jump.right(1) != "#")
    {
        QMessageBox::warning(NULL, tr("警告"), tr("命令结束字符必须为#"), QMessageBox::Ok,  QMessageBox::Ok);
        return;
    }*/

    if(m_str_cmd_jump.length() <= 2)
    {
        QMessageBox::warning(NULL, tr("警告"), tr("命令不能为空，请按格式输入跳转命令"), QMessageBox::Ok,  QMessageBox::Ok);
        return;
    }
    /*if(ui->txtEndSymbol->text() == "")
    {
        QMessageBox::warning(NULL, tr("警告"), tr("结束符不能为空"), QMessageBox::Ok,  QMessageBox::Ok);
        return;
    }*/
    if(ui->txtNum->text() == "")
    {
        QMessageBox::warning(NULL, tr("警告"), tr("分隔符数量不能为空"), QMessageBox::Ok,  QMessageBox::Ok);
        return;
    }
    if(ui->txtSaveAdr->text() == "")
    {
        QMessageBox::warning(NULL, tr("警告"), tr("数据保存地址不能为空"), QMessageBox::Ok,  QMessageBox::Ok);
        return;
    }
    if(ui->txtNum->text().toInt() > 0)
    {
        if(ui->txtSplit->text() == "")
        {
            QMessageBox::warning(NULL, tr("警告"), tr("分隔符不能为空"), QMessageBox::Ok,  QMessageBox::Ok);
            return;
        }
    }
    QString strName = ui->comboBoxDataType->currentText();

    int  index = 0;
    if(strName == "整型")
    {
        index = DATA_SINT;

    }else if(strName == "无符号整型")
    {
        index = DATA_UINT;

    }else if(strName == "浮点型")
    {
        index = DATA_FLT;

    }else if(strName == "双精度型")
    {
        index = DATA_DBL;

    }else
    {
        index = DATA_SINT;
    }
    m_i_data_type = index;

    str_End_Symbol = ui->txtEndSymbol->text();
    str_Num = ui->txtNum->text();
    str_SaveAdr = ui->txtSaveAdr->text();
    str_Split = ui->txtSplit->text();

    QDialog::accept();
}

/**
 * @brief CommandJumpSetDialog::on_btnQuit_clicked
 * @author dgq
 * @note 取消退出
 */
void CommandJumpSetDialog::on_btnQuit_clicked()
{
    QDialog::reject();
}

/**
 * @brief CommandJumpSetDialog::IniEditData
 * @param str_cmd_jump 跳转命令
 * @param str_Jump_Step 跳转步骤
 * @author dgq
 * @note 点击编辑按钮的初始化函数
 */
void CommandJumpSetDialog::IniEditData(QString str_cmd_jump,QString str_Jump_Step)
{
    //    ui->comboBoxJumpCmdStep->clear();
    //    ui->comboBoxJumpCmdStep->addItems(taskList);
    ui->txtTriggerCmd->setText(str_cmd_jump);
    int icount = ui->comboBoxJumpCmdStep->count();
    int i;

    QString strTemp;

    for(i =0; i<icount;i++)
    {
        strTemp = ui->comboBoxJumpCmdStep->itemText(i);
        if(strTemp == str_Jump_Step)
        {
            ui->comboBoxJumpCmdStep->setCurrentIndex(i);
            break;
        }
    }
    ui->txtEndSymbol->setText(str_End_Symbol);
    ui->txtNum->setText(str_Num);
    ui->txtSaveAdr->setText(str_SaveAdr);
    ui->txtSplit->setText(str_Split);
    if(m_i_data_type == DATA_SINT)
    {
        ui->comboBoxDataType->setCurrentIndex(0);
    }else if(m_i_data_type == DATA_UINT)
    {
        ui->comboBoxDataType->setCurrentIndex(1);
    }else if(m_i_data_type == DATA_FLT)
    {
        ui->comboBoxDataType->setCurrentIndex(2);
    }else if(m_i_data_type == DATA_DBL)
    {
        ui->comboBoxDataType->setCurrentIndex(3);
    }
}

/**
 * @brief CommandJumpSetDialog::LoadKeyBoardLib、
 * @author th
 * @note 加载输入软键盘库
 */
void CommandJumpSetDialog::LoadKeyBoardLib()
{
    m_keyBoard_Lib.setFileName("libFrmInputKeyBoard.so");
    if(m_keyBoard_Lib.isLoaded())
    {
        return;
    }
    if(m_keyBoard_Lib.load())
    {
        printf("libFrmInputKeyBoard.so OK\n");
    }
    else
    {
        qDebug()<<"load libFrmInputKeyBoard.so fail"<<m_keyBoard_Lib.errorString();
    }
}

/**
 * @brief CommandJumpSetDialog::eventFilter
 * @param watched
 * @param event
 * @return
 * @author
 * @note 事件过滤器，行文本编辑框模拟鼠标点击事件
 */
bool CommandJumpSetDialog::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->txtTriggerCmd)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            if(((QLineEdit *)watched)->isEnabled())
            {
                Fun_GetkeyBoardDlg GetKeyBoardDlg = (Fun_GetkeyBoardDlg)m_keyBoard_Lib.resolve("GetKeyBoardDialog");
                Fun_GetInputString GetInputString = (Fun_GetInputString)m_keyBoard_Lib.resolve("GetInputString");
                if(GetKeyBoardDlg)
                {
                    QDialog *dlg = GetKeyBoardDlg();
                    Fun_SetInputString SetInputString  = (Fun_SetInputString)m_keyBoard_Lib.resolve("SetInputString");
                    if(SetInputString)
                    {
                        SetInputString(ui->txtTriggerCmd->text());
                    }
                    dlg->move(0, 150);
                    int ret = dlg->exec();
                    if(ret == QDialog::Accepted)
                    {
                        if(GetInputString)
                            ((QLineEdit *)watched)->setText(GetInputString());
                    }
                    delete dlg;
                }
                else
                {
                    qDebug()<<"get GetDialog func fail:"<<m_keyBoard_Lib.errorString();
                }
            }
        }
    }

    if(watched == ui->txtNum)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            if(((QLineEdit *)watched)->isEnabled())
            {
                Fun_GetkeyBoardDlg GetKeyBoardDlg = (Fun_GetkeyBoardDlg)m_keyBoard_Lib.resolve("GetKeyBoardDialog");
                Fun_GetInputString GetInputString = (Fun_GetInputString)m_keyBoard_Lib.resolve("GetInputString");
                if(GetKeyBoardDlg)
                {
                    QDialog *dlg = GetKeyBoardDlg();
                    Fun_SetInputString SetInputString  = (Fun_SetInputString)m_keyBoard_Lib.resolve("SetInputString");
                    if(SetInputString)
                    {
                        SetInputString(ui->txtNum->text());
                    }
                    dlg->move(0, 150);
                    int ret = dlg->exec();
                    if(ret == QDialog::Accepted)
                    {
                        QString strNum = GetInputString();
                        if(strNum.toInt()<0 || strNum.toInt()>256)
                        {
                            QMessageBox::about(NULL,"提示","请输入0到256的数字");
                            return QWidget::eventFilter(watched, event);
                        }
                        if(GetInputString)
                            ((QLineEdit *)watched)->setText(GetInputString());
                    }
                    delete dlg;
                }
                else
                {
                    qDebug()<<"get GetDialog func fail:"<<m_keyBoard_Lib.errorString();
                }
            }
        }
    }
    if(watched == ui->txtSaveAdr)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            if(((QLineEdit *)watched)->isEnabled())
            {
                Fun_GetkeyBoardDlg GetKeyBoardDlg = (Fun_GetkeyBoardDlg)m_keyBoard_Lib.resolve("GetKeyBoardDialog");
                Fun_GetInputString GetInputString = (Fun_GetInputString)m_keyBoard_Lib.resolve("GetInputString");
                if(GetKeyBoardDlg)
                {
                    QDialog *dlg = GetKeyBoardDlg();
                    Fun_SetInputString SetInputString  = (Fun_SetInputString)m_keyBoard_Lib.resolve("SetInputString");
                    if(SetInputString)
                    {
                        SetInputString(ui->txtSaveAdr->text());
                    }
                    dlg->move(0, 150);
                    int ret = dlg->exec();
                    if(ret == QDialog::Accepted)
                    {
                        QString strNum = GetInputString();
                        if(strNum.toInt()<1 || strNum.toInt()>1024)
                        {
                            QMessageBox::about(NULL,"提示","请输入1到1024的数字");
                            return QWidget::eventFilter(watched, event);
                        }
                        if(GetInputString)
                            ((QLineEdit *)watched)->setText(GetInputString());
                    }
                    delete dlg;
                }
                else
                {
                    qDebug()<<"get GetDialog func fail:"<<m_keyBoard_Lib.errorString();
                }
            }
        }
    }
    if(watched == ui->txtEndSymbol || watched == ui->txtSplit)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            if(((QLineEdit *)watched)->isEnabled())
            {
                Fun_GetkeyBoardDlg GetKeyBoardDlg = (Fun_GetkeyBoardDlg)m_keyBoard_Lib.resolve("GetKeyBoardDialog");
                Fun_GetInputString GetInputString = (Fun_GetInputString)m_keyBoard_Lib.resolve("GetInputString");
                if(GetKeyBoardDlg)
                {
                    QDialog *dlg = GetKeyBoardDlg();
                    Fun_SetInputString SetInputString  = (Fun_SetInputString)m_keyBoard_Lib.resolve("SetInputString");
                    if(SetInputString)
                    {
                        SetInputString(((QLineEdit *)watched)->text());
                    }
                    dlg->move(0, 150);
                    int ret = dlg->exec();
                    if(ret == QDialog::Accepted)
                    {
                        QString strNum = GetInputString();
                        if(strNum.length() >1)
                        {
                            QMessageBox::about(NULL,"提示","请输入长度为1的字符");
                            return QWidget::eventFilter(watched, event);
                        }
                        if(GetInputString)
                            ((QLineEdit *)watched)->setText(GetInputString());
                    }
                    delete dlg;
                }
                else
                {
                    qDebug()<<"get GetDialog func fail:"<<m_keyBoard_Lib.errorString();
                }
            }
        }
    }

    return QWidget::eventFilter(watched, event);
}
