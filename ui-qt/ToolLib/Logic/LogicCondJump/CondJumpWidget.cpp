#include <QDebug>
#include "CondJumpWidget.h"
#include "ui_CondJumpWidget.h"
#include <QMessageBox>
#include "LinkDataGlobal.h"
#include "CondJumpListItem.h"

CondJumpWidget::CondJumpWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CondJumpWidget)
{
    m_ok_io = 1;
    m_ng_io = 2;
    ui->setupUi(this);
}

CondJumpWidget::~CondJumpWidget()
{
    delete ui;
}

/**
 * @brief CondJumpWidget::Init_Input_Ptr
 * @param ptr input结构体指针
 * @param i_step_index 当前步骤号
 * @param new_flag 新加步骤标志：1新加，0编辑
 * @author dgq
 * @note 初始化设置Input结构体指针
 */
void CondJumpWidget::Init_Input_Ptr(void *ptr,int i_step_index,int new_flag,void *pen_color)
{
    pInputPara = ptr;
    m_step_index = i_step_index;
    if(pInputPara == NULL)
    {
        QMessageBox::about(this,tr(""),tr("初始化数据失败,初始化失败"));
        return;
    }
    if(new_flag)
    {
        Task_Step_Synthetic_Judge_Flag_Set(i_step_index,1);
        ((CONDITION_JUMP_INPUT_PARAM*)pInputPara)->ok_jump_index = 0;
        ((CONDITION_JUMP_INPUT_PARAM*)pInputPara)->ng_jump_index = 0;
        ((CONDITION_JUMP_INPUT_PARAM*)pInputPara)->ok_io = 0;
        ((CONDITION_JUMP_INPUT_PARAM*)pInputPara)->ng_io = 0;
        ((CONDITION_JUMP_INPUT_PARAM*)pInputPara)->and_or = 0;
        memset(((CONDITION_JUMP_INPUT_PARAM*)pInputPara)->link_step_bitmap,0,8);
        memset(((CONDITION_JUMP_INPUT_PARAM*)pInputPara)->link_step_bitmap,0,8);
    }
    InitData(i_step_index);
}

/**
 * @brief CondJumpWidget::Set_Parameter_To_Ram
 * @return 1成功，0失败
 * @author dgq
 * @note 将界面参数写入内存
 */
int CondJumpWidget::Set_Parameter_To_Ram()
{
    ((CONDITION_JUMP_INPUT_PARAM*)pInputPara)->ok_jump_index = atoi(ui->comboBoxOKJump->currentText().toStdString().c_str());
    ((CONDITION_JUMP_INPUT_PARAM*)pInputPara)->ng_jump_index = atoi(ui->comboBoxNGJump->currentText().toStdString().c_str());
    ((CONDITION_JUMP_INPUT_PARAM*)pInputPara)->ok_io = m_ok_io;
    ((CONDITION_JUMP_INPUT_PARAM*)pInputPara)->ng_io = m_ng_io;
    if(ui->radioButtonAndAll->isChecked())
    {
        ((CONDITION_JUMP_INPUT_PARAM*)pInputPara)->and_or = 0;
    }else
    {
        ((CONDITION_JUMP_INPUT_PARAM*)pInputPara)->and_or = 1;
    }
    int cnt = ui->listWidgetAssociationStepsData->count();
    if(cnt == 0)
    {
        return 0;
    }
    for(int i = 0; i < cnt;i++)
    {
        QListWidgetItem *item =  ui->listWidgetAssociationStepsData->item(i);
        QWidget *qWidget = ui->listWidgetAssociationStepsData->itemWidget(item);
        QString strJumpStepName = ((CondJumpListItem*)qWidget)->GetJumpSetpName();
        int iposition = strJumpStepName.indexOf('.');
        int index = strJumpStepName.left(iposition).toInt();
//        bitmap_set_bit(((CONDITION_JUMP_INPUT_PARAM*)pInputPara)->link_step_bitmap,index);
        SetCorrelationStep(1,index-1);

        bool bflag = ((CondJumpListItem*)qWidget)->GetCheckboxState();
        if(bflag)
        {
            SetCorrelationStepNegation(index-1, 1);
        }else
        {
            SetCorrelationStepNegation(index-1, 0);
        }
    }
    return 1;

}

