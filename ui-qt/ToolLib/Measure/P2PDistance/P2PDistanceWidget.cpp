#include <QDebug>
#include "P2PDistanceWidget.h"
#include "ui_P2PDistanceWidget.h"
#include "TaskStepGlobal.h"
#include "FWP2PDistanceLabel.h"
#include "PixelConvert.h"
#include <QMessageBox>
#include "TaskRstGlobal.h"
#include "PointsDistGlobal.h"
#include "xmlInitGlobal.h"
#include "LinkDataGlobal.h"

P2PDistanceWidget::P2PDistanceWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::P2PDistanceWidget)
{
    ui->setupUi(this);
    LoadKeyBoardLib();
    LoadLearnLib();
    ui->MaxValidData->installEventFilter(this);
    ui->MinValidData->installEventFilter(this);
    m_label = new FWP2PDistanceLabel(this);
    m_label->setGeometry(10,10,640,480);
    m_label->setAutoFillBackground(true);
    QPalette p = m_label->palette();
    p.setColor(QPalette::Background,QColor(50,50,50,255));
    m_label->setPalette(p);
    CalcTimer = new QTimer;

    ui->radioButton_pix->setChecked(true);
    connect(ui->comboBoxPoint1, SIGNAL(currentIndexChanged(int)), this, SLOT(Point1TaskChangeSlot(int)));
    connect(ui->comboBoxPoint2, SIGNAL(currentIndexChanged(int)), this, SLOT(Point2TaskChangeSlot(int)));
    connect(ui->comboBoxPoint1Result, SIGNAL(activated(int)), this, SLOT(Point1ResultChangeSlot(int)));
    connect(ui->comboBoxPoint2Result, SIGNAL(activated(int)), this, SLOT(Point2ResultChangeSlot(int)));

    connect(CalcTimer, &QTimer::timeout, this, &P2PDistanceWidget::CalcTimerSlot);

}

P2PDistanceWidget::~P2PDistanceWidget()
{
    ui->MaxValidData->removeEventFilter(this);
    ui->MinValidData->removeEventFilter(this);
    if(m_label !=NULL)
    {
        delete m_label;
        m_label = NULL;
    }
    delete CalcTimer;
    delete ui;
}
QPoint P2PDistanceWidget::Get_Image_Pos()
{
    QPoint point(10,10);

    if(m_label != NULL)
    {
        point = m_label->pos();
    }

    return point;
}
/**
 * @brief P2PDistanceWidget::Set_Parameter_To_Ram
 * @author dgq
 * @note 将界面的配置参数写入内存
 */
int P2PDistanceWidget::Set_Parameter_To_Ram()
{
    unsigned int i_task_id;
    TASK_STEP_HEADER *pStephead = Task_Step_Head_Get(m_step_index);
    int i_task1_index =  atoi(ui->comboBoxPoint1->currentText().toStdString().c_str());
    Task_Step_Type_ID_Get(i_task1_index,&i_task_id);
    int i_result1_index = Get_Point_Or_Line_Result_Id(i_task_id,ui->comboBoxPoint1Result->currentIndex());
    int i_task2_index =  atoi(ui->comboBoxPoint2->currentText().toStdString().c_str());
    Task_Step_Type_ID_Get(i_task2_index,&i_task_id);
    int i_result2_index = Get_Point_Or_Line_Result_Id(i_task_id,ui->comboBoxPoint2Result->currentIndex());
    if(i_task1_index == i_task2_index && i_result1_index == i_result2_index)
    {
        return 0;
    }
    pStephead->step_link.link_count = 2;
    pStephead->step_link.link_info[0].step_index = i_task1_index;
    pStephead->step_link.link_info[0].result_index = i_result1_index;
    pStephead->step_link.link_info[1].step_index = i_task2_index;
    pStephead->step_link.link_info[1].result_index = i_result2_index;
    SetRangetoLib();
    return 1;

}

