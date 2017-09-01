#include <QDebug>
#include "WHMeasureWidget.h"
#include "ui_WHMeasureWidget.h"
#include <QMessageBox>
#include "FWWHMeasureLabel.h"
#include "xmlInitGlobal.h"
#include "LinkDataGlobal.h"
#include "HardwareConfig.h"

WHMeasureWidget::WHMeasureWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WHMeasureWidget)
{
    ui->setupUi(this);
    LoadKeyBoardLib();
    LoadLearnLib();
    QList<QLineEdit *> lineEdit = this->findChildren<QLineEdit *>();
    foreach (QLineEdit * L, lineEdit) {
        L->installEventFilter(this);
        }
    m_label = new FWWHMeasureLabel(this);
    m_label->setGeometry(10,10,640,480);
    m_label->setAutoFillBackground(true);
    QPalette p = m_label->palette();
    p.setColor(QPalette::Background,QColor(50,50,50,255));
    m_label->setPalette(p);
    Calc_rst_flag = 0;
    CalcTimer = new QTimer;
    connect(CalcTimer, &QTimer::timeout, this, &WHMeasureWidget::CalcTimerSlot);
    connect(ui->btnMoveUp,&QPushButton::released,this,&WHMeasureWidget::GetCurrentTime);
    connect(ui->btnMoveDown,&QPushButton::released,this,&WHMeasureWidget::GetCurrentTime);
    connect(ui->btnMoveLeft,&QPushButton::released,this,&WHMeasureWidget::GetCurrentTime);
    connect(ui->btnMoveRight,&QPushButton::released,this,&WHMeasureWidget::GetCurrentTime);

    connect((FWWHMeasureLabel*)m_label,&FWWHMeasureLabel::LinePosChangeSignal,\
            this,&WHMeasureWidget::LinePosChangeSlot);
}

WHMeasureWidget::~WHMeasureWidget()
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
    delete CalcTimer;
//    Destroy_Map_Mem();
    delete ui;
}

void WHMeasureWidget::LinePosChangeSlot(int x, int y)
{
    ui->txt_x_stat_threshold->setText(QString::number(x));
    ui->txt_y_stat_threshold->setText(QString::number(y));
}

/**
 * @brief WHMeasureWidget::Get_Image_Pos
 * @return
 * @author dgq
 * @note 获取图像显示区域的位置
 */
QPoint WHMeasureWidget::Get_Image_Pos()
{
    QPoint point(10,10);

    if(m_label != NULL)
    {
        point = m_label->pos();
    }
    return point;
}

int WHMeasureWidget::Set_Parameter_To_Ram()
{
    TASK_STEP_HEADER *pTaskHead = Task_Step_Head_Get(m_step_index);
    if(!pTaskHead->compass_enable)
    {
        QMessageBox::about(this,tr(""),tr("请先使能关联定位，并选择关联数据"));
        return -1;
    }
#if 0 //设置引用直线的索引
    unsigned int i_task_id;
    TASK_STEP_HEADER *pStephead = Task_Step_Head_Get(m_step_index);
    int i_task_index = atoi(ui->comboBoxLineStep->currentText().toStdString().c_str());
    Task_Step_Type_ID_Get(i_task_index,&i_task_id);
    int i_result_index = Get_Point_Or_Line_Result_Id(i_task_id,ui->comboBoxLineIndex->currentIndex());
    pStephead->step_link.link_count = 1;
    pStephead->step_link.link_info[0].step_index = i_task_index;
    pStephead->step_link.link_info[0].result_index = i_result_index;
#endif
    int x_stat_threshold = ui->txt_x_stat_threshold->text().toInt();
    int y_stat_threshold = ui->txt_y_stat_threshold->text().toInt();
    int x_real_value;
    int y_real_value;
    PixelCvt(&x_stat_threshold,&x_real_value,CVT_VGA2REAL|CVT_I2I|CVT_DATA);
    PixelCvt(&y_stat_threshold,&y_real_value,CVT_VGA2REAL|CVT_I2I|CVT_DATA);
    pInputPara->x_stat_threshold = y_real_value;
    pInputPara->y_stat_threshold = x_real_value;
    qDebug()<<"pInputPara->x_stat_threshold = "<<pInputPara->x_stat_threshold;
    qDebug()<<"pInputPara->y_stat_threshold = "<<pInputPara->y_stat_threshold;
    if(ui->radioButton_phy->isChecked())
    {
        pInputPara->pix_phy_flag = 1;
    }else
    {
        pInputPara->pix_phy_flag = 0;
    }

    Set_Range_To_Ram();
    return 1;
}