/**
 * @brief CondJumpWidget::InitData
 * @param i_step_index
 * @author dgq
 * @note 初始化界面显示
 */
void CondJumpWidget::InitData(int i_step_index)
{
    ui->comboBoxOKJump->addItem(" ");
    ui->comboBoxNGJump->addItem(" ");
    ui->cmbAssociationSteps->addItem(" ");
    int i_task_cnt = GetTaskStepCount();
    int i = 0;
    for(i = 0;i < i_task_cnt;i++)
    {
        char taskName[40];
        unsigned int task_type;
        int ret = Task_Step_Type_ID_Get(i+1,&task_type);
        if(ret == 0)
        {
            memset(taskName, 0, 40);
            int ret = Get_Task_Name(i+1, taskName);
            if(ret != -1)
            {
                if(i < i_step_index-1)
                {
                    ui->cmbAssociationSteps->addItem(QString::number(i+1) +"."+ QString::fromUtf8(taskName));
                }
                if(i > i_step_index - 1)
                {
                    ui->comboBoxOKJump->addItem(QString::number(i+1) +"."+ QString::fromUtf8(taskName));
                    ui->comboBoxNGJump->addItem(QString::number(i+1) +"."+ QString::fromUtf8(taskName));
                }
            }
        }
        int iTask  = GetCorrelationStep(i);
        if(iTask == 0)
            continue;
        ret = Task_Step_Type_ID_Get(i+1,&task_type);
        if(!ret)
        {
            memset(taskName, 0, 40);
            int ret = Get_Task_Name(i+1, taskName);
            if(ret != -1)
            {
                QString strTask = QString::number(i+1) +"."+ QString::fromUtf8(taskName);
                int iNegation= GetCorrelationStepNegation(i);
                int size =ui->listWidgetAssociationStepsData->count();
                CondJumpListItem *dlg = new CondJumpListItem();
                QListWidgetItem* mItem = new QListWidgetItem(ui->listWidgetAssociationStepsData);
                dlg->SetJumpSetpName(strTask);

                if(iNegation > 0)
                    dlg->SetCheckboxState(true);
                else
                    dlg->SetCheckboxState(false);

                ui->listWidgetAssociationStepsData->setItemWidget(mItem,(QWidget*)dlg);
                ui->listWidgetAssociationStepsData->item(size)->setSizeHint(QSize(300,30));
            }
        }
    }
    int i_ok_jump = ((CONDITION_JUMP_INPUT_PARAM*)pInputPara)->ok_jump_index ;
    int i_ng_jump = ((CONDITION_JUMP_INPUT_PARAM*)pInputPara)->ng_jump_index ;

    for( i = 0; i< ui->comboBoxOKJump->count();i++)
    {
        QString strTask_ok = ui->comboBoxOKJump->itemText(i);
        QString strTask_ng = ui->comboBoxNGJump->itemText(i);


        if(i_ok_jump == atoi(strTask_ok.toStdString().c_str()))
        {
            ui->comboBoxOKJump->setCurrentIndex(i);
            if(i_ok_jump > i_ng_jump)
            {
                break;
            }
        }
        if(i_ng_jump == atoi(strTask_ng.toStdString().c_str()))
        {
            ui->comboBoxNGJump->setCurrentIndex(i);
            if(i_ok_jump < i_ng_jump)
            {
                break;
            }
        }
    }
    if(((CONDITION_JUMP_INPUT_PARAM*)pInputPara)->and_or == 1)
    {
        ui->radioButtonAndAll->setChecked(false);
        ui->radioButtonNotAll->setChecked(true);
    }
    else
    {
        ui->radioButtonAndAll->setChecked(true);
        ui->radioButtonNotAll->setChecked(false);
    }

    if(((CONDITION_JUMP_INPUT_PARAM*)pInputPara)->ok_io != 0)
    {
        ui->checkBoxOKIO->setChecked(true);
        SetOKChecked(((CONDITION_JUMP_INPUT_PARAM*)pInputPara)->ok_io);
    }
    else
    {
        ui->radioButtonOKIO1->setEnabled(false);
        ui->radioButtonOKIO2->setEnabled(false);
        ui->radioButtonOKIO3->setEnabled(false);
        ui->radioButtonOKIO4->setEnabled(false);
    }

    if(((CONDITION_JUMP_INPUT_PARAM*)pInputPara)->ng_io != 0)
    {
        ui->checkBoxNGIO->setChecked(true);
        SetNGChecked(((CONDITION_JUMP_INPUT_PARAM*)pInputPara)->ng_io);
    }
    else
    {
        ui->radioButtonNGIO1->setEnabled(false);
        ui->radioButtonNGIO2->setEnabled(false);
        ui->radioButtonNGIO3->setEnabled(false);
        ui->radioButtonNGIO4->setEnabled(false);
    }

    connect(ui->comboBoxOKJump, SIGNAL(currentIndexChanged(int)), this, SLOT(OKComboBoxChangeSlot(int)));
    connect(ui->comboBoxNGJump, SIGNAL(currentIndexChanged(int)), this, SLOT(NGComboBoxChangeSlot(int)));
    connect(ui->checkBoxOKIO, &QCheckBox::released, this, &CondJumpWidget::OKCheckBoxSlot);
    connect(ui->checkBoxNGIO, &QCheckBox::released, this, &CondJumpWidget::NGCheckBoxSlot);
    connect(ui->radioButtonOKIO1, &QRadioButton::released, this, &CondJumpWidget::CheckButtonOKIO1Slot);
    connect(ui->radioButtonOKIO2, &QRadioButton::released, this, &CondJumpWidget::CheckButtonOKIO2Slot);
    connect(ui->radioButtonOKIO3, &QRadioButton::released, this, &CondJumpWidget::CheckButtonOKIO3Slot);
    connect(ui->radioButtonOKIO4, &QRadioButton::released, this, &CondJumpWidget::CheckButtonOKIO4Slot);
    connect(ui->radioButtonNGIO1, &QRadioButton::released, this, &CondJumpWidget::CheckButtonNGIO1Slot);
    connect(ui->radioButtonNGIO2, &QRadioButton::released, this, &CondJumpWidget::CheckButtonNGIO2Slot);
    connect(ui->radioButtonNGIO3, &QRadioButton::released, this, &CondJumpWidget::CheckButtonNGIO3Slot);
    connect(ui->radioButtonNGIO4, &QRadioButton::released, this, &CondJumpWidget::CheckButtonNGIO4Slot);

}