/**
 * @brief P2PDistanceWidget::Init_Input_Ptr
 * @param ptr 输入结构体内存指针
 * @param i_step_index 任务步骤号
 * @author dgq
 * @note 初始化Input结构体指针
 */
void P2PDistanceWidget::Init_Input_Ptr(void *ptr,int i_step_index,int new_flag,void *pen_color)
{
    ((FWP2PDistanceLabel*)m_label)->SetPenColor(pen_color);
    pInputPara = ptr;
    m_step_index = i_step_index;
    if(pInputPara == NULL)
    {
        QMessageBox::about(this,tr(""),tr("初始化数据失败"));
        return;
    }
    unsigned int i_task_id = 0;
    int i = 0;
    ui->comboBoxPoint1->addItem("");
    ui->comboBoxPoint2->addItem("");
    for(i = 0; i < i_step_index-1; i++)
    {
        int ret =Task_Step_Type_ID_Get(i+1,&i_task_id);
        if(ret == 0)
        {
            QString name = InitPointCombobox(i+1,i_task_id);
            if(!name.isEmpty())
            {
                ui->comboBoxPoint1->addItem(QString::number(i+1)+"."+name);
                ui->comboBoxPoint2->addItem(QString::number(i+1)+"."+name);
            }
        }
    }
    m_i_load_first = 0;
    if(new_flag)
    {
        TASK_STEP_HEADER *pStephead = Task_Step_Head_Get(i_step_index);
        pStephead->step_link.link_count = 0;
        pStephead->step_link.link_info[0].step_index = 0;
        pStephead->step_link.link_info[0].result_index = 0;
        pStephead->step_link.link_info[1].step_index = 0;
        pStephead->step_link.link_info[1].result_index = 0;
        Task_Step_Synthetic_Judge_Flag_Set(i_step_index,1);
        ((P2P_DIST_INPUT_PARAM*)pInputPara)->pix_phy_flag = 0;
        ((P2P_DIST_INPUT_PARAM*)pInputPara)->valid_range.high_enable = 0;
        ((P2P_DIST_INPUT_PARAM*)pInputPara)->valid_range.low_enable = 0;
    }
    InitData(i_step_index);
    m_i_load_first = 1;
}

QString P2PDistanceWidget::InitPointCombobox(int TaskIndex, int id)
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

/**
 * @brief P2PDistanceWidget::InitData
 * @param i_step_index
 * @author dgq
 * @note 初始化
 */
