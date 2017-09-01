#include <QDebug>
#include "HomoCalcWidget.h"
#include "ui_HomoCalcWidget.h"
#include "TaskStepGlobal.h"
#include "FWHomoCalcLabel.h"
#include "PixelConvert.h"
#include <QMessageBox>
#include "TaskRstGlobal.h"
#include "xmlInitGlobal.h"
#include "LinkDataGlobal.h"

HomoCalcWidget::HomoCalcWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomoCalcWidget)
{
    ui->setupUi(this);
    LoadKeyBoardLib();
    QList<QLineEdit *> lineEdit = this->findChildren<QLineEdit *>();
    foreach (QLineEdit * L, lineEdit) {
        L->installEventFilter(this);
        }
    m_label = new FWHomoCalcLabel(this);
    m_label->setGeometry(10,10,640,480);
    m_label->setAutoFillBackground(true);
    QPalette p = m_label->palette();
    p.setColor(QPalette::Background,QColor(50,50,50,255));
    m_label->setPalette(p);
    connect(ui->comboBoxPoint, SIGNAL(currentIndexChanged(int)), this, SLOT(PointTaskChangeSlot(int)));
    connect(ui->comboBoxPointResult, SIGNAL(activated(int)), this, SLOT(PointResultChangeSlot(int)));
    connect(ui->comboBoxAngle, SIGNAL(currentIndexChanged(int)), this, SLOT(AngleTaskChangeSlot(int)));
    connect(ui->comboBoxAngleResult, SIGNAL(activated(int)), this, SLOT(AngleResultChangeSlot(int)));
}

HomoCalcWidget::~HomoCalcWidget()
{
    QList<QLineEdit *> lineEdit = this->findChildren<QLineEdit *>();
    foreach (QLineEdit * L, lineEdit) {
        L->removeEventFilter(this);
        }
    if(m_label !=NULL)
    {
        delete m_label;
        m_label = NULL;
    }
    delete ui;
}

QPoint HomoCalcWidget::Get_Image_Pos()
{
    QPoint point(10,10);

    if(m_label != NULL)
    {
        point = m_label->pos();
    }

    return point;
}

int HomoCalcWidget::Set_Parameter_To_Ram()
{
    if(ui->comboBoxPointResult->isEnabled())
    {
        if(ui->comboBoxPointResult->currentIndex() <= 0)
            return 0;
    }else
    {
        if(ui->comboBoxPoint->currentIndex() <= 0)
            return 0;
    }
    if(ui->radioButton_homo->isChecked())
    {
        pInputPara->homo_index_mode = HOMO_INDEX_COMMON;
    }else
    {
        pInputPara->homo_index_mode = HOMO_INDEX_REF_GRST;
    }
    unsigned int i_task_id;
    TASK_STEP_HEADER *pStephead = Task_Step_Head_Get(m_step_index);
    int i_task_index = atoi(ui->comboBoxPoint->currentText().toStdString().c_str());
    Task_Step_Type_ID_Get(i_task_index,&i_task_id);
    int i_result_index = Get_Point_Or_Line_Result_Id(i_task_id,ui->comboBoxPointResult->currentIndex());
    pStephead->step_link.link_count = 1;
    pStephead->step_link.link_info[0].step_index = i_task_index;
    pStephead->step_link.link_info[0].result_index = i_result_index;
    if(ui->checkBox_OffsetCacl->isChecked())
    {
        if(ui->comboBoxAngleResult->isEnabled())
        {
            if(ui->comboBoxAngleResult->currentIndex() <= 0)
                return 0;
        }else
        {
            if(ui->comboBoxAngle->currentIndex() <= 0)
                return 0;
        }
        pInputPara->offset_calc_enable = 1;
        pStephead->step_link.link_count = 2;
        i_task_index = atoi(ui->comboBoxAngle->currentText().toStdString().c_str());
        Task_Step_Type_ID_Get(i_task_index,&i_task_id);
        i_result_index = AssociationMap_Change_TaskResultID(i_task_id, ui->comboBoxAngleResult->currentIndex(), Task_link_D_index);
        pStephead->step_link.link_info[1].step_index = i_task_index;
        pStephead->step_link.link_info[1].result_index = i_result_index;
    }else
    {
        pInputPara->offset_calc_enable = 0;
    }


    if(!ui->groupBox_DefaultValue->isChecked())
    {
        pInputPara->error_pad_enable = HOMO_ERR_PADDING_DISABLE;
    }
    else
    {
        pInputPara->error_pad_enable = HOMO_ERR_PADDING_ENABLE;
        pInputPara->pos_pix_def.x_f = ui->txtPixX->text().toFloat();
        pInputPara->pos_pix_def.y_f = ui->txtPixY->text().toFloat();
        pInputPara->pos_phy_def.x_f = ui->txtPhyX->text().toFloat();
        pInputPara->pos_phy_def.y_f = ui->txtPhyY->text().toFloat();
    }
    pInputPara->homo_dynamic_index = ui->txtHomoPara->text().toInt();

    return 1;
}

