#include <QDebug>
#include "BlobWidget.h"
#include "ui_BlobWidget.h"
#include "FWMatchBlobLabel.h"
#include "QMessageBox"

BlobWidget::BlobWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BlobWidget)
{
    ui->setupUi(this);
    LoadKeyBoardLib();
    LoadLearnLib();
    QList<QLineEdit *> lineEdit = this->findChildren<QLineEdit *>();
    foreach (QLineEdit * L, lineEdit) {
        L->installEventFilter(this);
        }
    m_label = new FWMatchBlobLabel(this);
    m_label->setGeometry(10,10,640,480);
    m_label->setAutoFillBackground(true);
    QPalette p = m_label->palette();
    p.setColor(QPalette::Background,QColor(50,50,50,255));
    m_label->setPalette(p);
    Calc_rst_flag = 0;
    CalcTimer = new QTimer;
    connect(CalcTimer, &QTimer::timeout, this, &BlobWidget::CalcTimerSlot);
    m_i_load_first  = 0;
}

BlobWidget::~BlobWidget()
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
    delete ui;
}
/**
 * @brief BlobWidget::Get_Image_Pos
 * @return
 * @author dgq
 * @note 获取图像显示区域的位置
 */
QPoint BlobWidget::Get_Image_Pos()
{
    QPoint point(10,10);

    if(m_label != NULL)
    {
        point = m_label->pos();
    }
    return point;
}

/**
 * @brief BlobWidget::Init_Input_Ptr
 * @param ptr input结构体指针
 * @param i_step_index 当前步骤号
 * @param new_flag 新加步骤标志：1新加，0编辑
 * @author dgq
 * @note 初始化设置Input结构体指针
 */
void BlobWidget::Init_Input_Ptr(void *ptr,int i_step_index,int new_flag,void *pen_color)
{
    ((FWMatchBlobLabel*)m_label)->SetPenColor(pen_color);
    pInputPara = (BLOB_INPUT_PARAM*)ptr;
    m_step_index = i_step_index;
    if(pInputPara == NULL)
    {
        QMessageBox::about(this,tr(""),tr("初始化数据失败"));
        return;
    }
    if(new_flag)
    {
        Task_Step_Synthetic_Judge_Flag_Set(i_step_index,1);
        pInputPara->blob_num_max = 60;
        pInputPara->sort_type = BLOB_NO_SORT;
        pInputPara->degree_lock = 1;
        pInputPara->single_link_area.high_enable = 0;
        pInputPara->single_link_area.low_enable = 0;
        pInputPara->single_link_ratio.high_enable = 0;
        pInputPara->single_link_ratio.low_enable = 0;
        pInputPara->total_link_num.high_enable = 0;
        pInputPara->total_link_num.low_enable = 0;
        pInputPara->total_link_area.high_enable = 0;
        pInputPara->total_link_area.low_enable = 0;
    }
    InitData();
}

/**
 * @brief BlobWidget::eventFilter
 * @param watched
 * @param event
 * @return
 * @author dgq
 * @note 事件过滤器函数，行文本框模拟点击事件
 */