void P2PDistanceWidget::InitData(int i_step_index)
{
//    int i_task_count = GetTaskStepCount();
    int i = 0;
    TASK_STEP_HEADER *pStephead = Task_Step_Head_Get(i_step_index);
    int i_task1_index = pStephead->step_link.link_info[0].step_index;
    int i_result1_index = pStephead->step_link.link_info[0].result_index;
    int i_task2_index = pStephead->step_link.link_info[1].step_index;
    int i_result2_index = pStephead->step_link.link_info[1].result_index;

    for(i = 0; i < ui->comboBoxPoint1->count(); i++)
    {
        if(i_task1_index == atoi(ui->comboBoxPoint1->itemText(i).toStdString().c_str()))
            ui->comboBoxPoint1->setCurrentIndex(i);
    }
    for(i = 0; i < ui->comboBoxPoint2->count(); i++)
    {
        if(i_task2_index == atoi(ui->comboBoxPoint2->itemText(i).toStdString().c_str()))
            ui->comboBoxPoint2->setCurrentIndex(i);
    }
    ui->comboBoxPoint1Result->addItem(" ");
    ui->comboBoxPoint2Result->addItem(" ");
    unsigned int i_mul_rst_cnt = 0;
    if(i_task1_index > 0)
    {
        int ret = TaskMultiRstNumGet(i_task1_index,1,&i_mul_rst_cnt);
        if(ret == 0)
        {
            for(unsigned int i = 1; i < i_mul_rst_cnt+1; i++)
            {
                ui->comboBoxPoint1Result->addItem(tr("点")+QString::number(i));
            }
        }
    }
    if(i_task2_index > 0)
    {
        int ret = TaskMultiRstNumGet(i_task2_index,1,&i_mul_rst_cnt);
        if(ret == 0)
        {
            for(unsigned int i = 1; i < i_mul_rst_cnt+1; i++)
            {
                ui->comboBoxPoint2Result->addItem(tr("点")+QString::number(i));
            }
        }
    }
    QPoint point;
    unsigned int id;
    Task_Step_Type_ID_Get(i_task1_index,&id);
    int  Mul_Flag = Get_Multi_Result_Task_Flag(id);
    if(Mul_Flag == -1)
    {
        ui->comboBoxPoint1Result->setEnabled(false);
    }else
    {
        ui->comboBoxPoint1Result->setCurrentIndex(Point_Or_Line_Result_Id_Change_UI_Id(id,i_result1_index));
    }
    GetPointRefPara(i_task1_index,i_result1_index,&point);
    ((FWP2PDistanceLabel*)m_label)->SetPoint1(point);

    Task_Step_Type_ID_Get(i_task2_index,&id);
    Mul_Flag = Get_Multi_Result_Task_Flag(id);
    if(Mul_Flag == -1)
    {
        ui->comboBoxPoint2Result->setEnabled(false);
    }else
    {
        ui->comboBoxPoint2Result->setCurrentIndex(Point_Or_Line_Result_Id_Change_UI_Id(id,i_result2_index));
    }
    GetPointRefPara(i_task2_index,i_result2_index,&point);
    ((FWP2PDistanceLabel*)m_label)->SetPoint2(point);
    InitRangeData();
}


/**
 * @brief P2PDistanceWidget::Point1TaskChangeSlot
 * @param index 下拉框的当前索引
 * @author dgq
 * @note 点1的关联任务发生改变时的处理
 */
void P2PDistanceWidget::Point1TaskChangeSlot(int index)
{
    ((FWP2PDistanceLabel*)m_label)->SetPoint1(QPoint(-20,-20));
    if(m_i_load_first == 1)
    {
        int task_index1 = atoi(ui->comboBoxPoint1->currentText().toStdString().c_str());
        if(task_index1  == 0)
        {
            ui->comboBoxPoint1Result->clear();
            return;
        }
        ui->comboBoxPoint1Result->setEnabled(true);

        ui->comboBoxPoint1Result->clear();
        ui->comboBoxPoint1Result->addItem(" ");
        unsigned int id;
        Task_Step_Type_ID_Get(task_index1 ,&id);
        int  Mul_Flag = Get_Multi_Result_Task_Flag(id);
        if(Mul_Flag ==1)
        {
            unsigned int i_mul_rst_cnt = 0;
            TaskMultiRstNumGet(task_index1 ,1,&i_mul_rst_cnt);
            ui->comboBoxPoint1Result->setEnabled(true);
            for(unsigned int i = 1; i<= i_mul_rst_cnt;i++)
            {
                QString strLineIndex;
                strLineIndex = tr("点")+QString::number(i);
                ui->comboBoxPoint1Result->addItem(strLineIndex);
            }
        }
        else
        {
            ui->comboBoxPoint1Result->setEnabled(false);
            QPoint point1;
            int i_result1_index = Get_Point_Or_Line_Result_Id(id,0);
            GetPointRefPara(task_index1 ,i_result1_index,&point1);
            ((FWP2PDistanceLabel*)m_label)->SetPoint1(point1);
        }

    }
}