void HomoCalcWidget::Init_Input_Ptr(void *ptr,int i_step_index,int new_flag,void *pen_color)
{
    ((FWHomoCalcLabel*)m_label)->SetPenColor(pen_color);
    pInputPara = (HOMO_CALC_INPUT_PARAM *)ptr;
    m_step_index = i_step_index;
    if(pInputPara == NULL)
    {
        QMessageBox::about(this,tr(""),tr("初始化数据失败"));
        return;
    }
    m_i_load_first = 0;
    unsigned int i_task_id = 0;
    int i = 0;
    ui->comboBoxPoint->addItem("");
    ui->comboBoxAngle->addItem("");
    for(i = 0; i < i_step_index-1; i++)
    {
        int ret =Task_Step_Type_ID_Get(i+1,&i_task_id);
        if(ret == 0)
        {
            QString name = InitPointCombobox(i+1,i_task_id);
            if(!name.isEmpty())
            {
                ui->comboBoxPoint->addItem(QString::number(i+1)+"."+name);
            }
            name = InitAngleCombobox(i+1,i_task_id);
            if(!name.isEmpty())
            {
                ui->comboBoxAngle->addItem(QString::number(i+1)+"."+name);
            }
        }
    }
    if(new_flag)
    {
        TASK_STEP_HEADER *pStephead = Task_Step_Head_Get(i_step_index);
        pStephead->step_link.link_count = 0;
        pStephead->step_link.link_info[0].step_index = 0;
        pStephead->step_link.link_info[0].result_index = 0;
        Task_Step_Synthetic_Judge_Flag_Set(i_step_index,1);
        pInputPara->error_pad_enable = HOMO_ERR_PADDING_DISABLE;
        pInputPara->homo_index_mode = HOMO_INDEX_COMMON;
        pInputPara->homo_dynamic_index = 1;
        pInputPara->offset_calc_enable = 0;
        pInputPara->pos_pix_def.x_f = 0.0;
        pInputPara->pos_pix_def.y_f = 0.0;
        pInputPara->pos_phy_def.x_f = 0.0;
        pInputPara->pos_phy_def.y_f = 0.0;
    }
    InitData(i_step_index);
    m_i_load_first = 1;
}

void HomoCalcWidget::Get_Result_From_Ram()
{

}

bool HomoCalcWidget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->txtPixX || watched == ui->txtPixY || \
            watched == ui->txtPhyX || watched == ui->txtPhyY ||\
            watched == ui->txtHomoPara){
        if (event->type()==QEvent::MouseButtonPress){
            NumInputPro((QLineEdit *)watched);
        }
    }
    return QWidget::eventFilter(watched, event);
}


/**
 * @brief BlobWidget::NumInputPro
 * @author dgq
 * @note blob最大检测个数的输入响应函数
 */