bool BlobWidget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->txtNum){
        if (event->type()==QEvent::MouseButtonPress){
            BlobNumInputPro();
        }
    }
    if(watched == ui->txtThresholdHigh){
        if (event->type()==QEvent::MouseButtonPress){
            RangeInputPro(ui->txtThresholdHigh,ui->txtThresholdLow,"0",THRESHOLD_HIGH);
        }
    }
    if(watched == ui->txtThresholdLow){
        if (event->type()==QEvent::MouseButtonPress){
            RangeInputPro(ui->txtThresholdHigh,ui->txtThresholdLow,"0",THRESHOLD_LOW);
        }
    }
    if(watched == ui->txtThresholdRatioHigh){
        if (event->type()==QEvent::MouseButtonPress){
            RangeInputPro(ui->txtThresholdRatioHigh,ui->txtThresholdRatioLow,"0",THRESHOLD_HIGH);
        }
    }
    if(watched == ui->txtThresholdRatioLow){
        if (event->type()==QEvent::MouseButtonPress){
            RangeInputPro(ui->txtThresholdRatioHigh,ui->txtThresholdRatioLow,"0",THRESHOLD_LOW);
        }
    }
    if(watched == ui->txtBlobCountMax){
        if (event->type()==QEvent::MouseButtonPress){
            RangeInputPro(ui->txtBlobCountMax,ui->txtBlobCountMin,ui->label_BlobCount->text(),THRESHOLD_HIGH);
        }
    }
    if(watched == ui->txtBlobCountMin){
        if (event->type()==QEvent::MouseButtonPress){
            RangeInputPro(ui->txtBlobCountMax,ui->txtBlobCountMin,ui->label_BlobCount->text(),THRESHOLD_LOW);
        }
    }
    if(watched == ui->txtBlobAreaMax){
        if (event->type()==QEvent::MouseButtonPress){
            RangeInputPro(ui->txtBlobAreaMax,ui->txtBlobAreaMin,ui->label_SumArea->text(),THRESHOLD_HIGH);
        }
    }
    if(watched == ui->txtBlobAreaMin){
        if (event->type()==QEvent::MouseButtonPress){
            RangeInputPro(ui->txtBlobAreaMax,ui->txtBlobAreaMin,ui->label_SumArea->text(),THRESHOLD_LOW);
        }
    }
    return QWidget::eventFilter(watched, event);
}

/**
 * @brief BlobWidget::BlobNumInputPro
 * @author dgq
 * @note blob最大检测个数的输入响应函数
 */
void BlobWidget::BlobNumInputPro()
{
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
                if( num.toInt()>=0 && num.toInt()<=60)
                {
                    ui->txtNum->setText(num);
                }
                else
                {
                    QString strTemp;
                    strTemp = tr("请输入0到60之间的数值");
                    QMessageBox::information(NULL,tr("提示"),strTemp);
                }
            }
        }
    }
}

/**
 * @brief BlobWidget::RangeInputPro
 * @param pEditMax 上限输入框
 * @param pEditMin 下限输入框
 * @param calc_value 计算值
 * @param flag 上限、下限标志 1上限，0下限
 * @author dgq
 * @note blob门限输入函数
 */
void BlobWidget::RangeInputPro(QLineEdit *pEditMax,QLineEdit *pEditMin,QString calc_value,int flag)
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

/**
 * @brief BlobWidget::InitData
 * @author dgq
 * @note 界面初始化函数
 */
