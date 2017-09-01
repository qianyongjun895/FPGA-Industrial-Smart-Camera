#include <QDebug>
#include "SpotFlawWidget.h"
#include "ui_SpotFlawWidget.h"
#include "FWSpotFlawLabel.h"
#include <QMessageBox>

SpotFlawWidget::SpotFlawWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SpotFlawWidget)
{
    ui->setupUi(this);
    LoadKeyBoardLib();
    LoadLearnLib();
    QList<QLineEdit *> lineEdit = this->findChildren<QLineEdit *>();
    foreach (QLineEdit * L, lineEdit) {
        L->installEventFilter(this);
        }
    m_label = new FWSpotFlawLabel(this);
    m_label->setGeometry(10,10,640,480);
    m_label->setAutoFillBackground(true);
    QPalette p = m_label->palette();
    p.setColor(QPalette::Background,QColor(50,50,50,255));
    m_label->setPalette(p);

    CalcTimer = new QTimer;
    connect(CalcTimer, &QTimer::timeout, this, &SpotFlawWidget::CalcTimerSlot);
    m_i_load_first  = 0;

}

SpotFlawWidget::~SpotFlawWidget()
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

QPoint SpotFlawWidget::Get_Image_Pos()
{
    QPoint point(10,10);

    if(m_label != NULL)
    {
        point = m_label->pos();
    }
    return point;
}

int SpotFlawWidget::Set_Parameter_To_Ram()
{
    SetDataToLib();
    return 1;
}

void SpotFlawWidget::Init_Input_Ptr(void *ptr,int i_step_index,int new_flag,void *pen_color)
{
    ((FWSpotFlawLabel*)m_label)->SetPenColor(pen_color);
    pInputPara = (SPOT_FLAW_INPUT_PARAM *)ptr;
    m_step_index = i_step_index;
    if(pInputPara == NULL)
    {
        QMessageBox::about(this,tr(""),tr("初始化数据失败"));
        return;
    }
    if(new_flag)
    {
        Task_Step_Synthetic_Judge_Flag_Set(i_step_index,1);
        pInputPara->sort_type = FLAW_X_ASCEND_SORT;
        pInputPara->single_flaw_area_threshold.high_enable = 0;
        pInputPara->single_flaw_area_threshold.low_enable = 0;
        pInputPara->flaw_area_sum_threshold.high_enable = 0;
        pInputPara->flaw_area_sum_threshold.low_enable = 0;
        pInputPara->flaw_count_threshold.high_enable = 0;
        pInputPara->flaw_count_threshold.low_enable = 0;
    }
    InitData();

}


bool SpotFlawWidget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->txtSingleAreaMax){
        if (event->type()==QEvent::MouseButtonPress){
            RangeInputPro(ui->txtSingleAreaMax,ui->txtSingleAreaMin,ui->label_SingleArea->text(),THRESHOLD_HIGH);
        }
    }
    if(watched == ui->txtSingleAreaMin){
        if (event->type()==QEvent::MouseButtonPress){
            RangeInputPro(ui->txtSingleAreaMax,ui->txtSingleAreaMin,ui->label_SingleArea->text(),THRESHOLD_LOW);
        }
    }
    if(watched == ui->txtSumAreaMax){
        if (event->type()==QEvent::MouseButtonPress){
            RangeInputPro(ui->txtSumAreaMax,ui->txtSumAreaMin,ui->label_FlawNum->text(),THRESHOLD_HIGH);
        }
    }
    if(watched == ui->txtSumAreaMin){
        if (event->type()==QEvent::MouseButtonPress){
            RangeInputPro(ui->txtSumAreaMax,ui->txtSumAreaMin,ui->label_FlawNum->text(),THRESHOLD_LOW);
        }
    }
    if(watched == ui->txtFlawCountMax){
        if (event->type()==QEvent::MouseButtonPress){
            RangeInputPro(ui->txtFlawCountMax,ui->txtFlawCountMin,ui->label_FlawNum->text(),THRESHOLD_HIGH);
        }
    }
    if(watched == ui->txtFlawCountMin){
        if (event->type()==QEvent::MouseButtonPress){
            RangeInputPro(ui->txtFlawCountMax,ui->txtFlawCountMin,ui->label_FlawNum->text(),THRESHOLD_LOW);
        }
    }
    return QWidget::eventFilter(watched, event);
}

void SpotFlawWidget::RangeInputPro(QLineEdit *pEditMax,QLineEdit *pEditMin,QString calc_value,int flag)
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