void WHMeasureWidget::Init_Input_Ptr(void *ptr,int i_step_index,int new_flag,void *pen_color)
{
    ((FWWHMeasureLabel*)m_label)->SetPenColor(pen_color);
    pInputPara = (MAP_INPUT_PARAM *)ptr;
    m_step_index = i_step_index;
    if(pInputPara == NULL)
    {
        QMessageBox::about(this,tr(""),tr("初始化数据失败"));
        return;
    }

    ui->radioButton_phy->setEnabled(true);
    unsigned int i_caliPara;
    Task_Step_Scale_Cali_Param_Index_Get(m_step_index,&i_caliPara);
    if(i_caliPara == 0)
    {
        ui->radioButton_phy->setEnabled(false);
        ui->radioButton_pix->setChecked(true);
        pix_phy_flag = 0;
    }
//    InitComboBox(i_step_index);
    if(new_flag)
    {
        Task_Step_Synthetic_Judge_Flag_Set(i_step_index,1);
        pInputPara->x_stat_threshold = 320;
        pInputPara->y_stat_threshold = 240;
        pInputPara->pix_phy_flag = 0;
        pInputPara->width_threshold.high_enable = TH_DISABLE;
        pInputPara->width_threshold.low_enable = TH_DISABLE;
        pInputPara->heigh_threshold.high_enable = TH_DISABLE;
        pInputPara->heigh_threshold.low_enable = TH_DISABLE;
    }
    InitData();
}

void WHMeasureWidget::CalcTimerSlot()
{
    Calc_rst_flag = 1;
    Fun_SetResultString SetResultString = (Fun_SetResultString)m_Learn_Lib.resolve("SetResultString");
    QString info = tr("正在计算，请稍等");
    SetResultString(info);
//    TaskRunRstMemInit();
    int ret = TaskStepLearnProc(m_step_index);
    if(ret == 0)
    {
        Get_Result_From_Ram();
        info = tr("计算成功!");
    }else
    {
        info = tr("计算失败!")+tr("错误码:")+QString::number(ret,16);
    }
    SetResultString(info);
    Calc_rst_flag = 0;
    CalcTimer->stop();
}