void BlobWidget::InitData()
{
    m_i_load_first  = 0;
    int value;

    value = pInputPara->degree_lock;
    if(value == 0)
        ui->checkBox_AngleLock->setChecked(false);
    else
        ui->checkBox_AngleLock->setChecked(true);

    value = pInputPara->sort_type;

    if(value >=0 && value <= 8)
        ui->comboBoxSort->setCurrentIndex(value);
    value = pInputPara->blob_num_max;
    ui->txtNum->setText(QString::number(value));

    //获取单个连通域筛选上门限使能(1:使能； 0：不使能)
    if(pInputPara->single_link_area.high_enable == 1){
        value = pInputPara->single_link_area.high_threshold;
        ui->txtThresholdHigh->setText(QString::number(value));
    }else{
        ui->txtThresholdHigh->setText("---");
    }

    //获取单个连通域筛选下门限使能(1:使能； 0：不使能)
    if(pInputPara->single_link_area.low_enable == 1){
        value = pInputPara->single_link_area.low_threshold;
        ui->txtThresholdLow->setText(QString::number(value));
    }else{
        ui->txtThresholdLow->setText("---");
    }

    float f_value;
    //获取单个连通域长宽比筛选上门限使能(1:使能； 0：不使能)
    if(pInputPara->single_link_ratio.high_enable == 1){
        f_value = pInputPara->single_link_ratio.high_threshold;
        ui->txtThresholdRatioHigh->setText(QString::number(f_value));
    }else{
        ui->txtThresholdRatioHigh->setText("---");
    }
    //获取单个连通域长宽比筛选下门限使能(1:使能； 0：不使能)
    if(pInputPara->single_link_ratio.low_enable == 1){
        f_value = pInputPara->single_link_ratio.low_threshold;
        ui->txtThresholdRatioLow->setText(QString::number(f_value));
    }else{
        ui->txtThresholdRatioLow->setText("---");
    }


    //获取有效blob数量上门限使能(1:使能； 0：不使能)
    if(pInputPara->total_link_num.high_enable == 1){
        value = pInputPara->total_link_num.high_threshold;
        ui->txtBlobCountMax->setText(QString::number(value));
    }else{
        ui->txtBlobCountMax->setText("---");
    }

    //获取有效blob数量下门限使能(1:使能； 0：不使能)
    if(pInputPara->total_link_num.low_enable == 1){
        value = pInputPara->total_link_num.low_threshold;
        ui->txtBlobCountMin->setText(QString::number(value));
    }else{
        ui->txtBlobCountMin->setText("---");
    }

    //获取有效blob的面积总数上门限使能(1:使能； 0：不使能)
    if(pInputPara->total_link_area.high_enable == 1){
        value = pInputPara->total_link_area.high_threshold;
        ui->txtBlobAreaMax->setText(QString::number(value));
    }else{
        ui->txtBlobAreaMax->setText("---");
    }

    //获取有效blob的面积总数下门限使能(1:使能； 0：不使能)
    if(pInputPara->total_link_area.low_enable == 1){
        value = pInputPara->total_link_area.low_threshold;
        ui->txtBlobAreaMin->setText(QString::number(value));
    }else{
        ui->txtBlobAreaMin->setText("---");
    }
    //m_CGetImageThread->SetVgaDisplay(1,0,VGADISPLAY_PHYADDR,m_startx,m_starty);
    m_i_load_first  =1;
}

/**
 * @brief BlobWidget::LoadKeyBoardLib
 * @author dgq
 * @note 加载输入软键盘库
 */
void BlobWidget::LoadKeyBoardLib()
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

/**
 * @brief BlobWidget::LoadLearnLib
 * @author dgq
 * @note 加载取样进度条弹窗库
 */
void BlobWidget::LoadLearnLib()
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

/**
 * @brief BlobWidget::on_btnPrePage_clicked
 * @author dgq
 * @note 上一页
 */
void BlobWidget::on_btnPrePage_clicked()
{
    if(ui->stackedWidget->currentIndex() > 0)
    {
        ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()-1);
    }
    ui->label_CurrentIndex->setText(QString::number(ui->stackedWidget->currentIndex()+1));
    ui->label_AllIndex->setText(QString::number(ui->stackedWidget->count()));
}

/**
 * @brief BlobWidget::on_btnNextPage_clicked
 * @author dgq
 * @note 下一页
 */
void BlobWidget::on_btnNextPage_clicked()
{
    if(ui->stackedWidget->currentIndex() < ui->stackedWidget->count()-1)
    {
        ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()+1);
    }
    ui->label_CurrentIndex->setText(QString::number(ui->stackedWidget->currentIndex()+1));
    ui->label_AllIndex->setText(QString::number(ui->stackedWidget->count()));
}

/**
 * @brief BlobWidget::Set_Parameter_To_Ram
 * @author dgq
 * @note 将界面参数写入内存
 */