void SpotFlawWidget::SetDataToLib()
{
    pInputPara->sort_type =ui->comboBoxSortWay->currentIndex()+1;

    int i_single_max = 0;
    int i_single_min = 0;
    //设置单缺陷面积上门限使能
    if(ui->txtSingleAreaMax->text() == "---"){
        pInputPara->single_flaw_area_threshold.high_enable = 0;
    }else{
        pInputPara->single_flaw_area_threshold.high_enable = 1;
        i_single_max = ui->txtSingleAreaMax->text().toInt();
        pInputPara->single_flaw_area_threshold.high_threshold = i_single_max;
    }

    //设置单缺陷面积下门限使能
    if(ui->txtSingleAreaMin->text() == "---"){
        pInputPara->single_flaw_area_threshold.low_enable = 0;
    }else{
        pInputPara->single_flaw_area_threshold.low_enable = 1;
        i_single_min = ui->txtSingleAreaMin->text().toInt();
        pInputPara->single_flaw_area_threshold.low_threshold= i_single_min;
    }

    int i_sum_max = 0;
    int i_sum_min = 0;
    //设置缺陷强度上门限使能
    if(ui->txtSumAreaMax->text() == "---"){
        pInputPara->flaw_area_sum_threshold.high_enable = 0;
    }else{
        pInputPara->flaw_area_sum_threshold.high_enable = 1;
        i_sum_max = ui->txtSumAreaMax->text().toInt();
        //设置缺陷强度上门限
        pInputPara->flaw_area_sum_threshold.high_threshold = i_sum_max;
    }

    //设置缺陷强度下门限使能
    if(ui->txtSumAreaMin->text() == "---"){
        pInputPara->flaw_area_sum_threshold.low_enable = 0;
    }else{
        pInputPara->flaw_area_sum_threshold.low_enable = 1;
        i_sum_min = ui->txtSumAreaMin->text().toInt();
        //设置缺陷强度下门限
        pInputPara->flaw_area_sum_threshold.low_threshold = i_sum_min;
    }

    int i_count_max = 0;
    int i_count_min = 0;
    //设置缺陷数量上门限使能
    if(ui->txtFlawCountMax->text() == "---"){
        pInputPara->flaw_count_threshold.high_enable = 0;
    }else{
        pInputPara->flaw_count_threshold.high_enable = 1;
        //设置缺陷数量上门限
        i_count_max = ui->txtFlawCountMax->text().toInt();
        pInputPara->flaw_count_threshold.high_threshold = i_count_max;
    }


    //设置缺陷数量下门限使能
    if(ui->txtFlawCountMin->text() == "---"){
        pInputPara->flaw_count_threshold.low_enable = 0;
    }else{
        pInputPara->flaw_count_threshold.low_enable = 1;
        i_count_min = ui->txtFlawCountMin->text().toInt();
        //设置缺陷数量下门限
        pInputPara->flaw_count_threshold.low_threshold = i_count_min;
    }
}

void SpotFlawWidget::GetDataFromLib()
{
    SPOT_FLAW_PRIVATE_PARAM *pPrivate = (SPOT_FLAW_PRIVATE_PARAM *)Task_Step_Private_Para_Get(m_step_index);
    //获取缺陷总面积
    unsigned int i_FlawSum = pPrivate->model_spot_flaw_rst.flaw_area_sum;
    //获取缺陷点数据
    int i_flaw_cnt = pPrivate->model_spot_flaw_rst.flaw_cnt;
    QVector<QPoint> flawPoints;
    QVector<unsigned int> i_FlawArea;
    for(int  i = 0 ; i < i_flaw_cnt; i++)
    {
        float pix_vga_x = 0.0;
        float pix_vga_y = 0.0;
        float pix_sub_x = pPrivate->model_spot_flaw_rst.flaw_info[i].pos.x_i;
        float pix_sub_y = pPrivate->model_spot_flaw_rst.flaw_info[i].pos.y_i;
        PixelCvt((void *)(&pix_sub_x),(void *)(&pix_vga_x),CVT_SUB2VGA|CVT_F2F|CVT_DATA);
        PixelCvt((void *)(&pix_sub_y),(void *)(&pix_vga_y),CVT_SUB2VGA|CVT_F2F|CVT_DATA);

        flawPoints.append(QPoint(pix_vga_x,pix_vga_y));
        i_FlawArea.append(pPrivate->model_spot_flaw_rst.flaw_info[i].area);
    }
    ((FWSpotFlawLabel *)m_label)->SetFlawsCenterPoint(flawPoints);

    ui->label_SumArea->setText(QString::number(i_FlawSum));
    ui->label_FlawNum->setText(QString::number(i_flaw_cnt));
    if(i_flaw_cnt > 0){
        ui->label_SingleArea->setText(QString::number(i_FlawSum/i_flaw_cnt));
    }
    if(ui->checkBoxAuto->isChecked())
    {
        ui->txtSumAreaMax->setText(QString::number((int)(i_FlawSum*1.2)));
        ui->txtSumAreaMin->setText(QString::number((int)(i_FlawSum*0.8)));
        ui->txtFlawCountMax->setText(QString::number((int)(i_flaw_cnt*1.2)));
        ui->txtFlawCountMin->setText(QString::number((int)(i_flaw_cnt*0.8)));
    }
    //获取缺陷面积 = ((SpotFlawData*)m_p_data)->GetFlawArea();

    ui->tableWidget_CalcResult->setRowCount(i_flaw_cnt);
    for(int i = 0; i < i_flaw_cnt; i++)
    {
        ui->tableWidget_CalcResult->setItem(i,0,new QTableWidgetItem(QString::number(i_FlawArea[i])));
    }
}