void HomoCalcWidget::NumInputPro(QLineEdit *txtInput)
{
    if(!txtInput->isEnabled())
    {
        return;
    }
    Fun_GetNumkeyBoardDlg GetNumKeyBoardDlg = (Fun_GetNumkeyBoardDlg)m_keyBoard_Lib.resolve("GetNumKeyBoardDialog");
    if(GetNumKeyBoardDlg)
    {
        QDialog *Numkey = GetNumKeyBoardDlg();
        int ret = Numkey->exec();
        if(ret== QDialog::Accepted)
        {
            Fun_GetNumString GetNumString = (Fun_GetNumString)m_keyBoard_Lib.resolve("GetNum");
            if(GetNumString)
            {
                QString num = GetNumString();
                if(txtInput->objectName() == "txtHomoPara")
                {
                    bool ok;
                    int index = num.toInt(&ok);
                    if(ok)
                    {
                        if(index < 1)
                            num = "1";
                        if(index > 1024)
                            num = "1024";
                    }else
                    {
                        QMessageBox::about(this,tr("提示"),tr("请输入1~1024之间的整数"));
                        return;
                    }
                }
                txtInput->setText(num);
            }
        }
    }
}

void HomoCalcWidget::PointTaskChangeSlot(int index)
{
    ((FWHomoCalcLabel*)m_label)->SetPoint(QPoint(-20,-20));
    if(m_i_load_first == 1)
    {
        int task_index = atoi(ui->comboBoxPoint->currentText().toStdString().c_str());
        if(task_index == 0)
        {
            ui->comboBoxPointResult->clear();
            return;
        }
        ui->comboBoxPointResult->setEnabled(true);


        ui->comboBoxPointResult->clear();
        ui->comboBoxPointResult->addItem(" ");
        unsigned int id;
        Task_Step_Type_ID_Get(task_index ,&id);
        int  Mul_Flag = Get_Multi_Result_Task_Flag(id);
        if(Mul_Flag ==1)
        {
            unsigned int i_mul_rst_cnt = 0;
            TaskMultiRstNumGet(task_index,1,&i_mul_rst_cnt);
            ui->comboBoxPointResult->setEnabled(true);
            for(unsigned int i = 1; i<= i_mul_rst_cnt;i++)
            {
                QString strLineIndex;
                strLineIndex = tr("点")+QString::number(i);
                ui->comboBoxPointResult->addItem(strLineIndex);
            }
        }
        else
        {
            ui->comboBoxPointResult->setEnabled(false);
            QPoint point;
            int i_result_index = Get_Point_Or_Line_Result_Id(id,0);
            GetRefPara(task_index,i_result_index,&point);
            ((FWHomoCalcLabel*)m_label)->SetPoint(point);
        }
    }
}

void HomoCalcWidget::PointResultChangeSlot(int index)
{
    if(m_i_load_first ==1)
    {
        int Result_index = ui->comboBoxPointResult->currentIndex();
        int Task_index = atoi(ui->comboBoxPoint->currentText().toStdString().c_str());
        QPoint point;
        unsigned int id;
        Task_Step_Type_ID_Get(Task_index,&id);
        int result_index = Get_Point_Or_Line_Result_Id(id,Result_index);
        GetRefPara(Task_index,result_index,&point);
        ((FWHomoCalcLabel*)m_label)->SetPoint(point);

    }
}

void HomoCalcWidget::AngleTaskChangeSlot(int index)
{
    if(m_i_load_first == 1)
    {
        int task_index = atoi(ui->comboBoxAngle->currentText().toStdString().c_str());
        QStringList result_list = GetResultString(task_index, Task_link_D_index);
        ui->comboBoxAngleResult->clear();
        ui->comboBoxAngleResult->addItem(" ");
        ui->comboBoxAngleResult->addItems(result_list);
    }
}

void HomoCalcWidget::AngleResultChangeSlot(int index)
{

}

