#include "CommandJumpWidget.h"
#include "ui_CommandJumpWidget.h"
#include <QMessageBox>
#include <qdebug.h>

CommandJumpWidget::CommandJumpWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CommandJumpWidget)
{
    ui->setupUi(this);
}

CommandJumpWidget::~CommandJumpWidget()
{
    delete ui;
}

/**
 * @brief CommandJumpWidget::Init_Input_Ptr
 * @param ptr 输入结构体内存指针
 * @param i_step_index 当前步骤的步骤索引
 * @author dgq
 * @note 将当前步骤的输入结构体指针传到编辑界面
 */
void CommandJumpWidget::Init_Input_Ptr(void *ptr,int i_step_index,int new_flag,void *pen_color)
{
    pInputPara = ptr;
    m_step_index = i_step_index;
    if(pInputPara == NULL)
    {
        QMessageBox::about(this,tr(""),tr("pInputPara"));
        return;
    }
    if(new_flag)
    {
        Task_Step_Synthetic_Judge_Flag_Set(i_step_index,1);
        ((CMD_JUMP_INPUT_PARAM*)pInputPara)->cmd_count = 0;
        ((CMD_JUMP_INPUT_PARAM*)pInputPara)->target_step = 0;


    }
    InitData(i_step_index);
}


/**
 * @brief CommandJumpWidget::Set_Parameter_To_Ram
 * @author dgq
 * @note 将界面的配置参数写入内存
 */
int CommandJumpWidget::Set_Parameter_To_Ram()
{
    int i_cmd_cnt = ui->tabJumpData->rowCount();
    if(i_cmd_cnt == 0)
    {
        return 0;
    }
    ((CMD_JUMP_INPUT_PARAM*)pInputPara)->cmd_count = i_cmd_cnt;
    void *pPrivate = Task_Step_Private_Para_Get(m_step_index);

    for(int i = 0; i < i_cmd_cnt; i++)
    {
        QTableWidgetItem *item = ui->tabJumpData->item(i,1);
        if(item != NULL)
        {
            int i_index = atoi(item->text().toStdString().c_str());
            ((CMD_JUMP_PRIVATE_PARAM *)pPrivate)->Trigger[i].step_index = i_index;
        }
        item = ui->tabJumpData->item(i,0);
        if(item != NULL)
        {
            QString str_cmd = item->text();
            QByteArray ba = str_cmd.toLatin1();
            char *data = ba.data();
            memset(((CMD_JUMP_PRIVATE_PARAM *)pPrivate)->Trigger[i].Trigger_data,0,TRIGGER_STR_LEN);
            memcpy(((CMD_JUMP_PRIVATE_PARAM *)pPrivate)->Trigger[i].Trigger_data,data,str_cmd.length());
        }

        item = ui->tabJumpData->item(i,2);
        if(item != NULL)
        {
            QString strAddr = item->text();
            ((CMD_JUMP_PRIVATE_PARAM *)pPrivate)->Trigger[i].addr = strAddr.toInt();
        }
        item = ui->tabJumpData->item(i,3);
        if(item != NULL)
        {
            QString strNum = item->text();
            ((CMD_JUMP_PRIVATE_PARAM *)pPrivate)->Trigger[i].data_cnt = strNum.toInt();
        }
        item = ui->tabJumpData->item(i,4);
        if(item != NULL)
        {
            QString strDataType = item->text();
            ((CMD_JUMP_PRIVATE_PARAM *)pPrivate)->Trigger[i].data_type = GetDataTypeIndex(strDataType);
        }
        item = ui->tabJumpData->item(i,5);
        if(item != NULL)
        {
            QString strSplit = item->text();
            ((CMD_JUMP_PRIVATE_PARAM *)pPrivate)->Trigger[i].separator = strSplit.toUtf8().data()[0];

        }
        item = ui->tabJumpData->item(i,6);
        if(item != NULL)
        {
            QString strEndSymple = item->text();
            ((CMD_JUMP_PRIVATE_PARAM *)pPrivate)->Trigger[i].end_char = strEndSymple.toUtf8().data()[0];
        }
    }
    return 1;
}

/**
 * @brief CommandJumpWidget::InitData
 * @param i_step_index
 * @author dgq
 * @note 初始化加载配置参数
 */