void WHMeasureWidget::Get_Result_From_Ram()
{
    MAP_PRIVATE_PARAM *pPrivate = (MAP_PRIVATE_PARAM *)Task_Step_Private_Para_Get(m_step_index);
    if(ui->radioButton_phy->isChecked())
    {
        double d_width_rst = pPrivate->model_map_rst.width_phy;
        double d_height_rst = pPrivate->model_map_rst.height_phy;
        ui->txt_CalcWidth->setText(QString::number(d_width_rst));
        ui->txt_calcHeight->setText(QString::number(d_height_rst));
        if(ui->checkBox_AutoSet->isChecked())
        {
            ui->MaxWidth->setText(QString::number((int)(d_width_rst*1.2)));
            ui->MinWidth->setText(QString::number((int)(d_width_rst*0.8)));
            ui->MaxHeight->setText(QString::number((int)(d_height_rst*1.2)));
            ui->MinHeight->setText(QString::number((int)(d_height_rst*0.8)));
        }
    }else
    {
        unsigned int i_width_rst = pPrivate->model_map_rst.width_pixel;
        unsigned int i_height_rst = pPrivate->model_map_rst.height_pixel;
        ui->txt_CalcWidth->setText(QString::number(i_width_rst));
        ui->txt_calcHeight->setText(QString::number(i_height_rst));
        if(ui->checkBox_AutoSet->isChecked())
        {
            ui->MaxWidth->setText(QString::number((int)(i_width_rst*1.2)));
            ui->MinWidth->setText(QString::number((int)(i_width_rst*0.8)));
            ui->MaxHeight->setText(QString::number((int)(i_height_rst*1.2)));
            ui->MinHeight->setText(QString::number((int)(i_height_rst*0.8)));
        }
    }
    unsigned int width = Get_HWC_Pixel_Width();
    unsigned int height = Get_HWC_Pixel_Height();
    void *p_xStat = NULL;
    void *p_yStat = NULL;
    if (p_xStat == NULL) {
        p_xStat = GetMapDataAddr();
    }
    if (p_yStat == NULL) {
        p_yStat = (void *)((u32)p_xStat + sizeof(u16)*width);
    }

    QVector<QPoint> xPoints;
    QVector<QPoint> yPoints;
    xPoints.clear();
    yPoints.clear();
    int index = 0;
    for(unsigned int i = 0; i < width; i++)
    {
        if(i%2 == 0)
        {
            index++;
            xPoints.append(QPoint(index,(((u16*)p_xStat)[i])*0.5));
            if(i < height)
            {
                yPoints.append(QPoint((((u16*)p_yStat)[i])*0.5,index));
            }
        }
    }
    ((FWWHMeasureLabel *)m_label)->SetXCurveLines(xPoints);
    ((FWWHMeasureLabel *)m_label)->SetYCurveLines(yPoints);


}

void WHMeasureWidget::on_btnCalculation_clicked()
{
    int ret = Set_Parameter_To_Ram();
    if(ret == -1)
    {
        return;
    }
    Fun_GetLearnDialog GetDialog = (Fun_GetLearnDialog)m_Learn_Lib.resolve("GetDialog");
    QDialog *dlg = GetDialog();
    CalcTimer->start(10);
    dlg->exec();
}

bool WHMeasureWidget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->MaxWidth){
        if (event->type()==QEvent::MouseButtonPress){
            RangeInputPro(ui->MaxWidth,ui->MinWidth,ui->txt_CalcWidth->text(),THRESHOLD_HIGH);
        }
    }
    if(watched == ui->MinWidth){
        if (event->type()==QEvent::MouseButtonPress){
            RangeInputPro(ui->MaxWidth,ui->MinWidth,ui->txt_CalcWidth->text(),THRESHOLD_LOW);
        }
    }
    if(watched == ui->MaxHeight){
        if (event->type()==QEvent::MouseButtonPress){
            RangeInputPro(ui->MaxHeight,ui->MinHeight,ui->txt_calcHeight->text(),THRESHOLD_HIGH);
        }
    }
    if(watched == ui->MinHeight){
        if (event->type()==QEvent::MouseButtonPress){
            RangeInputPro(ui->MaxHeight,ui->MinHeight,ui->txt_calcHeight->text(),THRESHOLD_LOW);
        }
    }
    return QWidget::eventFilter(watched, event);
}


/**
 * @brief WHMeasureWidget::RangeInputPro
 * @param pEditMax 上限输入框
 * @param pEditMin 下限输入框
 * @param calc_value 计算值
 * @param flag 上限、下限标志 1上限，0下限
 * @author dgq
 * @note blob门限输入函数
 */
void WHMeasureWidget::RangeInputPro(QLineEdit *pEditMax,QLineEdit *pEditMin,QString calc_value,int flag)
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

void WHMeasureWidget::InitData()
{
    unsigned int x_real_value = pInputPara->y_stat_threshold;
    unsigned int y_real_value = pInputPara->x_stat_threshold;
    int x_stat_threshold;
    int y_stat_threshold;
    PixelCvt(&x_real_value,&x_stat_threshold,CVT_REAL2VGA|CVT_I2I|CVT_DATA);
    PixelCvt(&y_real_value,&y_stat_threshold,CVT_REAL2VGA|CVT_I2I|CVT_DATA);
    ((FWWHMeasureLabel *)m_label)->SetXDirLine(x_stat_threshold);
    ((FWWHMeasureLabel *)m_label)->SetYDirLine(y_stat_threshold);
    InitRangeData();

}



