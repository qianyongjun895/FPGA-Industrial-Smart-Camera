#include <QDebug>
#include "P2POffsetWidget.h"
#include "ui_P2POffsetWidget.h"
#include "TaskStepGlobal.h"
#include "FWP2POffsetLabel.h"
#include "PixelConvert.h"
#include <QMessageBox>
#include "TaskRstGlobal.h"
#include "threshold.h"
#include "PointOffsetGlobal.h"
#include "xmlInitGlobal.h"
#include "LinkDataGlobal.h"

P2POffsetWidget::P2POffsetWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::P2POffsetWidget)
{
    ui->setupUi(this);
    LoadKeyBoardLib();
    LoadLearnLib();
    m_label = new FWP2POffsetLabel(this);
    m_label->setGeometry(10,10,640,480);
    m_label->setAutoFillBackground(true);
    QPalette p = m_label->palette();
    p.setColor(QPalette::Background,QColor(50,50,50,255));
    m_label->setPalette(p);

    ui->radioButton_pix->setChecked(true);
    CalcTimer = new QTimer;
    ui->MaxXValidData->installEventFilter(this);
    ui->MinXValidData->installEventFilter(this);
    ui->MaxYValidData->installEventFilter(this);
    ui->MinYValidData->installEventFilter(this);
    connect(ui->comboBoxPoint1, SIGNAL(currentIndexChanged(int)), this, SLOT(Point1TaskChangeSlot(int)));
    connect(ui->comboBoxPoint2, SIGNAL(currentIndexChanged(int)), this, SLOT(Point2TaskChangeSlot(int)));
    connect(ui->comboBoxPoint1Result, SIGNAL(activated(int)), this, SLOT(Point1ResultChangeSlot(int)));
    connect(ui->comboBoxPoint2Result, SIGNAL(activated(int)), this, SLOT(Point2ResultChangeSlot(int)));
    connect(CalcTimer, &QTimer::timeout, this, &P2POffsetWidget::CalcTimerSlot);
}

P2POffsetWidget::~P2POffsetWidget()
{
    ui->MaxXValidData->removeEventFilter(this);
    ui->MinXValidData->removeEventFilter(this);
    ui->MaxYValidData->removeEventFilter(this);
    ui->MinYValidData->removeEventFilter(this);
    if(m_label !=NULL)
    {
        delete m_label;
        m_label = NULL;
    }
    delete CalcTimer;
    delete ui;
}

/**
 * @brief P2POffsetWidget::Set_Parameter_To_Ram
 * @author dgq
 * @note 将界面的配置参数写入内存
 */
int P2POffsetWidget::Set_Parameter_To_Ram()
{
    unsigned int i_task_id;
    TASK_STEP_HEADER *pStephead = Task_Step_Head_Get(m_step_index);
    int i_task1_index =  atoi(ui->comboBoxPoint1->currentText().toStdString().c_str());
    Task_Step_Type_ID_Get(i_task1_index,&i_task_id);
    int i_result1_index =  Get_Point_Or_Line_Result_Id(i_task_id,ui->comboBoxPoint1Result->currentIndex());
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
    SetXRangetoLib();
    SetYRangetoLib();
    return 1;
}

int P2POffsetWidget::SetXRangetoLib()
{
    if(ui->radioButton_phy->isChecked())
    {
        ((OFFSET_POINT_INPUT_PARAM*)pInputPara)->pix_phy_flag = 1;
    }
    else
    {
        ((OFFSET_POINT_INPUT_PARAM*)pInputPara)->pix_phy_flag = 0;
    }
    if(ui->MaxXValidData->text() == "---"){
        ((OFFSET_POINT_INPUT_PARAM*)pInputPara)->valid_range_x.high_enable = 0;
    }else{
        ((OFFSET_POINT_INPUT_PARAM*)pInputPara)->valid_range_x.high_enable = 1;
        ((OFFSET_POINT_INPUT_PARAM*)pInputPara)->valid_range_x.high_threshold = ui->MaxXValidData->text().toFloat();
    }

    if(ui->MinXValidData->text() == "---"){
        ((OFFSET_POINT_INPUT_PARAM*)pInputPara)->valid_range_x.low_enable = 0;
    }else{
        ((OFFSET_POINT_INPUT_PARAM*)pInputPara)->valid_range_x.low_enable = 1;
        ((OFFSET_POINT_INPUT_PARAM*)pInputPara)->valid_range_x.low_threshold = ui->MinXValidData->text().toFloat();
    }
    return 0;
}