void CommandJumpWidget::InitData(int i_step_index)
{
    int i_cmd_cnt =((CMD_JUMP_INPUT_PARAM*)pInputPara)->cmd_count;

    //初始化界面
    QStringList  HStrList;
    HStrList.push_back(QString("跳转命令"));
    HStrList.push_back(QString("跳转步骤"));
    HStrList.push_back(QString("保存地址"));
    HStrList.push_back(QString("数量"));
    HStrList.push_back(QString("数据类型"));
    HStrList.push_back(QString("分隔符"));
    HStrList.push_back(QString("结束符"));

    //设置行列数(只有列存在的前提下，才可以设置列标签)
    int HlableCnt = HStrList.count();
    ui->tabJumpData->setRowCount(0);
    ui->tabJumpData->setColumnCount(HlableCnt);
    //设置列标签
    ui->tabJumpData->setHorizontalHeaderLabels(HStrList);
    ui->tabJumpData->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tabJumpData->setColumnWidth(0,260);
    ui->tabJumpData->setColumnWidth(1,220);
    ui->tabJumpData->setColumnWidth(2,80);
    ui->tabJumpData->setColumnWidth(3,50);
    ui->tabJumpData->setColumnWidth(4,100);
    ui->tabJumpData->setColumnWidth(5,60);
    ui->tabJumpData->setColumnWidth(6,60);
    //设置只读
    ui->tabJumpData->setEditTriggers(QAbstractItemView::NoEditTriggers);
    for(unsigned int i = 0; i <= i_cmd_cnt; i++)
    {

        void *pPrivate = Task_Step_Private_Para_Get(m_step_index);
        char *data = ((CMD_JUMP_PRIVATE_PARAM *)pPrivate)->Trigger[i].Trigger_data;
        memcpy(data,((CMD_JUMP_PRIVATE_PARAM *)pPrivate)->Trigger[i].Trigger_data,TRIGGER_STR_LEN);
//        QString cmdStr = QString::fromUtf8(((CMD_JUMP_PRIVATE_PARAM *)pPrivate)->Trigger[i].Trigger_data);
        QString cmdStr = QString::fromUtf8(data);
        int index = ((CMD_JUMP_PRIVATE_PARAM *)pPrivate)->Trigger[i].step_index;

        if(index < 1)
        {
            continue;
        }
        char taskName[40];
        unsigned int task_type;
        int ret = Task_Step_Type_ID_Get(index,&task_type);

        if(ret == 0)
        {
            memset(taskName, 0, 40);
            int ret = Get_Task_Name(index, taskName);

            if(ret != -1)
            {
                int count = (int)((CMD_JUMP_PRIVATE_PARAM *)pPrivate)->Trigger[i].data_cnt;
                QString strCount = QString::number(count);
                int iAddr = (int )((CMD_JUMP_PRIVATE_PARAM *)pPrivate)->Trigger[i].addr;
                QString strAddr = QString::number(iAddr);
                int dataType = ((CMD_JUMP_PRIVATE_PARAM *)pPrivate)->Trigger[i].data_type;
                QString strDataType = GetStrDataType(dataType);
                char buf[2];
                memset(buf,0,sizeof(buf));
                buf[0]= ((CMD_JUMP_PRIVATE_PARAM *)pPrivate)->Trigger[i].separator;
                QString strSplit = QString::fromUtf8(buf);
                buf[0] = ((CMD_JUMP_PRIVATE_PARAM *)pPrivate)->Trigger[i].end_char;
                QString strEnd = QString::fromUtf8(buf);
                QString strTaskName = (QString::number(index) +"."+ QString::fromUtf8(taskName));

                InitTableData(cmdStr, \
                              strTaskName, \
                              strAddr, \
                              strCount, \
                              strDataType, \
                              strSplit, \
                              strEnd);
            }
        }
    }
}
QString CommandJumpWidget::GetStrDataType(int index)
{
    QString str = "";
    if(index == DATA_SINT)
    {
        str = "整型";
    }else if(index == DATA_UINT)
    {
        str = "无符号整型";
    }else if(index == DATA_FLT)
    {
        str = "浮点型";
    }else if(index == DATA_DBL)
    {
        str = "双精度型";
    }else
    {
        str = "整型";
    }
    return str;
}
int CommandJumpWidget::GetDataTypeIndex(QString strName)
{
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
    return index;
}
/**
 * @brief CommandJumpWidget::InitTableData
 * @param strJumpCmdValue 跳转命令
 * @param strJumpStepValue 跳转步骤
 * @author dgq
 * @note 数据列表新建一行
 */
void CommandJumpWidget::InitTableData(QString strJumpCmdValue, \
                                      QString strJumpStepValue, \
                                      QString strAddr, \
                                      QString strNum, \
                                      QString  strDataType,\
                                      QString strSPlit, \
                                      QString strEnd)
{

    int row = ui->tabJumpData->rowCount();
    ui->tabJumpData->setRowCount(row+1);
    ui->tabJumpData->setItem(row, 0, new QTableWidgetItem(strJumpCmdValue));
    ui->tabJumpData->setItem(row, 1, new QTableWidgetItem(strJumpStepValue));
    ui->tabJumpData->setItem(row, 2, new QTableWidgetItem(strAddr));
    ui->tabJumpData->setItem(row, 3, new QTableWidgetItem(strNum));
    ui->tabJumpData->setItem(row, 4, new QTableWidgetItem(strDataType));
    ui->tabJumpData->setItem(row, 5, new QTableWidgetItem(strSPlit));
    ui->tabJumpData->setItem(row, 6, new QTableWidgetItem(strEnd));
}