void P2PDistanceWidget::InitRangeData()
{
    if(((P2P_DIST_INPUT_PARAM*)pInputPara)->pix_phy_flag == 0)
    {
        ui->radioButton_pix->setChecked(true);
        pix_phy_flag = 0;
    }else
    {
        ui->radioButton_phy->setChecked(true);
        pix_phy_flag = 1;
    }

    if(((P2P_DIST_INPUT_PARAM*)pInputPara)->valid_range.low_enable == 0){
        ui->MinValidData->setText("---");
    }else{
        ui->MinValidData->setText(QString::number(((P2P_DIST_INPUT_PARAM*)pInputPara)->valid_range.low_threshold));
    }

    if(((P2P_DIST_INPUT_PARAM*)pInputPara)->valid_range.high_enable == 0){
        ui->MaxValidData->setText("---");
    }else{
        ui->MaxValidData->setText(QString::number(((P2P_DIST_INPUT_PARAM*)pInputPara)->valid_range.high_threshold));
    }

}

/**
 * @brief P2PDistanceWidget::Point2TaskChangeSlot
 * @param index 下拉框的当前索引
 * @author dgq
 * @note 点2的关联任务发生改变时的处理
 */
void P2PDistanceWidget::Point2TaskChangeSlot(int index)
{
    ((FWP2PDistanceLabel*)m_label)->SetPoint2(QPoint(-20,-20));
    if(m_i_load_first == 1)
    {
        int task_index2 = atoi(ui->comboBoxPoint2->currentText().toStdString().c_str());
        if(task_index2 == 0)
        {
            ui->comboBoxPoint2Result->clear();
            return;
        }
        ui->comboBoxPoint2Result->setEnabled(true);
        ui->comboBoxPoint2Result->clear();
        ui->comboBoxPoint2Result->addItem(" ");
        unsigned int id;
        Task_Step_Type_ID_Get(task_index2,&id);
        int  Mul_Flag = Get_Multi_Result_Task_Flag(id);
        if(Mul_Flag == 1)
        {
            unsigned int i_mul_rst_cnt = 0;
            TaskMultiRstNumGet(task_index2,1,&i_mul_rst_cnt);
            ui->comboBoxPoint2Result->setEnabled(true);
            for(unsigned int i = 1; i <= i_mul_rst_cnt;i++)
            {
                QString strLineIndex;
                strLineIndex = "点"+QString::number(i);
                ui->comboBoxPoint2Result->addItem(strLineIndex);
            }
        }
        else
        {
            ui->comboBoxPoint2Result->setEnabled(false);
            QPoint point2;
            int i_result2_index = Get_Point_Or_Line_Result_Id(id,0);
            GetPointRefPara(task_index2,i_result2_index,&point2);
            ((FWP2PDistanceLabel*)m_label)->SetPoint2(point2);
        }

    }
}

/**
 * @brief P2PDistanceWidget::Point1ResultChangeSlot
 * @param index 下拉框索引
 * @author dgq
 * @note 引用结果发生改变时的处理
 */
void P2PDistanceWidget::Point1ResultChangeSlot(int index)
{
    if(m_i_load_first ==1)
    {
        int Task_index1 = atoi(ui->comboBoxPoint1->currentText().toStdString().c_str());
        int Result1_index = ui->comboBoxPoint1Result->currentIndex();
        QPoint point1;
        unsigned int id;
        Task_Step_Type_ID_Get(Task_index1,&id);
        int result_index = Get_Point_Or_Line_Result_Id(id,Result1_index);
        GetPointRefPara(Task_index1,result_index,&point1);
        ((FWP2PDistanceLabel*)m_label)->SetPoint1(point1);
    }
}
void P2PDistanceWidget::Point2ResultChangeSlot(int index)
{
    if(m_i_load_first ==1)
    {
        int Task_index2 = atoi(ui->comboBoxPoint2->currentText().toStdString().c_str());
        int Result2_index = ui->comboBoxPoint2Result->currentIndex();

        QPoint point2;unsigned int id;
        Task_Step_Type_ID_Get(Task_index2,&id);
        int result_index = Get_Point_Or_Line_Result_Id(id,Result2_index);
        GetPointRefPara(Task_index2,result_index,&point2);
        ((FWP2PDistanceLabel*)m_label)->SetPoint2(point2);
    }
}


