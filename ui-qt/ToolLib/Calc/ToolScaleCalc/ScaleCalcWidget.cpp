#include <QDebug>
#include "ScaleCalcWidget.h"
#include "ui_ScaleCalcWidget.h"
#include "TaskStepGlobal.h"
#include "FWScaleCalcLabel.h"
#include "PixelConvert.h"
#include <QMessageBox>
#include "TaskRstGlobal.h"
#include "xmlInitGlobal.h"
#include "LinkDataGlobal.h"

ScaleCalcWidget::ScaleCalcWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScaleCalcWidget)
{
    ui->setupUi(this);
    LoadKeyBoardLib();
    QList<QLineEdit *> lineEdit = this->findChildren<QLineEdit *>();
    foreach (QLineEdit * L, lineEdit) {
        L->installEventFilter(this);
        }
    m_label = new FWScaleCalcLabel(this);
    m_label->setGeometry(10,10,640,480);
    m_label->setAutoFillBackground(true);
    QPalette p = m_label->palette();
    p.setColor(QPalette::Background,QColor(50,50,50,255));
    m_label->setPalette(p);
    connect(ui->comboBoxPoint, SIGNAL(currentIndexChanged(int)), this, SLOT(PointTaskChangeSlot(int)));
    connect(ui->comboBoxPointResult, SIGNAL(activated(int)), this, SLOT(PointResultChangeSlot(int)));
}

ScaleCalcWidget::~ScaleCalcWidget()
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

QPoint ScaleCalcWidget::Get_Image_Pos()
{
    QPoint point(10,10);

    if(m_label != NULL)
    {
        point = m_label->pos();
    }

    return point;
}

int ScaleCalcWidget::Set_Parameter_To_Ram()
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
    if(ui->radioButton_Comm_Scale->isChecked())
    {
        pInputPara->scale_index_mode = SCALE_INDEX_COMMON;
    }else
    {
        pInputPara->scale_index_mode = SCALE_INDEX_REF_PRE_STEP;
    }
    unsigned int i_task_id;
    TASK_STEP_HEADER *pStephead = Task_Step_Head_Get(m_step_index);
    int i_task_index =  atoi(ui->comboBoxPoint->currentText().toStdString().c_str());
    Task_Step_Type_ID_Get(i_task_index,&i_task_id);
    int i_result_index = Get_Dist_Result_ID(i_task_id,ui->comboBoxPointResult->currentIndex());
    pStephead->step_link.link_count = 1;
    pStephead->step_link.link_info[0].step_index = i_task_index;
    pStephead->step_link.link_info[0].result_index = i_result_index;
    if(!ui->groupBox_DefaultValue->isChecked())
    {
        pInputPara->error_pad_enable = SCALE_ERR_PADDING_DISABLE;
    }
    else
    {
        pInputPara->error_pad_enable = SCALE_ERR_PADDING_ENABLE;
        pInputPara->len_pix_def = ui->txtPixLen->text().toFloat();
        pInputPara->len_phy_def = ui->txtPhyLen->text().toFloat();
    }
    pInputPara->scale_dynamic_index = ui->txtScalePara->text().toInt();

    return 1;
}

void ScaleCalcWidget::Init_Input_Ptr(void *ptr,int i_step_index,int new_flag,void *pen_color)
{
    pInputPara = (SCALE_CALC_INPUT_PARAM *)ptr;
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
        }
    }
    if(new_flag)
    {
        TASK_STEP_HEADER *pStephead = Task_Step_Head_Get(i_step_index);
        pStephead->step_link.link_count = 0;
        pStephead->step_link.link_info[0].step_index = 0;
        pStephead->step_link.link_info[0].result_index = 0;
        Task_Step_Synthetic_Judge_Flag_Set(i_step_index,1);
        pInputPara->error_pad_enable = SCALE_ERR_PADDING_DISABLE;
        pInputPara->scale_index_mode = SCALE_INDEX_COMMON;
        pInputPara->scale_dynamic_index = 1;
        pInputPara->len_pix_def = 0.0;
        pInputPara->len_pix_def = 0.0;
    }
    InitData(i_step_index);
    m_i_load_first = 1;
}