int P2POffsetWidget::SetYRangetoLib()
{
    if(ui->MaxYValidData->text() == "---"){
        ((OFFSET_POINT_INPUT_PARAM*)pInputPara)->valid_range_y.high_enable = 0;
    }else{
        ((OFFSET_POINT_INPUT_PARAM*)pInputPara)->valid_range_y.high_enable = 1;
        ((OFFSET_POINT_INPUT_PARAM*)pInputPara)->valid_range_y.high_threshold = ui->MaxYValidData->text().toFloat();
    }

    if(ui->MinYValidData->text() == "---"){
        ((OFFSET_POINT_INPUT_PARAM*)pInputPara)->valid_range_y.low_enable = 0;
    }else{
        ((OFFSET_POINT_INPUT_PARAM*)pInputPara)->valid_range_y.low_enable = 1;
        ((OFFSET_POINT_INPUT_PARAM*)pInputPara)->valid_range_y.low_threshold = ui->MinYValidData->text().toFloat();
    }
    return 0;
}

/**
 * @brief P2POffsetWidget::Init_Input_Ptr
 * @param ptr 输入结构体内存指针
 * @param i_step_index 任务步骤号
 * @author dgq
 * @note 初始化Input结构体指针
 */
void P2POffsetWidget::Init_Input_Ptr(void *ptr,int i_step_index,int new_flag,void *pen_color)
{
    ((FWP2POffsetLabel*)m_label)->SetPenColor(pen_color);
    pInputPara = ptr;
    m_step_index = i_step_index;
    if(pInputPara == NULL)
    {
        QMessageBox::about(this,tr(""),tr("初始化数据失败"));
        return;
    }
    m_i_load_first = 0;
    unsigned int i_task_id = 0;
    unsigned int i = 0;
    ui->comboBoxPoint1->addItem("");
    ui->comboBoxPoint2->addItem("");
    for(unsigned i = 0; i < i_step_index-1; i++)
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
    if(new_flag)
    {
        TASK_STEP_HEADER *pStephead = Task_Step_Head_Get(i_step_index);
        pStephead->step_link.link_info[0].step_index = 0;
        pStephead->step_link.link_info[0].result_index = 0;
        pStephead->step_link.link_info[1].step_index = 0;
        pStephead->step_link.link_info[1].result_index = 0;
        Task_Step_Synthetic_Judge_Flag_Set(i_step_index,1);
        ((OFFSET_POINT_INPUT_PARAM*)pInputPara)->pix_phy_flag = 0;
        ((OFFSET_POINT_INPUT_PARAM*)pInputPara)->valid_range_x.high_enable = 0;
        ((OFFSET_POINT_INPUT_PARAM*)pInputPara)->valid_range_x.low_enable = 0;
        ((OFFSET_POINT_INPUT_PARAM*)pInputPara)->valid_range_y.high_enable = 0;
        ((OFFSET_POINT_INPUT_PARAM*)pInputPara)->valid_range_y.low_enable = 0;
    }
    InitData(i_step_index);
    m_i_load_first = 1;

}