void HomoCalcWidget::InitData(int i_step_index)
{
    unsigned int homo_index_mode = pInputPara->homo_index_mode;
    unsigned int error_pad_enable = pInputPara->error_pad_enable;
    unsigned int homo_dynamic_index = pInputPara->homo_dynamic_index;
    unsigned int offset_calc_enable = pInputPara->offset_calc_enable;
    POINT_F pos_pix_def = pInputPara->pos_pix_def;
    POINT_F pos_phy_def = pInputPara->pos_phy_def;

    ui->txtHomoPara->setText(QString::number(homo_dynamic_index));
    if(homo_index_mode == HOMO_INDEX_COMMON)
    {
        ui->radioButton_homo->setChecked(true);
    }else
    {
        ui->radioButton_Grst->setChecked(true);
    }
    if(offset_calc_enable)
    {
        ui->checkBox_OffsetCacl->setChecked(true);
        ui->groupBox_rotate_angle->setEnabled(true);
    }else
    {
        ui->checkBox_OffsetCacl->setChecked(false);
        ui->groupBox_rotate_angle->setEnabled(false);
    }
    int i = 0;
    TASK_STEP_HEADER *pStephead = Task_Step_Head_Get(i_step_index);
    int i_task_index = pStephead->step_link.link_info[0].step_index;
    int i_result_index = pStephead->step_link.link_info[0].result_index;
    int i_task2_index = 0;
    int i_result2_index = 0;
    if( pStephead->step_link.link_count == 2)
    {
        i_task2_index = pStephead->step_link.link_info[1].step_index;
        i_result2_index = pStephead->step_link.link_info[1].result_index;
        for(i = 0; i < ui->comboBoxAngle->count(); i++)
        {
            if(i_task2_index == atoi(ui->comboBoxAngle->itemText(i).toStdString().c_str()))
                ui->comboBoxAngle->setCurrentIndex(i);
        }
        ui->comboBoxAngleResult->addItem(" ");
        if(i_task2_index > 0)
        {
            QStringList result_list = GetResultString(i_task2_index, Task_link_D_index);
            ui->comboBoxAngleResult->addItems(result_list);
        }
        unsigned int id;
        Task_Step_Type_ID_Get(i_task2_index,&id);
        int index = AssociationMap_Change_UIID(id, i_result2_index, Task_link_D_index);
        ui->comboBoxAngleResult->setCurrentIndex(index);
    }
    for(i = 0; i < ui->comboBoxPoint->count(); i++)
    {
        if(i_task_index == atoi(ui->comboBoxPoint->itemText(i).toStdString().c_str()))
            ui->comboBoxPoint->setCurrentIndex(i);
    }
    ui->comboBoxPointResult->addItem(" ");
    unsigned int i_mul_rst_cnt = 0;
    if(i_task_index > 0)
    {
        int ret = TaskMultiRstNumGet(i_task_index,1,&i_mul_rst_cnt);
        if(ret == 0)
        {
            for(unsigned int i = 1; i < i_mul_rst_cnt+1; i++)
            {
                ui->comboBoxPointResult->addItem(tr("点")+QString::number(i));
            }
        }
    }
    QPoint point;
    unsigned int id;
    Task_Step_Type_ID_Get(i_task_index,&id);
    int  Mul_Flag = Get_Multi_Result_Task_Flag(id);
    if(Mul_Flag == -1)
    {
        ui->comboBoxPointResult->setEnabled(false);
    }else
    {
        ui->comboBoxPointResult->setCurrentIndex(Point_Or_Line_Result_Id_Change_UI_Id(id,i_result_index));
    }
    GetRefPara(i_task_index,i_result_index,&point);
    ((FWHomoCalcLabel*)m_label)->SetPoint(point);


    if(error_pad_enable == HOMO_ERR_PADDING_DISABLE)
    {
        ui->groupBox_DefaultValue->setChecked(false);
    }else
    {
        ui->groupBox_DefaultValue->setChecked(true);
        ui->txtPixX->setText(QString::number(pos_pix_def.x_f));
        ui->txtPixY->setText(QString::number(pos_pix_def.y_f));
        ui->txtPhyX->setText(QString::number(pos_phy_def.x_f));
        ui->txtPhyY->setText(QString::number(pos_phy_def.y_f));
    }
}

QString HomoCalcWidget::InitPointCombobox(int TaskIndex, int id)
{
    QString name;
    int ret = Get_Point_Or_Line_Flag(id);
    if(ret == 0)//线任务
    {
        char taskName[40];
        memset(taskName,0,40);
        int ret = Get_Task_Name(TaskIndex, taskName);
        if(ret != -1)
        {
            name = QString::fromUtf8(taskName);
        }
    }
    return name;
}