int BlobWidget::Set_Parameter_To_Ram()
{

    int value = 0;
    value = ui->comboBoxSort->currentIndex();
    pInputPara->sort_type = value;
    //设置最多检测个数
    value = ui->txtNum->text().toInt();
    pInputPara->blob_num_max = value;
    if(ui->checkBox_AngleLock->isChecked())
    {
        pInputPara->degree_lock = 1;
    }else
    {
        pInputPara->degree_lock = 0;
    }
    //设置单个连通域筛选下门限使能(1:使能； 0：不使能)
    if(ui->txtThresholdLow->text() == "---"){
        pInputPara->single_link_area.low_enable = 0;
    }else{
        pInputPara->single_link_area.low_enable = 1;
        value = ui->txtThresholdLow->text().toInt();
        pInputPara->single_link_area.low_threshold = value;
    }

    //设置单个连通域筛选上门限使能(1:使能； 0：不使能)
    if(ui->txtThresholdHigh->text() == "---"){
        pInputPara->single_link_area.high_enable = 0;
    }else{
        pInputPara->single_link_area.high_enable = 1;
        value = ui->txtThresholdHigh->text().toInt();
        pInputPara->single_link_area.high_threshold = value;
    }

    float f_value;
    //设置单个连通域长宽比筛选上门限使能(1:使能； 0：不使能)
    if(ui->txtThresholdRatioHigh->text() == "---"){
        pInputPara->single_link_ratio.high_enable = 0;
    }else{
        //设置单个连通域长宽比筛选上门限
        pInputPara->single_link_ratio.high_enable = 1;
        f_value = ui->txtThresholdRatioHigh->text().toFloat();
        pInputPara->single_link_ratio.high_threshold = f_value;
    }
    //设置单个连通域长宽比筛选下门限使能(1:使能； 0：不使能)
    if(ui->txtThresholdRatioLow->text() == "---"){
        pInputPara->single_link_ratio.low_enable = 0;
    }else{
        pInputPara->single_link_ratio.low_enable = 1;
        //设置单个连通域长宽比筛选下门限
        f_value = ui->txtThresholdRatioLow->text().toFloat();
        pInputPara->single_link_ratio.low_threshold = f_value;
    }

    //设置有效blob数量上门限使能(1:使能； 0：不使能)
    if(ui->txtBlobCountMax->text() == "---"){
        pInputPara->total_link_num.high_enable = 0;
    }else{
        pInputPara->total_link_num.high_enable = 1;
        value = ui->txtBlobCountMax->text().toInt();
        pInputPara->total_link_num.high_threshold = value;
    }

    //设置有效blob数量下门限使能(1:使能； 0：不使能)
    if(ui->txtBlobCountMin->text() == "---"){
        pInputPara->total_link_num.low_enable = 0;
    }else{
        pInputPara->total_link_num.low_enable = 1;
        value = ui->txtBlobCountMin->text().toInt();
        pInputPara->total_link_num.low_threshold = value;
    }

    //设置有效blob的面积总数上门限使能(1:使能； 0：不使能)
    if(ui->txtBlobAreaMax->text() == "---"){
        pInputPara->total_link_area.high_enable = 0;
    }else{
        pInputPara->total_link_area.high_enable = 1;
        value = ui->txtBlobAreaMax->text().toInt();
        pInputPara->total_link_area.high_threshold = value;
    }
    //设置有效blob的面积总数下门限使能(1:使能； 0：不使能)
    if(ui->txtBlobAreaMin->text() == "---"){
        pInputPara->total_link_area.low_enable = 0;
    }else{
        pInputPara->total_link_area.low_enable = 1;
        value = ui->txtBlobAreaMin->text().toInt();
        pInputPara->total_link_area.low_threshold = value;
    }
    return 1;
}

/**
 * @brief BlobWidget::Get_Result_From_Ram
 * @author dgq
 * @note 从内存中获取取样、计算的结果数据更新界面显示
 */