/**
 * @brief CommandJumpWidget::on_btnAdd_clicked
 * @author dgq
 * @note 添加按钮响应函数
 */
void CommandJumpWidget::on_btnAdd_clicked()
{

    int row = ui->tabJumpData->rowCount();

    if(row < 50)
    {
        int ret;
        CommandJumpSetDialog dlg(m_step_index);
        ret = dlg.exec();
        if(ret == QDialog::Accepted)
        {
            //将数据增加到表格中
            QString str_cmd = dlg.GetJumpCmdValue();
            for(int i = 0; i < ui->tabJumpData->rowCount();i++)
            {
                QTableWidgetItem *item = ui->tabJumpData->item(i,0);
                if(item == NULL)
                {
                    return;
                }
                else if(str_cmd == item->text())
                {
                    QMessageBox::about(NULL,tr("提示"),tr("命令已存在，添加失败"));
                    return;
                }
            }
            InitTableData(str_cmd,dlg.GetJumpStepValue(),dlg.str_SaveAdr,dlg.str_Num,GetStrDataType(dlg.m_i_data_type),dlg.str_Split,dlg.str_End_Symbol);
        }
    }else
    {
        QMessageBox::about(NULL,tr("提示"),tr("最大只能添加50条数据"));
    }
}

/**
 * @brief CommandJumpWidget::on_btnDelete_clicked
 * @author dgq
 * @note 删除按钮响应函数
 */
void CommandJumpWidget::on_btnDelete_clicked()
{
    int rowIndex = ui->tabJumpData->currentRow();
    if (rowIndex != -1)
    {
        QMessageBox::StandardButton rb = QMessageBox::warning(NULL, tr("警告"), tr("确定要删除列表中数据?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

        if(rb == QMessageBox::Yes)
        {
            ui->tabJumpData->removeRow(rowIndex);
        }
    }
}

/**
 * @brief CommandJumpWidget::on_btn_Edit_clicked
 * @author dgq
 * @note 编辑按钮响应函数
 */
void CommandJumpWidget::on_btn_Edit_clicked()
{
    int row = ui->tabJumpData->currentRow();
    if( row > -1)
    {
        int ret;
        QString str_cmd_jump;
        QString str_Jump_Step;
        CommandJumpSetDialog dlg(m_step_index);
        QTableWidgetItem * item1 = new QTableWidgetItem;
        item1 = ui->tabJumpData->item(row,0);
        str_cmd_jump = item1->text();
        item1 = ui->tabJumpData->item(row,1);
        str_Jump_Step =item1->text();

        item1 = ui->tabJumpData->item(row,2);
        if(item1 != NULL)
        {
            QString strAddr = item1->text();
            dlg.str_SaveAdr = strAddr;

        }
        item1 = ui->tabJumpData->item(row,3);
        if(item1 != NULL)
        {
            QString strNum = item1->text();
            dlg.str_Num = strNum;
        }
        item1 = ui->tabJumpData->item(row,4);
        if(item1 != NULL)
        {
            QString strDataType = item1->text();
            dlg.m_i_data_type = GetDataTypeIndex(strDataType);

        }
        item1 = ui->tabJumpData->item(row,5);
        if(item1 != NULL)
        {
            QString strSplit = item1->text();
            dlg.str_Split = strSplit;

        }
        item1 = ui->tabJumpData->item(row,6);
        if(item1 != NULL)
        {
            QString strEndSymple = item1->text();
            dlg.str_End_Symbol = strEndSymple;
        }
        dlg.IniEditData(str_cmd_jump,str_Jump_Step);
        ret = dlg.exec();

        if(ret == QDialog::Accepted)
        {
            QString str_cmd = dlg.GetJumpCmdValue();
            for(int i = 0; i < ui->tabJumpData->rowCount();i++)
            {
                if(row == i)
                {
                    continue;
                }
                QTableWidgetItem *item = ui->tabJumpData->item(i,0);
                if(item == NULL)
                {
                    return;
                }
                else if(str_cmd == item->text())
                {
                    QMessageBox::about(NULL,tr("提示"),tr("命令已存在，修改失败"));
                    return;
                }
            }

            ui->tabJumpData->setItem(row, 0, new QTableWidgetItem(str_cmd));
            ui->tabJumpData->setItem(row, 1, new QTableWidgetItem(dlg.GetJumpStepValue()));
            ui->tabJumpData->setItem(row, 2, new QTableWidgetItem(dlg.str_SaveAdr));
            ui->tabJumpData->setItem(row, 3, new QTableWidgetItem(dlg.str_Num));
            ui->tabJumpData->setItem(row, 4, new QTableWidgetItem(GetStrDataType(dlg.m_i_data_type)));
            ui->tabJumpData->setItem(row, 5, new QTableWidgetItem(dlg.str_Split));
            ui->tabJumpData->setItem(row, 6, new QTableWidgetItem(dlg.str_End_Symbol));


        }
    }
    else{
        QMessageBox::about(NULL,tr("提示"),tr("请选择要编辑数据"));
    }
}