/**
 * @brief CondJumpWidget::OKComboBoxChangeSlot
 * @param index
 * @author dgq
 * @note Ok跳转步骤下拉框索引改变响应函数
 */
void CondJumpWidget::OKComboBoxChangeSlot(int index)
{
    Q_UNUSED(index);
    int current_index =atoi(ui->comboBoxOKJump->currentText().toStdString().c_str());
    if(current_index <= m_step_index)
    {
        QMessageBox::warning(NULL, tr("Warning"), tr("跳转到本步任务或本步任务之前，有可能导致运行进入死循环!"), QMessageBox::Ok,  QMessageBox::Ok);
    }
    ((CONDITION_JUMP_INPUT_PARAM*)pInputPara)->ok_jump_index =current_index;
}

//ng关联数据下拉框
/**
 * @brief CondJumpWidget::NGComboBoxChangeSlot
 * @param index
 * @author dgq
 * @note NG跳转步骤下拉框索引改变响应函数
 */
void CondJumpWidget::NGComboBoxChangeSlot(int index)
{
    Q_UNUSED(index);
    int current_index =atoi(ui->comboBoxNGJump->currentText().toStdString().c_str());
    if(current_index <= m_step_index)
    {
        QMessageBox::warning(NULL, tr("Warning"), tr("跳转到本步任务或本步任务之前，有可能导致运行进入死循环!"), QMessageBox::Ok,  QMessageBox::Ok);
    }
    ((CONDITION_JUMP_INPUT_PARAM*)pInputPara)->ng_jump_index =current_index;
}

/**
 * @brief CondJumpWidget::SetOKChecked
 * @param IO_index
 * @author dgq
 * @note 设置根据OK IO值选择界面显示效果
 */