void SpotFlawWidget::InitData()
{
    //获取排序方式,见枚举：SORT_TYPE
    unsigned int i_sortType = pInputPara->sort_type;
//    if(i_sortType < 0)
//        i_sortType = 0;
    ui->comboBoxSortWay->setCurrentIndex(i_sortType-1);

    //获取单缺陷面积上门限使能
    if(pInputPara->single_flaw_area_threshold.high_enable == 1){
        //获取单缺陷面积上门限
        int i_singleAreaMax = pInputPara->single_flaw_area_threshold.high_threshold;
        ui->txtSingleAreaMax->setText(QString::number(i_singleAreaMax));
    }else{
        ui->txtSingleAreaMax->setText("---");
    }
    //获取单缺陷面积下门限使能
    if(pInputPara->single_flaw_area_threshold.low_enable == 1){
        //获取单缺陷面积下门限
        int i_singleAreaMin = pInputPara->single_flaw_area_threshold.low_threshold;
        ui->txtSingleAreaMin->setText(QString::number(i_singleAreaMin));
    }else{
        ui->txtSingleAreaMin->setText("---");
    }


    //获取缺陷总面积上门限使能
    if(pInputPara->flaw_area_sum_threshold.high_enable == 1){
        //获取缺陷强度上门限
        int i_AreaSumMax = pInputPara->flaw_area_sum_threshold.high_threshold;
        ui->txtSumAreaMax->setText(QString::number(i_AreaSumMax));
    }else{
        ui->txtSumAreaMax->setText("---");
    }

    //获取缺陷强度下门限使能
    if(pInputPara->flaw_area_sum_threshold.low_enable == 1){
        //获取缺陷强度下门限
        int i_AreaSumMin = pInputPara->flaw_area_sum_threshold.low_threshold;
        ui->txtSumAreaMin->setText(QString::number(i_AreaSumMin));
    }else{
        ui->txtSumAreaMin->setText("---");
    }

    //获取缺陷数量上门限使能
    if(pInputPara->flaw_count_threshold.high_enable == 1){
        //获取缺陷数量上门限
        int i_FlawCountMax = pInputPara->flaw_count_threshold.high_threshold;
        ui->txtFlawCountMax->setText(QString::number(i_FlawCountMax));
    }else{
        ui->txtFlawCountMax->setText("---");
    }

    //获取缺陷数量下门限使能
    if(pInputPara->flaw_count_threshold.low_enable == 1){
        //获取缺陷数量下门限
        int i_FlawCountMin = pInputPara->flaw_count_threshold.low_threshold;
        ui->txtFlawCountMin->setText(QString::number(i_FlawCountMin));
    }else{
        ui->txtFlawCountMin->setText("---");
    }


}

void SpotFlawWidget::LoadKeyBoardLib()
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
 * @brief TaskDetectSpotFlaw::on_btnNextPage_clicked
 * @note 下一页
 */
void SpotFlawWidget::on_btnNextPage_clicked()
{
    if(ui->stackedWidget->currentIndex() < ui->stackedWidget->count()-1)
    {
        ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()+1);
    }
    ui->label_CurrentIndex->setText(QString::number(ui->stackedWidget->currentIndex()+1));
    ui->label_AllIndex->setText(QString::number(ui->stackedWidget->count()));
}

/**
 * @brief TaskDetectSpotFlaw::on_btnPrePage_clicked
 * @note 上一页
 */
void SpotFlawWidget::on_btnPrePage_clicked()
{
    if(ui->stackedWidget->currentIndex() > 0)
    {
        ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()-1);
    }
    ui->label_CurrentIndex->setText(QString::number(ui->stackedWidget->currentIndex()+1));
    ui->label_AllIndex->setText(QString::number(ui->stackedWidget->count()));
}

void SpotFlawWidget::on_btnAutoCalc_clicked()
{
    SetDataToLib();
    Fun_GetLearnDialog GetDialog = (Fun_GetLearnDialog)m_Learn_Lib.resolve("GetDialog");
    QDialog *dlg = GetDialog();
    CalcTimer->start(10);
    dlg->exec();
}


void SpotFlawWidget::CalcTimerSlot()
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

void SpotFlawWidget::LoadLearnLib()
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