void WHMeasureWidget::LoadKeyBoardLib()
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

void WHMeasureWidget::LoadLearnLib()
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

QString WHMeasureWidget::InitLineCombobox(int TaskIndex, int id)
{
    QString name;
    int ret = Get_Point_Or_Line_Flag(id);
    if(ret == 1)//线任务
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

int WHMeasureWidget::Line_Paint_Base_On_KB_SubPixel(float k_f, float b_f, QLine *pOsd_line)
{
    int i = 0;
    int count = 0;
    QPointF calc_point[4];

    calc_point[0].setX(0);
    calc_point[0].setY(b_f);
    /* Point1 x=640, calculate y  */
    calc_point[1].setX(VGA_WIDTH);
    calc_point[1].setY(k_f*VGA_WIDTH+b_f);
    /* Point1 y=0, calculate x  */
    calc_point[2].setX((0-b_f)/k_f);
    calc_point[2].setY(0);
    /* Point1 y=480, calculate x  */
    calc_point[3].setX((VGA_HEIGHT-b_f)/k_f);
    calc_point[3].setY(VGA_HEIGHT);

    for(i = 0; i < 4; i++)
    {
        //DRV_PRINT(LOCATION_DEBUG, "point%d: x=%d, y=%d\n", i, (int)calc_point[i].x_f, (int)calc_point[i].y_f);
        if(calc_point[i].x()>=0 && calc_point[i].x()<=VGA_WIDTH && calc_point[i].y()>=0 && calc_point[i].y()<=VGA_HEIGHT)
        {
            if(count == 0)
            {
                count++;
                pOsd_line->setP1(QPoint(calc_point[i].x(),calc_point[i].y()));
            }
            else
            {
                pOsd_line->setP2(QPoint(calc_point[i].x(),calc_point[i].y()));
            }
        }
    }

    return 0;
}

int WHMeasureWidget::Line_Osd_Init(LineParameter *pLinePara, QLine *pOsdLine)
{
    float line_kf = 0;
    float line_bf = 0;
    float line_k, line_b;

    float pix_vga_y = 0.0;
    float pix_vga_x = 0.0;
    float pix_sub_y = (float)pLinePara->y;
    float pix_sub_x = (float)pLinePara->x;
    PixelCvt((void *)(&pix_sub_y),(void *)(&pix_vga_y),CVT_SUB2VGA|CVT_F2F|CVT_DATA);
    PixelCvt((void *)(&pix_sub_x),(void *)(&pix_vga_x),CVT_SUB2VGA|CVT_F2F|CVT_DATA);
    line_kf = tan(pLinePara->theta);
//    line_bf = (X_Y_CONVERT_SUB2UI((float)pLinePara->y) - line_kf * X_Y_CONVERT_SUB2UI((float)pLinePara->x));
    line_bf = (pix_vga_y - line_kf * pix_vga_x);
    line_k = (int)(line_kf*10000);
    line_b = (int)(line_bf*10000);

    if(line_k == 0x7fffffff || line_k == 0x80000000 || line_b == 0x7fffffff || line_b == 0x80000000)
    {
//        Vertical_Line_Paint((unsigned int)pLinePara->x, pOsdLine);

        pOsdLine->setP1(QPoint(pix_vga_x,0));
        pOsdLine->setP2(QPoint(pix_vga_x,VGA_HEIGHT));
    }else
    {
        Line_Paint_Base_On_KB_SubPixel(line_kf, line_bf, pOsdLine);
    }

    return 0;
}


int WHMeasureWidget::Set_Range_To_Ram()
{
    if(ui->MaxWidth->text() == "---"){
        pInputPara->width_threshold.high_enable = 0;
    }else{
        pInputPara->width_threshold.high_enable = 1;
        pInputPara->width_threshold.high_threshold = ui->MaxWidth->text().toFloat();
    }

    if(ui->MinWidth->text() == "---"){
        pInputPara->width_threshold.low_enable = 0;
    }else{
        pInputPara->width_threshold.low_enable = 1;
        pInputPara->width_threshold.low_threshold = ui->MinWidth->text().toFloat();
    }

    if(ui->MaxHeight->text() == "---"){
        pInputPara->heigh_threshold.high_enable = 0;
    }else{
        pInputPara->heigh_threshold.high_enable = 1;
        pInputPara->heigh_threshold.high_threshold = ui->MaxHeight->text().toFloat();
    }

    if(ui->MinHeight->text() == "---"){
        pInputPara->heigh_threshold.low_enable = 0;
    }else{
        pInputPara->heigh_threshold.low_enable = 1;
        pInputPara->heigh_threshold.low_threshold = ui->MinHeight->text().toFloat();
    }
    return 0;
}


void WHMeasureWidget::InitRangeData()
{

    if(pInputPara->pix_phy_flag == 0)
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
    if(pInputPara->width_threshold.low_enable == 0){
        ui->MinWidth->setText("---");
    }else{
        ui->MinWidth->setText(QString::number(pInputPara->width_threshold.low_threshold));
    }

    //获取X方向上限范围使能
    if(pInputPara->width_threshold.high_enable == 0){
        ui->MaxWidth->setText("---");
    }else{
        ui->MaxWidth->setText(QString::number(pInputPara->width_threshold.high_threshold));
    }


    //获取Y方向下限范围使能
    if(pInputPara->heigh_threshold.low_enable == 0){
        ui->MinHeight->setText("---");
    }else{
        ui->MinHeight->setText(QString::number(pInputPara->heigh_threshold.low_threshold));
    }


    //获取Y方向上限范围使能
    if(pInputPara->heigh_threshold.high_enable == 0){
        ui->MaxHeight->setText("---");
    }else{
        ui->MaxHeight->setText(QString::number(pInputPara->heigh_threshold.high_threshold));
    }
}

#if 0
/**
 * @brief WHMeasureWidget::InitComboBox
 * @param i_step_index
 * @author dgq
 * @note 初始化下拉框的显示
 */
void WHMeasureWidget::InitComboBox(int i_step_index)
{
    m_i_load_first = 0;
    unsigned int i_task_id = 0;
    int i = 0;
    ui->comboBoxLineStep->addItem("");
    ui->comboBoxLineIndex->addItem("");
    for(i = 0; i < i_step_index-1; i++)
    {
        int ret =Task_Step_Type_ID_Get(i+1,&i_task_id);
        if(ret == 0)
        {
            QString name = InitLineCombobox(i+1,i_task_id);
            if(!name.isEmpty())
                ui->comboBoxLineStep->addItem(QString::number(i+1)+"."+name);
        }
    }
    TASK_STEP_HEADER *pStephead = Task_Step_Head_Get(i_step_index);
    int i_task_index = pStephead->step_link.link_info[0].step_index;
    int i_result_index = pStephead->step_link.link_info[0].result_index;
    for(i = 0; i < ui->comboBoxLineStep->count(); i++)
    {
        if(i_task_index == atoi(ui->comboBoxLineStep->itemText(i).toStdString().c_str()))
            ui->comboBoxLineStep->setCurrentIndex(i);
    }
    ui->comboBoxLineIndex->addItem(" ");
    unsigned int i_mul_rst_cnt = 0;

    if(i_task_index > 0)
    {
        int ret = TaskMultiRstNumGet(i_task_index,1,&i_mul_rst_cnt);
        if(ret == 0)
        {
            for(i = 1; i < i_mul_rst_cnt+1; i++)
            {
                ui->comboBoxLineIndex->addItem(tr("直线")+QString::number(i));
            }
        }
    }
    LineParameter pLinePara;
    unsigned int id;
    Task_Step_Type_ID_Get(i_task_index,&id);
    int  Mul_Flag = Get_Multi_Result_Task_Flag(id);
    if(Mul_Flag == -1)
    {
        ui->comboBoxLineIndex->setEnabled(false);
    }else
    {
        ui->comboBoxLineIndex->setCurrentIndex(Point_Or_Line_Result_Id_Change_UI_Id(id,i_result_index));
    }
    measure_ref_line_result_get(i_task_index,i_result_index,(void*)&pLinePara,1);
    QLine line;
    Line_Osd_Init(&pLinePara,&line);
    ((FWWHMeasureLabel*)m_label)->SetOSDData(line);
    m_i_load_first = 1;
}

/**
 * @brief WHMeasureWidget::on_comboBoxLineStep_currentIndexChanged
 * @param index
 * @author dgq
 * @note 直线任务下拉框改变的响应函数
 */
void WHMeasureWidget::on_comboBoxLineStep_currentIndexChanged(int index)
{
    ((FWWHMeasureLabel*)m_label)->SetOSDData(QLine(0,0,0,0));
    if(m_i_load_first == 1)
    {
        int task_index = atoi(ui->comboBoxLineStep->currentText().toStdString().c_str());
        if(task_index == 0)
        {
            ui->comboBoxLineIndex->clear();
            return;
        }
        ui->comboBoxLineIndex->setEnabled(true);

        ui->comboBoxLineIndex->clear();
        ui->comboBoxLineIndex->addItem(" ");
        unsigned int id;
        Task_Step_Type_ID_Get(task_index,&id);
        int  Mul_Flag = Get_Multi_Result_Task_Flag(id);
        if(Mul_Flag == 1)
        {
            unsigned int i_mul_rst_cnt = 0;
            TaskMultiRstNumGet(task_index,1,&i_mul_rst_cnt);
            for(unsigned int i = 1; i <= i_mul_rst_cnt;i++)
            {
                QString strLineIndex;
                strLineIndex = "直线"+QString::number(i);
                ui->comboBoxLineIndex->addItem(strLineIndex);
            }
        }
        else
        {
            LineParameter pLinePara;
            ui->comboBoxLineIndex->setEnabled(false);

            int ret = measure_ref_line_result_get(task_index,Point_Or_Line_Result_Id_Change_UI_Id(id,0),(void*)&pLinePara,1);
            if(ret != 0)
            {
                QString info = tr("获取失败!")+tr("错误码111:")+QString::number(ret,16);
                QMessageBox::about(this,tr(""),info);
                return;
            }
            QLine line;
            Line_Osd_Init(&pLinePara,&line);
            ((FWWHMeasureLabel*)m_label)->SetOSDData(line);
        }
    }
}

/**
 * @brief WHMeasureWidget::on_comboBoxLineIndex_activated
 * @param index
 * @author dgq
 * @note 直线结果下拉框改变的响应函数
 */
void WHMeasureWidget::on_comboBoxLineIndex_activated(int index)
{
    if(m_i_load_first ==1)
    {
        LineParameter pLinePara;
        int Task_index = atoi(ui->comboBoxLineStep->currentText().toStdString().c_str());
        int Result_index = ui->comboBoxLineIndex->currentIndex();
        if(Result_index == 0)
        {
            ((FWWHMeasureLabel*)m_label)->SetOSDData(QLine(0,0,0,0));
            return;
        }
        unsigned int id;
        Task_Step_Type_ID_Get(Task_index,&id);
        int ret = measure_ref_line_result_get(Task_index,Get_Point_Or_Line_Result_Id(id,Result_index),(void*)&pLinePara,1);
        if(ret != 0)
        {
            QString info = tr("获取失败!")+tr("错误码:")+QString::number(ret,16);
            QMessageBox::about(this,tr(""),info);
            return;
        }
        QLine line;
        Line_Osd_Init(&pLinePara,&line);
        ((FWWHMeasureLabel*)m_label)->SetOSDData(line);
    }
}
#endif


void WHMeasureWidget::on_btnMoveUp_pressed()
{
    SetBtnRepeatParam(ui->btnMoveUp);
    if(ui->btnMoveUp->autoRepeatInterval() == 10)
        ((FWWHMeasureLabel*)m_label)->MoveUp(5);
    else
        ((FWWHMeasureLabel*)m_label)->MoveUp(1);
}

void WHMeasureWidget::on_btnMoveDown_pressed()
{
    SetBtnRepeatParam(ui->btnMoveDown);
    if(ui->btnMoveDown->autoRepeatInterval() == 10)
        ((FWWHMeasureLabel*)m_label)->MoveDown(5);
    else
        ((FWWHMeasureLabel*)m_label)->MoveDown(1);
}

void WHMeasureWidget::on_btnMoveLeft_pressed()
{
    SetBtnRepeatParam(ui->btnMoveLeft);
    if(ui->btnMoveLeft->autoRepeatInterval() == 10)
        ((FWWHMeasureLabel*)m_label)->MoveLeft(5);
    else
        ((FWWHMeasureLabel*)m_label)->MoveLeft(1);
}

void WHMeasureWidget::on_btnMoveRight_pressed()
{
    SetBtnRepeatParam(ui->btnMoveRight);
    if(ui->btnMoveRight->autoRepeatInterval() == 10)
        ((FWWHMeasureLabel*)m_label)->MoveRight(5);
    else
        ((FWWHMeasureLabel*)m_label)->MoveRight(1);
}

/**
 * @brief WHMeasureWidget::SetBtnRepeatParam
 * @param btn 需要设置长按参数的按钮
 * @author dgq
 * @note 设置按钮长按加速参数
 */
void WHMeasureWidget::SetBtnRepeatParam(QToolButton *btn)
{
    static int i_delay = 300;
    static int i_interV = 100;
    static int m_calc = 0;
    if(m_calc > 0)
    {
        stopTime = QTime::currentTime();
        int elapsed = startTime.msecsTo(stopTime);
        if(abs(elapsed )> i_interV)
        {
            m_calc = 0;
            i_delay = 300;
            i_interV = 100;
            btn->setAutoRepeat(false);
        }
    }
    m_calc++;
    if(m_calc < 2)
    {
        i_delay = 300;
        i_interV = 100;
    }
    if(m_calc > 2 && m_calc < 5)
    {
        i_delay = 100;
        i_interV = 100;
    }
    if(m_calc > 5)
    {
        i_delay = 10;
        i_interV = 10;
    }
    btn->setAutoRepeat(true);
    btn->setAutoRepeatDelay(i_delay);
    btn->setAutoRepeatInterval(i_interV);
}

/**
 * @brief BaseLineWidget::GetCurrentTime
 * @author dgq
 * @note 获取按钮释放的时间
 */
void WHMeasureWidget::GetCurrentTime()
{
    startTime = QTime::currentTime();
}

void WHMeasureWidget::on_radioButton_phy_clicked()
{
    if(pix_phy_flag == 0)
    {
        QMessageBox::StandardButton rb = QMessageBox::warning(NULL, tr("警告"), tr("切换数据类型会清空偏移量范围的数据，确定切换?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
        if(rb == QMessageBox::No)
        {
            ui->radioButton_pix->setChecked(true);
            return;
        }
        pix_phy_flag = 1;
        ui->txt_x_stat_threshold->setText("");
        ui->txt_y_stat_threshold->setText("");
        ui->MaxWidth->setText("---");
        ui->MaxHeight->setText("---");
        ui->MinWidth->setText("---");
        ui->MinHeight->setText("---");
    }

}

void WHMeasureWidget::on_radioButton_pix_clicked()
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
        ui->txt_x_stat_threshold->setText("");
        ui->txt_y_stat_threshold->setText("");
        ui->MaxWidth->setText("---");
        ui->MaxHeight->setText("---");
        ui->MinWidth->setText("---");
        ui->MinHeight->setText("---");
    }
}