void CondJumpWidget::SetOKChecked(unsigned int IO_index)
{
    if(ui->checkBoxNGIO->isChecked() == true)
    {
        ui->radioButtonNGIO1->setEnabled(true);
        ui->radioButtonNGIO2->setEnabled(true);
        ui->radioButtonNGIO3->setEnabled(true);
        ui->radioButtonNGIO4->setEnabled(true);
    }

    switch(IO_index)
    {
    case 1:
        ui->radioButtonOKIO1->setChecked(true);
        ui->radioButtonNGIO1->setEnabled(false);
        ui->radioButtonOKIO2->setChecked(false);
        ui->radioButtonOKIO3->setChecked(false);
        ui->radioButtonOKIO4->setChecked(false);
        break;

    case 2:
        ui->radioButtonOKIO1->setChecked(false);
        ui->radioButtonOKIO2->setChecked(true);
        ui->radioButtonNGIO2->setEnabled(false);
        ui->radioButtonOKIO3->setChecked(false);
        ui->radioButtonOKIO4->setChecked(false);
        break;

    case 4:
        ui->radioButtonOKIO1->setChecked(false);
        ui->radioButtonOKIO2->setChecked(false);
        ui->radioButtonOKIO3->setChecked(true);
        ui->radioButtonNGIO3->setEnabled(false);
        ui->radioButtonOKIO4->setChecked(false);
        break;

    case 8:
        ui->radioButtonOKIO1->setChecked(false);
        ui->radioButtonOKIO2->setChecked(false);
        ui->radioButtonOKIO3->setChecked(false);
        ui->radioButtonOKIO4->setChecked(true);
        ui->radioButtonNGIO4->setEnabled(false);
        break;

    default:
        ((CONDITION_JUMP_INPUT_PARAM*)pInputPara)->ok_io = 1;
        ui->radioButtonOKIO1->setChecked(true);
        ui->radioButtonNGIO1->setEnabled(false);
        ui->radioButtonOKIO2->setChecked(false);
        ui->radioButtonOKIO3->setChecked(false);
        ui->radioButtonOKIO4->setChecked(false);
        break;
    }
}

//设置根据NG IO值选择界面显示效果
/**
 * @brief CondJumpWidget::SetNGChecked
 * @param IO_index
 * @author dgq
 * @note 设置根据NG IO值选择界面显示效果
 */
void CondJumpWidget::SetNGChecked(unsigned int IO_index)
{
    if(ui->checkBoxOKIO->isChecked() == true)
    {
        ui->radioButtonOKIO1->setEnabled(true);
        ui->radioButtonOKIO2->setEnabled(true);
        ui->radioButtonOKIO3->setEnabled(true);
        ui->radioButtonOKIO4->setEnabled(true);
    }

    switch(IO_index)
    {
    case 1:
        ui->radioButtonNGIO1->setChecked(true);
        ui->radioButtonOKIO1->setEnabled(false);
        ui->radioButtonNGIO2->setChecked(false);
        ui->radioButtonNGIO3->setChecked(false);
        ui->radioButtonNGIO4->setChecked(false);
        break;

    case 2:
        ui->radioButtonNGIO1->setChecked(false);
        ui->radioButtonNGIO2->setChecked(true);
        ui->radioButtonOKIO2->setEnabled(false);
        ui->radioButtonNGIO3->setChecked(false);
        ui->radioButtonNGIO4->setChecked(false);
        break;

    case 4:
        ui->radioButtonNGIO1->setChecked(false);
        ui->radioButtonNGIO2->setChecked(false);
        ui->radioButtonNGIO3->setChecked(true);
        ui->radioButtonOKIO3->setEnabled(false);
        ui->radioButtonNGIO4->setChecked(false);
        break;

    case 8:
        ui->radioButtonNGIO1->setChecked(false);
        ui->radioButtonNGIO2->setChecked(false);
        ui->radioButtonNGIO3->setChecked(false);
        ui->radioButtonNGIO4->setChecked(true);
        ui->radioButtonOKIO4->setEnabled(false);
        break;

    default:
        ((CONDITION_JUMP_INPUT_PARAM*)pInputPara)->ng_io = 2;
        ui->radioButtonNGIO1->setChecked(false);
        ui->radioButtonNGIO2->setChecked(true);
        ui->radioButtonOKIO2->setEnabled(false);
        ui->radioButtonNGIO3->setChecked(false);
        ui->radioButtonNGIO4->setChecked(false);
        break;
    }
}