void BlobWidget::Get_Result_From_Ram()
{

    unsigned int blob_num = 0;
    unsigned int blob_sum_area = 0;
    BLOB_OSD_EDIT blob_osd_edit;
    BLOB_PRIVATE_PARAM *pPrivate = (BLOB_PRIVATE_PARAM *)Task_Step_Private_Para_Get(m_step_index);
    blob_num = pPrivate->model_blob_num;
    QStringList header;
    ui->tableWidget_CalcResult->setRowCount(blob_num);
    ui->tableWidget_CalcResult->setColumnCount(5);
    for(unsigned int i = 0; i < blob_num; i++)
    {
        float pix_vga_x = 0.0;
        float pix_vga_y = 0.0;
        float pix_sub_x = pPrivate->blob_model_rst[i].blob_center_pixel.x_f;
        float pix_sub_y = pPrivate->blob_model_rst[i].blob_center_pixel.y_f;
        PixelCvt((void *)(&pix_sub_x),(void *)(&pix_vga_x),CVT_SUB2VGA|CVT_F2F|CVT_DATA);
        PixelCvt((void *)(&pix_sub_y),(void *)(&pix_vga_y),CVT_SUB2VGA|CVT_F2F|CVT_DATA);
        blob_osd_edit.m_vt_point.append(QPoint(pix_vga_x,pix_vga_y));

        float pix_vga_w = 0.0;
        float pix_vga_h = 0.0;
        float pix_sub_w = pPrivate->blob_model_rst[i].blobWidth;
        float pix_sub_h = pPrivate->blob_model_rst[i].blobHeight;
        PixelCvt((void *)(&pix_sub_w),(void *)(&pix_vga_w),CVT_REAL2VGA|CVT_F2F|CVT_DATA);
        PixelCvt((void *)(&pix_sub_h),(void *)(&pix_vga_h),CVT_REAL2VGA|CVT_F2F|CVT_DATA);
        blob_osd_edit.m_blob_width.append(pix_vga_w);
        blob_osd_edit.m_blob_heigth.append(pix_vga_h);

        blob_osd_edit.m_angle.append(pPrivate->blob_model_rst[i].theta);
        header.append(tr("blob")+QString::number(i+1));
        ui->tableWidget_CalcResult->setItem(i,0,new QTableWidgetItem(QString::number(pPrivate->blob_model_rst[i].cur_area)));
        ui->tableWidget_CalcResult->setItem(i,1,new QTableWidgetItem(QString::number(pPrivate->blob_model_rst[i].degree)));
        ui->tableWidget_CalcResult->setItem(i,2,new QTableWidgetItem(QString::number(pPrivate->blob_model_rst[i].blobRatio)));
        ui->tableWidget_CalcResult->setItem(i,3,new QTableWidgetItem(QString::number(pPrivate->blob_model_rst[i].blobWidth)));
        ui->tableWidget_CalcResult->setItem(i,4,new QTableWidgetItem(QString::number(pPrivate->blob_model_rst[i].blobHeight)));
        blob_sum_area +=pPrivate->blob_model_rst[i].cur_area;
    }
    ((FWMatchBlobLabel *)m_label)->SetOSDData(&blob_osd_edit);
    ui->tableWidget_CalcResult->setVerticalHeaderLabels(header);
    ui->label_BlobCount->setText(QString::number(blob_num));
    ui->label_SumArea->setText(QString::number(blob_sum_area));
    if(ui->checkBox_AutoSetResult->isChecked() && Calc_rst_flag == 1)//如果是取样的结果就不能根据自动设置来更改门限值
    {
        ui->txtBlobCountMax->setText(QString::number((int)(blob_num*1.2)));
        ui->txtBlobCountMin->setText(QString::number((int)(blob_num*0.8)));

        ui->txtBlobAreaMax->setText(QString::number((int)(blob_sum_area*1.2)));
        ui->txtBlobAreaMin->setText(QString::number((int)(blob_sum_area*0.8)));
    }

}

/**
 * @brief BlobWidget::on_btnAutoCalc_clicked
 * @author dgq
 * @note 计算按钮响应函数
 */
void BlobWidget::on_btnAutoCalc_clicked()
{
    Set_Parameter_To_Ram();
    Fun_GetLearnDialog GetDialog = (Fun_GetLearnDialog)m_Learn_Lib.resolve("GetDialog");
    QDialog *dlg = GetDialog();
    CalcTimer->start(10);
    dlg->exec();
}

/**
 * @brief BlobWidget::CalcTimerSlot
 * @author dgq
 * @note 计算过程定时器响应函数
 */
void BlobWidget::CalcTimerSlot()
{
    Calc_rst_flag = 1;
    Fun_SetResultString SetResultString = (Fun_SetResultString)m_Learn_Lib.resolve("SetResultString");
    QString info = tr("正在计算，请稍等");
    SetResultString(info);
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