QString P2POffsetWidget::InitPointCombobox(int TaskIndex, int id)
{
    QString name;

    int ret = Get_Point_Or_Line_Flag(id);
    if(ret == 0)
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
 * @brief P2POffsetWidget::InitData
 * @param i_step_index
 * @author dgq
 * @note 初始化
 */
void P2POffsetWidget::InitData(int i_step_index)
{
    unsigned int i = 0;
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
            for(i = 1; i < i_mul_rst_cnt+1; i++)
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
            for(i = 1; i < i_mul_rst_cnt+1; i++)
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
    GetRefPara(i_task1_index,i_result1_index,&point);
    ((FWP2POffsetLabel*)m_label)->SetPoint1(point);
    Task_Step_Type_ID_Get(i_task2_index,&id);
    Mul_Flag = Get_Multi_Result_Task_Flag(id);
    if(Mul_Flag == -1)
    {
        ui->comboBoxPoint2Result->setEnabled(false);
    }else
    {
        ui->comboBoxPoint2Result->setCurrentIndex(Point_Or_Line_Result_Id_Change_UI_Id(id,i_result2_index));
    }
    GetRefPara(i_task2_index,i_result2_index,&point);
    ((FWP2POffsetLabel*)m_label)->SetPoint2(point);
    InitRangeData();
}

void P2POffsetWidget::InitRangeData()
{

    if(((OFFSET_POINT_INPUT_PARAM*)pInputPara)->pix_phy_flag == 0)
    {
        ui->radioButton_phy->setChecked(false);
        ui->radioButton_pix->setChecked(true);
        pix_phy_flag = 0;
    }else
    {
        ui->radioButton_phy->setChecked(true);
        ui->radioButton_pix->setChecked(false);
        pix_phy_flag = 1;
    }
    if(((OFFSET_POINT_INPUT_PARAM*)pInputPara)->valid_range_y.low_enable == 0){
        ui->MinXValidData->setText("---");
    }else{
        ui->MinXValidData->setText(QString::number(((OFFSET_POINT_INPUT_PARAM*)pInputPara)->valid_range_x.low_threshold));
    }

    //获取X方向上限范围使能
    if(((OFFSET_POINT_INPUT_PARAM*)pInputPara)->valid_range_y.high_enable == 0){
        ui->MaxXValidData->setText("---");
    }else{
        ui->MaxXValidData->setText(QString::number(((OFFSET_POINT_INPUT_PARAM*)pInputPara)->valid_range_x.high_threshold));
    }


    //获取Y方向下限范围使能
    if(((OFFSET_POINT_INPUT_PARAM*)pInputPara)->valid_range_y.low_enable == 0){
        ui->MinYValidData->setText("---");
    }else{
        ui->MinYValidData->setText(QString::number(((OFFSET_POINT_INPUT_PARAM*)pInputPara)->valid_range_y.low_threshold));
    }


    //获取Y方向上限范围使能
    if(((OFFSET_POINT_INPUT_PARAM*)pInputPara)->valid_range_y.high_enable == 0){
        ui->MaxYValidData->setText("---");
    }else{
        ui->MaxYValidData->setText(QString::number(((OFFSET_POINT_INPUT_PARAM*)pInputPara)->valid_range_y.high_threshold));
    }
}

/**
 * @brief P2POffsetWidget::Point1TaskChangeSlot
 * @param index 下拉框的当前索引
 * @author dgq
 * @note 点1的关联任务发生改变时的处理
 */
void P2POffsetWidget::Point1TaskChangeSlot(int index)
{
    ((FWP2POffsetLabel*)m_label)->SetPoint1(QPoint(-20,-20));
    if(m_i_load_first == 1)
    {
        int index1 = atoi(ui->comboBoxPoint1->currentText().toStdString().c_str());
        if(index1 == 0)
        {
            ui->comboBoxPoint1Result->clear();
            return;
        }
        ui->comboBoxPoint1Result->setEnabled(true);

        ui->comboBoxPoint1Result->clear();
        ui->comboBoxPoint1Result->addItem(" ");
        unsigned int id;
        Task_Step_Type_ID_Get(index1,&id);
        int  Mul_Flag = Get_Multi_Result_Task_Flag(id);
        if(Mul_Flag ==1)
        {
            unsigned int i_mul_rst_cnt = 0;
            TaskMultiRstNumGet(index1,1,&i_mul_rst_cnt);
            ui->comboBoxPoint1Result->setEnabled(true);
            for(unsigned int i = 1; i<= i_mul_rst_cnt;i++)
            {
                QString strLineIndex;
                strLineIndex = tr("点")+QString::number(i);
                ui->comboBoxPoint1Result->addItem(strLineIndex);
            }
        }else
        {
            ui->comboBoxPoint1Result->setEnabled(false);
            QPoint point1;
            GetRefPara(index1,Point_Or_Line_Result_Id_Change_UI_Id(id,0),&point1);
            ((FWP2POffsetLabel*)m_label)->SetPoint1(point1);
        }

    }
}

/**
 * @brief P2POffsetWidget::Point2TaskChangeSlot
 * @param index 下拉框的当前索引
 * @author dgq
 * @note 点2的关联任务发生改变时的处理
 */
void P2POffsetWidget::Point2TaskChangeSlot(int index)
{
    ((FWP2POffsetLabel*)m_label)->SetPoint2(QPoint(-20,-20));
    if(m_i_load_first == 1)
    {
        int index2 = atoi(ui->comboBoxPoint2->currentText().toStdString().c_str());
        if(index2 == 0)
        {
            ui->comboBoxPoint2Result->clear();
            return;
        }
        ui->comboBoxPoint2Result->setEnabled(true);

        ui->comboBoxPoint2Result->clear();
        ui->comboBoxPoint2Result->addItem(" ");
        unsigned int id;
        Task_Step_Type_ID_Get(index2,&id);
        int  Mul_Flag = Get_Multi_Result_Task_Flag(id);
        if(Mul_Flag == 1)
        {
            unsigned int i_mul_rst_cnt = 0;
            TaskMultiRstNumGet(index2,1,&i_mul_rst_cnt);
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
            GetRefPara(index2,Point_Or_Line_Result_Id_Change_UI_Id(id,0),&point2);
            ((FWP2POffsetLabel*)m_label)->SetPoint2(point2);
        }
    }
}

/**
 * @brief P2POffsetWidget::Point1ResultChangeSlot
 * @param index 下拉框索引
 * @author dgq
 * @note 引用结果发生改变时的处理
 */
void P2POffsetWidget::Point1ResultChangeSlot(int index)
{
    if(m_i_load_first ==1)
    {
        int Result1_index = ui->comboBoxPoint1Result->currentIndex();
        int Task_index1 = atoi(ui->comboBoxPoint1->currentText().toStdString().c_str());
        QPoint point1;
        float point_pix_vga_x = 0.0;
        float point_pix_vga_y = 0.0;
        float point_pix_sub_x = 0.0;
        float point_pix_sub_y = 0.0;
#if 1
        POINT_F pointf;
        unsigned int id;
        Task_Step_Type_ID_Get(Task_index1,&id);
        int ret = measure_ref_point_result_get(Task_index1,Get_Point_Or_Line_Result_Id(id,Result1_index),&pointf,1);
        if(ret != 0)
        {
            qDebug()<<"measure_ref_point_result_get ret = "<<ret;
        }
        point_pix_sub_x = pointf.x_f;
        point_pix_sub_y = pointf.y_f;
        PixelCvt(&point_pix_sub_x,&point_pix_vga_x,CVT_SUB2VGA|CVT_F2F|CVT_DATA);
        PixelCvt(&point_pix_sub_y,&point_pix_vga_y,CVT_SUB2VGA|CVT_F2F|CVT_DATA);
        point1.setX(point_pix_vga_x);
        point1.setY(point_pix_vga_y);
        ((FWP2POffsetLabel*)m_label)->SetPoint1(point1);
#endif
    }
}
void P2POffsetWidget::Point2ResultChangeSlot(int index)
{
    if(m_i_load_first ==1)
    {
        int Result2_index = ui->comboBoxPoint2Result->currentIndex();
        int Task_index2 = atoi(ui->comboBoxPoint2->currentText().toStdString().c_str());

        QPoint point2;
        float point_pix_vga_x = 0.0;
        float point_pix_vga_y = 0.0;
        float point_pix_sub_x = 0.0;
        float point_pix_sub_y = 0.0;
#if 1
        POINT_F pointf;
        unsigned int id;
        Task_Step_Type_ID_Get(Task_index2,&id);
        int ret = measure_ref_point_result_get(Task_index2,Get_Point_Or_Line_Result_Id(id,Result2_index),&pointf,1);
        if(ret != 0)
        {
            qDebug()<<"measure_ref_point_result_get ret = "<<ret;
        }
        point_pix_sub_x = pointf.x_f;
        point_pix_sub_y = pointf.y_f;
        PixelCvt(&point_pix_sub_x,&point_pix_vga_x,CVT_SUB2VGA|CVT_F2F|CVT_DATA);
        PixelCvt(&point_pix_sub_y,&point_pix_vga_y,CVT_SUB2VGA|CVT_F2F|CVT_DATA);
        point2.setX(point_pix_vga_x);
        point2.setY(point_pix_vga_y);
        ((FWP2POffsetLabel*)m_label)->SetPoint2(point2);
#endif
    }
}

void P2POffsetWidget::on_btnCalculation_clicked()
{
    Set_Parameter_To_Ram();
    Fun_GetLearnDialog GetDialog = (Fun_GetLearnDialog)m_Learn_Lib.resolve("GetDialog");
    QDialog *dlg = GetDialog();
    CalcTimer->start(10);
    dlg->exec();
}


void P2POffsetWidget::CalcTimerSlot()
{

    Fun_SetResultString SetResultString = (Fun_SetResultString)m_Learn_Lib.resolve("SetResultString");
    QString info = tr("正在计算，请稍等");
    SetResultString(info);
    int ret = TaskStepLearnProc(m_step_index);
    if(ret == 0)
    {
        GetDataFromLib();
        info = tr("计算成功!");
    }else
    {
        info = tr("计算失败!")+tr("错误码:")+QString::number(ret,16);
    }
    SetResultString(info);
    CalcTimer->stop();
}

void P2POffsetWidget::LoadLearnLib()
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

void P2POffsetWidget::GetDataFromLib()
{
    float i_X_Offset = 0.0;
    float i_Y_Offset = 0.0;
    void *pPrivate = NULL;
    pPrivate = Task_Step_Private_Para_Get(m_step_index);
    if(ui->radioButton_pix->isChecked())
    {
        i_X_Offset = ((OFFSET_POINT_PRIVATE_PARAM*)pPrivate)->model_offset_result.point_offset.x_f;
        i_Y_Offset = ((OFFSET_POINT_PRIVATE_PARAM*)pPrivate)->model_offset_result.point_offset.y_f;
    }else
    {
        i_X_Offset = ((OFFSET_POINT_PRIVATE_PARAM*)pPrivate)->model_offset_result.phy_point_offset.x_f;
        i_Y_Offset = ((OFFSET_POINT_PRIVATE_PARAM*)pPrivate)->model_offset_result.phy_point_offset.y_f;
    }

    ui->lineEdit_XOffset->setText(QString::number(i_X_Offset));
    ui->lineEdit_YOffset->setText(QString::number(i_Y_Offset));
    if(ui->checkBox_AutoSet->isChecked())
    {

        float iXMax ;
        float iXMin;
        if(i_X_Offset > 0)
        {
            iXMax = i_X_Offset*1.2;
            iXMin = i_X_Offset*0.8;
        }
        else
        {
            iXMin = i_X_Offset*1.2;
            iXMax = i_X_Offset*0.8;
        }
        float iYMax ;
        float iYMin ;
        if(i_Y_Offset > 0)
        {
            iYMax = i_Y_Offset*1.2;
            iYMin = i_Y_Offset*0.8;
        }
        else
        {
            iYMin = i_Y_Offset*1.2;
            iYMax = i_Y_Offset*0.8;
        }
        if(ui->radioButton_phy->isChecked())
        {
            ui->MaxXValidData->setText(QString::number(iXMax));
            ui->MinXValidData->setText(QString::number(iXMin));
            ui->MaxYValidData->setText(QString::number(iYMax));
            ui->MinYValidData->setText(QString::number(iYMin));
        }
        else
        {
            ui->MaxXValidData->setText(QString::number(qRound(iXMax)));
            ui->MinXValidData->setText(QString::number(qRound(iXMin)));
            ui->MaxYValidData->setText(QString::number(qRound(iYMax)));
            ui->MinYValidData->setText(QString::number(qRound(iYMin)));
        }
    }
}

void P2POffsetWidget::LoadKeyBoardLib()
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

bool P2POffsetWidget::eventFilter(QObject *watched, QEvent *event)
{

    if (watched == ui->MaxXValidData || watched == ui->MinXValidData ||\
            watched == ui->MaxYValidData || watched == ui->MinYValidData)         //首先判断控件(这里指 lineEdit1)
    {
//        LoadKeyBoardLib();
        if (event->type() == QEvent::MouseButtonPress)     //然后再判断控件的具体事件 (这里指点击事件)
        {
            QDialog *dlg;
            Fun_GetNumkeyBoardDlg GetNumKeyBoardDlg = (Fun_GetNumkeyBoardDlg)m_keyBoard_Lib.resolve("GetNumKeyBoardDialog");
            if(GetNumKeyBoardDlg)
            {
                dlg = GetNumKeyBoardDlg();
                Fun_SetRangeInput SetRangeInput = (Fun_SetRangeInput)m_keyBoard_Lib.resolve("SetRangeInput");
                if(SetRangeInput)
                {
                    if(watched == ui->MaxXValidData)
                    {

                        if(ui->MaxXValidData->text() != "---"){
                            SetRangeInput(ui->MaxXValidData->text(),ui->MinXValidData->text(),1);
                        }else{
                            SetRangeInput(ui->lineEdit_XOffset->text(),ui->MinXValidData->text(),1);
                        }
                    }
                    if(watched == ui->MaxYValidData)
                    {
                        if(ui->MaxYValidData->text() != "---"){
                            SetRangeInput(ui->MaxYValidData->text(),ui->MinYValidData->text(),1);
                        }else{
                            SetRangeInput(ui->lineEdit_YOffset->text(),ui->MinYValidData->text(),1);
                        }
                    }
                    if(watched == ui->MinXValidData)
                    {
                        if(ui->MinXValidData->text() != "---"){
                            SetRangeInput(ui->MaxXValidData->text(),ui->MinXValidData->text(),0);
                        }else{
                            SetRangeInput(ui->MaxXValidData->text(),ui->lineEdit_XOffset->text(),0);
                        }
                    }
                    if(watched == ui->MinYValidData)
                    {
                        if(ui->MinYValidData->text() != "---"){
                            SetRangeInput(ui->MaxYValidData->text(),ui->MinYValidData->text(),0);
                        }else{
                            SetRangeInput(ui->MaxYValidData->text(),ui->lineEdit_YOffset->text(),0);
                        }
                    }
                    int ret = dlg->exec();
                    if(ret == QDialog::Accepted)
                    {
                        Fun_GetRangeNum GetRangeNum = (Fun_GetRangeNum)m_keyBoard_Lib.resolve("GetRangeNum");
                        if(GetRangeNum)
                        {
                            ((QLineEdit *)watched)->setText(GetRangeNum());
                        }
                    }
                }
            }
        }
    }
    return QWidget::eventFilter(watched, event);

}


void P2POffsetWidget::on_radioButton_phy_clicked()
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
        QMessageBox::StandardButton rb = QMessageBox::warning(NULL, tr("警告"), tr("切换数据类型会清空偏移量范围的数据，确定切换?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
        if(rb == QMessageBox::No)
        {
            ui->radioButton_pix->setChecked(true);
            return;
        }
        pix_phy_flag = 1;
        ui->lineEdit_XOffset->setText("");
        ui->lineEdit_YOffset->setText("");
        ui->MaxXValidData->setText("---");
        ui->MaxYValidData->setText("---");
        ui->MinXValidData->setText("---");
        ui->MinYValidData->setText("---");
    }

}

void P2POffsetWidget::on_radioButton_pix_clicked()
{
    if(pix_phy_flag == 1)
    {
        QMessageBox::StandardButton rb = QMessageBox::warning(NULL, tr("警告"), tr("切换数据类型会清空偏移量范围的数据，确定切换?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
        if(rb == QMessageBox::No)
        {
            ui->radioButton_phy->setChecked(true);
            return;
        }
        pix_phy_flag = 0;
        ui->lineEdit_XOffset->setText("");
        ui->lineEdit_YOffset->setText("");
        ui->MaxXValidData->setText("---");
        ui->MaxYValidData->setText("---");
        ui->MinXValidData->setText("---");
        ui->MinYValidData->setText("---");
    }
}

void P2POffsetWidget::GetRefPara(int ref_step,int ref_result,QPoint *point)
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
QPoint P2POffsetWidget::Get_Image_Pos()
{
    QPoint point(10,10);

    if(m_label != NULL)
    {
        point = m_label->pos();
    }

    return point;
}