/**
 * @brief CondJumpWidget::OKCheckBoxSlot
 * @author dgq
 * @note OK IO跳转使能按钮点击响应函数
 */
void CondJumpWidget::OKCheckBoxSlot()
{
    if(ui->checkBoxOKIO->isChecked() == true)
    {
        ui->radioButtonOKIO1->setEnabled(true);
        ui->radioButtonOKIO2->setEnabled(true);
        ui->radioButtonOKIO3->setEnabled(true);
        ui->radioButtonOKIO4->setEnabled(true);

        switch(((CONDITION_JUMP_INPUT_PARAM*)pInputPara)->ng_io)
        {
        case 0:

            break;
        case 1:
            ui->radioButtonOKIO1->setEnabled(false);
            break;
        case 2:
            ui->radioButtonOKIO2->setEnabled(false);
            break;
        case 4:
            ui->radioButtonOKIO3->setEnabled(false);
            break;
        case 8:
            ui->radioButtonOKIO4->setEnabled(false);
            break;
        default:
            break;
        }
        SetOKChecked(((CONDITION_JUMP_INPUT_PARAM*)pInputPara)->ok_io);
    }
    else
    {
        ui->radioButtonOKIO1->setEnabled(false);
        ui->radioButtonOKIO2->setEnabled(false);
        ui->radioButtonOKIO3->setEnabled(false);
        ui->radioButtonOKIO4->setEnabled(false);
        if(ui->checkBoxNGIO->isChecked() == true)
        {
            ui->radioButtonNGIO1->setEnabled(true);
            ui->radioButtonNGIO2->setEnabled(true);
            ui->radioButtonNGIO3->setEnabled(true);
            ui->radioButtonNGIO4->setEnabled(true);
        }

    }
}

/**
 * @brief CondJumpWidget::NGCheckBoxSlot
 * @author dgq
 * @note NG IO跳转使能按钮点击响应函数
 */
void CondJumpWidget::NGCheckBoxSlot()
{
    if(ui->checkBoxNGIO->isChecked() == true)
    {
        ui->radioButtonNGIO1->setEnabled(true);
        ui->radioButtonNGIO2->setEnabled(true);
        ui->radioButtonNGIO3->setEnabled(true);
        ui->radioButtonNGIO4->setEnabled(true);

        switch(((CONDITION_JUMP_INPUT_PARAM*)pInputPara)->ok_io)
        {
        case 0:

            break;
        case 1:
            ui->radioButtonNGIO1->setEnabled(false);
            break;
        case 2:
            ui->radioButtonNGIO2->setEnabled(false);
            break;
        case 4:
            ui->radioButtonNGIO3->setEnabled(false);
            break;
        case 8:
            ui->radioButtonNGIO4->setEnabled(false);
            break;
        default:
            break;
        }

        SetNGChecked(((CONDITION_JUMP_INPUT_PARAM*)pInputPara)->ng_io);
    }
    else
    {
        ui->radioButtonNGIO1->setEnabled(false);
        ui->radioButtonNGIO2->setEnabled(false);
        ui->radioButtonNGIO3->setEnabled(false);
        ui->radioButtonNGIO4->setEnabled(false);
        if(ui->checkBoxOKIO->isChecked() == true)
        {
            ui->radioButtonOKIO1->setEnabled(true);
            ui->radioButtonOKIO2->setEnabled(true);
            ui->radioButtonOKIO3->setEnabled(true);
            ui->radioButtonOKIO4->setEnabled(true);
        }
    }
}

/**
 * @brief CondJumpWidget::CheckButtonOKIO1Slot
 * @author dgq
 * @note 选择ok时的IO端口1
 */
void CondJumpWidget::CheckButtonOKIO1Slot()
{
    if(ui->radioButtonOKIO1->isChecked() == true)
    {
        SetOKChecked(1);
        m_ok_io = 1;
    }
}


/**
 * @brief CondJumpWidget::CheckButtonOKIO2Slot
 * @author dgq
 * @note 选择ok时的IO端口2
 */