void ScaleCalcWidget::Get_Result_From_Ram()
{

}

bool ScaleCalcWidget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->txtPixLen || watched == ui->txtPhyLen ||\
            watched == ui->txtScalePara){
        if (event->type()==QEvent::MouseButtonPress){
            BlobNumInputPro((QLineEdit *)watched);
        }
    }
    return QWidget::eventFilter(watched, event);
}


/**
 * @brief BlobWidget::BlobNumInputPro
 * @author dgq
 * @note blob最大检测个数的输入响应函数
 */
void ScaleCalcWidget::BlobNumInputPro(QLineEdit *txtInput)
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
                if(txtInput->objectName() == "txtScalePara")
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


void ScaleCalcWidget::on_radioButton_Comm_Scale_clicked()
{

}

void ScaleCalcWidget::on_radioButton_Ref_Result_clicked()
{

}


void ScaleCalcWidget::PointTaskChangeSlot(int index)
{
//    ((FWScaleCalcLabel*)m_label)->SetPoint(QPoint(-20,-20));
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
        unsigned int id;
        Task_Step_Type_ID_Get(task_index ,&id);
        int  Mul_Flag = Get_Dist_Flag(id);
        if(Mul_Flag == 2)
        {
            ui->comboBoxPointResult->addItem(tr("宽度"));
            ui->comboBoxPointResult->addItem(tr("高度"));
        }
        else
        {
            ui->comboBoxPointResult->setEnabled(false);
        }
    }
}

void ScaleCalcWidget::PointResultChangeSlot(int index)
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
//        ((FWScaleCalcLabel*)m_label)->SetPoint(point);

    }
}

void ScaleCalcWidget::InitData(int i_step_index)
{
    unsigned int scale_index_mode = pInputPara->scale_index_mode;
    unsigned int error_pad_enable = pInputPara->error_pad_enable;
    unsigned int scale_dynamic_index = pInputPara->scale_dynamic_index;
    float len_pix_def = pInputPara->len_pix_def;
    float len_phy_def = pInputPara->len_phy_def;

    ui->txtScalePara->setText(QString::number(scale_dynamic_index));
    if(scale_index_mode == SCALE_INDEX_COMMON)
    {
        ui->radioButton_Comm_Scale->setChecked(true);
    }else
    {
        ui->radioButton_Ref_Result->setChecked(true);
    }
    int i = 0;
    TASK_STEP_HEADER *pStephead = Task_Step_Head_Get(i_step_index);
    int i_task_index = pStephead->step_link.link_info[0].step_index;
    int i_result_index = pStephead->step_link.link_info[0].result_index;
    for(i = 0; i < ui->comboBoxPoint->count(); i++)
    {
        if(i_task_index == atoi(ui->comboBoxPoint->itemText(i).toStdString().c_str()))
            ui->comboBoxPoint->setCurrentIndex(i);
    }
    unsigned int id;
    Task_Step_Type_ID_Get(i_task_index,&id);
    int  Mul_Flag = Get_Dist_Flag(id);
    if(Mul_Flag == 1)
    {
        ui->comboBoxPointResult->setEnabled(false);
    }else
    {
        ui->comboBoxPointResult->addItem(tr("宽度"));
        ui->comboBoxPointResult->addItem(tr("高度"));
        ui->comboBoxPointResult->setCurrentIndex(i_result_index);
    }

    if(error_pad_enable == SCALE_ERR_PADDING_DISABLE)
    {
        ui->groupBox_DefaultValue->setChecked(false);
    }else
    {
        ui->groupBox_DefaultValue->setChecked(true);
        ui->txtPixLen->setText(QString::number(len_pix_def));
        ui->txtPhyLen->setText(QString::number(len_phy_def));
    }
}

QString ScaleCalcWidget::InitPointCombobox(int TaskIndex, int id)
{
    QString name;
    int ret = Get_Dist_Flag(id);
    if(ret == 1 || ret == 2)//线任务
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

void ScaleCalcWidget::GetRefPara(int ref_step, int ref_result, QPoint *point)
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
void ScaleCalcWidget::LoadKeyBoardLib()
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