void P2PDistanceWidget::GetPointRefPara(int ref_step,int ref_result,QPoint *point)
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


void P2PDistanceWidget::LoadKeyBoardLib()
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


bool P2PDistanceWidget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->MaxValidData){
        if (event->type()==QEvent::MouseButtonPress){
            RangeInputPro(ui->MaxValidData,ui->MinValidData,ui->lineEdit_Dist->text(),THRESHOLD_HIGH);
        }
    }
    if(watched == ui->MinValidData){
        if (event->type()==QEvent::MouseButtonPress){
            RangeInputPro(ui->MaxValidData,ui->MinValidData,ui->lineEdit_Dist->text(),THRESHOLD_LOW);
        }
    }
    return QWidget::eventFilter(watched, event);
}


/**
 * @brief P2PDistanceWidget::RangeInputPro
 * @param pEditMax 上限输入框
 * @param pEditMin 下限输入框
 * @param calc_value 计算值
 * @param flag 上限、下限标志 1上限，0下限
 * @author dgq
 * @note blob门限输入函数
 */
void P2PDistanceWidget::RangeInputPro(QLineEdit *pEditMax,QLineEdit *pEditMin,QString calc_value,int flag)
{
    QLineEdit * pEdit;
    Fun_GetNumkeyBoardDlg GetNumKeyBoardDlg = (Fun_GetNumkeyBoardDlg)m_keyBoard_Lib.resolve("GetNumKeyBoardDialog");
    QDialog *dlg = GetNumKeyBoardDlg();
    Fun_SetRangeInput SetRangeInput = (Fun_SetRangeInput)m_keyBoard_Lib.resolve("SetRangeInput");

    if (flag == THRESHOLD_LOW) {
        pEdit = pEditMin;
    } else {
        pEdit = pEditMax;
    }

    if(pEdit->text() != "---"){
        SetRangeInput(pEditMax->text(),pEditMin->text(),flag);
    }else{
        SetRangeInput(pEditMax->text(),calc_value,flag);
    }
    if(dlg->exec()== QDialog::Accepted)
    {
        Fun_GetRangeNum GetRangeNum = (Fun_GetRangeNum)m_keyBoard_Lib.resolve("GetRangeNum");
        pEdit->setText(GetRangeNum());
    }
}