void CondJumpWidget::CheckButtonOKIO2Slot()
{
    if(ui->radioButtonOKIO2->isChecked() == true)
    {
        SetOKChecked(2);
        m_ok_io = 1;
    }
}

/**
 * @brief CondJumpWidget::CheckButtonOKIO3Slot
 * @author dgq
 * @note 选择ok时的IO端口3
 */
void CondJumpWidget::CheckButtonOKIO3Slot()
{
    if(ui->radioButtonOKIO3->isChecked() == true)
    {
        SetOKChecked(4);
        m_ok_io = 4;
    }
}

/**
 * @brief CondJumpWidget::CheckButtonOKIO4Slot
 * @author dgq
 * @note 选择ok时的IO端口4
 */
void CondJumpWidget::CheckButtonOKIO4Slot()
{
    if(ui->radioButtonOKIO4->isChecked() == true)
    {
        SetOKChecked(8);
        m_ok_io = 8;
    }
}


/**
 * @brief CondJumpWidget::CheckButtonNGIO1Slot
 * @author dgq
 * @note 选择ng时的IO端口1
 */
void CondJumpWidget::CheckButtonNGIO1Slot()
{
    if(ui->radioButtonNGIO1->isChecked() == true)
    {
        SetNGChecked(1);
        m_ng_io = 1;
    }
}

/**
 * @brief CondJumpWidget::CheckButtonNGIO2Slot
 * @author dgq
 * @note 选择ng时的IO端口2
 */
void CondJumpWidget::CheckButtonNGIO2Slot()
{
    if(ui->radioButtonNGIO2->isChecked() == true)
    {
        SetNGChecked(2);
        m_ng_io = 2;
    }
}

/**
 * @brief CondJumpWidget::CheckButtonNGIO3Slot
 * @author dgq
 * @note 选择ng时的IO端口3
 */
void CondJumpWidget::CheckButtonNGIO3Slot()
{
    if(ui->radioButtonNGIO3->isChecked() == true)
    {
        SetNGChecked(4);
        m_ng_io = 4;
    }
}

/**
 * @brief CondJumpWidget::CheckButtonNGIO4Slot
 * @author dgq
 * @note 选择ng时的IO端口4
 */
void CondJumpWidget::CheckButtonNGIO4Slot()
{
    if(ui->radioButtonNGIO4->isChecked() == true)
    {
        SetNGChecked(8);
        m_ng_io = 8;
    }
}

/**
 * @brief CondJumpWidget::on_btnAdd_clicked
 * @author dgq
 * @note 添加按钮响应函数
 */
void CondJumpWidget::on_btnAdd_clicked()
{
    if(ui->cmbAssociationSteps->currentIndex()>=1)
    {
        int size =ui->listWidgetAssociationStepsData->count();
        QString strtemp = ui->cmbAssociationSteps->itemText(ui->cmbAssociationSteps->currentIndex());
        if(IsTaskStepInTable(strtemp))
        {
            QMessageBox::about(NULL,tr("提示"),tr("列表中已存在改步骤，请选择其他步骤!"));
            return;
        }

        CondJumpListItem *dlg = new CondJumpListItem();
        QListWidgetItem* mItem = new QListWidgetItem(ui->listWidgetAssociationStepsData);
        dlg->SetJumpSetpName(strtemp);
        ui->listWidgetAssociationStepsData->setItemWidget(mItem,(QWidget*)dlg);
        ui->listWidgetAssociationStepsData->item(size)->setSizeHint(QSize(300,30));
    }else
    {
        QMessageBox::about(NULL,tr("提示"),tr("请先选择关联步骤"));
    }
}
//判断任务号是否在列表中
/**
 * @brief CondJumpWidget::IsTaskStepInTable
 * @param StrTask
 * @return
 * @author dgq
 * @note 判断选择的任务是否已存在列表中
 */
int CondJumpWidget::IsTaskStepInTable(QString StrTask)
{
    int icount = ui->listWidgetAssociationStepsData->count();
    int i;
    int isIN = 0;
    for(i = 0;i<icount;i++)
    {
        QListWidgetItem *item =  ui->listWidgetAssociationStepsData->item(i);
        QWidget *qWidget = ui->listWidgetAssociationStepsData->itemWidget(item);
        QString strJumpStepName = ((CondJumpListItem*)qWidget)->GetJumpSetpName();

        if(StrTask == strJumpStepName)
        {
            isIN = 1;
            break;
        }
    }
    return isIN;

}
//删除关联步骤列表中的数据
/**
 * @brief CondJumpWidget::on_btnDelete_clicked
 * @author dgq
 * @note 删除关联步骤列表中的数据
 */