QString HomoCalcWidget::InitAngleCombobox(int TaskIndex, int id)
{
    QString name;
    if(TaskIndex < 1){
        return QString::null;
    }
    int ret = Get_Task_Link_Type_Flag(id, Task_link_D_index);
    if(ret == 1)//角度任务
    {
        char taskName[40];
        memset(taskName,0,40);
        int ret = Get_Task_Name(TaskIndex, taskName);
        if(ret != -1)
        {
            name = QString::fromUtf8(taskName);
        }
    }
    return name;
}

void HomoCalcWidget::GetRefPara(int ref_step, int ref_result, QPoint *point)
{
    float point_pix_vga_x = 0.0;
    float point_pix_vga_y = 0.0;
    float point_pix_sub_x = 0.0;
    float point_pix_sub_y = 0.0;
    POINT_F pointf;
    int ret = measure_ref_point_result_get(ref_step,ref_result,&pointf,1);
    if(ret != 0)
    {
        qDebug()<<"measure_ref_point_result_get ret = "<<__LINE__<<ret;
    }
    point_pix_sub_x = pointf.x_f;
    point_pix_sub_y = pointf.y_f;
    PixelCvt(&point_pix_sub_x,&point_pix_vga_x,CVT_SUB2VGA|CVT_F2F|CVT_DATA);
    PixelCvt(&point_pix_sub_y,&point_pix_vga_y,CVT_SUB2VGA|CVT_F2F|CVT_DATA);
    point->setX(point_pix_vga_x);
    point->setY(point_pix_vga_y);
}

/**
 * @brief BlobWidget::LoadKeyBoardLib
 * @author dgq
 * @note 加载输入软键盘库
 */
void HomoCalcWidget::LoadKeyBoardLib()
{
    m_keyBoard_Lib.setFileName("libFrmInputKeyBoard.so");
    if(m_keyBoard_Lib.isLoaded())
    {
        qDebug()<<"load libFrmInputKeyBoard.so isLoaded";
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

void HomoCalcWidget::on_checkBox_OffsetCacl_clicked()
{
    if(ui->checkBox_OffsetCacl->isChecked())
        ui->groupBox_rotate_angle->setEnabled(true);
    else
        ui->groupBox_rotate_angle->setEnabled(false);
}

QStringList HomoCalcWidget::GetResultString(int task_index, int link_type_index)
{
    QStringList ResultString;
    int current_index = 0;
    ResultString.clear();
    RESULT_NAME MultiResult;
    if(task_index < 1){
        return ResultString;
    }
    unsigned int type = 0;
    int ret = 0;
    ret = Task_Step_Type_ID_Get(task_index, &type);
    if(ret == 0){
        if(Get_Multi_Result_Task_Flag(type) == -1){
            ret = Init_AssociationMap_Task_Result_String(type, -1, link_type_index);
            if(ret > 0){
                for(int multiIndex = 0; multiIndex < ret; multiIndex++)
                {
                    memset(MultiResult.Result_Name, 0, sizeof(RESULT_NAME));
                    int rst = Get_AssociationMap_Result_String(multiIndex, &MultiResult);
                    if(rst == -1){
                        return ResultString;
                    }
                    current_index++;
                    ResultString.append(QString::fromUtf8(MultiResult.Result_Name));
                }
            }
        }else{
            unsigned int ResultCount = 0;
            ret = TaskMultiRstNumGet(task_index, 1, &ResultCount);
            if(ret != 0){
                return ResultString;
            }
            ret = Init_AssociationMap_Task_Result_String(type, ResultCount, link_type_index);
            if(ret > 0){
                for(int multiIndex = 0; multiIndex < ret; multiIndex++)
                {
                    memset(MultiResult.Result_Name, 0, sizeof(RESULT_NAME));
                    int rst = Get_AssociationMap_Result_String(multiIndex, &MultiResult);
                    if(rst == -1){
                        return ResultString;
                    }
                    current_index++;
                    ResultString.append(QString::fromUtf8(MultiResult.Result_Name));
                }
            }
        }
    }
    return ResultString;
}