void P2PDistanceWidget::on_radioButton_phy_clicked()
{
    unsigned int i_caliPara;
    Task_Step_Scale_Cali_Param_Index_Get(m_step_index,&i_caliPara);
    if(i_caliPara == 0)
    {
        QMessageBox::about(this,tr("提示"),tr("本步骤没有关联刻度校准参数，无法切换到物理值"));
        ui->radioButton_pix->setChecked(true);
        pix_phy_flag = 0;
        return;
    }
    else if(pix_phy_flag == 0)
    {
        QMessageBox::StandardButton rb = QMessageBox::warning(NULL, tr("警告"), tr("切换数据类型会清空范围数据，确定切换?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
        if(rb == QMessageBox::No)
        {
            ui->radioButton_pix->setChecked(true);
            return;
        }
        pix_phy_flag = 1;
        ui->lineEdit_Dist->setText("");
        ui->MaxValidData->setText("---");
        ui->MinValidData->setText("---");
    }

}

void P2PDistanceWidget::on_radioButton_pix_clicked()
{
    if(pix_phy_flag == 1)
    {
        QMessageBox::StandardButton rb = QMessageBox::warning(NULL, tr("警告"), tr("切换数据类型会清空范围数据，确定切换?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
        if(rb == QMessageBox::No)
        {
            ui->radioButton_phy->setChecked(true);
            return;
        }
        pix_phy_flag = 0;
        ui->lineEdit_Dist->setText("");
        ui->MaxValidData->setText("---");
        ui->MinValidData->setText("---");
    }
}


int P2PDistanceWidget::SetRangetoLib()
{
    if(ui->radioButton_phy->isChecked())
    {
        ((P2P_DIST_INPUT_PARAM*)pInputPara)->pix_phy_flag = 1;
    }
    else
    {
        ((P2P_DIST_INPUT_PARAM*)pInputPara)->pix_phy_flag = 0;
    }
    if(ui->MaxValidData->text() == "---"){
        ((P2P_DIST_INPUT_PARAM*)pInputPara)->valid_range.high_enable = 0;
    }else{
        ((P2P_DIST_INPUT_PARAM*)pInputPara)->valid_range.high_enable = 1;
        ((P2P_DIST_INPUT_PARAM*)pInputPara)->valid_range.high_threshold = ui->MaxValidData->text().toFloat();
    }

    if(ui->MinValidData->text() == "---"){
        ((P2P_DIST_INPUT_PARAM*)pInputPara)->valid_range.low_enable = 0;
    }else{
        ((P2P_DIST_INPUT_PARAM*)pInputPara)->valid_range.low_enable = 1;
        ((P2P_DIST_INPUT_PARAM*)pInputPara)->valid_range.low_threshold = ui->MinValidData->text().toFloat();
    }
    return 0;
}

void P2PDistanceWidget::on_btnCalculation_clicked()
{
    int ret = Set_Parameter_To_Ram();
    if(ret == 0)
    {
        QMessageBox::about(this,tr("警告"),tr("参数有误，请仔细检查并修改无误后重试！"));
        return;
    }
    Fun_GetLearnDialog GetDialog = (Fun_GetLearnDialog)m_Learn_Lib.resolve("GetDialog");
    QDialog *dlg = GetDialog();
    CalcTimer->start(10);
    dlg->exec();
}

void P2PDistanceWidget::CalcTimerSlot()
{

    Fun_SetResultString SetResultString = (Fun_SetResultString)m_Learn_Lib.resolve("SetResultString");
    QString info = tr("正在计算，请稍等");
    SetResultString(info);
    int ret = TaskStepLearnProc(m_step_index);
    if(ret == 0)
    {
        float i_range = 0.0;
        void *pPrivate = NULL;
        pPrivate = Task_Step_Private_Para_Get(m_step_index);
        if(ui->radioButton_phy->isChecked())
        {
            i_range = ((P2P_DIST_PRIVATE_PARAM *)pPrivate)->model_p2p_dist_result.phy_distance;
        }
        else
        {
            i_range = ((P2P_DIST_PRIVATE_PARAM *)pPrivate)->model_p2p_dist_result.distance;
        }
        ui->lineEdit_Dist->setText(QString::number(i_range));
        if(ui->checkBox_AutoSet->isChecked())
        {
            float iXMax ;
            float iXMin;
            iXMax = i_range*1.2;
            iXMin = i_range*0.8;
            ui->MaxValidData->setText(QString::number(iXMax));
            ui->MinValidData->setText(QString::number(iXMin));

        }
         ((FWP2PDistanceLabel*)m_label)->SetSet_Parameter_To_RamFlag(1);
        info = tr("计算成功!");
    }else
    {
        ((FWP2PDistanceLabel*)m_label)->SetSet_Parameter_To_RamFlag(0);
        info = tr("计算失败!")+tr("错误码:")+QString::number(ret,16);
    }
    SetResultString(info);
    CalcTimer->stop();
}

void P2PDistanceWidget::Get_Result_From_Ram()
{
    ((FWP2PDistanceLabel*)m_label)->SetSet_Parameter_To_RamFlag(1);
}

void P2PDistanceWidget::LoadLearnLib()
{
    m_Learn_Lib.setFileName("libLearningDialog.so");
    if(m_Learn_Lib.isLoaded())
    {
        qDebug()<<"load libLearningDialog.so isLoaded";
        return;
    }
    if(m_Learn_Lib.load())
    {
        printf("libLearningDialog.so OK\n");
    }
    else
    {
        qDebug()<<"load libLearningDialog.so fail"<<m_Learn_Lib.errorString();
    }
}