void CondJumpWidget::on_btnDelete_clicked()
{
    if(ui->listWidgetAssociationStepsData->currentRow() < 0)
    {
        return;
    }
    QMessageBox::StandardButton rb = QMessageBox::warning(NULL, tr("警告"), tr("确定删除本行数据?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    if(rb == QMessageBox::Yes)
    {
        QListWidgetItem *item1 = ui->listWidgetAssociationStepsData->item(ui->listWidgetAssociationStepsData->currentRow());
        QWidget *widget = ui->listWidgetAssociationStepsData->itemWidget(item1);
        QString task = ((CondJumpListItem*)widget)->GetJumpSetpName();
        int index = atoi(task.toStdString().c_str());
        SetCorrelationStep(0,index-1);
        QListWidgetItem *item =  ui->listWidgetAssociationStepsData->takeItem(ui->listWidgetAssociationStepsData->currentRow());
        delete item;
    }
}


/**********************************************
 *以下函数为写bitmap专用
 *********************************************/

/*
*    获取关联步骤取反标志
*参数   unsigned int:对应的关联步骤-1
*返回   unsigned int:关联步骤取反标志
*@author  th
*@version  v1.0
*/
int CondJumpWidget::GetCorrelationStepNegation(unsigned int step)
{
    int step_index = step / 32;
    int step_bit = step % 32;
    unsigned int ret = ((((CONDITION_JUMP_INPUT_PARAM*)pInputPara)->link_step_negation[step_index] & (0x01 << step_bit)) >> step_bit);
    return ret;
}


/*
*    设置关联步骤取反标志
*参数   unsigned int:对应的关联步骤-1  unsigned int:关联步骤取反标志
*返回   无
*@author  th
*@version  v1.0
*/
int CondJumpWidget::SetCorrelationStepNegation(unsigned int step,unsigned int flag)
{
    unsigned int step_index = step /32;
    unsigned int step_bit = step % 32;

    if(1 == flag)
    {
        ((CONDITION_JUMP_INPUT_PARAM*)pInputPara)->link_step_negation[step_index] |= (0x01 << step_bit);
    }
    else
    {
        ((CONDITION_JUMP_INPUT_PARAM*)pInputPara)->link_step_negation[step_index] &= (~(0x01 << step_bit));
    }
//    printf("g_tTaskParam.ParamStruct.ConditionalJumpParameter.link_step_negation[step_index] = %#x\n",g_tTaskParam.ParamStruct.ConditionalJumpParameter.link_step_negation[step_index]);
}

/*
*    获取关联步骤BITMAP
*参数   unsigned int:对应的关联步骤-1
*返回   unsigned int:BITMAP值
*@author  th
*@version  v1.0
*/
int CondJumpWidget::GetCorrelationStep(unsigned int step)
{

    int step_index = step / 32;
    int step_bit = step % 32;
    unsigned int ret = ((((CONDITION_JUMP_INPUT_PARAM*)pInputPara)->link_step_bitmap[step_index] & (0x01 << step_bit)) >> step_bit);
    //    printf("ret ========= %#x\n",ret);
    return ret;
}

/*
*    设置关联步骤BITMAP
*参数   unsigned int:BITMAP值  unsigned int:对应的关联步骤-1
*返回   无
*@author  th
*@version  v1.0
*/
void CondJumpWidget::SetCorrelationStep(unsigned int bitmap,unsigned int step)
{

    unsigned int step_index = step /32;
    unsigned int step_bit = step % 32;

    if(1 == bitmap)
    {
        ((CONDITION_JUMP_INPUT_PARAM*)pInputPara)->link_step_bitmap[step_index] |= (0x01 << step_bit);
    }
    else
    {
        ((CONDITION_JUMP_INPUT_PARAM*)pInputPara)->link_step_bitmap[step_index] &= (~(0x01 << step_bit));
    }

}
